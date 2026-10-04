#include <ultra64.h>
#define func_150ADA20 func_150ADA20_u8_decl_in_functions_h
#include "functions.h"
#undef func_150ADA20
u32 func_150ADA20(void);
#include "variables.h"

typedef struct {
    s32 unk0;
    u8 pad4[0x10];
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    u8 pad20[0x3B - 0x20];
    u8 unk3B;
    u8 pad3C[0x94 - 0x3C];
    s32 unk94;
    u8 pad98[0x1D4 - 0x98];
    s32 unk1D4;
} Obj64DC;

typedef struct {
    /* 0x00 */ void *unk0;
    /* 0x04 */ void *unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ u8  pad1A[0x2];
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ u8  unk30;
    /* 0x31 */ u8  unk31;
    /* 0x32 */ u8  unk32;
    /* 0x33 */ u8  unk33;
    /* 0x34 */ u8  unk34;
    /* 0x35 */ u8  unk35;
    /* 0x36 */ u8  unk36;
    /* 0x37 */ u8  unk37;
    /* 0x38 */ u8  unk38;
    /* 0x39 */ u8  unk39;
} struct_7484;

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
    /* 0x25 */ u8  pad25;
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
} struct_150F6890;

extern u8 D_800917F8;
extern u8 D_80091930;
extern u8 D_8009193C;
extern u8 D_80091948;
struct102 *func_15169968(struct_7484 *);
void *func_15134DAC(struct_150F6890 *, s32);

void func_150F5420(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    struct_7484 sp24;
    s32 temp_v0;

    if (arg3 != 0) {
        if (arg3 == 2) {
            sp24.unk2C = 0xF0;
            sp24.unk2E = 0xBA;
            sp24.unk0 = &D_80091948;
        } else {
            sp24.unk2C = 0x10E;
            sp24.unk2E = 0x7C;
            if (arg3 == 1) {
                sp24.unk0 = &D_80091930;
            } else {
                sp24.unk0 = &D_8009193C;
            }
        }
        sp24.unk30 = 9;
        sp24.unk39 = 0x10;
        sp24.unk28 = 0;
        sp24.unk2A = 0;
        sp24.unk36 = 8;
    } else {
        sp24.unk0 = &D_800917F8;
        sp24.unk30 = 0xA;
        sp24.unk2C = 0xA0;
        sp24.unk2E = 0xC0;
        sp24.unk39 = 0x20;
        sp24.unk28 = 0x1000;
        sp24.unk2A = 0x1000;
        sp24.unk36 = 0x18;
    }

    temp_v0 = arg0 + arg1 + arg2;
    sp24.unk8 = (arg0 << 16) | arg1;
    sp24.unkC = (arg2 << 16) | temp_v0;
    sp24.unk10 = 0x2710;
    sp24.unk14 = temp_v0;
    sp24.unk1C = 146.0f;
    sp24.unk20 = 100.0f;
    sp24.unk18 = 0;
    sp24.unk24 = 0;
    sp24.unk26 = 0;
    sp24.unk31 = 1;
    sp24.unk32 = 0xFF;
    sp24.unk33 = 0xFF;
    sp24.unk34 = 0xFF;
    sp24.unk37 = 0x11;
    sp24.unk35 = 0;
    sp24.unk16 = 0;
    func_15169968(&sp24);
}

struct Struct150F5590 {
    char pad0[0x18];
    s32 unk18;
    s32 unk1C;
    char pad20[0x24 - 0x20];
    s16 unk24;
    char pad26[0x38 - 0x26];
    s16 unk38;
    s16 unk3A;
    char pad3C[0x45 - 0x3C];
    u8 unk45;
};

void func_150F55C8(struct Struct150F5590 *);

void func_150F5590(struct Struct150F5590 *arg0) {
    s32 temp = 0x1000 - (arg0->unk24 << 2);
    arg0->unk38 = temp;
    arg0->unk3A = arg0->unk38;
    func_150F55C8(arg0);
}

