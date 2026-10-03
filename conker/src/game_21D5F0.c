#include <ultra64.h>
#include "functions.h"
#include "variables.h"


// HAND-WRITTEN (or a different compiler build) -- PROVEN 2026-08-26, not a guess.
//
// The semantics are the published SDK guMtxXFMF and the reconstruction below is right:
// at the TU's own -O2 it reaches mism=49, n=41/40, and `mf[i][j] * <coord>` (matrix operand
// FIRST) reproduces every mul.s encoding.  The single structural gap is how the third float
// argument gets into the FP file:
//     golden:  mtc1 $a1,$f12   mtc1 $a2,$f14   mtc1 $a3,$f16
//     ours:    mtc1 $a1,$f12   mtc1 $a2,$f14   sw $a3,0xC($sp) / lwc1 $fN,0xC($sp)
// That extra word is the whole length difference, and every later FP register is rotated by it.
//
// IDO 5.3 CANNOT EMIT THE THIRD mtc1.  Standalone probe (ido5.3_recomp cc, -O2, objdump -dz),
// three functions with three f32 parameters behind a pointer:
//     f(void*, f32 x, f32 y, f32 z) { return x + y + z; }  ->  mtc1 a1,$f12 / mtc1 a2,$f14 /
//                                                              sw a3,12(sp) / lwc1 $f6,12(sp)
//     ...{ return z + y + x; }                             ->  mtc1 a2,$f14 / mtc1 a3,$f12 /
//                                                              sw a1,4(sp)  / lwc1 $f6,4(sp)
//     ...with a 5th stack arg and a store                  ->  same shape again
// i.e. this compiler has exactly TWO GPR->FPR move targets, $f12 and $f14, handed to whichever
// two floats it needs first; every further float parameter goes through its home slot.  No
// source spelling can produce a third mtc1, so no source spelling can match this function.
// Flags checked on the best spelling: -O2 = 49 (best), -O2 -g3 = 58 (n=42/40), -O1 = 130
// (n=49/40), -O3 = asm-processor reject.  Local copies of the parameters: 50.
//
// void guMtxXFMF(float mf[4][4], float x, float y, float z, float *ox, float *oy, float *oz) {
//     *ox = mf[0][0] * x + mf[1][0] * y + mf[2][0] * z + mf[3][0];
//     *oy = mf[0][1] * x + mf[1][1] * y + mf[2][1] * z + mf[3][1];
//     *oz = mf[0][2] * x + mf[1][2] * y + mf[2][2] * z + mf[3][2];
// }
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
