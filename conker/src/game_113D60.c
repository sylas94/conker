#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ s32 unk8;
} Struct150E81A8Vec;

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ Struct150E81A8Vec unk10;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ s16 unk4C;
    /* 0x4E */ s16 unk4E;
    /* 0x50 */ s16 unk50;
    /* 0x52 */ s16 unk52;
    /* 0x54 */ s16 unk54;
    /* 0x56 */ s16 unk56;
    /* 0x58 */ s8 unk58;
} Struct150E81A8;

typedef struct {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ u8 unk4;
    /* 0x5 */ u8 unk5;
    /* 0x6 */ s8 unk6;
    /* 0x7 */ u8 unk7;
} Struct150E81A8Small;

extern Struct150E81A8Vec D_800A1290[];
extern f32 *D_80088A3C;
extern f32 *D_80088A40;
extern f32 D_800A130C;
extern f32 D_800A1354;
extern f32 D_800A1358;
extern f32 D_800A135C;
extern f32 D_800A1360;
extern f32 D_800A1364;
extern f32 D_800A1310;
extern f32 D_800A1314;
extern f32 D_800A1318;
extern f32 D_800A131C;
extern f32 D_800A1320;
extern void func_151D3FF4(Struct150E81A8Vec *arg0, u8 arg1, s32 arg2);
extern void func_1514FCE8(Struct150E81A8 *arg0, u8 arg1, s32 arg2);
extern void func_151D8868(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_151337C0(f32 *arg0);


#pragma GLOBAL_ASM("asm/nonmatchings/game_113D60/func_150E68B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_113D60/func_150E6B84.s")

void func_150E6E34(f32 *out) {
    f32 *p;
    f32 t;

    if (func_150ADA68() < D_800A130C) {
        p = D_80088A3C;
    } else {
        p = D_80088A40;
    }
    t = func_150ADA68();
    out[0] = p[0] + (p[3] - p[0]) * t;
    out[1] = p[1] + (p[4] - p[1]) * t;
    out[2] = p[2] + (p[5] - p[2]) * t;
}

extern s32 func_1514470C(struct134 *, s32);

void func_150E6ED8(s32 arg0) {
    func_1514470C((&D_800D9A20)[func_150ADA20() & 1], arg0);
}

extern f32 *D_80088A44[];

void func_150E6F18(f32 *out) {
    f32 *p;
    f32 t;
    p = D_80088A44[(u32)func_150ADA20() % 6];
    t = func_150ADA68();
    out[0] = p[0] + (p[3] - p[0]) * t;
    out[1] = p[1] + (p[4] - p[1]) * t;
    out[2] = p[2] + (p[5] - p[2]) * t;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_113D60/func_150E6FAC.s")

void func_150E70CC(f32 *arg0, f32 *arg1) {
    arg0[0] = arg1[5];
    arg0[1] = arg1[6];
    arg0[2] = arg1[7];
}

void func_150E70EC(s32 arg0, s32 arg1, f32 *arg2, f32 *out) {
    f32 temp_f2;
    f32 temp_f16;

    out[0] = func_150484A0(arg2[0], arg2[2]);
    out[2] = func_150ADA68() * D_800A1310;
    out[4] = func_150ADA68() * D_800A1314;
    out[6] = func_150ADA68() * 0.5f;
    temp_f2 = arg2[0];
    temp_f16 = arg2[2];
    out[1] = func_150484A0(sqrtf((temp_f2 * temp_f2) + (temp_f16 * temp_f16)), arg2[1]) - D_800A1318;
    out[3] = func_150ADA68() * D_800A131C;
    out[5] = func_150ADA68() * D_800A1320;
    out[7] = func_150ADA68() * 0.5f;
}

extern f32 D_800A1324;
extern f32 D_800A1328;
extern f32 D_800A132C;
extern f32 D_800A1330;
extern f32 D_800A1334;
extern f32 D_800A1338;
extern f32 D_800A133C;

void func_150E71E4(s32 arg0, s32 arg1, f32 *arg2, f32 *out) {
    out[0] = func_150484A0(arg2[0], arg2[2]);
    out[2] = D_800A1324;
    out[4] = func_150ADA68() * D_800A1328;
    out[6] = func_150ADA68() * D_800A132C;
    out[1] = D_800A1330;
    out[3] = D_800A1334;
    out[5] = func_150ADA68() * D_800A1338;
    out[7] = func_150ADA68() * D_800A133C;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_113D60/func_150E7290.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_113D60/func_150E75A0.s")

typedef struct {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ u8  unk10;
    /* 0x11 */ u8  pad11;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ u16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ u8  unk1A;
    /* 0x1B */ u8  unk1B;
    /* 0x1C */ u8  unk1C;
    /* 0x1D */ u8  unk1D;
    /* 0x1E */ u8  unk1E;
    /* 0x1F */ u8  unk1F;
    /* 0x20 */ u8  unk20;
    /* 0x21 */ u8  unk21;
    /* 0x22 */ u8  unk22;
    /* 0x23 */ u8  unk23;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ u8  unk40;
    /* 0x41 */ u8  unk41;
    /* 0x42 */ u8  pad42[2];
    /* 0x44 */ u8  unk44;
    /* 0x45 */ u8  pad45[3];
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ f32 unk58;
} Struct150E76D0;

typedef struct {
    /* 0x0 */ s32 unk0[3];
} Struct150E76D0Tbl;

extern Struct150E76D0Tbl D_80088A68;
extern Struct150E76D0Tbl D_80088A74;
extern void *func_1515548C(Struct150E76D0 *, s32, s32, s32, s32, u8, s32);

void func_150E76D0(f32 arg0, s16 arg1, u8 arg2, u8 arg3, u8 arg4, s16 arg5, s16 arg6, s32 arg7, s32 arg8, u8 arg9, s32 arg10) {
    Struct150E76D0 sp54;
    u8 sp53;

    sp53 = func_150ADA20() & 3;

    sp54.unk12 = arg1;
    sp54.unk14 = arg2 & 0xFFF9;
    sp54.unk16 = arg5;
    sp54.unk18 = arg6;
    sp54.unk1A = 5;
    sp54.unk1B = 0xFF;
    sp54.unk1C = 0xE6;
    sp54.unk1D = 0xBE;
    sp54.unk1E = arg3;
    sp54.unk1F = 0xFF;
    sp54.unk20 = 0xFF;
    sp54.unk21 = 0xFF;
    sp54.unk22 = 0xFF;
    sp54.unk23 = arg4;
    sp54.unk24 = 1;
    sp54.unk28 = 0;
    sp54.unk2C = 0;
    sp54.unk40 = 0;
    sp54.unk41 = 0xA;
    sp54.unk30 = 7;
    sp54.unk34 = 0x3C;
    sp54.unk38 = 0x80;
    sp54.unk3C = 0x20;
    sp54.unk0C = arg0;
    sp54.unk08 = arg0;

    switch (sp53) {
    case 0:
    case 1:
        {
            Struct150E76D0Tbl sp44;

            sp44 = D_80088A68;
            sp54.unk10 = sp44.unk0[(u32)func_150ADA20() % 3];
            sp54.unk04 = (func_150ADA68() * 160.0f) + -80.0f;
            switch (sp53) {
            case 0:
                sp54.unk14 |= 2;
                sp54.unk00 = 145.0f - arg0;
                break;
            case 1:
                sp54.unk00 = arg0 - 145.0f;
                break;
            }
        }
        break;
    case 2:
    case 3:
        {
            Struct150E76D0Tbl sp38;

            sp38 = D_80088A74;
            sp54.unk10 = sp38.unk0[(u32)func_150ADA20() % 3];
            sp54.unk00 = (func_150ADA68() * 260.0f) + -130.0f;
            switch (sp53) {
            case 2:
                sp54.unk14 |= 4;
                sp54.unk04 = 110.0f - arg0;
                break;
            case 3:
                sp54.unk04 = arg0 - 110.0f;
                break;
            }
        }
        break;
    }

    func_1515548C(&sp54, 0, arg7, arg8, 0, arg9, arg10);
}

typedef struct {
    /* 0x0 */ f32 unk0;
    /* 0x4 */ f32 unk4;
    /* 0x8 */ s16 unk8;
    /* 0xA */ s16 unkA;
} Struct150E7994;

extern f32 func_15142A80(f32);
extern f32 func_15142AC0(f32);
extern f32 func_15142B04(f32);
extern f32 func_15142B44(f32);

struct260 *func_150E7994(s16 arg0, f32 arg1, u8 arg2, s32 arg3) {
    struct260 *obj;
    Struct150E7994 spB8;
    Struct150E81A8Small spB0;
    f32 sp90[8];
    f32 *out;
    f32 t;
    f32 step;
    s16 i;

    if (arg0 < 2) {
        return NULL;
    }

    func_1512D748(&D_800DBFF0[D_800BE9E8], 0, 1);

    spB0.unk0 = 1;
    spB0.unk2 = (func_150ADA20() % 0xBU) + 0x1E;
    spB0.unk4 = 8;
    spB0.unk6 = -1;
    spB0.unk5 = 1;
    func_151D8868(&spB0, 0, 0xFF, 0);

    spB8.unk0 = arg1;
    spB8.unk4 = 0.0f;
    spB8.unk8 = arg0;
    spB8.unkA = 0;

    obj = func_151491F4(0x12C, -1, 0x10, 1, 0xC, (arg0 * 8) + 0x10, arg2, arg3);
    if (obj != NULL) {
        memcpy((void *)((s32)obj + 0x28), &spB8, 0xC);

        sp90[0] = -146.0f;
        sp90[1] = (func_150ADA68() * 160.0f) - 80.0f;
        sp90[2] = -50.0f;
        sp90[3] = (func_150ADA68() * 160.0f) - 80.0f;
        sp90[4] = 50.0f;
        sp90[5] = (func_150ADA68() * 160.0f) - 80.0f;
        sp90[6] = 146.0f;
        sp90[7] = (func_150ADA68() * 160.0f) - 80.0f;

        t = -1.0f;
        out = (f32 *)((s32)obj + 0x38);
        step = 3.0f / (f32)(arg0 - 1);

        for (i = 0; i < arg0; i++) {
            out[i * 2] = (func_15142A80(t) * sp90[0]) + (func_15142AC0(t) * sp90[2]) + (func_15142B04(t) * sp90[4]) + (func_15142B44(t) * sp90[6]);
            out[(i * 2) + 1] = (func_15142A80(t) * sp90[1]) + (func_15142AC0(t) * sp90[3]) + (func_15142B04(t) * sp90[5]) + (func_15142B44(t) * sp90[7]);
            t += step;
        }
    }
    return obj;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_113D60/func_150E7C9C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_113D60/func_150E7FEC.s")

void func_150E81A8(u8 arg0, s32 arg1, s32 arg2) {
    Struct150E81A8Vec sp84;
    Struct150E81A8 sp28;
    Struct150E81A8Small sp20;

    if (arg0 == 4 || arg0 == 5 || arg0 == 6 || arg0 == 7) {
        sp84 = D_800A1290[arg0];
        *(f32 *)&sp84.unk4 += 200.0f;
        func_151D3FF4(&sp84, ((u8 *)&arg1)[3], arg2);

        sp28.unk00 = 0;
        sp28.unk02 = 0xFF;
        sp28.unk04 = -0x40;
        sp28.unk06 = 0x4D;
        sp28.unk08 = 0xA;
        sp28.unk0C = 5;
        sp28.unk10 = sp84;
        sp28.unk1C = 252.0f;
        sp28.unk20 = 117.0f;
        sp28.unk24 = 308.0f;
        sp28.unk28 = 256.0f;
        sp28.unk2C = D_800A1354;
        sp28.unk30 = D_800A1358;
        sp28.unk34 = 4;
        sp28.unk38 = 7;
        sp28.unk3C = 27.0f;
        sp28.unk40 = D_800A135C;
        sp28.unk44 = D_800A1360;
        sp28.unk48 = D_800A1364;
        sp28.unk4C = 25;
        sp28.unk4E = 15;
        sp28.unk50 = 100;
        sp28.unk52 = 100;
        sp28.unk54 = 12;
        sp28.unk56 = 20;
        sp28.unk58 = 0;

        func_1514FCE8(&sp28, ((u8 *)&arg1)[3], arg2);

        sp20.unk0 = 1;
        sp20.unk2 = (func_150ADA20() % 0xBU) + 0x1E;
        sp20.unk4 = 8;
        sp20.unk6 = -1;
        sp20.unk5 = 1;
        func_151D8868(&sp20, 0, 0xFF, 0);
    }
}

void func_150E83AC(struct127 *arg0, s16 arg1, u8 arg2, s32 arg3) {
    struct {
        Struct150E81A8Vec unk0;
        f32 unkC;
    } sp40;
    struct260 *temp_v0;

    sp40.unk0 = *(Struct150E81A8Vec *)arg0;
    sp40.unkC = 0.0f;

    temp_v0 = func_15149130((arg1 == -1) ? 0x12C : arg1, -1, 0x28, -1, (arg1 == -1) ? 0 : 1, 0, (struct37 *)0x10, arg2, arg3);
    if (temp_v0 != NULL) {
        memcpy((void *)((s32)temp_v0 + 0x28), &sp40, 0x10);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_113D60/func_150E8470.s")

extern s32 func_15131828(s32, s32, s32, s32);

s32 func_150E8824(s32 arg0, s32 arg1) {
    func_15131828(arg0, arg0 + 0xAC, arg0 + 0xA8, arg0 + 0xAA);
    return 1;
}

void func_150E8854(void) {
    struct260 *temp_v0;
    f32 sp30;

    sp30 = 10.0f;

    temp_v0 = func_15149130(0x12C, -1, 0x35, -1, 0, 0, (struct37 *)0x4, 0xFF, 1);
    if (temp_v0 != NULL) {
        memcpy((void *)((s32)temp_v0 + 0x28), &sp30, 4);
    }
}

extern f32 D_800A1378;
extern void func_150E8930(void *);

void func_150E88C0(void *arg0) {
    *(f32 *)((u8 *)arg0 + 0x28) -= D_800BE9A4;
    if (*(f32 *)((u8 *)arg0 + 0x28) < 0.0f) {
        *(f32 *)((u8 *)arg0 + 0x28) = (func_150ADA68() * D_800A1378) + 201.0f;
        func_150E8930(arg0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_113D60/func_150E8930.s")

extern f32 D_800A137C;
extern f32 D_800A1380;

void func_150E8A80(void) {
    struct260 *temp_v0;
    struct {
        f32 unk0;
        f32 unk4;
        f32 unk8;
    } sp38;

    sp38.unk0 = D_800A137C;
    sp38.unk4 = D_800A1380;
    sp38.unk8 = 0.0f;

    temp_v0 = func_15149130((func_150ADA20() % 0x29U) + 0x1E, -1, 0x33, -1, 1, 0, (struct37 *)0xC, 0xFF, 1);
    if (temp_v0 != NULL) {
        memcpy((void *)((s32)temp_v0 + 0x28), &sp38, 0xC);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_113D60/func_150E8B1C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_113D60/func_150E8D5C.s")

extern f32 D_800A13B0;
extern f32 D_800A13B4;

void func_150E90DC(void) {
    struct260 *temp_v0;
    struct {
        f32 unk0;
        f32 unk4;
        f32 unk8;
    } sp38;

    sp38.unk0 = D_800A13B0;
    sp38.unk4 = D_800A13B4;
    sp38.unk8 = 0.0f;

    temp_v0 = func_15149130((func_150ADA20() % 0x1AU) + 0x5, -1, 0x36, -1, 1, 0, (struct37 *)0xC, 0xFF, 1);
    if (temp_v0 != NULL) {
        memcpy((void *)((s32)temp_v0 + 0x28), &sp38, 0xC);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_113D60/func_150E9178.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_113D60/func_150E93DC.s")

s32 func_150E971C(f32 *arg0) {
    f32 *temp_v1;
    struct157 tmp[1];

    func_151337C0(arg0);
    temp_v1 = (f32 *)((u8 *)arg0 + 0x170);
    if (arg0[15] < temp_v1[0]) {
        if ((((s32 *)temp_v1)[1] & 0x1F) == 0xA) {
            f32 temp_f2;

            temp_f2 = (func_150ADA68() * 20.0f) + 20.0f;

            tmp->unk6 = 0xB;
            tmp->unk7 = 0;
            tmp->unk0 = 0x9701;
            tmp->unk4 = 0x64;
            tmp->unk8 = 0;
            tmp->unkC = 0;
            *(u8 *)&tmp->unk10 = 0xFF;
            *(u8 *)&tmp->unk11 = 0xFF;
            *(u8 *)&tmp->unk12 = 0xFF;
            *(u8 *)&tmp->unk13 = 0xFF;
            *(u8 *)&tmp->unk14 = 0xFF;
            *(u8 *)&tmp->unk15 = 0xFF;
            tmp->unk18 = 0x3B0003;
            tmp->unk16 = 0;
            tmp->unk17 = 7;
            tmp->unk22 = 0x14;
            tmp->unk24 = 0xC;

            func_1513C73C((s32)tmp, 0, 0, (s32)(temp_v1 + 2), arg0[14], temp_v1[0] + 5.0f, arg0[16], temp_f2, temp_f2, func_150ADA20() & 0xFF, 0, 0, *(u8 *)((u8 *)arg0 + 0xC), *(u8 *)((u8 *)arg0 + 1));
        }
        return 0;
    }
    return 1;
}
