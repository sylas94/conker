#include <ultra64.h>
#include "functions.h"
#include "variables.h"


struct LL155FD4 {
    u8 pad_0x0[0x8];
    struct LL155FD4 *field_0x8;
    u8 pad_0xC[0x2];
    s16 field_0xE;
    u8 field_0x10;
    u8 field_0x11;
    u8 pad_0x12[0x2];
    s32 field_0x14;
    u8 pad_0x18[0x80];
    f32 field_0x98;
};

extern u8 D_800DCE50[];


extern void *func_15167A68(s32, s32, s32, s32, s32, s32);
void func_1518C900(s32);

void *func_15155780(s32 arg0, s32 arg1) {
    struct LL155FD4 *temp_v0;

    temp_v0 = (struct LL155FD4 *)func_15167A68(0x50, 0, 0xA0, 1, arg1, 1);
    if (temp_v0 == 0) {
        return temp_v0;
    }
    temp_v0->field_0x10 = arg0;
    temp_v0->field_0x98 = 0.0f;
    temp_v0->field_0x11 = 0;
    temp_v0->field_0x14 = 0;
    func_1518C900(0xA6);
    return temp_v0;
}

extern u8 D_800CC37D;
extern u8 *func_15155FD4(s32 arg0);

void func_151557FC(s32 arg0, s32 arg1, f32 arg2) {
    struct LL155FD4 *temp_v0;

    temp_v0 = (struct LL155FD4 *)func_15155FD4(arg0);
    if (temp_v0 == 0) {
        temp_v0 = (struct LL155FD4 *)func_15155780(arg0, 0xFF);
    }
    if (temp_v0 != 0) {
        temp_v0->field_0x98 = arg2;
        if ((&D_800CC37D)[arg0 * 812] != 0) {
            temp_v0->field_0xE = 0;
            temp_v0->field_0x11 = 0;
        } else {
            temp_v0->field_0x11 = 3;
            temp_v0->field_0xE = arg1;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_182C30/func_1515589C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_182C30/func_15155CFC.s")

void func_1515F10C(struct226 *arg0, struct225 *arg1);
void func_1518CA04(s32 arg0);

void func_15155EF8(struct225 *arg0) {
    if (arg0->unk14 != NULL) {
        func_1515F10C(arg0->unk14, arg0);
    }
    func_15169804((struct102 *)arg0);
    func_1518CA04(0xA6);
}

extern u8 *func_15155FD4(s32 arg0);

void func_15155F3C(void) {
    u8 *temp_v0 = func_15155FD4(D_800C3E78);
    if (temp_v0 != NULL) {
        if (temp_v0[0x11] == 2) {
            temp_v0[0x11] = 0;
        } else if (temp_v0[0x11] == 3) {
            temp_v0[0x11] = 2;
        }
    }
}


void func_15155F90(void) {
    u8 *temp_v0 = func_15155FD4(D_800C3E78);
    if (temp_v0 != NULL) {
        if (temp_v0[0x11] == 3) {
            temp_v0[0x11] = 1;
        }
    }
}

u8 *func_15155FD4(s32 arg0) {
    s32 i;
    struct LL155FD4 *node;

    i = 0;
    do {
        node = *(struct LL155FD4 **)&D_800DCE50[i + 0x140];
        i += 0x1A0;
        while (node != NULL) {
            if (arg0 == node->field_0x10) {
                return (u8 *)node;
            }
            node = node->field_0x8;
        }
    } while ((u8 *)&D_800DD190 != &D_800DCE50[i]);
    return NULL;
}

typedef struct {
    u8 pad0[0x10];
    u8 owner;
} Node15156028;

void func_15156028(Node15156028 *arg0, struct127 **arg1, u8 arg2) {
    if (arg2 == 0) {
        s32 a = arg1[0] - D_800CC2D0;

        if ((a >= 0) && (a < 25) && (a == arg0->owner)) {
            func_1516972C((struct102 *)arg0);
        }
    } else if (arg2 == 0x2D) {
        s32 a = arg1[0] - D_800CC2D0;
        s32 b = arg1[1] - D_800CC2D0;

        if ((a >= 0) && (a < 25) && (b >= 0) && (b < 25)) {
            if (a == arg0->owner) {
                arg0->owner = b;
            } else if (b == arg0->owner) {
                arg0->owner = a;
            }
        }
    }
}
