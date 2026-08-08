#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern void guMtxIdentF(float mf[4][4]);
extern void guMtxF2L(float mf[4][4], Mtx *m);
extern void guMtxCatL(Mtx *m, Mtx *n, Mtx *res);
f32 func_150AD780(f32);
f32 func_150AD78C(f32);
extern u8 D_800BE9C0;
extern s32 D_800BE9E4;
extern struct10 *D_800DC2A0;
extern f32 D_800A36C0;
extern f32 D_800A36C4;
extern f32 D_800A36C8;
extern f32 D_800A36CC;
extern f32 D_800A36D0;
extern f32 D_800A36D4;
extern f32 D_800A36D8;
void func_150495B0(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5);

typedef struct Func1512D070Object {
    u8 pad0[0x2C];
    s32 unk2C;
    u8 pad30[0x23C - 0x30];
    u8 unk23C;
    u8 unk23D;
    u8 pad23E[0x298 - 0x23E];
    s16 unk298;
    u8 pad29A[0x5F0 - 0x29A];
    s32 unk5F0;
    u8 pad5F4[0x7B0 - 0x5F4];
    f32 unk7B0;
    f32 unk7B4;
    u8 pad7B8[0x7D8 - 0x7B8];
    f32 unk7D8;
    f32 unk7DC;
} Func1512D070Object;


#pragma GLOBAL_ASM("asm/nonmatchings/game_159940/func_1512C490.s")

void func_1512D070(Func1512D070Object *arg0) {
    s32 mtx[16];
    f32 mf[4][4];

    {
    f32 var_f2;

    if ((arg0->unk2C & 0x80000) != 0) {
        var_f2 = D_800A36C0;
    } else if (arg0->unk298 != 0) {
        var_f2 = D_800A36C4;
    } else {
        var_f2 = D_800A36C8;
    }

    if (((arg0->unk2C & 0x80000) != 0) || (arg0->unk5F0 & 1) || ((arg0->unk2C != 0x40000) && (arg0->unk5F0 & 8))) {
        arg0->unk7B0 += D_800A36CC * ((f32) D_800BE9E4);
        if (D_800A36D0 < arg0->unk7B0) {
            arg0->unk7B0 -= D_800A36D4;
        }
    } else {
        var_f2 = 0.0f;
    }

    if ((arg0->unk23C != 0) || (arg0->unk5F0 & 4)) {
        arg0->unk7DC = var_f2;
    } else {
        func_150495B0(&arg0->unk7DC, var_f2, &arg0->unk7D8, 0.200000003f, D_800A36D8, arg0->unk7B4);
    }

    guMtxIdentF(mf);
    mf[0][0] = ((func_150AD78C(arg0->unk7B0) * arg0->unk7DC) * 2.0f) + (arg0->unk7DC + arg0->unk7DC) + 1.0f;
    mf[1][1] = ((func_150AD780(arg0->unk7B0) * arg0->unk7DC) + arg0->unk7DC) + 1.0f;
    guMtxF2L(mf, (Mtx *)mtx);
    guMtxCatL(&((Mtx *) ((s32 *) (&D_800DC2A0))[D_800BE9C0])[arg0->unk23D],
              (Mtx *)mtx,
              &((Mtx *) ((s32 *) (&D_800DC2A0))[D_800BE9C0])[arg0->unk23D]);
    }
}

extern s32 D_800DC280[];
extern s32 D_800DC290[];
s32 func_1502B5C8(s32 *, s32, s32, s32);

typedef struct Game159940Object {
    char pad_0[0x84D];
    u8 field_0x84D;
    u8 field_0x84E;
    char pad_0x84F[0x1];
    s32 field_0x850;
} Game159940Object;

void func_1512D238(void) {
    u32 sp3C;
    s32 i;

    for (i = 0; i < 4; i++) {
        D_800DC280[i] = func_1502B5C8((s32 *)&sp3C, 2, 0x1B, i);
        D_800DC290[i] = sp3C / 0x18;
    }
}

typedef struct {
    u8 pad0[0x84D];
    /* 0x84D */ u8 unk84D;
    u8 pad84E[0x2];
    /* 0x850 */ s32 unk850;
} S1512D2E4;

void func_1512D2E4(S1512D2E4 *arg0, s32 arg1) {
    arg0->unk850 = arg1;
    arg0->unk84D = 0x1;
}

void func_1512D2F8(Game159940Object *arg0) {
    u8 temp;

    switch (arg0->field_0x84D) {
    case 1:
        arg0->field_0x84E = 0;
        arg0->field_0x84D = 2;
        break;
    case 2:
        temp = arg0->field_0x84E + D_800BE9E4;
        arg0->field_0x84E = temp;
        if ((s32)(temp & 0xFF) >= D_800DC290[arg0->field_0x850]) {
            arg0->field_0x84D = 0;
        }
        break;
    }
}

void func_1512D368(s32 arg0) {
    arg0 = arg0;
}
