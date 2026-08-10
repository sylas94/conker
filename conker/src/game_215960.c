#include <ultra64.h>
#define func_1502B7F0 func_1502B7F0_5
#include "functions.h"
#undef func_1502B7F0
#include "variables.h"

extern s32 D_800E0A74;
extern u8 D_800E0B96;
extern u8 D_800E0B97;
extern Gfx D_80090028;
extern u8 D_800917F8;
extern u8 D_80091804;
extern u8 D_80091810;
extern s32 (*D_8008FFF4[])(s32);
extern s32 D_80000300;
extern u8 D_800BE616;
extern u8 D_800BE740;
extern s8 D_8008FD90;
extern s8 D_800E0BD3;
extern s32 *D_800E0BD8;
extern u8 D_7FB;
extern u8 D_887;
extern u8 D_800E0A94;
extern u8 D_800E0C85;
extern s32 D_8009013C;
extern s32 func_1510D0EC(s32, s32, s32, s32);
extern s32 func_1502B7F0(s32 *, s32, s32);
extern void func_10004074(void *);
Gfx *func_151ED1E0(Gfx *);
void func_15042D94();
Gfx *func_151ED430(Gfx *, void *, s32, s32, s32, s32, f32, s32);
Gfx *func_15096934(Gfx *);
Gfx *func_1501A6CC(Gfx *arg0, s32 a, s32 b, s32 c, s32 d);

s32 func_151E84B0(s32 arg0) {
    s32 tmp;

    D_8003C8E0 = 0x9000001;
    tmp = 0;
    arg0 = func_151ED1E0(arg0);
    if (D_8008FFF4[D_800E0B94] != 0) {
        arg0 = D_8008FFF4[D_800E0B94](arg0);
    }

    if (D_80000300 != 0) {
        if ((D_800BE616 != 0) && (D_8008FD90 >= 2)) {
            if ((D_800BE740 & 0xF) == 0) {
                if (D_800E0BD3 == 1) {
                    tmp = 0x33;
                } else if (D_800E0BD3 == 2) {
                    tmp = 0x16;
                }
            }
        } else {
            if ((D_800BE740 & 1) == 0) {
                if (D_800E0BD3 == 1) {
                    tmp = 0x32;
                } else if (D_800E0BD3 == 2) {
                    tmp = 0x15;
                }
            }
        }
    }

    if (tmp != 0) {
        func_1504332C(0xFF, 0xFF, 0xFF, 0xFF);
        func_15042D94(0x94, 0xC8, 0x81, D_800E0BD8[tmp]);
    }

    D_8003C8E0 = 0;
    return arg0;
}

extern u8 D_800E0B94;
extern s32 (*D_8008FFC0[])(s32);
extern s32 D_8003C8E0;
extern s32 D_80090058;
extern s16 D_800E0C78;
extern u8 D_800BE9C0;
extern s32 D_800BE9C8[];
extern s32 D_800BEBA4;

s32 func_151E8620(s32 arg0) {
    s32 cond;
    s32 orig;
    s32 idx;

    idx = D_800E0B94;
    orig = arg0;
    D_8003C8E0 = 0x9000000;
    if (D_8008FFC0[idx] != 0) {
        arg0 = D_8008FFC0[idx](arg0);
    }
    if (D_800E0B94 != 0) {
        D_80090058 = 0;
        D_800E0C78 = 0;
    }
    D_8003C8E0 = 0;
    if (((arg0 - D_800BE9C8[D_800BE9C0]) >> 3) > D_800BEBA4) {
        cond = 1;
    } else {
        cond = 0;
    }
    if (cond) {
        return orig;
    }
    return arg0;
}

