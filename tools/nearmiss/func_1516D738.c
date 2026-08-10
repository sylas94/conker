struct Anim1516D738 {
    u8 pad0[0xA];
    u8 unkA;
};

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    u8 unkA;
    u8 unkB;
    u8 unkC;
    u8 unkD;
    u8 unkE[6];
} Pt1516D738;

extern struct Anim1516D738 *D_8008CA4C[];
extern s32 D_800D2C9C;
extern u8 D_800D2DA8;
extern u8 D_800D2DA9;
extern u8 D_800D2DAA;
extern s16 D_800DD1BC;
extern s16 D_800DD1C8;
extern s16 D_800DD1CA;
extern s16 D_800DD1CC;

extern Gfx *func_15142E24(Gfx *, s32, s32, s32, s32, s32, s32, u8, s32, u8 *, s32);
extern Gfx *func_15142FBC(Gfx *, s32, s32, u8 *);
extern s32 func_15095760(Gfx *, Pt1516D738 *);

Gfx *func_1516D738(Gfx *arg0, struct Obj1516D4E8 *arg1, s32 arg2) {
    Pt1516D738 sp84;
    Gfx *gfx;
    struct {
        s32 sync;
        struct Anim1516D738 *anim;
    } st;
    s32 combiner;
    s32 r;
    s32 g;
    s32 b;
    s32 frame;
    s32 otherModeH;
    s32 cycleType;
    s32 otherModeL;


    st.sync = 0;
    otherModeL = G_RM_AA_ZB_XLU_SURF | G_RM_AA_ZB_XLU_SURF2 | G_ZS_PRIM;
    D_800D2DAB = 0;
    st.anim = D_8008CA4C[arg1->unk1A];
    frame = arg1->unk1B;

    gfx = func_15142E24(arg0, (s32) st.anim, frame << 8, 2, 0x100, 0x100, 0, 6, (s32) &sp84,
                        (u8 *) &st.sync, 3);

    combiner = (st.anim->unkA == 5) ? 2 : 1;
    if (combiner != (&D_800DD1BC)[0]) {
        if (st.sync == 0) {
            gDPPipeSync(gfx++);
            st.sync = 1;
        }

        (&D_800DD1BC)[0] = combiner;
        if (combiner == 1) {
            cycleType = G_CYC_1CYCLE;
            gDPSetCombineLERP(gfx++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, PRIMITIVE, 0, TEXEL0, 0,
                              PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, PRIMITIVE, 0, TEXEL0, 0);
        } else {
            cycleType = G_CYC_2CYCLE;
            gDPSetCombineLERP(gfx++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, PRIMITIVE, 0, TEXEL1, 0,
                              0, 0, 0, COMBINED, 0, 0, 0, COMBINED);
        }
    }

    otherModeH = cycleType | D_800D2C9C;
    gfx = func_15142FBC(gfx, otherModeH | (G_TF_BILERP | G_TC_FILT), otherModeL, (u8 *) &st.sync);

    sp84.unk0 = arg1->unkE;
    sp84.unk2 = arg1->unk10;
    sp84.unk4 = arg1->unk12;
    sp84.unk6 = arg1->unk14;
    sp84.unk8 = arg1->unk16;
    sp84.unkA = arg1->unk1F;
    sp84.unkD = 0;

    D_800D2DA8 = arg1->unk1C;
    D_800D2DA9 = arg1->unk1D;
    D_800D2DAA = arg1->unk1E;

    r = arg1->unk20;
    g = arg1->unk21;
    b = arg1->unk22;

    if ((r != (&D_800DD1C8)[0]) || (g != D_800DD1CA) || (b != D_800DD1CC)) {
        (&D_800DD1C8)[0] = r;
        D_800DD1CA = g;
        D_800DD1CC = b;

        if (st.sync == 0) {
            gDPPipeSync(gfx++);
        }

        gDPSetEnvColor(gfx++, r, g, b, 0);
    }

    return (Gfx *) func_15095760(gfx, &sp84);
}
