#include <ultra64.h>
#define func_1513D524 func_1513D524_void_proto
#include "functions.h"
#undef func_1513D524
#include "variables.h"

extern void func_1510F800(s32);
extern s32 func_1513D524(s32, u8, u8, u8, u8, u8, s32, u8, s32);
extern void func_1513F680();
extern void func_151429E0(u8, u8 *, u8 *, u8 *);
extern void func_1518CA80(void *, u8);
extern void func_151D5D60();

typedef s32 (*Func1514C2F0Callback)(s32, s16, f32, f32, f32, f32, f32, f32,
                                    s32, s32, f32, s32, f32, s32, u8);
extern Func1514C2F0Callback D_8008AA00[];

typedef struct {
    struct17 unk0;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    s16 unk20;
    s16 unk22;
    s16 unk24;
    u8 unk26;
    u8 unk27;
    u8 unk28;
    u8 unk29;
    u16 unk2A;
    u8 unk2C;
    u8 unk2D;
    u8 unk2E;
    u8 unk2F;
    s32 unk30;
    u8 unk34;
    u8 pad35[3];
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    f32 unk44;
} Struct15149550Arg;

typedef struct {
    u8 unk0;
    u8 pad1;
    s16 unk2;
    s16 unk4;
    u8 pad6[2];
    s32 unk8;
    s32 unkC;
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
    f32 unk14;
    f32 unk18;
    struct17 unk1C;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    s32 unk40;
    u8 unk44;
    u8 unk45;
    u8 pad46[2];
    s32 unk48;
    s32 pad4C;
    s32 pad50;
    s32 pad54;
} Struct15149550Local;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    s16 unkC;
    s16 unkE;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    s16 unk24;
    s16 unk26;
    f32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    s16 unk38;
    s16 unk3A;
    f32 unk3C;
    f32 unk40;
    f32 unk44;
    u8 unk48;
    u8 pad49[3];
    f32 unk4C;
} Struct15149550Extra;

s32 func_15149550(Struct15149550Arg *arg0, u8 arg1, u8 arg2, s32 arg3, u8 arg4, s32 arg5) {
    s32 ret;
    Struct15149550Local sp94;
    Struct15149550Extra sp44;
    s32 temp_v0;

    sp94.unk40 = arg0->unk2A | 0x40000000;
    sp94.unk1C = arg0->unk0;
    if (arg2 != 0) {
        sp94.unk40 |= 0x01000000;
        func_1510F800(0);
        sp94.unk48 = func_1510FD20((s32)sp94.unk1C.unk0, (s32)sp94.unk1C.unk8);
    } else {
        sp94.unk40 &= 0xFEFFFFFF;
        sp94.unk48 = 0;
    }

    switch ((u8)arg3) {
    case 1:
        sp94.unk0 = 0x13;
        break;
    case 2:
        sp94.unk0 = 0x71;
        break;
    case 0:
    default:
        if (func_150ADA20() & 1) {
            sp94.unk0 = 0x13;
        } else {
            sp94.unk0 = 0x14;
        }
        break;
    }

    sp94.unk2 = 0x301;
    sp94.unk4 = arg0->unk24;
    sp94.unk10 = arg0->unk26;
    sp94.unk11 = arg0->unk27;
    sp94.unk12 = arg0->unk28;
    sp94.unk13 = arg0->unk29;
    sp94.unk44 = arg0->unk2C;
    sp94.unk45 = arg0->unk2D;
    sp94.unk28 = 0.0f;
    sp94.unk2C = 0.0f;
    sp94.unk30 = 0.0f;
    sp94.unk34 = arg0->unk38;
    sp94.unk38 = 0.0f;
    sp94.unk3C = 1.0f;

    sp44.unk0 = arg0->unkC;
    sp44.unk4 = arg0->unk14;
    sp44.unkC = 0;
    sp44.unkE = 6;
    sp44.unk8 = (sp44.unk0 + sp44.unk4) * 0.5f;
    sp44.unk10 = 0.186f;
    sp44.unk14 = arg0->unk10;
    sp44.unk18 = arg0->unk18;
    sp44.unk1C = arg0->unk1C;
    sp44.unk20 = (sp44.unk14 + sp44.unk18) * 0.5f;
    sp44.unk24 = 0;
    sp44.unk26 = 0x11;
    sp44.unk28 = 0.359f;
    sp44.unk2C = arg0->unk20;
    sp44.unk30 = arg0->unk22;
    sp44.unk34 = 0;
    sp44.unk38 = 0;
    sp44.unk3A = 0xF;
    sp44.unk3C = 0.231f;
    sp44.unk40 = arg0->unk40;
    sp44.unk44 = arg0->unk44;
    sp94.unk8 = 0;
    sp94.unkC = (sp44.unk2C + sp44.unk30) >> 1;
    sp94.unk14 = 0.0f;
    sp94.unk18 = 0.0f;
    sp44.unk48 = arg0->unk34;
    sp44.unk4C = arg0->unk3C;

    if (func_150ADA20() & 1) {
        temp_v0 = 1;
    } else {
        temp_v0 = 0;
    }
    arg0 = (Struct15149550Arg *) func_1513D524((s32)&sp94, arg0->unk2E, 0xE, arg0->unk2F, (u8)arg1, (u8)(temp_v0 | 2), arg0->unk30 + 0x50, (u8)arg4, arg5);
    if (arg0 != 0) {
        memcpy((u8 *)arg0 + 0x110, &sp44, sizeof(sp44));
    }
    return (s32)arg0;
}

typedef struct {
    char pad_0x0[0x1C];
    s16 unk1C;
    char pad_0x1E[0x6];
    s32 unk24;
    char pad_0x28[0x4];
    f32 unk2C;
    f32 unk30;
    char pad_0x34[0x24];
    s32 unk58;
    char pad_0x5C[0x14];
    u8 unk70;
    char pad_0x71[0x1];
    u8 unk72;
    u8 unk73;
    char pad_0x74[0x9C];
    Struct15149550Extra unk110;
} Struct15149838Obj;

