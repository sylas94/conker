#include <ultra64.h>
#define func_15169260 func_15169260_s32_decl
#include "functions.h"
#undef func_15169260
#include "variables.h"

extern f32 sqrtf(f32);
extern f32 D_800A3848;
extern f32 D_800A384C;
extern f32 D_800A3850;
extern void (*D_80089814[])(s32 *);

typedef struct Obj15131B7C {
    u8 pad0[0x3C];
    f32 unk3C;
    f32 unk40;
    f32 unk44;
    u8 pad48[0x10];
    f32 unk58;
    f32 unk5C;
    f32 unk60;
    f32 unk64;
    s32 unk68;
} Obj15131B7C;

typedef struct Struct15131B7CArg3 {
    u8 unk0;
    u8 pad1[3];
    f32 unk4;
} Struct15131B7CArg3;

typedef struct Struct15130280 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Struct15130280;

typedef struct Struct15130280Payload {
    Struct15130280 unk0[3];
} Struct15130280Payload;

typedef struct Obj15130280 {
    u8 pad_0x0[0x2B];
    u8 field_0x2B;
    u8 pad_0x2C[0xC];
    f32 field_0x38;
    f32 field_0x3C;
    u8 pad_0x40[0xC];
    f32 field_0x4C;
    u8 pad_0x50[0x4];
    f32 field_0x54;
    f32 field_0x58[3];
    u8 pad_0x64[0x1C];
    Struct15130280Payload unk80;
    u8 pad_0xA4[0x4];
    f32 field_0xA8;
    f32 field_0xAC;
    f32 field_0xB0;
    f32 field_0xB4;
    f32 field_0xB8;
} Obj15130280;

typedef struct Obj15130280AngleState {
    u8 pad_0x0[0x38];
    f32 field_0x38;
    f32 field_0x3C;
    u8 pad_0x40[0x68];
    u8 field_0xA8[2];
    s8 field_0xAA[2];
    f32 field_0xAC;
    f32 field_0xB0[2];
} Obj15130280AngleState;

typedef struct Data15131D4C {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Data15131D4C;

extern Data15131D4C D_800A37F0;
void func_15169260(Data15131D4C *, s32, s32, u8);

extern void *func_15167A68(s32, s32, s32, s32, s32, s32);

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
} Struct15131EE4Extra;

typedef struct {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    s32 unkC;
    s32 unk10;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 unk17;
    u8 unk18;
    u8 unk19;
    u8 unk1A;
    u8 unk1B;
    u8 unk1C;
    u8 unk1D;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    struct17 unk30;
    struct17 unk3C;
    struct17 unk48;
    f32 unk54;
    s32 unk58;
    s32 unk5C;
    u8 unk60;
    u8 unk61;
    u8 unk62;
    s8 unk63;
    s8 unk64;
    u8 unk65;
    u8 unk66;
    u8 pad67[9];
} Struct15131EE4Local;

void *func_15130280(void *arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5) {
    void *temp_v0;
    void *sp24;
    s32 id;

    switch (arg1) {
    case 0:
        id = 0x2B;
        break;
    case 1:
        id = 0x52;
        break;
    case 2:
        id = 0x47;
        break;
    default:
        id = 0x2B;
        break;
    }

    temp_v0 = func_15167A68(id, arg5, arg3 + 0xA8, 1, arg4, 1);
    if (temp_v0 == 0) {
        return NULL;
    }

    sp24 = temp_v0;
    memcpy((s32)temp_v0 + 0x10, arg0, 0x70);

    if (arg2 != 0) {
        ((Obj15130280 *)sp24)->unk80 = *(Struct15130280Payload *)arg2;
    } else {
        *(u8 *)((s32)sp24 + 0x9C) = 0;
    }

    return sp24;
}

void func_15130374(s32 a0, u8 a1, s32 a2, u8 a3, s32 a4) {
    func_15130280(a0, a1, 0, a2, a3, a4);
}

