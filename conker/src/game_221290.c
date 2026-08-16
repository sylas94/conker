#include <ultra64.h>

#include "functions.h"
#include "variables.h"



extern f32 D_800B0C2C;
extern f32 D_800B0C30;
extern f32 D_800B0C34;
extern f32 D_800B0C38;
extern f32 D_800B0C3C;
extern f32 D_800B0C40;
extern f32 D_800B0C44;
extern f32 D_800B0C48;
extern s32 *D_800E0E20;
extern s32 D_800E0E28;
extern f32 *D_800E0E30;
/* One 36-entry IMDCT window per block type; D_800E0EC8 and D_800E0FE8 are rows
 * 1 and 3 of the same table, which func_151F78B4 indexes as D_800E0E38[type]. */
extern f32 D_800E0E38[4][36];
extern f32 D_800E0EC8[36];
extern f32 D_800E0FE8[36];
extern f32 *D_800E1078;
extern f32 D_800E1080[256];
extern f32 D_800E1480[256];

s32 func_151F3DE0(void) {
    s32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 sp18;

    for (sp34 = 0; sp34 < 0x24; sp34++) {
        D_800E0E38[0][sp34] = sinf(((f32)sp34 + 0.5f) * D_800B0C2C);
    }
    for (sp34 = 0; sp34 < 0x12; sp34++) {
        D_800E0EC8[sp34] = sinf(((f32)sp34 + 0.5f) * D_800B0C30);
    }
    for (sp34 = 0x12; sp34 < 0x18; sp34++) {
        D_800E0EC8[sp34] = 1.0f;
    }
    for (sp34 = 0x18; sp34 < 0x1E; sp34++) {
        D_800E0EC8[sp34] = sinf((((f32)sp34 + 0.5f) - 18.0f) * D_800B0C34);
    }
    for (sp34 = 0x1E; sp34 < 0x24; sp34++) {
        D_800E0EC8[sp34] = 0.0f;
    }
    for (sp34 = 0; sp34 < 6; sp34++) {
        D_800E0FE8[sp34] = 0.0f;
    }
    for (sp34 = 6; sp34 < 0xC; sp34++) {
        D_800E0FE8[sp34] = sinf((((f32)sp34 + 0.5f) - 6.0f) * D_800B0C38);
    }
    for (sp34 = 0xC; sp34 < 0x12; sp34++) {
        D_800E0FE8[sp34] = 1.0f;
    }
    for (sp34 = 0x12; sp34 < 0x24; sp34++) {
        D_800E0FE8[sp34] = sinf(((f32)sp34 + 0.5f) * D_800B0C3C);
    }
    for (sp34 = 1; sp34 < 0x22; sp34++) {
        D_800E0E20[sp34] += D_800E0E28;
    }
    D_800E1078 = D_800E0E30;
    if (D_800E1078 == NULL) {
        return 0;
    }
    sp30 = 1.0f;
    D_800E1078[0] = 0.0f;
    for (sp34 = 1; sp34 < 0x2000; sp34++) {
        sp24 = (f32)sp34;
        sp24 = sp24 * sp24;
        sp20 = sp24 * D_800B0C40;
        sp24 = sp24 * sp24;
        do {
            sp2C = sp30 * sp30;
            sp28 = ((sp2C * sp30) - sp24) / (2.0f * sp2C);
            sp30 -= sp28;
        } while ((sp28 > sp20) || (sp28 < -sp20));
        D_800E1078[sp34] = sp30;
    }
    sp1C = D_800B0C44;
    sp18 = 0.25f;
    D_800E1080[0] = 1.0f;
    D_800E1480[0] = 1.0f;
    for (sp34 = 1; sp34 < 0x100; sp34++) {
        D_800E1080[sp34] = sp1C;
        D_800E1480[sp34] = sp18;
        sp18 = sp18 * 0.25f;
        sp1C = sp1C * D_800B0C48;
    }
    return 1;
}
/* The per-granule frame view of the decoder context.  Three pairs of fields in
 * here genuinely OVERLAP in the ROM -- unk3BF8[1] runs into unk3C78, unk3F94[1]
 * would start where unk4418[0] does, and unk465C[1] is the same word as
 * unk4660[0] -- so the array bounds below are written to the largest size that
 * does not collide.  The address arithmetic (strides 1156 / 578 / 128 / 4) is
 * what the ROM encodes.  A [2][1] shape reproduces a pair of indices that both
 * stride by one element. */
extern u8  D_800AEB54[8];    /* scalefactor-band group boundaries: 0 6 11 16 21 | 0 6 12 */
extern u8  D_800AEB5C[2][16];/* the two scalefactor length (slen) tables */
extern s16 D_800AE840[][3][22];
extern u8  D_800AE948[][3][13];
extern s32 D_800AE7B8[34];

typedef struct {
    /* 0x00 */ s32 unk00[23];
    /* 0x5C */ s32 unk5C[3][13];
} AudSfRow; /* size 0xF8 */

typedef struct {
    /* 0x0000 */ u8  pad0000[0x1C];
    /* 0x001C */ u8  unk001C[0x2004];
    /* 0x2020 */ s32 unk2020;
    /* 0x2024 */ u8  pad2024[0x3BA4 - 0x2024];
    /* 0x3BA4 */ s32 unk3BA4;
    /* 0x3BA8 */ u8  pad3BA8[0x3BB4 - 0x3BA8];
    /* 0x3BB4 */ s32 unk3BB4;
    /* 0x3BB8 */ u8  pad3BB8[0x3BF8 - 0x3BB8];
    /* 0x3BF8 */ s32 unk3BF8[1][32];
    /* 0x3C78 */ s32 unk3C78[2][1];
    /* 0x3C80 */ s32 unk3C80[2][1];
    /* 0x3C88 */ u8  pad3C88[0x3C90 - 0x3C88];
    /* 0x3C90 */ s32 unk3C90[2][1];
    /* 0x3C98 */ s32 unk3C98[2][1];
    /* 0x3CA0 */ s32 unk3CA0[2][1];
    /* 0x3CA8 */ s32 unk3CA8[2][1];
    /* 0x3CB0 */ s32 unk3CB0[2][1][3];
    /* 0x3CC8 */ u8  pad3CC8[0x3CE0 - 0x3CC8];
    /* 0x3CE0 */ s32 unk3CE0[2][1];
    /* 0x3CE8 */ s32 unk3CE8[2][1];
    /* 0x3CF0 */ u8  pad3CF0[0x3D00 - 0x3CF0];
    /* 0x3D00 */ s32 unk3D00[2][1];
    /* 0x3D08 */ AudSfRow unk3D08[2][1];
    /* 0x3EF8 */ u8  pad3EF8[0x3F94 - 0x3EF8];
    /* 0x3F94 */ s16 unk3F94[1][578];
    /* 0x4418 */ u8  unk4418[1][578];
    /* 0x465A */ u8  pad465A[0x465C - 0x465A];
    /* 0x465C */ s32 unk465C[1];
    /* 0x4660 */ s32 unk4660[2];
} AudFrm;

s32 func_151F8960(void *, s32 *, s32);
s32 func_151F4F38(AudFrm *, s32, s32);
s32 func_151F8994(void *, s32 *, s32, s32, s32, s32, s16 **, u8 **);
s32 func_151F8B4C(void *, s32 *, s32, s32, s32, s16 **, u8 **);

