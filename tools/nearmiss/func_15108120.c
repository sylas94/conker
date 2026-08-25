/* NEAR-MISS PARK -- game_1355D0 / func_15108120  (432 B).  fastscore mism=43, n=108/108,
 * frame=-136 (0x88, GOLDEN'S FRAME).  Progression: 54 -> 43 this session.
 *
 * READ THIS FIRST: THE OLD HEADER'S ARITHMETIC IS VOID.  It claimed golden's .s was
 * "105 real words + 3 pad nops" and that fastscore charged a phantom 30.  That was the
 * pre-fix tool (objdump -d collapsing runs of zero words).  With the fixed tool the length is
 * EXACT at n=108/108 for every candidate below.  Read `mism` directly; there is no pad
 * correction.  The old numbers map as: old "84 raw / 54 pad-corrected" == 54 today.
 *
 * THIS FILE IS NOW A COMPLETE COMPILABLE TU (the old one was a fragment and CCFAILed):
 *     python3 tools/fastscore.py game_1355D0 func_15108120 tools/nearmiss/func_15108120.c
 *
 * ======================= WHAT MOVED IT: THE FRAME IS SOLVED =======================
 * Ours was 0x90, golden 0x88 -- 8 extra bytes of compiler temp, with the 84-byte named-local
 * area identical but shifted.  ROOT CAUSE, localised by ADDITIVE bisection on a skeleton
 * (start from three locals + three calls, which reserves 4 bytes of temp, then add the real
 * body back one GROUP at a time).  The previous session only ever did single-statement
 * DELETION from the full function, which is why it found nothing: no single statement is
 * responsible, a PAIR of them is.
 *
 *     READING THE SAME GLOBAL TWICE RESERVES 8 BYTES OF COMPILER TEMP.
 *         sp34.unk30 = D_800A2438;
 *         sp34.unk34 = D_800A2438;     <- IDO CSEs the load and mints a spill slot for it
 *
 * Bisection evidence (savearea read off the prologue every time, as the old header warns):
 * skeleton 0x80 / temps 4; + vectors + RNG + int fills + struct copy still 0x88 / temps 4;
 * adding the float group takes it to 0x90.  Inside the float group, dropping EITHER half of
 * the doubled pair returns it to 0x88, while all five singly-read floats together stay at
 * 0x88.  So it is the DOUBLING -- not the number of float stores, and not the (s32)arg1
 * spill, which the u8 prototype had already removed.
 *
 * THE FIX -- chain the assignment so there is one read, not two:
 *         sp34.unk30 = sp34.unk34 = D_800A2438;
 * Frame becomes 0x88 and all 28 stack-offset rows vanish in one step.  Tied at 43: the
 * reversed chain, and `unk34 = D_800A2438; unk30 = sp34.unk34;` either way round -- a ranking
 * tie, so the exact spelling below is a choice, not a measurement.  (The old header's claim
 * that `unk34 = unk30` is "3 instructions too long" was the broken tool talking; it is
 * n=108/108, same as everything else here.)
 *
 * ======================= WHAT IS LEFT: ALL 43 ROWS ARE ONE THING =======================
 * Golden hoists  lui $at,%hi(D_800A2438) / lwc1 $f0,%lo(D_800A2438)  into the FIRST slot after
 * the func_150E83AC call and keeps that value in $f0 for ~40 instructions, storing it to
 * 0x64/0x68 only after the six `sh` stores.  We emit the load where the source statement is,
 * into $f8, and store it immediately.  Because golden's value has the long live range it takes
 * $f0, and every later FP value shifts one slot in the allocation:
 *     golden  f0=D_800A2438  f8=8.0f   f10=10.0f  f16=243C  f18=2440  f4=2444  f6=40.0f
 *     ours    f8=D_800A2438  f10=8.0f  f16=10.0f  f18=243C  f4=2440   f6=2444  f8=40.0f
 * Every remaining row is that one-slot rotation plus the displaced stores.  Fix the hoist and
 * the rotation should follow: the register assignment is a CONSEQUENCE of the live range.
 *
 * THE CRUEL PART, and where the next attempt should start.  The UNCHAINED spelling already
 * produces golden's register ($f0) and a long live range -- its load lands at idx50 and its
 * stores at idx78/79, against golden's idx33 and idx73/74.  So the CSE is what buys $f0, and
 * the CSE is also what costs the 8 bytes of frame.  In every spelling measured the two effects
 * are welded together.  Golden has BOTH the CSE's allocation AND no temp.  What is needed is
 * something that makes IDO place a doubled global's load at the top of the basic block without
 * minting a spill slot for it.
 *
 * ======================= MEASURED AND REJECTED THIS SESSION =======================
 *   * ASCENDING FIELD ORDER.  The matched twin func_151036B4 (game_130B40.c:55) fills its
 *     identical descriptor in ascending field order, and IDO reorders the stores itself -- so
 *     golden's non-ascending STORE order is NOT proof of a non-ascending source, and the old
 *     header's inference on that point is RETRACTED.  Measured anyway: ascending scores 59
 *     unchained / 67 chained, against 54 / 43 for the order below.  The order below wins.
 *   * Scoping sp34 into a nested block (fill only; fill+call2; fill+call2+call3): COMPLETELY
 *     INERT, 54 -> 54.  "Nested-block locals get no frame slot" does not reach a 0x3C-byte
 *     struct here.
 *   * A block-scope `f32 t = D_800A2438;` feeding both stores -- the shape that closed
 *     func_15011D60 -- makes the frame GROW to 0x90: this f32 does get a frame slot.
 *     Function-scope likewise.  Bare blocks round the fill carrying `s32 n`, `u8 c`,
 *     `struct17 v`, or a `struct Conker15108120 *p`: 43 at best, 128 at worst.
 *   * Position of the doubled statement: 15 positions x 3 spellings.  Chained scores 37 at
 *     positions 0-2 and 43 from position 3 on -- but the 37 has the load in the right SLOT
 *     with the wrong register and its stores 34 slots early, i.e. a worse shape wearing a
 *     better number.  Treat 43 as the real best.  Unchained is 54-64 at every position.
 *   * RNG spelling: 7 forms (with/without the (u32) cast, with/without the U suffix, with/
 *     without the (s16), plus a named local) -- all inert.  The canonical matched idiom is
 *     game_1312F0.c:62 `(s16)(func_150ADA20() % 0x3EU + 0x78)`; it scores the same as ours.
 *   * `extern const f32 D_800A2438;` (and const on all five): inert.  A 5-element array view
 *     of the 0x800A2434 table: 124, and it loses 4 instructions.
 *   * conker/Makefile has NO per-TU OPT_FLAGS override for game_1355D0; -O2 -g3 is the build.
 *
 * PERMUTER: `./permuter_tu.sh selftest permuter_tu/func_15108120` FAILS.  Check (b2), the
 * pycparser round-trip, yields an object with no func_15108120 in it at all, so (c) has no
 * base score and all four of (d)'s live perturbations read as score-invisible.  Check (e)
 * reports that isolation DIFFERS from the in-TU build.  The harness is NOT trustworthy on this
 * TU and no permuter number from it should be believed.
 *
 * STILL TRUE FROM THE PREVIOUS SESSION (verified, do not re-derive): func_15136C3C's 7th
 * parameter is u8, which removes the (s32)arg1 CSE spill -- func_15152190's 7th is PINNED to
 * s32 by the matched func_151036B4 and must stay s32; u8 arg1 and s32 arg2 are required
 * because golden re-reads lbu 0x8F(sp) / lw 0x90(sp) at each call site; func_150E83AC's 3rd
 * parameter must stay u8 (+40 as s32); declaration order of the three locals is inert.
 *
 * The function below replaces the single remaining
 *   #pragma GLOBAL_ASM("asm/nonmatchings/game_1355D0/func_15108120.s")
 * in conker/src/game_1355D0.c, which is UNTOUCHED and still holds its pragma.
 */