extern f32 D_8008FE1C;
extern f32 D_8008FE20;
Gfx *func_151E86E4(Gfx *gfx, s32 xl, s32 yl, s32 xh, s32 yh, s32 tile, s32 s, s32 t, s32 dsdx, s32 dtdy)
{
  f32 yScale;
  s16 xlTemp;
  if (D_8008FE1C != 1.0f)
  {
    xl = (s32) (((f32) xl) * D_8008FE1C);
    yScale = D_8008FE20;
    xh = (s32) (((f32) xh) * D_8008FE1C);
    yl = (s32) (((f32) yl) * yScale);
    yh = (s32) (((f32) yh) * yScale);
    dsdx = (s32) (((f32) dsdx) / D_8008FE1C);
    dtdy = (s32) (((f32) dtdy) / D_8008FE20);
  }
 { Gfx *_g = (Gfx *) (gfx++); _g->words.w0 = (((unsigned int) ((((unsigned int) 0xe4) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) ((((s16) xh) > 0) ? ((s16) xh) : (0))) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) ((((s16) yh) > 0) ? ((s16) yh) : (0))) & ((0x01 << 12) - 1)) << 0)); _g->words.w1 = (((unsigned int) ((((unsigned int) tile) & ((0x01 << 3) - 1)) << 24)) | ((unsigned int) ((((unsigned int) ((((s16) xl) > 0) ? ((s16) xl) : (0))) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) ((((s16) yl) > 0) ? ((s16) yl) : (0))) & ((0x01 << 12) - 1)) << 0)); { Gfx *_g = (Gfx *) (gfx++); _g->words.w0 = (unsigned int) ((((unsigned int) 0xe1) & ((0x01 << 8) - 1)) << 24); _g->words.w1 = (unsigned int) (((unsigned int) ((((unsigned int) (s - ((((s16) xl) < 0) ? ((((s16) dsdx) < 0) ? ((((((s16) xl) * ((s16) dsdx)) >> 7) > 0) ? ((((s16) xl) * ((s16) dsdx)) >> 7) : (0)) : ((((((s16) xl) * ((s16) dsdx)) >> 7) < 0) ? (((xlTemp = (s16) xl) * ((s16) dsdx)) >> 7) : (0))) : (0)))) & ((0x01 << 16) - 1)) << 16)) | ((unsigned int) ((((unsigned int) (t - ((yl < 0) ? ((((s16) dtdy) < 0) ? ((((((s16) yl) * ((s16) dtdy)) >> 7) > 0) ? ((((s16) yl) * ((s16) dtdy)) >> 7) : (0)) : ((((((s16) yl) * ((s16) dtdy)) >> 7) < 0) ? ((((s16) yl) * ((s16) dtdy)) >> 7) : (0))) : (0)))) & ((0x01 << 16) - 1)) << 0))); } ; { Gfx *_g = (Gfx *) (gfx++); _g->words.w0 = (unsigned int) ((((unsigned int) 0xf1) & ((0x01 << 8) - 1)) << 24); _g->words.w1 = (unsigned int) (((unsigned int) ((((unsigned int) dsdx) & ((0x01 << 16) - 1)) << 16)) | ((unsigned int) ((((unsigned int) dtdy) & ((0x01 << 16) - 1)) << 0))); }
    ;
  }
  ;
  return gfx;
}


#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151E89A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151E966C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151E9D18.s")

typedef struct {
    /* 0x00 */ char pad0[0x42];
    /* 0x42 */ s8 unk42;
    /* 0x43 */ char pad43[3];
    /* 0x46 */ s16 unk46[4];
    /* 0x4E */ char pad4E[0x18];
    /* 0x66 */ struct {
        /* 0x00 */ s16 unk0;
        /* 0x02 */ s16 unk2;
        /* 0x04 */ s16 unk4;
        /* 0x06 */ s16 unk6;
        /* 0x08 */ s16 unk8;
        /* 0x0A */ s16 unkA;
    } rec[4];
} ScoreState;

typedef struct {
    /* 0x000 */ char pad0[0x1AA];
    /* 0x1AA */ s16 unk1AA;
} ScoreActor;

extern ScoreState *D_8008FDD4;
extern ScoreActor *D_800CC5EC[];
extern u16 D_8008FDC0;
extern s8 D_8008FDC8;
extern s8 D_8008FD7C;
extern s8 D_8008FE44[];
extern s8 D_800E0C00[];
extern s8 D_800E0AC0[];
extern s16 D_800E0AA0[];
extern s16 D_800E0AD0[];
extern u8 D_800ABA90[][4];
extern u8 D_800ABAA8;
extern u8 D_800ABAAC;
extern u8 D_800ABAB0;
extern u8 D_800ABAB8;
extern u8 D_800ABABC;
extern u8 D_800ABAC0;
extern u8 D_800ABAC4;
extern u8 D_843;
extern u8 D_888;
Gfx *func_151E9D18(Gfx *, s32, s32);
Gfx *func_151E966C(Gfx *, s32, s32, s8, s32);

