#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void *func_151CD4C0();
void func_151CE47C();

struct Vec3w151CEC10;

extern f32 D_800AB020;
extern f32 D_800AB024;
extern f32 D_800AB008;
extern f32 D_800D9860;
extern f32 func_15144AA8(s32);
extern struct17 *func_15144B34(s32);
extern s32 func_15046C80(f32 *, s32, f32, f32 *);
extern struct260 *func_15147A80(void *, s32, s32, s32, s32, s32, s32, s32, s32, u8, s32);
s32 func_151CEC10(struct Vec3w151CEC10 *, f32 *, void *);

typedef struct {
    char pad_0x0[0x48];
    s32 field_0x48;
} Func151CE4DCTemp;

typedef struct {
    char pad_0x0[0x98];
    s32 field_0x98;
} Func151CE4DCArg0;

typedef struct {
    char pad_0x0[0x30];
    s32 field_0x30;
} ConkerField30Object;

typedef struct {
    ConkerField30Object *field_0x0;
} ConkerField0Slot;

typedef struct {
    char pad_0x0[0x98];
    ConkerField0Slot *field_0x98;
} ConkerField98Owner;


struct260 *func_151CD2C0(void *arg0, u8 arg1, s32 arg2) {
    struct260 *temp_v0;
    struct {
        void *unk0;
        s32 unk4;
        s32 unk8;
        u8 unkC;
        u8 padD;
        u8 padE;
        u8 padF;
    } sp34;

    sp34.unk0 = arg0;
    sp34.unk4 = *(s32 *)((s32)arg0 + 0x18);
    sp34.unk8 = 0;
    sp34.unkC = *(s32 *)((s32)arg0 + 0x1C);

    temp_v0 = func_15149130(0x12C, -1, -1, -1, 0, 0x1E, (struct37 *)0x10, arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy((void *)((s32)temp_v0 + 0x28), &sp34, 0x10);
    }
    return temp_v0;
}

void func_151CD35C(s32 arg0) {
    s32 sp1C;

    if (arg0 >= 0 && arg0 < 4) {
        sp1C = arg0;
        func_151494E0((s32)&sp1C, 0x17);
    }
}

void func_151CD394(s32 arg0) {
    s32 sp1C;

    if (arg0 >= 0 && arg0 < 4) {
        sp1C = arg0;
        func_151494E0((s32)&sp1C, 0x18);
    }
}

typedef struct {
    void *unk0;
    s32 unk4;
    void *unk8;
    u8 unkC;
} Sub151CD3CC;

