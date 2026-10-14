typedef struct {
    Mtx mtx[2];
    f32 rotX;
    f32 rotY;
    f32 rotZ;
    u8 pad8C[4];
    f32 offset;
    s16 time;
    s16 duration;
    u8 euler;
    u8 pad99[7];
} Petal15187A98;

typedef struct {
    u8 pad0[0x10];
    Mtx mtx[2];
    f32 x;
    f32 y;
    f32 z;
    f32 scaleYZ;
    f32 scaleX;
    Petal15187A98 *petals;
    s16 state;
} Flower15187A98;

extern Vtx D_8008D538[];
extern void func_150A7DA0(f32 arg0[4][4], f32 arg1, f32 arg2, f32 arg3);
extern void func_150A7A48(f32 a[4][4], f32 b[4][4], f32 c[4][4]);
extern void guMtxF2L2(f32 mf[4][4], Mtx *m);
void func_15187D6C(f32 m[4][4], f32 x, f32 y, f32 z);

Gfx *func_15187A98(Gfx *gfx, Flower15187A98 *arg1, s32 arg2) {
    s32 i;
    s32 alpha;
    s32 dur;
    f32 base[4][4];
    f32 rot[4][4];

    if (arg1->state >= 0) {
        func_150A7DA0(base, arg1->x, arg1->y, arg1->z);
        guMtxF2L2(base, &arg1->mtx[D_800BE9C0]);
        for (i = 0; i < 12; i++) {
            gSPMatrix(gfx++, &arg1->mtx[D_800BE9C0], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            func_150A7DA0(base, arg1->petals[i].offset, 0.0f, 0.0f);
            base[0][0] *= arg1->scaleX;
            base[1][1] *= arg1->scaleYZ;
            base[2][2] *= arg1->scaleYZ;
                if (arg1->petals[i].euler == 0) {
                func_150A8050(rot, arg1->petals[i].rotX, arg1->petals[i].rotY, arg1->petals[i].rotZ);
            } else {
                func_15187D6C(rot, arg1->petals[i].rotX, arg1->petals[i].rotY, arg1->petals[i].rotZ);
            }
            func_150A7A48(base, rot, base);
            guMtxF2L(base, &arg1->petals[i].mtx[D_800BE9C0]);
                dur = arg1->petals[i].duration;
            alpha = ((dur - arg1->petals[i].time) * 255) / dur;
            gDPSetPrimColor(gfx++, 1, 0, 0xFF, 0xFF, 0xFF, alpha);
            gSPMatrix(gfx++, &arg1->petals[i].mtx[D_800BE9C0], G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
            gSPVertex(gfx++, D_8008D538, 4, 0);
            gSP1Triangle(gfx++, 0, 1, 2, 0);
            gSP1Triangle(gfx++, 0, 1, 3, 0);
            gSP1Triangle(gfx++, 0, 2, 3, 0);
        }
    }
    return gfx;
}
