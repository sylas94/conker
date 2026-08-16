#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern u8 D_8009D954[];
extern u8 *D_80087240[];

extern s32 func_15084D70(s32, s32, s32, s16 *, f32 *, u8 *, u8 *, s32 *, s32 *, s32, s32 *);
extern f32 func_1506AD30(struct127 *, f32, s32);
extern void func_1507C3E0(struct127 *arg0, s16 *arg1, s16 *arg2, s16 *arg3);
extern void func_1505D6F0(struct127 *, s32);
extern void func_15005818(struct108 *arg0, struct168 *arg1, f32 *arg2);
extern void func_15169040(s32 arg0, u8 arg1);

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

void func_15085430(struct127 *arg0, s32 arg1, s32 arg2) {
    s16 sp78[3];
    f32 sp6C[3];
    u8 sp6B;
    u8 sp6A;
    s32 sp64;
    s32 sp60;
    struct127 *oldObject;
    s32 oldIndex;
    struct {
        s32 unk0;
        u8 unk4;
    } sp50;
    s32 angle;

    func_15084D70(arg0->unk127, arg1, D_800D18A8, sp78, sp6C, &sp6B, &sp6A, &sp60, &sp64, arg2, 0);

    oldObject = D_800D154C;
    oldIndex = D_800C3E78;
    D_800D154C = arg0;
    D_800C3E78 = arg0 - D_800CC2D0;
    func_1506AD30(arg0, 800.0f, 1);
    D_800D154C = oldObject;
    D_800C3E78 = oldIndex;

    arg0->x_position = sp78[0];
    arg0->y_position = sp78[1];
    arg0->old_x_position = arg0->x_position;
    arg0->old_y_position = arg0->y_position;
    arg0->z_position = sp78[2];
    arg0->old_z_position = arg0->z_position;

    angle = sp6A << 8;
    arg0->unk7A = angle;
    arg0->unk78 = angle;
    arg0->unk76 = angle;
    arg0->unk40 = (s16)(angle + 0x4000) * 0.0054931640625f;

    arg0->unkB8 = (sp6B * 360) >> 8;
    while (arg0->unkB8 > 180.0f) {
        arg0->unkB8 -= 360.0f;
    }

    arg0->unk28 = 0.0f;
    arg0->unk180 = arg0->y_position;
    if (arg0->unk31C != NULL) {
        func_1507C3E0(arg0, (s16 *)&arg0->unk31C->unk114, (s16 *)&arg0->unk31C->unk116,
                      (s16 *)&arg0->unk31C->unk118);
    }
    arg0->unk1CC = arg0->y_position;
    arg0->unk2F8 &= ~0x10;
    arg0->unk22C |= 0x200;
    arg0->unk164 = 0.0f;
    arg0->unk168 = 0.0f;
    arg0->unk16C = 0.0f;
    arg0->unk170 = 0.0f;

    if (arg0->unk127 != 0xFF) {
        *((u8 *)arg0->unk31C + 0x23) = sp64;
        if (D_800BE616 && D_800D18A8) {
            func_1505D6F0(arg0, arg0 - D_800CC2D0);
        }
        if ((arg0->unk31C->unk78 == 0) && (arg0->unk31C->unk19B != 4) && (arg0->unk31C->unk19B != 7)) {
            arg0->unk83 = 0;
        }
    } else {
        arg0->unk83 = 0;
    }

    if (arg0->camera != NULL) {
        func_15005818(arg0->camera, (struct168 *)arg0, sp6C);
    }
    sp50.unk0 = (s32)arg0;
    sp50.unk4 = arg0->unique_id;
    func_15169040((s32)&sp50, 4);
}

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
