#include <ultra64.h>
#include "functions.h"
#include "variables.h"

s32 func_1513FAB4(void *arg0, s32 arg1, f32 *arg2, s16 arg3);
s32 func_151BB0E0();
extern f32 D_800AA8E0;
extern f32 D_800AA8E8;
extern f32 D_800AA8EC;
extern f32 D_800AA8F0;
extern f32 D_800AA8F4;
extern f32 D_800AA8F8;
extern f32 D_800AA8FC;
extern f32 D_800AA900;
extern f32 D_800AA904;
extern f32 D_800AA908;
extern f32 D_800AA90C;
void func_15150F90(void *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_15153634(void *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_151602C0(Header *, Header2 *, s32, s32, s32, s32, s32, s32, s32, u8, s32);


#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151B9F00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BA084.s")

typedef struct {
    s32 unk0;
    u8  unk4;
} SubA_151BA468;

typedef struct {
    u8  pad[0x3B];
    u8  unk3B;
} SomeObj_151BA468;

typedef struct {
    u8  pad[0x50];
    s32 unk50;
} Base_151BA468;

typedef struct {
    s32 unk0;
    union {
        s32 w4;
        u8  b4;
    } u4;
    u8  unk8;
    u8  unk9;
} ArgB_151BA468;

void func_151BA468(struct260 *arg0, s32 arg1, u8 arg2) {
    SubA_151BA468 *temp_v0 = (SubA_151BA468 *)((u8 *)arg0 + ((Base_151BA468 *)arg0)->unk50 + 0xF8);
    ArgB_151BA468 *b = (ArgB_151BA468 *)arg1;
    s32 b0 = temp_v0->unk0;
    SomeObj_151BA468 *o = (SomeObj_151BA468 *)b0;

    if (arg2 == 0) {
        if ((b0 == b->unk0) || (b->u4.b4 == o->unk3B)) {
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

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BA518.s")

void func_151BB044(struct127 *arg0) {
    func_1000FA64(0x4A7, (s16)(s32)arg0->x_position,
                  (s16)(s32)arg0->y_position,
                  (s16)(s32)arg0->z_position, 0x2000, 0x320, 0xC8,
                  (s32)func_151BB0E0, arg0, 0, 8, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BB0E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BB61C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BBA9C.s")

void func_151BBEE4(f32 *arg0, u8 arg1, s32 arg2) {
    Header header;
    Header2 header2;

    header.unk0 = 3;
    header.unk1 = -1;
    header.unk2 = (func_150ADA20() & 0xF) + 5;
    header.unk4 = 0;

    header2.unk0 = (s32) arg0[0];
    header2.unk4 = (s32) arg0[1];
    header2.unk8 = (s32) arg0[2];

    func_151602C0(&header, &header2, (func_150ADA20() % 0x15U) + 0x1E, 0xFF, 0x61, 0x36, 0xFF, 0, 0, arg1, arg2);
}

void func_150E7FEC(f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_151BBFBC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    union { u32 w; f64 _a; } r1;
    f32 temp_f;
    u32 r2;

    temp_f = func_150ADA68();
    r1.w = func_150ADA20();
    r2 = func_150ADA20();
    func_150E7FEC(temp_f * 75.0f + 75.0f, ((r1.w % 0x38) + 0xC8) & 0xFF, arg0, arg1,
                  (r2 % 0xCD) + 0x12B, 1, 1, 0, 0, 0, (u8)arg2, 0);
}

extern f32 D_800AA82C;
extern u8 D_800AA760;
extern u8 D_800AA76C;
void func_15160CDC(s32, s32, void *, void *, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_151BC074(s32 arg0) {
    if (arg0 != 0) {
        func_15160CDC(arg0, 1, &D_800AA760, &D_800AA76C, D_800AA82C, 2, 0x12C,
                      0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 0, 0xFF, 1);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BC104.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BC370.s")

s32 func_151BC580(s32 *arg0) {
    s32 *p = (s32 *)arg0[0x10];
    if (*p == 0) {
        return 0;
    }
    return 1;
}

typedef struct {
    s32 unk0;
    u8  unk4;
} SubA_151BC5A4;

typedef struct {
    s32 unk0;
    union {
        s32 w4;
        u8  b4;
    } u4;
    u8  unk8;
    u8  unk9;
} ArgB_151BC5A4;

void func_151BC5A4(struct260 *arg0, s32 arg1, u8 arg2) {
    SubA_151BC5A4 *temp_v0 = (SubA_151BC5A4 *)((u8 *)arg0 + 0x40);
    ArgB_151BC5A4 *b = (ArgB_151BC5A4 *)arg1;
    s32 b0 = temp_v0->unk0;

    if (arg2 == 0) {
        if ((b0 == b->unk0) || (temp_v0->unk4 == b->u4.b4)) {
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

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BC64C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BC794.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BCA90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BD21C.s")

s32 func_151BD2BC(s32 *arg0) {
    s32 *p = (s32 *)arg0[0xA];
    if (*p == 0) {
        return 0;
    }
    if (*((u8 *)arg0 + 0x2C) != *((u8 *)p + 0x3B)) {
        return 0;
    }
    return 1;
}

extern f32 D_800AA850;
extern f32 D_800AA860;
extern f32 D_800AA864;

typedef struct {
    /* 0x00 */ u8  unk0;
    /* 0x01 */ u8  pad1[0x3];
    /* 0x04 */ void *unk4;
    /* 0x08 */ u8  unk8;
    /* 0x09 */ u8  pad9[0x3];
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u8  unk24;
    /* 0x25 */ u8  pad25[0x1];
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ u8  unk2E;
    /* 0x2F */ u8  unk2F;
    /* 0x30 */ s8  unk30;
    /* 0x31 */ u8  pad31[0x3];
    /* 0x34 */ f32 unk34;
    /* 0x38 */ u8  unk38;
    /* 0x39 */ s8  unk39;
} struct_E9FE0_2F8;

void *func_15134DAC(struct_E9FE0_2F8 *, s32);

void func_151BD2F8(void *arg0, s32 arg1, s32 arg2) {
    struct_E9FE0_2F8 sp24;
    struct { s16 unk0; u8 pad[2]; } sp20;
    void *temp_v0;

    if (arg0 == NULL) {
        return;
    }

    sp24.unk0 = *((u8 *)arg0 + 0x3B);
    sp24.unk4 = arg0;
    sp24.unk8 = 1;
    sp24.unkC = 31.0f;
    sp24.unk10 = -34.0f;
    sp24.unk14 = -117.0f;
    sp24.unk18 = 35.0f;
    sp24.unk1C = -24.0f;
    sp24.unk20 = -182.0f;
    sp24.unk24 = 0;
    sp24.unk26 = 0x32;
    sp24.unk28 = 0x64;
    sp24.unk2A = 0x12C;
    sp24.unk2E = 4;
    sp24.unk2F = 4;
    sp24.unk30 = 3;
    sp24.unk34 = D_800AA850;
    sp24.unk38 = 5;
    sp24.unk39 = -1;

    sp20.unk0 = 0;

    temp_v0 = func_15134DAC(&sp24, 2);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x80, &sp20, 2);
    }

    sp24.unkC = -sp24.unkC;
    sp24.unk18 = -sp24.unk18;

    temp_v0 = func_15134DAC(&sp24, 2);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x80, &sp20, 2);
    }
}

typedef struct {
    u8 pad0[0x80];
    /* 0x80 */ s16 unk80;
} S151BD42C;

s32 func_151BD42C(S151BD42C *arg0) {
    arg0->unk80 = 0;
    return 0x1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BD43C.s")

f32 func_151BD750(s16 *arg0) {
    s16 temp;
    f32 ret;

    temp = arg0[0x40];
    ret = (1.0f + 1.0f) * (f32) temp * D_800AA860 + D_800AA864;
    arg0[0x40] = temp + D_800BE9E4;
    return ret;
}

extern void func_1513170C(void);

struct S151BD79C_sub {
    s32 unk0;
    u8 unk4;
    u8 pad5[0xF];
    f32 unk14;
    f32 unk18;
    f32 unk1C;
};

struct S151BD79C {
    u8 pad0[0x4C];
    f32 unk4C;
    f32 unk50;
    f32 unk54;
    u8 padB0[0xB0 - 0x58];
    struct S151BD79C_sub *unkB0;
};

void func_151BD79C(struct S151BD79C *arg0) {
    struct S151BD79C_sub *v0 = arg0->unkB0;
    if (v0->unk0 != 0 && v0->unk4 != 0xFF) {
        arg0->unk4C = v0->unk14;
        arg0->unk50 = v0->unk18;
        arg0->unk54 = v0->unk1C;
    }
    func_1513170C();
}

void func_151BD7F4(s32 arg0) {
    s32 sp18[2];
    sp18[0] = arg0;
    *((u8 *)&sp18 + 4) = *((u8 *)arg0 + 0x3B);
    func_151494E0((s32)&sp18, 0x3B);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BD828.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BDD8C.s")

typedef struct {
    s32 unk0;
    u8  unk4;
} SubA_151BE0AC;

typedef struct {
    s32 unk0;
    u8  b4;
} ArgB_151BE0AC;

void func_151BE0AC(s32 arg0, s32 arg1, u8 arg2) {
    s32 *pp = &arg0;
    s32 t;
    if (arg2 == 0x3B) {
        t = *pp + 0x28;
        if ((*(s32 *)t == *(s32 *)arg1) ||
            (*(u8 *)(t + 4) == *(u8 *)(pp[1] + 4))) {
            func_1516972C((struct102 *)*pp);
        }
    } else {
        t = *pp + 0x28;
        func_15169850(arg1, arg2, t, t + 4, *pp);
    }
}

void func_151BE138(struct260 *arg0) {
    struct102 **p;

    p = (struct102 **)((u8 *)arg0 + 0x28);
    if (p[2] != 0) {
        func_1516972C(p[2]);
    }
    if (p[3] != 0) {
        func_1516972C(p[3]);
    }
    if (p[4] != 0) {
        func_1516972C(p[4]);
    }
    if (p[5] != 0) {
        func_1516972C(p[5]);
    }
}

extern void func_151BE138(struct260 *arg0);

void func_151BE1B8(struct260 *arg0) {
    func_151BE138(arg0);
    func_1514933C(arg0);
}

extern void func_15149368(struct260 *arg0);

void func_151BE1E4(struct260 *arg0) {
    func_151BE138(arg0);
    func_15149368(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BE210.s")

typedef struct {
    s32 unk0;
    u8 pad4[0x37];
    u8 unk3B;
} Obj151BE4B8;

typedef struct {
    Obj151BE4B8 *unk0;
    u8 unk4;
    u8 pad5[0x3B];
    f32 unk40;
    f32 unk44;
    u8 pad48[0xC];
    f32 unk54;
    u8 unk58;
} Sub151BE4B8;

s32 func_151BE4B8(void *arg0, s16 arg1) {
    Obj151BE4B8 *temp_v0;
    Sub151BE4B8 *sub;
    f32 sp20[2];

    sub = (Sub151BE4B8 *)((u8 *)arg0 + 0x110);
    temp_v0 = sub->unk0;
    if ((temp_v0->unk3B != sub->unk4) || (temp_v0->unk0 == 0)) {
        func_1516972C((struct102 *)arg0);
        return 0;
    }

    if (!(sub->unk58 & 1)) {
        return 0;
    }

    sp20[0] = sub->unk40 * sub->unk54;
    sp20[1] = sub->unk44 * sub->unk54;
    return func_1513FAB4(arg0, 0, sp20, arg1);
}

typedef struct { s32 unk0; u8 unk4; } SubA_151BE558;
typedef struct { s32 unk0; union { s32 w4; u8 b4; } u4; u8 unk8; u8 unk9; } ArgB_151BE558;

void func_151BE558(struct260 *arg0, s32 arg1, u8 arg2) {
    SubA_151BE558 *temp_v0 = (SubA_151BE558 *)((u8 *)arg0 + 0xB0);
    ArgB_151BE558 *b = (ArgB_151BE558 *)arg1;
    s32 b0;

    if (arg2 == 0x2D) {
        if (temp_v0->unk0 == b->unk0) {
            temp_v0->unk0 = b->u4.w4;
            temp_v0->unk4 = b->unk9;
        } else if (temp_v0->unk0 == b->u4.w4) {
            temp_v0->unk0 = b->unk0;
            temp_v0->unk4 = b->unk8;
            goto dummy_label_442082; dummy_label_442082: ;
        }
    } else if (arg2 == 0) {
        b0 = b->unk0;
        if ((b0 == temp_v0->unk0) || (b->u4.b4 == temp_v0->unk4)) {
            func_1516972C((struct102 *)arg0);
        }
    }
}

void func_151BE604(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x110, arg0 + 0x114, arg0);
}

struct Sub151BE644 {
    u8  pad0[0x5];
    u8  unk5;
    u8  pad6[0x4A];
    s32 unk50;
};

void func_151BE644(struct210 *arg0) {
    struct Sub151BE644 *v0 = (struct Sub151BE644 *)((u8 *)arg0 + 0x110);
    if (*(s32 *)((u8 *)arg0 + 0x160) != 0) {
        s32 v1 = v0->unk50 + 0x28;
        *(s32 *)(v1 + (v0->unk5 << 2) + 8) = 0;
    }
}

void func_151BE674(struct210 *arg0) {
    func_151BE644(arg0);
    func_1513CA6C(arg0);
}

void func_151BE6A0(struct210 *arg0) {
    func_151BE644(arg0);
    func_1513CAA0(arg0);
}

struct S4151BE6CC { s32 w[4]; };
extern struct S4151BE6CC D_800AA7A8;
extern f32 D_800AA8AC;

struct Bar151BE6CC {
    char pad48[0x48];
    f32 unk48;
};

struct Obj151BE6CC {
    char pad18[0x18];
    u8  unk18;
    char pad19[0x170 - 0x19];
    s16 unk170;
    char pad172[0x2];
    f32 unk174;
};

s32 func_151BE6CC(struct Obj151BE6CC *arg0) {
    s32 dummy;
    struct S4151BE6CC sp24;
    struct Bar151BE6CC *v1 = (struct Bar151BE6CC *)((char *)arg0 + 0x110);

    sp24 = D_800AA7A8;

    arg0->unk170 -= D_800BE9E4;
    if (arg0->unk170 < 0) {
        arg0->unk18 = sp24.w[func_150ADA20() & 3];
        arg0->unk170 = (func_150ADA20() & 7) + 3;
    }

    v1->unk48 = v1->unk48 + (arg0->unk174 - v1->unk48) * D_800AA8AC;
    return 1;
}

void func_151BE788(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x180, arg0 + 0x184, arg0);
}

typedef struct {
    u8 pad0[0x10];
    s32 unk10;
} BE7C8_elem;

typedef struct {
    u8 pad0[0x8];
    s32 *unk8;
    u8 unkC;
} BE7C8_sub;

void func_151BE7C8(struct210 *arg0) {
    BE7C8_sub *sub = (BE7C8_sub *)((u8 *)arg0 + 0x170);
    if (sub->unk8 != NULL) {
        s32 *arr = (s32 *)((u8 *)sub->unk8 + 0x28);
        ((BE7C8_elem *)&arr[sub->unkC])->unk10 = 0;
    }
}

extern void func_151BE7C8(struct210 *);
extern void func_151411A4(struct210 *);

void func_151BE7F8(struct210 *arg0) {
    func_151BE7C8(arg0);
    func_151411A4(arg0);
}

void func_151BE824(struct210 *arg0) {
    func_151BE7C8(arg0);
    func_151411C4(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BE850.s")

struct S151BEB20 {
    u8 pad0[0x54];
    f32 unk54;
    f32 unk58;
    f32 unk5C;
    u8 pad60[0x7C - 0x60];
    f32 mat[1][4][4];
    u8 padBC[0x120 - 0xBC];
    f32 unk120;
};

s32 func_151BEB20(struct S151BEB20 *arg0) {
    f32 m;

    func_150A8050(arg0->mat[D_800BE9C0], 0.0f, arg0->unk120, 0.0f);

    m = D_800AA8E0;
    arg0->mat[D_800BE9C0][3][0] = arg0->unk54;
    arg0->mat[D_800BE9C0][3][1] = arg0->unk58;
    arg0->mat[D_800BE9C0][3][2] = arg0->unk5C;

    arg0->mat[D_800BE9C0][0][0] *= m;
    arg0->mat[D_800BE9C0][0][1] *= m;
    arg0->mat[D_800BE9C0][0][2] *= m;
    arg0->mat[D_800BE9C0][1][0] *= m;
    arg0->mat[D_800BE9C0][1][1] *= m;
    arg0->mat[D_800BE9C0][1][2] *= m;
    arg0->mat[D_800BE9C0][2][0] *= m;
    arg0->mat[D_800BE9C0][2][1] *= m;
    arg0->mat[D_800BE9C0][2][2] *= m;

    return 1;
}

s32 func_151BEC94(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 *arg4) {
    *arg4 = 1;
    return arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BECB8.s")

s32 func_151BEE94(struct127 *arg0) {
    if (arg0->unk127 == 0xFF) {
        return 0;
    }
    if (arg0->interaction_state == 0) {
        return 0;
    }
    if (arg0->id == 0xFF) {
        return 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BEEE0.s")

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3F_151BF0C8;

typedef struct {
    s32 unk0;
    s32 unk4;
    Vec3F_151BF0C8 unk8;
    f32 unk14;
    f32 unk18;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    u8 unk3C;
    u8 pad3D;
    s16 unk3E;
    s16 unk40;
} Struct151BF0C8_A;

typedef struct {
    s16 unk0;
    s16 unk2;
    u8 unk4;
    u8 pad5;
    s16 unk6;
    s32 unk8;
    s32 unkC;
    s16 unk10;
    s16 unk12;
    s32 unk14;
    s32 unk18;
    u8 unk1C;
    u8 unk1D;
    u8 unk1E;
    u8 unk1F;
    u8 unk20;
    u8 unk21;
    u8 unk22;
    u8 unk23;
    u8 unk24;
    u8 unk25;
    s16 unk26;
    s16 unk28;
    s16 unk2A;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    Vec3F_151BF0C8 unk38;
    s16 unk44;
    s16 unk46;
    s16 unk48;
    s16 unk4A;
    f32 unk4C;
    f32 unk50;
    f32 unk54;
    f32 unk58;
    s32 unk5C;
    u8 unk60;
    s8 unk61;
    u8 unk62;
    u8 unk63;
    u8 unk64;
    u8 pad65[3];
    f32 unk68;
} Struct151BF0C8_B;

void func_151BF0C8(Vec3F_151BF0C8 *arg0) {
    Struct151BF0C8_A sp84;
    Struct151BF0C8_B sp18;

    sp84.unk0 = 0x18;
    sp84.unk4 = 0xA;
    sp84.unk8 = *arg0;
    sp84.unk14 = D_800AA8E8;
    sp84.unk18 = D_800AA8EC;
    sp84.unk1C = 0;
    sp84.unk1E = 0xFF;
    sp84.unk20 = -0x32;
    sp84.unk22 = 0x3C;
    sp84.unk24 = 13.0f;
    sp84.unk28 = 13.0f;
    sp84.unk2C = D_800AA8F0;
    sp84.unk30 = D_800AA8F4;
    sp84.unk34 = D_800AA8F8;
    sp84.unk38 = D_800AA8FC;
    sp84.unk3C = 3;
    sp84.unk3E = 0x41;
    sp84.unk40 = 0x1E;
    func_15150F90(&sp84, 1, 0xFF, 1);

    sp18.unk0 = 0x14;
    sp18.unk2 = 8;
    sp18.unk4 = 0x6C;
    sp18.unk6 = 0x5103;
    sp18.unk8 = 0x200005;
    sp18.unkC = 0;
    sp18.unk10 = 0x28;
    sp18.unk12 = 0x28;
    sp18.unk14 = 0;
    sp18.unk18 = 0;
    sp18.unk1F = 0xFF;
    sp18.unk1C = 0xFF;
    sp18.unk1D = 0x91;
    sp18.unk1E = 6;
    sp18.unk20 = 0xFF;
    sp18.unk21 = 0xFF;
    sp18.unk22 = 0;
    sp18.unk23 = 0x14;
    sp18.unk24 = 0xC8;
    sp18.unk25 = 0xFF;
    sp18.unk26 = 0x32;
    sp18.unk28 = 5;
    sp18.unk2A = 0x32;
    sp18.unk2C = D_800AA900;
    sp18.unk30 = 175.0f;
    sp18.unk34 = 160.0f;
    sp18.unk38 = *arg0;
    sp18.unk44 = 0;
    sp18.unk46 = -0x33;
    sp18.unk48 = 0xFF;
    sp18.unk4A = 0x50;
    sp18.unk4C = 4.0f;
    sp18.unk50 = 13.0f;
    sp18.unk54 = D_800AA904;
    sp18.unk58 = D_800AA908;
    sp18.unk5C = 0x840E07;
    sp18.unk60 = 0x10;
    sp18.unk61 = -1;
    sp18.unk62 = 8;
    sp18.unk63 = 6;
    sp18.unk64 = 1;
    sp18.unk68 = D_800AA90C;
    func_15153634(&sp18, 0xFF, 0xFF, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BF340.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BF81C.s")

void func_151BFB2C(struct260 *arg0) {
    s32 i;
    s32 v;
    s32 *p = (s32 *)((u8 *)arg0 + 0x28);

    if (p[0] != 0) {
        func_1516972C((struct102 *)p[0]);
    }
    for (i = 0; i < 2; i = (u8)(i + 1)) {
        v = p[i + 1];
        if (v != 0) {
            func_1516972C((struct102 *)v);
        }
    }
}

void func_151BFBA4(struct260 *arg0) {
    func_151BFB2C(arg0);
    func_1514933C(arg0);
}

void func_151BFBD0(struct260 *arg0) {
    func_151BFB2C(arg0);
    func_15149368(arg0);
}

void func_151BFBFC(struct102 *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 0x57) {
        func_1516972C(arg0);
    }
}
