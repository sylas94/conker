#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_3D2E0/func_1500FE30.s")

extern s32 D_800917B8;
extern void func_1510C4AC(s32, s32, s32, s32);

void func_1500FF9C(void) {
    func_1510C4AC(D_800917B8, 0, 0xAD, 0x75);
}

extern s32 D_800902DC;
extern u8 *D_80088870;
void func_1500FE30(void);

void func_1500FFCC(void) {
    f32 sp44;
    struct260 *fx;

    func_15195AA8(D_800B0E00[0], D_800902DC, 1, -1, 0, 0, 0, -4);
    func_15195AA8(D_800B0E04, D_800902DC, 1, -1, 0, 1, 0, -4);
    func_1500FE30();
    func_1500FF9C();
    sp44 = 0.0f;
    fx = func_151491F4(0x12C, -1, 0x12, 0, 0xE, 4, 0xFF, 0);
    if (fx != NULL) {
        memcpy((u8 *)fx + 0x28, &sp44, 4);
    }
    {
        struct {
            f32 unk0;
            f32 unk4;
        } sp38;
        struct260 *fx2;

        sp38.unk0 = 0.0f;
        sp38.unk4 = 0.0f;
        fx2 = func_15149130(0x12C, -1, 0x17, -1, 0, 0x14, (struct37 *)8, 0xFF, 1);
        if ((D_80088870 = (u8 *)fx2) != NULL) {
            memcpy((u8 *)fx2 + 0x28, &sp38, 8);
        }
    }
}
