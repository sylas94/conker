/* =====================================================================================
 * game_2DDF0 / func_15000940   (384 B, 96 instructions)   PARKED 2026-08-16
 *
 * BEST SCORE: 136  (fastscore, n = 100/96, frame -0x30 vs golden -0x28)
 *              first reconstruction 106 (n=98) but with the WRONG multiply form; see below --
 *              136 is the better parked result because its instruction SHAPE is right.
 *
 * WHAT THE FUNCTION IS -- fully decoded, no unknowns left in the logic:
 *   A 4 x 3 table initialiser.  It reads a config index out of the global struct104,
 *   walks three 3-byte source records, and broadcasts them into five 4x3 destination
 *   tables (plus one 3-byte table that is rewritten identically on every outer pass).
 *
 *      rec  = D_800A2CD0[D_800B0DF0->unk29];   // u8 [][3]
 *      srcA = D_800A2CE8[rec[0]];              // u8 [][3]
 *      srcB = D_800A2CEC[rec[1]];              // u8 [][3]   (= D_800A2CE8 + 4)
 *      srcC = D_800A2D04[rec[2]];              // u8 [][3]   (= D_800A2CE8 + 0x1C)
 *      for (i = 0; i < 4; i++)                 // bound is &D_800D9EC4 (= D_800D9EB8 + 12)
 *          for (j = 0; j < 3; j++) {           // bound is &D_800D9EB7 (= D_800D9EB4 + 3)
 *              D_800D9E70[i][j] = 0;           // u16 [4][3]
 *              D_800D9EB8[i][j] = 0;           // u8  [4][3]
 *              D_800D9EB4[j]    = srcC[j];     // u8  [3]     <- no outer stride, re-based
 *              D_800D9EA8[i][j] = srcC[j];     // u8  [4][3]
 *              D_800D9E88[i][j] = srcA[j];     // u8  [4][3]
 *              D_800D9E98[i][j] = srcB[j];     // u8  [4][3]
 *          }
 *   The `[][3]` shapes were already guessed (commented out) at variables.h:1185-1194; this
 *   run confirms every one of them, plus D_800D9EB4 is [3] not [][3], and struct104.unk29 is
 *   the index.  `sw a0,0x28(sp)` in golden's prologue = the unused s32 parameter homed, so
 *   the signature really is `void func_15000940(s32 arg0)`.
 *
 * TWO THINGS THAT WERE ALREADY UNLOCKED AND ARE WORTH KEEPING
 *   1. THE INNER BODY IS EXACT.  Load srcC, srcA, srcB into three u8 locals FIRST, then do
 *      the six stores.  Written without the locals, `srcC[j]` is loaded TWICE (a u8 store may
 *      alias a u8 source, so IDO will not CSE across the stores) and the whole body
 *      re-schedules.  With them, golden's exact 18-instruction body comes out:
 *      3 lbu, 9 pointer increments, 6 stores at -1/-2 offsets, store in the branch delay slot.
 *   2. THE MULTIPLY-BY-3 FORM IS THE COOKBOOK'S "STRENGTH REDUCTION FIRES ON A LOCAL" LAW
 *      (ido_cookbook.md, the actor-array unlock, ~line 2560), and this function is a second,
 *      independent confirmation of it -- WITH A NEW WRINKLE:
 *          index straight out of memory      `D_800A2CE8[rec[0]]`   -> li 3 + multu + mflo
 *          index hoisted into an s32 local   `i1 = rec[0]; ...[i1]` -> sll 2 ; subu  (golden)
 *      NEW: the failure mode is not "no strength reduction", it is that IDO PROMOTES THE
 *      LITERAL 3 INTO A REGISTER as soon as TWO OR MORE such multiplies exist in the function
 *      (`li a3,3` hoisted to the top), and a register multiplier can no longer be reduced.
 *      Measured with 1/2/3/4 multiplies: 1 -> CSD, 2+ -> multu for ALL of them.  So this is
 *      an all-or-nothing property of the whole function, not of one expression.
 *      Also measured and REFUTED as fixes: `3 * x`, `x * 3U`, casts to s32/s16, a real
 *      3-byte struct, `u8 (*)[3]` row pointers, flat arrays with `[i*3]`, pointer arithmetic,
 *      `k *= 3` on a reused local (reusing ONE local for all four indices puts multu back!),
 *      `(x<<2)-x` (gives sll + negu + addu, not subu), `(x*4)-x` (same), and -O1/-O3/-g/-g1/
 *      -g2/-Wab,-r4300_mul on/off (-O1 DOES give the CSD but then loses the -O2 loop
 *      strength reduction: 108 instructions).  FOUR SEPARATE s32 index locals is the only
 *      thing that produced golden's four CSD triples at -O2 -g3.
 *
 * THE RESIDUAL, exactly
 *   4 instructions and a frame 8 bytes too big: golden saves s0-s7 (frame 0x28), we save
 *   s0-s7 PLUS s8 and ra (frame 0x30) -- `sw ra` / `sw s8` / `lw ra` / `lw s8`.  We are two
 *   integer registers short.  Everything else is the same instruction multiset with a global
 *   rename, which is what inflates 4 real instructions into a score of 136.
 *   The two extra live values come from the prologue: the four index locals i0..i3 keep
 *   rec[0..2] alive across the address computations, whereas golden consumes each one
 *   immediately (it loads rec[0], rec[1], computes srcA, THEN loads rec[2], computes srcB and
 *   srcC).  Also note golden re-materialises `&D_800D9EB4` with a lui+addiu INSIDE the outer
 *   loop rather than keeping it in a register -- a register-pressure symptom, not a cause.
 *   Interleaving the assignments, using u8 locals, using 2 or 3 locals instead of 4, and
 *   loading all three up front were all tried: every one is 136 with frame -0x30.  That is a
 *   ranking tie; the lever has to be something that shortens a live range in the prologue.
 *
 * NEXT MOVE: get IDO to consume rec[0..2] one at a time while STILL seeing locals (the two
 *   requirements currently fight each other).  If that frees s8/ra the score should collapse,
 *   since the loop nest is already byte-exact in shape.
 * ===================================================================================== */

