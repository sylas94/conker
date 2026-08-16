/* func_150C16C0  (game_EEB10, 696 bytes)  --  BLOCKED ON A RODATA MIGRATION, NOT ON C.
 *
 * STATUS: this C scores 0 (asm-differ -o, max 18900) and the .rodata it emits is
 * BYTE-IDENTICAL to the golden pool.  It cannot ship because game_EEB10's float pool
 * is not assigned to the TU in conker.us.yaml, so conker.ld sends the object's live
 * .rodata to /DISCARD/ and the five %hi/%lo relocations resolve to nothing.
 *
 * THE UNLOCK -- one line, exactly the shape the yaml already documents elsewhere:
 *     conker/conker.us.yaml:1261
 *         -      - [0x244CB0, rodata]
 *         +      - [0x244CB0, .rodata, game_EEB10]   # float pool for func_150C16C0
 *     then regenerate conker.ld (splat --modes ld; conker.ld is gitignored/generated).
 * The wave-brief forbade touching conker.us.yaml ("none of your targets needs a
 * migration"), so it was left unapplied.  Everything else is done and verified.
 *
 * EVIDENCE THE MIGRATION IS EXACT
 *   golden asm/data/244CB0.rodata.s (0x20 bytes):
 *       418b3333 41a1999a 41c5999a 3e4ccccd 3ecccccd 00000000 00000000 00000000
 *   readelf/objdump of build/src/game_EEB10.c.o built from the C below:
 *       .rodata  PROGBITS  size 0x000020  align 16
 *       0000 418b3333 41a1999a 41c5999a 3e4ccccd
 *       0010 3ecccccd 00000000 00000000 00000000
 *   -- identical, trailing zero padding included (IDO's 16-byte .rodata alignment
 *   reproduces splat's padding for free, same as the jtbl case).
 *
 * WHY THE `extern f32` ESCAPE DOES NOT WORK HERE (this is the transferable finding)
 *   The usual workaround -- declare the pool entries as `extern f32 D_800A01F0;` and
 *   read them -- produces IDENTICAL SEMANTICS but a DIFFERENT LOOP-INVARIANT RANKING:
 *
 *     literals  : IDO hoists the loop-invariant *value*  17.4f into $f30, and the two
 *                 loop-invariant *addresses* it hoists into GPRs are &sp108 -> $s7 and
 *                 &spE8 -> $s8.  == golden.
 *     externs   : the extern's ADDRESS becomes a hoistable address node and outranks the
 *                 stack addresses.  IDO hoists %hi/%lo(D_800A01F0) -> $s6 and
 *                 %hi/%lo(D_800A01F4) -> $s8 instead, spills 25.5f into $f30, and emits
 *                 `addiu a0,sp,0x108` / `addiu a1,sp,0xe8` inline at the call.
 *
 *   Same 2 GPRs + 1 FPR hoisting budget either way, different winners.  Best honest
 *   extern score: 1575.  Best literal score: 0.  No spelling escapes it -- it is a
 *   property of which node kinds the hoister ranks, so this is a genuine migration
 *   blocker and NOT a bail signature.
 *   NOTE for the backlog: game_EBD00/func_150BE850 used the same extern escape for
 *   D_800A00B0/B4 and closed at 0 -- the escape only fails when a LOOP forces the
 *   hoister to rank address nodes against stack-address nodes.
 *
 * MODEL NOTES (all confirmed by moving the score)
 *   - Structural template is the matched sibling func_15151A38 in game_17CAF0.c; the
 *     three stack structs are the same 0x20-byte spawn/part/style triple as
 *     func_150BD954 (game_E8C10.c) and func_15148F1C (game_175250.c), with the same
 *     style-block constants (0,1,0x160600,3,0x10,0x80,0x20,0,9).
 *   - `% 13U` / `% 9U` with plain literals DO reproduce golden's
 *     `divu zero,v0,$s5` + `bnez $s5 / break 7`: IDO hoists the divisor constant into a
 *     callee-saved register out of the loop and keeps the div-by-zero trap.  (A literal
 *     divisor only loses the trap when the modulo is NOT in a loop -- cf. game_E7970
 *     func_150BA4C0, which gets `addiu $at,$zero,9` and no break.)
 *   - The trip-1 loop is a genuine bottom-tested countdown: `i = 1; do {...} i--; }
 *     while (i != 0);`  A `for (i = 0; i < 1; i++)` gives increment+compare (score +445).
 *   - `i = 1;` must sit BEFORE the struct field stores, not next to the `do` -- that is
 *     the difference between `li s1,1` landing at 0x110 (golden) and 0x144.  Worth 60.
 *   - There is NO named `temp_f0` local for `mag * spA` (unlike func_15151A38): golden's
 *     scalar local region is 0x28 bytes, one 8-byte slot short of what 8 named scalars
 *     cost.  Writing `(mag * spA)` twice and letting IDO CSE it took the frame from
 *     0x130 to golden's 0x128.  Worth 265.
 *
 * REPRODUCE:  paste the body below over the #pragma in conker/src/game_EEB10.c, then
 *   tools/buildlock.sh bash -c 'make -s VERSION=us NON_MATCHING=1 PERMUTER=1 \
 *       build/src/game_EEB10.c.o && python3 ../tools/asm-differ/diff.py -o \
 *       -f build/src/game_EEB10.c.o --format json func_150C16C0'
 * Without the yaml line the diff shows score 0 with ten rows whose only delta is
 * `%hi(.rodata)` where golden has `%hi(D_800A01F0..0200)`.
 */

