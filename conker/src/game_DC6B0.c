#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern s32 *D_800DBF94;
extern s32 func_151149AC(u32);
extern s32 func_1505D024(struct127 *, s32, u16, s32);
extern void func_150A7960(f32 *, f32, f32, f32, f32 *, f32 *, f32 *);
extern void func_150E1AB0(s32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, u16, s32, s32, s16, s16, s32, u8, s16, s32, s32, u8, f32, f32, f32, f32, f32, f32);
extern void func_150E2DB4(struct127 *, u8, s16, s32, f32, f32, f32, f32, f32, f32, s16, s16, u16, u8);
extern void func_15179008(s32);
extern void func_15131828(void *, void *, void *, void *);
extern void func_15131958(void *, s32, void *);

typedef struct {
    char pad0[0xC];
    s32 unkC;
} struct150AF6E4;

void func_150AF200(s32 arg0, s32 arg1) {
    struct131 *temp;
    s32 idx;

    if (D_800CC3D4[0] != 0) {
        return;
    }

    temp = (struct131 *)func_151149AC(arg0 & 0xFF);
    idx = temp - D_800DBEF4;
    if (D_800DBF94[idx] & 1) {
        func_1505D024(&D_800CC2D0[0], 0x3F, 0x6E00, -1);
        return;
    }

    temp = (struct131 *)func_151149AC((u8)arg1);
    idx = temp - D_800DBEF4;
    if (D_800DBF94[idx] & 1) {
        func_1505D024(&D_800CC2D0[0], 0x3F, 0xEE00, -1);
    }
}

extern void func_151CF898(void *, f32, f32);

void func_150AF2E0(void *arg0, s16 *arg1) {
    func_151CF898(arg0, (f32)(arg1[4] + arg1[1]), (f32)arg1[1]);
}

typedef struct {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    s32 unkC;
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
    struct17 unk30;
    struct17 unk3C;
    struct17 unk48;
    f32 unk54;
    u32 unk58;
    s32 unk5C;
    u8 unk60;
    u8 unk61;
    u8 unk62;
    s8 unk63;
    s8 unk64;
    u8 unk65;
    u8 unk66;
    u8 pad67[9];
} Spawn15130280;

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} Extra150AF328;

typedef struct {
    struct17 pos;
    f32 accum;
} Sub150AF328;

typedef struct {
    u8 pad0;
    u8 unk1;
    u8 pad2[0xA];
    u8 unkC;
    u8 padD[0x1B];
    Sub150AF328 unk28;
} Obj150AF328;

extern void *func_15130280(void *, u8, s32, s32, u8, s32);

