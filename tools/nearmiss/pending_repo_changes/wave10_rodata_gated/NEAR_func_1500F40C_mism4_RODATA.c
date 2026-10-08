#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern s32 func_151EF610(void);

struct LocalDef1500F290 {
    s32 unk0;
    s16 unk4;
    s8  unk6;
    s8  unk7;
    s32 unk8;
    s32 unkC;
    u8  unk10;
    u8  unk11;
    u8  unk12;
    u8  unk13;
    u8  unk14;
    u8  unk15;
    s8  unk16;
    s8  unk17;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
};

s32 *func_1500F290(f32 arg0, f32 arg1, f32 arg2) {
    struct LocalDef1500F290 tmp;
    s32 temp;

    tmp.unk6 = 0x38;
    tmp.unk8 = 0;
    temp = func_151EF610();
    tmp.unkC = (temp % 0x1000) + 0x4000;
    tmp.unk0 = 0x20014;
    tmp.unk4 = 1;
    tmp.unk10 = 0xFF;
    tmp.unk11 = 0xFF;
    tmp.unk12 = 0;
    tmp.unk13 = 0;
    tmp.unk14 = 0;
    tmp.unk15 = 0xFF;
    tmp.unk18 = 0x30001;
    return (s32 *)func_1513C5B0((s32)&tmp, 0, 0, 0, arg0, arg1, arg2, 110.0f, 110.0f, 0, 0, 0, 0xFF, 0);
}

typedef struct {
    u8  pad0[0x28];
    s16 unk28;
    s16 unk2A;
    s16 unk2C;
    s16 unk2E;
    s8  unk30;
} Struct1500F378;

s32 func_1500F378(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Struct1500F378 *temp;

    temp = (Struct1500F378 *)func_151491F4((s16)((func_150ADA20() & 0x7F) + 0xA), 1, -1, 1, 0, 0xA, 0xFF, 0);
    if (temp != 0) {
        temp->unk28 = arg0;
        temp->unk2A = arg1;
        temp->unk2C = arg2;
        temp->unk2E = arg3;
        temp->unk30 = 1;
    }
}

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ s16 unk44;
    /* 0x46 */ s16 unk46;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 unk4C;
} Struct1500F40C;

extern s32 *D_800D98D0[];
extern void func_15189900(Struct1500F40C *, s32);

