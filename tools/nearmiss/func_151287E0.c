/* ============================================================================
 * PARKED NEAR-MISS: func_151287E0  (TU game_155C90, single-pragma TU, 308 words)
 *
 * SCORE          fastscore mism=288  frame=-72(0x48)  n=312/308   -O2 -g3 (default)
 * REAL DISTANCE  12 instructions.  `mism` is misleading here: two extra
 *                instructions early shift every later index, so the raw row count
 *                is ~288 while the actual edit distance (difflib over masked
 *                words, sp offsets masked) is TWELVE, all inside ONE 26-instruction
 *                window (ours[56..82] / gold[56..80]).  Everything from
 *                gold idx 83 to the end is instruction-for-instruction identical
 *                except for a uniform +4 on every *local* stack offset.
 *
 * TOOLING NOTE   Do not steer by fastscore's mism on this function.  A word-level
 *                difflib scorer is in the wave scratch as align.py; the recipe is
 *                  - mask reloc fields (as fastscore does)
 *                  - mask sp-relative immediates and branch displacements
 *                  - difflib.SequenceMatcher over the masked word lists
 *                It turned a useless 250..290 plateau into a 12..168 spread that
 *                actually ranks spellings.  Rebuild it before touching this again.
 *
 * ---------------------------------------------------------------------------
 * WHAT IS ALREADY SETTLED (do not re-litigate)
 *
 *  * OPT_FLAGS: measured -O2 -g3 = 12 edits, -O2 = 22, -O1 = 504, -g = 542.
 *    The tree default is correct.  This is NOT an OPT_FLAGS case.
 *
 *  * The float constants ARE LITERALS, not externs.  0x800A35B0..0x800A35CC is
 *    this TU's own anonymous literal pool: EIGHT floats, (1/90, 1/2700) x4, of
 *    which the SECOND pair (D_800A35B8/BC) is referenced by nothing in the whole
 *    repo.  Compiling the body with the literals `0.01111111138f` /
 *    `0.0003703703696f` reproduces that pool EXACTLY -- 8 entries, the 2nd pair
 *    dead, the live ones consumed at pool+0x00/0x04, +0x10/0x14, +0x18/0x1C,
 *    matching golden's three materialisation points (before the 3-way branch, and
 *    again after the func_150495B0 call at 0x15128AA4).
 *    An `extern f32 D_800A35C0;` spelling CANNOT byte-match: golden reloads the
 *    same value from a DIFFERENT pool slot (0x35C8) after the call, which only
 *    IDO's per-rematerialisation literal allocator produces.
 *    => shipping this requires a rodata migration:
 *         conker.us.yaml  [0x248070, rodata]
 *           ->            [0x248070, .rodata, game_155C90]
 *                         [0x248090, rodata]      <- D_800A35D0/D4 + jtbl_800A35D8
 *                                                    belong to game_156160
 *       then regenerate conker.ld (splat --modes ld).  Ownership is proven:
 *       game_14FF90.c references D_800A34B0..D_800A35AC and stops exactly one
 *       float short of 0x800A35B0.
 *
 *  * Assignment order of the five D_800894F0 row values is INERT: all 120
 *    permutations were measured, every one scores 12 or 13.  IDO assigns the
 *    stack slots canonically (by struct offset), not by declaration order --
 *    declaring `saved` after the floats (v06) also changed nothing.
 *
 * ---------------------------------------------------------------------------
 * THE REMAINING BLOCKER (one cause, three symptoms)
 *
 *   IDO births the `0.0f` constant used by `if (var_f2 < 0.0f)` in the WRONG
 *   BASIC BLOCK.  Golden materialises it as `mtc1 $zero,$f10` at .L15128920
 *   (gold idx 80), where it fills the c.lt.s->bc1fl hazard slot.  Ours emits it
 *   in the block BEFORE the `bnez $v1` (ours idx 67).  Everything else follows:
 *
 *     1. ours idx 67  `mtc1 zero,$f10`   +1 instruction in that block
 *     2. because that slot is taken, `lw $a0,0x2C($s0)` cannot land in the
 *        branch delay slot, so as1 converts `bnez` -> `bnezl` and orphans a
 *        duplicated `mtc1 zero,$f18`     +1 instruction
 *     3. ours idx 82 is a `nop` where golden has the mtc1                +0
 *     4. the 5 row loads then interleave with their stores instead of being
 *        batched 4-loads-then-4-stores (gold 56..63)
 *
 *   REMAINING DIFF ROWS (aligned; ours idx / gold idx)
 *     gold[56..59] lwc1 f4,0x4(v0) / f6,0x8 / f8,0xC / f10,0x10   (4 loads batched)
 *     gold[60..63] swc1 f4,0x40(sp)/f6,0x3C/f8,0x38/f10,0x34      (4 stores batched)
 *     gold[64]     lbu  v1,0x23C(s0)
 *     gold[65]     mtc1 at,f0          (30.0f, at still holds 0x41F0 from idx 24)
 *     gold[66]     lwc1 f16,0x0(v0)    <- row->unk0 loaded LAST, after the lbu
 *     gold[67]     bnez v1,.L15128908  (NOT bnezl)
 *     gold[68]     lw   a0,0x2C(s0)    (delay slot)
 *     gold[80]     mtc1 zero,f10       (at .L15128920)
 *   ours instead: lwc1 f4,0x4 / lwc1 f16,0x0 / mtc1 at,f0 / swc1 f4 / lwc1 f6 /
 *                 swc1 f6 / lwc1 f8 / swc1 f8 / lwc1 f10 / swc1 f10 / lbu v1 /
 *                 mtc1 zero,f10 / lw a0 / bnezl / mtc1 zero,f18(delay) ...
 *                 ... nop at idx 82.
 *
 *   FRAME: golden 0x50, ours 0x48.  Stack maps:
 *     golden  0x10 0x14 | 0x20(s0) 0x24(ra) | 0x28(f18 spill) | HOLE 0x2C-0x33 |
 *             0x34 0x38 0x3C 0x40 0x44 0x48 (locals) | HOLE 0x4C | 0x54(arg1 home)
 *     ours    0x10 0x14 | 0x20      0x24    | 0x2C(f18 spill) | (no hole) |
 *             0x30 0x34 0x38 0x3C 0x40 0x44 (locals) | 0x4C(arg1 home)
 *   i.e. golden's register allocator reserved THREE spill words (0x28/0x2C/0x30)
 *   and used only the lowest; ours reserved one.  8 unused bytes -> +8 frame.
 *   This is a live-range artefact of symptom (1), not an independent problem:
 *   v64 (`if (x<0) s=-1; if (!(x<0)) s=1;`) reaches frame=-80 by raising
 *   pressure in exactly this region -- but at 158 edits, so it is the wrong
 *   spelling.  Whoever fixes the 0.0f birth block should re-check the frame; it
 *   is likely to follow.
 *
 * ---------------------------------------------------------------------------
 * DO-NOT-REPEAT  (every spelling measured, edits = word-level difflib distance)
 *
 *   12  BASELINE (this file)
 *   12  a..e assignment order: all 120 permutations (6 score 12, 114 score 13-14)
 *   12  `sign` as a ternary                                   (v21)
 *   12  `if (0.0f > var_f2)` instead of `< 0.0f`              (v22)
 *   12  `var_f18 = 0;` instead of `0.0f`                      (v23)
 *   12  30.0f clamp as a ternary                              (v24)
 *   12  30.0f clamp written `var_f18 > 30.0f`                 (v30)
 *   12  `arg0->unk2C` hoisted into a local `flags`            (v26)
 *   12  var_f18 via ternary                                   (v43)
 *   12  `row` declared first / `f32 *row` with row[0..4]      (v42, v45)
 *   12  `arg0->unk23C` tested truthy / paren variations       (v46, v47)
 *   12  `var_f2 = var_f2 - (90.0f*sign)`                      (v61)
 *   12  val expression re-parenthesised                       (v66)
 *   13  `(c == a)` instead of `(a == c)`                      (v44)
 *   13  `var_f2 -= sign * 90.0f`                              (v62)
 *   14  a assigned last (b,c,d,e,a)                           (v02/x1)
 *   15  `var_f2 = arg0->unk390` hoisted above the f18 block   (v28)
 *   15  nested if instead of `||`                             (v25)
 *   16  `if (var_f2 >= 0.0f) s=1 else s=-1`                   (v60)
 *   19  f18 if/else inverted to `(unk23C==0 && a!=c)`         (v08)
 *   20  `a` assigned inside the condition `(a=row->unk0)==c`  (v11/v12/v16)
 *   35  `s32 idx = arg0->unk134;` local for the index         (v40/v41)
 *  104  `a` assigned after the if/else, cond uses row->unk0   (v50)
 *  106  a assigned after the clamp / before unk390 read       (v51, v53)
 *  114  `sign = 1.0f; if (x<0) sign = -1.0f;`                 (v29)
 *  116  no `a` local, row->unk0 inline in cond and val        (v03/v14/v54)
 *  145  val computed inside an if/else on the 0x100 flag      (v27)
 *  146  `var_f2 = var_f2 - 180.0f` (must be `-180.0f + var_f2`, add.s f8,f2)
 *  149  sign hardcoded (diagnostic only)                      (v20)
 *  153  no locals at all, row-> inline everywhere             (v04)
 *  158  sign as two separate ifs                             (v64)  frame=-80!
 *  170  a assigned immediately before val                     (v52)
 *  227  D_800894F0[arg0->unk134].unkX inline, no row pointer  (v05)
 *  504/542  -O1 / -g
 *
 * ---------------------------------------------------------------------------
 * TYPES / SEMANTICS -- all decoded and believed correct
 *   arg0 = struct108 * (camera).  arg1, arg2 = f32 * out-params (both NULL in
 *   the only known call site, game_14FF90.c:289 `func_151287E0(arg0, 0, 0)`).
 *   D_800894F0 = table of 5 floats, stride 0x14, indexed by arg0->unk134.
 *   1/90 = 0.01111111138f, 1/2700 = 0.0003703703696f.
 *   struct108 offsets 0x65C / 0x660 fall inside structs.h's pad61C[0x48]; they
 *   are reached by cast here rather than by editing the shared header.
 *   The `if (var_f2 < 90.0f) var_f2 = -180.0f + var_f2;` branch looks wrong but
 *   is right: combined with the sign fold below it, both arms compute var_f2-90.
 * ========================================================================= */

