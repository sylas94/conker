#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_1B0740/func_15183290.s")

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} Struct15183974;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Inner1502B6BC;

extern u8 D_800DDF69[];
void func_15183ACC(s32);
Inner1502B6BC *func_1502B6BC(s32, s32, s32, s32, s32, s32);

void func_151838B0(s32 arg0) {
    Inner1502B6BC *ret;

    if (((Struct15183974 *)D_800DDE80)[arg0].unk0 == 0) {
        func_15183ACC(arg0);
    }
    if (((Struct15183974 *)D_800DDE80)[arg0 + 1].unk0 == 0) {
        ret = func_1502B6BC(0, 0, 0, 2, 9, arg0 + 0xAE);
        if (ret != 0) {
            ((Struct15183974 *)D_800DDE80)[arg0 + 1].unk0 = (s32)ret;
            ((Struct15183974 *)D_800DDE80)[arg0 + 1].unk4 = ret->unk0;
            ((Struct15183974 *)D_800DDE80)[arg0 + 1].unk8 = ret->unk8;
            ((Struct15183974 *)D_800DDE80)[arg0 + 1].unk10 = 0;
            ((Struct15183974 *)D_800DDE80)[arg0 + 1].unkC = ((Struct15183974 *)D_800DDE80)[arg0].unkC;
            D_800DDF69[arg0] = 1;
        }
    }
}

void func_15183974(s32 arg0) {
    if (((Struct15183974 *)D_800DDE80)[arg0].unk0 == 0) {
        func_15183ACC(arg0);
    }
    if (((Struct15183974 *)D_800DDE80)[arg0 + 1].unk0 == 0) {
        func_15183ACC(arg0 + 1);
        ((Struct15183974 *)D_800DDE80)[arg0 + 1].unkC = ((Struct15183974 *)D_800DDE80)[arg0].unkC;
    }
}

void func_151839F0(s32 arg0, s32 arg1) {
    Inner1502B6BC *ret;

    if (((Struct15183974 *)D_800DDE80)[arg0].unk0 == 0) {
        func_15183ACC(arg0);
    }
    if (((Struct15183974 *)D_800DDE80)[arg0].unk0 != 0) {
        if (((Struct15183974 *)D_800DDE80)[arg1].unk0 == 0) {
            ret = func_1502B6BC(0, 0, 0, 2, 9, arg1 + 0xAD);
            if (ret != 0) {
                ((Struct15183974 *)D_800DDE80)[arg1].unk0 = (s32)ret;
                ((Struct15183974 *)D_800DDE80)[arg1].unk4 = ret->unk0;
                ((Struct15183974 *)D_800DDE80)[arg1].unk8 = ret->unk8;
                ((Struct15183974 *)D_800DDE80)[arg1].unkC = ((s32 *)ret)[6];
                ((Struct15183974 *)D_800DDE80)[arg1].unk10 = 0;
                D_800DDF68[arg1] = 1;
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B0740/func_15183ACC.s")

extern u8 D_800A72D0[];

u32 *func_15183BA4(u32 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 idx;
    s32 i;
    u32 *p;

    idx = -1;
    for (i = 0; i != 11; i++) {
        if (arg1 == D_800A72D0[i]) {
            idx = i;
            break;
        }
    }

    if (idx != -1) {
        if (D_800DDF78[idx] != 0) {
            p = arg0;
            arg0 += 2;
            p[0] = 0xDE000000;
            p[1] = D_800DDF78[idx];
        }
    }
    return arg0;
}

extern s8 D_800DDF70;
extern s8 D_800DDF71;
extern s32 D_800DDF20;
extern s32 D_800DDF98;
void func_1510D630(s32);
void func_10004074(s16 *);

void func_15183C28(s32 arg0) {
    if (((Struct15183974 *)D_800DDE80)[arg0].unk10 != 0) {
        func_1510D630(((Struct15183974 *)D_800DDE80)[arg0].unk10);
        ((Struct15183974 *)D_800DDE80)[arg0].unk10 = 0;
    }
    if (arg0 == 8) {
        if (D_800DDF71 != -2) {
            return;
        }
    } else if (arg0 == 9) {
        if (D_800DDF70 == -2) {
            if (D_800DDF20 != 0) {
                func_10004074((s16 *) D_800DDF20);
                D_800DDF20 = 0;
                D_800DDF98 = 0;
            }
        }
    }
    if (((Struct15183974 *)D_800DDE80)[arg0].unk0 != 0) {
        func_10004074((s16 *) ((Struct15183974 *)D_800DDE80)[arg0].unk0);
        ((Struct15183974 *)D_800DDE80)[arg0].unk0 = 0;
        D_800DDF78[arg0] = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B0740/func_15183D28.s")

typedef struct {
    char pad[0x57];
    u8 unk57;
} Struct15184118;

typedef struct {
    char pad[0x31C];
    Struct15184118 *unk31C;
} Obj15184118;

s32 func_15184118(Obj15184118 *a0) {
    if (a0->unk31C != 0) {
        if (a0->unk31C->unk57 != 0) {
            return 1;
        }
    }
    return 0;
}