/* The requantisation + reordering pass of the layer-III decoder. */
typedef struct {
    /* 0x00 */ s32 unk00[22];
} AudPretab; /* size 0x58 */

extern AudPretab D_800B0AB4;

/* Scalefactor-band boundary table, six [id][sfreq] rows of 37 s16: entries
 * 0..22 are the 23 long-block boundaries, 23..36 the 14 short-block ones. */
extern s16 D_800AE998[6][37];

f32 func_1504A400(f32, f32);

typedef struct {
    /* 0x0000 */ u8  pad0000[0x3BA4];
    /* 0x3BA4 */ s32 unk3BA4;
    /* 0x3BA8 */ u8  pad3BA8[0x3BB4 - 0x3BA8];
    /* 0x3BB4 */ s32 unk3BB4;
    /* 0x3BB8 */ u8  pad3BB8[0x3C88 - 0x3BB8];
    /* 0x3C88 */ s32 unk3C88[2][1];
    /* 0x3C90 */ u8  pad3C90[0x3C98 - 0x3C90];
    /* 0x3C98 */ s32 unk3C98[2][1];
    /* 0x3CA0 */ s32 unk3CA0[2][1];
    /* 0x3CA8 */ s32 unk3CA8[2][1];
    /* 0x3CB0 */ u8  pad3CB0[0x3CC8 - 0x3CB0];
    /* 0x3CC8 */ s32 unk3CC8[2][1][3];
    /* 0x3CE0 */ u8  pad3CE0[0x3CF0 - 0x3CE0];
    /* 0x3CF0 */ s32 unk3CF0[2][1];
    /* 0x3CF8 */ s32 unk3CF8[2][1];
    /* 0x3D00 */ u8  pad3D00[0x3D08 - 0x3D00];
    /* 0x3D08 */ AudSfRow unk3D08[2][1];
    /* 0x3EF8 */ u8  pad3EF8[0x3F94 - 0x3EF8];
    /* 0x3F94 */ s16 unk3F94[1][578];
    /* 0x4418 */ u8  unk4418[1][578];
    /* 0x465A */ u8  pad465A[0x465C - 0x465A];
    /* 0x465C */ s32 unk465C[1];
    /* 0x4660 */ s32 unk4660[1];
    /* 0x4664 */ f32 unk4664[1][576];
} AudRqt;

s32 func_151F42E8(AudRqt *arg0, s32 arg1, s32 arg2) {
    s32 sp1BC;
    s32 sp1B8;
    s32 sp1B4;
    s32 sp1B0;
    AudPretab sp158 = D_800B0AB4;
    f32 sp100[22];
    f32 sp64[3][13];
    f32 sp60;
    s32 sp5C;
    s32 sp58;
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    s32 sp48;
    s32 sp44;
    f32 *sp40;
    s16 *sp3C;
    u8 *sp38;
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s32 sp28;
    f32 *sp24;

    sp1BC = arg0->unk3BB4 + arg0->unk3BA4 * 3;
    if ((arg0->unk3C98[arg1][arg2] != 0) && (arg0->unk3CA0[arg1][arg2] == 2)) {
        if (arg0->unk3CA8[arg1][arg2] != 0) {
            sp1B8 = D_800AE998[sp1BC][1];
        } else {
            sp1B8 = D_800AE998[sp1BC][24] * 3;
            sp1B0 = D_800AE998[sp1BC][24];
            sp1B4 = 0;
        }
    } else {
        sp1B8 = D_800AE998[sp1BC][1];
    }
    sp60 = func_1504A400(2.0f, ((f32)arg0->unk3C88[arg1][arg2] - 210.0f) * 0.25f);
    sp54 = arg0->unk3CF8[arg1][arg2];
    for (sp5C = 0; sp5C < 22; sp5C++) {
        sp4C = (arg0->unk3D08[arg1][arg2].unk00[sp5C] +
                arg0->unk3CF0[arg1][arg2] * sp158.unk00[sp5C]) * (sp54 + 1);
        sp100[sp5C] = D_800E1080[sp4C] * sp60;
    }
    for (sp58 = 0; sp58 < 3; sp58++) {
        for (sp5C = 0; sp5C < 13; sp5C++) {
            sp50 = arg0->unk3CC8[arg1][arg2][sp58];
            sp4C = arg0->unk3D08[arg1][arg2].unk5C[sp58][sp5C] * (sp54 + 1);
            sp64[sp58][sp5C] = sp60 * D_800E1480[sp50] * D_800E1080[sp4C];
        }
    }
    sp5C = 0;
    sp48 = 0;
    sp44 = arg0->unk465C[arg2];
    sp40 = arg0->unk4664[arg2];
    sp3C = arg0->unk3F94[arg2];
    sp38 = arg0->unk4418[arg2];
    sp34 = (arg0->unk3CA0[arg1][arg2] == 2) && (arg0->unk3CA8[arg1][arg2] == 0);
    sp30 = (arg0->unk3CA0[arg1][arg2] == 2) && (arg0->unk3CA8[arg1][arg2] != 0);
    sp2C = arg0->unk3C98[arg1][arg2];
    while (sp48 < sp44) {
        if (sp1B8 > sp44) {
            sp1B8 = sp44;
        }
        if (sp2C && (sp34 || (sp30 && (sp48 >= 0x24)))) {
            sp58 = (sp48 - sp1B4) / sp1B0;
            sp28 = sp1B4 + sp1B0;
        }
        while (sp48 < sp1B8) {
            if (sp2C && (sp34 || (sp30 && (sp48 >= 0x24)))) {
                if (sp48 >= sp28) {
                    sp28 += sp1B0;
                    sp58++;
                }
                sp24 = sp64[sp58];
                if (*sp38++) {
                    *sp40++ = -(D_800E1078[*sp3C++] * sp24[sp5C]);
                } else {
                    *sp40++ = D_800E1078[*sp3C++] * sp24[sp5C];
                }
            } else {
                if (*sp38++) {
                    *sp40++ = -(D_800E1078[*sp3C++] * sp100[sp5C]);
                } else {
                    *sp40++ = D_800E1078[*sp3C++] * sp100[sp5C];
                }
            }
            sp48++;
        }
        if ((arg0->unk3C98[arg1][arg2] != 0) && (arg0->unk3CA0[arg1][arg2] == 2)) {
            if (arg0->unk3CA8[arg1][arg2] != 0) {
                if (D_800AE998[sp1BC][8] == sp48) {
                    sp1B8 = D_800AE998[sp1BC][27] * 3;
                    sp5C = 3;
                    sp1B0 = D_800AE998[sp1BC][sp5C + 24] - D_800AE998[sp1BC][sp5C + 23];
                    sp1B4 = D_800AE998[sp1BC][sp5C + 23] * 3;
                } else if (sp48 < D_800AE998[sp1BC][8]) {
                    sp1B8 = D_800AE998[sp1BC][++sp5C + 1];
                } else {
                    sp1B8 = D_800AE998[sp1BC][++sp5C + 24] * 3;
                    sp1B0 = D_800AE998[sp1BC][sp5C + 24] - D_800AE998[sp1BC][sp5C + 23];
                    sp1B4 = D_800AE998[sp1BC][sp5C + 23] * 3;
                }
            } else {
                sp1B8 = D_800AE998[sp1BC][++sp5C + 24] * 3;
                sp1B0 = D_800AE998[sp1BC][sp5C + 24] - D_800AE998[sp1BC][sp5C + 23];
                sp1B4 = D_800AE998[sp1BC][sp5C + 23] * 3;
            }
        } else {
            sp1B8 = D_800AE998[sp1BC][++sp5C + 1];
        }
    }
    /* The early `return 1` is LOAD-BEARING SOURCE, not a redundancy: at -g each `return`
       emits its own `b <epilogue>; addiu v0,1` pair, and golden has TWO of them plus the
       implicit end-of-function `b; nop`.  Delete-and-measure, run both ways: with it 788
       instructions (match), folded into a single trailing `return 1;` 786 -- i.e. removing
       it drops us BELOW golden.  An if/else with a `return 1` in each arm is wrong the
       other way: it adds the else's merge jump, giving 790. */
    if (sp48 < 0x240) {
        bzero(sp40, arg0->unk4660[arg2] * 4);
        return 1;
    }
    return 1;
}