#include <ultra64.h>

#include "functions.h"
#include "variables.h"

/* These six are already present, commented out, at variables.h:1185-1194 -- this run
 * confirms the shapes (except D_800D9EB4, which is [3], not [][3]). */
extern u16 D_800D9E70[][3];
extern u8 D_800D9E88[][3];
extern u8 D_800D9E98[][3];
extern u8 D_800D9EA8[][3];
extern u8 D_800D9EB4[3];
extern u8 D_800D9EB8[][3];
extern u8 D_800A2CE8[][3];
extern u8 D_800A2CEC[][3];
extern u8 D_800A2D04[][3];

void func_15000940(s32 arg0) {
    u8 *rec;
    u8 *srcA;
    u8 *srcB;
    u8 *srcC;
    s32 i0;
    s32 i1;
    s32 i2;
    s32 i3;
    u8 a;
    u8 b;
    u8 c;
    s32 i;
    s32 j;

    i0 = D_800B0DF0->unk29;
    rec = D_800A2CD0[i0];
    i1 = rec[0];
    i2 = rec[1];
    i3 = rec[2];
    srcA = D_800A2CE8[i1];
    srcB = D_800A2CEC[i2];
    srcC = D_800A2D04[i3];

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            c = srcC[j];
            a = srcA[j];
            b = srcB[j];
            D_800D9E70[i][j] = 0;
            D_800D9EB8[i][j] = 0;
            D_800D9EB4[j] = c;
            D_800D9EA8[i][j] = c;
            D_800D9E88[i][j] = a;
            D_800D9E98[i][j] = b;
        }
    }
}
