#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ u8  unk8;
    /* 0x09 */ u8  unk9;
    /* 0x0A */ u8  unkA;
    /* 0x0B */ u8  unkB;
    /* 0x0C */ s32 unkC;
} Struct150950D4;

extern s32   D_800DBE80;
extern Mtx   D_80089470;
extern Mtx  *D_800DBEB0;
extern Vtx  *D_800DBE88[];

Gfx *func_1501A680(Gfx *arg0);
Gfx *func_150950D4(Gfx *gfx, Struct150950D4 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);
void func_151102CC(f32 arg0[4][4], f32 arg1, f32 arg2, f32 arg3);
void func_150A7A48(f32 a[4][4], f32 b[4][4], f32 c[4][4]);

Gfx *func_150D1810(Gfx *gfx, s32 arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    f32 spC0[4][4];
    f32 sp80[4][4];
    s32 sp7C;
    s32 sp78;
    Vtx *vtx;
    Struct150950D4 sp64;

    if ((D_800BE9F0 == 0x33) || (D_800BE9F0 == 0x32) || (D_800BE9F0 == 0x3F)) {
        sp7C = -98;
        sp78 = 39;
    } else {
        sp7C = -19;
        sp78 = 101;
    }

    sp64.unk0 = D_800DBE80;
    sp64.unk4 = 4;
    sp64.unk6 = 0x100;
    sp64.unk8 = 0;
    sp64.unk9 = 3;
    sp64.unkA = 0;

    gSPTexture(gfx++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPPipeSync(gfx++);
    gDPSetOtherMode(gfx++, 0x082C0F, 0x0F0A4004);
    gDPSetCombine(gfx++, 0xFFFFFF, 0xFFFCF279);
    gfx = (Gfx *)func_1501A490((s32)gfx, D_80082FA4, 0, 0, 0, 0);
    gfx = func_1501A680(gfx);
    gfx = func_150950D4(gfx, &sp64, 0, 0, 0, 0, 2, 0x100, 0x100, 3);

    func_151102CC(spC0, 0.0f, 0.0f, arg6);
    func_150A7A48(spC0, (f32 (*)[4])((u8 *)((struct259 *)D_800BE628 + D_80082FA4) + 0xBC), sp80);
    guMtxF2L(sp80, &D_800DBEB0[(D_80082FA4 * 2) + D_800BE9C0]);

    gSPMatrix(gfx++, &D_800DBEB0[(D_80082FA4 * 2) + D_800BE9C0], G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(gfx++, &D_80089470, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPPerspNormalize(gfx++, *(u16 *)((u8 *)((struct259 *)D_800BE628 + D_80082FA4) + 0xB8));

    vtx = D_800DBE88[(D_80082FA4 * 2) + D_800BE9C0];
    vtx[0].v.tc[1] = vtx[1].v.tc[1] = ((sp7C + 0x100) << 5) + (s32)(arg4 * 81.0f);
    vtx[2].v.tc[1] = vtx[3].v.tc[1] = ((sp78 + 0x1FF) << 5) + (s32)(arg4 * 81.0f);
    gSPVertex(gfx++, vtx, 4, 0);
    gSP2Triangles(gfx++, 0, 1, 2, 0, 0, 2, 3, 0);
    return gfx;
}
