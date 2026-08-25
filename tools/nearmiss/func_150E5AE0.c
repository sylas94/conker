/* =====================================================================================
 * PARK: func_150E5AE0  (TU game_112F90 -- the only function in that TU)
 *
 * FILE SHAPE: STANDALONE TU.  This file IS conker/src/game_112F90.c with the
 *             #pragma GLOBAL_ASM line replaced by the body.  Score it directly:
 *                 python3 tools/fastscore.py game_112F90 func_150E5AE0 <this file>
 *             Do NOT try to splice only the body -- the extern block is needed and
 *             scoring the wrong shape yields a CCFAIL that looks like a broken park.
 *
 * BEST SCORE     mism=241    n=320/316 (we are 4 instructions LONG)
 * FRAME          -208 (0xD0) == GOLDEN EXACTLY, incl. all six sdc1 $f20..$f30 saves
 * OPT_FLAGS      -O2 -g3 (default; game_112F90 has no Makefile override)
 *
 * HOW CLOSE IT REALLY IS
 * ----------------------
 * A register-blind comparison (mask rs/rt/rd/fs/ft/fd, keep opcode+funct+imm) says
 * instructions 0..147 are STRUCTURALLY IDENTICAL to golden: every branch, both
 * duplicated-lui delay slots, every div/break-7/break-6 trap pair, the continue-shaped
 * loop, the bnel peephole site, the 28-argument call block.  All of the 241 in rows
 * 0..147 is register NAMING.  The first genuinely structural row is idx148.
 *
 * REMAINING DIFF ROWS (first 40 of 201; the rest are downstream of the idx148 shift)
 *   idx22   ours=15c10115 gold=15c10110  branch displacement (we are 5 instrs long here)
 *   idx41   ours=3c04.... gold=3c03800e  \
 *   idx42   ours=3c04.... gold=3c03800e   | We put &D_800D9A14 in $a0 and its VALUE in
 *   idx43   ours=2484.... gold=24639a14   | $v0.  Golden puts the ADDRESS in $v1 and the
 *   idx46   ours=8c820000 gold=8c640000   | VALUE in $a0, i.e. one register slot later.
 *   idx47   ours=004a082a gold=008a082a   | Consequently D_800BE9E4 lands in $v1 for us
 *   idx49   ours=245e000a gold=249e000a   | and $v0 for golden.  This single rotation
 *   idx52   ours=004c6821 gold=008c6821   | explains rows idx41..idx72 (~20 rows).
 *   idx53   ours=ac8d0000 gold=ac6d0000   |
 *   idx55   ours=01a01025 gold=01a02025   |
 *   idx56   ours=24840000 gold=24639a14   |
 *   idx57   ours=8c820000 gold=8c640000   |
 *   idx58   ours=8e230000 gold=8e220000   |
 *   idx59   ours=0062082a gold=0044082a   |
 *   idx61   ours=00437023 gold=00827023   |
 *   idx62   ours=ac8e0000 gold=ac6e0000   |
 *   idx64   ours=01c01025 gold=01c02025   |
 *   idx66   ours=ac800000 gold=ac600000   |
 *   idx67   ours=00001025 gold=00002025   |
 *   idx68   ours=245e000a gold=249e000a   |
 *   idx72   ours=24530001 gold=24930001  /
 *   idx75   ours=1bc000e0 gold=1bc000db  blez displacement (5 long)
 *   idx90   ours=567800cf gold=571300ca  bnel operand order ($s3,$t8 vs $t8,$s3) + disp
 *   idx95..idx147                        pure $t-register ROTATION inside the loop
 *                                        (ours t9/t1/t0..., golden t0/t1/t2...)
 *   idx148  ours=16e00002 gold=3c0140a0  <== FIRST REAL STRUCTURAL ROW
 *   idx149  ours=00000000 gold=4481b000
 *
 * THE BLOCKER, STATED PRECISELY
 * -----------------------------
 * Golden schedules three instructions INTO the middle of the fourth `% 200` div-trap:
 *      lui $at,(0x40A00000>>16) ; mtc1 $at,$f22 ; cvt.s.w $f8,$f6
 * i.e. it materialises the 5.0f literal ONCE, into a CALLEE-SAVED f-register, ahead of
 * the trap, and converts the second (rand%200) straight there as well.  We emit the trap
 * first and then the cvt, and we materialise 5.0f TWICE -- once on each side of the
 * `fz - 5.0f < fx && fx < fz + 5.0f` short circuit, which straddles a basic-block edge.
 * We additionally emit `cvt.s.w $f0,$f4 ; mov.s $f24,$f0` where golden emits
 * `cvt.s.w $f24,$f6` directly (IDO splits the live range and keeps the fresh value in
 * $f0/$f2 for the immediate compare).
 *      => our 4 extra instructions are exactly 2 x mov.s + 1 duplicated (lui+mtc1) pair.
 *
 * The whole f-register PERMUTATION falls out of the same decision.  The webs and the
 * coalescings are IDENTICAL to golden (fx -> sinf-product, ang1 -> cosf-product,
 * fz -> second sinf-product); only the register numbers differ:
 *      golden   f20=fx   f22=ang1  f24=fz   f26=fy2  f28=fy1  f30=ang2
 *      ours     f20=ang1 f22=ang2  f24=fz   f26=fx   f28=fy2  f30=fy1
 *
 * DO-NOT-REPEAT  (every spelling measured, with its score)
 * -------------------------------------------------------
 *   276   local `s32 t` for D_800D9A10 AND local `s32 v` for D_800D9A14 (n=316/316!)
 *   253   drop local `v`; let IDO value-number D_800D9A14 through the branch merge
 *   241   ALSO drop local `t`; write `D_800D9A14 += D_800BE9E4 * 2`      <== THIS FILE
 *   241   + `if (D_800D9A0C > D_800D9A14)` instead of `D_800D9A14 < D_800D9A0C`
 *   241   + `if (D_800D9A14 > D_800BE9E4)` instead of `D_800BE9E4 < D_800D9A14`
 *   241   + `fy1 = fy2 + (f32)(rand%200) - 100.0f` (operand swap)
 *   241   + `fx = (f32)x;` before `fz = (f32)z;`
 *   241   + `if (fx > fz - 5.0f && fx < fz + 5.0f)`
 *   241   + named `f32 tol; tol = 5.0f;` used on both sides  <- does NOT stop the
 *                                                               duplicate materialisation
 *   241   + implicit int<->float conversions instead of explicit (f32)/(s32) casts
 *   243   four extra named f32 temps (sx1/sz1/sx2/sz2) holding the sin/cos products
 *   243   reuse fx/fz/ang1 as the sin/cos destinations (mirrors golden's coalescing)
 *   243   ALL 720 PERMUTATIONS of the six f32 declarations (exhaustive sweep).
 *         *** DECLARATION ORDER HAS ZERO EFFECT ON THIS FUNCTION.  Do not sweep again. ***
 *   374   conversions `fz=(f32)z; fx=(f32)x;` moved BEFORE the two rand%200 calls
 *         (n=328 -- strictly worse; IDO then needs two more callee-saved f-registers)
 *
 * FACTS ESTABLISHED (do not re-derive)
 *   * The `% 200` divisor sits in $s7 WITH break-7/break-6 traps while `% 30`, `% 11`
 *     and `/ 10` use $at with no traps.  That is the documented cookbook law (a literal
 *     %N divisor INSIDE a loop is hoisted to a callee-saved register and keeps the trap);
 *     plain literals reproduce it.  The divisor is NOT a variable.
 *   * The three beql/bnel rows are the as1 assembler peephole and appear for free.
 *   * D_800A1170..D_800A1184 are genuine `extern f32` (golden loads them with
 *     lui %hi + lwc1 %lo every iteration); they are NOT an anonymous literal pool, so
 *     this function is NOT rodata-blocked and needs no conker.us.yaml migration.
 *   * The "-g3 named local costs 4 bytes" law does NOT bite here: 11 named locals and
 *     the frame is byte-exact at 0xD0.
 *
 * WHAT WOULD MOVE IT
 *   The residual is an IDO scheduling / rematerialisation decision inside one extended
 *   basic block, not a semantic error, and the source-level lever space is exhausted
 *   above.  Next tool is tools/decomp-permuter seeded with this file: the structure is
 *   already right and only the f-register assignment plus one 3-instruction schedule
 *   need permuting.
 *
 * SEMANTICS (high confidence -- worth keeping even if the match never lands)
 *   D_80088A04 s32   gate; the effect only runs while == 1, self-clears at the end
 *   D_800D9A10 s32   phase accumulator advanced by dt (D_800BE9E4); on reaching 0x83 it
 *                    is reset to -(rand()%30), i.e. a randomised cooldown
 *   D_800D9A14 s32   intensity ramp; grows by 2*dt while below the cap D_800D9A0C during
 *                    the "phase >= 0x1F" window, decays by dt otherwise, and on hitting 0
 *                    disarms D_80088A04
 *   count = (intensity + 10) / 10 instances are emitted per frame; j = intensity + 1
 *                    steps down by 10 per instance and gates the tail through rand()%11
 *   D_800D9A04/08    centre and half-range of the random XZ scatter
 *   Two angles, (f32)x * D_800A1170 and (f32)z * D_800A117C; their sin/cos scaled by
 *   D_800A1174/1178 and D_800A1180/1184 are added to the CAMERA position
 *   (D_800DBFF0->unk2F8/2FC/300) to give the two endpoints passed to func_150E1AB0
 *   together with (160,10,4,360, 15, 0x43, 0.., -1, 0..) -- a two-point effect emitted
 *   around the camera.  Reads as a WEATHER / LIGHTNING-STRIKE spawner.
 * ===================================================================================== */

