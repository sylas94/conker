#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 sinf(f32);

void func_150D278C(s32, void*, u8, u8);

struct Func150D317CSub {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    u8 pad20[0x8];
    f32 unk28;
    f32 unk2C;
};

struct Func150D317CObj {
    u8 pad0[0x5C];
    u8 unk5C;
    u8 pad5D[0xCB];
    f32 unk128;
    f32 unk12C;
    f32 unk130;
    f32 unk134;
};

struct S150D26F0 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u8 unk10;
};

void func_150D26F0(u8 *arg0) {
    struct S150D26F0 *v1 = (struct S150D26F0 *)(arg0 + 0x28);

    if (arg0[0x78] & 1) {
        v1->unkC = v1->unkC - D_800BE9E4;
        if (v1->unkC < 0) {
            func_150D278C(v1->unk0, &v1->unk10, arg0[0xC], arg0[1]);
            v1->unkC = func_150ADA20() % (u32)(v1->unk8 + 1) + v1->unk4;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_FFBA0/func_150D278C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_FFBA0/func_150D2924.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_FFBA0/func_150D2D6C.s")

s32 func_150D317C(struct Func150D317CObj *arg0) {
    struct Func150D317CSub *sub;

    arg0->unk128 += arg0->unk130 * D_800BE9A4;
    arg0->unk12C += arg0->unk134 * D_800BE9A4;
    sub = (struct Func150D317CSub *)((u8 *)arg0 + 0x110);
    sub->unk18 = func_15144B68(arg0->unk128);
    sub->unk1C = func_15144B68(sub->unk1C);
    sub->unk0 = (sinf(sub->unk18) * sub->unk10) + sub->unk8;
    sub->unk4 = (sinf(sub->unk1C) * sub->unk14) + sub->unkC;
    sub->unk28 -= D_800BE9A4;
    arg0->unk5C = sub->unk2C * sub->unk28;
    if (sub->unk28 > 0.0f) {
        return 1;
    }
    return 0;
}

void func_150D278C(s32, void*, u8, u8);

struct S150D32FC {
    s32 unk0;
    u8 pad4[0xC];
    u8 unk10;
    u8 pad11[0x40];
    u8 unk51;
};

void func_150D32FC(u8 *arg0, u8 *arg1, u8 arg2) {
    struct S150D32FC *v0 = (struct S150D32FC *)(arg0 + 0x28);

    if (arg2 == 0x34 && arg1[0] == ((u8*)v0)[0x51]) {
        func_150D278C(v0->unk0, &v0->unk10, arg0[0xC], arg0[1]);
    }
}
