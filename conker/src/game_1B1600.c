#include <ultra64.h>
#include "functions.h"
#include "variables.h"

struct vtx151857DC;
extern struct vtx151857DC *(*D_8008D498[])(struct vtx151857DC *, struct vtx151857DC *, struct vtx151857DC *);
extern s32 (*D_8008D4C0[])(struct vtx151857DC *);

extern f32 D_800D3688;
extern s32 D_800DE01C;
extern s32 D_800DE020;
extern s32 D_800DE024;
extern s32 D_800DE030;
extern s32 D_800DE034;
extern s32 D_800DE038;
extern f32 D_800DE03C;
extern u8 D_800DE040;
extern u8 D_800DE041;

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15184150.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15184368.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15184DF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15184FA4.s")

struct vtx151857DC {
    f32 x;       /* 0x0 */
    f32 y;       /* 0x4 */
    f32 z;       /* 0x8 */
    s16 unkC;    /* 0xC */
    s16 unkE;    /* 0xE */
    s16 unk10;   /* 0x10 */
};

struct vtx151857DC *func_15185454(struct vtx151857DC *a0, struct vtx151857DC *a1, struct vtx151857DC *a2) {
    f32 t;
    f32 y;

    t = (a0->z - a0->y) / ((a1->y - a0->y) - (a1->z - a0->z));
    a2->x = a0->x + (a1->x - a0->x) * t;
    y = a0->y + (a1->y - a0->y) * t;
    a2->z = y;
    a2->y = y;
    a2->unkC = (s16)((f32)a0->unkC + (f32)(a1->unkC - a0->unkC) * t);
    a2->unkE = (s16)((f32)a0->unkE + (f32)(a1->unkE - a0->unkE) * t);
    a2->unk10 = (s16)((f32)a0->unk10 + (f32)(a1->unk10 - a0->unk10) * t);
    return a2 + 1;
}

s32 func_15185554(f32 *arg0) {
    return arg0[2] < arg0[1];
}

struct vtx151857DC *func_1518557C(struct vtx151857DC *a0, struct vtx151857DC *a1, struct vtx151857DC *a2) {
    f32 t;

    t = (a0->z + a0->x) / ((a0->x - a1->x) + (a0->z - a1->z));
    a2->x = a0->x + (a1->x - a0->x) * t;
    a2->y = a0->y + (a1->y - a0->y) * t;
    a2->z = -a2->x;
    a2->unkC = (s16)((f32)a0->unkC + (f32)(a1->unkC - a0->unkC) * t);
    a2->unkE = (s16)((f32)a0->unkE + (f32)(a1->unkE - a0->unkE) * t);
    a2->unk10 = (s16)((f32)a0->unk10 + (f32)(a1->unk10 - a0->unk10) * t);
    return a2 + 1;
}

s32 func_1518567C(f32 *arg0) {
    return arg0[0] < -arg0[2];
}

struct vtx151856A8 {
    f32 x;
    f32 y;
    f32 z;
    s16 unkC;
    s16 unkE;
    s16 unk10;
};

struct vtx151856A8 *func_151856A8(struct vtx151856A8 *a0, struct vtx151856A8 *a1, struct vtx151856A8 *a2) {
    f32 t;

    t = (a0->z + a0->y) / ((a0->y - a1->y) + (a0->z - a1->z));
    a2->x = a0->x + (a1->x - a0->x) * t;
    a2->y = a0->y + (a1->y - a0->y) * t;
    a2->z = -a2->y;
    a2->unkC = (s16)((f32)a0->unkC + (f32)(a1->unkC - a0->unkC) * t);
    a2->unkE = (s16)((f32)a0->unkE + (f32)(a1->unkE - a0->unkE) * t);
    a2->unk10 = (s16)((f32)a0->unk10 + (f32)(a1->unk10 - a0->unk10) * t);
    return a2 + 1;
}

s32 func_151857B0(f32 *arg0) {
    return arg0[1] < -arg0[2];
}

struct vtx151857DC *func_151857DC(struct vtx151857DC *a0, struct vtx151857DC *a1, struct vtx151857DC *a2) {
    f32 t;

    t = (a0->z - a0->x) / ((a1->x - a0->x) - (a1->z - a0->z));
    a2->x = a0->x + (a1->x - a0->x) * t;
    a2->y = a0->y + (a1->y - a0->y) * t;
    a2->z = a2->x;
    a2->unkC = (s16)((f32)a0->unkC + (f32)(a1->unkC - a0->unkC) * t);
    a2->unkE = (s16)((f32)a0->unkE + (f32)(a1->unkE - a0->unkE) * t);
    a2->unk10 = (s16)((f32)a0->unk10 + (f32)(a1->unk10 - a0->unk10) * t);
    return a2 + 1;
}

