#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern s16 D_80082FA6;
Gfx *func_1501A680(Gfx *arg0);

typedef struct {
    f32 unk0;
    f32 unk4;
    u8  unk8[0x178];
} View15173D00; // size 0x180, layout of D_800BE628 records

Gfx *func_15173D00(Gfx *gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s16 arg6) {
    Gfx *ret;

    gDPPipeSync(gfx++);
    gDPSetRenderMode(gfx++, 0, 0);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetCycleType(gfx++, G_CYC_COPY);
    gDPSetAlphaCompare(gfx++, G_AC_NONE);
    gDPSetTextureLUT(gfx++, G_TT_NONE);
    gDPSetColorDither(gfx++, G_CD_DISABLE);
    gDPSetAlphaDither(gfx++, G_AD_DISABLE);
    gDPLoadTextureBlock(gfx++, (arg2 * D_800BE620 * 2) + D_800BE9C4, G_IM_FMT_RGBA, G_IM_SIZ_16b, (s32)((View15173D00 *)D_800BE628)[arg6].unk4, 1, 0, 0, 0, 0, 0, 0, 0);
    gDPSetColorImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, arg4);
    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, (s32)((View15173D00 *)D_800BE628)[arg6].unk4, 1);
    gSPTextureRectangle(gfx++, 0, 0, 12, 4, G_TX_RENDERTILE, arg1 << 5, 0, 0x1000, 0x400);
    gDPLoadTextureBlock(gfx++, D_8002AAE8[D_800BE9C0] + (arg2 * D_800BE620 * 2), G_IM_FMT_RGBA, G_IM_SIZ_16b, (s32)((View15173D00 *)D_800BE628)[arg6].unk4, 1, 0, 0, 0, 0, 0, 0, 0);
    gDPSetColorImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, arg5);
    gSPTextureRectangle(gfx++, 0, 0, 12, 4, G_TX_RENDERTILE, arg1 << 5, 0, 0x1000, 0x400);

    ret = (Gfx *)func_1501A490((s32)func_1501A680(gfx), D_80082FA6, 0, 0, 0, 0);
    gDPSetTexturePersp(ret, G_TP_PERSP);
    return ret + 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A11B0/func_151742EC.s")

typedef struct Blk151745F0 {
    s32 unk0[9];
} Blk151745F0;

typedef struct Rec151745F0 {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ char padD[3];
    /* 0x10 */ Blk151745F0 unk10;
    /* 0x34 */ s8 unk34;
    /* 0x35 */ char pad35[3];
    /* 0x38 */ s32 unk38;
} Rec151745F0;

extern Rec151745F0 D_800DD348[3];

s32 func_151745F0(f32 arg0, f32 arg1, f32 arg2, Blk151745F0 *arg3, s8 arg4, s32 arg5) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (D_800DD348[i].unkC == 0) {
            D_800DD348[i].unk0 = arg0;
            D_800DD348[i].unk4 = arg1;
            D_800DD348[i].unkC = 3;
            D_800DD348[i].unk8 = arg2;
            D_800DD348[i].unk34 = arg4;
            D_800DD348[i].unk38 = arg5;
            if (arg3 != NULL) {
                D_800DD348[i].unk10 = *arg3;
            }
            return 0;
        }
    }
    return 1;
}

