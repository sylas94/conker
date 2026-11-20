#include <ultra64.h>

#define func_150ADA20 func_150ADA20_orig
#define func_1513D668 func_1513D668_void_proto
#define func_151DA08C func_151DA08C_void_proto
#include "functions.h"
#undef func_150ADA20
#undef func_1513D668
#undef func_151DA08C
#include "variables.h"

s32 func_150ADA20(void);
s32 func_1513D668(s32 arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, s16 arg6, f32 arg7, f32 arg8, s32 arg9, s32 argA, u8 argB, s32 argC, u8 argD, s32 argE);
s32 func_151DA08C(u8 arg0, f32 arg1, f32 arg2, u8 arg3, s16 arg4, s32 arg5, void *arg6, s32 arg7, s32 arg8);
s32 func_151D9450(void *arg0p, void *arg1);
s32 func_1514672C(struct17 *arg0);
s32 func_15046C80(f32 *arg0, s32 arg1, f32 arg2, void *arg3);
u8 func_151D9534();
void func_151D9FC0(u8 arg0, f32 arg1, u8 arg2, s32 arg3, s32 arg4, u8 arg5, s32 arg6);
void func_151DAB58(u8 arg0, f32 arg1, u8 arg2, struct17 *arg3, u8 arg4, u8 arg5, s32 arg6);
s32 func_15131918(s32 arg0, s32 arg1);
struct three;
struct struct218XXX;
extern void func_15153F18(struct struct218XXX *arg0, struct three *arg1, s32 arg2, u8 arg3, s32 arg4);

extern u8 (*D_8008FCD0[])(void);
extern u8 (*D_8008FD04[])(void);
extern u8 D_800AB330[];
extern u8 D_800AB414[];
extern f32 D_800AB44C;
extern f32 D_800AB450;
extern f32 D_800AB454;
extern f32 D_800AB458;
extern f32 D_800AB45C;
extern f32 D_800AB460;
extern f32 D_800AB470;
extern f32 D_800AB474;
extern f32 D_800AB478;
extern f32 D_800AB47C;
extern f32 D_800AB4A0;
extern f32 D_800AB4A4;
extern f32 D_800AB4A8;
extern f32 D_800AB4AC;

void func_151D9014(void *arg0, f32 *arg1, u8 arg2, f32 arg3, s32 arg4, u8 arg5, f32 arg6, s32 arg7, f32 arg8, f32 arg9, u8 argA, s32 argB, s32 argC, s32 argD, u8 argE, s32 argF);

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    u8 unk18;
    u8 pad19[3];
} Struct151DA08CExtra;

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
} Struct151DA08CMain;


u8 func_151D8E20(void) {
    if ((D_800BE9F0 == 0) && (func_150A29C8(0, 0x1C) == 0)) {
        return 10;
    }
    return D_800E0A10;
}

u8 func_151D8E6C(void) {
    u8 tmp[3] = D_800AB340;
    return tmp[(func_150ADA20() % 3U)];
}

u8 func_151D8EB0(void) {
    return 117;
}

u8 func_151D8EBC(void) {
    return 29;
}

u8 func_151D8EC8(void) {
    s32 tmp;

    if (func_150ADA20() & 1) {
        tmp = 17;
    } else {
        tmp = 147;
    }
    return tmp;
}

u8 func_151D8EFC(void) {
    s32 tmp;

    if (func_150ADA20() & 1) {
        tmp = 90;
    } else {
        tmp = 91;
    }
    return tmp;
}

u8 func_151D8F30(void) {
    u8 tmp[5] = D_800AB344;
    return tmp[func_150ADA20() % 5U];
}

u8 func_151D8F7C(void) {
    s32 tmp;

    if ((func_150ADA20() & 1) != 0) {
        tmp = 102;
    } else {
        tmp = 103;
    }
    return tmp;
}

u8 func_151D8FB0(void) {
    return 149;
}

u8 func_151D8FBC(void) {
    return 159;
}

u8 func_151D8FC8(void) {
    return 179;
}

u8 func_151D8FD4(void) {
    return 117;
}

u8 func_151D8FE0(void) {
    u8 tmp[4] = D_800AB34C;
    return tmp[func_150ADA20() & 3];
}

// big struct definition
// void func_151D9014(void *arg0, f32 *arg1, u8 arg2, f32 arg3, s16 arg4, u8 arg5, f32 arg6, u8 arg7, f32 arg8, f32 arg9, u8 argA, s32 argB, u8 argC, u8 argD, u8 argE, s32 argF);
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9014.s")

s32 func_151D93F4(void *arg0, void *arg1) {
    s32 res;

    if (func_151D9450(arg0, arg1) != 0) {
        if (func_151D9534(arg0, arg1) != 0) {
            res = 1;
        } else {
            res = 0;
        }
    } else {
        res = 0;
    }
    return res;
}

struct Sub151D9450 {
    f32 unk0;
    u8 unk4;
    u8 unk5;
    s8 unk6;
    s8 unk7;
    f32 unk8;
    f32 unkC;
};

s32 func_151D9450(void *arg0p, void *arg1) {
    struct Sub151D9450 *p;

    p = (struct Sub151D9450 *)((u8 *)arg0p + 0xA8);
    if (((u8 *)arg0p)[0xC1] & 1) {
        return 1;
    }
    p->unk4 = p->unk4 + p->unk6 * D_800BE9E4;
    p->unk5 = p->unk5 + p->unk7 * D_800BE9E4;
    *(f32 *)((u8 *)arg0p + 0x38) = p->unk8 * func_151423D8((u8)(p->unk4 - 0x40)) + p->unk0;
    *(f32 *)((u8 *)arg0p + 0x3C) = p->unkC * func_151423D8((u8)(p->unk5 - 0x40)) + p->unk0;
    return 1;
}

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    u8 unk18;
    u8 unk19;
} Struct151D9534Sub;

