#include <ultra64.h>
#define func_15048A40 func_15048A40_hdr
#define func_150ADA20 func_150ADA20_hdr
#include "functions.h"
#undef func_15048A40
#undef func_150ADA20
#include "variables.h"

extern f32 func_15048A40(u8 arg0);
extern f32 func_150489B0(u8 arg0);
extern s32 func_150ADA20(void);
extern f32 D_800AA584;
extern f32 D_800AA588;
extern f32 D_800AA58C;
extern void func_15171D4C(f32, f32, f32, s32, s32, s32, f32, s32, s32, s32, s32, s32, s32, s32);

typedef struct {
    /* 0x00 */ u8  unk0;
    /* 0x01 */ u8  unk1;
    /* 0x02 */ u8  pad2[0xA];
    /* 0x0C */ u8  unkC;
    /* 0x0D */ u8  padD[0x7];
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ u8  pad1C[0x4];
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ u8  pad26[0x4];
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ u8  pad2C[0x4];
    /* 0x30 */ s16 unk30;
    /* 0x32 */ u8  pad32[0x2];
    /* 0x34 */ s16 unk34;
    /* 0x36 */ s16 unk36;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ u8  pad3A[0x1];
    /* 0x3B */ u8  unk3B;
    /* 0x3C */ u8  pad3C[0x3];
    /* 0x3F */ u8  unk3F;
} struct_151B9964;

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E6B40/func_151B9690.s")

void func_151B9964(struct_151B9964 *arg0) {
    s32 value;
    s32 height;
    f32 wave;
    f32 wave2;
    f32 amount;
    s16 current;
    s32 delta;
    s32 mode;
    u8 angle;

    mode = arg0->unk18;
    if (mode == 1) {
        angle = arg0->unk3B + D_800BE9E4 * 4 + D_800BE9E4 * 2;
        arg0->unk3B = angle;
        arg0->unk2A = arg0->unk2A * D_800AA584;
        amount = arg0->unk2A;
        wave = func_15048A40(angle);
        arg0->unk34 = (wave + 3.0f) * amount * D_800AA588;
        wave2 = func_150489B0(angle);
        arg0->unk36 = (wave2 + 3.0f) * amount * D_800AA58C;
    } else {
        value = arg0->unk14 >> 16;
        if (value != arg0->unk34) {
            height = arg0->unk34 - D_800BE9E4 * 4;
            if (height < value) {
                height = value;
            }
            arg0->unk36 = height;
            arg0->unk34 = height;
        }
    }

    current = arg0->unk14;
    if (current >= arg0->unk22) {
        arg0->unk38 = 0;
        if (mode == 0) {
            if ((u8)func_150ADA20() < 0x40) {
                func_15171D4C((f32)arg0->unk20, (f32)current, (f32)arg0->unk24, 0xA, 0,
                              0x13, 0.0f, 0, 0x32, 0xF, 0x100, 0, arg0->unkC, arg0->unk1);
            }
            if ((u8)func_150ADA20() < 0xF) {
                func_150ADA20();
                func_10010F88(0x70, 0x1388, 0, 0, 0, arg0->unk20, current, arg0->unk24,
                              0x1F4, 0x7D0);
            }
        }
    } else if (arg0->unk30 < 0) {
        delta = arg0->unk22 - current;
        if (delta < 0x40) {
            arg0->unk3F = delta * 4;
        }
    }
}

typedef struct {
    u8  unk0;
    u8  unk1;
    u8  pad2[0xA];
    u8  unkC;
    u8  padD[0x3];
    s32 unk10;
    u8  unk14;
    u8  unk15;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    s16 unk24;
    s16 unk26;
    s16 unk28;
    s16 unk2A;
} struct_151B9BF0;

s32 func_15167A68(s32, s32, s32, s32, s32, s32);
void func_151B9690(u8, u8, s16, s16, s16, s16, f32, s16, s16, s16, s16, s16, s16, s16, s16, u8, s32);

void func_151B9BF0(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5,
                   s16 arg6, s16 arg7, s16 arg8, s16 arg9, s16 arg10, s16 arg11,
                   s16 arg12, s32 arg13, u8 arg14, s32 arg15) {
    struct_151B9BF0 *ret;

    ret = (struct_151B9BF0 *)func_15167A68(7, arg15, 0x2C, 0, arg14, 1);
    if (ret != 0) {
        ret->unk14 = arg0;
        ret->unk15 = arg1;
        ret->unk16 = arg2;
        ret->unk18 = arg3;
        ret->unk1A = arg4;
        ret->unk1C = arg5;
        ret->unk1E = arg6;
        ret->unk20 = arg7;
        ret->unk22 = arg8;
        ret->unk24 = arg9;
        ret->unk26 = arg10;
        ret->unk28 = arg11;
        ret->unk2A = arg12;
        ret->unk10 = arg13;
    }
}

void func_151B9CB0(struct_151B9BF0 *arg0) {
    f32 *temp_v0;
    struct_151B9BF0 *temp_s5;
    s16 temp_s2;
    s16 temp_s3;
    s16 temp_s4;
    s32 i;
    f32 temp_f20;
    s32 temp_s5_2;
    s32 temp_s6;
    s32 temp_v0_2;

    temp_v0 = (f32 *)arg0->unk10;
    temp_s5 = arg0;
    if (temp_v0 == 0) {
        temp_s2 = arg0->unk16;
        temp_s3 = arg0->unk18;
        temp_s4 = arg0->unk1A;
    } else {
        temp_s2 = (s16)(s32)temp_v0[0];
        temp_s3 = (s16)(s32)temp_v0[1];
        temp_s4 = (s16)(s32)temp_v0[2];
    }

    i = 0;
    if (arg0->unk28 > 0) {
        temp_f20 = 0.0f;
        do {
            func_151B9690(arg0->unk14, arg0->unk15, temp_s2, temp_s3, temp_s4, -0x50,
                          temp_f20, 0x168, arg0->unk1C, arg0->unk1E, arg0->unk20,
                          arg0->unk22, 0xF, arg0->unk24, arg0->unk26, arg0->unkC,
                          arg0->unk1);
            i++;
        } while (i < temp_s5->unk28);
        i = 0;
    }
    temp_f20 = 0.0f;

    temp_s6 = 4;
    temp_s5_2 = 3;
    while (1) {
        func_151B9690(arg0->unk14, arg0->unk15, temp_s2, temp_s3, temp_s4, -0x50,
                      temp_f20, 0x168, (arg0->unk1C * temp_s5_2) / 2,
                      arg0->unk1E * 2, arg0->unk20, arg0->unk22, 0xF,
                      arg0->unk24, arg0->unk26, arg0->unkC, arg0->unk1);
        i++;
        if (i == temp_s6) {
            break;
        }
    }

    temp_v0_2 = arg0->unk2A;
    temp_v0_2 -= D_800BE9E4;
    if (temp_v0_2 < 0) {
        func_1516972C((struct102 *)arg0);
    } else {
        arg0->unk2A = temp_v0_2;
    }
}
