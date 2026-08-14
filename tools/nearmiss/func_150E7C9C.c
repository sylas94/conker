/* ===========================================================================
 * func_150E7C9C  --  game_113D60.c  --  848 B, frame 0xA8, 4 callees, 12 fp
 *
 * BEST SCORE: 1466 (asm-differ -R --max-lines 4096).  Cold start this wave.
 *
 * RESIDUAL CLASS: **rodata float literal** (NOT allocation / scheduling /
 * basic-block / as1-peephole).  The whole 1466 is the downstream cascade of a
 * SINGLE extra instruction:
 *
 *     golden (inside the loop):   lui  $at, %hi(D_800A1350)
 *                                 lwc1 $f10, %lo(D_800A1350)($at)
 *     mine   (loop preheader):    lui   $s6, %hi(D_800A1350)
 *                                 addiu $s6, $s6, %lo(D_800A1350)
 *            (inside the loop):   lwc1  $f10, 0($s6)
 *
 * D_800A1350 is NOT a variable.  asm/data/245C90.rodata.s:181 gives
 *     D_800A1350 = .float 0.4315068424      ( == 63.0f / 146.0f )
 * and the caller-side context proves it is a source-level FLOAT LITERAL:
 * func_150E7994 (live C, same TU, ~line 320) builds the spline control points
 * as -146.0f .. +146.0f, and the value here is fed to func_10010F30 (a sound
 * call) as its u8 `pan' argument together with + 64.0f -- i.e. the original
 * expression is  x * (63.0f/146.0f) + 64.0f, mapping [-146,146] -> [1,127].
 *
 * Because this project /DISCARD/s live-C .rodata (all rodata comes from the
 * external asm/data/*.s blobs), a non-inlinable literal has to be written as
 * `extern f32 D_800A1350'.  A literal is a link-time CONSTANT to IDO and its
 * %hi/%lo pair is never a loop-invariant-code-motion candidate; an extern
 * VARIABLE's address is an ordinary loop invariant, and with s6/s7 free IDO
 * promotes it into $s6.  That one extra callee-saved web renumbers every temp
 * register in the loop and shifts the saved-register block by 4/8 bytes, which
 * is where the 1466 comes from.
 *
 * PROOF (single-variable experiment, everything else identical):
 *     (sp98[0] * D_800A1350) + 64.0f          -> 1466   ($s6 hoist present)
 *     (sp98[0] * 0.4375f)    + 64.0f          ->  604   ($s6 hoist GONE;
 *         0.4375f = 0x3EE00000, low16 == 0, so it inlines as lui+mtc1 with no
 *         rodata.  Every branch target and every saved-reg offset in the
 *         prologue/epilogue then matches golden exactly -- diff lines 3,5,
 *         8..19, 199..214 all disappear.  0.4375f is semantically WRONG, it is
 *         only a probe.)
 * => needs_rodata_migration = YES.  Unblocking needs the 0x800A130C..0x800A1364
 *    literal run migrated into game_113D60's own .rodata (conker.us.yaml
 *    `[0xADDR, .rodata, game_113D60]` + splat --modes ld), which cannot be done
 *    while the other ~20 functions of this TU are still #pragma GLOBAL_ASM and
 *    own literals interleaved in the same block.
 *
 * RULED OUT for the hoist, each measured:
 *   extern const f32 D_800A1350;                       -> 1466 (no change)
 *   (D_800A1350 * sp98[0]) + 64.0f  (operand swap)     -> 1466 (no change)
 *   naming the two ternary results as s32 locals a,b   -> 1466 (byte-identical
 *       object; they are never homed, so they are pure register temps)
 *
 * ---------------------------------------------------------------------------
 * FRAME DECODE (read off golden, then validated against the built object)
 *   framesize 0xA8
 *   0x00..0x2F  argbuild   = roundup(4 * 12 args, 16) = 0x30   [func_150E75A0]
 *   0x30..0x5F  fp saves   f20,f22,f24,f26,f28,f30 (6 doubles)
 *   0x60..0x7F  gp saves   0x60 pad, s0..s5 @0x64..0x78, ra @0x7C
 *   0x80..0xA7  locals + temps (40 B)
 *       0xA4  f32 t                    (1st declared)
 *       0xA0  Emitter *p               (2nd declared)
 *       0x98  f32 sp98[2]              (3rd declared; address taken -> $s5)
 *       0x80..0x97  compiler temps
 *   The parked source reproduces this EXACTLY: frame 0xA8, s5 = sp+0x98,
 *   swc1 to 0x98/0x9c.  Declaration ORDER is load-bearing here:
 *       p, sp98, t   -> frame 0xB0, sp98 @0x9C   (score 1479)
 *       t, p, sp98   -> frame 0xA8, sp98 @0x98   (score 1466)  <-- golden
 *
 * REGISTER MAP (golden)
 *   $s3 = obj (param)             $s0 = p = &obj->unk28
 *   $s4 = compiler copy of $s0 used only by the rotated bottom-of-loop test
 *         (NOT a source variable -- my C reproduces `or $s4,$s0,$zero' too)
 *   $s5 = &sp98 (hoisted)         $s1 = second ternary (2), $s2 = first (4)
 *   $f22 = 1.0f  $f24 = 12.0f  $f26 = 30.0f  $f28 = 25.0f  $f30 = 100.0f
 *   $f20 = t (first func_150ADA68 result, live across 3 calls)
 *
 * OTHER LEVERS THAT PAID ON THE WAY DOWN (all still in the parked source):
 *   1614 -> 1479 : `if (...) { do {...} while (...); }' instead of `while'.
 *                  Golden's ENTRY test reloads obj->unk2C (lwc1 0x2C($s3),
 *                  right after the store through $s3) but its BOTTOM test
 *                  reloads p->unk4 (lwc1 0x4($s0)).  A plain `while' emits the
 *                  same expression twice, so the two tests must be two
 *                  different source expressions -> guard + do/while.
 *                  Same edit fixed 64.0f (0x42800000 is 64.0, not 128.0).
 *   1479 -> 1466 : `p->unkA != p->unk8' not `p->unk8 != p->unkA'.  IDO reverses
 *                  comparison operands and evaluates the RIGHT operand's load
 *                  first: golden is `lh t6,8(s0); lh t7,0xa(s0); beql t6,t7'.
 *
 * PROTOTYPES DERIVED FROM GOLDEN (all confirmed by the callee frames)
 *   func_150E75A0(f32 *, f32, s32, u8, u32, u8, s16, s16, s32, s32, u8, s32)
 *     -- a3 is u8 because golden emits `andi $t8,$a3,0xFF; or $a3,$t8,$zero'
 *        (identical shape to func_10010F30's declared `u8 arg2');
 *     -- arg4 is UNSIGNED-32, not u8: golden emits the 0x4F000000-biased
 *        float->unsigned inline sequence with NO trailing andi, which is what
 *        IDO emits when a float expression is passed to an unsigned 32-bit
 *        parameter.  (The callee reads it back with `lbu 0x9B($sp)', i.e. it
 *        narrows internally -- that is the callee's business, not the caller's.)
 *   func_10010F30 already correct in include/functions.h.
 *
 * NO shared header was edited.  Everything above is file-local.
 * =========================================================================== */

