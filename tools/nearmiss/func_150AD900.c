/* tools/nearmiss/func_150AD900.c -- game_DADB0 (BOTH functions of the TU; 2 pragmas)
 *
 * FILE KIND: STANDALONE TU. Score directly:
 *   python3 tools/fastscore.py game_DADB0 func_150AD900 tools/nearmiss/func_150AD900.c
 *   python3 tools/fastscore.py game_DADB0 func_150AD930 tools/nearmiss/func_150AD900.c
 *
 * *** THIS TU IS BUILT WITHOUT DEBUG INFO. -g3 IS THE BLOCKER. MEASURED 2026-08-23. ***
 *      -O2 -g3 (tree default)   AD900 mism=21 n=13/12   |  AD930 mism=41 n=15/12
 *      -O2  (no -g3)            AD900 mism=10 n=12/12   |  AD930 mism=9  n=12/12   <- BOTH EXACT
 *      -O1                      AD900 mism=10 n=12/12   |  AD930 mism=52 n=16/12
 *      -g                       AD900 mism=50           |  AD930 mism=92
 * -g3 is what stops IDO filling the `jr $ra` delay slot. At plain -O2 the final add moves
 * into the slot and BOTH functions become length-exact. The tree already records this exact
 * pattern -- conker/Makefile's libultra comment says libultra "was shipped compiled without
 * debug info", and there are ~20 `OPT_FLAGS := -g` overrides for init_* TUs. game_DADB0
 * belongs in that group.
 *
 * REQUIRED WHEN EITHER FUNCTION GOES LIVE:
 *      $(BUILD_DIR)/$(SRC_DIR)/game_DADB0.c.o: OPT_FLAGS := -O2
 *
 * *** THEREFORE THE ENTIRE "DO NOT REPEAT" LIST BELOW WAS MEASURED AT THE WRONG BASELINE. ***
 * It was all scored at -O2 -g3. Re-run at -O2, with a control in the same sweep:
 *      AD900: current a2b2+(a0b0+a1b1) 10 | operands swapped 10 | left-to-right 11
 *             explicit ((..+..)+..) 11    | partial sum named 11 | accumulator += 22
 *      AD930: current 9 | no inner parens 9 | explicit parens 9 | third term first 9
 *             named sum 10 | accumulator += 10
 * The current spellings survive as the best, so the list's CONCLUSION happens to hold -- but
 * its numbers do not, and a refutation measured against a wrong baseline is not a refutation.
 *
 * WHAT REMAINS is FP register naming only, and it looks hand-written: golden accumulates into
 * $f0 from the first instruction (`mul.s $f0,$f0,$f2`, dest == source; `mul.s $f0,$f0,$f0` for
 * the squares), while IDO allocates fresh temps from $f4/$f12 upward and only writes $f0 at
 * the end. Accumulating into the return register from the start is what an asm author does.
 * These two sit at 0x150AD9xx, inside the region already identified as the HAND-WRITTEN math
 * cluster (sin/cos/matrix/RNG), so C may not reach 0 here at all.
 *
 * SUPERSEDED MEASUREMENT 2026-08-22, tree default -O2 -g3:
 *   func_150AD900  mism=21  n=13/12   (dot product)
 *   func_150AD930  mism=41  n=15/12   (vector length)
 *
 * SEMANTICS ARE CERTAIN, read straight off golden:
 *   func_150AD900 = a[0]*b[0] + a[1]*b[1] + a[2]*b[2]
 *   func_150AD930 = sqrtf(a[0]*a[0] + a[1]*a[1] + a[2]*a[2])
 *
 * THE BLOCKER on func_150AD900 is SCHEDULING, precisely characterised.
 * Golden (12 words) interleaves the third multiply BETWEEN the two adds, which breaks the
 * add->add dependency chain and lets the final add fill the jr delay slot:
 *      lwc1 f0,0(a0) ; lwc1 f2,0(a1) ; lwc1 f4,4(a0) ; mul.s f0,f0,f2
 *      lwc1 f6,4(a1) ; lwc1 f8,8(a0) ; mul.s f4,f4,f6 ; lwc1 f10,8(a1)
 *      add.s f0,f0,f4 ; mul.s f8,f8,f10 ; jr $ra ; add.s f0,f0,f8
 * Ours (13 words) issues all three multiplies, then two BACK-TO-BACK adds, so the final
 * add cannot fill the delay slot and IDO emits a nop.
 * Golden also uses the ACCUMULATOR form (mul.s f0,f0,f2, dest == source) where every
 * spelling tried keeps three separate destinations -- golden has fewer live values.
 *
 * DO NOT REPEAT (all measured IN-FILE with both functions present)
 *   a[0]*b[0] + a[1]*b[1] + a[2]*b[2]              22
 *   ((a0*b0) + (a1*b1)) + (a2*b2)                  22
 *   (a0*b0 + a1*b1) + a2*b2                        22
 *   named products p0,p1,p2 then p0+p1+p2          22
 *   accumulator s = ..; s += ..; s += ..           32   (n=14/12, WORSE)
 *   a[2]*b[2] + (a[0]*b[0] + a[1]*b[1])            21   <- current best
 *
 * *** MEASUREMENT WARNING -- cost the lead a wrong turn ***
 * Do NOT score these in a file containing only ONE of them. Alone, the function is last in
 * .text and absorbs different trailing padding: the same source read n=16/12 solo versus
 * n=13/12 in-file. Keep BOTH functions present.
 */
#include <ultra64.h>
#include "functions.h"
#include "variables.h"

f32 func_150AD900(f32 *a, f32 *b) {
    return a[2]*b[2] + (a[0]*b[0] + a[1]*b[1]);
}

f32 func_150AD930(f32 *a) {
    return sqrtf((a[0] * a[0]) + (a[1] * a[1]) + (a[2] * a[2]));
}