s32 func_151F4F38(AudFrm *arg0, s32 arg1, s32 arg2) {
    s32 sp34;
    s32 sp30;
    s32 sp2C;

    if ((arg0->unk3C98[arg1][arg2] != 0) && (arg0->unk3CA0[arg1][arg2] == 2)) {
        if (arg0->unk3CA8[arg1][arg2] != 0) {
            for (sp30 = 0; sp30 < 8; sp30++) {
                arg0->unk3D08[arg1][arg2].unk00[sp30] =
                    (D_800AEB5C[0][arg0->unk3C90[arg1][arg2]] != 0)
                        ? func_151F8960(arg0->unk001C, &arg0->unk2020,
                                        D_800AEB5C[0][arg0->unk3C90[arg1][arg2]])
                        : 0;
            }
            for (sp30 = 3; sp30 < 6; sp30++) {
                for (sp2C = 0; sp2C < 3; sp2C++) {
                    arg0->unk3D08[arg1][arg2].unk5C[sp2C][sp30] =
                        (D_800AEB5C[0][arg0->unk3C90[arg1][arg2]] != 0)
                            ? func_151F8960(arg0->unk001C, &arg0->unk2020,
                                            D_800AEB5C[0][arg0->unk3C90[arg1][arg2]])
                            : 0;
                }
            }
            for (sp30 = 6; sp30 < 0xC; sp30++) {
                for (sp2C = 0; sp2C < 3; sp2C++) {
                    arg0->unk3D08[arg1][arg2].unk5C[sp2C][sp30] =
                        (D_800AEB5C[1][arg0->unk3C90[arg1][arg2]] != 0)
                            ? func_151F8960(arg0->unk001C, &arg0->unk2020,
                                            D_800AEB5C[1][arg0->unk3C90[arg1][arg2]])
                            : 0;
                }
            }
        } else {
            for (sp34 = 0; sp34 < 2; sp34++) {
                for (sp30 = D_800AEB54[sp34 + 5]; sp30 < D_800AEB54[sp34 + 6]; sp30++) {
                    for (sp2C = 0; sp2C < 3; sp2C++) {
                        arg0->unk3D08[arg1][arg2].unk5C[sp2C][sp30] =
                            (D_800AEB5C[sp34][arg0->unk3C90[arg1][arg2]] != 0)
                                ? func_151F8960(arg0->unk001C, &arg0->unk2020,
                                                D_800AEB5C[sp34][arg0->unk3C90[arg1][arg2]])
                                : 0;
                    }
                }
            }
        }
        for (sp2C = 0; sp2C < 3; sp2C++) {
            arg0->unk3D08[arg1][arg2].unk5C[sp2C][12] = 0;
        }
    } else {
        for (sp34 = 0; sp34 < 4; sp34++) {
            if ((arg0->unk3BF8[arg2][sp34] == 0) || (arg1 == 0)) {
                for (sp30 = D_800AEB54[sp34]; sp30 < D_800AEB54[sp34 + 1]; sp30++) {
                    arg0->unk3D08[arg1][arg2].unk00[sp30] =
                        (D_800AEB5C[(sp34 < 2) ? 0 : 1][arg0->unk3C90[arg1][arg2]] != 0)
                            ? func_151F8960(arg0->unk001C, &arg0->unk2020,
                                            D_800AEB5C[(sp34 < 2) ? 0 : 1]
                                                      [arg0->unk3C90[arg1][arg2]])
                            : 0;
                }
            } else {
                for (sp30 = D_800AEB54[sp34]; sp30 < D_800AEB54[sp34 + 1]; sp30++) {
                    arg0->unk3D08[1][arg2].unk00[sp30] = arg0->unk3D08[0][arg2].unk00[sp30];
                }
            }
        }
        arg0->unk3D08[arg1][arg2].unk00[22] = 0;
    }
    return 1;
}

/* Rare's compressed-audio bitstream decoder context. Not in structs.h. */
typedef struct {
    /* 0x00 */ s32 unk00[23];
    /* 0x5C */ s32 unk5C[13];
    /* 0x90 */ s32 unk90[13];
    /* 0xC4 */ s32 unkC4[13];
} AudRow; /* size 0xF8 */

typedef struct {
    /* 0x0000 */ u8 unk0000[0x1C];
    /* 0x001C */ u8 unk001C[0x2004];
    /* 0x2020 */ s32 unk2020;
    /* 0x2024 */ u8 unk2024[0x3BC4 - 0x2024];
    /* 0x3BC4 */ s32 unk3BC4;
    /* 0x3BC8 */ u8 unk3BC8[0x3C90 - 0x3BC8];
    /* 0x3C90 */ s32 unk3C90[2];
    /* 0x3C98 */ s32 unk3C98[2];
    /* 0x3CA0 */ s32 unk3CA0[2];
    /* 0x3CA8 */ s32 unk3CA8[2];
    /* 0x3CB0 */ u8 unk3CB0[0x3CF0 - 0x3CB0];
    /* 0x3CF0 */ s32 unk3CF0[2];
    /* 0x3CF8 */ u8 unk3CF8[0x3D08 - 0x3CF8];
    /* 0x3D08 */ AudRow unk3D08[2];
    /* 0x3EF8 */ s32 unk3EF8;
    /* 0x3EFC */ s32 unk3EFC[6];
    /* 0x3F14 */ s32 unk3F14[16];
} AudCtx;

typedef struct {
    /* 0x000 */ s32 unk000[2][3][3][4];
} AudCounts; /* size 0x120 */

extern AudCounts D_800B0B0C;

s32 func_151F8960(void *, s32 *, s32);

