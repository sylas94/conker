#include <ultra64.h>

#define func_1513D524 func_1513D524_void_proto
#define func_15169260 func_15169260_s32
#include "functions.h"
#undef func_1513D524
#undef func_15169260
#include "variables.h"

extern void *func_1513D524(s32, u8, u8, u8, u8, u8, s32, u8, s32);
extern s32 D_800DC9F0;

typedef void (*Callback_151416E8)(void *, s32, u8);
extern Callback_151416E8 D_8008A02C[];
void func_150A7960(f32 *arg0, f32 arg1, s32 arg2, f32 arg3, f32 *arg4, f32 *arg5, f32 *arg6);

struct conk14182C_pos {
    f32 x;
    f32 y;
    f32 z;
};

struct conk14182C {
    u8 pad0[0x34];
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    f32 unk44;
    f32 unk48;
};

struct conkMotionSample {
    f32 field_0x0;
    u8 pad_0[0x4];
    f32 field_0x8;
};

struct conkMotionControl {
    u8 pad_0[0x170];
    s32 field_0x170;
    f32 field_0x174;
    struct conkMotionSample *field_0x178;
    struct conk14182C_pos field_0x17C;
};


void *func_151407D0(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s8 arg7, u8 arg8, s32 arg9) {
    void *ret;
    void *dst;

    *(u8 *)((s32)arg2 + 1) = 3;
    *(s32 *)((s32)arg2 + 0x40) |= 0x40400000;
    ret = func_1513D524((s32)arg2, arg3, arg4, arg5, 1, arg6, arg1, arg8, arg9);
    if (ret != NULL) {
        dst = (void *)((s32)ret + 0x110);
        memcpy(dst, arg0, arg1);
        *(s8 *)((s32)dst + 0x59) = arg7;
        *(s32 *)((s32)dst + 0x44) = 0;
store_done_151407D0:
        ;
    } else {
        return NULL;
    }
    if (ret == NULL) {
    } else {
        D_800DC9F0 += 1;
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_151408A4.s")

void func_151411A4(struct210 *arg0) {
    func_1513CA6C(arg0);
}

void func_151411C4(struct210 *arg0) {
    func_1513CAA0(arg0);
}

extern s32 D_800DC9F0;
extern void (*D_80089F9C[])(void *);
void func_1517E134(void *);

struct conk1411E4 { u8 pad0[0x154]; void *unk154; u8 pad158[0x10]; u8 unk168; };

void func_151411E4(struct conk1411E4 *arg0) {
    void **pp = &arg0->unk154;

    if (*pp != 0) {
        func_1517E134(*pp);
    }
    D_800DC9F0 -= 1;
    D_80089F9C[arg0->unk168](arg0);
}

extern s32 D_800DC9F0;
extern void (*D_80089FE4[])(void *);

void func_15141250(void *arg0) {
    s32 **pp = (s32 **)((u8 *)arg0 + 0x154);
    if (*pp != 0) {
        func_1517E134(*pp);
    }
    D_800DC9F0 -= 1;
    D_80089FE4[*(u8 *)((u8 *)arg0 + 0x168)](arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_151412BC.s")

struct conk1514143C_vec {
    f32 x;
    f32 y;
    f32 z;
};

struct conk1514143C_sub {
    u8 pad0[0x44];
    struct conk1514143C_vec *unk44;
};

// permuter MATCHED (was best 120): s32 return type (vs void) makes IDO hoist the
// `addiu a0+0x110` correctly. Byte-perfect; keep the s32 return.
s32 func_1514143C(void *arg0) {
    struct conk1514143C_sub *s = (struct conk1514143C_sub *)((u8 *)arg0 + 0x110);
    if (s->unk44 != NULL) {
        s->unk44->x = *(f32 *)((u8 *)arg0 + 0x34);
        s->unk44->y = *(f32 *)((u8 *)arg0 + 0x38);
        s->unk44->z = *(f32 *)((u8 *)arg0 + 0x3C);
    }
}

extern f32 D_800BE9A4;

struct conk141478b {
    f32 field_0x0;
    f32 field_0x4;
    f32 field_0x8;
    f32 field_0xC;
    f32 field_0x10;
    f32 field_0x14;
    f32 field_0x18;
};

struct conk141478a {
    u8 pad_0[0x48];
    f32 field_0x48;
};

struct conk141478 {
    u8 pad_0[0x110];
    struct conk141478a field_0x110;
    u8 pad_1[0x14];
    struct conk141478b field_0x170;
};

s32 func_15141478(struct conk141478 *arg0) {
    struct conk141478b *v1;
    struct conk141478a *a0;

    a0 = &arg0->field_0x110;
    v1 = &arg0->field_0x170;
    v1->field_0x10 -= D_800BE9A4;
    if (v1->field_0x10 < 0.0f) {
        v1->field_0x10 = func_150ADA68() * v1->field_0x14;
        if (func_150ADA20() & 3) {
            v1->field_0xC = func_150ADA68() * (v1->field_0x0 - v1->field_0x4) + v1->field_0x4;
        } else {
            v1->field_0xC = func_150ADA68() * (v1->field_0x8 - v1->field_0x0) + v1->field_0x0;
        }
    }
    a0->field_0x48 = a0->field_0x48 + (v1->field_0xC - a0->field_0x48) * v1->field_0x18;
    return 1;
}

s32 func_15141564(struct conk141478 *arg0) {
    f32 *v1 = &arg0->field_0x170.field_0x0;
    f32 *p;

    arg0->field_0x110.field_0x48 = v1[1] * sinf(arg0->field_0x170.field_0x8) + v1[0];
    p = &v1[2];
    *p = v1[3] * D_800BE9A4 + *p;
    *p = func_15144B68(*p);
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_151415D4.s")

void func_151416E8(void *arg0, s32 arg1, s32 arg2) {
    Callback_151416E8 *callbacks;
    u8 *v1;

    callbacks = D_8008A02C;
    if (((Callback_151416E8 volatile *)callbacks)[*(volatile u8 *)((u8 *)arg0 + 0x168)] != 0) {
        callbacks[*(volatile u8 *)((u8 *)arg0 + 0x168)](arg0, arg1, (u8)arg2);
    }

    v1 = (u8 *)arg0 + 0x110;
    switch ((u8)arg2) {
    case 0x22:
    case 0x24:
    case 0x25:
        if (*(u8 *)arg1 == v1[0x58]) {
            switch ((u8)arg2) {
            case 0x22:
                func_1516972C((struct102 *)arg0);
                break;
            case 0x24:
                ((s8 *)v1)[0x59] = -1;
                break;
            case 0x25:
                v1[0x59] = 2;
                break;
            }
        }
        break;
    }
}

struct Data_151417C4 {
    s32 unk0;
    s32 unk4;
};
void func_15169260(struct Data_151417C4 *, s32, u8 *, u8);

void func_151417C4(u8 arg0, u8 arg1) {
    u8 sp24[4];
    struct Data_151417C4 sp1C;

    sp1C = *(struct Data_151417C4 *)D_8008A074;
    sp24[0] = arg0;
    func_15169260(&sp1C, 2, sp24, arg1);
}

s32 func_15141818(s32 arg0, s32 arg1) {
    return 0;
}

f32 func_1514182C(void *arg0, void *arg1, s32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    register f32 temp_f14;
    register f32 temp_f16;
    register f32 temp_f18;
    f32 sp34[4][4];

    func_150A8050(sp34, arg4, 0.0f, arg5);
    sp34[3][0] = ((struct conk14182C_pos *)arg1)->x;
    sp34[3][1] = ((struct conk14182C_pos *)arg1)->y;
    sp34[3][2] = ((struct conk14182C_pos *)arg1)->z;
    func_150A7960(&sp34[0][0], 0.0f, arg2, 0.0f, &((struct conk14182C *)arg0)->unk34, &((struct conk14182C *)arg0)->unk38, &((struct conk14182C *)arg0)->unk3C);
    temp_f14 = (((struct conk14182C *)arg0)->unk34 - ((struct conk14182C_pos *)arg1)->x) * arg3;
    temp_f16 = (((struct conk14182C *)arg0)->unk38 - ((struct conk14182C_pos *)arg1)->y) * arg3;
    temp_f18 = (((struct conk14182C *)arg0)->unk3C - ((struct conk14182C_pos *)arg1)->z) * arg3;
    ((struct conk14182C *)arg0)->unk40 = ((struct conk14182C *)arg0)->unk34 + (temp_f14 * 500.0f);
    ((struct conk14182C *)arg0)->unk44 = ((struct conk14182C *)arg0)->unk38 + (temp_f16 * 500.0f);
    ((struct conk14182C *)arg0)->unk48 = ((struct conk14182C *)arg0)->unk3C + (temp_f18 * 500.0f);
}
// f32 func_1514182C(void *arg0, void *arg1, s32 arg2, f32 arg3, s32 arg4, s32 arg5) {
//     f32 sp6C;
//     f32 sp68;
//     f32 sp64;
//     ? sp34;
//     f32 temp_f0;
//     f32 temp_f12;
//     f32 temp_f2;
//
//     func_150A8050(&sp34, arg4, 0, arg5);
//     sp64 = arg1->unk0;
//     sp68 = arg1->unk4;
//     sp6C = arg1->unk8;
//     func_150A7960(&sp34, 0, arg2, 0, arg0 + 0x34, arg0 + 0x38, arg0 + 0x3C);
//     temp_f0 = arg0->unk34;
//     temp_f2 = arg0->unk38;
//     temp_f12 = arg0->unk3C;
//     arg0->unk40 = (f32) (temp_f0 + ((temp_f0 - arg1->unk0) * arg3 * 500.0f));
//     arg0->unk44 = (f32) (temp_f2 + ((temp_f2 - arg1->unk4) * arg3 * 500.0f));
//     arg0->unk48 = (f32) (temp_f12 + ((temp_f12 - arg1->unk8) * arg3 * 500.0f));
//     return temp_f0;
// }

extern f32 func_1514182C(void *, void *, s32, f32, f32, f32);

s32 func_15141928(struct conkMotionControl *arg0) {
    struct conkMotionSample *temp_v0;

    temp_v0 = arg0->field_0x178;
    func_1514182C(arg0, &arg0->field_0x17C, arg0->field_0x170, arg0->field_0x174, temp_v0->field_0x0, temp_v0->field_0x8);
    return 1;
}
// s32 func_15141928(void *arg0) {
//     void *temp_v0 = arg0->unk178;
//     func_1514182C(arg0, arg0->unk17C, arg0->unk170, arg0->unk174, temp_v0->unk0, temp_v0->unk8);
//     return 1;
// }
