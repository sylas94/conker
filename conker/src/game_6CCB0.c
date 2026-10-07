#include <ultra64.h>
#include "functions.h"
#include "variables.h"


typedef struct Node1503F800 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
} Node1503F800;

extern Node1503F800 *D_800DBE48;
extern void func_1510F800(s32);

s32 func_1503F800(void *arg0, s16 x, s16 y, s32 bit, s32 arg4) {
    Node1503F800 *node;
    s32 off;

    func_1510F800(0);
    node = D_800DBE48;
    while (node != NULL) {
        if (node->unk8 + node->unk6 >= x && x >= node->unk8 - node->unk6
            && node->unkA + node->unk6 >= y && y >= node->unkA - node->unk6) {
            if (!(node->unk2 & (1 << bit))) {
                return 1;
            }
            if (node->unkC != 0) {
                off = node->unkC;
            } else {
                return 0;
            }
        } else {
            off = node->unk4;
        }
        if (off != 0) {
            node = (Node1503F800 *)((u8 *)node + off);
        } else {
            node = NULL;
        }
    }
    return 1;
}

struct Game1503F904 {
    char pad14[0x14];
    f32 unk14;
    char pad18[0x4];
    f32 unk1C;
};

extern s32 func_1503F800(void *, s16, s16, s32, s32);

void func_1503F904(struct Game1503F904 *arg0, s32 arg1, s32 arg2) {
    func_1503F800((s32)arg0 + 0x320, (s16)(s32)arg0->unk14, (s16)(s32)arg0->unk1C, arg1, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_6CCB0/func_1503F964.s")
