/* PARK 2026-10-08 (wave 10C): mism 6. At the three != -1 compares golden has b->v0, -1->v1; ours swapped. Block 244FA0 (287.0f, 750.0f) is owned only by this function, so literals are OK. Refuted: -1 != b, 0xFFFFFFFF, b+1 != 0, u32 b, extra none/d locals. Next: permuter on the first if/else-if chain. */
#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_1509BE40();
void func_151254F4(struct108 *arg0, s32 arg1);
s32 func_15123934(struct108 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 D_80088800;

void func_150C7E00(struct108 *arg0) {
    s32 a;
    s32 b;
    s32 c;
    f32 t;
    f32 f;
    struct127 *obj;

    a = func_1509BE40(0, func_1509BE40(0, 0x2010, 0xB7) | 0x2000, 0xBC);
    b = func_1509BE40(0, 0x2000, 0xBB);
    c = func_1509BE40(0, func_1509BE40(0, 0x2010, 0xB7) | 0x2000, 0xBB);
    if (func_1509BE40(0, 0x5071, 0x1A) == 0) {
        if (b != -1 && a == 0) {
            if (func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 3) != 0) {
                arg0->unk84 |= 0x1000000;
                func_151254F4(arg0, D_800CC335 - 1);
                arg0->unk674 = 0.0f;
            }
        } else if (b != -1 && a != 0) {
            func_151239CC(arg0, 2);
            if (func_15123934(arg0, 8, 0, arg0->unk134, 3) != 0) {
                func_151254F4(arg0, D_800CC335 - 1);
                arg0->unk84 &= ~4;
                arg0->unk674 = 0.0f;
                func_15123070(arg0);
            }
            arg0->unk5F0 |= 0x200;
            arg0->unk348 = 500.0f;
            arg0->unk34C = 500.0f;
            arg0->unk374 = 800.0f;
        } else {
            if (func_151239CC(arg0, 3) != 0) {
                func_151254F4(arg0, 0);
                arg0->unk84 &= ~0x1000000;
                arg0->unk3D4->unk198 = 0;
                arg0->unk73C = 0;
                if (arg0->unk6C8 == 0) {
                    arg0->unk674 = 0.0f;
                }
            }
            arg0->unk5F0 &= ~0x200;
        }
        return;
    }
    if (func_1509BE40(0, 0x5072, 0x1A) == 0) {
        if (*arg0->unk36C & 4) {
            arg0->unk190 = 20.0f;
        }
        if (func_1509BE40(0, 0x2000, 0x93) == 0) {
            arg0->unk190 = 0.0f;
            return;
        }
        func_1509BFB0(1, 0x9000, 0x17, func_1509BE40(1, func_1509BE40(0, 0x2011, 0xB7) | 0x2000, 0x9C, 0x2000));
        f = (func_1509BE40(1, func_1509BE40(0, 0x2011, 0xB7) | 0x2000, 0x9A, 0x2000) - 300.0f) / 900.0f;
        t = (f < 0.0f) ? 0.0f : ((f > 1.0f) ? 1.0f : f);
        if (a == 0) {
            arg0->unk34C = 200.0f;
            arg0->unk348 = 200.0f;
            arg0->unk190 = 100.0f;
        } else {
            arg0->unk190 = 103.0f * t + 287.0f;
            arg0->unk374 = 224.0f * t + 750.0f;
            arg0->unk348 = arg0->unk34C = 231.0f * t;
        }
        func_1509BFB0(2, 0x9000, 6, 1, 0x20000);
        func_1509BFB0(2, 0x9000, 6, 0, 4);
        if (c != -1) {
            arg0->unk670 = 0.0f;
        }
        D_80088800 = 0;
        if ((arg0->unk5F0 & 4) && (obj = func_15083E90(0x10)) != NULL && arg0->unk3D0->unk65 != 0) {
            arg0->unk3D0->x_position = obj->x_position;
            arg0->unk3D0->y_position = obj->y_position;
            arg0->unk3D0->z_position = obj->z_position;
        }
        if (func_151239CC(arg0, 3) != 0) {
            arg0->unk5F0 &= ~0x200;
            func_151254F4(arg0, 0);
            arg0->unk84 &= ~0x1000000;
            arg0->unk3D4->unk198 = 0;
            arg0->unk73C = 0;
            if (arg0->unk6C8 == 0) {
                extern s32 D_80088800;

                arg0->unk674 = 0.0f;
            }
        }
    } else if (func_151239CC(arg0, 3) != 0 || D_80088800 == 0) {
        arg0->unk84 |= 4;
        D_80088800 = 1;
        func_151254F4(arg0, 0);
        arg0->unk3D4->unk198 = 0;
        arg0->unk73C = 0;
        arg0->unk1B4 = 3;
        func_15124B18(arg0);
        arg0->unk190 = 0.0f;
        if (arg0->unk6C8 == 0) {
            arg0->unk674 = 0.0f;
        }
    }
    if (*arg0->unk36C & 4) {
        arg0->unk190 = 0.0f;
    }
}
