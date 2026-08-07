#include <ultra64.h>
#include "functions.h"
#include "variables.h"

struct CB3D0_arg1 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
};

extern f32 D_800D2FC0[];
extern f32 D_800D2FD8[];
extern u8 D_800D2FEC[];
extern s32 D_800D3840;

void func_1509DF20(s32 arg0, struct CB3D0_arg1 *arg1) {
    if (arg1->unk4 == 1) {
        if (D_800D3840 == 3) {
            D_800D2FC0[arg1->unk8] = (f32)arg1->unkC * 0.0000152587890625f;
            D_800D2FD8[arg1->unk8] = (f32)arg1->unkC * 0.0000152587890625f;
            D_800D2FEC[arg1->unk8] = 1;
        }
    }
}

void func_1509DFB4(s32 arg0, s32 arg1) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_CB3D0/func_1509DFC4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_CB3D0/func_1509E3DC.s")
