/* tools/nearmiss/func_1511A410.c -- game_142560, 33 instructions, LEAF, frame -0x18
 *
 * STATUS: mism=44, n=31/33 (TWO SHORT).  Cold decompile 2026-08-26.
 *
 * WHAT IT IS: scan an array of 8-byte records for up to TWO entries whose s8 field 0 is -3,
 * stopping at the -0x21 (-33) terminator; return the first index and write the second
 * through arg1.  `found[]` is a 2-slot stack array at sp+0xC, zero-initialised.
 *
 * The overall shape is already right: the folded entry test (`lb $t6,0($a0)`) AND the
 * separate un-folded preheader load (`sll $t7,$zero,3` / `addu` / `lb`) both reproduce, the
 * `slti $at,$v0,2` sits in the right place, and the `beql` + `lw $t4,0x10($sp)` delay pair
 * is right.  Frame size is exact.
 *
 * ---------------------------------------------------------------- WHAT IS LEFT (ONE CAUSE)
 * STRENGTH REDUCTION.  We turn `arg0[i]` into a walking pointer (`addiu $a1,$a1,8` +
 * `lb $a2,0x8($a1)`); golden recomputes the address every iteration:
 *      sll  $t2, $v1, 3
 *      addu $t3, $t2, $a0
 *      lb   $a1, 0x0($t3)
 * That is the two-instruction deficit, and every remaining row is the resulting shift.
 * Note golden does NOT strength-reduce the `&found[count]` address either -- it rebuilds
 * `sll/addiu $t1,$sp,0xC/addu` inside the `if`.  Whatever suppresses the loop optimiser
 * here suppresses it for both.
 *
 * Secondary (probably falls out with the above): golden's array is at sp+0xC, ours at
 * sp+0x10 -- golden reserves only 0xC of outgoing-arg space in a leaf frame, we reserve
 * 0x10.  `s32 found[3]` does NOT produce it (frame grows to -0x20, 45).
 *
 * ---------------------------------------------------------------- MEASURED
 *   44  while-loop with `(arg0[i].unk0 != -0x21) && (count < 2)`      <-- PARKED (below)
 *   44  the same as a `for (i = 0; ...; i++)`                          (identical output)
 *   45  `s32 found[3]`  /  45 for-loop + found[3]   (frame -0x20, wrong)
 *   55  `if (arg0->unk0 != -0x21) { do { ... } while (...); }`  (n=30/33 -- loses a third)
 *   56  hoisting the record byte into an `s8 v` local read once per iteration (n=30/33)
 *   46  at plain -O2;  163 at -O1 (frame -0x10, n=46/33).  Not a flag question.
 */
typedef struct Rec1511A410 {
    s8 unk0;
    char pad1[7];
} Rec1511A410;

s32 func_1511A410(Rec1511A410 *arg0, s32 *arg1) {
    s32 found[2];
    s32 count;
    s32 i;

    found[0] = 0;
    found[1] = 0;
    count = 0;
    i = 0;
    while ((arg0[i].unk0 != -0x21) && (count < 2)) {
        if (arg0[i].unk0 == -3) {
            found[count] = i;
            count++;
        }
        i++;
    }
    *arg1 = found[1];
    return found[0];
}
