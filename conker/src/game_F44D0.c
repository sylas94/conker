#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_800A0490;

typedef struct {
    /* 0x00 */ u8  unk0;
    /* 0x01 */ u8  pad1[0x3];
    /* 0x04 */ void *unk4;
    /* 0x08 */ u8  unk8;
    /* 0x09 */ u8  pad9[0x3];
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u8  unk24;
    /* 0x25 */ u8  pad25[0x1];
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s8  unk2E;
    /* 0x2F */ u8  unk2F;
    /* 0x30 */ s8  unk30;
    /* 0x31 */ u8  pad31[0x3];
    /* 0x34 */ f32 unk34;
    /* 0x38 */ u8  unk38;
    /* 0x39 */ s8  unk39;
} struct_E9FE0_2F8;

void *func_15134DAC(struct_E9FE0_2F8 *, s32);
void func_1516962C(s32, void *, s32);

void func_150C7020(void *arg0, s16 arg1, s32 arg2, s32 arg3) {
    struct_E9FE0_2F8 sp1C;

    if (arg0 == NULL) {
        return;
    }

    func_1516962C(0x29, arg0, 0x12);

    sp1C.unk0 = *((u8 *)arg0 + 0x3B);
    sp1C.unk4 = arg0;
    sp1C.unk8 = 0xD;
    sp1C.unkC = 2.0f;
    sp1C.unk10 = 0.0f;
    sp1C.unk14 = 34.0f;
    sp1C.unk18 = -15.0f;
    sp1C.unk1C = 0.0f;
    sp1C.unk20 = 34.0f;
    sp1C.unk24 = 0;
    sp1C.unk2E = -1;
    sp1C.unk2F = 1;
    sp1C.unk30 = -1;
    sp1C.unk34 = D_800A0490;
    sp1C.unk38 = 2;
    sp1C.unk39 = -1;

    if (arg1 != 0) {
        sp1C.unk2A = arg1;
        sp1C.unk24 = 2;
    } else {
        sp1C.unk2A = 0x12C;
    }

    sp1C.unk26 = (func_150ADA20() % 0x42U) + 0x23;
    sp1C.unk28 = (func_150ADA20() % 0x1AU) + 0x19;
    func_15134DAC(&sp1C, 0);

    sp1C.unk8 = 0xC;
    sp1C.unkC = -2.0f;
    sp1C.unk10 = 0.0f;
    sp1C.unk14 = 34.0f;
    sp1C.unk18 = 15.0f;
    sp1C.unk1C = 0.0f;
    sp1C.unk20 = 34.0f;

    sp1C.unk26 = (func_150ADA20() % 0x42U) + 0x23;
    sp1C.unk28 = (func_150ADA20() % 0x1AU) + 0x19;
    func_15134DAC(&sp1C, 0);
}


/* Near-miss at 299/9900; see tools/nearmiss/func_150C71C0.c */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F44D0/func_150C71C0.s")
