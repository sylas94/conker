#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_800D9C10[][4][4];
extern f32 D_800A2C20;
extern f32 D_800D9B28[4][4];
extern s16 D_800DD2F2;
extern s16 D_800DD2F4;
void func_150A7A48(f32 a[4][4], f32 b[4][4], f32 c[4][4]);
void func_1501B22C(s32 arg0);

typedef struct {
    char pad_0[0xC];
    f32 field_0x0C;
    f32 field_0x10;
} D_800BE628View;


void func_1510B070(s32 arg0) {
    D_800BE628View *be628;
    f32 temp_f0;
    f32 temp_f2;

    D_800D9B20 = (f32)D_800DD2F2;
    D_800D9B1C = (f32)D_800DD2F4;
    D_800D3670 = 100.0f - D_800D9B1C;
    be628 = (D_800BE628View *)D_800BE628;
    func_151EF954(
        D_800D9B28,
        -(temp_f0 = be628->field_0x0C),
        temp_f0,
        -(temp_f2 = be628->field_0x10),
        temp_f2,
        1.0f,
        D_800A2C20,
        1.0f);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_138520/func_1510B128.s")

void func_1510B128(s32, f32, f32, f32, f32);

void func_1510B32C(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    func_1510B128(arg0, arg1, arg2, arg3, 0.0f);
    D_800D9AC0[arg0].unk0 = arg3;
    D_800D9AC0[arg0].unk4 = arg1;
    D_800D9AC0[arg0].unk8 = arg2;
    D_800D9AF0 = 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_138520/func_1510B3B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_138520/func_1510B458.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_138520/func_1510B51C.s")

void func_1510B5F8(s32 arg0, u16 *perspNorm, f32 fovy, f32 aspect, f32 near, f32 far, f32 scale) {
    guPerspectiveF((f32 (*)[4])((u8 *)D_800BE628 + arg0 * 0x180 + 0xBC), perspNorm, fovy, aspect, near, far, scale);
    guMtxF2L((f32 (*)[4])((u8 *)D_800BE628 + arg0 * 0x180 + 0xBC), (Mtx *)((u8 *)D_800BE628 + arg0 * 0x180 + D_800BE9C0 * 0x40 + 0x100));
}

void func_1510B690(void) {
    s32 i;
    f32 sp4C[4][4];
    f32 (*d9d10)[4][4];

    d9d10 = (f32 (*)[4][4])D_800D9D10;
    for (i = 0; i <= D_80082FA0; i = (s16)(i + 1)) {
        guMtxL2F(sp4C, (Mtx *)&((struct259 *)D_800BE628)[i].unkB8[(D_800BE9C0 << 6) + 0x48]);
        guMtxL2F(D_800D9C10[i], (Mtx *)(((s32 *)&D_800DC2A0)[D_800BE9C0] + (i << 6)));
        func_150A7A48(D_800D9C10[i], sp4C, d9d10[i]);
        func_1501B22C(i);
    }
}

extern s32 D_800BE628;
extern u8 D_800BE9C0;
extern struct10 *D_800DC2A0;
extern u8 D_80089470;

#define WGFX2(pkt, a, b)            \
{                                   \
    Gfx *_g = (Gfx *)(pkt);         \
    _g->words.w0 = (u32)(a);        \
    _g->words.w1 = (u32)(b);        \
}

Gfx *func_1510B7B4(Gfx *gfx, s32 idx) {
    WGFX2(gfx++, 0xE7000000, 0x00000000);
    WGFX2(gfx++, 0xF9000000, 0x00000001);
    WGFX2(gfx++, 0xDA380003, &D_80089470);
    WGFX2(gfx++, 0xDB0E0000, *(u16 *)((u8 *)((struct259 *)D_800BE628 + idx) + 0xB8));
    WGFX2(gfx++, 0xDB040004, 0x00000003);
    WGFX2(gfx++, 0xDB04000C, 0x00000003);
    WGFX2(gfx++, 0xDB040014, 0x0000FFFD);
    WGFX2(gfx++, 0xDB04001C, 0x0000FFFD);
    WGFX2(gfx++, 0xD9EFFFFF, 0x00000000);
    WGFX2(gfx++, 0xDA380007, (u8 *)&((struct259 *)D_800BE628)[idx].unkB8[(D_800BE9C0 << 6) + 0x48]);
    WGFX2(gfx++, 0xDA380005, ((s32 *)&D_800DC2A0)[D_800BE9C0] + (idx << 6));
    WGFX2(gfx++, 0xEF082C3F, 0x00552230);
    return gfx;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_138520/func_1510B958.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_138520/func_1510B9D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_138520/func_1510BF60.s")

typedef struct {
    /* 0x00 */ s16 tc0;
    /* 0x02 */ s16 tc1;
} UvWobbleSrc;

typedef struct {
    /* 0x00 */ UvWobbleSrc *unk00;
    /* 0x04 */ UvWobbleSrc *unk04;
    /* 0x08 */ u8 unk08;
    /* 0x09 */ u8 unk09;
    /* 0x0A */ u8 unk0A;
    /* 0x0B */ u8 unk0B;
    /* 0x0C */ u8 unk0C;
    /* 0x0D */ u8 unk0D;
    /* 0x0E */ u16 unk0E;
    /* 0x10 */ u16 unk10;
    /* 0x12 */ u16 unk12;
} UvWobble;

extern UvWobble *D_800D9E60[];
extern Vtx *D_800B0E10[];
extern Vtx *D_800B0E14;
extern s32 D_800917B8;
extern f32 sinf(f32);
extern f32 cosf(f32);
extern void *allocate_memory(s32, s32, s32, s32);
s32 func_1510BF60(s32 dl, s32 segAddr, Vtx **outVtx, s32 skip);

UvWobble *func_1510C4AC(s32 dl, s32 arg1, s32 arg2, s32 arg3) {
    Vtx *vtx;
    s32 count;
    s32 i;
    UvWobble *wob;

    if (D_800D9E64 > 0) {
        return NULL;
    }

    wob = allocate_memory(0x14, 1, 0, 0);
    if (wob == NULL) {
        return NULL;
    }

    D_800D9E60[D_800D9E64++] = wob;
    wob->unk0C = arg1;
    wob->unk00 = NULL;
    wob->unk04 = NULL;
    wob->unk0E = 0;
    wob->unk10 = arg2;
    wob->unk12 = arg3;

    count = func_1510BF60(D_800B0E00[0], dl, &vtx, 0);
    if (count != 0) {
        wob->unk08 = count;
        wob->unk0A = vtx - D_800B0E10[0];
        wob->unk00 = allocate_memory(count * 4, 1, 0, 0);
        for (i = 0; i < count; i++) {
            wob->unk00[i].tc0 = vtx[i].v.tc[0];
            wob->unk00[i].tc1 = vtx[i].v.tc[1];
        }
    }

    count = func_1510BF60(D_800B0E04, D_800917B8, &vtx, 0);
    if (count != 0) {
        wob->unk09 = count;
        wob->unk0B = vtx - D_800B0E14;
        wob->unk04 = allocate_memory(count * 4, 1, 0, 0);
        for (i = 0; i < count; i++) {
            wob->unk04[i].tc0 = vtx[i].v.tc[0];
            wob->unk04[i].tc1 = vtx[i].v.tc[1];
        }
    }

    return wob;
}

void func_1510C8A8(void) {
    s32 i;
    s32 j;
    UvWobble *wob;
    Vtx *vtx;
    f32 ang;
    s16 offX;
    s16 offY;

    for (i = 0; i < D_800D9E64; i++) {
        wob = D_800D9E60[i];
        if (wob->unk0C == 0) {
            if (wob->unk00 != NULL) {
                f32 sn;
                f32 cs;

                wob->unk0E += wob->unk10 * D_800BE9E4;
                vtx = D_800B0E10[0];
                vtx += wob->unk0A;
                ang = wob->unk0E * 9.587380191e-05f;
                sn = sinf(ang);
                cs = cosf(ang);
                offX = (s16)(s32)(wob->unk12 * sn);
                offY = (s16)(s32)(wob->unk12 * cs);
                for (j = 0; j < wob->unk08; j++) {
                    vtx[j].v.tc[0] = wob->unk00[j].tc0 + offX;
                    vtx[j].v.tc[1] = wob->unk00[j].tc1 + offY;
                }
            }
            if (wob->unk04 != NULL) {
                vtx = D_800B0E10[1];
                vtx += wob->unk0B;
                for (j = 0; j < wob->unk09; j++) {
                    vtx[j].v.tc[0] = wob->unk04[j].tc0 + offX;
                    vtx[j].v.tc[1] = wob->unk04[j].tc1 + offY;
                }
            }
        }
    }
}
