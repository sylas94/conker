#include <ultra64.h>

#include "functions.h"
#include "variables.h"

extern u8 D_800BE2F0[];
extern u8 D_800BE2F2;
extern u8 D_800BE2F3;
extern u8 D_800BE2F4[];
extern u8 D_800BE35A[];
extern s8 D_800E0BE0[0x1C];
extern u8 D_800E0BFC;
extern u8 D_800D2E69;
extern void *D_80082BBC;
extern u8 D_8008FE30;

extern void func_151DD3A0(void *, s32, void *, s32);
extern s32 func_151DCEF0(void *, s32, void *, s32);
extern s32 func_151DD4E0(void *, u8, void *);
extern void func_151DD9E4(void);
extern void func_151E7EF8(void);
extern void func_15007168(void);

typedef struct Struct33990 {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ s8 unk1;
    /* 0x02 */ s8 unk2;
    /* 0x03 */ s8 unk3;
    /* 0x04 */ s8 unk4;
    /* 0x05 */ u8 unk5;
    /* 0x06 */ u8 unk6;
    /* 0x07 */ u8 unk7;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
} Struct33990; /* size = 0xA */


void func_150064E0(void) {
    s32 i = 0;
    func_15017790();

    do {
        D_800C3A60[i++] = 0;
    } while (i < 69);

    D_800BE3DF = 24;
    D_800BE3E8 = 0;
    D_800D2E45 = 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_15006590.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_15006BEC.s")
// PERMUTER CANDIDATE best 1532: structure byte-exact; only diff is the target keeps the (dead)
// return of the first func_151DD4E0 call live in a saved reg (s1) -> 8 saved regs. My build DCEs
// it (no -g3 dead-local slotting here) -> 7 saved regs, shifting all s-reg numbers & stack offsets.
// Likely the original uses that return value. Reconstruction:
// void func_1500707C(s32 arg0) {
//     s32 i; u8 *p358 = D_800BE358; s8 *p3D8 = &D_800BE3D8;
//     for (i = 0; i < 8; i++) { p358[i] = 0xFF; }
//     osWritebackDCacheAll();
//     if (D_8002AC5C == 0) {
//         for (i = 0; i < 4; i++) {
//             if (arg0 == *p3D8) {
//                 s32 idx = (i << 4) + 4;
//                 s32 ret = func_151DD4E0(&D_800BE900, (u8)idx, p358);
//                 func_151DD4E0(&D_800BE900, (u8)(idx + 1), p358);
//             }
//             p3D8++;
//         }
//     }
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_1500707C.s")
void func_15007168(void) {
    s32 i;

    for (i = 0; i < 0x68; i++) {
        D_800BE2F0[i] = 0;
    }

    for (i = 0; i != 10; i++) {
        ((Struct33990 *)D_80082BBC)[i].unk1 = 3;
        ((Struct33990 *)D_80082BBC)[i].unk3 = 2;
        ((Struct33990 *)D_80082BBC)[i].unk4 = 1;
        ((Struct33990 *)D_80082BBC)[i].unk2 = 10;
        switch (i) {
            case 0:
                ((Struct33990 *)D_80082BBC)[i].unk5 = 3;
                break;
            case 1:
            case 2:
                ((Struct33990 *)D_80082BBC)[i].unk5 = 5;
                break;
            case 7:
                ((Struct33990 *)D_80082BBC)[i].unk5 = 20;
                break;
            case 5:
                ((Struct33990 *)D_80082BBC)[i].unk5 = 20;
                ((Struct33990 *)D_80082BBC)[i].unk2 = 0;
                break;
            case 8:
            case 9:
                ((Struct33990 *)D_80082BBC)[i].unk5 = 3;
                break;
        }
        ((Struct33990 *)D_80082BBC)[i].unk9 = 0;
    }
}
// PERMUTER CANDIDATE best 1165: loop structure byte-exact; remaining diff is a clean 3-register
// rotation {sum,i,p}->{v0,v1,a0} (target sum=v0,i=v1,p=a0) plus seed 0xCC reassociation.
// void func_1500727C(void) {
//     u16 sum;
//     s32 i;
//     u8 *p;
//     func_151DD3A0(&D_800BE900, 0x44, &D_800BE2F0, 0x70);
//     sum = (D_800BE2F2 << 2) + 0xCC + (D_800BE2F3 << 3);
//     p = D_800BE2F4;
//     i = 4;
//     do {
//         sum += *p++ << (i & 3);
//         i++;
//     } while (i != 0x68);
//     if (sum != D_800BE2F0) {
//         func_15007168();
//     }
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_1500727C.s")
// PERMUTER CANDIDATE best 1265: same unrolled-checksum 3-register rotation {sum,i,p}->{v0,v1,a0}
// as func_1500727C, plus target keeps the (dead) func_151DCEF0 return in a stack slot (frame -0x20
// vs my -0x18) which my build DCEs. Reconstruction:
// void func_15007360(void) {
//     u16 sum; s32 i; u8 *p; s32 ret;
//     sum = (D_800BE2F2 << 2) + 0xCC + (D_800BE2F3 << 3);
//     p = D_800BE2F4; i = 4;
//     do { sum += *p++ << (i & 3); i++; } while (i != 0x68);
//     D_800BE2F0 = sum;
//     if (D_8002AC5C == 0) { ret = func_151DCEF0(&D_800BE900, 0x44, &D_800BE2F0, 0x70); }
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_15007360.s")
// PERMUTER/DATA-LAYOUT CANDIDATE best 705: structure byte-exact. Blockers: (1) checksum pointer
// gets offset -2 (base+i) + v0/v1 swap vs target's base+0; (2) fill/copy loops reference the
// D_800E0BFC symbol as the unrolled end + clean count -> requires D_800E0BE0/D_800E0BFC to be
// compile-time-related (same struct/array); with separate externs IDO emits D_800E0BE0+0x1c and
// picks the src pointer for the copy bound. Reconstruction:
// void func_15007440(void) {
//     u16 sum; s32 i; s8 saved;
//     func_151DD3A0(&D_800BE900, 0, &D_800BE358, 0x20);
//     sum = 0xCC;
//     for (i = 2; i < 0x1E; i++) { sum += D_800BE35A[i - 2] << (i & 3); }
//     saved = D_800E0BE0[0x10];
//     if (sum != *(u16 *)D_800BE358) { for (i=0;i<0x1C;i++) D_800E0BE0[i] = -1; }
//     else { for (i=0;i<0x1C;i++) D_800E0BE0[i] = D_800BE358[i + 2]; }
//     D_800E0BE0[0x10] = saved;
//     func_151DD9E4(); func_151E7EF8(); D_8008FE30 = 1;
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_15007440.s")
// PERMUTER CANDIDATE best 610: checksum loop byte-exact. Two residual blockers:
// (1) the dead func_151DCEF0 return -> target keeps `sw v0,0x18(sp)` (frame 0x20); my build DCEs it
//     (a `volatile s32 ret` restores the store but overshoots frame to 0x30). Same blocker as
//     func_15007360. (2) copy-loop v0/v1 swap: IDO CSEs &D_800BE358 into a saved reg across the loop
//     (move v0,dst) instead of the target's rematerialize-at-bottom, swapping dst/src regs.
// void func_15007558(void) {
//     u16 sum; s32 i; s8 *src; u8 *dst; u8 *p;
//     src = D_800E0BE0; dst = D_800BE358;
//     do { dst++; dst[1] = *src++; } while (src < (s8 *)&D_800E0BFC);
//     sum = 0xCC; p = D_800BE35A; i = 2;
//     do { sum += *p++ << (i & 3); i++; } while (i != 0x1E);
//     *(u16 *)D_800BE358 = sum;
//     if (D_8002AC5C == 0) { func_151DCEF0(&D_800BE900, 0, D_800BE358, 0x20); }
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_15007558.s")

void func_15007644(void) {
}

void func_1500764C(void) {
    D_80082BB4 = (u8)6;
    D_800BE3EC = (u8)0;
}

void func_15007668(void) {
    D_80082BB4 = (u8)7;
    D_800BE3EC = (u8)0;
}

void func_15007684(void) {
    D_80082BB4 = (u8)4;
    D_800BE3EC = (u8)0;
}

void func_150076A0(void) {
    D_80082BB4 = (u8)5;
    D_800BE3EC = (u8)0;
}

void func_150076BC(s32 arg0) {
    if (arg0 < 0) {
        func_150064E0();
    }
    if ((arg0 >= 0) && (arg0 < 4) && (D_800BE616 == 0)) {
        D_80082BB4 = (u8)1;
        D_800BE3EC = arg0;
    }
}

void func_15007718(s32 arg0) {
    if ((arg0 >= 0) && (arg0 < 3) && (D_800BE616 == 0)) {
        D_80082BB4 = (u8)2;
        D_800BE3EC = arg0;
    }
}

void func_15007750(s32 arg0) {
    if ((arg0 >= 0) && (arg0 < 3)) {
        D_80082BB4 = (u8)3;
        D_800BE3EC = arg0;
    }
}

// PERMUTER CANDIDATE best 3600: struct stores + loop2 (D_800D2E60 clear) match; blocker is IDO
// unrolling the 27-iter D_800D2E4C byte-clear (target leaves it rolled, reloading the pointer each
// iter) + the final four -1 stores materialize fresh regs in target. Reconstruction:
// void func_15007778(void) {
//     u8 *q; s32 i;
//     ((struct162 *)&D_800BE3F8)->unk8 = -1;
//     ((struct162 *)&D_800BE3F8)->unk18 = -1;
//     ((struct162 *)&D_800BE3F8)->unk28 = -1;
//     ((struct162 *)&D_800BE3F8)->unkE = -1;
//     ((struct162 *)&D_800BE3F8)->unk1E = -1;
//     ((struct162 *)&D_800BE3F8)->unk2E = -1;
//     D_800BE3DC = -1; D_800BE3DE = 0; D_80082BC0 = 1;
//     i = 0; do { ((u8 *)D_800D2E4C)[i] = 0; i++; } while (i < 27);
//     q = D_800D2E60; do { *q++ = 0; } while (q < &D_800D2E69);
//     D_800BE3DB = -1; D_800BE3DA = -1; D_800BE3D9 = -1; D_800BE3D8 = -1;
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_15007778.s")
