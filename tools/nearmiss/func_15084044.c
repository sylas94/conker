/* func_15084044  --  conker/src/game_AEB40.c   (194 instrs, 0 fp, 3 callees)
 *
 * ############################################################################
 * ### 2026-08-14 WAVE 3 (PERMUTER WAVE).   70 -> 10.   13 rows -> ONE ROW.  ###
 * ### But read the HONESTY FLAG below before treating the 10 as the base.   ###
 * ############################################################################
 *
 * STATUS
 *   parked-honest base   asm-differ 70   13 differing rows   <- the C at the bottom
 *   improved base        asm-differ 10    1 differing row    <- one-line change, FLAGGED
 *   permuter zero        asm-differ  0                       <- REFUSED, banned forcer
 *
 * Both numbers confirmed on the REAL loop (make + `diff.py -o func_15084044 -R
 * --max-lines 4096`), identical with and without -R, frame 0x60 throughout.
 *
 * =========================================================================
 * 1. THE PERMUTER REACHED ZERO AND IT IS A FAKE.  QUOTED SO NOBODY RE-FINDS IT.
 * =========================================================================
 * From the 13-row base, decomp-permuter (TU harness, frame+stack-offset gated, the
 * fake-construct passes already zeroed) hit score 0 at iteration 1987 of ~7,500 with
 * exactly one edit -- in the mode-1 guard:
 *
 *     -   if ((base->unk28C == 0) || (base->unk28C          == tmpl))
 *     +   if ((base->unk28C == 0) || ((obj = base->unk28C)  == tmpl))
 *
 * `obj` is DEAD at that point: its only read is the `mode` ternary far above, and it
 * is never read again.  That is a dead assignment whose sole effect is to consume one
 * more IDO virtual-register number -- the temp-rotation-counter forcer the project
 * memory describes.  REFUSED under the no-fake-matches rule.  Its value is diagnostic
 * only: it proves a zero exists one virtual register away, and it says the defect is
 * "one value too few in the numbering", not "wrong expression".
 *
 * =========================================================================
 * 2. THE HONEST 70 -> 10.  ONE LINE.  BUT IT IS FORCER-SHAPED -- JUDGEMENT NEEDED.
 * =========================================================================
 * The permuter's OTHER output (score 10) carried a single honest-looking edit:
 *
 *     -   tmpl = (&D_800D19A0)[idx];
 *     -   if (tmpl == 0) {              return 0; }
 *     +   tmpl = (&D_800D19A0)[idx];
 *     +   if ((&D_800D19A0)[idx] == 0) { return 0; }
 *
 * i.e. the null test re-reads the array instead of testing the local just assigned
 * from it.  That ALONE fixes twelve of the thirteen rows: it puts the 0x28C CSE in
 * $a3 and tmpl in $a0, exactly as golden has them, and every one of the 13 rows the
 * previous two waves chased was that one colour.
 *
 * HONESTY FLAG -- I did not ship this and I would not ship it at 0 without a ruling.
 * It emits IDENTICAL INSTRUCTIONS at its own site (one load into $a0, one test of
 * $a0, same as `if (tmpl == 0)`); its only effect is the downstream register colour.
 * That is the exact signature of a forcer, even though it is not on the banned list
 * (it is not dead code, not a no-op, not an unused local -- it computes a real value
 * and tests it).  It is a redundant RE-READ.  Whether a human wrote
 * `tmpl = arr[idx]; if (arr[idx] == 0) return 0;` is a judgement call, and the
 * ordering is load-bearing in a way that argues against it: moving the assignment to
 * AFTER the test -- the reading a human would more likely write -- scores 195, not 1.
 *
 * =========================================================================
 * 3. THE ONE ROW THAT IS LEFT
 * =========================================================================
 *     0x2ad0   ours 14870025 = bne $a0,$a3      golden 14e40025 = bne $a3,$a0
 * Same test, same branch target, same two registers ($a3 = the 0x28C CSE, $a0 = the
 * `tmpl` local).  ONLY which operand IDO puts in rs.  Ours puts the LOCAL in rs,
 * golden puts the CSE there.
 *
 * The previous wave's rule "IDO canonicalises the compare by register number, higher
 * in rs" is now DISPROVED: ours is rs=$a0(4), rt=$a3(7) -- lower in rs.  It held only
 * by coincidence while the colour was wrong.  Elsewhere in this same function, where
 * BOTH operands are compiler CSEs, rs is reliably the FIRST source operand
 * (`beql $v0,$t6` at 0x15084230, `bnel $t7,$t8` at 0x15084248, `beql $a3,$t4` at
 * 0x150842A8 -- all match us).  The working rule is therefore: with two CSEs, rs =
 * first source operand; with a CSE and a LOCAL, IDO puts the local in rs regardless
 * of source order.  Golden has the CSE in rs, so in golden that operand is NOT a
 * local -- but see the frame proof in section 5 for why it cannot be one here either.
 *
 * =========================================================================
 * 4. NEGATIVES MEASURED THIS WAVE, ALL FROM THE 1-ROW BASE
 * =========================================================================
 * Every negative in the previous park entry was measured with the CSE mis-coloured
 * $v0, so the whole list had to be re-run once the colour was right.  All of these
 * leave the last row untouched at mism=1 unless stated.
 *
 *   OPERAND / BOOLEAN SPELLING of the failing compare -- ALL INERT (9 forms, all 1):
 *     `x == tmpl` / `tmpl == x` / `0 == x` on the first operand / `!x` for the first
 *     operand / `!((x != 0) && (x != tmpl))` / `!((x != 0) && (tmpl != x))` /
 *     `!(x != 0) || !(x != tmpl)` / `x == 0 || !(x != tmpl)`.
 *     Swapping the two `||` operands is WORSE (2 rows -- it reorders the branches).
 *     IDO fully canonicalises this site; the C-level order carries no information.
 *
 *   DECLARATION ORDER -- ALL 720 RE-RUN FROM THE 1-ROW BASE, histogram = {1: 720}.
 *     Inert again, frame -96 throughout.  This lever is now dead twice over.
 *
 *   TYPE / SHAPE RE-SWEEP (all 1): tmpl as `s32 *`, tmpl `u32`, ret `u32`, arg1 `u32`,
 *     base `u8 *`, obj `u8 *`, size via `<< 4`, truthy early return, nested-if early
 *     return, `!arr[idx]` null test, `0 ==` on the allocate result, mode ternary as
 *     if/else.   WORSE: mode as `u8` 75; `idx` computed after `mode` 15.
 *
 *   DELETE-A-LOCAL (the transformation that closed func_150D5124 this same wave):
 *     drop `idx` 673 (frame -80), drop `tmpl` 163, drop `size` 205, drop `base` 17.
 *     drop_base is instructive: it keeps all 13 CSE rows and ADDS 4 -- `ret`'s spill
 *     slides 0x48 -> 0x4C because losing a pre-`ret` local moves `ret` to ordinal 5.
 *
 *   MIS-DECLARED-GLOBAL LAW -- CLEAN NEGATIVE, NOW ACTUALLY TESTED.
 *     The previous entry dismissed this law because `base` has no global in its address
 *     chain.  True, but the function touches three ARRAY globals that variables.h
 *     declares wrongly, and those were never tested.  Using the TU-scoped
 *     `#define SYM SYM_decl_in_variables_h` + `#include` + `#undef` idiom (the same one
 *     game_AEB40.c already uses for two prototypes, precedent commit 468e0e1):
 *         `extern s32 D_800D19A0[];`  + `D_800D19A0[idx]`            -> 13 (no change)
 *         `extern u8  D_800D1F80[];`  + `D_800D1F80[idx]`            -> 13 (no change)
 *         both together                                             -> 13 (no change)
 *     and the already-matched sibling func_150843AC, which uses both, emitted
 *     BYTE-IDENTICAL code in all three.  The law does not bite here.
 *     (The #undef is required: without it your own declaration is parsed as a
 *     redeclaration of the renamed symbol and cfe errors.)
 *
 *   WHERE `tmpl` IS ASSIGNED -- all much worse, and the 1-row base is a sharp optimum:
 *     assign inside both arms 154; assign only in the mode-0 arm and read the array in
 *     the mode-1 guard 148; keep the local null test but read the array in the guard
 *     195; move the assignment to after the null test 195.
 *
 * =========================================================================
 * 5. NEW FRAME LAW -- THIS PERMANENTLY KILLS THE "GIVE THE CSE A VARIABLE" FAMILY
 * =========================================================================
 * A TENTH local moves the frame 0x60 -> 0x68 NO MATTER WHICH DECLARATION SLOT IT SITS
 * IN (all ten slots measured, all frame -104, all mism 204).  The function already has
 * exactly nine locals, and golden's frame is 0x60.  Therefore the 0x28C value CANNOT
 * be a declared variable in golden -- it must be a compiler CSE -- and every "give the
 * CSE its own local `cur`" idea (the previous wave's 1220, and my role-swap idea of
 * making `base->0x28C` the local and `tmpl` the CSE) is unreachable BY THE FRAME, not
 * by luck.  So is any other spelling that needs one more named value.
 * Refinement of the old note: "6..9 locals all give framesize 0x60" -- 10 gives 0x68.
 *
 * =========================================================================
 * 6. PERMUTER BUDGET SPENT (all with the TU harness, gated
 *    PERMUTER_TU_REQUIRE_FRAME=96 PERMUTER_TU_REQUIRE_OFFSETS=1, fake passes zeroed)
 * =========================================================================
 *   from the 13-row base: 9,930 iterations over three runs (5,898 at -j 6, then 1,987
 *       and 2,045 at -j 10).  The histogram bottomed out AT THE BASE: 1,404 ties at 70,
 *       next best 75, then 80; nothing under 70 except the two outputs.  Those were
 *       score 10 (the honest one-liner in section 2) and score 0 (the banned dead
 *       assignment in section 1, found at iteration 1987 of the second run).
 *   from the 1-row base: 11,132 iterations at -j 10, --only-if-below 1 so that EVERY
 *       distinct zero would be captured for auditing rather than stopping at the first.
 *       ZERO zeros.  Histogram: 2,680 ties at 10, then 15, 20, 25, 30, 45 -- it never
 *       went below the base.  Total across both bases: 21,062 gated iterations.
 *
 * VERDICT: BOUNDED at 1 row for every honest source shape I can name or the permuter
 * can reach.  The residual is a single `bne` operand order at 0x2ad0, and section 3
 * plus the frame law in section 5 together say it needs golden's second operand to be
 * something other than a declared local while the frame forbids adding one.  Do not
 * hand-search the spelling space again -- it is measured and inert.  The only lever
 * anyone should still consider is a STRUCTURAL re-reading of the mode-1 arm that makes
 * the compare's right-hand side a CSE without adding a tenth local.
 *
 * THE C BELOW IS THE HONEST 13-ROW / asm-differ 70 BASE (unchanged from wave 2), so
 * that this file never carries the flagged construct as if it were settled.  To
 * reproduce the 1-row base, change the tmpl null test to `if ((&D_800D19A0)[idx] == 0)`.
 */

