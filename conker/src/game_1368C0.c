#include <ultra64.h>
#include "functions.h"
#include "variables.h"

struct Vec3F15109C20 {
    f32 x;
    f32 y;
    f32 z;
};

struct Arg15109C20 {
    u8 pad0;
    u8 unk1;
    u8 pad2[0xA];
    u8 unkC;
    u8 padD[0x6];
    u8 unk13;
    u8 pad14[0x14];
    void *unk28;
};

struct Arg15109C20Sub {
    u8 pad0[0x3B];
    u8 unk3B;
};

typedef struct {
    s32 unk0;
    s32 unk4;
    u8 unk8;
    u8 unk9;
} GameStruct1510A8CCa;

typedef struct {
    s32 unk0;
    u8 unk4;
} GameStruct1510A8CCb;

extern void func_15132A4C(void *, s32, s32, s32, u8, s32);


struct260 *func_15109410(void *arg0, s16 arg1, s8 arg2, s8 arg3, f32 arg4, s32 arg5, u8 arg6, s32 arg7) {
    struct260 *temp_v0;
    struct {
        void *unk0;
        u8 unk4;
        u8 pad5;
        u8 pad6;
        u8 pad7;
        f32 unk8;
        f32 unkC;
        u8 unk10;
        u8 unk11;
    } sp38;
    s16 sp44;
    u8 sp40;

    if (arg0 == NULL) {
        return NULL;
    }

    sp40 = 0;
    if (arg1 < 0) {
        sp44 = 0x12C;
    } else {
        sp40 = 1;
        sp44 = (s16)arg1;
    }

    sp38.unk8 = 0.0f;
    sp38.unkC = arg4;
    sp38.unk10 = arg2;
    sp38.unk11 = arg3;
    sp38.unk0 = arg0;
    sp38.unk4 = *(u8 *)((s32)arg0 + 0x3B);

    temp_v0 = func_15149130(sp44, -1, 0x1A, -1, sp40, 0x1A, (struct37 *)((s32)arg5 + 0x14), arg6, arg7);
    if (temp_v0 != NULL) {
        memcpy((void *)((s32)temp_v0 + 0x28), &sp38, 0x14);
    }
    return temp_v0;
}

typedef struct {
    s32 unk0;
    u8 pad4[0x37];
    u8 unk3B;
    u8 pad3C[0x1D4 - 0x3C];
    s32 unk1D4;
} Obj1368C0;

typedef struct {
    Obj1368C0 *unk0;
    u8 unk4;
    f32 unk8;
    f32 unkC;
    s8 unk10;
    s8 unk11;
} State151094FC;

typedef struct {
    u8 pad0[0xE];
    s16 unkE;
    u8 pad10[0x18];
    State151094FC unk28;
} Actor151094FC;

static const struct Vec3F15109C20 D_800A24B0[7] = {
    { 10.0f, -2.0f, 73.0f },
    { 10.0f, 7.0f, 211.0f },
    { 10.0f, 0.0f, 231.0f },
    { 10.0f, -17.0f, 238.0f },
    { 10.0f, -36.0f, 231.0f },
    { 10.0f, -41.0f, 209.0f },
    { 10.0f, -34.0f, 78.0f },
};

static const f32 D_800A2504[7] = {
    138.2931213f, 21.18962097f, 18.38477707f, 20.24845695f, 22.56102753f, 131.1868896f, 351.8638916f,
};

static const struct Vec3F15109C20 D_800A2520[6] = {
    { 10.0f, 22.0f, 211.0f },
    { 10.0f, 7.0f, 236.0f },
    { 10.0f, -19.0f, 248.0f },
    { 10.0f, -40.0f, 243.0f },
    { 10.0f, -50.0f, 213.0f },
    { 10.0f, -47.0f, 79.0f },
};

extern void (*D_80088C60[])(void *);
extern void (*D_80088C64[])(void *, struct Vec3F15109C20 *, struct Vec3F15109C20 *, struct Vec3F15109C20 *, struct Vec3F15109C20 *, struct Vec3F15109C20 *);
extern void func_15143134(const void *, void *, s32);
extern s32 func_15145128(void *, void *, f32 *, f32 *);