typedef struct {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
} Struct150E7C9CPt;

typedef struct {
    /* 0x00 */ f32 unk0;   /* emission rate                                  */
    /* 0x04 */ f32 unk4;   /* accumulator; == obj->unk2C, same address       */
    /* 0x08 */ s16 unk8;   /* control-point count (from func_150E7994 arg0)  */
    /* 0x0A */ s16 unkA;   /* cursor                                         */
    /* 0x0C */ s32 unkC;
    /* 0x10 */ Struct150E7C9CPt unk10[1];  /* obj+0x38, the spline points    */
} Struct150E7C9CEmitter;

typedef struct {
    /* 0x00 */ u8 pad0[0x1];
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 pad2[0xA];
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 padD[0x1];
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 pad10[0x18];
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
} Struct150E7C9CObj;

extern f32 D_800A1350;   /* rodata literal 63.0f/146.0f -- see header above */
extern void func_150E75A0(f32 *arg0, f32 arg1, s32 arg2, u8 arg3, u32 arg4, u8 arg5,
                          s16 arg6, s16 arg7, s32 arg8, s32 arg9, u8 arg10, s32 arg11);

void func_150E7C9C(Struct150E7C9CObj *obj) {
    f32 t;
    Struct150E7C9CEmitter *p;
    f32 sp98[2];

    p = (Struct150E7C9CEmitter *)&obj->unk28;
    obj->unk2C += obj->unk28 * D_800BE9A4;
    if (obj->unk2C > 1.0f && p->unkA != p->unk8) {
        do {
            sp98[0] = p->unk10[p->unkA].x;
            sp98[1] = p->unk10[p->unkA].y;
            t = func_150ADA68();
            func_150E75A0(sp98, (t * 12.0f) + 30.0f, 0x12C,
                          ((func_150ADA20() & 1) ? 4 : 0) | ((func_150ADA20() & 1) ? 2 : 0),
                          (func_150ADA68() * 25.0f) + 100.0f, 0xFF, 1, 0xFF, 0, 0, obj->unkC, obj->unk1);
            func_10010F30(0x360, 0x7FFF, (sp98[0] * D_800A1350) + 64.0f, 0, 0);
            p->unkA++;
            p->unk4 -= 1.0f;
        } while (p->unk4 > 1.0f && p->unkA != p->unk8);
    }
    if (p->unkA >= p->unk8) {
        obj->unkE = -1;
    }
}