void func_150F55C8(struct Struct150F5590 *arg0) {
    s32 temp_t2;
    s32 temp_v0;
    s32 temp_a1;
    s32 temp_a3;
    s32 temp_t1;
    s32 temp_t0;
    s32 temp_t6;
    s32 temp_t7;
    s32 temp_t4;

    temp_v0 = arg0->unk1C & 0xFFFF;
    temp_a1 = arg0->unk18 >> 16;
    temp_a3 = arg0->unk18 & 0xFFFF;
    temp_t0 = arg0->unk1C >> 16;
    temp_t1 = temp_v0 - temp_a1;
    temp_t2 = arg0->unk24;

    if (temp_t1 < temp_t2) {
        temp_t6 = temp_v0 - temp_t2;
        temp_t7 = temp_t6 * 0xFF;
        arg0->unk45 = temp_t7 / temp_a1;
    } else if ((temp_t1 - temp_a3) < temp_t2) {
        arg0->unk45 = 0xFF;
    } else {
        temp_t4 = temp_t2 * 0xFF;
        arg0->unk45 = temp_t4 / temp_t0;
    }
}

void func_15179008(s32);

void func_150F568C(s32 arg0) {
    func_15179008(0);
}

typedef struct {
    u8 pad0[0x8];
    f32 unk8;
} Obj56B0;
typedef struct {
    u8 pad0[0x84];
    u16 unk84;
    u8 pad86[0x2D0 - 0x86];
    Obj56B0 *unk2D0;
} Arg56B0;
typedef struct {
    u8 pad0[0x18];
    s16 unk18;
} Out56B0;
extern s32 D_80090274[];

