#include <ultra64.h>
#include "functions.h"
#include "variables.h"

s32 func_1509BE40();
void func_1509BFB0(s32 num, s32, s32, ...);
void func_151254F4(struct108 *arg0, s32 arg1);
void func_15123070(struct108 *arg0);

extern f32 D_800A00B0;
extern f32 D_800A00B4;

void func_150BE850(struct108 *arg0) {
    s32 temp2;
    s32 temp1;
    f32 temp3;

    temp1 = func_1509BE40(0, func_1509BE40(0, 0x2006, 0xB7) | 0x2000, 0xBC);
    temp2 = func_1509BE40(0, 0x2000, 0xBB);
    if ((temp1 != 0) && (temp2 != -1)) {
        func_1509BFB0(0, 0x400E, 1);
        if (arg0->unk2C != 8) {
            func_1512868C(arg0);
        }
        if (func_15123934(arg0, 8, 0, arg0->unk134, 3) != 0) {
            func_151254F4(arg0, D_800CC335 - 1);
            arg0->unk84 |= 0x1000200;
            arg0->unk73C = 0;
            arg0->unk84 &= ~4;
            arg0->unk674 = 0.0f;
        }
        temp3 = D_800A00B0;
        arg0->unk374 = D_800A00B4;
        arg0->unk348 = temp3;
        arg0->unk34C = temp3;
        arg0->unk190 = 0.0f;
        func_15123070(arg0);
    } else {
        if (func_151239CC(arg0, 3) != 0) {
            func_151254F4(arg0, 0);
            arg0->unk674 = 0.0f;
            func_1509BFB0(0, 0x400E, 0);
        }
    }
}
