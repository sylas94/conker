/* ============================================================================
 * PARKED NEAR-MISS  func_150D1C30  (game_FF0E0.c) -- LAST pragma in this TU.
 * 2026-08-13 WAVE 2:  1425 -> 445, at the exact golden size of 828 bytes.
 * Measured with the stale-object guard (rm the .o AND the asm-processor
 * intermediate, make, assert the object exists), everything through buildlock.
 * Calibration: with the #pragma in place the same harness prints CURRENT (0).
 * 445 with -R and 445 without -R.
 *
 * WHAT IS NOW EXACT: the prologue, the entry block, the whole float update
 * block, the func_150A8050 call, the ENTIRE if-arm loop -- preheader, body,
 * both calls, the float->int conversion sequence and the latch -- and the last
 * four unrolled iterations of the else arm.  The diff is ELEVEN rows, all in
 * the FIRST TWO unrolled iterations of the else arm (see the residual below).
 *
 * THE TWO GAINS, and both are the SHAPE of the if-arm loop, not its spelling.
 *
 * (1) 1425 -> 655: move the exit test OUT OF THE LATCH.
 *       for (i = 0; i != 6; i++) { ... }            <- 1425
 *       for (;;)  { ... i++; if (i == 6) break; }   <-  655
 *     Diagnosis first, then the fix.  Golden's latch is
 *         addiu s3,s3,1 / addiu at,zero,6 / bne s3,at / addiu s1,s1,4
 *     -- `6' is an ASSEMBLER-EXPANDED branch immediate through $at, i.e. IDO
 *     never gave it a register.  With the bound in the `for' header IDO makes
 *     the constant a loop-invariant temp and LICM hoists it AT RANK ONE, which
 *     evicts golden's fourth invariant &sp9C:
 *         golden  s5=&D_800A08F0  s6=12  s7=&sp98  s8=&sp9C   (`li at,6' in the latch)
 *         ours    s5=6  s6=&D_800A08F0  s7=12  s8=&sp98       (&sp9C remat'd inside)
 *     The hoisted list is golden's list with `6' PREPENDED, so the whole
 *     downstream register file rotated by one -- that single hoist was 980 of
 *     the 1425.  Writing the test as an explicit `if (i == 6) break;' inside
 *     the body leaves the branch a plain compare-with-literal and the constant
 *     never becomes a candidate.
 *     PROOF the else arm was NOT involved (this was the wave's working theory
 *     and it is WRONG): with the else arm's bound changed to 5 the `li s5,6'
 *     is still emitted, and with the if arm's bound changed to 7 the hoist
 *     still happens.  The two literals are independent.
 *
 * (2) 655 -> 445: put the induction init back in the for-header.
 *       i = 0; for (;;) { ... }   <- 655  (`move s3,zero' one instruction early)
 *       for (i = 0;;) { ... }     <- 445  (golden's preheader order exactly)
 *     Golden's preheader is  lui s5 / addiu s5 / move s3,zero / move s1,s2 ;
 *     a separate `i = 0;' statement schedules the `move s3,zero' before the
 *     `addiu s5,s5,%lo', which is one insert + one delete = 210 points.
 *
 * FRAME DECODE (framesize 0xf0), read off the golden .s -- unchanged, and it
 * still reproduces every sp offset exactly:
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
 *
 * THE RESIDUAL -- 11 rows, ONE cause, in the first two unrolled else-arm slots:
 *   golden  280: lw   v0,0x24(s2)     ours  280: lw   v1,0x24(s2)
 *           284: move v1,s2                 284: move v0,s2
 *           2a8: beqz  v0,2b8               2a8: beqzl v1,2bc
 *           2ac: nop                        2ac: lw    v0,0x24(s1)
 * i.e. golden puts the LOADED POINTER in $v0 and the unrolled cursor copy in
 * $v1; we do the reverse.  That swap is what lets OUR scheduler fill the
 * delay slot at 2a8 (our branch tests $v1 while the next load writes $v0, so
 * beqz+nop becomes beqzl+lw) -- golden could not, because both were $v0.  So
 * the two 200-point opcode rows are a CONSEQUENCE of the register swap, not a
 * separate problem: flip $v0/$v1 and all eleven rows go together.
 *   Order-of-definition reading: golden defines the guard's load first and the
 *   cursor copy second; we emit the cursor init first.  The cursor is the
 *   strength-reduced induction pointer of the unrolled else loop.
 *
 * MEASURED NEGATIVES, 2026-08-13 wave 2.  Everything below is a real differ
 * score taken with the guard; size is 828 (== golden) unless noted.
 *   ON THE 445 BASE -- EIGHT mutually exclusive respellings, ALL EXACTLY 445,
 *   which is the N-NO-OPS signal for the else-arm/declaration axis:
 *     else arm `if (p)' bare truthiness ............................. 445
 *     else arm `!= 0' instead of `!= NULL' .......................... 445
 *     else arm bound `i < 6' ........................................ 445
 *     else arm `(&sub->unk24)[i]' instead of the whole-struct cast ... 445
 *     else arm `((Part **)((u8 *)sub + 0x24))[i]' ................... 445
 *     else arm as `i = 0; do { ... } while (++i != 6);' ............. 445
 *     swap the `sub'/`part' declaration order ....................... 445
 *     outer test spelled `(... & 1) != 0' ........................... 445
 *   and these are worse:
 *     else arm BINDS `part' ......................................... 558
 *       (still the right call, but the penalty is 113 now, not 113+the
 *        prologue swap the old note described -- re-measured on this base)
 *     else arm `if (p == NULL) {} else {...}' .............. 5671 (788 B)
 *     else arm `if (p == NULL) continue;' ................. 5671 (788 B)
 *     else arm given the `for (;;)' treatment too ......... 3720 (728 B)
 *     `sub' re-assigned at the top of the if arm .................... 885
 *   ON THE 655 BASE:
 *     `i = 0; for (;;)' (the wave's first fix) ...................... 655
 *   ON THE 1425 BASE -- TWELVE more mutually exclusive loop-guard respellings,
 *   ALL EXACTLY 1425, which is why the guard axis was abandoned for the SHAPE
 *   axis (this is the lesson of the wave):
 *     `6 != i' on the if arm / on the else arm / on both ........... 1425
 *     `++i' instead of `i++' ...................................... 1425
 *     else arm as a do/while ...................................... 1425
 *     else arm bound `i < 6' ...................................... 1425
 *     `i != 3 + 3' on either arm .................................. 1425
 *     `9 + i' instead of `i + 9' .................................. 1425
 *     `part == 0' instead of `part == NULL' ....................... 1425
 *     `(&sub->unk24)[i]' .......................................... 1425
 *     D_800A08F0 as an array of 3-float structs ................... 1425
 *     `0.f' instead of `0.0f' ..................................... 1425
 *     truthiness on the func_150AC9C0 result ...................... 1425
 *     `sp88 * sub->unk3C' instead of `sub->unk3C * sp88' .......... 1425
 *     swap the `sub'/`part' declaration order ..................... 1425
 *   and, also from the 1425 base:
 *     bind `part' AFTER the guard, guard re-reads .......... 1550 (832 B)
 *     ditto with a bare `if (!p)' guard ................... 1550 (832 B)
 *     plain `if (p != NULL)' with `part' bound inside ..... 1648 (836 B)
 *     plain `if (p != NULL)' with `part' bound before ..... 1333 (832 B)
 *     `i = 0; do { ... } while (++i != 6);' ....................... 1635
 *     `i = 0; do {...; i++; } while (i != 6);' ............ 1543 (832 B)
 *     `i = 0; while (i != 6) {...; i++; }' ................ 1543 (832 B)
 *
 * NOT A ROUTE: conker/permuter_tu.sh SELFTEST FAILS on this TU (compile.sh's
 * IDO invocation dies with `as1: Error: <tmp>/tu.c, line 255: No such file or
 * directory'), so every score it would report is meaningless.  Fix the harness
 * before believing any permuter number here.
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

        for (i = 0;;) {
            part = ((Part150D1C30 **)sub)[i + 9];
            if (part != NULL) {
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
            i++;
            if (i == 6) {
                break;
            }
        }
    } else {
        /* Deliberately does NOT bind `part'.  Binding it here makes ONE web that
           spans both arms of the outer if, so it holds a callee-saved register
           across the whole function.  Golden's else arm uses the caller-saved
           $v0/$v1 pair, which is only reachable when `part' is confined to the
           if arm.  Re-measured on the 445 base: bind -> 558, don't bind -> 445,
           both at the exact 828 bytes. */
        for (i = 0; i != 6; i++) {
            if (((Part150D1C30 **)sub)[i + 9] != NULL) {
                ((Part150D1C30 **)sub)[i + 9]->unk14->unk9 = 1;
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
