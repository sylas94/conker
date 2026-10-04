/* tools/nearmiss/func_10001420.c -- init_1420, 9 instructions, LEAF
 *
 * STATUS: mism=19, n=10/9 (ONE OVER).  Re-opened 2026-08-26 (the TU carries an old
 * "JUSTREG / imported into decomp-permuter" comment; that diagnosis was incomplete).
 *
 * WHAT IT IS: zero the 508-entry TLB slot table (0xFE0 bytes = 1016 words) at D_80043B40.
 * See src/game_45B80.c:149 for what the table is.
 *
 * IT IS NOT A REGISTER PROBLEM -- IT IS ONE EXTRA INSTRUCTION.
 *      golden:  lui   $t6, %hi(D_80043B40)
 *               addiu $a1, $t6, %lo(D_80043B40)      ; p
 *               addiu $a0, $a1, 0xFE0                ; end DERIVED FROM p AT RUNTIME
 *      ours:    lui   $v0, %hi(D_80043B40)
 *               lui   $v1, %hi(D_80043B40)           ; <-- THE EXTRA WORD
 *               addiu $v0, $v0, %lo(D_80043B40)
 *               addiu $v1, $v1, %lo(D_80043B40)+0xFE0
 * The loop body itself (`addiu p,4` / `sltu at,p,end` / `bnez` / `sw zero,-4(p)`) is
 * byte-identical already.
 *
 * ---------------------------------------------------------------- MEASURED (all 19)
 * The bound-fold is UNCONDITIONAL at -O2.  Every one of these emits the second lui:
 *   `end = p + 1016`;  `end = &p[1016]`;  `end = (s32*)((u8*)p + 0xFE0)`;
 *   `end = (s32*)((u32)p + 0xFE0)`;  `end = p; end += 1016;`  (split statements)
 *   `p = end; end = p + 1016;`  (assign through the other variable first)
 *   bound inline in the condition (LAW E form);  while- and for- and do/while shapes;
 *   `volatile s32 *p`;  u32 vs s32 element type;  decl order end-then-p.
 * Counted-loop forms are strictly worse (index + `*p++`: 49, subscript: 39, `--i`: 39).
 * Flags: -O2 = 19, -O2 -g3 = 19, -O1 = 98, -g = 129, -O3 / -O1 -g3 = asm-processor reject.
 *
 * PROVEN WITH A STANDALONE PROBE (ido5.3 cc, objdump -dz), four spellings:
 *   complete-type `extern s32 arr[1016]` with a symbol bound; the same with a
 *   pointer-derived bound; `(s32*)&ptrvar` with a pointer-derived bound; do/while with a
 *   symbol bound.  ALL FOUR emit byte-identical code with TWO luis and the locals in
 *   $v0/$v1.  There is no C spelling of "zero this global array" that makes IDO -O2
 *   derive the bound from the pointer register.
 *
 * ---------------------------------------------------------------- WHAT IS LEFT
 * Golden puts the two loop pointers in $a1/$a0 and uses $t6 only as the lui temp.  IDO -O2
 * puts locals in $v0/$v1 (LAW C).  Combined with the un-folded bound, this function does
 * not look like IDO -O2 -g3 output at all.  Next step is to decide between:
 *   (a) it is hand-written asm (its TU neighbours in init_1420 are boot/TLB code, and
 *       func_10001550 already carries a hand-delay-slot comment), or
 *   (b) it was built with a per-object flag this tree does not model.
 * Do NOT "fix" it by giving the function unused parameters to occupy $a0/$a1 -- the two
 * callers (func_10001444, func_100014C4) call it with no arguments, so that is a forcer.
 */

void func_10001420(void) {
    s32 *p;
    s32 *end;

    p = (s32 *)&D_80043B40;
    end = p + 1016;
    do {
        *p++ = 0;
    } while (p < end);
}
