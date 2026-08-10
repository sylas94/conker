#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_800A3408;
extern f32 D_800A340C;
extern f32 D_800A3410;
extern f32 D_800A3414;
extern f32 D_800A3418;

#pragma GLOBAL_ASM("asm/nonmatchings/game_14D110/func_1511FC60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_14D110/func_15120158.s")

void func_15121490(struct127 *arg0, u16 *arg1) {
    struct126 *stats;
    s32 state;
    vertex endPoint;
    vertex origin;
    f32 angle;
    vertex dir;
    f32 temp;

    arg0->unk31C->unk198 = 0;
    if (*arg1 & 0x10) {
        stats = arg0->unk31C;
        state = stats->unk78;
        if ((state == 0x9) || (state == 0x38) || (state == 0x39) || (state == 0x37) ||
            (state == 0x3B) || (state == 0x15) || (state == 0x26) || (state == 0x3A)) {
            angle = (arg0->unk40 - 90.0f) * D_800A3408;
            endPoint.x = arg0->x_position;
            endPoint.y = arg0->y_position + ((f32)(s16)stats->unk114 * 0.75f);
            endPoint.z = arg0->z_position;
            origin = endPoint;
            endPoint.x = (sinf(angle) * 100.0f) + origin.x;
            endPoint.y = origin.y;
            endPoint.z = (cosf(angle) * 100.0f) + origin.z;
            origin.y += arg0->y_position - arg0->old_y_position;
            *(vertex *)((u8 *)stats + 0x13C) = origin;
            *(vertex *)((u8 *)stats + 0x148) = endPoint;
            stats->unk198 = 1;
            dir.x = 1.0f;
            temp = dir.x * cosf(*(f32 *)((u8 *)stats + 0x170) * D_800A340C);
            dir.y = dir.x * sinf(*(f32 *)((u8 *)stats + 0x170) * D_800A3410);
            dir.x = temp;
            temp = dir.x * cosf(*(f32 *)((u8 *)stats + 0x16C) * D_800A3414);
            dir.z = dir.x * sinf(*(f32 *)((u8 *)stats + 0x16C) * D_800A3418);
            dir.x = temp;
            *(vertex *)((u8 *)stats + 0x130) = dir;
        }
    }
}

void func_151216F8(struct108 *arg0) {
    s32 temp_v0;

    temp_v0 = arg0->unk23E;
    if (temp_v0) {
        if (temp_v0 == 0x34) {
            arg0->unk190 = 80.0f;
            *(f32 *)((u8 *)arg0 + 0x784) = 350.0f;
            return;
        }
        if ((temp_v0 == 0x3B) && ((D_800BE9F0 == 0x41) || (D_800BE9F0 == 0x3C))) {
            arg0->unk190 = -12.0f;
            *(f32 *)((u8 *)arg0 + 0x99C) = -28.0f;
            *(f32 *)((u8 *)arg0 + 0x784) = 106.0f;
            return;
        }
        if ((temp_v0 == 2) || (temp_v0 == 0xA) || (temp_v0 == 0x13)) {
            arg0->unk190 = 10.0f;
            arg0->unk84 |= 0x80;
            *(f32 *)((u8 *)arg0 + 0x784) = 135.0f;
            *(f32 *)((u8 *)arg0 + 0x99C) = 0.0f;
            return;
        }
        if ((temp_v0 == 0x12) && (D_800BE9F0 == 0x3C)) {
            arg0->unk190 = 10.0f;
            *(f32 *)((u8 *)arg0 + 0x784) = 180.0f;
            *(f32 *)((u8 *)arg0 + 0x99C) = 0.0f;
            return;
        }
        if (temp_v0 == 0xF) {
            arg0->unk190 = 10.0f;
            *(f32 *)((u8 *)arg0 + 0x784) = 480.0f;
            *(f32 *)((u8 *)arg0 + 0x99C) = 0.0f;
            return;
        }
        if (temp_v0 == 0x38) {
            *(f32 *)((u8 *)arg0 + 0x784) = 110.0f;
            arg0->unk190 = 5.0f;
            *(f32 *)((u8 *)arg0 + 0x99C) = 0.0f;
            return;
        }
        if (temp_v0 == 0x15) {
            *(f32 *)((u8 *)arg0 + 0x784) = 110.0f;
            arg0->unk190 = 25.0f;
            *(f32 *)((u8 *)arg0 + 0x99C) = 0.0f;
            return;
        }
        arg0->unk190 = 5.0f;
        *(f32 *)((u8 *)arg0 + 0x784) = 75.0f;
        *(f32 *)((u8 *)arg0 + 0x99C) = 0.0f;
        return;
    }
    *(f32 *)((u8 *)arg0 + 0x784) = 90.0f;
    arg0->unk190 = 25.0f;
    *(f32 *)((u8 *)arg0 + 0x99C) = 0.0f;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_14D110/func_151218C4.s")
