#include <ultra64.h>
#include "functions.h"
#include "variables.h"


typedef struct {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
} Vec150B06B0;

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ Vec150B06B0 unk08;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
} Burst150B06B0;

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ Vec150B06B0 unk08;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 unk32;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ s16 unk36;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ s8  unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ s16 unk44;
    /* 0x46 */ s16 unk46;
    /* 0x48 */ s32 unk48;
} Spray150B06B0;

extern s32 D_8009F810;
extern f32 D_8009F814;
extern s32 D_8009F818;
extern f32 D_8009F81C;
extern f32 D_8009F820;
extern f32 D_8009F824;
extern f32 D_8009F828;
extern f32 D_8009F82C;
extern f32 D_8009F830;
extern f32 D_8009F834;
extern f32 D_8009F838;
extern f32 D_8009F83C;
extern f32 D_8009F840;
extern f32 D_8009F844;
extern f32 D_8009F848;
extern f32 D_8009F84C;
extern f32 D_8009F850;
extern f32 D_8009F854;
extern f32 D_8009F858;
extern f32 D_8009F85C;

extern s32 func_15143E24(struct127 *);
extern void func_1504715C(f32 *, struct127 *);
extern void func_151C329C(Vec150B06B0 *, u8, s32);
extern void func_15152190(Burst150B06B0 *, s32 *, f32 *, s32, f32, s32, s32, s32);
extern void func_15153F18(Spray150B06B0 *, Vec150B06B0 *, f32 *, u8, s32);

void func_150B06B0(struct127 *arg0, struct127 *arg1, u8 arg2, s32 arg3) {
    Vec150B06B0 sp134;
    s8 sp133;
    f32 sp10C[9];
    Vec150B06B0 sp100;
    Burst150B06B0 spC4;
    Burst150B06B0 sp88;
    Spray150B06B0 sp3C;

    sp134.unk00 = arg0->x_position;
    sp134.unk04 = arg0->y_position;
    sp134.unk08 = arg0->z_position;
    sp133 = func_15143E24(arg1) + 0x40;
    func_1504715C(sp10C, arg0);

    if (arg0->id == 0xA6) {
        sp100.unk00 = sp134.unk00;
        sp100.unk04 = sp134.unk04 + 50.0f;
        sp100.unk08 = sp134.unk08;
        func_151C329C(&sp100, arg2, arg3);

        spC4.unk00 = 0xA;
        spC4.unk04 = 0xA;
        spC4.unk08 = sp134;
        spC4.unk14 = sp133 - 0x28;
        spC4.unk16 = 0x50;
        spC4.unk18 = -0x2D;
        spC4.unk1A = 0x1A;
        spC4.unk1C = 7.0f;
        spC4.unk20 = 17.0f;
        spC4.unk24 = D_8009F820;
        spC4.unk28 = D_8009F824;
        spC4.unk2C = 0x19;
        spC4.unk2E = 0x19;
        spC4.unk30 = D_8009F828;
        spC4.unk34 = D_8009F82C;
        spC4.unk38 = D_8009F830;
        func_15152190(&spC4, &D_8009F810, &D_8009F814, 1, 0.0f, 0, arg2, arg3);
    } else {
        sp88.unk00 = 0xA;
        sp88.unk04 = 0xA;
        sp88.unk08 = sp134;
        sp88.unk14 = sp133 - 0x28;
        sp88.unk16 = 0x50;
        sp88.unk18 = -0x15;
        sp88.unk1A = 0xD;
        sp88.unk1C = 7.0f;
        sp88.unk20 = 17.0f;
        sp88.unk24 = D_8009F834;
        sp88.unk28 = D_8009F838;
        sp88.unk2C = 0x19;
        sp88.unk2E = 0x19;
        sp88.unk30 = D_8009F83C;
        sp88.unk34 = D_8009F840;
        sp88.unk38 = D_8009F844;
        func_15152190(&sp88, &D_8009F818, &D_8009F81C, 1, 0.0f, 0, arg2, arg3);

        sp3C.unk08 = sp134;
        sp3C.unk14 = D_8009F848;
        sp3C.unk18 = D_8009F84C;
        sp3C.unk1C = D_8009F850;
        sp3C.unk20 = D_8009F854;
        sp3C.unk24 = D_8009F858;
        sp3C.unk28 = D_8009F85C;
        sp3C.unk2C = 7;
        sp3C.unk2E = 3;
        sp3C.unk00 = sp133 - 0x3C;
        sp3C.unk02 = 0x78;
        sp3C.unk04 = -0x1E;
        sp3C.unk06 = 0x10;
        sp3C.unk30 = 3; sp3C.unk32 = 2;
        sp3C.unk36 = sp3C.unk34 = 0x14;
        sp3C.unk38 = 0x9B;
        sp3C.unk3A = 0x64; sp3C.unk44 = 0x10;
        sp3C.unk46 = 0xF;
        sp3C.unk48 = 0;
        sp3C.unk40 = 0.5f;
        sp3C.unk3C = 0;
        func_15153F18(&sp3C, &sp3C.unk08, sp10C, arg2, arg3);
        sp3C.unk3C = 1;
        func_15153F18(&sp3C, &sp3C.unk08, sp10C, arg2, arg3);
    }
}

extern f32 D_8009F870;

void func_150B0A60(s32 *arg0, s32 *arg1, f32 *arg2, f32 *arg3, f32 *arg4, s16 *arg5) {
    f32 r1;
    f32 v;
    f32 ang;

    *arg5 = (s16)(*(f32 *)((s32)arg0 + 0x40) * D_8009F870 - 128.0f);
    r1 = func_150ADA68() * 248.0f;
    v = func_150ADA68() + -0.5f;
    if (r1 < 122.0f) {
        arg4[0] = arg2[0] * -31.5f + (arg3[0] * v) * 122.0f;
        arg4[1] = 0.0f;
        arg4[2] = arg2[1] * -31.5f + (arg3[1] * v) * 122.0f;
    } else {
        f32 k = 63.0f;
        ang = 61.0f;
        r1 = r1 - 122.0f;
        if (r1 < k) {
            ang = -ang;
            *arg5 += 0x40;
        } else {
            *arg5 -= 0x40;
        }
        arg4[0] = arg2[0] * k * v + arg3[0] * ang;
        arg4[1] = 0.0f;
        arg4[2] = arg2[1] * k * v + arg3[1] * ang;
    }
    arg4[0] += *(f32 *)((s32)arg0 + 0x14);
    arg4[1] += *(f32 *)((s32)arg1 + 0x118);
    arg4[2] += *(f32 *)((s32)arg0 + 0x1C);
}

void func_150B0C58(void *, u8, s32);

s32 func_150B0C34(s32 arg0) {
    func_150B0C58((void *)arg0, 0xFF, 1);
}

void func_150B0C58(void *arg0, u8 arg1, s32 arg2) {
    struct {
        void *unk0;
        u8 unk4;
        u8 pad5;
        u8 pad6;
        u8 pad7;
        f32 unk8;
    } sp34;
    struct260 *temp_v0;

    sp34.unk0 = arg0;
    sp34.unk4 = *(u8 *)((s32)arg0 + 0x3B);
    sp34.unk8 = 0.0f;

    temp_v0 = func_15149130(0x12C, -1, 0x58, -1, 0, 0x43, (struct37 *)0xC, arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy((void *)((s32)temp_v0 + 0x28), &sp34, 0xC);
    }
}

void func_150B0CE0(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_DDB60/func_150B0D20.s")