void func_151CD3CC(struct260 *arg0, s32 arg1, u8 arg2) {
    Sub151CD3CC *sub;
    /* Reserves 12 bytes at the top of the -g3 stack frame that the shipped
     * build allocated but never referenced. */
    s32 unused[3];

    sub = (Sub151CD3CC *)((s32)arg0 + 0x28);
    if (arg2 == 0x17) {
        if (sub->unk4 == *(s32 *)arg1) {
            if (sub->unk8 == NULL) {
                sub->unk8 = func_151CD4C0(sub->unk0, sub->unkC, sub->unk4, arg0->pad0[0xC], arg0->pad0[1]);
                *(u8 *)((s32)sub->unk0 + 0x14) = 0;
            dummy_label_151CD3CC_1: ;
            }
        }
    } else if (arg2 == 0x18) {
        if (sub->unk4 == *(s32 *)arg1) {
            if (sub->unk8 != NULL) {
                func_151CE47C(sub->unk8);
            }
        }
    } else if (arg2 == 0x23) {
        if (sub->unk4 == *(s32 *)arg1) {
            sub->unk8 = NULL;
            *(u8 *)((s32)sub->unk0 + 0x14) = 1;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CD4C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CD674.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CD7BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CDB94.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CDE20.s")

typedef struct {
    char pad0[0x1E];
    u16 unk1E;
    char pad20[0x10];
    u8 unk30;
} ConkerStruct151CE47C;

void func_151CE47C(ConkerStruct151CE47C *arg0) {
    arg0->unk30 = 0;
    arg0->unk1E &= ~0x2;
    arg0->unk1E |= 0x8;
}

extern void func_151478F4(void *);

void func_151CE49C(Func151CE4DCArg0 *arg0) {
    s32 sp1C;
    Func151CE4DCTemp *temp;

    temp = (Func151CE4DCTemp *)arg0->field_0x98;
    sp1C = temp->field_0x48;
    func_151494E0((s32)&sp1C, 0x23);
    func_151478F4((void *)arg0);
}

extern void func_15147928(s32);

void func_151CE4DC(Func151CE4DCArg0 *arg0) {
    s32 sp1C;
    Func151CE4DCTemp *temp;

    temp = (Func151CE4DCTemp *)arg0->field_0x98;
    sp1C = temp->field_0x48;
    func_151494E0((s32)&sp1C, 0x23);
    func_15147928((s32)arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CE51C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CE634.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CE6D0.s")

s32 func_151CEA20(f32 *arg0) {
    f32 temp_f2;
    f32 temp_f12;

    temp_f2 = arg0[0x11];
    temp_f12 = arg0[0x10];
    arg0[0x11] += temp_f12 * D_800BE9A4;
    *(volatile f32 *)&arg0[0xE] = arg0[0xE] + ((temp_f2 + ((0.5f * temp_f12) * D_800BE9A4)) * D_800BE9A4);
    *(f32 *)&arg0[0x14] = ((*(volatile f32 *)&arg0[0x13]) * D_800BE9A4) + (*(volatile f32 *)&arg0[0x14]);
    if (arg0[0x14] > 1.0f) {
        arg0[0x14] = 1.0f;
    }
    return 1;
}

struct260 *func_151CEAAC(void *arg0, void *arg1, u8 arg2, u8 arg3, s32 arg4) {
    struct {
        f32 unk0;
        f32 unk4;
        f32 unk8;
        s16 unkC;
        s16 unkE;
        s32 unk10;
        u8 unk14;
        u8 unk15;
        u8 pad16[2];
        s32 unk18;
    } sp6C;
    struct {
        void *unk0;
        u8 unk4;
        u8 pad5[3];
        void *unk8;
        f32 unkC;
        f32 unk10;
        f32 unk14;
        f32 unk18;
        u8 unk1C;
        u8 pad1D[3];
        f32 unk20;
        f32 unk24;
    } sp44;
    struct260 *temp_v0;
    s32 flag;
    f32 temp_f;

    sp6C.unk15 = 0x19;
    sp6C.unkC = 0x12C;
    sp6C.unkE = 0x10;
    sp6C.unk10 = 0x11;
    sp6C.unk14 = 3;

    sp44.unk0 = arg0;
    if (arg0 != NULL) {
        sp44.unk4 = *(u8 *)((s32)arg0 + 0x3B);
    } else {
        sp44.unk4 = 0;
    }

    sp44.unk10 = 1.0f;
    sp44.unk18 = 1.0f;
    sp44.unk8 = arg1;
    sp44.unkC = 0.0f;
    sp44.unk14 = 0.0f;
    if (arg2 != 0) {
        flag = 2;
    } else {
        flag = 0;
    }
    sp44.unk1C = flag;

    sp44.unk20 = (func_150ADA68() * 400.0f) + 400.0f;
    temp_f = func_150ADA68();
    sp44.unk24 = (temp_f + temp_f) * D_800AB008;

    if (func_151CEC10((struct Vec3w151CEC10 *)&sp6C, (f32 *)arg0, arg1) == 0) {
        sp6C.unk0 = 0.0f;
        sp6C.unk4 = 0.0f;
        sp6C.unk8 = 0.0f;
    }

    temp_v0 = func_15147A80(&sp6C, 0x28, 0x28, 0, 0xF, 0xF, 0, 0, 0, arg3, arg4);
    if (temp_v0 != NULL) {
        memcpy((void *)*(s32 *)((s32)temp_v0 + 0x98), &sp44, 0x28);
    }
    return temp_v0;
}

struct Vec3w151CEC10 { s32 x, y, z; };

s32 func_151CEC10(struct Vec3w151CEC10 *arg0, f32 *arg1, void *arg2) {
    if (arg2 != NULL) {
        *arg0 = *(struct Vec3w151CEC10 *)((s32)arg2 + 0x40);
    } else {
        *(f32 *)&arg0->x = arg1[5];
        *(f32 *)&arg0->y = arg1[6];
        *(f32 *)&arg0->z = arg1[7];
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CEC54.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CF120.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CF380.s")

struct s151CF844 { s32 pad[0x26]; s32 *unk98p; };

void func_151CF844(struct s151CF844 *arg0, s32 arg1, u8 arg2) {
    s32 *temp = arg0->unk98p;
    if (temp[0] != 0) {
        func_15169850(arg1, arg2, (s32)temp, (s32)temp + 4, (s32)arg0);
    }
}

typedef struct {
    char pad0[0x23D];
    u8 unk23D;
} ConkerStruct151CF898Camera;

typedef struct {
    struct17 vec;
    f32 unkC;
} ConkerStruct151CF898Payload;

void func_151CF898(struct127 *arg0, f32 arg1, f32 arg2) {
    ConkerStruct151CF898Camera *camera;
    struct17 sp58;
    struct17 *pos;
    f32 yaw;
    f32 angle;
    f32 distance;
    ConkerStruct151CF898Payload sp38;
    struct260 *temp_v0;

    camera = (ConkerStruct151CF898Camera *)arg0->camera;
    if (camera != NULL) {
        if (func_150ADA68() < D_800AB020) {
            pos = func_15144B34(camera->unk23D);
            yaw = func_15144AA8(camera->unk23D);
            angle = ((func_150ADA68() * 80.0f) + (yaw - 40.0f)) * D_800AB024;
            distance = func_150ADA68() * 2000.0f;

            sp58.unk0 = pos->unk0 - (sinf(angle) * distance);
            sp58.unk4 = arg1;
            sp58.unk8 = pos->unk8 - (cosf(angle) * distance);

            if (func_15046C80((f32 *)&sp58, 0, arg2, &D_800D9860) != 0) {
                sp58.unk4 = D_800D9860;
                sp38.vec = sp58;
                sp38.unkC = 0.0f;

                temp_v0 = func_15149130((s16)((func_150ADA20() % 0x83U) + 0x33),
                                        -1, 0x20, -1, 1, 0, (struct37 *)0x10, 0xFF, 1);
                if (temp_v0 != NULL) {
                    memcpy((u8 *)temp_v0 + 0x28, &sp38, 0x10);
                }
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CFA4C.s")

void func_151D0024(struct127 *arg0) {
    struct {
        s32 unk0;
        u8 unk4;
    } sp18;

    sp18.unk0 = (s32)arg0;
    sp18.unk4 = arg0->unique_id;
    func_151494E0((s32)&sp18, 0x18);
}

void func_151D0058(struct127 *arg0, u8 arg1, u8 arg2, s32 arg3) {
    struct260 *temp_v0;
    struct {
        struct127 *unk0;
        u8 unk4;
        u8 pad5;
        u16 unk6;
        f32 unk8;
        u8 unkC;
        u8 unkD;
        u8 padE;
        u8 padF;
    } sp3C;

    sp3C.unk0 = arg0;
    sp3C.unk4 = arg0->unique_id;
    sp3C.unk8 = (arg0->xz_scale + arg0->y_scale) * 0.5f;
    sp3C.unkD = arg1;
    sp3C.unkC = (func_150ADA20() % 0x38U) + 0xC8;
    sp3C.unk6 = arg0->unk84.uh;

    temp_v0 = func_15149130(0x12C, -1, 0x61, 4, 0, 0x31, (struct37 *)0x10, arg2, arg3);
    if (temp_v0 != NULL) {
        memcpy((void *)((s32)temp_v0 + 0x28), &sp3C, 0x10);
    }
}

typedef struct {
    char pad84[0x84];
    u16 unk84;
} ConkerStruct151D0128b;

typedef struct {
    char padE[0xE];
    s16 unkE;
    char pad10[0x18];
    ConkerStruct151D0128b *unk28;
    char pad2C[0x2];
    u16 unk2E;
} ConkerStruct151D0128;

void func_151D0128(ConkerStruct151D0128 *arg0) {
    ConkerStruct151D0128b *p = arg0->unk28;
    if (arg0->unk2E != p->unk84) {
        arg0->unkE = -1;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151D014C.s")

typedef struct {
    s32 unk0;
    u8  unk4;
} SubA151D08F0;

typedef struct {
    s32 unk0;
    union {
        s32 w4;
        u8  b4;
    } u4;
    u8  unk8;
    u8  unk9;
} ArgB151D08F0;

void func_151D08F0(struct260 *arg0, s32 arg1, u8 arg2) {
    SubA151D08F0 *temp_v0 = (SubA151D08F0 *)((u8 *)arg0 + 0x28);
    ArgB151D08F0 *b = (ArgB151D08F0 *)arg1;
    s32 b0;

    if (arg2 == 0 || arg2 == 0x18) {
        b0 = b->unk0;
        if ((b0 == temp_v0->unk0) || (b->u4.b4 == temp_v0->unk4)) {
            func_1516972C((struct102 *)arg0);
        }
    } else if (arg2 == 0x2D) {
        if (temp_v0->unk0 == b->unk0) {
            temp_v0->unk0 = b->u4.w4;
            temp_v0->unk4 = b->unk9;
        } else if (temp_v0->unk0 == b->u4.w4) {
            temp_v0->unk0 = b->unk0;
            temp_v0->unk4 = b->unk8;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151D09A8.s")

void func_151D0ED8(void *arg0) {
    if (*(struct102 **)((u8 *)arg0 + 0xA8) != 0) {
        func_1516972C(*(struct102 *volatile *)((u8 *)arg0 + 0xA8));
    }
}

void func_151D0ED8(void *arg0);

void func_1513173C(void *arg0);

void func_151D0F08(void *arg0) {
    func_151D0ED8(arg0);
    func_1513173C(arg0);
}

void func_1513175C(void *arg0);

void func_151D0F34(void *arg0) {
    func_151D0ED8(arg0);
    func_1513175C(arg0);
}

extern s32 (*D_8008FC30[])(struct127 *, void *);

struct vec3_151D0F60 { f32 x; f32 y; f32 z; };

void func_151D0F60(struct127 *arg0, u8 arg1, u8 arg2, s32 arg3) {
    struct260 *temp_v0;
    struct {
        struct127 *unk0;
        u8 unk4;
        u8 pad5[3];
        s32 unk8;
        struct vec3_151D0F60 unkC;
        struct vec3_151D0F60 unk18;
        struct vec3_151D0F60 unk24;
        f32 unk30;
        u8 unk34;
    } sp34;

    sp34.unk0 = arg0;
    sp34.unk4 = arg0->unique_id;
    sp34.unk8 = 0;

    if (D_8008FC30[arg1](arg0, &sp34.unk18) == 0) {
        sp34.unk18 = *(struct vec3_151D0F60 *)&D_800A5480;
    }

    sp34.unkC = sp34.unk18;
    sp34.unk24 = *(struct vec3_151D0F60 *)&D_800A5480;
    sp34.unk30 = 0.0f;
    sp34.unk34 = arg1;

    temp_v0 = func_15149130(0x12C, -1, 0x5F, -1, 0, 0x48, (struct37 *)0x38, arg2, arg3);
    if (temp_v0 != NULL) {
        memcpy((void *)((s32)temp_v0 + 0x28), &sp34, 0x38);
    }
}

s32 func_151D1074(f32 *arg0, f32 *arg1) {
    arg1[0] = arg0[5];
    arg1[1] = arg0[96] + 8.0f;
    arg1[2] = arg0[7];
    return 1;
}

s32 func_151D10E4(void *arg0, s32 arg1, s32 arg2);

s32 func_151D10A4(void *arg0, s32 arg1) {
    return func_151D10E4(arg0, arg1, 0);
}

s32 func_151D10C4(void *arg0, s32 arg1) {
    return func_151D10E4(arg0, arg1, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151D10E4.s")

typedef struct {
    struct127 *unk0;
    u8 unk4;
    u8 pad5[3];
    s32 unk8;
    struct17 unkC;
    struct17 unk18;
    struct17 unk24;
    f32 unk30;
    u8 unk34;
} Sub151D1138;

extern f32 func_15143E64(struct17 *);
extern s32 func_1510F8CC(s32);
void func_151D13E0(struct260 *arg0);
void func_151D1448(struct260 *arg0);

void func_151D1138(struct260 *arg0) {
    Sub151D1138 *sub;
    struct127 *obj;
    u8 finished = 0;
    s32 state;

    sub = (Sub151D1138 *)((u8 *)arg0 + 0x28);
    obj = sub->unk0;

    if (obj->interaction_state == 0 || obj->unique_id != sub->unk4) {
        arg0->unkE = -1;
        return;
    }

    sub->unkC = sub->unk18;
    if (D_8008FC30[sub->unk34](obj, &sub->unk18) == 0) {
        sub->unk18 = sub->unkC;
        finished = 1;
    }

    sub->unk24.unk0 = sub->unk18.unk0 - sub->unkC.unk0;
    sub->unk24.unk4 = sub->unk18.unk4 - sub->unkC.unk4;
    sub->unk24.unk8 = sub->unk18.unk8 - sub->unkC.unk8;
    sub->unk30 = func_15143E64(&sub->unk24);

    state = func_1510F8CC(obj->unk184);
    if (sub->unk30 > 300.0f || sub->unk30 <= 0.0f || obj->unk28 != 0.0f || obj->in_water != 0 ||
        state == 5 || state == 6 || state == 9 || state == 0xD || state == 0xE) {
        finished = 1;
    }

    if (finished != 0) {
        func_151D13E0(arg0);
    } else if (sub->unk8 == 0) {
        func_151D1448(arg0);
    }
}

void func_151D1328(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}

void func_151D13E0(struct260 *arg0);

void func_151D1368(struct260 *arg0) {
    func_151D13E0(arg0);
}

void func_151D1388(struct260 *arg0) {
    func_151D1368(arg0);
    func_1514933C(arg0);
}

void func_15149368(struct260 *arg0);

void func_151D13B4(struct260 *arg0) {
    func_151D1368(arg0);
    func_15149368(arg0);
}

struct Obj151D13E0 {
    char pad0[0x1C];
    s16 unk1C;
    u16 unk1E;
    char pad20[0x10];
    u8 unk30;
    char pad31[0x67];
    s32 *unk98;
};

struct Slot151D13E0 {
    char pad0[0x8];
    struct Obj151D13E0 *unk8;
};

void func_151D13E0(struct260 *arg0) {
    struct Slot151D13E0 *slot = (struct Slot151D13E0 *)((char *)arg0 + 0x28);
    struct Obj151D13E0 *obj;
    s32 *p;

    if (slot->unk8 != 0) {
        p = slot->unk8->unk98;
        slot->unk8->unk30 = 0;
        slot->unk8->unk1E &= ~0x2;
        slot->unk8->unk1E |= 0x8;
        slot->unk8->unk1E |= 0x1;
        slot->unk8->unk1C = 0x28;
        *p = 0;
        slot->unk8 = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151D1448.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151D15D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151D197C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151D1C98.s")

void func_151D223C(ConkerField98Owner *arg0) {
    ConkerField0Slot *temp_v0;
    ConkerField30Object *temp_v1;

    temp_v0 = arg0->field_0x98;
    temp_v1 = temp_v0->field_0x0;
    if (temp_v1 != 0) {
        temp_v1->field_0x30 = 0;
    }
}

extern void func_151478F4(void *);

void func_151D2258(s32 arg0) {
    func_151D223C(arg0);
    func_151478F4((void *)arg0);
}

extern void func_15147928(s32);

void func_151D2284(s32 arg0) {
    func_151D223C(arg0);
    func_15147928(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151D22B0.s")
