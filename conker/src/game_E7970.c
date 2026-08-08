#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_8009FE64;
void func_15143E94(s32 arg0, s32 arg1);
void func_15165F80(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);
void func_1514C678(f32 arg0, f32 arg1, s32 arg2, f32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, f32 arg9, s32 argA, s32 argB);


void func_150BA4C0(struct127 *arg0, u8 arg1, s32 arg2) {
    struct {
        struct127 *unk0;
        u8 unk4;
        f32 unk8;
    } sp3C;
    struct260 *temp_v0;

    sp3C.unk0 = arg0;
    sp3C.unk4 = arg0->unique_id;
    sp3C.unk8 = 0.0f;

    temp_v0 = func_15149130((func_150ADA20() % 9U) + 0xF, -1, 0x52, -1, 1, 0x3F, (struct37 *)0xC, arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy((void *)((s32)temp_v0 + 0x28), &sp3C, 0xC);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_E7970/func_150BA55C.s")

void func_15149514(s32 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_150BA8F0(s32 arg0, s32 arg1, u8 arg2) {
    func_15149514(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}

extern f32 D_8009FE60;
void func_1504715C(s32 *arg0);
void func_15046C80(struct17 *arg0, s32 arg1, f32 arg2, s32 *arg3);

s32 func_150BA930(struct17 *arg0, struct127 *arg1, s32 *arg2, s32 arg3) {
    struct17 sp24;

    arg0->unk0 = arg1->x_position;
    if (D_8009FE60 < arg1->unk180) {
        arg0->unk4 = arg1->unk180;
    } else {
        arg0->unk4 = arg1->y_position;
    }
    arg0->unk8 = arg1->z_position;
    if (arg2 == 0) {
        return 1;
    }
    sp24.unk0 = arg0->unk0;
    sp24.unk4 = arg0->unk4 + 100.0f;
    sp24.unk8 = arg0->unk8;
    func_1504715C(arg2);
    func_15046C80(&sp24, 0, arg0->unk4 - 100.0f, arg2);
}

s32 func_150BAA00(s32 arg0, s32 arg1) {
    return 0x9;
}

void func_150BAA14(struct127 *arg0, s32 arg1, s32 arg2) {
    struct17 sp6C;
    s32 sp48[9];
    s32 sp44;
    u8 sp43;

    if (arg0->unk1D4 == 0) {
        return;
    }

    sp43 = func_150BA930(&sp6C, arg0, sp48, (u8)arg1);
    func_151D5404(&sp6C, 1307.0f, 2000.0f, 0.0005f, 0xC, 0xF, 0xFF, 0);
    func_15143E94(5, 0x4022);

    if (sp43 != 0) {
        sp44 = (s32)(D_800DBFF0[D_80082FA4].unk380 * D_8009FE64);
        func_15165F80(-1, (s32)sp6C.unk0, (s32)(sp6C.unk4 + 6.0f), (s32)sp6C.unk8,
                      0x19, 0x12, 0, 0xFF, 1);
        *((f32 *)&sp44 - 3) = func_150ADA68();
        func_1514C678(sp6C.unk0, sp6C.unk4, *(s32 *)&sp6C.unk8,
                      (*((f32 *)&sp44 - 3) * 50.0f) + 40.0f, sp44 + 0x3C, sp44 - 0x3C,
                      (func_150ADA20() % 11U) + 0x1E, 5, 0, 0.0f, 0, 0xFF);
    }
}
