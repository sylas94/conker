/* tools/nearmiss/func_151DD970.c -- game_20AE20, 29 instructions, leaf
 *
 * STATUS: mism=48, n=31/29 (TWO OVER).  Cold decompile 2026-08-25 off the LAW A sweep
 * (see NOTES_ido_loop_laws.md); this is the cleanest textbook instance of that law found.
 *
 * WHAT IT IS: a 23-byte copy, D_8008FE54 -> D_800E0BE0, both s8 (lb/sb).
 *      23 % 4 == 3  ->  golden PEELS 3 iterations with absolute addressing, then runs a
 *      4x-unrolled loop from D_8008FE57 to D_8008FE6B (5 iterations).  Exactly LAW A.
 * The body below is certainly the right source; only the peel's SCHEDULE is off.
 *
 * ------------------------------------------------------------------ SCORE LADDER (measured)
 *   173  pointer do-while against `&D_8008FE54[23]` -- n=13, NOT unrolled at all.  A symbol
 *        comparison hides the trip count, so the unroller never runs.  (Same mechanism as
 *        the f32 loop in func_15017640: pointer bound => real loop, index bound => unroll.)
 *   128  a 23-byte struct assignment -- n=18, a different expansion entirely
 *    48  `for (i = 0; i < 23; i++) D_800E0BE0[i] = D_8008FE54[i];`   <-- PARKED
 *        identical for `i != 23` and for complete `[23]` array declarations
 *
 * ------------------------------------------------------------------ WHAT IS LEFT: 2 luis
 * Golden emits the peel as THREE LOADS THEN THREE STORES, so the three stores are adjacent
 * and share ONE `lui $at`:
 *      lui t6 ; lui t7 ; lui t8 ; lb t8,%lo(FE56) ; lb t7,%lo(FE55) ; lb t6,%lo(FE54)
 *      lui at ; ... ; sb t8,%lo(0BE2)(at) ; sb t7,%lo(0BE1)(at) ; sb t6,%lo(0BE0)(at)
 * We interleave load/store/load/store/load/store, and IDO's $at tracking is invalidated by
 * ANY intervening instruction, so we pay `lui $at` three times -- exactly the 2 extra words.
 *
 * PROVEN by a deliberate probe (scratchpad/r6.c): hoisting the three loads into locals so the
 * three stores land adjacent drops n to 29/29 and mism to 27.  So adjacency IS the mechanism.
 * That probe is NOT the answer -- it spells the peel by hand, which is exactly what LAW A says
 * not to do, and it re-introduces base pointers where golden uses per-symbol luis.
 *
 * REOPEN WITH: whatever makes IDO order the unroll PROLOGUE as loads-then-stores instead of
 * interleaved.  Ours reorders a load ahead of a preceding store (the aggressive, alias-aware
 * order); golden keeps the conservative order.  Find what makes IDO conservative about these
 * two symbols and the two luis collapse on their own.
 */

extern s8 D_8008FE54[];
extern s8 D_800E0BE0[];

void func_151DD970(void) {
    s32 i;

    for (i = 0; i < 23; i++) {
        D_800E0BE0[i] = D_8008FE54[i];
    }
}
