#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_800A05AC;
extern f32 D_800A05B0;
extern f32 D_800A05B4;
extern f32 D_800A05B8;
extern f32 D_800A05BC;
extern f32 D_800A05C0;
extern f32 D_800A05C4;
extern f32 D_800A05C8;
extern f32 D_800A05CC;
extern f32 D_800A05D0;
extern f32 D_800A05D4;
extern f32 D_800A05D8;
extern f32 D_800A0570;
extern f32 D_800A0574;
extern f32 D_800A0578;
extern f32 D_800A057C;
extern f32 D_800A04F0;
extern f32 D_800A04F4;
extern f32 D_800A04F8;
extern f32 D_800A04FC;

void func_15143794(s32, s32, f32, f32 *);
struct260 *func_15130374(void *, u8, s32, u8, s32);
s32 func_15132A4C(void *, s32, s32, s32, u8, s32);
extern void func_1503E5F8(f32 (*)[4], f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);
extern struct260 *func_15073118(struct108 *, s32, s32, f32, f32, f32, f32, f32, f32, f32, s32);

typedef struct {
    u8 pad0[2];
    s8 unk2;
    u8 pad3;
    s16 unk4;
    s16 unk6;
    s16 unk8;
} Struct150C8350;

void func_150C8350(void) {
    Struct150C8350 *record;
    register s32 offset;
    s32 clamp;
    s32 max;
    s32 current;
    s32 target;
    s32 adjustedTarget;
    s32 diff;
    s32 absDiff;
    s32 step;
    s32 value;

    clamp = 0x4FF;
    max = 0x500;
    record = (Struct150C8350 *)0;

    for (offset = (s32)record; offset != 0x64; offset += sizeof(Struct150C8350)) {
        record = (Struct150C8350 *)((u8 *)D_800BE4E0 + offset);
        current = record->unk6;
        target = record->unk8;
        if (current != target) {
            adjustedTarget = target;
            if (current < 0) {
                adjustedTarget = -target;
            }

            diff = adjustedTarget - current;
            step = D_800BE9E4 << 4;
            absDiff = (diff < 0) ? -diff : diff;

            if (absDiff < step) {
                record->unk6 = adjustedTarget;
                record = (Struct150C8350 *)((u8 *)D_800BE4E0 + offset);
                current = record->unk6;
            } else {
                if (diff < 0) {
                    diff = -1;
                } else {
                    diff = 1;
                }
                value = step * diff;
                record->unk6 = current + value;
                record = (Struct150C8350 *)((u8 *)D_800BE4E0 + offset);
                current = record->unk6;
            }
        }

        record->unk4 += (current * record->unk2) * D_800BE9A0;
        record = (Struct150C8350 *)((u8 *)D_800BE4E0 + offset);
        value = record->unk4;
        if (value >= max) {
            record->unk4 = value - max;
            record = (Struct150C8350 *)((u8 *)D_800BE4E0 + offset);
            record->unk4 = max - record->unk4;
            record = (Struct150C8350 *)((u8 *)D_800BE4E0 + offset);
            record->unk2 = -record->unk2;
            record = (Struct150C8350 *)((u8 *)D_800BE4E0 + offset);
            if (record->unk4 >= max) {
                record->unk4 = clamp;
            }
        } else if (value < 0) {
            record->unk4 = -value;
            record = (Struct150C8350 *)((u8 *)D_800BE4E0 + offset);
            record->unk2 = -record->unk2;
            record = (Struct150C8350 *)((u8 *)D_800BE4E0 + offset);
            if (record->unk4 < 0) {
                record->unk4 = 0;
            }
        }

    }
}

extern void func_150C8350(void);

