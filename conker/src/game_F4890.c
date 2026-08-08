#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_800A04B0;

extern void func_151616D0(u8, u8, s32);

typedef struct {
    u8  pad_0x0[0x13];
    u8  field_0x13;
    u8  pad_0x14[0x24];
    s32 field_0x38;
    s32 field_0x3C;
} GameF4890Object;

s32 func_150C73E0(GameF4890Object *arg0, struct108 *arg1) {
    f32 alpha;
    f32 maxAlpha;
    f32 fade;

    maxAlpha = 1.0f;
    alpha = arg0->field_0x3C / 255.0f;

    if (arg0->field_0x38 == 0) {
        arg0->field_0x13 = 12;
        if (arg1->unk2E4 != 0) {
            func_151616D0(0x11, 0x41, 0);
            arg1->unk2E4 = 0;
        }
        return 0;
    }

    if (arg0->field_0x38 < 60) {
        alpha = (u32)(func_150ADA20() & 1) * ((arg0->field_0x38 / 60.0f) / 4.0f);
    } else if (arg0->field_0x38 < 300) {
        fade = (arg0->field_0x38 - 60) / 240.0f;
        alpha = (fade * 0.75f) + 0.25f;
    } else if (arg0->field_0x38 < 330.0f) {
        if ((maxAlpha - (1.0f / 4.0f)) < alpha) {
            alpha = 0.25f;
        } else {
            alpha = alpha + (1.0f / 4.0f);
        }
    } else {
        alpha += (maxAlpha - alpha) * D_800A04B0;
    }

    if (arg0->field_0x38 <= D_800BE9E4) {
        arg0->field_0x38 = 0;
    } else {
        arg0->field_0x38 -= D_800BE9E4;
    }

    arg0->field_0x3C = alpha * 255.0f;

    if (alpha != 0.0f) {
        if (arg0->field_0x13 != 2) {
            func_10010F30((func_150ADA20() & 7) + 0x44B, 0x7D00, 0x40, 0, 0);
        }
        arg0->field_0x13 = 2;
        if (arg1->unk2E4 != 1) {
            func_151616D0(0x11, 0x40, 0);
            arg1->unk2E4 = 1;
        }
    } else {
        arg0->field_0x13 = 12;
        if (arg1->unk2E4 != 0) {
            func_151616D0(0x11, 0x41, 0);
            arg1->unk2E4 = 0;
        }
    }

    return 0;
}
