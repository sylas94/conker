#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_1509DD10(s32 arg0) {
    return 1;
}

s32 func_1509DD20(s32 arg0) {
    return 1;
}

s32 func_1509DD30(s32 arg0) {
    return 1;
}

s32 func_1509DD40(s32 arg0) {
    return 1;
}

s32 func_1509DD50(s32 arg0, struct214 *arg1) {
    func_15177F90(arg1->unk7, 0, arg1->unkB, arg1->unkC, arg1->unk10, arg1->unk14, arg1->unk18, 0x7FFF, 0xFF, arg1->unk1C, 0);
    return 1;
}

s32 func_1509DDC4(s32 arg0, u8 arg1) {
    func_15178E14(arg0 & 0xff, arg0);
    return 0;
}

s32 func_15084000(s32);
void func_15178C34(u8, s32, s32, s32, s32);
void func_15178BE4(u8, f32*, s32);
s32 func_15178C9C(u8 arg0, s32 arg1);

// NON-MATCHING, best score 225. The logic below is believed correct and is byte-identical
// except for ONE delay slot: IDO speculatively hoists the `lw` reload of arg0 from the
// case 1 block into the `beq` delay slot, where golden instead fills that slot with the
// default path's `move v0,zero` and leaves the following `b` with a `nop`. Golden is
// therefore 4 bytes LONGER than ours; every instruction, register and operand otherwise
// agrees. This is a delay-slot-filler PREFERENCE (fall-through block vs branch target),
// not something a spelling reaches.
//
// Spellings tried (all honest; the two that are semantically identical give the same
// number, and the two that genuinely change the IR are much worse -- bail signature):
//    225  switch, `return 1` per case, `return 0` after the switch   <- BEST, shown below
//    225  switch with an explicit `default: return 0;`               (identical output)
//    990  dropping the redundant `& 0xFF` (both callees already take u8)
//    705  `break` in each case with a common `return 1` after the switch
//
// s32 func_1509DDFC(s32 arg0, s32 arg1, struct215 *arg2) {
//     switch (arg1) {
//     case 0:
//         func_15178BE4(arg0 & 0xFF, &D_800CC2D0[func_15084000(arg2->unk8 & ~0x2000)].x_position, arg2->unkC.s.unk2);
//         return 1;
//     case 1:
//         func_15178C34(arg0 & 0xFF, arg2->unk8, arg2->unkC.i.unk0, arg2->unk10, arg2->unk14);
//         return 1;
//     }
//     return 0;
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_CB1C0/func_1509DDFC.s")

s32 func_1509DEC4(s32 arg0, s32 arg1, struct215 *arg2) {
    if (arg1 == 0) {
        s32 mask = ~0x2000;
        return func_15178C9C(arg0 & 0xff, func_15084000(arg2->unk8 & mask));
    }
    return 0;
}
