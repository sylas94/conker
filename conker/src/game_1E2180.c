#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern u8 D_800A3FE6[];

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u8  unk8;
    /* 0x09 */ u8  pad9[0x3];
    /* 0x0C */ struct102 *unkC;
    /* 0x10 */ u8  unk10;
    /* 0x11 */ u8  pad11[0x3];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ u8  unk2A;
    /* 0x2B */ u8  unk2B;
    /* 0x2C */ s8  unk2C;
    /* 0x2D */ u8  unk2D;
} struct_4FE0;

s32 func_15134070(struct102 *);
void func_1516962C(s32, struct102 *, s32);
void *func_1513418C(struct_4FE0 *, s32, u8, s32);

void *func_151B4CD0(struct102 *arg0, s32 arg1, s32 arg2) {
    void *result;
    struct_4FE0 sp24;
    u8 sp20[4];
    s32 temp_v0;

    if (arg0 == 0) {
        return 0;
    }

    temp_v0 = func_15134070(arg0);
    if (temp_v0 == 0x63) {
        return 0;
    }

    if (D_800A3FE6[temp_v0 << 4] == 2) {
        return 0;
    }

    func_1516962C(0x28, arg0, 0x16);

    sp24.unk0 = 0;
    sp24.unk4 = 0;
    sp24.unk8 = *((u8 *)arg0 + 0x3B);
    sp24.unkC = arg0;
    sp24.unk10 = 2;
    sp24.unk14 = 0.0f;
    sp24.unk18 = -27.0f;
    sp24.unk1C = 16.0f;
    sp24.unk20 = 15.0f;
    sp24.unk24 = 0.448f;
    sp24.unk2A = 6;
    sp24.unk28 = (func_150ADA20() % 0x15U) + 0x28;
    sp24.unk2B = 8;
    sp24.unk2C = -1;
    sp24.unk2D = 7;

    if (D_800A3FE6[temp_v0 << 4] == 1) {
        sp20[0] = 1;
    } else {
        sp20[0] = 0;
    }

    result = func_1513418C(&sp24, 1, (u8)arg1, arg2);
    if (result != 0) {
        memcpy((u8 *)result + 0x58, sp20, 1);
    }
    return result;
}

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3f_local_4E4C;

void func_151B4EA4(Vec3f_local_4E4C *, f32, f32, f32, u8, u8);

void func_151B4E4C(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, void *arg6) {
    Vec3f_local_4E4C sp24;

    sp24.x = arg0;
    sp24.y = arg1;
    sp24.z = arg2;
    func_151B4EA4(&sp24, arg3, arg4, arg5, *(u8 *)((s32)arg6 + 0x58), *(u8 *)((s32)arg6 + 0xC));
}

void func_151D9014(f32 *, f32 *, s32, f32, s32, s32, f32, s32, f32, f32, s32, s32, s32, s32, u8, s32);

void func_151B4EA4(Vec3f_local_4E4C *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5) {
    f32 k;
    f32 vel[3];
    s32 c;
    f32 g;
    u32 b;
    u32 a;
    f32 f;

    k = 0.20500001f;
    vel[0] = -arg1 * k;
    vel[1] = -arg2 * k;
    vel[2] = -arg3 * k;
    f = func_150ADA68();
    a = func_150ADA20();
    b = func_150ADA20();
    g = func_150ADA68();
    c = func_150ADA20() & 1;
    func_151D9014((f32 *)arg0, vel, arg4, f * 0.497f + -1.0f, a % 31 + 20, b % 101 + 155, g * 152.0f + 109.0f, c, 1.7f, 1.7f, 0, 0,
                  1, 0, arg5, 1);
}


void *func_151B4FE0(struct102 *arg0, s32 arg1, s32 arg2) {
    void *result;
    struct_4FE0 sp1C;

    if (arg0 == 0) {
        return 0;
    }
    sp1C.unk0 = 0;
    sp1C.unk4 = 0;
    sp1C.unk8 = *((u8 *)arg0 + 0x3B);
    sp1C.unkC = arg0;
    sp1C.unk10 = 2;
    sp1C.unk14 = 0.0f;
    sp1C.unk18 = -27.0f;
    sp1C.unk1C = 16.0f;
    sp1C.unk20 = 9.8f;
    sp1C.unk24 = 0.143f;
    sp1C.unk2A = 2;
    sp1C.unk28 = 0x12C;
    sp1C.unk2B = 9;
    sp1C.unk2C = -1;
    sp1C.unk2D = 8;
    result = func_1513418C(&sp1C, 0, (u8)arg1, arg2);
    return result;
}


typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3f_local;

void func_151B50F4(Vec3f_local *, f32, f32, f32, u8);

void func_151B50A4(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, void *arg6) {
    Vec3f_local sp24;

    sp24.x = arg0;
    sp24.y = arg1;
    sp24.z = arg2;
    func_151B50F4(&sp24, arg3, arg4, arg5, *(u8 *)((s32)arg6 + 0xC));
}

void func_151B50F4(Vec3f_local *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4) {
    f32 k;
    f32 vel[3];
    u8 flag;
    f32 c;
    u32 b;
    u32 a;
    f32 f;

    k = 0.13000001f;
    vel[0] = -arg1 * k;
    vel[1] = -arg2 * k;
    vel[2] = -arg3 * k;
    flag = (func_150ADA20() & 1) ? 1 : 0;
    f = func_150ADA68();
    a = func_150ADA20();
    b = func_150ADA20();
    c = func_150ADA68() * 202.0f + 142.0f;
    func_151D9014((f32 *)arg0, vel, 0, f * 0.126f + -0.702f, (a & 0xF) + 10, b % 45 + 137,
                  c, flag, 1.7f, 1.7f, 0, 0, 1, 0, arg4, 1);
}
