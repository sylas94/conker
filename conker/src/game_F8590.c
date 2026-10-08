#include <ultra64.h>
#define func_1513D668 func_1513D668_void_proto
#include "functions.h"
#undef func_1513D668
s32 func_1513D668(s32 arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, s16 arg6, f32 arg7, f32 arg8, s32 arg9, s32 argA, u8 argB, s32 argC, u8 argD, s32 argE);
#include "variables.h"

extern f32 D_800A05E0[];
extern f32 D_800A05EC[];
extern f32 D_800A0604;
extern f32 D_800A0608;
extern f32 D_800A060C;
extern f32 D_800A0610;
extern f32 D_800A0614;
extern f32 D_800A0618;
extern f32 D_800A061C;
extern f32 D_800A0620;
extern f32 D_800A0624;
extern f32 D_800A0628;
extern f32 D_800A062C;
extern f32 D_800A0630;
void func_15143134(void *, f32 *, s32);
void func_1504715C(s32, s32);
s32 func_15046C80(f32 *, s32, f32, s32);
void func_15143794(s32, s32, f32, f32 *);
struct260 *func_15130374(void *, u8, s32, u8, s32);
s32 func_15132A4C(void *, s32, s32, s32, u8, s32);

typedef struct {
    char pad_0[0x7A];
    u16 unk7A;
    char pad_7C[0x1D4 - 0x7C];
    s32 field_0x1D4;
} AnimFrameOwner;

s32 func_150CB0E0(f32 *arg0, AnimFrameOwner *arg1, s32 arg2, u8 arg3) {
    f32 sp2C[3];
    f32 *temp_a0;
    s32 temp_a2;

    if ((arg3 != 1) && (arg3 != 2)) {
        return 0;
    }

    if (arg3 == 1) {
        temp_a0 = D_800A05EC;
    } else {
        temp_a0 = D_800A05E0;
    }

    if (arg3 == 1) {
        temp_a2 = arg1->field_0x1D4 + 0xA00;
    } else {
        temp_a2 = arg1->field_0x1D4 + 0xBC0;
    }

    func_15143134(temp_a0, arg0, temp_a2);
    if (arg2 == 0) {
        return 1;
    }

    sp2C[0] = arg0[0];
    sp2C[1] = arg0[1] + 100.0f;
    sp2C[2] = arg0[2];
    func_1504715C(arg2, (s32)arg1);
    return func_15046C80(sp2C, 0, arg0[1] - 500.0f, arg2);
}

s32 func_150CB1E0(s32 arg0, s32 arg1) {
    return 0xB;
}

typedef struct {
    f32 unk00;
    f32 unk04;
    f32 unk08;
    f32 unk0C;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    u8 unk1C;
    u8 pad1D[0x7];
} CB1F4Ground; /* 0x24 */

typedef struct {
    s16 unk0;
    f32 unk4;
} CB1F4Extra;

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
} CB1F4Col;

typedef struct {
    u8 unk0;
    u8 unk1;
    s16 unk2;
    s16 unk4;
    u8 pad6[2];
    s32 unk8;
    s32 unkC;
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
    f32 unk14;
    f32 unk18;
    struct17 unk1C;
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
    s32 unk48;
    u8 unk4C;
    u8 pad4D[3];
    s32 unk50;
    s16 unk54;
    s16 unk56;
} CB1F4Main; /* 0x58 */

typedef struct {
    u8 r;
    u8 g;
    u8 b;
} CB1F4Rgb;

extern f32 D_800A05F8;
extern f32 D_800A05FC;
extern f32 D_800A0600;
void func_150CCD90(f32, f32 *, f32 *, f32 *);
void func_1514C678(f32, f32, s32, f32, s32, s32, s32, s32, s32, f32, s32, s32);
s32 func_1518ABD0(s32, s32, s32);