#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_150495B0(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5);

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
} struct894F0; /* size 0x14 */

extern struct894F0 D_800894F0[];

void func_151287E0(struct108 *arg0, f32 *arg1, f32 *arg2) {
    s32 saved;
    f32 a;
    f32 b;
    f32 c;
    f32 d;
    f32 e;
    f32 var_f18;
    f32 var_f2;
    f32 sign;
    f32 val;
    f32 ang;
    struct894F0 *row;

    saved = arg0->unk134;
    if ((arg0->unk2C & 0x40) != 0) {
        arg0->unk134 = 0;
    }
    if ((D_800D2DB4 != 0) || ((arg0->unk73C != 0) && (arg0->unk73C != 3)) ||
        (arg0->unk3D4->unk120 != 0)) {
        func_150495B0(&arg0->unk5E8, 0.0f, (f32 *) ((u8 *) arg0 + 0x660), 6.0f, 9.0f, arg0->unk7B4);
        func_150495B0(&arg0->unk3A8, 0.0f, (f32 *) ((u8 *) arg0 + 0x65C), 1.5f, 2.5f, arg0->unk7B4);
        return;
    }

    row = &D_800894F0[arg0->unk134];
    a = row->unk0;
    b = row->unk4;
    c = row->unk8;
    d = row->unkC;
    e = row->unk10;

    if ((arg0->unk23C != 0) || (a == c)) {
        var_f18 = 0.0f;
    } else {
        var_f18 = arg0->unk3D0->xz_velocity;
    }
    if (30.0f < var_f18) {
        var_f18 = 30.0f;
    }

    var_f2 = arg0->unk390;
    if (arg0->unk6C8 != 0) {
        if ((arg0->unk6FC == 10) || (arg0->unk6FC == 14)) {
            var_f2 = fabsf(arg0->unk390);
        }
    }
    while (180.0f < var_f2) {
        var_f2 = 360.0f - var_f2;
    }
    if (var_f2 < 90.0f) {
        var_f2 = -180.0f + var_f2;
    }
    if (var_f2 < 0.0f) {
        sign = -1.0f;
    } else {
        sign = 1.0f;
    }
    var_f2 -= 90.0f * sign;
    val = ((var_f2 * 0.01111111138f) * a) - (((var_f2 * var_f18) * 0.0003703703696f) * c) + e;
    if ((arg0->unk2C & 0x100) != 0) {
        val = 0.0f;
    }
    if (arg2 != NULL) {
        *arg2 = val;
    } else if (arg0->unk23C != 0) {
        arg0->unk3A8 = val;
        *(f32 *) ((u8 *) arg0 + 0x65C) = 0.0f;
    } else {
        func_150495B0(&arg0->unk3A8, val, (f32 *) ((u8 *) arg0 + 0x65C), 1.5f, 2.5f, arg0->unk7B4);
    }

    ang = arg0->unk390;
    while (180.0f < ang) {
        ang -= 360.0f;
    }
    if (90.0f < ang) {
        ang = 180.0f - ang;
    } else if (ang < -90.0f) {
        ang = -180.0f - ang;
    }
    if (arg1 != NULL) {
        *arg1 = -((ang * 0.01111111138f) * b) - (((ang * var_f18) * 0.0003703703696f) * d);
    } else if (arg0->unk23C != 0) {
        arg0->unk5E8 = -((ang * 0.01111111138f) * b) - (((ang * var_f18) * 0.0003703703696f) * d);
        *(f32 *) ((u8 *) arg0 + 0x660) = 0.0f;
    } else if ((arg0->unk2C & 0x100) != 0) {
        func_150495B0(&arg0->unk5E8, -((ang * 0.01111111138f) * b) - (((ang * var_f18) * 0.0003703703696f) * d),
                      (f32 *) ((u8 *) arg0 + 0x660), 6.0f, 9.0f, arg0->unk7B4);
    } else {
        func_150495B0(&arg0->unk5E8, -((ang * 0.01111111138f) * b) - (((ang * var_f18) * 0.0003703703696f) * d),
                      (f32 *) ((u8 *) arg0 + 0x660), 1.5f, 2.5f, arg0->unk7B4);
    }
    arg0->unk134 = saved;
}
