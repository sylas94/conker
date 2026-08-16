#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    u8 *unk0;
    s32 unk4;
} struct_game_197C20_0;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u8 unkA;
    /* 0x0B */ char pad_B[0x1B];
    /* 0x26 */ u16 unk26;
    /* 0x28 */ char pad_28[0x4];
    /* 0x2C */ s32 unk2C;
} struct_game_197C20_1;

typedef struct {
    /* 0x00 */ u8 field_0x0;
    /* 0x01 */ char pad_0[0xC];
    /* 0x0D */ u8 field_0xD;
    /* 0x0E */ u8 field_0xE;
    /* 0x0F */ u8 field_0xF;
    /* 0x10 */ struct_game_197C20_1 *field_0x10;
    /* 0x14 */ u8 field_0x14;
    /* 0x15 */ u8 field_0x15;
    /* 0x16 */ s16 field_0x16;
    /* 0x18 */ s16 field_0x18;
    /* 0x1A */ u8 field_0x1A;
    /* 0x1B */ char pad_1[0x4];
    /* 0x1F */ u8 field_0x1F;
    /* 0x20 */ u8 field_0x20;
    /* 0x21 */ char pad_2[0x3];
    /* 0x24 */ u8 *field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ char pad_3[0xC];
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ char pad_4[0x34];
} struct_game_197C20_3;

extern struct_game_197C20_0 *D_800DD254;
extern struct_game_197C20_0 *D_800DD258;
extern f32 D_800A6CD0;
extern f32 D_800A6CD4;

extern void *func_15167A68(s32, s32, s32, s32, s32, s32);
extern void func_150428D4(u8 *, s32 *, s32 *, s32 *);
u8 *func_1516C878(struct_game_197C20_1 *arg0, s32 arg1, s16 arg2);


s32 func_1516A770(u8 *arg0) {
    s32 count = 1;

    while (*arg0 != 0) {
        if (*arg0 == 0xBD) {
            *arg0 = 0;
            count++;
        }
        arg0++;
    }
    return count;
}

struct_game_197C20_3 *func_1516A7B0(u32 arg0, s32 arg1, s32 arg2, s32 arg3, struct_game_197C20_1 *arg4, s32 arg5) {
    struct_game_197C20_3 *obj;
    struct_game_197C20_1 *text;
    s32 i;
    f32 lineHeight;
    u8 *str;

    obj = (struct_game_197C20_3 *)func_15167A68(0x51, 0, 0x74, 0, arg5, 2);
    if (obj != 0) {
        text = arg4;
        if (arg4 == 0) {
            if (arg0 >= 0x100) {
                text = (struct_game_197C20_1 *)D_800DD258[arg0 - 0x100].unk0;
            } else {
                text = (struct_game_197C20_1 *)D_800DD254[arg0].unk0;
            }
        }
        if (arg4 != 0) {
            obj->field_0xD = 2;
        } else if (arg0 >= 0x100) {
            obj->field_0xD = 1;
        } else {
            obj->field_0xD = 0;
        }
        text->unk9 = arg1;
        text->unkA = arg2;
        text->unk2C = arg3;
        obj->field_0xF = text->unk0 & 0xF;
        obj->field_0x10 = text;
        obj->field_0x15 = 1;
        obj->field_0x1F = 0;
        if (arg4 != 0) {
            obj->field_0x14 = 1;
            obj->field_0x16 = arg4->unk26;
        } else {
            obj->field_0x14 = 0;
            obj->field_0x16 = text->unk26 >> 1;
        }
        obj->field_0x18 = 0;
        obj->field_0x1A = 0;
        obj->field_0x28 = 0.0f;
        obj->field_0x38 = 0.0f;
        obj->field_0x3C = 0.0f;
        if (obj->field_0xD == 2) {
            text->unk8 = func_1516A770((u8 *)text->unk4);
        }
        for (i = 0; i < text->unk8; i++) {
            s32 width;
            s32 height;
            s32 baseline;

            str = func_1516C878(text, i, obj->field_0xD);
            func_150428D4(str, &width, &height, &baseline);
            if (obj->field_0x38 < (f32)width) {
                obj->field_0x38 = (f32)width;
            }
            if (obj->field_0x3C < (f32)height) {
                obj->field_0x3C = (f32)height;
            }
        }
        lineHeight = (text->unk0 & 2) ? 25.0f : 18.0f;
        obj->field_0x38 = (obj->field_0x38 + lineHeight * 0.5f) * D_800A6CD0;
        obj->field_0x3C = (obj->field_0x3C + lineHeight) * D_800A6CD4;
        obj->field_0x24 = func_1516C878(text, 0, obj->field_0xD);
        obj->field_0x20 = 0;
        text->unk0 &= ~0x7000;
        ((u8 *)&D_800CC2D0[text->unk9])[0x1E3] = 1;
        obj->field_0xE = 0;
    }
    return obj;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_197C20/func_1516AA70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_197C20/func_1516B6BC.s")

u8 *func_1516C878(struct_game_197C20_1 *arg0, s32 arg1, s16 arg2) {
    u8 *temp_v1;
    u8 *sp0;
    s32 temp_v0;
    s32 temp_a0;

    switch (arg2) {
    case 0:
        temp_v1 = D_800DD254[arg0->unk4].unk0;
        break;
    case 1:
        temp_v1 = D_800DD258[arg0->unk4].unk0;
        break;
    case 2:
        temp_v1 = (u8 *)arg0->unk4;
        break;
    default:
        temp_v1 = sp0;
        break;
    }

    temp_v0 = 0;
    if (arg1 > 0) {
        temp_a0 = temp_v1[0];
        do {
            temp_v0++;
            if (temp_a0 != 0) {
                do {
                    temp_a0 = temp_v1[1];
                    temp_v1++;
                } while (temp_a0 != 0);
            }
            if (temp_a0 == 0) {
                do {
                    temp_a0 = temp_v1[1];
                    temp_v1++;
                } while (temp_a0 == 0);
            }
        } while (temp_v0 != arg1);
    }

    return temp_v1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_197C20/func_1516C934.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_197C20/func_1516CC58.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_197C20/func_1516D0CC.s")

void func_1516D2E0(struct_game_197C20_3 *arg0) {
    if ((arg0 != 0) && (arg0->field_0x0 == 0x51)) {
        arg0->field_0x10->unk8 = 0;
        func_1516972C((struct102 *)arg0);
        arg0->field_0x15 = 0;
    }
}

void func_1516D328(struct_game_197C20_3 *arg0) {
    if ((arg0 != 0) && (arg0->field_0x0 == 0x51)) {
        arg0->field_0x10->unk0 |= 0x100;
        arg0->field_0x10->unk0 &= ~0x400;
        arg0->field_0x20 = arg0->field_0x10->unk8;
    }
}

u8 *func_1516D378(struct_game_197C20_3 *arg0) {
    if ((arg0 != 0) && (arg0->field_0x0 == 0x51)) {
        arg0->field_0x10->unk0 |= 0x100;
        arg0->field_0x10->unk0 &= ~0x400;
        return (u8 *)arg0;
    }
    return 0;
}

s32 func_1516D3C4(u8 *arg0) {
    s32 *temp;

    if ((arg0 != 0) && (*arg0 == 0x51)) {
        temp = *(s32 **)(arg0 + 0x10);
        *temp |= 0x500;
        return (s32)arg0;
    }
    return 0;
}