void func_150CB1F4(AnimFrameOwner *arg0, s32 arg1, s32 arg2) {
    f32 pos[3];
    CB1F4Ground ground;
    f32 fr;
    f32 fg;
    f32 fb;
    u8 r;
    u8 g;
    u8 b;
    s32 off;
    CB1F4Extra extra;
    CB1F4Main mn;
    s32 ret;

    if (arg0->field_0x1D4 == 0) {
        return;
    }
    if (func_150CB0E0(pos, arg0, (s32)&ground, (u8)arg1) == 0) {
        return;
    }
    func_1512D748(&D_800DBFF0[D_800BE9E8], 7, 1);
    func_151D5404((struct17 *)pos, 1502.0f, 3000.0f, 0.0003333333298f, 0xC, 0xF, 0xFF, 0);
    func_150CCD90(pos[2], &fr, &fg, &fb);
    r = (u8)fr;
    g = (u8)fg;
    b = (u8)fb;
    {
        CB1F4Col cols[4];
        s16 spd;
        s16 spd2;
        CB1F4Rgb rgb;

        cols[0].unk0 = r;
        cols[0].unk2 = g;
        cols[0].unk4 = b;
        cols[0].unk6 = 0xFF;
        cols[0].unk8 = 0;
        cols[1].unk0 = r;
        cols[1].unk2 = g;
        cols[1].unk4 = b;
        cols[1].unk6 = 0xFF;
        cols[1].unk8 = 0;
        cols[2].unk0 = r;
        cols[2].unk2 = g;
        cols[2].unk4 = b;
        cols[2].unk6 = 0xFF;
        cols[2].unk8 = 0;
        cols[3].unk0 = r;
        cols[3].unk2 = g;
        cols[3].unk4 = b;
        cols[3].unk6 = 0xFF;
        cols[3].unk8 = 0;
        if (arg1 == 1) {
            mn.unk0 = 0x4C;
        } else {
            mn.unk0 = 0x4B;
        }
        mn.unk2 = 0x2603;
        mn.unk4 = 2;
        mn.unk8 = 0;
        mn.unkC = 0;
        mn.unk10 = 0xFF;
        mn.unk11 = 0xFF;
        mn.unk12 = 0xFF;
        mn.unk13 = 0xFF;
        mn.unk14 = mn.unk18 = ((func_150ADA68() * 50.0f) + D_800A05F8) * D_800A05FC;
        mn.unk1C.unk0 = pos[0];
        mn.unk1C.unk4 = ground.unk00 + 10.0f;
        mn.unk1C.unk8 = pos[2];
        mn.unk28 = 0.0f;
        mn.unk2C = 0.0f;
        mn.unk30 = 0.0f;
        mn.unk34 = 1.0f;
        mn.unk38 = 1.0f;
        mn.unk3C = 1.0f;
        mn.unk40 = 0x401C0000;
        mn.unk44 = (func_150ADA20() % 51U) + 160;
        mn.unk45 = 0xFF;
        extra.unk0 = (func_150ADA20() & 3) + 7;
        extra.unk4 = (((func_150ADA68() * 30.0f) + 30.0f) * mn.unk14) * D_800A0600;
        mn.unk46 = 0;
        mn.unk47 = 6;
        off = (arg1 == 1) ? -8 : 8;
        ret = func_1513D668((s32)&mn, (s32)cols, 0, 0x17, 0, 0,
                            (s16)((arg0->unk7A >> 8) - off),
                            500.0f, 500.0f, 0, (s32)&ground.unk04, 1, 8, 0xFF, 0);
        if (ret != 0) {
            memcpy((u8 *)ret + 0x128, &extra, 8);
            if (func_1518ABD0(D_800D98E0, ret, 2) == 0) {
                func_1516972C((struct102 *)ret);
            }
        }
        spd = (func_150ADA20() & 0xF) + 10;
        func_1514C678(pos[0], pos[1], *(s32 *)&pos[2], (func_150ADA68() * 59.0f) + 80.0f,
                      0, 0xFF, spd, 0xE, 0, 0.0f, 0, 0xFF);
        spd2 = (func_150ADA20() & 0xF) + 5;
        rgb.r = r;
        rgb.g = g;
        rgb.b = b;
        func_1514C678(pos[0], pos[1], *(s32 *)&pos[2], (func_150ADA68() * 59.0f) + 70.0f,
                      0, 0xFF, spd2, 0xF, 0, 0.0f, (s32)&rgb, 0xFF);
    }
}