void func_151094FC(Actor151094FC *arg0) {
    State151094FC *state;
    Obj1368C0 *obj;
    struct Vec3F15109C20 a;
    struct Vec3F15109C20 b;
    struct Vec3F15109C20 c;
    struct Vec3F15109C20 d;
    struct Vec3F15109C20 e;
    struct Vec3F15109C20 pos;
    const struct Vec3F15109C20 *p;
    s32 m;
    s32 i;
    f32 r;
    f32 t;

    state = &arg0->unk28;
    obj = state->unk0;
    if (obj->unk0 == 0 || obj->unk3B != state->unk4) {
        arg0->unkE = -1;
        return;
    }
    state->unk8 += state->unkC * D_800A2504[6] * D_800BE9A4;
    if (state->unk11 != -1 && obj->unk1D4 != 0) {
        while (state->unk8 > 1.0f) {
            r = func_150ADA68() * D_800A2504[6];
            for (i = 0; D_800A2504[i] < r; i++) {
                r -= D_800A2504[i];
            }
            t = func_150ADA68();
            p = &D_800A24B0[i];
            pos.x = p[0].x + (p[1].x - p[0].x) * t;
            pos.y = p[0].y + (p[1].y - p[0].y) * t;
            pos.z = p[0].z + (p[1].z - p[0].z) * t;
            m = obj->unk1D4 + 0x240;
            func_15143134(&pos, &a, m);
            func_15143134(&p[0], &b, m);
            func_15143134(&p[1], &c, m);
            func_15143134(&D_800A2520[i], &d, m);
            t = func_150ADA68();
            e.x = (d.x - c.x) * t + c.x - b.x;
            e.y = (d.y - c.y) * t + c.y - b.y;
            e.z = (d.z - c.z) * t + c.z - b.z;
            func_15145128(&e, &e, NULL, NULL);
            D_80088C64[state->unk11](arg0, &a, &b, &c, &d, &e);
            state->unk8 -= 1.0f;
        }
    } else {
        while (state->unk8 > 1.0f) {
            state->unk8 -= 1.0f;
        }
    }
    if (state->unk10 != -1) {
        D_80088C60[state->unk10](arg0);
    }
}

typedef struct {
    s32 unk00;
    s32 unk04;
    s16 unk08;
    s16 unk0A;
    s32 unk0C;
    s32 unk10;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 unk17;
    u8 unk18;
    u8 unk19;
    u8 unk1A;
    u8 unk1B;
    u8 unk1C;
    u8 unk1D;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    struct Vec3F15109C20 unk30;
    f32 unk3C;
    f32 unk40;
    f32 unk44;
    f32 unk48;
    f32 unk4C;
    f32 unk50;
    f32 unk54;
    s32 unk58;
    u8 pad5C[4];
    u8 unk60;
    u8 unk61;
    s8 unk62;
    s8 unk63;
    s8 unk64;
    u8 unk65;
    u8 pad66[0xA];
} Effect15130374;

typedef struct {
    s32 unk0;
    s32 unk4;
    struct Vec3F15109C20 unk8;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    s16 unk2C;
    s16 unk2E;
    s16 unk30;
    s16 unk32;
    s32 unk34;
    s32 unk38;
    s16 unk3C;
    s16 unk3E;
    u16 unk40;
    u8 unk42;
    u8 unk43;
    u8 unk44;
    u8 unk45;
    u8 unk46;
    u8 unk47;
    u8 unk48;
    u8 unk49;
    u8 unk4A;
    u8 unk4B;
    u8 unk4C;
    u8 unk4D;
    u8 unk4E;
    u8 unk4F;
    u8 unk50;
    u8 unk51;
    u8 unk52;
    u8 unk53;
    u8 unk54;
    u8 unk55;
    u8 unk56;
    u8 unk57;
    u8 unk58;
    u8 pad59[3];
    s32 unk5C;
    s32 unk60;
    s16 unk64;
    s16 unk66;
    s16 unk68;
    u8 unk6A;
    u8 pad6B;
    f32 unk6C;
    s8 unk70;
    s8 unk71;
    s8 unk72;
    s8 unk73;
} Spawn15152B38;

