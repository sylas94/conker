#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern s32 D_8008CA4C;
s32 func_15167D84(void *, s32, s32, s32, s32, s32);

/**
 * Caller-supplied description of a sprite particle to spawn.
 * Built on the stack by e.g. func_15149EC4 (game_176A00.c) and func_150C1E34.
 * Position is supplied either as floats (x/y/z) or as pre-split
 * integer + 1/256 fraction (xInt/yInt/zInt + xFrac/yFrac/zFrac).
 */
typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ s16 xInt;
    /* 0x0E */ s16 yInt;
    /* 0x10 */ s16 zInt;
    /* 0x12 */ u8 xFrac;
    /* 0x13 */ u8 zFrac;
    /* 0x14 */ u8 yFrac;
    /* 0x15 */ u8 pad15;
    /* 0x16 */ s16 width;
    /* 0x18 */ s16 height;
    /* 0x1A */ s16 widthGrowth;
    /* 0x1C */ s16 heightGrowth;
    /* 0x1E */ s16 velX;
    /* 0x20 */ s16 velZ;
    /* 0x22 */ s16 velY;
    /* 0x24 */ s16 accelY;
    /* 0x26 */ s16 lifetime;
    /* 0x28 */ u8 primR;
    /* 0x29 */ u8 primG;
    /* 0x2A */ u8 primB;
    /* 0x2B */ u8 envR;
    /* 0x2C */ u8 envG;
    /* 0x2D */ u8 envB;
    /* 0x2E */ u8 brightness;
    /* 0x2F */ u8 alpha;
    /* 0x30 */ s8 alphaFade;
    /* 0x31 */ u8 expireFuncIdx;
} ParticleSpawnArgs;

/**
 * The 0x38-byte init block handed to func_15167D84, which bcopy()s it verbatim
 * into the body of a freshly allocated class-5 object at object offset +0x10.
 * So field 0xNN here becomes object field 0xNN+0x10; the generic per-frame
 * updater func_15167E0C and renderer func_15168118 (game_1944C0.c) read it there.
 */
typedef struct {
    /* 0x00 */ s32 animPtr;        /* obj+0x10: sprite/anim descriptor (+0 frame table, +4 frame count) */
    /* 0x04 */ s32 sizeGrowth;     /* obj+0x14: packed (widthGrowth << 16) | heightGrowth, applied by func_1518CCA8 */
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s16 animFrame;      /* obj+0x1C: 8.8 frame cursor */
    /* 0x0E */ s16 animSpeed;      /* obj+0x1E: 8.8 frames advanced per tick */
    /* 0x10 */ s16 x;
    /* 0x12 */ s16 y;
    /* 0x14 */ s16 z;
    /* 0x16 */ s16 velX;
    /* 0x18 */ s16 velZ;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ u8 xFrac;
    /* 0x1D */ u8 zFrac;
    /* 0x1E */ u8 yFrac;
    /* 0x1F */ s8 updateFuncIdx;   /* obj+0x2F: index into D_8008C9C8; 9 == func_1518CCA8 below */
    /* 0x20 */ s16 velY;
    /* 0x22 */ s16 accelY;         /* obj+0x32: added to velY every tick */
    /* 0x24 */ s16 width;          /* obj+0x34 */
    /* 0x26 */ s16 height;         /* obj+0x36 */
    /* 0x28 */ s16 lifetime;       /* obj+0x38: counts down by the frame delta; 0 == expired */
    /* 0x2A */ s8 alphaFade;       /* obj+0x3A: subtracted from alpha each tick */
    /* 0x2B */ u8 expireFuncIdx;   /* obj+0x3B: low nibble indexes D_8008D5D0 */
    /* 0x2C */ s8 primR;
    /* 0x2D */ s8 primG;
    /* 0x2E */ s8 primB;
    /* 0x2F */ u8 alpha;
    /* 0x30 */ s8 envR;
    /* 0x31 */ s8 envG;
    /* 0x32 */ s8 envB;
    /* 0x34 */ s16 flags;          /* obj+0x44: bit0 enables the env colour */
} ParticleInit;

void func_1518CA80(ParticleSpawnArgs *params, u8 useFloatPos)
{
    ParticleInit sp30;
    u8 brightness;

    brightness = params->brightness;
    sp30.primR = (params->primR * brightness) >> 8;
    sp30.primG = (params->primG * brightness) >> 8;
    sp30.primB = (params->primB * brightness) >> 8;
    sp30.envR = (params->envR * brightness) >> 8;
    sp30.envG = (params->envG * brightness) >> 8;
    sp30.envB = (params->envB * brightness) >> 8;
    sp30.lifetime = params->lifetime;
    sp30.alpha = params->alpha;
    sp30.alphaFade = params->alphaFade;
    sp30.animFrame = 0;
    sp30.animPtr = D_8008CA4C;
    sp30.animSpeed = 0x100;

    if (useFloatPos == 1) {
        sp30.x = (s32)params->x;
        sp30.y = (s32)params->y;
        sp30.z = (s32)params->z;
        sp30.xFrac = ((s32)(params->x * 256.0f)) & 0xFF;
        sp30.yFrac = ((s32)(params->y * 256.0f)) & 0xFF;
        sp30.zFrac = ((s32)(params->z * 256.0f)) & 0xFF;
    } else {
        sp30.x = params->xInt;
        sp30.y = params->yInt;
        sp30.z = params->zInt;
        sp30.xFrac = params->xFrac;
        sp30.yFrac = params->yFrac;
        sp30.zFrac = params->zFrac;
    }

    sp30.velX = params->velX;
    sp30.velZ = params->velZ;
    sp30.velY = params->velY;
    sp30.accelY = params->accelY;
    sp30.updateFuncIdx = 9;
    sp30.flags = 1;
    sp30.width = params->width;
    sp30.height = params->height;
    sp30.sizeGrowth = params->widthGrowth << 16;
    sp30.sizeGrowth += params->heightGrowth;
    sp30.expireFuncIdx = params->expireFuncIdx;
    sp30.unk1A = 0;
    sp30.unk08 = 0;
    func_15167D84(&sp30, 0, 0, -1, 0xFF, 1);
}

extern void (*D_8008D5D0[])(void);

/* D_8008C9C8[9]: the per-frame hook selected by ParticleInit::updateFuncIdx.
 * obj points at the spawned object, i.e. ParticleInit sits at obj + 0x10. */
void func_1518CCA8(u8 *obj)
{
  s32 sizeGrowth;
  s32 expireFuncIdx;
  sizeGrowth = *((s32 *) (obj + 0x14));
  *((s16 *) (obj + 0x34)) = (*((s16 *) (obj + 0x34))) + ((sizeGrowth & 0xFFFF0000) >> 0x10);
  *((s16 *) (obj + 0x36)) = (*((s16 *) (obj + 0x36))) + (sizeGrowth & 0xFFFFu);
  if ((*((s16 *) (obj + 0x38))) == 0)
  {
    expireFuncIdx = obj[0x3B] & 0xF;
    if (expireFuncIdx != 0)
    {
      D_8008D5D0[expireFuncIdx]();
    }
  }
}
