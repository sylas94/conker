#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern f32 D_800A0C00;
extern f32 D_800A0C04;
extern f32 D_800A0C08;
extern f32 D_800A0C0C;
extern f32 D_800A0C10;
extern f32 D_800A0C14;
extern f32 D_800A0C18;
extern f32 D_800A0C1C;
extern f32 D_800A0C20;
extern f32 D_800A0C24;
extern f32 D_800A0C28;
extern f32 D_800A0C2C;
extern f32 D_800A0C30;
extern s32 D_80090514;

void func_15152F70(void *arg0, u8 arg1);
void func_15153298(void *arg0, u8 arg1, s32 arg2);
void func_15196438(s32 arg0, s32 arg1, u8 arg2, s32 arg3);

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
    s16 unk24;
    s16 unk26;
    s16 unk28;
    s16 unk2A;
    s16 unk2C;
    s16 unk2E;
    s16 unk30;
    s16 unk32;
    s16 unk34;
    s16 unk36;
    s8 unk38;
    s8 unk39;
    u8 pad3A[2];
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    s32 unk48;
    s32 unk4C;
    s32 unk50;
    u8 unk54;
    u8 unk55;
    u8 pad56[2];
} Struct150DB9E0A;

typedef struct {
    f32 unk00;
    f32 unk04;
    f32 unk08;
    s16 unk0C;
    s16 unk0E;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    f32 unk18;
    f32 unk1C;
    s16 unk20;
    s16 unk22;
    s16 unk24;
    s16 unk26;
    s8 unk28;
    s8 unk29;
    s16 unk2A;
    s16 unk2C;
    s16 unk2E;
    s16 unk30;
    s16 unk32;
    s16 unk34;
    s16 unk36;
    void *unk38;
    u8 unk3C;
    u8 unk3D;
    u8 pad3E[2];
} Struct150DB9E0B;

typedef struct {
    u8 pad_0x00[0x20];
    u8 field_0x20;
} EffectSpawnState;

typedef struct {
    f32 field_0x00;
    f32 field_0x04;
    f32 field_0x08;
    f32 field_0x0C;
    f32 field_0x10;
} EffectSpawnPoint;

typedef struct {
    u8 pad_0x00[0x1];
    u8 field_0x01;
    u8 pad_0x02[0xA];
    u8 field_0x0C;
    u8 pad_0x0D[0x20];
    s8 field_0x2D;
    u8 pad_0x2E[0x66];
    EffectSpawnPoint *field_0x94;
    EffectSpawnState *field_0x98;
} EffectSpawnSource;

typedef struct {
    s32 field_0x00;
    s16 field_0x04;
    s8 field_0x06;
    u8 pad_0x07[0x1];
    s32 field_0x08;
    s32 field_0x0C;
    u8 field_0x10;
    u8 field_0x11;
    u8 field_0x12;
    u8 field_0x13;
    u8 field_0x14;
    u8 field_0x15;
    u8 pad_0x16[0x2];
    s32 field_0x18;
    u8 pad_0x1C[0xC];
    EffectSpawnPoint *field_0x28;
    EffectSpawnState *field_0x2C;
} EffectSpawnParams;

