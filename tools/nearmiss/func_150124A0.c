/* tools/nearmiss/func_150124A0.c  --  game_3F820 (the TU's ONLY remaining pragma)
 *
 * KIND: WHOLE-TU REPLACEMENT.  This file IS conker/src/game_3F820.c with the
 * pragma replaced by live C.  Score it DIRECTLY, in one command:
 *     python3 tools/fastscore.py game_3F820 func_150124A0 tools/nearmiss/func_150124A0.c
 *
 * SCORE: raw 49  /  pad-corrected 19, at the exact instruction count (n=157 real)
 *        and the exact frame (0xF8).  Golden .s lists 160 words but the last THREE
 *        are inter-function pad nops, so a perfect match scores 30, not 0.
 *        Independently confirmed: permuter_tu.sh frame reports base.c's STACK-OFFSET
 *        MULTISET (63 displacements) MATCHES golden exactly.
 *        History: 169 -> 53 -> 50 -> 49.
 *
 * WHAT IT IS: the sky/star-dome seeder.  Three rows of ten Slots (0x10 each) in
 *   D_800DCA30[3][10]; for each, two random byte angles, four func_151423D8
 *   (sin/cos table) lookups, a raycast func_150AC9C0 from (0,300,0) along
 *   (10 sinB cosA, -10 cosB, 10 sinB sinA); the hit point is pushed out by
 *   D_80096570 about y=300.  Then a func_151491F4 spawn + memcpy of a 6-byte
 *   {0x14, 0x32, 0} block to +0x28.
 *
 * ===================  THE FOURTEENTH SCALAR: IDENTIFIED  ====================
 * The previous revision of this file reached the frame with `s32 pad0;`, an
 * admitted placeholder.  That slot is now a REAL VARIABLE: `sinB`, the named
 * result of the FOURTH func_151423D8 call.  Golden is
 *
 *     t = 10.0f * sinB      ->  mul.s $f2, $f18, $f0     (constant in fs)
 *
 * whereas multiplying the CALL directly,
 *
 *     t = 10.0f * func_151423D8(...)   ->  mul.s $f2, $f0, $f18
 *
 * puts the call result in fs.  Both operand orders in the source produce the
 * SECOND form (measured: `10.0f * f(x)` and `f(x) * 10.0f` are identical), so
 * the only way to reach golden's operand order is for the call result to be
 * bound to a name before the multiply.  That is positive evidence for a
 * fourteenth named f32, not merely a slot count -- and it removed a row (50->49).
 *
 * HONEST CAVEAT: `sinB` is register-resident, so its NAME is not observable;
 * `t = f(x); t = 10.0f * t;` (reusing t, keeping a pad) also scores 49.  What
 * distinguishes them is parsimony: the sinB reading explains the frame with
 * fourteen REAL locals and no residue, the t-reuse reading leaves an
 * unexplained slot.  There is no longer any placeholder in this file.
 *
 * ===================  THE FRAME LAW, RE-DERIVED HERE  =======================
 *   frame = roundup8(0xA4 + total declared local bytes), locals packed DOWNWARD
 *   from the frame top in DECLARATION order.  Measured both ways:
 *     14 scalars + struct17 + s16[3]  = 76 bytes -> 0xF8   (golden)
 *     13 scalars                      = 72 bytes -> 0xF0   (and p lands at 0xAC)
 *   The grouping is forced, not chosen: 5 scalars above struct17 spD8 (0xD8),
 *   5 more above s16 spBC[3] (0xBC, the array is padded to 4), then FOUR
 *   scalars of which `p` must be the THIRD (0xB0).  Any other count or
 *   grouping moves every sp-relative row.
 *   IMPORTANT COROLLARY, measured: a local declared in a NESTED BLOCK gets no
 *   frame slot of its own (the block-scope `q` below is free), and a
 *   function-scope `q = p` is copy-propagated into the load, losing BOTH the
 *   `or $s0,$v1,$zero` AND its slot (frame 0xF0, 173 rows).
 *
 * OTHER DISCOVERIES (do not undo):
 *  1. `divu`, not `div`.  The modulus is UNSIGNED: `(u32)func_150ADA20() % 13U`.
 *     Signed `%` costs five extra instructions (the -1/overflow check).  162 -> 156.
 *  2. THE MISSING `or $s0,$v1,$zero` (worth ~110 rows).  Declaring q INSIDE the
 *     do-block -- { Slot *q; j = 0; q = p; for (; j != 0xA0; j += 0x10) {...} } --
 *     makes IDO load into $v1 and copy.  156 -> 157 instructions, 169 -> 53.
 *     Measured and rejected: q as `Slot (*p)[10]` + `*p`/`p[0]`/`&p[0][0]`;
 *     `q = &p[0]`, `q = p + 0`; `void *p`; `u8 *p`; `s32 p` (+2 instrs, 160);
 *     `volatile` p (+2, 152); a second copy `qq = p; q = qq;` (169);
 *     `p[j]`/`q[j]` subscripting (168/203); an inner do-while (+4, 138);
 *     q at function scope in every tail slot (173).
 *
 * ===============  RESIDUAL (19 real rows) -- RANKING TIE  ===================
 * Three coupled clusters, all register/schedule, none semantic:
 *   - `scale`/`y0` are swapped between $f30 and $f28 (idx18-23, 74).  Re-swept
 *     THIS wave: 2 declaration orders x 4 assignment orders = 8 spellings, ALL 49.
 *   - `p`'s address lands in $v0, golden's in $v1 (idx20, 21, 26, 31, 33).
 *     4 spellings of `p = ...` and 3 init-statement orders: ALL 49.
 *   - the else-body idx98-107 is the same eleven instructions UNSCHEDULED.
 *     Golden hoists all three spD8 loads above the first store; ours cannot,
 *     because &spD8.unk0/4/8 escape into func_150AC9C0 and IDO therefore treats
 *     a store through `q` as a possible alias.  All 6 statement permutations,
 *     spD8 as 3 separate f32s, spD8 as f32[3], `f32 *q`, scale-on-the-left,
 *     inner-while and outer-for/while: ALL 49-51.
 * DIAGNOSTIC (do not ship, but it localises the cause): reading the three
 * fields into dead c1/s1/c2 first DOES hoist the loads (proving the alias
 * theory), and the permuter's `q->unk4 = y0; q->unk4 = ... + q->unk4;`
 * double-store DOES flip $f28/$f30 to golden's assignment -- but each costs a
 * real instruction (n=158) and is a forcer.  REJECTED.
 *
 * PERMUTER: 3167 iterations, REQUIRE_FRAME=248 + REQUIRE_OFFSETS=1.  Best
 * "425" output re-scored with fastscore = 86 at n=158.  A false win; its two
 * moves were (i) replacing `zero` with 0.0f literals, which merely recreates
 * an unused local, and (ii) the double-store forcer above.  Both rejected.
 */
