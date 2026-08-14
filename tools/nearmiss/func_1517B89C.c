/* PARKED NEAR-MISS: func_1517B89C   (conker/src/game_1A89B0.c, 196 instructions, 0x39C..0x6A4)
 * Hoare quicksort over the global array D_800DDD18[] of 14-byte `struct Struct800DDD18`
 * (definition copied verbatim from the LIVE C in conker/src/game_36680.c:561).
 * D_8008CEB4 (s32) selects the sort key: 0 -> .unk0, nonzero -> .unk4.
 * Caller: game_36680.c func_1500BEC0 -> `D_8008CEB4 = 0; func_1517B89C(0, D_800DDD20 - 1);`
 *
 * BEST SCORE 630 (bounded, --max-lines 4096).  Base for all deltas below.
 *
 * PROGRESSION (every number measured, IDO 5.3 -O2 -g3, `-o func_1517B89C -R`)
 *   1010  s32 i, j + 2 struct temps, pivot written inline as D_800DDD18[right].unkX
 *          -> tmp landed at sp+0x50 / tmp2 at sp+0x40; golden wants 0x4C / 0x3C.
 *             FRAME LAW: home area was 4 bytes short => exactly ONE 4-byte local missing.
 *             Also golden built the arr[right] induction variable BEFORE arr[i]'s.
 *    755  + `s32 pivot;` declared THIRD and assigned once per flag-branch.
 *             Fixes BOTH symptoms at once: home area now 44 bytes
 *             (i@0x64, j@0x60, pivot@0x5C, tmp@0x4C, tmp2@0x3C -- structs are
 *             4-ALIGNED and size-rounded to 16 in the home area), and the pivot
 *             load is what creates t5 = right*14 first.  Frame 0x68 EXACT.
 *    630  + swap-block tail spelled `j--; i++;` instead of `i++; j--;`   <-- PARKED
 *
 * MEASURED NEGATIVES (all from the 630/755 base, all rebuilt from scratch each time)
 *    755  `i++; j--;`                          (natural order, but 125 worse)
 *    755  `i = i + 1; j = j - 1;`              (spelling of ++ is irrelevant)
 *    630  `j = j - 1; i = i + 1;`              (spelling of -- is irrelevant)
 *    755  `i++;` moved above the last copy
 *    925  `j--; D_800DDD18[j + 1] = tmp; i++;`
 *   1890  increments hoisted to the top of the swap block with `i - 1`/`j + 1`
 *          subscripts  -- this DESTROYS the induction variables; the block-start
 *          theory cannot be bought this way
 *    630  `if (i < j) { ... } else { break; }`  (identical to `if (i >= j) break;`)
 *    755  same if/else with `i++; j--;`
 *    755  `for (;; i++, j--)`
 *    630  `for (;; j--, i++)`
 *    630  `while (1)` instead of `for (;;)`
 *    630  declaration order `s32 i; s32 pivot; s32 j;`  (only i's ordinal is pinned,
 *          because i is the one that spills, to 0x64 = the FIRST home slot)
 *    630  `D_800DDD18[j--] = tmp; i++;`  (post-decrement folded into the last copy)
 *    630  `i = i + 1;` instead of `i++`
 *   ---- the 630 plateau is a genuine tie: five different honest spellings reach it.
 *
 * HARNESS INTEGRITY: every batch above included a CONTROL that moved the score
 * (i++/j-- = 755 vs j--/i++ = 630), so an identical-score run is real evidence and
 * not a broken patcher.  This file, pasted over the pragma, rebuilds to 630.
 *
 * RESIDUAL AT 630 -- CLASSIFY: as1 PEEPHOLE / SCHEDULING (delay-slot fill).
 *   Instruction MULTISET is identical; mine is exactly ONE instruction longer.
 *   Golden's swap basic block is scheduled so that `addiu t0,t0,0xe` (the i*14
 *   derived induction variable) is its FIRST instruction; as1 then hoists it into
 *   the delay slot of a plain `beqz`, and `addiu a3,a3,-0xe` ends up last so it
 *   fills the `b` delay slot:
 *        52c: beqz  at,5dc  /  530: addiu t0,t0,0xe   ...  5d4: b 3fc / 5d8: addiu a3,a3,-0xe
 *   Mine begins the block with the `lwl/lwr` unaligned-load MACRO, which as1 will
 *   not split into a delay slot, so it emits `beqzl` + a duplicated `lwl` (+1 insn):
 *        52c: beqzl at,5e4  /  530: lwl at,0(v1)
 *   The same one-position shift shows up in the post-loop block: golden starts it
 *   with `addiu v0,sp,0x3c` (address of tmp2), mine starts it with lwl/lwr and the
 *   two call-argument setups (`move a0,s1`, `addiu a1,a2,-1`) then land in
 *   different stall slots.  Every differing row is one of these four scalar ops
 *   (t0, a3, v0-address, a1) sitting in a different slot of the SAME basic block.
 *   No allocation, no basic-block, no relocation difference remains.
 *
 * NOTE FOR THE NEXT RUN: `--max-lines 196` reports a FALSE 0 for this function
 * (truncation trap).  Score only with --max-lines 4096.
 */
struct Struct800DDD18
{
  s16 unk0;
  s16 unk2;
  s16 unk4;
  u8  unk6;
  u8  unk7;
  u8  unk8;
  u8  unk9;
  u8  unkA;
  u8  unkB;
  u8  unkC;
  u8  unkD;
};

extern struct Struct800DDD18 *D_800DDD18;
extern s32 D_8008CEB4;

void func_1517B89C(s32 left, s32 right)
{
    s32 i;
    s32 j;
    s32 pivot;
    struct Struct800DDD18 tmp;
    struct Struct800DDD18 tmp2;

    if (left < right)
    {
        i = left;
        j = right;
        for (;;)
        {
            if (D_8008CEB4 == 0)
            {
                pivot = D_800DDD18[right].unk0;
                while ((D_800DDD18[i].unk0 < pivot) && (i < right))
                {
                    i++;
                }
                while ((pivot < D_800DDD18[j].unk0) && (left < j))
                {
                    j--;
                }
            }
            else
            {
                pivot = D_800DDD18[right].unk4;
                while ((D_800DDD18[i].unk4 < pivot) && (i < right))
                {
                    i++;
                }
                while ((pivot < D_800DDD18[j].unk4) && (left < j))
                {
                    j--;
                }
            }
            if (i >= j)
            {
                break;
            }
            tmp = D_800DDD18[i];
            D_800DDD18[i] = D_800DDD18[j];
            D_800DDD18[j] = tmp;
            j--;
            i++;
        }
        tmp2 = D_800DDD18[i];
        D_800DDD18[i] = D_800DDD18[right];
        D_800DDD18[right] = tmp2;
        func_1517B89C(left, i - 1);
        func_1517B89C(i + 1, right);
    }
}
