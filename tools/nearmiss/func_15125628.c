/* tools/nearmiss/func_15125628.c -- game_14FF90, 26 instructions, leaf
 *
 * STATUS: mism=16, n=26/26 (EXACT LENGTH).  Cold decompile 2026-08-25.
 * Four independent "decrement if non-zero" byte counters.  Each block is 6 instructions in
 * BOTH builds; the entire residue is the address form, four times over.
 *
 *   ours:   lui v1,%hi ; addiu v1,v1,%lo ; lbu v0,0(v1) ; beqz ; addiu t6,v0,-1 ; sb t6,0(v1)
 *   golden: lui v0,%hi ; lbu v0,%lo(v0)  ; lui at,%hi   ; beqz ; addiu t6,v0,-1 ; sb t6,%lo(at)
 *
 * IDO builds a full pointer when an address is used twice and the `lui`+%lo macro form when
 * used once.  A read-modify-write names the variable twice, so we always CSE the address;
 * golden materialises it twice.  Refuted, all identical at 16:
 *      D_800DBFF4[0] (the real array declaration) vs four true SCALAR externs -- SAME score,
 *      so this is NOT about array-vs-scalar, it is purely the load/store address CSE.
 *      `volatile` makes it much worse (106, n=34).
 * NOTE this is the same shape as the "$at + addend" question but the OPPOSITE direction, and
 * it is NOT solved by the unroller trick that fixed func_150B6C90 -- there is no loop here
 * (4 blocks, all absolute; LAW A would have used a computed base).
 */

void func_15125628(void) {
    if (D_800DBFF4[0] != 0) {
        D_800DBFF4[0]--;
    }
    if (D_800DBFF5 != 0) {
        D_800DBFF5--;
    }
    if (D_800DBFF6 != 0) {
        D_800DBFF6--;
    }
    if (D_800DBFF7 != 0) {
        D_800DBFF7--;
    }
}
