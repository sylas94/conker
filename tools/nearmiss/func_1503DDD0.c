/* game_6B280 / func_1503DDD0 -- PARKED at 260 (naive spelling: 1245)
 *
 * The full model, the seven spellings tried and their scores are recorded in the block
 * comment at the top of conker/src/game_6B280.c, which is the file a future attempt will
 * open first. This file records only what is NOT obvious from there.
 *
 * WHAT IS LEFT (three instruction-level rows plus register rotation):
 *
 *   golden                          ours (260)
 *   44: beqz  v0,end                44: beqz  v0,end
 *   48:  addiu a0,v0,-1             48:  nop
 *   4c: multu a0,a3                 4c: multu v0,a3
 *   ...                             ...
 *   5c: lhu   t3,6(v1)              5c: lhu   t3,-0xe(v1)
 *   7c: lhu   t6,6(v1)              7c: lhu   t5,-0xe(v1)
 *
 * Both compute &ENTRIES[count-1].unk6 and both strength-reduce the loop to
 * `addiu v1,v1,-0x14`. The only difference is WHERE the -1 lives: golden multiplies
 * (count-1) by the 0x14 stride held in a3; we multiply count and fold the resulting -20
 * into the load displacement (6 - 20 = -0xE). IDO distributed the subtraction over the
 * multiply for us and did not for the original.
 *
 * THE DECISIVE MEASUREMENT (do not redo it): the SIGNEDNESS of the loop variable controls
 * the normalisation, but the two halves cannot be had at once.
 *     s32 count  ->  `li a3,0x14` + `multu a0,a3`  (golden's multiply)  and  `-0xe(v1)`
 *     u32 count  ->  `6(v1)`      (golden's displacement)               and  a shift/add
 *                    chain instead of the register multiply (total score 1915)
 * Both come out of the same IV analysis. Signed is much closer overall, hence 260.
 *
 * WHY THIS IS PROBABLY NOT A SPELLING PROBLEM
 * The loop body, the loop rotation, the store-before-test ordering and even IDO's
 * redundant `move v0,t5` copy are all reproduced exactly by
 *     D_800C6654 = count - 1;
 *     count--;
 * Every restructuring that changes the index expression far enough to move the
 * normalisation ALSO destroys the strength reduction (the two-local form went to 1210
 * with a `multu` recomputed every iteration; the pointer-walk form went to 370). So the
 * two properties are coupled through the same IV analysis and no honest spelling found so
 * far gets both. Next idea worth trying: something that makes 0x14 a compile-time
 * constant at the point of the index (note golden keeps it in a3 via `li a3,0x14`, which
 * is the -Wab,-r4300_mul register-multiply path) -- e.g. checking whether any already-
 * matching function in the tree indexes a 20-byte array by `i-1` inside a loop, and
 * copying its exact shape.
 *
 * TWO HEADER INACCURACIES CONFIRMED HERE (neither header was edited):
 *   structs.h  struct160.unk6   is u16, not s16   (golden uses `lhu`)
 *   variables.h D_800C6650      is a struct160 *, not a struct160[]
 *                               (game_32490.c already works around this the same way)
 */
