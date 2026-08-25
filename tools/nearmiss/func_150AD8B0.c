/* tools/nearmiss/func_150AD8B0.c -- game_DAD60, cross product
 *
 * *** -g3 IS A BLOCKER HERE TOO: 59 -> 19, AND THE LENGTH BECOMES EXACT. ***
 *      -O2 -g3 (tree default)  mism=59  n=24/20
 *      -O2                     mism=19  n=20/20   <- length exact, jr delay slot filled
 * Same effect as game_21C4F0 and game_21D420 (both shipped byte-perfect on this) and
 * game_DADB0. game_DAD60 is ALL-PRAGMA, so the override below is risk-free -- there is no
 * matched sibling for it to break:
 *      $(BUILD_DIR)/$(SRC_DIR)/game_DAD60.c.o: OPT_FLAGS := -O2
 *
 * WHAT REMAINS (19 rows) IS FP REGISTER ALLOCATION, WITH A CONSISTENT SIGNATURE.
 * Golden loads a0,a1,b0,b1,b2,a2 into $f0,$f2,$f4,$f6,$f8,$f10 -- sequential from $f0, and it
 * never touches $f12/$f14. IDO starts at $f0/$f2 and then jumps to $f12,$f14,$f16,$f18,
 * because $f12/$f14 are the float ARGUMENT registers and this function takes three pointers,
 * so they are free and IDO helps itself to them. The declaration order in the source already
 * matches golden's load order; the registers still differ.
 *
 * The same signature appears on func_150AD900 and func_150AD930. All three sit in the 0x150AD
 * region already identified as the HAND-WRITTEN math cluster, and allocating sequentially from
 * $f0 while avoiding the argument registers is what an asm author does, not what a register
 * allocator does.
 *
 * *** THE ISA LEVEL IS NOT THE EXPLANATION -- REFUTED. ***
 * MIPSBIT is separate from OPT_FLAGS in this tree, and the cluster notes record that the RNG
 * here needs -mips3, so it was worth one measurement. At -O2:
 *      func_150AD8B0   -mips2 19  |  -mips1 59  |  -mips3 19
 *      func_150AD900   -mips2 10  |  -mips1 21  |  -mips3 10
 *      func_150AD930   -mips2  9  |  -mips1 82  |  -mips3  9
 * -mips2 and -mips3 are identical and -mips1 is worse. Do not chase the ISA level again.
 */

