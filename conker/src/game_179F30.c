#include <ultra64.h>
#define func_15083568 func_15083568_orig
#define func_1514D3B0 func_1514D3B0_orig
#include "functions.h"
#undef func_15083568
#undef func_1514D3B0
#include "variables.h"

struct St1514DE94 {
    char pad0[0x38];
    s32 unk38;
};
struct St1514DE94 *func_15083568(struct127 *, s32, f32, s32);

typedef struct struct_1514EBA4 {
    char pad0[0x10];
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s16 unk1C;
} struct_1514EBA4;

typedef struct Vec3w1514F308 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Vec3w1514F308;

typedef struct Struct1514F5CCArg {
    s32 unk00;
    f32 unk04;
    struct127 *unk08;
    u8 unk0C;
    u8 pad0D[3];
    f32 unk10;
    s16 unk14;
    s16 unk16;
    u8 unk18;
} Struct1514F5CCArg;

typedef struct HudSpriteState {
    char pad_0x00[0x9];
    u8 field_0x09;
} HudSpriteState;

typedef struct HudSpriteHandle {
    char pad_0x00[0x14];
    HudSpriteState *field_0x14;
} HudSpriteHandle;

extern struct_1514EBA4 *func_15167A68(s32, s32, s32, s32, s32, s32);
extern f32 D_800A5E08;
extern f32 D_800A5E0C;
extern f32 D_800A5E10;
extern f32 D_800A5E14;
extern f32 D_800A5E18;
extern f32 D_800A5E1C;
extern f32 D_800A5E58;
extern f32 D_800A5E5C;
extern f32 D_800A5DE4;
extern f32 D_800A5DE8;
extern f32 D_800A5DEC;
extern f32 D_800A5DF0;
extern Vec3w1514F308 D_800A5970;
extern Vec3w1514F308 D_800A597C;
extern u8 D_800A58A0;
extern u8 D_800A5958;
extern u8 D_800A5964;
extern s32 D_800A58D0;
extern s32 D_800A58E4;
extern s32 D_800A58F8;
extern s32 D_800A590C;
extern s32 D_800A5920;
s32 func_15189FF0(void *, void *, void *, s32, s32, s32, s32);
extern void func_151D74B0(s32, s32, s32, s32, s32);
void func_151BB044(s32);
void func_151BC074(s32);
void func_151BD2F8(void *, s32, s32);
void func_151B9F00(void *, s32, s32);
void func_150C0AC0(Struct1514F5CCArg *, s32, s32);
s32 func_150C5370(void *, s32);
s32 func_1514EC1C(s32, s32, s16);
extern void *func_15155FD4(s32);
extern void *func_15155780(s32, s32);
s32 func_1514CA80(struct127 *, s32 *, s32 *, s32 *);
extern void (*D_8008AA70[])(struct127 *);
extern void (*D_8008AACC[])(struct127 *);
extern u8 *D_8008AB90[];
extern u8 D_800A5EC0[];
extern u8 D_800A5ED8[];
s32 func_15160A58(s32, s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_1518D1C0(s32, s32, s32, s32, s32, s32, s32 *);
s32 func_1515D5F8(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_150C4120(s32, s32, s32, s32);

typedef struct Struct1514E00C_2C {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 unk1D;
    /* 0x1E */ s8 unk1E;
    /* 0x1F */ u8 pad1F;
} Struct1514E00C_2C;

typedef struct Struct1514E00C_4C {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 pad01;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ u8 pad06[2];
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 unk13;
    /* 0x14 */ u8 pad14[8];
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ u8 pad34[0xC];
    /* 0x40 */ s32 unk40;
    /* 0x44 */ u8 pad44;
    /* 0x45 */ u8 unk45;
    /* 0x46 */ u8 pad46[0x12];
} Struct1514E00C_4C;

typedef struct Struct1514E00C_A4 {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u8 pad24[0x24];
    /* 0x48 */ f32 unk48;
    /* 0x4C */ u8 pad4C[8];
    /* 0x54 */ u8 unk54;
    /* 0x55 */ u8 unk55;
    /* 0x56 */ u8 unk56;
    /* 0x57 */ u8 unk57;
    /* 0x58 */ u8 pad58[4];
} Struct1514E00C_A4;


#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514CA80.s")

s32 func_1514D15C(struct127 *arg0) {
    s32 sp44;
    s32 sp40;
    s32 sp3C;
    u8 flags;
    s32 temp_s0;
    s32 index;
    void *temp_v0;

    sp44 = -1;
    sp40 = -1;
    sp3C = -1;
    index = arg0 - D_800CC2D0;
    if (*(s32 *)((u8 *)arg0 + 0x2F4) != 0) {
        return 0;
    }

    do {
        temp_v0 = func_15155FD4(index);
        if (temp_v0 != 0) {
            func_1516972C((struct102 *)temp_v0);
        }
    } while (temp_v0 != 0);

    if ((index == 0) && (D_800BE616 == 0)) {
        func_15155780(index, 0xFF);
    }

    D_8008AACC[0](arg0);
    temp_s0 = func_1514CA80(arg0, &sp44, &sp40, &sp3C);
    flags = temp_s0;
    if (temp_s0 == 0) {
        return 0;
    }

    if (flags & 4) {
        temp_s0 = D_800A5ED8[sp3C];
        if (temp_s0 != 0) {
            D_8008AA70[temp_s0](arg0);
        }
    }

    temp_s0 = flags & 2;
    if (temp_s0 != 0) {
        index = D_800A5EC0[sp40];
        if (index != 0) {
            D_8008AA70[index](arg0);
        }
    }

    if ((temp_s0 != 0) && (flags & 1)) {
        if (D_8008AA70[D_8008AB90[sp40][sp44]] != NULL) {
            D_8008AA70[D_8008AB90[sp40][sp44]](arg0);
        }
    }
    return 1;
}

typedef struct Node1514D310 {
    char pad0[0x10];
    s32 unk10;
    struct Node1514D310 *unk14;
    char pad18[0x4];
    s16 unk1C;
} Node1514D310;

typedef struct Cont1514D310 {
    char pad0[0x2F4];
    Node1514D310 *unk2F4;
} Cont1514D310;

typedef struct Struct8008ABE8 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} Struct8008ABE8;

extern void (*D_8008AB58[])(s32);
extern s32 (*D_8008AB64[])(s32, s32, s32);
extern Struct8008ABE8 *D_8008ABE8[];
s32 func_1514D4B8(s16, s16);

s32 func_1514D310(Cont1514D310 *arg0) {
    Node1514D310 *node;
    Node1514D310 *next;

    node = arg0->unk2F4;
    while (node != 0) {
        next = node->unk14;
        if (D_8008ABE8[node->unk1C]->unk2 != -1) {
            D_8008AB58[D_8008ABE8[node->unk1C]->unk2](node->unk10);
        }
        func_1516972C((struct102 *) node);
        node = next;
    }
    return 1;
}

s32 func_1514D3B0(Cont1514D310 *arg0, s16 arg1, s32 arg2, s32 arg3) {
    Node1514D310 *node;
    s32 result;

    node = arg0->unk2F4;
    result = 0;
    if (node != 0) {
        do {
            if ((arg1 == node->unk1C) || (func_1514D4B8(D_8008ABE8[arg1]->unk4, node->unk1C) != 0)) {
                if (D_8008ABE8[node->unk1C]->unk0 != -1) {
                    if (D_8008AB64[D_8008ABE8[node->unk1C]->unk0](node->unk10, arg2, arg3) != 0) {
                        result = 1;
                    } else {
                        result = 0;
                    }
                }
            }
            node = node->unk14;
        } while (node != 0);
    }
    return result;
}

s32 func_1514D4B8(s16 arg0, s16 arg1) {
    if (arg0 == -1) {
        return 0;
    }
    if (arg0 == arg1) {
        return 1;
    }

    if (func_1514D4B8(D_8008ABE8[arg0]->unk6, arg1) != 0) {
        return 1;
    }
    if (func_1514D4B8(D_8008ABE8[arg0]->unk4, arg1) != 0) {
        return 1;
    }
    return 0;
}

typedef struct Struct1514D564Payload {
    struct127 *unk0;
    u8 unk4;
    s8 unk5;
    u8 pad6[2];
    f32 unk8;
    f32 unkC;
    f32 unk10;
} Struct1514D564Payload;

typedef struct Struct1514D564Desc {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    s8 unk18;
    u8 pad19[3];
    f32 unk1C;
    s8 unk20;
    u8 pad21[3];
} Struct1514D564Desc;

void func_1514D564(struct127 *arg0) {
    Struct1514D564Desc sp34;
    s32 temp_v0;
    Struct1514D564Payload sp1C;
    register f32 neg;

    neg = -180.0f;
    sp1C.unk0 = arg0;
    sp1C.unk4 = arg0->unique_id;
    sp1C.unk8 = 0.0f;
    sp1C.unkC = neg;
    sp1C.unk10 = 77.0f;
    sp34.unk0 = D_800A5DE4;
    sp34.unk4 = D_800A5DE8;
    sp34.unk8 = D_800A5DEC;
    sp1C.unk5 = 6;
    sp34.unk18 = 1;
    sp34.unkC = arg0->x_position;
    sp34.unk10 = arg0->y_position;
    sp34.unk14 = arg0->z_position;
    sp34.unk20 = 1;
    sp34.unk1C = D_800A5DF0;
    temp_v0 = func_150C5370(&sp34, 0x14);
    if (temp_v0 != 0) {
        memcpy((void *)(temp_v0 + 0xC8), &sp1C, 0x14);
        func_1514EC1C(temp_v0, (s32) arg0, 0x15);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514D64C.s")

void func_1514D96C(s32 arg0) {
}

s32 func_15158BD0(s32, s32, s32);
s32 func_1514EC1C(s32, s32, s16);

void func_1514D978(s32 arg0) {
    struct {
        s32 unk0;
        s32 unk4;
        s32 unk8;
        s32 unkC;
        f32 unk10;
        s32 unk14;
        s32 unk18;
        s32 unk1C;
    } sp20;
    s32 v0;

    sp20.unk0 = 0;
    sp20.unk4 = 0;
    sp20.unk8 = 0;
    sp20.unkC = 0;
    sp20.unk14 = 0;
    sp20.unk18 = 0;
    sp20.unk1C = 0;
    sp20.unk10 = 12.0f;

    v0 = func_15158BD0(arg0, 1, 0x20);
    if (v0 != 0) {
        memcpy((void *)(v0 + 0x58), &sp20, 0x20);
        func_1514EC1C(v0, arg0, 0x13);
    }
}

s32 func_151ACA60(s32, f32, s32);
s32 func_1514EC1C(s32, s32, s16);

void func_1514D9F4(s32 arg0) {
    s32 v0;
    func_1514D978(arg0);
    v0 = func_151ACA60(arg0, 20.0f, 0);
    func_1514EC1C(v0, arg0, 0x14);
}

void func_1514DA38(s32 arg0) {
    s32 temp_v0;
    struct {
        s32 unk0;
        s32 unk4;
        s32 unk8;
        s32 unkC;
        s32 unk10;
        s32 unk14;
        s32 unk18;
    } sp18;

    sp18.unk14 = 0;
    sp18.unk18 = 0;
    sp18.unk0 = 0;
    sp18.unk4 = 0;
    sp18.unk8 = 0;
    sp18.unkC = 0;
    temp_v0 = func_15158BD0(arg0, 1, 0x1C);
    if (temp_v0 != 0) {
        memcpy((void *)(temp_v0 + 0x58), &sp18, 0x1C);
        func_1514EC1C(temp_v0, arg0, 0x13);
    }
}

void func_1514DAA4(struct127 *arg0) {
    s32 v0;
    s32 sp1C[2];

    arg0->unk94 |= 0x2;
    sp1C[0] = 0;
    sp1C[1] = 0;
    {
        extern s32 func_15158BD0();

        if ((v0 = func_15158BD0((s32) arg0, 1, 8)) != 0) {
            memcpy((void *)(v0 + 0x58), sp1C, 8);
            func_1514EC1C(v0, (s32) arg0, 0x13);
        }
    }
}

s32 func_15158BD0(s32, s32, s32);
s32 func_1514EC1C(s32, s32, s16);

void func_1514DB18(s32 arg0) {
    s32 v0 = func_15158BD0(arg0, 1, 0);
    if (v0 != 0) {
        func_1514EC1C(v0, arg0, 0x13);
    }
}

void func_1514DB58(s32 arg0) {
}

extern s32 D_800BE9F0;
void func_151B2060(void);

void func_1514DB64(void) {
    if (D_800BE9F0 == 0x14) {
        func_151B2060();
    }
}

void func_1514F194();

void func_1514DB98(void) {
    func_1514F194();
}

void func_1514DBB8(s32 arg0) {
    func_15160A58(arg0, 2, &D_800A58A0, 2, 0x12C, 0x28, 0xFF, 0xFF, 0xFF, 0xFF, 0, -1, 0, 0, 0xFF, 1);
}

void func_1514DC38(struct127 *arg0) {
    func_1500EE18(arg0, 0xFF, 1);
}

void func_151D0F60(void *, s32, s32, s32);

void func_1514DC5C(void *arg0) {
    func_151D0F60(arg0, 0, 0xFF, 1);
}

typedef struct {
    u8 pad0[0x94];
    /* 0x94 */ s32 unk94;
} S1514DC84;

void func_1514DC84(S1514DC84 *arg0) {
    arg0->unk94 |= 0x2;
}

typedef struct {
    u8 pad0[0x94];
    /* 0x94 */ s32 unk94;
} S1514DC98;

void func_1514DC98(S1514DC98 *arg0) {
    arg0->unk94 |= 0x710;
}

void func_1514DCAC(arg0)
struct127 *arg0;
{
    *(s32 *)((u8 *)arg0 + 0x9C) = 0x6000;
    func_15083568(arg0, 0x23, 1.0f, 0);
    func_15083568(arg0, 0x44, 1.0f, 0);
}

struct struct1514DCF4 {
    u8 pad[0x31C];
    struct127 *unk31C;
};

void func_1514DCF4(struct struct1514DCF4 *arg0) {
    if (arg0->unk31C != NULL) {
        *(u8 *)((u8 *)arg0->unk31C + 0x94) = 1;
    }
    func_15083568((struct127 *)arg0, 0x17, 1.0f, 0);
}

void func_1514DD2C(void) {
    func_1514DCAC();
}

void func_1514DD4C(void) {
    func_1514DCAC();
}

void func_1514DD6C(void) {
    func_1514DCAC();
}

void func_1514DD8C(void) {
    func_1514DCAC();
}

void func_1514DDAC(void) {
    func_1514DCAC();
}

void func_1514DDCC(void) {
    func_1514DCAC();
}

void func_1514DDEC(void) {
    func_1514DCAC();
}

void func_1514DE0C(void) {
    func_1514DCAC();
}

void func_1514DE2C(s32 arg0) {
}

void func_1514DE38(s32 arg0) {
}

void func_1514DE44(s32 arg0) {
}

void func_1514DE50(void) {
    if (((u8 *)D_800D2E4C)[0x11] & 8) {
        func_1514DCAC();
    }
}

void func_1514DE88(s32 arg0) {
}

void func_15160CDC(s32, s32, void *, void *, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_15160A58(s32, s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern f32 D_800A5E04;
extern u8 D_800A58AC;
extern u8 D_800A58B8;
extern u8 D_800A58C4;
extern u8 D_800BE9B4;

void func_1514DE94(s32 arg0) {
    struct St1514DE94 *temp;

    func_15160CDC(arg0, 0xC, &D_800A58AC, &D_800A58B8, D_800A5E04, 2, 0x12C,
                  0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 1, 0xFF, 1);
    temp = func_15083568((struct127 *)arg0, 0x3C, 1.0f, 0);
    if (D_800BE9B4 == 0) {
        temp->unk38 = 0x960;
    }
    func_1514EC1C(func_15160A58(arg0, 0, &D_800A58C4, 2, 0x12C, 0xB, 0xFF, 0xFF, 0xFF, 2, 0, -1, 0, 0, 0xFF, 1), arg0, 0x19);
}

s32 func_15083FB0(s32);

void func_1514DFD0(u8 *arg0) {
    arg0[0x65] = func_15083FB0(9) + 1;
    arg0[0x101] |= 0x34;
}

void func_1514E00C(s32 arg0) {
    Struct1514E00C_A4 spA4;
    Struct1514E00C_4C sp4C;
    Struct1514E00C_2C sp2C;

    sp4C.unk00 = 3;
    sp4C.unk08 = 0;
    sp4C.unk0C = 0;
    sp4C.unk40 = 0x12002;
    sp4C.unk04 = 0;
    sp4C.unk45 = 0xFF;
    sp4C.unk10 = 0xFF;
    sp4C.unk11 = 0x8E;
    sp4C.unk12 = 0x19;
    sp4C.unk13 = 0xFF;
    sp4C.unk02 = 0x401;
    sp4C.unk1C = 0.0f;
    sp4C.unk20 = 0.0f;
    sp4C.unk24 = 0.0f;
    sp4C.unk28 = 0.0f;
    sp4C.unk2C = 0.0f;
    sp4C.unk30 = 0.0f;

    spA4.unk00 = 20.0f;
    spA4.unk04 = 20.0f;
    spA4.unk08 = 20.0f;
    spA4.unk0C = 20.0f;
    spA4.unk10 = 0.0f;
    spA4.unk14 = 0.0f;
    spA4.unk18 = 0.5f;
    spA4.unk1C = 0.5f;
    spA4.unk20 = D_800A5E08;

    sp2C.unk1D = ((u8 *)arg0)[0x3B];
    sp2C.unk00 = 35.0f;
    sp2C.unk04 = 27.0f;
    sp2C.unk0C = 35.0f;
    sp2C.unk10 = 27.0f;
    sp2C.unk18 = arg0;
    sp2C.unk1C = 6;
    spA4.unk54 = 0;
    spA4.unk55 = 0;
    spA4.unk56 = 0;
    spA4.unk57 = 0;
    sp2C.unk1E = -1;

    sp2C.unk08 = 59.0f;
    sp2C.unk14 = D_800A5E0C;
    spA4.unk48 = 1.0f;

    func_1514EC1C(func_15189FF0(&sp4C, &spA4, &sp2C, 2, 0, 0, 0), arg0, 6);
    func_151D74B0(arg0, 5, -1, 0xFF, 1);
}

void func_1514E194(s32 arg0) {
    Struct1514E00C_A4 spA4;
    Struct1514E00C_4C sp4C;
    Struct1514E00C_2C sp2C;

    sp4C.unk00 = 3;
    sp4C.unk08 = 0;
    sp4C.unk0C = 0;
    sp4C.unk40 = 0x12002;
    sp4C.unk04 = 0;
    sp4C.unk45 = 0xFF;
    sp4C.unk10 = 0xFF;
    sp4C.unk11 = 0x8E;
    sp4C.unk12 = 0x19;
    sp4C.unk13 = 0xFF;
    sp4C.unk02 = 0x401;
    sp4C.unk1C = 0.0f;
    sp4C.unk20 = 0.0f;
    sp4C.unk24 = 0.0f;
    sp4C.unk28 = 0.0f;
    sp4C.unk2C = 0.0f;
    sp4C.unk30 = 0.0f;

    spA4.unk00 = 16.0f;
    spA4.unk04 = 16.0f;
    spA4.unk08 = 16.0f;
    spA4.unk0C = 16.0f;
    spA4.unk10 = 0.0f;
    spA4.unk14 = 0.0f;
    spA4.unk18 = 0.5f;
    spA4.unk1C = 0.5f;
    spA4.unk20 = D_800A5E10;

    sp2C.unk1D = ((u8 *)arg0)[0x3B];
    sp2C.unk00 = 35.0f;
    sp2C.unk04 = 27.0f;
    sp2C.unk0C = 35.0f;
    sp2C.unk10 = 27.0f;
    sp2C.unk18 = arg0;
    sp2C.unk1C = 6;
    spA4.unk54 = 0;
    spA4.unk55 = 0;
    spA4.unk56 = 0;
    spA4.unk57 = 0;
    sp2C.unk1E = -1;

    sp2C.unk08 = 59.0f;
    sp2C.unk14 = D_800A5E14;
    spA4.unk48 = 1.0f;

    func_1514EC1C(func_15189FF0(&sp4C, &spA4, &sp2C, 2, 0, 0, 0), arg0, 6);
    func_151D74B0(arg0, 5, -1, 0xFF, 1);
}

void func_1514E31C(s32 arg0) {
    Struct1514E00C_A4 spA4;
    Struct1514E00C_4C sp4C;
    Struct1514E00C_2C sp2C;

    sp4C.unk00 = 3;
    sp4C.unk08 = 0;
    sp4C.unk0C = 0;
    sp4C.unk40 = 0x2012;
    sp4C.unk04 = 0;
    sp4C.unk45 = 0xFF;
    sp4C.unk10 = 0xFF;
    sp4C.unk11 = 0xE6;
    sp4C.unk12 = 0;
    sp4C.unk13 = 0xFF;
    sp4C.unk02 = 0x401;
    sp4C.unk1C = 0.0f;
    sp4C.unk20 = 0.0f;
    sp4C.unk24 = 0.0f;
    sp4C.unk28 = 0.0f;
    sp4C.unk2C = 0.0f;
    sp4C.unk30 = 0.0f;

    spA4.unk00 = 45.0f;
    spA4.unk0C = 45.0f;
    spA4.unk10 = 0.5f;
    spA4.unk14 = 0.5f;
    spA4.unk1C = 0.0f;
    spA4.unk04 = 55.0f;
    spA4.unk08 = 25.0f;
    spA4.unk18 = D_800A5E18;
    spA4.unk20 = D_800A5E1C;

    sp2C.unk1D = ((u8 *)arg0)[0x3B];
    sp2C.unk00 = 0.0f;
    sp2C.unk04 = 0.0f;
    sp2C.unk0C = 0.0f;
    sp2C.unk10 = 0.0f;
    sp2C.unk18 = arg0;
    sp2C.unk1C = 0xC;
    spA4.unk54 = 0;
    spA4.unk55 = 0;
    spA4.unk56 = 0;
    spA4.unk57 = 0;
    sp2C.unk1E = 2;

    sp2C.unk08 = 100.0f;
    sp2C.unk14 = 600.0f;
    spA4.unk48 = 1.0f;

    func_1514EC1C(func_15189FF0(&sp4C, &spA4, &sp2C, 2, 3, 0, 0), arg0, 7);

    {
        struct {
            f32 unk0;
            f32 unk4;
            f32 unk8;
        } sp50;

        sp50.unk0 = 0.0f;
        sp50.unk4 = 0.0f;
        sp50.unk8 = 150.0f;
        func_15160A58(arg0, 0xC, &sp50, 2, 0x12C, 0x28, 0xFF, 0xB5, 0, 0xFF, 0, 2, 0, 0, 0xFF, 1);
    }
}

void func_1514E508(s32 arg0) {
    s32 v0;
    s32 temp;

    v0 = func_1518D1C0(arg0, 5, 0, 1, 0xFF, 1, &D_800A58D0);
    func_1514EC1C(v0, arg0, 0xD);
    temp = arg0 + 0x14;
    v0 = func_1515D5F8(-0x8000, temp >> 16, temp & 0xFFFF, 5, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0);
    func_1514EC1C(v0, arg0, 0x18);
}

void func_1514E5B8(s32 arg0) {
    s32 v0;
    s32 temp;

    v0 = func_1518D1C0(arg0, 5, 0, 1, 0xFF, 1, &D_800A58E4);
    func_1514EC1C(v0, arg0, 0xD);
    temp = arg0 + 0x14;
    v0 = func_1515D5F8(-0x8000, temp >> 16, temp & 0xFFFF, 5, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0);
    func_1514EC1C(v0, arg0, 0x18);
}

void func_1514E668(s32 arg0) {
    s32 v0;
    s32 temp;

    v0 = func_1518D1C0(arg0, 5, 0, 1, 0xFF, 1, &D_800A58F8);
    func_1514EC1C(v0, arg0, 0xD);
    temp = arg0 + 0x14;
    v0 = func_1515D5F8(-0x8000, temp >> 16, temp & 0xFFFF, 5, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0);
    func_1514EC1C(v0, arg0, 0x18);
}

void func_1514E718(s32 arg0) {
    s32 v0;
    s32 temp;

    v0 = func_1518D1C0(arg0, 5, 0, 1, 0xFF, 1, &D_800A590C);
    func_1514EC1C(v0, arg0, 0xE);
    temp = arg0 + 0x14;
    v0 = func_1515D5F8(-0x8000, temp >> 16, temp & 0xFFFF, 5, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0);
    func_1514EC1C(v0, arg0, 0x18);
}

void func_1514E7C8(s32 arg0) {
    s32 v0;

    v0 = func_1518D1C0(arg0, 7, 0, 1, 0xFF, 1, &D_800A5920);
    func_1514EC1C(v0, arg0, 0xF);
}

void func_1514E824(s32 arg0) {
}

void func_1514E830(struct102 *arg0) {
    func_1516972C(arg0);
}

void func_1518E308(void *);

void func_1514E850(void *arg0) {
    func_1518E308(arg0);
    func_1516972C(arg0);
}

void func_1514E87C(void) {
    func_1515F10C();
}

s32 func_1514E89C(arg0, arg1, arg2)
s32 arg0;
s32 arg1;
s32 arg2;
{
    s32 flags;

    switch (arg1) {
    case 0:
        flags = *(s32 *) (arg0 + 0x10);
        if (flags & 1) {
            *(s32 *) (arg0 + 0x10) = flags & ~1;
        } else {
            *(s32 *) (arg0 + 0x10) = flags | 1;
        }
        break;
    case 2:
        *(s32 *) (arg0 + 0x10) = *(s32 *) (arg0 + 0x10) & ~1;
        break;
    case 1:
        *(s32 *) (arg0 + 0x10) = *(s32 *) (arg0 + 0x10) | 1;
        break;
    default:
        return 0;
    }
    return 1;
}

s32 func_1514E89C();

s32 func_1514E920(arg0, arg1, arg2)
s32 arg0;
s32 arg1;
s32 arg2;
{
    u8 *sub;
    s32 flags;
    u8 *ptr;

    sub = (u8 *) arg0 + 0x110;
    switch (arg1) {
    case 0:
        flags = *(s32 *) (arg0 + 0x10);
        if (flags & 1) {
            *(s32 *) (arg0 + 0x10) = flags & ~1;
            ptr = *(u8 **) (sub + 0x44);
            if (ptr != 0) {
                ptr[0x30] = 0;
            }
        } else {
            *(s32 *) (arg0 + 0x10) = flags | 1;
        }
        break;
    case 2:
        *(s32 *) (arg0 + 0x10) = *(s32 *) (arg0 + 0x10) & ~1;
        ptr = *(u8 **) (sub + 0x44);
        if (ptr != 0) {
            ptr[0x30] = 0;
        }
        break;
    case 1:
        *(s32 *) (arg0 + 0x10) = *(s32 *) (arg0 + 0x10) | 1;
        break;
    default:
        return func_1514E89C(arg0, arg1, arg2);
    }
    return 1;
}

s32 func_1514E920();

void func_1514E9DC(void) {
    func_1514E920();
}

s32 func_1514E89C();

void func_1514E9FC(void) {
    func_1514E89C();
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514EA1C.s")

void func_1514EB6C(void) {
    func_1514E89C();
}

s32 func_1514EB8C(s32 arg0, s32 arg1, s32 arg2) {
    return 1;
}

struct_1514EBA4 *func_1514EBA4(s32 arg0, s16 arg1, s32 arg2) {
    struct_1514EBA4 *ret;

    ret = func_15167A68(0x24, 1, arg2 + 0x20, 1, 0xFF, 1);
    if (ret == 0) {
        return NULL;
    }
    ret->unk10 = arg0;
    ret->unk14 = 0;
    ret->unk18 = 0;
    ret->unk1C = arg1;
    return ret;
}

s32 func_1514EC1C(s32 arg0, s32 arg1, s16 arg2) {
    s32 result;
    struct_1514EBA4 *ret;

    result = 0;
    if (arg0 != 0) {
        ret = func_1514EBA4(arg0, arg2, 0);
        result = (s32) ret;
        if (ret != 0) {
            ret->unk14 = (s32) ((Cont1514D310 *) arg1)->unk2F4;
            ((Cont1514D310 *) arg1)->unk2F4 = (Node1514D310 *) ret;
            ret->unk18 = 0;
            if (ret->unk14 != 0) {
                ((struct_1514EBA4 *) ret->unk14)->unk18 = (s32) ret;
            }
        } else if (D_8008ABE8[arg2]->unk2 != -1) {
            D_8008AB58[D_8008ABE8[arg2]->unk2](arg0);
        } else {
            func_1516972C((struct102 *) arg0);
        }
    }
    return result;
}

typedef struct Node1514ECE0 {
    char pad0[0x14];
    struct Node1514ECE0 *unk14;
    char pad18[0x4];
    s16 unk1C;
} Node1514ECE0;

s32 func_1514ECE0(Node1514ECE0 *arg0, s16 arg1, s32 *arg2) {
    s32 found;
    Node1514ECE0 *node;
    Node1514ECE0 *next;

    found = 0;
    node = arg0;
    if (node != 0) {
        do {
            next = node->unk14;
            if (arg1 == node->unk1C) {
                found = 1;
            } else {
                node = next;
            }
        } while (node != 0 && found == 0);
    }

    if (arg2 != 0) {
        *arg2 = (s32) node;
    }
    return found;
}

typedef struct Node1514ED3C {
    char pad0[0x10];
    s32 key;
    struct Node1514ED3C *next;
} Node1514ED3C;

s32 func_1514ED3C(Node1514ED3C *node, s32 key, s32 *out) {
    s32 found = 0;
    Node1514ED3C *cur = node;
    Node1514ED3C *next;
    if (cur != 0) {
        do {
            next = cur->next;
            if (key == cur->key) {
                found = 1;
            } else {
                cur = next;
            }
        } while (cur != 0 && found == 0);
    }
    if (out != 0) {
        *out = (s32) cur;
    }
    return found;
}

typedef struct Node1514ED8C {
    char pad0[0x10];
    s32 unk10;
    struct Node1514ED8C *unk14;
    struct Node1514ED8C *unk18;
} Node1514ED8C;

typedef struct Cont1514ED8C {
    char pad0[0x2F4];
    Node1514ED8C *unk2F4;
} Cont1514ED8C;

s32 func_1514ED8C(Node1514ED8C *node, Cont1514ED8C *cont) {
    s32 ret;
    if (node == cont->unk2F4) {
        cont->unk2F4 = node->unk14;
    }
    if (node->unk14 != 0) {
        node->unk14->unk18 = node->unk18;
    }
    if (node->unk18 != 0) {
        node->unk18->unk14 = node->unk14;
    }
    ret = node->unk10;
    func_1516972C((struct102 *) node);
    return ret;
}

void func_1514EDF0(s32 key, Cont1514ED8C *cont) {
    Node1514ED8C *node;
    s32 ret;
    s32 out;
    u8 found;

    node = cont->unk2F4;
    out = 0;
    do {
        ret = func_1514ED3C((Node1514ED3C *) node, key, &out);
        found = ret;
        if (ret) {
            node = ((Node1514ED8C *) out)->unk14;
            func_1514ED8C((Node1514ED8C *) out, cont);
        }
    } while (found != 0);
}

struct Struct1514EE70 {
    s32 unk0;
    u8 unk4;
    u8 unk5;
    u16 unk6;
};

s32 func_1515BE50(struct Struct1514EE70 *, s32, s32, s32);

void func_1514EE70(u8 *arg0) {
    struct Struct1514EE70 sp20;
    s32 v0;

    sp20.unk0 = (s32) arg0;
    sp20.unk4 = arg0[0x3B];
    sp20.unk5 = 0;
    sp20.unk6 = 0x12C;
    v0 = func_1515BE50(&sp20, 0, 0xFF, 1);
    func_1514EC1C(v0, (s32) arg0, 0x16);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514EECC.s")

void func_1514F110(void) {
    func_1514F194();
}

s32 func_1514F130(HudSpriteHandle *arg0, s32 arg1, s32 arg2) {
    switch (arg1) {
    case 13:
        arg0->field_0x14->field_0x09 = 0;
        break;
    case 14:
        arg0->field_0x14->field_0x09 = 1;
        break;
    default:
        return func_1514E89C((s32) arg0, arg1, arg2);
    }
    return 1;
}

void func_1514F194(s32 arg0) {
    s32 v0;

    func_151D0F60((void *)arg0, 1, 0xFF, 1);
    func_151D0F60((void *)arg0, 2, 0xFF, 1);
    func_151BB044(arg0);
    if (D_800BE616 == 0) {
        func_151BC074(arg0);
    }
    func_151BD2F8((void *)arg0, 0xFF, 1);
    func_151B9F00((void *)arg0, 0xFF, 1);
    func_15160A58(arg0, 1, &D_800A5958, 2, 0x12C, 0xC, 0xFF, 0xFF, 0xFF, 2, 0, -1, 0, 0, 0xFF, 1);
    v0 = func_15160A58(arg0, 1, &D_800A5964, 2, 0x12C, 0xF, 0xFF, 0, 0, 0xFF, 1, -1, 0, 0, 0xFF, 1);
    if (v0 != 0) {
        func_1514EC1C(v0, arg0, 0x19);
    }
}

void func_1514F308(s32 arg0) {
    Vec3w1514F308 sp54;
    Vec3w1514F308 sp48;

    sp54 = D_800A5970;
    sp48 = D_800A597C;
    func_15160CDC(arg0, 5, &sp54, &sp48, D_800A5E58, 2, 0x12C,
                  0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 0, 0xFF, 1);
}

void func_1514F3CC(struct127 *arg0) {
    struct {
        struct127 *unk0;
        u8 unk4;
        f32 unk8;
    } sp34;
    struct260 *temp_v0;

    sp34.unk0 = arg0;
    sp34.unk4 = arg0->unique_id;
    sp34.unk8 = 0.0f;

    temp_v0 = func_15149130(0x12C, -1, 0x3A, -1, 0, 0x2B, (struct37 *)0xC, 0xFF, 1);
    if (temp_v0 != NULL) {
        memcpy((void *)((s32)temp_v0 + 0x28), &sp34, 0xC);
    }
}

extern s32 D_800A5988;
s32 func_1518D1C0(s32, s32, s32, s32, s32, s32, s32 *);

void func_1514F44C(s32 arg0) {
    s32 v0;

    v0 = func_1518D1C0(arg0, 5, 0, 1, 0xFF, 1, &D_800A5988);
    func_1514EC1C(v0, arg0, 0xD);
}

extern void func_151D74B0(s32, s32, s32, s32, s32);

void func_1514F4A8(s32 arg0) {
    func_151D74B0(arg0, 1, -1, 0xFF, 1);
}

void func_1514F4D8(s32 arg0) {
    func_151D74B0(arg0, 2, 1, 0xFF, 1);
}

void func_1514F508(s32 arg0) {
    func_151D74B0(arg0, 3, 0, 0xFF, 1);
}

void func_1514F538(s32 arg0) {
    func_151D74B0(arg0, 4, -1, 0xFF, 1);
}

void func_1514F568(s32 arg0) {
    func_150C4120(arg0, -1, 0xFF, 1);
}

void func_1501175C(struct127 *arg0, u8 arg1, s32 arg2);

void func_1514F590(struct127 *arg0) {
    func_1501175C(arg0, 0xFF, 1);
    func_15011A78(arg0, 0xFF, 1);
}

void func_1514F5CC(struct127 *arg0) {
    Struct1514F5CCArg sp1C;

    sp1C.unk00 = 0;
    sp1C.unk08 = arg0;
    sp1C.unk04 = 0.0f;
    sp1C.unk0C = arg0->unique_id;
    sp1C.unk10 = D_800A5E5C;
    sp1C.unk14 = 0x14;
    sp1C.unk16 = 0x12C;
    sp1C.unk18 = 4;
    func_150C0AC0(&sp1C, 0xFF, 1);
}
