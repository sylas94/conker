#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern s32 D_800DBDC0;
extern s32 D_800DBDC4;
extern s32 D_800DBDC8;
extern f32 D_800DBDCC;
extern f32 D_800DBDD0;
extern f32 D_800A2D50;
extern f32 D_800A2D54;
extern f32 D_800A2D58;
extern f32 D_800A2D5C;

typedef struct unkfunc_1510FE30 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
} unkfunc_1510FE30;

typedef struct unkfunc_1510F8D8 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} unkfunc_1510F8D8;

extern unkfunc_1510FE30 *D_800DBE48;

extern s32 func_150A3A70(s32, s32);
extern void func_150A6760(s32);
extern void func_150F33F8(s32);
extern s32 func_1510FE30(s32);

#pragma GLOBAL_ASM("asm/nonmatchings/game_13BB20/func_1510E670.s")

void func_1510E950(s32, s32, s32, s32, s32, s32, s32, f32, f32, f32, f32, u16, s32, f32, f32, s32);

void func_1510E7A4(s32 a0, s32 a1, s32 a2, s32 a3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u16 arg10, s32 arg11, f32 arg12, f32 arg13) {
    func_1510E950(a0, a1, 0, a2, a3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, 0);
}

void func_1510E82C(s32 a0, s32 a1, s32 a2, s32 a3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u16 arg10, s32 arg11) {
    func_1510E950(a0, a1, 0, a2, a3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, D_800A2D50, D_800A2D54, 0);
}

void func_1510E8BC(s32 a0, s32 a1, s32 a2, s32 a3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u16 arg10, s32 arg11, f32 arg12, f32 arg13, s32 arg14) {
    func_1510E950(a0, a1, 0, a2, a3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, D_800A2D58, D_800A2D5C, arg14);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_13BB20/func_1510E950.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_13BB20/func_1510F648.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_13BB20/func_1510F720.s")

extern void func_150A49F4(void);

void func_1510F800() {
    func_150A49F4();
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_13BB20/func_1510F820.s")

s32 func_1510F8CC(s32 arg0) {
    return arg0 & 0x1F;
}

s32 func_1510F8D8(s32 arg0, s32 arg1, s32 arg2, s32 *arg3) {
    s32 count;
    s32 bestIndex;
    s32 i;
    unkfunc_1510F8D8 *entries;
    f32 arg1f;
    f32 best;
    f32 current;

    func_1510F800(0);
    count = func_150A3A70(arg0, arg2);
    if (count == 0) {
        return -10000;
    }

    entries = (unkfunc_1510F8D8 *)&D_800D3300;
    bestIndex = 0;
    arg1f = (f32)arg1;
    best = arg1f - ((f32)entries[0].unk0 * 0.00390625f);

    for (i = 1; i < count; i++) {
        current = arg1f - ((f32)entries[i].unk0 * 0.00390625f);
        if (((best >= 0.0f) && (current < best) && (current >= 0.0f)) ||
            ((best < 0.0f) && (best < current))) {
            best = current;
            bestIndex = i;
        }
    }

    if (arg3 != NULL) {
        *arg3 = entries[bestIndex].unk4;
    }

    return (s32)((f32)entries[bestIndex].unk0 * 0.00390625f);
}

void func_1510FC34(s32 arg0) {
    struct108 *temp_v0;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_v0_2;
    s16 *temp_v1;

    D_800DBDC0 = arg0;
    temp_v0 = (struct108 *)((u8 *)D_800DBFF0 + (arg0 * sizeof(struct108)));
    temp_a0 = temp_v0->unk2F8;
    temp_a1 = temp_v0->unk300;
    D_800DBDCC = temp_a0;
    D_800DBDD0 = temp_a1;
    temp_v0_2 = func_1510FD20(temp_a0, temp_a1);
    D_800DBDC8 = temp_v0_2;
    temp_v0_2 = func_1510FE30(temp_v0_2);
    D_800DBDC4 = temp_v0_2;
    temp_v1 = &((s16 *)&D_800DBE30)[arg0];
    if (temp_v0_2 != *temp_v1) {
        *temp_v1 = temp_v0_2;
        func_150A6760(arg0);
    }
    if (D_800BE9F0 == 0x3C) {
        func_150F33F8(arg0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_13BB20/func_1510FD20.s")

s32 func_1510FE30(s32 arg0) {
    unkfunc_1510FE30 *temp_v0;
    s32 temp_v1;
    s16 temp_a1;

    temp_v0 = D_800DBE48;
    temp_v1 = 0;

    while (temp_v0 != NULL) {
        if ((s32)temp_v0 == arg0) {
            return temp_v1;
        }
        temp_a1 = temp_v0->unkC;
        if (temp_a1 != 0) {
            temp_v0 = (unkfunc_1510FE30 *)((u8 *)temp_v0 + temp_a1);
        } else {
            temp_a1 = temp_v0->unk4;
            if (temp_a1 != 0) {
                temp_v0 = (unkfunc_1510FE30 *)((u8 *)temp_v0 + temp_a1);
                temp_v1++;
            } else {
                temp_v0 = NULL;
            }
        }
    }

    return 0;
}
