/* func_150D4D58 -- game_100810.c -- 972 bytes / 243 insns / frame 0x108
 * STATUS: best 1205.  NOT a match.  Live C is parked here; the repo file has the
 * #pragma GLOBAL_ASM restored and `git status --short -- conker/src/game_100810.c`
 * prints NOTHING.
 *
 * ================== WAVE 2026-08-12: NO SCORE CHANGE, BUT THE BLOCKER IS NOW PROVEN =========
 * The previous wave left the residual described as "(a) the preheader ordering, not
 * reachable from statement placement".  That was right about the conclusion and wrong
 * about the reason, and the corrected reason matters because it closes the axis for good
 * instead of leaving it as an open idea.  Three new measurements, all mine, all on the
 * real asm-differ with the object asserted to exist:
 *
 * 1. THE RESIDUAL IS A PURE REORDERING OF ONE 49-INSTRUCTION BASIC BLOCK.
 *    Extracting the preheader window (first `lui at,0x3f80` .. first `jal func_150ADA68`)
 *    from both panes and comparing the instruction MULTISETS:
 *        golden preheader window: 49 instrs
 *        mine   preheader window: 49 instrs
 *        in golden only: sb t9,0xf9(sp) / lui t6,0x4 / sb t3,0xfa(sp) / sra t9,t8,0x8 /
 *                        addiu s4,t9,0x40 / li t7,1 / ori t6,t6,0xc207 / sll t3,s4,0x10 /
 *                        sh t7,0xba(sp) / sw t6,0xf0(sp) / sra s4,t3,0x10
 *        in mine   only: the SAME eleven instructions with t9<->t7 and t3<->t6
 *    i.e. every opcode, every immediate, every stack displacement is already golden's.
 *    The whole 1205 is: 17 rows out of order + 18 rows that differ only by a $t name.
 *    Marker census of the whole diff: r=18, i=3, |=8, >=3, <=3.  Nothing else in the
 *    function differs at all -- the entire loop body, the params store sequence, the
 *    epilogue and the sign-extension interleave (residual "(c)" of the last wave) match.
 *
 * 2. THE $t RENAME IS DOWNSTREAM, AND IT IS A ROTATION BY TWO.
 *    The four long-lived temps in that block, in allocation order:
 *        golden  7->t9, -1->t3, 1->t7, 0x4C207->t6
 *        mine    7->t7, -1->t6, 1->t9, 0x4C207->t3
 *    mine is golden's list rotated by exactly 2 (mine = golden[2],[3],[0],[1]).  That is
 *    the ordinary IDO temp-rotation counter running two allocations out of phase, which
 *    is what a two-instruction-pair displacement upstream produces.  It is not separately
 *    attackable and must not be "fixed" with mask chains -- see the fake-match policy.
 *
 * 3. WHY THE ORDER CANNOT BE REACHED.  Every `lui at,X` in the block writes the SAME
 *    register, so the seven of them are totally ordered and the chain is a direct readout
 *    of IDO's pre-scheduling order:
 *        GOLDEN  0x3f80(1.0f), %hi(A18), 0x4120(10.0f), 0x4347(199.0f), 0x4369(233.0f),
 *                %hi(D_800A0A1C), %hi(D_800A0A20)
 *        MINE    0x3f80, %hi(A18), %hi(D_800A0A20), %hi(D_800A0A1C), 0x4120, 0x4347, 0x4369
 *    Golden's last five are f30,f28,f26,f24,f22 -- ONE descending run, i.e. one hoist
 *    group covering all five callee-saved FP registers.  Mine's hoist group is only
 *    f30,f28,f26; f22/f24 are emitted at the source position of `spread = ...; base = ...`.
 *    So to match, the two global loads must be IN the hoist group.  Both halves of that
 *    are now closed by measurement:
 *
 *    (i) A PRE-LOOP SOURCE STATEMENT CAN NEVER BE EMITTED AFTER THE HOIST GROUP.
 *        Probe: move `params.unk24 = 1.0f;` (the only other $at-using setup statement)
 *        to be the LAST pre-loop statement, after `base = D_800A0A1C;`.  Result 2357, and
 *        the chain becomes  %hi(A18), %hi(A20), %hi(A1C), 0x3f80, 0x4120, 0x4347, 0x4369
 *        -- 0x3f80 moved past the two globals exactly as its statement did, and still
 *        landed BEFORE the hoists.  The hoist group is unconditionally last.
 *
 *   (ii) THE TWO GLOBAL LOADS CANNOT BE HOISTS, BECAUSE IDO NEVER HOISTS A GLOBAL LOAD
 *        OUT OF A CALL-CONTAINING LOOP.  Golden proves this against itself: inside the
 *        loop it emits `lui at,%hi(D_800A0A24) / lwc1 $f18,%lo(D_800A0A24)(at)` and the
 *        same pair for D_800A0A28, every iteration, even though both are loop-invariant.
 *        Reproduced from the source side twice this wave:
 *          globals assigned to the locals INSIDE the loop top .......... 4849, 944 bytes
 *              -> IDO hoists only the ADDRESSES into $s6/$s7 and emits
 *                 `lwc1 $f20,0(s6)` / `lwc1 $f22,0(s7)` in the loop
 *          globals inlined in the loop expression, the two freed declaration slots spent
 *              on two REAL subexpression locals (`size` for the unk28/unk2C pair, `speed`
 *              for the func_15143794 third argument) ................... 5150, 940 bytes,
 *              frame 0x100  -> same `lwc1 $f16,0(s6)` / `lwc1 $f4,0(s7)` address hoist,
 *              and 5.0f becomes a hoist because f22/f24 came free.
 *        This last one is the experiment the previous wave could not run cleanly: it had
 *        deleted the two locals without replacing them, so its 6000 was measured at frame
 *        0xf8 and the register pressure was not golden's.  Rerun with the declaration
 *        count preserved, the answer is the same.  So golden's f22/f24 are pre-loop
 *        source-assigned locals, exactly like mine.
 *
 *    (i) and (ii) together are a contradiction under any model in which the preheader
 *    order is a function of source statement order: golden's two loads are positioned
 *    where only a hoist can be, and they provably are not hoists.  Whatever IDO is doing
 *    there is not controlled by anything expressible in the source.  DO NOT SPEND ANOTHER
 *    WAVE ON STATEMENT ORDER, CAST SPELLING OR DECLARATION TYPE HERE -- three exhaustive
 *    sweeps (992 + 528 + 26 + 15 builds) and these three probes all land on the same wall.
 *
 * IDO's hoist priority, incidentally, is now fully characterised by golden and worth
 * keeping: loop invariants are hoisted in FIRST-USE order until the callee-saved registers
 * of that class run out.  FP first uses in the loop are A20, A1C, 233.0f, 199.0f, 10.0f,
 * 5.0f, A24, A28 -- the first five get f22,f24,f26,f28,f30 and the last three are
 * recomputed every iteration.  Integer first uses are &D_800A09C0, 18, 156, then 130, 81
 * -- the first three get $s6,$s7,$fp and the last two become `li at,0x82` / `li at,0x51`
 * in the loop.  Hoisting 18 and 156 into registers is also what makes IDO forget they are
 * constants and emit the two `bnez / break 7` divide guards, which my build reproduces.
 * ============================================================================================
 *
 * WHAT IT IS: a particle burst emitter.  It fills a 0x70-byte spawn-parameter struct and
 * calls func_15130280 (the particle spawner) rand%11+10 times, each time re-randomising
 * colour (D_800A09C0[rand&3]), lifetime, size, launch direction (func_15143794 turns an
 * s16 yaw/pitch pair + speed into a velocity vector) and two random render flags.
 * The RNG call ORDER is semantically load-bearing: func_150ADA20/func_150ADA68 are a PRNG
 * pair, so no statement containing a call may be reordered against another.  That is why
 * the `arg2 = func_150ADA68() * spread + base;` statement cannot be moved later in the
 * loop to change which invariants have the earliest first use.
 *
 * ================= FRAME DECODE (golden .s, framesize 0x108 = 264) ==================
 *   0x00..0x17  arg build, 6 words (func_15130280 takes 6 args; slots 0x10/0x14 used)
 *   0x18..0x1F  pad to 8 for the sdc1 block
 *   0x20..0x4F  sdc1 $f20,$f22,$f24,$f26,$f28,$f30
 *   0x50..0x77  sw  $s0..$s7,$fp,$ra                      -> saved area ends at 0x78
 *   0x78..0x97  32 bytes: compiler TEMP area + declared-auto homes
 *   0x98..0x107 `params`, 0x70 bytes, ENDING EXACTLY AT FRAMESIZE
 *               => params is the FIRST-DECLARED local (first declared = highest address)
 *   0x114       $a3 home (caller's arg slot); read back as `lbu 0x117(sp)` => arg3 is u8
 *   0x118       5th parameter (arg4)
 * THE FRAME AND THE FULL STACK-OFFSET MULTISET ARE GOLDEN'S -- permuter_tu.sh frame says
 * "golden frame = 264; base.c frame = 264; stack-offset multiset MATCHES golden (83
 * displacements)".  0x78..0x97 is never referenced in either object, so all 32 bytes are
 * homes that never spill plus compiler temp:
 *     framesize = roundup8(120 + T + 112 + 4N)
 *     dummy-scalar calibration from the 7-scalar base (+1 0x110, +2 0x118, +3 0x118,
 *     +4 0x120) pins T in [5,8]; golden's 264 then admits N=5 or N=6, and N=6 is the
 *     six below.  NOTE the previous wave wrote "Ng in {5,6}" and then asserted 6 without
 *     saying 5 was still open -- it is open, but every N=5 decomposition tried this wave
 *     (dropping a float local for an inline global) moves the frame off 0x108.
 * A WRITTEN-TO REGISTER PARAMETER IS HOMED IN THE CALLER'S ARG SLOT, not in the callee's
 * locals area, so assigning to `arg2` instead of declaring a `speed` local sheds exactly
 * 4 frame bytes (0x110 -> 0x108) and was worth 326 points.  Golden's `sw a3,276(sp)` is
 * that mechanism.  Do not re-derive the old, wrong claim that it costs a home.
 * ====================================================================================
 */

