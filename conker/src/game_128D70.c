#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_800A1EB0;
extern f32 D_800A1EB4;
extern f32 D_800A1EB8;
extern f32 D_800A1EBC;
extern f32 D_800A1EC0;
extern f32 D_800A1EC4;
extern f32 D_800A1EC8;
extern f32 D_800A1ECC;
extern f32 D_800A1ED0;
extern struct260 *func_15164780(void *, s32, u8, s32);

typedef struct {
    u8 pad0[0x23D];
    u8 unk23D;
} Sub318_150FC438;

typedef struct {
    u8 pad0[0x3B];
    u8 unk3B;
    u8 pad3C[0x2DC];
    Sub318_150FC438 *unk318;
} Arg1_150FC438;

typedef struct {
    u8 pad0[0x3B];
    u8 unk3B;
} Arg0_150FC438;

typedef struct {
    s32 unk0;
    u8  unk4;
    u8  pad5[3];
    f32 unk8;
    u8  unkC;
    u8  unkD;
    u8  padE[2];
    s32 unk10;
    s16 unk14;
    s8  unk16;
    u8  pad17;
    Arg1_150FC438 *unk18;
    u8  unk1C;
    u8  unk1D;
    u8  pad1E[2];
} Data_150FC438;

typedef union {
    s64 align;
    struct {
        u8  unk0;
        s8  unk1;
        s8  unk2;
        u8  pad3;
        s16 unk4;
        u8  unk6;
        u8  pad7;
        f32 unk8;
        f32 unkC;
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
    } f;
} Child_150FC438;

#pragma GLOBAL_ASM("asm/nonmatchings/game_128D70/func_150FB8C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_128D70/func_150FC368.s")

void func_150FC438(Arg0_150FC438 *arg0, Arg1_150FC438 *arg1, u8 arg2, u8 arg3) {
    Data_150FC438 sp80;
    struct260 *temp_v0;
    s32 dest;
    Child_150FC438 sp40;

    sp80.unk0 = (s32)arg0;
    sp80.unk4 = arg0->unk3B;
    sp80.unk8 = 0.0f;
    sp80.unkC = 0;
    sp80.unkD = arg2;
    sp80.unk10 = 0;
    sp80.unk14 = 0;
    sp80.unk1D = arg3;
    if (arg1) {
        if (arg1->unk318) {
            sp80.unk16 = arg1->unk318->unk23D;
            goto block_150FC438_1;
        }
    }
    sp80.unk16 = -1;
block_150FC438_1:
    sp80.unk18 = arg1;
    if (arg1) {
        sp80.unk1C = arg1->unk3B;
    } else {
        sp80.unk1C = 0xFF;
    }

    temp_v0 = func_15149130(0x12C, -1, 0x27, -1, 0, 0x25, (struct37 *)0x20, 0xFF, 1);
    if (temp_v0 != 0) {
        dest = (s32)temp_v0 + 0x28;
        memcpy(dest, &sp80, sizeof(sp80));
        if (arg1) {
            if (arg1->unk318) {
                sp40.f.unk0 = 4;
                sp40.f.unk1 = -1;
                sp40.f.unk2 = -1;
                sp40.f.unk4 = 0x12C;
                sp40.f.unk6 = arg1->unk318->unk23D;
                sp40.f.unk8 = 12.0f;
                sp40.f.unkC = 20.0f;
                sp40.f.unk10 = 19.0f;
                sp40.f.unk14 = D_800A1EB0;
                sp40.f.unk18 = D_800A1EB4;
                sp40.f.unk1C = D_800A1EB8;
                sp40.f.unk20 = D_800A1EBC;
                sp40.f.unk24 = D_800A1EC0;
                sp40.f.unk28 = D_800A1EC4;
                sp40.f.unk2C = D_800A1EC8;
                sp40.f.unk30 = D_800A1ECC;
                sp40.f.unk34 = D_800A1ED0;
                *(struct260 **)(dest + 0x10) = func_15164780(&sp40, 0, 0xFF, 1);
            }
        }
    }
}

typedef struct {
    u8  pad0[0x1AA];
    s16 unk1AA;
} Sub31C_150FC614;

typedef struct {
    u8  pad0[0x31C];
    Sub31C_150FC614 *unk31C;
} Holder_150FC614;

typedef struct {
    s32 unk0;
    u8  unk4;
    u8  pad5[0x36];
    u8  unk3B;
    u8  pad3C[0x48];
    u16 unk84;
} Owner_150FC614;

typedef struct {
    Owner_150FC614 *unk0;
    u8  unk4;
    u8  pad5[3];
    f32 unk8;
    u8  unkC;
    u8  unkD;
    u8  padE[2];
    s32 unk10;
    s16 unk14;
    s8  unk16;
    u8  pad17;
    Holder_150FC614 *unk18;
    u8  unk1C;
    u8  unk1D;
    u8  pad1E[2];
} Data_150FC614;

