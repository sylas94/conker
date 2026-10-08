#include <ultra64.h>
#include "functions.h"
#include "variables.h"


typedef struct {
    u8 unk0;
    u8 pad1;
    s8 unk2;
    u8 pad3;
    s16 unk4;
    s16 unk6;
    s16 unk8;
} Struct1500FE30;

extern void *allocate_memory(s32, s32, s32, s32);
extern void func_150C851C(s32);

void func_1500FE30(void) {
    s32 i;

    D_800BE4E0 = (s32)allocate_memory(100, 1, 0, 0);
    bzero((void *)D_800BE4E0, 100);
    for (i = 0; i < 10; i++) {
        ((Struct1500FE30 *)D_800BE4E0)[i].unk0 = i / 5;
        ((Struct1500FE30 *)D_800BE4E0)[i].unk2 = -1;
        ((Struct1500FE30 *)D_800BE4E0)[i].unk4 = (u32)func_150ADA20() % 5;
    }
    func_150C851C(100);
    for (i = 0; i < 10; i++) {
        ((Struct1500FE30 *)D_800BE4E0)[i].unk6 = ((Struct1500FE30 *)D_800BE4E0)[i].unk8;
    }
}

extern s32 D_800917B8;
extern void func_1510C4AC(s32, s32, s32, s32);

void func_1500FF9C(void) {
    func_1510C4AC(D_800917B8, 0, 0xAD, 0x75);
}

extern s32 D_800902DC;
extern u8 *D_80088870;
void func_1500FE30(void);

void func_1500FFCC(void) {
    f32 sp44;
    struct260 *fx;

    func_15195AA8(D_800B0E00[0], D_800902DC, 1, -1, 0, 0, 0, -4);
    func_15195AA8(D_800B0E04, D_800902DC, 1, -1, 0, 1, 0, -4);
    func_1500FE30();
    func_1500FF9C();
    sp44 = 0.0f;
    fx = func_151491F4(0x12C, -1, 0x12, 0, 0xE, 4, 0xFF, 0);
    if (fx != NULL) {
        memcpy((u8 *)fx + 0x28, &sp44, 4);
    }
    {
        struct {
            f32 unk0;
            f32 unk4;
        } sp38;
        struct260 *fx2;

        sp38.unk0 = 0.0f;
        sp38.unk4 = 0.0f;
        fx2 = func_15149130(0x12C, -1, 0x17, -1, 0, 0x14, (struct37 *)8, 0xFF, 1);
        if ((D_80088870 = (u8 *)fx2) != NULL) {
            memcpy((u8 *)fx2 + 0x28, &sp38, 8);
        }
    }
}
