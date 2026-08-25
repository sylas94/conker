/* tools/nearmiss/func_151D324C.c -- game_1FFF60.
 *
 * FILE KIND: STANDALONE TU (a note; splice the body over the pragma in src/game_1FFF60.c).
 *
 * STATUS 2026-08-23: mism=44 at the tree default, frame -0x18 (golden's), n=46/47.
 * Rows 0-12 are byte-identical; ONE missing instruction shifts everything after it.
 *
 * THE BODY (all three tail spellings score 44 -- prefer the plainest):
 *
 *   void func_151D324C(struct224 *arg0, struct223 *arg1, u8 arg2) {
 *       void (*fn)(struct224 *, struct223 *, u8);
 *       s32 temp_v0;
 *       s32 temp_v1;
 *
 *       if (arg2 == 0) {
 *           func_151D33FC();
 *       } else if (arg2 == 0x2D) {
 *           temp_v0 = arg1->unk0;
 *           temp_v1 = arg0->unk10;
 *           if (temp_v0 == temp_v1) {
 *               arg0->unk10 = arg1->unk4.w;
 *               arg0->unk14 = arg1->unk9;
 *           } else if (arg1->unk4.w == temp_v1) {
 *               arg0->unk10 = temp_v0;
 *               arg0->unk14 = arg1->unk8;
 *           }
 *       }
 *       fn = D_8008FC64[*((u8 *)arg0 + 0x1D)];
 *       if (fn != 0) {
 *           fn(arg0, arg1, arg2);
 *       }
 *   }
 *
 * The dispatch takes no argument setup -- golden's `jalr $v0` has a bare nop in its delay
 * slot -- because a0/a1/a2 still hold the incoming arguments. That is also why the arg2==0
 * path spills and reloads them around func_151D33FC. The (struct224 *, struct223 *, u8)
 * signature is the TU's own existing declaration of D_8008FC64, not a guess, and the
 * `*((u8 *)arg0 + 0x1D)` cast follows the already-matched func_151D2E5C in this same file.
 *
 * *** THE BLOCKER. *** Golden duplicates `lbu $t1, 0x1D($a0)` into FOUR branch delay slots,
 * one for each path into the dispatch, so its join label sits AFTER the load. We emit only
 * three: on the arg2==0 path we fill the `b` delay slot with the `lbu $a2, 0x23($sp)` reload
 * and branch to a shared copy of the load instead.
 *      golden:  lbu $a2, 0x23($sp) / b .L151D32D8 / lbu $t1, 0x1D($a0)
 *      ours:    b <shared lbu>     / lbu $a2, 0x23($sp)
 * REFUTED: fn in a local read once, no local read twice, an intermediate u8 index local;
 * if/else-if vs switch (switch is WORSE at the tree default, 51). Flags: -O2 = 48. Curiously
 * the switch form at -O2 gives 16 with n=47/47 -- the correct LENGTH -- but this TU has many
 * matched siblings at the tree default, so its flags are not available to change.
 *
 * PERMUTER RUN 2026-08-24 -- HARD NEGATIVE. permuter_tu.sh selftest PASSED all five checks
 * (base score 125, offset gate active). 8553 iterations, 3 workers, --stack-diffs, 285 errors,
 * and ZERO outputs: it never once beat the baseline. Do not simply re-run it.
 *
 * FAMILY -- READ THIS BEFORE SPENDING MORE TIME. This is the FOURTH function found in one
 * session whose entire residue is one instruction at a branch delay slot that golden keeps
 * and our IDO folds away:
 *      func_151DD140 / func_151DD4E0  a redundant `b` ending the last switch case
 *      func_151D3130                  a `bnel` with a speculatively duplicated `lb`
 *      func_151D324C                  a duplicated `lbu` in a `b` delay slot
 * All four have golden's frame and golden's every other instruction, and in all four the
 * source spelling has been swept hard (10, 6 and 3 variants respectively) without moving.
 * Treat it as ONE problem, not four. It is NOT a flag question: -O3, -O2 -g0/-g1/-g2,
 * -O1 -g3, -mips2 and -Wo,-loopunroll,0 were re-tested PER-TU and genuinely do not compile,
 * so the tree really only offers -O2 -g3, -O2, -O1, -g, -O0.
 */
