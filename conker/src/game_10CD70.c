#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern f32 D_800A0FB4;
extern f32 D_800A0FB8;
extern void *func_1513418C(void *, s32, u8, s32);

typedef union {
    s8 field_0x0_s8;
    s32 field_0x0_s32;
} DisplayListWord0;

typedef struct {
    DisplayListWord0 field_0x0;
    u8 pad_0x4[0x4];
} DisplayListEntry8;

typedef struct {
    u8 pad_0x0[0x13];
    u8 field_0x13;
    u8 pad_0x14[0x10];
    DisplayListEntry8 **field_0x24;
} Game10CD70Object;

typedef struct {
    u8 pad_0x0[0x2D8];
    f32 field_0x2D8;
    f32 field_0x2DC;
    u8 pad_0x2E0[0xC];
    s32 field_0x2EC;
} Game10CD70FadeState;

typedef struct {
    u8 pad_0x0[0x30];
    f32 field_0x30;
    f32 field_0x34;
    f32 field_0x38;
} Game10CD70Transform;

typedef struct {
    u8 pad_0x0[0x14];
    f32 field_0x14;
    u8 pad_0x18[0x4];
    f32 field_0x1C;
    u8 pad_0x20[0x1B4];
    s32 field_0x1D4;
} Game10CD70Actor;

typedef struct {
    s32 unk0;
    s32 unk4;
    u8 unk8;
    u8 pad9[3];
    void *unkC;
    u8 unk10;
    u8 pad11[3];
    struct17 unk14;
    f32 unk20;
    f32 unk24;
    s16 unk28;
    u8 unk2A;
    u8 unk2B;
    s8 unk2C;
    u8 unk2D;
} Struct150E0348;

typedef struct { u8 c[3]; } Outer;
extern Outer D_80088984;

s32 func_150DF8C0(s32 a0) {
    Outer sp4;
    sp4 = D_80088984;
    if (((struct178 *)*(s32 *)&D_800D3098)[((u8 *)&sp4)[a0]].unk6[0xE] != 0) {
        return 1;
    }
    return 0;
}

typedef struct {
    DisplayListWord0 field_0x0;
    s32 field_0x4;
} DisplayListCmd;

extern u8 D_800D9950[];
extern void func_150A2864(s32, s32);
extern void func_150A3444(s32, s16, s16, s16);
extern void func_151749A0(s32, s32);

