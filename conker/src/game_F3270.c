#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    char pad_0x0[0x4];
    u8 field_0x4;
} GameF3270Child58State;

typedef struct {
    char pad_0x0[0x58];
    GameF3270Child58State field_0x58;
} GameF3270SpawnedObject;

typedef struct {
    char pad_0x0[0x18];
    s32 field_0x18;
    char pad_0x1C[0x40];
    GameF3270SpawnedObject *field_0x5C;
} GameF3270SpawnOwner;

typedef struct {
    char pad_0x0[0x4];
    u8 field_0x4;
    char pad_0x5[0x3];
    f32 field_0x8;
    f32 field_0xC;
    f32 field_0x10;
    s16 field_0x14;
    s16 field_0x16;
    s16 field_0x18;
    char pad_0x1A[0x2];
    f32 field_0x1C;
} GameF3270B0State;

typedef struct {
    char pad_0x0[0x24];
    s32 field_0x24;
    char pad_0x28[0x88];
    GameF3270B0State field_0xB0;
} GameF3270Object;

typedef struct {
    char pad_0x0[0x58];
    GameF3270Object *field_0x58;
} GameF3270ObjectOwner58;

GameF3270Object *func_150C6460(GameF3270ObjectOwner58 *arg0);
GameF3270SpawnedObject *func_150C5F94(s32 arg0, GameF3270SpawnOwner *arg1);

void func_150C5DC0(GameF3270ObjectOwner58 *arg0) {
    GameF3270B0State *temp;

    if (*(s32 *)&arg0->field_0x58 != 0) {
        temp = &arg0->field_0x58->field_0xB0;
        temp->field_0x4 = 1;
        done:
            ;
    } else {
        arg0->field_0x58 = func_150C6460(arg0);
    }
}

s32 func_150C5E0C(GameF3270Object *arg0) {
    s8 ret;
    GameF3270B0State *sub;

    ret = 1;
    sub = &arg0->field_0xB0;
    if (sub->field_0x4 == 0) {
        ret = 0;
    }
    sub->field_0x4 = 0;
    sub->field_0x14 -= D_800BE9E4;
    if (sub->field_0x14 < 0) {
        sub->field_0x14 = (func_150ADA20() % (u32)(sub->field_0x18 + 1)) + sub->field_0x16;
        sub->field_0x10 = func_150ADA68() * sub->field_0xC + sub->field_0x8;
    }
    arg0->field_0x24 += (s32)((sub->field_0x10 - (f32)arg0->field_0x24) * sub->field_0x1C);
    return ret;
}

extern s32 func_1513F6C0(void *arg0, s32 arg1, s32 arg2);

s32 func_150C5EFC(u8 *arg0) {
    s32 *temp = (s32 *)((*(u8 **)((u8 *)arg0 + 0xB0)) + 0x58);
    temp[0] = 0;
    *(s32 *)((u8 *)arg0 + 0x18) |= 2;
    *(u8 **)((u8 *)arg0 + 0xB0) = 0;
    func_1513F6C0(arg0, 0, 0);
    return 0;
}

void func_150C5F40(GameF3270SpawnOwner *arg0) {
    s32 temp_a2;
    GameF3270Child58State *temp;

    temp_a2 = arg0->field_0x18;
    if (*(s32 *)&arg0->field_0x5C != 0) {
        temp = &arg0->field_0x5C->field_0x58;
        temp->field_0x4 = 1;
        done:
            ;
    } else {
        arg0->field_0x5C = func_150C5F94(temp_a2, arg0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_F3270/func_150C5F94.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_F3270/func_150C60D8.s")

s32 func_150C63EC(u8 *arg0) {
    s32 ret = 1;

    if (arg0[0x5C] == 0) {
        ret = 0;
    }
    arg0[0x5C] = 0;
    return ret;
}

void func_150C6410(struct102 *arg0) {
    s32 *temp = (s32 *)((*(u8 **)((u8 *)arg0 + 0x58)) + 0x58);
    temp[1] = 0;
    func_151346EC(arg0);
}

void func_150C6438(struct102 *arg0) {
    s32 *temp = (s32 *)((*(u8 **)((u8 *)arg0 + 0x58)) + 0x58);
    temp[1] = 0;
    func_1513470C(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_F3270/func_150C6460.s")
