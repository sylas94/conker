/* tools/nearmiss/func_1509CDDC.c -- game_C9EC0, 34 instructions, frame -0x30 (s0-s4 + ra)
 *
 * STATUS: mism=34, n=35/34 (ONE OVER), FRAME EXACT, register roles all correct.
 * Cold decompile 2026-08-26.
 *
 * WHAT IT IS: repeatedly sweep the 0xCC-entry byte table at D_800D2E70 looking for entries
 * marked 3, calling func_1509CCF4(i) on each and summing what it returns, until a whole
 * sweep adds nothing.  `s32 func_1509CCF4(s32)` is DEFINED in this TU at line 115 and
 * `extern s32 D_800D2E70;` (variables.h:1123, "size 0xF0") is addressed as
 * `((u8 *)&D_800D2E70)[i]`, the idiom the rest of the TU already uses.
 * The leading `jal func_1509CCF4` has a bare `nop` delay slot -- that is `func_1509CCF4(arg0)`
 * with arg0 still in $a0, which is why THIS FUNCTION TAKES A PARAMETER (confirmed:
 * src/game_20AE20.c:79 declares `void func_1509CDDC(s32);`).
 *
 * ---------------------------------------------------------------- WHAT IS LEFT (ONE CAUSE)
 * A CONTRADICTION between two IDO behaviours, and no spelling satisfies both:
 *   * INDEX form `((u8 *)&D_800D2E70)[i]` (parked below, 34) -- IDO materialises the base
 *     ONCE outside the outer loop into $s3 (correct, matches nothing being re-luied) but
 *     then does NOT strength-reduce: `addu $t6,$s3,$s0` + `lbu $t7,0($t6)` every iteration.
 *     That `addu` is the extra word.
 *   * POINTER form `p = (u8 *)&D_800D2E70;` at the top of the outer loop (62, n=37/34) --
 *     IDO DOES strength-reduce (`addiu $s1,$s1,1` in the branch delay slot, exactly golden)
 *     but HOISTS the `lui`/`addiu` of the symbol out of the outer loop into a SIXTH
 *     callee-saved register ($s5) and adds a per-iteration copy.  Three words too many.
 * Golden has both: `lui $s1,%hi` + `addiu $s1,$s1,%lo` INSIDE the outer loop head, and the
 * walking `addiu $s1,$s1,1`.  Find what stops the LICM hoist without losing the pointer
 * induction and this closes.  This is the same shape as [[conker-constant-hoist-family]]
 * but inverted -- there IDO refused to hoist, here it insists.
 *
 * MEASURED (all 62, i.e. hoist + 6th register): pointer assigned before `total = 0`;
 * after `total = 0`; after both `total = 0` and `i = 0`; the pointer advanced in a `for`
 * increment clause; do/while vs for for the inner loop.
 */
void func_1509CDDC(s32 arg0) {
    s32 i;
    s32 total;

    func_1509CCF4(arg0);
    do {
        total = 0;
        for (i = 0; i != 0xCC; i++) {
            if (((u8 *)&D_800D2E70)[i] == 3) {
                total += func_1509CCF4(i);
            }
        }
    } while (total != 0);
}