void func_150DF920(s32 arg0) {
    struct127 *obj;
    s32 i;
    s32 j;
    s32 id;
    s32 slot;
    f32 x;
    f32 y;
    f32 z;
    s32 active;
    DisplayListCmd *dl;
    s32 c;
    s32 uls;
    s32 ult;

    if (arg0 != 0) {
        return;
    }

    func_151749A0(5, 4);

    id = 6;
    slot = 3;
    for (i = 0; i < 2; i++) {
        obj = func_15083E90((u8)id);
        id = 7;
        if (obj != NULL) {
            func_150A2864(slot, 0);
            x = obj->x_position;
            y = obj->y_position + 200.0f;
            z = obj->z_position;
            func_150A3444(slot, (s16)x, (s16)y, (s16)z);
        } else {
            func_150A2864(slot, 1);
        }
        slot = 4;
    }

    dl = (DisplayListCmd *)D_800B0E00[0];

    for (i = 0; i < 3; i++) {
        active = func_150DF8C0(i);
        if (active) {
            if (D_800D9950[i] < 0x60) {
                D_800D9950[i] += D_800BE9E4;
                if (D_800D9950[i] > 0x60) {
                    D_800D9950[i] = 0x60;
                }
            }
        } else {
            D_800D9950[i] = 0;
        }

        j = -1;
        do {
            j++;
            while ((((DisplayListCmd *)((j << 3) + (u8 *)dl))->field_0x0.field_0x0_s8 != -3) &&
                   (((DisplayListCmd *)((j << 3) + (u8 *)dl))->field_0x0.field_0x0_s8 != -0x21)) {
                j++;
            }
            if (((DisplayListCmd *)((j << 3) + (u8 *)dl))->field_0x0.field_0x0_s8 == -0x21) {
                j = -1;
                break;
            }
        } while (((DisplayListCmd *)((u8 *)dl + (j * 8)))->field_0x4 != ((i << 24) + 0x02000000));

        if (j != -1) {
            while ((c = ((DisplayListCmd *)((j << 3) + (u8 *)dl))->field_0x0.field_0x0_s8) != -0xE) {
                j++;
            }

            if (j != -1) {
                if (active) {
                    uls = ((u32)((DisplayListCmd *)((u8 *)dl + (j * 8)))->field_0x0.field_0x0_s32 >> 12) & 0xFFF;
                    ult = ((DisplayListCmd *)((u8 *)dl + (j * 8)))->field_0x0.field_0x0_s32 & 0xFFF;
                    ult += (D_800D9950[i] / 16) * D_800BE9E4;
                } else {
                    ult = 2;
                    uls = 2;
                }
                ((DisplayListCmd *)((u8 *)dl + (j * 8)))->field_0x0.field_0x0_s32 =
                    0xF2000000 | ((uls & 0xFFF) << 12) | (ult & 0xFFF);
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_10CD70/func_150DFBD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_10CD70/func_150DFCA8.s")

extern f32 D_800A0FB0;

void func_150DFDA4(Game10CD70Actor *arg0) {
    Game10CD70Transform *p = (Game10CD70Transform *)(arg0->field_0x1D4 + 0x40);

    p->field_0x30 = arg0->field_0x14;
    p->field_0x34 = D_800A0FB0;
    p->field_0x38 = arg0->field_0x1C;
}

s32 func_150DFDD0(Game10CD70Object *arg0, Game10CD70FadeState *arg1) {
    f32 temp_f2;
    DisplayListEntry8 *temp_v0;
    s32 temp_a0;
    s32 temp_a2;
    s32 temp_v1;

    if (arg1->field_0x2EC != 0) {
        arg0->field_0x13 = 2;
        arg1->field_0x2D8 = arg1->field_0x2D8 - D_800BE9A4;
        if (arg1->field_0x2D8 < 0.0f) {
            arg1->field_0x2EC = 0;
            return 1;
        }
        temp_f2 = 1.0f - (arg1->field_0x2DC * arg1->field_0x2D8);
    } else {
        temp_f2 = 0.0f;
        arg0->field_0x13 = 0;
    }

    temp_v0 = *arg0->field_0x24;
    if (temp_v0 != 0) {
        temp_v1 = 0;
        if (((DisplayListEntry8 *)((temp_v1 << 3) + (u8 *)temp_v0))->field_0x0.field_0x0_s8 != -0xE) {
            do {
            } while (((DisplayListEntry8 *)((u8 *)temp_v0 + (++temp_v1 << 3)))->field_0x0.field_0x0_s8 != -0xE);
        }
        temp_a0 = ((DisplayListEntry8 *)((u8 *)temp_v0 + (temp_v1 * 8)))->field_0x0.field_0x0_s32;
        arg1 = (Game10CD70FadeState *)((u8 *)temp_v0 + (temp_v1 * 8));
        temp_a2 = 2 - ((s32)(((u32)temp_a0 >> 12) & 0xFFF) / 3);
        while (temp_a2 < 0) {
            temp_a2 += 0x40;
        }
        ((DisplayListEntry8 *)arg1)->field_0x0.field_0x0_s32 = 0xF2000000 | ((((s32)((500.0f * temp_f2) + 2.0f)) & 0xFFF) << 12) | (temp_a2 & 0xFFF);
    }

    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_10CD70/func_150DFEFC.s")

void func_150E02C0(s32 arg0, s32 arg1, s32 arg2) {
    func_15149514(arg1, (u8)arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}

void func_1513BAE8(void);

void func_150E0300(void) {
    if (D_80088980 == 0) {
        func_1515F170(6, 0);
        func_1513BAE8();
        D_80088980 = 1;
    }
}

void func_150E0348(void *arg0, u8 arg1, s32 arg2) {
    Struct150E0348 sp18;

    sp18.unk0 = 0;
    sp18.unk4 = 0;
    sp18.unk8 = *((u8 *)arg0 + 0x3B);
    sp18.unk10 = 0;
    sp18.unkC = arg0;
    sp18.unk14 = *(struct17 *)&D_800A5480;
    sp18.unk28 = 0x12C;
    sp18.unk2A = 0x1B;
    sp18.unk2B = 0xB;
    sp18.unk2C = -1;
    sp18.unk2D = 0;
    sp18.unk20 = D_800A0FB4;
    sp18.unk24 = D_800A0FB8;
    func_1513418C(&sp18, 0, arg1, arg2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_10CD70/func_150E03F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_10CD70/func_150E05F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_10CD70/func_150E06D8.s")
