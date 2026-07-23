#include <ultra64.h>


// Best 160 under -g3 (only the final jr delay slot differs). Reconstruction is
// algorithmically exact and matches to the last 2 instrs under -O2; the target has
// `swc1 0x3c` then `sw zero 0x38` in the jr delay slot, which -g3 will not fill for a
// pure-store function (leaves a nop). Needs a scheduling-enabled flag to reach 0.
// void func_150A7CB0(f32 mtx[4][4], s32 x, s32 y, s32 z) {
//     *(s32 *)&mtx[0][0] = x;
//     *(s32 *)&mtx[0][1] = 0; *(s32 *)&mtx[0][2] = 0; *(s32 *)&mtx[0][3] = 0;
//     *(s32 *)&mtx[1][0] = 0;
//     *(s32 *)&mtx[1][1] = y;
//     *(s32 *)&mtx[1][2] = 0; *(s32 *)&mtx[1][3] = 0;
//     *(s32 *)&mtx[2][0] = 0; *(s32 *)&mtx[2][1] = 0;
//     *(s32 *)&mtx[2][2] = z;
//     *(s32 *)&mtx[2][3] = 0;
//     *(s32 *)&mtx[3][0] = 0; *(s32 *)&mtx[3][1] = 0;
//     mtx[3][3] = 1.0f;
//     *(s32 *)&mtx[3][2] = 0;
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_D5160/func_150A7CB0.s")

// NON-MATCHING: sw/jr in wrong order
// void func_150A7CB0(f32 mtx[4][4], s32 x, s32 y, s32 z) {
//     ((s32)mtx[0][0]) = x;
//     ((s32)mtx[0][1]) = 0;
//     ((s32)mtx[0][2]) = 0;
//     ((s32)mtx[0][3]) = 0;
//     ((s32)mtx[1][0]) = 0;
//     ((s32)mtx[1][1]) = y;
//     ((s32)mtx[1][2]) = 0;
//     ((s32)mtx[1][3]) = 0;
//     ((s32)mtx[2][0]) = 0;
//     ((s32)mtx[2][1]) = 0;
//     ((s32)mtx[2][2]) = z;
//     ((s32)mtx[2][3]) = 0;
//     ((s32)mtx[3][0]) = 0;
//     ((s32)mtx[3][1]) = 0;
//     mtx[3][3] = 1.0f;
//     // fakematch to "help"...
//     dummy_label_123:;
//     ((s32)mtx[3][2]) = 0;
// }
