#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    /* 0x0 */ s32 unk0;
} Struct150C04C0Word;

typedef struct {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
} Vec3F150C04C0;

typedef struct {
    /* 0x0 */ f32 unk0;
    /* 0x4 */ Struct150C04C0Word unk4;
    /* 0x8 */ s32 unk8;
} Struct150C04C0Sub;

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ Vec3F150C04C0 unk08;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ void *unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ void *unk48;
    /* 0x4C */ void *unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ u8 unk58;
    /* 0x59 */ u8 unk59;
    /* 0x5A */ u8 pad5A[2];
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ void *unk60;
} Struct150C04C0;

typedef struct {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ s16 unk6;
} Struct150C04C0Color;

typedef struct {
    char pad_0[0x14];
    s16 field_0x14;
    s16 field_0x16;
    char pad_0x18[0x7];
    u8 field_0x1F;
    char pad_0x20[0x4];
    u8 field_0x24;
    char pad_0x25[0x1];
    u8 field_0x26;
    u8 field_0x27;
    char pad_0x28[0x4];
    u8 field_0x2C;
    s8 field_0x2D;
    s8 field_0x2E;
    u8 field_0x2F;
} Struct150BF0F4;

extern Struct150C04C0Word D_800A0108;
extern f32 D_800A0170;
extern f32 D_800A0174;
extern f32 D_800A0178;
extern f32 D_800A017C;
extern f32 D_800A0180;
extern f32 D_800A0184;
extern f32 D_800A0188;
extern f32 D_800A018C;
extern f32 D_800A0190;
extern void func_15150400(Struct150C04C0 *, Struct150C04C0Color *, u8, s32);

void func_150BEF70(s32 arg0) {
}

extern void func_1516D99C();

void func_150BEF7C(s32 arg0) {
    s32 i;
    s32 pos;
    s32 v;
    v = arg0 & 0xFFFF;
    pos = 0x17C;
    for (i = 0; i != 2; i++) {
        func_1516D99C(0x1FDB, 0x25, (s16)pos, 0xD,
            0, 0x50, 0x8F, 0, 0, 0, 0, 0,
            8, 0xC8, 0xA, 0, 0, 0, 0, 0,
            0x28, 0x28, 4, 0, 0, 0, 0, 0x555,
            0x555, 0x555, 0x555, v, 0x32, 0, 0xFF, 0x14,
            0xFA0, 0x7D0, 1, 6, 0, 1, 0, 0,
            0, 0, 3, 0xFF, 0);
        pos = -pos;
    }
}

s32 func_150BF0F4(Struct150BF0F4 *arg0) {
    s32 temp_v0;
    s32 temp_v1;
    s32 temp_a1;

    temp_v0 = arg0->field_0x1F;
    temp_v1 = arg0->field_0x26;
    temp_a1 = arg0->field_0x24;
    if (temp_a1 != 0) {
        if (temp_v0 != temp_v1) {
            temp_v0 += D_800BE9E4 * arg0->field_0x27;
            if (temp_v1 < temp_v0) {
                temp_v0 = temp_v1;
            }
            arg0->field_0x1F = temp_v0;
            temp_a1 = ((volatile Struct150BF0F4 *)arg0)->field_0x24;
        }
    } else {
        if (temp_v0 != 0) {
            temp_v0 -= D_800BE9E4 * arg0->field_0x2F;
            if (temp_v0 < 0) {
                temp_v0 = 0;
            }
            arg0->field_0x1F = temp_v0;
            temp_a1 = ((volatile Struct150BF0F4 *)arg0)->field_0x24;
        }
    }

    if ((temp_a1 == 0) && (temp_v0 == 0)) {
        return 1;
    }

    temp_v0 = arg0->field_0x2D;
    temp_v0 *= D_800BE9E4;
    arg0->field_0x14 = arg0->field_0x14 + temp_v0;
    temp_v1 = arg0->field_0x14;
    temp_v0 = arg0->field_0x2E;
    temp_v0 *= D_800BE9E4;
    arg0->field_0x16 = arg0->field_0x16 + temp_v0;
    if ((temp_v1 <= 0) || (temp_v1 <= 0)) {
        arg0->field_0x16 = 0;
        arg0->field_0x14 = arg0->field_0x16;
        return 1;
    }

    temp_v1 = arg0->field_0x2C;
    temp_v1 += D_800BE9E4;
    if (temp_v1 >= 0x80) {
        temp_v1 = 0x7F;
    }
    arg0->field_0x2C = temp_v1;
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_EC420/func_150BF21C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_EC420/func_150BF760.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_EC420/func_150BFA7C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_EC420/func_150BFFE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_EC420/func_150C01DC.s")

void func_150C04C0(Vec3F150C04C0 *arg0, void *arg1, s32 arg2, u8 arg3, u8 arg4, s32 arg5) {
    Struct150C04C0 sp34;
    Struct150C04C0Color sp2C;
    Struct150C04C0Sub sp20;
    u8 temp_v0;

    sp20.unk4 = D_800A0108;
    sp20.unk8 = arg2;
    sp34.unk00 = 9;
    sp34.unk04 = 4;
    sp20.unk0 = D_800A0170;
    sp34.unk08 = *arg0;
    sp34.unk14 = 4.0f;
    sp34.unk18 = 7.0f;
    sp34.unk1C = D_800A0174;
    sp34.unk20 = D_800A0178;
    sp34.unk28 = D_800A017C;
    sp34.unk2C = D_800A0180;
    sp34.unk24 = 0x50;
    sp34.unk26 = 0x3C;
    sp34.unk34 = arg1;
    sp34.unk48 = &sp20.unk8;
    sp34.unk4C = &sp20.unk4;
    sp34.unk50 = 1;
    sp34.unk30 = D_800A0184;
    sp34.unk38 = D_800A0188;
    sp34.unk3C = D_800A018C;
    sp34.unk40 = D_800A0190;
    sp34.unk44 = 10.0f;
    sp34.unk54 = 78.0f;
    if (arg3 != 0) {
        temp_v0 = 1;
    } else {
        temp_v0 = 0;
    }
    sp34.unk58 = temp_v0;
    sp34.unk59 = 0xE;
    sp34.unk5C = 4;
    sp34.unk60 = &sp20.unk0;
    sp2C.unk0 = 0;
    sp2C.unk2 = 0xFF;
    sp2C.unk4 = -0x32;
    sp2C.unk6 = 0x23;
    func_15150400(&sp34, &sp2C, arg4, arg5);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_EC420/func_150C0648.s")
