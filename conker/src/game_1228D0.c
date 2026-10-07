#include <ultra64.h>
#define func_150ADA20 func_150ADA20_u8_decl_in_functions_h
#include "functions.h"
#undef func_150ADA20
u32 func_150ADA20(void);
#include "variables.h"

/* Partial view of an actor (struct127) that an effect is attached to. */
typedef struct {
    s32 interaction_state; /* 0 = actor slot free */
    u8 pad4[0x10];
    f32 x_position;
    f32 y_position;
    f32 z_position;
    u8 pad20[0x3B - 0x20];
    u8 unique_id; /* changes when the slot is reused; effects compare it to detect a dead owner */
    u8 pad3C[0x94 - 0x3C];
    s32 unk94;
    u8 pad98[0x1D4 - 0x98];
    s32 model; /* model instance; points are transformed from its local space to world */
} EffectOwner;

/* Creation parameters for a 2D overlay sprite (func_15169968). Copied to the live sprite at +0x10. */
typedef struct {
    /* 0x00 */ void *image;
    /* 0x04 */ void *unk4;
    /* 0x08 */ s32 fadeInHold;   /* (fade-in frames << 16) | hold frames */
    /* 0x0C */ s32 fadeOutTotal; /* (fade-out frames << 16) | total frames */
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s16 duration;     /* initial countdown timer = total frames */
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ u8  pad1A[0x2];
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 scaleX;       /* 4.12 fixed point, 0x1000 = 1.0 */
    /* 0x2A */ s16 scaleY;
    /* 0x2C */ s16 x;            /* screen position */
    /* 0x2E */ s16 y;
    /* 0x30 */ u8  unk30;
    /* 0x31 */ u8  unk31;
    /* 0x32 */ u8  unk32;
    /* 0x33 */ u8  unk33;
    /* 0x34 */ u8  unk34;
    /* 0x35 */ u8  unk35;
    /* 0x36 */ u8  unk36;
    /* 0x37 */ u8  unk37;
    /* 0x38 */ u8  unk38;
    /* 0x39 */ u8  unk39;
} OverlayDesc;

typedef struct {
    /* 0x00 */ u8  ownerId; /* owner->unique_id */
    /* 0x01 */ u8  pad1[0x3];
    /* 0x04 */ void *owner;
    /* 0x08 */ u8  unk8;
    /* 0x09 */ u8  pad9[0x3];
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u8  unk24;
    /* 0x25 */ u8  pad25;
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
} struct_150F6890;

extern u8 D_800917F8;
extern u8 D_80091930;
extern u8 D_8009193C;
extern u8 D_80091948;
struct102 *func_15169968(OverlayDesc *);
void *func_15134DAC(struct_150F6890 *, s32);

/* Spawns one of four 2D overlay images with a fade-in / hold / fade-out alpha envelope.
 * variant 0 is drawn centred at full scale; variants 1-3 are smaller images placed off-centre. */
void overlay_spawn_faded(s32 fadeIn, s32 hold, s32 fadeOut, s32 variant) {
    OverlayDesc desc;
    s32 total;

    if (variant != 0) {
        if (variant == 2) {
            desc.x = 0xF0;
            desc.y = 0xBA;
            desc.image = &D_80091948;
        } else {
            desc.x = 0x10E;
            desc.y = 0x7C;
            if (variant == 1) {
                desc.image = &D_80091930;
            } else {
                desc.image = &D_8009193C;
            }
        }
        desc.unk30 = 9;
        desc.unk39 = 0x10;
        desc.scaleX = 0;
        desc.scaleY = 0;
        desc.unk36 = 8;
    } else {
        desc.image = &D_800917F8;
        desc.unk30 = 0xA;
        desc.x = 0xA0;
        desc.y = 0xC0;
        desc.unk39 = 0x20;
        desc.scaleX = 0x1000;
        desc.scaleY = 0x1000;
        desc.unk36 = 0x18;
    }

    total = fadeIn + hold + fadeOut;
    desc.fadeInHold = (fadeIn << 16) | hold;
    desc.fadeOutTotal = (fadeOut << 16) | total;
    desc.unk10 = 0x2710;
    desc.duration = total;
    desc.unk1C = 146.0f;
    desc.unk20 = 100.0f;
    desc.unk18 = 0;
    desc.unk24 = 0;
    desc.unk26 = 0;
    desc.unk31 = 1;
    desc.unk32 = 0xFF;
    desc.unk33 = 0xFF;
    desc.unk34 = 0xFF;
    desc.unk37 = 0x11;
    desc.unk35 = 0;
    desc.unk16 = 0;
    func_15169968(&desc);
}

