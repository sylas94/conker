#include <ultra64.h>

#include "functions.h"
#include "variables.h"

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

// PERMUTER CANDIDATE (best honest score 1483; the C below is semantically complete
// and reproduces every instruction of the body -- only register colouring in `case 2`
// plus the frame size resist):
//  (1) frame 0x50 vs 0x40: the target reserves SIX local words (0x38..0x4c) but only
//      touches two -- `spawn` at 0x44 (sw/lw) and `rate`'s uninitialised home at 0x3c
//      (lw only).  Mine reserves exactly the two it uses (0x3c/0x38).  The 4 dead words
//      are IDO's compiler-temp region; neither extra named locals nor block-scoped
//      locals nor declaration order moves it (all verified).
//  (2) `case 2` colours `t`/`j` as v1/v0 where the target has v0/v1, which drags
//      `count` off a2 onto a0 and breaks the in-place `unk02 -=`.  Declaration order
//      has no effect either way.
//  (3) `case 0` emits `mul.s $f8,$f6,$f0` where the target has `$f0,$f6`; the
//      identical expression in `case 2` DOES come out as `$f0,$f18`, so it is an FP
//      register-allocation artifact, not operand order (both source orders tested).
//  (4) the loop-end bound compiles to %hi/%lo(D_800D2460+0x60), which is the same
//      address as the target's %hi/%lo(D_800D24C0) -- reloc spelling only.
// Notes for whoever picks this up: the two structural discoveries that took it from
// 9858 to 1483 were (a) indexing D_800D2460[] directly instead of through a pointer
// local -- a pointer local defeats IDO's alias analysis and makes it reload
// D_800BE9E4 after every store in case 2, and (b) declaring the per-case scratch
// ints in block scope.  Also: lvl/rate and the D_800D24C0 countdown/oxygen value are
// each ONE variable in the original (that is what lands `rate` in s7 and frees v1).
// Needs, at the top of the TU:
//   typedef struct { s16 unk00, unk02, unk04, unk06, unk08, unk0A;
//                    u8 unk0C, unk0D, unk0E, unk0F; } StructD2460;   /* 0x10 bytes */
//   extern StructD2460 D_800D2460[6];      /* variables.h has u8 [][16] */
//   extern f32 func_15048A40(u8 arg0);     /* functions.h has it as void */
//   void func_1508F9F4(void);              /* func_1508F0A4 calls it above */
//
// void func_1508F9F4(void) {
//     s32 spawn;
//     s32 rate;
//     s32 air;
//     s32 i;
//     f32 cs;
//
//     air = D_800D24C0;
//     if (air != 0) {
//         air -= D_800BE9E4;
//         if (air < 0) {
//             air = 0;
//         }
//         D_800D24C0 = air;
//     }
//     if (D_800CC2D0[0].in_water != 0) {
//         air = D_800CC2D0[0].unkB2;
//     } else {
//         air = 0;
//     }
//     if (air >= 0x5B) {
//         rate = air / 240;
//         if (rate >= 7) {
//             rate = 6;
//         }
//         rate = 6 - rate;
//         rate = rate * 9;
//         if (rate == 0) {
//             spawn = 0;
//         }
//     } else {
//         spawn = 0;
//     }
//     for (i = 0; i < 6; i++) {
//         if (D_800D2460[i].unk0D == 2) {
//             s32 t;
//             t = D_800D2460[i].unk0A;
//             t -= D_800BE9E4;
//             if (t <= 0) {
//                 t = 6;
//                 D_800D2460[i].unk0D = 3;
//             }
//             D_800D2460[i].unk0A = t;
//         }
//         switch (D_800D2460[i].unk0D) {
//         case 0:
//             if (spawn != 0 && D_800D24C0 == 0) {
//                 D_800D24C0 = 10;
//                 D_800D2460[i].unk0D = 1;
//                 D_800D2460[i].unk00 = 0xFC;
//                 D_800D2460[i].unk02 = 0x60;
//                 D_800D2460[i].unk06 = 0;
//                 D_800D2460[i].unk0C = 0;
//                 D_800D2460[i].unk0E = func_150ADA20();
//                 D_800D2460[i].unk08 = 0x500;
//                 cs = func_15048A40(D_800D2460[i].unk0E);
//                 D_800D2460[i].unk0F = 0;
//                 D_800D2460[i].unk0A = rate;
//                 D_800D2460[i].unk04 = 0xFC - ((s32)(cs * D_800D2460[i].unk08) >> 8);
//             }
//             break;
//         case 1: {
//             s32 t;
//             t = D_800D2460[i].unk06;
//             t += D_800BE9E4 * 200;
//             if (t >= 0x666) {
//                 D_800D2460[i].unk0D = 2;
//                 t = 0x666;
//             }
//             D_800D2460[i].unk06 = t;
//             break;
//         }
//         case 2: {
//             s32 t;
//             s32 j;
//             u8 count;
//             count = D_800D2460[i].unk0C;
//             if (count < 0x20) {
//                 t = count;
//                 t += D_800BE9E4;
//                 if (t > 0x20) {
//                     t = 0x20;
//                 }
//                 D_800D2460[i].unk0C = t;
//                 count = t;
//             }
//             D_800D2460[i].unk02 -= (D_800BE9E4 * count) >> 4;
//             t = D_800D2460[i].unk06;
//             for (j = 0; j < D_800BE9E4; j++) {
//                 t = (t * 0x104) >> 8;
//             }
//             D_800D2460[i].unk06 = t;
//             D_800D2460[i].unk0E += D_800BE9E4 * 5;
//             D_800D2460[i].unk08 += D_800BE9E4 * 30;
//             cs = func_15048A40(D_800D2460[i].unk0E);
//             D_800D2460[i].unk0F += D_800BE9E4 * 10;
//             D_800D2460[i].unk00 = ((s32)(cs * D_800D2460[i].unk08) >> 8) + D_800D2460[i].unk04;
//             break;
//         }
//         case 3:
//             if (D_800D2460[i].unk0A == 0) {
//                 D_800D2460[i].unk0D = 0;
//             }
//             break;
//         }
//     }
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_1508F9F4.s")
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
