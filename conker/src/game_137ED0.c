#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_15179008(s32);
extern f32 D_800A26B0;
extern f32 D_800A26B4;
extern f32 D_800A26B8;
extern void func_15114D24(s32, s32, s32, s16, s32, s32);

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
} struct_func_1510AEE0;

typedef struct {
    f32 field_0x00;
    u8 pad_0x04[0x5C];
    f32 field_0x60;
    u8 pad_0x64[0x18];
    s32 field_0x7C;
    f32 field_0x80;
} OscillatorState;

typedef struct {
    u8  pad00[0x8];
    f32 unk8;
    u8  pad0C[0x30];
    s32 unk3C;
    u8  pad40[0x28];
    f32 unk68;
    u8  pad6C[0x10];
    s32 unk7C;
    s32 unk80;
    s32 unk84;
    u8  pad88[0x20];
    f32 unkA8;
    u8  padAC[0x5C];
    f32 unk108;
} ClockActor;

extern u32 D_800BE3E4;

void func_1510AA20(s32 arg0) {
    func_15179008(0);
}

void func_1510AA44(ClockActor *arg0) {
    s32 oldMin;
    s32 min;
    s32 sec;
    f32 angle;

    oldMin = arg0->unk3C / 3600 % 60;
    if (arg0->unk84 == 0) {
        if (D_800BE3E4 != 0) {
            arg0->unk84 = 1;
            arg0->unk3C = D_800BE3E4 * 180 % 43200;
            arg0->unk3C = arg0->unk3C * 60;
            oldMin = arg0->unk3C / 3600 % 60;
        }
    }
    if (oldMin < 0) {
        oldMin += 60;
    }
    arg0->unk3C = arg0->unk3C + D_800BE9E4;
    if (arg0->unk3C >= 2592000) {
        arg0->unk3C = arg0->unk3C - 2592000;
    }
    sec = arg0->unk3C / 60;
    min = sec / 60;
    angle = (f32) (sec / 300) * 2.5f;
    if (angle > 360.0f) {
        arg0->unk3C = arg0->unk3C - 2592000;
    }
    min = min % 60;
    if (min < 0) {
        min += 60;
    }
    if (oldMin != min) {
        if (oldMin / 15 != min / 15) {
            if ((min / 15 & 3) == 0) {
                arg0->unk7C = (s32) (angle / 30.0f);
                if (arg0->unk7C == 0) {
                    arg0->unk7C = 12;
                }
            } else {
                arg0->unk7C = 1;
            }
            arg0->unk80 = -1;
        }
    }
    if (arg0->unk7C != 0) {
        if (arg0->unk80 != sec) {
            arg0->unk80 = sec;
            arg0->unk7C = arg0->unk7C - 1;
            func_15114D24((s32) arg0, 0x4CC, 0x7FFF, 0xC8, 0x3E8, 0xC);
        }
    }
    arg0->unk68 = 5.0f;
    arg0->unk108 = 5.0f;
    arg0->unk8 = -((f32) min * 6.0f);
    arg0->unkA8 = -angle;
}

void func_1510ADD8(OscillatorState *arg0) {
    f32 temp;

    arg0->field_0x80 += (D_800A26B0 * D_800BE9E4) / 60.0f;
    temp = cosf(arg0->field_0x80) * 10.0f;
    arg0->field_0x60 = arg0->field_0x00 - temp;
    arg0->field_0x00 = temp;
    if (arg0->field_0x7C == 0) {
        if (D_800A26B4 <= arg0->field_0x80) {
            arg0->field_0x7C = 1;
            func_15114D24((s32)arg0, 0x4CA, 0x2EE0, 0xC8, 0x3E8, 4);
        }
    } else {
        temp = D_800A26B8;
        if (temp <= arg0->field_0x80) {
            arg0->field_0x80 -= temp;
            arg0->field_0x7C = 0;
            func_15114D24((s32)arg0, 0x4CB, 0x2EE0, 0xC8, 0x3E8, 4);
        }
    }
}

s32 func_1510AEE0(struct_func_1510AEE0 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 *arg8, f32 *arg9) {
    f32 temp_f2;
    f32 temp_f16;
    f32 temp_f18;
    f32 sp0[1];

    temp_f2 = -(arg0->unk38 + ((arg0->unk8 * arg1) + (arg0->unk18 * arg2) + (arg0->unk28 * arg3)));
    if (temp_f2 < arg4) {
        return 1;
    }
    if (arg5 < temp_f2) {
        return 1;
    }

    temp_f16 = arg0->unk30 + ((arg0->unk0 * arg1) + (arg0->unk10 * arg2) + (arg0->unk20 * arg3));
    temp_f16 = fabsf(temp_f16) * arg6;
    if (temp_f2 < temp_f16) {
        return 1;
    }

    temp_f18 = arg0->unk34 + ((arg0->unk4 * arg1) + (arg0->unk14 * arg2) + (arg0->unk24 * arg3));
    sp0[0] = fabsf(temp_f18) * arg7;
    if (temp_f2 < sp0[0]) {
        return 1;
    }

    if (arg8 != 0) {
        *arg8 = 1.0f - (temp_f16 / temp_f2);
    }
    if (arg9 != 0) {
        *arg9 = 1.0f - (sp0[0] / temp_f2);
    }
    return 0;
}
