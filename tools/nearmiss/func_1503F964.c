/* tools/nearmiss/func_1503F964.c -- game_6CCB0, 35 instructions, LEAF, no frame
 *
 * STATUS: mism=14, n=35/35 (EXACT LENGTH), leaf/no-frame exact.  Cold decompile 2026-10-02.
 * The DECODE IS COMPLETE AND CERTAIN -- every instruction, immediate and branch target is
 * accounted for.  What is left is ONE register swap (see below).
 *
 * WHAT IT IS: advance the "current object" cursor D_800C67F1 to the next actor (circularly,
 * wrapping at 25) whose struct127.unkF8 has bit 0x800000 set, giving up when the scan comes
 * back round to where it started.  Gated on D_800C67F0 being non-zero.
 * All the types are already in the tree: `extern u8 D_800C67F0/D_800C67F1` (variables.h
 * 950/951), `extern struct127 D_800CC2D0[26]` (variables.h 1003), `s32 unkF8` at offset
 * 0xF8 of struct127 (structs.h, struct127 starts at line 1031).  The 0x32C stride and the
 * D_800CC2D0 actor array are [[conker-actor-control-system]].
 *
 * ---------------------------------------------------------------- WHAT IS LEFT (ONE SWAP)
 * $v1 and $a0 are exchanged, and nothing else differs:
 *      golden:  $v0 = start,  $v1 = &D_800CC2D0 (loop-invariant),  $a0 = i
 *      ours:    $v0 = start,  $a0 = &D_800CC2D0,                   $v1 = i
 * $a1/$a2/$a3 (the &D_800C67F1 address, the 0x32C stride and the 0x800000 mask) are already
 * right, so the only free slots are $v0/$v1/$a0 and IDO fills them in a different order.
 * Note the index is NOT monotonic (it wraps to 0), so there is no strength reduction and the
 * array base legitimately stays a hoisted invariant -- that part is correct.
 *
 * MEASURED -- all of these score exactly 14, so the lever is not any of them:
 *   declaration order `s32 i; s32 start;` and `s32 start; s32 i;`
 *   an explicit `struct127 *p = D_800CC2D0;` base local declared 2nd, and declared 3rd
 *     (IDO coalesces it away either way -- it does NOT claim $v1)
 *   `(0x800000 & ...unkF8) != 0` (LAW H operand swap)
 *   `if (...unkF8 & 0x800000)` (LAW G truthiness)
 *   `if (!(i < 25))` instead of `if (i >= 25)`
 * This is a pure allocation-priority residue: whatever makes IDO rank the invariant address
 * ABOVE the loop counter closes it.  Candidate next step is the permuter.
 */
void func_1503F964(void) {
    s32 i;
    s32 start;

    if (D_800C67F0 == 0) {
        return;
    }
    start = D_800C67F1;
    i = start + 1;
    if (i >= 25) {
        i = 0;
    }
    while (i != start) {
        if ((D_800CC2D0[i].unkF8 & 0x800000) != 0) {
            D_800C67F1 = i;
            return;
        }
        i++;
        if (i >= 25) {
            i = 0;
        }
    }
}
