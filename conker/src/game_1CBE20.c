#include <ultra64.h>
#include "functions.h"
#include "variables.h"


struct Vec1519EA78 {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
};

struct Conker1519EA78 {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ struct Vec1519EA78 unk08;
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
};

struct Src1519EA78 {
    /* 0x00 */ struct Vec1519EA78 unk00;
};

extern f32 D_800A8CC0;
extern f32 D_800A8CC4;
extern f32 D_800A8CC8;
extern f32 D_800A8CCC;
extern f32 D_800A8CD0;

void func_15152190(struct Conker1519EA78 *arg0, s32 *arg1, f32 *arg2, s32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7);

struct Obj1519E970 {
    char pad0[0x10];
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s16 unk20;
    char pad22[0x24 - 0x22];
    s32 unk24;
    u8  unk28;
};

extern struct Obj1519E970 *func_15167A68(s32, s32, s32, s32, s32, s32);

struct Obj1519E970 *func_1519E970(s16 a0, s32 a1, u8 a2, s32 a3, s32 a4, u8 a5, s32 a6) {
    struct Obj1519E970 *ret = func_15167A68(0x26, a6, 0x2C, 1, a5, 1);
    if (ret == 0) {
        return NULL;
    }
    ret->unk18 = a3;
    ret->unk1C = a4;
    ret->unk20 = a0;
    ret->unk28 = a2;
    ret->unk24 = a1;
    ret->unk10 = 1;
    ret->unk14 = 0;
    return ret;
}

struct Local1519EA04 {
    char pad0[0x10];
    s32 unk10;
    char pad14[0x20 - 0x14];
    s16 unk20;
    char pad22[0x24 - 0x22];
    s32 *unk24;
    u8 unk28;
};

void func_1519EA04(struct Local1519EA04 *arg0) {
    if (arg0->unk10 & 1) {
        s32 flag = 0;
        arg0->unk20 -= D_800BE9E4;
        if (arg0->unk20 < 0) {
            flag = 1;
        }
        if (flag != 0) {
            if (arg0->unk28 == 0) {
                s32 *p = arg0->unk24;
                p[0x30 / 4] = 0;
            }
            func_1516972C((struct102 *)arg0);
        }
    }
}

void func_1519EA78(struct Src1519EA78 *arg0, u16 arg1, f32 arg2, u8 arg3, s32 arg4) {
    struct Conker1519EA78 sp34;
    s32 sp30;
    f32 sp2C;

    sp34.unk00 = 0xA;
    sp34.unk04 = 7;
    sp34.unk08 = arg0->unk00;
    sp34.unk14 = 0;
    sp34.unk16 = 0xFF;
    sp34.unk18 = -0x35;
    sp34.unk1A = 0x18;
    sp34.unk1C = 10.0f;
    sp34.unk20 = 8.0f;
    sp34.unk24 = D_800A8CC0;
    sp34.unk28 = D_800A8CC4;
    sp34.unk2C = 0x32;
    sp34.unk2E = 0x14;
    sp34.unk30 = D_800A8CC8;
    sp34.unk34 = D_800A8CCC;
    sp34.unk38 = D_800A8CD0;
    sp30 = arg1;
    sp2C = arg2;
    func_15152190(&sp34, &sp30, &sp2C, 1, 0.0f, 0, arg3, arg4);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1CBE20/func_1519EB8C.s")

struct Src1519ED24 {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
};

struct Obj1519ED24 {
    char pad0[0x18];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    char pad2C[0x38 - 0x2C];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    char pad44[0x170 - 0x44];
    /* 0x170 */ struct Src1519ED24 *unk170;
};

extern f32 D_800A8CD8;

/* scale is read once into a local; src lives in a nested block (a -g3 scheduling barrier),
 * which is what lets the scale load win the cycle-0 tie against the arg0->unk170 load. */
s32 func_1519ED24(struct Obj1519ED24 *arg0) {
    f32 scale;

    scale = D_800A8CD8;
    {
        struct Src1519ED24 *src = arg0->unk170;

        arg0->unk18 = src->unk18 * scale;
        arg0->unk1C = src->unk1C * scale;
        arg0->unk20 = src->unk0C;
        arg0->unk24 = src->unk10;
        arg0->unk28 = src->unk14;
        arg0->unk38 = src->unk00;
        arg0->unk3C = src->unk04;
        arg0->unk40 = src->unk08;
        return 1;
    }
}

typedef struct {
    /* 0x00 */ u8  unk0;
    /* 0x01 */ u8  unk1;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u8  pad6[2];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8  unk10;
    /* 0x11 */ u8  unk11;
    /* 0x12 */ u8  unk12;
    /* 0x13 */ u8  unk13;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ u8  unk44;
    /* 0x45 */ u8  unk45;
    /* 0x46 */ u8  unk46;
    /* 0x47 */ u8  unk47;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ u8  unk4C;
    /* 0x4D */ u8  pad4D[3];
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s16 unk54;
    /* 0x56 */ s16 unk56;
} Struct1519ED84;

void func_1519ED84(f32 *arg0, s32 arg1, s16 arg2, u8 arg3, s32 arg4) {
    Struct1519ED84 sp48;
    s32 sp44;
    void *temp_v0;

    sp44 = (s32)arg0;
    sp48.unk0 = arg1;
    sp48.unk1 = 0;
    sp48.unk2 = 0x3B03;
    sp48.unk4 = arg2;
    sp48.unk8 = 0;
    sp48.unkC = 0;
    sp48.unk10 = 0xFF;
    sp48.unk11 = 0xFF;
    sp48.unk12 = 0xFF;
    sp48.unk13 = 0xFF;
    sp48.unk14 = arg0[6] * 10.0f;
    sp48.unk18 = arg0[7] * 10.0f;
    sp48.unk1C = arg0[0];
    sp48.unk20 = arg0[1];
    sp48.unk24 = arg0[2];
    sp48.unk28 = arg0[3];
    sp48.unk2C = arg0[4];
    sp48.unk30 = arg0[5];
    sp48.unk34 = 1.0f;
    sp48.unk38 = 1.0f;
    sp48.unk3C = 1.0f;
    sp48.unk40 = 0x45C0081;
    sp48.unk44 = 0xFF;
    sp48.unk45 = 0xFF;
    sp48.unk46 = 0;
    sp48.unk47 = 7;
    sp48.unk48 = 0;
    sp48.unk4C = 0xFF;
    sp48.unk50 = 0;
    sp48.unk54 = 1;
    sp48.unk56 = 0xFF;

    temp_v0 = func_1513D2F0(&sp48, &D_800A4AA0, 0x27, 0, 0, 0x17, 0, 3, 0xFF, 4, arg3, arg4);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x110, &sp44, 4);
    }
}

struct Sub1519EF04 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
};

struct Obj1519EF04 {
    char pad0[0x2C];
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    f32 unk44;
    f32 unk48;
    char pad4C[0x110 - 0x4C];
    struct Sub1519EF04 *unk110;
};

s32 func_1519EF04(struct Obj1519EF04 *a0) {
    struct Sub1519EF04 *v1 = a0->unk110;

    a0->unk2C = v1->unk18 * 10.0f;
    a0->unk30 = v1->unk1C * 10.0f;
    a0->unk40 = v1->unkC;
    a0->unk44 = v1->unk10;
    a0->unk48 = v1->unk14;
    a0->unk34 = v1->unk0;
    a0->unk38 = v1->unk4;
    a0->unk3C = v1->unk8;
    return 1;
}