extern struct260 *func_15130374(void *, u8, s32, u8, s32);
extern void func_15152B38(void *, u8, s32);

#pragma GLOBAL_ASM("asm/nonmatchings/game_1368C0/func_15109848.s")

void func_15109C20(struct Arg15109C20 *arg0, struct Vec3F15109C20 *arg1, s32 arg2, s32 arg3, s32 arg4, struct Vec3F15109C20 *arg5) {
    s32 padA4;
    struct Arg15109C20Sub *sub;
    f32 scale;
    s32 pad98;
    struct {
        f32 unk00;
        f32 unk04;
        f32 unk08;
        f32 unk0C;
        f32 unk10;
        f32 unk14;
        f32 unk18;
        f32 unk1C;
        f32 unk20;
        f32 unk24;
        struct Vec3F15109C20 unk28;
        f32 unk34;
        f32 unk38;
        f32 unk3C;
        f32 unk40;
        f32 unk44;
        f32 unk48;
        f32 unk4C;
        s32 unk50;
        s16 unk54;
        s16 unk56;
        u8 unk58;
        u8 pad59[3];
        s32 unk5C;
        u8 unk60;
        u8 unk61;
        u8 unk62;
        u8 unk63;
        u8 unk64;
        u8 unk65;
        u8 unk66;
        u8 unk67;
        u8 unk68;
        u8 pad69;
        u8 unk6A;
        u8 pad6B;
        struct Arg15109C20Sub *unk6C;
        u8 unk70;
        u8 pad71;
        s16 unk72;
        s16 unk74;
        u8 pad76[2];
    } sp20;

    sub = arg0->unk28;
    scale = ((func_150ADA68() * 4611.0f) + 1581.0f) * 0.001f;
    sp20.unk00 = 1.0f;
    sp20.unk04 = 1.0f;
    sp20.unk08 = sp20.unk0C = ((func_150ADA68() * 3522.0f) + 4599.0f) * 1e-6f;
    sp20.unk10 = func_150ADA68() * 360.0f;
    sp20.unk14 = func_150ADA68() * 360.0f;
    sp20.unk18 = func_150ADA68() * 360.0f;
    sp20.unk1C = 1.0f;
    sp20.unk20 = 1.0f;
    sp20.unk24 = 1.0f;
    sp20.unk28 = *arg1;
    sp20.unk34 = arg5->x * scale;
    sp20.unk38 = arg5->y * scale;
    sp20.unk3C = arg5->z * scale;
    sp20.unk40 = ((func_150ADA68() * 24546.0f) + -12273.0f) * 0.001f;
    sp20.unk44 = 0.0f;
    sp20.unk48 = ((func_150ADA68() * 24546.0f) + -12273.0f) * 0.001f;
    sp20.unk4C = ((func_150ADA68() * 124.0f) + -231.0f) * 0.001f;
    sp20.unk50 = 0x29E8;
    sp20.unk54 = (func_150ADA20() % 15U) + 0x14;

    if (func_150ADA20() & 1) {
        sp20.unk56 = 0x23;
    } else {
        sp20.unk56 = 0x24;
    }

    sp20.unk58 = 0;
    sp20.unk5C = 0;
    sp20.unk60 = 0xFF;
    sp20.unk61 = 8;
    sp20.unk62 = 0;
    sp20.unk63 = 0;
    sp20.unk64 = 0;
    sp20.unk65 = 0;
    sp20.unk66 = 0;
    sp20.unk67 = 0;
    sp20.unk68 = 2;
    if (arg0->unk13 == 0x1A) {
        sp20.unk6A = 1;
    } else {
        sp20.unk6A = 2;
    }
    sp20.unk6C = sub;
    sp20.unk70 = sub->unk3B;
    sp20.unk72 = 0xA;
    sp20.unk74 = 0x19;

    func_15132A4C(&sp20, 3, 0xFF, 0, arg0->unkC, arg0->unk1);
}

