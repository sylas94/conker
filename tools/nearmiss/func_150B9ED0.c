/* func_150B9ED0  (game_E7380, 1164 bytes)  --  PARKED at 1014 / 29100.
 *
 * SUPERSEDES func_150B9ED0.INFLIGHT.c and .INFLIGHT2.c: I scored both this wave and they are
 * the same program -- BOTH read exactly 1014.  The only textual difference between them is
 * whether `dirY = 0.0f` sits at argument 5 or argument 15 of the func_150AC9C0 call, and IDO
 * produces an identical object either way.
 *
 * MEASURED THIS WAVE (object deleted before each build, --max-lines 4096):
 *     INFLIGHT.c / INFLIGHT2.c            1014
 *     dirY hoisted to its own statement   1014   (inert)
 *     dirY hoisted + literal last arg     1014   (inert)
 *     dirX and dirZ ALSO hoisted          1594   (WORSE -- they must stay inline)
 *
 * THE WHOLE 1014 IS ONE CLUSTER.  Every other instruction in this 1164-byte function is
 * byte-identical; the only differing rows are 0x104..0x17c, the argument block of the
 * 15-argument func_150AC9C0 call.  Same instruction COUNT, same registers, same stack slots,
 * same values -- purely a schedule order.  The knot is one instruction:
 *     golden  lui at,0x42a0 / mtc1 zero,$f18 / lwc1 $f8,0x15c(sp) / ...
 *     ours    lui at,0x42a0 / <the five lwc1> / mtc1 zero,$f18
 * i.e. IDO materialises the 0.0f SECOND in golden and SEVENTH in ours, and every later
 * addiu/sw in the block phase-shifts by one slot as a result.  Golden also stores arg15
 * (swc1 $f18,0x38(sp)) with the other zero args rather than last, which is the same fact.
 *
 * WHAT IS ALREADY RIGHT: the func_151E7EF8..func_151E7F60 `~*p` checksum loop and its
 * 0x3843095E compare, both func_150A3058 guard calls with the (s16) trunc/sll/sra idiom,
 * every one of the 15 argument slots (0x10..0x38) with the correct value and register,
 * dirX/dirZ as `-(field - param)` (sub.s + neg.s -- NOT `param - field`, which would emit a
 * single sub), the whole spE4 block with its two `% 0x33U` / `% 0x65U` randoms, and the
 * entire sp70 tail including all seven D_8009FE* pool reads.
 *
 * RODATA: this TU's constants D_8009FE10..D_8009FE28 sit in splat block [0x2448D0, rodata].
 * That block is now SCOPED (see func_150BA55C.c): it splits cleanly at 0x2448F0 into an
 * all-game_E7380 half and an all-game_E7970 half.  The migration cannot ship until this
 * function reaches 0, because the block carries its constants.
 */

#include <ultra64.h>
/* include/functions.h declares func_150ADA20 as returning u8.  The golden code for
 * func_150B9ED0 feeds its result straight into `divu` with no zero-extension, which a
 * u8-returning declaration cannot produce, so the real return type is a word.  Per project
 * policy the shared header is left alone and the correct prototype is made file-local:
 * the header's declaration is renamed out of the way while functions.h is included. */
#define func_150ADA20 func_150ADA20_u8_decl_in_functions_h
#include "functions.h"
#undef func_150ADA20
s32 func_150ADA20(void);
#include "variables.h"

extern s32 func_150AC9C0(f32, f32, f32, f32, f32, f32, void *, void *, f32 *, f32 *, f32 *,
                         s32, s32 *, s32, f32);
extern s32 func_15145C90(s32);
extern void func_151511FC(void *, u8, s32);
extern void func_151E7EF8(void);
extern void func_151E7F60(void);

extern u8 D_80084060;
extern f32 D_8009FE10;
extern f32 D_8009FE14;
extern f32 D_8009FE18;
extern f32 D_8009FE1C;
extern f32 D_8009FE20;
extern f32 D_8009FE24;
extern f32 D_8009FE28;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3_E7380;

