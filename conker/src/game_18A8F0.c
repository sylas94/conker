#include <ultra64.h>
#define func_1515D4D4 func_1515D4D4_prototype
#include "functions.h"
#undef func_1515D4D4
#include "variables.h"


s32 *allocate_memory(s32, s32, s32, s32);
s32 func_150A1DA0(u8 *, struct178 *, s32);
f32 func_1515F008(s16 *, s32);
void func_1515F040(f32, s32);
void func_1515F0AC(f32, s32);
extern void func_10004074(void *);
extern f32 D_800A6530;

struct Struct1515FBC4 {
    u8 pad0[0x98];
    struct127 *unk98;
};

struct Struct1515FBC4 *func_15105C24(s32);

s32 *func_1515D440(void) {
    s32 *temp;

    temp = allocate_memory(0x10, 1, 2, 0);
    bzero(temp, 0x10);
    return temp;
}

s32 *func_1515D480(s32 arg0) {
    s32 *temp;
    s32 size;
    s32 *pp = &arg0;

    size = *pp * 0x60;
    temp = allocate_memory(size, 1, 2, 0);
    bzero(temp, size);
    return temp;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515D4D4.s")

struct Node1515D520 {
    struct Node1515D520 *next;
};

s32 *func_1515D520(void) {
    struct Node1515D520 *node;
    struct Node1515D520 *p;
    struct Node1515D520 *q;

    node = (struct Node1515D520 *)allocate_memory(0x34, 1, 2, 2);
    if (node != 0) {
        bzero(node, 0x34);
        if (D_800DCD78 != 0) {
            p = (struct Node1515D520 *)D_800DCD78;
            q = p->next;
            while (q != 0) {
                p = q;
                q = q->next;
            }
            p->next = node;
        } else {
            D_800DCD78 = (s32)node;
        }
        node->next = 0;
    }
    return (s32 *)node;
}

s32 func_1515D5F8(s32, s32, s32, s32, s32, s32, s32, s32, s32, u8);

s32 func_1515D5AC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, u8 arg9) {
    return func_1515D5F8(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515D5F8.s")

struct Node1515D69C {
    struct Node1515D69C *next;
    char pad4[8];
    s8 unkC;
    char pad10[0x23];
    s8 unk30;
};

void func_1515D69C(void) {
    struct Node1515D69C *p;

    for (p = (struct Node1515D69C *)D_800DCD78; p != 0; p = p->next) {
        p->unkC = 0;
        p->unk30 = 0;
    }
}

void func_1515D6C8(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515D6D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515D914.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515E278.s")

struct Node1515E43C {
    char pad0[0x18];
    u32 unk18;
    u32 unk1C;
};

struct Node1515EB84 {
    struct Node1515EB84 *next;
    struct178 *unk4;
};

struct Node1515E43C *func_1515EB84(s32, s32, s32, s32, struct Node1515EB84 *);

void func_1515E43C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 *arg4, u8 *arg5, u8 *arg6, u8 *arg7) {
    struct Node1515E43C *node;

    node = func_1515EB84(arg0, arg1, arg2, 0, D_800DCD84);
    if (node != NULL) {
        arg4[0] = node->unk18 & 0xFF;
        arg4[1] = (node->unk18 >> 8) & 0xFF;
        arg4[2] = (node->unk18 >> 16) & 0xFF;
        arg5[0] = node->unk1C & 0xFF;
        arg5[1] = (node->unk1C >> 8) & 0xFF;
        arg5[2] = (node->unk1C >> 16) & 0xFF;
        arg6[0] = (node->unk1C >> 24) & 0xFF;
        arg7[0] = (node->unk18 >> 24) & 0xFF;
    } else {
        arg4[0] = ((u8 *)D_800DCD24)[0];
        arg4[1] = ((u8 *)D_800DCD24)[1];
        arg4[2] = ((u8 *)D_800DCD24)[2];
        arg5[0] = D_800DCD28[0];
        arg5[1] = D_800DCD28[1];
        arg5[2] = D_800DCD28[2];
        arg6[0] = D_800DCD3C;
        arg7[0] = D_800DCD3D;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515E544.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515E888.s")

struct Node1515E43C *func_1515EB84(s32 arg0, s32 arg1, s32 arg2, s32 arg3, struct Node1515EB84 *node) {
    u8 sp34[0x32C];
    struct178 *entry;

    *(f32 *)&sp34[0x14] = (f32)arg0;
    *(f32 *)&sp34[0x18] = (f32)arg1;
    *(f32 *)&sp34[0x180] = (f32)arg1;
    *(f32 *)&sp34[0x2C] = (f32)arg0;
    *(f32 *)&sp34[0x30] = (f32)arg1;
    *(f32 *)&sp34[0x1C] = (f32)arg2;
    *(f32 *)&sp34[0x34] = (f32)arg2;

    while (node != 0) {
        entry = node->unk4;
        if (entry->unk6[0xE] == 0) {
            if ((arg3 == 0) || (((*(u32 *)&entry->unk6[0x12] >> 24) & arg3) != 0)) {
                if ((0x18 == ((s32)entry->unk6[0xF] >> 2)) || ((*(u32 *)&entry->unk6[0x12] >> 31) == 0)) {
                    if (func_150A1DA0(sp34, entry, 0) == 0) {
                        return (struct Node1515E43C *)node->unk4;
                    }
                }
            }
        }
        node = node->next;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515EC78.s")

void func_1515EF74(s16 *arg0) {
    func_1515F040(1.0f / func_1515F008(arg0, 0), 0);
    func_1515F040(1.0f / func_1515F008(arg0, 5), 1);
    func_1515F040(1.0f / func_1515F008(arg0, 0xA), 2);
    func_1515F0AC(-func_1515F008(arg0, 0xE), 3);
}

f32 func_1515F008(s16 *arg0, s32 arg1) {
    s32 hi = arg0[arg1];
    hi = (hi << 16) | (u16)arg0[arg1 + 0x10];
    return (f32)hi * 1.52587890625e-05f;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515F040.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515F0AC.s")

struct Node1515F10C {
    struct Node1515F10C *next;
};

void func_1515F10C(struct Node1515F10C *arg0) {
    struct Node1515F10C *node;
    struct Node1515F10C *prev;

    node = (struct Node1515F10C *)D_800DCD78;
    prev = 0;
    if (node != arg0) {
        do {
            prev = node;
            node = node->next;
        } while (node != arg0);
    }
    if (prev != 0) {
        prev->next = node->next;
    } else {
        D_800DCD78 = (s32)node->next;
    }
    func_10004074(node);
}

struct Node1515F170 {
    struct Node1515F170 *next;
    char pad4[5];
    s8 unk9;
    char padA[1];
    u8 unkB;
};

void func_1515F170(s32 arg0, u8 arg1) {
    struct Node1515F170 *p;

    for (p = (struct Node1515F170 *)D_800DCD78; p != 0; p = p->next) {
        if (arg0 == p->unkB) {
            p->unk9 = arg1;
        }
    }
}

struct Node1515F1B0 {
    s32 unk0;
    f32 unk4;
    f32 unk8;
    s32 unkC;
};

struct Node1515F1B0 *func_1515F1B0(s32 arg0) {
    struct Node1515F1B0 *temp;

    temp = (struct Node1515F1B0 *)func_10003C6C(0x10, 1, 2, 0, 1);
    if (temp == 0) {
        return 0;
    }
    temp->unk0 = arg0;
    if (arg0 != 0) {
        temp->unk4 = func_1514462C(arg0);
    } else {
        temp->unk4 = 0.0f;
    }
    if (arg0 != 0) {
        temp->unk8 = func_15144598((struct134 *)arg0);
    } else {
        temp->unk8 = 0.0f;
    }
    temp->unkC = 0;
    return temp;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515F25C.s")

extern void (*D_8008B090[])(s32);

void func_1515F270(s32 arg0, s32 *arg1) {
    s32 idx = arg1[6];

    if (idx >= 0 && idx < 12) {
        if (D_8008B090[idx] != 0) {
            D_8008B090[idx](arg0);
        }
    }
}

s32 func_1505D024(struct127 *arg0, s32 arg1, u16 arg2, s32 arg3);

s32 func_1515F2B8(struct127 *arg0, s32 arg1) {
    return func_1505D024(arg0, 0x6001D, arg0->unk7A, -1);
}

extern void (*D_8008B0C0[])(void);

void func_1515F2E8(u8 *arg0, s32 *arg1) {
    s32 idx;

    if (arg0[0x3B] == 1) {
        idx = arg1[7];
        if (idx >= 0 && idx < 3) {
            D_8008B0C0[idx]();
        }
    }
}

void func_1515F338(s32 arg0, s32 arg1) {
    u8 temp_v1;
    u8 temp_t0;
    u8 temp_t1;

    temp_v1 = ((u8 *)&D_800DCD20)[0];
    temp_t0 = ((u8 *)&D_800DCD20)[1];
    temp_t1 = ((u8 *)&D_800DCD20)[2];
    if (D_800DCD94 != 97.0f) {
        D_800DCD94 += (97.0f - D_800DCD94) * 0.5f;
        temp_v1 = (u8)(u32)D_800DCD94;
    }
    if (D_800DCD98 != 96.0f) {
        D_800DCD98 += (96.0f - D_800DCD98) * 0.5f;
        temp_t0 = (u8)(u32)D_800DCD98;
    }
    if (D_800DCD9C != 98.0f) {
        D_800DCD9C += (98.0f - D_800DCD9C) * 0.5f;
        temp_t1 = (u8)(u32)D_800DCD9C;
    }
    func_1515D4D4(temp_v1, temp_t0, temp_t1, 0);
}

void func_1515F5C4(s32 arg0, s32 arg1) {
    u8 temp_v1;
    u8 temp_t0;
    u8 temp_t1;

    temp_v1 = ((u8 *)&D_800DCD20)[0];
    temp_t0 = ((u8 *)&D_800DCD20)[1];
    temp_t1 = ((u8 *)&D_800DCD20)[2];
    if (D_800DCD94 != 229.0f) {
        D_800DCD94 += (229.0f - D_800DCD94) * 0.5f;
        temp_v1 = (u8)(u32)D_800DCD94;
    }
    if (D_800DCD98 != 253.0f) {
        D_800DCD98 += (253.0f - D_800DCD98) * 0.5f;
        temp_t0 = (u8)(u32)D_800DCD98;
    }
    if (D_800DCD9C != 160.0f) {
        D_800DCD9C += (160.0f - D_800DCD9C) * 0.5f;
        temp_t1 = (u8)(u32)D_800DCD9C;
    }
    func_1515D4D4(temp_v1, temp_t0, temp_t1, 0);
}

struct Stack1515F850 {
    s32 pad14;
    s32 pad18;
    u8 sp1C;
    u8 sp1D;
    u8 sp1E;
    u8 pad1F;
    f32 sp20;
    f32 sp24;
    f32 sp28;
};

void func_1515F850(s32 arg0, s32 arg1) {
    s32 pad;
    struct Stack1515F850 stack;
    f32 temp_f0;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;

    stack.sp1C = ((u8 *)&D_800DCD20)[0];
    stack.sp1D = ((u8 *)&D_800DCD20)[1];
    stack.sp1E = ((u8 *)&D_800DCD20)[2];
    temp_f0 = sinf(D_800DCDA0);
    temp_f14 = (temp_f0 * 29.5f) + 127.5f;
    temp_f16 = (temp_f0 * 71.0f) + 109.0f;
    stack.sp28 = temp_f14;
    stack.sp24 = temp_f16;
    temp_f18 = (temp_f0 * 26.0f) + 26.0f;
    stack.sp20 = temp_f18;
    D_800DCDA0 += D_800A6530 * D_800BE9A4;
    D_800DCDA0 = func_15144B68(D_800DCDA0);
    if (stack.sp28 != D_800DCD94) {
        D_800DCD94 += (stack.sp28 - D_800DCD94) * 0.5f;
        stack.sp1C = (u8)(u32)D_800DCD94;
    }
    if (stack.sp24 != D_800DCD98) {
        D_800DCD98 += (stack.sp24 - D_800DCD98) * 0.5f;
        stack.sp1D = (u8)(u32)D_800DCD98;
    }
    if (stack.sp20 != D_800DCD9C) {
        D_800DCD9C += (stack.sp20 - D_800DCD9C) * 0.5f;
        stack.sp1E = (u8)(u32)D_800DCD9C;
    }
    func_1515D4D4(stack.sp1C, stack.sp1D, stack.sp1E, 0);
}

long func_1515FB70(u8 *a0, u8 *a1)
{
  long offset;
  s32 v0;
  s32 *slot;
  v0 = (*((u8 *) (a0 + 0x3B))) == 1;
  if ((*((u8 *) (a0 + 0x3B))) == 1)
  {
    v0 = *((s32 *) (a1 + 0x1C));
    if (v0 >= 0)
    {
      offset = 0x1C;
      if (!v0)
      {
        slot = (s32 *) (a1 + offset);
      }
    }
  }
}


s32 func_1515FB94(struct127 *arg0, s32 arg1) {
    return func_1505D024(arg0, 0x6002D, arg0->unk7A, -1);
}

void func_1515FBC4(struct127 *arg0, s32 arg1) {
    struct Struct1515FBC4 *temp_v0;
    struct127 *temp_v1;
    s32 temp_a3;

    temp_v1 = 0;
    temp_v0 = func_15105C24(arg1);
    if (temp_v0 != 0) {
        temp_v1 = temp_v0->unk98;
    }
    if (temp_v1 != 0) {
        temp_a3 = ((s32)temp_v1 - (s32)D_800CC2D0) / (s32)sizeof(struct127);
    } else {
        temp_a3 = -1;
    }
    func_1505D024(arg0, 0x6002E, arg0->unk7A, temp_a3);
}

s32 func_1505D024(struct127 *arg0, s32 arg1, u16 arg2, s32 arg3);

s32 func_1515FC34(struct127 *arg0, s32 arg1) {
    return func_1505D024(arg0, 0x33, 0xC000, -1);
}

struct Struct1515FC60 {
    s16 unk0;
    u8 pad2[2];
    s16 unk4;
    s16 unk6;
    u8 pad8[0x14];
    u32 unk1C;
};

union Union1515FC60 {
    f32 f;
    f32 pad[2];
};

extern f32 D_800A6534;
s32 func_150AD960(s32, s32, s32, s32);
void func_15136C3C(struct127 *, s32, s32, s32, s32, s32, s32, s32);
void func_1507CD64(struct127 *, s32);

void func_1515FC60(struct127 *arg0, struct Struct1515FC60 *arg1) {
    f32 temp_f0;
    union Union1515FC60 temp_f18;
    s32 temp_v0;

    if (arg0->unk31C != NULL) {
        if (arg0->unk31C->unk120 == 0) {
            temp_v0 = arg1->unk1C;
            if (temp_v0 != 0) {
                temp_f18.f = (f32)(u32)temp_v0 * D_800A6534;
                temp_v0 = func_150AD960(arg1->unk0, arg1->unk4, (s32)arg0->x_position, (s32)arg0->z_position);
                temp_f0 = ((f32)arg1->unk6 * temp_f18.f) - (f32)arg0->unkE4;
                if (temp_f0 > (f32)temp_v0) {
                    return;
                }
            }
            func_1505D024(arg0, 0x2F, 0, -1);
            func_15136C3C(arg0, 1, 1, 1, 1, 0, 0xFF, 1);
            func_15145A50(arg0);
            func_1507CD64(arg0, 6);
        }
    }
}
