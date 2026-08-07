#include <ultra64.h>
#define func_15048A40 func_15048A40_void_unused
#include "functions.h"
#undef func_15048A40
#include "variables.h"
extern f32 func_15048A40(u8);
extern void func_15188010(s32, f32 *);
extern s32 func_151149AC(u32);
extern f32 D_800A2F8C;
extern void *allocate_memory(s32, s32, s32, s32);
extern f32 D_800A3210;
extern f32 D_800A3214;
extern f32 D_800A2FF4;
extern f32 D_800A2FF8;
extern f32 D_800A2FFC;
extern f32 D_800A2FB0;
extern f32 D_800A2FB4;

struct Struct1511F31CArg {
    u8 pad0[0x10];
    s16 unk10;
    s16 unk12;
    s16 unk14;
    u8 pad16[0x28];
    u16 unk3E;
    u8 pad40[0x14];
    u16 unk54;
};

extern void func_1511F31C(struct Struct1511F31CArg *arg0);

struct Struct1511490C {
    char pad0[0x10];
    s16 unk10;
    s16 unk12;
    s16 unk14;
    char pad16[2];
    f32 unk18;
    char pad1C[0x10];
    s32 unk2C;
    s32 unk30;
    s32 unk34;
};

extern void func_1511490C(f32 arg0[4][4], struct Struct1511490C *arg1);
extern void func_150A7960(f32 *arg0, f32 arg1, s32 arg2, f32 arg3, f32 *arg4, f32 *arg5, f32 *arg6);

struct Obj151151FC {
    f32 unk0;
    u8 pad4[0x38];
    s32 unk3C;
    u8 pad40[0x20];
    f32 unk60;
};

struct Obj151150BC {
    u8 pad0[0x8];
    f32 unk8;
    u8 padC[0x30];
    s32 unk3C;
    u8 pad40[0x28];
    f32 unk68;
};

struct Obj1511515C {
    u8 pad0[0x4];
    f32 unk4;
    u8 pad8[0x34];
    s32 unk3C;
    u8 pad40[0x24];
    f32 unk64;
};

struct Obj151152A8 {
    char pad_0x0[0x12];
    s16 field_0x12;
    char pad_0x14[0x28];
    s32 field_0x3C;
    char pad_0x40[0xF];
    u8 field_0x4F;
    char pad_0x50[0x23];
    u8 field_0x73;
    char pad_0x74[0x8];
    s32 field_0x7C;
};

void func_151150B0(s32 arg0) {
}

void func_151150BC(struct Obj151150BC *arg0) {
    arg0->unk68 = (f32)((arg0->unk3C >> 16) * D_800BE9E4) * 0.00390625f;
    arg0->unk8 = arg0->unk8 + arg0->unk68;
    if (arg0->unk8 < 0.0f) {
        arg0->unk8 = arg0->unk8 + 360.0f;
        return;
    }
    if (arg0->unk8 >= 360.0f) {
        arg0->unk8 = arg0->unk8 - 360.0f;
    }
}

void func_1511515C(struct Obj1511515C *arg0) {
    arg0->unk64 = (f32)((arg0->unk3C >> 16) * D_800BE9E4) * 0.00390625f;
    arg0->unk4 = arg0->unk4 + arg0->unk64;
    if (arg0->unk4 < 0.0f) {
        arg0->unk4 = arg0->unk4 + 360.0f;
        return;
    }
    if (arg0->unk4 >= 360.0f) {
        arg0->unk4 = arg0->unk4 - 360.0f;
    }
}

void func_151151FC(struct Obj151151FC *arg0) {
    arg0->unk60 = (f32)((arg0->unk3C >> 16) * D_800BE9E4) * 0.00390625f;
    arg0->unk0 = arg0->unk0 + arg0->unk60;
    if (arg0->unk0 < 0.0f) {
        arg0->unk0 = arg0->unk0 + 360.0f;
        return;
    }
    if (arg0->unk0 >= 360.0f) {
        arg0->unk0 = arg0->unk0 - 360.0f;
    }
}

