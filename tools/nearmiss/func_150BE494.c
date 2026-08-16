/*
 * PARKED near-miss -- func_150BE494  (game_EB340.c, 956 B)
 *
 * BEST MEASURED: 575   (was 585)
 *   cd conker && python3 ../tools/asm-differ/diff.py -o func_150BE494 -R --max-lines 4096
 *   Identical with and without -R.  Frame 0x160 correct.  This file IS the 575 source.
 *
 * WHAT MOVED IT: exactly one source line.  `sp58.unk34 = 0x1E; sp58.unk36 = 0x14;` must sit on
 * ONE line.  Found by decomp-permuter's perm_sameline pass and then reproduced by hand; the
 * 585 and 575 sources are TOKEN-IDENTICAL (tr -s ' \t\n' normalises them to the same stream),
 * so this is purely the -O2 -g3 source-line scheduling lever from tools/ido_cookbook.md.
 * NOTE: the pycparser round trip inside decomp-permuter re-splits that line, so re-seeding the
 * permuter from this file gives it a 585 base again -- chain from the output dir instead.
 *
 * RESIDUAL -- one instruction placement, no register is wrong:
 *   golden  addiu s0,sp,0x60   (&sp58.unk08: the CSE used by the 12-byte struct copy AND by
 *                               all three func_15153F18 calls)
 *           addiu t6,sp,0x154
 *           lw    at,0(t6)  /  li t0,4  /  li t9,3  /  sw at,0(s0) ...
 *   ours    addiu t6,sp,0x154
 *           lw    at,0(t6)
 *           addiu s0,sp,0x60      <-- sunk two slots, into the load-delay slot
 * That one shift cascades the li cascade by one slot and swaps `addiu a0,sp,0x58` / `move a1,s0`
 * in the FIRST of the three calls only.  Blocks 1 and 2 (spE0, spA4) are byte-correct; they
 * differ from block 3 only in that their copy destination is a single-use temp, so IDO is free
 * to sink it -- which is what it also does to the CSE in block 3 and does not do in golden.
 *
 * MEASURED NEGATIVES (each built hard: `rm -f build/src/game_EB340.c.o build/src/game_EB340.c`,
 * make hard-failed on error, object presence asserted, scored with AND without -R -- the two
 * numbers were equal for every single variant below):
 *    585  parked baseline
 *    585  copy statement joined onto the previous call's source line
 *    585  copy statement joined onto the next statement's source line
 *    585  copy joined onto BOTH neighbours (one long line)
 *    585  *(struct vec150BE494 *)&sp58.unk08 = sp154;
 *    585  *(struct vec150BE494 *)&sp58.unk08 = *(struct vec150BE494 *)&sp154;
 *    585  sp58.unk08 = *&sp154;
 *    599  sp58.unk2C = 4; sp58.unk2E = 3;   joined onto one line
 *    599  that join together with the explicit-address LHS
 *   1496  the whole block-3 assignment run collapsed onto one line
 *   1974  copy + unk2C + unk2E on one line
 *   3615  copy statement moved after `sp58.unk2E = 3;`
 *    924  named `struct vec150BE494 *pos` local declared FIRST   (frame 0x160 -> 0x168)
 *   1160  same, declared LAST                                    (frame 0x160 -> 0x168)
 *    873  Struct1504715C shrunk to 0x20 with no compensating local (frame -> 0x15C)
 *
 * FRAME FACT (keep -- it kills the obvious hypothesis): the local area 0x58..0x160 is EXACTLY
 * packed by the eight declared locals (0xC+4+4+4+0x24+0x44+0x3C+0x4C = 0x108).  At -O2 -g3 IDO
 * homes even a pointer local that lives entirely in a register, so a ninth local normally pushes
 * the frame to 0x168 -- measured.  There is exactly ONE legal slot: shrink Struct1504715C to
 * 0x20 and declare a 4-byte local between sp148 and sp124; it lands at 0x144 and the frame stays
 * 0x160.  Tried with `pos = &sp58.unk08; *pos = sp154;` and with `pos` used only by the three
 * calls: IDO copy-propagates `pos` away and both score EXACTLY 585.  So "golden has a hidden
 * pointer variable" is dead as an explanation and does not need re-exploring.
 *
 * HARNESS: `./permuter_tu.sh selftest` PASSES for game_EB340 (a, b, b2, c, d all PASS; (e)
 * reports that isolation differs from the in-TU build, i.e. the TU-aware harness is
 * load-bearing here).  ~2000 iterations with PERMUTER_TU_REQUIRE_FRAME=352 found only the
 * one-line join recorded above.
 */
#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_800A0068;

