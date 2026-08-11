/* ============================================================================
 * PERMUTER CANDIDATE -- func_1508F9F4  (game_BC510.c, 836 B, underwater bubbles)
 *
 * WHOLE-TU FILE. Drop it over conker/src/game_BC510.c to reproduce. It builds
 * and every OTHER function in the TU still scores 0 (verified). The live body
 * of func_1508F9F4 is at the bottom, replacing its #pragma.
 *
 * MEASURED, honest, no forcers:  score 1113
 *   (previous wave parked this at 1483; the delta below is real hand work)
 *
 * HOW IT GOT HERE
 *   9858 -> 1483  earlier wave: index D_800D2460[] DIRECTLY, never through a
 *                 pointer local (a pointer local defeats IDO alias analysis and
 *                 makes it reload D_800BE9E4 after every store in case 2); and
 *                 declare the per-case scratch ints in BLOCK scope.
 *   1483 -> 1113  this wave: in case 2 put `unk00 = ...` BEFORE `unk0F += ...`.
 *                 The target schedules `lh unk04` ahead of `lbu unk0F`; source
 *                 order is what drives it. Killed both `|` reorder rows there.
 *
 * SEED THE PERMUTER FROM THIS FILE, NOT FROM A RAW BASE. (func_151C1D5C ground
 * 11,939 iterations for zero improvement from its raw base and then found the
 * answer in ~5k once hand work had taken it 385 -> 320.)
 *
 * ---------------------------------------------------------------------------
 * RESIDUAL, exactly four items. Nothing else in the function differs.
 *
 * (1) FRAME 0x50 vs 0x40  -- rows: `addiu sp,sp,-0x50`, `addiu sp,sp,0x50`,
 *     and 4 stack-offset rows.
 *     Target local homes:  rate 0x3C (lw only, NEVER stored), spawn 0x44.
 *     Mine:                rate 0x38,                          spawn 0x3C.
 *     IDO packs homes tightly and hands the FIRST-declared local the HIGHEST
 *     slot, so the target has SIX word homes (0x38,0x3C,0x40,0x44,0x48,0x4C)
 *     with spawn 3rd and rate 5th -- but only two are ever referenced; the
 *     other four words are dead. Four extra memory-resident locals cannot be
 *     produced from honest C:
 *       - unused named locals are eliminated by IDO (verified, no effect);
 *       - block-scoped locals are eliminated (verified, no effect);
 *       - declaration order only permutes the two homes that exist (verified);
 *       - splitting lvl/rate into two real variables makes `rate` spill for
 *         real (sw+lw at 0x38) but the area stays 2 words, frame stays 0x40 --
 *         and it costs s7, blowing the score to 2939. DO NOT SPLIT lvl/rate.
 *     `rate`'s home exists because `rate` is UNDEFINED on the `air < 0x5B`
 *     path and IDO materialises the undefined value with `lw s7,0x3C(sp)`.
 *     That read of an uninitialised local is an ORIGINAL-GAME BUG and must be
 *     reproduced, not fixed. Same for `spawn`, which is only ever assigned 0.
 *
 * (2) case 2 v0/v1 COLOURING -- the bulk of the residual (~50 rows).
 *     target: t->v0, j->v1, count->a2 (the lbu destination itself),
 *             the `unk02 -=` scratch ->a0.
 *     mine:   j->v0, t->v1, count->a0 (needs an extra `move a0,a2`),
 *             the `unk02 -=` scratch ->t5/t7/t8.
 *     Everything else in case 2 (rows for `lh unk06` vs `sh unk02` around the
 *     `blez a1` guard, and the `b`+nop vs `b`+`sh` delay slot at the end of the
 *     case) is DOWNSTREAM of this colouring -- they are the scheduler reacting
 *     to which registers are live, not independent defects.
 *     RULED OUT, each measured:
 *       - `s32 t; s32 j;`  vs  `s32 j; s32 t;`  -> byte-identical output.
 *       - `count = t;`     vs  `count = D_800D2460[i].unk0C;` -> byte-identical.
 *       - hoisting t/j/count to function scope -> 1765 (drags `state` off v1
 *         onto a0 in the pre-block and case 1, which currently match).
 *     Two independent spellings leaving the score EXACTLY 1113 is the v0/v1
 *     allocation tie. No source handle exists. This is the permuter's job.
 *
 * (3) case 0 `mul.s $f8,$f0,$f6` vs mine `$f8,$f6,$f0`  -- ONE row.
 *     The IDENTICAL expression in case 2 comes out `$f0,$f18` and matches, so
 *     this is fp register allocation, not operand order. Writing the multiply
 *     as `D_800D2460[i].unk08 * cs` instead of `cs * D_800D2460[i].unk08`
 *     produces byte-identical output (measured). Another tie.
 *
 * (4) `%hi/%lo(D_800D2460+0x60)` vs target `%hi/%lo(D_800D24C0)` -- 2 rows,
 *     plus 1 knock-on register row. THIS IS THE KNOWN RELOC-SPELLING ARTEFACT,
 *     NOT A DEFECT. `for (i = 0; i < 6; i++)` is strength-reduced by IDO to a
 *     pointer walk whose limit is &D_800D2460[6] == 0x800D24C0; splat, reading
 *     the LINKED rom, names that address D_800D24C0. The unlinked object
 *     encodes `lui $t5,0` + R_MIPS_HI16 either way and links to the same bytes.
 *     DO NOT invent an extern or a pointer-loop to silence it -- the floor for
 *     this function is these rows, not 0.
 *
 * ---------------------------------------------------------------------------
 * HEADER FIXES THIS FILE CARRIES (all file-local, zero effect on other TUs;
 * the `#define X X_proto` idiom is established repo precedent -- see
 * src/game_10B7D0.c and src/game_142560.c):
 *   functions.h says `void func_15048A40(u8)`; it really returns f32 in $f0.
 *   variables.h says `u8 D_800D2460[][16]`;    it is really a 6-element array
 *                                              of the 0x10-byte StructD2460.
 *   `void func_1508F9F4(void);` is forward-declared because func_1508F0A4,
 *   already live C above it, calls it.
 * Field map recovered from the asm (StructD2460, 0x10 bytes):
 *   00 s16 x   02 s16 y   04 s16 baseX  06 s16 radius/scale
 *   08 s16 angleStep      0A s16 timer  0C u8 alpha  0D u8 state
 *   0E u8 phase           0F u8 phase2
 * D_800D24C0 (s32, immediately after the array) is the shared spawn cooldown.
 * D_800CC2D0[0].in_water / .unkB2 are the player's water flag and oxygen.
 * ============================================================================
 */
