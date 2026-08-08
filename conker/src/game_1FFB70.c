#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_15167A68(s32, s32, s32, s32, s32, s32);
extern s32 func_1510D0EC(s32, s32, s32, s32);
extern u8 D_A48[];

#define WGFX151D2830(pkt, a, b)    \
{                                   \
    Gfx *_g = (Gfx *)(pkt);         \
    _g->words.w0 = (u32)(a);        \
    _g->words.w1 = (u32)(b);        \
}

/* Full-screen scrolling haze/overlay effect object (spawned + stopped by script
 * commands).  func_151D275C is its per-frame update and func_151D2830 its draw
 * callback; both are installed in the object-type callback table at 0x8008C0D8. */
struct ScreenOverlayFx {
    u8  pad0[0xE];
    s16 timer;         /* 0..0x12D; timer += dt * timerStep, drives alpha */
    s16 viewportIndex; /* only drawn while the renderer's viewport index matches */
    s16 scrollS;       /* texture S offset, +1/frame, wraps at 0x100 (= 64 texels) */
    s16 alpha;         /* env-colour alpha, 0..0x80; 0 = nothing to draw */
    s8  timerStep;     /* +1 while playing, -2 to rewind/abort the effect */
};

struct ScreenOverlayFx *func_151D26C0(s16 viewportIndex) {
    struct ScreenOverlayFx *fx;

    fx = func_15167A68(0x3C, 1, 0x18, 0, 0xFF, 1);
    fx->alpha = 0;
    fx->scrollS = 0;
    fx->timer = 0;
    fx->timerStep = 1;
    fx->viewportIndex = viewportIndex;
    return fx;
}

/* The same objects seen through the object manager's list links. */
struct ScreenOverlayNode {
    char pad0[0x8];
    struct ScreenOverlayNode *next;
    char padC[0x4];
    s16 viewportIndex;
    char pad12[0x4];
    s8 timerStep;
};

extern struct ScreenOverlayNode *D_800DD0E0;

void func_151D2718(s16 viewportIndex) {
    struct ScreenOverlayNode *node;

    for (node = D_800DD0E0; node != NULL; node = node->next) {
        if (viewportIndex == node->viewportIndex) {
            node->timerStep = -2;
        }
    }
}

void func_151D275C(struct ScreenOverlayFx *fx) {
    s32 step;
    s32 maxAlpha;

    maxAlpha = 0x80;
    fx->timer += (u32)D_800BE9E4 * (step = fx->timerStep);

    if ((step > 0) && (fx->timer >= 0xED)) {
        fx->alpha = (0x128 - fx->timer) << 2;
        if (fx->alpha < 0) {
            fx->alpha = 0;
        }
    } else {
        fx->alpha = (*(s16 *)&fx->timer) * 2;
    }

    if (fx->alpha >= 0x80) {
        fx->alpha = maxAlpha;
    }

    fx->scrollS++;
    if (fx->scrollS >= 0x100) {
        fx->scrollS -= 0x100;
    }

    if ((fx->timer >= 0x12D) || (fx->timer < 0)) {
        func_1516972C((struct102 *)fx);
    }
}

Gfx *func_151D2830(Gfx *gfx, struct ScreenOverlayFx *fx, s16 viewportIndex) {
    s32 texAddr;

    if ((viewportIndex != fx->viewportIndex) || (fx->alpha == 0)) {
        return gfx;
    }

    WGFX151D2830(gfx++, 0xD7000002, 0xFFFFFFFF);
    WGFX151D2830(gfx++, 0xE7000000, 0);
    WGFX151D2830(gfx++, 0xFC12D225, 0xFFA7FFFF);
    WGFX151D2830(gfx++, 0xEF002C3F, 0x00504244);

    texAddr = func_1510D0EC((s32)D_A48, 0, 3, 0);

    WGFX151D2830(gfx++, 0xFD700000, texAddr);
    WGFX151D2830(gfx++, 0xF5700000, 0x07018060);
    WGFX151D2830(gfx++, 0xE6000000, 0);
    WGFX151D2830(gfx++, 0xF3000000, 0x077FF000);
    WGFX151D2830(gfx++, 0xE7000000, 0);
    WGFX151D2830(gfx++, 0xF5681000, 0x00018060);
    WGFX151D2830(gfx++, 0xF2000000, 0x000FC0FC);
    /* 0xFB = G_SETENVCOLOR: alpha rides in the low byte of the packed RGBA. */
    WGFX151D2830(gfx++, 0xFB000000, (fx->alpha & 0xFF) | 0x00FF0000);
    gSPTextureRectangle(gfx++, 0, 0, 0x500, 0x3C0, 0, fx->scrollS << 3, 0x400, 0x400, 0x400);
    WGFX151D2830(gfx++, 0xE7000000, 0);
    WGFX151D2830(gfx++, 0xFB000000, ((fx->alpha >> 1) & 0xFF) | 0xFF000000);
    gSPTextureRectangle(gfx++, 0, 0, 0x500, 0x3C0, 0, fx->scrollS << 3, 0, 0x200, 0x200);

    return gfx;
}
