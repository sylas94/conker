#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_15056B08(struct127 *arg0);
void func_150585F0(struct127 *arg0, f32 arg1);
void func_15052760(struct127 *arg0, s16 arg1);
s32  func_150535F4(struct127 *arg0);
void func_1502178C(struct127 *arg0, s32 arg1, s32 arg2);

/* D_800D20FC is a table of 0x30-byte spawn records. */
typedef struct {
    char pad_0[0x8];
    s16  field_0x8;
    char pad_A[0x26];
} SpawnRecord;

/* A window onto the 8-byte path points D_800D2104 points at. */
typedef struct {
    char pad_0[0xA];
    s16  field_0xA;
} PathPointWindow;

#pragma GLOBAL_ASM("asm/nonmatchings/game_DE5A0/func_150B10F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_DE5A0/func_150B12FC.s")

void func_150B1484(struct127 *arg0) {
    s16 prevAngle;

    prevAngle = arg0->unk76;
    arg0->unk80 = 0xA;
    if (arg0->stunned == 0) {
        f32 targetY;

        targetY = (f32)((SpawnRecord *)D_800D20FC)[arg0->unk13F].field_0x8 + 210.0f;
        if (!(arg0->unk22C & 8)) {
            if (arg0->unk223 != 3) {
                arg0->unkB8 = arg0->y_velocity * -0.5f;
            } else {
                arg0->unkB8 = 0.0f;
            }
        }
        if (arg0->unk223 == 0xE) {
            f32 time;

            time = func_1505A6F8(&D_800CC2D0[arg0->unk222], arg0) / arg0->xz_velocity;
            arg0->y_velocity = ((*(f32 *)((u8 *)D_800CC2E8 + (arg0->unk222 * sizeof(struct127))) + (f32)(s16)arg0->unk224) - arg0->y_position) / time;
            arg0->gravity = 0.0f;
        } else {
            s16 offsetY;

            if (arg0->unk223 == 1) {
                targetY = D_800CC2E8[0] + 210.0f;
            }
            offsetY = (s16)arg0->unk224;
            if (offsetY != 0) {
                if (offsetY == 10000) {
                    targetY = (f32)((PathPointWindow *)((u8 *)D_800D2104[arg0->unk13F] + (arg0->unk21E * 8)))->field_0xA;
                } else if ((arg0->id == 0x50) || (arg0->id == 5) || (arg0->id == 0xAD) || (arg0->id == 0xAE) || (arg0->id == 0xAF)) {
                    targetY = (f32)(offsetY * 8);
                } else {
                    targetY = (f32)(offsetY * 8) + arg0->unk180;
                }
            }
            if (!(arg0->unk100 & 0x40)) {
                f32 gravity;
                f32 maxSpeed;

                if (arg0->id == 0x44) {
                    targetY = (f32)((PathPointWindow *)((u8 *)D_800D2104[arg0->unk13F] + (arg0->unk21E * 8)))->field_0xA;
                    gravity = 3.0f;
                    maxSpeed = 12.0f;
                } else {
                    gravity = 5.0f;
                    maxSpeed = 35.0f;
                }
                func_15058EA4(arg0, targetY, gravity, targetY, -gravity, maxSpeed, -maxSpeed);
            }
        }
        func_15056B08(arg0);
    } else {
        func_150585F0(arg0, 0.05000000074505806f);
    }
    arg0->unk40 = (s16)(arg0->unk7A + 0x4000) * 0.0054931640625f;
    func_15059140(arg0);
    if ((arg0->id == 5) || (arg0->id == 0xAD) || (arg0->id == 0xAE) || (arg0->id == 0xAF) || (arg0->id == 0x44)) {
        func_15052760(arg0, prevAngle);
    }
    if (func_150535F4(arg0) == 0) {
        func_1502178C(arg0, 0, -1);
    }
}

extern f32 D_8009F8C4;
extern f32 D_8009F8C8;

struct127 *func_1505EEB0(s32 state, s32 *arg1);
void func_15056B08(struct127 *arg0);
void func_1505A770(struct127 *arg0);

void func_150B17DC(struct127 *arg0) {
    s32 sp3C;
    f32 angle;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    struct127 *other;

    other = func_1505EEB0(0xA, &sp3C);
    func_15056B08(arg0);
    if (arg0->unk1E5 == 2) {
        arg0->x_position = other->x_position;
        arg0->z_position = other->z_position;
        arg0->y_position = other->y_position + ((f32)(arg0->unk21C / 5) + 160.0f);
        arg0->y_velocity = 0.0f;
        arg0->gravity = D_8009F8C4;
        arg0->unk7E = 0;
    } else {
        angle = (f32)(u32)arg0->unk7E;
        angle *= D_8009F8C8;
        other->unkB8 = func_150AD78C(angle) * 6.0f;
        func_1505A770(arg0);
        other->y_position = arg0->y_position - 170.0f;
        other->unk13C = D_800C3E78 + 100;
        func_1505A184(other->unk7A, other->unkB8 * -7.0f, 0.0f, &sp34, &sp30, &sp2C);
        other->x_position = arg0->x_position + sp34;
        other->z_position = arg0->z_position + sp30;
        other->unk7A = other->unk7A + (D_800BE9A0 << 8);
        arg0->unk7E = arg0->unk7E + D_800BE9A0;
        other->in_water = 0;
        other->xz_velocity = 0.0f;
        other->unk16C = 0.0f;
        other->unk170 = 0.0f;
    }
    arg0->unk7A = func_1505A630(D_800CC2D0[0].x_position - arg0->x_position, arg0->z_position - D_800CC2D0[0].z_position, 0);
    arg0->unk40 = (s16)(arg0->unk7A + 0x4000) * 0.0054931640625f;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_DE5A0/func_150B19E0.s")
