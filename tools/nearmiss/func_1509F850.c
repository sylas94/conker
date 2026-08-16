#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
} Cmd1509;

typedef struct {
    u16 unk0;
    u16 unk2;
    u16 unk4;
} Slot1509;

extern u8    D_80087410[];
extern s32   D_800D2F58;
extern s32   D_800D2E48;
extern u8    D_800D2E69;
extern s32   D_800D3000;
extern s32   D_800D3004;
extern s32   D_800D3840;
extern s8    D_800E0BB1;
extern u16   D_800BE930[];
extern Slot1509 D_800BE918[];
extern u8    D_800D2E40;

struct248 *func_1509B704(s16 arg0);
s32  func_1509B5AC(s32 arg0, s32 arg1);
void func_150AE280(void);
void func_1501C730(s32, s32, s32, s32, s32);
void func_15172E7C(void *, s32, s32);
void func_151E53E8(s32);
void func_1517EE40(s32, s32, s32, s32, s32, s32);
void func_15042E3C(char *, s32);
void func_151E8214(void);
void func_151E4DC4(void);
s32  func_151E5F64(s32);

s32 func_1509F850(s32 arg0, s32 arg1, Cmd1509 *arg2) {
    struct248 *nodeA;
    struct248 *nodeB;
    struct248 *nodeC;
    struct248 *nodeD;
    struct248 *nodeE;
    u8 *bits;
    s32 i;
    s32 temp;

    switch (arg1) {
    case 2:
        nodeA = func_1509B704((s16)arg0);
        bits = (u8 *)((arg0 >> 3) + (s32)D_800D2E4C);
        *bits = *bits & 7 & (1 << (arg0 & 7));
        D_800D2F58 = 1;
        D_800D2E43 = 1;
        if (nodeA == 0) {
            return 0;
        }
        nodeA->unk0 |= 0x8000;
        return 1;
    case 1:
        if (D_80087410[1] != 0) {
            D_80087410[1] = 0;
            return 0;
        }
        bits = (u8 *)((arg0 >> 3) + (s32)D_800D2E4C);
        *bits |= 1 << (arg0 & 7);
        D_800D2F58 = 1;
        D_800D2E43 = 1;
    case 3:
        nodeB = func_1509B704((s16)arg0);
        if (nodeB == 0) {
            return 0;
        }
        nodeB->unk0 |= 0x8000;
        if (arg0 == D_800D2E48) {
            func_150AE280();
            return 0;
        }
        return 1;
    case 5:
        nodeC = func_1509B704((s16)arg0);
        if (nodeC == 0) {
            return 0;
        }
        bzero((u8 *)nodeC + nodeC->unkA, nodeC->unk6);
        return 0;
    case 4:
        nodeD = func_1509B704((s16)arg0);
        if (nodeD == 0) {
            break;
        }
        nodeD->unk0 |= 0x4000;
        return 1;
    case 6:
        func_1509B5AC(arg0, 0);
        return 0;
    case 7:
        if (D_800D3840 == 4) {
            func_1501C730(2, arg2->unk8, arg2->unkC, 0, 0);
            return 0;
        }
        break;
    case 8:
        if (D_800D3840 != 4) {
            break;
        }
        func_15172E7C(D_800CC2D0, arg2->unk8 & 0xFFF, arg2->unkC & 0xFFF);
        break;
    case 9:
        D_800D2E69 = 1;
        if (arg2->unk8 != 0) {
            bits = &D_800D2E60[arg2->unkC >> 3];
            *bits |= 1 << (arg2->unkC & 7);
        } else {
            bits = &D_800D2E60[arg2->unkC >> 3];
            *bits = *bits & 7 & (1 << (arg2->unkC & 7));
        }
        D_800D2E43 = 1;
        break;
    case 10:
        func_151E53E8(arg2->unk8);
        return 0;
    case 11:
        nodeE = func_1509B704((s16)arg0);
        bits = (u8 *)((arg0 >> 3) + (s32)D_800D2E4C);
        *bits |= 1 << (arg0 & 7);
        D_800D2F58 = 1;
        D_800D2E43 = 1;
        if (nodeE == 0) {
            return 0;
        }
        nodeE->unk0 |= 0x8000;
        func_151E53E8(0);
        func_150AE280();
        return 0;
    case 12:
        if (arg2->unk8 < 0) {
            temp = osGetCount();
            D_800D3000 = temp;
            D_800D3004 = temp;
            break;
        }
        osGetCount();
        D_800D3000 = osGetCount();
        return 0;
    case 13:
        D_800DDE38 = 1;
        break;
    case 14:
        D_800E9D00 |= arg2->unk8;
        break;
    case 15:
        if (arg2->unkC == 0) {
            D_800D2120 &= ~(1 << arg2->unk8);
        } else {
            D_800D2124 &= ~(1 << arg2->unk8);
        }
        break;
    case 16:
        if (arg2->unkC == 0) {
            D_800D2120 |= 1 << arg2->unk8;
        } else {
            D_800D2124 |= 1 << arg2->unk8;
        }
        break;
    case 17:
        func_1517EE40(0, 0, 0, 0, 1, 0);
        return 0;
    case 18:
        for (i = 0; i <= D_80082FA0; i++) {
            func_1517EE40(arg2->unk8, arg2->unkC, arg2->unk10, arg2->unk14, arg2->unk18, i);
        }
        break;
    case 19:
        D_800BE3DF = arg2->unk8;
        D_800BE3E0 = arg2->unkC;
        D_800BE9F4 = (u16 *)(*(s8 *)&D_800BE3DF);
        break;
    case 20:
        func_151E8214();
        return 0;
    case 21:
        func_151E4DC4();
        return 0;
    case 22:
        func_15042E3C("%d", arg2->unk8);
        return 0;
    case 23:
        if (arg2->unk8 != 0) {
            D_800D2E44 = 1;
        } else {
            D_800D2E44 = 0;
        }
        break;
    }
    return 0;
}

