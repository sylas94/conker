#include <ultra64.h>
#include "functions.h"
#include "variables.h"


typedef struct {
    char pad_0[0x28];
    u8 field_0x28;
    u8 field_0x29;
    u8 field_0x2A;
    char pad_0x2B[0x2D];
    s32 field_0x58;
} GameObjectColorFlags;

void func_150D7420(GameObjectColorFlags *arg0, u8 *arg1, u8 arg2) {
    if (arg2 == 0x36) {
        switch (*arg1) {
            case 0:
                break;
            case 1:
                arg0->field_0x58 |= 2;
                arg0->field_0x28 = 0xFF;
                arg0->field_0x29 = 0;
                arg0->field_0x2A = 0;
                return;
            case 2:
                arg0->field_0x58 |= 2;
                arg0->field_0x28 = 0xFF;
                arg0->field_0x29 = 0;
                arg0->field_0x2A = 0;
                return;
            case 3:
                arg0->field_0x28 = 0;
                arg0->field_0x58 |= 2;
                arg0->field_0x29 = 0xFF;
                arg0->field_0x2A = 0;
                return;
        }
        arg0->field_0x58 &= ~2;
    }
}

void func_150D74DC(GameObjectColorFlags *arg0, u8 *arg1, u8 arg2) {
    if (arg2 == 0x36) {
        switch (*arg1) {
            case 0:
                break;
            case 1:
                arg0->field_0x58 &= ~2;
                return;
            case 2:
                arg0->field_0x58 |= 2;
                arg0->field_0x28 = 0xFF;
                arg0->field_0x29 = 0;
                arg0->field_0x2A = 0;
                return;
            case 3:
                arg0->field_0x28 = 0;
                arg0->field_0x58 |= 2;
                arg0->field_0x29 = 0xFF;
                arg0->field_0x2A = 0;
                return;
        }
        arg0->field_0x58 &= ~2;
    }
}

void func_150D758C(GameObjectColorFlags *arg0, u8 *arg1, u8 arg2) {
    if (arg2 == 0x36) {
        switch (*arg1) {
            case 0:
                break;
            case 1:
                arg0->field_0x58 &= ~2;
                return;
            case 2:
                arg0->field_0x58 &= ~2;
                return;
            case 3:
                arg0->field_0x28 = 0;
                arg0->field_0x58 |= 2;
                arg0->field_0x29 = 0xFF;
                arg0->field_0x2A = 0;
                return;
        }
        arg0->field_0x58 &= ~2;
    }
}

extern u16 D_800D9910;

void func_150D7630(s32 arg0) {
    if (arg0 == 0) {
        D_800D9910 += D_800BE9E4 << 6;
    }
}

extern s32 D_80090230[5];
extern s32 D_80090244[5];

Gfx *func_150D765C(Gfx *gdl) {
    s32 i;
    s32 seg;
    s32 frame;
    s32 out;
    s32 set;
    s32 idx;
    s32 addr;
    s32 *tables[2] = { D_80090230, D_80090244 };

    set = 0;
    frame = D_800D9910 >> 8;
    for (i = 0; i < 6; i++) {
        if (i >= 4) {
            set = 1;
        }
        idx = (frame + i * 13) % 5;
        addr = func_1510D0EC(tables[set][idx], &out, 3, 0);
        seg = i + 2;
        gSPSegment(gdl++, seg, addr);
    }
    return gdl;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1048D0/func_150D7790.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1048D0/func_150D7928.s")