struct Func150CB7CC {
    char pad0[0x1C];
    s16 unk1C;
    char pad1E[0x28 - 0x1E];
    u8 unk28;
};

s32 func_150CB7CC(struct Func150CB7CC *arg0) {
    s32 v1;

    if (arg0->unk1C < 0x20) {
        v1 = arg0->unk1C << 3;
        if (v1 < arg0->unk28) {
            arg0->unk28 = v1;
        }
    }
    return 1;
}

s32 func_150CB800(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5,
                  s32 arg6, s32 arg7, s16 arg8, s32 arg9, s32 arg10, s32 arg11,
                  s32 arg12, s32 arg13, u8 arg14) {
    struct {
        f32 unk00;
        f32 unk04;
        f32 unk08;
        f32 unk0C;
        f32 unk10;
        f32 unk14;
        f32 unk18;
        f32 unk1C;
        f32 unk20;
        f32 unk24;
        f32 unk28;
        f32 unk2C;
        f32 unk30;
        f32 unk34;
        f32 unk38;
        f32 unk3C;
        f32 unk40;
        f32 unk44;
        f32 unk48;
        f32 unk4C;
        s32 unk50;
        s16 unk54;
        s16 unk56;
        u8 unk58;
        u8 pad59[3];
        s32 unk5C;
        u8 unk60;
        u8 unk61;
        u8 unk62;
        u8 unk63;
        u8 unk64;
        u8 unk65;
        u8 unk66;
        u8 unk67;
        u8 unk68;
        u8 pad69;
        u8 unk6A;
        u8 pad6B;
        s32 unk6C;
        u8 unk70;
        u8 pad71;
        s16 unk72;
        s16 unk74;
        s32 pad78;
        s32 pad7C;
    } sp28;

    sp28.unk28 = arg2;
    sp28.unk2C = arg3;
    sp28.unk1C = 1.0f;
    sp28.unk20 = 1.0f;
    sp28.unk24 = 1.0f;
    sp28.unk50 = 0x29E8;
    sp28.unk10 = 0.0f;
    sp28.unk14 = 0.0f;
    sp28.unk18 = 0.0f;
    sp28.unk44 = 0.0f;
    sp28.unk00 = 1.0f;
    sp28.unk56 = 0x20;
    sp28.unk30 = arg4;
    sp28.unk04 = D_800A0604;

    ((s32 *)&sp28)[-2] = func_150ADA20();
    func_15143794(arg8, (s16)((((s32 *)&sp28)[-2] % 36U) - 55), (func_150ADA68() * 200.0f + 200.0f) * D_800A0608, &sp28.unk34);
    sp28.unk40 = (func_150ADA68() * 300.0f + -149.0f) * D_800A060C;
    sp28.unk48 = (func_150ADA68() * 300.0f + -149.0f) * D_800A0610;
    sp28.unk54 = (func_150ADA20() % 33U) + 32;
    sp28.unk4C = (func_150ADA68() * D_800A0614 + D_800A0618) * D_800A061C;
    sp28.unk0C = (func_150ADA68() * 300.0f + 101.0f) * D_800A0620;
    sp28.unk58 = 0;
    sp28.unk5C = 0;
    sp28.unk08 = sp28.unk0C;
    sp28.unk60 = (func_150ADA20() % 101U) + 155;
    sp28.unk61 = 2;
    sp28.unk62 = 0;
    sp28.unk63 = 0;
    sp28.unk64 = 0;
    sp28.unk65 = 0;
    sp28.unk66 = 0;
    sp28.unk67 = 0;
    sp28.unk68 = 0;
    sp28.unk6A = 2;
    sp28.unk6C = 0;
    sp28.unk70 = 0;
    sp28.unk72 = 0x20;
    sp28.unk74 = 7;
    func_15132A4C(&sp28, 3, 0xFF, 0, arg14, 0);
    return 1;
}

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
    s16 unk128;
    char pad12A[0x12C - 0x12A];
    f32 unk12C;
} CBA30Struct;