#include <ultra64.h>

#define func_15048A40 func_15048A40_void_proto
#define D_800D2460 D_800D2460_u8_proto
#include "functions.h"
#include "variables.h"
#undef func_15048A40
#undef D_800D2460

extern f32 func_15048A40(u8 arg0);

typedef struct {
    s16 unk00;
    s16 unk02;
    s16 unk04;
    s16 unk06;
    s16 unk08;
    s16 unk0A;
    u8  unk0C;
    u8  unk0D;
    u8  unk0E;
    u8  unk0F;
} StructD2460; /* 0x10 */

extern StructD2460 D_800D2460[6];

void func_1508F9F4(void);

extern s32 func_1510D0EC(s32, s32, s32, s32);
void func_15042D94(s32, s32, u8, s32 *, ...);
extern u8 D_D16[];
extern u8 D_11AD[];
extern s32 D_800D2450;
void func_150A7D00(s32, f32, f32, f32);
extern Gfx D_80084160[];
extern Gfx D_80083440[];
extern Gfx D_800835C0[];
extern Gfx D_80084190[];
extern f32 D_8009DD40;
extern f32 D_8009DD44;
extern f32 D_8009DD48;

typedef struct {
    Mtx  unk00[2];   /* 0x00 */
    Gfx *unk80;      /* 0x80 */
    Gfx *unk84[7];   /* 0x84 */
    f32  unkA0;      /* 0xA0 */
    f32  unkA4;      /* 0xA4 */
    f32  unkA8;      /* 0xA8 */
    s32  unkAC;      /* 0xAC */
    u16  unkB0;      /* 0xB0 */
    u16  unkB2;      /* 0xB2 */
    u16  unkB4;      /* 0xB4 */
    u16  unkB6;      /* 0xB6 */
    u16  unkB8;      /* 0xB8 */
    u8   unkBA;      /* 0xBA */
} StructD24C8;