typedef struct {
    u8 pad0[0x1];
    u8 unk1;
    u8 pad2[0xA];
    u8 unkC;
    u8 padD[0x1E];
    u8 unk2B;
    u8 pad2C[0xC];
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    f32 unk44;
    f32 unk48;
    u8 pad4C[0xC];
    f32 unk58;
    f32 unk5C;
    f32 unk60;
    f32 unk64;
    s32 unk68;
    u8 pad6C[0x14];
    f32 unk80;
    struct17 unk84;
    u8 pad90[0xD];
    u8 unk9D;
    u8 pad9E[0xA];
    Struct151D9534Sub unkA8;
} Struct151D9534;

u8 func_151D9534(Struct151D9534 *arg0, struct17 *arg1) {
    u8 sp5F;
    struct17 sp50;
    Struct151D9534Sub *sub;
    f32 sp48;
    f32 damp;

    sp5F = 1;
    if (arg0->unk44 < arg1->unk4) {
        sp50.unk0 = arg0->unk40;
        sp50.unk4 = arg1->unk4;
        sp50.unk8 = arg0->unk48;
        if (func_1514672C(&sp50) == 0) {
            return 0;
        }
        if (func_15046C80((f32 *)&sp50, 0, arg0->unk44, &arg0->unk80) != 0) {
            sp50.unk4 = arg0->unk80 + 2.0f;
            if (arg0->unkA8.unk19 & 2) {
                damp = D_800AB44C;
                arg0->unk44 = (arg0->unk3C * D_800AB450) + sp50.unk4;
                arg0->unk58 = arg0->unk58 * damp;
                arg0->unk5C = arg0->unk5C * D_800AB454;
                arg0->unk60 = arg0->unk60 * damp;
                if (fabsf(arg0->unk5C) < D_800AB458) {
                    arg0->unk58 = 0.0f;
                    arg0->unk68 &= ~6;
                    arg0->unk5C = 0.0f;
                    arg0->unk60 = 0.0f;
                    arg0->unk64 = 0.0f;
                }
            } else {
                sp5F = 0;
                sub = &arg0->unkA8;
                sp48 = (arg0->unk38 + arg0->unk3C) * 0.5f;
                if (arg0->unk9D == 3) {
                    func_151D9FC0(sub->unk18, sub->unk14 * sp48, arg0->unk2B, (s32)&arg0->unk84, (s32)&sp50, arg0->unkC, arg0->unk1);
                } else if (func_150ADA20() & 1) {
                    func_151D9B8C(sub->unk18, (sp48 * D_800AB45C) * sub->unk10, arg0->unk2B, (s32)&arg0->unk84, &sp50, 100, 0, 1, 0, arg0->unkC, arg0->unk1);
                } else {
                    func_151DAB58(sub->unk18, (sp48 * D_800AB460) * sub->unk10, arg0->unk2B, &sp50, 1, arg0->unkC, arg0->unk1);
                }
            }
        }
    }
    return sp5F;
}

u8 func_151D97A8(void) {
    s32 tmp[7] = D_800AB350;
    return tmp[func_150ADA20() % 7U];
}

u8 func_151D9820(void) {
    s32 tmp[3] = D_800AB36C;
    return tmp[func_150ADA20() % 3U];
}

u8 func_151D9878(void) {
    s32 tmp[3] = D_800AB378;
    return tmp[func_150ADA20() % 3U];
}

u8 func_151D98D0(void) {
    s32 tmp[2] = D_800AB384;
    return tmp[func_150ADA20() & 1];
}

u8 func_151D9918(void) {
    s32 tmp[2] = D_800AB38C;
    return tmp[func_150ADA20() & 1];
}

u8 func_151D9960(void) {
    s32 tmp[5] = D_800AB394;
    return tmp[func_150ADA20() % 5U];
}

u8 func_151D99C8(void) {
    s32 tmp[3] = D_800AB3A8;
    return tmp[func_150ADA20() % 3U];
}

u8 func_151D9A20(void) {
    s32 tmp[2] = D_800AB3B4;
    return tmp[func_150ADA20() & 1];
}

u8 func_151D9A68(void) {
    s32 tmp[3] = D_800AB3BC;
    return tmp[func_150ADA20() % 3U];
}

u8 func_151D9AC0(void) {
    s32 tmp[1] = D_800AB3C8;
    return tmp[0];
}

u8 func_151D9ADC(void) {
    s32 tmp[3] = D_800AB3CC;
    return tmp[func_150ADA20() % 3U];
}