void func_150AF328(Obj150AF328 *arg0) {
    Sub150AF328 *sub;

    sub = &arg0->unk28;
    sub->accum += (1352.0f + func_150ADA68() * 1698.0f) * 0.0001f * D_800BE9A4;
    if (sub->accum > 1.0f) {
        Spawn15130280 spawn;
        Extra150AF328 extra;
        void *ret;

        extra.unkC = 0.9704700112f;
        spawn.unk1D = 0x6C;
        spawn.unk8 = 0x5103;
        spawn.unk0 = 0x200005;
        spawn.unk1E = 0x46;
        spawn.unk20 = 3;
        spawn.unk58 = 0x80DE07;
        spawn.unk60 = 8;
        spawn.unk61 = 6;
        spawn.unk62 = 0x16;
        extra.unk0 = 0;
        extra.unk1 = 0;
        spawn.unk4 = 0;
        spawn.unkC = 0;
        spawn.unk10 = 0;
        spawn.unk63 = -1;
        spawn.unk64 = -1;
        spawn.unk65 = 0;
        spawn.unk22 = 0x46;
        spawn.unk14 = 0xC7;
        spawn.unk15 = 0x78;
        spawn.unk16 = 8;
        spawn.unk17 = 0xFF;
        spawn.unk18 = 0x30;
        spawn.unk19 = 0xE;
        spawn.unk1A = 0;
        spawn.unk1C = 0xFF;
        spawn.unk24 = 1.021028996f;
        spawn.unk30 = sub->pos;
        spawn.unk3C.unk0 = 0.0f;
        spawn.unk3C.unk4 = 0.0f;
        spawn.unk3C.unk8 = 0.0f;
        spawn.unk48.unk0 = 0.0f;
        spawn.unk48.unk4 = 0.0f;
        spawn.unk48.unk8 = 0.0f;
        do {
            extra.unk2 = func_150ADA20() % 5U + 4;
            extra.unk3 = func_150ADA20() % 5U + 4;
            extra.unk4 = func_150ADA68() * 11.0f;
            extra.unk8 = func_150ADA68() * 11.0f;
            spawn.unk54 = func_150ADA68() * 0.172f + 0.09800000489f;
            spawn.unk58 &= ~0xC0;
            spawn.unk58 |= ((func_150ADA20() & 1) ? 0x40 : 0) | ((func_150ADA20() & 1) ? 0x80 : 0);
            spawn.unk1B = func_150ADA20() % 101U + 100;
            spawn.unkA = func_150ADA20() % 51U + 80;
            spawn.unk28 = spawn.unk2C = func_150ADA68() * 71.0f + 80.0f;
            ret = func_15130280(&spawn, 0, 0, 0x10, arg0->unkC, arg0->unk1);
            if (ret != NULL) {
                memcpy((u8 *)ret + 0xA8, &extra, sizeof(extra));
            }
            sub->accum -= 1.0f;
        } while (sub->accum > 1.0f);
    }
}

s32 func_150AF6E4(u8 *arg0, s32 arg1) {
    struct150AF6E4 *temp_a2;

    temp_a2 = (struct150AF6E4 *)(arg0 + 0xA8);
    func_15131828(arg0, arg0 + 0xAC, temp_a2, arg0 + 0xAA);
    func_15131958(arg0 + 0x58, temp_a2->unkC, temp_a2);
    return 1;
}

extern void func_1515FF74(void *, s32, u8, s32);

struct sp18 {
    s8 unk0;
    s8 unk1;
    s8 unk2;
    s8 pad3;
    s16 unk4;
    s8 unk6;
};

void func_150AF738(s16 arg0, u8 arg1, s32 arg2) {
    struct sp18 sp18;

    sp18.unk0 = 1;
    sp18.unk1 = -1;
    sp18.unk2 = 2;
    sp18.unk4 = arg0;
    sp18.unk6 = 0;
    func_1515FF74(&sp18, 0, arg1, arg2);
}

extern void func_150B1DB0(void *, void *);

void func_150AF790(void *arg0, u8 *arg1) {
    func_150B1DB0(arg1, arg1 + 0x1ECC0);
}

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 pad11;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ u8 unk1A;
    /* 0x1B */ u8 unk1B;
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 unk1D;
    /* 0x1E */ u8 unk1E;
    /* 0x1F */ u8 unk1F;
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 unk21;
    /* 0x22 */ u8 unk22;
    /* 0x23 */ u8 unk23;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ u8 unk40;
    /* 0x41 */ u8 unk41;
    /* 0x42 */ u8 pad42[2];
    /* 0x44 */ u8 unk44;
    /* 0x45 */ u8 pad45[3];
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 unk54;
} Emitter150AF7C4;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} Extra150AF7C4;

typedef struct {
    s16 unk0;
    s16 unk2;
} Timers150AF7C4;

typedef struct {
    u8 pad0;
    u8 unk1;
    u8 pad2[0xA];
    u8 unkC;
    u8 padD;
    s16 unkE;
    u8 pad10[0x18];
    Timers150AF7C4 unk28;
} Obj150AF7C4;

extern void *func_1515548C(Emitter150AF7C4 *, s32, s32, s32, s32, u8, s32);
extern u8 func_151D8E6C(void);