s32 func_15149838(Struct15149838Obj *arg0) {
    Struct15149550Extra *sub;
    s32 temp_v0;

    sub = (Struct15149550Extra *)((u8 *)arg0 + 0x110);
    sub->unkC -= D_800BE9E4;
    if (sub->unkC < 0) {
        sub->unkC = func_150ADA20() % (u32)sub->unkE;
        sub->unk8 = (func_150ADA68() * (sub->unk0 - sub->unk4)) + sub->unk4;
    }
    arg0->unk2C = arg0->unk2C + ((sub->unk8 - arg0->unk2C) * sub->unk10);
    sub->unk24 -= D_800BE9E4;
    if (sub->unk24 < 0) {
        sub->unk24 = func_150ADA20() % (u32)sub->unk26;
        if (func_150ADA20() & 3) {
            sub->unk20 = (func_150ADA68() * (sub->unk14 - sub->unk18)) + sub->unk18;
        } else {
            sub->unk20 = (func_150ADA68() * (sub->unk1C - sub->unk14)) + sub->unk14;
        }
    }
    arg0->unk30 = arg0->unk30 + ((sub->unk20 - arg0->unk30) * sub->unk28);
    sub->unk38 -= D_800BE9E4;
    if (sub->unk38 < 0) {
        sub->unk38 = func_150ADA20() % (u32)sub->unk3A;
        sub->unk34 = (func_150ADA20() % (u32)((sub->unk2C - sub->unk30) + 1)) + sub->unk30;
    }
    temp_v0 = arg0->unk24;
    arg0->unk24 += (s32)(((f32)sub->unk34 - (f32)temp_v0) * sub->unk3C);
    if (arg0->unk1C < 5) {
        func_1513F680(arg0, arg0->unk70, sub->unk48, arg0->unk72, arg0->unk73);
        arg0->unk1C = 0x12C;
        arg0->unk58 &= -2;
    }
    return 1;
}

typedef struct {
    char pad_0x0[0x8];
    f32 field_0x8;
    char pad_0xC[0x14];
    f32 field_0x20;
    char pad_0x24[0x20];
    f32 field_0x44;
} Struct15149550ObjExtra;

typedef struct {
    char pad_0x0[0x1C];
    s16 field_0x1C;
    char pad_0x1E[0xE];
    f32 field_0x2C;
    f32 field_0x30;
    char pad_0x34[0x24];
    s32 field_0x58;
    char pad_0x5C[0x14];
    u8 field_0x70;
    char pad_0x71[0x1];
    u8 field_0x72;
    u8 field_0x73;
    u8 field_0x74;
    char pad_0x75[0x9B];
    Struct15149550ObjExtra field_0x110;
    u8 field_0x158;
} Struct15149550Obj;

s32 func_15149A94(Struct15149550Obj *arg0) {
    Struct15149550ObjExtra *temp_v0;
    s32 var_v1;
    s32 flags;

    flags = arg0->field_0x74;
    var_v1 = 1;
    temp_v0 = &arg0->field_0x110;
    if (!(flags & 2)) {
        arg0->field_0x2C += (temp_v0->field_0x8 - arg0->field_0x2C) * temp_v0->field_0x44;
        if ((temp_v0->field_0x8 * 0.95f) < arg0->field_0x2C) {
            arg0->field_0x74 |= 2;
            flags = arg0->field_0x74;
        } else {
            var_v1 = 0;
            flags = arg0->field_0x74;
        }
    }
    if (!(flags & 8)) {
        arg0->field_0x30 += (temp_v0->field_0x20 - arg0->field_0x30) * temp_v0->field_0x44;
        if ((temp_v0->field_0x20 * 0.95f) < arg0->field_0x30) {
            arg0->field_0x74 |= 8;
        } else {
            var_v1 = 0;
        }
    }
    if (var_v1) {
        func_1513F680(arg0, arg0->field_0x70, 0xD, arg0->field_0x72, arg0->field_0x73);
    }
    if (arg0->field_0x1C < 5) {
        func_1513F680(arg0, arg0->field_0x70, arg0->field_0x158, arg0->field_0x72, arg0->field_0x73);
        arg0->field_0x1C = 0x64;
        arg0->field_0x58 &= -2;
    }
    return 1;
}

struct Foo15149BF4 {
    char pad0[0x2C];
    f32 unk2C;
    f32 unk30;
    char pad34[0x11C];
    f32 unk150;
};

s32 func_15149BF4(struct Foo15149BF4 *arg0) {
    s32 ret;

    arg0->unk2C = arg0->unk2C - (arg0->unk2C * arg0->unk150);
    arg0->unk30 = arg0->unk30 - (arg0->unk30 * arg0->unk150);
    if (arg0->unk2C < 2.0f) {
        goto ret0;
    }
    ret = 1;
    if (arg0->unk30 < 2.0f) {
        ret0:
        return 0;
    }
    return ret;
}

extern f32 D_800BE9A4;
s32 func_15149C58(f32 *arg0) {
    arg0[11] -= arg0[11] * arg0[84];
    arg0[12] -= arg0[12] * arg0[84];
    arg0[20] += arg0[19] * D_800BE9A4;
    arg0[14] += arg0[20] * D_800BE9A4;
    if (arg0[87] < arg0[14]) {
        return 0;
    }
    if ((arg0[11] < 4.0f) || (arg0[12] < 4.0f)) {
        return 0;
    }
    return 1;
}

struct Foo15149D18 {
    char pad0[0x2C];
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    char pad40[0x80];
    char unkC0[0x40];
    s16 *unk100[1];
};

s16 *func_15149D18(struct Foo15149D18 *arg0, s16 arg1) {
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

    temp_f2 = D_800DD1D8[arg1] * arg0->unk2C;
    temp_f12 = D_800DD1E8[arg1] * arg0->unk2C;

    var_v0[0] = var_v0[0x18] = arg0->unk34 + temp_f12;
    var_v0[1] = var_v0[9] = arg0->unk38;
    var_v0[2] = var_v0[0x1A] = arg0->unk3C - temp_f2;
    var_v0[8] = var_v0[0x10] = arg0->unk34 - temp_f12;
    var_v0[0x11] = var_v0[0x19] = arg0->unk38 + arg0->unk30;
    var_v0[0xA] = var_v0[0x12] = arg0->unk3C + temp_f2;

    return ret;
}

