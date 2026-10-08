#include <ultra64.h>
#define func_15048A40 func_15048A40_hdr
#include "functions.h"
#undef func_15048A40
#include "variables.h"


extern f32 func_15048A40(u8 arg0);

typedef struct {
    f32 unk0;
    u8 pad4[0xC];
    s16 unk10;
    s16 unk12;
    s16 unk14;
    u8 pad16[0x39];
    u8 unk4F;
    u8 pad50[0x10];
    f32 unk60;
    u8 pad64[0x18];
    s32 unk7C;
} Struct150C4D20;

void func_150C4D20(Struct150C4D20 *arg0) {
    f32 v;
    f32 x;
    f32 r;
    s32 t;

    x = arg0->unk0;
    v = arg0->unk60;
    if (x > 180.0f) {
        x -= 360.0f;
    }
    t = arg0->unk7C;
    t += D_800BE9E4;
    v -= x * 0.009f;
    if ((f32)t >= 256.0f) {
        t = (f32)t - 256.0f;
        func_10010F88(0xF, 0x55F0, 0, 0, 0, arg0->unk10, arg0->unk12, arg0->unk14, 500, 1000);
    }
    arg0->unk7C = t;
    r = func_15048A40(t);
    v += r * 0.1f;
    if ((arg0->unk4F & 4) == 4) {
        v += 0.1f;
    }
    v *= 0.8f;
    arg0->unk60 = v;
    arg0->unk0 += v;
    if (arg0->unk0 < 0.0f) {
        arg0->unk0 += 360.0f;
    } else if (arg0->unk0 >= 360.0f) {
        arg0->unk0 -= 360.0f;
    }
}

extern void *allocate_memory(s32, s32, s32, s32);
extern void func_1511A410(s32, void *);
extern s32 func_1510D0EC(s32, s32 *, s32, s32);
extern void func_1510D874(void *, s32, s32, s32, s32);
extern u8 D_2C1;
extern u8 D_1C0;

typedef struct {
    u8 pad0[0xA];
    s16 unkA;
    u8 padC[4];
} Struct150C4E9CKey;

typedef struct {
    s32 unk0;
    s16 unk4;
    u8 pad6[2];
    f32 unk8;
    f32 unkC;
} Struct150C4E9CState;

typedef struct {
    u8 pad0[0x16];
    u16 unk16;
    u8 pad18[4];
    s32 unk1C;
    Struct150C4E9CKey *unk20[2];
    Struct150C4E9CKey *unk28;
    u8 pad2C[0x47];
    u8 unk73;
    u8 pad74[8];
    Struct150C4E9CState *unk7C;
} Struct150C4E9C;

void func_150C4E9C(Struct150C4E9C *arg0) {
    s32 anim;
    s32 sp50;
    s32 r;
    s32 x;
    Struct150C4E9CState *p;
    s32 mode;
    s32 i;

    mode = arg0->unk73 & 3;
    if (arg0->unk7C == NULL) {
        p = arg0->unk7C = allocate_memory(0x10, 1, 0, 0);
        func_1511A410(arg0->unk1C, p);
        p->unk4 = arg0->unk28->unkA;
        p->unk8 = 0.0f;
        p->unkC = 0.0f;
    } else {
        p = arg0->unk7C;
    }
    if (mode == 0 || mode == 2) {
        anim = (s32)&D_2C1;
    } else {
        anim = (s32)&D_1C0;
    }
    if (mode == 0 || mode == 3) {
        p->unk8 = 0.0f;
        p->unkC = 0.0f;
    } else if (mode == 2) {
        if (p->unk8 < 300.0f) {
            p->unk8 += 25.0f * D_800BE9E4;
        } else {
            p->unk8 = 300.0f;
        }
    } else if (mode == 1) {
        s32 a;
        s32 b;

        if (100.0f < p->unk8) {
            p->unk8 -= 25.0f * D_800BE9E4;
        } else {
            p->unk8 = 100.0f;
            a = arg0->unk20[D_800BE9C0]->unkA % 0x400;
            while (a < 0) {
                a += 0x400;
            }
            b = p->unk4 % 0x400;
            while (b < 0) {
                b += 0x400;
            }
            if (a >= b && (a - p->unk8 <= b)) {
                p->unk8 = a - b;
                arg0->unk73 &= ~3;
                arg0->unk73 |= 3;
            }
        }
    }
    if (p->unk8) {
        for (i = 0; i < arg0->unk16; i++) {
            arg0->unk20[D_800BE9C0][i].unkA -= p->unk8;
        }
    }
    if (arg0->unk20[D_800BE9C0]->unkA < -0x2800) {
        for (i = 0; i < arg0->unk16; i++) {
            arg0->unk20[D_800BE9C0][i].unkA += 0x2800;
        }
    }
    x = 0;
    r = func_1510D0EC(anim, &sp50, 3, 0);
    if (p->unk0 != 0) {
        x = sp50 + r - 0x200;
    }
    func_1510D874(arg0, r, x, 4, 5);
}

extern s32 *D_800D98D0[];

void func_150C522C(void) {
    s32 i;
    s32 v;

    i = 0;
    do {
        v = (s32)D_800D98D0[i];
        if (v != 0) {
            func_1516972C((struct102 *)v);
        }
        i++;
        D_800D98D0[i - 1] = 0;
    } while ((s32 **)&D_800D98E0 != &D_800D98D0[i]);
}

extern u8 D_800C35E8;

s32 func_150C5280(void) {
    u8 v0;
    if (D_800C35EA == 1) {
        v0 = D_800C35E8;
        if (v0 == 0xB || v0 == 0xC || v0 == 0xD) {
            return 1;
        }
    }
    return 0;
}

extern s32 func_150C5280(void);
extern s32 (*D_8008ADA8)(s32);

s32 func_150C52CC(s32 arg0) {
    if (func_150C5280()) {
        return 0;
    }
    return D_8008ADA8(arg0);
}

s32 func_150C5310(s32 *arg0) {
    if (func_150C5280()) {
        arg0[0x18] |= 0x20000;
    } else {
        arg0[0x18] &= ~0x20000;
    }
    return 1;
}
