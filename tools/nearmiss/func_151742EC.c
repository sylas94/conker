/* Best attempt at func_151742EC (game_1A11B0.c) -- SCORE 2240, NOT a match.
 * Frame size 0xB8 matches; loop structure, z-decode, viewport clip and both
 * calls all line up.  Residual: s1/s2 swapped (i vs i*8), &D_800BE9C0 hoisted
 * into s8 across both loops (target re-materialises the lui in each loop, and
 * hoists 0xFFFF into s8 in loop 2 instead), s3/s4/s5 base-symbol mapping,
 * one missing `move a1,t7` in the z-decode, one `lw D_800DD300[i]` scheduled
 * early, D_800DD340 store not sunk into the beq delay slot, `beq s6,v1` vs
 * `beq v1,s6`.
 */

typedef struct {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ u8  unk0C;
    /* 0x0D */ u8  pad0D[3];
    /* 0x10 */ f32 unk10[9];
    /* 0x34 */ s8  unk34;
    /* 0x35 */ u8  pad35[3];
    /* 0x38 */ s32 unk38;
} Struct151742EC; /* size 0x3C */

typedef struct {
    /* 0x00 */ u32 shift;
    /* 0x04 */ u32 base;
} StructZDecode;

typedef struct {
    /* 0x00 */ char pad00[0x24];
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
} Struct151742ECView;

extern StructZDecode D_80089630[];
extern void (*D_8008A080[])(Struct151742EC *, s32, s32, s32);
extern s32 D_800DD300[];
extern u16 D_800DD310[][4];
extern u16 D_800DD328[][4];
extern s32 D_800DD340;
extern Struct151742EC D_800DD348[3];

Gfx *func_15173D00(Gfx *gfx, s32 arg1, s32 arg2, s32 arg3, u16 *arg4, u16 *arg5, s32 arg6);
void func_1501A764(s16 arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4, f32 *arg5, f32 *arg6);

Gfx *func_151742EC(Gfx *gfx, s32 arg1) {
    f32 sx;
    f32 sy;
    f32 sz;
    Struct151742ECView *vp;
    s32 voff;
    s16 view;
    s32 zval;
    u32 zsum;
    u32 z;
    s32 diff;
    s32 dist;
    s32 idx;
    s32 r;
    s32 g;
    s32 b;
    s32 x;
    s32 y;
    s32 i;

    if (arg1 != 0) {
        return gfx;
    }

    for (i = 0; i < 3; i++) {
        if (D_800DD348[i].unk0C == D_800BE9C0 + 1) {
            zval = D_800DD310[i][0];
            zsum = (((zval >> 2) & 0x7FF) << D_80089630[zval >> 13].shift) + D_80089630[zval >> 13].base;
            z = zsum >> 3;
            diff = z - D_800DD300[i];
            dist = (diff < 0) ? -diff : diff;
            if (dist < 300) {
                D_800DD340 = D_800DD328[i][0];
                idx = D_800DD348[i].unk34;
                r = (D_800DD340 >> 8) & 0xF8;
                g = (D_800DD340 >> 3) & 0xF8;
                b = (D_800DD340 << 2) & 0xF8;
                if (idx != -1) {
                    D_8008A080[idx](&D_800DD348[i], r, g, b);
                }
            }
            D_800DD348[i].unk0C = 0;
        }
    }

    for (i = 0; i < 3; i++) {
        if (D_800DD348[i].unk0C == 3) {
            D_800DD310[i][0] = 0xFFFF;
            D_800DD348[i].unk0C = D_800BE9C0 + 1;
            voff = arg1 * 0x180;
            view = arg1;
            func_1501A764(view, D_800DD348[i].unk00, D_800DD348[i].unk04, D_800DD348[i].unk08, &sx, &sy, &sz);
            D_800DD300[i] = (s32)sz;
            x = (s32)sx;
            y = (s32)sy;
            vp = (Struct151742ECView *)((u8 *)D_800BE628 + voff);
            if (x >= (s32)vp->unk2C && x < (s32)vp->unk30 && y >= (s32)vp->unk24 && y < (s32)vp->unk28) {
                gfx = func_15173D00(gfx, x, y, 1, D_800DD310[i], D_800DD328[i], view);
            }
        }
    }

    return gfx;
}