Gfx *func_151EA15C(Gfx *gfx, s32 arg1, s32 arg2, s32 arg3) {
    s32 image;
    s32 y;
    s32 i;
    s32 c;
    s32 v;
    s32 xbase;
    s32 x;
    s32 yq;
    s32 strBase;
    s32 yq2;
    s32 pct;
    s32 total;
    s32 sIdx;
    s8 flagA;
    s8 flagB;
    s8 flagC;

    if ((D_8008FDD4->unk42 == 0xB) || (D_8008FDD4->unk42 == 0xC)) {
        if (arg3 != 0) {
            return gfx;
        }
        gDPPipeSync(gfx++);
        gDPSetEnvColor(gfx++, 0xFF, 0xFF, 0xFF, arg2);
        gDPSetCombine(gfx++, 0x12D225, 0xFFA7FFFF);
        image = func_1510D0EC(&D_843, 0, 3, 0);
        if (image == (s32)0x80000000) {
            return gfx;
        }
        gDPSetTextureImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 1, image);
        gDPSetTile(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 5, 0, G_TX_CLAMP, 5, 0);
        gDPLoadSync(gfx++);
        gDPLoadBlock(gfx++, G_TX_LOADTILE, 0, 0, 0x3FF, 0);
        gDPPipeSync(gfx++);
        gDPSetTile(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, 0, G_TX_CLAMP, 5, 0);
        gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, 0, 0x7C, 0x7C);
        gDPSetOtherMode(gfx++, 0x002C3F, 0x504244);
        y = 0x48;
        for (i = 0; i < 4; i++) {
            if (D_8008FE44[i] >= 0) {
                v = D_8008FE44[i] & 3;
                gfx = func_151E86E4(gfx, 0x120, (y - 2) << 2, 0x160, (y + 0xE) << 2, 0,
                                    (v & 1) << 9, (v >> 1) << 9, 0x400, 0x400);
                y += 0x12;
            }
        }
        return gfx;
    }

    y = arg1;
    if (D_8008FDC0 & 1) {
        xbase = 0x1A;
    } else {
        xbase = 0x34;
    }
    if (D_800E0B94 != 0) {
        if (D_8008FDC8 != 0) {
            y = arg1 - 0x28;
        }
    }
    func_1504332C(0xFF, 0xFF, 0xFF, arg2);
    if (D_800E0BD3 == 2) {
        strBase = 9;
        flagC = 1;
    } else {
        strBase = 0x5E;
        flagC = 0;
    }
    if (D_8008FDD4->unk42 == 8) {
        flagA = 0;
    } else {
        flagA = 1;
    }
    gDPPipeSync(gfx++);
    gDPSetEnvColor(gfx++, 0xFF, 0xFF, 0xFF, arg2);
    gDPSetCombine(gfx++, 0x12D225, 0xFFA7FFFF);
    flagB = 0;
    for (i = 0; i < 4; i++) {
        if (D_8008FE44[i] < 0) {
            continue;
        }
        if (D_80087270[i] == 0xA) {
            continue;
        }
        c = D_800E0C00[i];
        if ((c != 0) || ((c == 0) && (flagA != 0))) {
            if (flagB == 0) {
                image = func_1510D0EC(&D_887, 0, 3, 0);
                if (image == (s32)0x80000000) {
                    return gfx;
                }
                gDPSetTextureImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 1, image);
                gDPSetTile(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 5, 0, G_TX_CLAMP, 5, 0);
                gDPLoadSync(gfx++);
                gDPLoadBlock(gfx++, G_TX_LOADTILE, 0, 0, 0x3FF, 0);
                gDPPipeSync(gfx++);
                gDPSetTile(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, 0, G_TX_CLAMP, 5, 0);
                gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, 0, 0x7C, 0x7C);
                gDPSetOtherMode(gfx++, 0x000C3F, 0x504244);
                x = (xbase - 0x28) << 2;
                if (D_8008FDC0 & 1) {
                    yq = (y - 0x11) << 2;
                    gfx = func_151E86E4(gfx, x + 0x1D4, yq, x + 0x214, yq + 0x40, 0, 0x200, 0, 0x400, 0x400);
                    x += 0x78;
                }
                yq = (y - 0x11) << 2;
                x += 0x1D4;
                if (D_8008FDD4->unk42 == 1) {
                    x -= 0x78;
                }
                gfx = func_151E86E4(gfx, x + 0x164, yq, x + 0x1A4, yq + 0x3C, 0, 0, 0x200, 0x400, 0x400);
                if (D_8008FDD4->unk42 == 1) {
                    x += 0x78;
                }
                gDPPipeSync(gfx++);
                image = func_1510D0EC(&D_888, 0, 3, 0);
                if (image == (s32)0x80000000) {
                    return gfx;
                }
                gDPSetTextureImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 1, image);
                gDPSetTile(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 5, 0, G_TX_CLAMP, 5, 0);
                gDPLoadSync(gfx++);
                gDPLoadBlock(gfx++, G_TX_LOADTILE, 0, 0, 0x3FF, 0);
                gDPPipeSync(gfx++);
                gDPSetTile(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, 0, G_TX_CLAMP, 5, 0);
                gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, 0, 0x7C, 0x7C);
                yq2 = yq + 0x40;
                gfx = func_151E86E4(gfx, x, yq, x + 0x40, yq2, 0, 0x200, 0, 0x400, 0x400);
                x += 0x74;
                gfx = func_151E86E4(gfx, x, yq, x + 0x40, yq2, 0, 0, 0, 0x400, 0x400);
                if (D_8008FDD4->unk42 != 1) {
                    x += 0x4C;
                    gfx = func_151E86E4(gfx, x, yq, x + 0x80, yq2, 0, 0, 0x200, 0x400, 0x400);
                }
                gDPPipeSync(gfx++);
                image = func_1510D0EC(&D_843, 0, 3, 0);
                if (image == (s32)0x80000000) {
                    return gfx;
                }
                gDPSetTextureImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 1, image);
                gDPSetTile(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 5, 0, G_TX_CLAMP, 5, 0);
                gDPLoadSync(gfx++);
                gDPLoadBlock(gfx++, G_TX_LOADTILE, 0, 0, 0x3FF, 0);
                gDPPipeSync(gfx++);
                gDPSetTile(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, 0, G_TX_CLAMP, 5, 0);
                gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, 0, 0x7C, 0x7C);
                gDPSetOtherMode(gfx++, 0x002C3F, 0x504244);
                flagB = 1;
            }
            func_1504332C(D_800ABA90[c][0], D_800ABA90[c][1], D_800ABA90[c][2], arg2);
            pct = 0;
            v = D_8008FE44[i] & 3;
            gfx = func_151E86E4(gfx, (xbase + 8) << 2, (y - 2) << 2, (xbase + 0x18) << 2, (y + 0xE) << 2, 0,
                                (v & 1) << 9, (v >> 1) << 9, 0x400, 0x400);
            if (arg3 != 0) {
                total = ((ScoreActor *)*(s32 *)((u8 *)D_800CC5EC + (i * 0x32C)))->unk1AA;
            } else {
                total = D_8008FDD4->rec[i].unk6;
            }
            if (total > 0) {
                pct = (D_8008FDD4->rec[i].unk0 * 100) / total;
            }
            if (pct >= 10000) {
                pct = 9999;
            }
            if (D_8008FDC8 != 0) {
                c = i;
            }
            x = xbase;
            sIdx = (s8)(D_800E0AC0[c] - 1);
            if (sIdx < 0) {
                sIdx = 0;
            }
            func_15042D94(x + 0x3C, y, 0x81, &D_800ABAA8, D_800E0BD8[sIdx + strBase]);
            if (D_8008FDC0 & 1) {
                func_15042D94(xbase + 0x54, y, 0x81, &D_800ABAAC, D_800E0AA0[c]);
                x = xbase + 0x1E;
            }
            x += 0x58;
            func_15042D94(x, y, 0x81, &D_800ABAB0, pct);
            x += 0x1A;
            func_15042D94(x, y, 0x81, &D_800ABAB8, D_8008FDD4->unk46[i]);
            x += 0x1E;
            if (D_8008FDD4->unk42 != 1) {
                if ((D_80087270[i] == 9) || ((i == 0) && (D_8008FD7C == 9))) {
                    func_15042D94(x, y, 0x81, &D_800ABABC);
                } else {
                    func_15042D94(x, y, 0x81, &D_800ABAC0, D_8008FDD4->rec[i].unk4);
                }
                x += 0x1E;
            }
            func_15042D94(x, y, 0x81, &D_800ABAC4, D_800E0AD0[i]);
            y += 0xF;
        }
    }
    if (D_8008FDC0 & 0x6340) {
        gSPDisplayList(gfx++, &D_80090028);
        gDPSetCombine(gfx++, 0x12FE25, 0xFFFFF3F9);
        gfx = func_151E9D18(gfx, 0x320, flagC);
    }
    if (arg3 != 0) {
        if (D_8008FDC0 & 1) {
            gfx = func_151E966C(gfx, 0x320, -1, 1, flagC);
        }
    }
    return gfx;
}