void func_150DB9E0(s32 arg0, s32 arg1, u8 arg2) {
    Struct150DB9E0A sp78;
    Struct150DB9E0B sp38;

    if (arg0 != 0) {
        switch (arg1) {
        case 0:
            func_15196438(arg0, 1, arg2, 0);

            sp78.unk00 = D_800A0C00;
            sp78.unk24 = 8;
            sp78.unk26 = 8;
            sp78.unk28 = -0x4B;
            sp78.unk2C = -0x26;
            sp78.unk2A = 0x16;
            sp78.unk2E = 0x23;
            sp78.unk30 = 3;
            sp78.unk32 = 2;
            sp78.unk34 = 0x29;
            sp78.unk36 = 0;
            sp78.unk38 = 0xA;
            sp78.unk39 = 0x28;
            sp78.unk3C = 1;
            sp78.unk40 = 0;
            sp78.unk44 = 0;
            sp78.unk48 = 0;
            sp78.unk4C = 0;
            sp78.unk50 = 0;
            sp78.unk54 = 0xFF;
            sp78.unk55 = 0xFF;
            sp78.unk0C = 3.0f;
            sp78.unk10 = 3.0f;
            sp78.unk04 = D_800A0C04;
            sp78.unk08 = D_800A0C08;
            sp78.unk1C = 9.0f;
            sp78.unk20 = 8.0f;
            sp78.unk14 = D_800A0C0C;
            sp78.unk18 = 0.0f;
            func_15152F70(&sp78, arg2);

            func_151491F4(0x1E, -1, 0, 1, 0, 0, arg2, 0);

            sp38.unk00 = D_800A0C10;
            sp38.unk04 = D_800A0C14;
            sp38.unk08 = D_800A0C18;
            sp38.unk0C = 6;
            sp38.unk18 = D_800A0C1C;
            sp38.unk0E = 3;
            sp38.unk10 = -0x4A;
            sp38.unk14 = -0x26;
            sp38.unk12 = 0x15;
            sp38.unk16 = 0x23;
            sp38.unk1C = D_800A0C20;
            sp38.unk20 = 0xE;
            sp38.unk22 = 0xE;
            sp38.unk24 = -0x3D;
            sp38.unk26 = 0x1C;
            sp38.unk28 = -1;
            sp38.unk29 = 0x12;
            sp38.unk2A = 6;
            sp38.unk2C = 6;
            sp38.unk2E = 0;
            sp38.unk30 = 0xAE;
            sp38.unk32 = 0x73;
            sp38.unk34 = 0x73;
            sp38.unk36 = 0x87;
            sp38.unk38 = &D_80090514;
            sp38.unk3C = 0xFF;
            sp38.unk3D = 0xFF;
            func_15153298(&sp38, arg2, 1);
            break;
        case 1:
            func_15196438(arg0, 2, arg2, 0);
            break;
        }
    }
}