/* A live overlay sprite (fields from OverlayDesc land here at +0x10). */
struct OverlaySprite {
    char pad0[0x18];
    s32 fadeInHold;   /* (fade-in frames << 16) | hold frames */
    s32 fadeOutTotal; /* (fade-out frames << 16) | total frames */
    char pad20[0x24 - 0x20];
    s16 timer;        /* counts down from total frames */
    char pad26[0x38 - 0x26];
    s16 scaleX;
    s16 scaleY;
    char pad3C[0x45 - 0x3C];
    u8 alpha;
};

void overlay_update_fade(struct OverlaySprite *);

/* Overlay update for the zooming variant: scale grows toward 1.0 as the timer runs down. */
void overlay_update_zoom_fade(struct OverlaySprite *sprite) {
    s32 scale = 0x1000 - (sprite->timer << 2);
    sprite->scaleX = scale;
    sprite->scaleY = sprite->scaleX;
    overlay_update_fade(sprite);
}

/* Alpha envelope: ramps 0 -> 255 over the fade-in, holds at 255, then ramps back to 0. */
void overlay_update_fade(struct OverlaySprite *sprite) {
    s32 timer;
    s32 total;
    s32 fadeIn;
    s32 hold;
    s32 fadeInEnd;
    s32 fadeOut;
    s32 elapsed;
    s32 rampIn;
    s32 rampOut;

    total = sprite->fadeOutTotal & 0xFFFF;
    fadeIn = sprite->fadeInHold >> 16;
    hold = sprite->fadeInHold & 0xFFFF;
    fadeOut = sprite->fadeOutTotal >> 16;
    fadeInEnd = total - fadeIn;
    timer = sprite->timer;

    if (fadeInEnd < timer) {
        elapsed = total - timer;
        rampIn = elapsed * 0xFF;
        sprite->alpha = rampIn / fadeIn;
    } else if ((fadeInEnd - hold) < timer) {
        sprite->alpha = 0xFF;
    } else {
        rampOut = timer * 0xFF;
        sprite->alpha = rampOut / fadeOut;
    }
}

void func_15179008(s32);

void func_150F568C(s32 arg0) {
    func_15179008(0);
}

/* Animation playback state (struct197). */
typedef struct {
    u8 pad0[0x8];
    f32 frame; /* current animation frame */
} AnimState;
/* Partial view of an actor (struct127). */
typedef struct {
    u8 pad0[0x84];
    u16 animId; /* animation currently playing */
    u8 pad86[0x2D0 - 0x86];
    AnimState *anim;
} AnimActor;
/* A model part whose texture can be swapped per frame. */
typedef struct {
    u8 pad0[0x18];
    s16 texId;
} TexPart;
extern s32 D_80090274[]; /* nine texture frames, ids 0xCB2..0xCBA */

/* Animated-texture callback: while the actor plays animation 0xAE, picks which of the nine
 * texture frames to show from how far the animation has progressed (frame 6 otherwise). */
