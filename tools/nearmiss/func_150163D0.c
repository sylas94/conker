/*
 * ===================================================================== CLOSED
 * func_150163D0 (game_43880.c, 304 B) -- MATCHED.  game_43880.c is retired
 * (0 pragmas).  verify_match.sh: ALL CHECKS RAN AND PASSED (.text SECTION SIZE
 * 0x130 both sides, .text IDENTICAL).  relcheck.py: PASS, 3 relocated fields
 * checked, 0 unpaired HI16.
 *
 * FINAL SOURCE (no forcers -- every statement carries meaning):
 *
 *   typedef struct { s32 unk0; s32 unk4; } Struct43880;
 *   extern Struct43880 *D_800D18B0;
 *
 *   void func_150163D0(s32 arg0) {
 *       s32 count;
 *       s32 i;
 *
 *       if (func_1502B7F0((s32 *)&D_800D18B0, 3, 12, arg0, 9) > 0) {
 *           count = 1;
 *           i = 0;
 *           while (D_800D18B0[i].unk0 != 0) {
 *               count++;
 *               i++;
 *           }
 *           for (i = 0; i < count - 1; i++) {
 *               D_800D18B0[i].unk0 += (s32)D_800D18B0;
 *           }
 *       } else {
 *           D_800D18B0 = NULL;
 *       }
 *   }
 *
 * ------------------------------------------------------------- WHY IT WAS HARD
 * The previous analysis mis-read the asm.  It saw `addiu a0,zero,1` and
 * `addiu a3,a0,-1` and concluded the scan counter was "biased +1" and indexed
 * `arr[i - 1]`.  It is not.  The +1 counter is `count` (which counts the NULL
 * terminator record as one), and the 0-based index `i` was ELIMINATED as a
 * redundant induction variable and strength-reduced into the pointer.  Every
 * spelling built on the `arr[i - 1]` reading sat on an 80/74 plateau because it
 * was reproducing IDO's OUTPUT rather than IDO's INPUT.
 *
 * ================================================== THE REUSABLE LAW (new, big)
 *   AN INIT THAT SURVIVES IN A BLOCK THAT SEEMS NOT TO NEED IT IS EVIDENCE OF A
 *   SECOND INDUCTION VARIABLE THAT IDO ELIMINATED.
 *
 * The whole residual was one missing word: golden emits `or a1,zero,zero` (i = 0)
 * TWICE -- once in the loop-1 preheader and once on the loop-1 exit path -- and
 * therefore never constant-folds `sll a0,a1,3` at the loop-2 preheader.  Every
 * single-init spelling gives ONE def, which folds to `sll a0,zero,3`.
 *
 * The mechanism is IDO's partial redundancy elimination:
 *   - `i = 0` is live entering loop 1 (loop 1 uses i as its index),
 *   - on the loop-NOT-taken path (the `beql` early exit) i is still 0, so the
 *     loop-2 init is already AVAILABLE -> no insertion,
 *   - on the loop-TAKEN path i was clobbered -> insert `i = 0` there.
 *   => two reaching defs at the use => the constant fold is blocked.
 * Then the `blez` guard's delay slot is left for `addiu v0,a0,-1` instead of
 * being filled with the sunk `or a1,zero,zero`, which is the +1 word.
 *
 * DIAGNOSTIC RECIPE that found it (cheap, generalises):
 *   1. fastscore the current candidate; if `n` is short by exactly k words and
 *      the missing words are register INITS, ask what could clobber that
 *      register on ONE predecessor of the join.
 *   2. Add a deliberate clobber of that variable inside the preceding loop
 *      (`j++`).  If the length snaps to n = golden, the model is confirmed:
 *      game_43880 went 80/n=74 -> 31/n=76 on that one edit.
 *   3. NOW hunt for the honest source that makes that clobber meaningful.  Here
 *      the permuter, re-seeded from the confirmed-shape candidate, closed the
 *      last 31 rows (a v0/v1 swap) by moving the array index onto the clobbered
 *      variable -- which is exactly what a second induction variable looks like.
 *   NOTE step 2's clobber is a DIAGNOSTIC, not a candidate: `j++` with `j` dead
 *   is not C anyone writes, and it was NOT shipped.
 *
 * PERMUTER NOTE.  Seeding the permuter from the 80-plateau base ran 2039
 * iterations and reached only 355.  Re-seeded from the step-2 diagnostic (390 on
 * the permuter's scale) it hit score 0 three times within 1604 iterations.  The
 * permuter is a LOCAL search: paying for the structural insight first is worth
 * more than any amount of extra CPU on the wrong basin.
 *
 * PERMUTER PROPOSALS REJECTED (all reached 0 or near-0, none shipped):
 *   - `D_800D18B0[i - (new_var = 1)]` with `unsigned short new_var` (355):
 *     an assignment-expression buried in a subscript.  Rejected as a forcer;
 *     its only real content was "stop IDO folding the -1", which the correct
 *     0-based reading gives for free.
 *   - `j = 0; j = i - 1;` back-to-back before the scan loop (score 0): a dead
 *     store followed by a redundant one.  Same object as the clean form, so it
 *     is pure noise; the clean form was derived from it and shipped instead.
 *
 * RULED OUT ALONG THE WAY (all identical objects, worth not re-testing):
 *   - `j = 0;` before loop 1 with the loop-2 init still in the `for` header:
 *     DCE removes the first store, byte-identical to the plain form.
 *   - `j = 0;` BETWEEN the loops, with `for (; j < i-1; j++)` or a `while`:
 *     also byte-identical.  (The old note that this "destroys the 4x unroll" is
 *     wrong -- only hoisting it ABOVE loop 1 with a `for (;;)` header did that.)
 *   - explicit `Struct43880 *p` pointer walkers in loop 1, in four placements:
 *     all lose the extra word and fall back to 74 instructions.
 *   - a `count` variable used as loop 2's BOUND (`for (j=0; j<count; j++)`):
 *     IDO then eliminates `i` instead of `j` and the whole shape inverts (98).
 *     The bound must be the expression `count - 1`.
 */
