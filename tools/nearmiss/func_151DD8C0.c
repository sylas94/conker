/* tools/nearmiss/func_151DD8C0.c -- game_20A990, demo/attract-mode playback.
 *
 * FILE KIND: STANDALONE TU (a note; the real TU is src/game_20A990.c, where three of the four
 * functions are already matched).
 *
 * STATUS 2026-08-23: mism=35 at the tree default, n=44/44, leaf. EVERY INSTRUCTION IS
 * GOLDEN'S -- the entire residue is register allocation.
 *
 * ONE SEMANTIC FIX GOT IT HERE: the button write is UNCONDITIONAL, not inside the
 * `index < 0x1F3` guard. Golden puts `sh $t3, 0x0($a1)` in the delay slot of `beqz $at`,
 * and a MIPS delay slot always executes:
 *      D_800BE748_pad.button = f->unk04 | (D_800BE748_pad.button & 0x1000);
 *      if (D_800E0A74 < 0x1F3) { if (D_800BE9E4 < f[1].unk02) { D_800E0BD2 = ...; } }
 *
 * THE RESIDUE. Golden holds &D_800BE748 in $a1 and the frame pointer in $a0, and starts its
 * short-lived temps at $t8 ascending; we hold &D_800BE748 in $a0 and the frame pointer in
 * $v0, leave $a1 for a short-lived temp, and start temps at $t7 -- then allocate DESCENDING
 * ($t7 before $t6), which is the tell that something upstream consumed a temp first.
 * Golden also emits `addu $a0, $t8, $t9` (base + offset) where we emit offset + base.
 *
 * SPELLINGS TRIED, none better (45-50 with the function placed first in the TU; the baseline
 * is 35 in ROM order -- BEWARE, moving a function within the TU changes its trailing
 * alignment padding and therefore its score, so only compare variants at the same position):
 *   f = &D_800E0A70[D_800E0A74]   /  f = D_800E0A70 + D_800E0A74
 *   no local at all, index at every use
 *   the index cached in an s32 local first
 *   f[1] hoisted into its own DemoFrame *n
 *   the two nested ifs collapsed into one &&
 *
 * PERMUTER RUN 2026-08-23 -- NEGATIVE RESULT, do not simply re-run it.
 * permuter_tu.sh setup + selftest PASSED all five checks (including (e), which confirmed a
 * plain single-function permuter would optimise different bytes here, so the TU-aware harness
 * is load-bearing). 3110 iterations, 3 workers, --stack-diffs, 52 outputs. Best permuter
 * score 305 against a 695 baseline; re-scored honestly in the real TU with fastscore that is
 * mism=32 against our 35 -- a 3-point move on a 44-row function, i.e. noise, not a crack.
 * Its transformation was legitimate (hoisting `f->unk01` and `f[1].unk02` into locals), it
 * just does not reach golden's allocation. If you retry, CHAIN from an output to break the
 * plateau rather than re-running from the same base, or attack a different member of the
 * delay-slot family first -- see memory/conker-delayslot-duplication-family.md.
 *
 * HARNESS GOTCHA that cost a cycle: selftest check (a) "head+region+tail == input TU" fails
 * with a whole-file `1,150c1,150` diff if the candidate TU has CRLF line endings. Writing the
 * candidate from Windows Python does exactly that. Convert to LF before setup; the failure
 * looks like a splicing bug and is not one.
 *
 * The record is 6 bytes: { s8 unk00; s8 unk01; u16 unk02; u16 unk04; } and the function
 * legitimately peeks at f[1].unk02 (the NEXT frame's field) -- that is not a stride error.
 * D_800BE9E4 is the frame-delta global (see memory/conker-actor-control-system.md).
 */