s32 animtex_select_frame(TexPart *part, AnimActor *actor) {
    AnimState *anim;
    s32 idx;
    f32 t;

    anim = actor->anim;
    if (anim == NULL) {
        return 0;
    }
    idx = 6;
    if (actor->animId == 0xAE) {
        if (anim->frame >= 36.0f && anim->frame <= 51.0f) {
            t = anim->frame - 36.0f;
            t *= 0.0625f;
            t = 1.0f - t;
            idx = 6 * t;
        } else if (anim->frame > 51.0f && anim->frame <= 54.0f) {
            idx = 0;
        } else if (anim->frame > 54.0f && anim->frame <= 60.0f) {
            t = anim->frame - 54.0f;
            t *= 0.1428571492f;
            idx = 6 * t;
        } else if (anim->frame > 60.0f && anim->frame <= 65.0f) {
            t = anim->frame - 60.0f;
            t *= 0.1666666716f;
            idx = (s32)(2 * t) + 7;
        } else if (anim->frame > 65.0f && anim->frame <= 67.0f) {
            t = anim->frame - 65.0f;
            t *= 0.3333333433f;
            t = 1.0f - t;
            idx = (s32)(2 * t) + 7;
        } else if (anim->frame > 67.0f && anim->frame <= 70.0f) {
            t = anim->frame - 67.0f;
            t *= 0.25f;
            t = 1.0f - t;
            idx = (s32)(2 * t) + 4;
        } else if (anim->frame > 70.0f && anim->frame <= 74.0f) {
            t = anim->frame - 70.0f;
            t *= 0.200000003f;
            idx = (s32)(2 * t) + 4;
        } else if (anim->frame > 74.0f && anim->frame <= 119.0f) {
            t = anim->frame - 74.0f;
            t *= 0.02173913084f;
            idx = (s32)(2 * t) + 7;
        } else if (anim->frame > 119.0f && anim->frame <= 150.0f) {
            t = anim->frame - 119.0f;
            t *= 0.03125f;
            t = 1.0f - t;
            idx = (s32)(2 * t) + 7;
        }
    }
    part->texId = D_80090274[idx];
    return 0;
}

/* A model part whose display list has a scrollable texture. */
typedef struct {
    u8 pad0[0x24];
    Gfx **gfx;
    u8 pad28[0x10];
    s32 state; /* 0 = waiting for animation 5, 1 = following it, 2 = finished */
} ScrollPart;

/* Texture-scroll callback: patches the first G_SETTILESIZE in the part's display list so the
 * texture slides with the actor's animation 5 (frames 69..84 map to S = 102..44). */
s32 texscroll_follow_anim(ScrollPart *part, AnimActor *actor) {
    AnimState *anim;
    s32 count;
    Gfx *gfx;
    s32 fixed;
    f32 ratio; /* BUG (original game): read uninitialised when state is not 0-2 and animId != 5 */
    s32 i;
    s32 s;

    anim = actor->anim;
    if (anim == NULL) {
        return 0;
    }
    gfx = *part->gfx;
    count = 1;
    fixed = 0;
    switch (part->state) {
        case 0:
            if (actor->animId == 5) {
                part->state = 1;
                ratio = 1.0f;
            } else {
                fixed = 1;
            }
            break;
        case 1:
            ratio = 1.0f;
            break;
        case 2:
            ratio = 0.0f;
            break;
    }
    if (actor->animId == 5) {
        if (anim->frame < 69.0f) {
            ratio = 1.0f;
        } else if (anim->frame > 84.0f) {
            ratio = 0.0f;
            part->state = 2;
        } else {
            ratio = (anim->frame - 69.0f) / 15.0f;
            ratio = 1.0f - ratio;
        }
    }
    i = 0;
    do {
        while (((s8 *)&gfx[i])[0] != (s8)G_SETTILESIZE) {
            i++;
        }
        count--;
        if (count != 0) {
            i++;
        }
    } while (count != 0);
    if (fixed) {
        s = 2;
    } else {
        s = 58.0f * ratio + 44.0f;
    }
    gfx[i].words.w0 = _SHIFTL(G_SETTILESIZE, 24, 8) | _SHIFTL(2, 12, 12) | _SHIFTL(s, 0, 12);
    return 0;
}

/* Spawns an effect attached to `owner` and stores {owner, owner->unique_id, 0.0f} in its data at
 * +0x28 -- the layout emitter_update's emitter reads. */
void func_150F5C08(void *owner, s16 arg1, u8 arg2, s32 arg3) {
    struct {
        void *owner;
        u8 ownerId;
        u8 pad5;
        u8 pad6;
        u8 pad7;
        f32 accum;
    } data;
    struct260 *effect;

    data.owner = owner;
    data.ownerId = *(u8 *)((s32)owner + 0x3B);
    data.accum = 0.0f;

    effect = func_15149130(arg1, -1, 0x51, -1, 1, 0x3E, (struct37 *)0xC, arg2, arg3);
    if (effect != NULL) {
        memcpy((void *)((s32)effect + 0x28), &data, 0xC);
    }
}

