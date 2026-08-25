/* tools/nearmiss/guMtxXFMF.c -- game_21D5F0, a NAMED libultra gu function
 *
 * FILE KIND: STANDALONE TU (game_21D5F0 holds guMtxXFMF + guMtxCatF and nothing else).
 *
 * *** THE SIBLING SHIPPED 2026-08-24. *** guMtxCatF (92 words) is byte-perfect and ROM-gated:
 *      triple loop (i,j,k) with `temp[i][j] = 0.0f;` then `temp[i][j] += m[i][k]*n[k][j];`
 *      followed by a SEPARATE nested copy loop back into r (NOT guMtxCopyF -- golden has no call).
 * NOTE THIS IS *NOT* THE PUBLISHED SDK SPELLING. The SDK's xfmf.c writes the flat four-term
 * expression and then calls guMtxCopyF; that form scores 91 here. The zero-init-and-accumulate
 * form scores 0. Same lesson as the private-libultra TUs: the game's copy is not the book's.
 * It required `OPT_FLAGS := -O2` (Makefile line 164) -- 0 at -O2, 3 at the tree default.
 *
 * STATUS 2026-08-24: guMtxXFMF stuck at mism=49, n=41/40 at -O2. ONE instruction too many.
 *
 * *** THE FLAG IS NOW PINNED AND CANNOT MOVE. *** guMtxCatF matches ONLY at plain -O2:
 *      -O2 => 0    -O2 -g3 => 3    -O1 => 236    -g => 236    -O0 => 164
 * so any fix for guMtxXFMF must work AT -O2. -O1 (the private-libultra law) is not available
 * here; measured, not assumed: XFMF is 130 at -O1, worse than its 49 at -O2. These gu functions
 * are therefore NOT part of the -O1 private-libultra group even though they live at 0x151Fxxxx.
 *
 * *** SPELLING IS REFUTED AS A LEVER -- ALL FOUR SHAPES TIE AT EXACTLY 49 / n=41/40 AT -O2. ***
 *      trans-first matrix*scalar 49 | trans-first scalar*matrix 49
 *      SDK exact (trans last)    49 | locals-then-store          49
 * They differ at -O2 -g3 (58/59/58/70), which is what made spelling LOOK like a lever earlier.
 * At the flag that actually matters they are indistinguishable. Do not re-sweep expression
 * shape; it has been swept and it is flat.
 *
 * THE SIGNATURE IS FIXED BY THE HEADER, not guessed. gu.h line 167 already declares
 *      void guMtxXFMF(f32 m[4][4], f32 x, f32 y, f32 z, f32 *ox, f32 *oy, f32 *oz)
 * and any variation (e.g. flat `f32 *m` with manual indices) is a hard CCFAIL on
 * "redeclaration of 'guMtxXFMF'". So parameter-shape variants are not available either.
 *
 * *** THE WHOLE RESIDUE IS ONE SPILLED FLOAT PARAMETER. ***
 * Golden homes all three incoming floats with three register-to-register moves, interleaved
 * with the matrix loads so each latency is hidden:
 *      mtc1 $a1,$f12 / lwc1 $f4,0x0($a0) / mtc1 $a2,$f14 / lwc1 $f8,0x10($a0) / mtc1 $a3,$f16
 * We home only two, and route the third through its ARGUMENT HOME SLOT on the stack:
 *      sw $a2,0x8($sp)  ;  lwc1 $f6,0x8($sp)        <- this pair is the 41st word
 * and we bind the other two to the wrong registers (x -> $f14, z -> $f12; golden x -> $f12).
 * IDO here will use $f12 and $f14 to home float parameters but WILL NOT reach for $f16;
 * golden's compiler did. Everything else follows from that one decision:
 *   - our first product is m[1][0]*y where golden's is m[0][0]*x (we start with the spilled one)
 *   - both of our add.s operand pairs come out COMMUTED relative to golden
 *     (we emit `C + (A+B)` then `sum + m[3][0]`; golden emits `(A+B) + C` then `m[3][0] + sum`)
 * The commuted adds are a SYMPTOM, not a separate bug -- do not chase them independently.
 *
 * NEXT LEVER, AND IT IS THE ONLY ONE LEFT: this is a pure register-allocation residue with a
 * flat source-level search space, which is precisely decomp-permuter's job. Note the two prior
 * permuter runs that failed this session were on the DELAY-SLOT DUPLICATION family, a different
 * shape (permuter cannot invent an instruction). Here the instruction count is one too MANY and
 * the fix is an allocation choice, which permuter can actually reach. Use conker/permuter_tu.sh
 * with PERMUTER_TU_REQUIRE_FRAME (frame is leaf, so require offsets too).
 *
 * DO NOT force this. There is no legitimate C that says "put z in $f16"; anything that appears
 * to (inline asm, a dummy float local sized to shove the allocator) is a forcer and fails the
 * load-bearing test. If the permuter cannot find it, the honest read is that the SDK's gu
 * library was compiled by a different IDO build than the game's own TUs, and this one BAILS.
 */
#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void guMtxXFMF(f32 m[4][4], f32 x, f32 y, f32 z, f32 *ox, f32 *oy, f32 *oz) {
    *ox = m[3][0] + (m[0][0]*x + m[1][0]*y + m[2][0]*z);
    *oy = m[3][1] + (m[0][1]*x + m[1][1]*y + m[2][1]*z);
    *oz = m[3][2] + (m[0][2]*x + m[1][2]*y + m[2][2]*z);
}
