#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern u8 D_80084930;
extern u8 D_800848D0[];
extern u8 D_80085930;
extern u8 D_80085931;
extern u8 D_80085932;
extern u8 D_80085933[];

#define WGFX(pkt, a, b)             \
{                                   \
    Gfx *_g = (Gfx *)(pkt);         \
    _g->words.w0 = (u32)(a);        \
    _g->words.w1 = (u32)(b);        \
}

Gfx *func_150412C0(Gfx *gfx) {
    WGFX(gfx++, 0xD7000002, 0xFFFFFFFF);
    WGFX(gfx++, 0xE7000000, 0x00000000);
    WGFX(gfx++, 0xFCFFFFFF, 0xFFFCF279);
    WGFX(gfx++, 0xEF002C0F, 0x0055204C);
    WGFX(gfx++, 0xFD90003F, &D_80084930);
    WGFX(gfx++, 0xFD900000, &D_80084930);
    WGFX(gfx++, 0xF5900000, 0x07000000);
    WGFX(gfx++, 0xE6000000, 0x00000000);
    WGFX(gfx++, 0xF3000000, 0x077FF200);
    WGFX(gfx++, 0xE7000000, 0x00000000);
    WGFX(gfx++, 0xF5800800, 0x00000000);
    WGFX(gfx++, 0xF2000000, 0x000FC1FC);
    return gfx;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_6E770/func_150413FC.s")

s32 func_15041480(u8 arg0) {
    s32 i;

    for (i = 0; ; ) {
        if (arg0 == D_800848D0[i]) {
            return i;
        }
        if (arg0 == D_800848D0[i + 1]) {
            return i + 1;
        }
        if (arg0 == D_800848D0[i + 2]) {
            return i + 2;
        }
        if (arg0 == D_800848D0[i + 3]) {
            return i + 3;
        }
        i += 4;
        if (i != 0x50) {
            continue;
        }
        break;
    }

    return i;
}

Gfx *func_15041508(Gfx *gfx, s32 arg1, s32 arg2, s32 arg3)
{
  s32 rem;
  rem = arg3 % 8;
 { Gfx *_g = (Gfx *) (gfx++); _g->words.w0 = (((unsigned int) ((((unsigned int) 0xe4) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) ((arg1 + 8) << 2)) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) ((arg2 + 12) << 2)) & ((0x01 << 12) - 1)) << 0)); _g->words.w1 = (((unsigned int) ((((unsigned int) 0) & ((0x01 << 3) - 1)) << 24)) | ((unsigned int) ((((unsigned int) (arg1 << 2)) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) (arg2 << 2)) & ((0x01 << 12) - 1)) << 0)); { Gfx *_g = (Gfx *) (gfx++); _g->words.w0 = (unsigned int) ((((unsigned int) 0xe1) & ((0x01 << 8) - 1)) << 24); _g->words.w1 = (unsigned int) (((unsigned int) ((((unsigned int) ((rem * 8) << 5)) & ((0x01 << 16) - 1)) << 16)) | ((unsigned int) ((((unsigned int) ((((arg3 - rem) / 8) * 0x180) & 0xFFFFu)) & ((0x01 << 16) - 1)) << 0))); } ; { Gfx *_g = (Gfx *) (gfx++); _g->words.w0 = (unsigned int) ((((unsigned int) 0xf1) & ((0x01 << 8) - 1)) << 24); _g->words.w1 = (unsigned int) (((unsigned int) ((((unsigned int) 0x400) & ((0x01 << 16) - 1)) << 16)) | ((unsigned int) ((((unsigned int) 0x400) & ((0x01 << 16) - 1)) << 0))); }
    ;
  }
  ;
  return gfx;
}


#pragma GLOBAL_ASM("asm/nonmatchings/game_6E770/func_150415E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_6E770/func_150417AC.s")

extern u8 (*D_80085994)[4];
extern f32 D_800380A4;

s32 func_15042C40(u8);
void func_150415E0(s32, s32 *, s32 *, f32 *, s32 *, f32 *);

void func_150428D4(u8 *str, s32 *arg1, s32 *arg2, s32 *arg3) {
    u8 *p;
    u8 c;
    s32 glyph;
    s32 lineH;
    s32 maxW;
    s32 flag;
    s32 sp64;
    s32 sp60;
    f32 sp5C;
    s32 sp58;
    f32 sp54;
    s32 temp;

    if (str == NULL) {
        return;
    }

    *arg1 = 0;
    *arg2 = 0;
    *arg3 = 0;
    maxW = 0;
    lineH = 0;
    glyph = 0;
    if (str[0] == 0) {
        *arg2 += 0xC;
    }
    p = &str[glyph];
    if (str[0] != 0) {
        c = *p;
        do {
            if (c == 0xBC) {
                p += 2;
            } else {
                glyph = func_15042C40(c) & 0xFF;
                flag = 0;
                if (glyph == 0x60) {
                    *arg1 += 4;
                    if (lineH < 0xC) {
                        lineH = 0xC;
                    }
                } else if ((glyph >= 0xA1) && (glyph < 0xA8)) {
                    /* control codes 0xA1..0xA7 occupy no space */
                } else if ((glyph >= 0xA8) && (glyph < 0x100)) {
                    func_150415E0(glyph, &sp64, &sp60, &sp5C, &sp58, &sp54);
                    *arg1 = (s32)(*arg1 + sp64 * sp54);
                    temp = (s32)((s32)(sp60 * sp54) - sp5C) + 1;
                    if (lineH < temp) {
                        lineH = temp;
                    }
                    if (*arg3 < sp5C) {
                        *arg3 = (s32)sp5C;
                    }
                } else if (glyph < 0xA1) {
                    if (p[0] == 0xA) {
                        if (maxW < *arg1) {
                            maxW = *arg1;
                        }
                        *arg1 = 0;
                        if (lineH < 0xC) {
                            lineH = 0xC;
                        }
                        *arg2 += lineH;
                        lineH = 0;
                    } else {
                        flag = 1;
                    }
                }
                p++;
                if (flag != 0) {
                    *arg1 += D_80085994[glyph][0] + D_80085994[glyph][2] - 1;
                    temp = D_80085994[glyph][1] + D_80085994[glyph][3];
                    if (lineH <= temp) {
                        lineH = temp;
                    }
                }
            }
            c = *p;
        } while (c != 0);
    }

    if (*arg1 < maxW) {
        *arg1 = maxW;
    }
    *arg2 += lineH;
    *arg1 = (s32)(*arg1 * D_800380A0);
    *arg2 = (s32)(*arg2 * D_800380A4);
    *arg3 = (s32)(*arg3 * D_800380A0);
}

s32 func_15042C40(u8 arg0) {
    s32 i;
    u8 c;
    u8 *ptr;
    s32 original;

    original = arg0;
    if ((original >= 0x61) && (original < 0x7B)) {
        c = original - 0x20;
    } else {
        c = original;
    }

    if (original == 0x20) {
        return 0x60;
    }

    i = 3;
    if (D_80085930 == c) {
        return 0;
    }
    if (D_80085931 == c) {
        return 1;
    }
    if (D_80085932 == c) {
        return 2;
    }

    ptr = D_80085933;
    for (i = 3; ; ) {
        if (c == ptr[0]) {
            return i;
        }
        if (c == ptr[1]) {
            return i + 1;
        }
        if (c == ptr[2]) {
            return i + 2;
        }
        if (c == ptr[3]) {
            return i + 3;
        }
        i += 4;
        ptr += 4;
        if (i != 0x5F) {
            continue;
        }
        break;
    }

    return original;
}
