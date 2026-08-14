/* ===========================================================================
 * func_1505D6F0  --  conker/src/game_83300.c   (1004 B, frame 0x88)
 * PARKED near-miss.  Cold start this wave.
 *
 * BEST SCORE SO FAR: 5895  (asm-differ -o func_1505D6F0 -R --max-lines 4096;
 *                           identical with and without -R)
 * Progression: 11365 (draft 1) -> 6075 (float locals) -> 6050 (count=25 hoisted
 *              into the entry block) -> 5895 (dy split into two statements).
 *
 * NOTE: this file also needs the file-scope prototype
 *     void func_1505D6F0(struct127 *arg0, s32 arg1);
 * added to the prototype block at the top of game_83300.c, because the TU
 * already calls func_1505D6F0 at line ~567 (func_15059140) and without a
 * prototype IDO implicitly declares it `int f()` and then rejects the `void`
 * definition.  Adding the prototype was measured NOT to disturb func_15059140
 * (still scores 0).
 *
 * ---------------------------------------------------------------------------
 * FRAME DECODE (golden)
 *   framesize 0x88.
 *     0x00..0x33  arg build (13 words: func_1505D5D0 takes 13 args, last at
 *                 0x30(sp)), padded to 0x38 for the sdc1 alignment
 *     0x38..0x67  sdc1 f20,f22,f24,f26,f28,f30
 *     0x68..0x6B  alignment pad
 *     0x6C..0x87  sw s0,s1,s2,s3,s4,s5,ra
 *   => LOCAL HOME AREA IS ZERO BYTES.  Golden homes no local at all.
 *   My current C needs 0x98: 8 extra bytes of temp area below the saved regs
 *   AND 16 bytes of local home above them, of which only 0x88 is ever touched
 *   -- that is `count`, which golden keeps in $s5.  See RESIDUAL below.
 *
 * REGISTER MAP (golden)
 *   s0 = obj (walks D_800CC2D0, += 0x32C)     s1 = i
 *   s2 = arg0                                  s3 = arg1
 *   s4 = the constant 1 (CSE'd; used by three `== 1` tests and by `count = 1`)
 *   s5 = count
 *   f20 = (f32)arg0->unkE4      f22 = arg0->unkEC     f24 = arg0->x_position
 *   f26 = arg0->y_position + (f32)(s16)arg0->unkE8    f28 = arg0->z_position
 *   f30 = 120.0f  (loop-invariant constant, hoisted into the preheader)
 *   f12 = dx   f14 = dz   f16 = distSq   f18 = otherRadius
 *   f0  = sumRadius        f2 = dy
 *   (mine currently agrees on f12/f14/f16/f18 but has dy=f0 / sumRadius=f2,
 *    i.e. those two are SWAPPED.)
 *
 * RODATA PROBE: NOT NEEDED / NOT BLOCKED.
 *   Every float constant in this function has low16 == 0 and inlines via
 *   lui+mtc1: 0x42F00000 (120.0f), 0x437A0000 (250.0f), 0xC3020000 (-130.0f),
 *   0x43020000 (130.0f), 0x430C0000 (140.0f), 0xC2480000 (-50.0f),
 *   0x3F000000 (0.5f), 0.0f (mtc1 zero).  D_80099530 is an ordinary extern f32
 *   global (lui %hi / lwc1 %lo of a symbol), not a compiler literal.
 *   => this function is NOT in the rodata class.
 *
 * ---------------------------------------------------------------------------
 * RESIDUAL, classified
 *
 * 1. ALLOCATION (dominant, ~15 rows + the frame + every branch displacement):
 *    `count` is spilled to 0x88(sp) instead of living in $s5.  Golden uses six
 *    callee-saved GPRs (s0..s5); mine stops at five (s0..s4) and puts count in
 *    memory.  s0..s4 already agree exactly with golden.  Every `continue`
 *    branch-likely delay slot therefore holds `lw t6,0x88(sp)` where golden
 *    holds `addiu s1,s1,1`.
 *    Ruled out: moving `count = 0x19;` from just-before-the-loop to the first
 *    statement of the function.  That WAS right -- it moved the `li` into the
 *    entry basic block as golden has it, worth 6075 -> 6050 -- but it did not
 *    stop the spill.
 *
 * 2. ALLOCATION (~10 rows): dy and sumRadius are swapped, dy=f0/sumRadius=f2
 *    where golden has dy=f2/sumRadius=f0.  Everything else in the FP pool
 *    (f12=dx, f14=dz, f16=distSq, f18=otherRadius) already matches.
 *
 * 3. SCHEDULING (2 rows): golden emits `add.s $f10,$f22,$f4`
 *    (selfW first, obj->unkEC second) where I emit `add.s $f6,$f10,$f22`
 *    (obj->unkEC first).  Likewise golden's `mul.s $f2,$f2,$f6` has dy first
 *    and the 0.5f-scale second; mine has the scale first.
 *
 * 4. BASIC BLOCK (2 rows): golden splits the D_800CC2D0 address materialisation
 *    across the `blez count` guard -- `lui s0,%hi(...)` before it, `addiu
 *    s0,s0,%lo(...)` in the PREHEADER after it.  Writing `obj = D_800CC2D0` in
 *    the for-init (the version below) puts both before the guard.
 *    SOLVED, but not adopted -- see the INDEXED FORM note.
 *
 * 5. RELOCATION (2 rows, `i` flagged): golden's .s says
 *        lui v0,%hi(D_800CC5EC) / lw v0,%lo(D_800CC5EC)(v0)
 *    where the natural C `D_800CC2D0[arg1].unk31C` gives
 *        lui v0,%hi(D_800CC2D0) / lw v0,%lo(D_800CC2D0+0x31c)(v0).
 *    D_800CC5EC == &D_800CC2D0[0].unk31C exactly, so the LINKED bytes are
 *    identical and the ROM is unaffected; only the REL addend split differs
 *    (HI16 field 0 both sides, LO16 field 0x031C vs 0x0000).  splat named the
 *    resolved address because game_131620.c declares
 *        extern struct126 *D_800CC5EC;
 *    and uses it as a scalar.  To make the objects bit-identical this has to be
 *    spelled through that symbol.  NOT YET RESOLVED -- see TODO.
 *
 * ---------------------------------------------------------------------------
 * MEASURED NEGATIVES / POSITIVES (each with its score)
 *   11365  draft 1: arg0->x_position / z_position / unkEC read inline at the
 *          use sites.  WRONG -- golden hoists five arg0 values into the
 *          callee-saved FP registers f20..f28, so they are locals.
 *    6075  + selfRadius/selfW/selfX/selfY/selfZ locals, + otherRadius local
 *          (golden converts obj->unkE4 to float in the block BEFORE the
 *          D_800BE616 test, so it cannot be part of the later sumRadius add).
 *    6050  + `count = 0x19;` hoisted to the first statement (golden's
 *          `li s5,0x19` sits in the entry basic block, before the
 *          `bne s4,t6` that guards the interaction_state==1 branch).
 *    5895  + dy written as TWO statements
 *              dy = selfY - (obj->y_position + (f32)(s16)obj->unkE8);
 *              dy = dy * ((selfW + obj->unkEC) * 0.5f);
 *          This is the in-place FP statement form; it is what moved dx to f12
 *          and dz to f14 (they were f2 and f12 before).  Single-statement dy
 *          scores 6050 and mis-allocates dx/dz.
 *
 * ---------------------------------------------------------------------------
 * INDEXED FORM  (5910) -- measured, and structurally MORE faithful than the
 * 5895 version below.  Delete the `obj` local, write the loop as
 *     for (i = 0; i < count; i++)
 * and replace every `obj->` with `D_800CC2D0[i].` and `obj` with
 * `&D_800CC2D0[i]` at the two call sites.  IDO strength-reduces the index into
 * exactly golden's preheader pointer:
 *     79b4 lui s0,%hi(D_800CC2D0)      <- above the guard, as golden
 *     79c0 bgez ...
 *     79d4 blez ...
 *     79e0 addiu s0,s0,%lo(D_800CC2D0) <- in the preheader, as golden
 * so residual 4 disappears.  It costs 15 points elsewhere: the guard becomes
 * `blezl t7` + `lw ra,0x84(sp)` instead of golden's `blez s5` + `move s1,zero`,
 * because the spilled `count` has to be reloaded before the branch and so
 * steals the delay-slot candidate.  BOTH of those two-row misses are downstream
 * of residual 1; once `count` wins $s5 the indexed form should strictly win.
 * The 5895 cursor form is kept below only because it is the better MEASURED
 * number today.
 *
 * ---------------------------------------------------------------------------
 * RULED OUT for residual 1 (`count` spill) -- ALL SIX scored 5910, i.e.
 * IDENTICAL to the base.  By the N-no-ops test that is evidence about the
 * MEASUREMENT, not about the constructs: none of these axes reaches the thing
 * that decides the spill.
 *     5910  `count` declared first among the locals
 *     5910  `count` declared last among the locals
 *     5910  explicit `s32 active = 1;` variable used for the three `== 1`
 *           comparisons and for `count = active;`  (the idiom the sibling loop
 *           func_1502378C in game_49D30.c uses).  NOTE: this variant DID make
 *           IDO use six callee-saved GPRs (s0..s5) and it STILL spilled count
 *           to 0x8C(sp) with s6/s7 free -- so the spill is NOT register
 *           exhaustion, IDO is declining to promote `count`.
 *     5910  `register s32 count;`
 *     5910  `register s32 i; register s32 count;`
 *     5910  every local declared `register`
 *           (IDO 5.3 ignores the storage class at -O2.)
 *
 * TODO next: (a) make `count` win $s5 -- the whole remaining gap is downstream
 *                of this; it is worth ~15 rows plus the frame size plus every
 *                branch displacement in the function;
 *            (b) swap dy/sumRadius in the FP pool (residual 2);
 *            (c) resolve the D_800CC5EC spelling (residual 5).
 * =========================================================================== */