/* Particle descriptor passed to func_15130280 (0x70 bytes). */
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
    s16 unk20; /* 255 / lifetime */
    s16 unk22;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    struct17 pos;
    struct17 unk3C;
    struct17 vel;
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
} ParticleDesc; /* 0x70 */
typedef struct {
    EffectOwner *owner;
    u8 ownerId;
    u8 pad5[3];
    f32 accum; /* fractional particles owed */
} EmitterData;
typedef struct {
    u8 pad0;
    u8 unk1;
    u8 pad2[0xA];
    u8 unkC;
    u8 padD;
    s16 state; /* set to -1 to free the effect */
    u8 pad10[0x28 - 0x10];
    EmitterData data;
} EmitterEffect;
/* Emitter segment endpoints in the owner's model space. */
const struct17 D_800A1B00 = { 0.0f, 0.0f, 14.0f };
const struct17 D_800A1B0C = { 0.0f, 0.0f, 78.0f };
extern s32 func_15145EA4(s32 *arg0, s32 *arg1, s32 arg2, s32 arg3);
extern void *func_15130280(void *, u8, s32, s32, u8, s32);

/* Emitter update: frees itself when the owner is gone, otherwise emits ~0.26-0.46 particles per
 * frame scattered along a segment of the owner's model, each moving along that segment. */
void emitter_update(EmitterEffect *effect) {
    EmitterData *data;
    EffectOwner *owner;
    ParticleDesc spawn;
    f32 tint;
    struct17 start;
    struct17 end;
    f32 dx;
    f32 dy;
    f32 dz;
    s32 srcs[2];
    s32 dsts[2];
    s32 flags;
    s16 life;
    f32 scale;
    void *ret;

    data = &effect->data;
    owner = data->owner;
    if (owner->interaction_state == 0 || owner->unique_id != data->ownerId) {
        effect->state = -1;
        return;
    }
    if (owner->model == 0) {
        return;
    }
    data->accum += (0.2600000203f + func_150ADA68() * 0.1950000077f) * D_800BE9A4;
    if (data->accum > 1.0f) {
        spawn.unk14 = 0xFF;
        spawn.unk15 = 0xFF;
        spawn.unk16 = 0xFF;
        spawn.unk18 = 0xB4;
        spawn.unk19 = 0xB4;
        spawn.unk1A = 0xB4;
        srcs[0] = (s32)&D_800A1B00;
        srcs[1] = (s32)&D_800A1B0C;
        dsts[0] = (s32)&start;
        dsts[1] = (s32)&end;
        func_15145EA4(srcs, dsts, owner->model + 0x140, 2);
        spawn.unk1D = 0x6C;
        spawn.unk8 = 0x5103;
        spawn.unk0 = 0x200005;
        spawn.unk4 = 0x9F0600;
        spawn.unkC = 0;
        spawn.unk10 = 0;
        spawn.unk17 = 0xFF;
        spawn.unk1C = 0xFF;
        dx = end.unk0 - start.unk0;
        dy = end.unk4 - start.unk4;
        dz = end.unk8 - start.unk8;
        spawn.unk3C = *(struct17 *)&D_800A5480;
        spawn.unk58 = 0x84CE07;
        spawn.unk60 = 8;
        spawn.unk61 = 6;
        spawn.unk62 = 0x10;
        spawn.unk63 = -1;
        spawn.unk64 = -1;
        spawn.unk65 = 0;
        spawn.unk5C = 0;
        spawn.unk66 = 0xFF;
        spawn.unk68 = 1000;
        spawn.unk6C = 1000.0f;
        tint = 0.9730340242f;
        spawn.unk24 = 1.022472024f;
        do {
            life = spawn.unk1E = spawn.unk22 = spawn.unkA = func_150ADA20() % 21U + 20;
            spawn.unk20 = 255 / life;
            spawn.unk1B = func_150ADA20() % 26U + 8;
            spawn.unk28 = spawn.unk2C = func_150ADA68() * 70.0f + 148.0f;
            spawn.unk54 = func_150ADA68() * 0.2190000117f + 0.08600000292f;
            scale = func_150ADA68() * 0.04100000113f + 0.07800000161f;
            spawn.vel.unk0 = dx * scale;
            spawn.vel.unk4 = dy * scale;
            spawn.vel.unk8 = dz * scale;
            scale = func_150ADA68() * D_800BE9A4;
            spawn.unk58 &= ~0xC0;
            spawn.pos.unk0 = spawn.vel.unk0 * scale + start.unk0;
            spawn.pos.unk4 = spawn.vel.unk4 * scale + start.unk4;
            spawn.pos.unk8 = spawn.vel.unk8 * scale + start.unk8;
            flags = (func_150ADA20() & 1) ? 0x80 : 0;
            spawn.unk58 |= ((func_150ADA20() & 1) ? 0x40 : 0) | flags;
            ret = func_15130280(&spawn, 1, 0, 4, effect->unkC, effect->unk1);
            if (ret != NULL) {
                memcpy((u8 *)ret + 0xA8, &tint, 4);
            }
            data->accum -= 1.0f;
        } while (data->accum > 1.0f);
    }
}

