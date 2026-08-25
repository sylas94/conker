/* tools/nearmiss/func_151EF080.c -- game_21C4F0 (libultra TU; BOTH its functions live here)
 *
 * ############ func_151EF080 IS MATCHED AND SHIPPED, 2026-08-23. ROM GATE PASSED. ############
 * It is live C in conker/src/game_21C4F0.c and both sha1s are byte-perfect. func_151EF040
 * remains a #pragma; the notes below still apply to IT.
 *
 * THE FIX WAS A BUILD FLAG, NOT THE C. The C was always `return sqrtf(arg0);`.
 *      $(BUILD_DIR)/$(SRC_DIR)/game_21C4F0.c.o: OPT_FLAGS := -O2
 * At -g3 IDO refuses to schedule the final instruction into the `jr $ra` delay slot, so we
 * emitted `sqrt.s` BEFORE the `jr`; at -O2 the two swap and the function is byte-identical.
 *
 * *** THE OLD READING OF -O2 HERE WAS WRONG, AND THE ERROR IS INSTRUCTIVE. ***
 * The sweep below recorded "-O2 -> 1EF080 mism=10 n=5/4" and treated 10 as worse than 2.
 * But mism = 10*|length delta| + differing rows, so 10 with a 1-word delta means ZERO compared
 * rows differ -- the code already matched and the entire score was trailing padding. A score
 * is not a scalar to be compared blindly; decompose it before believing it.
 *
 * *** ALSO: -g0/-g1/-g2/-O3/-O1 -g3 DO NOT BUILD AT ALL. ***
 * Those rows in the old sweep are not measurements. Only -O2 -g3, -O2, -O1, -g and -O0 are
 * usable flag sets in this tree; anything else fails before it produces an object.
 *
 * FOR func_151EF040 (still open, 12 rows at -O2 -g3, 25 at -O2): golden keeps the status in
 * $s0 across __osPiRelAccess with frame 0x28; we spill it to the stack with frame 0x20. Since
 * the TU is now pinned at -O2 and a #pragma function is spliced from golden asm regardless of
 * OPT_FLAGS, that override does not affect it -- but whoever takes it on must re-measure at
 * -O2, not at the tree default.
 *
 * FILE KIND: STANDALONE TU. Score directly:
 *   python3 tools/fastscore.py game_21C4F0 func_151EF080 tools/nearmiss/func_151EF080.c
 *   python3 tools/fastscore.py game_21C4F0 func_151EF040 tools/nearmiss/func_151EF080.c
 *
 * MEASURED 2026-08-22 at the tree default -O2 -g3:
 *   func_151EF080   mism=2    n=4/4    (LENGTH EXACT)
 *   func_151EF040   mism=12   n=16/16  (LENGTH EXACT)
 *
 * WHAT THE TU IS. func_151EF040 is libultra osPiReadIo: __osPiGetAccess() ->
 * osPiRawReadIo(devAddr, data) -> __osPiRelAccess() -> return status. Golden homes
 * a0/a1 across the first call and parks the result in $s0, the stock SDK shape.
 * func_151EF080 is a bare sqrtf leaf (sqrtf is an intrinsic via
 * include/2.0L/PR/gu.h, "#pragma intrinsic(sqrtf)").
 *
 * THE ONLY RESIDUAL on func_151EF080 is instruction ORDER:
 *   idx0  ours sqrt.s $f0,$f12   golden jr $ra
 *   idx1  ours jr $ra            golden sqrt.s $f0,$f12   (delay slot)
 * Golden puts the sqrt in the jr delay slot; at -O2 -g3 IDO emits it before the jr.
 *
 * DO NOT REPEAT (all measured IN-FILE, both functions present)
 *   return sqrtf(x);                        2   <- current, the floor
 *   f32 r; r = sqrtf(x); return r;          2   (identical)
 *   return (f32)sqrt(x);                   84   (n=12/4 -- becomes a CALL)
 *   return __builtin_sqrtf(x);             84   (n=12/4 -- IDO has no such builtin)
 *   f64 return type                         3
 *
 * *** AN OPT_FLAGS OVERRIDE IS REFUTED -- DO NOT PROPOSE ONE. ***
 * Compiling func_151EF080 ALONE at -O2 or -O1 does put sqrt.s in the delay slot, which
 * looks like the answer. It is an artefact: alone, the function is last in .text and its
 * trailing padding changes. Scored IN-FILE with both functions present:
 *      -O2 -g3   1EF040 mism=12 n=16/16   |   1EF080 mism=2  n=4/4     <- BEST, both exact
 *      -O2       1EF040 mism=25 n=15/16   |   1EF080 mism=10 n=5/4
 *      -O1       1EF040 mism=25 n=15/16   |   1EF080 mism=10 n=5/4
 *      -g        1EF040 mism=54 n=20/16   |   1EF080 mism=41 n=8/4
 * The tree default is correct for this TU.
 *
 * ALSO REFUTED 2026-08-23: DEFINITION ORDER. IDO schedules the last function in a TU
 * differently from one with another definition after it, so "080 last" looked like it might
 * explain why the sqrt misses the delay slot in-file but hits it when compiled alone.
 * Measured, scoring BOTH functions in every arrangement:
 *      040 then 080 (current) ......... 080: 2  n=4/4   |  040: 12  n=16/16   <- best
 *      080 then 040 ................... 080: 12 n=3/4   |  040: 22  n=17/16
 *      080 then 040, 040 prototyped ... 080: 12 n=3/4   |  040: 22  n=17/16
 * Being LAST is what gives 080 its 4th word, so the current order is correct on both counts.
 *
 * NEXT MOVE: the 12 rows on func_151EF040 are the real target -- its length is already
 * exact, so it is register/schedule only, and closing it plus these 2 rows zeroes the TU.
 */
#include <ultra64.h>
#include "functions.h"
#include "variables.h"

s32 func_151EF040(u32 devAddr, u32 *data) {
    s32 status;

    __osPiGetAccess();
    status = osPiRawReadIo(devAddr, data);
    __osPiRelAccess();

    return status;
}

f32 func_151EF080(f32 arg0) {
    return sqrtf(arg0);
}
