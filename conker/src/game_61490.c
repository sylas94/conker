#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern void func_1503453C(s32);
extern void func_15036310(s32, s32, s32, s32);
extern void func_15034EB4(struct127 *, s32, s32);
extern void func_150F1A00(struct127 *);
extern void func_150DFDA4(struct127 *);


#pragma GLOBAL_ASM("asm/nonmatchings/game_61490/func_15033FE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_61490/func_150341BC.s")

s16 *func_15034340(s16 *arg0, s32 arg1) {
    struct127 *obj = &D_800CC2D0[arg1];

    if (obj->unk1D1 != 0) {
        *arg0 = 6;
        arg0 += 2;
        arg0[-1] = obj->unk1D1 * 200;
    }
    return arg0;
}

s16 *func_150343B0(s16 *arg0, s32 arg1) {
    struct127 *obj = &D_800CC2D0[arg1];

    if (obj->unk1D1 != 0) {
        *arg0 = 6;
        arg0 += 2;
        arg0[-1] = obj->unk1D1 * 200;
    }
    return arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_61490/func_15034420.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_61490/func_150344A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_61490/func_1503453C.s")

void func_150345E4(s32 arg0) {
    if (D_800CC2D0[arg0].unk1D4 != 0) {
        if ((D_800CC2D0[arg0].interaction_state == 1) || (D_800CC2D0[arg0].unk5 == 7)) {
            func_1503453C(arg0);
        }

        if (D_800CC2D0[arg0].interaction_state == 0x22) {
            func_1503453C(arg0);
        }

        switch (D_800CC2D0[arg0].id) {
        case 4:
            if (D_800BE616 == 0) {
                func_15036310(0, arg0, 9, 0);
                func_15036310(0, arg0, 4, 0);
            }
            break;
        case 0x70:
            func_15034EB4(&D_800CC2D0[arg0], 10, 11);
            break;
        case 0x7B:
            func_150F1A00(&D_800CC2D0[arg0]);
            break;
        case 0x60:
            func_150DFDA4(&D_800CC2D0[arg0]);
            break;
        }
    }
}

extern s32 func_1502DB20(u8);

void func_15034728(struct127 *arg0) {
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    u8 *m;

    if (arg0->unk1D4 != NULL && arg0->unk9C != 0) {
        n = func_1502DB20(arg0->id) - 1;
        m = (u8 *)arg0->unk1D4;
        i = 31;
        if (n < 31) {
            i = n;
        }
        for (; i >= 0; i--) {
            if (arg0->unk9C & (1 << i)) {
                for (j = 0; j < 3; j++) {
                    for (k = 0; k < 3; k++) {
                        ((f32 *)((i << 6) + m + (j << 4)))[k] = 0.0f;
                    }
                }
            }
        }
    }
}


extern void func_15034728(struct127 *);

void func_150347E8(void) {
    struct127 *obj;

    if (D_800BEAC0 != 0) {
        return;
    }

    obj = D_800CC2D0;
    do {
        if (obj->interaction_state != 0 && obj->unk9C != 0) {
            func_15034728(obj);
        }
        obj++;
    } while (obj != (struct127 *)&D_800D121C);
}
