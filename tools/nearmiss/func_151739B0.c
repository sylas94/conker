/* game_1A0E60 / func_151739B0  (688 B)  -- NEAR MISS
 *
 *   raw fastscore : mism=71   frame=-64  n=172/172     (was 128)
 *   n= gap        : ZERO.  Golden is 172 words, ours is 172, and the golden .s
 *                   has no trailing pad (func_15173C60 starts immediately).
 *   pad-corrected : 71, all of it mismatch ROWS, none of it length phantom.
 *   stack offsets : `permuter_tu.sh frame` reports base MATCHES golden
 *                   (29 displacements, exact multiset).
 *
 * WHAT IT IS: a leaf vertex-colour blend.  For each group i in [start,end) and
 * each vertex j in that group it does, per channel c in {0,1,2}:
 *     vtx[idx].cn[c] = (((src[c] - ref[c]) * arg2) >> 8) + ref[c];
 * $ra is used as a general register (leaf), holding &D_800B0DF0.
 *
 * WHAT IS NOW EXACT: idx0-80 and idx114-171 match at the instruction level
 * apart from register naming -- that is the whole prologue, all four early
 * returns, the three-way ref selection, the sll/lui/lw CSE placement, the loop
 * guard, the strength-reduced grp init in the preheader, the whole 3-channel
 * body, both loop tails and the epilogue.
 *
 * THREE THINGS CLOSED IT (128 -> 71).  Keep all three.
 * ---------------------------------------------------
 *  A. The inner loop is a `while` with an EXPLICIT `j++` in the body, not a
 *     `for (j = 0; j < ...; j++)`.  Golden groups all four increments together
 *     (`addiu t1,1 / t2,2 / t3,3 / a3,3`); a `for` puts j++ alone at the loop
 *     bottom.                                              128 -> 121 -> 113
 *  B. `grp` is the BASE pointer indexed by i (`grp[i].unk4`), NOT a walking
 *     pointer initialised to &D_800B0E30_p[arg0][start] with `grp++` at the
 *     bottom.  IDO strength-reduces grp[i] into golden's `addu s0,v0,t6` in the
 *     LOOP PREHEADER plus `addiu s0,s0,0xC` -- exactly golden.  It must be
 *     assigned AFTER the vtx selection.                     -> 113
 *  C. `grp` is declared INSIDE the block that owns the loop, and `i` is moved
 *     up to function scope to keep the function-scope local count at four.
 *     This is what finally hoists `sll $s3, $a0, 2` to func+0x58 (idx22, the
 *     entry region) while leaving the whole %hi/%lo(D_800B0E30) chain late at
 *     idx61-78 -- THE TENSION THE OLD HEADER SAID NOBODY HAD SEPARATED.
 *                                            113 -> 78 (grp) -> 71 (i + inits)
 *
 * FRAME.  Golden's frame is 0x40 = FOUR function-scope local words (of which
 * only 0x30 is used, for `end`).  Slots run downward from frame-4 = 0x3C, so
 * `end` must be the FOURTH and last declared: vtx(0x3C) i(0x38) start(0x34)
 * end(0x30).  Moving grp out of function scope without adding `i` puts `end` at
 * 0x34 and costs 4 rows.  Any of the three orders that keep `end` last is flat.
 *
 * THE REMAINING 71 ROWS -- exactly two clusters
 * ---------------------------------------------
 *  (1) idx81-89, the inner-loop PREHEADER.  Golden loads unk4/unk0 into v0/v1
 *      BEFORE the `blez` guard and then COPIES them into the loop's induction
 *      registers after it:
 *          lw v0,0x4(s0) / lw v1,0x0(s0) / blez t8
 *          or t1,zero,zero  (j) / or t2,v0,zero (idxp)
 *          or t3,zero,zero  (k) / or a3,v1,zero (src)
 *      Ours coalesces the copies away and loads straight into t1/t2.  Golden's
 *      preheader order is j, idxp, k, src.  Six declaration/assignment forms
 *      were swept (initialised-at-declaration vs declare-then-assign, four
 *      orders): they move the score between 71 and 78 but NONE reproduces the
 *      four `or`s.  Something forces IDO not to coalesce; not yet identified.
 *  (2) idx94-113, the two `ref` arms.  Golden issues `multu $t0,$t5` (idx*3)
 *      FIRST and, with the multiplier busy, STRENGTH-REDUCES the second product
 *      `D_800BE524_p[arg4] * 3` to `sll/subu`.  Ours evaluates the D_800BE524
 *      chain first, so both products become register multiplies and a `nop`
 *      appears at idx108.  Golden also emits `bnez $fp` + `nop` where ours emits
 *      `bnezl` + a duplicated load -- consistent, because golden's arm-2 block
 *      starts with a `multu`, which IDO will not speculate into a likely-branch
 *      delay slot.  Four associativity spellings of arm 2 were swept: r2a/r2b/
 *      r2d are flat, r2c (`&D_800BE510_p[a*3 + b*3]`) is much worse (124, and
 *      it loses a word).  The lever is EVALUATION ORDER of the two `* 3`, not
 *      association.
 *
 * DO NOT REPEAT (all measured; the ones marked NEW were re-measured on the
 * 71-row base because the codegen changed under the old results):
 *   - grp = D_800B0E30_p[arg0] + start / &[..][start]     -> 125-140
 *   - grp assigned before the vtx selection                -> 125
 *   - grp assigned at the very top of the function         -> 154
 *   - no grp local at all, D_800B0E30_p[arg0][i] inlined   -> 210, n=178
 *   - grp assigned INSIDE the outer loop (ptr or index)    -> 195, frame 0x68
 *   - `for` instead of `while` for the inner loop     NEW  -> +8
 *   - swapping the `s32 idx` / `u8 *ref` declarations NEW  -> flat
 *   - a `u8 **row = D_800BE520_p[arg0];` local in the else NEW -> 119
 *   - a `u8 *p = D_800BE510_p;` local in the arg1==0 arm NEW -> 154, n=173
 *   - splitting D_800B0E34_p into a local first        NEW -> 135
 *   - vtx moved into the loop block as well            NEW -> frame 0x38, wrong
 *   - four increment orders other than j-first         NEW -> flat or +2
 *
 * TU CONTEXT AND RETURN TYPE (measured NEW): appending the TU's other two
 * functions (func_15173C60, func_15173C90) and declaring this one `s32` instead
 * of `void` leaves the object BIT-IDENTICAL.  The isolated file below is
 * therefore a faithful search vehicle.  Note the real TU declares
 * `extern s32 func_151739B0(...)` after the pragma and func_15173C60 does
 * `return func_151739B0(...)`, so the shipped definition must be spelled `s32`
 * with bare `return;` -- that costs nothing.
 *
 * HEADER BUGS -- STILL NOT FIXED.  variables.h types are wrong for six of these
 * symbols and they are used by game_138520.c, game_305D0.c and game_3FC60.c, so
 * this file declares its own _p-suffixed externs for the search.  Relocation
 * fields are masked by fastscore so the names do not affect the score, but
 * THIS FILE IS NOT SHIPPABLE AS-IS.  Correct types:
 *     D_800B0DF0  pointer to a struct with a u8 at 0x21   (ok already)
 *     D_800B0E34  is `u8 *`      -- header says u8[]   (golden does lw)
 *     D_800B0E30  is `Group **`  -- header says s32[]  (golden does lw)
 *     D_800B0E10  is `Vtx *`     -- not declared at all
 *     D_800BE510  is `u8 *`      -- not declared at all
 *     D_800BE520  is `u8 ***`    -- not declared at all
 *     D_800BE524  is `u16 *`     -- not declared at all
 * Group is {u8 *unk0; u16 *unk4; s32 unk8;} (stride 0xC).  D_800DBEF4 is a
 * POINTER and struct131 is 0xA0 (golden's stride is arg4*160).  The vtx write
 * offsets 0xC/0xD/0xE are Vtx_t.cn[0..2] (16-byte stride).
 *
 * PERMUTER: `permuter_tu.sh selftest` PASSES EVERY CHECK on game_1A0E60
 *   (a) PASS, (b) PASS, (b2) PASS, (c) base score, (d) PASS,
 *   (e) isolation DIFFERS -> the TU harness is load-bearing.
 *   Run gated:  PERMUTER_TU_REQUIRE_FRAME=64 PERMUTER_TU_REQUIRE_OFFSETS=1
 *   ~4000 iterations from the 113-row base produced one "win" (2335 -> 1715 on
 *   asm-differ's scale) that was REJECTED: it wrote `k = idx * 3;` inside the
 *   arg1!=0 ref arm, clobbering the running channel offset that the OTHER arm
 *   and the trailing `k += 3` read back.  The value read back is not the value
 *   written -- that is a semantic change, not a forcer.
 *   Note also that asm-differ's --stack-diffs score and fastscore DISAGREE in
 *   direction here (the 71-row source scores 2360 vs the 113-row source's 2335).
 *   fastscore is the authority: 71 vs 113 differing words at equal length.
 *
 * Pass this file straight to fastscore; it needs no hand edits:
 *   python3 tools/fastscore.py game_1A0E60 func_151739B0 tools/nearmiss/func_151739B0.c
 */