void func_1500F40C(void) {
    Struct1500F40C sp28;

    func_1500F378(0x1612, -0x553, -0x2DC, -0x69F);
    func_1500F378(0x1633, -0x553, -0x3C2, -0x69F);
    D_800D98D0[0] = func_1500F290(4054.0f, -1692.0f, 0.0f);
    D_800D98D0[1] = func_1500F290(3890.0f, -1692.0f, -78.0f);
    D_800D98D0[2] = func_1500F290(4380.0f, -1692.0f, -664.0f);
    D_800D98D0[3] = func_1500F290(4218.0f, -1692.0f, -740.0f);
    sp28.unk28 = 0.0f;
    sp28.unk8 = 2686.0f;
    sp28.unk2C = 0.240000024f;
    sp28.unk48 = 3;
    sp28.unk4C = 2;
    sp28.unk2 = 0x12;
    sp28.unk30 = 2.0f;
    sp28.unk4 = -0x15;
    sp28.unk6 = 0xF;
    sp28.unk38 = 0x9B;
    sp28.unk34 = 6.0f;
    sp28.unk20 = 7.0f;
    sp28.unk3A = 0x64;
    sp28.unk10 = 2063.0f;
    sp28.unk24 = 10.0f;
    sp28.unk44 = 0x29;
    sp28.unk46 = 0x29;
    sp28.unk3C = 0.497000009f;
    sp28.unk40 = 0.315000027f;
    sp28.unkC = -1667.0f;
    sp28.unk14 = 2810.0f - sp28.unk8;
    sp28.unk18 = 0;
    sp28.unk1C = 1637.0f - sp28.unk10;
    sp28.unk0 = (s16)(func_150484A0(sp28.unk14, sp28.unk1C) * 40.7436638f) - 0x40;
    func_15189900(&sp28, 1);
    sp28.unkC = -1667.0f;
    sp28.unk8 = 2810.0f;
    sp28.unk10 = 1637.0f;
    sp28.unk14 = 2667.0f - sp28.unk8;
    sp28.unk18 = -1668.0f - sp28.unkC;
    sp28.unk1C = 1236.0f - sp28.unk10;
    sp28.unk0 = (s16)(func_150484A0(sp28.unk14, sp28.unk1C) * 40.7436638f) - 0x40;
    func_15189900(&sp28, 1);
    sp28.unk8 = 2667.0f;
    sp28.unkC = -1668.0f;
    sp28.unk10 = 1236.0f;
    sp28.unk14 = 2220.0f - sp28.unk8;
    sp28.unk18 = -1676.0f - sp28.unkC;
    sp28.unk1C = 1025.0f - sp28.unk10;
    sp28.unk0 = (s16)(func_150484A0(sp28.unk14, sp28.unk1C) * 40.7436638f) - 0x40;
    func_15189900(&sp28, 1);
    sp28.unk8 = 1894.0f;
    sp28.unkC = -1674.0f;
    sp28.unk10 = 788.0f;
    sp28.unk14 = 1841.0f - sp28.unk8;
    sp28.unk18 = -1677.0f - sp28.unkC;
    sp28.unk1C = 557.0f - sp28.unk10;
    sp28.unk0 = (s16)(func_150484A0(sp28.unk14, sp28.unk1C) * 40.7436638f) - 0x40;
    func_15189900(&sp28, 1);
    sp28.unk8 = 1841.0f;
    sp28.unkC = -1677.0f;
    sp28.unk10 = 557.0f;
    sp28.unk14 = 1594.0f - sp28.unk8;
    sp28.unk18 = -1678.0f - sp28.unkC;
    sp28.unk1C = 455.0f - sp28.unk10;
    sp28.unk0 = (s16)(func_150484A0(sp28.unk14, sp28.unk1C) * 40.7436638f) - 0x40;
    func_15189900(&sp28, 1);
    sp28.unk8 = 1594.0f;
    sp28.unk10 = 455.0f;
    sp28.unkC = -1678.0f;
    sp28.unk14 = 1400.0f - sp28.unk8;
    sp28.unk18 = 0.0f;
    sp28.unk1C = 613.0f - sp28.unk10;
    sp28.unk0 = (s16)(func_150484A0(sp28.unk14, sp28.unk1C) * 40.7436638f) - 0x40;
    func_15189900(&sp28, 1);
    sp28.unk8 = 1253.0f;
    sp28.unkC = -1673.0f;
    sp28.unk10 = 668.0f;
    sp28.unk14 = 1075.0f - sp28.unk8;
    sp28.unk18 = -1682.0f - sp28.unkC;
    sp28.unk1C = 572.0f - sp28.unk10;
    sp28.unk0 = (s16)(func_150484A0(sp28.unk14, sp28.unk1C) * 40.7436638f) - 0x40;
    func_15189900(&sp28, 1);
    sp28.unk8 = 1075.0f;
    sp28.unkC = -1682.0f;
    sp28.unk10 = 572.0f;
    sp28.unk14 = 872.0f - sp28.unk8;
    sp28.unk18 = -1680.0f - sp28.unkC;
    sp28.unk1C = 687.0f - sp28.unk10;
    sp28.unk0 = (s16)(func_150484A0(sp28.unk14, sp28.unk1C) * 40.7436638f) - 0x40;
    func_15189900(&sp28, 1);
    sp28.unk8 = 872.0f;
    sp28.unkC = -1680.0f;
    sp28.unk10 = 687.0f;
    sp28.unk14 = 772.0f - sp28.unk8;
    sp28.unk18 = -1676.0f - sp28.unkC;
    sp28.unk1C = 931.0f - sp28.unk10;
    sp28.unk0 = (s16)(func_150484A0(sp28.unk14, sp28.unk1C) * 40.7436638f) - 0x40;
    func_15189900(&sp28, 1);
}
