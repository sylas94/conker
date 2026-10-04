/* tools/nearmiss/func_151D2F90.c -- game_1FFF60.
 *
 * FILE KIND: STANDALONE TU (a note; splice the body over the pragma in src/game_1FFF60.c).
 *
 * STATUS 2026-08-24: mism=42, frame -0x18 (golden's), n=104/104 -- EXACT LENGTH.
 * From no attempt at all to 42 with the right frame and length; the residue is register
 * rotation plus one branch-likely store.
 *
 * BUILT FROM THE MATCHED SIBLING, not from scratch. func_151D2C40 sits directly above it in
 * the same file and shares the shape: obj = arg0->unk10, the same three-clause early-out to
 * func_1516972C, and the same byte-offset cast idiom. The `& 0xFFFD` spelling (rather than
 * `& ~2`) is also already in this file, in func_151D2F00 -- IDO emits `andi ...,0xFFFD`
 * because the u8 promotes to int.
 *
 * TWO MEASURED FINDINGS, both worth more than the score:
 *
 * 1. `was` MUST BE READ SEPARATELY FROM arg0, not derived from a cached `flags` local.
 *        was = *(u8 *)((u8 *)arg0 + 0x18) & 2;     ->  42
 *        flags = ...; was = flags & 2;             ->  70
 *    Golden computes `was` BEFORE the early-out and spends it on two branch delay slots we
 *    otherwise leave as nop:
 *        lbu  $v1, 0x18($a0)      flags
 *        lw   $t7, 0x0($v0)
 *        or   $a1, $v1, $zero     a1 = flags
 *        andi $t6, $a1, 0x2
 *        beqz $t7, .L151D2FD4
 *        or   $a1, $t6, $zero     a1 = flags & 2   <- delay slot
 *    The double move through $a1 is the tell that `was` is assigned twice, not once.
 *
 * 2. ASSIGNMENT ORDER IS LOAD-BEARING AND ONE DIRECTION IS STRICTLY WRONG.
 *        assign flags then was  ->  42, n=104/104
 *        assign was then flags  -> 108, n=105/104   (an extra instruction appears)
 *    Declaration order does NOT matter here (42 either way), which is unusual for this
 *    codebase -- see memory/conker-private-libultra-copies.md for the frame-layout law where
 *    it does. Dropping the `flags` local entirely and re-reading at each use also gives 42,
 *    and is the simplest honest spelling, so prefer it.
 *
 * REMAINING RESIDUE. Golden keeps `flags` in the load register $v1 and routes `was` through
 * $a1; we put the load in $a2 and the copy in $a1 -- a one-register rotation. And at
 *        beql $t1, $zero, .L151D301C
 *        sb   $t5, 0x18($a0)          <- store in the branch-likely delay slot
 * we emit `beqz` + `nop`. That second half is the SAME delay-slot family as four other
 * functions -- see memory/conker-delayslot-duplication-family.md before spending time on it.
 *
 * GOLDEN CONTAINS DEAD CODE HERE, which is a useful sanity anchor: the `sb $t5, 0x18($a0)`
 * after `b .L151D301C` is unreachable, the orphan left when IDO converted the `||` chain into
 * two branch-likelies that each carry the same store in their delay slot. Do not try to
 * reproduce it deliberately; it falls out of the || spelling.
 */