#include <ultra64.h>
#include "functions.h"
#include "variables.h"

struct Conker15108120 {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ struct17 unk08;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
};

extern s32 D_800A2430;
extern f32 D_800A2434;
extern f32 D_800A2438;
extern f32 D_800A243C;
extern f32 D_800A2440;
extern f32 D_800A2444;

void func_150E83AC(struct17 *, s16, u8, s32);
void func_15152190(struct Conker15108120 *, s32 *, f32 *, s32, f32, s32, s32, s32);
void func_15136C3C(struct127 *, s32, s32, s32, s32, s32, u8, s32);

void func_15108120(struct127 *arg0, u8 arg1, s32 arg2) {
    struct17 sp7C;
    struct17 sp70;
    struct Conker15108120 sp34;

    sp7C.unk0 = arg0->x_position;
    sp7C.unk4 = arg0->y_position;
    sp7C.unk8 = arg0->z_position;
    sp70.unk0 = arg0->x_position;
    sp70.unk4 = arg0->y_position + 30.0f;
    sp70.unk8 = arg0->z_position;
    func_150E83AC(&sp7C, (s16)((u32)func_150ADA20() % 0xC9U + 0x1F4), arg1, arg2);
    sp34.unk00 = 0xF;
    sp34.unk04 = 8;
    sp34.unk08 = sp70;
    sp34.unk14 = 0;
    sp34.unk16 = 0xFF;
    sp34.unk18 = -0x40;
    sp34.unk1A = 0x29;
    sp34.unk2C = 0x27;
    sp34.unk2E = 0x14;
    sp34.unk30 = sp34.unk34 = D_800A2438;
    sp34.unk1C = 8.0f;
    sp34.unk20 = 10.0f;
    sp34.unk24 = D_800A243C;
    sp34.unk28 = D_800A2440;
    sp34.unk38 = D_800A2444;
    func_15152190(&sp34, &D_800A2430, &D_800A2434, 1, 40.0f, 0, arg1, arg2);
    func_15136C3C(arg0, 1, 1, 1, 0, 0, arg1, arg2);
}