struct260 *func_15109ED4(void *arg0, s16 arg1, s8 arg2, s8 arg3, f32 arg4, s32 arg5, u8 arg6, s32 arg7) {
    struct260 *temp_v0;
    struct {
        void *unk0;
        f32 unk4;
        f32 unk8;
        u8 unkC;
        u8 unkD;
    } sp34;
    s16 sp44;
    u8 sp40;

    if (arg0 == NULL) {
        return NULL;
    }

    sp40 = 0;
    if (arg1 < 0) {
        sp44 = 0x12C;
    } else {
        sp40 = 1;
        sp44 = (s16)arg1;
    }

    sp34.unk4 = 0.0f;
    sp34.unk8 = arg4;
    sp34.unkC = arg2;
    sp34.unkD = arg3;
    sp34.unk0 = arg0;

    temp_v0 = func_15149130(sp44, -1, 0x1B, -1, sp40, 0x1B, (struct37 *)((s32)arg5 + 0x10), arg6, arg7);
    if (temp_v0 != NULL) {
        memcpy((void *)((s32)temp_v0 + 0x28), &sp34, 0x10);
    }
    return temp_v0;
}

static const struct Vec3F15109C20 D_800A2568[7] = {
    { 0.0f, 6.764999866485596f, -3.0f },
    { 0.0f, 10.824000358581543f, 79.80000305175781f },
    { 0.0f, 7.6670002937316895f, 91.80000305175781f },
    { 0.0f, 0.0f, 96.0f },
    { 0.0f, -8.569000244140625f, 91.80000305175781f },
    { 0.0f, -10.824000358581543f, 78.60000610351562f },
    { 0.0f, -7.6670002937316895f, 0.0f },
};

static const struct Vec3F15109C20 D_800A25BC[6] = {
    { 0.0f, 17.589000701904297f, 79.80000305175781f },
    { 0.0f, 10.824000358581543f, 94.80000305175781f },
    { 0.0f, -0.9020000100135803f, 102.00000762939453f },
    { 0.0f, -10.373000144958496f, 99.00000762939453f },
    { 0.0f, -14.883000373840332f, 81.0f },
    { 0.0f, -13.529999732971191f, 0.6000000238418579f },
};

typedef struct {
    void *unk0;
    f32 unk4;
    f32 unk8;
    s8 unkC;
    s8 unkD;
} State15109FB8;

typedef struct {
    u8 pad0[0x28];
    State15109FB8 unk28;
} Actor15109FB8;

extern void func_1511490C(f32 arg0[4][4], void *arg1);
extern void func_150A7960(f32 *, f32, f32, f32, f32 *, f32 *, f32 *);

void func_15109FB8(Actor15109FB8 *arg0) {
    State15109FB8 *state;

    state = &arg0->unk28;
    state->unk4 += state->unk8 * D_800A2504[6] * D_800BE9A4;
    if (state->unkD != -1) {
        while (state->unk4 > 1.0f) {
            f32 mtx[4][4];
            struct Vec3F15109C20 a;
            struct Vec3F15109C20 b;
            struct Vec3F15109C20 c;
            struct Vec3F15109C20 d;
            struct Vec3F15109C20 e;
            const struct Vec3F15109C20 *p;
            s32 i;
            f32 r;
            f32 t;
            f32 x;
            f32 y;
            f32 z;

            func_1511490C(mtx, state->unk0);
            r = func_150ADA68() * D_800A2504[6];
            for (i = 0; D_800A2504[i] < r; i++) {
                r -= D_800A2504[i];
            }
            t = func_150ADA68();
            p = &D_800A2568[i];
            x = p[0].x + (p[1].x - p[0].x) * t;
            y = p[0].y + (p[1].y - p[0].y) * t;
            z = p[0].z + (p[1].z - p[0].z) * t;
            func_150A7960((f32 *)mtx, x, y, z, &a.x, &a.y, &a.z);
            func_150A7960((f32 *)mtx, p[0].x, p[0].y, p[0].z, &b.x, &b.y, &b.z);
            func_150A7960((f32 *)mtx, p[1].x, p[1].y, p[1].z, &c.x, &c.y, &c.z);
            func_150A7960((f32 *)mtx, D_800A25BC[i].x, D_800A25BC[i].y, D_800A25BC[i].z, &d.x, &d.y, &d.z);
            t = func_150ADA68();
            e.x = (d.x - c.x) * t + c.x - b.x;
            e.y = (d.y - c.y) * t + c.y - b.y;
            e.z = (d.z - c.z) * t + c.z - b.z;
            func_15145128(&e, &e, NULL, NULL);
            D_80088C64[state->unkD](arg0, &a, &b, &c, &d, &e);
            state->unk4 -= 1.0f;
        }
    } else {
        while (state->unk4 > 1.0f) {
            state->unk4 -= 1.0f;
        }
    }
    if (state->unkC != -1) {
        D_80088C60[state->unkC](arg0);
    }
}


