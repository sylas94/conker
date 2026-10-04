#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern void *func_15167A68(s32, s32, s32, s32, s32, s32);
extern void func_1517E05C(s32, s32, s32);
extern f32 D_800A6C94;

typedef struct {
    u8 pad_0x00[0x12];
    s16 field_0x12;
    u8 pad_0x14[0x2];
    s16 field_0x16;
    s16 field_0x18;
    s16 field_0x1A;
    u8 pad_0x1C[0x6];
    s16 field_0x22;
    u8 pad_0x24[0x2];
    s16 field_0x26;
    s16 field_0x28;
    s16 field_0x2A;
    u8 pad_0x2C[0x6];
    s16 field_0x32;
    u8 pad_0x34[0x2];
    s16 field_0x36;
    s16 field_0x38;
    s16 field_0x3A;
    u8 pad_0x3C[0x6];
    s16 field_0x42;
    u8 pad_0x44[0x2];
    s16 field_0x46;
    s16 field_0x48;
    s16 field_0x4A;
} EffectQuadFields;

typedef struct {
    u8 pad_0x00[0x90];
    u8 field_0x90;
    u8 field_0x91;
    u8 field_0x92;
    u8 field_0x93;
    u8 field_0x94;
    u8 field_0x95;
    s16 field_0x96;
    s16 field_0x98;
    s16 field_0x9A;
    s16 field_0x9C;
    s16 field_0x9E;
    u8 field_0xA0;
    u8 field_0xA1;
    u8 pad_0xA2[0x6];
} EffectType4Object;

void func_15165F80(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    s32 i;
    EffectType4Object *temp_v0;
    f32 angle;
    EffectQuadFields *ptr;

    temp_v0 = func_15167A68(4, arg8, 0xA8, 1, (u8)arg7, 1);
    if (temp_v0 != NULL) {
        if (arg0 == -1) {
            {
                s32 j;
                EffectQuadFields *quad_ptr;

                j = 0;
                quad_ptr = (EffectQuadFields *)temp_v0;
                do {
                    j += 0x40;
                    quad_ptr = (EffectQuadFields *)((u8 *)quad_ptr + 0x40);
                    ((EffectQuadFields *)((u8 *)quad_ptr - 0x40))->field_0x12 = arg2;
                    ((EffectQuadFields *)((u8 *)quad_ptr - 0x40))->field_0x22 = arg2;
                    ((EffectQuadFields *)((u8 *)quad_ptr - 0x40))->field_0x32 = arg2;
                    ((EffectQuadFields *)((u8 *)quad_ptr - 0x40))->field_0x42 = arg2;
                    ((EffectQuadFields *)((u8 *)quad_ptr - 0x40))->field_0x16 = 0;
                    ((EffectQuadFields *)((u8 *)quad_ptr - 0x40))->field_0x26 = 0;
                    ((EffectQuadFields *)((u8 *)quad_ptr - 0x40))->field_0x36 = 0;
                    ((EffectQuadFields *)((u8 *)quad_ptr - 0x40))->field_0x46 = 0;
                } while (j != 0x80);
            }
            temp_v0->field_0x95 = 0;
        } else {
            angle = (f32)arg0 * D_800A6C94;
            temp_v0->field_0x91 = (s32)(sinf(angle) * 127.0f);
            temp_v0->field_0x90 = (s32)(-cosf(angle) * 127.0f);
            temp_v0->field_0x95 = 1;
        }

        i = 0;
        ptr = (EffectQuadFields *)temp_v0;
        do {
            i++;
            ptr = (EffectQuadFields *)((u8 *)ptr + 0x40);
            ((EffectQuadFields *)((u8 *)ptr - 0x40))->field_0x18 = 0x2000;
            ((EffectQuadFields *)((u8 *)ptr - 0x40))->field_0x1A = 0x2000;
            ((EffectQuadFields *)((u8 *)ptr - 0x40))->field_0x28 = 0x2800;
            ((EffectQuadFields *)((u8 *)ptr - 0x40))->field_0x2A = 0x2000;
            ((EffectQuadFields *)((u8 *)ptr - 0x40))->field_0x38 = 0x2800;
            ((EffectQuadFields *)((u8 *)ptr - 0x40))->field_0x3A = 0x2800;
            ((EffectQuadFields *)((u8 *)ptr - 0x40))->field_0x48 = 0x2000;
            ((EffectQuadFields *)((u8 *)ptr - 0x40))->field_0x4A = 0x2800;
        } while (i != 2);

        temp_v0->field_0x9A = arg2;
        temp_v0->field_0x9E = 1;
        temp_v0->field_0x92 = arg5;
        temp_v0->field_0x93 = arg5;
        temp_v0->field_0x98 = arg1;
        temp_v0->field_0x9C = arg3;
        temp_v0->field_0x96 = arg4;
        temp_v0->field_0x94 = arg6;
        func_1517E05C(arg1, arg2, arg3);
    }
}

typedef struct {
    Vtx v[4];
} VtxQuad15166118;

void func_15166118(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
    s32 i;
    EffectType4Object *temp_v0;

    temp_v0 = func_15167A68(4, arg9, 0xA8, 1, (u8)arg8, 1);
    if (temp_v0 != NULL) {
        temp_v0->field_0x95 = 2;
        for (i = 0; i < 2; i++) {
            ((VtxQuad15166118 *)((u8 *)temp_v0 + 0x10))[i].v[0].v.tc[0] = 0x2000;
            ((VtxQuad15166118 *)((u8 *)temp_v0 + 0x10))[i].v[0].v.tc[1] = 0x2000;
            ((VtxQuad15166118 *)((u8 *)temp_v0 + 0x10))[i].v[1].v.tc[0] = 0x2800;
            ((VtxQuad15166118 *)((u8 *)temp_v0 + 0x10))[i].v[1].v.tc[1] = 0x2000;
            ((VtxQuad15166118 *)((u8 *)temp_v0 + 0x10))[i].v[2].v.tc[0] = 0x2800;
            ((VtxQuad15166118 *)((u8 *)temp_v0 + 0x10))[i].v[2].v.tc[1] = 0x2800;
            ((VtxQuad15166118 *)((u8 *)temp_v0 + 0x10))[i].v[3].v.tc[0] = 0x2000;
            ((VtxQuad15166118 *)((u8 *)temp_v0 + 0x10))[i].v[3].v.tc[1] = 0x2800;
        }

        temp_v0->field_0x9E = 1;
        temp_v0->field_0x92 = arg6;
        temp_v0->field_0x93 = arg6;
        temp_v0->field_0x98 = arg2;
        temp_v0->field_0x9A = arg3;
        temp_v0->field_0x9C = arg4;
        temp_v0->field_0x96 = arg5;
        temp_v0->field_0x94 = arg7;
        temp_v0->field_0xA0 = arg0;
        temp_v0->field_0xA1 = arg1;
        func_1517E05C(arg2, arg3, arg4);
    }
}

void func_15166204(EffectType4Object *arg0) {
    s32 temp_v0;

    temp_v0 = arg0->field_0x92;
    arg0->field_0x9E = arg0->field_0x9E + (arg0->field_0x96 * D_800BE9E4);
    temp_v0 -= D_800BE9E4;
    if (temp_v0 <= 0) {
        func_1516972C((struct102 *)arg0);
        return;
    }
    arg0->field_0x92 = temp_v0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_193430/func_15166268.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_193430/func_151668B8.s")
