#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* Near-miss at 160/6300; see tools/nearmiss/func_150C7670.c */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F4B20/func_150C7670.s")

extern u8 D_80089470[];

s32 func_150C773C(void *arg0, s32 arg1) {
    memcpy(arg0, D_80089470, 0x40);
    return 1;
}
