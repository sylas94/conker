#include <ultra64.h>
#define func_150ADA20 func_150ADA20_u8_decl_in_functions_h
#include "functions.h"
#undef func_150ADA20
s32 func_150ADA20(void);
#include "variables.h"

const u8 D_800A1C00[8][8] = {
    { 0xFD, 0xFB, 0xF9, 0xF7, 0xF5, 0xF3, 0xF1, 0xEF },
    { 0xFC, 0xFA, 0xF8, 0xF6, 0xF4, 0xF2, 0xF0, 0xEE },
    { 0xE6, 0xE5, 0xE4, 0xE3, 0xE2, 0xE1, 0xE0, 0xDF },
    { 0xDE, 0xDD, 0xDC, 0xDB, 0xDA, 0xD9, 0xD8, 0xD7 },
    { 0xD6, 0xD5, 0xD4, 0xD3, 0xD2, 0xD1, 0xD0, 0xCF },
    { 0xCE, 0xCD, 0xCC, 0xCB, 0xCA, 0xC9, 0xC8, 0xC7 },
    { 0xC6, 0xC5, 0xC4, 0xC3, 0xC2, 0xC1, 0xC0, 0xBF },
    { 0xBE, 0xBD, 0xBC, 0xBB, 0xBA, 0xB9, 0xB8, 0xB7 },
};

const u8 D_800A1C40[8] = { 0, 4, 1, 5, 2, 6, 3, 7 };

const f32 D_800A1C48[3] = { -124.0f, -8.0f, 28.0f };
const f32 D_800A1C54[3] = { -170.0f, -8.0f, 28.0f };

extern f32 func_150ADA68(void);
void func_151541B8(void *, f32, u32, f32, f32, u8, s32);
void func_151D3F14(void *, u8, s32);
struct126 *func_150FF288(struct127 *);
s32 func_150FF6E0(struct17 *, struct17 *, struct17 *, struct17 *, struct17 *, struct127 *, struct126 *);
void func_150FF474(struct17 *, struct17 *, s32, s32);
void func_151D4408(struct17 *, struct17 *, void *, struct127 *, f32, s32, s32);

typedef u8 Func150F9950Entry[0x40];

s32 func_1513264C(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5, s32 arg6);

typedef struct {
    s32 unk0;
    s32 unk4;
    struct17 unk8;
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
    s32 unk34;
    s32 unk38;
    s16 unk3C;
    s16 unk3E;
    u16 unk40;
    u8 unk42;
    u8 unk43;
    u8 unk44;
    u8 unk45;
    u8 unk46;
    u8 unk47;
    u8 unk48;
    u8 unk49;
    u8 unk4A;
    u8 unk4B;
    u8 unk4C;
    u8 unk4D;
    u8 unk4E;
    u8 unk4F;
    u8 unk50;
    u8 unk51;
    u8 unk52;
    u8 unk53;
    u8 unk54;
    u8 unk55;
    u8 unk56;
    u8 unk57;
    u8 unk58;
    u8 pad59[3];
    s32 unk5C;
    s32 unk60;
    s16 unk64;
    s16 unk66;
    s16 unk68;
    u8 unk6A;
    u8 pad6B[1];
    f32 unk6C;
    s8 unk70;
    s8 unk71;
    s8 unk72;
    s8 unk73;
} Func150F85A0Spawn;

extern struct225 *func_151602C0(Header *, Header2 *, s32, s32, s32, s32, u8, u8, s32, u8, s32);
extern void func_15152B38(Func150F85A0Spawn *, u8, s32);

