#include <ultra64.h>
#include "functions.h"
#include "variables.h"

struct Vec3F1518A3C0 {
    f32 x;
    f32 y;
    f32 z;
};

extern s32 D_8008D5B0[];
extern s32 D_8008D5B8[];
extern void *func_151580B0(void *, s32, s32, u8, s32, u8, s32);

void *func_1518A3C0(struct Vec3F1518A3C0 *arg0, struct Vec3F1518A3C0 *arg1, f32 arg2, struct Vec3F1518A3C0 *arg3, struct Vec3F1518A3C0 *arg4, f32 arg5, f32 arg6, u8 arg7, s16 arg8, u8 arg9, s32 argA, u8 argB, s32 argC) {
    void *ret;
    struct {
        u8 unk00[1];
        u8 unk01[1];
        u8 unk02[1];
        u8 unk03[1];
        s16 unk04;
        u8 unk06;
        u8 pad07;
        s32 unk08;
        s32 unk0C;
        s32 unk10;
        s32 unk14;
        s32 unk18;
        s32 unk1C;
        s32 unk20;
        u8 unk24;
        u8 unk25;
        u8 pad26[2];
        u8 unk28;
        u8 unk29;
        u8 unk2A;
        u8 unk2B;
        u8 unk2C;
        u8 unk2D;
        u8 unk2E;
        u8 unk2F;
        s32 unk30;
        u8 unk34;
        u8 unk35;
        u8 pad36[2];
        struct Vec3F1518A3C0 unk38;
    } sp68;
    struct {
        struct Vec3F1518A3C0 unk00;
        f32 unk0C;
        struct Vec3F1518A3C0 unk10;
        struct Vec3F1518A3C0 unk1C;
        f32 unk28;
        f32 unk2C;
    } sp38;
    struct {
        s16 unk00;
        u8 pad02[2];
        s32 unk04;
    } sp30;

    sp38.unk00 = *arg1;
    sp38.unk10 = *arg3;
    sp38.unk1C = *arg4;
    sp38.unk0C = arg2;
    sp38.unk28 = arg5;
    sp38.unk2C = arg6;
    sp68.unk00[0] = arg7;
    sp68.unk02[0] = 1;
    sp68.unk03[0] = 1;
    sp68.unk04 = arg8;

    if (arg9) {
        sp68.unk06 = D_8008D5B8[func_150ADA20() & 1];
    } else {
        sp68.unk06 = D_8008D5B0[func_150ADA20() & 1];
    }

    sp68.unk0C = 0x220205;
    sp68.unk10 = 0x40600;
    sp68.unk25 = 7;
    sp68.unk14 = 1;
    sp68.unk18 = 0x4A;
    sp68.unk1C = 0x80;
    sp68.unk20 = 0x20;
    sp68.unk08 = 0;
    sp68.unk24 = 0;
    sp68.unk01[0] = 1;
    sp68.unk28 = 0xFF;
    sp68.unk29 = 0xFF;
    sp68.unk2A = 0xFF;
    sp68.unk2B = 0xFF;
    sp68.unk2C = 0xFF;
    sp68.unk2D = 0xFF;
    sp68.unk2E = 0xFF;
    sp68.unk2F = 0xFF;
    sp68.unk30 = 0;
    sp68.unk34 = 0;
    sp68.unk35 = 2;
    sp68.unk38 = *arg0;

    sp30.unk00 = 0xC;
    sp30.unk04 = 0x15;

    ret = func_151580B0(&sp68, 3, 0xFF, 1, argA + 0x38, argB, argC);
    if (ret == 0) {
        return 0;
    }
    memcpy((u8 *)ret + 0xF8, &sp30, 8);
    memcpy((u8 *)ret + 0x100, &sp38, 0x30);
    return ret;
}

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} MotionVec1518A5F4;

typedef struct {
    /* 0x00 */ MotionVec1518A5F4 rot;
    /* 0x0C */ f32 scale;
    /* 0x10 */ MotionVec1518A5F4 vel;
    /* 0x1C */ MotionVec1518A5F4 rotVel;
    /* 0x28 */ f32 gravity;
    /* 0x2C */ f32 drag;
} MotionState1518A5F4;

typedef struct {
    u8 pad_0x0[0x48];
    /* 0x48 */ f32 posX;
    /* 0x4C */ f32 posY;
    /* 0x50 */ f32 posZ;
    u8 pad_0x54[0x100 - 0x54];
    /* 0x100 */ MotionState1518A5F4 motion;
} struct1518A5F4;

s32 func_15158AFC(struct1518A5F4 *);

s32 func_1518A5F4(struct1518A5F4 *arg0) {
    MotionState1518A5F4 *p;
    MotionVec1518A5F4 oldVel;
    f32 accelX;
    f32 accelY;
    f32 accelZ;
    s32 i;

    p = &arg0->motion;
    func_15158AFC(arg0);
    oldVel = p->vel;
    p->vel.y += p->gravity * D_800BE9A4;
    for (i = D_800BE9E4; i != 0; i--) {
        p->vel.x *= p->drag;
        p->vel.y *= p->drag;
        p->vel.z *= p->drag;
    }
    accelX = (p->vel.x - oldVel.x) * D_800BE9A8;
    accelY = (p->vel.y - oldVel.y) * D_800BE9A8;
    accelZ = (p->vel.z - oldVel.z) * D_800BE9A8;
    arg0->posX += (oldVel.x + 0.5f * accelX * D_800BE9A4) * D_800BE9A4;
    arg0->posY += (oldVel.y + 0.5f * accelY * D_800BE9A4) * D_800BE9A4;
    arg0->posZ += (oldVel.z + 0.5f * accelZ * D_800BE9A4) * D_800BE9A4;
    p->rot.x += p->rotVel.x * D_800BE9A4;
    p->rot.y += p->rotVel.y * D_800BE9A4;
    p->rot.z += p->rotVel.z * D_800BE9A4;
    return 1;
}

struct Sub1518A914 {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
};

struct Foo1518A914 {
    char pad0[0x48];
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
    char pad54[0x100 - 0x54];
    /* 0x100 */ struct Sub1518A914 unk100;
};

s32 func_1518A914(Mtx *arg0, struct Foo1518A914 *arg1) {
    struct Sub1518A914 *p = &arg1->unk100;
    f32 sp24[4][4];

    func_150A8050(sp24, p->unk0, p->unk4, p->unk8);
    sp24[3][0] = arg1->unk48;
    sp24[3][1] = arg1->unk4C;
    sp24[3][2] = arg1->unk50;
    sp24[0][0] *= p->unkC;
    sp24[0][1] *= p->unkC;
    sp24[0][2] *= p->unkC;
    sp24[1][0] *= p->unkC;
    sp24[1][1] *= p->unkC;
    sp24[1][2] *= p->unkC;
    sp24[2][0] *= p->unkC;
    sp24[2][1] *= p->unkC;
    sp24[2][2] *= p->unkC;
    guMtxF2L(sp24, arg0);
    return 1;
}