#include <ultra64.h>

#include "functions.h"
#include "variables.h"

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    u8 padC[0x174];
} D_800BE628View15012370;

void func_15012370(void) {
    f32 temp_f0;
    f32 temp_f2;
    f32 temp_f24;
    f32 one;
    f32 half;
    s32 i;

    i = 0;
    if (D_80082FA0 >= 0) {
        temp_f24 = D_80096560;
        one = 1.0f;
        half = 0.5f;
        do {
            func_151EF954(
                ((f32 (*)[4][4])D_800DCC10)[i],
                -(temp_f0 = (*(D_800BE628View15012370 **)&D_800BE628)[i].unk4 * half),
                temp_f0,
                -(temp_f2 = (*(D_800BE628View15012370 **)&D_800BE628)[i].unk8 * half),
                temp_f2,
                one,
                temp_f24,
                one);
            i = (i + 1) & 0xFF;
        } while (D_80082FA0 >= i);
    }
}

void func_15012470(void) {
    D_80088750 = func_1518AADC(4, 300, 0);
}

extern s32 func_150AC9C0(f32, f32, f32, f32, f32, f32, void *, void *, f32 *, f32 *, f32 *, s32, s32 *, s32, f32);

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    s32 unkC;
} Slot;

extern Slot D_800DCA30[3][10];
extern u8 D_8009F920[];

void func_150124A0(void) {
    f32 c1;
    f32 s1;
    f32 c2;
    f32 sinB;
    f32 t;
    struct17 spD8;
    f32 zero;
    f32 scale;
    f32 y0;
    s32 ang1;
    s32 ang2;
    s16 spBC[3];
    s32 j;
    u8 *r;
    Slot *p;
    struct260 *o;

    scale = D_80096570;
    y0 = 300.0f;
    zero = 0.0f;
    p = &D_800DCA30[0][0];
    r = D_8009F920;
    do {
        {
        Slot *q;
        j = 0;
        q = p;
        for (; j != 0xA0; j += 0x10) {
            ang1 = (s16)((r[0xC] + ((u32)func_150ADA20() % 13U)) - 0x86);
            ang2 = (s16)((func_150ADA20() & 0xF) - 0xA);
            c1 = func_151423D8((u8)(ang1 - 0x40));
            s1 = func_151423D8((u8)ang1);
            c2 = func_151423D8((u8)(ang2 - 0x40));
            sinB = func_151423D8((u8)ang2);
            t = 10.0f * sinB;
            if (func_150AC9C0(zero, y0, zero, t * c1, -10.0f * c2, t * s1, 0, 0,
                              &spD8.unk0, &spD8.unk4, &spD8.unk8, 0, 0, 0, zero) == 0) {
                q->unk0 = zero;
                q->unk4 = zero;
                q->unk8 = zero;
            } else {
                q->unk0 = spD8.unk0 * scale;
                q->unk4 = ((spD8.unk4 - y0) * scale) + y0;
                q->unk8 = spD8.unk8 * scale;
            }
            q++;
        }
        }
        p += 10;
        r += 0x10;
    } while (p != (Slot *)D_800DCC10);
    spBC[0] = 0x14;
    spBC[1] = 0x32;
    spBC[2] = 0;
    o = func_151491F4(0x12C, -1, 7, 0, 0, 6, 0xFF, 0);
    if (o != NULL) {
        memcpy((u8 *)o + 0x28, spBC, 6);
    }
}