void func_150AF7C4(Obj150AF7C4 *arg0) {
    Timers150AF7C4 *p;

    p = &arg0->unk28;
    arg0->unk28.unk0 -= D_800BE9E4;
    if (arg0->unk28.unk0 < 0) {
        Emitter150AF7C4 e;
        Extra150AF7C4 x;
        void *ret;

        x.unk0 = func_150ADA68() * 280.0f + -140.0f;
        x.unk4 = func_150ADA68() * 50.0f;
        x.unk8 = func_150ADA68() * 3.1415927f * 2.0f;
        x.unkC = func_150ADA68() * 0.268f;
        e.unk0 = 0.0f;
        e.unk4 = 0.0f;
        func_150ADA68();
        e.unk8 = 1.0f;
        e.unkC = 115.0f;
        e.unk10 = 0xFF;
        e.unk12 = func_150ADA20() % 71U + 20;
        if (arg0->unkE < e.unk12) {
            e.unk12 = arg0->unkE;
        }
        e.unk14 = 0x21;
        e.unk16 = 1;
        e.unk18 = 0xFF;
        e.unk1A = 0;
        e.unk1B = 0xFF;
        e.unk1C = 0xFF;
        e.unk1D = 0xFF;
        e.unk1E = func_150ADA20() % 71U + 40;
        e.unk1F = 0xFF;
        e.unk20 = 0xFF;
        e.unk21 = 0xFF;
        e.unk22 = 0xFF;
        e.unk23 = 0xFF;
        e.unk24 = 0;
        e.unk28 = 0x200004;
        e.unk2C = 0x1F0601;
        e.unk30 = 0x19;
        e.unk34 = 0x54;
        e.unk38 = 0x80;
        e.unk3C = 0x20;
        e.unk40 = 0;
        e.unk41 = 0xA;
        e.unk44 = 0;
        ret = func_1515548C(&e, 6, 0, 0, 0x10, arg0->unkC, arg0->unk1);
        if (ret != NULL) {
            memcpy((u8 *)ret + 0x70, &x, sizeof(x));
        }
        arg0->unk28.unk0 = func_150ADA20() % 41U + 45;
    }
    p->unk2 -= D_800BE9E4;
    if (p->unk2 < 0) {
        Emitter150AF7C4 e2;

        e2.unk0 = func_150ADA68() * 280.0f + -140.0f;
        e2.unk4 = func_150ADA68() * 200.0f + -100.0f;
        e2.unk8 = e2.unkC = func_150ADA68() * 2.0f + 1.0f;
        e2.unk10 = func_151D8E6C();
        e2.unk12 = func_150ADA20() % 7U + 5;
        if (arg0->unkE < e2.unk12) {
            e2.unk12 = arg0->unkE;
        }
        e2.unk14 = 1 | (func_150ADA20() ? 2 : 0) | 0x20 | (func_150ADA20() ? 4 : 0);
        e2.unk16 = 1;
        e2.unk18 = 0xFF;
        e2.unk1A = 0;
        e2.unk1B = 0xFF;
        e2.unk1C = 0xFF;
        e2.unk1D = 0xFF;
        e2.unk1E = func_150ADA20() % 121U + 80;
        e2.unk1F = 0xFF;
        e2.unk20 = 0xFF;
        e2.unk21 = 0xFF;
        e2.unk22 = 0xFF;
        e2.unk23 = 0xFF;
        e2.unk24 = 0;
        e2.unk28 = 0x200004;
        e2.unk2C = 0x1F0601;
        e2.unk30 = 0x19;
        e2.unk34 = 0x55;
        e2.unk38 = 0x80;
        e2.unk3C = 0x20;
        e2.unk40 = 0;
        e2.unk41 = 7;
        e2.unk44 = 0;
        func_1515548C(&e2, 0, 0, 0, 0, arg0->unkC, arg0->unk1);
        p->unk2 = func_150ADA20() % 11U + 3;
    }
}

extern f32 sinf(f32);

struct Sub150AFBF4 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
};

