#include <ultra64.h>
#include "functions.h"
#include "variables.h"


// Best 635 under -g3. Reconstruction algorithmically exact; blocked by two things -g3
// won't reproduce for a pure-store fn: (1) the four 1.0f stores CSE to $f0 vs target $f4,
// (2) the mtc1/jr branch delay slots are left as nop instead of being filled with the
// adjacent `sw zero`/`swc1`. Needs a scheduling-enabled flag to reach 0.
// void guMtxIdentF(float mf[4][4]) {
//     mf[0][0] = 1.0f;
//     ((s32)mf[0][1]) = 0; ((s32)mf[0][2]) = 0; ((s32)mf[0][3]) = 0;
//     ((s32)mf[1][0]) = 0;
//     mf[1][1] = 1.0f;
//     ((s32)mf[1][2]) = 0; ((s32)mf[1][3]) = 0;
//     ((s32)mf[2][0]) = 0; ((s32)mf[2][1]) = 0;
//     mf[2][2] = 1.0f;
//     ((s32)mf[2][3]) = 0;
//     ((s32)mf[3][0]) = 0; ((s32)mf[3][1]) = 0; ((s32)mf[3][2]) = 0;
//     mf[3][3] = 1.0f;
// }
#pragma GLOBAL_ASM("asm/nonmatchings/libultra/gu/guMtxIdentF/guMtxIdentF.s")

// NON-MATCHING: assume handwritten like OOT
// void guMtxIdentF(f32 mf[4][4]) {
//     if (0) {};
//     ((s32)mf[0][1]) = (s32)0;
//     mf[0][0] = 1;
//     dummy_label:;
//     ((s32)mf[0][2]) = 0;
//     ((s32)mf[0][3]) = 0;
//     ((s32)mf[1][0]) = 0;
//     mf[1][1] = 1;
//     ((s32)mf[1][2]) = 0;
//     ((s32)mf[1][3]) = 0;
//     ((s32)mf[2][0]) = 0;
//     ((s32)mf[2][1]) = 0;
//     mf[2][2] = 1;
//     ((s32)mf[2][3]) = 0;
//     ((s32)mf[3][0]) = 0;
//     ((s32)mf[3][1]) = 0;
//     ((s32)mf[3][2]) = 0;
//     mf[3][3] = 1;
// }
