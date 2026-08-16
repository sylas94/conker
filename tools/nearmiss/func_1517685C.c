#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} Struct15176B84;

typedef struct {
    u8  pad0[0x90];
    u8  unk90;
    u8  unk91;
    s16 unk92;
    s32 unk94;
    f32 unk98;
    f32 unk9C;
    f32 unkA0;
    u8  padA4[0x4];
    f32 unkA8;
    f32 unkAC;
    u8  padB0[0x4];
    f32 unkB4;
    f32 unkB8;
    u8  padBC[0xC];
    f32 unkC8;
    f32 unkCC;
    u8  padD0[0x2];
    s16 unkD2;
    u8  padD4[0x6];
    s16 unkDA;
    u8  padDC[0x8];
    f32 unkE4;
    u8  padE8[0x5];
    u8  unkED;
    u8  padEE[0x2];
    u8  unkF0;
    u8  unkF1;
} Obj15176B84;

s32 func_150AD960(s32, s32, s32, s32);
void func_15175958(Obj15176B84 *arg0);

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A20A0/func_15174BF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A20A0/func_15174FA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A20A0/func_15175390.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A20A0/func_15175958.s")

void func_1517685C(Obj15176B84 *obj) {
    s32 roll;

    if (D_800DDF5C[obj->unk90] != 0) {
        D_800DDF68[obj->unkED] = 1;
        switch (obj->unk91) {
            case 0:
                if (func_150AD960((s32)D_800CC2D0[0].x_position, (s32)D_800CC2D0[0].z_position, (s32)obj->unk98,
                                  (s32)obj->unkA0) < 400) {
                    obj->unk91 = 1;
                    obj->unkB4 = (f32)(-1 - (func_150ADA20() & 3));
                    obj->unkA8 = -8.0f;
                    return;
                } else if (obj->unkCC != 0.0f) {
                    obj->unkA8 += obj->unkCC;
                    if (obj->unkCC < 0.0f) {
                        obj->unkAC += obj->unkB8;
                    }
                    if (obj->unkA8 > 45.0f) {
                        obj->unkCC = -5.0f;
                    } else if (obj->unkCC < 0) {
                        if (obj->unkA8 > 25.0f) {
                            roll = func_150ADA20() & 0xFF;
                            if (roll < 51) {
                                obj->unkCC = 5.0f;
                            }
                        }
                    }
                    if (obj->unkA8 <= 10.0f) {
                        obj->unkCC = 0.0f;
                    }
                    return;
                } else {
                    roll = func_150ADA20() & 0xFF;
                    if (roll >= 25) {
                        return;
                    }
                    obj->unkCC = 5.0f;
                    if (roll < 13) {
                        obj->unkB8 = (f32)((s32)(func_150ADA20() % 6U) - 3);
                        return;
                    }
                    obj->unkB8 = 0.0f;
                }
                break;
            case 1:
                if (obj->unk9C >= (300.0f + obj->unkC8)) {
                    obj->unk91 = 2;
                    obj->unk92 &= ~1;
                    obj->unk92 |= 4;
                    obj->unkE4 = (f32)(func_150ADA20() & 0x7F) + (300.0f + obj->unkC8);
                }
                func_15175958(obj);
                break;
            case 2:
            case 3:
            default:
                if (obj->unk9C < obj->unkE4) {
                    obj->unkB4 = -1.5f;
                } else if (obj->unkA8 < 0) {
                    obj->unkB4 = 1.5f;
                }
                func_15175958(obj);
                break;
        }
    } else {
