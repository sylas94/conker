/* tools/nearmiss/func_151A8584.c -- game_1D4E00, 20 instructions, frame -0x18
 *
 * STATUS: mism=11 at plain -O2 with EXACT LENGTH (20/20).  Was 28 at the tree default
 * -O2 -g3 (n=21/20).  Updated 2026-08-26.
 *
 * >>> func_151A85D4 in the same TU is the IDENTICAL function with D_8008F958 and
 * >>> func_15169824 substituted -- SOLVE ONE, SHIP BOTH.  Same park text applies.
 *
 * Dispatches D_8008F94C[arg0->unk5C](arg0) when non-NULL, then func_151A8560(arg0) and
 * func_15169804(arg0).
 *
 * ---------------------------------------------------------------- THE -g3 FINDING
 *   -O2 -g3 (tree default) : 28, n=21/20 -- IDO reloads arg0 into a TEMP ($t6) and adds
 *                            `or $a0,$t6,$zero` before the jalr.  That copy is the +1.
 *   -O2                    : 11, n=20/20 -- the copy is gone, arg0 stays in $a0.
 *   -O1                    : 30, frame -0x20 (wrong)
 *   -g                     : 89, n=27/20
 * See [[conker-g3-delayslot]]: a per-TU `OPT_FLAGS := -O2` override has already shipped
 * three byte-perfect functions elsewhere.  game_1D4E00 has 8 pragmas left, so the override
 * is cheap to TEST -- the ROM sha1 gate is the acceptance test for whether the TU's
 * already-matched functions survive it.  Do that before spending more on the source shape.
 *
 * ---------------------------------------------------------------- WHAT IS LEFT (at -O2)
 * SPILL PLACEMENT, and it is invariant to every source shape tried:
 *      ours:   `sw $a0,0x18($sp)` hoisted into the PROLOGUE (before the `lbu 0x5C($a0)`),
 *              one store + two reloads, and a `nop` left in the jalr delay slot.
 *      golden: no prologue store; `sw $a0` sits in the jalr delay slot and again in the
 *              `jal func_151A8560` delay slot -- spill-before-each-call, reload-after.
 * Measured identical (11) for ALL of: `if (fn)` vs `if (fn != NULL)`; no `fn` local (call
 * the table entry inline twice); `(*fn)(arg0)`; parameter typed `struct102 *` with the
 * casts moved to the field read; `register` on the parameter; a separate `u8 idx` local;
 * an empty `else` branch.  The shape of the C is not the lever here.
 */

typedef struct Obj151A8584 {
    char pad0[0x5C];
    /* 0x5C */ u8 unk5C;
} Obj151A8584;

extern void (*D_8008F94C[])(Obj151A8584 *);

void func_151A8584(Obj151A8584 *arg0) {
    void (*fn)(Obj151A8584 *);

    fn = D_8008F94C[arg0->unk5C];
    if (fn != NULL) {
        fn(arg0);
    }
    func_151A8560(arg0);
    func_15169804((struct102 *)arg0);
}