u8 func_151D9B34(void) {
    s32 tmp[4] = D_800AB3D8;
    return tmp[func_150ADA20() & 3];
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9B8C.s")

typedef struct {
    s16 unk0;
    u8 pad2[2];
    f32 unk4;
    struct17 unk8;
    u8 unk14;
    u8 unk15;
    u8 unk16;
} Struct151D9EB0Sub;

void func_151D9EB0(void *arg0) {
    Struct151D9EB0Sub *sp50;
    u32 rand;
    f32 sp54;

    sp50 = (Struct151D9EB0Sub *)((u8 *)arg0 + 0x28);
    *(s16 *)((u8 *)arg0 + 0x28) = (s16)(*(s16 *)((u8 *)arg0 + 0x28) - D_800BE9E4);
    if (*(s16 *)((u8 *)arg0 + 0x28) < 0) {
        sp54 = func_150ADA68();
        rand = func_150ADA20();
        func_151D9014(&sp50->unk8, &D_800A5480, sp50->unk16, sp54 * D_800AB464 + D_800AB468,
                      (rand % 41U) + 0x23, sp50->unk14, sp50->unk4, 0, 1.0f, 1.0f, sp50->unk15, 0, 1, 0,
                      *((u8 *)arg0 + 0xC), *((u8 *)arg0 + 1));
        sp50->unk0 = (func_150ADA20() % 111U) + 0x1E;
    }
}

void func_151D9FC0(u8 arg0, f32 arg1, u8 arg2, s32 arg3, s32 arg4, u8 arg5, s32 arg6) {
    func_151DBCBC(arg0, arg1 * 0.5f, arg2, arg3, arg4, arg5, arg6);
    if ((arg0 != 5) && (arg0 != 2)) {
        func_151DA08C(arg0, arg1 * D_800AB46C, 1.0099999904632568f, arg2, 100, arg3, arg4, arg5, arg6);
    }
}

s32 func_151DA08C(u8 arg0, f32 arg1, f32 arg2, u8 arg3, s16 arg4, s32 arg5, void *arg6, s32 arg7, s32 arg8) {
    s32 ret;
    Struct151DA08CMain main;
    Struct151DA08CExtra extra;
    s32 temp_v0;
    s32 rand2;
    s32 rand1;

    extra.unk0 = 0;
    extra.unk1 = 0;
    extra.unk10 = arg1;
    extra.unk2 = (func_150ADA20() % 5U) + 2;
    extra.unk3 = (func_150ADA20() % 5U) + 2;
    extra.unk4 = ((func_150ADA68() * D_800AB470) + D_800AB474) * extra.unk10;
    extra.unk8 = ((func_150ADA68() * D_800AB478) + D_800AB47C) * extra.unk10;
    extra.unk18 = arg0;
    extra.unkC = 0.0f;
    main.unk0 = D_8008FD04[(u8)arg0]();
    main.unk2 = 3;
    main.unk8 = 0;
    main.unkC = 0;
    main.unk10 = 0;
    main.unk11 = 0;
    main.unk12 = 0;
    main.unk13 = 0xFF;
    main.unk18 = arg1;
    main.unk14 = arg1;
    main.unk1C = *(struct17 *)arg6;
    main.unk40 = 0x0CDC0008;
    main.unk34 = 1.0f;
    main.unk38 = 1.0f;
    main.unk3C = 1.0f;
    main.unk28 = 0.0f;
    main.unk2C = 0.0f;
    main.unk30 = 0.0f;
    if (arg4 == -1) {
        main.unk4 = 0x12C;
        extra.unk14 = 1.0f;
        main.unk54 = 1;
        main.unk56 = 0xFF;
    } else {
        main.unk4 = arg4;
        main.unk40 = 0x0CDC0009;
        extra.unk14 = arg2;
        if (arg4 >= 0x100) {
            main.unk54 = 0xFF;
        } else {
            main.unk54 = arg4;
        }
        if (arg4 >= 0x100) {
            main.unk56 = 1;
        } else {
            main.unk56 = 0xFF / arg4;
        }
    }
    main.unk44 = arg3;
    main.unk45 = 0xFF;
    main.unk1 = 0;
    main.unk46 = 4;
    main.unk47 = 5;
    main.unk48 = 0;
    main.unk4C = 0xFF;
    main.unk50 = 0;
    rand1 = func_150ADA20();
    rand2 = func_150ADA20();
    temp_v0 = func_150ADA20();
    ret = func_1513D668((s32)&main, 0, 0xE, 0x13, 0, (rand2 & 1) + (rand1 & 1), temp_v0 & 0xFF, 500.0f, 500.0f, 0, arg5, 0, 0x1C, 0xFF, 0);
    if (ret != 0) {
        memcpy((void *)(ret + 0x128), &extra, sizeof(extra));
    }
    return ret;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DA368.s")
// TODO when we know what arg0 is...
s32 func_151DA6A8(s32 *arg0) {
    s32 i;
    f32 *p;

    if (arg0[0x16] & 1) {
        p = (f32 *)((u8 *)arg0 + 0x128);
        i = D_800BE9E4;
        while (i--) {
            p[4] = p[5] * p[4];
        }
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DA6F8.s")
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
} Struct151DA938_elem;

typedef struct {
    u8 unk0[0x1];
    u8 unk1;
    u8 pad2[0xA];
    u8 unkC;
    u8 padD[0x20];
    s8 unk2D;
    u8 pad2E[0x66];
    Struct151DA938_elem *unk94;
    u8 *unk98;
} Struct151DA938;

typedef struct {
    f32 unk0;
    u8 pad4[0x4];
    u8 unk8;
} Struct151DA938_sub;

typedef struct {
    f32 unk0;
    u8 pad4[0x17];
    u8 unk1B;
    u8 pad1C[0x4];
    u8 unk20;
    u8 pad21[0x27];
    Struct151DA938_sub unk48;
} Struct151DA938_v1;

extern f32 D_800AB49C;

s32 func_151DA938(Struct151DA938 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5) {
    Struct151DA938_v1 *v1 = (Struct151DA938_v1 *)arg0->unk98;
    Struct151DA938_elem *base = arg0->unk94;
    struct17 sp4C;
    Struct151DA938_sub *sub = &v1->unk48;

    sp4C.unk0 = base[arg0->unk2D].unk0;
    sp4C.unk4 = arg4 + 2.0f;
    sp4C.unk8 = base[arg0->unk2D].unk8;
    if (func_150ADA20() & 1) {
        func_151D9B8C(sub->unk8, (v1->unk0 * 3.0f) * sub->unk0, v1->unk1B, arg5, &sp4C, 100, 0, 1, 0, arg0->unkC, arg0->unk1);
    } else {
        func_151DAB58(sub->unk8, (v1->unk0 * D_800AB49C) * sub->unk0, v1->unk1B, &sp4C, 1, arg0->unkC, arg0->unk1);
    }
    v1->unk20 = 4;
    return 1;
}

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
} Struct151DAA88_elem;

typedef struct {
    u8 unk0[0x1];
    u8 unk1;
    u8 pad2[0xA];
    u8 unkC;
    u8 padD[0x20];
    s8 unk2D;
    u8 pad2E[0x66];
    Struct151DAA88_elem *unk94;
    u8 *unk98;
} Struct151DAA88;

typedef struct {
    f32 unk0;
    u8 pad4[0x17];
    u8 unk1B;
    u8 pad1C[0x4];
    u8 unk20;
    u8 pad21[0x2B];
    f32 unk4C;
    u8 unk50;
} Struct151DAA88_v1;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} Vec3151DAA88;

s32 func_151DAA88(Struct151DAA88 *arg0, f32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5) {
    Struct151DAA88_v1 *v1 = (Struct151DAA88_v1 *)arg0->unk98;
    Struct151DAA88_elem *base = arg0->unk94;
    Vec3151DAA88 sp34;

    sp34.unk0 = base[arg0->unk2D].unk0;
    sp34.unk4 = arg4;
    sp34.unk8 = base[arg0->unk2D].unk8;
    func_151D9FC0(v1->unk50, v1->unk0 * 11.0f * v1->unk4C, v1->unk1B, arg5, (s32)&sp34, arg0->unkC, arg0->unk1);
    v1->unk20 = 4;
    return 1;
}
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
} Struct151DAB58Local;

