extern void func_150A7DA0(f32 mf[4][4], f32 arg1, f32 arg2, f32 arg3);
extern void func_150A7A48(f32 a[4][4], f32 b[4][4], f32 c[4][4]);
extern void guMtxF2L2(f32 mf[4][4], Mtx *m);
extern void func_15187D6C(f32 mf[4][4], f32 arg1, f32 arg2, f32 arg3);

extern u8 D_800BE9C0;
extern Vtx D_8008D538[];

typedef struct {
    Mtx mtx[2];   /* 0x00 */
    f32 unk80;    /* 0x80 */
    f32 unk84;    /* 0x84 */
    f32 unk88;    /* 0x88 */
    f32 unk8C;    /* 0x8C */
    f32 unk90;    /* 0x90 */
    s16 unk94;    /* 0x94 */
    s16 unk96;    /* 0x96 */
    u8  unk98;    /* 0x98 */
    u8  pad99[7];
} Segment15187A98;  /* size 0xA0 */

typedef struct {
    u8  pad0[0x10];
    Mtx mtx[2];              /* 0x10 */
    f32 unk90;               /* 0x90 */
    f32 unk94;               /* 0x94 */
    f32 unk98;               /* 0x98 */
    f32 unk9C;               /* 0x9C */
    f32 unkA0;               /* 0xA0 */
    Segment15187A98 *unkA4;  /* 0xA4 */
    s16 unkA8;               /* 0xA8 */
    s16 unkAA;               /* 0xAA */
} Rope15187A98;

Gfx *func_15187A98(Gfx *gfx, Rope15187A98 *arg1, s32 arg2) {
    s32 i;
    s32 life;
    f32 mf[4][4];
    f32 mf2[4][4];
    s32 alpha;

    arg2 = arg2;

    if (arg1->unkA8 >= 0) {
        func_150A7DA0(mf, arg1->unk90, arg1->unk94, arg1->unk98);
        guMtxF2L2(mf, &arg1->mtx[D_800BE9C0]);

        for (i = 0; i < 12; i++) {
            gSPMatrix(gfx++, &arg1->mtx[D_800BE9C0], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);

            func_150A7DA0(mf, arg1->unkA4[i].unk90, 0.0f, 0.0f);
            mf[0][0] *= arg1->unkA0;
            mf[1][1] *= arg1->unk9C;
            mf[2][2] *= arg1->unk9C;

            if (arg1->unkA4[i].unk98 == 0) {
                func_150A8050(mf2, arg1->unkA4[i].unk80, arg1->unkA4[i].unk84, arg1->unkA4[i].unk88);
            } else {
                func_15187D6C(mf2, arg1->unkA4[i].unk80, arg1->unkA4[i].unk84, arg1->unkA4[i].unk88);
            }
            func_150A7A48(mf, mf2, mf);
            guMtxF2L(mf, &arg1->unkA4[i].mtx[D_800BE9C0]);

            life = arg1->unkA4[i].unk96;
            alpha = (life - arg1->unkA4[i].unk94) * 255 / life;
            gDPSetPrimColor(gfx++, 1, 0, 255, 255, 255, alpha);
            gSPMatrix(gfx++, &arg1->unkA4[i].mtx[D_800BE9C0], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
            gSPVertex(gfx++, D_8008D538, 4, 0);
            gSP1Triangle(gfx++, 0, 1, 2, 0);
            gSP1Triangle(gfx++, 0, 1, 3, 0);
            gSP1Triangle(gfx++, 0, 2, 3, 0);
        }
    }

    return gfx;
}
