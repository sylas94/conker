/* game_76E50 / func_150499A0 (672 B) -- affine 4x4 matrix INVERSE.  PARKED, not a match.
 *
 * SCORE (tools/fastscore.py game_76E50 func_150499A0 <this file>)
 *   raw            = 206
 *   pad-corrected  = 186     golden .s is 168 words: 166 real + 2 trailing inter-TU pad nops.
 *   n = 172 ours vs 166 real golden -> we emit SIX instructions too many, all of them
 *   register-allocator SPILL/RELOAD pairs in the determinant block.  frame 0x38 vs golden 0x30.
 *
 * WHAT IS ALREADY PROVEN CORRECT -- do not re-derive
 *   Signature `void func_150499A0(f32 arg0[4][4], f32 arg1[4][4])` is CONFIRMED by the caller in
 *   src/game_6B320.c:12 and by the matched neighbour TU src/game/done/game_768F0.c, which fixes
 *   the row-major [row][col] convention (row 3 = translation, stride 0x10).
 *   Every arithmetic operand was read off golden instruction by instruction and VERIFIED:
 *     - det = the 6 triple products in exactly the order/sign below; golden's add/sub chain is
 *       flat left-assoc ((((t1+t2)+t3)-t4)-t5)-t6, so TERM ORDER IS PINNED, not free.
 *     - all nine cofactors: offsets and subtraction operand order confirmed one by one.
 *     - the three translation rows and the 0/1 fills confirmed.
 *   `det = expr; det = 1.0f / det;` (ONE variable, reused) is proven by golden's
 *   `div.s $f0, $f2, $f0` -- dividend 1.0f, divisor AND result the same register.  A second
 *   variable for the reciprocal gives `div.s $f0, $f6, $f4` and is WRONG (see below).
 *
 * THE ONLY OPEN QUESTION: WHY DOES GOLDEN SPILL LESS?
 *   Golden keeps the determinant accumulator in $f0 from the very first `mul.s $f0,$f4,$f14`
 *   through to the div, and spills OPERANDS instead -- 5 stack slots, all < 0x20:
 *     0x10 <- arg0[2][0]   0xC <- arg0[0][2]   0x8 <- arg0[1][0]
 *     0x1C <- arg0[2][1]   0x0 <- arg0[2][0] again (a split live range, stored from the
 *                                register already holding the 0x10 slot's value)
 *   Every store is immediately followed by a load of the same slot -- IDO spilling at the
 *   definition point under pressure, NOT declared locals (see the refuted hypothesis below).
 *   Ours additionally spills the ACCUMULATOR (to 0x4), which costs the 6 extra instructions
 *   and the extra 8 bytes of frame.
 *
 * DO NOT REPEAT -- ALL MEASURED
 *   - Declared f32 locals for the 3x3 elements (a..i + det, 10 locals): frame grows to 0x48 and
 *     n=181, mism 297.  The "frame = roundup8(4 + declared_local_bytes) = 0x30 means 10 locals"
 *     reading is WRONG for this function: it is a frameless-style leaf whose frame is dominated
 *     by SPILL slots, and more declared locals made it bigger, not smaller.  Hypothesis REFUTED.
 *   - Separate reciprocal local (`det = expr; r = 1.0f/det;`): reaches golden's frame 0x30 and
 *     mism 207 / n=172, but emits `swc1` HOME STORES for det and r at 0x2C/0x24 that golden does
 *     not have, and the wrong div operand shape.  It is a DIFFERENT position, not a better one.
 *   - `det = 1.0f / (expr);` as one statement: 227.
 *   - Associativity/factor-order sweep over all 6 terms, 12 forms each (6 factor orders x
 *     parenthesised or not), coordinate descent to convergence from two starts: EVERYTHING that
 *     reaches n=172 scores exactly 206.  A hard RANKING TIE across many genuinely different
 *     honest spellings -- the metric cannot distinguish them.
 *   - decomp-permuter (permuter_tu.sh, selftest PASSES here including check b2 -- this TU has no
 *     GBI macros) ran 7851 iterations, -j 4: 3895 -> 3242 and stuck.  3242 corresponds to this
 *     same fastscore 206 plateau; it found the same class of reassociation win and no more.
 *
 * NEXT LEVER TO TRY (not attempted)
 *   The residue is "IDO spills the accumulator, golden spills an operand".  That is a pressure
 *   ordering question, so the untried axis is the ORDER OF THE FIRST FEW LOADS -- i.e. whether
 *   the original spelled some element through a helper/parameter, or whether the cofactor block
 *   (which golden reloads straight from arg0) was written BEFORE the determinant.
 *
 * NOTE ON THE PARENTHESES BELOW
 *   The lone `arg0[0][2] * (arg0[1][0] * arg0[2][1])` on term 3 is the sweep's best position, not
 *   a claim about the original.  The stylistically uniform spelling (all six terms as `a * b * c`)
 *   scores 246 / n=176.  Both are honest; neither matches.
 */

#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_150499A0(f32 arg0[4][4], f32 arg1[4][4]) {
    f32 det;

    det = arg0[0][0] * arg0[1][1] * arg0[2][2] + arg0[0][1] * arg0[1][2] * arg0[2][0] + arg0[0][2] * (arg0[1][0] * arg0[2][1]) - arg0[0][2] * arg0[1][1] * arg0[2][0] - arg0[0][1] * arg0[1][0] * arg0[2][2] - arg0[0][0] * arg0[1][2] * arg0[2][1];
    det = 1.0f / det;
    arg1[0][0] = (arg0[1][1] * arg0[2][2] - arg0[2][1] * arg0[1][2]) * det;
    arg1[1][0] = (arg0[1][2] * arg0[2][0] - arg0[2][2] * arg0[1][0]) * det;
    arg1[2][0] = (arg0[1][0] * arg0[2][1] - arg0[2][0] * arg0[1][1]) * det;
    arg1[0][1] = (arg0[0][2] * arg0[2][1] - arg0[2][2] * arg0[0][1]) * det;
    arg1[1][1] = (arg0[0][0] * arg0[2][2] - arg0[2][0] * arg0[0][2]) * det;
    arg1[2][1] = (arg0[0][1] * arg0[2][0] - arg0[2][1] * arg0[0][0]) * det;
    arg1[0][2] = (arg0[0][1] * arg0[1][2] - arg0[1][1] * arg0[0][2]) * det;
    arg1[1][2] = (arg0[0][2] * arg0[1][0] - arg0[1][2] * arg0[0][0]) * det;
    arg1[2][2] = (arg0[0][0] * arg0[1][1] - arg0[1][0] * arg0[0][1]) * det;
    arg1[3][0] = -(arg0[3][0] * arg1[0][0] + arg0[3][1] * arg1[1][0] + arg0[3][2] * arg1[2][0]);
    arg1[3][1] = -(arg0[3][0] * arg1[0][1] + arg0[3][1] * arg1[1][1] + arg0[3][2] * arg1[2][1]);
    arg1[3][2] = -(arg0[3][0] * arg1[0][2] + arg0[3][1] * arg1[1][2] + arg0[3][2] * arg1[2][2]);
    arg1[3][3] = 1.0f;
    arg1[0][3] = 0.0f;
    arg1[1][3] = 0.0f;
    arg1[2][3] = 0.0f;
}
