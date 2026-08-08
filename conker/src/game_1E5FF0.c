#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* Wraps an angle back into [0, 2*pi). */
extern f32 func_15144B68(f32);

/*
 * Every updater in this file implements the same behaviour for a different
 * object class: hover the object up and down on a sine wave while spinning it
 * at a constant rate about X and Z (a floating, tumbling object).
 *
 * D_800BE9A4 is the float frame delta.
 */

/*
 * Generic game object (behaviour table D_800898B0).
 * Layout cross-checked against func_15132DDC / func_151337C0 / func_15154A88:
 *   0x20..0x28 rotation xyz, 0x38..0x40 position xyz,
 *   0x44..0x4C velocity xyz, 0x50..0x58 angular velocity xyz, 0x5C gravity.
 * This behaviour re-uses the velocity/gravity slots as its oscillator state.
 */
struct BobSpinObj151B8B40 {
    char pad20[0x20];
    /* 0x20 */ f32 rotX;
    char pad24[0x4];
    /* 0x28 */ f32 rotZ;
    char pad2C[0x10];
    /* 0x3C */ f32 posY;
    /* 0x40 */ f32 posZ;
    /* 0x44 */ f32 bobPhase;
    /* 0x48 */ f32 bobBaseY;
    /* 0x4C */ f32 bobPhaseSpeed;
    /* 0x50 */ f32 rotSpeedX;
    char pad54[0x4];
    /* 0x58 */ f32 rotSpeedZ;
    /* 0x5C */ f32 bobAmplitude;
};

s32 func_151B8B40(struct BobSpinObj151B8B40 *obj) {
    obj->posY = sinf(obj->bobPhase) * obj->bobAmplitude + obj->bobBaseY;
    obj->bobPhase = obj->bobPhase + obj->bobPhaseSpeed * D_800BE9A4;
    obj->bobPhase = func_15144B68(obj->bobPhase);
    obj->rotX = obj->rotX + obj->rotSpeedX * D_800BE9A4;
    obj->rotZ = obj->rotZ + obj->rotSpeedZ * D_800BE9A4;
    return 1;
}

extern void func_151D9450(void*, void*);

/*
 * Sprite/particle object (the class func_151D9450 / func_151D9534 drive):
 *   0x38/0x3C sprite scale x/y, 0x40..0x48 position xyz,
 *   0x58..0x60 velocity xyz, 0x64 gravity.
 * Again the velocity/gravity slots double as this behaviour's oscillator
 * state; func_151D9450 then pulses the sprite's scale.
 */
struct BobSprite151B8BE0 {
    char pad44[0x44];
    /* 0x44 */ f32 posY;
    char pad48[0x10];
    /* 0x58 */ f32 bobPhase;
    /* 0x5C */ f32 bobBaseY;
    /* 0x60 */ f32 bobPhaseSpeed;
    /* 0x64 */ f32 bobAmplitude;
};

void func_151B8BE0(struct BobSprite151B8BE0 *spr, void *arg1) {
    spr->posY = sinf(spr->bobPhase) * spr->bobAmplitude + spr->bobBaseY;
    spr->bobPhase = spr->bobPhase + spr->bobPhaseSpeed * D_800BE9A4;
    spr->bobPhase = func_15144B68(spr->bobPhase);
    func_151D9450(spr, arg1);
}

/*
 * Object of the class updated through D_8008AD90 (see func_151572D0 /
 * func_15157010): position xyz lives at 0x54/0x58/0x5C and the 0x38-byte
 * behaviour parameter block is memcpy'd to object+0x120.
 */
struct BobSpinObj151B8C54 {
    char pad58[0x58];
    /* 0x58 */ f32 posY;
};

/*
 * The parameter block at object+0x120.  func_15157918 / func_15157DEC build
 * the object's matrix from params[0..2] as euler rotation xyz and params[3]
 * as scale, so 0x0/0x8 here are the X and Z rotation angles.
 */
struct BobSpinParams151B8C54 {
    /* 0x00 */ f32 rotX;
    char pad4[0x4];
    /* 0x08 */ f32 rotZ;
    char padC[0x4];
    /* 0x10 */ f32 bobPhase;
    /* 0x14 */ f32 bobBaseY;
    /* 0x18 */ f32 bobPhaseSpeed;
    /* 0x1C */ f32 rotSpeedX;
    char pad20[0x4];
    /* 0x24 */ f32 rotSpeedZ;
    /* 0x28 */ f32 bobAmplitude;
};

s32 func_151B8C54(struct BobSpinObj151B8C54 *obj) {
    struct BobSpinParams151B8C54 *params = (struct BobSpinParams151B8C54 *)((char *)obj + 0x120);
    obj->posY = sinf(params->bobPhase) * params->bobAmplitude + params->bobBaseY;
    params->bobPhase = params->bobPhase + params->bobPhaseSpeed * D_800BE9A4;
    params->bobPhase = func_15144B68(params->bobPhase);
    params->rotX += params->rotSpeedX * (&D_800BE9A4)[0];
    params->rotZ += params->rotSpeedZ * (&D_800BE9A4)[0];
    return 1;
}

/*
 * Object of the class updated through D_80089C70: func_1514143C copies
 * 0x34/0x38/0x3C out as x/y/z, and func_151B85AC integrates 0x40/0x44/0x48
 * by the rates at 0x4C/0x50/0x54, so 0x40..0x48 is the rotation triple.
 */
struct BobSpinObj151B8CFC {
    char pad38[0x38];
    /* 0x38 */ f32 posY;
    char pad3C[0x4];
    /* 0x40 */ f32 rotX;
    char pad44[0x4];
    /* 0x48 */ f32 rotZ;
};

/* The behaviour parameter block at object+0x110. */
struct BobSpinParams151B8CFC {
    /* 0x00 */ f32 bobBaseY;
    /* 0x04 */ f32 bobAmplitude;
    /* 0x08 */ f32 bobPhase;
    /* 0x0C */ f32 bobPhaseSpeed;
    /* 0x10 */ f32 rotSpeedX;
    char pad14[0x4];
    /* 0x18 */ f32 rotSpeedZ;
};

s32 func_151B8CFC(struct BobSpinObj151B8CFC *obj) {
    struct BobSpinParams151B8CFC *params = (struct BobSpinParams151B8CFC *)((char *)obj + 0x110);
    obj->posY = sinf(params->bobPhase) * params->bobAmplitude + params->bobBaseY;
    params->bobPhase = params->bobPhase + params->bobPhaseSpeed * D_800BE9A4;
    params->bobPhase = func_15144B68(params->bobPhase);
    obj->rotX += params->rotSpeedX * (&D_800BE9A4)[0];
    obj->rotZ += params->rotSpeedZ * (&D_800BE9A4)[0];
    return 1;
}
