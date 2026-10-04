/* tools/nearmiss/eeprom_switch_b.c -- osEepromRead + osEepromWrite.
 *      func_151DD140  osEepromRead   (game_20A5F0)  mism=47, frame -0x80, n=113/113
 *      func_151DD4E0  osEepromWrite  (game_20A990)  mism=38, frame -0x48, n=95/95
 * BOTH now have golden's EXACT FRAME AND EXACT LENGTH (was 101 / 85, both one instruction
 * short). What remains is the dispatch shape only.
 *
 * *** HOW THE MISSING INSTRUCTION WAS FOUND -- THE METHOD MATTERS MORE THAN THE RESULT. ***
 * The permuter failed hard on this family (see memory/conker-delayslot-duplication-family.md:
 * 3110 iterations for one member, 8553 with ZERO outputs for another). What worked was
 * scanning the 683 ALREADY-MATCHED functions for golden asm that contains the construct we
 * were missing, then reading their C. tools/nearmiss/_findb.py does this: 87 matched
 * functions contain a `b` to the label that is literally the next instruction.
 * game_981E0's func_1506C32C is the clearest worked example, and its C is a plain
 * if/else-if chain assigning a variable:
 *      if (a != 0) index = 4; else if (b != 0) index = 3; else if (c != 0) index = 2;
 *      else index = 0;
 * A SWITCH does not produce it; the CHAIN does.
 *
 * *** AND A PROCESS ERROR WORTH NOT REPEATING. *** if/else-if had already been swept here and
 * dismissed at 141 -- but that sweep ran BEFORE the frame was corrected, so it was scored
 * against the wrong local layout. The frame fix and the structure sweep INTERACT: after
 * changing the declaration set, re-run the structure sweep. Doing so took 101 -> 47.
 *
 * THE SHAPE THAT WORKS (note the empty first arm -- `if (ret == 0) { if/else-if }` gives 140,
 * the flat chain gives 47):
 *      if (ret != 0) {
 *      } else if ((sdata.type & 0xC000) == 0x8000) {
 *          if (address >= 0x40)  { ret = -1; }
 *      } else if ((sdata.type & 0xC000) == 0xC000) {
 *          if (address >= 0x100) { ret = -1; }
 *      } else {
 *          ret = 8;
 *      }
 *
 * DECLARATION SETS (derived from the frames, not guessed -- the two functions DIFFER):
 *   func_151DD140: FOUR word scalars, sdata BEFORE eepromformat
 *      OSMesg dummy; s32 ret = 0; s32 i; u8 *ptr; OSContStatus sdata; __OSContEepromFormat f;
 *      -> sdata 0x3C, eepromformat 0x30, ret 0x4C, frame 0x50
 *   func_151DD4E0: FOUR word scalars, eepromformat BEFORE sdata
 *      s32 ret = 0; s32 i; u8 *ptr; OSMesg dummy; __OSContEepromFormat f; OSContStatus sdata;
 *      -> sdata 0x2C, eepromformat 0x30, ret 0x44, frame 0x48
 *   Without the 4th scalar the write side drops to frame 0x40 and scores 47 instead of 38.
 *
 * SCANNER VALIDATED. _findb.py calls a function "matched" if it has no #pragma; that is an
 * assumption, and one of its hits (game_16EE20/func_151462C8) even has a stale
 * `# nonmatching` header in its .s file. Scored it directly: mism=0, n=124/124. The set is
 * sound -- but re-verify any hit before trusting it, the header comments lie.
 *
 * NARROWED HIT LIST: 9 of the 87 have BOTH a switch-style forward dispatch and a redundant
 * `b`. The closest in shape to the eeprom pair is game_16EE20/func_151462C8 (2 forward beq,
 * 1 redundant `b` carrying an assignment). Its C wraps the switch in `do { ... } while (0);`
 * and carries a stray `do { } while (0);` between two cases, plus `case 0:` sharing the
 * default body. REFUTED here, all still 101/n=112: switch inside do{}while(0), a stray
 * do{}while(0) before the default, after the default, and both together. A third case sharing
 * the default body is not viable either -- golden has exactly TWO compares in its dispatch,
 * and any extra case adds one.
 *
 * *** THE DISCRIMINATOR, FOUND 2026-08-24 -- START HERE. ***
 * game_83300/func_1506045C is a MATCHED function whose switch retains the redundant `b` on
 * its LAST case body, in exactly the shape we want:
 *      addiu $s0, $zero, 0xE        default, at the dispatch fallthrough
 *   .L15060640:
 *      b     .L15060650
 *      addiu $s0, $zero, 0x1B       case 0x23 / 0x8A
 *   .L15060648:
 *      b     .L15060650             <- RETAINED on the physically-last body
 *      addiu $s0, $zero, 0x8        case 0xC
 *   .L15060650:
 * Its C (src/game_83300.c ~line 1464):
 *      switch (D_800CC2D0[idx - 1].id) {
 *      case 0x23: case 0x8A: state = 0x1B; break;
 *      case 0xC:            state = 8;    break;
 *      case 0x28:           state = 0;    break;
 *      default:             state = 0xE;  break;
 *      }
 *
 * DIFFERENCE FROM OURS: every case body is a PLAIN CONSTANT ASSIGNMENT. The eeprom's bodies
 * are `if (address >= K) { ret = -1; }` -- a NESTED CONDITIONAL, which itself branches to the
 * join, and that is what lets IDO fold the trailing `b` away. That is a testable hypothesis
 * and it is the first concrete one this family has had:
 *   **plain-assignment case body -> `b` retained; case body containing an `if` -> `b` folded.**
 *
 * NEXT EXPERIMENT (not yet run): find a spelling that keeps the semantics but takes the
 * conditional OUT of the case body while preserving golden's per-case `slti`/`bnez` -- e.g.
 * hoisting the range test so each case is a straight assignment. Verify against golden's asm
 * first: golden DOES have the `slti` inside each body, so any rewrite must still produce that.
 * If no such spelling exists, this is a bail, not a near-miss. Do NOT pad with a no-op.
 *
 * *** SHARPER CHARACTERISATION (supersedes the paragraph below). *** Dumping the switch and
 * the goto forms side by side shows the split is NARROWER than "switch head vs chain bodies":
 *   - The SWITCH form already reproduces golden's dispatch EXACTLY, including the detail that
 *     matters most: `address` is loaded TWICE into two different registers and HOISTED into
 *     the dispatch's spare slots (golden rows 18 and 23, one per case body), forward beq to
 *     each body, default falling through. Its ONLY defect is the missing trailing `b`.
 *   - The GOTO form (a literal transcription of golden's layout) fixes the length but does
 *     NOT hoist: each body loads `address` itself. It scores 42, better than the chain's 47,
 *     and still not 0 -- proving LAYOUT ALONE IS NOT THE REMAINING ISSUE.
 * So the target is: keep the switch (which already has the hoisting and the dispatch) and
 * find what makes IDO retain the `b` on its LAST case body. Everything else is already right.
 * The goto form is a DIAGNOSTIC only -- do not ship it; it is not what libultra source says.
 *
 * SUPERSEDED NOTE -- REMAINING RESIDUE: the DISPATCH. Golden branches FORWARD to each case body and falls through
 * to the default (switch-style: `beq $t7,$at,.L1A8` / `beq $t7,$at,.L1BC` / `b .L1D0` +
 * `addiu $a0,$zero,8`). The if/else-if chain instead emits inverted tests with the bodies
 * inline (`bne` + fallthrough). So golden wants a SWITCH dispatch head with CHAIN body
 * termination. The switch spelling gives the right head and loses the trailing `b`; the chain
 * gives the right bodies and the wrong head. That is the last question on both functions.
 * Do NOT reach for `else { ret = ret; }` or similar no-ops to pad a delay slot -- that is a
 * forcer; see memory/conker-fake-match-policy.md.
 */
