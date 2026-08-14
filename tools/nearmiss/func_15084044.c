/* func_15084044  --  conker/src/game_AEB40.c   (221 asm lines, 0 fp, 3 callees)
 * PARKED AT 70.  max_score 81400.  Residual: ALLOCATION (one virtual register).
 *
 * ############################################################################
 * ### 2026-08-14 WAVE 2.  STILL 70.  THE SEARCH SPACE BELOW IS NOW CLOSED. ###
 * ############################################################################
 * Baseline re-confirmed in my own build before any change: 70 with -R, frame 0x60,
 * 13 differing rows -- byte-for-byte the 13 rows the previous wave listed.
 *
 * NEW TOOL, USE IT FIRST NEXT TIME: tools/fastscore.py gives the EXACT same row
 * count in 0.7 s instead of ~60 s (asm_processor + IDO cc into a private dir, then a
 * relocation-masked word compare against the golden .s; it never touches conker/build/
 * so it needs no buildlock).  Verified against asm-differ on this very function:
 *     python3 tools/fastscore.py game_AEB40 func_15084044 cand.c   ->  mism=13
 * That is what made the 720-case sweep below affordable (466 s total).
 *
 * === THE MIS-DECLARED-GLOBAL LAW DOES NOT APPLY HERE.  CLEAN NEGATIVE. ===
 * The wave brief asked to check whether `base`'s global is mis-declared in variables.h.
 * THERE IS NO GLOBAL IN THE ADDRESS CHAIN.  `base` is derived entirely from the
 * PARAMETER arg0:  base = (s32 *)((u8 *)arg0 + (arg1 * 8)), and golden's access is a
 * plain `lw $a3,0x28C($s4)` -- one register plus an immediate, which every spelling
 * produces identically.  The shadow idiom has nothing to bite on.  No change made,
 * score before = 70, score after = 70.
 *
 * === THE 13 ROWS ARE ONE DEFECT, AND THE OPERAND FLIP IS NOT A SECOND ONE ===
 * Confirmed from the raw words: ours 14820025 = bne $a0,$v0 ; golden 14e40025 =
 * bne $a3,$a0.  BOTH put the HIGHER-NUMBERED register in rs (ours a0=4 > v0=2,
 * golden a3=7 > a0=4).  So IDO canonicalises the compare by register number and the
 * operand order is a pure consequence of the colour.  Fix the colour, fix all 13.
 *
 * === WHAT THE COLOUR ACTUALLY IS (read this before theorising again) ===
 * Golden's caller-saved pseudos:  v0=obj, v1=mode, a0=tmpl, a1=arg1, a2=arg0, a3=P1
 * (P1 = the CSE of *(s32 *)((u8 *)base + 0x28C)).  All six are used.
 * Ours:                           v0=obj THEN RECYCLED FOR P1, v1=mode, a0=tmpl,
 * a1=arg1, a2=arg0, a3 never used as a pseudo.
 * So the single question is: why does golden NOT recycle $v0 for P1 after `obj` dies?
 * Everything else -- frame 0x60, ret spilled at 0x48 (ordinal 6), the 0x30 address-CSE
 * temp, every branch, every call site -- already matches.
 *
 * === NEGATIVE: DECLARATION ORDER IS COMPLETELY INERT.  ALL 720 CASES MEASURED. ===
 * This retires parked lever #2 ("reorder the five pre-`ret` locals").  With `ret`
 * pinned at ordinal 6, every one of 5! x 3! = 720 orderings of the other eight locals
 * was built and scored:  best = 13, and in fact EVERY SINGLE ONE scored exactly 13,
 * with frame -96 throughout.  466 s, tools/fastscore.py.  DO NOT REPEAT THIS SWEEP.
 *
 * === NEGATIVES: ~25 SOURCE-SHAPE VARIANTS, ALL EXACTLY 13 (base 13) ===
 * nested ifs instead of the `&&` in the early return; if/else instead of the `mode`
 * ternary; `!tmpl` for `tmpl == 0`; `base` declared `u8 *`; reversed `||` operands in
 * the mode-1 guard; `idx` and `mode` statements swapped; `base` computed later; blank
 * line before the mode chain; truthiness (`if (a && b)` with no `!= 0`); `arg1` as u32;
 * `ret` as u32; `size` via `<< 4`; `p` cast through u8 * instead of s8 *; `0 ==` on the
 * allocate_memory result test; `obj` typed `u8 *`; `mode` typed u8; `tmpl` typed `s32 *`;
 * capturing arg0[0x65] into a new `u8 kind` local in each of 9 declaration slots.
 * WORSE, with scores: `switch (mode)` 177 rows + frame 0x68; `p = base` 203 (192 instrs,
 * two short -- golden really does recompute p from arg0/arg1); `arg1 << 3` for `base`
 * 203 (same 192-instr collapse, so the `* 8` spelling is REQUIRED); `arg0` typed `u8 *`
 * 15; reversing the `(&D_800D19A0)[idx] ==` compare in the loop 14; passing bcopy's dst
 * as `*(void **)` 47; moving the `mode` computation after the early returns 13 rows but
 * it re-colours `base` s4 -> s5 (a WORSE shape that my first metric mistook for a win --
 * count the register in `lw ?,0x28C(?)`, never grep for a fixed base register).
 *
 * === WHAT IS LEFT TO TRY (nothing cheap remains; this needs the permuter) ===
 * Every source-level lever I can name is now measured and inert, and the residual is a
 * single virtual-register colour with the instruction stream already exact.  That is
 * precisely the decomp-permuter's job, and with tools/fastscore.py the iteration cost is
 * 0.7 s, so a long run is finally affordable:  import the TU, PERMUTER_TU_REQUIRE_FRAME
 * =0x60, and drive on the 13-row metric.  If a wave cannot run the permuter, DO NOT
 * hand-search this function again -- the hand-search space is exhausted.
 *
 * Baselines measured (all `-o func_15084044 -R --max-lines 4096`, expected/ seeded
 * from a clean pragma build of the TU):
 *     721   build #1, natural transcription, 9 locals with `ret` declared last
 *     685   same, `ret` moved to declaration slot 6  (frame law: (0x60-0x48)/4 = 6)
 *      70   same, `return ret` inside the mode-2 loop replaced by `break`
 *    1220   NEGATIVE -- `cur` promoted to a declared local (see below)
 *
 * WHAT IS LEFT (13 rows, all one issue):
 *   golden holds the CSE of *(s32 *)((u8 *)base + 0x28C) in $a3; this source puts
 *   it in $v0 (the register `obj` vacates).  Every one of the 13 differing rows is
 *   that substitution, e.g.
 *       golden   2a54: lw a3,0x28c(s4)      mine  2a54: lw v0,0x28c(s4)
 *       golden   2ad0: bne a3,a0,2b68       mine  2ad0: bne a0,v0,2b68
 *   The operand order of that `bne` follows from the register numbers (rs is the
 *   higher-numbered register in both), so it is one defect, not two.
 *
 * NEGATIVE, WITH ITS SCORE -- 1220, base 70.  Promoting the CSE to a declared
 * local `s32 cur;` (assigned at each of the four sites where golden re-loads the
 * field) is WRONG.  It grew the frame 0x60 -> 0x68 and re-coloured s4/s5/a1/a2,
 * proving golden's value is a compiler CSE of the field read and not a variable:
 *   - a declared local would not be re-loaded after `base->unk28C = allocate_memory(...)`,
 *     yet golden re-loads at 2b20 while testing the raw call result at 2b0c;
 *   - the skip path `bne a3,a0,2b68` reaches `sw a3,0x290(s4)` carrying the value
 *     read at the TOP of the function, which is exactly CSE reach-in.
 *
 * FRAME LAW NOTES (confirmed by measurement on this function):
 *   framesize 0x60; arg-build 0x00-0x13, saved s0-s5+ra 0x14-0x2F, compiler temp
 *   at 0x30 (the spill of the &D_800D1F80[idx] address CSE across allocate_memory
 *   -- an ADDRESS CSE, so a temp slot, not a home), locals home ends at 0x60.
 *   `ret` is the only spilled local: 0x48 => declaration ordinal 6.  With 9 locals
 *   the home is 0x3C-0x5F; 6..9 locals all give framesize 0x60, so the count is
 *   free but the ORDINAL OF `ret` IS NOT.
 *
 * NEGATIVE, WITH ITS SCORE -- 70, base 70 (NO CHANGE).  Reversing the compare to
 * `tmpl == base->unk28C' does NOT move it.  Worth recording because the same
 * rewrite DID fix a three-register cluster in func_1000A03C this wave (golden
 * `bnel t7,t8' with rs = the second source operand), so IDO's operand
 * normalisation is not uniform: it reverses a compare of two field READS but not
 * one where an operand is already a live register.
 *
 * NEGATIVE, WITH ITS SCORE -- 820, base 70.  Demoting `base' and `tmpl' from
 * locals to inline expressions (7 locals, `ret' still 6th) is wrong: without the
 * `tmpl' local IDO stops sharing the two `(&D_800D19A0)[idx]' reads across the
 * store to +0x290 in the mode-0 arm and emits an extra `lw t4,0(s3)'.  So `tmpl'
 * IS a declared local even though it is re-loaded at 2b98/2c14 (those re-loads
 * are in the mode-2 loop, past a call, where the local is dead).
 *
 * STILL UNTRIED (next levers, in the order I would try them):
 *   1. drop `base` and `tmpl` as declared locals (both are pure CSEs in golden:
 *      `base` is an arg-only address expression, `tmpl` is re-loaded at 2b98/2c14),
 *      keeping some other pair in the five pre-`ret` slots so `ret` stays 6th.
 *   2. reorder the five pre-`ret` locals.
 *   3. permuter on this TU with PERMUTER_TU_REQUIRE_FRAME=0x60.
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
