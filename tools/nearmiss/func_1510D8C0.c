/* tools/nearmiss/func_1510D8C0.c -- game_139FC0, 44 instructions, leaf
 *
 * STATUS: mism=39, n=44/44 (EXACT LENGTH).  Cold decompile 2026-08-25.
 * Semantics fully solved; the entire residue is ONE address-form decision, and it is a
 * FOURTH member of the constant-hoist family (see NOTES below).
 *
 * WHAT IT IS: walks the D_800D9ED8 table (filled by func_1510D874 right above the pragma,
 * whose `struct Entry1510D874` this reuses) and emits a gSPSegment pair per matching entry.
 * The magic 0xDB060000 is F3DEX2's gsMoveWd(G_MW_SEGMENT,...) header, so the two words are
 * exactly gSPSegment(gfx++, seg, base) -- no hand-rolled packet macro needed.
 *
 * FIXED ALONG THE WAY: `struct Entry1510D874.unkC/.unkD` were declared s8 but golden loads
 * them with `lbu`.  Widened to u8 in the TU (safe -- the only other user only ever `sb`s
 * them, and the ROM gate is green with the change in).
 *
 * ------------------------------------------------------------------ WHAT IS LEFT (all 39)
 * Same instruction COUNT, different addressing for the loop bound:
 *      ours:   lui a3,%hi(D_800D9ED0) ; addiu a3,a3,%lo  (hoisted ONCE out of the loop)
 *              ... lbu t6,0(a3) ... lbu t1,0(a3)
 *      golden: lui v1,%hi(D_800D9ED0) ; lbu v1,%lo(D_800D9ED0)(v1)   -- TWICE, not hoisted
 * Both are 4 instructions, so n stays 44/44; every register downstream shifts because ours
 * burns $a3 on the hoisted address while golden spends it on the 0xDB06 constant.
 *
 * We hoist the loop-invariant ADDRESS out; golden re-materialises it each time.  Refuted,
 * all identical at 39: `for` with an index, `for` with a strength-reduced entry pointer
 * (`i = 0, e = D_800D9ED8`), and an explicit `if (D_800D9ED0 > 0) do {...} while` -- the
 * hoist is stable across every loop spelling.
 *
 * >>> This is the CONSTANT-HOIST FAMILY residue, seen from the other side: those parks are
 * >>> "IDO will not hoist a global load out of a storing loop", this one is "IDO hoists a
 * >>> global's ADDRESS when golden did not".  Same alias question about stores through the
 * >>> Gfx* invalidating a global.  Solve it once for all four.
 */

Gfx *func_1510D8C0(Gfx *gfx, s32 arg1) {
    s32 i;

    for (i = 0; i < D_800D9ED0; i++) {
        if (arg1 == D_800D9ED8[i].unk0) {
            gSPSegment(gfx++, D_800D9ED8[i].unkC, D_800D9ED8[i].unk4);
            if (D_800D9ED8[i].unk8 != 0) {
                gSPSegment(gfx++, D_800D9ED8[i].unkD, D_800D9ED8[i].unk8);
            }
        }
    }
    return gfx;
}
