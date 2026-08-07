#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} struct1512ABF8;

extern struct1512ABF8 D_80089590[];
extern u8 D_800DC0C0[];
extern struct1512ABF8 D_800DC200[][4];
extern s16 D_800DC204[];
extern s16 D_800DC206[];
extern f32 D_800A3694;
extern f32 D_800A3698;

void func_15123A54(struct108 *arg0);
void func_1512AD54(struct108 *arg0);
void func_1512C150(struct108 *arg0);

#pragma GLOBAL_ASM("asm/nonmatchings/game_157840/func_1512A390.s")

void func_1512ABF8(void) {
    f32 temp_f2;
    f32 temp_f0;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_t1;
    s32 temp_t2;
    u8 i;
    u8 j;
    register struct1512ABF8 *src;
    struct1512ABF8 *temp_v0;

    temp_f2 = 0.75f;
    temp_f0 = 0.5f;
    src = D_80089590;
    temp_t2 = 0x1E;
    temp_t1 = 0x1B;

    for (temp_a1 = D_80082FA0, temp_a2 = D_800BE9F0, i = 0; i < 4; i++) {
        j = 0;
        do {
            temp_v0 = &D_800DC200[i][j];
            *temp_v0 = src[j];

            if ((temp_a1 > 0) && (temp_a1 < 4)) {
                temp_v0->unk0 = temp_v0->unk0 * temp_f0;
                temp_v0->unk2 = temp_v0->unk2 * temp_f0;
            }

            if ((temp_t1 == temp_a2) || (temp_t2 == temp_a2)) {
                temp_v0->unk0 = temp_v0->unk0 * temp_f2;
                temp_v0->unk2 = temp_v0->unk2 * temp_f2;
            }
            j++;
        } while (j < 4);
    }

    bzero(D_800DC0C0, 0x130);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_157840/func_1512AD54.s")

void func_1512B100(struct108 *arg0) {
    s32 temp_v0;

    temp_v0 = arg0->unk2C;
    if ((temp_v0 & ~0x100) && (D_800BEAC0 == 0) && (D_800C3671 == 0)) {
        if (temp_v0 != 0x40) {
            temp_v0 = arg0->unk84;
            if ((temp_v0 & 8) && !(temp_v0 & 0x200) && (arg0->unk23C == 0)) {
                temp_v0 = arg0->unk5F0;
                if (!(temp_v0 & 0x80) && !(temp_v0 & 0x40)) {
                    func_1512AD54(arg0);
                    return;
                }
            }
        }
        *(s16 *)((u8 *)arg0 + 0x5F8) = 1;
        arg0->unk5FC = 2;
        arg0->unk5FE = 0x3C;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_157840/func_1512B1B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_157840/func_1512B53C.s")

struct Struct1512B5FC {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    s32 unk4;
    s32 unk8;
};

void func_1512B5FC(struct Struct1512B5FC *arg0, s32 arg1, s32 arg2) {
    arg0->unk2 = arg0->unk1;
    if (arg0->unk4 < arg1) {
        arg0->unk1 = 0;
    } else {
        arg0->unk1 = 1;
    }
    arg0->unk8 = arg2;
    arg0->unk4 = arg1;
}

s32 func_1512B630(struct108 *arg0, struct Struct1512B5FC *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp;

    if (arg5 == 0) {
        temp = *(s16 *)((u8 *)D_800DC204 + (arg0->unk23D * 0x20) + (arg0->unk1B4 * 8));
    } else {
        temp = *(s16 *)((u8 *)D_800DC206 + (arg0->unk23D * 0x20) + (arg0->unk1B4 * 8));
    }

    if (arg0->unk84 & 0x8000) {
        temp = (s16)(temp << 1);
    }

    if ((temp < arg2) && (arg3 < arg4)) {
        arg1->unk0 = 2;
        func_1512B5FC(arg1, arg3, arg2);
        return 1;
    }

    if ((temp < arg2) && (arg4 < arg3)) {
        arg1->unk0 = 1;
        func_1512B5FC(arg1, arg3, arg2);
        return 1;
    }

    arg1->unk1 = 0;
    arg1->unk0 = 0;
    arg1->unk8 = 0xFFFC;
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_157840/func_1512B730.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_157840/func_1512BB10.s")

void func_1512C068(struct108 *arg0) {
    f32 temp_f14;
    f32 temp_f2;
    f32 temp_f12;
    f32 temp_f0;

    if (arg0->unk390 < 180.0f) {
        temp_f14 = 2.0f;
    } else {
        temp_f14 = -2.0f;
    }

    if ((arg0->unk2C != 0x80) && (arg0->unk2C != 0x40)) {
        temp_f2 = arg0->unk2F8 - arg0->unk2BC;
        temp_f12 = arg0->unk300 - arg0->unk2C4;
        temp_f0 = sqrtf((temp_f2 * temp_f2) + (temp_f12 * temp_f12));
        *(f32 *)arg0->pad370 = temp_f0;

        if (temp_f0 < 42.0f) {
            arg0->unk384 = arg0->unk37C - (45.0f * temp_f14);
            arg0->unk5CC = 0.0f;
            func_15123A54(arg0);
            arg0->unk240 |= 2;
        }
    }

    func_1512C150(arg0);
}

void func_1512C150(struct108 *arg0) {
    f32 temp_f0;

    arg0->unk5CC += D_800A3694;
    temp_f0 = arg0->unk5CC;
    if (temp_f0 > 1.0f) {
        arg0->unk5CC = 1.0f;
    } else {
        arg0->unk5CC = temp_f0;
    }

    if (arg0->unk5CC == 1.0f) {
        arg0->unk384 = D_800A3698;
        arg0->unk240 &= ~2;
    } else {
        arg0->unk384 += func_15048A70(arg0->unk384, arg0->unk37C) * arg0->unk5CC;
    }
}

void func_1512C200(s32 arg0) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_157840/func_1512C20C.s")

s32 func_1512C47C(s32 arg0) {
    return 0x1;
}
