/* NEAR-MISS PARK -- game_18D250 / func_1515FDA0  (468 B)   fastscore mism=179
 *
 * THE SHAPE IS SOLVED.  This is the "iterate a linked list while the callback may
 * splice it" idiom already reconstructed for the twin func_151670C0 in
 * game_1944C0.c: the next pointer is parked in the global cursor stack
 * D_800DD198[D_800DD190] before the callback runs and re-read after it.
 * Control flow, strength reduction (i*0x1A0 as ((i*4-i)*4+i)*32), the hoisted
 * loop constants 1/-1/-5, the beql/beqzl delay-slot fills and every field offset
 * are all reproduced.
 *
 * THE ENTIRE RESIDUAL IS ONE OPTIMISER DECISION: loop-invariant hoisting of two
 * global ADDRESSES.
 *   golden  : &D_800C35EA -> $s6 and &D_8008B0D8 -> $s7 are hoisted; &D_800DD190
 *             and &D_800DD198 are NOT -- they are re-materialised (lui/%lo) at
 *             every use, which is why golden is 117 instructions and we are 110.
 *             That frees $s2 for arg0 and $fp for `i`.
 *   ours    : IDO hoists all FOUR addresses (s2,s4,s7,s8), so arg0 gets homed at
 *             sp+0x48 and the u8 `i` gets a stack slot at sp+0x43, frame 0x48 not
 *             0x40.  ~109 of 110 rows are that one renaming cascade.
 *   knock-on: because &D_800DD190 lives in a register, the `D_800DD190++` store is
 *             not forwarded into the following index read (we emit an extra `lb`);
 *             golden forwards it (sll 24 / sra 24 on the stored value).
 *
 * MEASURED AND INERT (all still 179): casting u8 D_800DD198[] vs a file-local
 * `Node **D_800DD198[]` shadow; `volatile` on D_800DD190, on D_800DD198, or both;
 * u8 vs s32 `doit`; `else if` vs a nested `if`.  WORSE: `s32 i` (223 -- kills the
 * andi 0xFF and spills more), `node->unkE &= 0xFB` instead of `&= ~4` (182 -- and
 * note it does NOT free arg0/i even though it removes the -5 constant, so simple
 * s-register saturation is NOT the mechanism).
 *
 * CALIBRATION POINT worth keeping: the twin func_151670C0's golden DOES hoist
 * &D_800DD190/&D_800DD198 into $s3/$s4.  So the hoist is not forbidden per se --
 * something about this function's candidate set makes IDO decline it.  The lead is
 * therefore "what makes arg0 and i outrank the two addresses", not "how do I spell
 * the stack access".
 *
 * Header inaccuracy noted: struct102.unk10 is s16 in structs.h but golden uses
 * `lb 0x10` -- it is an s8 handler index (same family as unkF used by
 * func_1515FFEC in this TU).  Shadowed file-locally below.
 */
#include <ultra64.h>
#define func_15169260 func_15169260_s32
#include "functions.h"
#undef func_15169260
#define D_800DD198 D_800DD198_hdr_u8
#include "variables.h"
#undef D_800DD198
typedef struct Node1515FDA0 {
    /* 0x00 */ u8  pad0[0x8];
    /* 0x08 */ struct Node1515FDA0 *unk8;
    /* 0x0C */ u8  padC[0x2];
    /* 0x0E */ u8  unkE;
    /* 0x0F */ u8  unkF;
    /* 0x10 */ s8  unk10;
} Node1515FDA0;
extern Node1515FDA0 *D_800DD198[];


extern void *func_15167A68(s32, s32, s32, s32, u8, s32);
extern s32 (*D_8008B0D0[])(void *);
extern char D_800A6540[];
extern char D_800A6548[];
extern char D_800A657C[];
extern char D_800A6584[];
extern char D_800A65B8[];
extern char D_800A65C0[];
extern char D_800A65F4[];
extern char D_800A65FC[];
extern char D_800A6630[];
extern char D_800A663C[];
extern f32 D_800A6674;
extern f32 D_800A6678;
extern f32 D_800A667C;
extern f32 D_800A6680;

typedef struct {
    s32 unk0;
} Data_15160274;

