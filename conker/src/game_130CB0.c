#include <ultra64.h>

#define func_1000F85C func_1000F85C_hdr
#include "functions.h"
#undef func_1000F85C
#include "variables.h"

extern struct127 *func_1505EEF4(s32);



void func_15103800(void) {
    bzero(D_800D9AB0, 8); // bzero
}

void func_15103828(void) {
    u16 temp_v1;
    s32 i;

    for (i = 0; i < 4; i++)
    {
        if (D_800D9AB0[i]) {
            if (D_800D9AB0[i] > D_800BE9E4)
            {
                D_800D9AB0[i] -= D_800BE9E4;
            } else {
              D_800D9AB0[i] = 0;
            }
        }
    }
}

// need to figure out the structs
typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    u16 unk8;
    s16 unkA;
    s32 unkC;
    s32 unk10;
    u8 pad14[4];
    s32 unk18;
    struct127 *unk1C;
    u8 pad20[4];
    u16 unk24;
} SoundEmitter130CB0;

s32 func_15103910(SoundEmitter130CB0 *arg0, s32 *arg1, s32 *arg2, s32 arg3, s32 arg4, s32 arg5, u16 *arg6) {
    s16 temp_a3;
    struct127 *obj;

    obj = arg0->unk1C;
    temp_a3 = arg0->unk18;
    arg0->unk2 = obj->x_position;
    arg0->unk4 = obj->y_position;
    arg0->unk6 = obj->z_position;
    if (temp_a3 != 0) {
        if (*arg6 != 0) {
            arg0->unk18 = (*arg6 << 16) | (arg0->unk18 & 0xFFFF);
            arg0->unk0 = 0;
            *arg6 = 0;
            func_10010344(0x5B0, obj, 0x61A8, 100, 0x78);
            return 0;
        }
        temp_a3 -= D_800BE9E4;
        if (temp_a3 <= 0) {
            *arg6 = arg0->unk18 >> 16;
            arg0->unk0 = *arg6;
            *arg2 = arg0->unkC;
            *arg1 = 1;
            arg0->unk18 = 0;
            return 0;
        }
    } else {
        *arg2 = arg0->unkC;
        *arg1 = 1;
        if (arg0->unk24 == 0) {
            func_10010344(0x5B1, obj, arg0->unkC, arg0->unkA, arg0->unk8);
            return 1;
        }
        if (obj->unk8C != arg0->unk24) {
            func_100111C8(obj->unk8C);
            obj->unk8C = arg0->unk24;
        }
        arg0->unk10 &= ~0x80;
    }
    arg0->unk18 = (arg0->unk18 & 0xFFFF0000) | temp_a3;
    return 0;
}

void func_1000F85C(u16 arg0, s16 arg1, s32 arg2);

s32 func_15103AA0(SoundEmitter130CB0 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u16 *arg6) {
    u32 timer;
    struct127 *obj;

    obj = arg0->unk1C;
    timer = arg0->unk18 & 0x7FFF;
    arg0->unk2 = obj->x_position;
    arg0->unk4 = obj->y_position;
    arg0->unk6 = obj->z_position;
    if (timer != 0) {
        if (*arg6 != 0) {
            arg0->unk18 = (*arg6 << 16) | (arg0->unk18 & 0xFFFF);
            arg0->unk0 = 0;
            *arg6 = 0;
            func_10010344(0x5B0, obj, -25000, arg0->unkA, arg0->unk8);
            return 0;
        }
        if (timer <= D_800BE9E4) {
            *arg6 = arg0->unk18 >> 16;
            arg0->unk0 = *arg6;
            arg0->unk18 &= ~0x7FFF;
            return 0;
        }
        timer -= D_800BE9E4;
    } else {
        if (arg0->unk24 == 0) {
            func_10010344(0x5B1, obj, -25000, arg0->unkA, arg0->unk8);
            return 1;
        }
        if (arg0->unk18 != 0) {
            if (!(arg0->unk18 & 0x8000)) {
                func_1000F85C(arg0->unk24, 0x8000, 2);
            }
            arg0->unk18 = 0;
        }
        arg0->unk10 &= ~0x80;
    }
    arg0->unk18 = (arg0->unk18 & ~0x7FFF) | timer;
    return 0;
}

void func_15103C14(s32 arg0, s32 arg1, u32 arg2, s32 arg3, s32 arg4) {
    struct127 *obj;
    s32 useCamera;

    useCamera = 0;
    if (D_800D9AB0[arg3] != 0) {
        if (arg0 != 0x58D) {
            return;
        }
    }

    obj = func_1505EEF4(arg1);
    if (obj == 0) {
        return;
    }
    if (func_10010894(obj) != 0) {
        return;
    }

    if (arg2 != 0) {
        if (arg4 != 0) {
            arg0 += (func_150ADA20() % arg2) * 2;
        } else {
            arg0 += func_150ADA20() % arg2;
        }
    }

    if (obj->camera != 0) {
        useCamera = 1;
    } else if (arg4 != 0) {
        arg0 += 1;
    }

    if (useCamera != 0) {
        func_1000FA64(arg0, (s16)(s32)obj->x_position, (s16)(s32)obj->y_position, (s16)(s32)obj->z_position,
                      0x7530, 0x7FFF, 0x7FFE, (s32)func_15103910, (void *)0x14, (s32)obj, 0x100, 0);
    } else {
        func_1000FA64(arg0, (s16)(s32)obj->x_position, (s16)(s32)obj->y_position, (s16)(s32)obj->z_position,
                      0x7FBC, 0x7FFF, 0x7FFE, (s32)func_15103AA0, (void *)((arg4 << 15) | 0x14), (s32)obj, 0x100, 0);
    }

    D_800D9AB0[arg3] = 0x258;
}
