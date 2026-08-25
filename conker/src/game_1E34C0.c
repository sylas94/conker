#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern f32 D_800AA450;
extern void *func_15132A4C(void *, s32, s32, s32, u8, s32);

/* The particle descriptor func_15132A4C consumes; same layout as
 * struct S151D4408 in game_200930.c and sp28 in game_F5800.c
 * (here unk10/unk40 are struct17 vectors rather than loose floats). */
typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ struct17 unk10;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ struct17 unk28;
    /* 0x34 */ struct17 unk34;
    /* 0x40 */ struct17 unk40;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s16 unk54;
    /* 0x56 */ s16 unk56;
    /* 0x58 */ u8  unk58;
    /* 0x59 */ u8  pad59[3];
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ u8  unk60;
    /* 0x61 */ u8  unk61;
    /* 0x62 */ u8  unk62;
    /* 0x63 */ u8  unk63;
    /* 0x64 */ u8  unk64;
    /* 0x65 */ u8  unk65;
    /* 0x66 */ u8  unk66;
    /* 0x67 */ u8  unk67;
    /* 0x68 */ u8  unk68;
    /* 0x69 */ u8  pad69;
    /* 0x6A */ u8  unk6A;
    /* 0x6B */ u8  pad6B;
    /* 0x6C */ s32 unk6C;
    /* 0x70 */ u8  unk70;
    /* 0x71 */ u8  pad71;
    /* 0x72 */ s16 unk72;
    /* 0x74 */ s16 unk74;
    /* 0x78 */ s32 pad78;   /* same 0x7C total as struct S151D4408 in game_200930.c */
} S151B6010;

/* Copied to +0x170 of the particle the call returns. */
typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
} S151B6010Payload;

s32 func_151B6010(struct17 *arg0, struct17 *arg1, f32 arg2, struct17 *arg3,
                  struct17 *arg4, f32 arg5, s16 arg6, u8 arg7, s32 arg8,
                  f32 arg9, u8 arg10, u8 arg11, u8 arg12, s32 arg13) {
    void *ret;
    S151B6010 sp30;
    S151B6010Payload sp28;

    sp28.unk4 = arg2;
    sp28.unk0 = 0.0f;
    sp30.unk0 = D_800AA450 * arg2;
    sp30.unk4 = arg9;
    sp30.unkC = arg2;
    sp30.unk8 = arg2;
    sp30.unk10 = *arg3;
    sp30.unk1C = 1.0f;
    sp30.unk20 = 1.0f;
    sp30.unk24 = 1.0f;
    sp30.unk28 = *arg0;
    sp30.unk4C = arg5;
    sp30.unk50 = 0x3900;
    if (arg6 == -1) {
        sp30.unk54 = 0x12C;
    } else {
        sp30.unk54 = arg6 + (0x100 >> arg10);
        sp30.unk50 = 0x3980;
    }
    if (arg1 != NULL) {
        sp30.unk34 = *arg1;
        sp30.unk50 |= 0x20;
    } else {
        sp30.unk34.unk0 = 0.0f;
        sp30.unk34.unk4 = 0.0f;
        sp30.unk34.unk8 = 0.0f;
    }
    if (arg4 != NULL) {
        sp30.unk40 = *arg4;
        sp30.unk50 |= 0x40;
    } else {
        sp30.unk40.unk0 = 0.0f;
        sp30.unk40.unk4 = 0.0f;
        sp30.unk40.unk8 = 0.0f;
    }
    if (arg11 != 0) {
        sp30.unk50 |= 1;
    }
    sp30.unk56 = 3;
    sp30.unk58 = 0;
    sp30.unk5C = 0;
    sp30.unk60 = arg7;
    sp30.unk61 = 6;
    sp30.unk62 = 0;
    sp30.unk63 = 6;
    sp30.unk64 = 0;
    sp30.unk65 = 0;
    sp30.unk66 = 0;
    sp30.unk67 = 0;
    sp30.unk68 = 2;
    sp30.unk6A = 0;
    sp30.unk6C = 0;
    sp30.unk70 = 0;
    sp30.unk72 = (0x100 >> arg10);
    sp30.unk74 = 0xFF / (0x100 >> arg10);
    ret = func_15132A4C(&sp30, 3, 0xFF, 8, arg12, arg13);
    if (ret != NULL) {
        memcpy((u8 *)ret + 0x170, &sp28, 8);
    }
    return (s32)ret;
}


#pragma GLOBAL_ASM("asm/nonmatchings/game_1E34C0/func_151B6254.s")