#include <ultra64.h>
#include "functions.h"
#include "variables.h"

s32 func_15147DA0(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
                  s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10, s32 *arg11,
                  s32 arg12, u8 arg13, s32 arg14);

s32 func_150C16C0(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5,
                  s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10, s32 arg11,
                  s32 arg12, s32 arg13, u8 arg14) {
    struct { f32 x; f32 y; f32 z; s16 unk0C; s16 unk0E; s32 unk10; u8 pad14; u8 unk15; s32 pad18; s32 pad1C; } sp108;
    struct { f32 unk00; f32 unk04; f32 unk08; f32 unk0C; f32 unk10; u8 pad14[4]; u8 unk18; u8 unk19; u8 unk1A; u8 unk1B; s32 pad1C; } spE8;
    struct { s32 unk00; s32 unk04; s32 unk08; s32 unk0C; s32 unk10; s32 unk14; s32 unk18; u8 unk1C; u8 unk1D; } spC8;
    s32 i;
    s16 ang;
    f32 mag;
    f32 spA;
    f32 spB;
    f32 spC;
    f32 spD;

    i = 1;
    spC8.unk00 = 0;
    spC8.unk04 = 1;
    spC8.unk08 = 0x160600;
    spC8.unk0C = 3;
    spC8.unk10 = 0x10;
    spC8.unk14 = 0x80;
    spC8.unk18 = 0x20;
    spC8.unk1C = 0;
    spC8.unk1D = 9;
    sp108.unk10 = 1;
    sp108.unk0E = 1;
    spE8.unk19 = 0xA;
    spE8.unk1A = 0xFF;
    spE8.unk18 = 0x28;
    spE8.unk1B = 0xFF;
    sp108.x = arg2;
    sp108.y = arg3;
    sp108.z = arg4;

    do {
        ang = (func_150ADA20() % 13U) - 0x3F;
        spA = func_151423D8((u8)ang);
        spB = func_151423D8((u8)(ang - 0x40));
        spC = func_151423D8((u8)arg8);
        spD = func_151423D8((u8)(arg8 - 0x40));
        mag = (func_150ADA68() * 17.4f) + 25.5f;
        sp108.unk15 = (func_150ADA20() % 9U) + 5;
        sp108.unk0C = (func_150ADA20() & 0x3F) + 0x5A;
        spE8.unk00 = (func_150ADA68() * 20.2f) + 24.7f;
        spE8.unk10 = (func_150ADA68() * 0.2f) + 0.4f;
        spE8.unk04 = (mag * spA) * spD;
        spE8.unk08 = -mag * spB;
        spE8.unk0C = (mag * spA) * spC;
        func_15147DA0(&sp108, &spE8, 0, 1, 5, 0, 0, 0, 0, 0, 0, (s32 *)&spC8, 0, arg14, 0);
        i--;
    } while (i != 0);
    return 1;
}
