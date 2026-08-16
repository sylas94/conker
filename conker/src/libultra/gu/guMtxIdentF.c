#include <ultra64.h>
#include "functions.h"
#include "variables.h"

// PARKED -- almost certainly HAND-WRITTEN ASSEMBLY, same as its ROM neighbour guMtxF2L.
// conker.us.yaml sandwiches this TU inside the 0x150A hand-asm math cluster:
//   0xD4C40 libultra/gu/guMtxF2L (parked, proven hand-asm by its bare cvt.w.s)
//   0xD4E10 game_D4E10   4 pragmas, 0 live C
//   0xD5070 libultra/gu/guMtxIdentF   <- here
//   0xD5500 game_D5500   2 pragmas, 0 live C
// while every gu routine that IS compiled C lives elsewhere and is already matched (cosf,
// sinf, guPerspectiveF, guRotateF at 0x750B0-0x75640; guNormalize, mtxcatl at 0x21D4A0).
// See the guMtxF2L comment for the full argument. That independently explains the codegen
// wall below, which no source shape or flag combination can cross.
//
// Best honest score 1110 at -O2 from the reconstruction below. The instruction
// MIX and COUNT are already exactly right (20 words, `sw zero` for the off-diagonal,
// one `lui/mtc1` for the 1.0f, the last `swc1` in the `jr ra` delay slot); the only two
// residuals are a register NAME and a store ORDER, and this IDO cannot produce both at once:
//
//   flags      1.0f constant                       store order
//   ---------  ----------------------------------  -----------------------------------
//   -O2 / -O3  CSE'd to ONE mtc1, but into $f0     all 4 swc1 SUNK below all 12 sw
//   -O1 / -g3  lands in $f4 (correct!), but NOT    all 4 swc1 SUNK below all 12 sw
//              CSE'd -- four mtc1 ($f4/$f6/$f8/$f10)
//   ROM        ONE mtc1 into $f4                   source order, ONE swap (0x4 before 0x0)
//
// $f4-with-CSE is unreachable: CSE moves the constant into the compiler-temp pool ($f0),
// and only the *un*-CSE'd form is allocated from the user pool ($f4+). `register f32 one`
// does not help -- -O2 constant-propagates it straight back to a temp.
//
// The store sinking is NOT a scheduling flag. It reproduces at EVERY level including -g3
// (where scheduling is off and the `jr ra` delay slot is left as a nop), so it is this
// IDO's code generator grouping stores by instruction class -- all mtc1, then all sw, then
// all swc1. The ROM instead shows a single latency fill (`sw zero,4(a0)` hoisted between
// the mtc1 and its first swc1) and otherwise strict address order, i.e. a scheduler with a
// much smaller window. Closing this needs a different compiler build, not a different
// source; every source shape below is byte-equivalent input to IDO and scores identically:
//   *(s32 *)&mf[0][1] = 0;      (standard C, shown below)      -O2 1110  -g3 1490
//   ((s32)mf[0][1])   = 0;      (cast-as-lvalue extension)     -O2 1110  -g3 1490
//   s32 *m = (s32 *)mf; m[1] = 0;                              -O2 1110
// The SDK's plain double loop does NOT unroll here (-O2 scores 4145), so the shipped code
// is definitely straight-line, not the published `for (i..4) for (j..4) if (i==j)` form.
//
// Deliberately NOT closed with the `if (0) {}` + `dummy_label:;` scheduler-fence pair the
// earlier attempt used: those are forcers, they carry no semantics, and they only paper
// over the ordering half of the gap anyway.
//
// void guMtxIdentF(float mf[4][4]) {
//     mf[0][0] = 1.0;
//     *(s32 *)&mf[0][1] = 0;
//     *(s32 *)&mf[0][2] = 0;
//     *(s32 *)&mf[0][3] = 0;
//     *(s32 *)&mf[1][0] = 0;
//     mf[1][1] = 1.0;
//     *(s32 *)&mf[1][2] = 0;
//     *(s32 *)&mf[1][3] = 0;
//     *(s32 *)&mf[2][0] = 0;
//     *(s32 *)&mf[2][1] = 0;
//     mf[2][2] = 1.0;
//     *(s32 *)&mf[2][3] = 0;
//     *(s32 *)&mf[3][0] = 0;
//     *(s32 *)&mf[3][1] = 0;
//     *(s32 *)&mf[3][2] = 0;
//     mf[3][3] = 1.0;
// }
#pragma GLOBAL_ASM("asm/nonmatchings/libultra/gu/guMtxIdentF/guMtxIdentF.s")
