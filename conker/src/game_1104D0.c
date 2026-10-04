#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_800A1050;
extern f32 D_800A1054;
extern void func_1505D1C4(f32, f32, f32, s32, s32, s32, s32, s32);
void func_151C3B0C(s32, f32, f32, f32, f32, s32, s32, s32);
extern s32 func_150AD9A0(s32, s32, s32);
extern u8 *func_150E3020(s32, s32, s32, s32, s32, s32, s32, f32, s32, f32, f32, f32, s32, s16);

typedef struct {
    char pad_0x0[0x30];
    f32 field_0x30;
    f32 field_0x34;
    f32 field_0x38;
    char pad_0x3C[0x24];
    f32 field_0x60;
    f32 field_0x64;
    char pad_0x68[0x3C];
    s32 field_0xA4;
} Game1104D0EffectState;

typedef struct {
    char pad_0x0[0x110];
    Game1104D0EffectState field_0x110;
} Game1104D0EffectObj;

typedef struct {
    u8 field_0x0;
    char pad_0x1[0xF];
    f32 field_0x10;
    f32 field_0x14;
    f32 field_0x18;
    char pad_0x1C[0xC];
    f32 field_0x28;
    f32 field_0x2C;
    f32 field_0x30;
    char pad_0x34[0x14];
    u8 field_0x48;
    char pad_0x49[0x1];
    u16 field_0x4A;
    f32 field_0x4C;
    char pad_0x50[0x4];
    f32 field_0x54;
} Game1104D0EffectInstance;

#pragma GLOBAL_ASM("asm/nonmatchings/game_1104D0/func_150E3020.s")

s32 func_150E3208(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    u8 *temp;

    temp = func_150E3020(arg0, arg1, arg2, arg3, arg4, arg5, arg6,
                         (f32)func_150AD9A0(arg0 - arg3, arg1 - arg4, arg2 - arg5) / (f32)arg7,
                         0, 0.0f, 0.0f, 0.0f, 0, -99);
    if (temp != 0) {
        return temp[0x48] + 1;
    }
    return 0;
}

s32 func_150E32D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5) {
    u8 *temp;

    temp = func_150E3020(arg0, arg1, arg2, 0, 0, 0, arg4, arg5, arg3, 0.0f, 0.0f, 0.0f, 0, -99);
    if (temp != 0) {
        return temp[0x48] + 1;
    }
    return 0;
}

void func_150E3340(f32 *arg0, s32 *arg1, s32 arg2, s16 arg3) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a2;

    temp_a0 = arg1[0];
    temp_a1 = arg1[1];
    temp_a2 = arg1[2];
    func_150E3020(temp_a0, temp_a1, temp_a2, temp_a0, temp_a1, temp_a2, 0x1A, 10.0f, 0, arg0[0], arg0[1], arg0[2], arg2, arg3);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1104D0/func_150E33CC.s")

extern void func_150E33CC(void);

s32 func_150E3414(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, f32 arg8) {
    Game1104D0EffectInstance *temp;

    temp = (Game1104D0EffectInstance *)func_150E3020(arg3, arg4, arg5, 0, 0, 0, arg7, arg8, arg6, (f32)arg0, (f32)arg1, (f32)arg2, 0, -99);
    if (temp != 0) {
        temp->field_0x4A = func_1000FA64(0x2D0, (s16)arg0, (s16)arg1, (s16)arg2, 0x5DC0, 0x1770, 0x3E8, (s32)func_150E33CC, 0, 0, 0, 0);
        return temp->field_0x48 + 1;
    }
    return 0;
}

void func_150E3514(Game1104D0EffectInstance *arg0) {
    s32 temp;
    s32 *slot;
    u16 id;

    temp = arg0->field_0x48;
    if (temp >= 0) {
        slot = &D_800D99D0[temp];
        if (*slot == (s32)arg0) {
            *slot = 0;
        }
    }

    id = arg0->field_0x4A;
    if (id != 0) {
        func_100111C8(id);
        arg0->field_0x4A = 0;
        func_10010F88(0x2D7, 0x5DC0, 0, 0, 0,
                      (s32)arg0->field_0x28,
                      (s32)arg0->field_0x2C,
                      (s32)arg0->field_0x30,
                      0x3E8, 0x1770);
    }

    func_1516972C((struct102 *)arg0);
}

extern u8 D_800DCE50[];

typedef struct Node150E35DC {
    u8 pad0[0x8];
    struct Node150E35DC *unk8;
    u8 padC[0x3C];
    u8 unk48;
} Node150E35DC;

void func_150E35DC(s32 arg0) {
    s32 i;
    Node150E35DC *node;

    arg0--;
    for (i = 0; i != 2; i++) {
        D_800DD190++;
        node = ((Node150E35DC *(*)[104])D_800DCE50)[i][39];
        while (node != NULL) {
            *(Node150E35DC **)((u8 *)D_800DD198 + (D_800DD190 << 2)) = node->unk8;
            if (arg0 == -1 || arg0 == node->unk48) {
                func_150E3514((Game1104D0EffectInstance *)node);
            }
            node = *(Node150E35DC **)((u8 *)D_800DD198 + (D_800DD190 << 2));
        }
        {
            extern s8 D_800DD190;

            D_800DD190--;
        }
    }
}


void func_150E36BC(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    Game1104D0EffectInstance *temp;

    arg0 -= 1;
    if ((arg0 >= 0) && (arg0 < 8)) {
        temp = (Game1104D0EffectInstance *)D_800D99D0[arg0];
        if (temp != 0) {
            if (temp->field_0x0 == 0x27) {
                *arg1 = (s32)temp->field_0x10;
                *arg2 = (s32)temp->field_0x14;
                *arg3 = (s32)temp->field_0x18;
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1104D0/func_150E3738.s")

void func_150E4010(Game1104D0EffectObj *arg0) {
    Game1104D0EffectState *temp;

    temp = &arg0->field_0x110;
    if (arg0->field_0x110.field_0xA4 != 0) {
        func_1505D1C4(temp->field_0x30, temp->field_0x34, temp->field_0x38,
                      temp->field_0xA4 | 0x60000, -1,
                      ((u16)(u32)(func_150484A0(temp->field_0x60, temp->field_0x64) * D_800A1050) - 0x4000) | 1, 0, 0);
    }
}

void func_150E411C(s32 arg0) {
    func_151C3B0C(arg0, 0.352000028f, 0.701000035f, 0.566000044f, D_800A1054, 0xFF, 0xFF, 0xFF);
}

extern f32 D_800BE9A4;

s32 func_150E4174(Game1104D0EffectInstance *arg0) {
    arg0->field_0x2C += arg0->field_0x4C * D_800BE9A4;
    arg0->field_0x30 += arg0->field_0x54 * D_800BE9A4;
    return 1;
}