// need to figure out D_800D2460
// best 635: IDO folds constant index 2 to base=arr[0]; target keeps runtime
// `li 2; sll; addu` base at arr[2] (de-optimized) — non-foldable, uncrackable from C.
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_1508F060.s")

void func_1508F0A4(void) {
    func_1508F0D4();
    func_1508F9F4();
    func_1509093C();
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_1508F0D4.s")

void func_1508F7BC(void) {
    f32 sp48[4][4];
    f32 sp44;
    struct256 *temp_v0;

    D_800D2456 -= 1;
    D_800D2890.unk0 = (u32) (func_150ADA20() % 5U);
    D_800D2890.unk8 = sqrtf(25.0f - (D_800D2890.unk0 * D_800D2890.unk0));
    temp_v0 = allocate_memory(sizeof(*temp_v0), 1, 1, 0);
    temp_v0->unk80 = D_800D245C;
    D_800D245C = temp_v0;
    guMtxL2F(&sp48, (D_800D2456 << 7) + ((D_800BE9C0 ^ 1) << 6) + &D_800D2590);
    func_1503E5F8(&sp48, &temp_v0->unk84, &temp_v0->unk88, &temp_v0->unk8C, &temp_v0->unk9C, &temp_v0->unkA0, &temp_v0->unkA4, &sp44, &sp44, &sp44);

    temp_v0->unk90 = (u32)((func_150ADA20() & 0xF) + 10);
    temp_v0->unk94 = (u32)((func_150ADA20() & 0x1F) + 20);
    temp_v0->unk98 = 0.0f;
    temp_v0->unkA8 = (u32)(func_150ADA20() & 0xF);
    temp_v0->unkAC = (u32)(func_150ADA20() & 0xF);
    temp_v0->unkB0 = (u32)(func_150ADA20() & 0xF);
    temp_v0->unkB4 = 120;
}

void func_1508F9C4(void) {
    D_800D2410[D_800D2456++] = 0.0f;
}

void func_1508F9F4(void) {
    s32 spawn;
    s32 rate;
    s32 air;
    s32 i;
    f32 cs;

    air = D_800D24C0;
    if (air != 0) {
        air -= D_800BE9E4;
        if (air < 0) {
            air = 0;
        }
        D_800D24C0 = air;
    }
    if (D_800CC2D0[0].in_water != 0) {
        air = D_800CC2D0[0].unkB2;
    } else {
        air = 0;
    }
    if (air >= 0x5B) {
        rate = air / 240;
        if (rate >= 7) {
            rate = 6;
        }
        rate = 6 - rate;
        rate = rate * 9;
        if (rate == 0) {
            spawn = 0;
        }
    } else {
        spawn = 0;
    }
    for (i = 0; i < 6; i++) {
        if (D_800D2460[i].unk0D == 2) {
            s32 t;
            t = D_800D2460[i].unk0A;
            t -= D_800BE9E4;
            if (t <= 0) {
                t = 6;
                D_800D2460[i].unk0D = 3;
            }
            D_800D2460[i].unk0A = t;
        }
        switch (D_800D2460[i].unk0D) {
        case 0:
            if (spawn != 0 && D_800D24C0 == 0) {
                D_800D24C0 = 10;
                D_800D2460[i].unk0D = 1;
                D_800D2460[i].unk00 = 0xFC;
                D_800D2460[i].unk02 = 0x60;
                D_800D2460[i].unk06 = 0;
                D_800D2460[i].unk0C = 0;
                D_800D2460[i].unk0E = func_150ADA20();
                D_800D2460[i].unk08 = 0x500;
                cs = func_15048A40(D_800D2460[i].unk0E);
                D_800D2460[i].unk0F = 0;
                D_800D2460[i].unk0A = rate;
                D_800D2460[i].unk04 = 0xFC - ((s32)(cs * D_800D2460[i].unk08) >> 8);
            }
            break;
        case 1: {
            s32 t;
            t = D_800D2460[i].unk06;
            t += D_800BE9E4 * 200;
            if (t >= 0x666) {
                D_800D2460[i].unk0D = 2;
                t = 0x666;
            }
            D_800D2460[i].unk06 = t;
            break;
        }
        case 2: {
            s32 j;
            s32 t;
            u8 count;
            count = D_800D2460[i].unk0C;
            if (count < 0x20) {
                t = count;
                t += D_800BE9E4;
                if (t > 0x20) {
                    t = 0x20;
                }
                D_800D2460[i].unk0C = t;
                count = t;
            }
            D_800D2460[i].unk02 -= (D_800BE9E4 * count) >> 4;
            t = D_800D2460[i].unk06;
            for (j = 0; j < D_800BE9E4; j++) {
                t = (t * 0x104) >> 8;
            }
            D_800D2460[i].unk06 = t;
            D_800D2460[i].unk0E += D_800BE9E4 * 5;
            D_800D2460[i].unk08 += D_800BE9E4 * 30;
            cs = func_15048A40(D_800D2460[i].unk0E);
            D_800D2460[i].unk00 = ((s32)(cs * D_800D2460[i].unk08) >> 8) + D_800D2460[i].unk04;
            D_800D2460[i].unk0F += D_800BE9E4 * 10;
            break;
        }
        case 3:
            if (D_800D2460[i].unk0A == 0) {
                D_800D2460[i].unk0D = 0;
            }
            break;
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_1508FD38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_150900F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_15090630.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_1509093C.s")

// PERMUTER CANDIDATE (best 7174, all display-list commands byte-correct):
//  (1) IDO rematerializes &D_800D24C8 (lui/%lo) at every field access; target keeps
//      it in saved reg s1 throughout. Neither u8*+cast nor struct-ptr forces promotion.
//  (2) frame size 0xa8 (scratch at 0x90 passed to func_1510D0EC); scratch-array sizing
//      overshoots/undershoots. Both are register-alloc/remat heuristics — permuter needed.
// Gfx *func_150911F4(Gfx *arg0) {
//     StructD24C8 *base = (StructD24C8 *)&D_800D24C8;
//     s32 sp90[6]; s32 t0, t1, t2, t3;
//     if (base->unkBA == 0) return arg0;
//     gSPDisplayList(arg0++, D_80084160);
//     gSPSetGeometryMode(arg0++, 0x400);
//     gSPClearGeometryMode(arg0++, 0x0E0201);
//     gSPClearGeometryMode(arg0++, 0x420000);
//     if (base->unkBA < 0xFF) gSPSegment(arg0++, 8, D_80083440);
//     else                    gSPSegment(arg0++, 8, D_800835C0);
//     func_15043D90(&base->unk00[D_800BE9C0], -1.0f - base->unkA0, -11.0f + base->unkA8,
//                   0.0f, D_8009DD40, D_8009DD40, D_8009DD40, D_8009DD44, 152.0f, D_8009DD48);
//     gSPMatrix(arg0++, &base->unk00[D_800BE9C0], G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_PUSH);
//     gDPSetFogColor(arg0++, 0, 0, 0, 0xFF);
//     gDPSetPrimColor(arg0++, 0xF2, 0, 0, 0, 0, 0);
//     gDPSetEnvColor(arg0++, 0, 0, 0, base->unkBA);
//     gSPSegment(arg0++, 3, &base->unk00[D_800BE9C0]);
//     gSPSegment(arg0++, 1, base->unk84[D_800BE9C0]);
//     t0 = base->unkB0; if (t0) gSPSegment(arg0++, 6, func_1510D0EC(t0,(s32)sp90,3,0));
//     t1 = base->unkB2; if (t1) gSPSegment(arg0++, 7, func_1510D0EC(t1,(s32)sp90,3,0));
//     t2 = base->unkB4; if (t2) gSPSegment(arg0++, 0xA, func_1510D0EC(t2,(s32)sp90,3,0));
//     t3 = base->unkB6; if (t3) gSPSegment(arg0++, 0xB, func_1510D0EC(t3,(s32)sp90,3,0));
//     gSPDisplayList(arg0++, base->unk80);
//     gSPDisplayList(arg0++, D_80084190);
//     return arg0;
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_150911F4.s")

Gfx* func_15091534(Gfx* arg0, struct257 *arg1, u8 *arg2) {
    s32 temp_v0;

    *arg2 = 0;
    temp_v0 = func_1510D0EC((s32)arg1 + (s32)D_D16, 0, 3, 0);

    if (temp_v0 != (s32)0x80000000) {
        gDPSetTextureImage(arg0++, G_IM_FMT_CI, G_IM_SIZ_16b, 1, temp_v0);
        gDPSetTile(arg0++, G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD);
        gDPLoadSync(arg0++);
        gDPLoadBlock(arg0++, G_TX_LOADTILE, 0, 0, 1023, 0);
        gDPPipeSync(arg0++);
        gDPSetTile(arg0++, G_IM_FMT_CI, G_IM_SIZ_4b, 4, 0, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD);
        gDPSetTileSize(arg0++, G_TX_RENDERTILE, 0, 0, 0xFC, 0xFC);
        gDPSetTextureImage(arg0++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, temp_v0 + 0x800);
        gDPLoadSync(arg0++);
        gDPLoadTLUTCmd(arg0++, 6, 15);
        gDPSetOtherMode(arg0++, 0x00AC3F, 0x00504244);

        *arg2 = 1;
    }

    return arg0;
}

// Draws "M:SS:HH" (or "--: --: --" for a negative time). Best honest score 20:
// every instruction and the 0x48 frame size reproduce, but the two spill temps
// land at 0x34/0x3c instead of 0x30/0x38. The target frame has 8 dead bytes
// above the compiler-temp region; only a >=8-byte aggregate local lands there
// (named scalars, block-scoped locals and small arrays all sit *below* the temps
// and push them up; a used array/struct gets scalarised and loses its slot).
//   s32 seconds, minutes, hundredths;
//   if (arg2 >= 0x57030) arg2 = 0x57030;
//   hundredths = ((arg2 % 60) * 100) / 60;
//   if (hundredths >= 100) hundredths = 99;
//   arg0 -= 8;
//   if (arg2 >= 0) {
//       seconds = arg2 / 60;
//       minutes = seconds / 60;
//       func_15042D94((arg0 - ((minutes >= 10) ? 5 : 0)) - 8, arg1, (u8)arg3, &D_8009DCC0, minutes);
//       func_15042D94(arg0, arg1, arg3, &D_8009DCC4, seconds % 60);
//       func_15042D94(arg0 + 0x10, arg1, arg3, &D_8009DCCC, hundredths);
//       return;
//   }
//   func_15042D94(arg0 - 8, arg1, (u8)arg3, &D_8009DCD4);
//   func_15042D94(arg0, arg1, arg3, &D_8009DCD8);
//   func_15042D94(arg0 + 0x10, arg1, arg3, &D_8009DCE0);
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_150916B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_150918EC.s")

void func_15093818(s32 arg0) {
    if ((arg0 != 0) && (D_800D2458 == 0)) {
        D_800D2458 = 1;
        func_15093878();
        return;
    }
    if ((arg0 == 0) && (D_800D2458 != 0)) {
        D_800D2458 = 0;
    }
}

void func_15093878(void) {
    D_800D2448 = func_1518C900(0xBA);
    D_800D244C = allocate_memory(0x80, 1, 1, 0);
}

// Draws the 4-digit countdown timer (segments 4..1 = digit textures) and the
// HUD matrix/display list that renders it.
Gfx *func_150938BC(Gfx *arg0) {
    s32 x = 120;
    s32 y = 129;
    s32 z = -303;
    s32 i;
    s32 val;
    s32 tex;

    val = (D_800D2450 / 30) % 60;
    i = 4;
    do {
        tex = func_1510D0EC((s32)D_11AD + (val % 10), 0, 3, 0);
        if (tex == (s32)0x80000000) {
            return arg0;
        }
        gSPSegment(arg0++, i, tex);
        if (i == 3) {
            val = (D_800D2450 / 30) / 60;
        } else {
            val = val / 10;
        }
        i--;
    } while (i != 0);

    func_150A7D00((D_800BE9C0 << 6) + D_800D244C, x, y, z);
    gSPMatrix(arg0++, (D_800BE9C0 << 6) + D_800D244C, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPDisplayList(arg0++, D_800D2448);
    return arg0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_15093B58.s")