void func_150F85A0(s32 arg0, struct127 *arg1, s32 arg2) {
    struct17 pos;

    pos.unk0 = arg1->x_position;
    pos.unk4 = arg1->y_position + 50.0f;
    pos.unk8 = arg1->z_position;
    {
        Header header;
        Header2 header2;

        header.unk0 = 3;
        header.unk1 = -1;
        header.unk2 = (func_150ADA20() % 9U) + 5;
        header.unk4 = 0;
        header2.unk0 = pos.unk0;
        header2.unk4 = pos.unk4;
        header2.unk8 = pos.unk8;
        func_151602C0(&header, &header2, (func_150ADA20() % 31U) + 90, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0xFF, 1);
    }
    {
        Func150F85A0Spawn spawn;

        spawn.unk0 = 8;
        spawn.unk4 = 0xC;
        spawn.unk8 = pos;
        spawn.unk14 = 3.07f;
        spawn.unk18 = 6.2f;
        spawn.unk1C = -0.9690000415f;
        spawn.unk20 = 0.7180000544f;
        spawn.unk24 = 15.0f;
        spawn.unk28 = 30.0f;
        spawn.unk2C = 0;
        spawn.unk2E = 0xFF;
        spawn.unk30 = -0x40;
        spawn.unk32 = 0x50;
        spawn.unk34 = 3;
        spawn.unk38 = 1;
        spawn.unk3C = 0x14;
        spawn.unk3E = 0xF;
        spawn.unk40 = 1;
        spawn.unk42 = 4;
        spawn.unk43 = 2;
        spawn.unk44 = 3;
        spawn.unk45 = 0xFF;
        spawn.unk46 = 0xFF;
        spawn.unk47 = 0xFF;
        spawn.unk48 = 0xFF;
        spawn.unk49 = 0;
        spawn.unk4A = 0;
        spawn.unk4B = 0;
        spawn.unk4C = 0;
        spawn.unk4D = 0xFF;
        spawn.unk4E = 0xFF;
        spawn.unk4F = 0xFF;
        spawn.unk50 = 0xFF;
        spawn.unk51 = 0;
        spawn.unk52 = 0;
        spawn.unk53 = 0;
        spawn.unk54 = 0;
        spawn.unk55 = 0xFF;
        spawn.unk56 = 0;
        spawn.unk57 = 3;
        spawn.unk58 = 0x24;
        spawn.unk5C = 0x200005;
        spawn.unk60 = 0x60600;
        spawn.unk64 = 8;
        spawn.unk66 = 0x1F;
        spawn.unk68 = 1;
        spawn.unk6A = 0;
        spawn.unk6C = 1.0f;
        spawn.unk70 = -1;
        spawn.unk71 = 0;
        spawn.unk72 = -1;
        spawn.unk73 = -1;
        func_15152B38(&spawn, 0xFF, 1);
    }
}

void func_150F884C(s32 arg0, s32 arg1) {
    s32 sp18[2];
    sp18[0] = arg1;
    func_151494E0((s32)&sp18, 0x3F);
}


typedef struct {
    u8 pad0[0x10];
    s16 unk10;
    s16 unk12;
    s16 unk14;
    u8 pad16[0x58];
    u8 unk6E;
} Func150F892CPart;

typedef struct {
    s32 unk0;
    u8 unk4;
    u8 unk5;
    s16 unk6;
    u8 unk8;
    u8 pad9[3];
    Func150F892CPart *unkC[8];
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    s16 unk3C;
    u8 pad3E[2];
    f32 unk40;
    f32 unk44;
    f32 unk48;
} Func150F892CSub;

typedef struct {
    u8 pad0;
    u8 unk1;
    u8 pad2[0xA];
    u8 unkC;
    u8 padD[0x1B];
    Func150F892CSub unk28;
} Func150F892CArg;

typedef struct {
    u8 unk0;
    u8 pad1;
    s16 unk2;
    u8 unk4;
    u8 unk5;
    s8 unk6;
    u8 pad7;
} Func150F892CMsg;

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
    s8 unk69;
    u8 unk6A;
    u8 pad6B;
    s32 unk6C;
    u8 unk70;
    u8 pad71;
    s16 unk72;
    s16 unk74;
    u8 pad76[2];
    s32 unk78;
} Func150F892CSpawnA;

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
} Func150F892CSpawnB;

