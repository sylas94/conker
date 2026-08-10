#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_203340/func_151D5E90.s")

void func_151D61B0(u16 *fb) {
    s32 width;
    s32 height;
    s32 x;
    s32 y;
    u16 *row;
    u16 *p;
    u16 a;
    u16 b;
    u16 c;
    s32 red;
    s32 grn;
    s32 blu;
    s32 d;

    width = D_800BE620;
    height = D_800BE624;
    row = fb;
    for (y = 0; y < height; y++) {
        p = row + 1;
        b = row[1];
        c = row[2];
        for (x = 1; x < width - 1; x++) {
            a = b;
            b = c;
            c = p[2];
            red = ((b >> 11) & 0x1F) + ((a >> 12) & 0xF) + ((c >> 12) & 0xF);
            grn = ((b >> 6) & 0x1F) + ((a >> 7) & 0xF) + ((c >> 7) & 0xF);
            blu = ((b >> 1) & 0x1F) + ((a >> 2) & 0xF) + ((c >> 2) & 0xF);
            d = ((red & 0x3E) << 10) | ((grn & 0x3E) << 5) | (blu & 0x3E) | 1;
            p[1] = d;
            p++;
        }
        row += width;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_203340/func_151D6418.s")

void func_151D66F0(s32 arg0, s32 arg1) {
    if (D_800BE9F0 == 6 && D_80038080 == 0) {
        return;
    }
    if (arg1 == 0) {
        arg0 = 0;
    }
    D_800BE574 = arg0;
    if (arg0 != 0) {
        D_800BE575 = arg1;
    } else {
        D_800BE575 = 0;
    }
    if (arg0 == 0) {
        if (D_800BE570 != 0) {
            func_100043B4((s32 *)D_800BE570, 3);
            D_800BE570 = 0;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_203340/func_151D6778.s")