struct Obj150AFBF4 {
    char pad0[0x10];
    f32 unk10;
    char pad14[0x5C];
    struct Sub150AFBF4 unk70;
};

s32 func_150AFBF4(struct Obj150AFBF4 *arg0) {
    struct Sub150AFBF4 *p = &arg0->unk70;
    p->unk8 = p->unk8 + p->unkC * D_800BE9A4;
    p->unk8 = func_15144B68(p->unk8);
    arg0->unk10 = sinf(p->unk8) * p->unk4 + p->unk0;
    return 1;
}

extern void func_1516D99C();

void func_150AFC68(s32 a0, s32 a1, s32 a2, s32 a3, u8 a4, s32 a5) {
    func_1516D99C(1, 0, 0, 0xD,
        0, 0, 0, 0, 0, 0, 0, 0,
        4, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0,
        0xFF, 0, 1, 0, 0, 0, 0, 0xAA,
        0xAA, 0xAA, 0xAA, a2, a3, 0, a0, 0xF0,
        0x50, 0x50, 1, 4, 0, 1, 0, 0,
        0, a1, 0, a4, a5);
}

extern void *D_800DCE94;

struct Node150AFDB0 {
    char pad0[0x8];
    struct Node150AFDB0 *unk8;
    char pad0C[0x33];
    u8 unk3F;
};

void func_150AFDB0(void) {
    struct Node150AFDB0 *node;

    D_800DD190++;
    node = D_800DCE94;
    while (node != 0) {
        ((struct Node150AFDB0 **)D_800DD198)[(s8)D_800DD190] = node->unk8;
        if (node->unk3F == D_800C3E78) {
            func_1516972C((struct102 *)node);
        }
        node = ((struct Node150AFDB0 **)D_800DD198)[(s8)D_800DD190];
    }
    D_800DD190--;
}

void func_150AFE64(s32 arg0) {
    f32 spA4;
    f32 spA0;
    f32 sp9C;
    f32 sp98;
    f32 sp94;
    f32 sp90;
    s32 idx;
    f32 *mtx;
    f32 zero;

    if (D_800D154C->unk1D4 != 0) {
        if (arg0 == 0) {
            idx = 3;
        } else {
            idx = 2;
        }

        zero = 0.0f;
        mtx = (f32 *)((u8 *)D_800D154C->unk1D4 + (idx << 6));
        spA4 = zero;
        spA0 = zero;
        sp9C = -20.0f;
        func_150A7960(mtx, spA4, spA0, sp9C, &spA4, &spA0, &sp9C);
        sp98 = zero;
        sp94 = zero;
        sp90 = -150.0f;
        func_150A7960(mtx, sp98, sp94, sp90, &sp98, &sp94, &sp90);
        func_150E1AB0(0, spA4, spA0, sp9C, sp98, sp94, sp90, 40.0f, zero, 2.0f, 120.0f, 0x3C, 0x23, 0, 0, 0, 0, 0, 0, 0, 0, 0, zero, zero, zero, zero, zero, zero);
        func_150E2DB4(D_800D154C, D_800D154C->unique_id, (s16)idx, -1, zero, zero, -39.0f, zero, zero, -150.0f, 3, 0xFF, 4, 0);
    }
}

void func_150B003C(s32 arg0) {
    if (D_800BE9F0 == 6) {
        func_15179008(0);
        func_150AF200(0xE2, 0xE1);
        return;
    }
    func_150AF200(0xDF, 0xDE);
}

typedef struct {
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
    struct17 unk28;
    struct17 unk34;
    struct17 unk40;
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
    u8 pad76[2];
    s32 unk78;
} Spawn150B0094;

extern s32 func_15145128(struct17 *, struct17 *, f32 *, f32 *);
extern void func_15145974(struct17 *, f32 *, f32 *);
extern s32 func_1513264C(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5, s32 arg6);
extern s32 func_151B7328(s32 *, s32, s32, u8, s32);

