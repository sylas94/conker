#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern s32 (*D_800888A0[])(struct260 *);

struct struct_150D032C_prefix {
    u8 bytes[5];
};

extern struct struct_150D032C_prefix D_800A0880;
extern f32 D_800A0888;
void func_15042D94(s32, s32, s32, u8 *);

#pragma GLOBAL_ASM("asm/nonmatchings/game_FC5F0/func_150CF140.s")

typedef struct {
    s32 unk0;
    u8  unk4;
} SubA_150CF484;

typedef struct {
    s32 unk0;
    union {
        s32 w4;
        u8  b4;
    } u4;
    u8  unk8;
    u8  unk9;
} ArgB_150CF484;

void func_150CF484(struct260 *arg0, s32 arg1, u8 arg2) {
    SubA_150CF484 *temp_v0 = (SubA_150CF484 *)((u8 *)arg0 + 0x28);
    ArgB_150CF484 *b = (ArgB_150CF484 *)arg1;
    s32 b0;

    if (arg2 == 0) {
        b0 = b->unk0;
        if ((b0 == temp_v0->unk0) || (b->u4.b4 == temp_v0->unk4)) {
            func_1516972C((struct102 *)arg0);
        }
    } else if (arg2 == 0x2D) {
        if (temp_v0->unk0 == b->unk0) {
            temp_v0->unk0 = b->u4.w4;
            temp_v0->unk4 = b->unk9;
        } else if (temp_v0->unk0 == b->u4.w4) {
            temp_v0->unk0 = b->unk0;
            temp_v0->unk4 = b->unk8;
        }
    }
}

extern void func_151CF898(struct127 *, f32, f32);

void func_150CF530(s32 arg0) {
    func_151CF898(&D_800CC2D0[0], D_800CC2D0[0].y_position + 300.0f, -10000.0f);
}

extern s8 *D_80088890;
extern s8 *D_80088894;
extern s8 *D_80088898;
extern s8 *D_8008889C;

void func_150CF578(s32 arg0) {
    D_80088890 += D_800BE9E4 * 26;
    D_80088894 -= D_800BE9E4 * 28;
    D_80088898 -= D_800BE9E4 * 28;
}

#define WGFX150CF5E8(pkt, a, b)     \
{                                   \
    Gfx *_g = (Gfx *)(pkt);         \
    _g->words.w0 = (u32)(a);        \
    _g->words.w1 = (u32)(b);        \
}

Gfx *func_150CF5E8(Gfx *arg0) {
    WGFX150CF5E8(arg0++, (0xF2000000 | ((((s32)D_80088890 >> 7) & 0xFFF) << 12) | (((s32)D_80088894 >> 7) & 0xFFF)), 0x0047E47E);
    WGFX150CF5E8(arg0++, (0xF2000000 | ((((s32)D_80088898 >> 7) & 0xFFF) << 12) | (((s32)D_8008889C >> 7) & 0xFFF)), 0x0147E47E);
    return arg0;
}

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8  unk10;
    /* 0x11 */ u8  pad11;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ u8  unk1A;
    /* 0x1B */ u8  unk1B;
    /* 0x1C */ u8  unk1C;
    /* 0x1D */ u8  unk1D;
    /* 0x1E */ u8  unk1E;
    /* 0x1F */ u8  unk1F;
    /* 0x20 */ u8  unk20;
    /* 0x21 */ u8  unk21;
    /* 0x22 */ u8  unk22;
    /* 0x23 */ u8  unk23;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ u8  unk40;
    /* 0x41 */ u8  unk41;
    /* 0x42 */ u8  pad42[2];
    /* 0x44 */ u8  unk44;
    /* 0x45 */ u8  pad45[3];
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 unk54;
} struct_150CF680;

typedef struct {
    /* 0x00 */ u8  unk0;
    /* 0x01 */ u8  pad1[3];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
} struct_150CF680b;

void *func_1515548C(struct_150CF680 *, s32, s32, s32, s32, u8, s32);

