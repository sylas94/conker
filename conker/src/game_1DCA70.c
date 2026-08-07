#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_800AA0F0[];
extern f32 D_800AA0FC[];
extern f32 D_800AA110;
extern f32 D_800AA114;
extern f32 D_800AA118;
extern f32 D_800AA11C;

void func_15143134(f32 *, f32 *, s32);
void func_1504715C(s32, s32);
s32 func_15046C80(f32 *, s32, f32, s32);
void func_15143794(s32, s32, f32, f32 *);
struct260 *func_15130374(void *, u8, s32, u8, s32);

typedef struct {
    s16 unk0;
    f32 unk4;
} AFC08Sub;

typedef struct {
    char pad0[0x1C];
    s16 unk1C;
    char pad1E[0x2C - 0x1E];
    f32 unk2C;
    f32 unk30;
    char pad34[0x58 - 0x34];
    s32 unk58;
    u8 unk5C;
    char pad5D[0x128 - 0x5D];
    AFC08Sub unk128;
} AFC08Struct;

typedef struct {
    char pad_0[0x1D4];
    s32 field_0x1D4;
} ActorFields;

s32 func_151AF5C0(f32 *arg0, ActorFields *arg1, s32 arg2, u8 arg3) {
    f32 sp2C[3];
    f32 *temp_a0;
    s32 temp_a2;

    if ((arg3 != 1) && (arg3 != 2)) {
        return 0;
    }

    if (arg3 == 1) {
        temp_a0 = D_800AA0FC;
    } else {
        temp_a0 = D_800AA0F0;
    }

    if (arg3 == 1) {
        temp_a2 = arg1->field_0x1D4 + 0x800;
    } else {
        temp_a2 = arg1->field_0x1D4 + 0x640;
    }

    func_15143134(temp_a0, arg0, temp_a2);
    if (arg2 == 0) {
        return 1;
    }

    sp2C[0] = arg0[0];
    sp2C[1] = arg0[1] + 100.0f;
    sp2C[2] = arg0[2];
    func_1504715C(arg2, (s32) arg1);
    return func_15046C80(sp2C, 0, arg0[1] - 500.0f, arg2);
}

s32 func_151AF6C0(s32 arg0, s32 arg1) {
    return 0xC;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1DCA70/func_151AF6D4.s")

s32 func_151AFBD4(void *arg0) {
    s32 v0 = *(s16 *)((u8 *)arg0 + 0x1C);
    s32 v1;
    if (v0 < 0x20) {
        v1 = v0 * 8;
        if (v1 < *(u8 *)((u8 *)arg0 + 0x28)) {
            *(u8 *)((u8 *)arg0 + 0x28) = v1;
        }
    }
    return 1;
}

s32 func_151AFC08(AFC08Struct *arg0) {
    AFC08Sub *sub;

    if (arg0->unk58 & 1) {
        sub = &arg0->unk128;
        if (arg0->unk1C < 0x20) {
            if ((arg0->unk1C << 3) < arg0->unk5C) {
                *(u8*)((u8*)sub - 0xCC) = arg0->unk1C << 3;
            }
        }
        if (sub->unk0 < arg0->unk1C) {
            f32 v = sub->unk4 * D_800BE9A4;
            arg0->unk2C = arg0->unk2C + v;
            arg0->unk30 = arg0->unk30 + v;
        }
    }
    return 1;
}

s32 func_151AFC88(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5,
                  s32 arg6, s32 arg7, s16 arg8, s32 arg9, s32 arg10, s32 arg11,
                  s32 arg12, s32 arg13, u8 arg14) {
    struct260 *ret;
    struct {
        u8 pad24[8];
        f32 sp2C;
        u8 pad30[4];
        struct {
            s32 unk00;
            s32 unk04;
            s16 unk08;
            s16 unk0A;
            s32 unk0C;
            s32 unk10;
            u8 unk14;
            u8 unk15;
            u8 unk16;
            u8 unk17;
            u8 unk18;
            u8 unk19;
            u8 unk1A;
            u8 unk1B;
            u8 unk1C;
            u8 unk1D;
            s16 unk1E;
            s16 unk20;
            s16 unk22;
            f32 unk24;
            f32 unk28;
            f32 unk2C;
            f32 unk30;
            f32 unk34;
            f32 unk38;
            u8 pad3C[0xC];
            f32 unk48;
            f32 unk4C;
            f32 unk50;
            f32 unk54;
            s32 unk58;
            u8 pad5C[4];
            u8 unk60;
            u8 unk61;
            u8 unk62;
            s8 unk63;
        } sp34;
        u8 pad98[0xC];
    } stack;

    stack.sp34.unk1D = 0x29;
    stack.sp34.unk08 = 0xE03;
    stack.sp34.unk00 = 0x200005;
    stack.sp34.unk04 = 0;
    stack.sp34.unk0A = (func_150ADA20() & 0xF) + 0x19;
    stack.sp34.unk0C = 0;
    stack.sp34.unk10 = 0;
    stack.sp34.unk18 = 0xB0;
    stack.sp34.unk19 = 0xA0;
    stack.sp34.unk1A = 0x2A;
    stack.sp34.unk14 = 0x40;
    stack.sp34.unk15 = 0xB;
    stack.sp34.unk16 = 0x6A;
    stack.sp34.unk17 = 0xFF;
    stack.sp34.unk1B = (func_150ADA20() % 0x9CU) + 0x64;
    stack.sp34.unk1C = 0xFF;
    stack.sp34.unk60 = 3;
    stack.sp34.unk61 = 3;
    stack.sp34.unk28 = stack.sp34.unk2C = (func_150ADA68() * 202.0f) + 101.0f;
    stack.sp34.unk30 = arg2;
    stack.sp34.unk34 = arg3;
    stack.sp34.unk38 = arg4;

    ((s32 *)&stack.sp2C)[-2] = func_150ADA20();
    func_15143794(arg8, (s16)((((s32 *)&stack.sp2C)[-2] % 0x15U) - 0x14),
                  (func_150ADA68() * D_800AA110 + 500.0f) * D_800AA114,
                  &stack.sp34.unk48);

    stack.sp34.unk58 = 0xE05;
    stack.sp34.unk54 = 0.0f;

    if (func_150ADA20() & 1) {
        stack.sp34.unk58 |= 0x40;
    }

    if (func_150ADA20() & 1) {
        stack.sp34.unk58 |= 0x80;
    }

    stack.sp34.unk62 = 6;
    stack.sp34.unk24 = D_800AA118;
    stack.sp2C = D_800AA11C;
    stack.sp34.unk63 = -1;
    stack.sp34.unk1E = 0xF;
    stack.sp34.unk20 = 0x11;
    stack.sp34.unk22 = 0x19;

    ret = func_15130374(&stack.sp34, 1, 4, arg14, 1);
    if (ret != 0) {
        memcpy((u8 *)ret + 0xA8, &stack.sp2C, 4);
    }
    return 1;
}

s32 func_151AFEA4(f32 *arg0, s32 arg1) {
    volatile f32 *scale;
    s32 i;

    scale = (f32 *)((u8 *)arg0 + 0xA8);
    for (i = D_800BE9E4; i != 0; i--) {
        arg0[22] *= *scale;
        arg0[24] *= *scale;
    }
    return 1;
}
