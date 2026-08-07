#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_150A7960(f32 *, f32, f32, f32, f32 *, f32 *, f32 *);

void func_150D82B0(s32 arg0) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_105760/func_150D82BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_105760/func_150D83D8.s")

s16 *func_150D8590(s16 *arg0, s32 arg1) {
    arg0[0] = 0x42;
    arg0[1] = 0;
    return arg0 + 2;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_105760/func_150D85AC.s")

struct S150D88AC {
    u8 pad0[0x14];
    u8 *unk14;
    u8 *unk18;
};

s32 func_150D88AC(struct S150D88AC *arg0) {
    if (arg0->unk18[0x6F] != 0) {
        arg0->unk14[0x9] = 0;
    } else {
        arg0->unk14[0x9] = 1;
    }
    return 1;
}

s32 func_150D88E0(void *arg0, struct127 *arg1, u8 arg2) {
    struct {
        f32 z;
        f32 y;
        f32 x;
        s32 temp_a1;
    } sp30;

    switch (arg2) {
    case 3:
        sp30.temp_a1 = 0x12;
        sp30.x = -7.0f;
        sp30.z = 30.0f;
        break;
    case 4:
        sp30.temp_a1 = 0x15;
        sp30.x = -4.0f;
        sp30.z = 35.0f;
        break;
    case 5:
        sp30.temp_a1 = 0xF;
        sp30.x = 5.0f;
        sp30.z = 20.0f;
        break;
    case 6:
        sp30.temp_a1 = 0x18;
        sp30.x = 5.0f;
        sp30.z = 31.0f;
        break;
    }

    sp30.y = 0.0f;
    func_150A7960((f32 *)((u8 *)arg1->unk1D4 + (sp30.temp_a1 << 6)), sp30.x, sp30.y, sp30.z, &sp30.x, &sp30.y, &sp30.z);
    ((f32 *)arg0)[0] = sp30.x;
    ((f32 *)arg0)[1] = sp30.y;
    ((f32 *)arg0)[2] = sp30.z;
    return 1;
}

s32 func_150D8A20(s32 arg0, s32 arg1) {
    return 0x8;
}

extern f32 D_800A0B30;
extern f32 D_800A0B34;
s32 func_150D88E0(void *, struct127 *, u8);
void func_151875E0(f32, f32, f32, s32, s32, s32, f32, f32);
void func_15165F80(s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_150D8A34(struct127 *arg0, s32 arg1, s32 arg2) {
    struct { f32 x; f32 y; f32 z; } sp34;

    if (arg0->unk1D4 != NULL) {
        func_150D88E0(&sp34, arg0, (u8)arg1);
        func_151875E0(sp34.x, sp34.y, sp34.z, 0x1E, 0xF, 0x7, D_800A0B30, D_800A0B34);
        func_15165F80(-1, (s32)sp34.x, (s32)(arg0->unk180 + 4.0f), (s32)sp34.z, 4, 0x32, 0, 0xFF, 0);
    }
}
