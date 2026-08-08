#include <ultra64.h>
#define func_1513D524 func_1513D524_void_proto
#include "functions.h"
#undef func_1513D524
#include "variables.h"

extern void func_151D5D60();

struct Foo150DB2D8 {
    char pad0[0x2C];
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    char pad44[0x4];
    f32 unk48;
    char pad4C[0x74];
    char unkC0[0x40];
    s16 *unk100[1];
};


#pragma GLOBAL_ASM("asm/nonmatchings/game_108320/func_150DAE70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_108320/func_150DB114.s")

s16 *func_150DB2D8(struct Foo150DB2D8 *arg0, s16 arg1) {
    s16 *var_v0;
    s16 *ret;
    f32 temp_f2;
    f32 temp_f12;
    u8 sp37;

    func_151D5D60(arg0->unk100, arg1, 0x40, &var_v0, &sp37);
    ret = var_v0;
    if (var_v0) {
        if (sp37) {
            memcpy(arg0->unk100[arg1], arg0->unkC0, 0x40);
            memcpy(arg0->unk100[arg1] + 0x20, arg0->unkC0, 0x40);
        }
    } else {
        return 0;
    }

    temp_f2 = arg0->unk2C * arg0->unk40;
    temp_f12 = -arg0->unk2C * arg0->unk48;

    var_v0[0] = arg0->unk34 + temp_f2;
    var_v0[1] = arg0->unk38 + arg0->unk30;
    var_v0[2] = arg0->unk3C + temp_f12;
    var_v0[3] = 0;
    var_v0[8] = arg0->unk34 + temp_f2;
    var_v0[9] = arg0->unk38 - arg0->unk30;
    var_v0[10] = arg0->unk3C + temp_f12;
    var_v0[11] = 0;
    var_v0[16] = arg0->unk34 - temp_f2;
    var_v0[17] = arg0->unk38 - arg0->unk30;
    var_v0[18] = arg0->unk3C - temp_f12;
    var_v0[19] = 0;
    var_v0[24] = arg0->unk34 - temp_f2;
    var_v0[25] = arg0->unk38 + arg0->unk30;
    var_v0[26] = arg0->unk3C - temp_f12;
    var_v0[27] = 0;

    return ret;
}

typedef struct {
    u8  unk0;
    u8  unk1;
    s16 unk2;
    s16 unk4;
    u8  pad6[2];
    s32 unk8;
    s32 unkC;
    u8  unk10;
    u8  unk11;
    u8  unk12;
    u8  unk13;
    u8  pad14[0x2C];
    s32 unk40;
    u8  unk44;
    u8  unk45;
    u8  pad46[0x12];
} Struct150DB518;

typedef struct {
    u8  pad0[0x110];
    s32 unk110;
    s32 unk114;
    s32 unk118;
    s32 unk11C;
    s32 unk120;
} Struct150DB518Obj;

extern Struct150DB518Obj *func_1513D524(s32 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, s32 arg6, u8 arg7, s32 arg8);

void func_150DB518(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s16 arg5, u8 arg6, s32 arg7) {
    Struct150DB518 sp38;
    Struct150DB518Obj *temp_v0;

    if (arg0 != 0 && arg1 != 0 && arg2 != 0 && arg3 != 0 && arg4 != 0 && arg5 != 0) {
        sp38.unk0 = 0x17;
        sp38.unkC = 0x243A;
        sp38.unk40 = 0x401;
        sp38.unk44 = 0xFF;
        sp38.unk8 = 0;
        sp38.unk4 = arg5;
        sp38.unk45 = 0xFF;
        *((u8 *)&sp38 + 0x12) = 0xC8; *((u8 *)&sp38 + 0x11) = 0xC8; *((u8 *)&sp38 + 0x10) = 0xC8;
        *((u8 *)&sp38 + 0x13) = 0xC8;
        sp38.unk2 = 0x401;

        temp_v0 = func_1513D524((s32)&sp38, 0, 0xA, 0, 8, 0, 0x14, arg6, arg7);
        if (temp_v0 != 0) {
            temp_v0->unk110 = arg0;
            temp_v0->unk114 = arg1;
            temp_v0->unk118 = arg2;
            temp_v0->unk11C = arg4;
            temp_v0->unk120 = arg3;
        }
    }
}

s32 func_150DB630(void *arg0) {
    f32 temp_f0;
    s32 ret;

    ret = 1;
    if (255.0f < **(f32 * *)((u8 *)arg0 + 0x120)) {
        *(u8 *)((u8 *)arg0 + 0x5C) = 0xFF;
    } else {
        temp_f0 = **(f32 * volatile *)((u8 *)arg0 + 0x120);
        if (temp_f0 < 0.0f) {
            *(u8 *)((u8 *)arg0 + 0x5C) = 0;
        } else {
            *(u8 *)((u8 *)arg0 + 0x5C) = (u32)temp_f0;
        }
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_108320/func_150DB714.s")
