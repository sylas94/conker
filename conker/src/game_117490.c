#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_150E5AE0(void);

extern f32 D_800A1418;
extern f32 D_800A141C;
extern f32 D_800A1420;
extern f32 D_800A1424;
extern f32 D_800A1428;
extern f32 D_800A142C;
extern f32 D_800A1430;
extern f32 D_800A1434;

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
    /* 0x25 */ u8  pad25[0x1];
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
} struct_E9FE0;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
} struct_E9FE0b;

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
} Vec3F_EA11C;

typedef struct {
    /* 0x00 */ u8 pad0[0x74];
    /* 0x74 */ f32 unk74;
} struct_EA11C_arg5;

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s32 unk0C;
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
    /* 0x30 */ Vec3F_EA11C unk30;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ u8 pad5C[0x4];
    /* 0x60 */ u8 unk60;
    /* 0x61 */ u8 unk61;
    /* 0x62 */ u8 unk62;
    /* 0x63 */ s8 unk63;
} struct_EA11C_params;

typedef struct {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u8 unk06;
    /* 0x07 */ u8 unk07;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ u8 unk1A;
    /* 0x1B */ u8 unk1B;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u8 pad24[0x4];
} struct_EA11C_extra;

void *func_151303BC(struct_EA11C_params *, s32, s32);

extern f32 D_800A1410;
extern f32 D_800A1414;
void *func_15134DAC(struct_E9FE0 *, s32);

void *func_150E9FE0(void *arg0, s16 arg1, s32 arg2, s32 arg3) {
    struct_E9FE0 sp2C;
    void *temp_v1;
    struct_E9FE0b sp18;

    sp2C.unk0 = *((u8 *)arg0 + 0x3B);
    sp2C.unk4 = arg0;
    sp2C.unk8 = 8;
    sp2C.unkC = -9.0f;
    sp2C.unk10 = -14.0f;
    sp2C.unk14 = 27.0f;
    sp2C.unk18 = -21.0f;
    sp2C.unk1C = -14.0f;
    sp2C.unk20 = 41.0f;
    sp2C.unk24 = 2;
    sp2C.unk26 = 0x3C;
    sp2C.unk28 = 0x3C;
    sp2C.unk2A = arg1;
    sp2C.unk2E = 2;
    sp2C.unk2F = 2;
    sp2C.unk30 = 2;
    sp2C.unk34 = 0.5f;
    sp2C.unk38 = 3;
    sp2C.unk39 = -1;

    sp18.unk0 = 0;
    sp18.unk4 = 0x11111;
    sp18.unk8 = D_800A1410;
    sp18.unkC = D_800A1414;

    temp_v1 = func_15134DAC(&sp2C, 0x10);
    if (temp_v1 != NULL) {
        memcpy((u8 *)temp_v1 + 0x80, &sp18, 0x10);
    }
    return temp_v1;
}

typedef struct {
    u8 pad0[0x80];
    /* 0x80 */ s32 unk80;
} S150EA10C;

s32 func_150EA10C(S150EA10C *arg0) {
    arg0->unk80 = 0;
    return 0x1;
}

