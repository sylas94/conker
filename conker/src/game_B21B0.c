#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern u8 D_8009D954[];
extern u8 *D_80087240[];

// PERMUTER CANDIDATE: func_15084D00 best 855 (algorithm + non-unrolled single-back-edge
// loop are correct). Residual = LICM hoisting the %hi(D_80087240) base out of the outer
// loop (target recomputes `lui a3,%hi; addu a3,a3,i*4; lw a3,%lo(a3)` inline each iter) plus
// register allocation cascade (count a0<->a2, j swap, one extra key copy). Key structural
// insights: the inner search loop MUST be a goto/while(1) form (a counted `for`/do-while gets
// 4x loop-unrolled by IDO -O2 → 4170); hoisting `j = 0` above the `if (count > 0)` dropped
// 1495->855. Reconstruction (needs `extern u8 D_8009D954[]; extern u8 *D_80087240[];`):
//   u8 func_15084D00(struct127 *arg0) {
//     u8 key = arg0->id; s32 i, j, count; u8 *ptr, *p, b;
//     for (i = 0; i != 7; i++) {
//       count = D_8009D954[i]; j = 0;
//       if (count > 0) { ptr = D_80087240[i]; p = ptr;
//         loop: b = *p; j++; if (key == b) return ptr[0]; p++; if (j < count) goto loop; }
//     }
//     return key;
//   }
#pragma GLOBAL_ASM("asm/nonmatchings/game_B21B0/func_15084D00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_B21B0/func_15084D70.s")

void func_15085410(struct127 *arg0, s32 arg1) {
    arg0->unk31C->pad11B[0] = arg1;
}

u8 func_15085420(struct127 *arg0) {
    return arg0->unk31C->pad11B[0];
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_B21B0/func_15085430.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_B21B0/func_15085710.s")

// NEAR-MISS best 1220: the entire switch body (all 7 cases) is BYTE-PERFECT. Two blockers:
//   (1) HEADER TYPE: functions.h declares `func_150859AC(s16, s32)` but the target sign-
//       extends AND homes arg1 as a 16-bit param (sw a1,4(sp); sll;sra) — i.e. arg1 must be
//       s16. Can't redeclare (header conflict). `arg1=(s16)arg1` gives the sll/sra but not the
//       arg-home; `switch((s16)arg1)` gives an andi mask instead of sign-extend. The header's
//       s32 arg1 is the root blocker (also drives bnezl vs bnez + duplicated sltiu in the guard).
//   (2) JUMP TABLE: IDO generates the switch jtbl as anonymous `.rodata`; the golden object
//       references a named `jtbl_8009D9A0` — object-level rodata symbol mismatch in this
//       per-function GLOBAL_ASM setup.
// Reconstruction (needs functions.h fixed to s16 arg1, plus jtbl rodata handling):
//   extern s32 D_800D213C, D_800D2140, D_800D2148; extern s8 D_800D2144, D_800D2145;
//   extern u8 D_800D2146; // D_800D2340 is u16 (header says s16 -> read via *(u16*)&)
//   s32 func_150859AC(s16 arg0, s16 arg1) {
//     if (arg0 >= 0xFF) return 0;
//     switch (arg1) {
//       case 0: return *(u16*)&D_800D2340 & (1 << arg0);
//       case 1: return *(s32*)((u8*)&D_800D213C + arg0*0x1C);
//       case 2: return *(s32*)((u8*)&D_800D2140 + arg0*0x1C);
//       case 3: return *(s8 *)((u8*)&D_800D2144 + arg0*0x1C);
//       case 4: return *(s8 *)((u8*)&D_800D2145 + arg0*0x1C);
//       case 5: return *(u8 *)((u8*)&D_800D2146 + arg0*0x1C);
//       case 6: return *(s32*)((u8*)&D_800D2148 + arg0*0x1C);
//     } // falls off end (default returns garbage v0, matches target)
//   }
#pragma GLOBAL_ASM("asm/nonmatchings/game_B21B0/func_150859AC.s")

void func_15085ABC(s16 arg0) {
    s32 i;

    i = 0;
    if (D_800D18A8 == 0) {
        for (i = 0; i != 4; i++) {
            if ((1 << i) & arg0) {
                func_15085710((s16)i, 5, D_800CC2D0[i].health);
            }
        }
    }
}