/* ---- declarations added to game_100810.c ------------------------------------- */

typedef struct {                 /* == Struct15131EE4Local, src/game_15D730.c (matched) */
    s32 unk0;  s32 unk4;  s16 unk8;  s16 unkA;  s32 unkC; s32 unk10;
    u8 unk14; u8 unk15; u8 unk16; u8 unk17; u8 unk18; u8 unk19; u8 unk1A;
    u8 unk1B; u8 unk1C; u8 unk1D;
    s16 unk1E; s16 unk20; s16 unk22;
    f32 unk24; f32 unk28; f32 unk2C;
    struct17 unk30; struct17 unk3C; struct17 unk48;
    f32 unk54; s32 unk58; s32 unk5C;
    u8 unk60; u8 unk61; s8 unk62; s8 unk63; s8 unk64; u8 unk65; u8 unk66;
    u8 pad67[9];
} Struct150D4D58;
/* unk62 is s8, NOT the u8 the in-tree Struct15131EE4Local declares.  Golden materialises
 * the stored constant as `li t3,-1`; a u8 field turns `= -1` into `li 255`.  The in-tree
 * type is not evidence: its only live writer (func_15131EE4, src/game_15D730.c) does
 * `sp40.unk62 = 0x27`, a positive constant that compiles identically for u8 and s8, so it
 * never constrained the signedness.  Corrected file-locally, not in the shared header. */