void func_150EA11C(Vec3F_EA11C *arg0, Vec3F_EA11C *arg1, s32 arg2, s32 arg3, f32 arg4, struct_EA11C_arg5 *arg5) {
    void *temp_v0;
    f32 temp_f2;
    s32 padAC;
    struct_EA11C_params params;
    s32 pad44;
    struct_EA11C_extra extra;

    params.unk1D = 0x2F;
    params.unk08 = 0xC01;
    params.unk00 = 0x200005;
    params.unk04 = 0;
    params.unk1A = 0;
    params.unk19 = 0;
    params.unk18 = 0;
    params.unk17 = 0;
    params.unk16 = 0;
    params.unk15 = 0;
    params.unk14 = 0;
    params.unk10 = 0;
    params.unk0C = 0;
    params.unk1C = 0xFF;
    params.unk22 = 0;
    params.unk24 = 0.0f;
    params.unk58 = 0x1207;
    params.unk60 = 5;
    params.unk61 = 5;
    params.unk62 = 4;
    params.unk63 = -1;
    params.unk3C = 0.0f;
    params.unk40 = 0.0f;
    params.unk44 = 0.0f;
    params.unk1E = 0x14;
    params.unk20 = 0xC;
    extra.unk04 = 0;
    extra.unk05 = 0;
    extra.unk18 = 0;
    extra.unk19 = 0;
    extra.unk10 = 3.5f;
    extra.unk14 = D_800A1418;

    params.unk48 = (arg1->x - arg0->x) * arg5->unk74;
    params.unk4C = (arg1->y - arg0->y) * arg5->unk74;
    params.unk50 = (arg1->z - arg0->z) * arg5->unk74;
    params.unk30 = *arg0;
    params.unk30.x += params.unk48 * arg4;
    params.unk30.y += params.unk4C * arg4;
    params.unk30.z += params.unk50 * arg4;

    if (func_150ADA20() & 1) {
        params.unk58 |= 0x40;
    }
    if (func_150ADA20() & 1) {
        params.unk58 |= 0x80;
    }

    params.unk0A = (func_150ADA20() % 51U) + 0x32;
    params.unk1B = (func_150ADA20() % 101U) + 0x64;
    temp_f2 = (func_150ADA68() * 39.0f) + 31.0f;
    params.unk28 = temp_f2;
    extra.unk00 = temp_f2;
    params.unk2C = temp_f2;
    extra.unk06 = (func_150ADA20() % 5U) + 4;
    extra.unk07 = (func_150ADA20() % 5U) + 4;
    extra.unk08 = ((func_150ADA68() * 0.25f) + D_800A141C) * extra.unk00;
    extra.unk0C = ((func_150ADA68() * 0.25f) + D_800A1420) * extra.unk00;
    extra.unk1A = (func_150ADA20() % 5U) + 4;
    extra.unk1B = (func_150ADA20() % 5U) + 4;
    extra.unk1C = ((func_150ADA68() * D_800A1424) + D_800A1428) * extra.unk00;
    extra.unk20 = ((func_150ADA68() * D_800A142C) + D_800A1430) * extra.unk00;
    params.unk54 = ((func_150ADA68() * 70.0f) + 73.0f) * D_800A1434;

    temp_v0 = func_151303BC(&params, 2, 0x28);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0xA8, &extra, 0x28);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_117490/func_150EA490.s")

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u8  ownerActorId;
    /* 0x09 */ u8  pad9[0x3];
    /* 0x0C */ void *ownerActor;
    /* 0x10 */ u8  ownerTransformIndex;
    /* 0x11 */ u8  pad11[0x3];
    /* 0x14 */ f32 localOffsetX;
    /* 0x18 */ f32 localOffsetY;
    /* 0x1C */ f32 localOffsetZ;
    /* 0x20 */ f32 spawnRadius;
    /* 0x24 */ f32 spawnRate;
    /* 0x28 */ s16 lifetime;
    /* 0x2A */ u8  flags;
    /* 0x2B */ u8  spawnCallbackIndex;
    /* 0x2C */ s8  aliveCheckIndex;
    /* 0x2D */ u8  behaviorIndex;
} struct_EA500;

extern f32 D_800A1438;
void *func_1513418C(struct_EA500 *, s32, u8, s32);

