#include <ultra64.h>
#include "functions.h"
#include "variables.h"


// handwritten?
#pragma GLOBAL_ASM("asm/nonmatchings/game_21D5F0/guMtxXFMF.s")
// void func_151F0140(f32 arg0[4][4], f32 arg1, f32 arg2, f32 arg3, f32 *arg4, f32 *arg5, f32 *arg6) {
//     *arg4 = arg0[0][0] * arg1 + arg0[1][0] * arg2 + arg0[2][0] * arg3 + arg0[3][0];
//     *arg5 = arg0[0][1] * arg1 + arg0[1][1] * arg2 + arg0[2][1] * arg3 + arg0[3][1];
//     *arg6 = arg0[0][2] * arg1 + arg0[1][2] * arg2 + arg0[2][2] * arg3 + arg0[3][2];
// }

void guMtxCatF(float m[4][4], float n[4][4], float r[4][4]) {
    int i;
    int j;
    int k;
    float temp[4][4];

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            temp[i][j] = 0.0f;
            for (k = 0; k < 4; k++) {
                temp[i][j] += m[i][k] * n[k][j];
            }
        }
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            r[i][j] = temp[i][j];
        }
    }
}
