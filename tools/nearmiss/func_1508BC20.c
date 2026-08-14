/* func_1508BC20  (game_B3020.c)  -- COLD DECOMPILE, PARKED BASELINE: score 785
 *
 * Build history this wave (all measured, TU game_B3020, -o func_1508BC20 -R):
 *    1922  first shape: 13 declared locals (incl. `f32 fcount` and a separate `j`).
 *          Frame came out 0x90 vs golden 0x88 -> 8 bytes = 2 extra declared 4-byte
 *          locals.  FRAME LAW applied: dropped `fcount` (inlined the (f32)count) and
 *          merged the memset counter into `i`.
 *    1229  frame now 0x88 EXACTLY; `row` homed at 0x84; used[] at 0x50..0x60;
 *          s7/s8 = &used[0]/&used[16].  Residual moved to the prologue only.
 *     850  `dst` retyped `s8 *` -> `u8 *`.  DECISIVE: with `s8 *dst`, IDO narrows the
 *          store constant to (s8)0xFF == -1, which then COLLIDES with `dir = -1` and
 *          -1 becomes the hoisted loop-invariant constant in $s4 (`li s4,-1` +
 *          `move s6,s4`).  Golden hoists 0xFF (`li s4,0xff`) and materialises -1
 *          fresh inside the loop (`li s6,-1`).  Two distinct constants => u8 dest.
 *     785  moved the clear loop to the FIRST statement of the outer body.  Golden's
 *          outer-loop-top block is `addiu v0,sp,0x50 / li s6,-1 / li s1,0x55 /
 *          lw s2,0x6c(sp)`; the memset pointer init leading the block is the order
 *          signal.  <-- THIS FILE.  Everything from 0x6158 (loop top) to the epilogue
 *          is INSTRUCTION-IDENTICAL to golden.
 *
 * RESIDUAL at 785 -- classify: BASIC BLOCK (primary) + ALLOCATION (secondary).
 *   (a) golden emits `step = 0xAA / n` (div + trap checks + `sw t7,0x6c(sp)`) BEFORE
 *       the loop guard, then `move a1,zero` / `blezl s3,<epilogue>` with `lw ra`
 *       annulled in the delay slot.  Mine SINKS the whole div block into the loop
 *       preheader (asm-differ shows it attributed to the `for (row...)` line, not to
 *       the `step = ...` line) and emits a plain `blez` with `move a1,zero` in the slot.
 *   (b) consequence of (a): the quotient lands in a COMPILER TEMP (0x48) instead of
 *       `step`'s own home (0x6C = ordinal 7), and the (f32)count temp is pushed from
 *       0x48 down to 0x40.  3 stack-offset diffs.
 *   (c) the 4x-unrolled clear loop schedules `sb zero,-4(v0)` into the branch delay
 *       slot; golden puts `sb zero,-1(v0)` there.  4 diffs, independent of (a)/(b).
 *
 * MECHANISM FOUND (measured, do not re-derive):
 *   The quotient is homed at 0x6C ONLY when the variable holding it has MORE THAN ONE
 *   DEFINITION.  Rewriting as `n = count >> 1; if (n < 2) n = 2; n = 0xAA / n;` (one
 *   variable, three defs) makes IDO keep `n` as a real local: `sw <reg>,0x6c(sp)`
 *   lands in home ordinal 7, the div stops sinking, and the guard becomes
 *   `blezl s3,<epilogue>` + `lw ra` in the delay slot -- ALL of (a) and (b) fixed,
 *   and `swc1 $f6,0x48(sp)` becomes correct.  A single-def `step` is forward-
 *   substituted into `curStep = step` and degraded to a loop-invariant CSE temp.
 *   BUT that family costs more than it buys: IDO then ENREGISTERS `n` in $a0 (a
 *   caller-saved reg), producing `mflo a0` AFTER the trap checks instead of
 *   `mflo t7` + immediate store before them, plus a redundant `lw a0,0x6c(sp)` /
 *   `move s2,a0` at the loop top and an `sw a0,0x6c(sp)` spill before every call.
 *   Golden never enregisters it at all.  Scores measured in that family:
 *      1817  n multi-def + separate `j` for the clear loop  (the separate loop
 *            counter also costs an extra live `move s4,zero` and renumbers
 *            s4/s5/s6/s7/s8 by one)
 *      1123  n multi-def + `f32 r` as the 10th scalar.  Registers s4/s6/s7/s8 all
 *            correct, but `r` FLIPS the multiply: `mul.s f10,f8,f0` where golden and
 *            the inline spelling both give `mul.s f10,f0,f8`, and it rotates the
 *            t-register assignment (li t0,1 vs li t1,1; lb t8 vs lb t9).
 *            => the RNG result is NOT a named local; keep it inline.
 *      1113  n multi-def + `half` as the 10th scalar (`half = count>>1; n = half;
 *            if (half < 2) n = 2;`).  Best of that family; registers all correct;
 *            residual is purely the $a0 enregistration + 0x44 float temp + memset.
 *      2140  clear loop as a declared pointer walk
 *            (`for (p = used; p != &used[16]; p++) *p = 0;`).  IDO does NOT unroll
 *            the pointer form -- it emits a 1-byte/iteration loop and recomputes
 *            `addiu t7,s8,0x10` inside.  The INDEX form is what unrolls 4x.
 *            (This did confirm the float temp goes to 0x48 once only one temp exists.)
 *
 * MEASURED NO-OPS (identical object, do not retry):
 *   - moving `curStep = step;` from the top of the outer body to just before the fill
 *     loop: 785 -> 785, byte-identical.  IDO hoists the load to the loop top either
 *     way.  Same no-op in the n-multi-def family (1113 -> 1113).
 *
 * FRAME ACCOUNTING (golden, framesize 0x88):
 *   arg build 0x00..0x18, saved s0-s8+ra 0x18..0x40, temps 0x40..0x50 (only the
 *   (f32)count temp at 0x48 is live), home 0x50..0x88 = 56 bytes =
 *   10 four-byte scalars (0x60..0x88) + s8 used[16] (0x50..0x60, declared LAST).
 *   Homed/observed: row -> 0x84 (ordinal 1), quotient -> 0x6C (ordinal 7).
 *   0x6C is INSIDE the home area, so it cannot be a compiler temp: temps live below
 *   the home area.  Ten scalars are forced by used[] sitting at 0x50 with the frame
 *   at 0x88; they are exactly row, count, idx, val, dir, curStep, step, n, i, dst.
 *
 * TYPE EVIDENCE PINNED BY GOLDEN:
 *   D_8008FD8C  s8  (`lb`), read once into $s3 as the loop count.
 *   D_800D23B0  s8* (file-scope decl already in the TU); the row base is
 *               (u8 *)D_800D23B0 + 0x15B4, stride 0x10 per outer iteration.
 *   used[16]    s8  -- `lb $t9,0($v0)` is a SIGNED byte load.
 *   dst         u8* -- see the 850 entry above.
 *   `0.5f` is inline (lui 0x3f00 + mtc1), no rodata pool.  `c.lt.s $f18,$f0` is
 *   IDO's reversal of `x > 0.5f`.
 */