void *func_150EA500(void *arg0, s16 arg1, s32 arg2, s32 arg3) {
    struct_EA500 sp20;

    sp20.unk0 = 0;
    sp20.unk4 = 0;
    sp20.ownerActorId = *((u8 *)arg0 + 0x3B);
    sp20.ownerActor = arg0;
    sp20.ownerTransformIndex = 1;
    sp20.localOffsetX = 0.0f;
    sp20.localOffsetY = 0.0f;
    sp20.localOffsetZ = 0.0f;
    sp20.spawnRadius = 25.0f;
    sp20.spawnRate = D_800A1438;
    if (arg1 == -1) {
        sp20.lifetime = 0x12C;
    } else {
        sp20.lifetime = arg1;
    }
    sp20.flags = ((arg1 == -1) ? 0 : 4) | 0xA;
    sp20.spawnCallbackIndex = 7;
    sp20.aliveCheckIndex = -1;
    sp20.behaviorIndex = 6;
    return func_1513418C(&sp20, 0, 0xFF, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_117490/func_150EA5CC.s")

void func_150EA8E0(s32 arg0) {
    func_150E5AE0();
}

void func_150EA904(s32 arg0, s32 arg1) {
    u8 *p;

    p = (u8 *)D_800DBEF4 + arg1 * sizeof(struct131);
    if (p[0x72] == 0xE0) {
        p[0x73] = (p[0x73] & 0xFF) | 3;
    }
}

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u8  padC[0x4];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8  pad16[0x26];
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ u8  pad40[0x1A];
    /* 0x5A */ s16 unk5A;
    /* 0x5C */ s16 unk5C;
    /* 0x5E */ s16 unk5E;
    /* 0x60 */ f32 unk60;
    /* 0x64 */ f32 unk64;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ u8  pad6C[0x2];
    /* 0x6E */ u8  unk6E;
    /* 0x6F */ u8  pad6F[0x4];
    /* 0x73 */ u8  unk73;
    /* 0x74 */ u8  pad74[0x8];
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ u8  pad80[0xA];
    /* 0x8A */ u8  unk8A;
} struct_EA944;

void func_150EA944(struct_EA944 *arg0) {
    f32 temp_f0;
    f32 temp_f2;
    s32 temp_v0;

    if ((arg0->unk73 & 3) == 3) {
        temp_f0 = (f32)D_800BE9E4;

        arg0->unk0 += arg0->unk60 * temp_f0;
        temp_f2 = arg0->unk0;
        if (temp_f2 < 0.0f) {
            arg0->unk0 = temp_f2 + 360.0f;
        } else if (temp_f2 >= 360.0f) {
            arg0->unk0 = temp_f2 - 360.0f;
        }

        arg0->unk4 += arg0->unk64 * temp_f0;
        temp_f2 = arg0->unk4;
        if (temp_f2 < 0.0f) {
            arg0->unk4 = temp_f2 + 360.0f;
        } else if (temp_f2 >= 360.0f) {
            arg0->unk4 = temp_f2 - 360.0f;
        }

        arg0->unk8 += arg0->unk68 * temp_f0;
        temp_f2 = arg0->unk8;
        if (temp_f2 < 0.0f) {
            arg0->unk8 = temp_f2 + 360.0f;
        } else if (temp_f2 >= 360.0f) {
            arg0->unk8 = temp_f2 - 360.0f;
        }

        temp_v0 = arg0->unk8A;
        arg0->unk5C = arg0->unk5C - ((u32)arg0->unk3C * D_800BE9E4);
        arg0->unk10 = arg0->unk10 + ((u32)arg0->unk5A * D_800BE9E4);
        arg0->unk7C += (u32)arg0->unk5C * D_800BE9E4;
        arg0->unk12 = arg0->unk7C >> 3;
        arg0->unk14 = arg0->unk14 + ((u32)arg0->unk5E * D_800BE9E4);

        temp_v0 -= D_800BE9E4 << 2;
        if (temp_v0 > 0) {
            arg0->unk8A = temp_v0;
        } else {
            arg0->unk6E = 1;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_117490/func_150EAB10.s")

typedef struct {
    /* 0x00 */ f32 unk0;  /* arg0->0x18 */
    /* 0x04 */ f32 unk4;  /* arg0->0x1C */
    /* 0x08 */ f32 unk8;  /* arg0->0x20 */
    /* 0x0C */ f32 unkC;  /* arg0->0x24 */
    /* 0x10 */ f32 unk10; /* arg0->0x28 */
    /* 0x14 */ s32 unk14; /* arg0->0x2C */
    /* 0x18 */ f32 unk18; /* arg0->0x30 */
    /* 0x1C */ f32 unk1C; /* arg0->0x34 */
} struct_EAE24b;

typedef struct {
    /* 0x00 */ u8  pad0[0x14];
    /* 0x14 */ s16 *unk14;
    /* 0x18 */ struct_EAE24b unk18;
} struct_EAE24;

s32 func_15046C80(f32 *, s32, s32, f32 *);

s32 func_150EAE24(struct_EAE24 *arg0) {
    struct_EAE24b *p;
    f32 sp28[3];

    arg0->unk18.unk0 += arg0->unk18.unk8 * D_800BE9A4;
    arg0->unk18.unk4 += arg0->unk18.unkC * D_800BE9A4;
    sp28[0] = arg0->unk18.unk0;
    sp28[1] = arg0->unk18.unk10;
    sp28[2] = arg0->unk18.unk4;
    arg0->unk14[7] = (s16)arg0->unk18.unk0;
    arg0->unk14[9] = (s16)arg0->unk18.unk4;
    p = &arg0->unk18;
    if (func_15046C80(sp28, 0, arg0->unk18.unk14, &p->unk1C) != 0) {
        arg0->unk14[8] = (s16)p->unk1C;
    } else {
        arg0->unk14[8] = (s16)p->unk10;
    }
    p->unk18 -= D_800BE9A4;
    if (p->unk18 <= 0.0f) {
        return 0;
    }
    return 1;
}
