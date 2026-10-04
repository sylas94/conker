#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_188440/func_1515AF90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_188440/func_1515B21C.s")

extern void func_1515572C(s16 *, s32);

void func_1515B5F4(s16 arg0) {
    s16 sp1C[2];

    sp1C[0] = arg0;
    func_1515572C(sp1C, 0xB);
}

void func_1515B62C(struct102 *arg0, s16 *arg1, u8 arg2) {
    if (arg2 == 0xB) {
        if (*(s16 *)((u8 *)arg0 + 0x70) == arg1[0]) {
            func_1516972C(arg0);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_188440/func_1515B674.s")

typedef struct Obj1515B994 {
    char pad0[0x14];
    /* 0x14 */ f32 unk14;
    char pad18[4];
    /* 0x1C */ f32 unk1C;
    char pad20[0x74 - 0x20];
    /* 0x74 */ f32 unk74;
    /* 0x78 */ f32 unk78;
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
} Obj1515B994;

s32 func_1515B994(Obj1515B994 *arg0) {
    f32 old;

    old = arg0->unk78;
    arg0->unk14 += (old * D_800BE9A4) + ((0.5f * arg0->unk74) * D_800BE9A4);
    arg0->unk78 += arg0->unk74 * D_800BE9A4;
    arg0->unk1C = arg0->unk7C + ((arg0->unk80 * (arg0->unk78 + old)) * 0.5f);
    return 1;
}

void func_1515BA10(s32 arg0) {
}

extern void func_1515AF90(s16);

void func_1515BA1C(s16 arg0) {
    func_1515AF90(arg0);
}

void func_1515BA48(s32 arg0) {
}

extern void func_1515B674(s16);

void func_1515BA54(s16 arg0) {
    func_1515B674(arg0);
}

extern void func_1515B5F4(s16);

void func_1515BA80(s16 arg0) {
    func_1515B5F4(arg0);
}

void func_1515BAAC(s16 arg0) {
    func_1515B5F4(arg0);
}
