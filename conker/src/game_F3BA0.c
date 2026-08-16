#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_1513470C(struct102 *arg0);

typedef struct {
    /* 0x00 */ s32 field_0x00;
    /* 0x04 */ u8 field_0x04;
    /* 0x05 */ u8 pad_0x05[0x3];
    /* 0x08 */ f32 field_0x08;
    /* 0x0C */ f32 field_0x0C;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ s16 field_0x14;
    /* 0x16 */ s16 field_0x16;
    /* 0x18 */ s16 field_0x18;
    /* 0x1A */ s16 field_0x1A;
    /* 0x1C */ f32 field_0x1C;
} RandomLerpState;

typedef struct {
    /* 0x00 */ char pad_0x00[0x24];
    /* 0x24 */ s32 field_0x24;
    /* 0x28 */ char pad_0x28[0x88];
    /* 0xB0 */ RandomLerpState field_0xB0;
} RandomLerpObject;

typedef struct {
    /* 0x00 */ char pad_0x00[0x6C];
    /* 0x6C */ RandomLerpObject *field_0x6C;
} RandomLerpOwner;

RandomLerpObject *func_150C6D90(RandomLerpOwner *arg0);

void func_150C66F0(RandomLerpOwner *arg0) {
    RandomLerpState *temp;

    if (*(s32 *)&arg0->field_0x6C != 0) {
        temp = &arg0->field_0x6C->field_0xB0;
        temp->field_0x04 = 1;
        done:
            ;
    } else {
        arg0->field_0x6C = func_150C6D90(arg0);
    }
}

s32 func_150C673C(RandomLerpObject *arg0) {
    s8 ret;
    RandomLerpState *sub;

    ret = 1;
    sub = &arg0->field_0xB0;
    if (sub->field_0x04 == 0) {
        ret = 0;
    }
    sub->field_0x04 = 0;
    sub->field_0x14 -= D_800BE9E4;
    if (sub->field_0x14 < 0) {
        sub->field_0x14 = (func_150ADA20() % (u32)(sub->field_0x18 + 1)) + sub->field_0x16;
        sub->field_0x10 = func_150ADA68() * sub->field_0x0C + sub->field_0x08;
    }
    arg0->field_0x24 += (s32)((sub->field_0x10 - (f32)arg0->field_0x24) * sub->field_0x1C);
    return ret;
}

extern s32 func_1513F6C0(void *arg0, s32 arg1, s32 arg2);

s32 func_150C682C(u8 *arg0) {
    s32 *temp = (s32 *)((*(u8 **)((u8 *)arg0 + 0xB0)) + 0x58);
    temp[5] = 0;
    *(s32 *)((u8 *)arg0 + 0x18) |= 2;
    *(u8 **)((u8 *)arg0 + 0xB0) = 0;
    func_1513F6C0(arg0, 0, 0);
    return 0;
}

s32 func_150C68C4(s32 arg0);

void func_150C6870(u8 *arg0) {
    s32 temp = *(s32 *)((u8 *)arg0 + 0x18);
    if (*(s32 *)((u8 *)arg0 + 0x70) != 0) {
        u8 *p = *(u8 **)((u8 *)arg0 + 0x70) + 0x58;
        p[4] = 1;
    } else {
        *(s32 *)((u8 *)arg0 + 0x70) = func_150C68C4(temp);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_F3BA0/func_150C68C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_F3BA0/func_150C6A08.s")

typedef struct {
    char pad[0x5C];
    u8 unk5C;
} Func150C6D1CArg;

s32 func_150C6D1C(Func150C6D1CArg* arg) {
    s32 ret = 1;
    if (arg->unk5C == 0) {
        ret = 0;
    }
    arg->unk5C = 0;
    return ret;
}

typedef struct {
    char pad[0x18];
    s32 unk18;
} Func150C6D40Inner;

typedef struct {
    char pad[0x58];
    Func150C6D40Inner inner58;
} Func150C6D40Sub;

typedef struct {
    char pad[0x58];
    Func150C6D40Sub* unk58;
} Func150C6D40Arg;

void func_150C6D40(Func150C6D40Arg* arg0) {
    Func150C6D40Inner* inner = &arg0->unk58->inner58;
    inner->unk18 = 0;
    func_151346EC((struct102*)arg0);
}

void func_150C6D68(Func150C6D40Arg* arg0) {
    Func150C6D40Inner* inner = &arg0->unk58->inner58;
    inner->unk18 = 0;
    func_1513470C((struct102*)arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_F3BA0/func_150C6D90.s")
