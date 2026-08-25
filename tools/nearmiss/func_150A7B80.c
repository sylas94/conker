/* tools/nearmiss/func_150A7B80.c -- game_D5030.c, the TU's only function (guMtxIdent)
 *
 * STATUS 2026-08-24: mism=5, frame=leaf, n=16/16 EXACT. FIFTEEN of sixteen instructions are
 * byte-identical INCLUDING the jr delay slot. The entire residue is ONE REGISTER: we hold the
 * constant 1 in $v0, golden holds it in $t0.
 *
 * WHAT IT IS: guMtxIdent on the N64 fixed-point Mtx. Eight `sd $zero` clear all 64 bytes, then
 * four `sh $t0` write 1 into the diagonal INTEGER half-words at 0x0/0xA/0x14/0x1E -- i.e.
 * intpart[0], [5], [10], [15] of the packed layout (first 32 bytes all integer parts, last 32
 * all fractional). Mtx's `long long force_structure_alignment` member is what makes the struct
 * 8-byte aligned and the `sd` legal.
 *
 * *** THE OLD IN-FILE COMMENT WAS HALF WRONG. Corrected here. ***
 * src/game_D5030.c claimed "FILE-FLAGS-SUSPECT: needs -mips3 (target uses `sd zero`; -mips2
 * emits li+sw pairs)". -mips3 ALONE changes NOTHING: with the s32-pointer reconstruction the
 * score is 96 / n=24 under BOTH -mips2 and -mips3, because 32-bit stores can never merge into
 * `sd`. TWO things are required together:
 *      (a) a 64-bit TYPE at the store site  -- `long long *d = (long long *)arg0; d[i] = 0;`
 *      (b) -mips3                            -- so that type lowers to `sd` and not two `sw`
 * Measured: (a) alone at -mips2 = 176/n=32. (b) alone = 96/n=24. Both = 5/n=16.
 * `arg0[i].force_structure_alignment = 0` also reaches n=16 but scores 12 (worse addressing).
 *
 * *** BLOCKED, AND THE BLOCKER IS PROVEN, NOT ASSUMED. ***
 * A -mips3 object CANNOT be linked into this 32-bit ROM. Tested end-to-end on 2026-08-24 with a
 * per-TU `MIPSBIT := -mips3 -o32` override (MIPSBIT is a plain Make variable in the same recipe
 * as OPT_FLAGS, so per-TU overrides DO apply -- that part works):
 *      cc: Warning: -mips3 should not be used for ucode 32-bit compiles
 *      mips-linux-gnu-ld: failed to merge target specific data of file build/src/game_D5030.c.o
 *      make: *** [build/conker.us.elf] Error 1
 * This independently confirms the note already in conker/Makefile about the game_DAE50 RNG.
 * So the whole 0x150A math cluster shares ONE blocker: they need -mips3 codegen and -mips3
 * objects do not link. Converting the entire ROM to -mips3 is the only clean unlock, and that
 * is a very large change to validate.
 *
 * THE LAST REGISTER, for whoever picks this up if the link problem is ever solved: six honest
 * spellings were swept and ALL tie at exactly 5 -- bare `h[i] = 1`, an `s16` local, an `s32`
 * local, the local declared first, inline `((s16 *)arg0)[i]` casts with no pointer local, and
 * reordering the ones before the zeros. The register does not move from source. Note also that
 * $t0 rather than $v0 for a scratch constant in a leaf void function is characteristic of
 * HAND-WRITTEN assembly, which is exactly what memory records for this 0x150A cluster
 * (conker-handwritten-math-cluster). Do not force it with dead temps to rotate the allocator --
 * that is the forcer pattern and it fails the load-bearing test.
 *
 * VERDICT: BAIL until/unless the ROM-wide -mips3 question is taken on.
 */
#include <ultra64.h>

#include "functions.h"
#include "variables.h"

/* Reaches mism=5 (one register) ONLY under -mips3, which does not link. */
void func_150A7B80(Mtx *arg0) {
    long long *d = (long long *)arg0;
    s16 *h = (s16 *)arg0;

    d[0] = 0; d[1] = 0; d[2] = 0; d[3] = 0;
    d[4] = 0; d[5] = 0; d[6] = 0; d[7] = 0;
    h[0] = 1;
    h[5] = 1;
    h[10] = 1;
    h[15] = 1;
}