s32 func_1509FE0C(s32 arg0, s32 arg1, Cmd1509 *arg2) {
    struct248 *node;
    s32 mask;
    s32 j;
    s32 i;
    s32 total;
    s32 value;
    s32 threshold;
    s32 temp;

    switch (arg1) {
    case 26:
        return *(u8 *)((arg0 >> 3) + (s32)D_800D2E4C) & (1 << (arg0 & 7));
    case 27:
        return func_1509B704((s16)arg0)->unk2;
    case 28:
        return D_800BE9F0;
    case 29:
        mask = 0;
        for (j = 0; j < D_8008FD8C; j++) {
            if (D_80087270[j] != 10) {
                mask |= 1 << j;
            }
        }
        mask &= ~D_800D18A0;
        return mask;
    case 30:
        return func_151E5F64(arg2->unk8);
    case 31:
        return D_800BE9F8;
    case 32:
        return *(s8 *)&D_800BE3DF;
    case 33:
        return D_800BE3E0;
    case 34:
        total = 0;
        for (i = 0; i < arg2->unk8; i++) {
            total += (&arg2->unkC)[i];
        }
        threshold = (s32)(func_150ADA68() * total);
        total = 0;
        for (i = 0; i < arg2->unk8; i++) {
            value = (&arg2->unkC)[i];
            total += value;
            if ((total >= threshold) && (value != 0)) {
                return i;
            }
        }
        return arg2->unk8 - 1;
    case 35:
        return D_8008FD90;
    case 36:
        return D_800E0BB1;
    case 37:
        return D_8008FDBC & 0x10;
    case 38:
        return D_8008FD8C;
    case 39:
        return D_800BE930[arg2->unk8];
    case 40:
        return D_800BE918[arg2->unk8].unk0;
    case 41:
        return D_800E0B94 == 2;
    case 42:
        return arg2->unk8 & D_800E9D00;
    case 43:
        node = func_1509B704((s16)arg0);
        if (node != 0) {
            return (node->unk0 & 0x2000) == 0;
        }
        return 0;
    case 44:
        if (D_800D3840 == 3) {
            temp = arg2->unk8;
        } else {
            temp = 0;
        }
        return func_1517EFAC(temp);
    case 45:
        return D_800D2E40;
    }
    return 0;
}