#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern s32 D_80088A04;
extern s32 D_800BE9E4;
extern s32 D_800D9A04;
extern s32 D_800D9A08;
extern s32 D_800D9A0C;
extern s32 D_800D9A10;
extern s32 D_800D9A14;
extern f32 D_800A1170;
extern f32 D_800A1174;
extern f32 D_800A1178;
extern f32 D_800A117C;
extern f32 D_800A1180;
extern f32 D_800A1184;

s32 func_151EF610(void);
void func_150E4514(void);
void func_150E1AB0(s32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, u16, s32, s32, s16, s16, s32, u8, s16, s32, s32, u8, f32, f32, f32, f32, f32, f32);

void func_150E5AE0(void) {
    s32 i;
    s32 count;
    s32 j;
    s32 x;
    s32 z;
    f32 fx;
    f32 fz;
    f32 fy1;
    f32 fy2;
    f32 ang1;
    f32 ang2;

    if (D_80088A04 != 1) {
        return;
    }
    D_800D9A10 = D_800D9A10 + D_800BE9E4;
    if (D_800D9A10 >= 0x83) {
        D_800D9A10 = -(func_151EF610() % 30);
    }
    if (D_800D9A10 >= 0x1F) {
        if (D_800D9A14 < D_800D9A0C) {
            D_800D9A14 += D_800BE9E4 * 2;
        }
    } else {
        if (D_800BE9E4 < D_800D9A14) {
            D_800D9A14 = D_800D9A14 - D_800BE9E4;
        } else {
            D_80088A04 = 0;
            D_800D9A14 = 0;
        }
    }
    count = (D_800D9A14 + 10) / 10;
    j = D_800D9A14 + 1;
    func_150E4514();
    for (i = 0; i < count; i++, j -= 10) {
        if (j < 10 && func_151EF610() % 11 != j) {
            continue;
        }
        x = (func_151EF610() % D_800D9A08) * 2 - D_800D9A08 + D_800D9A04;
        z = (func_151EF610() % D_800D9A08) * 2 - D_800D9A08 + D_800D9A04;
        fy2 = (f32)(func_151EF610() % 200);
        fy1 = (f32)(func_151EF610() % 200) + fy2 - 100.0f;
        fz = (f32)z;
        fx = (f32)x;
        if (fz - 5.0f < fx && fx < fz + 5.0f) {
            fy1 += 150.0f;
            fy2 += 150.0f;
        }
        if (func_151EF610() % 2) {
            x = (s32)(fx + 180.0f);
            fx = (f32)x;
        } else {
            z = (s32)(fz + 180.0f);
            fz = (f32)z;
        }
        ang1 = fx * D_800A1170;
        ang2 = fz * D_800A117C;
        func_150E1AB0(0,
            sinf(ang1) * D_800A1174 + D_800DBFF0->unk2F8,
            fy1 + D_800DBFF0->unk2FC,
            cosf(ang1) * D_800A1178 + D_800DBFF0->unk300,
            sinf(ang2) * D_800A1180 + D_800DBFF0->unk2F8,
            fy2 + D_800DBFF0->unk2FC,
            cosf(ang2) * D_800A1184 + D_800DBFF0->unk300,
            160.0f, 10.0f, 4.0f, 360.0f, 15, 0x43, 0, 0, 0, 0, 0, 0, -1, 0, 0,
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    }
}
