/* tools/nearmiss/func_15169A48.c  --  game_196DB0
 *
 * KIND: WHOLE-TU REPLACEMENT.  This file IS conker/src/game_196DB0.c with the
 * pragma replaced by live C.  Score it DIRECTLY, in one command:
 *     python3 tools/fastscore.py game_196DB0 func_15169A48 tools/nearmiss/func_15169A48.c
 *
 * STATUS: PARKED at mism=28, n=138/138, frame=-104.  (SCORING NOTE: the "58" and the
 * whole pad-correction story below are VOID -- fastscore was fixed and the real number
 * was always 28.  Wherever the pre-2026-08 text below says 58, read 28; the ROW SETS it
 * records are still correct.  n=138/138 counts golden's three trailing alignment nops,
 * which our object also carries: our REAL body is 135 instructions, exactly golden's,
 * and a +1-instruction candidate silently EATS a pad nop instead of showing up in n --
 * on this function always read the ROWS, never n alone.)
 * See the 2026-08-21 WAVE ADDENDUM at the end of this comment block: the residual is
 * now fully decomposed and driven to mism=2 by a forcer, with exactly ONE unexplained
 * row-pair left.  Progress: 119 -> 74 -> 68 -> 28 (shippable) / 2 (forcer-only).
 *
 * Instructions idx0..idx81 -- the whole prologue, both early-exit tests, the
 * gDPSetPrimColor, the func_15094F70 branch, the four unk49 bit tests and the
 * gDPSetPrimDepth -- are BYTE-EXACT including registers, offsets and the frame.
 *
 * ==========================  DECODED SEMANTICS  =============================
 *  - The `addiu $a2, $sp, 0x5F` at 0x15169A70, which looks dead because $a2 is
 *    later zeroed, is NOT dead: it is the third argument (&update) of
 *    func_1513F4E4, hoisted above the branch.
 *  - w0 = 0xFA000100 is gDPSetPrimColor(pkt, 1, 0, ...) -- m=1, l=0.
 *  - w0 = 0xEE000000 / w1 = 0x795A0000 is gDPSetPrimDepth(pkt, 0x795A, 0).
 *  - func_1509629C takes TWELVE args; its 3rd/4th are f32 but land in $a2/$a3
 *    because arg 1 is a pointer (o32 only floats-in-FP-regs for args 1..2).
 *  - The third parameter `arg2` genuinely is unused: golden homes it with
 *    `sw $a2, 0x70($sp)` and never reads it back.  Do not invent a use for it.
 *
 * ==========================  FRAME  =========================================
 * Golden's frame is 0x68, `update` at sp+0x5F and the `flags` spill at sp+0x60.
 * That pins the local set to FIVE word-sized locals plus the u8, with exactly
 * TWO words declared BEFORE `update` (0x64 and 0x60) and THREE after.
 * Four words gives -96, six gives -112.
 *
 * ==========================  THE 28 ROWS: ONE CAUSE, FULLY ISOLATED  ========
 * Everything through idx81 is byte-identical; the divergence starts at idx82 and
 * is a TEMP-REGISTER ROTATION seeded by ONE extra temporary that golden consumes:
 *
 *   golden  idx93: or   $t9, $v1, $t3     <-- mode|D_800D2C9C into a FRESH temp
 *           idx94: lw   $t3, 0x0($v0)     <--   ($t3 recycled: the or freed it)
 *           idx95: lw   $t5, 0x4($v0)
 *           idx96: ori  $a1, $t9, 0x2CA0
 *   ours    idx93: lw   $t7, 0x0($v0)
 *           idx94: lw   $t1, 0x4($v0)
 *           idx95: or   $v1, $v1, $t3     <-- done IN PLACE, no temp consumed
 *           idx96: ori  $a1, $v1, 0x2CA0
 *
 * Golden allocates SEVEN temps in idx82..idx99, we allocate SIX.  That one
 * difference rotates every later temp: our 12-argument func_1509629C setup emits
 * t2,t5,t3,t6,t8,t9,t7,t1 where golden emits t8,t9,t7,t1,t4,t2,t5,t3 -- same
 * instructions, same order, same offsets, rotated names (idx103..idx129).
 *
 * ==========================  THE WALL (measured, ~70 variants this wave)  ====
 * The search space collapses into exactly two outcomes, with NOTHING in between:
 *
 *   (1) Any spelling in which the mode region holds THREE values (v, flags, mode)
 *       compiles to the in-place `or $v1,$v1,$t3` and scores 58 with an
 *       IDENTICAL row set: [82,84,88,91,92,93,94,95,96,97,98,99,101,103,104,109,
 *       111,112,114,115,118,119,122,123,124,125,127,129].
 *   (2) Any spelling that introduces a FOURTH distinct value (a second named
 *       local, a block local, a `register` local, a reused parameter, a reused
 *       dead local) makes IDO give that value a function-WIDE identity.  The
 *       whole allocation AND the schedule of the gDPSetPrimColor byte-packing
 *       shift, so the divergence jumps back to idx21 and the score jumps to
 *       101..111.  The colours also come out INVERTED versus golden: IDO puts
 *       the named variable in $v1 and the if/else result in $t1, where golden
 *       has the if/else result in $v1 and the OR result in $t9.
 *
 * Golden is neither: it has base's first 82 instructions AND a fourth value.
 * That means golden's OR result is a pure EXPRESSION temp (no function-wide
 * identity), which in C requires it to be inline in the call -- and every inline
 * grouping costs one extra instruction (136 vs 135).  The IDO grouping law,
 * measured exhaustively here for an argument position:
 *       (A|B)|const  ->  or argreg,A,B ; ori temp,argreg,const ; or argreg,temp,zero  (3)
 *       A|(B|const)  ->  ori temp,B,const ; or argreg,temp,A                          (2)
 *       (A|const)|B  ->  ori temp,A,const ; or argreg,temp,B                          (2)
 *       const|(A|B)  ->  REASSOCIATED to (A|B)|const, byte-identical object
 * Golden needs `or temp,A,B ; ori argreg,temp,const`, which NONE of the nine
 * groupings produce.  That shape is currently unreachable from this file's model.
 *
 * ==========================  DO NOT REPEAT  =================================
 * Earlier waves:
 *  - `if (a != 0 && b != 0) { body }` with the return at the end: 119.  The
 *    early-return `if ((a == 0) || (b == 0)) return pkt;` form is what golden
 *    compiles from.
 *  - INLINE arg 1 in any grouping: 136 instructions, 68.
 *  - A separate word local for the OR result with the frame held at 0x68: 101 in
 *    all three declaration slots.  Reusing dead `v`: 104.  Reusing `arg2`: 101.
 *  - Block-scoped `s32 m`: 111.  Block-scoped `mode`: 68.  Both: 118.
 *  - `mode |= D`, `mode = D | mode`, `(s32)` cast, ternary for the 0x100000/0
 *    choice, arg-2 swapped to `.unk0|.unk4`, `(a|b)|4`, `extern s32 D[][2]`,
 *    u32 table fields, `s8 unk46`: ALL FLAT at 58.
 *  - `4 | a | b` and `a | (b | 4)`: 134 instructions, 87.
 *  - Hoisting arg 2 into its own local: 134.  `Struct800A4AC8_2 *e` replacing
 *    pad1: 59; with the two statements swapped: 61.
 * This wave (all frame-preserving at -104 unless noted; all REFUTED):
 *  - Ternary FUSED with the OR in one statement, `m = (unk48==2 ? 0x100000 : 0)
 *    | D_800D2C9C;`, in all three trailing slots, both operand orders: 101.
 *  - if/else result in H and OR result in R for all 12 ordered pairs over
 *    {v, m1, m2, m3}: 101 (m-to-m) / 104 (into v) / 109 (out of v).
 *  - Casts on the inline OR -- (s32), (u32), (s32) on both operands, `u32 mode`,
 *    `0x2CA0 | (s32)(mode|D)`: 68, 136 instructions.
 *  - `(mode |= D) | 0x2CA0`, `(mode = mode|D) | 0x2CA0`, `(mode |= D, mode |
 *    0x2CA0)`: FLAT 58, identical rows.  `(pad1 = mode|D) | 0x2CA0` and the
 *    comma form with pad1: 101.
 *  - `register s32 m` in every declaration position: 101 / 104 / 106.
 *    Block-scoped `register s32 m`: 111.  `m` declared before `v`: 106; before
 *    `flags`: 103.
 *  - TYPES CARRY NO INFORMATION HERE.  D_800D2C9C as u32 / unsigned int / long /
 *    unsigned long, func_15142FBC's prototype with u32 / unsigned / long arg1,
 *    u32 arg2, and the UNPROTOTYPED `Gfx *func_15142FBC();`: all FLAT at 58 with
 *    byte-identical row sets.  Do not sweep prototypes again.
 *  - `v` rewritten as an inline ternary inside the func_15094F70 call (removing
 *    it as a local entirely): FLAT 58 with an IDENTICAL row set -- so `v` costs
 *    no home register and freeing it does not buy the missing OR temp.  Doing it
 *    together with an OR local: still 101.
 *  - Fully inline ternary with `mode` demoted to an unused pad (only v+flags
 *    used): 68 in every grouping except `tern|0x2CA0|D`, which is 61.
 *  - SOURCE-ORDER HOISTING of the mode computation: moving the unk48 if/else
 *    (with or without the OR) above the gDPSetPrimDepth block, or above the
 *    unk49&8 flags step: 147, and 139 instructions instead of 135.  Statement
 *    ORDER in this tail is pinned; only statement CONTENT is still free.
 *  - RAW DISPLAY-LIST WRITES instead of the GBI macros (pkt->words.w0/w1 = ...;
 *    pkt++;) for the gDPSetPrimColor and/or the gDPSetPrimDepth, in both store
 *    orders, alone and combined with an OR local: 107..152, and ALL of them drop
 *    the frame to -96.  The macros are what golden compiles from; the raw form
 *    removes whatever the macro needs the extra frame word for.  Do not retry.
 *  - PERMUTER STILL UNUSABLE.  `permuter_tu.sh selftest` re-run this wave: (a)
 *    PASSES, (b) FAILS (the harness object contains no func_15169A48 at all --
 *    disasm sha1 is the empty-string sha da39a3ee...), (b2) FAILS (pycparser
 *    round trip changes codegen), (c) and (d) fail as a consequence.  (e) reports
 *    that isolation differs from the in-TU build.  Every score it printed would
 *    be measured on a different source than the one shown.  Do not run it here.
 *
 * ==========================  HONESTY FLAG (NOW PROVABLY UNRESOLVABLE)  ======
 * `pad1` and `pad2` are PLACEHOLDERS and must stay marked.  Three of the five
 * word locals are identifiable from the code (v, flags, mode); the other two are
 * only pinned in COUNT and SIZE, by the frame.  Refuted identifications:
 *     s32 idx = arg1->unk46          103 (all three slots)
 *     s32 zsh = arg1->unk26 >> 8      68
 *     s32 tbl = the arg-2 OR value   133 (134 instrs)
 *     s32 w, h for the two lh/cvt    106
 *     Gfx *g / *g2 for the raw commands -- copy-coalesced with pkt, frame -96
 * This wave established WHY no further attempt can succeed: an unused local has
 * no live range, so it is allocated no register and appears nowhere in the
 * instruction stream -- it only consumes a frame slot.  Therefore NOTHING in
 * this function's bytes can ever discriminate between candidate names, and even
 * a score of 0 would not validate them.  Naming them requires evidence from
 * OUTSIDE this function (a sibling that shares the struct, or a symbol map).
 * This file must not be called a match while they carry these names.
 */

