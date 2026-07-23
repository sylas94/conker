#include <ultra64.h>
#include "functions.h"
#include "variables.h"


// s16 / f32 matrix
// FILE-FLAGS-SUSPECT: needs -mips3 (target has 8x `sd zero`; -mips2 emits li+sw pairs).
// guTranslate-style: build a fixed-point Mtx = identity with translation (x,y,z) in the
// bottom row, from 3 f32 args passed in a1/a2/a3 (int regs after the pointer arg0).
// Unverified reconstruction (cannot pscore-0 until the -mips3 override is added):
// void func_150A7D00(s16 *m, f32 x, f32 y, f32 z) {
//     s32 xi = x * 65536.0f, yi = y * 65536.0f, zi = z * 65536.0f;
//     s32 *w = (s32 *)m;
//     w[0]=0;w[1]=0;w[2]=0;w[3]=0;w[4]=0;w[5]=0;w[6]=0;w[7]=0;   // 8x sd zero (-mips3)
//     w[8]=0;w[9]=0;w[10]=0;w[11]=0;w[12]=0;w[13]=0;w[14]=0;w[15]=0;
//     m[0]=1; m[5]=1; m[10]=1; m[15]=1;                          // int-part diagonal
//     m[12]=(u32)xi>>16; m[13]=(u32)yi>>16; m[14]=(u32)zi>>16;   // int-part translation
//     m[28]=xi; m[29]=yi; m[30]=zi;                              // frac-part translation
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_D51B0/func_150A7D00.s")
