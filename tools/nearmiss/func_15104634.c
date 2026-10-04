/* game_131A90 / func_15104634 -- NEAR MISS, mism=341, n=259/275, frame 0xE0 (correct)
 *
 * Score: python3 tools/fastscore.py game_131A90 func_15104634 tools/nearmiss/func_15104634.c
 *
 * WHAT IS ALREADY RIGHT (do not disturb)
 *   - frame 0xE0, and every stack offset: sp78 @0x78, xs[3] @0x6C, zs[3] @0x60.
 *     That layout REQUIRES 4 scalars declared BEFORE sp78 (entries/count/n/i) --
 *     they push sp78's top down to 0xD0 so its base lands on 0x78.
 *   - the whole first loop, idx 0..90, is instruction-for-instruction correct
 *     apart from FP register NAMES (see below), including the k-loop's peeled
 *     last iteration and the `bc1fl` + duplicated `addiu t0,t0,1`.
 *   - hoisting `ptrs = entries[i].unk4; off = entries[i].unk8;` out of the k-loop
 *     is REQUIRED (without it the loads repeat inside the loop).
 *   - writing the winding test as an explicit plane constant
 *       dd = -(...);  if (0.0f < (... + dd))
 *     is REQUIRED: it produces golden's `neg.s` + `add.s`.  Writing it as
 *     `A + -(B)` folds to a single `sub.s` and loses ~10 rows.
 *
 * THE 16 MISSING INSTRUCTIONS (the whole remaining blocker)
 *   Golden REMATERIALISES the abs operand in two of the five copies of the second
 *   loop body (the `n & 3` remainder copy and unrolled copy 1):
 *       sll t6,v0,4 ; addu t7,a2,t6              <- 2nd address computed up front
 *       ...
 *       bc1fl .L15104850 ; c.lt.s f0,f12
 *       lw t8,0(t7) ; mtc1 ; nop ; cvt.s.w ; mul.s ; sub.s ; neg.s
 *   We instead keep the value in a register and emit `mov.s f0,f2` / `neg.s f0,f2`
 *   (which is exactly what golden does in copies 3,4,5).  8 instructions x 2 copies
 *   = 16 = the entire length gap.  Golden also saves/restores f22 (it parks arg0
 *   there across func_1510F800 with `mov.s f22,f12`, then reuses f22 for 0.0f);
 *   we spill arg0 to its incoming arg slot and put 0.0f in f18.  Both are symptoms
 *   of the same thing: golden's FP allocator is under more pressure here.
 *
 * DO NOT REPEAT (measured)
 *   - writing the expression twice, in ANY form (ternary, if/else, `d = -(expr)`)
 *     DESTROYS the 4x unroll of the second loop: n drops 259 -> 199..203, mism 874+.
 *   - `d = -d` vs `d = 0.0f - d`: the latter is 11 rows better (341 vs 352). Kept.
 *   - swapping the two addends of the plane equation, or the operands of any single
 *     mul.s: FLAT (341..343).  These are memory x register muls, forced canonical
 *     (cookbook lead 6), i.e. a genuine ranking tie -- do not grind on it.
 *   - inlining `nz`/`nx` so IDO CSEs them: 343, no change to the xs-vs-zs load order.
 *   - swapping the source order of `nz = xs[0]-xs[1]` and `nx = zs[1]-zs[0]`: 354.
 *     IDO computes the zs subtraction first either way; golden computes the xs one
 *     first.  This is the visible tip of the register-allocation difference.
 *   - block-scope decl inside the `if (0.0f < ...)` body: no effect on length.
 *
 * CALIBRATION TWIN: conker/src/game_13BB20.c func_1510F8D8 -- same
 *   `func_1510F800(0); count = func_150A3A70(...); if (count == 0) return X;` opening
 *   and the same `entries = (unkfunc *)&D_800D3300;` idiom.  D_800D3300 records are
 *   16 bytes: { s32 height_x256; s32 *vtxptrs; s32 vtxbase; s32 unkC }.
 *   Semantics: pick, among the candidate triangles at (arg0,arg1) whose 2D winding
 *   is negative, the one whose height is closest to arg2; write it to *arg3.
 */
#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_151045E0(s32 arg0, s32 arg1, s32 arg2) {
}

s32 func_151045F4(s32 arg0, s32 arg1) {
    return 0x1;
}

void func_15104608(f32 arg0, f32 arg1, s32 arg2, s32 arg3) {
}

s32 func_15104620(s32 arg0, s32 arg1) {
    return 0x1;
}

extern void func_1510F800(s32);
extern s32 func_150A3A70(s32, s32);
extern f32 D_800A2370;

typedef struct unkfunc_15104634 {
    s32 unk0;
    s32 *unk4;
    s32 unk8;
    s32 unkC;
} unkfunc_15104634;

s32 func_15104634(f32 arg0, f32 arg1, f32 arg2, f32 *arg3) {
    unkfunc_15104634 *entries;
    s32 count;
    s32 n;
    s32 i;
    s32 sp78[22];
    f32 xs[3];
    f32 zs[3];
    s32 j;
    s32 best;
    f32 bestd;
    f32 d;
    s32 k;
    f32 nz;
    f32 nx;
    f32 dd;
    s16 *v;
    s32 *ptrs;
    s32 off;

    func_1510F800(0);
    count = func_150A3A70((s32)arg0, (s32)arg1);
    if (count == 0) {
        return 0;
    }

    entries = (unkfunc_15104634 *)&D_800D3300;
    n = 0;
    for (i = 0; i < count; i++) {
        ptrs = entries[i].unk4;
        off = entries[i].unk8;
        for (k = 0; k < 3; k++) {
            v = (s16 *)(ptrs[k] + off);
            xs[k] = v[0];
            zs[k] = v[2];
        }
        nz = xs[0] - xs[1];
        nx = zs[1] - zs[0];
        dd = -((zs[0] * nz) + (nx * xs[0]));
        if (0.0f < (((zs[2] * nz) + (nx * xs[2])) + dd)) {
            sp78[n] = i;
            n++;
        }
    }

    if (n == 0) {
        return 0;
    }

    bestd = D_800A2370;
    best = -1;
    for (j = 0; j < n; j++) {
        d = ((f32)entries[sp78[j]].unk0 * 0.00390625f) - arg2;
        if (d < 0.0f) {
            d = 0.0f - d;
        }
        if ((d < bestd) || (best == -1)) {
            bestd = d;
            best = sp78[j];
        }
    }

    *arg3 = (f32)entries[best].unk0 * 0.00390625f;
    return 1;
}