/* ======================  WAVE ADDENDUM 2026-08-21  =========================
 * THE RESIDUAL IS NOW FULLY DECOMPOSED.  The 28 rows are 4 counter-driven causes
 * plus 24 knock-on rows, and the whole thing collapses to ONE instruction.
 *
 * ---- 1. THE BLOCK-SCOPE LAW: TESTED HERE, IT IS A ONE-WAY LEVER ------------
 * Injecting a block-scope declaration (`s32 zz;`, unused) into every block of this
 * function.  The frame stayed -104 in ALL 12 cases: NESTED LOCALS COST NO FRAME SLOT
 * HERE, so nested declarations are frame-free and may be added freely.
 *      block that FALLS THROUGH  -> COMPLETELY INERT, mism unchanged at 28
 *        (unk49&1 outer, v-else, flags-else, unk49&4, unk49&8, unk49&0x20, mode-else)
 *      block that EXITS VIA `b`  -> STRICTLY WORSE, and by a lot:
 *        early-return 57, unk49&2-then 95, flags-then 76, mode-then 54
 *      bare block wrapping the tail: with a decl 38, without 28
 * The law's REVERSE direction is thus confirmed on four independent blocks, and the
 * forward direction has nothing to bite on: every `b`-exiting block here ALREADY
 * fills its delay slot from above exactly as golden does.  The inert cases were
 * BYTE-identical, not merely equal in score, so the law does not rotate temps either
 * (checked again across a 24-cell cross with the second-variable spelling).
 * CONCLUSION: the block-scope law is EXHAUSTED here.  Do not re-sweep it.
 *
 * ---- 2. WHAT ACTUALLY MOVES THIS FUNCTION: THE TEMP-ROTATION COUNTER -------
 * IDO numbers expression values SEQUENTIALLY IN SOURCE ORDER and draws each temp
 * from a rotating free list, PERIOD 9 here ($t1..$t9; $t0 is held by `flags`).  A
 * value that emits NO instruction still consumes a number.  A redundant `& 0xFF` on
 * a u8 struct field is exactly such a free value.
 *   MEASURED, masks on `arg1->unk48` in the `== 2` test, n unchanged at 138:
 *      masks= 0  1  2  3  4  5  6  7  8  9
 *      mism = 28 32 32 32 12 32 31 31 32 28      (9 == 0: period confirmed)
 * At masks=4 the D_800A4AC8 lui/addiu, the unk46 lbu, the sll and the addu ALL land
 * on golden exactly ($t2/$t1/$t4/$t4+$t2).  The shift is FORWARD-ONLY: it moves
 * everything numbered after the mask and nothing before it.
 *
 * ---- 3. WHERE THE MISSING VALUES ARE, TO THE STATEMENT ---------------------
 * Masks on unk48 are numbered BEFORE the D_800D2C9C load, so they drag idx73/80/83/89
 * off golden (that is the residue of 12 at masks=4).  Moving the masks to the ARRAY
 * INDEX -- D_800A4AC8[arg1->unk46 & 0xFF & 0xFF & 0xFF & 0xFF] -- numbers them AFTER
 * D and before the array base:
 *      unk46 masks = 4                                     -> mism = 4
 *      + arg 2 written `.unk0 | .unk4 | 4`                  -> mism = 2
 * GOLDEN CONSUMES EXACTLY FOUR MORE FREE VALUE-NUMBERS THAN WE DO between the
 * D_800D2C9C load and the D_800A4AC8 base.  That single fact causes all 24
 * "rotation" rows; they are not independent defects and must never be chased singly.
 *
 * ---- 4. ARG 2 ORDER: SETTLED, AND THE FILE IS NOW CORRECTED ---------------
 * `.unk4|.unk0` and `.unk0|.unk4` BOTH score 28 at masks=0, so the old header was
 * right that it is flat -- but they are NOT equivalent.  IDO emits the `or` with the
 * higher-numbered register in rs, so the operand order in the OBJECT is a consequence
 * of register numbering; what the SOURCE order really controls is which offset is
 * loaded FIRST.  Golden loads 0x0 then 0x4.  With the counter aligned this becomes
 * visible and decisive: at masks=4, `.unk4|.unk0` = 4 rows (93,94,95,96) and
 * `.unk0|.unk4` = 2 rows (93,96), the extra two being purely the lw offsets.  The
 * file now carries `.unk0 | .unk4 | 4`.  Score-neutral today, provably correct.
 * DO NOT SWAP IT BACK.
 *
 * ---- 5. THE ONE ROW-PAIR LEFT (idx93 / idx96) -----------------------------
 *      ours  idx93  or   $v1, $v1, $t3        gold  or   $t9, $v1, $t3
 *      ours  idx96  ori  $a1, $v1, 0x2CA0     gold  ori  $a1, $t9, 0x2CA0
 * Everything else is byte-exact, including the schedule (our `or` is already emitted
 * BEFORE the two lw, as golden's is), the $t3 recycle and all 134 other words.
 * Golden writes the OR into a FRESH temp; we write it in place.
 *   MEASURED LAW: whenever the OR's destination is a NAMED LOCAL, IDO writes in
 *   place.  Verified on `mode`, on `v` (reused after its first live range dies), on
 *   `arg2` (the unused parameter) and on a second local in every declaration slot.
 *   MEASURED CONSTRAINT: golden has exactly THREE live locals in the tail.  A local's
 *   value number is allocated at DECLARATION time, so any FOURTH live value --
 *   function-scope, nested-block, `register`, or a reused parameter -- shifts the
 *   allocation BACKWARDS and breaks the gDPSetPrimColor byte-packing from idx21
 *   (53..110 in every cell of a 6x2x9 sweep).
 * So golden's OR result is a pure expression temp -- yet every inline grouping of
 * (mode|D)|0x2CA0 costs a THIRD instruction (136 real vs golden's 135) and can never
 * match.  That contradiction is the entire remaining residual.
 *
 * ---- 6. WHY IT IS PARKED RATHER THAN SHIPPED ------------------------------
 * mism=2 is reachable ONLY via four redundant `& 0xFF` on a u8 array index.  That is
 * a textbook forcer -- nobody writes `arr[x & 0xFF & 0xFF & 0xFF & 0xFF]` -- so the
 * file stays at the honest 28.  Searched for an honest source of those four free
 * values, ALL FLAT AT 28 (do not re-walk):
 *   - D_800D2C9C respelled D[0], D[3], D.a, D.b, D.a.b, D.a.b.c, D[0][0], D[1][1],
 *     D[2].a -- every array/struct/nesting shape yields ZERO free values.
 *   - D_800A4AC8 respelled as a flat s32 array with [i*2]/[i*2+1], [2*i+1],
 *     [(i<<1)+1]; as s32[][2]; s32[][1][2]; s32[][1][1][2]; a nested struct one and
 *     two levels deep; a union with a w[2] view; (u8*) pointer arithmetic; and a
 *     cast-to-struct-pointer.  The *2 forms are worth +1 value, everything else +0.
 *   - index respelled (u8), (u8)(s32), a four-deep cast chain, (u32), +0, *1, |0,
 *     %0x100, and a `u8 unk46 : 8` BITFIELD: all +0.  Only `& 0xFF`/`& 0xFFFF` count,
 *     and only a count of exactly 4 works.
 *   - free idioms on the OR result (& -1, & 0xFFFFFFFF, | 0, ^ 0, + 0, * 1, >> 0,
 *     << 0): all +0, all byte-identical.
 * A 15 x 2 x 9 sweep (mode/OR/arg1 spelling x arg-2 order x counter offset) and a
 * 6 x 2 x 9 nested-scope sweep found NOTHING below 2.
 *
 * ---- 7. WHAT A FUTURE WAVE SHOULD DO --------------------------------------
 * Find a plausible construct worth FOUR free value-numbers between the D_800D2C9C
 * load and the D_800A4AC8 base that ALSO gives the OR a fresh temp without adding a
 * fourth live local.  The most likely shape is a MACRO in the original whose
 * expansion contains redundant masks (the way the GBI _SHIFTL/_SHIFTR macros do)
 * wrapping either the array index or the mode word.  Evidence must come from a
 * sibling caller of func_15142FBC, not from this function.
 *
 * ---- 8. PERMUTER: STATUS CHANGED, STILL UNUSABLE HERE ---------------------
 * setup + selftest re-run this wave: (a) PASS, (b) NOW PASSES ("identical codegen" --
 * the old header's claim that the harness object contains no func_15169A48 is out of
 * date), (d) PASS, (b2) STILL FAILS ("round trip changes codegen"), so every score it
 * printed would be measured on a different source than the one shown.  Overall
 * SELFTEST: FAIL.  Do not run it here.  (It now fully PASSES on the sibling target
 * game_193E50/func_15166B50.)
 * ========================================================================== */

