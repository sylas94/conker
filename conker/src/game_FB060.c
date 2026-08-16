#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_800A07C4;
extern f32 D_800A07B4;
extern f32 D_800A07B8;
extern f32 D_800A07BC;
extern f32 D_800A07C0;
extern f32 D_800A07C8;
extern f32 D_800A07CC;
extern f32 D_800A07D0;
extern f32 D_800A07D4;
extern f32 D_800A07D8;
extern f32 D_800A07DC;
extern f32 D_800A07E0;

void func_15143794(s32, s32, f32, f32 *);
s32 func_15132A4C(void *, s32, s32, s32, u8, s32);

/* Near-miss at 315/35800; see tools/nearmiss/func_150CDBB0.c */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FB060/func_150CDBB0.s")

s32 func_150CDCF4(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5,
                  s32 arg6, s32 arg7, s16 arg8, s32 arg9, s32 arg10, s32 arg11,
                  s32 arg12, s32 arg13, u8 arg14) {
    struct260 *ret;
    struct {
        s32 temp;
        u8 pad28[4];
        f32 sp2C;
        u8 pad30[4];
        struct {
            s32 unk00;
            s32 unk04;
            s16 unk08;
            s16 unk0A;
            s32 unk0C;
            s32 unk10;
            u8 unk14;
            u8 unk15;
            u8 unk16;
            u8 unk17;
            u8 unk18;
            u8 unk19;
            u8 unk1A;
            u8 unk1B;
            u8 unk1C;
            u8 unk1D;
            s16 unk1E;
            s16 unk20;
            s16 unk22;
            f32 unk24;
            f32 unk28;
            f32 unk2C;
            f32 unk30;
            f32 unk34;
            f32 unk38;
            u8 pad3C[0xC];
            f32 unk48;
            f32 unk4C;
            f32 unk50;
            f32 unk54;
            s32 unk58;
            u8 pad5C[4];
            u8 unk60;
            u8 unk61;
            u8 unk62;
            s8 unk63;
        } sp34;
        u8 pad98[0xC];
    } stack;

    stack.sp34.unk1D = 0x29;
    stack.sp34.unk08 = 0xE03;
    stack.sp34.unk00 = 0x200005;
    stack.sp34.unk04 = 0;
    stack.sp34.unk0A = (func_150ADA20() % 0x29U) + 0x32;
    stack.sp34.unk0C = 0;
    stack.sp34.unk10 = 0;
    stack.sp34.unk18 = 0xB0;
    stack.sp34.unk19 = 0xA0;
    stack.sp34.unk1A = 0x2A;
    stack.sp34.unk14 = 0x40;
    stack.sp34.unk15 = 0xB;
    stack.sp34.unk16 = 0x6A;
    stack.sp34.unk17 = 0xFF;

    stack.sp34.unk1B = (func_150ADA20() % 0x65U) + 0x64;
    stack.sp34.unk1C = 0xFF;
    stack.sp34.unk60 = 3;
    stack.sp34.unk61 = 3;

    stack.sp34.unk28 = stack.sp34.unk2C = (func_150ADA68() * D_800A07B4) + 404.0f;
    stack.sp34.unk30 = arg2;
    stack.sp34.unk34 = arg3;
    stack.sp34.unk38 = arg4;

    stack.temp = func_150ADA20();
    func_15143794(arg8, (s16)((stack.temp % 0x14U) - 0x13),
                  (func_150ADA68() * 150.0f + 150.0f) * D_800A07B8,
                  &stack.sp34.unk48);

    stack.sp34.unk54 = 0.0f;
    stack.sp34.unk58 = 0xE05;

    if (func_150ADA20() & 1) {
        stack.sp34.unk58 |= 0x40;
    }

    if (func_150ADA20() & 1) {
        stack.sp34.unk58 |= 0x80;
    }

    stack.sp34.unk62 = 0xA;
    stack.sp34.unk24 = D_800A07BC;
    stack.sp2C = D_800A07C0;
    stack.sp34.unk63 = -1;
    stack.sp34.unk1E = 0x1E;
    stack.sp34.unk20 = 8;
    stack.sp34.unk22 = 0x46;

    ret = func_15130374(&stack.sp34, 1, 4, arg14, 1);
    if (ret != 0) {
        memcpy((u8 *)ret + 0xA8, &stack.sp2C, 4);
    }

    return 1;
}

s32 func_150CDF10(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5,
                  s32 arg6, s32 arg7, s16 arg8, s32 arg9, s32 arg10, s32 arg11,
                  s32 arg12, s32 arg13, u8 arg14) {
    struct {
            f32 unk00;
            f32 unk04;
            f32 unk08;
            f32 unk0C;
            f32 unk10;
            f32 unk14;
            f32 unk18;
            f32 unk1C;
            f32 unk20;
            f32 unk24;
            f32 unk28;
            f32 unk2C;
            f32 unk30;
            f32 unk34;
            f32 unk38;
            f32 unk3C;
            f32 unk40;
            f32 unk44;
            f32 unk48;
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
            u8 pad76[0xA];
    } sp28;

    sp28.unk28 = arg2;
    sp28.unk2C = arg3;
    sp28.unk1C = 1.0f;
    sp28.unk20 = 1.0f;
    sp28.unk24 = 1.0f;
    sp28.unk50 = 0x29E8;
    sp28.unk10 = 0.0f;
    sp28.unk14 = 0.0f;
    sp28.unk18 = 0.0f;
    sp28.unk44 = 0.0f;
    sp28.unk00 = 1.0f;
    sp28.unk56 = 0x20;
    sp28.unk30 = arg4;
    sp28.unk04 = D_800A07C4;

    ((s32 *)&sp28)[-2] = func_150ADA20();
    func_15143794(arg8, (s16)((((s32 *)&sp28)[-2] % 0x29U) - 0x3D),
                  (func_150ADA68() * 101.0f + 150.0f) * D_800A07C8,
                  &sp28.unk34);

    sp28.unk40 = (func_150ADA68() * 260.0f + -130.0f) * D_800A07CC;
    sp28.unk48 = (func_150ADA68() * 260.0f + -130.0f) * D_800A07D0;
    sp28.unk54 = (func_150ADA20() % 0x15U) + 0x32;
    sp28.unk4C = (func_150ADA68() * D_800A07D4 + D_800A07D8) * D_800A07DC;

    sp28.unk0C = (func_150ADA68() * 302.0f + 52.0f) * D_800A07E0;
    sp28.unk08 = sp28.unk0C;
    sp28.unk58 = 0;
    sp28.unk5C = 0;

    sp28.unk60 = (func_150ADA20() % 0x4CU) + 0xB4;
    sp28.unk61 = 8;
    sp28.unk62 = 0;
    sp28.unk63 = 0;
    sp28.unk64 = 0;
    sp28.unk65 = 0;
    sp28.unk66 = 0;
    sp28.unk67 = 0;
    sp28.unk68 = 0;
    sp28.unk6A = 2;
    sp28.unk6C = 0;
    sp28.unk70 = 0;
    sp28.unk72 = 0x20;
    sp28.unk74 = 7;

    func_15132A4C(&sp28, 3, 0xFF, 0, arg14, 0);
    return 1;
}
