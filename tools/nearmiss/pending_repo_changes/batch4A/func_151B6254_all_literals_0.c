extern f32 D_800AA454;
extern f32 D_800AA458;
extern f32 D_800AA45C;
extern f32 D_800BE9A4;
extern void func_15133894(void *);

typedef struct {
    /* 0x000 */ u8  pad0[0x18];
    /* 0x018 */ f32 unk18;
    /* 0x01C */ f32 unk1C;
    /* 0x020 */ u8  pad20[0x150];
    /* 0x170 */ f32 unk170;
    /* 0x174 */ f32 unk174;
} S151B6254;

void func_151B6254(S151B6254 *arg0) {
    f32 *p = &arg0->unk170;

    arg0->unk170 += 0.5560000539f * D_800BE9A4;
    while (6.2831855f < *p) {
        *p -= 6.2831855f;
    }
    arg0->unk18 = arg0->unk1C = sinf(p[0]) * (0.06100000441f * p[1]) + p[1];
    {
        extern void func_15133894(void *);

        func_15133894(arg0);
    }
}