struct260 *func_1510A344(void *arg0, s32 arg1, u8 arg2, s32 arg3) {
    struct260 *temp_v0;
    struct {
        void *unk0;
        u8 unk4;
        u8 pad5;
        u8 pad6;
        u8 pad7;
        f32 unk8;
        f32 unkC;
        f32 unk10;
    } sp30;

    if (arg0 == NULL) {
        return NULL;
    }

    sp30.unk0 = arg0;
    sp30.unk4 = *(u8 *)((s32)arg0 + 0x3B);
    sp30.unk8 = 0.0f;
    sp30.unkC = 0.204000011f;
    sp30.unk10 = 0.822f;

    temp_v0 = func_15149130((s16)arg1, -1, 0x1C, -1, 1, 0x1C, (struct37 *)0x14, arg2, arg3);
    if (temp_v0 != NULL) {
        memcpy((void *)((s32)temp_v0 + 0x28), &sp30, 0x14);
    }
    return temp_v0;
}

static const struct Vec3F15109C20 D_800A2604 = { -11.0f, -24.0f, 43.0f };
static const struct Vec3F15109C20 D_800A2610 = { 31.0f, -24.0f, 43.0f };
static const struct Vec3F15109C20 D_800A261C = { -51.0f, -24.0f, 43.0f };
static const struct Vec3F15109C20 D_800A2628 = { 81.0f, -24.0f, 43.0f };

/* func_15109848 is still GLOBAL_ASM: its literal pool, as named stand-ins in golden position */
const f32 D_800A2634[1] = { 851.0f };
const f32 D_800A2638[1] = { 525.0f };
const f32 D_800A263C[1] = { 0.001f };
const f32 D_800A2640[1] = { 1.05f };
const f32 D_800A2644[1] = { 1.89f };
const f32 D_800A2648[1] = { -0.815000057f };
const f32 D_800A264C[1] = { 0.577f };

typedef struct {
    Obj1368C0 *unk0;
    u8 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
} State1510A40C;

typedef struct {
    u8 pad0;
    u8 unk1;
    u8 pad2[0xA];
    u8 unkC;
    u8 padD;
    s16 unkE;
    u8 pad10[0x18];
    State1510A40C unk28;
} Actor1510A40C;

