/* ============================================================================
 * PARKED NEAR-MISS  func_150D1C30  (game_FF0E0.c) -- LAST pragma in this TU.
 * Measured 2026-08-13 with the stale-object guard (rm .o AND the asm-processor
 * intermediate, then make, then assert the object exists). Calibration: with the
 * #pragma in place the same harness prints CURRENT (0).
 *
 * BEST STRUCTURE (the body below, `continue` form): size 828 == golden 828,
 *   score 1538 with and without -R.
 * BEST SCORE (plain `if (part != NULL) { ... }` instead of the early exit):
 *   size 832 (+1 instruction), score 1446.
 * Both are ONE loop-invariant candidate away; the 1446 form is NOT closer --
 * it is one instruction LONGER (cookbook: count ins/del, not the score).
 *
 * FRAME DECODE (framesize 0xf0), read off the golden .s -- this is what fixes
 * the declaration list and it reproduces every sp offset exactly:
 *   0x00..0x3b arg build (func_150AC9C0 takes 15 args -> stack slots 0x10..0x38)
 *   0x48 $f20, 0x50..0x74 $s0..$s8/$ra          -> arg-build+saved = 0x00..0x77
 *   0x78..0x87 compiler temp area (16 B, unreferenced)
 *   0x88..0xef HOME AREA = 104 B = sum(sizeof(local)), top-down in decl order:
 *       0xec  4  sub          (pointer, lives in $s2)
 *       0xe8  4  part         (pointer, lives in $s0)
 *       0xa8 64  mtx[4][4]    (passed to func_150A8050 and func_150A7960)
 *       0xa4  4  i            (lives in $s3)
 *       0xa0/0x9c/0x98  3xf32 outputs of func_150A7960
 *       0x94/0x90/0x8c  3xf32 + 0x88 f32 outputs of func_150AC9C0
 *   The two dead 4-byte holes at 0xe8/0xec and the hole at 0xa4 ARE the three
 *   register-resident locals' homes; that is how the list was recovered.
 *
 * THE RESIDUAL, both forms: golden fills its four free callee-saved slots with
 *   s5=&D_800A08F0  s6=12  s7=&sp98  s8=&sp9C
 * and rematerialises `addiu a0,sp,0xa8` (the matrix) and `li at,6` (the loop
 * bound) inside the loop. We get one extra hoisted candidate which displaces
 * &sp9C and rotates every downstream register by one:
 *   plain-if form : s5=&mtx  s6=&D_800A08F0 s7=12 s8=&sp98   (+`move a0,s5` x2)
 *   continue form : s5=6     s6=&D_800A08F0 s7=12 s8=&sp98   (exact size)
 *
 * MEASURED NEGATIVES (all with the guard; every number is a real differ score):
 *   plain-if base, func_150A7960 proto `f32 *`, call `&mtx[0][0]` ....... 1446
 *   proto `f32 mtx[4][4]`, call `mtx` ................................... 1446
 *   proto `f32 *`, call `mtx` (implicit ptr conversion, warns) .......... 1446
 *   proto `void *`, call `mtx` .......................................... 1446
 *   `f32 mtx[16]` flat + casts .......................................... 1446
 *   outer call spelled `(f32 (*)[4])&mtx[0][0]` ......................... 1446
 *   call `mtx[0]` with `f32 *` proto .................................... 1446
 *   swap the `sub`/`part` declaration order ............................. 1446
 *   sp98/sp9C/spA0 as `f32 dir[3]`, sp8C/90/94 as `f32 hit[3]` .......... 1446
 *     (the array form is frame-identical -- 0x98..0xa3 and 0x8c..0x97 --
 *      and byte-identical output, so it is score-neutral, not a lever)
 *   `goto next;` early exit instead of `continue` ....................... 1538 (828 B)
 *   dir/hit arrays + `continue` ......................................... 1538 (828 B)
 *   do/while + `continue` + `} while (++i != 6);` ....................... 1748
 *   do/while + `goto next;` + explicit `i++` before the test ............ 1748
 *   `continue` in the ELSE-branch loop too (kills its unrolling) ........ 5766 (788 B)
 * DIAGNOSTIC (not a candidate, semantically wrong -- kept for the finding):
 *   pass `(f32 (*)[4])arg0` to func_150A8050 so &mtx has ONE reference:
 *   IDO STILL hoists it into $s5 with `move a0,s5`. So the hoist is not the
 *   two-reference CSE across the call -- it is LICM of a register-passed
 *   `lda` of a local, and no spelling of the address reaches it.
 *
 * WHAT IS STILL OPEN: the early exit is the only lever found that removes the
 * &mtx hoist, and it costs the `6`. Something must remove BOTH. Next moves:
 * seed conker/permuter_tu.sh with this body (it has a real structural handle --
 * 2 ins / 2 del -- so the "loop-invariant ranking tie" BAIL RULE does not apply
 * yet), or find the form in which the loop test's constant keeps ONE reference
 * while the guard still early-exits.
 * ============================================================================ */

#include <ultra64.h>
#include "functions.h"
#include "variables.h"


typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Vec150D1F6C;

typedef struct {
    Vec150D1F6C unk0;
    f32 unkC;
} Arg150D1F6C;

