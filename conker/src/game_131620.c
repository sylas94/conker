#include <ultra64.h>
#include "functions.h"
#include "variables.h"


typedef struct {
    u8  pad0[0x10];
    s32 unk10;
    s32 unk14;
    s16 unk18;
    u8  unk1A;
    u8  unk1B;
    u8  unk1C;
} struct_15104170;

s32 func_15167A68(s32, s32, s32, s32, s32, s32);

struct_15104170 *func_15104170(s32 arg0, s32 arg1, s32 arg2) {
    struct_15104170 *ret;

    ret = (struct_15104170 *)func_15167A68(0x64, 0, 0x20, 0, 0xFF, 1);
    if (ret != 0) {
        ret->unk18 = 0xF;
        ret->unk1A = 0;
        ret->unk1B = 0;
        ret->unk10 = arg1;
        ret->unk14 = arg2;
        ret->unk1C = arg0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_131620/func_151041E4.s")

s32 func_1517F08C(s32, s32, s32, s32, s32, s32);

s32 func_1510448C(s32 arg0, s32 arg1, s32 arg2) {
    s32 *p1 = &arg1;
    s32 *p2 = &arg2;
    s32 v0;
    if ((s16)*p2 != 0 || (v0 = *(u8 *)(*p1 + 0x1B)) == 0) {
        return arg0;
    }
    return func_1517F08C(arg0, ((v0 * 0x3F) >> 8), 0, 0, 0, *((s16 *)&arg2 + 1));
}

extern struct126 *D_800CC5EC;

u8 func_151044F4(void) {
    if (D_800CC5EC != 0) {
        return D_800CC5EC->matrix_physics;
    }
    return 0;
}