typedef struct {
    u8 field_0x00;
    u8 field_0x01;
    u8 pad_0x02[0x2];
    f32 field_0x04;
    f32 field_0x08;
} Struct151DAB58Extra;

typedef struct {
    u8 field_0x00;
    u8 pad_0x01[0x3];
    s32 field_0x04;
    u8 field_0x08;
    u8 field_0x09;
    u8 field_0x0A;
    u8 field_0x0B;
    u8 field_0x0C;
    u8 field_0x0D;
    u8 pad_0x0E[0x2];
    f32 field_0x10;
    f32 field_0x14;
    f32 field_0x18;
} AxisOscillator;

typedef struct {
    u8 pad_0x00[0x4C];
    f32 field_0x4C;
    f32 field_0x50;
    f32 field_0x54;
    u8 field_0x58;
    u8 pad_0x59[0x4F];
    AxisOscillator field_0xA8;
    u8 pad_0xC4[0x4C];
    Struct151DAB58Extra field_0x110;
} AxisOscillatorOwner;

void func_151DAB58(u8 arg0, f32 arg1, u8 arg2, struct17 *arg3, u8 arg4, u8 arg5, s32 arg6) {
    void *ret;
    Struct151DAB58Local sp54;
    Struct151DAB58Extra sp48;
    s32 style;

    sp54.unk0 = D_8008FCD0[arg0]();
    sp54.unk2 = (((arg4 != 0) ? 0x3B : 0x22) << 8) + 3;
    sp54.unk4 = 0x64;
    sp54.unk12 = 0;
    sp54.unk11 = 0;
    sp54.unk10 = 0;
    sp54.unk13 = 0xFF;
    sp54.unk44 = arg2;
    sp54.unk45 = 0xFF;
    sp54.unk1C = *arg3;
    sp54.unk40 = ((D_800AB330[arg0] != 0) ? 0x40000000 : 0) | 0x0CDC0009;
    sp54.unk28 = 0.0f;
    sp54.unk2C = 0.0f;
    sp54.unk30 = 0.0f;
    sp54.unk34 = 1.0f;
    sp54.unk38 = 1.0f;
    sp54.unk3C = 1.0f;
    sp54.unk8 = 0;
    sp54.unkC = 0;
    sp54.unk18 = arg1;
    sp54.unk14 = arg1;
    sp54.unk46 = 0;
    sp54.unk47 = 7;
    sp48.field_0x00 = 0;
    sp48.field_0x01 = (func_150ADA20() % 3U) + 6;
    sp48.field_0x04 = (func_150ADA68() * D_800AB4A0) + D_800AB4A4;
    sp48.field_0x08 = (func_150ADA68() * D_800AB4A8) + D_800AB4AC;
    sp54.unk1 = 0;
    sp54.unk48 = 0;
    sp54.unk4C = 0xFF;
    sp54.unk50 = 0;
    sp54.unk54 = 0x20;
    sp54.unk56 = 7;
    if (func_150ADA20() & 1) {
        style = 1;
    } else {
        style = 0;
    }
    ret = func_1513D2F0(&sp54, (s32)&D_800A4AA0, 0, 0x14, 0, 0xE, style | 2, arg4 ? 3 : 0, arg4 ? 0xFF : 0, 0xC, arg5, arg6);
    if (ret != 0) {
        memcpy((u8 *)ret + 0x110, &sp48, sizeof(sp48));
    }
}
extern f32 D_800AB4B0;

s32 func_151DADA0(AxisOscillatorOwner *arg0) {
    f32 f0;
    Struct151DAB58Extra *p;

    p = &arg0->field_0x110;
    p->field_0x00 = p->field_0x00 + (s8)p->field_0x01 * D_800BE9E4;
    f0 = func_151423D8((u8)(p->field_0x00 - 0x40));
    arg0->field_0x4C = p->field_0x04 * f0 + 1.0f;
    arg0->field_0x50 = D_800AB4B0 - p->field_0x08 * f0;
    return 1;
}

typedef struct {
    char pad0[0x2C];
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    char pad40[0xC];
    f32 unk4C;
    f32 unk50;
    char pad54[0x6C];
    char unkC0[0x40];
    s16 *unk100[1];
} Struct151DAE28;

s16 *func_151DAE28(Struct151DAE28 *arg0, s16 arg1) {
    s16 *var_v0;
    s16 *ret;
    f32 temp_f0;
    f32 temp_f14;
    f32 temp_f2;
    f32 temp_f12;
    u8 sp37;

    func_151D5D60(arg0->unk100, arg1, 0x40, &var_v0, &sp37);
    ret = var_v0;
    if (var_v0) {
        if (sp37) {
            memcpy(arg0->unk100[arg1], arg0->unkC0, 0x40);
            memcpy(arg0->unk100[arg1] + 0x20, arg0->unkC0, 0x40);
        }
    } else {
        return 0;
    }

    temp_f0 = arg0->unk2C * arg0->unk4C;
    temp_f14 = arg0->unk30 * arg0->unk50;
    temp_f2 = D_800DD1D8[arg1] * temp_f0;
    temp_f12 = D_800DD1E8[arg1] * temp_f0;

    var_v0[3] = 0;
    var_v0[0xB] = 0;
    var_v0[0x13] = 0;
    var_v0[0x1B] = 0;
    var_v0[0] = var_v0[0x18] = arg0->unk34 + temp_f12;
    var_v0[1] = var_v0[9] = arg0->unk38;
    var_v0[2] = var_v0[0x1A] = arg0->unk3C - temp_f2;
    var_v0[8] = var_v0[0x10] = arg0->unk34 - temp_f12;
    var_v0[0x11] = var_v0[0x19] = arg0->unk38 + temp_f14;
    var_v0[0xA] = var_v0[0x12] = arg0->unk3C + temp_f2;

    return ret;
}