s32 func_150CBA30(CBA30Struct *arg0) {
    arg0->unk128 -= D_800BE9E4;
    if (arg0->unk128 > 0) {
        f32 v = arg0->unk12C * D_800BE9A4;
        arg0->unk2C = arg0->unk2C + v;
        arg0->unk30 = arg0->unk30 + v;
    }
    if (arg0->unk58 & 1) {
        if (arg0->unk1C < 0x20) {
            if ((arg0->unk1C << 3) < arg0->unk5C) {
                arg0->unk5C = arg0->unk1C << 3;
            }
        }
    }
    return 1;
}

s32 func_150CBABC(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s16 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, s32 argD, u8 argE) {
    struct260 *ret;
    struct {
        s32 sp24;
        u8 pad28[4];
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
    stack.sp34.unk0A = (func_150ADA20() % 0x29U) + 0x28;
    stack.sp34.unk0C = 0;
    stack.sp34.unk10 = 0;
    stack.sp34.unk18 = 0xB0;
    stack.sp34.unk19 = 0xA0;
    stack.sp34.unk1A = 0x2A;
    stack.sp34.unk14 = 0x40;
    stack.sp34.unk15 = 0xB;
    stack.sp34.unk16 = 0x6A;
    stack.sp34.unk17 = 0xFF;
    stack.sp34.unk1B = (func_150ADA20() % 0x9DU) + 0x64;
    stack.sp34.unk1C = 0xFF;
    stack.sp34.unk60 = 3;
    stack.sp34.unk61 = 3;
    stack.sp34.unk28 = stack.sp34.unk2C = (func_150ADA68() * D_800A0624) + 300.0f;
    stack.sp34.unk30 = arg2;
    stack.sp34.unk34 = arg3;
    stack.sp34.unk38 = arg4;

    stack.sp24 = func_150ADA20();
    func_15143794(arg8, (s16)((stack.sp24 % 0x1AU) - 0x19), ((func_150ADA68() * 500.0f) + 1000.0f) * D_800A0628, &stack.sp34.unk48);
    stack.sp34.unk58 = 0xE05;
    stack.sp34.unk54 = 0.0f;

    if (func_150ADA20() & 1) {
        stack.sp34.unk58 |= 0x40;
    }

    if (func_150ADA20() & 1) {
        stack.sp34.unk58 |= 0x80;
    }

    stack.sp34.unk62 = 7;
    stack.sp34.unk63 = -1;
    stack.sp34.unk1E = 0x19;
    stack.sp34.unk20 = 0xA;
    stack.sp34.unk22 = 0x3C;
    stack.sp34.unk24 = D_800A062C;
    stack.sp2C = D_800A0630;

    ret = func_15130374(&stack.sp34, 1, 4, argE, 1);
    if (ret != 0) {
        memcpy((u8 *)ret + 0xA8, &stack.sp2C, 4);
    }
    return 1;
}

typedef struct {
    char pad0[0x58];
    f32 unk58;
    char pad5C[0x60 - 0x5C];
    f32 unk60;
} Func150CBCE0;

s32 func_150CBCE0(Func150CBCE0 *arg0, s32 arg1) {
    s32 i;
    volatile f32 *scale;

    scale = (volatile f32 *)((u8 *)arg0 + 0xA8);
    for (i = D_800BE9E4; i != 0; i--) {
        arg0->unk58 *= *scale;
        arg0->unk60 *= *scale;
    }
    return 1;
}

s32 func_150CBE88(f32 *arg0) {
    arg0[14] += arg0[17] * D_800BE9A4;
    arg0[15] += (arg0[18] * D_800BE9A4) + (((arg0[23] * D_800BE9A4) * D_800BE9A4) * 0.5f);
    arg0[16] += arg0[19] * D_800BE9A4;
    arg0[18] += arg0[23] * D_800BE9A4;
    arg0[8] += arg0[20] * D_800BE9A4;
    arg0[9] += arg0[21] * D_800BE9A4;
    arg0[10] += arg0[22] * D_800BE9A4;
    return 1;
}

struct Func150CBF5C {
    char pad0[0x1C];
    s16 unk1C;
    char pad1E[0x58 - 0x1E];
    s32 unk58;
};

void func_150CBF5C(struct Func150CBF5C *arg0) {
    arg0->unk58 |= 1;
    arg0->unk1C = 0x20;
}