s32 func_151F578C(AudCtx *arg0, s32 arg1, s32 arg2) {
    AudCounts sp70 = D_800B0B0C;
    s32 sp60[4];
    s32 sp5C = arg0->unk3C90[arg2];
    s32 *sp58 = &arg0->unk3CF0[arg2];
    s32 sp54 = arg0->unk3CA8[arg2];
    s32 sp50 = arg0->unk3CA0[arg2];
    s32 sp4C = arg0->unk3C98[arg2];
    s32 sp48;
    s32 sp44;
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    s32 sp28[4];
    s32 sp24;
    s32 sp20;
    s32 sp1C;

    if (((arg0->unk3BC4 != 1) && (arg0->unk3BC4 != 3)) || (arg2 != 1)) {
        sp48 = 0;
        if (sp5C < 0x190) {
            sp60[0] = (sp5C >> 4) / 5;
            sp60[1] = (sp5C >> 4) % 5;
            sp60[2] = (sp5C % 16) >> 2;
            sp60[3] = sp5C % 4;
            *sp58 = 0;
            sp44 = 0;
        } else if ((sp5C >= 0x190) && (sp5C < 0x1F4)) {
            sp60[0] = ((sp5C - 0x190) >> 2) / 5;
            sp60[1] = ((sp5C - 0x190) >> 2) % 5;
            sp60[2] = (sp5C - 0x190) % 4;
            sp60[3] = 0;
            *sp58 = 0;
            sp44 = 1;
        } else if ((sp5C >= 0x1F4) && (sp5C < 0x200)) {
            sp60[0] = (sp5C - 0x1F4) / 3;
            sp60[1] = (sp5C - 0x1F4) % 3;
            sp60[2] = 0;
            sp60[3] = 0;
            *sp58 = 1;
            sp44 = 2;
        }
    }
    if (((arg0->unk3BC4 == 1) || (arg0->unk3BC4 == 3)) && (arg2 == 1)) {
        arg0->unk3EF8 = sp5C % 2;
        sp38 = sp5C >> 1;
        sp48 = 1;
        if (sp38 < 0xB4) {
            sp60[0] = sp38 / 0x24;
            sp60[1] = (sp38 % 0x24) / 6;
            sp60[2] = (sp38 % 0x24) % 6;
            sp60[3] = 0;
            *sp58 = 0;
            sp44 = 0;
        } else if ((sp38 >= 0xB4) && (sp38 < 0xF4)) {
            sp60[0] = ((sp38 - 0xB4) % 0x40) >> 4;
            sp60[1] = ((sp38 - 0xB4) % 0x10) >> 2;
            sp60[2] = (sp38 - 0xB4) % 4;
            sp60[3] = 0;
            *sp58 = 0;
            sp44 = 1;
        } else if ((sp38 >= 0xF4) && (sp38 < 0xFF)) {
            sp60[0] = (sp38 - 0xF4) / 3;
            sp60[1] = (sp38 - 0xF4) % 3;
            sp60[2] = 0;
            sp60[3] = 0;
            *sp58 = 0;
            sp44 = 2;
        }
    }
    if ((sp4C != 0) && (sp50 == 2)) {
        bcopy(&sp70.unk000[sp48][sp44][sp54 + 1][0], sp28, 0x10);
    } else {
        bcopy(&sp70.unk000[sp48][sp44][0][0], sp28, 0x10);
    }
    sp24 = 0;
    if ((sp4C == 0) || ((sp4C != 0) && (sp50 != 2))) {
        for (sp40 = 0; sp40 < 4; sp40++) {
            sp20 = sp60[sp40];
            sp1C = (1 << sp20) - 1;
            for (sp3C = 0; sp3C < sp28[sp40]; sp3C++) {
                arg0->unk3D08[arg2].unk00[sp24] =
                    (sp20 != 0) ? func_151F8960(arg0->unk001C, &arg0->unk2020, sp20) : 0;
                if (arg2 != 0) {
                    arg0->unk3EFC[sp24] = sp1C;
                }
                sp24++;
            }
        }
    } else {
        if (sp50 == 2) {
            if (sp54 == 0) {
                for (sp40 = 0; sp40 < 4; sp40++) {
                    sp20 = sp60[sp40];
                    sp1C = (1 << sp20) - 1;
                    for (sp3C = 0; sp3C < sp28[sp40]; sp3C += 3) {
                        arg0->unk3D08[arg2].unk5C[sp24] =
                            (sp20 != 0) ? func_151F8960(arg0->unk001C, &arg0->unk2020, sp20) : 0;
                        arg0->unk3D08[arg2].unk90[sp24] =
                            (sp20 != 0) ? func_151F8960(arg0->unk001C, &arg0->unk2020, sp20) : 0;
                        arg0->unk3D08[arg2].unkC4[sp24] =
                            (sp20 != 0) ? func_151F8960(arg0->unk001C, &arg0->unk2020, sp20) : 0;
                        if (arg2 != 0) {
                            arg0->unk3F14[sp24] = sp1C;
                        }
                        sp24++;
                    }
                }
            } else {
                sp20 = sp60[0];
                sp1C = (1 << sp20) - 1;
                for (sp3C = 0; sp3C < 6; sp3C++) {
                    arg0->unk3D08[arg2].unk00[sp24] =
                        (sp20 != 0) ? func_151F8960(arg0->unk001C, &arg0->unk2020, sp20) : 0;
                    if (arg2 != 0) {
                        arg0->unk3EFC[sp24] = sp1C;
                    }
                    sp24++;
                }
                sp28[0] -= 6;
                sp24 = 3;
                for (sp40 = 0; sp40 < 4; sp40++) {
                    sp20 = sp60[sp40];
                    sp1C = (1 << sp20) - 1;
                    for (sp3C = 0; sp3C < sp28[sp40]; sp3C += 3) {
                        arg0->unk3D08[arg2].unk5C[sp24] =
                            (sp20 != 0) ? func_151F8960(arg0->unk001C, &arg0->unk2020, sp20) : 0;
                        arg0->unk3D08[arg2].unk90[sp24] =
                            (sp20 != 0) ? func_151F8960(arg0->unk001C, &arg0->unk2020, sp20) : 0;
                        arg0->unk3D08[arg2].unkC4[sp24] =
                            (sp20 != 0) ? func_151F8960(arg0->unk001C, &arg0->unk2020, sp20) : 0;
                        if (arg2 != 0) {
                            arg0->unk3F14[sp24] = sp1C;
                        }
                        sp24++;
                    }
                }
            }
        }
    }
    return 1;
}

