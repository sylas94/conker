#include <ultra64.h>
#define func_15083E90 func_15083E90_s32_decl_in_functions_h
#include "functions.h"
#undef func_15083E90
struct127 *func_15083E90(u8);
#include "variables.h"


struct C4DC0_elem30 {
    u8 pad0[2];
    u8 unk2;
    u8 pad3[0x2D];
};
extern s32 func_15082A44(void *, s32, s32, s32, s32);

s32 func_15097910(s32 arg0, s32 arg1) {
    s32 ret;
    struct127 *obj;

    ret = func_15083E0C((u8)arg0);
    if (ret != -1) {
        obj = func_15083E90((u8)arg0);
        if (obj == NULL) {
            ((struct C4DC0_elem30 *)D_800D20FC)[ret].unk2 = 0;
            if (func_15082A44(ret + (struct C4DC0_elem30 *)D_800D20FC, ret, 0, 0, 0) == 0) {
                return -1;
            }
            ret = func_15083E0C((u8)arg0);
        } else {
            ret = ((u8 *)obj)[0x13F];
        }
    }
    if (ret != 0) {
        ret |= 0x2000;
    }
    return ret;
}


struct C4DC0_arg1 {
    u8 pad0[4];
    s32 unk4;
};
struct C4DC0_elem {
    u8 pad0[2];
    u8 unk2;
    u8 pad3[0x2D];
};
extern struct127 *func_1505EEF4(s32);
extern s32 func_15053430(struct127 *);
extern u8 D_800D2100;
extern s32 D_800D3840;

s32 func_150979CC(s32 arg0, struct C4DC0_arg1 *arg1) {
    struct127 *temp;

    temp = func_1505EEF4(arg0);
    if (temp == 0) {
        return 0;
    }
    if (arg0 < D_800D2100) {
        ((struct C4DC0_elem *)D_800D20FC)[arg0].unk2 = 1;
    }
    if (D_800D3840 == 2) {
        if (arg1->unk4 == 0) {
            func_15060F28(temp, 0);
        } else {
            func_15053430(temp);
        }
    } else {
        func_15060F28(temp, 0);
    }
    return 999999;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_C4DC0/func_15097A8C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_C4DC0/func_15099C14.s")