void func_1510A40C(Actor1510A40C *arg0) {
    State1510A40C *state;
    Obj1368C0 *obj;
    struct Vec3F15109C20 pts[2];
    struct Vec3F15109C20 dirs[2];
    s32 m;
    Effect15130374 fx;
    f32 val;
    f32 scale;
    u8 sel;
    struct260 *ret;

    state = &arg0->unk28;
    obj = state->unk0;
    if (obj->unk0 == 0 || obj->unk3B != state->unk4) {
        arg0->unkE = -1;
        return;
    }
    state->unk8 += (state->unkC + func_150ADA68() * state->unk10) * D_800BE9A4;
    if (state->unk8 > 1.0f && obj->unk1D4 != 0) {
        m = obj->unk1D4 + 0x240;
        func_15143134(&D_800A2604, &pts[0], m);
        func_15143134(&D_800A2610, &pts[1], m);
        func_15143134(&D_800A261C, &dirs[0], m);
        func_15143134(&D_800A2628, &dirs[1], m);
        dirs[0].x -= pts[0].x;
        dirs[0].y -= pts[0].y;
        dirs[0].z -= pts[0].z;
        dirs[1].x -= pts[1].x;
        dirs[1].y -= pts[1].y;
        dirs[1].z -= pts[1].z;
        val = 0.9108009934f;
        fx.unk1D = 0x29;
        fx.unk08 = 0xE03;
        fx.unk00 = 0x200005;
        fx.unk04 = 0;
        fx.unk0C = 0;
        fx.unk10 = 0;
        fx.unk1E = 0x19;
        fx.unk20 = 0xA;
        fx.unk58 = 0xCE05;
        fx.unk60 = 3;
        fx.unk61 = 3;
        fx.unk62 = 0x10;
        fx.unk63 = -1;
        fx.unk64 = -1;
        fx.unk65 = 0;
        fx.unk22 = 0x19;
        fx.unk14 = 0xDD;
        fx.unk15 = 0xD3;
        fx.unk16 = 0xCD;
        fx.unk17 = 0xFF;
        fx.unk18 = 0x57;
        fx.unk19 = 0x55;
        fx.unk1A = 0x5A;
        fx.unk1B = 0xFF;
        fx.unk1C = 0xFF;
        fx.unk24 = 1.043205976f;
        fx.unk3C = 0.0f;
        fx.unk40 = 0.0f;
        fx.unk44 = 0.0f;
        fx.unk54 = 0.0f;
        do {
            if (func_150ADA20() & 1) {
                fx.unk58 |= 0x40;
            } else {
                fx.unk58 &= ~0x40;
            }
            if (func_150ADA20() & 1) {
                fx.unk58 |= 0x80;
            } else {
                fx.unk58 &= ~0x80;
            }
            sel = func_150ADA20() & 1;
            scale = ((func_150ADA68() * 203.0f) + 96.0f) * 0.001f;
            fx.unk0A = (func_150ADA20() & 0xF) + 0x14;
            fx.unk28 = fx.unk2C = (func_150ADA68() * 60.0f) + 60.0f;
            fx.unk30 = pts[sel];
            fx.unk48 = dirs[sel].x * scale;
            fx.unk4C = dirs[sel].y * scale;
            fx.unk50 = dirs[sel].z * scale;
            ret = func_15130374(&fx, 1, 4, arg0->unkC, arg0->unk1);
            if (ret != NULL) {
                memcpy((u8 *)ret + 0xA8, &val, 4);
            }
            state->unk8 -= 1.0f;
        } while (state->unk8 > 1.0f);
    } else {
        while (state->unk8 > 1.0f) {
            state->unk8 -= 1.0f;
        }
    }
}

void func_1510A870(void *arg0, GameStruct1510A8CCa *arg1, u8 arg2) {
    GameStruct1510A8CCb *v0 = (GameStruct1510A8CCb *)((u8 *)arg0 + 0x28);
    if (arg2 == 0x2D) {
        if (v0->unk0 == arg1->unk0) {
            v0->unk0 = arg1->unk4;
            v0->unk4 = arg1->unk9;
        } else if (v0->unk0 == arg1->unk4) {
            v0->unk0 = arg1->unk0;
            v0->unk4 = arg1->unk8;
        }
    }
}

void func_1510A8CC(void *arg0, GameStruct1510A8CCa *arg1, u8 arg2) {
    GameStruct1510A8CCb *v0 = (GameStruct1510A8CCb *)((u8 *)arg0 + 0x28);
    if (arg2 == 0x2D) {
        if (v0->unk0 == arg1->unk0) {
            v0->unk0 = arg1->unk4;
            v0->unk4 = arg1->unk9;
        } else if (v0->unk0 == arg1->unk4) {
            v0->unk0 = arg1->unk0;
            v0->unk4 = arg1->unk8;
        }
    }
}
