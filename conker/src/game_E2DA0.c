#include <ultra64.h>
/* functions.h types func_150ADA20 as returning u8; golden spills/uses the full u32 return
 * (same shadow-prototype idiom as game_121A20.c). */
#define func_150ADA20 func_150ADA20_u8_decl_in_functions_h
#include "functions.h"
#undef func_150ADA20
u32 func_150ADA20(void);
#include "variables.h"

extern f32 D_8009FC98;
extern f32 D_8009FC9C;
extern f32 D_8009FCA0;
extern f32 D_8009FCA4;
extern f32 D_8009FCA8;
extern f32 D_8009FCAC;
extern f32 D_8009FCB0;
extern f32 D_8009FCB4;
extern f32 D_8009FCB8;
extern s32 D_8009FC3C[][3];
extern f32 D_8009FC60[];
extern f32 D_8009FC6C[];
extern f32 D_8009FC78[];
extern s16 D_8009FC84[];
extern s16 D_8009FC8E[][2];
extern f32 D_8009FCCC;
extern f32 D_8009FCD0;
extern f32 D_8009FCD4;
extern f32 D_8009FCD8;
extern f32 D_8009FCDC;
extern f32 D_8009FCE0;
extern f32 D_8009FCE4;
f32 func_151423D8(u8);
void func_15143794(s32, s32, f32, f32 *);
void func_150B3F5C(void *, void *, s16);
void func_150B5A3C(f32 *arg0, u8 arg1, s32 arg2);
void func_150B5E34(f32 *arg0, u8 arg1, s32 arg2);
void func_150B6000(f32 *arg0, u8 arg1, s32 arg2);
void func_150B60E0(s32 *arg0, s32 arg1);
void func_15152B38(void *arg0, u8 arg1, s32 arg2);

typedef struct {
    /* 0x0 */ s32 a;
    /* 0x4 */ s32 b;
    /* 0x8 */ s32 c;
} Struct3W_E2DA0;

typedef struct Obj150B5950 {
    s32 unk0;
    u8 pad4[0x10];
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    u8 pad20[0x1B];
    u8 unk3B;
    u8 pad3C[0x198];
    s32 unk1D4;
} Obj150B5950;

typedef struct Arg150B5950 {
    u8 unk0;
    u8 unk1;
    u8 pad2[0xA];
    u8 unkC;
    u8 padD;
    s16 unkE;
    u8 pad10[0x18];
    Obj150B5950 *unk28;
    u8 unk2C;
} Arg150B5950;

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ Struct3W_E2DA0 unk08;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 unk32;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ s16 unk3E;
    /* 0x40 */ s16 unk40;
    /* 0x42 */ u8 unk42;
    /* 0x43 */ u8 unk43;
    /* 0x44 */ u8 unk44;
    /* 0x45 */ u8 unk45;
    /* 0x46 */ u8 unk46;
    /* 0x47 */ u8 unk47;
    /* 0x48 */ u8 unk48;
    /* 0x49 */ u8 unk49;
    /* 0x4A */ u8 unk4A;
    /* 0x4B */ u8 unk4B;
    /* 0x4C */ u8 unk4C;
    /* 0x4D */ u8 unk4D;
    /* 0x4E */ u8 unk4E;
    /* 0x4F */ u8 unk4F;
    /* 0x50 */ u8 unk50;
    /* 0x51 */ u8 unk51;
    /* 0x52 */ u8 unk52;
    /* 0x53 */ u8 unk53;
    /* 0x54 */ u8 unk54;
    /* 0x55 */ u8 unk55;
    /* 0x56 */ u8 unk56;
    /* 0x57 */ u8 unk57;
    /* 0x58 */ u8 unk58;
    /* 0x59 */ u8 pad59[3];
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s16 unk64;
    /* 0x66 */ s16 unk66;
    /* 0x68 */ s16 unk68;
    /* 0x6A */ u8 unk6A;
    /* 0x6B */ u8 pad6B;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ s8 unk70;
    /* 0x71 */ s8 unk71;
    /* 0x72 */ s8 unk72;
    /* 0x73 */ s8 unk73;
} Struct150B5A3C;


u16 *func_150B58F0(u16 *arg0, s32 arg1) {
    if (D_800C35EA == 1) {
        return arg0;
    }
    arg0[0] = 0x1A;
    arg0[1] = *(u16 *)((u8 *)D_800CC34A + 812 * arg1);
    return arg0 + 2;
}

