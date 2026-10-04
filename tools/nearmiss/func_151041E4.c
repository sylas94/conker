/* game_131620 / func_151041E4  (680 B)  -- NEAR MISS
 *
 *   raw fastscore : mism=14   frame=-72  n=170/170     (was 135 / n=168/170)
 *   n= gap        : ZERO.  Length is now exact; golden has no trailing pad
 *                   (the function ends at 0x15104488 and func_1510448C begins
 *                   at the very next word).
 *   pad-corrected : 14, all of it mismatch ROWS, none of it length phantom.
 *   stack offsets : the D<n> multiset now MATCHES golden exactly
 *                   (permuter_tu.sh frame reports no difference).
 *
 * ALL FOUR DELAY-SLOT DECISIONS ARE CLOSED.  The entire residue is 14 rows of
 * temp-register ROTATION -- no shape, no length, no scheduling left.
 *
 * WHAT CLOSED IT (three block-scope declarations; this is the whole story)
 * ----------------------------------------------------------------------
 * The four "b + store" vs "store; b; lw ra" epilogue choices are NOT decided by
 * statement order (all 120 orderings of the case-0 body were swept and are flat).
 * They are decided by whether the block that exits CONTAINS A DECLARATION.
 * A block-scope declaration mints an allocator web, and IDO then declines to
 * move the block's last instruction into the following branch's delay slot,
 * emitting "b .L15104480 / lw ra" (target duplication) instead.  Measured, each
 * change applied to the 135-row base:
 *     1. move `gfx` from function scope into the `if (flag != 0)` block
 *                                              135 -> 92   (idx43 AND idx89)
 *     2. give case 2's else a `struct_15104170_gfx *gfx2` and use it
 *        (instead of the inline obj2->unk318->unk674 = 0.0f)
 *                                               92 -> 84   (idx132)
 *     3. give case 1's else a block-scope local  84 -> 14   (idx106)  [see CAVEAT]
 *   1+2+3 together: 14 with n=170/170.  Each is independently load-bearing;
 *   deleting any one of them costs 45-70 rows.
 * The permuter found (1) on its own from the 135 base (1230 -> 560); (2) and (3)
 * were then found by hand by applying the same law to the two remaining sites.
 *
 * CAVEAT -- THE ONE UNRESOLVED CONSTRUCT
 * --------------------------------------
 * In case 1's else arm the code below reads
 *          } else {
 *              u8 v = temp1;
 *              arg0->unk1B = v;
 *          }
 * MEASURED: the *content* of that declaration is inert.  Replacing it with an
 * entirely unused `struct_15104170_sub *sx;` scores exactly the same 14, as do
 * `s32 v` and a differently-named u8.  Only the PRESENCE of a declaration
 * matters.  So the object proves golden's else arm declared something; it does
 * not prove what.  A bare extra `{ }` with no declaration does NOT work (84),
 * and neither does a `(u8)` cast (84) -- so this is a real structural fact about
 * the original source, but the spelling chosen here is a guess.  Do not ship
 * this as a match without either finding a spelling that is obviously natural
 * or accepting the u8-temp reading.
 * RE-MEASURED 2026-08-21: still unpinned.  `s32 v`, `u8 v;` split into
 * declare-then-assign, `struct_15104170 *p = arg0; p->unk1B = temp1;`, and an
 * unrelated-but-used `struct_15104170_gfx *gfx3` all score exactly 14.
 *
 * THE REMAINING 14 ROWS -- all register rotation, no shape
 * -------------------------------------------------------
 *   idx14           case-3 %hi(D_800BEA08):  ours t3, golden t4  (golden reuses
 *                   the SAME t4 it used for case 1; ours advances the rotation)
 *   idx87,88        case-0 gfx pointer:      ours v0, golden t3
 *   idx92,97        case-1 arg0->unk1B:      ours t3 + `addu v0,t3,t5`
 *                                            golden v0 + `addu v0,v0,t5`
 *   idx130-133      case-2 gfx2 / the 3:     ours v0,t2, golden t2,t3
 *   idx136-142      case-3 same as case 1:   ours t3/t4, golden t4/v0
 * The pattern is one consistent swap: golden puts the `arg0->unk1B` loads of
 * cases 1 and 3 in **v0** (reusing the switch selector's register) and keeps the
 * t-rotation for the gfx pointers; ours does the opposite.  This is the classic
 * IDO temp-register rotation offset.
 *
 * MEASURED ON THE *NEW* BASE, DO NOT REPEAT (the old base's flat results were
 * re-measured because the codegen changed under them):
 *   - break vs return, in every arm and all together      : flat at 14
 *   - `if (temp1 < 0xFF)` with the arms swapped           : 89 (worse)
 *   - `arg0->unk1B = (u8)temp1;` (cast, no declaration)   : 84
 *   - an extra bare `{ }` block, no declaration           : 84
 *   - declaring temp1 inside `case 1: { ... }`            : 170 (much worse)
 *   - `temp1 = arg0->unk1B; temp1 += D_800BEA08 * 10;`    : 32
 *   - `temp = arg0->unk1B; temp -= D_800BEA08 * 10;`      : 14 (flat, keep the
 *                                                           one-expression form)
 *   - `temp1 = D_800BEA08 * 10 + arg0->unk1B;`            : 15
 *   - `(u8)arg0->unk1B + D_800BEA08 * 10`                 : 14 (flat)
 *   - case-0 gfx write inlined (no gfx local)             : 27
 *   - case-2 gfx2 write inlined (keeps the declaration)   : 15
 *   - three declaration orders of the nine function-scope locals that keep
 *     slots #5/#6/#8/#9                                   : all flat at 14
 *   - `s32 v; v = temp1;` instead of `u8 v = temp1;`      : flat at 14
 *   - a block-scope declaration added to case 3's ELSE or THEN arm, or to
 *     case 1's else spelled as declare-then-assign         : all flat at 14
 *     (case 3 has no branch at either exit, so the law cannot bite there)
 *   - a block-scope declaration added to a THEN arm that golden FILLS from
 *     above -- case 1's `>= 0xFF` arm (87, n=171), case 2's `<` arm (78,
 *     n=171), case 0's `spd >= 19.0f` arm (156, n=171).  Each grows the
 *     function by a word, which is the law running in reverse and is strong
 *     corroboration that golden's then-arms contain NO declarations.
 *   - a second block-scope local in the `if (flag != 0)` block  : 30, frame 0x50
 *
 * FRAME / SLOTS (unchanged, still exact)
 *   NINE function-scope locals, not ten: frame = roundup8(0x1C + 4 + 9*4) = 0x48,
 *   the same 0x48 that ten gives.  Slots run DOWNWARD from frame-4 = 0x44, so
 *   #5 -> 0x34 (var14), #6 -> 0x30 (var10), #8 -> 0x28 (case-2 object),
 *   #9 -> 0x24 (case-3 temp).  Four of the nine never reach memory (sub, spd,
 *   flag, temp1) and one (#1, spelled `pad1`) is unused -- with only four
 *   register-resident variables to fill the five free positions {1,2,3,4,7} a
 *   NINTH function-scope local is structurally REQUIRED.
 *   RESOLVED (2026-08-21): it does NOT have to be a placeholder.  Four honest
 *   readings all reproduce the base bit-for-bit (mism=14, frame=-72, and the
 *   SAME fourteen rows):
 *       s32 kind;  kind = arg0->unk1C;  then `kind == 0` / `kind == 1`   <-- shipped
 *       s32 state; state = arg0->unk1A; switch (state)
 *       s32 dt;    dt = D_800BEA08;  in case 2   (or D_800BE9E4 in case 0)
 *   `kind` is the most natural: golden loads 0x1C ONCE (lbu v1) and compares it
 *   twice, which is exactly what a local reads like.  Deleting the ninth local
 *   entirely costs frame -64 and 30 rows, so its PRESENCE is load-bearing even
 *   though its identity is not pinned.  The unused-placeholder blocker is GONE.
 *
 * THREE ORIGINAL FINDINGS THAT STILL HOLD (keep all three):
 *  1. It is a switch, not an if/else-if chain -- only `switch (arg0->unk1A)`
 *     reproduces golden's beql/beq/beq/beq/b run.
 *  2. In case 0 the source is  sub = arg0->unk10->unk2D0;  spd = sub->unk8;
 *     -- NOT a separate local for arg0->unk10, and NOT fully inlined.
 *  3. `arg0->unk1A = D_800BEA0C = 1;` scores lower on the OLD base but
 *     materialises the address into a register pair; it is structurally wrong.
 *     Do not revisit.
 *
 * PERMUTER: `permuter_tu.sh selftest` PASSES EVERY CHECK on game_131620
 *   (a) reassembly identity PASS, (b) harness-vs-Makefile object PASS,
 *   (b2) pycparser round trip PASS, (c) base score, (d) negative control PASS,
 *   (e) isolation DIFFERS from the in-TU build -> the TU harness is load-bearing.
 *   Run it with the offset gate, which is now safe because the base matches:
 *     PERMUTER_TU_REQUIRE_FRAME=72 PERMUTER_TU_REQUIRE_OFFSETS=1 \
 *       ./permuter_tu.sh run <dir> -j 6 --best-only --stop-on-zero
 *   ~1400 gated iterations from this base produced nothing better than the base.
 *
 * NEW NEGATIVE RESULTS 2026-08-21 (all measured on THIS base, all flat or worse):
 *   - ALL 120 declaration orders of the five free positions {1,2,3,4,7}
 *     (kind/pad1, sub, spd, flag, temp1)              : every one flat at 14
 *   - case-0 gfx write inlined but the declaration KEPT : 27
 *     case-2 gfx2 inlined, declaration kept            : 15   (both worse, so
 *     gfx/gfx2 really are variables, not folded temps)
 *   - var10 and/or var14 moved to block scope          : 22 / 24 / 24
 *   - obj2 moved to block scope                        : 30, frame -80
 *   - temp moved into a `case 3: { }` block            : 30, frame -80
 *   - an extra USED block local in case 0 ahead of gfx : 17-30
 *   - `10 * D_800BEA08`, extra parens, `(s32)`/`(u8)` casts on arg0->unk1B
 *     in cases 1 AND 3                                 : all flat at 14
 *   - two-statement form in case 1 (`temp1 = ...; temp1 += ...`) : 31/32
 *
 * VERDICT: the residue is 14 rows of pure register NAMING -- golden puts the
 * cases-1/3 `arg0->unk1B` loads in v0 (evaluating the first operand straight
 * into the destination variable's register) and gives gfx/gfx2 rotation temps
 * t3/t2; ours does the exact opposite in both places.  No source-level knob was
 * found in ~150 honest spellings across 10 structural families, and ~1400 gated
 * permuter iterations found nothing better.  This is a RANKING TIE: park it.
 * Do NOT ship -- 14 is not 0.
 *
 * Pass this file straight to fastscore; it needs no hand edits:
 *   python3 tools/fastscore.py game_131620 func_151041E4 tools/nearmiss/func_151041E4.c
 */