#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    u8  pad0[0x21];
    u8  unk21;
} Owner_1A0E60;

typedef struct {
    u8  *unk0;
    u16 *unk4;
    s32  unk8;
} Group_1A0E60;

typedef struct {
    u8  pad0[0xC];
    u8  cn[4];
} Vtx_1A0E60;

typedef struct {
    u8         pad0[0x20];
    Vtx_1A0E60 *unk20[0x20];
} Ent_1A0E60;

extern Owner_1A0E60 *D_800B0DF0_p;
extern u8           *D_800B0E34_p;
extern Group_1A0E60 **D_800B0E30_p;
extern Vtx_1A0E60   *D_800B0E10_p;
extern Ent_1A0E60   *D_800DBEF4_p;
extern u8           *D_800BE510_p;
extern u8         ***D_800BE520_p;
extern u16          *D_800BE524_p;
extern u8            D_800BE9C0_p;

void func_151739B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Vtx_1A0E60 *vtx;
    s32 i;
    s32 start;
    s32 end;

    {
        s32 cnt = D_800B0E34_p[arg0];

        if (cnt == 0) {
            return;
        }
        if ((D_800B0DF0_p->unk21 & 4) == 0) {
            if ((arg1 == 0) && ((D_800B0DF0_p->unk21 & 1) == 0)) {
                return;
            }
            if ((arg1 == 1) && ((D_800B0DF0_p->unk21 & 2) == 0)) {
                return;
            }
        }
        if (arg3 == 0xFF) {
            start = 0;
            end = cnt;
        } else {
            if (arg3 >= cnt) {
                return;
            }
            start = arg3;
            end = arg3 + 1;
        }
    }
    if (arg1 == 0) {
        vtx = D_800B0E10_p;
    } else {
        vtx = D_800DBEF4_p[arg4].unk20[D_800BE9C0_p];
    }
    {
        Group_1A0E60 *grp = D_800B0E30_p[arg0];

        for (i = start; i < end; i++) {
            s32 j = 0;
            u16 *idxp = grp[i].unk4;
            s32 k = 0;
            u8 *src = grp[i].unk0;

            while (j < grp[i].unk8) {
                s32 idx = *idxp;
                u8 *ref;

                if ((D_800B0DF0_p->unk21 & 4) == 0) {
                    if (arg1 == 0) {
                        ref = &D_800BE510_p[idx * 3];
                    } else {
                        ref = &D_800BE510_p[D_800BE524_p[arg4] * 3] + idx * 3;
                    }
                } else {
                    ref = &D_800BE520_p[arg0][i][k];
                }
                vtx[idx].cn[0] = (((src[0] - ref[0]) * arg2) >> 8) + ref[0];
                vtx[idx].cn[1] = (((src[1] - ref[1]) * arg2) >> 8) + ref[1];
                vtx[idx].cn[2] = (((src[2] - ref[2]) * arg2) >> 8) + ref[2];
                j++;
                idxp++;
                src += 3;
                k += 3;
            }
        }
    }
}
