#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern s8 *D_80088890;
extern s8 *D_80088894;
extern s8 *D_80088898;
extern s8 *D_8008889C;
extern s32 *D_800DBF94;

extern struct131 *func_151149AC(s32);
extern void func_151951E0(struct127 *);
extern void func_15136C3C(struct127 *, s32, s32, s32, s32, s32, s32, s32);
extern void func_1507CD64(struct127 *, s32);

s32 func_1509BE40();
void func_1509BFB0(s32 num, s32, s32, ...);
void func_150495B0(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5);

extern f32 D_800888C0;
extern f32 D_800888C4;
extern f32 D_800888C8;
extern f32 D_800888CC;
extern f32 D_800888D0;
extern f32 D_800888D4;
extern f32 D_800888D8;
extern f32 D_800888DC;
extern f32 D_800888E0;

void func_150D08C0(struct108 *arg0) {
    if (func_1509BE40(1, 0x403D, 6, 0x9000) != 0) {
        arg0->unk84 |= 0x80021000;
        if (func_1509BE40(1, 0x4043, 6, 0x9000) != 0) {
            D_800888CC = 64.0f;
            D_800888D0 = 255.0f;
            D_800888D4 = 255.0f;
        } else if (func_1509BE40(1, 0x4044, 6, 0x9000) != 0) {
            D_800888CC = 255.0f;
            D_800888D0 = 64.0f;
            D_800888D4 = 255.0f;
        } else if (func_1509BE40(1, 0x4045, 6, 0x9000) != 0) {
            D_800888CC = 255.0f;
            D_800888D0 = 255.0f;
            D_800888D4 = 64.0f;
        } else {
            D_800888CC = 255.0f;
            D_800888D0 = 255.0f;
            D_800888D4 = 255.0f;
        }
    } else {
        D_800888CC = 255.0f;
        D_800888D0 = 255.0f;
        D_800888D4 = 255.0f;
        arg0->unk84 &= ~0x80021000;
        arg0->unk84 |= 8;
    }
    func_150495B0(&D_800888C0, D_800888CC, &D_800888D8, 4.0f, 6.0f, arg0->unk7B4);
    func_150495B0(&D_800888C4, D_800888D0, &D_800888DC, 4.0f, 6.0f, arg0->unk7B4);
    func_150495B0(&D_800888C8, D_800888D4, &D_800888E0, 4.0f, 6.0f, arg0->unk7B4);
    func_1509BFB0(1, 0x30F5, 0x12, (u8)D_800888C0);
    func_1509BFB0(1, 0x30F4, 0x12, (u8)D_800888C4);
    func_1509BFB0(1, 0x30F3, 0x12, (u8)D_800888C8);
    func_1509BFB0(1, 0x30FA, 0x12, (u8)D_800888C0);
    func_1509BFB0(1, 0x30F9, 0x12, (u8)D_800888C4);
    func_1509BFB0(1, 0x30F8, 0x12, (u8)D_800888C8);
}

void func_150D0E90(s32 arg0) {
    struct131 *temp;
    s32 idx;
    s32 i;

    D_80088890 += D_800BE9E4 * 0x28;
    D_80088894 += D_800BE9E4 * -0x42;
    D_80088898 += D_800BE9E4 * -8;
    D_8008889C += D_800BE9E4 * 0x5C;

    i = 0;
    if (D_800CC2D0->unk31C->unk120 == 0) {
        do {
            temp = func_151149AC((0xFA - i) & 0xFF);
            idx = temp - D_800DBEF4;
            if (D_800DBF94[idx] & 1) {
                func_151951E0(D_800CC2D0);
                func_10010154(0x627, D_800CC2D0, 0x7FFF, 0xC8, 0x2BC);
            }
            i += 1;
        } while (i != 3);

        temp = func_151149AC(0xFB);
        idx = temp - D_800DBEF4;
        if (D_800DBF94[idx] & 1) {
            func_10010154(0x627, D_800CC2D0, 0x7FFF, 0xC8, 0x2BC);
            func_15136C3C(D_800CC2D0, 1, 1, 1, 1, 0, 0xFF, 1);
            func_15145A50(D_800CC2D0);
            func_1507CD64(D_800CC2D0, 6);
        }
    }
}