void func_1511529C(s32 arg0) {
}

void func_151152A8(struct Obj151152A8 *arg0) {
    s32 target;
    s32 current;
    s32 step;
    s32 *targetPtr;

    targetPtr = &arg0->field_0x7C;
    target = *targetPtr;
    if (target == 0) {
        target = arg0->field_0x12;
        *targetPtr = target;
    }
    current = arg0->field_0x12;
    if ((arg0->field_0x4F & 0xFF) & 4) {
        step = arg0->field_0x3C;
        if ((target - current) < (s16)step) {
            arg0->field_0x12 = current - ((s16)(step >> 16) * D_800BE9E4);
            return;
        }
    } else {
        arg0->field_0x12 = (s32)((f32)current + ((f32)(target - current) * D_800A2F8C * (f32)D_800BE9E4));
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_15115368.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_151155C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_1511575C.s")

extern f32 D_800A2FA0;
extern f32 D_800A2FA4;

struct S_15115EDC { u8 pad[0x7C]; f32 unk7C; f32 unk80; };
struct A_15115EDC { u8 pad[0x84]; u16 unk84; };

struct B_15115E0C {
    u8 pad0[0x4];
    f32 unk4;
    u8 pad8[0x8];
    s16 unk10;
    u8 pad12[0x2];
    s16 unk14;
    u8 pad16[0x39];
    u8 unk4F;
    u8 pad50[0x2C];
    f32 unk7C;
    f32 unk80;
};

struct C_15115E0C {
    u8 pad0[0x14];
    f32 unk14;
    u8 pad18[0x4];
    f32 unk1C;
};

struct Obj151163C0 {
    f32 unk0;
    u8 pad4[0xE];
    s16 unk12;
    u8 pad14[0x4];
    f32 unk18;
    u8 pad1C[0x20];
    s32 unk3C;
    u8 pad40[0x1C];
    s16 unk5C;
    u8 pad5E[0x2];
    f32 unk60;
    u8 pad64[0x18];
    s32 unk7C;
    s32 unk80;
};

void func_15115E0C(struct B_15115E0C *arg0, struct C_15115E0C *arg1) {
    f32 s;
    f32 c;
    f32 dx;
    f32 dy;

    s = func_150AD780(arg0->unk4 * D_800A2FA0);
    c = func_150AD78C(arg0->unk4 * D_800A2FA4);
    dx = arg1->unk14 - (f32)arg0->unk10;
    dy = arg1->unk1C - (f32)arg0->unk14;
    if ((arg0->unk4F & 4) == 4) {
        arg0->unk7C = arg0->unk7C + (c * dx + s * dy);
        arg0->unk80 = arg0->unk80 - (c * dy + s * dx);
    }
}

void func_15115EDC(struct S_15115EDC *arg0, struct A_15115EDC *arg1) {
    f32 oldX;
    f32 oldY;
    oldX = arg0->unk7C;
    oldY = arg0->unk80;
    func_15115E0C((struct B_15115E0C *)arg0, (struct C_15115E0C *)arg1);
    if (arg1->unk84 == 0x4B) {
        oldX = (arg0->unk7C - oldX) * 4.0f;
        oldY = (arg0->unk80 - oldY) * 4.0f;
        arg0->unk7C = arg0->unk7C + oldX;
        arg0->unk80 = arg0->unk80 + oldY;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_15115F68.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_15116058.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_15116110.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_1511617C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_151162D4.s")

void func_151163C0(struct Obj151163C0 *arg0) {
    volatile f32 sp2C;
    u32 sp28;
    u32 sp24;
    volatile f32 sp20;
    s16 sp1E;
    f32 sp18;
    f32 temp_f2;
    u32 temp_t2;
    s32 temp_v0;

    temp_v0 = arg0->unk3C;
    temp_t2 = (temp_v0 >> 8) & 0xFF;
    sp28 = (temp_v0 >> 0x10) & 0xFF;
    sp2C = (f32)(temp_v0 & 0xFF);
    sp24 = (temp_v0 >> 0x18) & 0xFF;
    sp20 = (f32)temp_t2 * 1.40625f;
    sp1E = arg0->unk12;
    sp18 = arg0->unk0;
    arg0->unk18 = cosf((f32)arg0->unk7C * D_800A2FB0) * sp2C;
    temp_f2 = cosf((f32)arg0->unk80 * D_800A2FB4) * sp20;
    arg0->unk0 = temp_f2;
    arg0->unk7C = arg0->unk7C + (sp28 * D_800BE9E4);
    arg0->unk80 = arg0->unk80 + (sp24 * D_800BE9E4);
    arg0->unk5C = arg0->unk12 - sp1E;
    arg0->unk60 = temp_f2 - sp18;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_1511650C.s")

struct Obj15116888 {
    u8 pad0[0x14];
    f32 unk14;
    u8 pad18[0x4];
    f32 unk1C;
    u8 pad20[0x1C];
    f32 unk3C;
    u8 pad40[0x36];
    u16 unk76;
};

struct Vec15116888 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    u8 padC[0x4];
};

s32 func_150490A8(struct17 *arg0);

s32 func_15116888(s32 arg0, s32 arg1, s32 arg2, struct Obj15116888 *arg3) {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    f32 r;
    struct Vec15116888 sp1C;

    a = (s32)arg3->unk14;
    b = (s32)arg3->unk1C;
    sp1C.unk0 = (f32)(a - arg0);
    sp1C.unk8 = (f32)(b - arg1);

    c = func_150490A8((struct17 *)&sp1C);
    d = (s32)arg3->unk76 >> 8;
    d = 0x40 - d;
    d = d - c;
    r = func_15048A40((u8)d);
    r = arg3->unk3C * r;
    return (s32)r;
}

void func_15116924(s32 arg0) {
}

void func_15116930(u8 *arg0, u8 *arg1) {
    s32 temp;
    if (arg0[0x4F] & 0x4) {
        if (!(arg0[0x73] & 0x3) && !(arg0[0x73] & 0x4)) {
            if (((u8 **)arg1)[0x31C / 4][0x57] == 1) {
                arg0[0x73] &= 0xFFFC;
                arg0[0x73] |= 0x2;
            }
        }
    }
}

extern void func_151169B4(u8 *arg0);

void func_15116984(u8 *arg0) {
    if (arg0[0x73] & 0x2) {
        func_151169B4(arg0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_151169B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_15116BAC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_15116D7C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_15116EA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_151172D8.s")

struct Obj151174A0 {
    char pad0[0x8];
    f32 unk8;
};

extern f32 func_151172D8(struct Obj151174A0 *, f32);

void func_151174A0(struct Obj151174A0 *arg0) {
    arg0->unk8 = func_151172D8(arg0, arg0->unk8);
}

struct Obj151174C8 {
    char pad0[0x4];
    f32 unk4;
};

void func_151174C8(struct Obj151174C8 *arg0) {
    arg0->unk4 = func_151172D8((struct Obj151174A0 *)arg0, arg0->unk4);
}

struct Obj151174F0 {
    f32 unk0;
};

void func_151174F0(struct Obj151174F0 *arg0) {
    arg0->unk0 = func_151172D8((struct Obj151174A0 *)arg0, arg0->unk0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_15117518.s")

extern f32 func_15117518(struct Obj151174F0 *, f32);

void func_15117770(struct Obj151174F0 *arg0) {
    arg0->unk0 = func_15117518(arg0, arg0->unk0);
}

struct Obj15117798 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
};

struct Obj15117DA4 {
    f32 unk0;
    f32 unk4;
    u8 pad8[0x8];
    s16 unk10;
    s16 unk12;
    s16 unk14;
    u8 pad16[0x28];
    u16 unk3E;
    u8 pad40[0x14];
    u16 unk54;
};

void func_15117798(struct Obj15117798 *arg0) {
    arg0->unk8 = func_15117518((struct Obj151174F0 *)arg0, arg0->unk8);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_151177C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_151179BC.s")

void func_15117D3C(struct Obj151152A8 *arg0, struct127 *arg1) {
    s32 temp = arg0->field_0x3C & 0xFFFF;
    if (arg1->interaction_state == 1) {
        if (arg0->field_0x4F & 0x4) {
            if (!(arg0->field_0x73 & 0x3) && !(arg0->field_0x73 & 0x4)) {
                if (temp == 0 || arg1->unk31C->unk57 == 1) {
                    arg0->field_0x73 &= 0xFFFC;
                    arg0->field_0x73 |= 0x2;
                }
            }
        }
    }
}

void func_15117DA4(struct Obj15117DA4 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4) {
    f32 angle;
    f32 s;
    f32 c;
    f32 temp_z;
    f32 temp_x;

    if (arg0->unk54 == 0x8006) {
        if (D_800BE9F0 == 0x35) {
            arg0 = (struct Obj15117DA4 *)func_151149AC(0xFD);
            func_1511F31C((struct Struct1511F31CArg *)arg0);
            arg2 = D_800A2FF4;
            arg1 = 0.0f;
            arg3 = 0.0f;
        }
    }

    angle = arg0->unk0 * D_800A2FF8;
    s = sinf(angle);
    c = cosf(angle);
    arg4[0] = arg1;
    arg4[1] = (arg2 * c) - (arg3 * s);
    arg4[2] = (arg2 * s) + (arg3 * c);

    angle = arg0->unk4 * D_800A2FFC;
    s = sinf(angle);
    c = cosf(angle);
    temp_x = arg4[0];
    temp_z = arg4[2];
    arg4[0] = (temp_z * s) + (temp_x * c);
    arg4[2] = (temp_z * c) + (-temp_x * s);

    arg4[0] = *(volatile f32 *)&arg4[0] + arg0->unk10;
    arg4[1] = *(volatile f32 *)&arg4[1] + arg0->unk12;
    arg4[2] = *(volatile f32 *)&arg4[2] + arg0->unk14;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_15117F3C.s")

s32 func_151189AC(void *arg0, s32 arg1);

s32 func_1511896C(void *arg0) {
    return func_151189AC(arg0, 0);
}

s32 func_1511898C(void *arg0) {
    return func_151189AC(arg0, 3);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_151189AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_15118F24.s")

struct Obj151193AC_0 {
    char pad0[0x73];
    u8 unk73;
};

struct Obj151193AC_1 {
    s32 unk0;
    char pad4[0x61];
    u8 unk65;
};

void func_151193AC(struct Obj151193AC_0 *arg0, struct Obj151193AC_1 *arg1) {
    if (arg1->unk0 == 1) {
        if (arg1->unk65 == 0) {
            if (!(arg0->unk73 & 0x3) && !(arg0->unk73 & 0x4)) {
                arg0->unk73 &= 0xFFFC;
                arg0->unk73 |= 0x2;
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_151193F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_151194D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_151196D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_15119938.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_15119FC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_1511A410.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_1511A494.s")

extern void func_15116110(void *);
extern void func_1511A494(void *, void *, void *);

void func_1511A6FC(s32 *arg0) {
    if (arg0[0xF] != 0) {
        func_15116110(arg0);
    }
    func_1511A494(arg0, (u8 *)arg0 + 0x80, (u8 *)arg0 + 0x84);
}

extern u8 D_800C35EA;
extern struct131 *D_800DBEF4;
extern s32 func_15022B08(s32, s32);
extern void func_151162D4(void *);

void func_1511A738(struct131 *arg0) {
    if (D_800C35EA == 1) {
        if (func_15022B08(arg0 - D_800DBEF4, 0) != 0) {
            *(s32 *)((u8 *)arg0 + 0x7C) = 0;
            *(f32 *)((u8 *)arg0 + 0x18) = 0.0f;
        }
    }
    func_151162D4(arg0);
    func_1511A494(arg0, (u8 *)arg0 + 0x80, (u8 *)arg0 + 0x84);
}

struct S_1511A7C0 {
    u8 pad0[0x4];
    f32 *unk4;
    u8 pad8[0x8];
    f32 unk10;
    f32 unk14;
    f32 unk18;
    u8 unk1C;
    u8 unk1D;
    u8 unk1E;
};
struct A_1511A7C0 {
    u8 pad0[0x16];
    u16 unk16;
    u8 pad18[0x68];
    struct S_1511A7C0 *unk80;
};
void func_1511A7C0(struct A_1511A7C0 *arg0) {
    struct S_1511A7C0 *v0;
    s32 i;
    v0 = arg0->unk80;
    v0->unk1E = 1;
    v0->unk10 = 0.0f;
    v0->unk1C = 0;
    v0->unk1D = 7;
    v0->unk14 = 260.0f;
    v0->unk18 = 100.0f;
    for (i = 0; i < arg0->unk16; i++) {
        v0->unk4[i] = 0.0f;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_1511A838.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_1511AF30.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_1511B07C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_1511B51C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_1511B7D4.s")

struct Obj1511BA24 {
    u8 pad0[0x3C];
    s32 unk3C;
    u8 pad40[0x4A];
    u8 unk8A;
};

void func_1511BA24(struct Obj1511BA24 *arg0) {
    f32 sp1C;

    sp1C = 0.0f;
    func_15188010(arg0->unk3C, &sp1C);
    arg0->unk8A = sp1C * 255.0f;
    if (arg0->unk8A == 0) {
        arg0->unk8A = 1;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_1511BB04.s")

struct Obj1511BDF4 {
    u8  pad0[0x3F];
    u8  unk3F;
    u8  pad40[0x40];
    struct127 *unk80;
};

extern void func_1511BB04(struct Obj1511BDF4 *, f32, f32, f32, f32);

void func_1511BDF4(struct Obj1511BDF4 *arg0) {
    struct127 *temp;
    struct127 *sp;

    temp = arg0->unk80;
    if (temp != 0) {
        sp = temp;
    } else {
        sp = func_15083E90(arg0->unk3F);
    }
    if (sp != 0) {
        func_1511BB04(arg0, sp->x_position, sp->z_position, 1.0f, 1.0f);
    }
}

struct Obj1511BE5C {
    u8  pad0[0x4];
    f32 unk4;
    u8  pad8[0x8];
    s16 unk10;
    s16 unk12;
    s16 unk14;
};

extern f32 D_800A31E0;

void func_1511BE5C(struct Obj1511BE5C *arg0) {
    arg0->unk4 = func_150484A0((f32)arg0->unk10 - D_800DBFF0->unk2F8, (f32)arg0->unk14 - D_800DBFF0->unk300) * D_800A31E0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_1511BEBC.s")

void func_1511C540(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_1511C548.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_1511C638.s")

extern f32 D_800A31F4;

void func_1511CB2C(s32 arg0, f32 *arg1) {
    *arg1 = D_800A31F4;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_1511CB44.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_1511D394.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_1511D7BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_1511D9E4.s")

struct Obj1511DBC4Sub {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
};

struct Obj1511DBC4 {
    u8 pad0[0x8];
    f32 unk8;
    u8 padC[0x67];
    u8 unk73;
    u8 pad74[0x8];
    struct Obj1511DBC4Sub *unk7C;
};

void func_1511DBC4(struct Obj1511DBC4 *arg0) {
    s32 state;
    struct Obj1511DBC4Sub *temp;
    f32 ftemp;

    if (arg0->unk7C == NULL) {
        temp = allocate_memory(0x10, 1, 0, 0);
        arg0->unk7C = temp;
        temp->unk0 = 0.0f;
        temp->unk4 = 0.0f;
        temp->unk8 = 0.0f;
        temp->unkC = D_800A3210;
    } else {
        temp = arg0->unk7C;
    }

    state = arg0->unk73 & 3;
    if (state == 0) {
        arg0->unk8 = 0.0f;
    } else if (state == 3) {
        arg0->unk8 = 90.0f;
        ftemp = cosf(temp->unk0 * D_800A3214);
        ftemp = ftemp * 0.5f;
        arg0->unk8 = arg0->unk8 + ftemp;
        temp->unk0 = temp->unk0 + (3.0f * (f32)D_800BE9E4);
    } else if (state == 2) {
        if (arg0->unk8 == 0.0f) {
            temp->unk4 = 0.0f;
            temp->unk8 = 0.0f;
        }
        temp->unk8 = temp->unk8 + temp->unkC;
        temp->unk4 = temp->unk4 + temp->unk8;
        arg0->unk8 = arg0->unk8 + temp->unk4;
        if (arg0->unk8 >= 90.0f) {
            state = 3;
            arg0->unk8 = 90.0f;
        }
    } else {
        if ((f32)D_800BE9E4 < arg0->unk8) {
            arg0->unk8 = arg0->unk8 - (f32)D_800BE9E4;
        } else {
            arg0->unk8 = 0.0f;
            state = 0;
        }
    }

    arg0->unk73 &= 0xFFFC;
    arg0->unk73 |= state;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_1511DD98.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_1511DF6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_1511E780.s")

struct Obj1511EC50 {
    u8 pad0[0x12];
    s16 unk12;
    u8 pad14[0x28];
    s32 unk3C;
    u8 pad40[0x2E];
    s8 unk6E;
    u8 pad6F[0xD];
    s32 unk7C;
    s32 unk80;
    f32 unk84;
};

struct Obj1511ED84 {
    u8 pad0[0x14];
    s16 unk14;
    u8 pad16[0x5C];
    u8 unk72;
    u8 pad73[0x9];
    s32 unk7C;
    s32 unk80;
    f32 unk84;
};

void func_1511EC50(struct Obj1511EC50 *arg0) {
    f32 step;
    f32 limit;

    if (arg0->unk7C == 0) {
        arg0->unk84 = (f32)arg0->unk12;
    }

    step = (f32)D_800BE9E4 * 4.0f;
    if (arg0->unk3C != 0) {
        step = step * 0.25f;
    }

    if (arg0->unk80 != 0) {
        arg0->unk12 = (s32)((f32)arg0->unk12 + (step * 5.0f));
        limit = arg0->unk84 + 500.0f;
        if (limit < (f32)arg0->unk12) {
            arg0->unk12 = (s32)limit;
            arg0->unk6E = 1;
        }
    } else {
        limit = arg0->unk84;
        arg0->unk12 = (s32)((f32)arg0->unk12 - step);
        if ((f32)arg0->unk12 < limit) {
            arg0->unk12 = (s32)limit;
        }
    }
    arg0->unk7C = 1;
}

void func_1511ED84(struct Obj1511ED84 *arg0) {
    f32 step;
    f32 limit;
    s32 direction;

    if (arg0->unk7C == 0) {
        arg0->unk84 = (f32)arg0->unk14;
    }

    step = (f32)D_800BE9E4 * 4.0f;
    direction = 1 - (arg0->unk72 & 1);

    if (arg0->unk80 != 0) {
        if (direction & 1) {
            arg0->unk14 = (s32)((f32)arg0->unk14 + step);
            limit = arg0->unk84;
            if (limit < (f32)arg0->unk14) {
                arg0->unk14 = (s32)limit;
            }
        } else {
            limit = arg0->unk84;
            arg0->unk14 = (s32)((f32)arg0->unk14 - step);
            if ((f32)arg0->unk14 < limit) {
                arg0->unk14 = (s32)limit;
            }
        }
    } else {
        if (direction & 1) {
            arg0->unk14 = (s32)((f32)arg0->unk14 - step);
            limit = arg0->unk84 - 350.0f;
            if ((f32)arg0->unk14 < limit) {
                arg0->unk14 = (s32)limit;
            }
        } else {
            arg0->unk14 = (s32)((f32)arg0->unk14 + step);
            limit = arg0->unk84 + 350.0f;
            if (limit < (f32)arg0->unk14) {
                arg0->unk14 = (s32)limit;
            }
        }
    }
    arg0->unk7C = 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_1511EF40.s")

void func_1511F31C(struct Struct1511F31CArg *arg0) {
    f32 sp3C[21];
    struct Struct1511490C *temp_v0;
    u32 temp_id;

    temp_id = arg0->unk3E;
    if (arg0->unk54 == 0x8005) {
        if (D_800BE9F0 == 0x35) {
            temp_v0 = (struct Struct1511490C *)func_151149AC(temp_id & 0xFF);
            if (temp_v0 != NULL) {
                func_1511490C((f32 (*)[4])&sp3C[3], temp_v0);
                func_150A7960(&sp3C[3], -3.0f, 0x435F0000, 549.0f, &sp3C[2], &sp3C[1], &sp3C[0]);
                arg0->unk10 = (s16)sp3C[2];
                arg0->unk12 = (s16)sp3C[1];
                arg0->unk14 = (s16)sp3C[0];
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_1511F3E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_1511F4D0.s")

void func_1511F768(s32 *arg0, s32 arg1) {
    if (arg0[0x20] == 0) {
        arg0[0x20] = 1;
    }
}

struct Obj1511F788 {
    u8 pad0[0x12];
    s16 unk12;
    u8 pad14[0x4];
    f32 unk18;
    u8 pad1C[0x20];
    s32 unk3C;
    u8 pad40[0x1C];
    s16 unk5C;
    u8 pad5E[0x10];
    s8 unk6E;
    u8 pad6F[0xD];
    s32 unk7C;
    s32 unk80;
    s32 unk84;
};

union Temp1511F788 {
    struct {
        f32 pad;
        s32 w;
    } s;
    f64 d;
};

void func_1511F788(struct Obj1511F788 *arg0) {
    s32 dummy;
    union Temp1511F788 temp;
    s16 initial;
    s32 state;

    initial = (s16)(s32)((f32)arg0->unk12 + arg0->unk18);
    temp.s.w = arg0->unk3C;
    temp.s.w = (temp.s.w * 0x3C) / 0x3C;
    if (D_800BE9B4 != 0) {
        arg0->unk7C = func_150ADA20() & 0xFFFF;
    }

    arg0->unk18 = cosf((f32)arg0->unk7C * 0.0054931640625f) * 25.0f;
    state = arg0->unk80;
    arg0->unk7C = arg0->unk7C + (D_800BE9E4 * 10);

    if (state == 1) {
        arg0->unk84 = arg0->unk84 + D_800BE9E4;
        if (temp.s.w < arg0->unk84) {
            arg0->unk80 = 2;
        }
    } else if (state == 2) {
        arg0->unk12 = arg0->unk12 - D_800BE9E4;
        if (arg0->unk12 < -10000) {
            ((u8 *)arg0)[0x6E] = 1;
        }
    }

    arg0->unk5C = (s32)(((f32)arg0->unk12 + arg0->unk18) - (f32)initial);
}

extern s32 func_151149AC(u32);

void func_1511F92C(s16 *arg0) {
    s16 *temp_v0;

    temp_v0 = (s16 *)func_151149AC(*(u8 *)((u8 *)arg0 + 0x3F));
    if (temp_v0 != NULL) {
        arg0[8] = temp_v0[8];
        arg0[9] = temp_v0[9];
        arg0[0xA] = temp_v0[0xA];
    }
}
