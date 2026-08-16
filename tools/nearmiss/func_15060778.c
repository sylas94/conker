/* func_15060778 (game_83300.c) -- best 1948  (was 2878; -R and no -R agree, real make path).
 *
 * WHAT CHANGED 2026-08-11 (2878 -> 1948, two independent honest levers)
 * --------------------------------------------------------------------
 *   1. func_10010BE8's first argument spelled `0xFFFF & id` instead of `(u16)id`
 *      -- 2878 -> 2103.  func_10010BE8 is the ONE callee here whose first parameter is
 *      s32 (functions.h:980); every other call site converts implicitly to a u16
 *      parameter.  Writing that one conversion as an s32 AND instead of a cast stops IDO
 *      pooling all six conversions into a single long-lived web, and THAT is what stops
 *      the web being promoted to a callee-saved register.  Structural rows 18 -> 11.
 *      Golden's `sw a0,0x44(sp)` / `lw a0,0x44(sp)` spill pair appears for the first time,
 *      and only $s0 is saved (golden saves only $s0 too; the old C saved $s0 AND $s1).
 *   2. That same argument's third operand written `(flags * 50) + arg2` rather than
 *      `arg2 + (flags * 50)` -- 2103 -> 1948.  Operand order only, at ONE site.
 *
 * Lever 2 is the honest half of decomp-permuter output-1955; the permuter shipped it
 * wrapped in a banned `u16 *new_var = &arg1->unk8E; dest = new_var;` split.  The honest
 * half ALONE (1948) beats the permuter's own output WITH the forcer (1960).
 *
 * REMAINING RESIDUAL -- one decision, and everything else cascades from it
 * -----------------------------------------------------------------------
 * Golden computes `(u16)id` in EACH of the four switch predecessors (into $a0, in the
 * `b` delay slots) and the tail then consumes $a0 with no further masking.  This C keeps
 * the RAW id live into the merge block and masks it there, so:
 *   - the raw id needs a 4th call-crossing spill slot (0x5c)  => frame 0x60 vs 0x58;
 *   - `flags` and the raw id swap registers ($v1 <-> $t0) -- ~34 register-only rows;
 *   - golden's `bne a0,v0` + its own `b`/`andi` block for the mode==2 exit becomes a
 *     plain `beq v0,a0` fallthrough here (1 delete, 1 replace).
 * Kill the 4th spill and the frame, the register swap and the branch shape all follow.
 *
 * MEASURED, ALL ON THE REAL MAKE-PATH OBJECT (score / frame; golden frame = 0x58)
 * -----------------------------------------------------------------------------
 * Per-call-site spelling of the id argument.  Sites: S1 func_1001147C, S2 func_1000F91C,
 * S3/S4 func_1000F85C, S5 func_10010E78, S6 func_10010BE8.
 *   S1-S5 `id`,          S6 `(u16)id`        2878  0x50   <- the old parked C
 *   S1-S5 `(u16)id`,     S6 `(u16)id`        2878  0x50   (explicit casts are a no-op)
 *   S1-S5 `id`,          S6 `id`             5272  0x60
 *   S1-S5 `id`,          S6 `0xFFFF & id`    2103  0x60   <- lever 1
 *   S1-S5 `id`,          S6 `id & 0xFFFF`    2103  0x60   (AND operand order: neutral)
 *   S1-S5 `id`,          S6 `(u16)(id&0xFFFF)` 2575 0x60
 *   S1 `0xFFFF & id`, rest `id`, S6 `(u16)id`  3339 0x50
 *   S5 `0xFFFF & id`, rest `id`, S6 `(u16)id`  2894 0x60
 *   S1-S5 `0xFFFF & id`, S6 `0xFFFF & id`    2864  0x60
 *   S1-S5 `0xFFFF & id`, S6 `(u16)id`        3405  0x60
 *   S5 and S6 both `0xFFFF & id`             2894  0x60
 * Declared type of id (on the lever-1 base):  u16 6366/0x50, u32 2103/0x60, s32 2103/0x60.
 *   `u16 id` is a trap: it scores 6366 with 97 register-only rows because it rotates the
 *   whole t-register pool.  IDO re-emits the narrowing `andi a0,<reg>,0xffff` at every
 *   call site even for an already-u16 variable, so declaring it u16 buys nothing.
 * Declaration order (lever-1 base): id first 2103, id third 2135, id last (on the old
 *   base) 3070/0x48.  `handle` as s32 2496.  `flags` as u32 2103 (no change).
 * Statement order: `mode = arg6 & 3;` hoisted above the flags if/else 2103 (no change);
 *   `dest = NULL;` before `id = 0;` 2108.
 * A separate `u16 sid` carrier assigned in each switch arm: 2652 / 0x60, and it is
 *   INSTRUCTIVE -- it gets the register allocation almost exactly right (only 3
 *   register-only rows, `flags` lands in golden's $t0) but IDO MEMORY-HOMES the u16
 *   carrier (`sh v0,0x4c(sp)` / `lhu a0,0x4c(sp)`), which golden does not do.  Golden
 *   spills its carrier with `sw`/`lw`, i.e. it is a 32-bit compiler temp, not a u16 local.
 * Operand order elsewhere (on the 1948 base, all neutral or worse):
 *   `(flags*50) + arg2` at every site 2660; at S5+S6 1998; at S4 only 1998;
 *   `50 * flags` 1948; `arg3 + (arg1->unk13F * 10)` 1948.
 *
 * SETTLED, DO NOT RE-PROBE
 * ------------------------
 *   - `== arg0 & 0x7FFF` is a real C precedence bug in the original (`==` binds tighter
 *     than `&`), giving xor/sltiu/andi 0x7FFF.  `(func_1001147C(id) == arg0) & 0x7FFF` is
 *     the SAME parse and compiles identically; `== (arg0 & 0x7FFF)` would not match.
 *   - `if (mode == 2) { break; }` (early break) is what produces the
 *     `bne a0,v0 -> case-3 body` layout; an `if (mode != 2) {...}` wrapper gives beq.
 *   - s32 id + implicit u16 param conversions is what makes the raw id die before the
 *     call (target reuses v1 for arg0 right after func_1001147C).
 *   - Also previously tried and rejected: explicit (u16) casts at 0/1/all call sites,
 *     48 declaration-order permutations, split id/cur variables, `register`, tail
 *     duplication.
 *
 * CORPUS EVIDENCE FOR THE RESIDUAL (569,790 lines of disassembly, 5,479 live-C functions)
 * --------------------------------------------------------------------------------------
 * Golden's decision -- hold a value in an ARGUMENT register across a call and spill it to
 * a COMPILER TEMP slot rather than promote it to a callee-saved register -- occurs in only
 * 42 of 5,479 live-C functions, and in ZERO of them is the spilled value the result of a
 * narrowing mask.  Golden does it twice in this one function.  So there is corpus-level
 * reason to believe no C in this tree has ever produced this pattern, in the same sense as
 * func_150585F0's computed-$f14 finding.  Before spending more here, grep the corpus.
 *
 * PERMUTER STATUS
 * ---------------
 * game_83300 is USABLE (all five selftest checks pass; round-trip sha1 == makefile sha1).
 * Two runs, ~700 gated iterations (PERMUTER_TU_MAX_FRAME=96 -- an exact
 * PERMUTER_TU_REQUIRE_FRAME=88 gate is unusable here because NO known base reaches 0x58;
 * the frame only becomes 0x58 once the residual above is solved, so it gates the answer,
 * not the search).  Every output that beat the base did so with a banned construct:
 *   output-1782  `id = arg2;` reused a LIVE variable -- semantically WRONG (it changes
 *                func_10010BE8's third argument from arg2+flags*50 to id+flags*50).
 *   output-1955  `u16 *new_var = &arg1->unk8E; dest = new_var;`  (honest half extracted)
 *   output-1915  `(new_var = arg2)` assigned only on a path that always returns, then READ
 *                in the tail -- uninitialised.  Semantically WRONG.
 *   output-1919  `u8 *new_var = &arg1->unk13F;` for a SINGLE use -- pure register forcer.
 * All rejected.  The permuter has no structural handle here; the next lever, if there is
 * one, has to make the u16 conversion happen per-predecessor without a memory-homed local.
 */