/* game_DAD60 / func_150AD8B0  -- 3D CROSS PRODUCT, 80 bytes (20 words), leaf.
 *
 * STATUS: PARKED at fastscore mism=29 (-O2 -g3, n=21/20: 19 register rows + one
 * scheduler nop).  Strong evidence below that this function is HAND-WRITTEN ASM
 * and is not reachable from any C source under IDO 5.3 -O2.
 *
 * SEMANTICS ARE FULLY SOLVED AND CERTAIN (read straight off the golden .s):
 *     c[2] = a[0]*b[1] - a[1]*b[0];
 *     c[0] = a[1]*b[2] - a[2]*b[1];
 *     c[1] = a[2]*b[0] - a[0]*b[2];
 * and golden's STORE order really is c[2], c[0], c[1] -- the candidate below
 * reproduces that store order exactly.  Every mul/sub/store operand pairing matches.
 *
 * THE RESIDUAL IS ONE REGISTER-COLOURING FACT:
 *   golden's six loaded values occupy  $f0 $f2 $f4 $f6 $f8 $f10  (in the order
 *   a[0] a[1] b[0] b[1] b[2] a[2]) and its four product temps occupy
 *   $f16 $f18 $f12 $f14 (argument regs last).  Ours puts the six values in
 *   $f0 $f2 $f12 $f14 $f16 $f18 and the products in $f4 $f6 $f8 $f10 -- the exact
 *   transpose -- which cascades into all 19 rows.
 *
 * ==== NEW (this pass): IDO 5.3's FP POOLS ARE FIXED, AND THEY RULE GOLDEN OUT ====
 * Measured by compiling probe functions and reading the register numbers off objdump:
 *   * Named f32 LOCALS are allocated, in DECLARATION ORDER, from the fixed ordered
 *     pool  [$f0, $f2, $f12, $f14, $f16, $f18].
 *       - 2 named locals -> f0,f2.  4 -> f0,f2,f12,f14.  5 -> +f16.  6 -> +f18.
 *       - The pool does NOT depend on temp pressure: a probe needing only ONE
 *         expression temp still gives the 3rd named local $f12, not $f4.
 *       - A 7th+ named f32 local SPILLS to the stack (frame appears); it does not
 *         fall through to $f4.
 *   * Compiler TEMPS are allocated from [$f4, $f6, $f8, $f10, $f16, $f18, $f12, $f14]
 *     (what is left, argument registers $f12/$f14 last).  Golden's product order
 *     f16,f18,f12,f14 is exactly this list once f0..f10 are taken.
 *   => Golden needs four LONG-LIVED values in $f4-$f10, i.e. they must be compiler
 *      TEMPS, not named locals; so golden has at most TWO named f32 locals.
 *   => But a temp holding a loaded value does NOT survive a store through another
 *      f32* (IDO 5.3 has no type-based disambiguation -- see the rejected list), and
 *      golden's $f4 (=b[0]) is still live and used AFTER the swc1 to c[2].
 *   => The two requirements are mutually exclusive in C.  A form with six named
 *      locals can never colour like golden; a form without them always reloads
 *      (12 loads, mism>=98).  Also note 0x150AD8B0 sits inside the KNOWN
 *      hand-written math cluster (game_DAC30 / game_DAE50 neighbours), which is the
 *      simplest explanation for a 20-instruction, frame-free, perfectly scheduled
 *      cross product.
 *
 * MEASURED AND REJECTED -- DO NOT REPEAT (all at -O2 -g3 unless noted):
 *   * plain `c[i] = ...` with no locals, all 6 statement orders x 2 operand orders: 110.
 *   * ALIAS-DEFEATING TYPES, all >= 100 (still 12 loads): f32*/f32*/V3*, V3*/V3*/f32*,
 *     two DISTINCT struct types V3*/W3*, f32 a[3] parameters, `const f32 *`, f32 (*)[3].
 *   * three result temps then three stores (all 36 combos): 98-109, WITH a stack frame.
 *   * six named value-locals (the form below): 29, INERT across 6 declaration orders x
 *     6 statement orders x 2 decl styles, named results, 1-4 dummy locals, swapped
 *     factor orders, and six value locals + initialised result temps.
 *   * NEW: `register` on the locals, `register` on the parameters, declare-then-assign,
 *     read order != declaration order (30), two-result-temps + one direct store (29),
 *     one-result-temp (29), 4 named product locals (IDO folds them away -- byte
 *     identical to the base), 2 value locals + 4/2 named product locals (99),
 *     0 value locals + 4 product locals (110), `-(a1*b0 - a0*b1)` (40, adds neg.s).
 *   * COMPILER FLAGS: -O1/-O0/-O3/-g/-g1/-g2 all strictly worse; -O3 -g3 == -O2 -g3;
 *     -mips1: 39.  An OPT_FLAGS override is NOT the answer.
 *   * PERMUTER (conker/permuter_tu.sh, selftest PASS, TU context confirmed irrelevant
 *     for this single-function TU): 8027 iterations, -j 6.  Best asm-differ score 455
 *     (base 530) but that output is SEMANTICALLY WRONG -- it uses c[2] as scratch
 *     (`c[2] = a0; c[2] = b1; c[2] = c[2]*c[2] - a1*b0;`) so it computes b1*b1.
 *     Re-scored in-TU with fastscore, every honest permuter output is 29.
 *     Measured result: the permuter did not move this function.
 *
 * NEXT STEP IF ANYONE RETURNS: treat as hand-written asm (leave the pragma), or
 * disprove the pool rule above with a counter-example probe before spending more time.
 */
#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_150AD8B0(f32 *a, f32 *b, f32 *c) {
    f32 a0 = a[0], a1 = a[1], b0 = b[0], b1 = b[1], b2 = b[2], a2 = a[2];
    c[2] = a0 * b1 - a1 * b0;
    c[0] = a1 * b2 - a2 * b1;
    c[1] = a2 * b0 - a0 * b2;
}
