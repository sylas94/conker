/* ===========================================================================
 * func_150E7C9C  --  game_113D60.c  --  848 B, frame 0xA8, 4 callees, 12 fp
 *
 * BEST SHIPPABLE SCORE: 1466 (asm-differ -R --max-lines 4096).  Re-measured
 * this wave from this exact file: 1466 with -R and 1466 without.  Unchanged.
 *
 * ###########################################################################
 * ## THE RODATA MIGRATION IS IMPOSSIBLE.  DO NOT RE-PLAN IT.               ##
 * ###########################################################################
 * `- [0x245E10, .rodata, game_113D60]' (four bytes, D_800A1350 alone) cannot
 * work, on two independent grounds, both measured this wave:
 *   (1) IDO emits .rodata with sh_addralign 16 and pads sh_size to a multiple
 *       of 16 -- all 14 objects in this tree that have a .rodata are align 16,
 *       size 0x10/0x20/0x30, no exceptions.  Building this TU with the literal
 *       inlined gives
 *           .rodata PROGBITS 00000000 00de40 000010 01  A  0  0 16
 *           0000 3edcee77 00000000 00000000 00000000
 *       i.e. FOUR bytes of content in a SIXTEEN byte section.  0x800A1350 is
 *       16-aligned, so the start is fine, but the twelve pad bytes would land
 *       on ROM 0x245E14..0x245E1F, which is
 *           00245e10: 3edcee77 442ec000 43ff8000 3f483128
 *       -- D_800A1354 / D_800A1358 / D_800A135C, all owned by func_150E81A8
 *       and func_150E8470.  The ROM breaks.  A migrated range must be
 *       16-aligned, a multiple of 16, AND end in bytes that are zero in the
 *       ROM; only a COMPLETE original-TU rodata block satisfies that, which is
 *       exactly what conker.us.yaml's two existing migrations (0x247780 and
 *       0x24F480) are.
 *   (2) The whole-block alternative is closed by the segment layout.  splat's
 *       `migrate_rodata_to_functions' would put each still-stubbed function's
 *       rodata into its own asm/nonmatchings/*.s (asm-processor reserves it in
 *       source order via `const char _asmpp_rodataN[N]', asm_processor.py:844)
 *       -- but splat only pairs `.rodata' with `c' when they are SIBLINGS, and
 *       siblings are assigned per parent code segment
 *       (splat/segtypes/common/code.py:259-270).  conker.us.yaml puts C text in
 *       segment `game' (vram 0x15000000) and rodata in segment `game_data'
 *       (vram 0x80082B20), so they never are.  MEASURED on the game_64120
 *       block: after `- [0x23CD10, .rodata, game_64120]' and a FULL re-split,
 *       every nonmatchings .s came back .text-only and the rodata symbols were
 *       still in undefined_syms_auto.txt.  The stubs' rodata is dropped.
 *   Migrating this TU's block (0x245C90..0x245EAF) therefore needs ~14 more
 *   functions decompiled first: func_150E68B0, 150E6B84, 150E7290, 150E8470,
 *   150E8B1C, 150E8D5C, 150E9178, 150E93DC (and the live func_150E81A8 /
 *   150E6E34 / 150E70EC / 150E71E4 / 150E88C0 / 150E8A80 / 150E90DC switched
 *   from `extern f32' to literals in the same edit).
 *
 * ---------------------------------------------------------------------------
 * WHAT THE LITERAL PROBE ACTUALLY SAYS -- THE OLD 604 FIGURE WAS WRONG
 * ---------------------------------------------------------------------------
 * Re-run with the CORRECT value spelled inline (0.4315068424f == 0x3EDCEE77,
 * the true D_800A1350), everything else identical to the code below:
 *     score -R = 399, score without -R = 399   (not 604; 604 was 0.4375f,
 *     which is a DIFFERENT constant and mismeasures the residual)
 * At 399 the asm-differ output contains **no inserted, deleted or reordered
 * instruction** -- every diff line is either a temp-register renumbering or a
 * stack-frame constant.  Exactly two things are wrong:
 *     13ec: addiu sp,sp,-0xa8   vs   addiu sp,sp,-0xa0     (8 bytes short)
 *     1498: addiu s5,sp,0x98    vs   addiu s5,sp,0x90      (sp98 8 lower)
 * plus a $t-register rotation running through the whole loop
 * (golden lh t2 / t9 / t0 / t1 / t3 ... where mine has t0 / t8 / t9 / t0 / t1).
 * Both symptoms are ONE cause: golden reserves 8 more bytes between the gp
 * saves (which end at 0x80, identical in both) and sp98, i.e. it has two more
 * 4-byte webs than my source creates.  Golden never touches 0x80..0x97: the
 * only stack references above 0x80 in the golden .s are swc1/lwc1 0x98 and
 * 0x9C.  They are DEAD HOLES -- the frame-decode lever's signature for
 * declared-but-register-resident autos.
 *
 * !! CORRECTION TO THE OLD FRAME DECODE BELOW !!  The claim "the parked source
 * reproduces this EXACTLY: frame 0xA8" is a FALSE POSITIVE.  The parked source
 * only reaches 0xA8 because the `extern f32' hoist forces $s6 to be saved,
 * which costs 8 bytes of save area.  Take the hoist away and the true frame is
 * 0xA0.  The declaration list is 8 bytes SHORT of golden and always has been.
 *
 * TWO CANDIDATE DECLARATION LISTS TRIED AND MEASURED (both worse, both
 * genuinely informative -- do not repeat them):
 *   A. `s32 a; s32 b;' declared after sp98, carrying the two ternaries:
 *          a = (func_150ADA20() & 1) ? 4 : 0;
 *          b = (func_150ADA20() & 1) ? 2 : 0;   ... func_150E75A0(..., a | b, ...)
 *      -> 399 becomes 409, frame STILL 0xa0 (a and b land in $s1/$s2, which are
 *      callee-saved, so IDO gives them no home), AND it introduces a new error
 *      golden `or a3,s1,s2' vs mine `or a3,s2,s1'.  Since the inline-ternary
 *      form gets that `or' operand order RIGHT, this measurement CONFIRMS the
 *      inline ternaries are golden's form.  Naming them is wrong twice over.
 *   B. `s32 idc; s32 typ;' declared after sp98 for the last two arguments
 *          idc = obj->unkC; typ = obj->unk1;  ... func_150E75A0(..., idc, typ)
 *      -> 1694, frame 0xB0 (these DO get homed, +8, and IDO then also hoists
 *      into $s6/$s7 costing another 8) and s5 becomes s7.  Far worse.
 *   So the missing 8 bytes are NOT the ternary results and NOT the two byte
 *   loads.  Whatever they are, they are two webs that IDO keeps in CALLER-saved
 *   registers (that is what earns a home) and that add no instruction of their
 *   own.  Next wave should hunt there, using the literal probe (0.4315068424f)
 *   as the measuring instrument, because the `extern f32' form's frame is
 *   contaminated by the $s6 save and cannot see this at all.
 *
 * OLD FIGURE, RETAINED FOR THE RECORD: 1466 was and is the shippable score.
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
 *     (sp98[0] * D_800A1350)      + 64.0f     -> 1466   ($s6 hoist present)
 *     (sp98[0] * 0.4375f)         + 64.0f     ->  604   (wrong constant; the
 *         hoist is gone but this figure understates how close the C is)
 *     (sp98[0] * 0.4315068424f)   + 64.0f     ->  399   (the TRUE constant;
 *         0x3EDCEE77 goes to the TU's own .rodata, IDO treats it as a literal
 *         again, the $s6 hoist disappears and NOT ONE instruction differs from
 *         golden -- only the frame size and the $t rotation.  See the block at
 *         the top of this comment.)
 * => needs_rodata_migration = YES, and the migration is IMPOSSIBLE; the two
 *    independent proofs are at the top of this comment.  This function is
 *    blocked behind a whole-TU campaign, not behind a yaml line.
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
