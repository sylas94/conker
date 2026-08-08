#include <ultra64.h>
#include "functions.h"
#include "variables.h"

s32 func_1509BE40();
void func_1509BFB0(s32 num, s32, s32, ...);
void func_150495B0(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5);

extern f32 D_80088990[4];
extern f32 D_800889A0[4];
extern f32 D_800889B0[4];
extern s32 D_800889C0[4];
extern s32 D_800889D0[4];

void func_150E1860(struct108 *arg0) {
    s32 i;
    s32 flag;

    flag = 0;
    arg0->unk84 |= 0x10;
    for (i = 0; i < 4; i++) {
        if (func_1509BE40(1, D_800889C0[i], 6, 0x9000) != 0) {
            D_800889A0[i] = 192.0f;
            arg0->unk84 |= 0x80021010;
            flag = 1;
        } else {
            D_800889A0[i] = 255.0f;
        }
        func_150495B0(&D_80088990[i], D_800889A0[i], &D_800889B0[i], 4.0f, 6.0f, arg0->unk7B4);
        func_1509BFB0(1, D_800889D0[i], 0x12, (u8)D_80088990[i]);
    }
    if (flag == 0) {
        arg0->unk84 &= ~0x80021000;
    }
    if (func_1509BE40(1, 0x403D, 6, 0x2000) != 0) {
        arg0->unk84 &= ~0x80000000;
    } else {
        arg0->unk84 |= 0x80000000;
    }
}
