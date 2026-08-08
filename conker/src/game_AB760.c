#include <ultra64.h>
#include "functions.h"
#include "variables.h"

s32 func_1507E908(void *, s32);
s32 func_1507E968(void *);
void func_1507E5C8(u8 *, s32);
void *func_1507E9F8(void *, s32 *);
s32 func_150302F0(void *, s32);
void func_1507EA44(void *, s32, s32);
void func_1507E2B0(void *);
void func_1507EABC(void *);
extern struct124 *D_800D1C90[];
extern f32 D_8009B8A0;

typedef struct {
    char pad_0[0x5];
    u8 field_0x05;
    char pad_1[0x69];
    u8 field_0x6F;
    u8 field_0x70;
    char pad_2[0x1];
    u16 field_0x72;
} GameAB760ActorState;

#pragma GLOBAL_ASM("asm/nonmatchings/game_AB760/func_1507E2B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_AB760/func_1507E3C0.s")

void func_1507E500(u8 *arg0, s32 arg1, s32 arg2) {
    u8 *temp;
    u8 *temp2;

    if (arg1 < func_1507E968(arg0)) {
        temp = (u8 *)func_1507E908(arg0, arg0[0x6F]);
        if (temp[4] != 0) {
            temp2 = func_1507E9F8(arg0, 0);
            if (temp2 != 0) {
                func_150302F0(arg0, temp2[temp[4] - 1]);
            }
        }
        arg0[0x6F] = arg1;
        func_1507E5C8(arg0, arg2);
        if (arg2 != 0) {
            arg0[0x135] = arg2;
        } else {
            arg0[0x135] = ((u8 *)func_1507E908(arg0, arg1))[3];
        }
    }
}

void func_1507E5C8(u8 *arg0, s32 arg1) {
    u8 *temp;

    temp = (u8 *)func_1507E908(arg0, arg0[0x6F]);
    if (temp != 0) {
        func_1507EA44(arg0, temp[4], *(u16 *)(temp + 6));
        if (temp[2] != arg0[0x134]) {
            arg0[0x134] = temp[2];
            if (arg1 == 0) {
                arg0[0x135] = temp[3];
            } else {
                arg0[0x135] = arg1;
            }
        }
        arg0[0x6C] = temp[0] + 0xA;
        arg0[0x6D] = temp[1] + 0xA;
        if (temp[8] != 0) {
            arg0[0x68] = temp[8];
        } else {
            arg0[0x68] = *(u8 *)((s32)D_800D1C90[arg0[4]] + 0x3B);
        }
        if (temp[9] != 0) {
            arg0[0x69] = temp[9];
        } else {
            arg0[0x69] = *(u8 *)((s32)D_800D1C90[arg0[4]] + 0x3C);
        }
    }
}

s32 func_150849A0(void *);

s32 func_1507E6B8(u8 *arg0) {
    s32 v;
    s32 b;

    if (arg0[0x1CA] == 0) {
        return 0;
    }
    if (arg0[0x70] == arg0[0x6F]) {
        return 1;
    }
    v = func_150849A0(arg0);
    b = arg0[0x6F];
    if (v == 0) {
        if (b == 0x15) {
            return 1;
        }
    } else if (v == 0x52) {
        return 1;
    }
    return 0;
}

void func_1507E73C(GameAB760ActorState *arg0) {
    s32 temp_v1;

    if (arg0->field_0x05 != 2) {
        if (arg0->field_0x72 != 0) {
            temp_v1 = arg0->field_0x72;
            if (temp_v1 == 0xFFFE) {
                return;
            }
            if (temp_v1 != 0xFFFF) {
                if (D_800BE9E4 < temp_v1) {
                    arg0->field_0x72 = temp_v1 - D_800BE9E4;
                } else {
                    arg0->field_0x72 = 0;
                }
            }
        }
        if (func_1507E6B8((u8 *)arg0) != 0) {
            func_1507E2B0(arg0);
        }
        if (arg0->field_0x72 == 0) {
            if (arg0->field_0x6F != arg0->field_0x70) {
                func_1507EABC(arg0);
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_AB760/func_1507E7E4.s")

extern struct124 *D_800D1C90[];
s32 func_150849A0(void *arg0);

s32 func_1507E908(void *arg0, s32 arg1) {
    s32 *temp;
    s32 base;

    temp = (s32 *)D_800D1C90[func_150849A0(arg0)];
    if (temp != 0) {
        temp -= 2;
        base = temp[0];
        if (base != 0) {
            return (arg1 * 10) + base;
        }
    }
    return 0;
}

s32 func_1507E968(void *arg0) {
    u32 *temp;
    s32 idx;
    s32 b;

    b = ((u8 *)arg0)[4];
    idx = (b != 0x96) ? func_150849A0(arg0) : b;
    if (idx == 0xFF) {
        return 0;
    }
    temp = (u32 *)D_800D1C90[idx];
    if (temp != 0) {
        temp -= 2;
        return temp[1] / 10;
    }
    return 0;
}

void func_1507E9E8(s32 arg0, s32 arg1) {
}

extern s32 func_150849A0(void *);
extern s32 D_8009D910;

void *func_1507E9F8(void *arg0, s32 *arg1) {
    if (!func_150849A0(arg0)) {
        if (arg1 != 0) {
            *arg1 = 5;
        }
        return &D_8009D910;
    }
    if (arg1 != 0) {
        *arg1 = 0;
    }
    return (void *)0;
}

void func_1507EA44(void *arg0, s32 arg1, s32 arg2) {
    u8 *temp;

    if (arg1 != 0) {
        temp = func_1507E9F8(arg0, 0);
        if (temp != 0) {
            func_15083568(arg0, temp[arg1 - 1], (f32)arg2 * D_8009B8A0, 0);
        }
    }
}

extern void func_1507E7E4(void *, s32, s32, s32, s32);

void func_1507EABC(void *arg0) {
    func_1507E7E4(arg0, *(u8 *)((s32)arg0 + 0x70), 3, 0xFFFF, 0xA);
    *(u8 *)((s32)arg0 + 0x71) = 0;
    *(u16 *)((s32)arg0 + 0x72) = 0;
    if ((u8)*(u8 *)((s32)arg0 + 0x6C) >= 10) {
        *(u8 *)((s32)arg0 + 0x6C) = 0;
        *(u8 *)((s32)arg0 + 0x6A) = 0;
    }
    if ((u8)*(u8 *)((s32)arg0 + 0x6D) >= 10) {
        *(u8 *)((s32)arg0 + 0x6D) = 0;
        *(u8 *)((s32)arg0 + 0x6B) = 0;
    }
}

void func_1507EB4C(void *, s32);
void func_1507EABC(void *);

void func_1507EB2C(void *arg0) {
    func_1507EB4C(arg0, 0);
}

void func_1507EB4C(void *arg0, s32 arg1) {
    if (arg1 != *(u8 *)((s32)arg0 + 0x70)) {
        *(u8 *)((s32)arg0 + 0x70) = arg1;
        func_1507EABC(arg0);
    }
}