void func_151DB004(struct218 *arg0) {
    arg0->unk14 = (func_150ADA20() % 0x38U) + 80;
    arg0->unk15 = 0;
    arg0->unk16 = 0;
    arg0->unk18 = (func_150ADA20() % 0x2EU) + 180;
    arg0->unk19 = 0;
    arg0->unk1A = 0;
}

void func_151DB068(struct218 *arg0) {
    arg0->unk14 = arg0->unk15 = (func_150ADA20() % 0x38U) + 100;
    arg0->unk16 = 0;
    arg0->unk18 = arg0->unk19 = (func_150ADA20() % 0x2EU) + 180;
    arg0->unk1A = 0;
}

void func_151DB0CC(struct218 *arg0) {
    arg0->unk14 = (func_150ADA20() % 0x38U) + 80;
    arg0->unk15 = (func_150ADA20() % 0x38U) + 80;
    arg0->unk16 = 0;
    arg0->unk18 = (func_150ADA20() % 0x2EU) + 180;
    arg0->unk19 = (func_150ADA20() % 0x2EU) + 180;
    arg0->unk1A = 0;
}

void func_151DB15C(struct218 *arg0) {
    arg0->unk14 = (func_150ADA20() % 0x38U) + 80;
    arg0->unk15 = (func_150ADA20() % 0x38U) + 80;
    arg0->unk16 = 0;
    arg0->unk18 = (func_150ADA20() % 0x2EU) + 180;
    arg0->unk19 = (func_150ADA20() % 0x2EU) + 180;
    arg0->unk1A = 0;
}

void func_151DB1EC(struct218 *arg0) {
    arg0->unk14 = (func_150ADA20() % 0x38U) + 80;
    arg0->unk15 = (func_150ADA20() % 0x38U) + 80;
    arg0->unk16 = 0;
    arg0->unk18 = (func_150ADA20() % 0x2EU) + 180;
    arg0->unk19 = (func_150ADA20() % 0x2EU) + 180;
    arg0->unk1A = 0;
}

void func_151DB27C(struct218 *arg0) {
    arg0->unk14 = 0xFF;
    arg0->unk15 = 0xFF;
    arg0->unk16 = 0xFF;
    arg0->unk18 = 0xB4;
    arg0->unk19 = 0xC8;
    arg0->unk1A = 0xC8;
}

void func_151DB2A8(struct218 *arg0) {
    arg0->unk14 = 0;
    arg0->unk15 = 200;
    arg0->unk16 = 0;
    arg0->unk18 = 0;
    arg0->unk19 = 200;
    arg0->unk1A = 0;
}

void func_151DB2CC(struct218 *arg0) {
    arg0->unk14 = 0;
    arg0->unk15 = (func_150ADA20() % 0x38U) + 80;
    arg0->unk16 = 0;
    arg0->unk18 = 0;
    arg0->unk19 = (func_150ADA20() % 0x2EU) + 180;
    arg0->unk1A = 0;
}

void func_151DB330(struct218 *arg0) {
    arg0->unk14 = (func_150ADA20() % 0x15U) + 95;
    arg0->unk15 = (func_150ADA20() % 0x15U) + 95;
    arg0->unk16 = (func_150ADA20() % 0xBU) + 45;
    arg0->unk18 = (func_150ADA20() & 0xF) + 58;
    arg0->unk19 = (func_150ADA20() & 0xF) + 60;
    arg0->unk1A = (func_150ADA20() % 0xBU) + 25;
}

void func_151DB3D8(struct218 *arg0) {
    arg0->unk14 = 0;
    arg0->unk15 = arg0->unk16 = (func_150ADA20() % 0x38U) + 80;
    arg0->unk18 = 0;
    arg0->unk19 = arg0->unk1A = (func_150ADA20() % 0x2EU) + 180;
}

void func_151DB43C(struct218 *arg0) {
    arg0->unk14 = (func_150ADA20() % 0x38U) + 80;
    arg0->unk15 = 0;
    arg0->unk16 = (func_150ADA20() % 0x38U) + 80;
    arg0->unk18 = (func_150ADA20() % 0x2EU) + 180;
    arg0->unk19 = 0;
    arg0->unk1A = (func_150ADA20() % 0x2EU) + 180;
}

