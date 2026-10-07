#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern void *allocate_memory(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

typedef struct {
    u8 pad0[0x44];
    f32 unk44;
    u8 pad48[0x4];
    s16 unk4C;
} func_1503B7C0_sub;

typedef struct {
    u8 pad0[0x11C];
    func_1503B7C0_sub *unk11C;
} func_1503B7C0_inner;

void func_1503B7C0(struct127 *arg0) {
    ((func_1503B7C0_inner *)arg0->unk31C)->unk11C = allocate_memory(0x50, 1, 0, 0);
    bzero(((func_1503B7C0_inner *)arg0->unk31C)->unk11C, 0x50);
    ((func_1503B7C0_inner *)arg0->unk31C)->unk11C->unk44 = 30.0f;
    ((func_1503B7C0_inner *)arg0->unk31C)->unk11C->unk4C = func_150ADA20() % 30U;
}

extern u16 D_8009877C[90];
extern u16 D_80098830[3];

void func_1503B840(struct127 *arg0) {
    s32 i;

    if (arg0->interaction_state == 1) {
        for (i = 0; i < 3; i++) {
            if (arg0->unk84.uh == D_80098830[i]) {
                arg0->unk2FB |= 2;
                return;
            }
        }
        for (i = 0; i < 90; i++) {
            if (arg0->unk84.uh == D_8009877C[i]) {
                arg0->unk2FB |= 1;
                return;
            }
        }
    }
}

extern u8 D_800CC5CB[];

s32 func_1503B95C(s32 arg0, u8 *arg1) {
    s32 v = D_800CC5CB[arg0 * 812];
    if (v & 2) {
        arg1[0x4E] = 0;
        return 0;
    }
    if (v & 1) {
        return 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_68C70/func_1503B9BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_68C70/func_1503CB98.s")