void func_150B5950(Arg150B5950 *arg0) {
    vertex *sp28p;
    vertex sp28;
    Obj150B5950 *obj;

    obj = arg0->unk28;
    sp28p = &sp28;
    if ((obj->unk0 == 0) || (obj->unk3B != arg0->unk2C)) {
        arg0->unkE = -1;
        return;
    }

    if (obj->unk1D4 != 0) {
        if (func_150ADA68() < D_8009FC98) {
            sp28.x = obj->unk14;
            sp28.y = obj->unk18;
            sp28.z = obj->unk1C;
            func_150B5A3C((f32 *)sp28p, arg0->unkC, arg0->unk1);
        }

        if (func_150ADA68() < D_8009FC9C) {
            func_150B60E0((s32 *)obj, (s32)sp28p);
            func_150B5A3C((f32 *)sp28p, arg0->unkC, arg0->unk1);
        }
    }
}

void func_150B5A3C(f32 *arg0, u8 arg1, s32 arg2) {
    Struct150B5A3C sp1C;

    sp1C.unk00 = 5;
    sp1C.unk04 = 5;
    sp1C.unk08 = *(*(Struct3W_E2DA0 **)&arg0);
    sp1C.unk14 = 20.0f;
    sp1C.unk18 = D_8009FCA0;
    sp1C.unk1C = D_8009FCA4;
    sp1C.unk20 = D_8009FCA8;
    sp1C.unk24 = 39.0f;
    sp1C.unk28 = 35.0f;
    sp1C.unk2C = 0;
    sp1C.unk2E = 0xFF;
    sp1C.unk30 = -0x1F;
    sp1C.unk32 = 0x50;
    sp1C.unk34 = 3;
    sp1C.unk38 = 2;
    sp1C.unk3C = 0x14;
    sp1C.unk3E = 0x1E;
    sp1C.unk40 = 1;
    sp1C.unk42 = 4;
    sp1C.unk43 = 2;
    sp1C.unk44 = 3;
    sp1C.unk45 = 0xFF;
    sp1C.unk46 = 0xFF;
    sp1C.unk47 = 0xFF;
    sp1C.unk48 = 0xFF;
    sp1C.unk49 = 0;
    sp1C.unk4A = 0;
    sp1C.unk4B = 0;
    sp1C.unk4C = 0;
    sp1C.unk4D = 0xFF;
    sp1C.unk4E = 0xFF;
    sp1C.unk4F = 0xFF;
    sp1C.unk50 = 0xFF;
    sp1C.unk51 = 0;
    sp1C.unk52 = 0;
    sp1C.unk53 = 0;
    sp1C.unk54 = 0;
    sp1C.unk55 = 0xFF;
    sp1C.unk56 = 0;
    sp1C.unk57 = 3;
    sp1C.unk58 = 0x24;
    sp1C.unk5C = 0x200005;
    sp1C.unk60 = 0x60600;
    sp1C.unk64 = 8;
    sp1C.unk66 = 0x1F;
    sp1C.unk68 = 1;
    sp1C.unk6A = 0;
    sp1C.unk6C = 1.0f;
    sp1C.unk70 = -1;
    sp1C.unk71 = 0;
    sp1C.unk72 = -1;
    sp1C.unk73 = -1;

    func_15152B38(&sp1C, arg1, arg2);
    func_150B5E34(arg0, arg1, arg2);
    func_150B6000(arg0, arg1, arg2);
}