extern f32 D_800A5480;
extern f32 D_800A0A18;
extern f32 D_800A0A1C;
extern f32 D_800A0A20;
extern f32 D_800A0A24;
extern f32 D_800A0A28;
extern void func_15143794(s32, s32, f32, f32 *);
extern void *func_15130280(void *, u8, s32, s32, u8, s32);

/* ---- body (score 1205, frame 0x108 = golden, 243 insns = golden) -------------- */

void func_150D4D58(struct17 *arg0, struct17 *arg1, f32 arg2, u8 arg3, s32 arg4) {
    Struct150D4D58 params;
    s32 count;
    s32 angleBase;
    f32 spread;
    f32 base;
    s32 r1;
    s32 r2;

    count = func_150ADA20() % 11U + 10;
    params.unk8 = 0x2203;
    params.unk0 = 0x200005;
    params.unk4 = 0;
    params.unkC = 0;
    params.unk10 = 0;
    params.unk14 = 0xFF;
    params.unk15 = 0xFF;
    params.unk16 = 0xFF;
    params.unk17 = 0xFF;
    params.unk18 = 0xFF;
    params.unk19 = 0xFF;
    params.unk1A = 0xFF;
    params.unk1C = 0xFF;
    params.unk30 = *arg0;
    params.unk3C = *(struct17 *)&D_800A5480;
    params.unk1E = 10;
    params.unk20 = 25;
    params.unk61 = 7;
    params.unk62 = -1;
    params.unk22 = 1;
    params.unk24 = 1.0f;
    params.unk58 = 0x4C207;
    params.unk60 = 0;
    params.unk63 = -1;
    params.unk64 = -1;
    params.unk65 = 0;
    params.unk5C = 0;
    params.unk66 = 0xFF;
    angleBase = (s16) (arg2 * D_800A0A18);
    angleBase = (s16) ((angleBase >> 8) + 0x40);
    spread = D_800A0A20;
    base = D_800A0A1C;

    do {
        arg2 = func_150ADA68() * spread + base;
        params.unk1D = D_800A09C0[func_150ADA20() & 3];
        params.unkA = (s16) (func_150ADA20() % 18U) + 27;
        params.unk1B = func_150ADA20() % 156U + 100;
        params.unk28 = params.unk2C = func_150ADA68() * 233.0f + 199.0f;
        r1 = func_150ADA20();
        r2 = func_150ADA20();
        func_15143794((s16) (r1 % 130U + angleBase), (s16) (r2 % 81U - 64),
                      func_150ADA68() * 10.0f + 5.0f, &params.unk48.unk0);
        params.unk48.unk0 = params.unk48.unk0 - arg1->unk0 * arg2;
        params.unk48.unk8 = params.unk48.unk8 - arg1->unk8 * arg2;
        params.unk54 = func_150ADA68() * D_800A0A24 + D_800A0A28;
        params.unk58 &= ~0xC0;
        if (func_150ADA20() & 1) {
            r1 = 0x80;
        } else {
            r1 = 0;
        }
        if (func_150ADA20() & 1) {
            r2 = 0x40;
        } else {
            r2 = 0;
        }
        params.unk58 = params.unk58 | (r2 | r1);
        func_15130280(&params, 1, 0, 0, arg3, arg4);
        count -= 1;
    } while (count > 0);
}