#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    u8  pad0[0x8];
    f32 unk8;
} struct_15104170_sub;

typedef struct {
    u8  pad0[0x674];
    f32 unk674;
} struct_15104170_gfx;

typedef struct {
    u8  pad0[0x13F];
    u8  unk13F;
    u8  pad140[0x190];
    struct_15104170_sub *unk2D0;
    u8  pad2D4[0x44];
    struct_15104170_gfx *unk318;
} struct_15104170_owner;

typedef struct {
    u8  pad0[0x10];
    struct_15104170_owner *unk10;
    struct_15104170_owner *unk14;
    u16 unk18;
    u8  unk1A;
    u8  unk1B;
    u8  unk1C;
} struct_15104170;

extern u8 D_800BEA0C;

void func_1000E2F4(s32);
void func_151254F4(struct_15104170_gfx *, s32);
void func_151D66F0(s32, s32);

s32 func_15167A68(s32, s32, s32, s32, s32, s32);

struct_15104170 *func_15104170(s32 arg0, s32 arg1, s32 arg2) {
    struct_15104170 *ret;

    ret = (struct_15104170 *)func_15167A68(0x64, 0, 0x20, 0, 0xFF, 1);
    if (ret != 0) {
        ret->unk18 = 0xF;
        ret->unk1A = 0;
        ret->unk1B = 0;
        ret->unk10 = (struct_15104170_owner *)arg1;
        ret->unk14 = (struct_15104170_owner *)arg2;
        ret->unk1C = arg0;
    }
}

