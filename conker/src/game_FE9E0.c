#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_800A08D0;
extern f32 D_800A08D4;

s32 func_1509BE40();
s32 func_15123934(struct108 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_151239CC(struct108 *arg0, s32 arg1);

void func_150D1530(struct108 *arg0) {
    if (arg0->unk2C == 0x40) {
        return;
    }

    if (arg0->unk5F0 & 0x80) {
        f32 speed;
        s32 ok;

        speed = (arg0->unk3D0->xz_velocity < 0.0f)
                    ? 0.0f
                    : ((170.0f < arg0->unk3D0->xz_velocity) ? 170.0f : arg0->unk3D0->xz_velocity);
        speed = speed * D_800A08D0;
        if (func_15123934(arg0, 8, 0, arg0->unk134, 3) != 0) {
            arg0->unk84 |= 0x1300080;
            arg0->unk84 &= ~6;
            arg0->unk1B4 = 1;
            arg0->unk1E0 = 2;
        }
        arg0->unk374 = -194.0f * speed + 280.0f;
        arg0->unk34C = arg0->unk348 = 34.0f * speed + 75.0f;
        if (D_800BE9F0 == 0x32) {
            ok = func_1509BE40(4, arg0->unk23D | 0x2000, 0xAC, 0x4027, 0x4035, 0x4036, 0x4037);
        } else {
            ok = func_1509BE40(5, arg0->unk23D | 0x2000, 0xAC, 0x400A, 0x400B, 0x400C, 0x400D, 0x400E);
        }
        if (ok != 0) {
            arg0->unk84 |= 0x10000000;
        } else {
            if (arg0->unk3D0->unk81 != 0) {
                arg0->unk190 = -30.0f;
            } else {
                arg0->unk190 = 123.0f;
            }
            arg0->unk84 &= 0xEFFFFFFF;
        }
        arg0->unk1A4 = arg0->unk1A8 = D_800A08D4 * speed + 10.0f;
        if (arg0->unk23C != 0) {
            /* Present in the ROM as a real load/store pair for each field: the original
             * source assigned each of these to itself.  Not a matching device -- removing
             * either statement removes four instructions from the golden stream. */
            arg0->unk1A4 = arg0->unk1A4;
            arg0->unk1A8 = arg0->unk1A8;
        }
    } else if (func_151239CC(arg0, 3) != 0) {
        arg0->unk190 = arg0->unk1A4 = arg0->unk1A8 = 0.0f;
    }

    if (D_800BE9F0 == 0x32) {
        if (func_1509BE40(1, 0x4039, 6, 0x9000) != 0) {
            arg0->unk84 |= 0x1000;
        } else {
            arg0->unk84 &= ~0x1000;
        }
    }
}
