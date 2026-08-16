#include <ultra64.h>
#include "functions.h"
#include "variables.h"

struct Vec3F { f32 x; f32 y; f32 z; };

extern f32 D_800AA430;
extern u32 D_1500310C;
extern void *func_15132A4C(void *, s32, s32, s32, u8, s32);

typedef struct {
    char pad_0[0x88];
    s32 field_0x88;
} Game1E30A0Data;


void *func_151B5BF0(struct Vec3F *arg0, struct Vec3F *arg1, f32 arg2, struct Vec3F *arg3,
                    struct Vec3F *arg4, f32 arg5, s16 arg6, u8 arg7, s32 arg8, f32 arg9,
                    u8 arg10, u8 arg11, u8 arg12, s32 arg13) {
    void *ret;
    struct {
        f32 unk00;
        f32 unk04;
        f32 unk08;
        f32 unk0C;
        struct Vec3F unk10;
        f32 unk1C;
        f32 unk20;
        f32 unk24;
        struct Vec3F unk28;
        struct Vec3F unk34;
        struct Vec3F unk40;
        f32 unk4C;
        s32 unk50;
        s16 unk54;
        s16 unk56;
        u8 unk58;
        u8 pad59[3];
        s32 unk5C;
        u8 unk60;
        u8 unk61;
        u8 unk62;
        u8 unk63;
        u8 unk64;
        u8 unk65;
        u8 unk66;
        u8 unk67;
        u8 unk68;
        u8 pad69;
        u8 unk6A;
        u8 pad6B;
        s32 unk6C;
        u8 unk70;
        u8 pad71;
        s16 unk72;
        s16 unk74;
        u8 pad76[6];
    } sp48;
    struct {
        f32 unk00;
        f32 unk04;
    } sp40;
    u32 checksum;
    u32 *addr;
    u32 *codeEnd;
    s32 fadeStep;
    s32 fadeFrames;

    sp40.unk04 = arg2;
    sp40.unk00 = 0.0f;
    sp48.unk00 = D_800AA430 * arg2;
    sp48.unk04 = arg9;
    sp48.unk0C = arg2;
    sp48.unk08 = arg2;
    sp48.unk10 = *arg3;
    sp48.unk1C = 1.0f;
    sp48.unk20 = 1.0f;
    sp48.unk24 = 1.0f;
    sp48.unk28 = *arg0;
    sp48.unk50 = 0xB908;
    sp48.unk4C = arg5;

    if (arg6 == -1) {
        sp48.unk54 = 300;
        fadeStep = 0x100 >> arg10;
    } else {
        sp48.unk50 = 0xB988;
        fadeStep = 0x100 >> arg10;
        sp48.unk54 = arg6 + fadeStep;
    }

    if (arg1 != NULL) {
        sp48.unk34 = *arg1;
        sp48.unk50 |= 0x20;
    } else {
        sp48.unk34.x = 0.0f;
        sp48.unk34.y = 0.0f;
        sp48.unk34.z = 0.0f;
    }

    checksum = 0;
    addr = (u32 *)func_15002FB4;
    codeEnd = &D_1500310C;
    while (addr < codeEnd) {
        checksum += *addr;
        checksum *= 2;
        addr++;
    }
    if (checksum != 0x80D2D760) {
        D_8008FDA8 = -1;
    }

    if (arg4 != NULL) {
        sp48.unk40 = *arg4;
        sp48.unk50 |= 0x40;
    } else {
        sp48.unk40.x = 0.0f;
        sp48.unk40.y = 0.0f;
        sp48.unk40.z = 0.0f;
    }

    if (arg11 != 0) {
        sp48.unk50 |= 1;
    }

    sp48.unk56 = 2;
    sp48.unk58 = 0;
    sp48.unk5C = 0;
    sp48.unk60 = arg7;
    sp48.unk61 = 5;
    sp48.unk62 = 0;
    sp48.unk63 = 6;
    sp48.unk64 = 0;
    sp48.unk65 = 0;
    sp48.unk66 = 2;
    sp48.unk67 = 0;
    sp48.unk68 = 2;
    sp48.unk6A = 0;
    sp48.unk6C = 0;
    sp48.unk70 = 0;
    fadeFrames = 0xFF / fadeStep;
    sp48.unk72 = fadeStep;
    sp48.unk74 = fadeFrames;

    ret = func_15132A4C(&sp48, 3, 0xFF, 8, arg12, arg13);
    if (ret != NULL) {
        memcpy((u8 *)ret + 0x170, &sp40, 8);
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E30A0/func_151B5E94.s")

void func_151B5FCC(Game1E30A0Data *arg0) {
    if (arg0->field_0x88 != 0) {
        func_100111C8(arg0->field_0x88);
        arg0->field_0x88 = 0;
    }
}