void func_150B5C38(f32 *arg0, u8 arg1, s32 arg2) {
    Struct150B5A3C sp1C;

    sp1C.unk00 = 0xD;
    sp1C.unk04 = 8;
    sp1C.unk08 = *(*(Struct3W_E2DA0 **)&arg0);
    sp1C.unk14 = D_8009FCAC;
    sp1C.unk18 = D_8009FCB0;
    sp1C.unk1C = D_8009FCB4;
    sp1C.unk20 = D_8009FCB8;
    sp1C.unk24 = 152.0f;
    sp1C.unk28 = 100.0f;
    sp1C.unk2C = 0;
    sp1C.unk2E = 0xFF;
    sp1C.unk30 = -0x14;
    sp1C.unk32 = 0x32;
    sp1C.unk34 = 3;
    sp1C.unk38 = 2;
    sp1C.unk3C = 0x14;
    sp1C.unk3E = 0xF;
    sp1C.unk40 = 1;
    sp1C.unk42 = 4;
    sp1C.unk43 = 2;
    sp1C.unk44 = 3;
    sp1C.unk45 = 0xFF;
    sp1C.unk46 = 0xFF;
    sp1C.unk47 = 0xB4;
    sp1C.unk48 = 0xFF;
    sp1C.unk49 = 0;
    sp1C.unk4A = 0;
    sp1C.unk4B = 0;
    sp1C.unk4C = 0;
    sp1C.unk4D = 0xFF;
    sp1C.unk4E = 0xFF;
    sp1C.unk4F = 0xB4;
    sp1C.unk50 = 0xFF;
    sp1C.unk51 = 0;
    sp1C.unk52 = 0;
    sp1C.unk53 = 0;
    sp1C.unk54 = 0;
    sp1C.unk55 = 0xFF;
    sp1C.unk56 = 0;
    sp1C.unk57 = 3;
    sp1C.unk58 = 0x24;
    sp1C.unk5C = 0x200005;
    sp1C.unk60 = 0x60600;
    sp1C.unk64 = 8;
    sp1C.unk66 = 0x1F;
    sp1C.unk68 = 1;
    sp1C.unk6A = 0;
    sp1C.unk6C = 1.0f;
    sp1C.unk70 = -1;
    sp1C.unk71 = 0;
    sp1C.unk72 = -1;
    sp1C.unk73 = -1;

    func_15152B38(&sp1C, arg1, arg2);
    func_150B5E34(arg0, arg1, arg2);
    func_150B6000(arg0, arg1, arg2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_E2DA0/func_150B5E34.s")

void func_150B6000(f32 *arg0, u8 arg1, s32 arg2) {
    Header header;
    Header2 header2;

    header.unk0 = 3;
    header.unk1 = -1;
    header.unk2 = (func_150ADA20() % 9U) + 3;
    header.unk4 = 0;

    header2.unk0 = (s32) arg0[0];
    header2.unk4 = (s32) arg0[1];
    header2.unk8 = (s32) arg0[2];

    func_151602C0(&header, &header2, (func_150ADA20() % 0xC9U) + 0x37, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, arg1, arg2);
}

extern void func_15143134(void *, s32, s32);
extern s32 D_8009FC30;

void func_150B60E0(s32 *arg0, s32 arg1) {
    func_15143134(&D_8009FC30, arg1, arg0[0x1D4 / 4] + 0x140);
}

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    u8 padA[0xA];
    u8 unk14;
} Obj150B6110;

typedef struct {
    Obj150B6110 *obj;
    f32 accum;
} Data150B6110;

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 pad2[0xA];
    u8 unkC;
    u8 padD[0x1B];
    Obj150B6110 *unk28;
    f32 unk2C;
    u8 unk30;
} Arg150B6110;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec150B6110;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s32 unk20;
    s32 unk24;
    u8 unk28;
    u8 unk29;
    u8 unk2A;
    u8 unk2B;
    u8 unk2C;
} Desc150B6110;

extern f32 D_8009FCBC;
extern f32 D_8009FCC0;
extern f32 D_8009FCC4;
extern f32 D_8009FCC8;
extern void func_1514373C(f32 arg0, f32 arg1, f32 *arg2, f32 *arg3);
extern void func_15106F98(Vec150B6110 *, Vec150B6110 *, s32, Desc150B6110 *, f32, s32, s32, s32);

void func_150B6110(Arg150B6110 *arg0) {
    Data150B6110 *data;
    Obj150B6110 *obj;
    u8 prev;
    u8 a;

    obj = arg0->unk28;
    prev = arg0->unk30;
    arg0->unk30 = obj->unk14;
    if (obj->unk14 == 1) {
        if (arg0->unk30 != prev) {
            func_151494E0(0, 0x4A);
        }
        return;
    }
    data = (Data150B6110 *)((u8 *)arg0 + 0x28);
    data->accum += (D_8009FCBC + func_150ADA68() * D_8009FCC0) * D_800BE9A4;
    if (data->accum > 1.0f) {
        Desc150B6110 desc;
        Vec150B6110 from;
        Vec150B6110 to;
        f32 size;

        desc.unk0 = 35.0f;
        desc.unk4 = 35.0f;
        desc.unk8 = 76.0f;
        desc.unkC = 103.0f;
        desc.unk10 = D_8009FCC4;
        desc.unk14 = 0x28;
        desc.unk16 = 0;
        desc.unk18 = 4;
        desc.unk1A = 3;
        desc.unk1C = 7;
        desc.unk20 = 4;
        desc.unk24 = 3;
        desc.unk28 = 0x7E;
        desc.unk29 = 0xF9;
        desc.unk2A = 0xFF;
        desc.unk2B = 0x7F;
        desc.unk2C = 0x80;
        size = D_8009FCC8;
        from.y = obj->unk2 + obj->unk8;
        to.y = obj->unk2 + obj->unk8;
        do {
            a = func_150ADA20();
            func_1514373C((u32)a, obj->unk6, &from.x, &from.z);
            from.x += obj->unk0;
            from.z += obj->unk4;
            a += func_150ADA20() % 129 + 64;
            func_1514373C((u32)a, obj->unk6, &to.x, &to.z);
            to.x += obj->unk0;
            to.z += obj->unk4;
            func_15106F98(&from, &to, 4, &desc, size, 1, arg0->unkC, arg0->unk1);
            data->accum -= 1.0f;
        } while (data->accum > 1.0f);
    }
}