void func_151041E4(struct_15104170 *arg0) {
    s32 kind;
    struct_15104170_sub *sub;
    f32 spd;
    s32 flag;
    struct_15104170_owner *var14;
    struct_15104170_owner *var10;
    s32 temp1;
    struct_15104170_owner *obj2;
    s32 temp;

    switch (arg0->unk1A) {
    case 0:
        sub = arg0->unk10->unk2D0;
        spd = sub->unk8;
        flag = 0;
        kind = arg0->unk1C;
        if (kind == 0) {
            if (spd >= 19.0f) {
                flag = 1;
            }
        } else if (kind == 1) {
            if (D_800BE9E4 < arg0->unk18) {
                arg0->unk18 -= D_800BE9E4;
            } else {
                flag = 1;
            }
        }
        if (flag != 0) {
            struct_15104170_gfx *gfx;

            var14 = arg0->unk14;
            var10 = arg0->unk10;
            arg0->unk1A = 1;
            D_800BEA0C = 1;
            func_100176C4();
            func_10010F30(0x5B2, 0x7FFF, 0, 0, 0);
            func_10010F30(0x5B2, 0x7FFF, 0x7F, -100, 0);
            func_10010F30(0x5B2, 0x7FFF, 0, 0, 0);
            func_10010F30(0x5B2, 0x7FFF, 0x7F, -100, 0);
            func_151D66F0(0xD2, 2);
            func_151254F4(var10->unk318, var14->unk13F);
            gfx = var10->unk318;
            gfx->unk674 = 0.0f;
        }
        break;
    case 1:
        temp1 = arg0->unk1B + D_800BEA08 * 10;
        if (temp1 >= 0xFF) {
            arg0->unk1B = 0xFF;
            arg0->unk1A = 2;
            arg0->unk18 = 0xB4;
        } else {
            u8 v = temp1;

            arg0->unk1B = v;
        }
        break;
    case 2:
        if (D_800BEA08 < arg0->unk18) {
            arg0->unk18 -= D_800BEA08;
        } else {
            struct_15104170_gfx *gfx2;

            obj2 = arg0->unk10;
            D_800BEA0C = 0;
            func_1000E2F4(0);
            func_151254F4(obj2->unk318, obj2->unk13F);
            gfx2 = obj2->unk318;
            gfx2->unk674 = 0.0f;
            arg0->unk1A = 3;
        }
        break;
    case 3:
        temp = arg0->unk1B - D_800BEA08 * 10;
        if (temp <= 0) {
            func_1516972C((struct102 *)arg0);
            func_151D66F0(0, 0);
        } else {
            func_151D66F0((temp * 0xD2) >> 8, 2);
            arg0->unk1B = temp;
        }
        break;
    }
}

s32 func_1517F08C(s32, s32, s32, s32, s32, s32);

s32 func_1510448C(s32 arg0, s32 arg1, s32 arg2) {
    s32 *p1 = &arg1;
    s32 *p2 = &arg2;
    s32 v0;
    if ((s16)*p2 != 0 || (v0 = *(u8 *)(*p1 + 0x1B)) == 0) {
        return arg0;
    }
    return func_1517F08C(arg0, ((v0 * 0x3F) >> 8), 0, 0, 0, *((s16 *)&arg2 + 1));
}

extern struct126 *D_800CC5EC;

u8 func_151044F4(void) {
    if (D_800CC5EC != 0) {
        return D_800CC5EC->matrix_physics;
    }
    return 0;
}