s32 func_151F63C4(AudFrm *arg0, s32 arg1, s32 arg2) {
    s32 sp64;
    s32 sp60;
    s32 sp54[3];
    s16 *sp50;
    u8 *sp4C;
    s32 sp48;
    s16 *sp44;
    u8 *sp40;
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s32 sp28;

    sp64 = arg0->unk2020;
    if (arg0->unk3BA4 != 0) {
        func_151F4F38(arg0, arg1, arg2);
    } else {
        func_151F578C((AudCtx *)arg0, arg1, arg2);
    }
    sp60 = arg0->unk3C80[arg1][arg2] * 2;
    sp50 = &D_800AE840[arg0->unk3BA4][arg0->unk3BB4][0];
    sp4C = &D_800AE948[arg0->unk3BA4][arg0->unk3BB4][0];
    if ((arg0->unk3C98[arg1][arg2] == 0) && (arg0->unk3CA0[arg1][arg2] == 0)) {
        sp54[0] = sp50[arg0->unk3CE0[arg1][arg2]] + 1;
        if (sp54[0] > sp60) {
            sp54[0] = sp54[1] = sp60;
        } else {
            sp54[1] = sp50[arg0->unk3CE0[arg1][arg2] + arg0->unk3CE8[arg1][arg2] + 1] + 1;
            if (sp54[1] > sp60) {
                sp54[1] = sp60;
            }
        }
    } else {
        if ((arg0->unk3CA0[arg1][arg2] == 2) && (arg0->unk3CA8[arg1][arg2] == 0)) {
            sp54[0] = (sp4C[2] * 3) + 3;
        } else {
            sp54[0] = sp50[7] + 1;
        }
        if (sp54[0] > sp60) {
            sp54[0] = sp60;
        }
        sp54[1] = sp60;
    }
    sp54[2] = sp60;
    sp48 = 0;
    sp44 = arg0->unk3F94[arg2];
    sp40 = arg0->unk4418[arg2];
    for (sp3C = 0; sp3C < 3; sp3C++) {
        sp38 = arg0->unk3CB0[arg1][arg2][sp3C];
        sp34 = D_800AE7B8[sp38];
        sp30 = sp54[sp3C];
        if (D_800E0E20[sp38] == 0) {
            sp2C = sp30 - sp48;
            bzero(sp44, sp2C * 2);
            sp44 += sp2C;
            sp40 += sp2C;
            sp48 = sp30;
        } else {
            sp48 = func_151F8994(arg0->unk001C, &arg0->unk2020, sp38, sp48, sp34, sp30, &sp44,
                                 &sp40);
        }
    }
    sp38 = arg0->unk3D00[arg1][arg2] + 0x20;
    sp28 = arg0->unk3C78[arg1][arg2] + sp64;
    sp48 = func_151F8B4C(arg0->unk001C, &arg0->unk2020, sp38, sp48, sp28, &sp44, &sp40);
    arg0->unk2020 = sp28;
    if (sp48 > 0x240) {
        arg0->unk465C[arg2] = 0x240;
    } else {
        arg0->unk465C[arg2] = sp48;
    }
    if (sp48 < 0x240) {
        arg0->unk4660[arg2] = 0x240 - sp48;
        bzero(sp44, arg0->unk4660[arg2] * 2);
    } else {
        arg0->unk4660[arg2] = 0;
    }
    return 1;
}
extern s16 D_800AEB7C[2][3][576];

typedef struct {
    /* 0x0000 */ u8  pad0000[0x3BA4];
    /* 0x3BA4 */ s32 unk3BA4;
    /* 0x3BA8 */ u8  pad3BA8[0x3BB4 - 0x3BA8];
    /* 0x3BB4 */ s32 unk3BB4;
    /* 0x3BB8 */ u8  pad3BB8[0x3C98 - 0x3BB8];
    /* 0x3C98 */ s32 unk3C98[2];
    /* 0x3CA0 */ s32 unk3CA0[2];
    /* 0x3CA8 */ s32 unk3CA8[2];
    /* 0x3CB0 */ u8  pad3CB0[0x4664 - 0x3CB0];
    /* 0x4664 */ f32 unk4664[576];
    /* 0x4F64 */ f32 unk4F64[576];
} AudX6970;

s32 func_151F6970(AudX6970 *arg0, s32 arg1) {
    s16 *sp14;
    f32 *sp10;
    f32 *spC;
    s32 sp8;

    sp14 = &D_800AEB7C[arg0->unk3BA4][arg0->unk3BB4][0];
    sp10 = arg0->unk4F64;
    spC = arg0->unk4664;
    sp8 = 0;
    if ((arg0->unk3C98[arg1] != 0) && (arg0->unk3CA0[arg1] == 2)) {
        if (arg0->unk3CA8[arg1] != 0) {
            while (sp8++ < 0x24) {
                *sp10++ = *spC++;
            }
        }
        while (sp8 < 0x240) {
            sp10[sp14[sp8++]] = *spC++;
        }
    } else {
        while (sp8++ < 0x240) {
            *sp10++ = *spC++;
        }
    }
    return 1;
}

/* The de-interleave/rotation pass of the bitstream decoder.  The context is
 * re-described locally: the shared AudCtx above only names the fields the
 * already-decompiled functions need. */
extern f32 D_800B067C[8];
extern f32 D_800B069C[8];

typedef struct {
    /* 0x00 */ f32 unk00[8];
    /* 0x20 */ f32 unk20[8];
    /* 0x40 */ u8  pad40[0x8];
} AudBlk151F6B28; /* size 0x48 */

typedef struct {
    /* 0x0000 */ u8  pad0000[0x3C98];
    /* 0x3C98 */ s32 unk3C98[2][1];
    /* 0x3CA0 */ s32 unk3CA0[2][1];
    /* 0x3CA8 */ u8  pad3CA8[0x4F44 - 0x3CA8];
    /* 0x4F44 */ AudBlk151F6B28 unk4F44[2][32];
} AudState151F6B28;

s32 func_151F6B28(AudState151F6B28 *arg0, s32 arg1, s32 arg2) {
    s32 i;
    f32 *p;
    f32 v;
    f32 u;

    if (arg0->unk3C98[arg1][arg2] != 0) {
        if (arg0->unk3CA0[arg1][arg2] == 2) {
            return 1;
        }
    }

    for (i = 1; i < 32; i++) {
        p = arg0->unk4F44[arg2][i].unk20;

        v = p[0];
        u = p[-1];
        p[-1] = u * D_800B069C[0] - D_800B067C[0] * v;
        p[0] = v * D_800B069C[0] + D_800B067C[0] * u;

        v = p[1];
        u = p[-2];
        p[-2] = u * D_800B069C[1] - D_800B067C[1] * v;
        p[1] = v * D_800B069C[1] + D_800B067C[1] * u;

        v = p[2];
        u = p[-3];
        p[-3] = u * D_800B069C[2] - D_800B067C[2] * v;
        p[2] = v * D_800B069C[2] + D_800B067C[2] * u;

        v = p[3];
        u = p[-4];
        p[-4] = u * D_800B069C[3] - D_800B067C[3] * v;
        p[3] = v * D_800B069C[3] + D_800B067C[3] * u;

        v = p[4];
        u = p[-5];
        p[-5] = u * D_800B069C[4] - D_800B067C[4] * v;
        p[4] = v * D_800B069C[4] + D_800B067C[4] * u;

        v = p[5];
        u = p[-6];
        p[-6] = u * D_800B069C[5] - D_800B067C[5] * v;
        p[5] = v * D_800B069C[5] + D_800B067C[5] * u;

        v = p[6];
        u = p[-7];
        p[-7] = u * D_800B069C[6] - D_800B067C[6] * v;
        p[6] = v * D_800B069C[6] + D_800B067C[6] * u;

        v = p[7];
        u = p[-8];
        p[-8] = u * D_800B069C[7] - D_800B067C[7] * v;
        p[7] = v * D_800B069C[7] + D_800B067C[7] * u;
    }

    return 1;
}
/* The decoder instance.  unk0000 is an opaque handle handed back to the host,
 * unk0004 the host's read callback, and unk001C a 0x2000-byte sliding input
 * window whose bit cursor is unk2020 and byte fill level unk201C.  unk2024 is
 * the small header-byte buffer with its own bit cursor at unk2064; unk3BA4..
 * unk3BD0 are the twelve decoded header fields and unk3BD8..unk3BF0 the copy
 * kept from the first frame to detect a stream change. */
typedef struct AudInst AudInst;

typedef s32 (*AudReadFn)(s32, void *, s32, s32);
typedef s32 (*AudDecFn)(AudInst *);