typedef struct {
    /* 0x00 */ s32 v[7];
} PlaceValueTable;

extern void *D_80090074[];
extern PlaceValueTable D_8009009C;

Gfx *func_151EADFC(Gfx *gfx, s32 x, s32 y, s32 value) {
    s32 i;
    s32 digit;
    s32 started;
    s32 image;
    PlaceValueTable places;

    places = D_8009009C;

    x <<= 2; y <<= 2;
    if (value >= 10000000) {
        value = 9999999;
    }
    started = 0;
    if (value < 0) {
        value = 0;
    }

    for (i = 6; i >= 0; i--) {
        digit = value / places.v[i];
        value = value % places.v[i];
        if ((digit > 0) || started || (i == 0)) {
            image = func_1510D0EC(D_80090074[digit], 0, 3, 0);
            started = 1;
            if (image != (s32)0x80000000) {
                gDPSetTextureImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 1, image);
                gDPSetTile(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 5, 0, G_TX_CLAMP, 5, 0);
                gDPLoadSync(gfx++);
                gDPLoadBlock(gfx++, G_TX_LOADTILE, 0, 0, 0x3FF, 0);
                gDPPipeSync(gfx++);
                gDPSetTile(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, 0, G_TX_CLAMP, 5, 0);
                gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, 0, 0x7C, 0x7C);
                gfx = func_151E86E4(gfx, x, y, x + 0x80, y + 0x80, 0, 0, 0, 0x400, 0x400);
            }
            x += 0x60;
        }
    }

    return gfx;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EB06C.s")

