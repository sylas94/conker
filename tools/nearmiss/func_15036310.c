/* tools/nearmiss/func_15036310.c  --  game_637C0   ***  SOLVED / MATCHED  ***
 *
 * STATUS: CLOSED.  This source is LIVE in conker/src/game_637C0.c and is a
 *         byte-perfect match.  This file is kept only as the record of how it
 *         was closed; it is a COMPLETE TU and still re-scores in one command:
 *
 *           python3 tools/fastscore.py game_637C0 func_15036310 tools/nearmiss/func_15036310.c
 *
 *         -> mism=30, n=149/152, ZERO mismatch rows.
 *            The golden .s lists 152 words but only 149 are real; the three
 *            trailing pad nops after the delay slot cost 10 each, so 30 IS the
 *            perfect score for this function.  Read it as "0 real mismatches".
 *
 * VERIFIED (2026-08-20):
 *   tools/verify_match.sh game_637C0 func_15036310  -> ALL CHECKS RAN AND PASSED
 *       (score 0 with -R and without -R; .text IDENTICAL, 40 dump lines;
 *        .text section size 0x000260 both sides)
 *   tools/relcheck.py conker/build/src/game_637C0.c.o func_15036310 -> PASS
 *       (152/152 instructions, 147 unrelocated words equal, 5 relocated fields
 *        composed against the ROM, 0 unpaired HI16)
 *   full ROM: make VERSION=us -> "build/conker.us.bin: OK" (sha1 gate passed)
 *
 * ============================  HOW IT WAS CLOSED  ==========================
 * The inherited near-miss scored 40 raw / 10 real and was described as "one FP
 * register rotation, plain reordering exhausted".  It was not a rotation.  It
 * was THREE independent source facts, each worth a measured number of rows:
 *
 *  1. THE SWAP IS WRITTEN THE OTHER WAY ROUND  (4 rows).
 *        golden : temp = d[0];  d[0] = d[2];  d[2] = -temp;
 *        old    : temp = d[2];  d[2] = -d[0]; d[0] = temp;
 *     These are SEMANTICALLY IDENTICAL -- both map (x,z) -> (z,-x) -- but they
 *     differ in which element is loaded FIRST, and IDO hands the first-created
 *     value $f0 and the second $f16.  Golden pre-loads d[0] into $f0 before the
 *     branch, so the golden source must read d[0] first.  Fixes idx35/43/44/46.
 *     Load-bearing: restoring the old spelling re-costs exactly those 4 rows.
 *
 *  2. d[1] IS CACHED IN THE SCRATCH `temp`  (2 rows).
 *     Found by decomp-permuter (output-60-1, 652 iterations).  `temp = sp50[1];`
 *     before the cross products.  This is an honest CSE, not a forcer: sp50[1]
 *     is never written after the swap, so the value read back IS the value
 *     written.  Load-bearing: deleting it re-costs idx64/idx79.
 *     Its POSITION is a ranking tie (before or after the sp68 constant stores:
 *     both 30).  A permuter variant that instead computed b1*b1 was rejected.
 *
 *  3. FOUR mul.s OPERANDS ARE SPELLED THE OTHER WAY ROUND  (4 rows).
 *     The four right-hand terms of the six cross-product subtractions whose
 *     second factor is an ARRAY ELEMENT (d[0] or d[2]) are written with that
 *     element FIRST:  `(sp50[2] * sp68[1])`, not `(sp68[1] * sp50[2])`.
 *     Reason: for `a * b`, IDO emits the operand that is a memory LOAD as `fs`.
 *     Where the second factor is the register-resident local `temp` there is no
 *     load, so those two multiplies keep source order and must NOT be flipped.
 *     Multiplication is commutative, so this changes nothing semantically.
 *
 * MEASURED LADDER:  40 (inherited) -> 38 (permuter CSE) -> 36 (swap alone,
 * without CSE) -> 34 (swap + CSE) -> 30 = MATCH (swap + CSE + the four flips).
 *
 * ============================  DO NOT UNDO  ================================
 *   - The `{0,1,0}` up vector is the OUTPUT array sp68 reused as scratch.  IDO
 *     store-to-load-forwards the constants into mtc1 registers, deletes the
 *     dead stores, and does NOT fold the six multiplies.  Every other honest
 *     spelling of the up vector measured 136-245 (see git history of this file).
 *   - The unused `s32 arg0` parameter is correct: IDO emits the home-slot store
 *     `sw a0, 0x78(sp)` for a never-read first parameter.
 *   - Caching d[0]/d[2] in extra locals (the "obvious" version of fact 3) is
 *     WRONG: three or four f32 locals push the frame to 0x80/0x88 and score
 *     94-141.  The flip is what is honest AND free.
 */
#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_150440A0(f32 arg0[4][4], f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9);

void func_15036310(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    f32 (*mtx)[4];
    f32 sp68[3];
    f32 sp5C[3];
    f32 sp50[3];
    f32 sp44[3];

    struct127 *obj;
    f32 temp;

    obj = &D_800CC2D0[arg1];
    if (obj->unk1D4 != NULL) {
        mtx = (f32 (*)[4])((u8 *)obj->unk1D4 + (arg2 << 6));
        sp5C[0] = mtx[3][0];
        sp5C[1] = mtx[3][1];
        sp5C[2] = mtx[3][2];
        sp50[0] = D_800DBFF0->unk2F8 - sp5C[0];
        sp50[1] = D_800DBFF0->unk2FC - sp5C[1];
        sp50[2] = D_800DBFF0->unk300 - sp5C[2];
        if (arg3 != 0) {
            temp = sp50[0];
            sp50[0] = sp50[2];
            sp50[2] = -temp;
        }
        sp68[0] = 0.0f;
        sp68[1] = 1.0f;
        sp68[2] = 0.0f;
        temp = sp50[1];
        sp44[0] = (temp * sp68[2]) - (sp50[2] * sp68[1]);
        sp44[1] = (sp50[2] * sp68[0]) - (sp50[0] * sp68[2]);
        sp44[2] = (sp50[0] * sp68[1]) - (sp68[0] * temp);
        sp68[0] = (temp * sp44[2]) - (sp50[2] * sp44[1]);
        sp68[1] = (sp50[2] * sp44[0]) - (sp50[0] * sp44[2]);
        sp68[2] = (sp50[0] * sp44[1]) - (sp44[0] * temp);

        func_150440A0(mtx, sp5C[0], sp5C[1], sp5C[2],
                      sp5C[0] - sp50[0], sp5C[1] - temp, sp5C[2] - sp50[2],
                      sp68[0], sp68[1], sp68[2]);
        if (obj->xz_scale != 1.0f) {
            mtx[0][0] *= obj->xz_scale;
            mtx[1][0] *= obj->xz_scale;
            mtx[2][0] *= obj->xz_scale;
            mtx[0][2] *= obj->xz_scale;
            mtx[1][2] *= obj->xz_scale;
            mtx[2][2] *= obj->xz_scale;
        }
        if (obj->y_scale != 1.0f) {
            mtx[0][1] *= obj->y_scale;
            mtx[1][1] *= obj->y_scale;
            mtx[2][1] *= obj->y_scale;
        }
    }
}