typedef struct {
    s16 unk00;
    s16 unk02;
    s16 unk04;
    s16 unk06;
    s16 unk08;
    s16 unk0A;
    s16 unk0C;
    s16 unk0E;
    s16 unk10;
} Buf12_E7380;

typedef struct {
    s16 unk00;
    s16 unk02;
    Vec3_E7380 unk04;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    Buf12_E7380 unk1C;
    f32 unk30;
    u8 unk34;
    u8 unk35;
    s16 unk36;
    s16 unk38;
    s16 unk3A;
    f32 unk3C;
    f32 unk40;
    s32 unk44;
    u8 unk48;
    u8 unk49;
    f32 unk4C;
    f32 unk50;
    f32 unk54;
    f32 unk58;
    u8 unk5C;
    u8 unk5D;
    s32 unk60;
    s32 unk64;
    s16 unk68;
    s16 unk6A;
    f32 unk6C;
    f32 unk70;
} Effect_E7380;

typedef struct {
    s32 unk00;
    s16 unk04;
    u8 unk06;
    u8 unk07;
    s32 unk08;
    s32 unk0C;
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 unk17;
    s32 unk18;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    s16 unk24;
    s16 unk26;
} Spawn_E7380;

typedef struct {
    u8 pad00[0x14];
    f32 unk14;
    f32 unk18;
    f32 unk1C;
} Obj_E7380;

void func_150B9ED0(Obj_E7380 *arg0, f32 arg1, f32 arg2, u8 arg3, s32 arg4) {
    u32 *p, *end;
    s32 sum;
    s32 res1, res2, res3, res4;
    f32 dirZ, dirY, dirX;
    Vec3_E7380 hit;
    Buf12_E7380 sp110;
    s32 sp10C;
    Spawn_E7380 spE4;
    Effect_E7380 sp70;
    s32 randA, randB, randC;
    f32 fB, fA;

    if (arg0 == NULL) {
        return;
    }

    end = (u32 *)func_151E7F60;
    p = (u32 *)func_151E7EF8;
    sum = 0;
    while (p < end) {
        sum += ~*p;
        p++;
    }
    if (sum != 0x3843095E) {
        D_80084060 = 0xFF;
    }

    res1 = func_150A3058(2, (s16)arg0->unk14, (s16)arg0->unk18, (s16)arg0->unk1C);
    if (res1 != 0) {
        return;
    }
    res2 = func_150A3058(1, (s16)arg0->unk14, (s16)arg0->unk18, (s16)arg0->unk1C);
    if (res2 != 0) {
        return;
    }

    res3 = func_150AC9C0(arg0->unk14, arg0->unk18 + 80.0f, arg0->unk1C,
                         dirX = -(arg0->unk14 - arg1),
                         0.0f,
                         dirZ = -(arg0->unk1C - arg2),
                         NULL, &sp110, &hit.x, &hit.y, &hit.z, 0, &sp10C, 0, dirY = 0.0f);
    if (res3 == 0) {
        return;
    }

    res4 = func_15145C90(sp10C);
    if (res4 != 0) {
        spE4.unk06 = 6;
        spE4.unk07 = 0;
        spE4.unk00 = 0x9F01;
        spE4.unk04 = (func_150ADA20() % 0x33U) + 0x64;
        spE4.unk08 = 0;
        spE4.unk0C = 0;
        spE4.unk10 = (func_150ADA20() % 0x65U) + 0x9B;
        spE4.unk11 = 0xFF;
        spE4.unk12 = 0xFF;
        spE4.unk13 = 0xFF;
        spE4.unk14 = 0xFF;
        spE4.unk15 = 0xFF;
        spE4.unk18 = 0x3B0002;
        spE4.unk16 = 0;
        spE4.unk17 = 7;
        spE4.unk22 = 0x19;
        spE4.unk24 = 0xA;

        fA = func_150ADA68();
        fB = func_150ADA68();
        randA = func_150ADA20();
        randB = func_150ADA20();
        randC = func_150ADA20();
        func_1513C650((s32)&spE4, 0, 0, (s32)&sp110, hit.x, hit.y, hit.z,
                      (fA * 20.0f) + 40.0f, (fB * 20.0f) + 40.0f,
                      randA & 0xFF, (randC & 1) + ((randB & 1) * 2),
                      3, 0xFF, 0, arg3, arg4);
    }

    sp70.unk00 = 0xF;
    sp70.unk02 = 0xA;
    sp70.unk04 = hit;
    sp70.unk10 = -dirX;
    sp70.unk14 = -dirY;
    sp70.unk18 = -dirZ;
    sp70.unk1C = sp110;
    sp70.unk30 = D_8009FE10;
    sp70.unk34 = 7;
    sp70.unk35 = 0;
    sp70.unk36 = 0x3B01;
    sp70.unk38 = 0x1A;
    sp70.unk3A = 0x14;
    sp70.unk3C = 7.0f;
    sp70.unk40 = 10.0f;
    sp70.unk44 = 0x5C0001;
    sp70.unk48 = 0x64;
    sp70.unk49 = 0x9B;
    sp70.unk4C = D_8009FE14;
    sp70.unk50 = D_8009FE18;
    sp70.unk54 = D_8009FE1C;
    sp70.unk58 = D_8009FE20;
    sp70.unk5C = 0;
    sp70.unk5D = 7;
    sp70.unk60 = 3;
    sp70.unk64 = 0xFF;
    sp70.unk68 = 0xA;
    sp70.unk6A = 0x19;
    sp70.unk6C = D_8009FE24;
    sp70.unk70 = D_8009FE28;
    func_151511FC(&sp70, arg3, arg4);
}

