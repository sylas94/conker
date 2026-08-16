/* game_CB1C0 / func_1509DDFC -- PARKED at 225. BAIL SIGNATURE CONFIRMED.
 *
 * Model + spellings are in the comment above the pragma in conker/src/game_CB1C0.c.
 * A previous wave had already reached this same state and diagnosed it correctly; this
 * pass re-derived it independently, confirmed the diagnosis, and then tried to break it.
 *
 * THE ENTIRE RESIDUAL IS ONE DELAY SLOT:
 *
 *   golden                       ours (225)
 *   108: beq  a1,at,case1        108: beq  a1,at,case1
 *   10c:  move v0,zero           10c:  lw   t2,0x28(sp)     <- target block's first insn
 *   110: b    end                110: b    end
 *   114:  nop                    114:  move v0,zero
 *   ...                          ...
 *   178: lw   t2,0x28(sp)        178: (already consumed)
 *
 * Golden fills the `beq` delay slot from the FALL-THROUGH block (the default path's
 * `v0 = 0`), which leaves nothing for the following `b` and costs golden a `nop` -- so
 * golden is 4 bytes LONGER than our version. We fill it from the BRANCH TARGET (the
 * speculative, always-safe stack reload of arg0) and then still have `move v0,zero` left
 * for the `b`. Both are legal; IDO simply preferred the fall-through candidate.
 *
 * BAIL EVIDENCE -- four honest spellings, and the score does not move where it matters:
 *    225  switch, `return 1` per case, `return 0` after the switch
 *    225  switch with an explicit `default: return 0;`
 *    990  dropping the redundant `& 0xFF` (both callees are already prototyped u8)
 *    705  `break` per case with a common `return 1` after the switch
 * The two spellings that leave the IR shape alone give the identical number; the two that
 * change it are far worse. That is the allocator/scheduler-tie signature: the structure
 * is right and the last hop is not reachable by rewriting the source.
 *
 * EVERYTHING ELSE MATCHES EXACTLY, including the 812-byte (0x32C) stride expansion of
 * D_800CC2D0 into shift/add/sub chains, the `+0x14` x_position offset, `lh a2,0xe(s0)`,
 * and both call argument sets. Do not re-derive the model; attack the scheduler.
 *
 * WORTH TRYING NEXT: whether any OTHER matching function in the tree has a two-case
 * switch whose default is `return 0` and whose case bodies begin with a stack reload --
 * if one exists and matches, diff its source against this one. That is the only lever
 * left short of a compiler-behaviour finding.
 */
