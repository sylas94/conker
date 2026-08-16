#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_800AA97C;
extern f32 D_800AA980;
extern f32 D_800AA984;
extern f32 D_800AA988;
extern f32 D_800AA98C;
extern f32 D_800AA990;
extern f32 D_800AA994;
extern f32 D_800AA998;

void func_151541B8(void *, f32, s32, f32, f32, u8, s32);

typedef struct {
    char pad_0[0x4];
    u8 field_0x04;
    char pad_1[0x1CF];
    s32 field_0x1D4;
} GameObjectMatrixSource;

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ u8  pad08[0xC];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ s16 unk44;
    /* 0x46 */ s16 unk46;
    /* 0x48 */ s16 unk48;
    /* 0x4A */ s16 unk4A;
    /* 0x4C */ s16 unk4C;
    /* 0x4E */ s16 unk4E;
    /* 0x50 */ s8  unk50;
} Struct151BFC40;

void func_151BFC40(void *arg0, f32 *arg1) {
    Struct151BFC40 *temp = arg0;

    temp->unk00 = 3;
    temp->unk04 = 4 >> ((D_80082FA0 >= 2) ? 1 : 0);
    arg1[0] = 494.0f;
    temp->unk14 = D_800AA97C;
    temp->unk18 = D_800AA980;
    temp->unk1C = 45.0f;
    temp->unk20 = 53.0f;
    temp->unk24 = 203.0f;
    temp->unk28 = 414.0f;
    temp->unk2C = 7;
    temp->unk30 = 3 >> ((D_80082FA0 >= 2 || D_8008FD8C >= 8) ? 1 : 0);
    temp->unk34 = 15.0f;
    temp->unk38 = D_800AA984;
    temp->unk3C = D_800AA988;
    temp->unk40 = D_800AA98C;
    temp->unk44 = 25;
    temp->unk46 = 15;
    temp->unk48 = 100;
    temp->unk4A = 100;
    temp->unk4C = 12;
    temp->unk4E = 20;

    if (D_80082FA0 < 2) {
        if (D_8008FD8C < 8) {
            goto zero;
        }
    }

    temp->unk50 = -1;
    return;

zero:
    temp->unk50 = 0;
}

struct Vec3F151BFDA0 { f32 x; f32 y; f32 z; };
typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ struct Vec3F151BFDA0 unk10;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ s16 unk4C;
    /* 0x4E */ s16 unk4E;
    /* 0x50 */ s16 unk50;
    /* 0x52 */ s16 unk52;
    /* 0x54 */ s16 unk54;
    /* 0x56 */ s16 unk56;
    /* 0x58 */ s8 unk58;
} Struct151C0098;
struct Local151BFDA0 {
    struct Vec3F151BFDA0 unk0;  /* 0x00 (sp 0x24) */
    f32 unkC;                   /* 0x0C (sp 0x30) */
    u8 unk10[0x8];              /* 0x10 (sp 0x34) */
    struct Vec3F151BFDA0 unk18; /* 0x18 (sp 0x3C) */
    u8 unk24[0x40];             /* 0x24 (sp 0x48) */
};
void func_151C0418(f32 *, u8, s32);
void func_151C04F8(f32 *, u8, s32);
void func_151C05A4(void *, u8, s32);
void func_151C05F0(void *, u8, s32);
void func_151BFC40(void *, f32 *);
void func_1514FB98(void *, u8, s32);
void func_1514FCE8(Struct151C0098 *, u8, s32);
void func_1504715C(void *, s32);
s32 func_15046C80(f32 *, s32, f32, void *);
void func_151C0360(void *, void *, s32, s32);
void func_151C0644(void *, u8, s32);

