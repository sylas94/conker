/* ============================================================================
 * PARKED NEAR-MISS  func_150D1C30  (game_FF0E0.c) -- LAST pragma in this TU.
 * 2026-08-13 WAVE 3:  445 -> 400, at the exact golden size of 828 bytes, frame
 * 0xf0 == golden.  Measured with the stale-object guard (rm the .o AND the
 * asm-processor intermediate, make, assert the object exists), everything
 * through buildlock.  Calibration: with the #pragma in place the harness
 * prints CURRENT (0).  400 with -R and 400 without -R.
 *
 * ============ THE GAIN: THE ELSE ARM NEEDS ITS OWN POINTER LOCAL ============
 * Wave 2's residual was eleven rows, nine of them the $v0/$v1 swap between the
 * loaded pointer and the unrolled cursor copy.  ALL NINE ARE NOW GONE.  The
 * whole else arm -- both peeled slots and all four main-body slots -- matches
 * golden register for register.
 *
 * The diagnosis came from the `bind part' measurement, decoded rather than
 * ranked.  Binding `part' in the else arm (558) does NOT put the loaded pointer
 * in $v0; it puts it in $s0 and the CURSOR STILL TAKES $v0:
 *      golden  280: lw v0,0x24(s2)   284: move v1,s2
 *      bind    280: lw s0,0x24(s2)   284: move v0,s2
 * i.e. in our compile the cursor is allocated FIRST whatever the loaded pointer
 * is doing.  Golden allocates the loaded pointer first, and the only thing that
 * outranks a compiler-generated induction cursor is a SOURCE VARIABLE.  `part'
 * cannot be it -- its web then spans both arms of the outer if, is live across
 * the if arm's calls, and is forced into a callee-saved register (that is the
 * whole 558).  So golden has a SECOND pointer local, used only in the else arm,
 * where there are no calls, so it is free to live in $v0.
 *
 * THE FRAME OBJECTION WAS WRONG, and this is the transferable lesson.  Wave 2
 * ruled a new local out because sum(sizeof(local)) is exactly 104 == the home
 * area.  But a local declared LAST lands in the compiler-temp slack below the
 * home area and the frame does not move:
 *      `Part150D1C30 *p' declared LAST ......... 400, frame 0xf0, size 828
 *      `Part150D1C30 *p' declared SECOND ....... 473, frame 0xf0 but EVERY sp
 *          offset shifts down 4 (0xa8->0xa4, 0x9c->0x98, ... 0x88->0x84)
 *      a SECOND extra local (`s32 k' as a separate else-arm counter),
 *          either declaration order .............. 811, frame 0xf8
 * so there is room for EXACTLY ONE spare 4-byte local, and only in last place.
 * (The same wave closed func_150825C0 by adding TWO f32 locals in last place
 * without moving its frame -- see tools/nearmiss/func_150825C0.c.)
 *
 * ================= THE RESIDUAL: TWO ROWS, ONE PEEPHOLE =====================
 *   golden  2a8: beqz  v0,2b8      ours  2a8: beqzl v0,2bc
 *           2ac: nop                     2ac: lw    v0,0x24(s1)
 * 400 = 2 x 200 (replaced instruction).  Everything else in the function is
 * byte-identical, registers included.
 *
 * WHAT THE PEEPHOLE IS.  as1 converts `beqz X,L / nop' into `beqzl X,L+4' by
 * DUPLICATING the last instruction of the fall-through block into the (now
 * nullified-on-fall-through) delay slot and moving the join label past it.  It
 * does this at FIVE of the six unrolled guards in golden too -- guard 1 gets
 * `beql v0,zero,2a4' with `lw v0,0x28(v1)', guards 3..6 likewise.  Only guard 2
 * is left alone, and guard 2 is exactly the peel/main-body seam: its join label
 * 2b8 is the first instruction of the four-times-unrolled main body
 * (`lw v0,0x24(s1)', s1 = sub + t0, t0 = 2*4 hoisted to the ENTRY block as
 * `li s3,2 / sll t0,s3,0x2').  So golden keeps a block boundary at 2b8 that our
 * compile does not, and as1 therefore finds `sb s4,0x9(t9)' as the fall-through
 * block's last instruction -- unsafe to duplicate ($t9 undefined on the taken
 * path) -- and gives up.  Ours sees the load there instead and fills.
 * The two rows are ONE cause; whatever restores that boundary takes 400 -> 0.
 *
 * ============ MEASURED NEGATIVES, wave 3, all on the 400 base ==============
 * EIGHT mutually exclusive variants score EXACTLY 400 with the IDENTICAL
 * two-row residual.  Per the seven-axis rule these are NOT one axis -- they
 * span subscript spelling, guard spelling, loop shape, which local is which,
 * assignment placement and physical line layout -- so the residual is
 * invariant under all six of those axes:
 *   `p = ...; if (p != NULL)'  (the shipped form) .................... 400
 *   `if (p)' bare truthiness ........................................ 400
 *   `if ((p = ((Part **)sub)[i + 9]) != NULL)' assignment in guard ... 400
 *   `p = (&sub->unk24)[i]' member-address subscript .................. 400
 *   bound `i < 6' instead of `i != 6' ............................... 400
 *   `i = 0; do { ... i++; } while (i != 6);' ........................ 400
 *   the two pointer locals SWAPPED (if arm uses the last-declared one,
 *     else arm uses `part') ......................................... 400
 *   every statement split onto its own physical line ................ 400
 * and these are worse:
 *   the whole else-arm loop on ONE physical line ............ 520 (828 B)
 *     -- it swaps entry-block rows 3c/48 (`addiu s2,s0,0x28' vs
 *        `sll t0,s3,0x2'), which PROVES -g3 line layout is a live axis
 *        here; it just does not reach the peephole
 *   else arm binds `part' (one web across both arms) ....... 558 (828 B)
 *     -- also swaps $s0/$s1 in the prologue
 *   `p' declared second instead of last .................... 473 (828 B)
 *   `s32 k' as a separate else-arm counter ................. 811 (828 B, 0xf8)
 *   else arm given the if arm's `for (i = 0;;) { ... i++; if (i == 6)
 *     break; }' treatment ............................ 3520 (728 B)
 *     -- this DESTROYS the unroll: `move v0,zero' replaces golden's
 *        `li s3,2', i.e. the 2+4 peel is a property of the `for (i = 0;
 *        i != 6; i++)' header shape.  Do not touch that header.
 *   `if (p == NULL) continue;' ............................ 5656 (788 B, 0xd8)
 *   index off `arg0' rather than `sub' ................... 1130 (824 B)
 *
 * STILL TRUE FROM WAVE 2 -- do not re-measure:
 *   the if arm's `for (i = 0;;) { ... i++; if (i == 6) break; }' shape is
 *   worth 980 (it stops the constant 6 becoming a LICM candidate that evicts
 *   golden's fourth hoisted invariant &sp9C), and `for (i = 0;;)' rather than
 *   a separate `i = 0;' statement is worth a further 210.  Both are in the
 *   shipped source below.
 *
 * FRAME DECODE (framesize 0xf0), unchanged and still exact:
 *   0x00..0x3b arg build (func_150AC9C0 takes 15 args -> slots 0x10..0x38)
 *   0x48 $f20, 0x50..0x74 $s0..$s8/$ra
 *   0x88..0xef HOME AREA, top-down in declaration order:
 *       0xec sub / 0xe8 part / 0xa8 mtx[4][4] / 0xa4 i /
 *       0xa0 spA0 0x9c sp9C 0x98 sp98 / 0x94 sp94 0x90 sp90 0x8c sp8C 0x88 sp88
 *   and `p', declared last, takes 0x84 out of the temp slack.
 *
 * NOT A ROUTE: conker/permuter_tu.sh SELFTEST FAILS on this TU (compile.sh's
 * IDO invocation dies with `as1: Error: <tmp>/tu.c, line 255: No such file or
 * directory'), so every score it would report is meaningless.
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
    Part150D1C30 *p;

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
        for (i = 0; i != 6; i++) {
            p = ((Part150D1C30 **)sub)[i + 9];
            if (p != NULL) {
                p->unk14->unk9 = 1;
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
