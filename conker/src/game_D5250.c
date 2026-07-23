#include <ultra64.h>
#include "functions.h"
#include "variables.h"


// setting W values in identity matrix
// Best 635 under -g3. Reconstruction algorithmically exact; blocked by two things -g3
// won't reproduce for a pure-store fn: (1) the four 1.0f stores CSE to $f0 vs target $f4,
// (2) the mtc1/jr branch delay slots are left as nop instead of being filled with the
// adjacent `sw zero`/`swc1`. Needs a scheduling-enabled flag to reach 0.
// void func_150A7DA0(f32 arg0[4][4], s32 arg1, s32 arg2, s32 arg3) {
//     arg0[0][0] = 1.0f;
//     *(s32 *)&arg0[0][1] = 0; *(s32 *)&arg0[0][2] = 0; *(s32 *)&arg0[0][3] = 0;
//     *(s32 *)&arg0[1][0] = 0;
//     arg0[1][1] = 1.0f;
//     *(s32 *)&arg0[1][2] = 0; *(s32 *)&arg0[1][3] = 0;
//     *(s32 *)&arg0[2][0] = 0; *(s32 *)&arg0[2][1] = 0;
//     arg0[2][2] = 1.0f;
//     *(s32 *)&arg0[2][3] = 0;
//     *(s32 *)&arg0[3][0] = arg1;
//     *(s32 *)&arg0[3][1] = arg2;
//     *(s32 *)&arg0[3][2] = arg3;
//     arg0[3][3] = 1.0f;
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_D5250/func_150A7DA0.s")

// NON-MATCHING: same issues as other matrix funcs
// void func_150A7DA0(f32 arg0[4][4], s32 arg1, s32 arg2, s32 arg3) {
//     if (0) {};
//     ((s32)arg0[0][1]) = 0;
//     (arg0[0][0]) = 1.0f;
//     dummy_label_418035: ;
//     ((s32)arg0[0][2]) = 0;
//     ((s32)arg0[0][3]) = 0;
//     ((s32)arg0[1][0]) = 0;
//     (arg0[1][1]) = 1.0f;
//     ((s32)arg0[1][2]) = 0;
//     ((s32)arg0[1][3]) = 0;
//     ((s32)arg0[2][0]) = 0;
//     ((s32)arg0[2][1]) = 0;
//     (arg0[2][2]) = 1.0f;
//     ((s32)arg0[2][3]) = 0;
//     ((s32)arg0[3][0]) = arg1;
//     ((s32)arg0[3][1]) = arg2;
//     ((s32)arg0[3][2]) = arg3;
//     (arg0[3][3]) = 1.0f;
// }
