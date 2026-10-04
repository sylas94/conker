/* tools/nearmiss/func_151C1570.c -- game_1ED0F0, 35 instructions, frame -0x28
 *
 * STATUS: mism=27, n=35/35 (EXACT LENGTH).  Cold decompile 2026-10-02.
 * Frame is -0x18, golden is -0x28 (SIXTEEN TOO SMALL -- the opposite of the usual).
 *
 * >>> SAME RESIDUE AS tools/nearmiss/func_151A8584.c AND func_151A85D4.c.  THREE MEMBERS.
 * >>> "PARAMETER HOME-SLOT RESIDENCY": golden stores the incoming pointer ONCE to its own
 * >>> home slot and reloads it from there at every use, keeping NO register copy; our IDO
 * >>> copies it to a spare argument register and spills THAT.  Solve it once, close three.
 *
 * WHAT IT IS: the teardown for the 0x1ED0F0 object.  `void func_151C1570(void *);` is
 * already declared in the TU at line 328 (so the signature is settled), `func_151C110C` is
 * defined at line 305, and the +0x170 sub-object idiom is the TU's own -- see
 * func_151C1814 at line 396: `s32 *v0 = (s32 *)((u8 *)arg0 + 0x170); ... v0[0x1B]`.
 *
 * ---------------------------------------------------------------- SCORE LADDER (measured)
 *   43  `Sub *p` struct-typed view of +0x170, p assigned just before its first use
 *   43  everything inline as `*(s32 *)((u8 *)arg0 + 0x1F8)` (no +0x170 base at all)
 *   43  ...with a separate `v = p->unk88` local
 *   41  `s32 *p` + `p[0x22]`/`p[0x23]` indexing (the TU's own idiom)
 *   41  parameter retyped `s32 *arg0` with `arg0[0x7C]`/`arg0[0x7D]` (needs the line-328
 *       forward declaration dropped); identical to the `void *` + cast form
 *   27  >>> ...with `p = (s32 *)((u8 *)arg0 + 0x170);` HOISTED TO THE TOP OF THE FUNCTION.
 *       n goes 34 -> 35 (exact).  Assigning it anywhere later lets IDO fold p back into
 *       arg0-relative offsets (`508(a1)`) instead of materialising the base; assigning it
 *       at the top forces the base to exist across the calls.  Between the two `if`s
 *       scores the same 27.                                            <-- PARKED
 *   27  at plain -O2 as well;  54 at -O1 (frame -0x20, n=37/35).  NOT a flag question.
 *
 * ---------------------------------------------------------------- WHAT IS LEFT (ONE CAUSE)
 *      golden: sw $a0,0x28($sp)          <- arg0 to its OWN home slot, once
 *              lw $t6,0x28($sp) / lw $a1,0x28($sp) ...   reload per use
 *              addiu $a1,$a1,0x170       <- p built INTO that register, once
 *              sw $a1,0x1C($sp) / lw $a1,0x1C($sp)       p spilled round the 2nd call
 *      ours:   move $a3,$a0              <- a register copy of arg0 that golden never makes
 *              sw $a3,0x18($sp) / lw $a3,0x18($sp)       arg0 spilled round every call
 *              addiu $v0,$a3,368 (TWICE) <- p rematerialised instead of spilled
 * Both differences are one decision: which value IDO elects to keep live.  Golden keeps p
 * in a register and arg0 in memory; we keep arg0 in a register and rebuild p.  The 16 frame
 * bytes are golden's second spill slot plus [[conker-ido-local-decl-laws]] LAW I padding.
 */
void func_151C1570(void *arg0) {
    s32 *p;

    p = (s32 *)((u8 *)arg0 + 0x170);
    if (*(void **)((u8 *)arg0 + 0x1F0) != NULL) {
        func_1516972C(*(void **)((u8 *)arg0 + 0x1F0));
    }
    if (*(void **)((u8 *)arg0 + 0x1F4) != NULL) {
        func_1516972C(*(void **)((u8 *)arg0 + 0x1F4));
    }
    if (p[0x22] != 0) {
        *(s32 *)(p[0x22] + 0x110) = 0;
    }
    if (p[0x23] != 0) {
        func_1516972C((void *)p[0x23]);
    }
    func_1000FD38(func_151C110C, arg0, 0);
}