s32 func_151858D4(f32 *arg0) {
    return arg0[2] < arg0[0];
}

struct vtx151857DC *func_151858FC(struct vtx151857DC *a0, struct vtx151857DC *a1, struct vtx151857DC *a2) {
    f32 t;

    t = (D_800D3688 - a0->z) / (a1->z - a0->z);
    a2->x = a0->x + (a1->x - a0->x) * t;
    a2->y = a0->y + (a1->y - a0->y) * t;
    a2->z = D_800D3688;
    a2->unkC = (s16)((f32)a0->unkC + (f32)(a1->unkC - a0->unkC) * t);
    a2->unkE = (s16)((f32)a0->unkE + (f32)(a1->unkE - a0->unkE) * t);
    a2->unk10 = (s16)((f32)a0->unk10 + (f32)(a1->unk10 - a0->unk10) * t);
    return a2 + 1;
}

extern f32 D_800D3688;

s32 func_151859FC(f32 *arg0) {
    return D_800D3688 < arg0[2];
}

extern f32 D_800D368C;

struct vtx151857DC *func_15185A28(struct vtx151857DC *a0, struct vtx151857DC *a1, struct vtx151857DC *a2) {
    f32 t;

    t = (D_800D368C - a0->z) / (a1->z - a0->z);
    a2->x = a0->x + (a1->x - a0->x) * t;
    a2->y = a0->y + (a1->y - a0->y) * t;
    a2->z = D_800D368C;
    a2->unkC = (s16)((f32)a0->unkC + (f32)(a1->unkC - a0->unkC) * t);
    a2->unkE = (s16)((f32)a0->unkE + (f32)(a1->unkE - a0->unkE) * t);
    a2->unk10 = (s16)((f32)a0->unk10 + (f32)(a1->unk10 - a0->unk10) * t);
    return a2 + 1;
}

extern f32 D_800D368C;

s32 func_15185B28(f32 *arg0) {
    return arg0[2] < D_800D368C;
}

struct vtx151857DC *func_15185B54(struct vtx151857DC *a0, struct vtx151857DC *a1, struct vtx151857DC *a2) {
    f32 t;

    t = a0->x / (a0->x - a1->x);
    a2->x = 0.0f;
    a2->y = a0->y + (a1->y - a0->y) * t;
    a2->z = a0->z + (a1->z - a0->z) * t;
    a2->unkC = (s16)((f32)a0->unkC + (f32)(a1->unkC - a0->unkC) * t);
    a2->unkE = (s16)((f32)a0->unkE + (f32)(a1->unkE - a0->unkE) * t);
    a2->unk10 = (s16)((f32)a0->unk10 + (f32)(a1->unk10 - a0->unk10) * t);
    return a2 + 1;
}

s32 func_15185C44(f32 *arg0) {
    return arg0[0] <= 0.0f;
}

struct vtx151857DC *func_15185C6C(struct vtx151857DC *a0, struct vtx151857DC *a1, struct vtx151857DC *a2) {
    f32 t;

    t = a0->y / (a0->y - a1->y);
    a2->y = 0.0f;
    a2->x = a0->x + (a1->x - a0->x) * t;
    a2->z = a0->z + (a1->z - a0->z) * t;
    a2->unkC = (s16)((f32)a0->unkC + (f32)(a1->unkC - a0->unkC) * t);
    a2->unkE = (s16)((f32)a0->unkE + (f32)(a1->unkE - a0->unkE) * t);
    a2->unk10 = (s16)((f32)a0->unk10 + (f32)(a1->unk10 - a0->unk10) * t);
    return a2 + 1;
}

s32 func_15185D5C(f32 *arg0) {
    return arg0[1] <= 0.0f;
}

s32 func_15185D84(f32 *arg0) {
    return arg0[0] > 0.0f;
}

s32 func_15185DAC(f32 *arg0) {
    return arg0[1] > 0.0f;
}

struct vtx151857DC *func_15185DD4(struct vtx151857DC *arg0, s32 arg1, s32 arg2, struct vtx151857DC *arg3) {
    struct vtx151857DC *cur;
    struct vtx151857DC *prev;
    struct vtx151857DC *(*emit)(struct vtx151857DC *, struct vtx151857DC *, struct vtx151857DC *);
    s32 (*test)(struct vtx151857DC *);
    s32 i;