s32 func_150F56B0(Out56B0 *arg0, Arg56B0 *arg1) {
    Obj56B0 *obj;
    s32 idx;
    f32 t;

    obj = arg1->unk2D0;
    if (obj == NULL) {
        return 0;
    }
    idx = 6;
    if (arg1->unk84 == 0xAE) {
        if (obj->unk8 >= 36.0f && obj->unk8 <= 51.0f) {
            t = obj->unk8 - 36.0f;
            t *= 0.0625f;
            t = 1.0f - t;
            idx = 6 * t;
        } else if (obj->unk8 > 51.0f && obj->unk8 <= 54.0f) {
            idx = 0;
        } else if (obj->unk8 > 54.0f && obj->unk8 <= 60.0f) {
            t = obj->unk8 - 54.0f;
            t *= 0.1428571492f;
            idx = 6 * t;
        } else if (obj->unk8 > 60.0f && obj->unk8 <= 65.0f) {
            t = obj->unk8 - 60.0f;
            t *= 0.1666666716f;
            idx = (s32)(2 * t) + 7;
        } else if (obj->unk8 > 65.0f && obj->unk8 <= 67.0f) {
            t = obj->unk8 - 65.0f;
            t *= 0.3333333433f;
            t = 1.0f - t;
            idx = (s32)(2 * t) + 7;
        } else if (obj->unk8 > 67.0f && obj->unk8 <= 70.0f) {
            t = obj->unk8 - 67.0f;
            t *= 0.25f;
            t = 1.0f - t;
            idx = (s32)(2 * t) + 4;
        } else if (obj->unk8 > 70.0f && obj->unk8 <= 74.0f) {
            t = obj->unk8 - 70.0f;
            t *= 0.200000003f;
            idx = (s32)(2 * t) + 4;
        } else if (obj->unk8 > 74.0f && obj->unk8 <= 119.0f) {
            t = obj->unk8 - 74.0f;
            t *= 0.02173913084f;
            idx = (s32)(2 * t) + 7;
        } else if (obj->unk8 > 119.0f && obj->unk8 <= 150.0f) {
            t = obj->unk8 - 119.0f;
            t *= 0.03125f;
            t = 1.0f - t;
            idx = (s32)(2 * t) + 7;
        }
    }
    arg0->unk18 = D_80090274[idx];
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1228D0/func_150F5A54.s")

void func_150F5C08(void *arg0, s16 arg1, u8 arg2, s32 arg3) {
    struct {
        void *unk0;
        u8 unk4;
        u8 pad5;
        u8 pad6;
        u8 pad7;
        f32 unk8;
    } sp34;
    struct260 *temp_v0;

    sp34.unk0 = arg0;
    sp34.unk4 = *(u8 *)((s32)arg0 + 0x3B);
    sp34.unk8 = 0.0f;

    temp_v0 = func_15149130(arg1, -1, 0x51, -1, 1, 0x3E, (struct37 *)0xC, arg2, arg3);
    if (temp_v0 != NULL) {
        memcpy((void *)((s32)temp_v0 + 0x28), &sp34, 0xC);
    }
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
    s8 unk62;
    s8 unk63;
    s8 unk64;
    u8 unk65;
    u8 unk66;
    u8 pad67;
    s16 unk68;
    u8 pad6A[2];
    f32 unk6C;
} Spawn5C98; /* 0x70 */
typedef struct {
    Obj64DC *unk0;
    u8 unk4;
    u8 pad5[3];
    f32 unk8;
} Sub5C98;
typedef struct {
    u8 pad0;
    u8 unk1;
    u8 pad2[0xA];
    u8 unkC;
    u8 padD;
    s16 unkE;
    u8 pad10[0x28 - 0x10];
    Sub5C98 unk28;
} Arg5C98;
const struct17 D_800A1B00 = { 0.0f, 0.0f, 14.0f };
const struct17 D_800A1B0C = { 0.0f, 0.0f, 78.0f };
extern s32 func_15145EA4(s32 *arg0, s32 *arg1, s32 arg2, s32 arg3);
extern void *func_15130280(void *, u8, s32, s32, u8, s32);

void func_150F5C98(Arg5C98 *arg0) {
    Sub5C98 *sub;
    Obj64DC *obj;
    Spawn5C98 spawn;
    f32 tint;
    struct17 start;
    struct17 end;
    f32 dx;
    f32 dy;
    f32 dz;
    s32 srcs[2];
    s32 dsts[2];
    s32 flags;
    s16 life;
    f32 scale;
    void *ret;

    sub = &arg0->unk28;
    obj = sub->unk0;
    if (obj->unk0 == 0 || obj->unk3B != sub->unk4) {
        arg0->unkE = -1;
        return;
    }
    if (obj->unk1D4 == 0) {
        return;
    }
    sub->unk8 += (0.2600000203f + func_150ADA68() * 0.1950000077f) * D_800BE9A4;
    if (sub->unk8 > 1.0f) {
        spawn.unk14 = 0xFF;
        spawn.unk15 = 0xFF;
        spawn.unk16 = 0xFF;
        spawn.unk18 = 0xB4;
        spawn.unk19 = 0xB4;
        spawn.unk1A = 0xB4;
        srcs[0] = (s32)&D_800A1B00;
        srcs[1] = (s32)&D_800A1B0C;
        dsts[0] = (s32)&start;
        dsts[1] = (s32)&end;
        func_15145EA4(srcs, dsts, obj->unk1D4 + 0x140, 2);
        spawn.unk1D = 0x6C;
        spawn.unk8 = 0x5103;
        spawn.unk0 = 0x200005;
        spawn.unk4 = 0x9F0600;
        spawn.unkC = 0;
        spawn.unk10 = 0;
        spawn.unk17 = 0xFF;
        spawn.unk1C = 0xFF;
        dx = end.unk0 - start.unk0;
        dy = end.unk4 - start.unk4;
        dz = end.unk8 - start.unk8;
        spawn.unk3C = *(struct17 *)&D_800A5480;
        spawn.unk58 = 0x84CE07;
        spawn.unk60 = 8;
        spawn.unk61 = 6;
        spawn.unk62 = 0x10;
        spawn.unk63 = -1;
        spawn.unk64 = -1;
        spawn.unk65 = 0;
        spawn.unk5C = 0;
        spawn.unk66 = 0xFF;
        spawn.unk68 = 1000;
        spawn.unk6C = 1000.0f;
        tint = 0.9730340242f;
        spawn.unk24 = 1.022472024f;
        do {
            life = spawn.unk1E = spawn.unk22 = spawn.unkA = func_150ADA20() % 21U + 20;
            spawn.unk20 = 255 / life;
            spawn.unk1B = func_150ADA20() % 26U + 8;
            spawn.unk28 = spawn.unk2C = func_150ADA68() * 70.0f + 148.0f;
            spawn.unk54 = func_150ADA68() * 0.2190000117f + 0.08600000292f;
            scale = func_150ADA68() * 0.04100000113f + 0.07800000161f;
            spawn.unk48.unk0 = dx * scale;
            spawn.unk48.unk4 = dy * scale;
            spawn.unk48.unk8 = dz * scale;
            scale = func_150ADA68() * D_800BE9A4;
            spawn.unk58 &= ~0xC0;
            spawn.unk30.unk0 = spawn.unk48.unk0 * scale + start.unk0;
            spawn.unk30.unk4 = spawn.unk48.unk4 * scale + start.unk4;
            spawn.unk30.unk8 = spawn.unk48.unk8 * scale + start.unk8;
            flags = (func_150ADA20() & 1) ? 0x80 : 0;
            spawn.unk58 |= ((func_150ADA20() & 1) ? 0x40 : 0) | flags;
            ret = func_15130280(&spawn, 1, 0, 4, arg0->unkC, arg0->unk1);
            if (ret != NULL) {
                memcpy((u8 *)ret + 0xA8, &tint, 4);
            }
            sub->unk8 -= 1.0f;
        } while (sub->unk8 > 1.0f);
    }
}

void func_150F6138(s32 arg0, s32 arg1, u8 arg2) {
    func_15149514(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}

typedef struct {
    u8 pad0[0x48];
    f32 unk48;
    f32 unk4C;
    u8 pad50[0x58 - 0x50];
    u8 unk58;
} Part6178;
typedef struct {
    u8 pad0[0x34];
    struct17 unk34;
    struct17 unk40;
    u8 pad4C[0x110 - 0x4C];
    Part6178 unk110;
} Thing6178;
typedef struct {
    u8 pad0[0x9];
    u8 unk9;
    u8 padA[0xE - 0xA];
    s16 unkE;
    s16 unk10;
    s16 unk12;
} Light6178;
typedef struct {
    u8 pad0[0x14];
    Light6178 *unk14;
} Holder6178;
typedef struct {
    Obj64DC *unk0;
    u8 unk4;
    u8 pad5[3];
    Thing6178 *unk8;
    Holder6178 *unkC;
} Sub6178;
typedef struct {
    u8 pad0[0xE];
    s16 unkE;
    u8 pad10[0x28 - 0x10];
    Sub6178 unk28;
} Arg6178;
const struct17 D_800A1B18 = { 0.0f, -55.0f, 0.0f };
const struct17 D_800A1B24 = { 0.0f, -115.0f, 0.0f };

void func_150F6178(Arg6178 *arg0) {
    Sub6178 *sub;
    Obj64DC *obj;
    struct17 a;
    struct17 b;
    s32 srcs[2];
    s32 dsts[2];

    sub = &arg0->unk28;
    obj = sub->unk0;
    if (obj->unk0 == 0 || obj->unk3B != sub->unk4) {
        arg0->unkE = -1;
        return;
    }
    if (obj->unk1D4 != 0 && !(obj->unk94 & 2)) {
        Thing6178 *thing;
        Holder6178 *holder;
        Light6178 *light;

        srcs[0] = (s32)&D_800A1B18;
        srcs[1] = (s32)&D_800A1B24;
        dsts[0] = (s32)&a;
        dsts[1] = (s32)&b;
        func_15145EA4(srcs, dsts, obj->unk1D4, 2);
        if (sub->unk8 != NULL) {
            thing = sub->unk8;
            thing->unk110.unk58 |= 1;
            thing->unk34 = a;
            thing->unk40 = b;
        }
        holder = sub->unkC;
        if (holder != NULL) {
            light = holder->unk14;
            light->unk9 = 0;
            light->unkE = a.unk0;
            light->unk10 = a.unk4;
            light->unk12 = a.unk8;
        }
    } else {
        if (sub->unk8 != NULL) {
            Part6178 *part = &sub->unk8->unk110;

            part->unk58 &= ~1;
        }
        if (sub->unkC != NULL) {
            Light6178 *light = sub->unkC->unk14;

            light->unk9 = 1;
        }
    }
    if (sub->unk8 != NULL) {
        Part6178 *part = &sub->unk8->unk110;

        part->unk48 = 4.0f;
        part->unk4C = 8.0f;
    }
}

void func_150F631C(struct260 *arg0) {
    struct260 *temp_a1;
    struct102 *temp_a0;

    temp_a1 = arg0;
    if (*(struct102 *volatile *)((u8 *)temp_a1 + 0x30) != NULL) {
        func_1516972C(*(struct102 **)((u8 *)temp_a1 + 0x30));
    }

    temp_a0 = *(struct102 **)((u8 *)temp_a1 + 0x34);
    if (temp_a0 != NULL) {
        func_1516972C(temp_a0);
    }
}

void func_150F631C(struct260 *arg0);

void func_150F6368(struct260 *arg0) {
    func_150F631C(arg0);
    func_1514933C(arg0);
}

void func_15149368(struct260 *arg0);

void func_150F6394(struct260 *arg0) {
    func_150F631C(arg0);
    func_15149368(arg0);
}

void func_150F63C0(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}

typedef struct {
    char pad_0[0x8];
    s32 field_0x08;
} Field160ChildBlock;

typedef struct {
    char pad_0[0x160];
    u8 *field_0x160;
} Field160Owner;

void func_150F6400(Field160Owner *arg0) {
    Field160ChildBlock *p;

    if (*(s32 *)&arg0->field_0x160 != 0) {
        p = (Field160ChildBlock *)(arg0->field_0x160 + 0x28);
        p->field_0x08 = 0;
    }
}

void func_150F6420(u8 *arg0) {
    func_150F6400(arg0);
    func_1513CA6C((struct210 *)arg0);
}

void func_150F644C(u8 *arg0) {
    func_150F6400(arg0);
    func_1513CAA0((struct210 *)arg0);
}

void func_150F6478(struct210 *arg0) {
}

void func_150F6478(struct210 *);

void func_150F6484(struct210 *arg0) {
    func_150F6478(arg0);
    func_151411A4(arg0);
}

void func_151411C4(struct210 *);

void func_150F64B0(struct210 *arg0) {
    func_150F6478(arg0);
    func_151411C4(arg0);
}

typedef struct {
    Obj64DC *unk0;
    u8 unk4;
    u8 pad5;
    s16 unk6;
} Sub64DC;
typedef struct {
    u8 pad0;
    u8 unk1;
    u8 pad2[0xA];
    u8 unkC;
    u8 padD;
    s16 unkE;
    u8 pad10[0x28 - 0x10];
    Sub64DC unk28;
} Arg64DC;
extern s32 D_800BE9E4;
const f32 D_800A1B30[3] = { 0.0f, 465.0f, -102.0f };
void func_15143134(const void *, f32 *, s32);
struct225 *func_151602C0(Header *, Header2 *, s32, s32, s32, s32, s32, s32, s32, u8, s32);
void func_15107C1C(Obj64DC *, u8, const void *, s16, s32, s32, s32, f32, f32, s32, s32, u8 *, u8, s32);

void func_150F64DC(Arg64DC *arg0) {
    Sub64DC *p;
    Obj64DC *obj;
    s8 count;

    p = &arg0->unk28;
    obj = p->unk0;
    if (obj->unk0 == 0 || obj->unk3B != p->unk4) {
        arg0->unkE = -1;
        return;
    }
    if (obj->unk1D4 == 0 || (obj->unk94 & 2)) {
        return;
    }
    p->unk6 -= D_800BE9E4;
    if (p->unk6 >= 0) {
        return;
    }
    func_10010F88(0x679, 0x18CE, 0, 0, 0, obj->unk14, obj->unk18, obj->unk1C, 0x7918, 0x7D00);
    count = (func_150ADA20() & 1) + 2;
    {
        f32 pos[3];
        Header hdr;
        Header2 hdr2;
        u8 color[4];

        func_15143134(D_800A1B30, pos, obj->unk1D4);
        hdr.unk0 = 3;
        hdr.unk1 = -1;
        hdr.unk2 = func_150ADA20() % 9U + 10;
        hdr.unk4 = 0;
        hdr2.unk0 = pos[0];
        hdr2.unk4 = pos[1];
        hdr2.unk8 = pos[2];
        func_151602C0(&hdr, &hdr2, func_150ADA20() % 61U + 60, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, arg0->unkC,
                      arg0->unk1);
        do {
            color[0] = 0xA0;
            color[1] = 0xA0;
            color[2] = 0xFF;
            color[3] = func_150ADA20() % 101U + 155;
            func_15107C1C(obj, 0, D_800A1B30, (u8)func_150ADA20(), func_150ADA20() % 43U - 50,
                          func_150ADA20() % 18U + 5, 4, 27.0f, func_150ADA68() * 16.0f + 20.0f, 0, 2, color, arg0->unkC, arg0->unk1);
        } while (--count > 0);
    }
    p->unk6 = func_150ADA20() % 91U + 90;
}

void func_150F6850(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}

void func_150F6890(void *arg0, s16 arg1, s32 arg2, s32 arg3) {
    struct_150F6890 sp1C;

    sp1C.unk0 = *((u8 *)arg0 + 0x3B);
    sp1C.unk1C = 4.700000286f;
    sp1C.unk20 = 8.5f;
    sp1C.unk34 = 1.0f;
    sp1C.unk4 = arg0;
    sp1C.unk8 = 3;
    sp1C.unkC = 0.0f;
    sp1C.unk10 = 0.0f;
    sp1C.unk14 = 0.0f;
    sp1C.unk18 = 0.0f;
    sp1C.unk24 = 2;
    sp1C.unk26 = 0x28;
    sp1C.unk28 = 0x10;
    sp1C.unk2A = arg1;
    sp1C.unk2E = 5;
    sp1C.unk2F = 8;
    sp1C.unk30 = -1;
    sp1C.unk38 = 0;
    sp1C.unk39 = -1;
    sp1C.unk2C = 0;

    func_15134DAC(&sp1C, 0);
}

typedef struct { f32 x, y, z; } Vec695C;
typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ u8  pad4[0x14];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ u8  unk1C;
    /* 0x1D */ u8  unk1D;
    /* 0x1E */ u8  pad1E[2];
    /* 0x20 */ s32 unk20;
} Struct695C; /* 0x24 */
typedef struct {
    u8 pad0;
    u8 unk1;
    u8 pad2[0xA];
    u8 unkC;
    u8 padD[0xF];
    s32 unk1C;
} Arg695C;
void func_15137F30(Vec695C *, Vec695C *, Vec695C *, Vec695C *, f32, Arg695C *, Vec695C *,
                   Vec695C *, Vec695C *, f32 *, s16 *, u8 *, f32 *);
void func_1504715C(Struct695C *, s32);
void func_151D9014(void *, void *, s32, f32, s32, s32, f32, s32, f32, f32, s32, void *, s32, s32, s32, s32);

void func_150F695C(Vec695C *arg0, Vec695C *arg1, Vec695C *arg2, Vec695C *arg3, f32 arg4, Arg695C *arg5) {
    Vec695C spA4;
    Vec695C sp98;
    Vec695C sp8C;
    f32 sp88;
    s16 sp86;
    u8 sp85;
    f32 sp80;
    Struct695C sp5C;
    u8 flag;
    s32 flag2;

    func_15137F30(arg0, arg1, arg2, arg3, arg4, arg5, &spA4, &sp98, &sp8C, &sp88, &sp86, &sp85, &sp80);
    sp80 *= 1.0f + func_150ADA68() * 2.0f;
    flag = func_150ADA68() < 0.6000000238f;
    if (flag) {
        func_1504715C(&sp5C, arg5->unk1C);
    } else {
        sp5C.unk0 = -10000.0f;
        sp5C.unk18 = 0;
        sp5C.unk1C = 0;
        sp5C.unk1D = 0;
        sp5C.unk20 = 0;
    }
    if (flag) {
        flag2 = func_150ADA68() < 0.5f;
    } else {
        flag2 = 0;
    }
    func_151D9014(&spA4, &sp8C, 1, sp88, sp86, sp85, sp80, flag, 1.799999952f, 1.799999952f, 1, &sp5C, 1, flag2, arg5->unkC, arg5->unk1);
}
