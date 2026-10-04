#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_151F2D6C(s32, s32);
void func_151F2BA8(void);

s32 func_1509E640(s32 arg0, s32 arg1, s32 *arg2) {
    switch (arg1) {
    case 0: {
        extern s32 D_800D3840;
        s32 vol = 0x7FFF;

        if (D_800D3840 >= 3) {
            vol = arg2[2];
        }
        func_1001263C(arg0, vol, 0x40);
        return 1;
    }
    case 1: {
        extern s32 D_800D3840;

        if (D_800D3840 == 4) {
            func_151F2D6C(arg2[2], arg2[3]);
        } else {
            func_151F2D6C(arg2[2], 0);
        }
        return 1;
    }
    case 2:
        func_151F2BA8();
        return 1;
    }
    return 0;
}

s32 func_151F2CDC(void);

s32 func_1509E6F0(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 == 3) {
        return func_151F2CDC() == 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_CBAF0/func_1509E730.s")

s32 func_1000E8F0(void);

s32 func_1509E8A0(s32 arg0, s32 arg1, s32 arg2) {
    switch (arg1) {
    case 7:
        return func_1000E0F8(arg0);
    case 8:
        return func_1000E8F0();
    }
    return 0;
}