void func_151DB4CC(struct218 *arg0) {
    arg0->unk14 = (func_150ADA20() % 56U) + 200;
    arg0->unk15 = (func_150ADA20() % 56U) + 200;
    arg0->unk16 = (func_150ADA20() % 56U) + 200;
    arg0->unk18 = (func_150ADA20() % 56U) + 200;
    arg0->unk19 = (func_150ADA20() % 56U) + 200;
    arg0->unk1A = (func_150ADA20() % 56U) + 200;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DB5D0.s")

s32 func_151DB97C(AxisOscillatorOwner *arg0, s32 arg1) {
    AxisOscillator *p;
    f32 waveZ;
    f32 waveY;
    f32 waveX;

    if (!(arg0->field_0xA8.field_0x00 & 2)) {
        p = &arg0->field_0xA8;
    } else {
        func_15131918((s32)&arg0->field_0x58, arg0->field_0xA8.field_0x04);
        p = &arg0->field_0xA8;
    }

    if (p->field_0x00 & 1) {
        p->field_0x08 = p->field_0x08 + (p->field_0x0B * D_800BE9E4);
        p->field_0x09 = p->field_0x09 + (p->field_0x0C * D_800BE9E4);
        p->field_0x0A = p->field_0x0A + (p->field_0x0D * D_800BE9E4);

        waveX = func_151423D8((u8)(p->field_0x08 - 0x40));
        waveY = func_151423D8((u8)(p->field_0x09 - 0x40));
        waveZ = func_151423D8((u8)(p->field_0x0A - 0x40));
        arg0->field_0x4C = p->field_0x10 * waveX;
        arg0->field_0x50 = p->field_0x14 * waveY;
        arg0->field_0x54 = p->field_0x18 * waveZ;
    }
    return 1;
}

struct three {
    s32 a;
    s32 b;
    s32 c;
};

struct struct218XXX {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    struct three unk8;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    s16 unk2C;
    s16 unk2E;
    s16 unk30;
    s16 unk32;
    s16 unk34;
    s16 unk36;
    s16 unk38;
    s16 unk3A;
    s8 unk3C;
    u8 pad3D[0x3];
    f32 unk40;
    s16 unk44;
    s16 unk46;
    s32 unk48;
};

void func_151DBAA8(struct00 *arg0, s32 arg1, u8 arg2, u8 arg3, s32 arg4) {
    struct struct218XXX tmp;
    struct three *tmpVec;

    tmpVec = &tmp.unk8;
    *tmpVec = *(struct three *)arg0;

    tmp.unk2C = arg1;

    tmp.unk2 = 0xFF;
    tmp.unk4 = -0x40;
    tmp.unk6 = 0x2E;

    tmp.unk2E = 0;
    tmp.unk0 = 0;
    tmp.unk30 = 3;
    tmp.unk32 = 2;
    tmp.unk34 = 0x1E;
    tmp.unk36 = 0x1E;
    tmp.unk38 = 0x9B;
    tmp.unk14 = 5.5f;

    tmp.unk18 = D_800AB4C0;
    tmp.unk1C = D_800AB4C4;
    tmp.unk20 = D_800AB4C8;
    tmp.unk24 = 10.0f;
    tmp.unk28 = D_800AB4CC;

    tmp.unk3A = 0x64;
    tmp.unk44 = 0x10;
    tmp.unk46 = 0xF;
    tmp.unk48 = 0;
    tmp.unk40 = 0.5f;

    tmp.unk3C = arg2;

    func_15153F18(&tmp, tmpVec, 0, arg3, arg4);
}

// typedef struct {
//     s16 unk0; // sp24
//     s16 unk2;
//     s16 unk4;
//     s16 unk6;
//     // s32 unk8[3]; // sp2C
//     s32 unk8;
//     s32 unkC;
//     s32 unk10;
//     f32 unk14;
//     f32 unk18;
//     f32 unk1C;
//     f32 unk20; // sp44
//     f32 unk24;
//     f32 unk28;
//     s16 unk2C; // sp50
//     s16 unk2E;
//     s16 unk30; // sp54
//     s16 unk32;
//     s16 unk34;
//     s16 unk36;
//     s16 unk38;
//     s16 unk3A;
//     s8  unk3C; // sp60
//     u8  pad3D[0x3];
//     f32 unk40; // sp64
//     s16 unk44;
//     s16 unk46;
//     s32 unk48;
// } struct218XXX;
//
// void func_15153F18(s32, s32, s32, u8, s32);
// void func_151DBAA8(struct00 *arg0, s32 arg1, u8 arg2, u8 arg3, s32 arg4) {
//
//     struct218XXX tmp;
//
//     // tmp.unk8[0] = arg0->unk0;
//     // tmp.unk8[1] = arg0->unk4;
//     // tmp.unk8[2] = arg0->unk8;
//
//     tmp.unk2C = arg1;
//     tmp.unk3C = arg2;
//
//     tmp.unk0 = 0;
//     tmp.unk2 = 0xFF;
//     tmp.unk4 = -0x40;
//     tmp.unk6 = 0x2E;
//     tmp.unk8 = arg0->unk0;
//     tmp.unkC = arg0->unk4;
//     tmp.unk10 = arg0->unk8;
//
//     tmp.unk30 = 3;
//     tmp.unk2E = 0;
//     tmp.unk32 = 2;
//     tmp.unk34 = 0x1E;
//     tmp.unk36 = 0x1E;
//     tmp.unk38 = 0x9B;
//     tmp.unk14 = 5.5f;
//
//     tmp.unk18 = D_800AB4C0;
//     tmp.unk1C = D_800AB4C4;
//     tmp.unk20 = D_800AB4C8;
//     tmp.unk24 = 10.0f;
//     tmp.unk28 = D_800AB4CC;
//
//     tmp.unk3A = 0x64;
//     tmp.unk44 = 0x10;
//     tmp.unk46 = 0xF;
//     tmp.unk48 = 0;
//     tmp.unk40 = 0.5f;
//
//     func_15153F18(&tmp, &tmp.unk8, 0, arg3, arg4);
// }

void func_151DBBD4(struct17 *arg0, s32 arg1, u8 *arg2, u8 arg3, s32 arg4) {
    struct17 tmp;
    struct217 tmp2;

    tmp.unk0 = arg0->unk0;
    tmp.unk4 = arg0->unk4 + 5.0f;
    tmp.unk8 = arg0->unk8;

    tmp2.unkF = *arg2;
    tmp2.unk0 = func_150ADA68();
    tmp2.unk4 = func_150ADA20();

    func_151D9B8C(tmp2.unkF, (tmp2.unk0 * 25.0f) + 10.0f, ((tmp2.unk4 % 0x38U) + 200), arg1 + 4, &tmp, (func_150ADA20() % 0x97U) + 150, 0, 1, 0, arg3, arg4);
}

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s8 unk6;
    /* 0x07 */ s8 unk7;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 unk13;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ s8 unk16;
    /* 0x17 */ s8 unk17;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ u8 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ u16 unk24;
} Struct151DBCBC;