void func_150CF680(s16 arg0, u8 arg1, s32 arg2) {
    struct_150CF680 sp40;
    struct_150CF680b sp30;
    void *temp_v0;

    sp40.unk4 = 72.0f;
    sp40.unk10 = 0xC1;
    sp40.unk12 = arg0;
    sp40.unk14 = 0x31;
    sp40.unk16 = 1;
    sp40.unk18 = 0xFF;
    sp40.unk1A = 8;
    sp40.unk1B = 0xFF;
    sp40.unk1C = 0xFF;
    sp40.unk1D = 0xFF;
    sp40.unk1E = 0xFF;
    sp40.unk1F = 0xFF;
    sp40.unk20 = 0xFF;
    sp40.unk21 = 0xFF;
    sp40.unk22 = 0xFF;
    sp40.unk23 = 0xFF;
    sp40.unk28 = 0x200004;

    sp30.unk0 = 0;
    sp30.unk4 = 0.0f;
    sp40.unk0 = -300.0f;
    sp30.unk8 = -300.0f;
    sp30.unkC = 0.0f;
    sp40.unkC = 7.5f;
    sp40.unk8 = 7.5f;
    sp40.unk24 = 0;
    sp40.unk2C = 0x9F0601;
    sp40.unk40 = 0;
    sp40.unk41 = 0xA;
    sp40.unk30 = 0x17;
    sp40.unk34 = 0x44;
    sp40.unk38 = 0x80;
    sp40.unk3C = 0x20;
    sp40.unk4C = 1.0f;
    sp40.unk48 = 1.0f;
    sp40.unk54 = 0.0f;
    sp40.unk50 = 0.0f;
    sp40.unk44 = (u8)D_80082FA0;

    temp_v0 = func_1515548C(&sp40, 0xC, 0, 0, 0x10, arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x70, &sp30, 0x10);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_FC5F0/func_150CF800.s")

struct sub150CFBEC {
    u8 unk0;
    u8 pad[3];
    f32 unk4;
    f32 unk8;
    f32 unkC;
};

struct par150CFBEC {
    char pad10[0x10];
    f32 unk10;
    char pad14[0x70 - 0x14];
    struct sub150CFBEC unk70;
};

void func_150CFBEC(struct par150CFBEC *arg0, f32 *arg1, u8 arg2) {
    struct sub150CFBEC *temp = &arg0->unk70;

    if (arg2 == 0x52) {
        temp->unk0 |= 1;
        temp->unk4 = 0.0f;
        temp->unk8 = arg0->unk10;
        temp->unkC = arg1[0] - arg0->unk10;
    }
}

extern void func_1515572C(f32 *, s32);

void func_150CFC38(f32 arg0) {
    f32 sp1C;

    sp1C = arg0;
    func_1515572C(&sp1C, 0x52);
}

extern f32 D_800A0878;
extern f32 D_800A087C;

s32 func_150CFC60(f32 *arg0) {
    f32 *p = &arg0[28];
    arg0[4] += p[0] * D_800BE9A4;
    arg0[5] += (p[1] * D_800BE9A4) + (((0.5f * p[2]) * D_800BE9A4) * D_800BE9A4);
    p[1] += p[2] * D_800BE9A4;
    if (p[3] < arg0[5]) {
        arg0[5] = p[3];
        p[0] = p[0] * D_800A0878;
        p[1] = fabsf(p[1]) * D_800A087C;
    }
    return 1;
}

unsigned char *func_150CFD20(unsigned char *arg0) {
    if (*arg0 != 0xBD && *arg0 != 0) {
        do {
            arg0++;
        } while (*arg0 != 0xBD && *arg0 != 0);
    }
    return arg0;
}

unsigned char *func_150CFD5C(unsigned char *arg0) {
    if (*arg0 != 0) {
        do {
            arg0++;
        } while (*arg0 != 0);
    }
    return arg0;
}

extern unsigned char *func_150CFD20(unsigned char *);

s32 func_150CFD84(unsigned char *arg0, unsigned char **arg1) {
    unsigned char *temp;

    temp = func_150CFD20(arg0);
    *arg1 = temp;
    return temp - arg0;
}

s32 func_150CFDB8(unsigned char *arg0) {
    s32 best;
    unsigned char *end;
    unsigned char *sp2C;

    best = 0;
    end = func_150CFD5C(arg0);
    while (arg0 < end) {
        s32 v = func_150CFD84(arg0, &sp2C);
        if (best < v) {
            best = v;
        }
        arg0 = sp2C + 1;
    }
    return best;
}

struct inner150CFE3C {
    char pad0[0x14];
    u8 unk14;
    u8 unk15;
    char pad16[0x18 - 0x16];
    u8 *unk18[1];
};

struct flat150CFE3C {
    char pad0[0x34];
    u8 *unk34;
    char pad38[0x3C - 0x38];
    u8 unk3C;
    u8 unk3D;
    char pad3E[0x40 - 0x3E];
    u8 *unk40[1];
};

union par150CFE3C {
    struct flat150CFE3C flat;
    struct {
        char pad0[0x28];
        struct inner150CFE3C inner;
    } sub;
};

void func_150CFE3C(union par150CFE3C *arg0) {
    struct inner150CFE3C *inner;

    inner = &arg0->sub.inner;
    memcpy(arg0->flat.unk40[arg0->flat.unk3D], arg0->flat.unk34, arg0->flat.unk3C);
    inner->unk18[inner->unk15][inner->unk14] = 0;
}

struct inner150CFE98 {
    char pad0[0x8];
    u8 unk8;
    char pad9[0xC - 0x9];
    u8 *unkC;
    u8 *unk10;
    u8 unk14;
    u8 unk15;
};

void func_150CFE98(arg0)
union par150CFE3C *arg0;
{
    struct inner150CFE98 *inner = (struct inner150CFE98 *)((char *)arg0 + 0x28);

    if (*inner->unk10 != 0) {
        inner->unkC = inner->unk10 + 1;
        inner->unk14 = func_150CFD84(inner->unk10 + 1, &inner->unk10);
        inner->unk15 ^= 1;
        func_150CFE3C(arg0);
        inner->unk8 |= 1;
    }
}

struct frame150CFF10 {
    u8  unk0;
    s32 unk4;
    u8  unk8;
    s32 unkC;
    u8 *unk10;
    u8  unk14;
    u8  unk15;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    u8  unk24;
    u8  unk25;
};

extern s32 func_150CFDB8(unsigned char *);

struct out150CFF10 {
    char pad0[0x18];
    u8 *unk18;
    u8 *unk1C;
    u8 *unk20;
};

void *func_150CFF10(u8 arg0, s32 arg1, s16 arg2, s32 arg3, s8 arg4, u8 arg5, u8 arg6, void *arg7) {
    struct frame150CFF10 tmp;
    struct260 *temp_v0;
    s32 temp;
    struct out150CFF10 *base;

    tmp.unk25 = arg5;
    tmp.unk24 = arg4;
    tmp.unk15 = 0;
    tmp.unk8 = 1;
    tmp.unk4 = arg1;
    tmp.unkC = arg1;
    tmp.unk0 = arg0;
    tmp.unk14 = func_150CFD84((unsigned char *)arg1, &tmp.unk10);
    tmp.unk18 = 0;
    tmp.unk1C = 0;
    tmp.unk20 = 0;

    temp = func_150CFDB8((unsigned char *)arg1) + 1;

    temp_v0 = func_15149130(arg2, -1, -1, 5, 3, 0x47, (struct37 *)(arg3 + 0x2A + (temp - 1) * 2), arg6, (s32)arg7);
    if (temp_v0 != NULL) {
        base = (struct out150CFF10 *)((u8 *)temp_v0 + 0x28);
        memcpy(base, &tmp, 0x28);
        base->unk20 = (u8 *)base + 0x28;
        base->unk18 = base->unk20 + arg3;
        base->unk1C = base->unk18 + temp;
        *base->unk18 = 0;
        *base->unk1C = 0;
        func_150CFE3C((union par150CFE3C *)temp_v0);
    }
    return temp_v0;
}

s32 func_150D0034(s32 arg0, struct260 *arg1, s32 arg2) {
    u8 *temp_v1;
    s32 ret;

    if (*(volatile s8 *)((u8 *)arg1 + 0x4C) == -1) {
        temp_v1 = (u8 *)arg1 + 0x28;
    } else {
        ret = D_800888A0[*(s8 *)((u8 *)arg1 + 0x4C)](arg1);
        if (ret == 0) {
            arg1->unkE = -1;
            return arg0;
        }
        temp_v1 = (u8 *)arg1 + 0x28;
    }

    temp_v1[8] &= ~1;
    return arg0;
}

extern s32 (*D_800888B0[])(s32 *, s32, u8);

s32 func_150D00C0(s32 *a0, s32 a1, u8 a2) {
    s32 (*fn)(s32 *, s32, u8);

    if (a2 == 0x51) {
        if (*((u8 *)a0 + 0x28) == *((u8 *)a1)) {
            func_150CFE98();
        }
    } else {
        fn = D_800888B0[*((u8 *)a0 + 0x4D)];
        if (fn != 0) {
            fn(a0, a1, a2);
        }
    }
}

extern void *func_150CFF10(u8, s32, s16, s32, s8, u8, u8, void *);

struct frame150D0134 {
    u8 unk0;
    u8 pad[7];
};

void func_150D0134(u8 arg0, s32 arg1, s16 arg2, u8 arg3, void *arg4) {
    struct frame150D0134 sp30;
    void *ret;

    sp30.unk0 = 0;
    ret = func_150CFF10(arg0, arg1, arg2, 8, 0, 0, arg3, arg4);
    if (ret != 0) {
        memcpy(*(void **)((u8 *)ret + 0x48), &sp30.unk0, 1);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_FC5F0/func_150D01A0.s")

struct frame150D02B4 {
    f32 unk0;
    s16 unk4;
    u8 pad[2];
};

void func_150D02B4(u8 arg0, s32 arg1, s16 arg2, u8 arg3, void *arg4) {
    void *ret;
    struct frame150D02B4 sp2C;

    sp2C.unk4 = 0;
    sp2C.unk0 = 0.0f;
    ret = func_150CFF10(arg0, arg1, arg2, 8, 1, 0, arg3, arg4);
    if (ret != 0) {
        memcpy(*(void **)((u8 *)ret + 0x48), &sp2C.unk0, 8);
    }
}

struct frame150D032C {
    f32 unk0;
    s16 unk4;
    u8 pad[2];
};

s32 func_150D032C(struct260 *arg0) {
    struct inner150CFE3C *inner;
    struct frame150D032C *state;
    u8 sp28[0x50];
    struct struct_150D032C_prefix sp20;

    inner = (struct inner150CFE3C *)((u8 *)arg0 + 0x28);
    sp20 = D_800A0880;
    state = *(struct frame150D032C **)((u8 *)arg0 + 0x48);

    if (((u8 *)arg0)[0x30] & 1) {
        state->unk4 = 0;
        state->unk0 = 0.0f;
    }

    if (state->unk0 < (f32)inner->unk14) {
        state->unk0 = state->unk0 + (D_800A0888 * D_800BE9A4);
        if (state->unk0 > 1.0f) {
            do {
                state->unk4 = state->unk4 + 1;
                if (inner->unk14 < state->unk4) {
                    state->unk4 = inner->unk14;
                }
                state->unk0 = state->unk0 - 1.0f;
            } while (state->unk0 > 1.0f);
        }
    }

    memcpy(sp28, &sp20, 4);
    memcpy(&sp28[4], inner->unk18[inner->unk15], state->unk4);
    sp28[state->unk4 + 4] = 0x20;
    sp28[state->unk4 + 5] = 0xBB;
    sp28[state->unk4 + 6] = 0;
    func_1504332C(0, 0xFF, 0, 0x96);
    func_15042D94(0xF, 0xBE, 0x80, sp28);
    return 1;
}

void func_150D04C4(u8 arg0, s32 arg1, s16 arg2, u8 arg3, void *arg4) {
    struct frame150D0134 sp30;
    void *ret;

    sp30.unk0 = 0;
    ret = func_150CFF10(arg0, arg1, arg2, 8, 2, 0, arg3, arg4);
    if (ret != 0) {
        memcpy(*(void **)((u8 *)ret + 0x48), &sp30.unk0, 1);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_FC5F0/func_150D0534.s")