typedef struct {
    /* 0x00 */ u8  unk0;
    /* 0x01 */ u8  pad1[0x3];
    /* 0x04 */ void *unk4;
    /* 0x08 */ u8  unk8;
    /* 0x09 */ u8  pad9[0x3];
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u8  unk24;
    /* 0x25 */ u8  pad25[0x1];
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ u8  unk2E;
    /* 0x2F */ u8  unk2F;
    /* 0x30 */ s8  unk30;
    /* 0x31 */ u8  pad31[0x3];
    /* 0x34 */ f32 unk34;
    /* 0x38 */ u8  unk38;
    /* 0x39 */ s8  unk39;
} struct_10E4;

extern f32 D_800A0890;
void func_15134DAC(struct_10E4 *, s32);

void func_150D10E4(void *arg0, u8 arg1) {
    struct_10E4 sp1C;

    sp1C.unk0 = *((u8 *)arg0 + 0x3B);
    sp1C.unk4 = arg0;
    sp1C.unk8 = 0;
    sp1C.unkC = 0.0f;
    sp1C.unk10 = 0.0f;
    sp1C.unk14 = 0.0f;
    sp1C.unk18 = 0.0f;
    if (arg1 != 0) {
        sp1C.unk1C = -30.0f;
    } else {
        sp1C.unk1C = 30.0f;
    }
    sp1C.unk20 = 0.0f;
    sp1C.unk24 = 2;
    sp1C.unk26 = 0x32;
    sp1C.unk28 = 0x16;
    sp1C.unk2A = 0x7D0;
    sp1C.unk2C = 0;
    sp1C.unk2E = 6;
    sp1C.unk2F = 7;
    sp1C.unk30 = -1;
    sp1C.unk34 = D_800A0890;
    sp1C.unk38 = 0;
    sp1C.unk39 = -1;
    func_15134DAC(&sp1C, 0);
}

extern f32 D_800A0894;

s32 func_150D11B4(void *arg0) {
    *(f32 *)((char *)arg0 + 0x74) = (func_150ADA68() * 150.0f + 350.0f) * D_800A0894;
    return 1;
}

extern f32 D_800A0898;
extern f32 D_800A089C;
extern f32 D_800A08A0;
extern f32 D_800A08A4;

void func_151DB5D0(s32, f32 *, f32 *, f32, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32);

void func_150D1204(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 arg4, void *arg5) {
    f32 sp6C[3];
    f32 t0;
    f32 t1;
    f32 t2;
    f32 sp54[3];
    s32 pad50;
    s32 r1;
    f32 f2;
    f32 f1;

    sp6C[0] = arg2[0] * arg4 + arg0[0];
    sp6C[1] = arg2[1] * arg4 + arg0[1];
    sp6C[2] = arg2[2] * arg4 + arg0[2];

    t0 = arg3[0] * arg4 + arg1[0];
    t1 = arg3[1] * arg4 + arg1[1];
    t2 = arg3[2] * arg4 + arg1[2];

    sp54[0] = *(f32 *)((u8 *)arg5 + 0x74) * (t0 - sp6C[0]);
    sp54[1] = *(f32 *)((u8 *)arg5 + 0x74) * (t1 - sp6C[1]);
    sp54[2] = *(f32 *)((u8 *)arg5 + 0x74) * (t2 - sp6C[2]);

    f1 = func_150ADA68();
    f2 = func_150ADA68();
    r1 = func_150ADA20();

    func_151DB5D0(0, sp6C, sp54, f1 * 61.0f + 60.0f, D_800A0898, D_800A089C,
                  f2 * D_800A08A0 + D_800A08A4, (r1 & 0xF) + 0x23,
                  (s32)((u32)func_150ADA20() % 0x9CU) + 0x64, 0x1E, 8, 0,
                  *((u8 *)arg5 + 0xC), *((u8 *)arg5 + 1));
}
