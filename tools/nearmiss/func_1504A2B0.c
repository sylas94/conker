/* =====================================================================================
 * game_77760 / func_1504A2B0   (336 B, 81 instructions + 3 pad nops)   PARKED 2026-08-16
 *
 * BEST SCORE: 60  (fastscore, n = 84/84 -- length EXACT incl. padding)
 *              76 for the fully-plain spelling below; 88 for the first reconstruction.
 *
 * WHAT THE FUNCTION IS -- IT IS expf().  Fully identified, algorithm certain:
 *      ax = fabsf(x);                       // abs.s; fabsf is #pragma intrinsic in functions.h
 *      if (ax < 1.1920929e-7f) return 1.0f; // 0x34000000, inlined via lui+mtc1 (low16 == 0)
 *      n = ax / D_800990A0;                 // D_800990A0 = 0.6931471825f = ln2  (trunc.w.s)
 *      if (n > 1024) return x >= 0 ? D_800990A4 : 0.0f;   // D_800990A4 = 3.4028235e38 = FLT_MAX
 *      rem = ax - (f32)n * D_800990A8;      // D_800990A8 = ln2 AGAIN, a SECOND rodata slot
 *      sum = term = 1.0f; k = 1;
 *      do { old = sum; term *= rem/(f32)k; sum += term; k++; } while (sum != old);
 *      for (i = n; i != 0; i--) sum += sum; // x2^n, IDO 4x-unrolls w/ an (n&3) front peel
 *      return x >= 0.0f ? sum : 1.0f / sum;
 *   The sibling TU game_77AD0/func_1504A620 is the matching logf() (also parked, on the same
 *   "global FP-reg rotation" residual -- see its comment).  The three constants are separate
 *   rodata words in asm/data/23DB60.rodata.s, so they must be referenced as `extern f32`
 *   (the repo's standard escape); a written-out 0.6931472f literal would land in this TU's
 *   own .rodata, which is /DISCARD/ed, and would be a FALSE zero.
 *
 * THE RESIDUAL, exactly: ONE CSE DECISION ABOUT 1.0f, AND THE FP ROTATION IT CAUSES
 *   golden materialises 1.0f INDEPENDENTLY at each use --
 *        lui at,0x3F80 / mtc1 at,$f2 (sum) / mtc1 at,$f14 (term)   ... later ...
 *        lui at,0x3F80 (again!) ......... / mtc1 at,$f10 (the 1.0/sum numerator)
 *   i.e. it keeps the BIT PATTERN in the integer register $at across both loops and re-lui's
 *   it when clobbered.  IDO given the same source instead CSEs the FLOAT value:
 *        lui at,0x3F80 / mtc1 at,$f18 / mov.s $f14,$f18 / mov.s $f16,$f18
 *   and then keeps $f18 = 1.0f live to the end.  Consequences, all of them mechanical:
 *     - $f18 is occupied, so the whole FP colouring rotates:
 *           golden  sum=$f2  term=$f14  old=$f16  rem=$f18
 *           ours    sum=$f16 term=$f14  old=$f0   rem=$f2   (const 1.0f=$f18)
 *     - golden has a free register for the OTHER constant and hoists `mtc1 zero,$f14` (0.0f)
 *       once before the doubling loop, re-using it in all three copies of `c.le.s $f14,$f12`;
 *       we have to re-materialise 0.0f twice instead.
 *     - the tail is 2 instructions SHORT because golden's branch-likely target block begins
 *       with the re-materialising `mtc1 at,$f10` (duplicated into the delay slot, the usual
 *       IDO bc1fl artefact) while ours begins directly with the `div.s`.
 *   Only ONE constant can stay resident; golden picks 0.0f, IDO-from-this-source picks 1.0f.
 *
 * WHAT MOVES THE SCORE (measured)
 *      first reconstruction, plain if/else, `for (i = n; i != 0; i--)`          88
 *      `while (n != 0) {...; n--;}` instead                                     79   *
 *      + `term *= rem/(f32)k` (compound) instead of `term = term * (...)`       79
 *      + ternary on BOTH returns (`return c ? a : b;`)                          76
 *      + one init written as a double literal (`sum = 1.0; term = 1.0f;`)       60   <-- kept
 *      `old = 0.0f;` + a `while (sum != old)` head-tested loop                  61 (n=84 too,
 *                    but it hoists the compare above the loop -- worse shape)
 *   * `while (n != 0)` loses golden's `or v0,a0,zero` (golden keeps the ORIGINAL n in $a0 and
 *     decrements a COPY in $v0, so the source does have a second counter variable);
 *     `for (i = n; ...)` reproduces that copy, which is why the parked form uses it.
 *   NO-OPS: declaration order of the five f32 locals -- ALL 120 permutations score the same.
 *           Every spelling of the count expression.  `0.0f <= x` vs `x >= 0.0f`.
 *
 * THE 60 SPELLING IS ON THE HONESTY LINE.  `sum = 1.0;` (double literal into an f32) is
 *   ordinary C and is what defeats the float-value CSE, but I chose it FOR that effect after
 *   probing, and `term = 1.0f;` right beside it is inconsistent.  Both plain-`1.0f` variants
 *   are given below; the next attempt should decide.  A source-level lever that makes IDO
 *   keep 0.0f (not 1.0f) resident is the real unlock and I did not find one.
 *
 * PERMUTER: 25 min @ -j5 from the 60 seed.  NO ZERO; best output re-scores 59 in-file (one
 *   point, no structural change).  Consistent with the sibling logf, which the permuter also
 *   could not crack (best 1520 there).  This is an FP-colouring coin flip.
 * ===================================================================================== */