#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_15167A68(s32, s32, s32, s32, s32, s32);
extern void (*D_8008CA20[])(struct102 *);

s32 func_15169900(s32 arg0, s32 arg1) {
    s32 ret;

    ret = func_15167A68(0x5E, 0, 0x4C, 0, arg1, 1);
    if (ret != 0) {
        bcopy((void *)arg0, (void *)(ret + 0x10), 0x3C);
    }
    return ret;
}

s32 func_15169968(s32 arg0) {
    return func_15169900(arg0, 0xFF);
}

void func_15169988(struct102 *arg0) {
    s32 temp_v0;
    s32 temp_v1;
    s32 temp_t1;

    temp_v0 = *(s8 *)((u8 *)arg0 + 0x40);
    if (temp_v0 != 0) {
        D_8008CA20[temp_v0](arg0);
    }

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x26);
    temp_v0 += *(s16 *)((u8 *)arg0 + 0x28) * D_800BE9E4;
    temp_t1 = *(u8 *)((u8 *)arg0 + 0x41) << 8;
    if (temp_v0 >= temp_t1) {
        temp_v0 -= temp_t1;
    } else if (temp_v0 < 0) {
        temp_v0 += temp_t1;
    }

    temp_v1 = *(s16 *)((u8 *)arg0 + 0x24);
    *(s16 *)((u8 *)arg0 + 0x26) = temp_v0;
    if (temp_v1 != 0) {
        temp_v1 -= D_800BE9E4;
        if (temp_v1 <= 0) {
            func_1516972C(arg0);
            return;
        }
        *(s16 *)((u8 *)arg0 + 0x24) = temp_v1;
    }
}


