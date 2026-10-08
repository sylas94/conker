#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_15142314(s32, s32, s32);

typedef struct {
    char pad_0[0x1D4];
    s32 field_0x1D4;
} ActorFields;

s32 func_150C19C0(s32 arg0, ActorFields *arg1, u8 arg2) {
    s32 sp1C;

    switch (arg2) {
    case 1:
        sp1C = 0x18;
        break;
    case 2:
        sp1C = 0x15;
        break;
    }

    func_15142314(arg1->field_0x1D4, sp1C, arg0);
    return 1;
}

s32 func_150C1A2C(s32 arg0, s32 arg1) {
    return 0x7;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_EEE70/func_150C1A40.s")

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    char padC[0xA];
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    s16 unk24;
    s16 unk26;
    u8 unk28;
    u8 unk29;
    u8 unk2A;
    u8 unk2B;
    u8 unk2C;
    u8 unk2D;
    u8 unk2E;
    u8 unk2F;
    u8 unk30;
    u8 unk31;
} Struct150C1E34Stack;

extern f64 D_800A0228;
extern void func_151429E0(u8, u8 *, u8 *, u8 *);
extern void func_1518CA80(void *, u8);

s32 func_150C1E34(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7,
                  s32 arg8, s32 arg9, s32 argA, s32 argB, f32 argC) {
    Struct150C1E34Stack sp1C;

    sp1C.unk0 = arg2;
    sp1C.unk4 = arg3;
    sp1C.unk8 = arg4;
    sp1C.unk1E = (arg2 - arg5) * 10.0f;
    sp1C.unk20 = (arg4 - arg7) * 10.0f;
    sp1C.unk16 = sp1C.unk18 = argC;
    sp1C.unk1C = sp1C.unk1A = argC * D_800A0228;
    sp1C.unk22 = 150;
    sp1C.unk24 = 20;
    sp1C.unk26 = 600;
    func_151429E0(0, &sp1C.unk28, &sp1C.unk29, &sp1C.unk2A);
    func_151429E0(0, &sp1C.unk2B, &sp1C.unk2C, &sp1C.unk2D);
    sp1C.unk2E = 0xFF;
    sp1C.unk2F = 0xFF;
    sp1C.unk30 = (func_150ADA20() % 16U) + 12;
    sp1C.unk31 = 1;
    func_1518CA80(&sp1C, 1);
    return 1;
}