extern void func_10004074(void *arg0);
extern s32 D_800CC0E8;
extern u16 D_800C57A0[];
extern s32 D_800D19A0;
extern s32 D_800D1F80[187];
extern s32 allocate_memory(s32, s32, s32, s32);

s32 func_15084044(void *arg0, s32 arg1) {
    s32 *base;
    s32 *p;
    s32 obj;
    s32 mode;
    s32 tmpl;
    s32 ret;
    s32 size;
    s32 i;
    u8 idx;

    base = (s32 *)((u8 *)arg0 + (arg1 * 8));
    if (((u8 *)arg0)[0x65] != 0) {
        obj = *(s32 *)((u8 *)&D_800CC0E8 + (((u8 *)arg0)[0x65] * 0x32C));
    } else {
        obj = *(s32 *)((u8 *)arg0 + 0x144);
    }
    idx = (*(u8 **)((u8 *)arg0 + 0x2C4))[arg1];
    mode = (obj != 0) ? (((u8 *)obj)[0x10] & 3) : 0;
    if (idx == 0) {
        mode = 2;
    }
    if ((*(s32 *)((u8 *)base + 0x28C) != 0) && (*(s32 *)((u8 *)base + 0x290) != 0)) {
        return 0;
    }
    tmpl = (&D_800D19A0)[idx];
    if (tmpl == 0) {
        return 0;
    }
    ret = 0;
    if (mode == 0) {
        *(s32 *)((u8 *)base + 0x290) = tmpl;
        *(s32 *)((u8 *)base + 0x28C) = tmpl;
        ((u8 *)D_800D1F80)[idx] += 2;
    } else if (mode == 1) {
        if ((*(s32 *)((u8 *)base + 0x28C) == 0) || (*(s32 *)((u8 *)base + 0x28C) == tmpl)) {
            if (((u8 *)D_800D1F80)[idx] != 0) {
                size = D_800C57A0[idx] * 16;
                *(s32 *)((u8 *)base + 0x28C) = allocate_memory(size, 1, 2, 2);
                if (*(s32 *)((u8 *)base + 0x28C) == 0) {
                    ret = 1;
                } else if (*(s32 *)((u8 *)base + 0x28C) != 0) {
                    bcopy((void *)(&D_800D19A0)[idx], (void *)*(s32 *)((u8 *)base + 0x28C), size);
                } else {
                    *(s32 *)((u8 *)base + 0x28C) = (&D_800D19A0)[idx];
                }
            } else {
                *(s32 *)((u8 *)base + 0x290) = tmpl;
                *(s32 *)((u8 *)base + 0x28C) = tmpl;
                ((u8 *)D_800D1F80)[idx] += 2;
            }
        }
        *(s32 *)((u8 *)base + 0x290) = *(s32 *)((u8 *)base + 0x28C);
    } else if (mode == 2) {
        i = 0;
        p = (s32 *)((s8 *)arg0 + (arg1 << 3));
        do {
            if ((*(s32 *)((u8 *)p + 0x28C) == 0)
             || (*(s32 *)((u8 *)p + 0x28C) == (&D_800D19A0)[idx])
             || ((i == 4) && (*(s32 *)((u8 *)base + 0x28C) == *(s32 *)((u8 *)base + 0x290)))) {
                if (((u8 *)D_800D1F80)[idx] != 0) {
                    size = D_800C57A0[idx] * 16;
                    *(s32 *)((u8 *)p + 0x28C) = allocate_memory(size, 1, 2, 2);
                    if (*(s32 *)((u8 *)p + 0x28C) == 0) {
                        ret = 1;
                        if (i == 4) {
                            if (*(s32 *)((u8 *)base + 0x28C) != (&D_800D19A0)[idx]) {
                                func_10004074((void *)*(s32 *)((u8 *)base + 0x28C));
                            } else {
                                ((u8 *)D_800D1F80)[idx] -= 1;
                            }
                            *(s32 *)((u8 *)base + 0x28C) = 0;
                        }
                        break;
                    }
                    if (*(s32 *)((u8 *)p + 0x28C) != 0) {
                        bcopy((void *)(&D_800D19A0)[idx], (void *)*(s32 *)((u8 *)p + 0x28C), size);
                    } else {
                        *(s32 *)((u8 *)p + 0x28C) = (&D_800D19A0)[idx];
                    }
                } else {
                    *(s32 *)((u8 *)p + 0x28C) = (&D_800D19A0)[idx];
                    ((u8 *)D_800D1F80)[idx] += 1;
                }
            }
            i += 4;
            p++;
        } while (i != 8);
    }
    return ret;
}
