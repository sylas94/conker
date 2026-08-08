#include <ultra64.h>
#include "functions.h"
#include "variables.h"

/**
 * Sine-driven RGB oscillator: each channel is base + amplitude * sin(phase),
 * with the phase advanced by its own rate every frame and wrapped back into
 * [0, 2*PI) by func_15144B68. The resulting colour is pushed to the global
 * colour slot (D_800DCD20) via func_1515D4D4.
 */
typedef struct {
    /* 0x00 */ f32 baseR;
    /* 0x04 */ f32 baseG;
    /* 0x08 */ f32 baseB;
    /* 0x0C */ f32 ampR;
    /* 0x10 */ f32 ampG;
    /* 0x14 */ f32 ampB;
    /* 0x18 */ f32 phaseR;
    /* 0x1C */ f32 phaseG;
    /* 0x20 */ f32 phaseB;
    /* 0x24 */ f32 rateR;
    /* 0x28 */ f32 rateG;
    /* 0x2C */ f32 rateB;
} ColourPulse;

typedef struct {
    u8 pad0[0x28];
    /* 0x28 */ ColourPulse pulse;
} ColourPulseObj;

void func_150D2450(ColourPulseObj *arg0) {
    ColourPulse *pulse;
    f32 pad;
    f32 sinPhase[2];

    pulse = &arg0->pulse;
    sinPhase[0] = sinf(pulse->phaseR);
    sinPhase[1] = sinf(pulse->phaseG);

    func_1515D4D4(
        (u8)(pulse->baseR + (sinPhase[0] * pulse->ampR)),
        (u8)(pulse->baseG + (sinPhase[1] * pulse->ampG)),
        (u8)((sinf(pulse->phaseB) * pulse->ampB) + pulse->baseB),
        0);

    pulse->phaseR = func_15144B68(pulse->phaseR + (pulse->rateR * D_800BE9A4));
    pulse->phaseG = func_15144B68(pulse->phaseG + (pulse->rateG * D_800BE9A4));
    pulse->phaseB = func_15144B68(pulse->phaseB + (pulse->rateB * D_800BE9A4));
}