#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_800990A0;
extern f32 D_800990A4;
extern f32 D_800990A8;

/* BEST MEASURED: 60.  `sum = 1.0;` is the double-literal spelling discussed above. */
f32 func_1504A2B0(f32 arg0) {
    f32 ax;
    f32 rem;
    f32 sum;
    f32 term;
    f32 old;
    s32 n;
    s32 i;
    s32 k;

    ax = fabsf(arg0);
    if (ax < 1.1920929e-7f) {
        return 1.0f;
    }
    n = ax / D_800990A0;
    if (n > 1024) {
        return (arg0 >= 0.0f) ? D_800990A4 : 0.0f;
    }
    rem = ax - ((f32) n * D_800990A8);
    sum = 1.0;
    term = 1.0f;
    k = 1;
    do {
        old = sum;
        term *= rem / (f32) k;
        sum = sum + term;
        k++;
    } while (sum != old);
    for (i = n; i != 0; i--) {
        sum = sum + sum;
    }
    return (arg0 >= 0.0f) ? sum : 1.0f / sum;
}

#if 0
/* The same thing with both initialisers as plain 1.0f: 76.  Structurally identical; the
 * extra 16 points are only the float-constant CSE described in the header. */
f32 func_1504A2B0(f32 arg0) {
    f32 ax, rem, sum, term, old;
    s32 n, i, k;

    ax = fabsf(arg0);
    if (ax < 1.1920929e-7f) {
        return 1.0f;
    }
    n = ax / D_800990A0;
    if (n > 1024) {
        return (arg0 >= 0.0f) ? D_800990A4 : 0.0f;
    }
    rem = ax - ((f32) n * D_800990A8);
    sum = 1.0f;
    term = 1.0f;
    k = 1;
    do {
        old = sum;
        term *= rem / (f32) k;
        sum = sum + term;
        k++;
    } while (sum != old);
    for (i = n; i != 0; i--) {
        sum = sum + sum;
    }
    return (arg0 >= 0.0f) ? sum : 1.0f / sum;
}

/* Most conservative spelling (plain if/return everywhere): 88, but note it is the one that
 * reads most like a 1990s libm.  All of the difference from 60 is scheduling around the
 * two `x >= 0.0f` tests. */
f32 func_1504A2B0_plain(f32 arg0) {
    f32 ax, rem, sum, term, old;
    s32 n, i, k;

    ax = fabsf(arg0);
    if (ax < 1.1920929e-7f) {
        return 1.0f;
    }
    n = ax / D_800990A0;
    if (n > 1024) {
        if (arg0 >= 0.0f) {
            return D_800990A4;
        }
        return 0.0f;
    }
    rem = ax - ((f32) n * D_800990A8);
    sum = 1.0f;
    term = 1.0f;
    k = 1;
    do {
        old = sum;
        term *= rem / (f32) k;
        sum = sum + term;
        k++;
    } while (sum != old);
    for (i = n; i != 0; i--) {
        sum = sum + sum;
    }
    if (arg0 >= 0.0f) {
        return sum;
    }
    return 1.0f / sum;
}
#endif