void func_150BDE90(void *arg0, u8 arg1, s32 arg2) {
    struct {
        void *unk0;
        u16 unk4;
        u16 unk6;
    } sp38;
    struct260 *temp_v0;

    sp38.unk0 = arg0;
    sp38.unk4 = 0;

    temp_v0 = func_15149130(0x12C, -1, 0x4F, -1, 0, 0x3C, (struct37 *)0x8, arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy((void *)((s32)temp_v0 + 0x28), &sp38, 8);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_EB340/func_150BDF0C.s")

void func_1516972C(struct102 *arg0);

void func_150BE150(struct102 *arg0, s32 **arg1, u8 arg2) {
    if (arg2 == 0x21) {
        if (*(s32 *)((u8 *)arg0 + 0x28) == (s32)arg1[0]) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0) {
        s32 *temp = arg1[0];
        if (*(s32 *)((u8 *)arg0 + 0x28) == temp[0xC6]) {
            func_1516972C(arg0);
        }
    }
}

extern f32 D_800BE9A4;

s32 func_150BE1C4(f32 *arg0) {
    arg0[5] += arg0[32] * D_800BE9A4;
    if (arg0[5] > 120.0f) {
        return 0;
    }
    return 1;
}

extern void func_1511650C(struct131 *arg0, s32, s32, f32);

void func_150BE210(struct131 *arg0) {
    if ((((u8 *)arg0)[0x73] & 3) == 3) {
        return;
    }
    func_1511650C(arg0, 1, 0x62C, 500.0f);
    if (((u8 *)arg0)[0x4F] & 4) {
        *(f32 *)((u8 *)arg0 + 0x84) += *(f32 *)((u8 *)arg0 + 0x64);
    } else if (270.0f < *(f32 *)((u8 *)arg0 + 0x84)) {
        *(f32 *)((u8 *)arg0 + 0x84) = 270.0f;
    }
    if (360.0f < *(f32 *)((u8 *)arg0 + 0x84)) {
        u16 a0 = *(u16 *)((u8 *)arg0 + 0x74);
        ((u8 *)arg0)[0x73] &= 0xFFFC;
        ((u8 *)arg0)[0x73] |= 3;
        *(f32 *)((u8 *)arg0 + 0x64) = 0.0f;
        func_100111C8(a0);
        *(u16 *)((u8 *)arg0 + 0x74) = 0;
    }
}

void func_150BE2E8(s16 *arg0) {
    f32 temp_f12;
    f32 temp_f2;
    f32 temp_f0;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f20;
    f32 temp_f22;

    temp_f0 = arg0[0x3E];
    temp_f2 = arg0[0x3F];
    temp_f12 = arg0[0x40];
    temp_f14 = arg0[0x41];
    temp_f16 = arg0[0x42];
    temp_f18 = arg0[0x43];
    temp_f20 = arg0[0x1E] * 0.00006103515625f;
    temp_f22 = arg0[0x1F] * 0.00006103515625f;
    temp_f20 -= temp_f20 * D_800A0068;
    temp_f22 += temp_f20 * D_800BE9E4;

    arg0[0x8] = (s32)((temp_f14 - temp_f0) * temp_f22 + temp_f0);
    arg0[0x9] = (s32)((temp_f16 - temp_f2) * temp_f22 + temp_f2);
    arg0[0xA] = (s32)((temp_f18 - temp_f12) * temp_f22 + temp_f12);
    if (1.0f < temp_f22) {
        temp_f22 = 1;
    }

    arg0[0x1E] = (s32)(temp_f20 * 16384.0f);
    arg0[0x1F] = (s32)(temp_f22 * 16384.0f);
}

s16 *func_150BE438(s16 *arg0, s32 arg1) {
    arg0[0] = 0x68;
    arg0[1] = D_800CC2D0[arg1].unk2E8;
    arg0[2] = 0xE;
    arg0[3] = D_800CC2D0[arg1].unk2E4;
    return arg0 + 4;
}

typedef struct {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ u8  unk1C;
    /* 0x1D */ u8  pad1D[0x7];
} Struct1504715C; /* 0x24 */

struct vec150BE494 {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
};

struct emit1515080C {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ struct vec150BE494 unk08;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ u8  unk40;
}; /* 0x44 */

struct emit15152190 {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ struct vec150BE494 unk08;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
}; /* 0x3C */

struct emit15153F18 {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ struct vec150BE494 unk08;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 unk32;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ s16 unk36;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ s8  unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ s16 unk44;
    /* 0x46 */ s16 unk46;
    /* 0x48 */ s32 unk48;
}; /* 0x4C */

extern s32 D_800A0010[];
extern f32 D_800A0038[];
extern s32 D_800A0060;
extern f32 D_800A0064;
extern f32 D_800A006C;
extern f32 D_800A0070;
extern f32 D_800A0074;
extern f32 D_800A0078;
extern f32 D_800A007C;
extern f32 D_800A0080;
extern f32 D_800A0084;
extern f32 D_800A0088;
extern f32 D_800A008C;
extern f32 D_800A0090;
extern f32 D_800A0094;
extern f32 D_800A0098;
extern f32 D_800A009C;
extern f32 D_800A00A0;

void func_1515C244(struct127 *, f32 *, f32 *, f32 *);
void func_1504715C(Struct1504715C *, struct127 *);
void func_1515080C(struct emit1515080C *, s32 *, f32 *, s32, s32, s32, s32, s32, s32,
                   Struct1504715C *, f32, s32, s32, u8, s32);
void func_15152190(struct emit15152190 *, s32 *, f32 *, s32, f32, s32, u8, s32);
void func_15153F18(struct emit15153F18 *, struct vec150BE494 *, Struct1504715C *, u8, s32);

void func_150BE494(struct127 *arg0, u8 arg1, s32 arg2) {
    struct vec150BE494 sp154;
    f32 sp150;
    f32 sp14C;
    f32 sp148;
    Struct1504715C sp124;
    struct emit1515080C spE0;
    struct emit15152190 spA4;
    struct emit15153F18 sp58;

    if (arg0 == NULL) {
        return;
    }

    sp148 = (arg0->xz_scale + arg0->y_scale) * 0.5f;
    func_1515C244(arg0, &sp154.x, &sp150, &sp14C);
    func_1504715C(&sp124, arg0);

    spE0.unk00 = 0xA;
    spE0.unk04 = 0;
    spE0.unk08 = sp154;
    spE0.unk14 = 0;
    spE0.unk16 = 0xFF;
    spE0.unk18 = -0x40;
    spE0.unk1A = 0x32;
    spE0.unk1C = 13.0f;
    spE0.unk20 = 9.0f;
    spE0.unk24 = D_800A006C;
    spE0.unk28 = D_800A0070;
    spE0.unk2C = 0x4B;
    spE0.unk2E = 0x28;
    spE0.unk30 = sp148;
    spE0.unk34 = 0.0f;
    spE0.unk38 = D_800A0074;
    spE0.unk3C = 1.0f;
    spE0.unk40 = 0xB;
    func_1515080C(&spE0, D_800A0010, D_800A0038, 0xA, 0, 0, 0, 1, -1, &sp124, 55.0f, 0, 0,
                  arg1, arg2);

    spA4.unk00 = 0x11;
    spA4.unk04 = 9;
    spA4.unk08 = sp154;
    spA4.unk14 = 0;
    spA4.unk16 = 0xFF;
    spA4.unk18 = -0x3F;
    spA4.unk1A = 0x4B;
    spA4.unk1C = 14.0f;
    spA4.unk20 = 11.0f;
    spA4.unk24 = D_800A0078;
    spA4.unk28 = D_800A007C;
    spA4.unk2C = 0x28;
    spA4.unk2E = 0x14;
    spA4.unk30 = D_800A0080;
    spA4.unk34 = D_800A0084;
    spA4.unk38 = D_800A0088;
    func_15152190(&spA4, &D_800A0060, &D_800A0064, 1, 10.0f, 0, arg1, arg2);

    sp58.unk08 = sp154;
    sp58.unk14 = D_800A008C;
    sp58.unk18 = D_800A0090;
    sp58.unk1C = D_800A0094;
    sp58.unk20 = D_800A0098;
    sp58.unk24 = D_800A009C;
    sp58.unk28 = D_800A00A0;
    sp58.unk2C = 4;
    sp58.unk2E = 3;
    sp58.unk02 = 0xFF;
    sp58.unk00 = 0;
    sp58.unk04 = -0x2B;
    sp58.unk06 = 0x1A;
    sp58.unk30 = 3;
    sp58.unk32 = 3;
    sp58.unk34 = 0x1E; sp58.unk36 = 0x14;
    sp58.unk38 = 0x9B;
    sp58.unk3A = 0x64;
    sp58.unk44 = 0x10;
    sp58.unk46 = 0xF;
    sp58.unk48 = 0;
    sp58.unk40 = 0.5f;
    sp58.unk3C = 0;
    func_15153F18(&sp58, &sp58.unk08, &sp124, arg1, arg2);
    sp58.unk3C = 2;
    func_15153F18(&sp58, &sp58.unk08, &sp124, arg1, arg2);
    sp58.unk3C = 0xA;
    func_15153F18(&sp58, &sp58.unk08, &sp124, arg1, arg2);
}
