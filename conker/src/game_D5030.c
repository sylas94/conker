#include <ultra64.h>

#include "functions.h"
#include "variables.h"


// FILE-FLAGS-SUSPECT: needs -mips3 (target uses `sd zero`; -mips2 emits li+sw pairs).
// Reconstruction verified correct under -mips3:
// void func_150A7B80(Mtx *arg0) {
//     s32 *w = (s32 *)arg0;
//     s16 *h = (s16 *)arg0;
//     w[0]=0;w[1]=0;w[2]=0;w[3]=0;w[4]=0;w[5]=0;w[6]=0;w[7]=0;
//     w[8]=0;w[9]=0;w[10]=0;w[11]=0;w[12]=0;w[13]=0;w[14]=0;w[15]=0;
//     h[0]=1; h[5]=1; h[10]=1; h[15]=1;
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_D5030/func_150A7B80.s")

// struct WORD {
//     s64 unk0;
// };
//
// struct SHORTS {
//     s16 unk0;
//     s16 unk2;
//     s16 unk4;
//     s16 unk6;
// };
//
// typedef struct {
//     union {
//         struct SHORTS s;
//         struct WORD w;
//     } u0;
//     union {
//         struct SHORTS s;
//         struct WORD w;
//     } u1;
//     union {
//         struct SHORTS s;
//         struct WORD w;
//     } u2;
//     union {
//         struct SHORTS s;
//         struct WORD w;
//     } u3;
//     union {
//         struct SHORTS s;
//         struct WORD w;
//     } u4;
//     union {
//         struct SHORTS s;
//         struct WORD w;
//     } u5;
//     union {
//         struct SHORTS s;
//         struct WORD w;
//     } u6;
//     union {
//         struct SHORTS s;
//         struct WORD w;
//     } u7;
// } baz;
//
// typedef struct {
//     s16 unk0;
//     // s16 unk2;
//     // s16 unk4;
//     // s16 unk8;
//     s16 unkA;
//     // s16 unkC;
//     // s16 unkE;
//     // s16 unk10;
//     // s16 unk12;
//     s16 unk14;
//     // s16 unk18;
//     // s16 unk1A;
//     // s16 unk1C;
//     s16 unk1E;
//     // s16 unk20;
//     // s16 unk22;
//     // s16 unk24;
//     // s16 unk28;
//     // s16 unk2A;
//     // s16 unk2C;
//     // s16 unk2E;
//     // s16 unk30;
//     // s16 unk32;
//     // s16 unk34;
//     // s16 unk38;
//     // s16 unk3A;
//     // s16 unk3C;
//     // s16 unk3E;
// } foobar;
//
// void func_150A7B80(baz *arg0)
// {
//     arg0->u0.w.unk0 = 0;
//     arg0->u1.w.unk0 = 0;
//     arg0->u2.w.unk0 = 0;
//     arg0->u3.w.unk0 = 0;
//     arg0->u4.w.unk0 = 0;
//     arg0->u5.w.unk0 = 0;
//     arg0->u6.w.unk0 = 0;
//     arg0->u7.w.unk0 = 0;
//     arg0->u0.s.unk0 = 1;
//     arg0->u1.s.unk2 = 1;
//     arg0->u2.s.unk4 = 1;
//     arg0->u3.s.unk6 = 1;
//
// }