void func_151DBCBC(u8 arg0, f32 arg1, s16 arg2, s32 arg3, void *arg4, u8 arg5, s32 arg6) {
    Struct151DBCBC tmp;
    s32 r3;
    s32 r2;
    s32 r1;

    tmp.unk6 = 0x38;
    tmp.unkC = 0x8000;
    tmp.unk0 = 0x67B02;
    tmp.unk4 = 0x12C;
    tmp.unk8 = 0;
    tmp.unk10 = arg2;
    tmp.unk11 = 0xFF;
    tmp.unk12 = D_800AB414[arg0 * 3];
    tmp.unk13 = D_800AB414[arg0 * 3 + 1];
    tmp.unk14 = D_800AB414[arg0 * 3 + 2];
    tmp.unk15 = 0xFF;
    tmp.unk18 = 0x440001;
    tmp.unk7 = 0;
    tmp.unk16 = 0;
    tmp.unk17 = 6;
    tmp.unk22 = 1;
    tmp.unk24 = 0xFF;
    tmp.unk20 = 0xFF;
    tmp.unk1C = 0;
    if (arg3 != 0) {
        r1 = func_150ADA20();
        r2 = func_150ADA20();
        r3 = func_150ADA20();
        func_1513C73C((s32)&tmp, 0, 0, arg3, ((struct17 *)arg4)->unk0, ((struct17 *)arg4)->unk4, ((struct17 *)arg4)->unk8, arg1, arg1,
                      r1 & 0xFF, ((r3 & 1) << 1) + (r2 & 1), 0, arg5, arg6);
    } else {
        func_1513C5B0((s32)&tmp, 0, 0, 0, ((struct17 *)arg4)->unk0, ((struct17 *)arg4)->unk4, ((struct17 *)arg4)->unk8, arg1, arg1, 0, 0, 0, arg5, arg6);
    }
}


struct Struct151DBE80 {
    s8 unk0;
    s8 unk1;
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
    s8 unk46;
    s8 unk47;
    s32 unk48;
    u8 unk4C;
    u8 pad4D[3];
    s32 unk50;
    s16 unk54;
    u16 unk56;
};

void func_151DBE80(u8 arg0, f32 arg1, f32 arg2, s16 arg3, struct17 *arg4, s32 arg5, u8 arg6, u8 arg7, u8 arg8, s32 arg9) {
    struct Struct151DBE80 tmp;

    tmp.unk0 = 0x38;
    tmp.unk2 = ((arg7 != 0) ? 2 : 1) + 0x440000;
    tmp.unk4 = arg3;
    tmp.unk8 = 0;
    tmp.unkC = 0x4000;
    tmp.unk10 = D_800AB414[arg0 * 3];
    tmp.unk14 = 1.0f;
    tmp.unk18 = 1.0f;
    tmp.unk11 = D_800AB414[arg0 * 3 + 1];
    tmp.unk12 = D_800AB414[arg0 * 3 + 2];
    tmp.unk13 = 0xFF;

    *(struct three *)&tmp.unk1C = *(struct three *)arg4;

    tmp.unk34 = arg2;
    tmp.unk40 = 0x466C0001;
    tmp.unk44 = arg6;
    tmp.unk45 = 0xFF;
    tmp.unk1 = 0;
    tmp.unk46 = 0;
    tmp.unk47 = 6;
    tmp.unk48 = 0;
    tmp.unk4C = 0xFF;
    tmp.unk50 = 0;
    tmp.unk54 = 1;
    tmp.unk56 = 0xFF;
    tmp.unk38 = 1.0f;
    tmp.unk3C = 1.0f;
    tmp.unk28 = 0.0f;
    tmp.unk2C = 0.0f;
    tmp.unk30 = 0.0f;

    func_1513D668((s32)&tmp, 0, 0xB, 0x11, 0, (func_150ADA20() & 1) + (func_150ADA20() & 1), (s16)(func_150ADA20() & 0xFF), arg1, arg1, 0, arg5, 0, 0, arg8, arg9);
}

/* Particle descriptor passed to func_15130280 (0x70 bytes). */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u8 unk16;
    /* 0x17 */ u8 unk17;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ u8 unk1A;
    /* 0x1B */ u8 unk1B;
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 unk1D;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ struct17 pos;
    /* 0x3C */ struct17 unk3C;
    /* 0x48 */ struct17 vel;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ u32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ u8 unk60;
    /* 0x61 */ u8 unk61;
    /* 0x62 */ s8 unk62;
    /* 0x63 */ s8 unk63;
    /* 0x64 */ s8 unk64;
    /* 0x65 */ u8 unk65;
    /* 0x66 */ u8 unk66;
    /* 0x67 */ u8 pad67;
    /* 0x68 */ s16 unk68;
    /* 0x6A */ u8 pad6A[2];
    /* 0x6C */ f32 unk6C;
} ParticleDesc151DC034; /* 0x70 */

extern void *func_15130280(void *, u8, s32, s32, u8, s32);
extern u8 D_800AB320[];

void func_151DC034(struct17 *arg0, f32 arg1, u8 arg2, s16 arg3, u8 arg4, u8 arg5, s32 arg6) {
    ParticleDesc151DC034 spawn;
    s32 flags3;
    s32 flags2;
    s32 flags;

    spawn.unk1D = D_800AB320[arg4];
    spawn.unk8 = 0x4403;
    spawn.unk0 = 0x200005;
    spawn.unk4 = 0x9F0600;
    spawn.unkA = arg3;
    spawn.unkC = 0;
    spawn.unk10 = 0;
    spawn.unk14 = 0xFF;
    spawn.unk15 = 0xFF;
    spawn.unk16 = 0xFF;
    spawn.unk17 = 0xFF;
    spawn.unk18 = 0xFF;
    spawn.unk19 = 0xFF;
    spawn.unk1A = 0xFF;
    spawn.unk1B = arg2;
    spawn.unk1C = 0xFF;
    spawn.unk28 = spawn.unk2C = arg1;
    spawn.pos = *arg0;
    spawn.unk3C = *(struct17 *)&D_800A5480;
    spawn.vel = *(struct17 *)&D_800A5480;
    spawn.unk54 = 0.0f;
    spawn.unk1E = 4;
    spawn.unk20 = 0x3F;
    spawn.unk22 = 1;
    spawn.unk24 = 1.0f;
    flags = (func_150ADA20() & 1) ? 0x80 : 0;
    flags2 = (func_150ADA20() & 1) ? 0x40 : 0;
    flags3 = D_800AB330[arg4] ? 0x800000 : 0;
    spawn.unk58 = flags3 | 1 | flags2 | flags | 0x200 | 0x4000 | 0x8000 | 0x10000;
    spawn.unk60 = 6;
    spawn.unk61 = 8;
    spawn.unk62 = -1;
    spawn.unk63 = -1;
    spawn.unk64 = -1;
    spawn.unk65 = 0;
    spawn.unk5C = 0;
    spawn.unk66 = 0xFF;
    spawn.unk68 = 1000;
    spawn.unk6C = 1000.0f;
    func_15130280(&spawn, 1, 0, 0, arg5, arg6);
}
typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ struct three unk8;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ u8 unk2C;
    /* 0x2D */ u8 unk2D;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ s8 unk38;
    /* 0x39 */ u8 unk39;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ s8 unk40;
    /* 0x44 */ f32 unk44;
} Struct151DC260;

