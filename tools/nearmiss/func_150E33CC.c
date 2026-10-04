/* tools/nearmiss/func_150E33CC.c -- game_1104D0, 18 instructions, frame -0x18
 *
 * STATUS: mism=9, n=18/18 (EXACT LENGTH), FRAME EXACT.  Cold decompile 2026-08-26.
 *
 * WHAT IT IS: a CALLBACK -- src/game_1104D0.c:92 passes `(s32)func_150E33CC` to
 * func_1000FA64, which is why it has four parameters and uses only the third.  The TU's
 * own forward declaration `extern void func_150E33CC(void);` (line 85) is WRONG and must
 * be dropped/replaced when this ships.  `func_1000E7A0(u32, s32)` is prototyped in
 * src/game_AC030.c:238 and defined in src/init_B1B0.c:1033.
 *
 * THE THREE HOME-SLOT STORES ARE FREE.  `sw $a0,0x18($sp)` / `sw $a1,0x1C($sp)` /
 * `sw $a3,0x24($sp)` (and NOT $a2, which is dereferenced) fall straight out of declaring
 * four parameters and using only arg2 -- rows 0-4 match with no coaxing.  Do not read them
 * as a varargs prologue.
 *
 * ---------------------------------------------------------------- SCORE LADDER (measured)
 *   22  n=17/18 -- `if (*arg2 == 0) return 1; func_1000E7A0(2, *arg2); return 0;`
 *       and every straight-line variant of it: a named `s32 v` local, `if (!v)`, a
 *       `void **arg2` + NULL test + `(s32)` cast, `2U`, `arg2[0]` at the call, a separate
 *       `s32 w = 2` for the first argument, and the inverted `if (v != 0) {call; return 0;}
 *       return 1;`  ALL 22 -- IDO loads straight into $a1 and the copy never appears.
 *    9  n=18/18 -- ANY shape that puts the call INSIDE AN `else` ARM.  Confirmed with three
 *       independent spellings: `v`+`ret` locals; `ret` declared first; the single `v`
 *       reused as the result; and `if (v != 0) {call;} else {return 1;} return 0;`
 *       That is what buys the 18th instruction (`or $a1,$v0,$zero`) and hoists
 *       `addiu $a0,$zero,2` above the branch.                              <-- PARKED
 *
 * ---------------------------------------------------------------- WHAT IS LEFT (ONE CAUSE)
 * The loaded value must live in $v0, not $a1:
 *      ours:   lw $a1,0($a2) ... bne $a1 ... addiu $a1,$zero,1 ... or $v0,$a1,$zero
 *      golden: lw $v0,0($a2) ... bne $v0 ... addiu $v0,$zero,1 ... or $v0,$zero,$zero
 * i.e. IDO COALESCES our local into the outgoing argument register and golden does not.
 * All nine remaining rows are that one decision.  `register`, `volatile` (57, worse),
 * u32 vs s32, and an explicit `(s32)` cast at the call site do not break the coalescing.
 * Whatever makes IDO pin the loaded value to the return register closes this.
 */

s32 func_150E33CC(s32 arg0, s32 arg1, s32 *arg2, s32 arg3) {
    s32 v;
    s32 ret;

    v = *arg2;
    if (v == 0) {
        ret = 1;
    } else {
        func_1000E7A0(2, v);
        ret = 0;
    }
    return ret;
}