void func_151BFDA0(struct Vec3F151BFDA0 *arg0, struct Vec3F151BFDA0 *arg1, u8 arg2, u8 arg3, s32 arg4) {
    struct Local151BFDA0 sp24;

    func_151C0418((f32 *)arg0, arg3, arg4);
    func_151C04F8((f32 *)arg0, arg3, arg4);
    func_151C05A4(arg0, arg3, arg4);
    func_151C05F0(arg0, arg3, arg4);
    if (arg2 != 0) {
        sp24.unk0.x = -arg1->x;
        sp24.unk0.y = -arg1->y;
        sp24.unk0.z = -arg1->z;
        func_151BFC40(&sp24.unk10, &sp24.unkC);
        sp24.unk18 = *arg0;
        func_1514FB98(&sp24, arg3, arg4);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151BFE84.s")

void func_151C0098(struct Vec3F151BFDA0 *arg0, s32 arg1, volatile u8 arg2, u8 arg3, s32 arg4) {
    Struct151C0098 sp64;
    f32 sp58[3];
    f32 sp34[9];
    f32 sp28[3];

    func_151C0418((f32 *)arg0, arg3, arg4);
    func_151C04F8((f32 *)arg0, arg3, arg4);
    func_151C05A4(arg0, arg3, arg4);
    func_151C05F0(arg0, arg3, arg4);

    if (arg2 != 0) {
        sp64.unk00 = 0;
        sp64.unk02 = 0xFF;
        sp64.unk04 = -0x40;
        sp64.unk06 = 0x47;
        sp64.unk08 = 6;
        sp64.unk0C = 4;
        sp64.unk10 = *arg0;
        sp64.unk1C = 23.0f;
        sp64.unk20 = 30.0f;
        sp64.unk24 = 45.0f;
        sp64.unk28 = 53.0f;
        sp64.unk2C = 203.0f;
        sp64.unk30 = 414.0f;
        sp64.unk34 = 7;
        sp64.unk38 = 3;
        sp64.unk3C = 15.0f;
        sp64.unk40 = D_800AA990;
        sp64.unk44 = D_800AA994;
        sp64.unk48 = D_800AA998;
        sp64.unk4C = 25;
        sp64.unk4E = 15;
        sp64.unk50 = 100;
        sp64.unk52 = 100;
        sp64.unk54 = 12;
        sp64.unk56 = 20;
        sp64.unk58 = 0;
        func_1514FCE8(&sp64, arg3, arg4);
    }

    if (arg2 != 0 && arg1 != 0) {
        sp58[0] = arg0->x;
        sp58[1] = arg0->y + 100.0f;
        sp58[2] = arg0->z;
        func_1504715C(sp34, arg1);
        if (func_15046C80(sp58, 0, arg0->y - 1000.0f, sp34) != 0) {
            sp28[0] = sp58[0];
            sp28[1] = sp34[0];
            sp28[2] = sp58[2];
            func_151C0360(&sp34[1], sp28, arg3 & 0xFF, arg4);
            func_151C0644(arg0, arg3, arg4);
        }
    }
}

s32 func_151C02E4(s32 arg0, s32 arg1, s32 arg2, s32 *arg3) {
    u8 i;

    for (i = 0; i < arg2; i++) {
        if (arg0 == arg3[i]) {
            return 0;
        }
    }
    if (arg0 == arg1) {
        return 0;
    }
    if (*(s32 *)arg0 == 0) {
        return 0;
    }
    if (*(u8 *)(arg0 + 4) == 0xFF) {
        return 0;
    }
    return 1;
}

void func_150E7FEC(f32, s32, void *, void *, s32, s32, s32, s32, s32, s32, s32, s32);

void func_151C0360(void *arg0, void *arg1, s32 arg2, s32 arg3) {
    union { u32 w; f64 _a; } r1;
    f32 sp3C;
    u32 r2;

    sp3C = func_150ADA68();
    r1.w = func_150ADA20();
    r2 = func_150ADA20();
    func_150E7FEC(sp3C * 75.0f + 75.0f, (u8)((r1.w % 56U) + 200), arg0, arg1,
                  ((u32)r2 % 205U) + 299, 1, 1, 0, 0, 0, (u8)arg2, 0);
}

void func_151602C0(Header *, Header2 *, s32, s32, s32, s32, s32, s32, s32, u8, s32);

void func_151C0418(f32 *arg0, u8 arg1, s32 arg2) {
    Header header;
    Header2 header2;

    header.unk0 = 3;
    header.unk1 = -1;
    header.unk2 = (func_150ADA20() % 0xBU) + 0x14;
    header.unk4 = 0;

    header2.unk0 = (s32) arg0[0];
    header2.unk4 = (s32) arg0[1];
    header2.unk8 = (s32) arg0[2];

    func_151602C0(&header, &header2, (func_150ADA20() % 0x79U) + 0x3C, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, arg1, arg2);
}

void func_151C04F8(f32 *arg0, u8 arg1, s32 arg2) {
    union { f32 f; f64 _a; } temp_f0;
    u32 temp_a;

    temp_f0.f = func_150ADA68();
    temp_a = func_150ADA20();
    func_151541B8(arg0, temp_f0.f * 4.0f + 14.0f, 0x3F974EB9,
                  (f32)(u32)((temp_a % 0x38U) + 0xC8), 0.0f, arg1, arg2);
}

void func_151D5334(void *, f32, f32, f32, s32, u8, s32);

void func_151C05A4(void *arg0, u8 arg1, s32 arg2) {
    func_151D5334(arg0, 800.0f, 2000.0f, 0.0005f, 5, arg1, arg2);
}

void func_151C05F0(void *arg0, u8 arg1, s32 arg2) {
    func_151D5404(arg0, 800.0f, 2000.0f, 0.0005f, 0xF, 0x14, arg1, arg2);
}

void func_150E83AC(void *, s16, u8, s32);

void func_151C0644(void *arg0, u8 arg1, s32 arg2) {
    func_150E83AC(arg0, (s16)((u32)func_150ADA20() % 0x3E + 0x78), arg1, arg2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C0698.s")

typedef struct {
    u8 pad0[0x38];
    f32 unk38;
    f32 unk3C;
    f32 unk40;
} Struct151C110CInner;

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    u8 pad8[0x10];
    Struct151C110CInner *unk18;
} Struct151C110C;

s32 func_151C110C(Struct151C110C *arg0, s32 arg1, void **arg2, s32 arg3, s32 arg4, s32 arg5, s16 *arg6) {
    Struct151C110CInner *temp_v1;
    s16 *temp_t3;

    temp_v1 = arg0->unk18;
    temp_t3 = arg6;
    if (temp_v1 != NULL) {
        if (*arg2 != NULL) {
            arg0->unk2 = temp_v1->unk38;
            arg0->unk4 = temp_v1->unk3C;
            arg0->unk6 = temp_v1->unk40;
            return 0;
        }
    }

    *temp_t3 = 0;
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C1180.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C1570.s")

void func_151C1570(void *);
void func_15132570(void *);

void func_151C15FC(void *arg0) {
    func_151C1570(arg0);
    func_15132570(arg0);
}

void func_1513259C(void *);

void func_151C1628(void *arg0) {
    func_151C1570(arg0);
    func_1513259C(arg0);
}

void func_151D40D4(struct Vec3F151BFDA0 *, s32, s32, s32, s32, s32, s32, s32);
void func_151D42E8(struct Vec3F151BFDA0 *, s32, s32, s32, s32);

void func_151C1654(struct Vec3F151BFDA0 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    void (*callback)(s32, s32, s32);
    u8 temp;

    callback = (void (*)(s32, s32, s32)) D_800E0934;
    if (callback != NULL) {
        callback((s32)arg0->x, (s32)arg0->y, (s32)arg0->z);
    }

    temp = (u8)arg3;
    if (temp != 0) {
        switch (temp) {
        case 1:
            func_151D42E8(arg0, arg1, arg2, arg4, 0x24);
            return;
        case 2:
            func_151D42E8(arg0, arg1, arg2, arg4, 0x25);
            return;
        case 3:
            func_151D40D4(arg0, arg1, arg2, 0, arg4, 0x16, 0x26, 0);
            return;
        }
    }

    func_151D40D4(arg0, arg1, arg2, 0, arg4, 0x16, 0x15, 0);
}

void func_15143134(void *, s32, s32);
struct S800AA958 { s32 unk0; s32 unk4; s32 unk8; };
extern u8 D_800AA954[];
extern struct S800AA958 D_800AA958[];

void func_151C1798(GameObjectMatrixSource *arg0, s32 arg1) {
    s32 index;

    switch (arg0->field_0x04) {
    case 0x77:
        index = 1;
        break;
    case 0x28:
        index = 2;
        break;
    default:
        index = 0;
        break;
    }
    func_15143134(&D_800AA958[index], arg1,
                  arg0->field_0x1D4 + (D_800AA954[index] << 6));
}

void func_151C1814(s32 *arg0, s32 *arg1, u8 arg2) {
    s32 *v0 = (s32 *)((u8 *)arg0 + 0x170);
    if (arg2 == 0x2D) {
        if (arg1[0] == v0[0x1B]) {
            v0[0x1B] = arg1[1];
        } else if (arg1[1] == v0[0x1B]) {
            v0[0x1B] = arg1[0];
        }
    }
}

void func_151C1860(f32 *arg0, u8 arg1, s32 arg2) {
    Header header;
    Header2 header2;

    header.unk0 = 3;
    header.unk1 = -1;
    header.unk2 = (func_150ADA20() % 5U) + 5;
    header.unk4 = 0;

    header2.unk0 = (s32) arg0[0];
    header2.unk4 = (s32) arg0[1];
    header2.unk8 = (s32) arg0[2];

    func_151602C0(&header, &header2, (func_150ADA20() % 0xBU) + 5, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, arg1, arg2);
}

s32 func_151C02E4(s32, s32, s32, s32 *);

typedef struct {
    s32 unk0;
    s32 unk4[1];
} Struct151C1940;

s32 func_151C1940(s32 arg0, s32 arg1, Struct151C1940 *arg2) {
    return func_151C02E4(arg0, arg1, arg2->unk0, arg2->unk4);
}

typedef struct {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
} Vec151C196C;

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ Vec151C196C unk08;
    /* 0x14 */ Vec151C196C unk14;
    /* 0x20 */ Vec151C196C unk20;
    /* 0x2C */ Vec151C196C unk2C;
    /* 0x38 */ Vec151C196C unk38;
    /* 0x44 */ u8  pad44[0x12];
    /* 0x56 */ s16 unk56;
    /* 0x58 */ u8  unk58;
    /* 0x59 */ u8  unk59;
    /* 0x5A */ u8  unk5A;
    /* 0x5B */ u8  pad5B;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
} Ray151C196C;

void func_151C1D5C(s32, Vec151C196C *, Vec151C196C *, Ray151C196C *, f32, s32, s32, s32, s32,
                   s32, s32, s32, s32, s32);
s32 func_15145128(Vec151C196C *, Vec151C196C *, f32 *, f32 *);

s32 func_151C196C(Ray151C196C *arg0, Vec151C196C *arg1, Vec151C196C *arg2, Vec151C196C *arg3,
                  Vec151C196C *arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9,
                  s32 arg10) {
    u8 trace;
    u8 hit;
    Vec151C196C *src;

    trace = 1;
    hit = 0;

    if ((arg3 != NULL) && (arg4 != NULL)) {
        arg0->unk2C = *arg3;
        arg0->unk38 = *arg4;
        func_151C1D5C(arg5, &arg0->unk2C, &arg0->unk38, arg0, 0.0f, 0, 0, 1, 3, arg6, arg7,
                      arg8, arg9, arg10);

        if (arg0->unk59 == 0) {
            if ((arg1->x != arg0->unk2C.x) || (arg1->y != arg0->unk2C.y) ||
                (arg1->z != arg0->unk2C.z)) {
                arg0->unk2C = *arg1;
                arg0->unk38 = *arg4;
            } else {
                trace = 0;
            }
        } else {
            if ((arg1->x != arg0->unk2C.x) || (arg1->y != arg0->unk2C.y) ||
                (arg1->z != arg0->unk2C.z)) {
                arg0->unk2C = *arg1;
                arg0->unk38.x = arg0->unk08.x - arg1->x;
                arg0->unk38.y = arg0->unk08.y - arg1->y;
                arg0->unk38.z = arg0->unk08.z - arg1->z;
                if (func_15145128(&arg0->unk38, &arg0->unk38, &arg0->unk04, NULL) == 0) {
                    return 0;
                }
            }
        }
    } else {
        arg0->unk2C = *arg1;
        arg0->unk38 = *arg2;
    }

    if (trace != 0) {
        func_151C1D5C(arg5, &arg0->unk2C, &arg0->unk38, arg0, 0.0f, 0, 1, 1, 3, arg6, arg7,
                      arg8, arg9, arg10);
        if (arg0->unk59 != 0) {
            hit = 1;
        }
    }

    if (hit == 0) {
        arg0->unk00 = 0;
        arg0->unk04 = 5000.0f;
        arg0->unk2C = *arg1;
        if (arg4 != NULL) {
            src = arg4;
        } else {
            src = arg2;
        }
        arg0->unk38 = *src;
        arg0->unk08.x = arg0->unk2C.x + arg0->unk38.x * 5000.0f;
        arg0->unk08.y = arg0->unk2C.y + arg0->unk38.y * 5000.0f;
        arg0->unk08.z = arg0->unk2C.z + arg0->unk38.z * 5000.0f;
        arg0->unk14 = arg0->unk08;
        arg0->unk20 = arg0->unk08;
        arg0->unk56 = 0;
        arg0->unk58 = 0;
        arg0->unk59 = 0;
        arg0->unk5A = 0;
        arg0->unk5C = 0;
        arg0->unk60 = 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C1D5C.s")

struct sp18_151C1FB8 {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ u8 unk4;
    /* 0x5 */ u8 unk5;
    /* 0x6 */ s8 unk6;
    /* 0x7 */ u8 unk7;
};

extern void func_151D8868(void *, s32, s32, s32);

void func_151C1FB8(struct127 *arg0) {
    struct sp18_151C1FB8 sp18;

    if (arg0->camera != 0) {
        sp18.unk0 = 1;
        sp18.unk2 = (func_150ADA20() & 7) + 0xD;
        sp18.unk5 = 1 << arg0->camera->unk23D;
        sp18.unk4 = (func_150ADA20() % 3U) + 6;
        sp18.unk6 = -1;
        func_151D8868(&sp18, 0, 0xFF, 1);
    }
}