void func_150F6138(s32 arg0, s32 arg1, u8 arg2) {
    func_15149514(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}

typedef struct {
    u8 pad0[0x48];
    f32 unk48;
    f32 unk4C;
    u8 pad50[0x58 - 0x50];
    u8 flags; /* bit 0 = shown */
} Part6178;
/* Something drawn between two points (a beam or streak). */
typedef struct {
    u8 pad0[0x34];
    struct17 start;
    struct17 end;
    u8 pad4C[0x110 - 0x4C];
    Part6178 part;
} Beam6178;
/* Something drawn at a point (a glow or light). */
typedef struct {
    u8 pad0[0x9];
    u8 hidden;
    u8 padA[0xE - 0xA];
    s16 x;
    s16 y;
    s16 z;
} Glow6178;
typedef struct {
    u8 pad0[0x14];
    Glow6178 *glow;
} GlowHolder6178;
typedef struct {
    EffectOwner *owner;
    u8 ownerId;
    u8 pad5[3];
    Beam6178 *beam;
    GlowHolder6178 *glowHolder;
} BeamData;
typedef struct {
    u8 pad0[0xE];
    s16 state; /* set to -1 to free the effect */
    u8 pad10[0x28 - 0x10];
    BeamData data;
} BeamEffect;
/* Beam endpoints in the owner's model space. */
const struct17 D_800A1B18 = { 0.0f, -55.0f, 0.0f };
const struct17 D_800A1B24 = { 0.0f, -115.0f, 0.0f };

/* Beam update: keeps a beam and a glow attached to two points of the owner's model; hides them
 * while the owner has no model or has flag 2 set, and frees itself when the owner is gone. */
void func_150F6178(BeamEffect *effect) {
    BeamData *data;
    EffectOwner *owner;
    struct17 a;
    struct17 b;
    s32 srcs[2];
    s32 dsts[2];

    data = &effect->data;
    owner = data->owner;
    if (owner->interaction_state == 0 || owner->unique_id != data->ownerId) {
        effect->state = -1;
        return;
    }
    if (owner->model != 0 && !(owner->unk94 & 2)) {
        Beam6178 *beam;
        GlowHolder6178 *holder;
        Glow6178 *glow;

        srcs[0] = (s32)&D_800A1B18;
        srcs[1] = (s32)&D_800A1B24;
        dsts[0] = (s32)&a;
        dsts[1] = (s32)&b;
        func_15145EA4(srcs, dsts, owner->model, 2);
        if (data->beam != NULL) {
            beam = data->beam;
            beam->part.flags |= 1;
            beam->start = a;
            beam->end = b;
        }
        holder = data->glowHolder;
        if (holder != NULL) {
            glow = holder->glow;
            glow->hidden = 0;
            glow->x = a.unk0;
            glow->y = a.unk4;
            glow->z = a.unk8;
        }
    } else {
        if (data->beam != NULL) {
            Part6178 *part = &data->beam->part;

            part->flags &= ~1;
        }
        if (data->glowHolder != NULL) {
            Glow6178 *glow = data->glowHolder->glow;

            glow->hidden = 1;
        }
    }
    if (data->beam != NULL) {
        Part6178 *part = &data->beam->part;

        part->unk48 = 4.0f;
        part->unk4C = 8.0f;
    }
}

/* Releases the two overlay sprites (from func_15169968) held at +0x30 and +0x34. */
void func_150F631C(struct260 *arg0) {
    struct260 *temp_a1;
    struct102 *temp_a0;

    temp_a1 = arg0;
    if (*(struct102 *volatile *)((u8 *)temp_a1 + 0x30) != NULL) {
        func_1516972C(*(struct102 **)((u8 *)temp_a1 + 0x30));
    }

    temp_a0 = *(struct102 **)((u8 *)temp_a1 + 0x34);
    if (temp_a0 != NULL) {
        func_1516972C(temp_a0);
    }
}

void func_150F631C(struct260 *arg0);

void func_150F6368(struct260 *arg0) {
    func_150F631C(arg0);
    func_1514933C(arg0);
}

void func_15149368(struct260 *arg0);

void func_150F6394(struct260 *arg0) {
    func_150F631C(arg0);
    func_15149368(arg0);
}

void func_150F63C0(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}

typedef struct {
    char pad_0[0x8];
    s32 field_0x08;
} Field160ChildBlock;

typedef struct {
    char pad_0[0x160];
    u8 *field_0x160;
} Field160Owner;

void func_150F6400(Field160Owner *arg0) {
    Field160ChildBlock *p;

    if (*(s32 *)&arg0->field_0x160 != 0) {
        p = (Field160ChildBlock *)(arg0->field_0x160 + 0x28);
        p->field_0x08 = 0;
    }
}

void func_150F6420(u8 *arg0) {
    func_150F6400(arg0);
    func_1513CA6C((struct210 *)arg0);
}

void func_150F644C(u8 *arg0) {
    func_150F6400(arg0);
    func_1513CAA0((struct210 *)arg0);
}

void func_150F6478(struct210 *arg0) {
}

void func_150F6478(struct210 *);

void func_150F6484(struct210 *arg0) {
    func_150F6478(arg0);
    func_151411A4(arg0);
}

void func_151411C4(struct210 *);

void func_150F64B0(struct210 *arg0) {
    func_150F6478(arg0);
    func_151411C4(arg0);
}

typedef struct {
    EffectOwner *owner;
    u8 ownerId;
    u8 pad5;
    s16 timer; /* frames until the next zap */
} ZapData;
typedef struct {
    u8 pad0;
    u8 unk1;
    u8 pad2[0xA];
    u8 unkC;
    u8 padD;
    s16 state; /* set to -1 to free the effect */
    u8 pad10[0x28 - 0x10];
    ZapData data;
} ZapEffect;
extern s32 D_800BE9E4;
/* Zap origin in the owner's model space. */
const f32 D_800A1B30[3] = { 0.0f, 465.0f, -102.0f };
void func_15143134(const void *, f32 *, s32);
struct225 *func_151602C0(Header *, Header2 *, s32, s32, s32, s32, s32, s32, s32, u8, s32);
void func_15107C1C(EffectOwner *, u8, const void *, s16, s32, s32, s32, f32, f32, s32, s32, u8 *, u8, s32);

/* Periodic zap: every 90-180 frames plays sound 0x679 at the owner, flashes at a point on its
 * model and throws 2-3 bluish sparks. Frees itself when the owner is gone. */
void zap_update(ZapEffect *effect) {
    ZapData *data;
    EffectOwner *owner;
    s8 count;

    data = &effect->data;
    owner = data->owner;
    if (owner->interaction_state == 0 || owner->unique_id != data->ownerId) {
        effect->state = -1;
        return;
    }
    if (owner->model == 0 || (owner->unk94 & 2)) {
        return;
    }
    data->timer -= D_800BE9E4;
    if (data->timer >= 0) {
        return;
    }
    func_10010F88(0x679, 0x18CE, 0, 0, 0, owner->x_position, owner->y_position, owner->z_position, 0x7918, 0x7D00);
    count = (func_150ADA20() & 1) + 2;
    {
        f32 pos[3];
        Header hdr;
        Header2 hdr2;
        u8 color[4];

        func_15143134(D_800A1B30, pos, owner->model);
        hdr.unk0 = 3;
        hdr.unk1 = -1;
        hdr.unk2 = func_150ADA20() % 9U + 10;
        hdr.unk4 = 0;
        hdr2.unk0 = pos[0];
        hdr2.unk4 = pos[1];
        hdr2.unk8 = pos[2];
        func_151602C0(&hdr, &hdr2, func_150ADA20() % 61U + 60, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, effect->unkC,
                      effect->unk1);
        do {
            color[0] = 0xA0;
            color[1] = 0xA0;
            color[2] = 0xFF;
            color[3] = func_150ADA20() % 101U + 155;
            func_15107C1C(owner, 0, D_800A1B30, (u8)func_150ADA20(), func_150ADA20() % 43U - 50,
                          func_150ADA20() % 18U + 5, 4, 27.0f, func_150ADA68() * 16.0f + 20.0f, 0, 2, color, effect->unkC, effect->unk1);
        } while (--count > 0);
    }
    data->timer = func_150ADA20() % 91U + 90;
}

void func_150F6850(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}

/* Spawns an effect (func_15134DAC) that follows `owner`. */
void func_150F6890(void *owner, s16 arg1, s32 arg2, s32 arg3) {
    struct_150F6890 desc;

    desc.ownerId = *((u8 *)owner + 0x3B);
    desc.unk1C = 4.700000286f;
    desc.unk20 = 8.5f;
    desc.unk34 = 1.0f;
    desc.owner = owner;
    desc.unk8 = 3;
    desc.unkC = 0.0f;
    desc.unk10 = 0.0f;
    desc.unk14 = 0.0f;
    desc.unk18 = 0.0f;
    desc.unk24 = 2;
    desc.unk26 = 0x28;
    desc.unk28 = 0x10;
    desc.unk2A = arg1;
    desc.unk2E = 5;
    desc.unk2F = 8;
    desc.unk30 = -1;
    desc.unk38 = 0;
    desc.unk39 = -1;
    desc.unk2C = 0;

    func_15134DAC(&desc, 0);
}

typedef struct { f32 x, y, z; } Vec695C;
typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ u8  pad4[0x14];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ u8  unk1C;
    /* 0x1D */ u8  unk1D;
    /* 0x1E */ u8  pad1E[2];
    /* 0x20 */ s32 unk20;
} Struct695C; /* 0x24 */
typedef struct {
    u8 pad0;
    u8 unk1;
    u8 pad2[0xA];
    u8 unkC;
    u8 padD[0xF];
    s32 unk1C;
} Arg695C;
void func_15137F30(Vec695C *, Vec695C *, Vec695C *, Vec695C *, f32, Arg695C *, Vec695C *,
                   Vec695C *, Vec695C *, f32 *, s16 *, u8 *, f32 *);