struct AudInst {
    /* 0x0000 */ s32 unk0000;
    /* 0x0004 */ AudReadFn unk0004;
    /* 0x0008 */ s32 unk0008;
    /* 0x000C */ s32 unk000C;
    /* 0x0010 */ s32 unk0010;
    /* 0x0014 */ s32 unk0014;
    /* 0x0018 */ s32 unk0018;
    /* 0x001C */ u8  unk001C[0x2000];
    /* 0x201C */ s32 unk201C;
    /* 0x2020 */ s32 unk2020;
    /* 0x2024 */ u8  unk2024[0x40];
    /* 0x2064 */ s32 unk2064;
    /* 0x2068 */ s32 unk2068;
    /* 0x206C */ s32 unk206C;
    /* 0x2070 */ u8  unk2070[6][0x488];
    /* 0x3BA0 */ s32 unk3BA0;
    /* 0x3BA4 */ s32 unk3BA4;
    /* 0x3BA8 */ s32 unk3BA8;
    /* 0x3BAC */ s32 unk3BAC;
    /* 0x3BB0 */ s32 unk3BB0;
    /* 0x3BB4 */ s32 unk3BB4;
    /* 0x3BB8 */ s32 unk3BB8;
    /* 0x3BBC */ s32 unk3BBC;
    /* 0x3BC0 */ s32 unk3BC0;
    /* 0x3BC4 */ s32 unk3BC4;
    /* 0x3BC8 */ s32 unk3BC8;
    /* 0x3BCC */ s32 unk3BCC;
    /* 0x3BD0 */ s32 unk3BD0;
    /* 0x3BD4 */ s32 unk3BD4;
    /* 0x3BD8 */ s32 unk3BD8;
    /* 0x3BDC */ s32 unk3BDC;
    /* 0x3BE0 */ s32 unk3BE0;
    /* 0x3BE4 */ s32 unk3BE4;
    /* 0x3BE8 */ s32 unk3BE8;
    /* 0x3BEC */ s32 unk3BEC;
    /* 0x3BF0 */ s32 unk3BF0;
    /* 0x3BF4 */ s32 unk3BF4;
    /* 0x3BF8 */ s32 unk3BF8[1][32];
    /* 0x3C78 */ s32 unk3C78[2][1];
    /* 0x3C80 */ s32 unk3C80[2][1];
    /* 0x3C88 */ s32 unk3C88[2][1];
    /* 0x3C90 */ s32 unk3C90[2][1];
    /* 0x3C98 */ s32 unk3C98[2][1];
    /* 0x3CA0 */ s32 unk3CA0[2][1];
    /* 0x3CA8 */ s32 unk3CA8[2][1];
    /* 0x3CB0 */ s32 unk3CB0[2][1][3];
    /* 0x3CC8 */ s32 unk3CC8[2][1][3];
    /* 0x3CE0 */ s32 unk3CE0[2][1];
    /* 0x3CE8 */ s32 unk3CE8[2][1];
    /* 0x3CF0 */ s32 unk3CF0[2][1];
    /* 0x3CF8 */ s32 unk3CF8[2][1];
    /* 0x3D00 */ s32 unk3D00[2][1];
    /* 0x3D08 */ u8  pad3D08[0x3F7C - 0x3D08];
    /* 0x3F7C */ s32 unk3F7C;
    /* 0x3F80 */ s32 unk3F80;
    /* 0x3F84 */ s32 unk3F84;
    /* 0x3F88 */ s32 unk3F88;
    /* 0x3F8C */ s32 unk3F8C;
    /* 0x3F90 */ s32 unk3F90;
    /* 0x3F94 */ u8  pad3F94[0x465C - 0x3F94];
    /* 0x465C */ s32 unk465C[1];
    /* 0x4660 */ u8  pad4660[0x4F64 - 0x4660];
    /* 0x4F64 */ f32 unk4F64[2][32][18];
    /* 0x6164 */ u8  pad6164[0x6A64 - 0x6164];
    /* 0x6A64 */ f32 unk6A64[2][32][18];
    /* 0x7C64 */ u8  pad7C64[0x8474 - 0x7C64];
    /* 0x8474 */ s32 unk8474;
    /* 0x8478 */ AudDecFn unk8478;
    /* 0x847C */ AudDecFn unk847C;
}; /* size 0x8480 */

extern AudInst D_800E1880;
extern void (*D_800E0E00)(s32, void *, s32);
extern s32 D_800E0E04;
extern s32 D_800B06BC[2][15];  /* bitrate table, indexed [mpegId][bitrateIndex] */
extern s32 D_800B0734[2][4];   /* sample-rate table, indexed [mpegId][srIndex]   */

s32 func_151F8088(AudInst *, s32);
s32 func_151F6FD0(AudInst *);
s32 func_151F78B4(AudInst *);
s32 func_151F7F60(AudInst *);
s32 func_151F9BF0(f32 *, s32, f32 *, f32 *);
s32 func_151F8CF0(f32 *, s32, f32 *, f32 *, f32 *);