void func_150DBC60(void *arg0) {
    Struct150DB9E0A sp18;

    sp18.unk00 = D_800A0C24;
    sp18.unk24 = 1;
    sp18.unk26 = 2;
    sp18.unk28 = -0x4B;
    sp18.unk2C = -0x26;
    sp18.unk2A = 0x16;
    sp18.unk2E = 0x23;
    sp18.unk30 = 3;
    sp18.unk32 = 2;
    sp18.unk34 = 0x29;
    sp18.unk36 = 0;
    sp18.unk0C = 2.0f;
    sp18.unk10 = 2.0f;
    sp18.unk38 = 0xA;
    sp18.unk39 = 0x28;
    sp18.unk3C = 1;
    sp18.unk40 = 0;
    sp18.unk44 = 0;
    sp18.unk48 = 0;
    sp18.unk4C = 0;
    sp18.unk50 = 0;
    sp18.unk54 = 0xFF;
    sp18.unk55 = 0xFF;
    sp18.unk04 = D_800A0C28;
    sp18.unk08 = D_800A0C2C;
    sp18.unk1C = 7.0f;
    sp18.unk20 = 5.0f;
    sp18.unk14 = D_800A0C30;
    sp18.unk18 = 0.0f;
    func_15152F70(&sp18, *(u8 *)((u8 *)arg0 + 0xC));
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_108E90/func_150DBD70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_108E90/func_150DC558.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_108E90/func_150DCEA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_108E90/func_150DD640.s")

void func_150DDED0(void *arg0) {
    struct102 *temp_v0;
    s32 temp_v1;

    temp_v0 = (struct102 *)func_151491F4(0x64, 2, -1, 1, 0, 1, 0xFF, 0);
    if (temp_v0 != 0) {
        temp_v1 = ((u8 *)arg0)[0x72];
        switch (temp_v1) {
        case 0xFB:
            ((u8 *)temp_v0)[0x28] = 1;
            return;
        case 0xFC:
            ((u8 *)temp_v0)[0x28] = 2;
            return;
        case 0xFD:
            ((u8 *)temp_v0)[0x28] = 4;
            return;
        case 0xFE:
            ((u8 *)temp_v0)[0x28] = 3;
            return;
        default:
            func_1516972C(temp_v0);
            break;
        }
    }
}

s32 func_150DBD70(s32);

s32 func_150DDF88(u8 *arg0) {
    return func_150DBD70(arg0[0x28]);
}

s32 func_150DDFAC(EffectSpawnSource *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5) {
    EffectSpawnParams tmp;
    f32 scale;
    s32 rand2;
    s32 rand1;
    s32 rand0;

    tmp.field_0x2C = arg0->field_0x98;
    tmp.field_0x28 = arg0->field_0x94;
    scale = func_150ADA68() * 70.0f + 10.0f;
    tmp.field_0x2C->field_0x20 = 4;

    switch (func_150ADA20() & 1) {
    case 0:
        tmp.field_0x06 = 0x1D;
        break;
    case 1:
        tmp.field_0x06 = 0x1E;
        break;
    }

    tmp.field_0x08 = 0;
    tmp.field_0x0C = 0;
    tmp.field_0x00 = 0x11;
    tmp.field_0x04 = 0x64;
    tmp.field_0x10 = 0xFF;
    tmp.field_0x11 = 0xFF;
    tmp.field_0x12 = 0;
    tmp.field_0x13 = 0;
    tmp.field_0x14 = 0;
    tmp.field_0x15 = 0xFF;
    tmp.field_0x18 = 0x30002;

    rand0 = func_150ADA20();
    rand1 = func_150ADA20();
    rand2 = func_150ADA20();

    func_1513C73C((s32)&tmp, 5, 0, arg5,
                  tmp.field_0x28[arg0->field_0x2D].field_0x00,
                  arg4,
                  tmp.field_0x28[arg0->field_0x2D].field_0x08,
                  scale, scale,
                  rand0 & 0xFF, (rand2 & 1) + (rand1 & 1), 0,
                  arg0->field_0x0C, arg0->field_0x01);
    return 1;
}

s32 func_150DE12C(EffectSpawnSource *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5) {
    EffectSpawnParams tmp;
    f32 scale;
    s32 rand2;
    s32 rand1;
    s32 rand0;

    tmp.field_0x2C = arg0->field_0x98;
    tmp.field_0x28 = arg0->field_0x94;
    scale = func_150ADA68() * 10.0f + 10.0f;
    tmp.field_0x2C->field_0x20 = 4;

    switch (func_150ADA20() & 1) {
    case 0:
        tmp.field_0x06 = 0x1B;
        break;
    case 1:
        tmp.field_0x06 = 0x1C;
        break;
    }

    tmp.field_0x08 = 0;
    tmp.field_0x0C = 0;
    tmp.field_0x00 = 0x11;
    tmp.field_0x04 = 0x64;
    tmp.field_0x10 = 0xFF;
    tmp.field_0x11 = 0xFF;
    tmp.field_0x12 = 0;
    tmp.field_0x13 = 0;
    tmp.field_0x14 = 0;
    tmp.field_0x15 = 0xAA;
    tmp.field_0x18 = 0x30002;

    rand0 = func_150ADA20();
    rand1 = func_150ADA20();
    rand2 = func_150ADA20();

    func_1513C73C((s32)&tmp, 5, 0, arg5,
                  tmp.field_0x28[arg0->field_0x2D].field_0x00,
                  arg4,
                  tmp.field_0x28[arg0->field_0x2D].field_0x08,
                  scale, scale,
                  rand0 & 0xFF, (rand2 & 1) + (rand1 & 1), 0,
                  arg0->field_0x0C, arg0->field_0x01);
    return 1;
}

s32 func_150DE2A4(void *arg0) {
    s16 temp = *(s16 *)((u8 *)arg0 + 0x1C);
    if (temp < 0x20) {
        *(s8 *)((u8 *)arg0 + 0x28) = temp << 3;
    }
    return 1;
}

void func_150DE2C4(void *arg0) {
    *(s16 *)((u8 *)arg0 + 0x34) = *(s16 *)((u8 *)arg0 + 0x34) - 0x1A;
    *(s16 *)((u8 *)arg0 + 0x36) = *(s16 *)((u8 *)arg0 + 0x36) - 0x1A;
    if (*(s16 *)((u8 *)arg0 + 0x34) >= 0xA && *(s16 *)((u8 *)arg0 + 0x36) >= 0xA) {
        return;
    }
    *(s16 *)((u8 *)arg0 + 0x38) = 0;
}