void func_151303BC(s32 a0, u8 a1, s32 a2) {
    func_15130374(a0, a1, a2, 0xFF, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_151303EC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_15130A9C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_1513137C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_15131514.s")

void func_15131514(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
void func_1513137C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);

void func_1513164C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8) {
    func_15131514(a4, a5, a6, a7, a8);
    func_1513137C(a0, a1, a2, a3, a8);
}

void func_151318E8(f32 *a0, f32 a1);

s32 func_151316AC(s32 *a0, s32 a1) {
    func_151318E8((f32 *)((s32)a0 + 0x58), *(f32 *)&a0[0x2A]);
    return 1;
}

s32 func_15131918(f32 *a0, f32 a1);

s32 func_151316DC(s32 *a0, s32 a1) {
    func_15131918((f32 *)((s32)a0 + 0x58), *(f32 *)&a0[0x2A]);
    return 1;
}

s32 func_15131958(f32 *a0, f32 a1);

s32 func_1513170C(s32 *a0, s32 a1) {
    func_15131958((f32 *)((s32)a0 + 0x58), *(f32 *)&a0[0x2A]);
    return 1;
}

void func_1513173C(void) {
    extern void func_15169804();
    func_15169804();
}

void func_1513175C(void) {
    extern void func_15169824();
    func_15169824();
}

void func_1513177C(s32 *a0) {
    s32 idx;

    if (a0[0x1A] & 0x4000) {
        idx = *((u8 *)a0 + 0x75);
    } else {
        idx = 0;
    }
    D_80089814[idx](a0);
}

extern s32 (*D_80089844[])(s32 *);

s32 func_151317C8(s32 *a0) {
    s32 idx;

    if (a0[0x1A] & 0x4000) {
        idx = *((u8 *)a0 + 0x75);
    } else {
        idx = 0;
    }
    return D_80089844[idx](a0);
}

s32 func_15131814(s32 arg0, s32 arg1) {
    return 0;
}

void func_15131828(Obj15130280 *arg0, f32 *arg1, u8 *arg2, u8 *arg3) {
    arg0->field_0x4C = arg1[0] * func_151423D8((u8)(arg2[0] - 0x40));
    arg0->field_0x54 = arg1[1] * func_151423D8((u8)(arg2[1] - 0x40));
    arg2[0] = arg3[0] * D_800BE9E4 + arg2[0];
    arg2[1] = arg3[1] * D_800BE9E4 + arg2[1];
}

void func_151318E8(f32 *a0, f32 a1) {
    s32 i;

    for (i = D_800BE9E4; i > 0; i--) {
        a0[1] = a0[1] * a1;
    }
}

s32 func_15131918(f32 *a0, f32 a1) {
    s32 i;

    for (i = D_800BE9E4; i > 0; i--) {
        a0[0] = a0[0] * a1;
        a0[2] = a0[2] * a1;
    }
}

s32 func_15131958(f32 *a0, f32 a1) {
    s32 i;

    for (i = D_800BE9E4; i > 0; i--) {
        a0[0] = a0[0] * a1;
        a0[1] = a0[1] * a1;
        a0[2] = a0[2] * a1;
    }
}

s32 func_151319C4(void *arg0, s32 arg1, void *arg2);

s32 func_151319A4(u8 *arg0, s32 arg1) {
    return func_151319C4(arg0, arg1, arg0 + 0xA8);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_151319C4.s")

s32 func_15131AFC(Obj15130280 *arg0, s32 arg1) {
    func_15131958(arg0->field_0x58, arg0->field_0xA8);
    return func_151319C4(arg0, arg1, &arg0->field_0xB0);
}

s32 func_15131B3C(Obj15130280 *arg0, s32 arg1) {
    func_15131918(arg0->field_0x58, arg0->field_0xA8);
    return func_151319C4(arg0, arg1, &arg0->field_0xB0);
}

s32 func_15131B7C(Obj15131B7C *arg0, s32 arg1, f32 *arg2, Struct15131B7CArg3 *arg3) {
    arg0->unk44 = (arg0->unk3C * D_800A3848) + arg2[1];
    arg0->unk58 = arg0->unk58 * arg3->unk4;
    arg0->unk5C = arg0->unk5C * -arg3->unk4;
    arg0->unk60 = arg0->unk60 * arg3->unk4;
    if (fabsf(arg0->unk5C) < D_800A384C) {
        arg0->unk58 = 0.0f;
        arg0->unk5C = 0.0f;
        arg0->unk60 = 0.0f;
        arg0->unk64 = 0.0f;
        arg3->unk0 = arg3->unk0 & 0xFFFE;
        arg0->unk68 = arg0->unk68 & ~6;
    }
    return 1;
}

extern s32 (*D_80089878[])(s32 *, s32, u8);

s32 func_15131C2C(s32 *a0, s32 a1, u8 a2) {
    s32 (*fn)(s32 *, s32, u8);

    if (a0[0x1A] & 0x4000) {
        fn = D_80089878[*((u8 *)a0 + 0x75)];
        if (fn != 0) {
            fn(a0, a1, a2);
        }
    }
}

void func_15131C84(u8 *a0, s8 *a1, f32 a2, f32 *a3, f32 *a4, f32 *a5) {
    a0[0] = a1[0] * D_800BE9E4 + a0[0];
    a0[1] = a1[1] * D_800BE9E4 + a0[1];
    *a4 = a3[0] * func_151423D8((u8)(a0[0] - 0x40)) + a2;
    *a5 = a3[1] * func_151423D8((u8)(a0[1] - 0x40)) + a2;
}

void func_15131D4C(s32 arg0, u8 arg1) {
    Data15131D4C sp1C;

    sp1C = D_800A37F0;
    func_15169260(&sp1C, 3, arg0, arg1);
}

s32 func_15131D9C(Obj15130280AngleState *arg0, s32 arg1) {
    func_15131C84(arg0->field_0xA8, arg0->field_0xAA, arg0->field_0xAC, arg0->field_0xB0, &arg0->field_0x38, &arg0->field_0x3C);
    return 1;
}

s32 func_15131DEC(Obj15130280 *arg0, s32 arg1) {
    f32 temp_f2;
    f32 temp_f12;

    temp_f2 = arg0->field_0xA8;
    temp_f12 = arg0->field_0xB0 * sqrtf(temp_f2);
    arg0->field_0x3C = temp_f12;
    arg0->field_0x38 = temp_f12;

    arg0->field_0x2B = (u32)(arg0->field_0xB4 - ((arg0->field_0xB8 * temp_f2) * temp_f2));
    arg0->field_0xA8 = temp_f2 + D_800BE9A4;

    if (arg0->field_0xAC < arg0->field_0xA8) {
        return 0;
    }
    return 1;
}

s32 func_15131EE4(struct17 *arg0, f32 arg1, u8 arg2, s32 arg3) {
    Struct15131EE4Local sp40;
    Struct15131EE4Extra sp2C;
    s32 ret;
    s32 temp_v0;
    s32 temp_v1;

    sp2C.unk0 = 0.0f;
    sp2C.unk8 = D_800A3850 * arg1;
    sp2C.unk4 = func_150ADA68();
    sp2C.unk4 = (sp2C.unk4 + sp2C.unk4) + 5.0f;
    sp2C.unkC = (func_150ADA68() * 15.0f) + 240.0f;
    sp2C.unk10 = sp2C.unkC / (sp2C.unk4 * sp2C.unk4);

    sp40.unk1B = (u32)sp2C.unkC;
    sp40.unk1D = 0x69;
    sp40.unk8 = 0x4417;
    sp40.unk0 = 0x200004;
    sp40.unk4 = 1;
    sp40.unkC = 0;
    sp40.unk10 = 0;
    sp40.unk18 = 0xFF;
    sp40.unk19 = 0xFF;
    sp40.unk1A = 0xFF;
    sp40.unk17 = 0xFF;
    sp40.unk14 = 0xFF;
    sp40.unk15 = 0xFF;
    sp40.unk16 = 0xFF;
    sp40.unk1C = 0xFF;
    sp40.unk30 = *arg0;
    sp40.unk3C = *(struct17 *)&D_800A5480;
    sp40.unk1E = 1;
    sp40.unk20 = 0xFF;
    sp40.unk22 = 1;
    sp40.unk24 = 1.0f;

    if (func_150ADA20() & 1) {
        temp_v1 = 0x40;
    } else {
        temp_v1 = 0;
    }
    if (func_150ADA20() & 1) {
        temp_v0 = 0x80;
    } else {
        temp_v0 = 0;
    }
    sp40.unk58 = temp_v0 | 0x4C000 | temp_v1;
    sp40.unk60 = 6;
    sp40.unk61 = 6;
    sp40.unk62 = 0x27;
    sp40.unk63 = -1;
    sp40.unk64 = -1;
    sp40.unk65 = 0;
    sp40.unk5C = 0;
    sp40.unk66 = 0xFF;
    sp40.unk48 = *(struct17 *)&D_800A5480;
    sp40.unkA = 0x12C;
    sp40.unk28 = 0.0f;
    sp40.unk2C = 0.0f;
    sp40.unk54 = 0.0f;

    ret = (s32)func_15130280(&sp40, 1, 0, 0x14, arg2, arg3);
    if (ret != 0) {
        memcpy((u8 *)ret + 0xA8, &sp2C, sizeof(sp2C));
    }
    return ret;
}