void func_150C84F4(s32 arg0) {
    if (arg0 == 0) {
        func_150C8350();
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_F5800/func_150C851C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_F5800/func_150C8600.s")

typedef struct {
    u8 pad0[0x34];
    Mtx *unk34;
} Struct150C8730Arg0;

typedef struct {
    f32 sp48;
    f32 sp4C;
    f32 sp50;
    f32 sp54;
    f32 sp58;
    f32 sp5C;
    f32 sp60;
    f32 sp64[4][4];
    u8 padA4[0x14];
} Struct150C8730Stack;

s32 func_150C8730(Struct150C8730Arg0 *arg0, struct108 *arg1) {
    Struct150C8730Stack sp48;
    f32 sp44;
    f32 sp40;
    s32 temp_v0_2;
    s32 temp_v1;
    Mtx *temp_a1;
    register s16 temp_t7;

    temp_v0_2 = arg1->unk2D0;
    if (temp_v0_2 == 0) {
        return 0;
    }

    temp_v1 = *(u16 *)((u8 *)arg1 + 0x84);
    if (((temp_v1 == 0x14) && (10.0f < *(f32 *)((u8 *)temp_v0_2 + 8))) || (temp_v1 == 0x23)) {
        temp_v0_2 = D_800BE9C0;
        temp_a1 = arg0->unk34;
        temp_a1 = (Mtx *)((u8 *)temp_a1 + ((temp_v0_2 == 0) << 6));
        guMtxL2F((f32 (*)[4])((u8 *)sp48.sp64 - 8), temp_a1);
        ((f32 (*)[4])((u8 *)sp48.sp64 - 8))[0][3] = 0.0f;
        ((f32 (*)[4])((u8 *)sp48.sp64 - 8))[1][3] = 0.0f;
        ((f32 (*)[4])((u8 *)sp48.sp64 - 8))[2][3] = 0.0f;
        ((f32 (*)[4])((u8 *)sp48.sp64 - 8))[3][3] = 1.0f;
        func_1503E5F8((f32 (*)[4])((u8 *)sp48.sp64 - 8), (f32 *)((u8 *)&sp48.sp60 - 8), (f32 *)((u8 *)&sp48.sp5C - 8), (f32 *)((u8 *)&sp48.sp58 - 8), (f32 *)((u8 *)&sp48.sp48 - 8), (f32 *)((u8 *)&sp44 - 8), (f32 *)((u8 *)&sp40 - 8), (f32 *)((u8 *)&sp48.sp54 - 8), (f32 *)((u8 *)&sp48.sp50 - 8), (f32 *)((u8 *)&sp48.sp4C - 8));

        arg0 = (Struct150C8730Arg0 *) func_15073118(arg1, -1, 0x4E, 0.0f, 0.0f, 0.0f, 0.0f, D_800A04F0, D_800A04F4, D_800A04F8, 0xC8);
        *(f32 *)((u8 *)arg0 + 0x14) = *(f32 *)((u8 *)&sp48.sp60 - 8);
        *(f32 *)((u8 *)arg0 + 0x18) = *(f32 *)((u8 *)&sp48.sp5C - 8);
        *(f32 *)((u8 *)arg0 + 0x1C) = *(f32 *)((u8 *)&sp48.sp58 - 8);
        *(f32 *)((u8 *)arg0 + 0xB8) = *(f32 *)((u8 *)&sp48.sp48 - 8);
        *(f32 *)((u8 *)arg0 + 0x40) = *(f32 *)((u8 *)&sp44 - 8);
        *(f32 *)((u8 *)arg0 + 0xC4) = *(f32 *)((u8 *)&sp40 - 8);
        temp_t7 = (s32)((*(f32 *)((u8 *)arg0 + 0x40) - 90.0f) * D_800A04FC);
        *(s16 *)((u8 *)arg0 + 0x76) = temp_t7;
        *(s16 *)((u8 *)arg0 + 0x7A) = temp_t7;
        return 1;
    }

    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_F5800/func_150C88D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_F5800/func_150C8A68.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_F5800/func_150C8DB8.s")

typedef struct {
    u8 pad0[1];
    u8 unk1;
    u8 pad2[0xA];
    u8 unkC;
    u8 padD[0x13];
    f32 unk20;
} Struct150C99B4;

void func_150C99B4(Struct150C99B4 *arg0, struct17 *arg1, s32 arg2, s32 arg3) {
    struct {
        u8 pad30[2];
        s16 sp32;
        u8 pad34[4];
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
            struct17 unk30;
            f32 unk3C;
            f32 unk40;
            f32 unk44;
            struct17 unk48;
            f32 unk54;
            s32 unk58;
            u8 pad5C[4];
            u8 unk60;
            u8 unk61;
            s8 unk62;
            s8 unk63;
        } sp38;
        u8 pad9C[0xC];
    } stack;
    f32 temp_f12;
    s32 temp;

    stack.sp38.unk1D = 0x26;
    stack.sp38.unk08 = 0xC01;
    stack.sp38.unk00 = 0x200005;
    stack.sp38.unk04 = 0;
    stack.sp38.unk0A = (func_150ADA20() % 0x51U) + 0x19;
    stack.sp38.unk0C = 0;
    stack.sp38.unk10 = 0;
    stack.sp38.unk60 = 5;
    stack.sp38.unk61 = 5;
    stack.sp38.unk14 = 0;
    stack.sp38.unk15 = 0;
    stack.sp38.unk16 = 0;
    stack.sp38.unk17 = 0xFF;
    stack.sp38.unk18 = 0;
    stack.sp38.unk19 = 0;
    stack.sp38.unk1A = 0;
    stack.sp38.unk1B = (func_150ADA20() % 0x9CU) + 0x64;
    stack.sp38.unk1C = 0xFF;

    stack.sp38.unk28 = stack.sp38.unk2C = (func_150ADA68() * 500.0f) + 500.0f;
    stack.sp38.unk30 = *arg1;
    stack.sp38.unk3C = 0.0f;
    stack.sp38.unk40 = 0.0f;
    stack.sp38.unk44 = 0.0f;

    stack.sp38.unk54 = ((func_150ADA68() * D_800A0570) + -1416.0f) * D_800A0574;
    stack.sp38.unk1E = 0x14;
    stack.sp38.unk20 = 0xC;
    stack.sp38.unk22 = 0;
    stack.sp38.unk24 = 1.0f;

    temp = (func_150ADA20() & 1) ? 0x40 : 0;
    stack.sp38.unk58 = ((((func_150ADA20() & 1) ? 0x80 : 0) | 7) | temp) | 0x200;
    stack.sp38.unk62 = -1;
    stack.sp38.unk63 = -1;
    stack.sp32 = (func_150ADA20() % 0xBU) - 0x12;

    temp_f12 = (func_150ADA68() * (arg0->unk20 * D_800A0578)) + (arg0->unk20 * D_800A057C);
    func_15143794((u8)arg2, stack.sp32, temp_f12, &stack.sp38.unk48.unk0);
    func_15130374(&stack.sp38, 1, 0, arg0->unkC, arg0->unk1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_F5800/func_150C9BDC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_F5800/func_150C9DC4.s")

extern f32 D_800BE9A4;
s32 func_150CA07C(f32 *arg0) {
    arg0[14] += arg0[17] * D_800BE9A4;
    arg0[15] += (arg0[18] * D_800BE9A4) + (((arg0[23] * D_800BE9A4) * D_800BE9A4) * 0.5f);
    arg0[16] += arg0[19] * D_800BE9A4;
    arg0[18] += arg0[23] * D_800BE9A4;
    arg0[8] += arg0[20] * D_800BE9A4;
    arg0[9] += arg0[21] * D_800BE9A4;
    arg0[10] += arg0[22] * D_800BE9A4;
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_F5800/func_150CA150.s")

typedef struct {
    f32 unk0;
    f32 unk4;
    s32 unk8;
} Struct150CA930;

extern void func_1514C678(f32, f32, s32, f32, s32, s32, s32, s32, s32, f32, s32, s32);

void func_150CA930(Struct150CA930 *arg0) {
    s16 temp;

    temp = (func_150ADA20() % 21U) + 10;
    func_1514C678(arg0->unk0, arg0->unk4, arg0->unk8,
                  (func_150ADA68() * 59.0f) + 170.0f,
                  0, 0xFF, temp, 0x13, 0, 0.0f, 0, 0xFF);
}

typedef struct {
    char pad1C[0x1C];
    s16 unk1C;
    char pad1E[0x28 - 0x1E];
    u8 unk28;
} Struct150CA9D0;

s32 func_150CA9D0(Struct150CA9D0 *arg0) {
    s32 v1;
    if (arg0->unk1C < 0x20) {
        v1 = arg0->unk1C << 3;
        if (v1 < arg0->unk28) {
            arg0->unk28 = v1;
        }
    }
    return 1;
}

s32 func_150CAA04(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5,
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
    stack.sp34.unk0A = (func_150ADA20() % 0x1AU) + 0x19;
    stack.sp34.unk0C = 0;
    stack.sp34.unk10 = 0;
    stack.sp34.unk18 = 0xB0;
    stack.sp34.unk19 = 0xA0;
    stack.sp34.unk1A = 0x2A;
    stack.sp34.unk14 = 0x40;
    stack.sp34.unk15 = 0xB;
    stack.sp34.unk16 = 0x6A;
    stack.sp34.unk17 = 0xFF;

    stack.sp34.unk1B = (func_150ADA20() % 0x9CU) + 0x64;
    stack.sp34.unk1C = 0xFF;
    stack.sp34.unk60 = 3;
    stack.sp34.unk61 = 3;

    stack.sp34.unk28 = stack.sp34.unk2C = (func_150ADA68() * D_800A05AC) + 800.0f;
    stack.sp34.unk30 = arg2;
    stack.sp34.unk34 = arg3;
    stack.sp34.unk38 = arg4;

    stack.temp = func_150ADA20();
    func_15143794(arg8, (s16)((stack.temp % 0xCU) - 0x15),
                  (func_150ADA68() * 300.0f + 498.0f) * D_800A05B0,
                  &stack.sp34.unk48);

    stack.sp34.unk54 = 0.0f;
    stack.sp34.unk58 = 0xE05;

    if (func_150ADA20() & 1) {
        stack.sp34.unk58 |= 0x40;
    }

    if (func_150ADA20() & 1) {
        stack.sp34.unk58 |= 0x80;
    }

    stack.sp34.unk62 = 9;
    stack.sp34.unk24 = D_800A05B4;
    stack.sp2C = D_800A05B8;
    stack.sp34.unk63 = -1;
    stack.sp34.unk1E = 0x19;
    stack.sp34.unk20 = 0xA;
    stack.sp34.unk22 = 0x20;

    ret = func_15130374(&stack.sp34, 1, 4, arg14, 1);
    if (ret != 0) {
        memcpy((u8 *)ret + 0xA8, &stack.sp2C, 4);
    }

    return 1;
}

s32 func_150CAC28(f32 *arg0, s32 arg1) {
    f32 *scale;
    s32 i;

    scale = (f32 *)((u8 *)arg0 + 0xA8);
    for (i = D_800BE9E4; i != 0; i--) {
        arg0[22] *= *scale;
        arg0[24] *= *scale;
    }
    return 1;
}

s32 func_150CADD0(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5,
                  s32 arg6, s32 arg7, s16 arg8, s32 arg9, s32 arg10, s32 arg11,
                  s32 arg12, f32 *arg13, u8 arg14) {
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
    sp28.unk04 = D_800A05BC;

    ((s32 *)&sp28)[-2] = func_150ADA20();
    func_15143794(arg8, (s16)((((s32 *)&sp28)[-2] % 21U) - 40),
                  (func_150ADA68() * 204.0f + 500.0f) * D_800A05C0,
                  &sp28.unk34);

    sp28.unk40 = (func_150ADA68() * 260.0f + -130.0f) * D_800A05C4;
    sp28.unk48 = (func_150ADA68() * 260.0f + -130.0f) * D_800A05C8;
    sp28.unk54 = (func_150ADA20() % 0x33U) + 0x32;
    sp28.unk4C = (func_150ADA68() * 1008.0f + D_800A05CC) * D_800A05D0;

    sp28.unk08 = sp28.unk0C = (func_150ADA68() * D_800A05D4 + 200.0f) * D_800A05D8;
    sp28.unk58 = 0;
    sp28.unk5C = 0;

    sp28.unk60 = (func_150ADA20() % 0x4CU) + 0xB4;
    sp28.unk61 = 4;
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

s32 func_150CB008(f32 *arg0) {
    arg0[14] += arg0[17] * D_800BE9A4;
    arg0[15] += (arg0[18] * D_800BE9A4) + (((arg0[23] * D_800BE9A4) * D_800BE9A4) * 0.5f);
    arg0[16] += arg0[19] * D_800BE9A4;
    arg0[18] += arg0[23] * D_800BE9A4;
    arg0[8] += arg0[20] * D_800BE9A4;
    arg0[9] += arg0[21] * D_800BE9A4;
    arg0[10] += arg0[22] * D_800BE9A4;
    return 1;
}