s32 func_151F6FD0(AudInst *arg0) {
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    s32 sp1C;

    if (arg0->unk3BA4 != 0) {
        arg0->unk206C = (arg0->unk3BC0 == 3) ? 0x11 : 0x20;
    } else {
        arg0->unk206C = (arg0->unk3BC0 == 3) ? 9 : 0x11;
    }
    sp34 = arg0->unk0004(arg0->unk0000, &arg0->unk2024[arg0->unk2068], arg0->unk206C, -1);
    if (arg0->unk206C != sp34) {
        return 0;
    }
    arg0->unk0018 += arg0->unk206C;
    arg0->unk3F8C = (arg0->unk3BC0 == 3) ? 1 : 2;
    arg0->unk3F90 = (arg0->unk3BA4 != 0) ? 2 : 1;
    if (arg0->unk3BA4 != 0) {
        arg0->unk3BF4 = func_151F8960(arg0->unk2024, &arg0->unk2064, 9);
        (arg0->unk3F8C == 1) ? func_151F8960(arg0->unk2024, &arg0->unk2064, 5)
                             : func_151F8960(arg0->unk2024, &arg0->unk2064, 3);
    } else {
        arg0->unk3BF4 = func_151F8960(arg0->unk2024, &arg0->unk2064, 8);
        (arg0->unk3F8C == 1) ? func_151F8960(arg0->unk2024, &arg0->unk2064, 1)
                             : func_151F8960(arg0->unk2024, &arg0->unk2064, 2);
    }
    if (arg0->unk3BA4 != 0) {
        for (sp30 = 0; sp30 < arg0->unk3F8C; sp30++) {
            for (sp2C = 0; sp2C < 4; sp2C++) {
                arg0->unk3BF8[sp30][sp2C] = func_151F8960(arg0->unk2024, &arg0->unk2064, 1);
            }
        }
    }
    if (arg0->unk3BA4 != 0) {
        sp28 = 4;
    } else {
        sp28 = 9;
    }
    for (sp24 = 0; sp24 < arg0->unk3F90; sp24++) {
        for (sp30 = 0; sp30 < arg0->unk3F8C; sp30++) {
            arg0->unk3C78[sp24][sp30] = func_151F8960(arg0->unk2024, &arg0->unk2064, 0xC);
            arg0->unk3C80[sp24][sp30] = func_151F8960(arg0->unk2024, &arg0->unk2064, 9);
            arg0->unk3C88[sp24][sp30] = func_151F8960(arg0->unk2024, &arg0->unk2064, 8);
            arg0->unk3C90[sp24][sp30] =
                (sp28 != 0) ? func_151F8960(arg0->unk2024, &arg0->unk2064, sp28) : 0;
            arg0->unk3C98[sp24][sp30] = func_151F8960(arg0->unk2024, &arg0->unk2064, 1);
            if (arg0->unk3C98[sp24][sp30] != 0) {
                arg0->unk3CA0[sp24][sp30] = func_151F8960(arg0->unk2024, &arg0->unk2064, 2);
                arg0->unk3CA8[sp24][sp30] = func_151F8960(arg0->unk2024, &arg0->unk2064, 1);
                for (sp20 = 0; sp20 < 2; sp20++) {
                    arg0->unk3CB0[sp24][sp30][sp20] =
                        func_151F8960(arg0->unk2024, &arg0->unk2064, 5);
                }
                arg0->unk3CB0[sp24][sp30][2] = 0;
                for (sp1C = 0; sp1C < 3; sp1C++) {
                    arg0->unk3CC8[sp24][sp30][sp1C] =
                        func_151F8960(arg0->unk2024, &arg0->unk2064, 3);
                }
            } else {
                arg0->unk3CA0[sp24][sp30] = 0;
                arg0->unk3CA8[sp24][sp30] = 0;
                for (sp20 = 0; sp20 < 3; sp20++) {
                    arg0->unk3CB0[sp24][sp30][sp20] =
                        func_151F8960(arg0->unk2024, &arg0->unk2064, 5);
                }
                arg0->unk3CE0[sp24][sp30] = func_151F8960(arg0->unk2024, &arg0->unk2064, 4);
                arg0->unk3CE8[sp24][sp30] = func_151F8960(arg0->unk2024, &arg0->unk2064, 3);
            }
            if (arg0->unk3BA4 != 0) {
                arg0->unk3CF0[sp24][sp30] = func_151F8960(arg0->unk2024, &arg0->unk2064, 1);
            }
            arg0->unk3CF8[sp24][sp30] = func_151F8960(arg0->unk2024, &arg0->unk2064, 1);
            arg0->unk3D00[sp24][sp30] = func_151F8960(arg0->unk2024, &arg0->unk2064, 1);
        }
    }
    arg0->unk3F7C = D_800B06BC[arg0->unk3BA4][arg0->unk3BB0];
    arg0->unk3F80 = D_800B0734[arg0->unk3BA4][arg0->unk3BB4];
    if (arg0->unk3BA4 != 0) {
        arg0->unk3F84 = (arg0->unk3F7C * 144) / arg0->unk3F80;
    } else {
        arg0->unk3F84 = (arg0->unk3F7C * 72) / arg0->unk3F80;
    }
    arg0->unk3F88 = (arg0->unk3F84 + arg0->unk3BB8) - (arg0->unk2068 + arg0->unk206C);
    return 1;
}
s32 func_151F78B4(AudInst *arg0) {
    s32 sp954;
    s32 sp950;
    s32 sp94C;
    s32 sp948;
    s32 sp944;
    s32 sp940;
    s32 sp93C;
    s32 sp938;
    s16 *sp934;
    f32 sp34[32][18];
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    s32 sp24;
    s32 sp20;

    sp950 = 0;
    sp934 = (s16 *)arg0->unk2070[arg0->unk3BA0];
    sp954 = func_151F7F60(arg0);
    if (sp954 == 0) {
        return 0;
    }
    arg0->unk2020 = (sp954 - arg0->unk3BF4) * 8;
    if (arg0->unk2020 < 0) {
        return 1;
    }
    for (sp94C = 0; sp94C < arg0->unk3F8C; sp94C++) {
        func_151F63C4((AudFrm *)arg0, sp950, sp94C);
        func_151F42E8((AudRqt *)arg0, sp950, sp94C);
    }
    func_151F6970((AudX6970 *)arg0, sp950);
    if ((arg0->unk3C98[sp950][0] != 0) && (arg0->unk3CA0[sp950][0] == 2)) {
        sp948 = 0x20;
    } else {
        sp944 = ((arg0->unk465C[0] - 1) / 0x12) + 1;
        sp948 = sp944;
    }
    for (sp94C = 0; sp94C < arg0->unk3F8C; sp94C++) {
        func_151F6B28((AudState151F6B28 *)arg0, sp950, sp94C);
        if ((arg0->unk3C98[sp950][sp94C] != 0) && (arg0->unk3CA0[sp950][sp94C] == 2) &&
            (arg0->unk3CA8[sp950][sp94C] != 0)) {
            sp940 = 0;
        } else if (arg0->unk3C98[sp950][sp94C] == 0) {
            sp940 = 0;
        } else {
            sp940 = arg0->unk3CA0[sp950][sp94C];
        }
        if (sp940 == 2) {
            for (sp93C = 0; sp93C < 2; sp93C++) {
                func_151F9BF0(arg0->unk4F64[sp94C][sp93C], sp93C, sp34[sp93C],
                              arg0->unk6A64[sp94C][sp93C]);
            }
        } else {
            for (sp93C = 0; sp93C < 2; sp93C++) {
                func_151F8CF0(arg0->unk4F64[sp94C][sp93C], sp93C, sp34[sp93C],
                              arg0->unk6A64[sp94C][sp93C], D_800E0E38[sp940]);
            }
        }
        if ((arg0->unk3C98[sp950][sp94C] != 0) && (arg0->unk3CA0[sp950][sp94C] == 2) &&
            (arg0->unk3CA8[sp950][sp94C] != 0)) {
            sp940 = 2;
        }
        if (sp940 == 2) {
            for (sp93C = 2; sp93C < sp948; sp93C++) {
                func_151F9BF0(arg0->unk4F64[sp94C][sp93C], sp93C, sp34[sp93C],
                              arg0->unk6A64[sp94C][sp93C]);
            }
        } else {
            for (sp93C = 2; sp93C < sp948; sp93C++) {
                func_151F8CF0(arg0->unk4F64[sp94C][sp93C], sp93C, sp34[sp93C],
                              arg0->unk6A64[sp94C][sp93C], D_800E0E38[sp940]);
            }
        }
        while (sp93C < 0x20) {
            bcopy(arg0->unk6A64[sp94C][sp93C], sp34[sp93C], 0x48);
            bzero(arg0->unk6A64[sp94C][sp93C], 0x48);
            sp93C++;
        }
        sp30 = 65536.0f;
        sp28 = 1.0f;
        sp20 = (s32)((sp30 * sp28) * 16.0f);
        *sp934 = sp20 >> 16;
        sp934++;
        *sp934 = sp20 & 0xFFFF;
        sp934++;
        sp20 = -sp20;
        *sp934 = sp20 >> 16;
        sp934++;
        *sp934 = sp20 & 0xFFFF;
        sp934++;
        sp2C = 2048.0f / sp28;
        for (sp938 = 0; sp938 < 0x12; sp938++) {
            for (sp93C = 0; sp93C < 0x20; sp93C++) {
                sp24 = (s32)(sp34[sp93C][sp938] * sp2C);
                *sp934 = sp24;
                sp934++;
            }
        }
    }
    return 1;
}