typedef struct {
    char pad0[0x34];
    struct17 unk34;
} Struct15149EC4Arg;

typedef struct {
    struct17 unk0;
    char padC[0xA];
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    s16 unk24;
    s16 unk26;
    u8 unk28;
    u8 unk29;
    u8 unk2A;
    u8 unk2B;
    u8 unk2C;
    u8 unk2D;
    u8 unk2E;
    u8 unk2F;
    u8 unk30;
    u8 unk31;
} Struct15149EC4Stack;

s32 func_15149EC4(Struct15149EC4Arg *arg0) {
    Struct15149EC4Stack sp1C;

    sp1C.unk0 = arg0->unk34;
    sp1C.unk16 = 0;
    sp1C.unk18 = 0;
    sp1C.unk1A = sp1C.unk1C = (func_150ADA20() % 6U) + 8;
    sp1C.unk1E = 0;
    sp1C.unk20 = 0;
    sp1C.unk22 = (func_150ADA20() % 201U) + 0x64;
    sp1C.unk24 = (func_150ADA20() % 5U) + 3;
    sp1C.unk26 = 0x258;
    func_151429E0(3, &sp1C.unk28, &sp1C.unk29, &sp1C.unk2A);
    func_151429E0(4, &sp1C.unk2B, &sp1C.unk2C, &sp1C.unk2D);
    sp1C.unk2E = 0xFF;
    sp1C.unk2F = (func_150ADA20() % 65U) + 0x5C;
    sp1C.unk30 = (func_150ADA20() % 3U) + 1;
    sp1C.unk31 = 0;
    func_1518CA80(&sp1C, 1);
    return 0;
}

s16 *func_15149FD0(struct Foo15149D18 *arg0, s16 arg1) {
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

    temp_f2 = D_800DD1D8[arg1] * arg0->unk2C;
    temp_f12 = D_800DD1E8[arg1] * arg0->unk2C;

    var_v0[3] = 0;
    var_v0[0xB] = 0;
    var_v0[0x13] = 0;
    var_v0[0x1B] = 0;
    var_v0[0] = var_v0[0x18] = arg0->unk34 + temp_f12;
    var_v0[1] = var_v0[9] = arg0->unk38;
    var_v0[2] = var_v0[0x1A] = arg0->unk3C - temp_f2;
    var_v0[8] = var_v0[0x10] = arg0->unk34 - temp_f12;
    var_v0[0x11] = var_v0[0x19] = arg0->unk38 + arg0->unk30;
    var_v0[0xA] = var_v0[0x12] = arg0->unk3C + temp_f2;

    return ret;
}

struct Foo1514A19CObj {
    char pad0[0x24];
    s32 unk24;
    char pad28[0x4];
    f32 unk2C;
    f32 unk30;
};

struct Foo1514A19CSub {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    s16 unk1C;
    s16 unk1E;
    char pad20[0x18];
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    s16 unk44;
};

s32 func_1514A19C(struct Foo1514A19CObj *arg0) {
    struct Foo1514A19CSub *sub;
    s32 temp_v1;

    sub = (struct Foo1514A19CSub *)((u8 *)arg0 + 0x110);
    sub->unk1E -= D_800BE9E4;
    if (sub->unk1E < 0) {
        sub->unk1E = (u32) func_150ADA20() % 6;
        if (func_150ADA20() & 3) {
            sub->unk18 = (func_150ADA68() * (sub->unkC - sub->unk10)) + sub->unk10;
        } else {
            sub->unk18 = (func_150ADA68() * (sub->unk14 - sub->unkC)) + sub->unkC;
        }
    }
    arg0->unk30 = arg0->unk30 + ((sub->unk18 - arg0->unk30) * 0.359f);
    sub->unk1C -= D_800BE9E4;
    if (sub->unk1C < 0) {
        sub->unk1C = (u32) func_150ADA20() % 0x11;
        sub->unk8 = (func_150ADA68() * (sub->unk0 - sub->unk4)) + sub->unk4;
    }
    arg0->unk2C = arg0->unk2C + ((sub->unk8 - arg0->unk2C) * 0.186f);
    sub->unk44 -= D_800BE9E4;
    if (sub->unk44 < 0) {
        sub->unk44 = (u32) func_150ADA20() % 0xF;
        sub->unk40 = (func_150ADA68() * (sub->unk38 - sub->unk3C)) + sub->unk3C;
    }
    temp_v1 = arg0->unk24;
    arg0->unk24 += (s32)((sub->unk40 - (f32) temp_v1) * 0.231f);
    return 1;
}

typedef struct {
    char pad_0x0[0x8];
    f32 field_0x8;
    char pad_0xC[0xC];
    f32 field_0x18;
} Struct1514A380ObjExtra;

typedef struct {
    char pad_0x0[0x2C];
    f32 field_0x2C;
    f32 field_0x30;
    char pad_0x34[0x3C];
    u8 field_0x70;
    char pad_0x71[0x1];
    u8 field_0x72;
    u8 field_0x73;
    u8 field_0x74;
    char pad_0x75[0x9B];
    Struct1514A380ObjExtra field_0x110;
} Struct1514A380Obj;

s32 func_1514A380(Struct1514A380Obj *arg0) {
    Struct1514A380ObjExtra *temp_v0;
    s32 var_v1;
    s32 flags;

    flags = arg0->field_0x74;
    var_v1 = 1;
    temp_v0 = &arg0->field_0x110;
    if (!(flags & 2)) {
        arg0->field_0x2C += (temp_v0->field_0x8 - arg0->field_0x2C) * 0.7f;
        if ((temp_v0->field_0x8 * 0.95f) < arg0->field_0x2C) {
            arg0->field_0x74 |= 2;
            flags = arg0->field_0x74;
        } else {
            var_v1 = 0;
            flags = arg0->field_0x74;
        }
    }
    if (!(flags & 8)) {
        arg0->field_0x30 += (temp_v0->field_0x18 - arg0->field_0x30) * 0.7f;
        if ((temp_v0->field_0x18 * 0.95f) < arg0->field_0x30) {
            arg0->field_0x74 |= 8;
        } else {
            var_v1 = 0;
        }
    }
    if (var_v1) {
        func_1513F680(arg0, arg0->field_0x70, 4, arg0->field_0x72, arg0->field_0x73);
    }
    return 1;
}