extern u8 D_800BE616;
extern u8 D_800CC26C;
extern u8 D_800CC26D;
extern f32 D_80099530;
extern struct127 D_800CC2D0[];

void func_1505D408(struct127 *arg0, struct127 *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s32 arg7);
void func_1505D5D0(struct127 *arg0, struct127 *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s32 arg7,
                   f32 arg8, f32 arg9, f32 arg10, f32 arg11, f32 arg12);

void func_1505D6F0(struct127 *arg0, s32 arg1) {
    struct126 *tmp;
    struct127 *obj;
    s32 i;
    s32 count;
    f32 selfRadius;
    f32 selfW;
    f32 selfX;
    f32 selfY;
    f32 selfZ;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 otherRadius;
    f32 sumRadius;
    f32 distSq;

    count = 0x19;
    D_800CC268 = 0;
    D_800CC26C = 0;
    D_800CC26D = 0;

    if (arg0->interaction_state == 1) {
        tmp = D_800CC2D0[arg1].unk31C;
        if (tmp->unk4E != 0) {
            return;
        }
        if (tmp->unk27 != 0) {
            return;
        }
    }
    if (arg0->unk13D >= 0x64) {
        return;
    }
    if (arg0->unkE4 == 0) {
        return;
    }
    if (arg0->unk65 != 0) {
        return;
    }
    if (arg0->unkF8 & 0x1000000) {
        return;
    }
    if (arg0->unkF8 & 0x4000) {
        return;
    }

    /* structs.h types struct127::unkE8 as u16, but golden reads it with `lh`
       (1505D7E0: lh $t4,0xE8($s2) and 1505D8A8: lh $t3,0xE8($s0)), i.e. it is
       signed.  The header is shared by 106 TUs so it is not retyped here. */
    selfRadius = (f32) arg0->unkE4;
    selfW = arg0->unkEC;
    selfX = arg0->x_position;
    selfY = arg0->y_position + (f32) (s16) arg0->unkE8;
    selfZ = arg0->z_position;

    if (arg0->unkF8 & 0x2000000) {
        count = 1;
    }

    for (i = 0, obj = D_800CC2D0; i < count; i++, obj++) {
        if (obj->interaction_state == 0) {
            continue;
        }
        if (obj->unkE4 < 2) {
            continue;
        }
        if ((obj->unkF8 & 0x2000000) && (arg0->unk127 == 0xFF)) {
            continue;
        }
        if (obj->unkF8 & 0x1000000) {
            continue;
        }
        if (i == arg1) {
            continue;
        }
        if (arg1 + 1 == obj->unk65) {
            continue;
        }
        if (obj->unk13D >= 0x64) {
            continue;
        }
        if (obj->unk2FA == 0) {
            continue;
        }

        dx = selfX - obj->x_position;
        dz = selfZ - obj->z_position;
        dy = selfY - (obj->y_position + (f32) (s16) obj->unkE8);
        dy = dy * ((selfW + obj->unkEC) * 0.5f);
        otherRadius = (f32) obj->unkE4;

        if (D_800BE616 != 0) {
            if (((dx * dx) + (dy * dy)) + (dz * dz) < D_80099530) {
                /* structs.h has `u32 pad128` at 0x128; golden reads it with
                   lbu (1505D944/1505D948), so a u8 lives there. */
                if ((arg0->interaction_state == 1) && (obj->interaction_state == 1) &&
                    (*(u8 *) &obj->pad128 != *(u8 *) &arg0->pad128)) {
                    tmp = arg0->unk31C;
                    if (tmp->unk78 == 0) {
                        if (obj->unk31C->unk78 != 0) {
                            tmp->chased = 0x14;
                        }
                    }
                }
            }
        }

        sumRadius = selfRadius + otherRadius;
        distSq = ((dx * dx) + (dy * dy)) + (dz * dz);
        if (distSq < (sumRadius * sumRadius)) {
            func_1505D408(arg0, obj, dx, dy, dz, distSq, sumRadius, i);
        }
        if (obj->id != 0x34) {
            continue;
        }
        if (obj->unk251 == 2) {
            func_1505D5D0(arg0, obj, selfX, selfY, selfZ, selfW, selfRadius, i,
                          120.0f, 250.0f, 120.0f, -130.0f, 0.0f);
        } else {
            func_1505D5D0(arg0, obj, selfX, selfY, selfZ, selfW, selfRadius, i,
                          130.0f, 140.0f, 250.0f, -50.0f, 0.0f);
        }
    }
}