void func_1504715C(Struct695C *, s32);
void func_151D9014(void *, void *, s32, f32, s32, s32, f32, s32, f32, f32, s32, void *, s32, s32, s32, s32);

void func_150F695C(Vec695C *arg0, Vec695C *arg1, Vec695C *arg2, Vec695C *arg3, f32 arg4, Arg695C *arg5) {
    Vec695C spA4;
    Vec695C sp98;
    Vec695C sp8C;
    f32 sp88;
    s16 sp86;
    u8 sp85;
    f32 sp80;
    Struct695C sp5C;
    u8 flag;
    s32 flag2;

    func_15137F30(arg0, arg1, arg2, arg3, arg4, arg5, &spA4, &sp98, &sp8C, &sp88, &sp86, &sp85, &sp80);
    sp80 *= 1.0f + func_150ADA68() * 2.0f;
    flag = func_150ADA68() < 0.6000000238f;
    if (flag) {
        func_1504715C(&sp5C, arg5->unk1C);
    } else {
        sp5C.unk0 = -10000.0f;
        sp5C.unk18 = 0;
        sp5C.unk1C = 0;
        sp5C.unk1D = 0;
        sp5C.unk20 = 0;
    }
    if (flag) {
        flag2 = func_150ADA68() < 0.5f;
    } else {
        flag2 = 0;
    }
    func_151D9014(&spA4, &sp8C, 1, sp88, sp86, sp85, sp80, flag, 1.799999952f, 1.799999952f, 1, &sp5C, 1, flag2, arg5->unkC, arg5->unk1);
}