typedef struct {
    u8 pad0[0x18];
    Vec150D1F6C unk18;
    u8 pad24[0x18];
    f32 unk3C;
    s32 unk40;
    u8 unk44;
} Sub150D1F6C;

typedef struct {
    u8 pad0[0x40];
    Vec150D1F6C unk40;
} Obj150D1F6C;

/* --- func_150D1C30 -------------------------------------------------- */

typedef struct {
    u8  pad0[0x9];
    u8  unk9;
    u8  padA[0x4];
    s16 unkE;
    s16 unk10;
    s16 unk12;
    u8  pad14[0x1B];
    u8  unk2F;
} Node150D1C30;

typedef struct {
    u8  pad0[0x14];
    Node150D1C30 *unk14;
} Part150D1C30;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    Part150D1C30 *unk24;
    Part150D1C30 *unk28;
    Part150D1C30 *unk2C;
    Part150D1C30 *unk30;
    Part150D1C30 *unk34;
    Part150D1C30 *unk38;
    f32 unk3C;
    s32 unk40;
    u8  unk44;
} Sub150D1C30;

typedef struct {
    u8  pad0[0x6C];
    u8  unk6C;
} Obj150D1C30;

extern f32 D_800A08F0[][3];
extern void func_150A7960(f32 mtx[4][4], f32 x, f32 y, f32 z, f32 *ox, f32 *oy, f32 *oz);
extern s32 func_150AC9C0(f32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1, void *arg6,
                         void *arg7, f32 *arg8, f32 *arg9, f32 *arg10, f32 *arg11,
                         s32 *arg12, s32 arg13, f32 arg14);

void func_150D1C30(struct260 *arg0) {
    Sub150D1C30 *sub;
    Part150D1C30 *part;
    f32 mtx[4][4];
    s32 i;
    f32 spA0;
    f32 sp9C;
    f32 sp98;
    f32 sp94;
    f32 sp90;
    f32 sp8C;
    f32 sp88;

    sub = (Sub150D1C30 *)((u8 *)arg0 + 0x28);
    if (((Obj150D1C30 *)arg0)->unk6C & 1) {
        sub->unkC += sub->unk18 * D_800BE9A4;
        sub->unk10 += sub->unk1C * D_800BE9A4;
        sub->unk14 += sub->unk20 * D_800BE9A4;
        func_150A8050(mtx, sub->unkC, sub->unk10, sub->unk14);

        for (i = 0; i != 6; i++) {
            part = ((Part150D1C30 **)sub)[i + 9];
            if (part == NULL) {
                continue;
            }
            {
                func_150A7960(mtx, D_800A08F0[i][0], D_800A08F0[i][1], D_800A08F0[i][2],
                              &sp98, &sp9C, &spA0);
                if (func_150AC9C0(sub->unk0, sub->unk4, sub->unk8, sp98, sp9C, spA0, NULL, NULL,
                                  &sp8C, &sp90, &sp94, &sp88, NULL, 0, 0.0f) != 0) {
                    part->unk14->unk9 = 0;
                    part->unk14->unkE = sp8C;
                    part->unk14->unk10 = sp90;
                    part->unk14->unk12 = sp94;
                    part->unk14->unk2F = sub->unk3C * sp88;
                } else {
                    part->unk14->unk9 = 1;
                }
            }
        }
    } else {
        for (i = 0; i != 6; i++) {
            part = ((Part150D1C30 **)sub)[i + 9];
            if (part != NULL) {
                part->unk14->unk9 = 1;
            }
        }
    }
}

void func_150D1F6C(struct260 *arg0, s32 arg1, u8 arg2) {
    Sub150D1F6C *sub;
    Arg150D1F6C *arg;

    sub = (Sub150D1F6C *)((s32)arg0 + 0x28);
    if (arg2 == 0x32) {
        arg = (Arg150D1F6C *)arg1;
        sub->unk18 = arg->unk0;
        sub->unk3C = arg->unkC;
    dummy_label_150D1F6C_1: ;
    } else {
        if ((arg2 == 0x30) || (arg2 == 0x31)) {
            if (arg1 == sub->unk40) {
                if (arg2 == 0x30) {
                    sub->unk44 |= 1;
                } else {
                    sub->unk44 &= ~1;
                dummy_label_150D1F6C_2: ;
                }
            }
        } else if (arg2 == 0x4E) {
            ((Obj150D1F6C *)arg0)->unk40 = *(Vec150D1F6C *)&D_800A5480;
        } else if (arg2 == 0x4F) {
            func_1516972C((struct102 *)arg0);
        }
    }
}

void func_150D2054(struct260 *arg0) {
    s32 i;
    s32 *p;
    void *ptr;

    p = (s32 *)((u8 *)arg0 + 0x28);
    i = 0;
    do {
        ptr = (void *)p[i + 9];
        if (ptr != NULL) {
            func_1516972C((struct102 *)ptr);
        }
        i++;
        i = (u8)i;
    } while (i < 6);
}

extern void func_150D2054(struct260 *);

void func_150D20B0(struct260 *arg0) {
    func_150D2054(arg0);
    func_15149368(arg0);
}

void func_150D20DC(struct260 *arg0) {
    func_150D2054(arg0);
    func_1514933C(arg0);
}
