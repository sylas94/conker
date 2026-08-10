#include <ultra64.h>
#define func_1513D524 func_1513D524_void
#include "functions.h"
#undef func_1513D524
#include "variables.h"

s32 func_1513D524(s32 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, s32 arg6, u8 arg7, s32 arg8);

extern f32 D_800A0710;
extern f32 D_800A0714;
extern f32 D_800A0718;
extern f32 D_800A071C;
extern f32 D_800A0720;
extern f32 D_800A0724;
extern f32 D_800A0728;
extern f32 D_800A072C;
extern f32 D_800A0730;
extern f32 D_800A0734;
extern f32 D_800A0738;
extern f32 D_800A073C;
extern f32 D_800A0740;
extern f32 D_800A0744;
extern f32 D_800A0748;

struct Vec3I150CCEB0 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
};

struct Pair150CCEB0 {
    s32 unk0;
    s32 unk4;
};

struct Arg150CCEB0 {
    struct Vec3I150CCEB0 unk00;
    struct Vec3I150CCEB0 unk0C;
    f32 unk18;
    f32 unk1C;
    u8 unk20;
    u8 unk21;
    u8 unk22;
    u8 unk23;
    s32 unk24;
    struct Pair150CCEB0 unk28;
    f32 unk30;
};

struct Main150CCEB0 {
    u8 unk00;
    u8 pad01;
    s16 unk02;
    s16 unk04;
    u8 pad06[2];
    s32 unk08;
    s32 unk0C;
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
    struct Pair150CCEB0 unk14;
    struct Vec3I150CCEB0 unk1C;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    s32 unk40;
    u8 unk44;
    u8 unk45;
    u8 unk46;
    u8 unk47;
    u8 pad48[0x10];
};

struct Extra150CCEB0 {
    struct Vec3I150CCEB0 unk00;
    f32 unk0C;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    u8 pad20[4];
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
};

s32 func_150CCEB0(struct Arg150CCEB0 *arg0, u8 arg1, u8 arg2) {
    s32 ret;
    struct Main150CCEB0 main;
    struct Extra150CCEB0 extra;

    main.unk00 = 0x57;
    main.unk02 = 0x2D03;
    main.unk04 = arg0->unk24;
    main.unk08 = 0;
    main.unk0C = 0;
    main.unk10 = arg0->unk20;
    main.unk11 = arg0->unk21;
    main.unk12 = arg0->unk22;
    main.unk13 = 0xFF;
    main.unk14 = arg0->unk28;
    main.unk1C = arg0->unk00;
    main.unk28 = func_150ADA68() * 360.0f;
    main.unk2C = func_150ADA68() * 360.0f;
    main.unk30 = func_150ADA68() * 360.0f;
    main.unk40 = 0xC03E1;
    main.unk34 = 0.0f;
    main.unk38 = 0.0f;
    main.unk3C = 0.0f;
    main.unk44 = arg0->unk23;
    main.unk45 = 0xFF;
    main.unk46 = 0;
    main.unk47 = 6;

    extra.unk00 = arg0->unk0C;
    extra.unk3C = arg0->unk30;
    extra.unk10 = arg0->unk18;
    extra.unk0C = arg0->unk1C;
    extra.unk14 = ((func_150ADA68() * D_800A0710) + D_800A0714) * D_800A0718;
    extra.unk18 = ((func_150ADA68() * D_800A071C) + D_800A0720) * D_800A0724;
    extra.unk1C = ((func_150ADA68() * D_800A0728) + D_800A072C) * D_800A0730;
    extra.unk24 = 0.0f;
    extra.unk28 = ((func_150ADA68() * 206.0f) + 58.0f) * D_800A0734;
    extra.unk2C = func_150ADA68() * 360.0f;
    extra.unk30 = 0.0f;
    extra.unk34 = (func_150ADA68() * D_800A0738) * D_800A073C;
    extra.unk38 = ((func_150ADA68() * D_800A0740) + D_800A0744) * D_800A0748;

    ret = func_1513D524((s32)&main, 0x13, 0x1E, 0, 0x11, 0, 0x40, arg1, arg2);

    if (ret != 0) {
        memcpy((void *)(ret + 0x110), &extra, 0x40);
    }

    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_FA360/func_150CD17C.s")

struct Foo150CD59C {
    char pad0[0x2C];
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    f32 unk44;
    f32 unk48;
    f32 unk4C;
    f32 unk50;
    f32 unk54;
    char pad58[0x68];
    char unkC0[0x40];
    s16 *unk100[5];
    f32 unk114;
};

extern void func_151D5D60(s16 **arg0, s16 arg1, s32 arg2, s16 **arg3, u8 *arg4);
extern void func_150A7960(f32 *, f32, f32, f32, f32 *, f32 *, f32 *);

s16 *func_150CD59C(struct Foo150CD59C *arg0, s16 arg1) {
    s32 padD4;
    s16 *var_v0;
    s16 *ret;
    f32 mtx[4][4];
    f32 corners[4][3];
    u8 pad5B;
    u8 sp5A;
    s32 i;

    func_151D5D60(arg0->unk100, arg1, 0x40, &var_v0, &sp5A);
    ret = var_v0;
    if (var_v0) {
        if (sp5A) {
            memcpy(arg0->unk100[arg1], arg0->unkC0, 0x40);
            memcpy(arg0->unk100[arg1] + 0x20, arg0->unkC0, 0x40);
        }
    } else {
        return 0;
    }

    corners[0][0] = arg0->unk2C;
    corners[0][1] = arg0->unk30;
    corners[0][2] = 0.0f;
    corners[1][0] = -arg0->unk2C;
    corners[1][1] = arg0->unk30;
    corners[1][2] = 0.0f;
    corners[2][0] = -arg0->unk2C;
    corners[2][1] = -arg0->unk30;
    corners[2][2] = 0.0f;
    corners[3][0] = arg0->unk2C;
    corners[3][1] = -arg0->unk30;
    corners[3][2] = 0.0f;

    func_150A8050(mtx, arg0->unk40, arg0->unk44, arg0->unk48);

    mtx[3][0] = arg0->unk34;
    mtx[3][1] = arg0->unk38;
    mtx[3][2] = arg0->unk3C;

    if (arg0->unk114 < 0.0f) {
        mtx[3][0] += arg0->unk4C;
        mtx[3][1] += arg0->unk50;
        mtx[3][2] += arg0->unk54;
    }

    for (i = 0; i < 4; i = (i + 1) & 0xFF) {
        f32 *p = corners[i];

        func_150A7960(mtx[0], p[0], p[1], 0.0f, &p[0], &p[1], &p[2]);
        var_v0[0] = p[0];
        var_v0[1] = p[1];
        var_v0[2] = p[2];
        var_v0[3] = 0;
        var_v0 += 8;
    }

    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_FA360/func_150CD7F8.s")

struct Inner150CDB6C {
    s32 unk0;
    f32 unk4;
};
extern u8* D_80088870;
extern f32 D_800A07A4;

void func_150CDB6C(s32 arg0) {
    struct Inner150CDB6C* q;
    if (arg0 >= 0 && arg0 < 0x100) {
        if (D_80088870 != NULL) {
            q = (struct Inner150CDB6C*)(D_80088870 + 0x28);
            q->unk4 = (f32)arg0 * D_800A07A4;
        }
    }
}
