/* tools/nearmiss/func_151B6254.c -- the LAST pragma in game_1E34C0.c (closing it zeroes the TU)
 *
 * STATUS 2026-08-24: mism=36, frame=-40 EXACT, n=51/51 EXACT, instructions 0..13 byte-identical.
 * There is no length delta and no frame delta. The entire residue is ONE codegen decision,
 * described at the bottom. This is a strong near-miss, not a structural miss.
 *
 * *** THE SEMANTICS ARE FULLY SOLVED AND CONFIRMED FROM DATA, NOT GUESSED. ***
 * asm/data/24EF10.rodata.s gives the four constants outright:
 *      D_800AA450 = 8.100000381    D_800AA454 = 6.283185482  (== 2*pi)
 *      D_800AA458 = 0.5560000539   D_800AA45C = 0.06100000441
 * D_800AA454 being exactly 2*pi confirms the reading: this is a PHASE ACCUMULATOR that wraps,
 * feeding a sinf oscillation. The body is
 *
 *      f32 *p = &arg0->unk170;
 *      arg0->unk170 += D_800AA458 * D_800BE9A4;          // phase += rate * dt
 *      while (D_800AA454 < arg0->unk170) {               // c.lt.s $f2,$f18  (global on the LEFT)
 *          *p -= D_800AA454;                             // wrap by 2*pi
 *      }
 *      arg0->unk18 = arg0->unk1C = p[1] + sinf(p[0]) * (D_800AA45C * p[1]);
 *      func_15133894(arg0);
 *
 * Store order is 0x1C THEN 0x18, so it must be spelled `unk18 = unk1C = expr` (chained), not two
 * separate statements. unk174 is re-read from memory AFTER the sinf call (golden reloads
 * `lwc1 $f12,0x4($v0)`), so do NOT cache it in a local -- a temp for unk174 costs the frame.
 *
 * *** THE POINTER LOCAL IS LOAD-BEARING AND WAS THE WHOLE FRAME FIX. ***
 * Without `f32 *p`, the frame is -24 and n=43 (mism 114). With it, frame is -40 and n=51, both
 * exact. Golden saves it at 0x18($sp) across the sinf call -- that slot IS the local's -g3 home,
 * and it is the ONLY local: adding any second local (e.g. a float temp) pushes the frame to -48,
 * which is how we know golden has exactly one. arg0 itself is saved to 0x28($sp), its incoming
 * argument home, which sits just outside the frame.
 *
 * *** THE ONE REMAINING DIFFERENCE. ***
 * Golden loads the 2*pi constant ONCE, as a VALUE, before everything:
 *      lui $at,%hi(D_800AA454) ; lwc1 $f2,%lo(D_800AA454)($at)
 * and keeps $f2 live across the whole loop (used by both c.lt.s and both sub.s).
 * We instead hoist its ADDRESS and re-read the value on every iteration:
 *      lui $v1,%hi ; addiu $v1,%lo   then   lwc1 $f0,0($v1)   twice
 * i.e. our IDO will not lift a global f32 load out of a loop that STORES through an `f32 *`,
 * because the store may alias the global; golden's did. Note the instruction COUNTS coincide at
 * 51 either way (our 2 extra reloads vs golden's 2 extra address materialisations), so n=51/51
 * here is NOT evidence of a match -- same length trap as func_10003ACC. Check the dump.
 *
 * *** FOUR THEORIES TESTED AND REFUTED -- DO NOT RE-RUN THESE. ***
 * 1. ALIASING BROKEN BY `const`. `extern const f32` on the constant, or on all three: NO CHANGE,
 *    still 36. IDO 5.3 does not use const-qualification in its alias analysis.
 * 2. ALIASING BROKEN BY TYPE. Storing through a `struct {f32 unk0,unk4;} *` instead of a bare
 *    `f32 *`: NO CHANGE, still 36. IDO 5.3 has no type-based alias analysis; any store through
 *    any pointer invalidates every global.
 *    (1 and 2 were run as a 3x3 grid -- all nine cells tie at exactly 36.)
 * 3. THE CONSTANTS ARE FLOAT LITERALS, NOT GLOBALS. Attractive, because a literal is hoistable
 *    across stores, all four values have low16 != 0 so they MUST go to .rodata, and golden's
 *    rodata order (2*pi at 0x54 BEFORE 0.556 at 0x58) matches the SCHEDULE order rather than
 *    source order -- exactly what a hoisted literal looks like. REFUTED ANYWAY: literals score
 *    59 at n=47/51, four instructions SHORT. IDO hoists them too well. Golden uses the externs.
 *    Corollary: the rodata block does NOT need migrating for this function. That block
 *    (0x24EF10) is one of the rare clean ones -- exactly these four floats, referenced only by
 *    game_1E34C0 -- so migration stays available for some future need, but it is not this need.
 * 4. A FLOAT LOCAL HOLDING THE CONSTANT. Gets the value into a register, but costs a second -g3
 *    stack home: frame -48, n=47. Refuted by the frame, which is exact without it.
 * Loop form is also NOT the lever: while / do-while / condition via *p vs via arg0->unk170 all
 * land on the same 36.
 *
 * *** NEXT: THIS IS THE THIRD KNOWN MEMBER OF A FAMILY. DO NOT ATTACK IT ALONE. ***
 * A pure loop-invariant-code-motion ranking difference on a global load, at exact frame and
 * exact length, is the same residue already parked on:
 *      func_100049E0 -- "loses a loop-invariant ranking tie"  (conker.us.yaml note @ 0x2C0A0)
 *      func_15007B3C -- "the residual is a constant-hoist ranking tie" (yaml note @ 0x23A510)
 *      func_151B6254 -- this file
 * All three are otherwise structurally exact. The refutation grid above (const, struct-typed
 * store, float literals, float local) is the shared search space, so it does NOT need re-running
 * per member. A mechanism that explains one explains all three, and that is a SYSTEMIC unlock --
 * the category that actually closes functions here, unlike one-off spelling sweeps. Two of the
 * three also carry a ready rodata migration, so the payoff is larger than three functions.
 *
 * DO NOT force it. `volatile`, a dummy read, or hand-hoisting the constant into a local all
 * change either the semantics or the frame, and all fail the load-bearing test.
 */
#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_800AA454;
extern f32 D_800AA458;
extern f32 D_800AA45C;
extern f32 D_800BE9A4;
extern void func_15133894(void *);

typedef struct {
    /* 0x000 */ u8  pad0[0x18];
    /* 0x018 */ f32 unk18;
    /* 0x01C */ f32 unk1C;
    /* 0x020 */ u8  pad20[0x150];
    /* 0x170 */ f32 unk170;
    /* 0x174 */ f32 unk174;
} S151B6254;

void func_151B6254(S151B6254 *arg0) {
    f32 *p = &arg0->unk170;

    arg0->unk170 += D_800AA458 * D_800BE9A4;
    while (D_800AA454 < arg0->unk170) {
        *p -= D_800AA454;
    }
    arg0->unk18 = arg0->unk1C = p[1] + sinf(p[0]) * (D_800AA45C * p[1]);
    func_15133894(arg0);
}