extern s16 D_8008FDCC;
Gfx *func_151EA15C(Gfx *, s32, s32, s32);

s32 func_151EB930(s32 arg0) {
    if (D_8008FDCC != 0) {
        arg0 = (s32)func_151EA15C((Gfx *)arg0, 0x6A, D_8008FDCC, 0);
    }
    return arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EB96C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EBB50.s")

extern s32 D_800E0A90;
extern s32 *D_800E0BD8;
void func_15042D94();

s32 func_151EC178(s32 arg0) {
    s32 temp;
    if (D_800E0A90 >= 0x5DD) {
        temp = (D_800E0A90 - 0x5DC) << 3;
        if (temp >= 0x100) {
            temp = 0xFF;
        }
        func_1504332C(0xFF, 0xFF, 0xFF, temp);
        func_15042D94(0xDC, 0x130, 1, D_800E0BD8[0x1D0 / 4]);
    }
    return arg0;
}

Gfx *func_151EC1F0(Gfx *gfx) {
    s32 alpha;
    s32 temp;

    if (D_800BE9F0 == 0x21) {
        return gfx;
    }

    gSPDisplayList(gfx++, &D_80090028);
    temp = D_800E0A90;
    alpha = temp;
    if (alpha >= 0x12D) {
        temp = 0x1AC;
        alpha = temp - alpha;
        alpha <<= 1;
        if (alpha < 0) {
            alpha = 0;
        }
    } else {
        alpha = temp << 3;
        if (alpha >= 0x100) {
            alpha = 0xFF;
        }
    }

    if (alpha != 0) {
        gDPSetEnvColor(gfx++, 0xFF, 0xFF, 0xFF, alpha);
        gfx = func_151ED430(gfx, &D_800917F8, 0x92, 0x63, 5, 6, 1.0f, 0);
    }

    gDPSetEnvColor(gfx++, 0xFF, 0xFF, 0xFF, 0xFF);
    gfx = func_151ED430(gfx, &D_80091804, 0x92, 0xCB, 5, 2, 1.0f, 0);
    gDPSetCombine(gfx++, 0xFFD3FF, 0xFFA6FF7F);
    gDPSetEnvColor(gfx++, 0x20, 0xFF, 0x20, D_800E0B97);
    gfx = func_151ED430(gfx, &D_80091810, 0x92, 0xCB, 5, 2, 1.0f, 0);
    gfx = func_15096934(gfx);

    alpha = 0x1EA - D_800E0A74;
    if (alpha < 0) {
        alpha = 0;
    } else {
        alpha <<= 4;
        if (alpha >= 0x100) {
            alpha = 0xFF;
        }
    }
    alpha = 0xFF - alpha;
    D_800E0B96 = alpha;
    return gfx;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EC3E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EC648.s")

extern u8 D_800E0B97;
extern Gfx D_80090028;
extern u8 D_8009181C;
extern u8 D_80091828;
Gfx *func_151ED430(Gfx *, void *, s32, s32, s32, s32, f32, s32);
Gfx *func_15096934(Gfx *);

Gfx *func_151ED09C(Gfx *gfx) {
    s32 alpha;

    gSPDisplayList(gfx++, &D_80090028);
    alpha = D_800E0A90 << 2;
    if (alpha >= 0x100) {
        alpha = 0xFF;
    }
    gDPSetEnvColor(gfx++, 0xFF, 0xFF, 0xFF, alpha);
    gfx = func_151ED430(gfx, &D_8009181C, 0x92, 0x6C, 8, 3, 1.0f, 0);
    gDPPipeSync(gfx++);
    gDPSetCombine(gfx++, 0xFFD3FF, 0xFFA6FF7F);
    gDPSetEnvColor(gfx++, 0xFF, 0x80, 0x20, (D_800E0B97 * (alpha + 1)) >> 8);
    gfx = func_151ED430(gfx, &D_80091828, 0x92, 0x6C, 8, 3, 1.0f, 0);
    return func_15096934(gfx);
}

Gfx *func_151ED1E0(Gfx *gfx) {
    if (D_800E0B96 == 0) {
        return gfx;
    }
    gDPPipeSync(gfx++);
    gDPSetOtherMode(gfx++, 0x082C3F, 0x504340);
    gDPSetCombine(gfx++, 0xFFFFFF, 0xFFFEFB7D);
    gDPSetEnvColor(gfx++, 0, 0, 0, D_800E0B96);
    return func_1501A6CC(gfx, 0, 0, D_800BE620, D_800BE624);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151ED29C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151ED430.s")

typedef struct {
    /* 0x00 */ Gfx **unk0;
    /* 0x04 */ Gfx *unk4[4];
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u8 unk16[6];
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ f32 unk28[2][4][4];
} GameStruct151ED90C;

extern void *allocate_memory(s32, s32, s32, s32);
extern s32 func_1503F62C(s32, s32, void *, void *, void *, void *, void *);
extern void func_1503F5B8(s32, s32, s32, f32, f32, s32);

GameStruct151ED90C *func_151ED90C(s32 arg0, s32 arg1, s32 arg2, f32 arg3) {
    GameStruct151ED90C *obj;
    f32 (*mtx1)[4];
    f32 (*mtx2)[4];
    Gfx *dst;
    Gfx *src;
    s32 cmd;
    s32 size;
    s32 i;

    obj = allocate_memory(sizeof(GameStruct151ED90C), 1, 0, 1);
    if (obj == NULL) {
        return NULL;
    }
    obj->unk15 = 1;
    if (func_1503F62C(arg0, arg1, obj, &obj->unk14, &obj->unk1C, &obj->unk20, &obj->unk24) != 0) {
        func_10004074(obj);
        return NULL;
    }

    mtx1 = obj->unk28[0];
    guMtxIdentF(mtx1);
    mtx2 = obj->unk28[1];
    guMtxIdentF(mtx2);
    *(f32 (**)[4])(obj->unk24 + 0x3E0) = mtx1;
    *(f32 (**)[4])(obj->unk24 + 0x3E4) = mtx2;
    func_1503F5B8(obj->unk24, 1, arg2, arg3, 0.0f, 0);

    for (i = 0; i < obj->unk14; i++) {
        src = obj->unk0[i];
        size = 0;
        do {
            cmd = (src->words.w0 >> 24) & 0xFF;
            src++;
            size += 8;
        } while (cmd != 0xDF);

        dst = allocate_memory(size, 1, 1, 1);
        obj->unk4[i] = dst;
        if (dst == NULL) {
            for (size = 0; size < i; size++) {
                func_10004074(obj->unk4[size]);
            }
            func_10004074(obj);
            return NULL;
        }
    }

    for (i = 0; i < obj->unk14; i++) {
        dst = obj->unk4[i];
        src = obj->unk0[i];
        do {
            dst->words.w0 = src->words.w0;
            dst->words.w1 = src->words.w1;
            src++;
            cmd = (dst->words.w0 >> 24) & 0xFF;
            if (cmd == 0xEF) {
                dst->words.w0 &= 0xFFFEFFFF;
                dst->words.w1 = 0x5041C8;
            }
            if (cmd == 0xFC) {
                dst->words.w0 = 0;
            }
            dst++;
        } while (cmd != 0xDF);
    }

    return obj;
}

typedef struct {
    s32 unk0;
    s32 *unk4[4];
    u8 unk14;
    u8 pad15[0xF];
    s32 unk24;
} GameStruct151EDB58;

extern void func_1503F7B8(s32);

void func_151EDB58(GameStruct151EDB58 *arg0) {
    s32 i;

    if (arg0 != 0) {
        func_1503F7B8(arg0->unk24);
        func_100043B4((s32 *)arg0, 4);
        for (i = 0; i < arg0->unk14; i++) {
            func_100043B4(arg0->unk4[i], 4);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EDBDC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EDF4C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EE184.s")

Gfx *func_151EEBE8(Gfx *gfx, s32 arg1) {
    s32 image;

    gDPPipeSync(gfx++);
    gDPSetEnvColor(gfx++, 0xFF, 0xFF, 0xFF, D_800E0A94);
    image = func_1510D0EC(&D_7FB, 0, 3, 0);
    if (image != (s32)0x80000000) {
        gDPSetTextureImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, image);
        gDPSetTile(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR, 5, 0, G_TX_CLAMP, 6, 0);
        gDPLoadSync(gfx++);
        gDPLoadBlock(gfx++, G_TX_LOADTILE, 0, 0, 0x5FF, 0);
        gDPPipeSync(gfx++);
        gDPSetTile(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 12, 0, G_TX_RENDERTILE, 0, G_TX_MIRROR, 5, 0, G_TX_CLAMP, 6, 0);
        gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, 0, 0xBC, 0x7C);
        gDPSetOtherMode(gfx++, 0x002C3F, 0x504244);
        gfx = func_151E86E4(gfx, 0x190, 0x100, 0x250, 0x200, 0, 0, 0, 0x400, 0x400);
        gfx = func_151E86E4(gfx, 0x250, 0x100, 0x310, 0x200, 0, 0x5E0, 0, -0x400, 0x400);
    }

    gDPPipeSync(gfx++);
    image = func_1510D0EC(&D_887, 0, 3, 0);
    if (image != (s32)0x80000000) {
        gDPSetTextureImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 1, image);
        gDPSetTile(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 5, 0, G_TX_CLAMP, 5, 0);
        gDPLoadSync(gfx++);
        gDPLoadBlock(gfx++, G_TX_LOADTILE, 0, 0, 0x3FF, 0);
        gDPPipeSync(gfx++);
        gDPSetTile(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, 0, G_TX_CLAMP, 5, 0);
        gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, 0, 0x7C, 0x7C);
        gfx = func_151E86E4(gfx, 0x250, 0xBC, 0x290, 0xFC, 0, 0, 0, 0x400, 0x400);
        gfx = func_151E86E4(gfx, 0x180, 0xBC, 0x1D0, 0xFC, 0, 0x200, 0x200, 0x400, 0x400);
    }

    {
        s32 sp48;

        {
            u32 count;

            if (D_800E0C85 != (arg1 + 1)) {
                sp48 = 0;
                count = func_1502B7F0(&sp48, 1, 0x1D);
                if ((u32)arg1 < (u32)(count >> 1)) {
                    D_8009013C = ((u16 *)sp48)[arg1];
                } else {
                    D_8009013C = 0;
                }
                func_10004074((void *)sp48);
                D_800E0C85 = arg1 + 1;
            }
        }
    }

    if (D_8009013C != 0) {
        gDPPipeSync(gfx++);
        gfx = func_151ED430(gfx, &D_8009013C, 0x94, 0x60, 1, 2, 1.0f, 0);
    }
    return gfx;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EEFF0.s")
