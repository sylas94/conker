#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_15040D90(s32 arg0) {

}

void func_15040D9C(s32 arg0) {
    u16 *ptr;
    s32 i;
    s32 j;

    i = D_800BE9C0;
    ptr = (u16 *)D_8002AAE8[i == 0];
    for (j = 0; j != 8; j++) {
        for (i = 0; i != 8; i += 4) {
            *(ptr + (arg0 + i) + D_800BE620 * (j + 225) + 200) = 0xF800;
            ptr = (u16 *)D_8002AAE8[D_800BE9C0];
            *(ptr + (arg0 + i) + D_800BE620 * (j + 225) + 200) = 0xF800;
            ptr = (u16 *)D_800BE9C4;
            *(ptr + (arg0 + i) + D_800BE620 * (j + 225) + 200) = 0;

            *(ptr + (arg0 + i) + D_800BE620 * (j + 225) + 201) = 0xF800;
            ptr = (u16 *)D_8002AAE8[D_800BE9C0];
            *(ptr + (arg0 + i) + D_800BE620 * (j + 225) + 201) = 0xF800;
            ptr = (u16 *)D_800BE9C4;
            *(ptr + (arg0 + i) + D_800BE620 * (j + 225) + 201) = 0;

            *(ptr + (arg0 + i) + D_800BE620 * (j + 225) + 202) = 0xF800;
            ptr = (u16 *)D_8002AAE8[D_800BE9C0];
            *(ptr + (arg0 + i) + D_800BE620 * (j + 225) + 202) = 0xF800;
            ptr = (u16 *)D_800BE9C4;
            *(ptr + (arg0 + i) + D_800BE620 * (j + 225) + 202) = 0;

            *(ptr + (arg0 + i) + D_800BE620 * (j + 225) + 203) = 0xF800;
            ptr = (u16 *)D_8002AAE8[D_800BE9C0];
            *(ptr + (arg0 + i) + D_800BE620 * (j + 225) + 203) = 0xF800;
            ptr = (u16 *)D_800BE9C4;
            *(ptr + (arg0 + i) + D_800BE620 * (j + 225) + 203) = 0;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_6E240/func_15040FCC.s")

void func_1504129C(void) {
    s32 i = 0;
    do {} while (++i < 0x18000000);
}
