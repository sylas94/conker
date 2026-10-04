/* tools/nearmiss/func_151D3130.c -- game_1FFF60, walk arg0's child list and dispatch.
 *
 * FILE KIND: STANDALONE TU (a note; splice the body over the pragma in src/game_1FFF60.c).
 *
 * STATUS 2026-08-23: mism=24 at the tree default, frame -0x30 (golden's), n=48/49.
 * Only ONE instruction missing, and every other row before it is golden's.
 *
 * THE BODY (scores 24; the variant with a named `s8 index` local scores 25, so prefer this):
 *
 *   void func_151D3130(struct224 *arg0) {
 *       struct224 *obj;
 *       struct224 *next;
 *       void (*fn)(struct224 *);
 *
 *       fn = D_8008FC5C[*((u8 *)arg0 + 0x1D)];
 *       if (fn != 0) {
 *           fn(arg0);
 *       }
 *       obj = (struct224 *)arg0->unk24;
 *       while (obj != 0) {
 *           next = (struct224 *)obj->unk40;
 *           if (*(s8 *)((u8 *)obj + 0x2A) != -1) {
 *               D_8008FC48[*(s8 *)((u8 *)obj + 0x2A)](obj, (Func151D2C40Data *)&obj->unk34);
 *           }
 *           *(s32 *)((u8 *)obj + 0x2C) = 0;
 *           func_1516972C((struct102 *)obj);
 *           obj = next;
 *       }
 *       func_1514EDF0(arg0, arg0->unk10);
 *   }
 *
 * struct224 in include/structs.h does not describe 0x1D or 0x2A (0x2A falls inside its
 * `s32 unk28`). The byte-offset casts above are NOT a workaround I invented -- the
 * already-matched sibling func_151D2C40 in this same file reads the identical field as
 * `*(s8 *)((u8 *)arg0 + 0x2A)`. Fixing the header would be better but must be re-scored
 * across every TU that uses struct224; see memory/conker-header-inaccuracies.md.
 *
 * *** THE BLOCKER: golden SOFTWARE-PIPELINES the child loop and we do not. *** Golden ends it
 *      or   $s0, $s1, $zero          obj = next
 *      bnel $s1, $zero, .L151D318C   branch-LIKELY, so the delay slot is conditional
 *      lb   $v0, 0x2A($s0)           next iteration's index, loaded speculatively
 * with the loop head at `lw $s1, 0x40($s0)` and a second copy of the `lb` in the preheader.
 * We hoist the `lb` into the preheader too, but then branch back TO it, filling the delay
 * slot with the induction update:
 *      bnez $s1, <the lb>
 *      move $s0, $s1
 * -- one instruction shorter. IDO chose branch-likely in golden precisely because the
 * speculative `lb` would fault on the NULL that ends the list.
 *
 * REFUTED: while / do-while / do-while testing `next` / for-with-obj=next-as-increment, and
 * both orders of the two loads in the body -- all six land on 25. Flags: -O2 = 34,
 * -O1 = 45 but with n=49/49 (the length becomes right, the register rotation goes wrong),
 * -g = 159, -O0 = 179. -O3, -O2 -g0/-g1/-g2, -O1 -g3, -mips2 and -Wo,-loopunroll,0 do not
 * compile at all in this tree -- verified per-TU, not just from a whole-tree build.
 *
 * DO NOT hand-pipeline the source to force this. Writing `obj = next; index = obj->unk2A;`
 * at the bottom of the loop reads through the NULL that terminates it -- that is not what
 * the original source can have said, and it is exactly the kind of forcer the policy in
 * memory/conker-fake-match-policy.md exists to reject. The honest lever is the permuter.
 *
 * FAMILY: this is the THIRD function this session whose whole residue is one instruction at
 * a delay slot where golden keeps a branch IDO folds away for us -- see
 * tools/nearmiss/eeprom_switch_b.c for the other two. Worth attacking as one problem.
 */