s32 func_150BA35C(s16 *arg0) {
    s16 temp = arg0[0xE];
    if (temp < 0x40) {
        *((s8 *)arg0 + 0x28) = temp << 2;
    }
    return 1;
}

extern f32 D_800BE9A4;
extern f32 D_8009FE2C;

s32 func_150BA37C(s32 *arg0) {
    *(f32 *)((s8 *)arg0 + 0x114) = *(f32 *)((s8 *)arg0 + 0x114) + D_8009FE2C * D_800BE9A4;
    *(f32 *)((s8 *)arg0 + 0x34) = *(f32 *)((s8 *)arg0 + 0x110) * D_800BE9A4 + *(f32 *)((s8 *)arg0 + 0x34);
    *(f32 *)((s8 *)arg0 + 0x38) = *(f32 *)((s8 *)arg0 + 0x114) * D_800BE9A4 + *(f32 *)((s8 *)arg0 + 0x38);
    *(f32 *)((s8 *)arg0 + 0x3C) = *(f32 *)((s8 *)arg0 + 0x118) * D_800BE9A4 + *(f32 *)((s8 *)arg0 + 0x3C);
    *(f32 *)((s8 *)arg0 + 0x40) = *(f32 *)((s8 *)arg0 + 0x11C) * D_800BE9A4 + *(f32 *)((s8 *)arg0 + 0x40);
    *(f32 *)((s8 *)arg0 + 0x44) = *(f32 *)((s8 *)arg0 + 0x120) * D_800BE9A4 + *(f32 *)((s8 *)arg0 + 0x44);
    return 1;
}

s32 func_150BA424(s32 *arg0) {
    f32 diff = *(f32 *)((s8 *)arg0 + 0x38) - *(f32 *)((s8 *)arg0 + 0x124);
    s32 a;
    s32 b;

    if (diff < 0.0f) {
        return 0;
    }

    a = *(s16 *)((s8 *)arg0 + 0x1C) << 4;
    if (a >= 0x100) {
        a = 0xFF;
    }

    b = (s32)diff << 2;
    if (b >= 0x100) {
        b = 0xFF;
    }

    if (b < a) {
        *((s8 *)arg0 + 0x5C) = b;
    } else {
        *((s8 *)arg0 + 0x5C) = a;
    }

    if (*((u8 *)arg0 + 0x5C) < 0) {
        return 0;
    }
    return 1;
}
