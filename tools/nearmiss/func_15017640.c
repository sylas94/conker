/*
 * PARKED NEAR-MISS -- func_15017640  (game_44A90.c, 336 B, 84 words, frame 0x28)
 * Only pragma left in game_44A90.c; closing it retires the TU.
 *
 * BEST: fastscore mism=57 n=82/84 (pointer `for` loop, explicit 2460 stores)
 *       and     mism=60 n=84/84 (same but the 2460 stores written as a loop).
 *   Measure with: python3 tools/fastscore.py game_44A90 func_15017640 <cand.c>
 *
 * ------------------------------------------------------------------ SOLVED, keep these
 *   - float pool: 50.0f / 60.6f / 53.0f / 1.0f.  0x42726666 round-trips from "60.6"
 *     exactly (checked); D_800968B0 is the `far` argument, loaded with lwc1.
 *     guPerspective((Mtx *)&D_800D23D0, (u16 *)&D_800D2454, 50.0f, 60.6f, 53.0f,
 *                   D_800968B0, 1.0f)
 *   - the four byte stores are D_800D2460[2..5][13] = 0 (base+0x2D/0x3D/0x4D/0x5D).
 *     Golden's EMISSION order is [3],[4],[5],[2] but that is scheduling.
 *   - D_800D2428[i] = D_8009DCB4[i] is s16 -> f32 (lh + cvt.s.w), i = 0..2.
 *
 * -------------------------------------------------- RESIDUAL 1: the 1.0f loop is a LOOP
 * Golden:                                mine (`for (i=0;i<6;i++) D_800D2410[i]=1.0f;`):
 *   ---                                    (fully unrolled: six `swc1 f0,N(at)`)
 *   addiu v0,v0,4
 *   sltu  at,v0,v1        ; v1 = %hi/%lo(D_800D2428) == &D_800D2410[6]
 *   bnez  at,loop
 *    swc1 f0,-4(v0)
 * Golden has NO zero-trip guard, so IDO knew the trip count was a constant 6 -- yet it
 * did NOT fully unroll.  Every index-based spelling (for / while / do-while, complete
 * `extern f32 D_800D2410[6];`) unrolls to six stores.  A POINTER loop
 *     for (p = D_800D2410; p < D_800D2428; p++) *p = 1.0f;
 * reproduces the loop body exactly but adds a 2-instruction zero-trip guard
 * (`sltu at,v1,t9; bnez at,+7`) because IDO cannot compare two distinct symbols; the
 * do-while pointer form drops the guard and matches the body word-for-word.
 * So: golden = "constant trip count, guard elided" + "not unrolled" simultaneously,
 * which no spelling tried reproduces at once.
 *
 * --------------------------------------- RESIDUAL 2: the D_800D2460 base is COMPUTED
 * Golden materialises &D_800D2460 into t0 in the early address block and then does
 *     addiu v1,zero,2 ; sll t9,v1,4 ; addu v0,t9,t0 ; sb zero,0x1D(v0) ...
 * -- three instructions to form a compile-time-constant offset of 32.  That is IDO's
 * UNROLLER address form (base + IV*stride with the induction variable's start value
 * left in a register), not the constant folder's.  Everything tried folds instead:
 *   `for (i=2;i<6;i++)` / `while` / `do-while` / `i!=6`  -> four `lui at; sb zero,%lo`
 *   `i = 2; D_800D2460[i+1][13]=0; ...`                  -> IDO const-props i
 *   explicit constant subscripts                         -> one shared lui+addiu base
 *
 * REOPEN WITH: a model of when IDO's loop unroller (rather than its constant folder)
 * expands a 4..6-iteration constant-count loop.  Both residuals are the same question
 * asked twice -- one loop golden did NOT unroll, one loop golden DID unroll but through
 * the unroller's register-IV path.  Cracking that closes this function outright; the
 * rest of the 84 instructions already agree.
 */

#include <ultra64.h>

#include "functions.h"
#include "variables.h"

void func_15017640(void) {
    f32 *p;

    D_800D2458 = 0;
    D_800D2588 = 0;

    D_800D2438[0] = 0.0f;
    D_800D2438[1] = 0.0f;
    D_800D2438[2] = 0.0f;

    D_800D2428[0] = D_8009DCB4[0];
    D_800D2428[1] = D_8009DCB4[1];
    D_800D2428[2] = D_8009DCB4[2];

    D_800D2444 = 0;
    D_800D245C = NULL;

    for (p = D_800D2410; p < D_800D2428; p++) {
        *p = 1.0f;
    }

    D_800D246D = 0;
    D_800D247D = 0;

    D_800D2460[3][13] = 0;
    D_800D2460[4][13] = 0;
    D_800D2460[5][13] = 0;
    D_800D2460[2][13] = 0;

    D_800D24C0 = 0;
    bzero(&D_800D24C8, 0xC0);
    guPerspective((Mtx *)&D_800D23D0, (u16 *)&D_800D2454, 50.0f, 60.6f, 53.0f, D_800968B0, 1.0f);
}