void func_1508BC20(void) {
    s32 row;
    s32 count;
    s32 idx;
    s32 val;
    s32 dir;
    s32 curStep;
    s32 step;
    s32 n;
    s32 i;
    u8 *dst;
    s8 used[16];

    count = D_8008FD8C;
    dst = (u8 *) D_800D23B0 + 0x15B4;
    n = count >> 1;
    if (n < 2) {
        n = 2;
    }
    step = 0xAA / n;
    for (row = 0; row < count; row++) {
        for (i = 0; i < 16; i++) {
            used[i] = 0;
        }
        dir = -1;
        val = 0x55;
        curStep = step;
        idx = (s32) (func_150ADA68() * (f32) count);
        if (func_150ADA68() > 0.5f) {
            dir = 1;
        }
        while (used[idx] != 0) {
            idx += dir;
            if (idx < 0) {
                idx = count - 1;
            }
            if (idx >= count) {
                idx = 0;
            }
        }
        used[idx] = 1;
        for (i = 0; i < count; i++) {
            if (val < 0x100) {
                dst[idx] = val;
            } else {
                dst[idx] = 0xFF;
            }
            idx++;
            if (idx >= count) {
                idx = 0;
            }
            val += curStep;
            if (val >= 0x100) {
                curStep = -curStep;
            }
        }
        dst += 0x10;
    }
}
