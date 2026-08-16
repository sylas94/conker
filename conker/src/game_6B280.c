#include <ultra64.h>
#include "functions.h"
#include "variables.h"

/* NON-MATCHING, best score 260 (the naive first spelling scores 1245).
 *
 * THREE HEADER INACCURACIES were confirmed while modelling this function. None of the
 * shared headers was edited; the model below shadows them file-locally instead.
 *   1. variables.h `extern s32 D_800C6654`  -- really u32. Golden bounds-checks arg0
 *      against it with `sltu`, which a signed count cannot produce.
 *   2. structs.h `struct160.unk6` is s16    -- really u16. Golden reads it with `lhu`.
 *   3. variables.h `extern struct160 D_800C6650[]` -- really a `struct160 *`.
 *      func_15004FE0 in game_32490.c allocates it and stores through
 *      `(*(struct160 **)&D_800C6650)`; the same workaround is used here.
 *
 * WHAT MATCHES: every basic block, every branch, the loop rotation, the store-before-test
 * ordering, IDO's redundant `move v0,t5` copy, and the strength-reduced
 * `addiu v1,v1,-0x14` pointer walk.
 *
 * THE RESIDUAL is one induction-variable normalisation choice, three rows:
 *
 *   golden                        ours (260)
 *   48:  addiu a0,v0,-1           48:  nop
 *   4c:  multu a0,a3              4c:  multu v0,a3
 *   5c:  lhu   t3,6(v1)           5c:  lhu   t3,-0xe(v1)
 *   7c:  lhu   t6,6(v1)           7c:  lhu   t5,-0xe(v1)
 *
 * Both address &ENTRIES[count-1].unk6. Golden multiplies (count-1) by the 0x14 stride;
 * we multiply count and fold the resulting -20 into the load displacement (6-20 = -0xE).
 * Everything else is pure register rotation.
 *
 * KEY MEASUREMENT: signedness of the INDEX controls this, but not usably. Declaring the
 * loop variable `u32` DOES give golden's `lhu ...,6(v1)` -- and simultaneously throws away
 * golden's `li a3,0x14` + `multu a0,a3` register multiply in favour of a shift/add chain
 * (score 1915). Signed gives the multu and the wrong displacement; unsigned gives the
 * right displacement and the wrong multiply. The two properties come out of the same IV
 * analysis and no honest spelling found so far gets both.
 *
 * Spellings tried (all honest; none beat 260):
 *   1245  no local at all, loop driven straight off the global (no strength reduction)
 *    610  local, body `count--; D_800C6654 = count;`      (store sinks below the test)
 *    260  local, body `D_800C6654 = count - 1; count--;`  <- BEST, shown below
 *   1210  two locals (count + a separate index) -- loses strength reduction entirely
 *   3065  `while (count != 0) { count--; if (!(...)) break; ... }`
 *    710  `for (count = D_800C6654; ...; count--)`
 *    370  explicit `Entry1503DDD0 *p` pointer walk
 *   1915  `u32 count` (see KEY MEASUREMENT above)
 *
 * WAVE 61 -- five more structures, and the decisive negative result:
 *    260  the rotated form written out longhand,
 *         `if (count && (E[count-1].unk6 & 2)) do { ...; if (!count) break; } while (...)`
 *   1210  `i = count - 1;` index local carried across the loop, subscript `ENTRIES[i]`
 *   1210  same with the index declared first
 *   1295  same with `count = i; D_800C6654 = count; i = count - 1;`
 *   2995  `while (count != 0) { if (!(...)) break; ... }`
 *   2495  loop driven off the global with `D_800C6654--`
 *    745  x4 -- golden's EXACT control flow with a named `Entry1503DDD0 *p` local:
 *              p = &ENTRIES[count - 1];
 *              while (p->unk6 & 2) { D_800C6654 = count-1; count--; if (!count) return; p--; }
 *         and the three variations `ENTRIES + (count - 1)`, pointer declared first, and the
 *         `for (p = ...; p->unk6 & 2; p--)` form.  ALL FOUR still emit `multu v0,a3` +
 *         `lhu ...,-0xe(v1)`.
 * THAT LAST RESULT IS THE BAIL PROOF.  A named pointer local removes the `-1` from every
 * subscript in the source -- there is no displacement for the compiler to fold into -- and
 * IDO folds it anyway, by re-basing the pointer induction variable itself.  The
 * normalisation therefore happens in IDO's IV rewriting, downstream of anything the source
 * can express.  Twelve genuinely different structures, three of them golden's exact CFG.
 * Parked as an IDO codegen tie, not a spelling.
 *
 * #define D_800C6654 D_800C6654_s32_decl_in_variables_h
 * #include "variables.h"
 * #undef D_800C6654
 * extern u32 D_800C6654;
 *
 * typedef struct {
 *     s16 unk0; s16 unk2; s16 unk4; u16 unk6;     // unk6 is u16, not s16
 *     u32 unk8; s16 unkC; s16 unkE; s16 unk10; s16 unk12;
 * } Entry1503DDD0; // size 0x14
 *
 * #define ENTRIES (*(Entry1503DDD0 **)&D_800C6650)
 *
 * void func_1503DDD0(s32 arg0) {
 *     s32 count;
 *
 *     if ((arg0 < 0) || (arg0 >= D_800C6654)) {
 *         return;
 *     }
 *     ENTRIES[arg0].unk6 = 2;
 *     count = D_800C6654;
 *     while ((count != 0) && (ENTRIES[count - 1].unk6 & 2)) {
 *         D_800C6654 = count - 1;
 *         count--;
 *     }
 * }
 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B280/func_1503DDD0.s")