s32 func_10010E78(u16 arg0, s32 arg1, u16 arg2, s16 arg3, u8 arg4, s32 arg5,
                  s16 arg6, s16 arg7, s16 arg8, s16 arg9, s16 argA);

void func_15060778(s32 arg0, struct127 *arg1, u16 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 id;
    u16 *dest;
    s32 flags;
    s32 mode;
    u16 handle;

    id = 0;
    dest = NULL;
    if (arg6 & 8) {
        flags = 0;
    } else {
        flags = ((u32)arg1->unk184 >> 3) & 0x30;
    }

    mode = arg6 & 3;
    switch (mode) {
    case 1:
        dest = &arg1->unk8C;
        id = arg1->unk8C;
        break;
    case 2:
    case 3:
        dest = &arg1->unk8E;
        id = arg1->unk8E;
        if (mode == 2) {
            break;
        }
        if (func_1001147C(id) == arg0 & 0x7FFF) {
            if (arg6 & 4) {
                func_1000F91C(id, arg2 + (flags * 50), (arg1->unk13F * 10) + arg3, flags, 0,
                              arg1->x_position, arg1->y_position, arg1->z_position, arg4, arg5);
            } else {
                func_1000F85C(id, 0x10, arg3);
                func_1000F85C(id, 8, arg2 + (flags * 50));
            }
            return;
        }
        arg0 |= 0x8000;
        break;
    }

    if (arg6 & 4) {
        handle = func_10010E78(id, arg0, arg2 + (flags * 50), arg3, flags, 0,
                               arg1->x_position, arg1->y_position, arg1->z_position, arg4, arg5);
    } else {
        handle = func_10010BE8(0xFFFF & id, arg0, (flags * 50) + arg2, 0x40, arg3, flags, 1);
    }
    if (dest != NULL) {
        *dest = handle;
    }
}