typedef struct {
    s32 unk0;
    s32 unk4;
} Struct800A4AC8_2;

typedef struct {
    u8 pad0[0x10];
    s32 unk10;
    s32 unk14;
    u8 pad18[0xE];
    s16 unk26;
    u8 pad28[0x4];
    f32 unk2C;
    f32 unk30;
    s16 unk34;
    s16 unk36;
    s16 unk38;
    s16 unk3A;
    u16 unk3C;
    u16 unk3E;
    u8 pad40[0x2];
    u8 unk42;
    u8 unk43;
    u8 unk44;
    u8 unk45;
    u8 unk46;
    u8 unk47;
    u8 unk48;
    u8 unk49;
} Struct15169A48;

extern Struct800A4AC8_2 D_800A4AC8[];
extern s32 D_800D2C9C;

Gfx *func_1513F4E4(Gfx *, u8, u8 *);
Gfx *func_15094F70(Gfx *, s32, s32, s32, s32, s32, s32, s32, s32);
Gfx *func_15142FBC(Gfx *, s32, s32, u8 *);
Gfx *func_1509629C(Gfx *, s32, f32, f32, f32, f32, s32, s32, s32, s32, s32, s32);

Gfx *func_15169A48(Gfx *pkt, Struct15169A48 *arg1, s32 arg2) {
    s32 v;
    s32 flags;
    u8 update;
    s32 mode;
    s32 pad1;
    s32 pad2;

    if ((arg1->unk38 == 0) || (arg1->unk3A == 0)) {
        return pkt;
    }
        update = 1;
        pkt = func_1513F4E4(pkt, arg1->unk47, &update);
        gDPSetPrimColor(pkt++, 1, 0, arg1->unk42, arg1->unk43, arg1->unk44, arg1->unk45);
        if (arg1->unk49 & 1) {
            if (arg1->unk49 & 2) {
                v = (arg1->unk34 << 2) >> 5;
            } else {
                v = 0;
            }
            pkt = func_15094F70(pkt, arg1->unk14, 0, 0, 0x100, 1, v, 2, 3);
        }
        if (arg1->unk49 & 0x10) {
            flags = 1;
        } else {
            flags = 0;
        }
        if (arg1->unk49 & 4) {
            flags |= 2;
        }
        if (arg1->unk49 & 8) {
            flags |= 4;
        }
        if (arg1->unk49 & 0x20) {
            gDPSetPrimDepth(pkt++, 0x795A, 0);
        }
        if (arg1->unk48 == 2) {
            mode = 0x100000;
        } else {
            mode = 0;
        }
        mode = mode | D_800D2C9C;
        pkt = func_15142FBC(pkt, mode | 0x2CA0,
                            D_800A4AC8[arg1->unk46].unk0 | D_800A4AC8[arg1->unk46].unk4 | 4,
                            &update);
        return func_1509629C(pkt, arg1->unk10, arg1->unk38, arg1->unk3A, arg1->unk2C, arg1->unk30,
                             arg1->unk3C, arg1->unk3E, flags, arg1->unk34, arg1->unk36,
                             arg1->unk26 >> 8);
}

