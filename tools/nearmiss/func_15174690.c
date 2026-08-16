#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_800A7160;  /* -10000.0f, the "no water surface here" sentinel */
extern f32 D_800A7164;  /* pi / 180 */
extern s32 D_8008CA4C;

extern f32 sinf(f32);
extern f32 cosf(f32);
s32 func_15167D84(void *, s32, s32, s32, s32, s32);

/**
 * The 0x38-byte init block handed to func_15167D84, which bcopy()s it verbatim
 * into the body of a freshly allocated class-5 object at object offset +0x10.
 * Same layout as the one built by func_1518CA80 (game_1B9F30.c).
 */
typedef struct {
    /* 0x00 */ s32 animPtr;
    /* 0x04 */ s32 sizeGrowth;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s16 animFrame;
    /* 0x0E */ s16 animSpeed;
    /* 0x10 */ s16 x;
    /* 0x12 */ s16 y;
    /* 0x14 */ s16 z;
    /* 0x16 */ s16 velX;
    /* 0x18 */ s16 velZ;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ u8 xFrac;
    /* 0x1D */ u8 zFrac;
    /* 0x1E */ u8 yFrac;
    /* 0x1F */ s8 updateFuncIdx;
    /* 0x20 */ s16 velY;
    /* 0x22 */ s16 accelY;
    /* 0x24 */ s16 width;
    /* 0x26 */ s16 height;
    /* 0x28 */ s16 lifetime;
    /* 0x2A */ s8 alphaFade;
    /* 0x2B */ u8 expireFuncIdx;
    /* 0x2C */ s8 primR;
    /* 0x2D */ s8 primG;
    /* 0x2E */ s8 primB;
    /* 0x2F */ u8 alpha;
    /* 0x30 */ s8 envR;
    /* 0x31 */ s8 envG;
    /* 0x32 */ s8 envB;
    /* 0x34 */ s16 flags;
} ParticleInit;

/**
 * Spawn a splash/ripple sprite 10 units "behind" object arg0, scattered by
 * arg1 units in x and z. Only fires while the object is standing at a
 * surface whose height is still the uninitialised sentinel.
 */
void func_15174690(s32 objIdx, s32 spread, s32 sizeGrowth, s32 growthSpread, s32 size, s32 arg5, s32 velY, s32 arg7, s32 arg8) {
    f32 angle;
    f32 x;
    f32 y;
    f32 z;
    s32 rnd;
    struct127 *obj;
    ParticleInit sp40;

    obj = &D_800CC2D0[objIdx];
    if (obj->in_water != 0) {
        return;
    }
    if (D_800A7160 != obj->unk118) {
        return;
    }

    y = obj->y_position + 5.0f;
    angle = obj->unk40 * D_800A7164;
    x = obj->x_position;
    z = obj->z_position;
    x -= 10.0f * sinf(angle);
    z -= 10.0f * cosf(angle);

    if (spread != 0) {
        rnd = func_150ADA20();
        x += (f32)(rnd % spread);
        rnd = func_150ADA20();
        z += (f32)(rnd % spread);
    }
    if (growthSpread != 0) {
        sizeGrowth += func_150ADA20() % (u32)growthSpread;
    }

    sp40.animPtr = D_8008CA4C;
    sp40.sizeGrowth = sizeGrowth;
    sp40.unk08 = arg5;
    sp40.animFrame = 0;
    sp40.animSpeed = 0x100;
    sp40.x = (s32)x;
    sp40.y = (s32)y;
    sp40.z = (s32)z;
    sp40.velX = 0;
    sp40.velZ = 0;
    sp40.unk1A = 0;
    sp40.updateFuncIdx = 5;
    sp40.velY = velY;
    sp40.accelY = 0;
    sp40.width = size;
    sp40.height = size;
    sp40.lifetime = 0x200;
    sp40.alphaFade = 0;
    sp40.expireFuncIdx = 0;
    sp40.primR = 0xFF;
    sp40.primG = 0xFF;
    sp40.primB = 0xFF;
    sp40.alpha = 0xFF;
    sp40.flags = 0;
    func_15167D84(&sp40, 0, 0, -1, (u8)arg7, arg8);
}

void func_15174920(void *arg0) {
    s32 v0 = *(u8 *)((u8 *)arg0 + 0x3F);

    if (v0 >= 0xC9) {
        v0 = 0xC8;
    }
    v0 -= D_800BE9E4 * *(s32 *)((u8 *)arg0 + 0x18);
    if (v0 < 0) {
        *(s16 *)((u8 *)arg0 + 0x38) = 0;
        return;
    }
    *(u8 *)((u8 *)arg0 + 0x3F) = v0;
    *(s16 *)((u8 *)arg0 + 0x34) += *(s32 *)((u8 *)arg0 + 0x14);
    *(s16 *)((u8 *)arg0 + 0x36) += (*(s32 *)((u8 *)arg0 + 0x14) << 3) / 7;
}