struct Foo1514A498 {
    char pad1C[0x1C];
    s16 unk1C;
    char pad1E[0xE];
    f32 unk2C;
    f32 unk30;
    char pad34[0x28];
    u8 unk5C;
    char pad5D[0xE7];
    f32 unk144;
    char pad148[0xE];
    s16 unk156;
    s16 unk158;
};

s32 func_1514A498(struct Foo1514A498 *arg0) {
    arg0->unk30 = arg0->unk30 - arg0->unk30 * arg0->unk144;
    arg0->unk2C = arg0->unk2C - arg0->unk2C * arg0->unk144;
    if (arg0->unk1C < arg0->unk156) {
        arg0->unk5C = arg0->unk1C * arg0->unk158;
    }
    return 1;
}

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} Struct1514A4ECVec;

struct Foo1514A4EC {
    char pad0[0x34];
    Struct1514A4ECVec unk34;
    Struct1514A4ECVec unk40;
    char pad4C[0xE4];
    f32 unk130;
    f32 unk134;
    f32 unk138;
    f32 unk13C;
    f32 unk140;
};

s32 func_1514A4EC(struct Foo1514A4EC *arg0) {
    f32 temp_f0;
    s32 dummy;

    temp_f0 = arg0->unk140;
    arg0->unk40 = arg0->unk34;
    arg0->unk130 = arg0->unk130 * temp_f0;
    arg0->unk134 = arg0->unk134 + (arg0->unk13C * D_800BE9A4);
    dummy = arg0 ? 1 : 0;
    arg0->unk138 = arg0->unk138 * temp_f0;
    arg0->unk34.unk0 = arg0->unk34.unk0 + (arg0->unk130 * D_800BE9A4);
    arg0->unk34.unk4 = arg0->unk34.unk4 + (arg0->unk134 * D_800BE9A4);
    arg0->unk34.unk8 = arg0->unk34.unk8 + (arg0->unk138 * D_800BE9A4);
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_176A00/func_1514A594.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_176A00/func_1514A6A0.s")

void func_1514AB5C(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, f32 arg5, f32 arg6,
                   f32 arg7, f32 arg8, s16 arg9, s16 argA, u8 argB) {
    Struct15149550Arg sp88;
    u8 angle;
    f32 s;
    f32 c;
    f32 r;
    f32 h;
    f32 w;

    if (arg4 > 0) {
        sp88.unk20 = 0x6231, sp88.unk22 = 0x1A4D;
        sp88.unk26 = 0;
        sp88.unk27 = 0;
        sp88.unk28 = 0;
        sp88.unk29 = 0xFF;
        sp88.unk2A = 1;
        sp88.unk2C = 0xFF;
        sp88.unk2D = 0xFF;
        sp88.unk30 = 0;
        sp88.unk2E = 0;
        sp88.unk2F = argB;
        sp88.unk34 = 0xF;
        sp88.unk0.unk4 = arg1;
        sp88.unk38 = 0.0f;
        sp88.unk40 = 0.045f;
        sp88.unk44 = 0.7f;
        do {
            angle = func_150ADA20() & 0xFF;
            s = func_151423D8(angle - 0x40);
            c = func_151423D8(angle);
            r = func_150ADA68() * arg3;
            h = func_150ADA68() * arg6 + arg5;
            w = func_150ADA68() * arg8 + arg7;
            sp88.unk0.unk0 = r * s + arg0;
            sp88.unk0.unk8 = r * c + arg2;
            sp88.unkC = 22.6f * h;
            sp88.unk14 = 13.786f * h;
            sp88.unk10 = 57.969f * w;
            sp88.unk18 = 42.714f * w;
            sp88.unk1C = 118.763f * w;
            sp88.unk24 = func_150ADA20() % (u32)(argA + 1) + arg9;
            func_15149550(&sp88, 0xA, 0, 0, 0xFF, 1);
        } while (--arg4 != 0);
    }
}

u8 func_150ADA20(void);
f32 func_150ADA68(void);
s32 func_15149550(Struct15149550Arg *arg0, u8 arg1, u8 arg2, s32 arg3, u8 arg4, s32 arg5);
void func_1514AD9C(struct17 *arg0, u8 arg1, s32 arg2)
{
  Struct15149550Arg sp30;
  f32 t;
  f32 s;
 sp30.unk20 = 0x6231; sp30.unk22 = 0x1A4D; sp30.unk0 = *arg0;
  sp30.unk26 = 0;
  sp30.unk27 = 0;
  sp30.unk28 = 0;
  sp30.unk29 = 0xFF;
  sp30.unk2D = 0xFF;
  sp30.unk2E = 0;
  sp30.unk2F = 1;
  sp30.unk30 = 0;
  sp30.unk2A = 1;
  sp30.unk34 = 0x1C;
  sp30.unk3C = 0.0f;
  sp30.unk40 = 0.080000006f;
  sp30.unk44 = 0.4f;
  t = ((func_150ADA68() * 501.0f) + 999.0f) * 0.001f;
  s = func_150ADA68();
  sp30.unkC = 22.6f * t;
  sp30.unk14 = 13.786f * t;
  s = ((s * 1007.0f) + 1505.0f) * 0.001f;
  sp30.unk10 = 57.969f * s;
  sp30.unk18 = 42.714f * s;
  sp30.unk1C = 118.763f * s;
  sp30.unk24 = (((u32) func_150ADA20()) % 0x11U) + 0x10;
  sp30.unk38 = ((func_150ADA68() * 347.0f) + 50.0f) * 0.001f;
  sp30.unk2C = (((u32) func_150ADA20()) % 0x9CU) + 0x64;
  func_15149550(&sp30, 0xA, 0, 0, (u8) arg1, arg2);
}


extern f32 D_800BE9A4;
s32 func_1514AF74(f32 *arg0) {
    arg0[11] -= arg0[11] * arg0[84];
    arg0[12] -= arg0[12] * arg0[84];
    arg0[14] += (arg0[20] * D_800BE9A4) + (((0.5f * arg0[19]) * D_800BE9A4) * D_800BE9A4);
    arg0[20] += arg0[19] * D_800BE9A4;
    if ((arg0[11] < 10.0f) || (arg0[12] < 10.0f)) {
        return 0;
    }
    return 1;
}

extern void func_15143874(s16, f32, f32 *, f32 *);

void func_1514B034(struct17 *arg0, u8 arg1, s32 arg2) {
    f32 count;
    Struct15149550Arg sp84;
    s32 angle;
    f32 h;
    f32 w;

    count = ((func_150ADA68() * 20.0f) + 29.0f) * 0.0001f * 5541.7695f;
    if (count > 1.0f) {
        sp84.unk20 = 0x6231;
        sp84.unk22 = 0x1A4D;
        sp84.unk0.unk4 = arg0->unk4;
        sp84.unk26 = 0;
        sp84.unk27 = 0;
        sp84.unk28 = 0;
        sp84.unk29 = 0xFF;
        sp84.unk2D = 0xFF;
        sp84.unk2E = 0;
        sp84.unk2F = 1;
        sp84.unk30 = 0;
        sp84.unk2A = 1;
        sp84.unk34 = 0x1C;
        sp84.unk3C = 0.0f;
        do {
            angle = func_150ADA20();
            func_15143874(angle & 0xFF, func_150ADA68() * 42.0f, &sp84.unk0.unk0, &sp84.unk0.unk8);
            sp84.unk0.unk0 += arg0->unk0;
            sp84.unk0.unk8 += arg0->unk8;
            sp84.unk40 = ((func_150ADA68() * 16.0f) + 29.0f) * 0.001f;
            sp84.unk44 = ((func_150ADA68() * 600.0f) + 400.0f) * 0.001f;
            h = ((func_150ADA68() * 1205.0f) + 304.0f) * 0.001f;
            w = ((func_150ADA68() * 1006.0f) + 504.0f) * 0.001f;
            sp84.unkC = 22.6f * h;
            sp84.unk14 = 13.786f * h;
            sp84.unk10 = 57.969f * w;
            sp84.unk18 = 42.714f * w;
            sp84.unk1C = 118.763f * w;
            sp84.unk24 = func_150ADA20() % 31U + 20;
            sp84.unk38 = func_150ADA68() * 497.0f * 0.001f;
            sp84.unk2C = func_150ADA20() % 156U + 100;
            func_15149550(&sp84, 0xA, 0, 0, arg1, arg2);
            count -= 1.0f;
        } while (count > 1.0f);
    }
}

typedef struct {
    u8 unk0;
    u8 unk1;
    s16 unk2;
    s16 unk4;
    u8 pad6[2];
    s32 unk8;
    s32 unkC;
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
    f32 unk14;
    f32 unk18;
    struct17 unk1C;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    s32 unk40;
    u8 unk44;
    u8 unk45;
    u8 unk46;
    u8 unk47;
    s32 unk48;
    s32 pad4C;
    s32 pad50;
    s16 unk54;
    s16 unk56;
} Struct1514B8E4Desc;

typedef struct {
    s32 unk0;
    s32 unk4;
    struct17 unk8;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    s16 unk2C;
    s16 unk2E;
    s16 unk30;
    s16 unk32;
    s32 unk34;
    s32 unk38;
    s16 unk3C;
    s16 unk3E;
    u16 unk40;
    u8 unk42;
    u8 unk43;
    u8 unk44;
    u8 unk45;
    u8 unk46;
    u8 unk47;
    u8 unk48;
    u8 unk49;
    u8 unk4A;
    u8 unk4B;
    u8 unk4C;
    u8 unk4D;
    u8 unk4E;
    u8 unk4F;
    u8 unk50;
    u8 unk51;
    u8 unk52;
    u8 unk53;
    u8 unk54;
    u8 unk55;
    u8 unk56;
    u8 unk57;
    u8 unk58;
    u8 pad59[3];
    s32 unk5C;
    s32 unk60;
    s16 unk64;
    s16 unk66;
    s16 unk68;
    u8 unk6A;
    u8 pad6B[1];
    f32 unk6C;
    s8 unk70;
    s8 unk71;
    s8 unk72;
    s8 unk73;
} Struct1514B364Spawn;

typedef struct {
    struct17 unk0;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    s16 unk24;
    s16 unk26;
    s16 unk28;
    s16 unk2A;
    s16 unk2C;
    s16 unk2E;
    s16 unk30;
    s16 unk32;
    s16 unk34;
    s16 unk36;
    u8 unk38;
    u8 unk39;
    u8 pad3A[2];
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    s32 unk48;
    s32 unk4C;
    s32 unk50;
    u8 unk54;
    u8 unk55;
    u8 pad56[2];
} Struct1514B364Emit;

typedef struct {
    f32 unk00;
    f32 unk04;
    f32 unk08;
    f32 unk0C;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    u8 unk1C;
    u8 pad1D[0x7];
} Struct1514B364Hit;

extern s32 func_15046C80(struct17 *, s32, f32, Struct1514B364Hit *);
extern void func_15152B38(Struct1514B364Spawn *, u8, s32);
extern void func_15152F70(Struct1514B364Emit *, u8);

void func_1514B364(struct17 *arg0, Struct1514B364Hit *arg1, u8 arg2, s32 arg3) {
    struct17 pos;

    pos = *arg0;
    {
        struct17 probe;

        probe.unk0 = arg0->unk0;
        probe.unk4 = arg0->unk4 + 200.0f;
        probe.unk8 = arg0->unk8;
        if (func_15046C80(&probe, 0, arg0->unk4 - 200.0f, arg1) == 0) {
            return;
        }
    }
    {
        Struct1514B364Spawn spawn;

        spawn.unk0 = 0xA;
        spawn.unk4 = 0;
        spawn.unk14 = 9.900001f;
        spawn.unk18 = 21.0f;
        spawn.unk1C = -3.0000002f;
        spawn.unk20 = 1.016f;
        spawn.unk24 = 30.0f;
        spawn.unk28 = 30.4f;
        spawn.unk2C = 0;
        spawn.unk2E = 0xFF;
        spawn.unk30 = -0x3F;
        spawn.unk32 = 0x2B;
        spawn.unk34 = 4;
        spawn.unk38 = 5;
        spawn.unk3C = 0x1E;
        spawn.unk3E = 0x1E;
        spawn.unk40 = 1;
        spawn.unk42 = 0xC;
        spawn.unk43 = 2;
        spawn.unk44 = 3;
        spawn.unk45 = 0xB4;
        spawn.unk46 = 0;
        spawn.unk47 = 0;
        spawn.unk48 = 0x9B;
        spawn.unk49 = 0x32;
        spawn.unk4A = 0x64;
        spawn.unk4B = 0;
        spawn.unk4C = 0x64;
        spawn.unk4D = 0xFF;
        spawn.unk4E = 0xFF;
        spawn.unk4F = 0xFF;
        spawn.unk50 = 0xFF;
        spawn.unk51 = 0;
        spawn.unk52 = 0;
        spawn.unk53 = 0;
        spawn.unk54 = 0;
        spawn.unk55 = 0xFF;
        spawn.unk56 = 0;
        spawn.unk57 = 1;
        spawn.unk58 = 0x24;
        spawn.unk5C = 0x200005;
        spawn.unk60 = 0x60600;
        spawn.unk64 = 0x14;
        spawn.unk66 = 0xC;
        spawn.unk68 = 1;
        spawn.unk6A = 0;
        spawn.unk6C = 1.f;
        spawn.unk70 = -1;
        spawn.unk71 = 0;
        spawn.unk72 = -1;
        spawn.unk73 = -1;
        spawn.unk8 = pos;
        func_15152B38(&spawn, arg2, arg3);
    }
    {
        Struct1514B364Emit emit;

        emit.unk0 = pos;
        emit.unkC = 3.99f;
        emit.unk10 = 8.11f;
        emit.unk14 = 0.60200006f;
        emit.unk18 = 0.407f;
        emit.unk1C = 10.139999f;
        emit.unk20 = 10.2699995f;
        emit.unk24 = 8;
        emit.unk26 = 8;
        emit.unk28 = 0;
        emit.unk2A = 0xFF;
        emit.unk2C = -0x40;
        emit.unk2E = 0x2C;
        emit.unk30 = 5;
        emit.unk32 = 4;
        emit.unk34 = 0x42;
        emit.unk36 = 0x1E;
        emit.unk38 = 0xA;
        emit.unk39 = 0x21;
        emit.unk3C = 1;
        emit.unk40 = 0xC;
        emit.unk44 = 0;
        emit.unk48 = 0;
        emit.unk4C = 0;
        emit.unk50 = 0;
        emit.unk54 = 0xFF;
        emit.unk55 = func_150ADA20() % 101U + 0x9B;
        func_15152F70(&emit, 0xFF);
    }
    func_1514B034(&pos, arg2, arg3);

    {
        Struct1514B8E4Desc desc;
        s32 a;
        s32 c;
        s32 b;
        s32 sum;

        desc.unk0 = 0x38;
        desc.unk2 = 1;
        desc.unk4 = 0x32;
        desc.unk8 = 0;
        desc.unkC = 0x6666;
        desc.unk13 = 0xFF;
        desc.unk14 = 1.0f;
        desc.unk18 = 1.0f;
        desc.unk1C.unk0 = pos.unk0;
        desc.unk1C.unk4 = pos.unk4 + 10.0f;
        desc.unk1C.unk8 = pos.unk8;
        desc.unk28 = 0.0f;
        desc.unk2C = 0.0f;
        desc.unk30 = 0.0f;
        desc.unk34 = 0.2f;
        desc.unk38 = 1.0f;
        desc.unk3C = 1.0f;
        desc.unk40 = 0x400C0001;
        desc.unk44 = func_150ADA20() % 101U + 100;
        desc.unk45 = 0xFF;
        desc.unk46 = 0;
        desc.unk47 = 6;
        desc.unk10 = func_150ADA20() % 51U + 0xB4;
        desc.unk11 = func_150ADA20() % 101U;
        desc.unk12 = func_150ADA20() % 1U;
        a = func_150ADA20();
        b = func_150ADA20();
        c = func_150ADA20();
        sum = (b & 1) + (a & 1);
        func_1513D668((s32)&desc, 0, 0x12, 0x1D, 0, sum, (u8)c,
                      100.0f, 100.0f, 0, (s32)&arg1->unk04, 0, 0, arg2, arg3);
    }
}

struct Foo1514B844 {
    char pad1C[0x1C];
    s16 unk1C;
    char pad1E[0x7A];
    u8 *unk98;
};

s32 func_1514B844(struct Foo1514B844 *arg0) {
    u8 *p = arg0->unk98;
    s16 v = arg0->unk1C;
    if (v < 0x10) {
        s32 sh = v << 4;
        if (sh < p[0x1B]) {
            p[0x1B] = sh;
        }
    }
    return 1;
}

extern f32 D_800BE9A4;

struct Foo1514B87C {
    char pad2C[0x2C];
    f32 unk2C;
    f32 unk30;
    char pad34[0x18];
    f32 unk4C;
};

s32 func_1514B87C(struct Foo1514B87C *arg0) {
    f32 temp = arg0->unk4C * D_800BE9A4;
    arg0->unk2C = arg0->unk2C + temp;
    arg0->unk30 = arg0->unk30 + temp;
    return 1;
}

struct Foo1514B8B0 {
    char pad1C[0x1C];
    s16 unk1C;
    char pad1E[0x3E];
    u8 unk5C;
};

s32 func_1514B8B0(struct Foo1514B8B0 *arg0) {
    s32 v = arg0->unk1C;
    if (v < 0x10) {
        s32 sh = v << 4;
        if (sh < arg0->unk5C) {
            arg0->unk5C = sh;
        }
    }
    return 1;
}

typedef struct {
    f32 unk0;
    f32 unk4;
} Struct1514B8E4Size;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    struct17 unk38;
    f32 unk44;
    f32 unk48;
    f32 unk4C;
} Struct1514B8E4Extra;