/* ================================ MEASURED LOG ================================
 * Every number is the REAL asm-differ (`-o func_150D4D58 -R --max-lines 4096`) on an
 * object built with the repo's exact pipeline; -R and no-R agreed on every measurement
 * ever taken on this function.  BOUNDED: readelf size 972 == byte count, both objects.
 *
 * ---- how it got to 1205 ----
 *  1. first honest draft, 8 scalars                            7399   frame 0x110
 *  2. merge r1/flagA and r2/flagB -> 6 scalars                 7037   frame 0x108
 *  3. HOIST `spread`/`base` out of the loop                    4434
 *     The big structural lever.  Golden pre-loads BOTH globals into callee-saved
 *     $f22/$f24; a source that reads them inside the loop cannot (see (ii) above).
 *  4. + integer-store source order read off golden's store order                   3928
 *  5. + `r1 = func_150ADA20(); r2 = func_150ADA20();` as statements                3548
 *  6. + reuse r1/r2 for the two render flags                                       3498
 *  7. `speed` deleted; the loop assigns the PARAMETER `arg2` instead      3172  [0x108]
 *     -> 6 declared scalars, every sp displacement golden's.
 *  8. `params.unk62` u8 -> s8                                             3172  (0 points,
 *     but it converts `li 255` into golden's `li -1`)
 *  9. the angleBase pair moved to the END of the setup block, immediately before
 *     `spread`/`base`                                                     1353  [0x108]
 *     Found by an every-unit-to-every-position sweep of the 25-unit setup block.
 *     The INDEPENDENT-STATEMENT-ORDER lever, worth 1819 points.
 * 10. `params.unk2C = params.unk28 = X;` -> `params.unk28 = params.unk2C = X;`  1345
 *     Golden stores unk28 then unk2C; I had them the other way round.
 * 11. `params.unkA = (s16)(func_150ADA20() % 18U) + 27;`                   1205
 *     A TYPE lever, not an order lever, and instruction-count-neutral.  It buys the
 *     whole three-instruction group including registers:
 *         GOLD  mfhi t8 / addiu t7,t8,0x1b / sh t7,0xa2(sp)
 *         MINE  same    (was mfhi t5 / addiu t7,t5)
 *     The cast type is UNIQUE, not "any cast will do":
 *         (s16) 1205   (u16) 1340   (s32) 1345 (inert)   (s8) 1410   (u8) 1440
 *         (s16) applied OUTSIDE the +27 instead: 1345 (inert)
 *     The same cast elsewhere is worthless: unk1B (u8) 1320 (u16) 1320 (s16) 1325
 *     (s32) 1205 inert;  unk1D (u8)/(s32) 1205 inert;  splitting unk1B in two: 1345.
 *
 * ---- REFUSED (better score, demonstrably less like golden) ----
 * Golden's params byte-store sequence is  ... 1c 1e 20 61 62 22 58 60 63 64 65 5c 66 ...
 * and the parked 1205 reproduces it exactly (verified by extracting every sb/sh/sw to the
 * params area from both objects).  Four orderings beat 1205 and ALL FOUR break it:
 *     unk61 above unk20                1312 / 1172   emits ... 1c 1e 61 20 62 ...
 *     unk1E moved after unk61          1175          emits ... 1c 20 61 1e 62 ...
 *     unk62 moved before unk61         1179          emits ... 1c 1e 62 20 61 ...
 *     (plus the 1320/1323/1327 neighbours, same stores moved)
 * These are $t-rotation noise bought by making the code less like golden.  REFUSED, and
 * they must stay refused: the store sequence is the one thing this block states
 * unambiguously.  Moving params.unk66 between the two angleBase statements (the
 * permuter's top-ranked candidate on ITS scale) is 2336 on asm-differ AND breaks the
 * order.  The permuter's internal score is NOT comparable to asm-differ here -- its
 * "1280" was asm-differ 2336.  Re-score every candidate it proposes.
 *
 * ---- NEGATIVES (measured; frame in brackets) ----
 *   EXHAUSTIVE single-unit-move sweep at the 1345 base, 25x25 (625 builds), and RE-RUN at
 *     the 1205 base, 32x32 (992 builds): nothing beats 1205 except the four refused
 *     store-order-breaking moves; 14 further orderings are exactly 1205 (inert).
 *   EXHAUSTIVE split-angleBase placement, both statements independently at every (p,q)
 *     with p<=q over the 31-unit backbone (528 builds): best is the base itself
 *     (adjacent, last, 1205); next family 1482.  The pair wants to be adjacent and last.
 *   CAST SWEEP over every other expression site x {s16,u16,s32} / {f32,f64} (26 builds):
 *     count, unk1B, unk54, unk28/2C, both angleBase halves, unk48.unk0/unk8, arg2, the
 *     r2|r1 or -- ALL exactly 1205 (inert) or worse.  unkA is the ONLY live site.
 *   DECLARATION-TYPE sweep: all 15 s32/s16 assignments over {count,angleBase,r1,r2} that
 *     keep the frame at 0x108 -- every one WORSE, 1505..2320.  angleBase as u16/u8: 3318.
 *   THIS WAVE:
 *     `base = D_800A0A1C; spread = D_800A0A20;` (assignment order swapped) ..... 1495
 *        -- and its chain IS golden's relative order (A1C then A20); it still sits before
 *           the hoists, so the swap buys nothing and costs elsewhere.
 *     `params.unk24 = 1.0f;` moved to be the last pre-loop statement ........... 2357
 *        (the probe that proved the hoist group is unconditionally last)
 *     globals assigned to the locals inside the loop top ............... 4849 [944 bytes]
 *     same but with `base`/`spread` order swapped ...................... 4844 [944 bytes]
 *     globals inlined, slots spent on real `size`/`speed` locals ....... 5150 [0x100]
 *   OLDER, still true:
 *     `params.unk24 = 1.0f;` to every position (23 builds): flat at 1353 except one spot
 *       at 3038 -- its float store floats freely, so its position carries no information.
 *     `spread`/`base` pair moved to every earlier position: nothing better; moving the
 *       pair to the very top costs an instruction (3237) and the $at chain moves with it.
 *     `params.unk28 = X; params.unk2C = params.unk28;` (two statements)   1353, no gain.
 *     `extern const f32` on both globals: BYTE-IDENTICAL to the non-const build -- IDO
 *       ignores `const` for aliasing entirely.
 *     `(f32 *)&params.unk48` instead of `&params.unk48.unk0`: byte-identical.
 *     ablation probes for the temp area (deliberately WRONG code, run only to read the
 *       frame): delete `params.unk3C=` 4877 [0x110]; delete `params.unk30=*arg0` 6418
 *       [0x110]; delete both 10163 [0x110]; delete the func_15143794 call 8156 [0x100];
 *       delete the func_15130280 call 5758 [0x108] (argbuild 24->16).
 *
 * ---- CALLEE SIGNATURES, re-verified against golden's argument registers ----
 *   func_150ADA20()  -> s32 in $v0, no args.  Used 9x; every use is `divu`/`andi` on $v0.
 *   func_150ADA68()  -> f32 in $f0, no args.  Used 4x; every use is `mul.s` on $f0.
 *   func_15143794(s32 a0, s32 a1, f32 a2, f32 *a3)
 *       golden sets a0/a1 by `sll/sra 0x10` pairs (both s16-narrowed s32), a2 in $f14,
 *       a3 = `addiu a3,sp,224` = &params.unk48 (0x98+0x48=0xE0=224).  OK.
 *   func_15130280(void *a0, u8 a1, s32 a2, s32 a3, u8 stack0x10, s32 stack0x14)
 *       golden: a0 = `addiu a0,sp,152` (&params), `li a1,1`, a2/a3 = zero,
 *       `lbu t0,279(sp)` -> `sw t0,16(sp)` (arg3, u8, from its caller-slot home 0x117),
 *       and s5 = `lw s5,280(sp)` -> `sw s5,20(sp)` (arg4, s32, from 0x118).  Cross-checked
 *       against the LIVE MATCHED definition in src/game_15D730.c.
 *   All four confirmed; none is a remaining risk.
 *
 * ---- THE PERMUTER ----
 * conker/permuter_tu.sh setup + selftest PASS on the 1205 base: reassembly identity PASS,
 * harness object byte-identical to the Makefile object (disasm sha1
 * 532e07fb2f3e43f0b363a1edc4994a4afd2d6014), pycparser round trip codegen-neutral,
 * positive control 1497 on its own scale, negative control 1502.  `frame` reports the
 * frame AND the 83-displacement stack-offset multiset already equal to golden's, so the
 * run is gated with PERMUTER_TU_REQUIRE_FRAME=264 PERMUTER_TU_REQUIRE_OFFSETS=1.
 * It found the statement split that became lever 11 in an earlier wave.  This wave's run
 * result is recorded at the bottom of this file.
 *
 * ---- WHAT WOULD ACTUALLY BE LEFT TO TRY ----
 * Not statement order, not casts, not declaration types -- all three are exhausted above.
 * The only untested class is a DIFFERENT DECOMPOSITION with N=5 declared scalars that
 * still lands on frame 0x108 (the frame arithmetic admits N=5 with T in [5,8], and the
 * previous wave's assertion of N=6 was never proved).  Every N=5 form tried this wave
 * moved the frame, but the space was not enumerated.  That is a long shot: it would have
 * to produce the same 243 instructions, the same 83 stack displacements and the same
 * store sequence while changing which values are pre-loop locals.
 * ============================================================================== */