s32 func_151F7F60(AudInst *arg0) {
    s32 sp1C;
    s32 sp18;

    sp1C = 0x1000;
    if ((arg0->unk201C + arg0->unk3F88) >= 0x1FFC) {
        bcopy(&arg0->unk001C[sp1C], &arg0->unk001C[0], sp1C);
        arg0->unk201C -= sp1C;
        arg0->unk2020 -= sp1C * 8;
    }
    sp18 = arg0->unk0004(arg0->unk0000, &arg0->unk001C[arg0->unk201C], arg0->unk3F88, -1);
    if (sp18 < arg0->unk3F88) {
        bzero(&arg0->unk001C[sp18], arg0->unk3F88 - sp18);
    }
    arg0->unk0018 += arg0->unk3F88;
    arg0->unk201C += arg0->unk3F88;
    return arg0->unk201C - arg0->unk3F88;
}

s32 func_151F8088(AudInst *arg0, s32 arg1) {
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    u8 sp1B;

    if (arg1 != -1) {
        arg0->unk0018 = arg1;
    }
    sp24 = arg1;
    sp20 = 0;
    sp1B = 0xFF;
    while (1) {
        sp1C = arg0->unk0004(arg0->unk0000, &arg0->unk2024[sp20], 1, sp24);
        if (sp1C <= 0) {
            return 0;
        }
        sp24 = -1;
        arg0->unk0018++;
        if ((arg0->unk2024[sp20] != 0xFF) && (arg0->unk2024[sp20] != 0xF3)) {
            return 0;
        }
        if ((arg0->unk2024[sp20] & sp1B) != sp1B) {
            sp1B = 0xFF;
            sp20 = 0;
            continue;
        }
        sp20++;
        if (sp1B == 0xF0) {
            break;
        }
        sp1B = 0xF0;
    }
    sp1C = arg0->unk0004(arg0->unk0000, &arg0->unk2024[2], 2, -1);
    if (sp1C <= 0) {
        return 0;
    }
    arg0->unk0018 += 2;
    arg0->unk2064 = 0xC;
    arg0->unk3BA4 = func_151F8960(arg0->unk2024, &arg0->unk2064, 1);
    arg0->unk3BA8 = func_151F8960(arg0->unk2024, &arg0->unk2064, 2);
    arg0->unk3BAC = func_151F8960(arg0->unk2024, &arg0->unk2064, 1);
    arg0->unk3BB0 = func_151F8960(arg0->unk2024, &arg0->unk2064, 4);
    arg0->unk3BB4 = func_151F8960(arg0->unk2024, &arg0->unk2064, 2);
    arg0->unk3BB8 = func_151F8960(arg0->unk2024, &arg0->unk2064, 1);
    arg0->unk3BBC = func_151F8960(arg0->unk2024, &arg0->unk2064, 1);
    arg0->unk3BC0 = func_151F8960(arg0->unk2024, &arg0->unk2064, 2);
    arg0->unk3BC4 = func_151F8960(arg0->unk2024, &arg0->unk2064, 2);
    arg0->unk3BC8 = func_151F8960(arg0->unk2024, &arg0->unk2064, 1);
    arg0->unk3BCC = func_151F8960(arg0->unk2024, &arg0->unk2064, 1);
    arg0->unk3BD0 = func_151F8960(arg0->unk2024, &arg0->unk2064, 2);
    if ((arg0->unk3BB0 == 0xF) || (arg0->unk3BB4 == 3)) {
        return func_151F8088(arg0, -1);
    }
    if (arg0->unk3BD4 == 0) {
        arg0->unk3BD4 = 1;
        arg0->unk3BD8 = arg0->unk3BA4;
        arg0->unk3BDC = arg0->unk3BA8;
        arg0->unk3BE0 = arg0->unk3BAC;
        arg0->unk3BE4 = arg0->unk3BB4;
        arg0->unk3BE8 = arg0->unk3BC0;
        arg0->unk3BEC = arg0->unk3BC8;
        arg0->unk3BF0 = arg0->unk3BCC;
    } else if ((arg0->unk3BA4 != arg0->unk3BD8) || (arg0->unk3BA8 != arg0->unk3BDC) ||
               (arg0->unk3BAC != arg0->unk3BE0) || (arg0->unk3BB4 != arg0->unk3BE4) ||
               (arg0->unk3BC0 != arg0->unk3BE8) || (arg0->unk3BCC != arg0->unk3BF0)) {
        return func_151F8088(arg0, -1);
    }
    arg0->unk2068 = 4;
    if (arg0->unk3BAC == 0) {
        sp1C = arg0->unk0004(arg0->unk0000, &arg0->unk2024[4], 2, -1);
        if (sp1C <= 0) {
            return 0;
        }
        arg0->unk0018 += 2;
        arg0->unk2064 += 0x10;
        arg0->unk2068 = 6;
    }
    if (arg0->unk3BA8 == 1) {
        arg0->unk8478 = func_151F78B4;
        arg0->unk847C = func_151F6FD0;
    } else if (arg0->unk3BA8 == 2) {
        return 0;
    } else if (arg0->unk3BA8 == 3) {
        return 0;
    }
    if (arg0->unk847C(arg0) == 0) {
        return 0;
    }
    return 1;
}

AudInst *func_151F85C4(s32 arg0, AudReadFn arg1, s32 arg2) {
    AudInst *sp1C;

    sp1C = &D_800E1880;
    if (sp1C == NULL) {
        return NULL;
    }
    sp1C->unk000C = -1;
    sp1C->unk0010 = -1;
    sp1C->unk0014 = -1;
    sp1C->unk0000 = arg0;
    sp1C->unk0004 = arg1;
    sp1C->unk0008 = arg2;
    sp1C->unk201C = 0;
    sp1C->unk2020 = 0;
    sp1C->unk3BA0 = 0;
    if (func_151F8088(sp1C, 0) == 0) {
        return NULL;
    }
    sp1C->unk8474 = 0;
    bzero(sp1C->unk6A64, 0x900);
    return sp1C;
}

s32 func_151F86B0(AudInst *arg0, u8 **arg1, s32 *arg2) {
    AudInst *sp12C;
    s32 sp128;
    u8 sp28[0x100];
    s32 sp24;

    sp12C = arg0;
    sp12C->unk3BA0++;
    if (sp12C->unk3BA0 >= 6) {
        sp12C->unk3BA0 = 0;
    }
    if (func_151F8088(sp12C, sp12C->unk8474) == 0) {
        D_800E0E04 = 3;
        return 0;
    }
    sp12C->unk8474 = -1;
    sp128 = sp12C->unk8478(sp12C);
    if (sp128 == 0) {
        goto end;
    }
    *arg1 = sp12C->unk2070[sp12C->unk3BA0];
    *arg2 = sp12C->unk3F8C;
    if (sp12C->unk3BC8 != 0) {
        sp24 = 0;
        do {
            if (sp12C->unk0004(sp12C->unk0000, &sp28[sp24], 1, -1) == 0) {
                break;
            }
        } while (sp28[sp24++]);
        if (D_800E0E00 != NULL) {
            D_800E0E00(0, sp28, strlen(sp28) + 1);
        }
    }
end:
    return sp128;
}

