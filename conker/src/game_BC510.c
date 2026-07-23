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

void func_150916B4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    volatile s32 pad[2];
    s32 seconds;
    s32 hundredths;

    if (arg2 >= 0x57030) {
        arg2 = 0x57030;
    }

    hundredths = ((arg2 % 60) * 100) / 60;
    if (hundredths >= 100) {
        hundredths = 99;
    }

    arg0 -= 8;
    if (arg2 >= 0) {
        seconds = arg2 / 60;
        func_15042D94((arg0 - (((seconds / 60) >= 10) ? 5 : 0)) - 8, arg1, (u8)arg3, &D_8009DCC0, seconds / 60);
        func_15042D94(arg0, arg1, arg3, &D_8009DCC4, seconds % 60);
        func_15042D94(arg0 + 0x10, arg1, arg3, &D_8009DCCC, hundredths);
        return;
    }

    func_15042D94(arg0 - 8, arg1, (u8)arg3, &D_8009DCD4);
    func_15042D94(arg0, arg1, arg3, &D_8009DCD8);
    func_15042D94(arg0 + 0x10, arg1, arg3, &D_8009DCE0);
}
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

// PERMUTER CANDIDATE (best 2014, logic byte-correct — all ops match):
//  (1) saved-reg rotation: target s4=&D_11AD, s5=&D_800D2450, s6=30, s7=60;
//      IDO gives s4=&D_800D2450, s5=30, s6=60, s7=&D_11AD (first-use order).
//  (2) float args: target does runtime `li; mtc1; cvt.s.w` on 120/129/-303;
//      IDO folds (f32)const / 120.0f / bare-int to immediate float bits (lui/ori).
// Gfx *func_150938BC(Gfx *arg0) {
//     s32 i, val, tex;
//     val = (D_800D2450 / 30) % 60;
//     i = 4;
//     do {
//         tex = func_1510D0EC((s32)&D_11AD[val % 10], 0, 3, 0);
//         if (tex == (s32)0x80000000) return arg0;
//         gSPSegment(arg0++, i, tex);
//         if (i == 3) val = (D_800D2450 / 30) / 60; else val = val / 10;
//         i--;
//     } while (i != 0);
//     func_150A7D00((D_800BE9C0 << 6) + D_800D244C, 120.0f, 129.0f, -303.0f);
//     gSPMatrix(arg0++, (D_800BE9C0 << 6) + D_800D244C, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_PUSH);
//     gSPDisplayList(arg0++, D_800D2448);
//     return arg0;
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_150938BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_15093B58.s")