extern Data_15160274 D_800A6670;
void func_15169260(Data_15160274 *, s32, s32, u8);

extern u8 D_800DCF20[];
extern void (*D_8008B0D8[])(Node1515FDA0 *, s32);
extern s32 func_15181CC8(s32);
extern s32 func_1517EF00(s32);

void func_1515FDA0(s32 arg0) {
    Node1515FDA0 *node;
    u8 i;
    s32 doit;

    for (i = 0; i < 2; i++) {
        node = *(Node1515FDA0 **)&D_800DCF20[i * 0x1A0];
        D_800DD190++;
        if (node != NULL) {
            do {
                D_800DD198[D_800DD190] = node->unk8;
                if ((node->unkE & 4) != 0) {
                    node->unkE &= ~4;
                } else if (node->unk10 != -1) {
                    doit = 1;
                    if ((node->unkE & 2) != 0) {
                        if (D_800C35EA == 1) {
                            doit = 0;
                        }
                    }
                    if ((node->unkE & 8) != 0) {
                        if (func_15181CC8(0) == 0) {
                            doit = 0;
                        } else if (func_1517EF00(0) != 0) {
                            doit = 0;
                        }
                    }
                    if (doit != 0) {
                        D_8008B0D8[node->unk10](node, arg0);
                    }
                }
                node = D_800DD198[D_800DD190];
            } while (node != NULL);
        }
        D_800DD190--;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_18D250/func_1515FDA0.s")

void *func_1515FF74(void *arg0, s32 arg1, u8 arg2, s32 arg3) {
    void *temp_v0;
    void *sp24;

    temp_v0 = func_15167A68(0x34, arg3, arg1 + 0x18, 1, arg2, 1);
    if (temp_v0 == 0) {
        return NULL;
    }
    sp24 = temp_v0;
    memcpy((s32)temp_v0 + 0xE, arg0, 8);
    return sp24;
}

typedef struct {
    u8 pad0[0xE];
    u8 unkE;
    s8 unkF;
    u8 pad10[2];
    s16 unk12;
} Struct1515FFEC;

void func_1515FFEC(Struct1515FFEC *arg0) {
    s32 temp;
    u8 failed;

    failed = 0;
    if (arg0->unkE & 1) {
        arg0->unk12 -= D_800BE9E4;
        if (arg0->unk12 < 0) {
            failed = 1;
        }
    }
    if (failed == 0) {
        temp = arg0->unkF;
        if (temp != -1) {
            if (D_8008B0D0[temp](arg0) == 0) {
                failed = 1;
            }
        }
    }
    if (failed) {
        func_1516972C((struct102 *) arg0);
    }
}

extern void (*D_8008B0E4[])(void*, s32, u8);

void func_15160090(void *arg0, s32 arg1, u8 arg2) {
    void (*func)(void*, s32, u8);

    func = D_8008B0E4[*(u8*)((char*)arg0 + 0x14)];
    if (func != NULL) {
        func(arg0, arg1, arg2);
    }
}

s32 func_151600D8(void *arg0) {
    f32 *p;
    s32 i;

    p = (f32 *)((s32)arg0 + 0x18);
    i = 0;
    p[0] = (f32)func_151422DC(i++, D_800A6540, -2000, 2000, 0, D_800A6548, 0x1C4) * D_800A6674;
    p[1] = (f32)func_151422DC(i++, D_800A657C, -2000, 2000, 0, D_800A6584, 0x1C9) * D_800A6678;
    p[2] = (f32)func_151422DC(i++, D_800A65B8, 0, 2000, 500, D_800A65C0, 0x1CE) * D_800A667C;
    p[3] = (f32)func_151422DC(i++, D_800A65F4, 0, 2000, 500, D_800A65FC, 0x1D3) * D_800A6680;
    *(s32 *)&p[4] = func_151422DC(i, D_800A6630, 0, 0x10000, 0x10000, D_800A663C, 0x1D9);
    return 1;
}

void func_15160274(s32 arg0, u8 arg1) {
    Data_15160274 sp1C;

    sp1C = D_800A6670;
    func_15169260(&sp1C, 1, arg0, arg1);
}
