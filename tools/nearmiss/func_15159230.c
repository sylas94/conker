/* tools/nearmiss/func_15159230.c -- game_185560, 34 instructions, LEAF (no frame at all)
 *
 * STATUS: mism=33, n=33/34 (ONE SHORT).  Cold decompile 2026-08-26.
 * The SEMANTICS are certain and the prototype is already in the TU at line 399:
 *      s32 func_15159230(Struct15158BD0_src *, f32 *, u8);
 * and Struct15158BD0_src (line 293) already has unk14/unk18/unk1C as f32 at exactly the
 * offsets golden reads.  Do not invent a type for this one.
 *
 * Returns 0 when the three floats match, else 2 when arg2 is 1 or 2, else 1.
 * `sw $a2,0x8($sp)` with NO stack adjustment is the u8 parameter being written to its
 * caller-side home slot -- that comes free from declaring arg2 as `u8`, together with the
 * `andi $t6,$a2,0xFF` that follows it.  Rows 0-2 already match.
 *
 * ---------------------------------------------------------------- WHAT IS LEFT (TWO)
 * (1) FP COMPARE OPERAND ORDER.  Golden loads `arg1[i]` into the LOW register and the
 *     struct field into the high one; we do the opposite:
 *        ours:   lwc1 $f4,0x14($a0) ; lwc1 $f6,0x0($a1)
 *        golden: lwc1 $f4,0x0($a1)  ; lwc1 $f6,0x14($a0)
 *     `c.eq.s $f4,$f6` itself matches, so ONLY the two loads are swapped -- three times.
 *     IMPORTANT: LAW H (right operand first) DOES NOT APPLY to `c.eq.s`.  Writing
 *     `arg0->unk14 == arg1[0]` instead of `arg1[0] == arg0->unk14` produces BYTE-IDENTICAL
 *     output (33 either way), so IDO canonicalises FP compare operands and the lever is
 *     somewhere else -- probably the TYPE of arg1 (try a struct pointer with three named
 *     f32 members rather than `f32 *`).
 * (2) `ret = 0` PLACEMENT.  Golden sets `or $v1,$zero,$zero` BEFORE the third `c.eq.s`
 *     (filling its hazard slot) and then uses `bc1t` straight to the epilogue.  We emit
 *     `bc1f` + `b` + `or $v1,$zero,$zero` in the delay slot, which is the missing word, and
 *     it also flips the order of the two `addiu $v1,$zero,{1,2}` arms.
 *     Hoisting `ret = 0;` to the top of the function and negating the condition
 *     (`if (!(...))` or the de-Morgan'd `||` chain) makes it WORSE: 43, n=32/34.
 */
s32 func_15159230(Struct15158BD0_src *arg0, f32 *arg1, u8 arg2) {
    s32 ret;

    if ((arg1[0] == arg0->unk14) && (arg1[1] == arg0->unk18) && (arg1[2] == arg0->unk1C)) {
        ret = 0;
    } else if ((arg2 == 1) || (arg2 == 2)) {
        ret = 2;
    } else {
        ret = 1;
    }
    return ret;
}