    prev = &arg0[arg1 - 1];
    emit = D_8008D498[arg2];
    test = D_8008D4C0[arg2];
    cur = arg0;
    i = 0;
    if (arg1 > 0) {
        do {
            if (test(cur) != 0) {
                if (test(prev) != 0) {
                    *arg3++ = *cur;
                } else {
                    arg3 = emit(prev, cur, arg3);
                    *arg3++ = *cur;
                }
            } else {
                if (test(prev) != 0) {
                    arg3 = emit(prev, cur, arg3);
                }
            }
            i++;
            prev = cur;
            cur++;
        } while (i != arg1);
    }
    return arg3;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15185F24.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_1518652C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15186794.s")

void func_151872B0(s32 arg0) {
    D_800DE01C = 0x258;
    D_800DE020 = 0xB4;
    D_800DE024 = 0x5A;
    D_800DE030 = 0x3F8;
    D_800DE034 = 0;
    D_800DE038 = 1;
    D_800DE03C = 1.0f;
    D_800DE040 = 1;
    D_800DE041 = 1;

    switch (arg0) {
    case 0x21:
        D_800DE01C = 0x12C0;
        D_800DE020 = D_800DE01C - 1;
        D_800DE024 = D_800DE01C - 2;
        D_800DE030 = 0x3F2;
        D_800DE034 = 1;
        D_800DE038 = 4;
        D_800DE040 = 0;
        break;
    case 0x22:
        D_800DE01C = 0x960;
        D_800DE020 = D_800DE01C - 1;
        D_800DE024 = D_800DE01C - 2;
        D_800DE038 = 4;
        D_800DE040 = 0;
        break;
    case 0x14:
        D_800DE041 = 0;
        break;
    case 0x29:
        D_800DE01C = 0x4B0;
        D_800DE020 = 0x258;
        D_800DE024 = 0x12C;
        break;
    }
}

struct vtx151873E4 {
    f32 x;      /* 0x00 */
    f32 y;      /* 0x04 */
    f32 z;      /* 0x08 */
    s32 unkC;   /* 0x0C */
    s32 unk10;  /* 0x10 */
};              /* size 0x14 */

typedef struct {
    u8  pad0[0x10];
    s16 unk10;
    u8  pad12[0x2];
    s16 unk14;
    u8  pad16[0x39];
    u8  unk4F;
    u16 unk50;
    u16 unk52;
    u8  pad54[0x1A];
    u8  unk6E;
    u8  pad6F[0x31];
} unkfunc_151873E4; /* size 0xA0 */

extern void func_1510F800(s32);
extern void func_150A44F0(s32, s16 *, s32);
extern struct vtx151873E4 *func_150A5E44(s16 *, struct vtx151873E4 *, f32 *, struct vtx151873E4 *);

extern s32 D_800D3690;
extern s16 D_800D37E0[];
extern s32 D_800DF0E4;
extern s32 D_800DF0E8;
extern s32 D_800DF0EC;
extern s32 D_800DF0F0;
extern s32 D_800DF0F4;

s32 func_151873E4(s32 arg0, s32 arg1, s32 arg2, struct vtx151873E4 *arg3, f32 *arg4, struct vtx151873E4 *arg5, s32 arg6) {
    unkfunc_151873E4 *entry;
    s32 found;
    s32 i;
    s32 radius;

    if (D_800DBEF0 == 0) {
        return arg6;
    }

    func_1510F800(2);

    arg3 += arg6;
    D_800DF0E8 = arg0 - arg2;
    D_800DF0EC = arg0 + arg2;
    D_800DF0F0 = arg1 - arg2;
    D_800DF0F4 = arg1 + arg2;

    found = 0;
    for (i = 0; i < D_800DBEF0; i++) {
        entry = (unkfunc_151873E4 *)&D_800DBEF4[i];
        if (entry->unk6E != 0) {
            continue;
        }
        if (entry->unk4F & 0x60) {
            continue;
        }
        radius = (entry->unk52 < entry->unk50) ? entry->unk50 : entry->unk52;
        if (D_800DF0EC < entry->unk10 - radius) {
            continue;
        }
        if (entry->unk10 + radius < D_800DF0E8) {
            continue;
        }
        if (D_800DF0F4 < entry->unk14 - radius) {
            continue;
        }
        if (entry->unk14 + radius < D_800DF0F0) {
            continue;
        }
        D_800D37E0[found] = i;
        found++;
    }

    if (found != 0) {
        func_150A44F0(found, D_800D37E0, 0);
        D_800D3690 = D_800DBE3C;
        D_800DF0E4 = found;
        arg6 += func_150A5E44(D_800D37E0, arg3, arg4, arg5) - arg3;
    }
    return arg6;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_151875E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15187978.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15187A98.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15187D6C.s")