typedef struct {
    u8  pad0;
    u8  unk1;
    u8  pad2[0xA];
    u8  unkC;
    u8  padD;
    s16 unkE;
    u8  pad10[0x18];
    Data_150FC614 unk28;
} Entity_150FC614;

typedef struct {
    u8  unk0;
    u8  unk1;
    s16 unk2;
    u8  unk4;
    u8  unk5;
    s8  unk6;
    u8  unk7;
} Spark_150FC614;

extern void func_150FB8C0(Owner_150FC614 *arg0, u8 arg1, f32 arg2, u8 arg3, u8 arg4, u8 arg5);
extern void func_151D8868(void *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_150FC614(Entity_150FC614 *arg0) {
    Data_150FC614 *d;
    Owner_150FC614 *owner;
    Spark_150FC614 sp50;

    d = &arg0->unk28;
    owner = d->unk0;
    if ((owner->unk0 == 0) || (owner->unk4 == 0xFF) || (owner->unk3B != d->unk4) || (D_800C35EA == 1)) {
        arg0->unkE = -1;
        return;
    }
    if (owner->unk84 != d->unk1D) {
        arg0->unkE = -1;
        return;
    }

    d->unk8 -= D_800BE9A4;
    while (d->unk8 < 0.0f) {
        func_150FB8C0(owner, d->unkC, -d->unk8, d->unkD, arg0->unkC, arg0->unk1);
        d->unkC ^= 1;
        if (d->unk18 != NULL) {
            if (d->unk18->unk31C != NULL) {
                d->unk18->unk31C->unk1AA++;
            }
        }
        d->unk8 += 4.0f + (func_150ADA68() * 4.0f);
    }

    if (d->unk16 == -1) {
        return;
    }
    d->unk14 -= D_800BE9E4;
    if (d->unk14 < 0) {
        sp50.unk0 = 1;
        func_150ADA20();
        sp50.unk2 = 0x1E;
        sp50.unk5 = 1 << d->unk16;
        sp50.unk4 = (func_150ADA20() % 6U) + 3;
        sp50.unk6 = -1;
        func_151D8868(&sp50, 0, arg0->unkC, arg0->unk1);
        func_150ADA20();
        d->unk14 = 250;
    }
}

typedef struct {
    s32 unk0;
    u8  unk4;
    u8  pad5[0x13];
    s32 unk18;
    u8  unk1C;
} SubA_150FC818;

typedef struct {
    s32 unk0;
    union { s32 w4; u8 b4; } u4;
    u8  unk8;
    u8  unk9;
} ArgB_150FC818;

void func_150FC818(void *arg0, s32 arg1, u8 arg2) {
    ArgB_150FC818 *b = (ArgB_150FC818 *)arg1;
    SubA_150FC818 *a = (SubA_150FC818 *)((u8 *)arg0 + 0x28);
    s32 bu0;
    s32 bu0b;
    s32 au0;

    if (arg2 == 0) {
        bu0 = b->unk0;
        au0 = a->unk0;
        if ((au0 == bu0) || (a->unk4 == b->u4.b4)) {
            func_1516972C((struct102 *)arg0);
        } else if (a->unk18 != 0) {
            if ((bu0 == a->unk18) || (a->unk1C == b->u4.b4)) {
                func_1516972C((struct102 *)arg0);
            }
        }
    } else if (arg2 == 0x2D) {
        bu0b = b->unk0;
        if (bu0b == a->unk0) {
            a->unk0 = b->u4.w4;
            a->unk4 = b->unk9;
        } else if (a->unk0 == b->u4.w4) {
            a->unk0 = bu0b;
            a->unk4 = b->unk8;
        } else if (a->unk18 != 0) {
            if (bu0b == a->unk18) {
                a->unk18 = b->u4.w4;
                a->unk1C = b->unk9;
            } else if (a->unk18 == b->u4.w4) {
                a->unk18 = bu0b;
                a->unk1C = b->unk8;
            }
        }
    }
}

s32 func_150FC930(struct260 *arg0, s32 arg1, s32 arg2) {
    u8 v = *((u8 *)arg0 + 4);
    if (v == 0x12 || v == 0x23 || v == 0x73 || v == 0x8A) {
        return 0;
    }
    return 1;
}

void func_150FC974(struct260 *arg0) {
    s32 *p = (s32 *)((u8 *)arg0 + 0x38);
    if (*p != 0) {
        func_1516972C((struct102 *)*p);
    }
}

extern void func_150FC974(struct260 *);

void func_150FC9A4(struct260 *arg0) {
    func_150FC974(arg0);
    func_1514933C(arg0);
}

extern void func_15149368(struct260 *);

void func_150FC9D0(struct260 *arg0) {
    func_150FC974(arg0);
    func_15149368(arg0);
}
