#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern u8 D_800D9900;
struct260 *func_15149130(s16 arg0, s8 arg1, s8 arg2, s8 arg3, u8 arg4, u8 arg5, struct37 *arg6, u8 arg7, s32 arg8);

/*
 * Full-screen flash ("lightning") effect.
 *
 * A flash object cycles with period = flashDuration + darkDuration.  While
 * timer <= flashDuration the effect is in its bright phase (scene light forced
 * to white, screen filled white at flashAlpha); the rest of the cycle it fills
 * the screen black at darkAlpha.  The payload below is memcpy'd into the
 * generic effect object at +0x28 by func_15149130.
 */
struct FlashParams {
    /* 0x00 */ u8  isFlashing;
    /* 0x01 */ u8  pad1[3];
    /* 0x04 */ f32 timer;
    /* 0x08 */ f32 flashDuration;
    /* 0x0C */ f32 darkDuration;
    /* 0x10 */ f32 period;
    /* 0x14 */ u8  flashAlpha;
    /* 0x15 */ u8  darkAlpha;
    /* 0x16 */ u8  pad16[2];
};

void func_150D2110(s16 lifetime, f32 flashDuration, f32 darkDuration, u8 flashAlpha, u8 darkAlpha, u8 arg5, s32 arg6) {
    struct FlashParams flash;
    struct260 *temp_v0;

    D_800D9900++;

    flash.flashDuration = flashDuration;
    flash.darkDuration = darkDuration;
    flash.period = flashDuration + darkDuration;
    flash.isFlashing = 0;
    flash.timer = 0.0f;
    flash.flashAlpha = flashAlpha;
    flash.darkAlpha = darkAlpha;

    temp_v0 = func_15149130(lifetime, -1, 0x2F, 2, 1, 0x26, (struct37 *)0x18, arg5, arg6);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &flash, 0x18);
    }
}

extern f32 D_800BE9A4;

/* Same payload as struct FlashParams, as seen by the per-frame update. */
struct FlashState {
    /* 0x00 */ u8  isFlashing;
    /* 0x01 */ u8  pad1[3];
    /* 0x04 */ f32 timer;
    /* 0x08 */ f32 flashDuration;
    /* 0x0C */ u8  padC[4];
    /* 0x10 */ f32 period;
};

struct FlashObj {
    /* 0x00 */ u8  pad0[0x28];
    /* 0x28 */ struct FlashState flash;
};

/* Same object again, as seen by the draw callback. */
struct FlashDrawObj {
    /* 0x00 */ u8 pad_0x0[0x28];
    /* 0x28 */ u8 isFlashing;
    /* 0x29 */ u8 pad_0x29[0x13];
    /* 0x3C */ u8 flashAlpha;
    /* 0x3D */ u8 darkAlpha;
};

void func_150D21CC(struct FlashObj *obj) {
    struct FlashState *state = &obj->flash;

    obj->flash.timer += D_800BE9A4;
    if (obj->flash.period < obj->flash.timer) {
        do {
            state->timer -= state->period;
        } while (state->period < state->timer);
    }
    if (state->timer <= state->flashDuration) {
        state->isFlashing = 1;
        func_1515D4D4(255, 255, 255, 255);
    } else {
        state->isFlashing = 0;
    }
}

void func_150D22D4(s32 obj);

void func_150D227C(s32 obj) {
    func_150D22D4(obj);
    func_1514933C((struct260 *)obj);
}

void func_150D22A8(s32 obj) {
    func_150D22D4(obj);
    func_15149368((struct260 *)obj);
}

extern u8 D_800D9900;

void func_150D22D4(s32 obj) {
    D_800D9900--;
}

s32 func_1517F08C(s32, s32, s32, s32, s32, s32);

s32 func_150D22F4(s32 gfx, struct FlashDrawObj *obj, s32 viewport) {
    if (obj->isFlashing == 1) {
        gfx = func_1517F08C(gfx, obj->flashAlpha, 0xFF, 0xFF, 0xFF, (s16)viewport);
    } else {
        gfx = func_1517F08C(gfx, obj->darkAlpha, 0, 0, 0, (s16)viewport);
    }
    return gfx;
}

/*
 * Emitter that keeps spawning flash objects: every `timer` ticks it creates one
 * with a random lifetime in [lifetimeBase, lifetimeBase + lifetimeRange] and
 * then rearms itself with a random delay in [delayBase, delayBase + delayRange].
 */
struct FlashSpawner {
    /* 0x00 */ s32 delayBase;
    /* 0x04 */ s32 delayRange;
    /* 0x08 */ s32 timer;
    /* 0x0C */ s16 lifetimeBase;
    /* 0x0E */ s16 lifetimeRange;
    /* 0x10 */ f32 flashDuration;
    /* 0x14 */ f32 darkDuration;
    /* 0x18 */ u8 flashAlpha;
    /* 0x19 */ u8 darkAlpha;
};

void func_150D2374(u8 *obj) {
    struct FlashSpawner *spawner;
    s32 temp;

    spawner = (struct FlashSpawner *)(obj + 0x28);
    spawner->timer -= D_800BE9E4;
    if (spawner->timer < 0) {
        temp = func_150ADA20();
        func_150D2110((s16)((temp % (u32)(spawner->lifetimeRange + 1)) + spawner->lifetimeBase), spawner->flashDuration, spawner->darkDuration, spawner->flashAlpha, spawner->darkAlpha, obj[0xC], obj[1]);
        spawner->timer = (func_150ADA20() % (u32)(spawner->delayRange + 1)) + spawner->delayBase;
    }
}
