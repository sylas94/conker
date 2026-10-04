/* tools/nearmiss/func_150413FC.c -- game_6E770, 33 instructions, frame -0x28 (s0-s3 + ra)
 *
 * STATUS: mism=13, n=33/33 (EXACT LENGTH), FRAME EXACT, all four callee-saved registers
 * assigned exactly as golden (s0=str, s1=x, s2=gfx, s3=y).  Cold decompile 2026-08-26.
 *
 * WHAT IT IS: the text-drawing loop.  For every non-NUL byte of arg3 it emits one glyph
 * through func_15041508 and advances x by 8.  Callee prototypes are DEFINED in this TU
 * BELOW the pragma -- `s32 func_15041480(u8)` at line 38 and
 * `Gfx *func_15041508(Gfx *, s32, s32, s32)` at line 64 -- so the body needs matching
 * forward declarations or the compile fails with "redeclaration of func_15041480".
 *
 * ---------------------------------------------------------------- SCORE LADDER (measured)
 *   53  n=35/33 -- ANY spelling with NO local for the character:
 *       `while (*arg3 != 0) { ... func_15041480(*arg3) ... }`, the `for (; ...; arg3++,
 *       arg1 += 8)` form, `func_15041480(*arg3++)`, and the `if (...) do {...} while (...)`
 *       form.  All of them make IDO give the character its own CALLEE-SAVED register, so
 *       the function saves s0-s4 (five) instead of s0-s3 and grows to -0x30.
 *   53  the same shapes with a `u8 c` local (u8 behaves like no local at all here).
 *   15  `s32 c` local, increments written `arg1 += 8; arg3++;`
 *   13  `s32 c` local, increments written `arg3++; arg1 += 8;` (golden's order -- the
 *       bottom-of-loop `addiu $s0,$s0,1` lands before the delay-slot `addiu $s1,$s1,8`).
 *       Identical 13 for the `while ((c = *arg3) != 0)` form, the `if (c != 0) do {...}
 *       while (c != 0)` form, and with an explicit `(u8)c` cast at the call.   <-- PARKED
 *
 * ---------------------------------------------------------------- WHAT IS LEFT (ONE CAUSE)
 * The character needs to live in $a0, not in a register of its own:
 *      ours:   lbu $v1,0x0($s0) ... andi $a0,$v1,255 (inside the loop) ... lbu $v1,0x1($s0)
 *      golden: lbu $t6,0x0($a3) ... andi $a0,$t6,255 (in the beq DELAY SLOT, peeled) ...
 *              lbu $a0,0x1($s0)   <- straight into the argument register, NO mask
 * IDO elides the u8-parameter mask when the value comes directly out of an `lbu` into the
 * argument register, but not when it has to pass through a declared local.  So golden has
 * NO local -- yet every no-local spelling costs a fifth callee-saved register.  That is the
 * contradiction to break.  Consequences: we use `beql` + a duplicated `or $v0,$s2,$zero`
 * for the loop exit where golden uses `beq` and shares the epilogue's copy.
 */
s32 func_15041480(u8 arg0);
Gfx *func_15041508(Gfx *gfx, s32 arg1, s32 arg2, s32 arg3);

Gfx *func_150413FC(Gfx *gfx, s32 arg1, s32 arg2, u8 *arg3) {
    s32 c;

    c = *arg3;
    while (c != 0) {
        gfx = func_15041508(gfx, arg1, arg2, func_15041480(c));
        arg3++;
        arg1 += 8;
        c = *arg3;
    }
    return gfx;
}
