#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_1A20A0/func_15174BF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A20A0/func_15174FA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A20A0/func_15175390.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A20A0/func_15175958.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A20A0/func_1517685C.s")

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
    u8  pad92[0x2];
    s32 unk94;
    f32 unk98;
    f32 unk9C;
    f32 unkA0;
    u8  padA4[0x24];
    f32 unkC8;
    u8  padCC[0x6];
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

void func_15176B84(Obj15176B84 *obj) {
    s32 fade;

    if ((((Struct15176B84 *)D_800DDE80)[obj->unkED].unk0 == 0) || (D_800DDF78[obj->unkED] == 0)) {
        func_1516972C((struct102 *)obj);
        return;
    }

    fade = obj->unkF0;
    if (obj->unkF1 == 0) {
        if (D_800DDF5C[obj->unk90] == 0) {
            obj->unkF1 = 1;
        } else if (fade != 0xFF) {
            fade += D_800BE9E4 * 4;
            if (fade >= 0x100) {
                fade = 0xFF;
            }
            obj->unkF0 = fade;
        }
    } else {
        if (fade == 0) {
            func_1516972C((struct102 *)obj);
            return;
        }
        fade -= D_800BE9E4 * 4;
        if (fade < 0) {
            fade = 0;
        }
        obj->unkF0 = fade;
    }

    D_800DDF68[obj->unkED] = 1;

    switch (obj->unk91) {
        case 0:
            if (func_150AD960((s32)D_800CC2D0[0].x_position, (s32)D_800CC2D0[0].z_position, (s32)obj->unk98,
                              (s32)obj->unkA0) < 0xC8) {
                obj->unk91 = 2;
                obj->unkE4 = (f32)((u32)func_150ADA20() % obj->unkDA) + obj->unkD2;
                obj->unk94 = ((Struct15176B84 *)D_800DDE80)[obj->unkED].unk8;
            } else {
                obj->unk94 = ((Struct15176B84 *)D_800DDE80)[obj->unkED].unk4;
            }
            return;
        case 2:
        case 3:
            break;
        case 4:
            if (obj->unk9C < obj->unkC8) {
                func_1516972C((struct102 *)obj);
                return;
            }
            break;
    }
    func_15175958(obj);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A20A0/func_15176DF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A20A0/func_151770C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A20A0/func_1517725C.s")