void func_15150178(Struct151DC260 *arg0, struct three *arg1, s32 arg2, u8 arg3, s32 arg4);

extern f32 D_800AB4D0;
extern f32 D_800AB4D4;
extern f32 D_800AB4D8;
extern f32 D_800AB4DC;
extern f32 D_800AB4E0;

void func_151DC260(struct00 *arg0, s32 arg1, u8 arg2, u8 arg3, s32 arg4) {
    struct struct218XXX tmp2;

    tmp2.unk8 = *(struct three *)arg0;
    tmp2.unk2C = 0xA;
    tmp2.unk2E = 0xA;
    tmp2.unk2 = 0xFF;
    tmp2.unk4 = -0x40;
    tmp2.unk0 = 0;
    tmp2.unk6 = 0x28;
    tmp2.unk30 = 3;
    tmp2.unk32 = 1;
    tmp2.unk34 = 0x3C;
    tmp2.unk36 = 0x28;
    tmp2.unk14 = 3.0f;
    tmp2.unk18 = 4.0f;
    tmp2.unk1C = D_800AB4D0;
    tmp2.unk20 = D_800AB4D4;
    tmp2.unk24 = 12.0f;
    tmp2.unk28 = 11.0f;
    tmp2.unk38 = 0x64;
    tmp2.unk3A = 0x64;
    tmp2.unk44 = 0x10;
    tmp2.unk46 = 0xF;
    tmp2.unk48 = 0;
    tmp2.unk40 = 1.0f;
    tmp2.unk3C = arg2;
    func_15153F18(&tmp2, &tmp2.unk8, arg1, arg3, arg4);

    {
        Struct151DC260 tmp;

        tmp.unk8 = *(struct three *)arg0;
        tmp.unk14 = 0xC;
        tmp.unk16 = 6;
        tmp.unk2 = 0xFF;
        tmp.unk0 = 0;
        tmp.unk4 = -0x40;
        tmp.unk6 = 0x24;
        tmp.unk20 = 0x23;
        tmp.unk22 = 0xF;
        tmp.unk18 = 6.0f;
        tmp.unk1C = 8.0f;
        tmp.unk24 = D_800AB4D8;
        tmp.unk28 = D_800AB4DC;
        tmp.unk2C = 0x9B;
        tmp.unk2D = 0x64;
        tmp.unk30 = 123.0f;
        tmp.unk34 = 134.0f;
        tmp.unk38 = 1;
        tmp.unk39 = arg2;
        tmp.unk3C = D_800AB4E0;
        tmp.unk40 = 1;
        tmp.unk44 = 0.0f;
        func_15150178(&tmp, &tmp.unk8, arg1, arg3, arg4);
    }
}
void func_151DC484(struct00 *arg0, s32 arg1, u8 arg2, u8 arg3, s32 arg4) {
    struct struct218XXX tmp2;

    tmp2.unk8 = *(struct three *)arg0;
    tmp2.unk2C = 8;
    tmp2.unk2E = 6;
    tmp2.unk2 = 0xFF;
    tmp2.unk4 = -0x40;
    tmp2.unk0 = 0;
    tmp2.unk6 = 0x28;
    tmp2.unk30 = 3;
    tmp2.unk32 = 0;
    tmp2.unk34 = 0x3C;
    tmp2.unk36 = 0x28;
    tmp2.unk14 = 3.0f;
    tmp2.unk18 = 2.0f;
    tmp2.unk1C = D_800AB4E4;
    tmp2.unk20 = D_800AB4E8;
    tmp2.unk24 = 8.0f;
    tmp2.unk28 = 5.0f;
    tmp2.unk38 = 0x64;
    tmp2.unk3A = 0x64;
    tmp2.unk44 = 0x10;
    tmp2.unk46 = 0xF;
    tmp2.unk48 = 0;
    tmp2.unk40 = 1.0f;
    tmp2.unk3C = arg2;
    func_15153F18(&tmp2, &tmp2.unk8, arg1, arg3, arg4);

    {
        Struct151DC260 tmp;

        tmp.unk8 = *(struct three *)arg0;
        tmp.unk14 = 0xC;
        tmp.unk16 = 6;
        tmp.unk2 = 0xFF;
        tmp.unk0 = 0;
        tmp.unk4 = -0x40;
        tmp.unk6 = 0x1A;
        tmp.unk20 = 0x23;
        tmp.unk22 = 0xF;
        tmp.unk18 = 7.0f;
        tmp.unk1C = 3.0f;
        tmp.unk24 = D_800AB4EC;
        tmp.unk28 = D_800AB4F0;
        tmp.unk2C = 0x9B;
        tmp.unk2D = 0x64;
        tmp.unk30 = 59.0f;
        tmp.unk34 = 59.0f;
        tmp.unk38 = 1;
        tmp.unk39 = arg2;
        tmp.unk3C = D_800AB4F4;
        tmp.unk40 = 1;
        tmp.unk44 = 0.0f;
        func_15150178(&tmp, &tmp.unk8, arg1, arg3, arg4);
    }
}