void func_150B0094(struct17 *arg0, struct17 *arg1, u8 arg2, s32 arg3) {
    Spawn150B0094 spawn;
    struct17 dir;
    f32 len;
    f32 invLen;
    s32 ret;
    s32 zero;
    s32 obj;
    s32 *p;

    zero = 0;
    dir.unk0 = arg1->unk0 - arg0->unk0;
    dir.unk4 = arg1->unk4 - arg0->unk4;
    dir.unk8 = arg1->unk8 - arg0->unk8;
    if (func_15145128(&dir, &dir, &len, &invLen) == 0) {
        return;
    }
    spawn.unk00 = 1.0f;
    spawn.unk04 = 1.0f;
    spawn.unk0C = 0.7f;
    spawn.unk08 = 0.7f;
    spawn.unk28 = *arg0;
    spawn.unk34.unk0 = dir.unk0 * 80.0f;
    spawn.unk34.unk4 = dir.unk4 * 80.0f;
    spawn.unk34.unk8 = dir.unk8 * 80.0f;
    func_15145974(&spawn.unk34, &spawn.unk14, &spawn.unk10);
    spawn.unk1C = 1.0f;
    spawn.unk20 = 1.0f;
    spawn.unk24 = 1.0f;
    spawn.unk18 = 0.0f;
    spawn.unk40 = *(struct17 *)&D_800A5480;
    spawn.unk4C = 0.0f;
    spawn.unk50 = 0x19A0;
    spawn.unk54 = 0x12C;
    spawn.unk56 = 0xD2;
    spawn.unk58 = 7;
    spawn.unk5C = 0;
    spawn.unk60 = 0xFF;
    spawn.unk61 = 8;
    spawn.unk62 = 0;
    spawn.unk63 = 0;
    spawn.unk64 = 0;
    spawn.unk65 = 0;
    spawn.unk66 = 0;
    spawn.unk67 = 0;
    spawn.unk68 = 2;
    spawn.unk6A = 0;
    spawn.unk6C = 0;
    spawn.unk70 = 0;
    spawn.unk72 = 1;
    spawn.unk74 = 0xFF;
    spawn.unk78 = 0;
    ret = func_1513264C(&spawn, 3, 0xFF, 0, 4, arg2, arg3);
    if (ret != 0) {
        p = (s32 *)(ret + 0x170);
        memcpy(p, &zero, 4);
        obj = ret;
        *p = func_151B7328(&obj, 1, 8, arg2, arg3);
    }
}

void func_150B02C0(void *arg0) {
    if (*(s32 *)((u8 *)arg0 + 0x170) != 0) {
        func_1516972C(*(struct102 **)((u8 *)arg0 + 0x170));
    }
}

extern void func_150B02C0(void *);
extern void func_15132570(void *);

void func_150B02F0(void *arg0) {
    func_150B02C0(arg0);
    func_15132570(arg0);
}

extern void func_1513259C(void *);

void func_150B031C(void *arg0) {
    func_150B02C0(arg0);
    func_1513259C(arg0);
}

typedef struct {
    s16 unk0;
    s16 unk2;
    u8 unk4;
    u8 pad5;
    u16 unk6;
    s32 unk8;
    s32 unkC;
    s16 unk10;
    s16 unk12;
    s32 unk14;
    s32 unk18;
    u8 unk1C;
    u8 unk1D;
    u8 unk1E;
    u8 unk1F;
    u8 unk20;
    u8 unk21;
    u8 unk22;
    u8 unk23;
    u8 unk24;
    u8 unk25;
    s16 unk26;
    s16 unk28;
    s16 unk2A;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    struct17 unk38;
    s16 unk44;
    s16 unk46;
    s16 unk48;
    s16 unk4A;
    f32 unk4C;
    f32 unk50;
    f32 unk54;
    f32 unk58;
    s32 unk5C;
    s8 unk60;
    s8 unk61;
    u8 unk62;
    u8 unk63;
    u8 unk64;
    u8 pad65[3];
    f32 unk68;
} Arg15153634;