void *func_1514B8E4(struct17 *arg0, Struct1514B8E4Size *arg1, s16 arg2, u8 arg3, struct17 *arg4,
                    f32 arg5, f32 arg6, f32 arg7, u8 arg8, u8 arg9, u8 argA, s32 argB, u8 argC,
                    s16 argD, s16 argE, s32 argF, u8 arg10, s32 arg11) {
    void *ret;
    Struct1514B8E4Desc desc;
    Struct1514B8E4Extra extra;
    s32 flag;

    if (arg4 != NULL) {
        extra.unk38 = *arg4;
    } else {
        extra.unk38.unk0 = 0.0f;
        extra.unk38.unk4 = 0.0f;
        extra.unk38.unk8 = 0.0f;
    }
    extra.unk44 = arg5;
    extra.unk1C = 0.0f;
    extra.unk20 = 0.0f;
    extra.unk30 = 0.0f;
    desc.unkC = 0x3E3F;
    extra.unk34 = 15935.0f;
    extra.unk2C = 15935.0f;
    extra.unk48 = arg6;
    extra.unk4C = arg7;
    extra.unk24 = 6733.0f;
    extra.unk28 = 18404.0f;
    extra.unk0 = arg1->unk0 * 15.045272f;
    extra.unk8 = arg1->unk0 * 5.8676558f;
    extra.unk10 = arg1->unk0 * 12.111444f;
    desc.unk14 = 0.0f;
    extra.unk4 = arg1->unk4 * 0.396174f;
    extra.unkC = arg1->unk4 * 0.1042563f;
    extra.unk18 = arg1->unk4 * 0.5197371f;
    extra.unk14 = arg1->unk4 * 0.34404588f;
    desc.unk18 = 0.0f;
    desc.unk0 = argB;
    desc.unk1 = 0;
    desc.unk2 = 0x2203;
    if (arg2 == -1) {
        desc.unk4 = 300;
    } else {
        desc.unk4 = arg2;
    }
    desc.unk8 = 0;
    desc.unk10 = 0xFF;
    desc.unk11 = 0xFF;
    desc.unk12 = 0xFF;
    desc.unk13 = 0xFF;
    desc.unk1C = *arg0;
    desc.unk28 = arg0->unk0;
    desc.unk2C = arg0->unk4 + 100.0f;
    desc.unk30 = arg0->unk8;
    desc.unk34 = 1.0f;
    desc.unk38 = 1.0f;
    desc.unk3C = 1.0f;
    desc.unk40 = ((arg2 == -1) ? 0 : 1) | 0x40000 | 0x80000 | 0x200000 | 0x400000 | ((argC & 1) ? 0x800000 : 0) | ((argC & 2) ? 0x2000000 : 0) | 0x40000000;
    desc.unk44 = arg3;
    desc.unk45 = 0xFF;
    desc.unk46 = 0;
    desc.unk47 = 7;
    desc.unk48 = 0;
    desc.unk54 = argD;
    desc.unk56 = argE;
    if (func_150ADA20() & 1) {
        flag = 1;
    } else {
        flag = 0;
    }
    ret = func_1513D2F0(&desc, (s32)&D_800A4AA0, arg8, arg9, argA, 0x1C, flag | 2, 0, 0, argF + 0x50, arg10, arg11);
    if (ret != NULL) {
        memcpy((u8 *)ret + 0x110, &extra, sizeof(extra));
    }
    return ret;
}

