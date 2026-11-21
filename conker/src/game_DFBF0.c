#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_DFBF0/func_150B2740.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_DFBF0/func_150B2EB4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_DFBF0/func_150B3188.s")

struct Obj150B36AC {
    u8 pad0[0x10];
    f32 x10;
    f32 x14;
    u8 pad18[0x3C - 0x18];
    f32 x3C;
    u8 pad40[0x44 - 0x40];
    f32 x44;
    f32 x48;
    f32 x4C;
    f32 x50;
    f32 x54;
    f32 x58;
    u8 pad5C[0x60 - 0x5C];
    s32 x60;
    s16 x64;
    u8 pad66[0x170 - 0x66];
    f32 x170;
};

s32 func_150B36AC(struct Obj150B36AC *arg0, s32 a1, s32 a2, s32 a3, f32 arg5) {
    arg0->x3C = arg0->x10 + arg5;
    if (arg0->x170 < arg0->x48) {
        arg0->x60 &= ~0x7;
        arg0->x60 &= ~0x8;
        arg0->x60 &= ~0x40;
        arg0->x60 &= ~0x20;
        arg0->x44 = 0.0f;
        arg0->x48 = 0.0f;
        arg0->x4C = 0.0f;
        if (arg0->x64 >= 0x21) {
            arg0->x64 = 0x20;
        }
    } else {
        arg0->x44 = arg0->x44 * arg0->x14;
        arg0->x48 = -arg0->x48 * arg0->x14;
        arg0->x4C = arg0->x4C * arg0->x14;
        arg0->x50 = arg0->x50 * arg0->x14;
        arg0->x54 = arg0->x54 * arg0->x14;
        arg0->x58 = arg0->x58 * arg0->x14;
    }
    return 1;
}

s32 func_150B378C(void *a0) {
    u8 *p;
    s32 v1;
    p = *(u8 **)((u8 *)a0 + 0x98);
    v1 = *(s16 *)((u8 *)a0 + 0x1C) << 4;
    if (v1 >= 0x100) {
        v1 = 0xFF;
    }
    if (v1 < p[0x1B]) {
        p[0x1B] = v1;
    }
    return 1;
}

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ u8 pad8[0x4];
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ u8 pad14[0x5];
    /* 0x19 */ u8 unk19;
    /* 0x1A */ u8 unk1A;
    /* 0x1B */ u8 unk1B;
    /* 0x1C */ u8 pad1C[0x4];
    /* 0x20 */ u8 unk20;
} DustState;

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
} DustPoint; /* 0x14 */

typedef struct {
    /* 0x00 */ u8 pad0[0x1];
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 pad2[0xA];
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 padD[0x18];
    /* 0x25 */ u8 unk25;
    /* 0x26 */ u8 pad26[0x7];
    /* 0x2D */ s8 unk2D;
    /* 0x2E */ u8 pad2E[0x66];
    /* 0x94 */ DustPoint *unk94;
    /* 0x98 */ DustState *unk98;
} DustSource;

/* Descriptor passed to func_1513C73C. */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s8 unk6;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 unk13;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ u8 pad1C[0xC];
    /* 0x28 */ DustPoint *unk28;
} DustParams; /* 0x2C */

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x18 */ s32 unk18;
} DustSpawn; /* 0x1C */

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ u8 unk1A;
    /* 0x1B */ u8 unk1B;
    /* 0x1C */ u8 pad1C[0x4];
} DustPart; /* 0x20 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 unk1D;
} DustStyle; /* 0x20 */

typedef struct {
    s16 unk0[3];
} DustIds;

static DustIds D_80088700 = { { 0xF, 0x10, 0x11 } };

extern s32 func_15147DA0(DustSpawn *, DustPart *, s32, s32, s32, s32, s32, s32, s32, s32, s32, DustStyle *, s32, s32, s32);

s32 func_150B37C8(DustSource *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5) {
    DustState *state = arg0->unk98;
    DustParams tmp;
    f32 scale;
    DustIds ids;
    DustSpawn spawn;
    DustPart part;
    DustStyle style;

    tmp.unk28 = arg0->unk94;
    ids = D_80088700;
    {
        s32 rand2;
        s32 rand1;
        s32 rand0;

        state->unk20 = 4;
        scale = func_150ADA68() * 50.0f + 50.0f;
        rand2 = func_150ADA20();
        tmp.unk6 = ids.unk0[rand2 % 3U];
        tmp.unk8 = 0;
        tmp.unkC = 0;
        tmp.unk0 = 0x11;
        tmp.unk4 = 0x96;
        tmp.unk10 = state->unk1B;
        tmp.unk11 = state->unk1A;
        tmp.unk12 = 0;
        tmp.unk13 = 0;
        tmp.unk14 = 0;
        tmp.unk15 = 0xFF;
        tmp.unk18 = 0x30002;

        rand0 = func_150ADA20();
        rand1 = func_150ADA20();
        rand2 = func_150ADA20();

        func_1513C73C((s32)&tmp, 1, 0, arg5,
                      tmp.unk28[arg0->unk2D].unk0,
                      arg4,
                      tmp.unk28[arg0->unk2D].unk8,
                      scale, scale,
                      rand0 & 0xFF, (rand2 & 1) + (rand1 & 1), 0,
                      arg0->unkC, arg0->unk1);
    }

    style.unk0 = 0;
    style.unk4 = 1;
    style.unk8 = 0x160600;
    style.unkC = 3;
    style.unk10 = 0x10;
    style.unk14 = 0x80;
    style.unk18 = 0x20;
    style.unk1C = 0;
    style.unk1D = 9;
    spawn.unk10 = 1;
    spawn.unkE = 1;
    part.unk19 = state->unk19;
    part.unk1A = state->unk1A;
    part.unk18 = 8;
    part.unk1B = state->unk1B;
    spawn.unk0 = tmp.unk28[arg0->unk2D].unk0;
    spawn.unk4 = arg4;
    spawn.unk8 = tmp.unk28[arg0->unk2D].unk8;
    spawn.unk15 = arg0->unk25;
    spawn.unkC = 0x3C;
    part.unk0 = state->unk0 * 0.75f;
    part.unk10 = state->unk10;
    part.unk4 = state->unk4;
    part.unk8 = func_150ADA68() * 15.0f + 15.0f;
    part.unkC = state->unkC;
    func_15147DA0(&spawn, &part, 0, 1, 7, 0, 0, 0, 0, 0, 0, &style, 0, arg0->unkC, arg0->unk1);
    return 1;
}