typedef struct {
    s32 unk00;
    s32 unk04;
    struct17 unk08;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    s16 unk2C;
    s16 unk2E;
    f32 unk30;
    f32 unk34;
    f32 unk38;
} Arg15152190;

extern void func_15153634(Arg15153634 *, s32, u8, s32);
extern void func_15152190(Arg15152190 *, const s32 *, const f32 *, s32, f32, s32, u8, s32);

const s32 D_8009F790[5] = { 6, 6, 6, 0x52, 0x52 };
const f32 D_8009F7A4[5] = { 0.2f, 0.2f, 0.2f, 0.2f, 0.2f };

void func_150B0348(u8 *arg0, u8 arg1, s32 arg2) {
    struct17 pos;

    pos.unk0 = *(f32 *)(arg0 + 0x14);
    pos.unk4 = *(f32 *)(arg0 + 0x18) + 30.0f;
    pos.unk8 = *(f32 *)(arg0 + 0x1C);
    {
    Arg15153634 a;

    a.unk0 = 0xA;
    a.unk2 = 7;
    a.unk4 = 0x6C;
    a.unk6 = 0x5103;
    a.unk8 = 0x200005;
    a.unkC = 0;
    a.unk10 = 0x1E;
    a.unk12 = 0xF;
    a.unk14 = 0;
    a.unk18 = 0;
    a.unk1F = 0xFF;
    a.unk1C = 0x7F;
    a.unk1D = 0x4B;
    a.unk1E = 6;
    a.unk20 = 0x80;
    a.unk21 = 0x53;
    a.unk22 = 0;
    a.unk23 = 0x64;
    a.unk24 = 0x64;
    a.unk25 = 0xFF;
    a.unk26 = 0x20;
    a.unk28 = 7;
    a.unk2A = 0x20;
    a.unk2C = 1.025728941f;
    a.unk30 = 351.0f;
    a.unk34 = 200.0f;
    a.unk38 = pos;
    a.unk44 = 0;
    a.unk46 = -0x19;
    a.unk48 = 0xFF;
    a.unk4A = 0x15;
    a.unk4C = 5.0f;
    a.unk50 = 25.0f;
    a.unk54 = 0.008f;
    a.unk58 = 0.266f;
    a.unk5C = 0x40E07;
    a.unk60 = 0x10;
    a.unk61 = -1;
    a.unk62 = 8;
    a.unk63 = 6;
    a.unk64 = 1;
    a.unk68 = 0.938608f;
    func_15153634(&a, 0xFF, arg1, arg2);
    }
    {
    Arg15152190 b;

    b.unk00 = 0x24;
    b.unk04 = 0xA;
    b.unk08 = pos;
    b.unk14 = 0;
    b.unk16 = 0xFF;
    b.unk18 = -0x28;
    b.unk1A = 0x14;
    b.unk1C = 11.0f;
    b.unk20 = 8.0f;
    b.unk24 = -1.09f;
    b.unk28 = 0.3710000217f;
    b.unk2C = 0x22;
    b.unk2E = 0xF;
    b.unk30 = 0.302000016f;
    b.unk34 = 0.3180000186f;
    b.unk38 = 9.687f;
    func_15152190(&b, D_8009F790, D_8009F7A4, 5, 65.0f, 0, arg1, arg2);
    }
}

extern s32 func_151149AC(u32);

struct Obj150B060C {
    f32 unk0;
    f32 unk4;
    s16 *unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
};

s32 func_150B060C(u8 arg0, struct Obj150B060C *arg1) {
    arg1->unk8 = (s16 *)func_151149AC(arg0);
    if (arg1->unk8 == 0) {
        return 0;
    }
    arg1->unk0 = -150.0f;
    arg1->unk4 = 4.5f;
    arg1->unkC = (f32)arg1->unk8[8];
    arg1->unk10 = (f32)arg1->unk8[9];
    arg1->unk14 = (f32)arg1->unk8[10];
    return 1;
}