struct Foo1514BC08Obj {
    char pad0[0x24];
    s32 unk24;
    char pad28[0x4];
    f32 unk2C;
    f32 unk30;
};

struct Foo1514BC08Sub {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
};

s32 func_1514BC08(void *arg0, void *arg1) {
    struct Foo1514BC08Obj *obj;
    struct Foo1514BC08Sub *sub;

    obj = arg0;
    sub = arg1;
    sub->unk1C -= D_800BE9A4;
    if (sub->unk1C < 0.0f) {
        sub->unk1C = func_150ADA68() * 4.0f;
        sub->unk10 = func_150ADA68() * sub->unk8 + sub->unk0;
    }
    obj->unk2C = obj->unk2C + ((sub->unk10 - obj->unk2C) * 0.35f);
    sub->unk20 -= D_800BE9A4;
    if (sub->unk20 < 0.0f) {
        sub->unk20 = func_150ADA68() * 9.0f;
        if (func_150ADA20() & 1) {
            sub->unk14 = func_150ADA68() * sub->unkC + sub->unk4;
        } else {
            sub->unk14 = func_150ADA68() * sub->unk18 + sub->unk4;
        }
    }
    obj->unk30 = obj->unk30 + ((sub->unk14 - obj->unk30) * 0.4f);
    sub->unk30 -= D_800BE9A4;
    if (sub->unk30 < 0.0f) {
        sub->unk30 = func_150ADA68() * 7.0f;
        sub->unk2C = func_150ADA68() * sub->unk28 + sub->unk24;
    }
    sub->unk34 = sub->unk34 + ((sub->unk2C - sub->unk34) * 0.4f);
    obj->unk24 = sub->unk34;
    return 1;
}