void func_150B6450(struct102 *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 0x4A) {
        func_1516972C(arg0);
    }
}

typedef struct {
    f32 unk00;
    f32 unk04;
    f32 unk08;
    f32 unk0C;
    u8 unk10;
    u8 pad11[3];
    f32 unk14;
    f32 unk18;
    u8 unk1C;
    u8 pad1D[3];
    f32 unk20;
    u8 unk24;
    u8 pad25;
    s16 unk26;
    f32 unk28;
    f32 unk2C;
    u8 unk30;
    u8 unk31;
    u8 unk32;
    u8 unk33;
    u8 unk34;
    u8 unk35;
    s16 unk36;
    u8 unk38;
    u8 pad39[3];
    f32 unk3C;
} Stack150B648C;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3F150B648C;

void func_150B648C(u8 arg0) {
    Stack150B648C sp30;
    Vec3F150B648C sp24;

    if (arg0 == 0) {
        sp30.unk00 = func_151423D8(0xAA) * 10.0f;
        sp30.unk04 = 3.0f;
        sp30.unk08 = func_151423D8(0xEA) * 10.0f;
        sp24.x = D_8009FCCC - (func_151423D8(0xAA) * 150.0f);
        sp24.y = D_8009FCD0;
        sp24.z = D_8009FCD4 - (func_151423D8(0xEA) * 150.0f);
    } else if (arg0 == 1) {
        func_15143794(-0x45, 0x1C, 9.349999f, &sp30.unk00);
        sp24 = *(Vec3F150B648C *)D_8009FC3C[arg0];
    } else {
        func_15143794(0x18, 0xF, 9.349999f, &sp30.unk00);
        sp24 = *(Vec3F150B648C *)D_8009FC3C[arg0];
    }

    sp30.unk10 = 4;
    sp30.unk1C = 6;
    sp30.unk0C = D_8009FC60[arg0];
    sp30.unk24 = 0x80;
    sp30.unk26 = 0xFF;
    sp30.unk30 = 2;
    sp30.unk31 = 5;
    sp30.unk32 = 5;
    sp30.unk33 = 0x33;
    sp30.unk34 = 3;
    sp30.unk35 = 0x55;
    sp30.unk38 = 0;
    sp30.unk14 = D_8009FCD8;
    sp30.unk18 = D_8009FCDC;
    sp30.unk20 = D_8009FCE0;
    sp30.unk28 = D_8009FC6C[arg0];
    sp30.unk2C = D_8009FC78[arg0];
    sp30.unk36 = D_8009FC84[arg0];
    sp30.unk3C = D_8009FCE4;
    func_150B3F5C(&sp30, &sp24, D_8009FC8E[arg0][0]);
}

struct inner150B66DC {
    u8 pad[0x68];
    u8 unk68;
};
struct sub150B66DC {
    u8 pad0[0x14];
    u8 *unk14;
    struct inner150B66DC *unk18;
};

s32 func_150B66DC(struct sub150B66DC *arg0) {
    struct inner150B66DC *p = arg0->unk18;
    switch (p->unk68 - 0xF) {
    case 0:
        arg0->unk14[9] = 1;
        break;
    case 1:
        arg0->unk14[9] = 0;
        arg0->unk14[0x2F] = 0x14;
        break;
    case 2:
    default:
        arg0->unk14[9] = 0;
        arg0->unk14[0x2F] = 0x28;
        break;
    }
    return 1;
}

extern void func_15182670(s32, s32, s32, s32, s32, s32, s32, s32);

void func_150B6754(u8 arg0, s32 arg1) {
    u32 temp1;
    u32 temp0;

    temp0 = func_150ADA20();
    temp1 = func_150ADA20();
    func_15182670(0xCC, 0xCC, 0xFF, (u8)(temp0 % 0x38 + 0xC8), temp1 % 0xB + 0xF, 0, arg0, arg1);
}