extern void func_15164F0C(s32 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void func_151D8868(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_15143874(s16, f32, f32 *, f32 *);
extern void func_151C329C(void *, s32, s32);
extern void func_15143794(s16, s16, f32, f32 *);
extern void *func_15130280(void *, u8, s32, s32, u8, s32);
void func_151DB5D0(s32, f32 *, f32 *, f32, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32);

void func_150F892C(Func150F892CArg *arg0);

typedef struct {
    s32 unk0;
    u8 unk4;
} Func150F887CMsg;

void func_150F887C(Func150F892CArg *arg0, Func150F887CMsg *arg1, u8 arg2) {
    Func150F892CSub *sub = &arg0->unk28;

    if (arg2 == 0x42) {
        if (sub->unk4 == arg1->unk4) {
            u8 i;

            for (i = 0; i < 7; i++) {
                sub->unkC[i]->unk6E = 1;
            }
            sub->unkC[7]->unk6E = 0;
            sub->unk8 = 7;
        }
    } else if (arg2 == 0x3F) {
        if (arg0->unk28.unk0 == arg1->unk0) {
            func_150F892C(arg0);
        }
    }
}

void func_150F892C(Func150F892CArg *arg0) {
    s32 count;
    s32 i;
    Func150F892CSub *sub;

    count = 0;
    {
        struct127 *obj;

        obj = D_800CC2D0;
        for (i = 0; i < 25; i++, obj++) {
            if (obj->id == 0x98 && obj->unk84.uh == 0x1EB && obj->unk222 == 0) {
                count++;
            }
        }
    }
    sub = &arg0->unk28;
    if (count == 0) {
        return;
    }
    if (sub->unk8 < 7) {
        sub->unk6 -= D_800BE9E4 * count;
        if (sub->unk6 < 0) {
            Func150F892CMsg sp1F0;
            func_10010F88(func_150ADA20() % 3U + 0x2B3, 0x5DC0, 0, 0, -1,
                          sub->unkC[sub->unk8]->unk10, sub->unkC[sub->unk8]->unk12, sub->unkC[sub->unk8]->unk14,
                          500, 1000);
            sub->unkC[sub->unk8]->unk6E = 1;
            sub->unk8++;
            sub->unkC[sub->unk8]->unk6E = 0;
            func_15164F0C(7, 0, 0, arg0->unkC, arg0->unk1);
            sp1F0.unk0 = 1;
            sp1F0.unk2 = 0x19;
            sp1F0.unk5 = 1;
            sp1F0.unk4 = 8;
            sp1F0.unk6 = -1;
            func_151D8868(&sp1F0, 0, arg0->unkC, arg0->unk1);
            sub->unk6 = func_150ADA20() % 31U + 70;
        }
    }
    sub->unk3C -= D_800BE9E4 * count;
    if (sub->unk3C < 0) {
        Func150F892CMsg sp1E8;
        sp1E8.unk0 = 1;
        sp1E8.unk2 = func_150ADA20() % 21U + 10;
        sp1E8.unk5 = 1;
        sp1E8.unk4 = (func_150ADA20() & 3) + 1;
        sp1E8.unk6 = -1;
        func_151D8868(&sp1E8, 0, arg0->unkC, arg0->unk1);
        func_10010F88((func_150ADA20() & 3) + 0x6D6, 0x5DC0, 0, 0, -1,
                      sub->unkC[sub->unk8]->unk10, sub->unkC[sub->unk8]->unk12, sub->unkC[sub->unk8]->unk14,
                      500, 1000);
        sub->unk3C = func_150ADA20() % 151U + 150;
    }

    sub->unk38 += (0.02000000142f + func_150ADA68() * 0.025f) * (D_800BE9A4 * count);
    if (sub->unk38 > 1.0f) {
        s16 dir;
        struct17 sp1D8;
        dir = (sub->unk5 & 1) ? -1 : 1;
        do {
            func_15143874((func_150ADA20() % 126U - 220) * dir, sub->unk48, &sp1D8.unk0, &sp1D8.unk8);
            sp1D8.unk4 = func_150ADA68() * 150.0f + 30.0f;
            sp1D8.unk0 += sub->unk40;
            sp1D8.unk8 += sub->unk44;
            func_151C329C(&sp1D8, arg0->unkC, arg0->unk1);
            sub->unk38 -= 1.0f;
        } while (sub->unk38 > 1.0f);
    }

    sub->unk34 += (0.02000000142f + func_150ADA68() * 0.06000000238f) * (D_800BE9A4 * count);
    if (sub->unk34 > 1.0f) {
        s16 n;
        s16 dir;
        Func150F892CSpawnA sp158;
        dir = (sub->unk5 & 1) ? -1 : 1;
        sp158.unk00 = 1.0f;
        sp158.unk04 = 1.0f;
        sp158.unk1C = 1.0f;
        sp158.unk20 = 1.0f;
        sp158.unk24 = 1.0f;
        sp158.unk50 = 0x39E8;
        sp158.unk56 = 0x86;
        sp158.unk58 = 0;
        sp158.unk5C = 0;
        sp158.unk60 = 0xFF;
        sp158.unk61 = 8;
        sp158.unk62 = 0;
        sp158.unk63 = 0;
        sp158.unk64 = 0;
        sp158.unk65 = 0;
        sp158.unk66 = 0;
        sp158.unk67 = 0;
        sp158.unk68 = 0;
        sp158.unk6A = 2;
        sp158.unk6C = 0;
        sp158.unk70 = 0;
        sp158.unk72 = 0xC;
        sp158.unk74 = 0x15;
        sp158.unk78 = 0;
        sp158.unk44 = 0.0f;
        do {
            s16 angle;

            n = func_150ADA20() % 7U + 5;
            angle = (func_150ADA20() % 126U - 220) * dir;
            func_15143874(angle, sub->unk48, &sp158.unk28.unk0, &sp158.unk28.unk8);
            sp158.unk28.unk4 = func_150ADA68() * 150.0f + 30.0f;
            sp158.unk28.unk0 += sub->unk40;
            sp158.unk28.unk8 += sub->unk44;
            i = angle - 7;
            for (; n > 0; n--) {
                sp158.unk54 = (func_150ADA20() & 0xF) + 0x23;
                sp158.unk08 = sp158.unk0C = func_150ADA68() * 0.012f + 0.005f;
                sp158.unk10 = func_150ADA68() * 360.0f;
                sp158.unk14 = func_150ADA68() * 360.0f;
                sp158.unk18 = func_150ADA68() * 360.0f;
                func_15143794((func_150ADA20() & 0xF) + i, func_150ADA20() % 37U - 63,
                              func_150ADA68() * 8.0f + 10.0f, &sp158.unk34.unk0);
                sp158.unk40 = func_150ADA68() * 32.41f + -16.205f;
                sp158.unk48 = func_150ADA68() * 32.41f + -16.205f;
                sp158.unk4C = func_150ADA68() * 0.337f + -1.177f;
                func_1513264C(&sp158, 3, 1, 0, 0, 0xFF, 1);
            }
            sub->unk34 -= 1.0f;
        } while (sub->unk34 > 1.0f);
    }

    sub->unk30 += (0.05500000343f + func_150ADA68() * 0.05f) * (D_800BE9A4 * count);
    if (sub->unk30 > 1.0f) {
        s16 dir;
        s32 m;
        Func150F892CSpawnB spE0;
        dir = (sub->unk5 & 1) ? -1 : 1;
        spE0.unk1D = 0x86;
        spE0.unk8 = 0x4404;
        spE0.unk0 = 0x200005;
        spE0.unk4 = 0x9F0600;
        spE0.unkC = 0;
        spE0.unk10 = 0;
        spE0.unk14 = 0xFF;
        spE0.unk15 = 0xFF;
        spE0.unk16 = 0xFF;
        spE0.unk17 = 0xFF;
        spE0.unk18 = 0xFF;
        spE0.unk19 = 0xFF;
        spE0.unk1A = 0xFF;
        spE0.unk3C = *(struct17 *)&D_800A5480;
        spE0.unk1E = 8;
        spE0.unk20 = 0x1F;
        spE0.unk22 = 1;
        spE0.unk58 = 0x1C207;
        spE0.unk60 = 6;
        spE0.unk61 = 5;
        spE0.unk62 = -1;
        spE0.unk63 = -1;
        spE0.unk64 = -1;
        spE0.unk65 = 0;
        spE0.unk5C = 0;
        spE0.unk66 = 0xFF;
        spE0.unk68 = 0;
        spE0.unk24 = 1.0f;
        spE0.unk6C = 0.0f;
        do {
            s16 angle;

            m = func_150ADA20() % 13U + 7;
            angle = (func_150ADA20() % 126U - 220) * dir;
            func_15143874(angle, sub->unk48, &spE0.unk30.unk0, &spE0.unk30.unk8);
            spE0.unk30.unk4 = func_150ADA68() * 150.0f + 30.0f;
            spE0.unk30.unk0 += sub->unk40;
            spE0.unk30.unk8 += sub->unk44;
            i = angle - 4;
            for (; m > 0; m--) {
                s32 flags;

                spE0.unkA = func_150ADA20() % 21U + 30;
                spE0.unk1B = func_150ADA20() % 156U + 100;
                spE0.unk28 = spE0.unk2C = func_150ADA68() * 110.0f + 70.0f;
                spE0.unk58 &= ~0xC0;
                flags = (func_150ADA20() & 1) ? 0x80 : 0;
                spE0.unk58 |= ((func_150ADA20() & 1) ? 0x40 : 0) | flags;
                func_15143794(func_150ADA20() % 9U + i, (func_150ADA20() & 7) - 16,
                              func_150ADA68() * 10.0f + 6.0f, &spE0.unk48.unk0);
                spE0.unk54 = func_150ADA68() * 0.268f + -0.3870000243f;
                func_15130280(&spE0, 1, 0, 0, 0xFF, 1);
            }
            sub->unk30 -= 1.0f;
        } while (sub->unk30 > 1.0f);
    }

    sub->unk2C += (0.3360000253f + func_150ADA68() * 0.126f) * (D_800BE9A4 * count);
    if (sub->unk2C > 1.0f) {
        s16 dir;
        struct17 spC8;
        struct17 spBC;
        dir = (sub->unk5 & 1) ? -1 : 1;
        do {
            s16 angle;

            angle = (func_150ADA20() % 126U - 220) * dir;
            func_15143874(angle, sub->unk48, &spC8.unk0, &spC8.unk8);
            spC8.unk4 = func_150ADA68() * 150.0f + 30.0f;
            spC8.unk0 += sub->unk40;
            spC8.unk8 += sub->unk44;
            func_15143794(func_150ADA20() % 9U + angle - 4, (func_150ADA20() & 7) - 16,
                          func_150ADA68() * 6.0f + 4.0f, &spBC.unk0);
            func_151DB5D0(8, &spC8.unk0, &spBC.unk0, func_150ADA68() * 200.0f + 200.0f, 1.025439024f, 0.938816011f,
                          func_150ADA68() * 0.2070000172f + -0.1690000147f, func_150ADA20() % 21U + 35, func_150ADA20() % 121U + 100,
                          50, 5, 0, 0xFF, 1);
            sub->unk2C -= 1.0f;
        } while (sub->unk2C > 1.0f);
    }
}


void func_150F9720(u8 arg0) {
    struct { s32 unk0; u8 unk4; } sp18;
    sp18.unk0 = 0;
    sp18.unk4 = D_800A1C40[arg0 * 2];
    func_151494E0((s32)&sp18, 0x42);
    sp18.unk4 = D_800A1C40[arg0 * 2 + 1];
    func_151494E0((s32)&sp18, 0x42);
}

void func_150F9788(struct260 *arg0) {
}

void func_150F9788(struct260 *);

void func_150F9794(struct260 *arg0) {
    func_150F9788(arg0);
    func_1514933C(arg0);
}

void func_150F97C0(struct260 *arg0) {
    func_150F9788(arg0);
    func_15149368(arg0);
}

extern u8 D_80088B50;
extern s32 func_15145EA4(s32 *arg0, s32 *arg1, s32 arg2, s32 arg3);
extern void func_15102B38(s32, u8, const f32 *, const f32 *, f32 *, s32, s32, f32, struct17 *, s32, s32, s32, u8, s32);

void func_150F97EC(s32 arg0, s32 arg1, s32 arg2) {
    struct17 sp64;
    f32 scale;
    f32 sp58[2];
    s32 sp54[1];
    s32 sp50[1];
    s32 mtx;
    s32 sp48;
    s32 sp44;

    if (((struct127 *)arg0)->unk1D4 == 0) {
        return;
    }
    sp54[0] = (s32)D_800A1C48;
    sp50[0] = (s32)&sp64;
    mtx = (s32)((struct127 *)arg0)->unk1D4 + (D_80088B50 << 6);
    func_15145EA4(sp54, sp50, mtx, 1);
    scale = 1.0f;
    sp58[1] = func_150ADA68() * scale + 2.0f;
    sp58[0] = func_150ADA68() * 14.0f + 28.0f;
    sp44 = func_150ADA20();
    sp48 = func_150ADA20();
    func_15102B38(arg0, D_80088B50, D_800A1C48, D_800A1C54, sp58,
                  (sp44 % 3U) + 4, (sp48 % 0x9CU) + 0x64,
                  func_150ADA68() * 300.0f + 400.0f, &sp64, 0xFF,
                  0, -1, ((u8 *)&arg1)[3], arg2);
}

void func_150F9950(struct127 *arg0, s32 arg1, s32 arg2) {
    struct17 sp60[6];
    struct17 sp54;
    struct17 sp48;
    struct17 sp3C;
    struct17 sp30;
    struct126 *temp;

    temp = func_150FF288(arg0);
    if (temp != 0) {
        if (func_150FF6E0(sp60, &sp54, &sp48, &sp3C, &sp30, arg0, temp) != 0) {
            func_151D3F14(&sp54, ((u8 *)&arg1)[3], arg2);
            func_151D4408(&sp48, &sp3C, (*(Func150F9950Entry **)&arg0->unk1D4)[*((u8 *)temp + 2)], arg0, 1.0f, ((u8 *)&arg1)[3], arg2);
            func_150FF474(&sp54, sp60, ((u8 *)&arg1)[3], arg2);
        }
    }
}
