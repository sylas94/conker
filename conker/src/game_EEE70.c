#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_15142314(s32, s32, s32);

typedef struct {
    char pad_0[0x1D4];
    s32 field_0x1D4;
} ActorFields;

s32 func_150C19C0(s32 arg0, ActorFields *arg1, u8 arg2) {
    s32 sp1C;

    switch (arg2) {
    case 1:
        sp1C = 0x18;
        break;
    case 2:
        sp1C = 0x15;
        break;
    }

    func_15142314(arg1->field_0x1D4, sp1C, arg0);
    return 1;
}

s32 func_150C1A2C(s32 arg0, s32 arg1) {
    return 0x7;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_EEE70/func_150C1A40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_EEE70/func_150C1E34.s")