void func_1514BE00(u8 *arg0) {
    func_1514BC08(arg0, arg0 + 0x110);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_176A00/func_1514BE20.s")

void func_1514BF50(f32 *arg0) {
    arg0[0x10] = arg0[0xD];
    arg0[0x11] = arg0[0xE] + 100.0f;
    arg0[0x12] = arg0[0xF];
}

void func_1514BF7C(u8 *arg0) {
    func_1514BC08(arg0, arg0 + 0x110);
}

typedef struct {
    char pad0[0x38];
    struct17 unk38;
    f32 unk44;
    f32 unk48;
} Struct1514BF9CSub;

typedef struct {
    char pad0[0x34];
    struct17 unk34;
    char pad40[0xD0];
    Struct1514BF9CSub unk110;
} Struct1514BF9CObj;

void func_1514BF9C(Struct1514BF9CObj *arg0) {
    Struct1514BF9CSub *sub;
    struct17 old;
    s32 i;

    sub = (Struct1514BF9CSub *)((u8 *)arg0 + 0x110);
    old = sub->unk38;
    for (i = D_800BE9E4; i != 0; i--) {
        sub->unk38.unk0 *= sub->unk48;
        sub->unk38.unk4 *= sub->unk48;
        sub->unk38.unk8 *= sub->unk48;
    }
    {
        f32 ax;
        f32 ay;
        f32 az;

        sub->unk38.unk4 += sub->unk44 * D_800BE9A4;
        ax = (sub->unk38.unk0 - old.unk0) * D_800BE9A8;
        ay = (sub->unk38.unk4 - old.unk4) * D_800BE9A8;
        az = (sub->unk38.unk8 - old.unk8) * D_800BE9A8;
        arg0->unk34.unk0 += (old.unk0 + 0.5f * ax * D_800BE9A4) * D_800BE9A4;
        arg0->unk34.unk4 += (old.unk4 + 0.5f * ay * D_800BE9A4) * D_800BE9A4;
        arg0->unk34.unk8 += (old.unk8 + 0.5f * az * D_800BE9A4) * D_800BE9A4;
    }
}

extern void func_1514BE20(void *);

s32 func_1514C258(void *arg0) {
    func_1514BF9C(arg0);
    func_1514BE20(arg0);
    return 1;
}

s32 func_1514C288(void *arg0) {
    func_1514BF9C(arg0);
    func_1514BF50(arg0);
    return 1;
}

struct Foo1514C2B8 {
    char pad1C[0x1C];
    s16 unk1C;
    char pad1E[0x3A];
    s32 unk58;
    char pad5C[0x15];
    u8 unk71;
    u8 unk72;
    char pad73[0xE1];
    f32 unk154;
    char pad158[0x8];
    f32 unk160;
    s16 unk164;
};

s32 func_1514C2B8(struct Foo1514C2B8 *arg0) {
    arg0->unk72 = 0;
    arg0->unk71 = 0x24;
    arg0->unk1C = arg0->unk164;
    arg0->unk58 |= 0x08000000;
    arg0->unk154 = arg0->unk160;
    return 1;
}

void func_1514C2F0(f32 arg0, f32 arg1, f32 arg2, f32 arg3,
                   u8 arg4, s8 arg5, s16 arg6, u8 arg7,
                   s32 arg8, f32 arg9, s32 arg10, u8 arg11) {
    Func1514C2F0Callback *callbacks;
    Func1514C2F0Callback callback;
    f32 temp_f20;
    f32 temp_f0;
    f32 temp_f2;
    f32 temp_arg1;
    f32 temp_arg0;
    f32 temp_arg2;
    u8 var_s0;
    s16 i;

    temp_arg1 = arg1;
    temp_arg0 = arg0;
    temp_arg2 = arg2;
    var_s0 = arg4;
    i = 0;
    if (arg6 > 0) {
        callbacks = &D_8008AA00[arg7];
        do {
            temp_f20 = func_151423D8((u8)(var_s0 - 0x40));
            temp_f0 = func_151423D8(var_s0);
            temp_f2 = arg3 * temp_f0 + temp_arg2;
            callback = *callbacks;
            if (callback != 0) {
                if (callback(1, i, arg3 * temp_f20 + temp_arg0, temp_arg1, temp_f2,
                             temp_arg0, temp_arg1, temp_arg2, var_s0, arg4, arg3, arg8,
                             arg9, arg10, arg11) == 0) {
                    return;
                }
            }
            i++;
            var_s0 += arg5;
        } while (i < arg6);
    }
}

void func_1514C470(f32 arg0, f32 arg1, f32 arg2, f32 arg3,
                   f32 arg4, f32 arg5, f32 arg6, u8 arg7,
                   s32 arg8, f32 arg9, s32 arg10, u8 arg11) {
    Func1514C2F0Callback *callbacks;
    Func1514C2F0Callback callback;
    f32 pad[1];
    f32 step_z;
    f32 step_y;
    f32 step_x;
    f32 inv;
    f32 cur_x;
    f32 cur_y;
    f32 cur_z;
    f32 temp_arg0;
    f32 temp_arg1;
    s16 i;

    callbacks = &D_8008AA00[arg7];
    i = 0;
    if (arg6 < 2.0f) {
        return;
    }

    if ((s32) arg6 & 1) {
        inv = 1.0f / (arg6 - 1.0f);
        step_x = (arg3 - arg0) * inv;
        step_y = (arg4 - arg1) * inv;
        step_z = (arg5 - arg2) * inv;
    } else {
        inv = 1.0f / (arg6 - 1.0f);
        step_x = (arg3 - arg0) * inv;
        step_y = (arg4 - arg1) * inv;
        step_z = (arg5 - arg2) * inv;
    }

    cur_x = arg0;
    temp_arg0 = arg0;
    temp_arg1 = arg1;
    cur_y = arg1;
    cur_z = arg2;
    do {
        callback = *callbacks;
        if (callback != 0) {
            if (callback(0, i, cur_x, cur_y, cur_z, temp_arg0, temp_arg1, arg2,
                         0, 0, 0.0f, arg8, arg9, arg10, arg11) == 0) {
                return;
            }
        }
        arg6 -= 1.0f;
        cur_x += step_x;
        i++;
        cur_y += step_y;
        cur_z += step_z;
    } while (0.0f < arg6);
}

void func_1514C678(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, s16 arg5, s16 arg6, u8 arg7,
                   s32 arg8, f32 arg9, s32 argA, u8 argB) {
    Func1514C2F0Callback callback;
    f32 temp_arg1 = arg1;
    f32 temp_arg0 = arg0;
    f32 temp_arg2 = arg2;
    s16 range;
    s16 base;
    u8 angle;
    s16 i;
    f32 s;
    f32 c;
    f32 z;

    if (arg5 < arg4) {
        range = arg4 - arg5 + 1;
        base = arg5;
    } else {
        range = arg5 - arg4 + 1;
        base = arg4;
    }
    i = 0;
    if (arg6 > 0) {
        do {
            angle = (u32)func_150ADA20() % range + base;
            s = func_151423D8(angle - 0x40);
            c = func_151423D8(angle);
            z = arg3 * c + temp_arg2;
            callback = D_8008AA00[arg7];
            if (callback != 0) {
                if (callback(2, i, arg3 * s + temp_arg0, temp_arg1, z, temp_arg0, temp_arg1, temp_arg2, angle, arg4, arg3,
                                 arg8, arg9, argA, argB) == 0) {
                    return;
                }
            }
            i++;
        } while (i < arg6);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_176A00/func_1514C858.s")
