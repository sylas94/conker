/*
 * NEAR-MISS: game_F44D0 / func_150C71C0 (400 bytes, 100 instructions)
 * BEST: fastscore mism=7, n=100/100.  (Previous note said 299 on the asm-differ
 * scale; the two residuals it described are now ONE.)
 *   Measure with: python3 tools/fastscore.py game_F44D0 func_150C71C0 <cand.c>
 *
 * ============================================================ BEST SOURCE (7)
 *   extern f32 D_800A0494;   // 0.4070000052   asm/data/244F50.rodata.s
 *   extern f32 D_800A0498;   // 0.02000000142
 *   extern f32 D_800A049C;   // 1.040000081
 *   extern f32 D_800A04A0;   // 0.1940000057
 *   extern f32 D_800A04A4;   // -0.3500000238
 *
 *   void func_151DB5D0(s32, f32 *, f32 *, f32, f32, f32, f32,
 *                      s32, s32, s32, s32, s32, s32, s32);
 *
 *   void func_150C71C0(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 arg4, void *arg5) {
 *       f32 sp54[3];
 *       s16 sp52;
 *       u8  r1;
 *       f32 scale;          <-- NEW THIS WAVE, worth 6 of the 13 rows
 *       f32 sp40[3];
 *
 *       scale = D_800A0494;
 *       sp54[0] = (arg1[0] - arg0[0]) * scale;
 *       sp54[1] = (arg1[1] - arg0[1]) * scale;
 *       sp54[2] = (arg1[2] - arg0[2]) * scale;
 *
 *       sp52 = (func_150ADA20() % 0x1FU) + 0x2A;
 *       sp40[0] = func_150ADA68();
 *       sp40[1] = func_150ADA68();
 *       sp40[2] = func_150ADA68();
 *       r1 = func_150ADA20();
 *
 *       func_151DB5D0(0, arg0, sp54, sp40[0] * 70.0f + 30.0f,
 *                     sp40[1] * D_800A0498 + D_800A049C, 1.0f,
 *                     sp40[2] * D_800A04A0 + D_800A04A4,
 *                     sp52, (r1 % 0x65U) + 0x9B, sp52,
 *                     0xFF / sp52, 1,
 *                     *((u8 *)arg5 + 0xC), *((u8 *)arg5 + 1));
 *   }
 *
 * ================================================= NEW LAW: $f0 IS A NAME TAG
 * IDO gives a NAMED f32 local $f0; anonymous expression temps start at $f6.
 * That was already in the cookbook as a fact about OUR output.  Use it in the
 * OTHER direction as a READING RULE on golden:
 *
 *     golden holds a value in $f0  =>  the original source had a NAMED f32
 *     local for it, even if the value is only ever a constant.
 *
 * Here golden holds D_800A0494 in $f0 across all three multiplies while every
 * other float sits in $f4/$f6/$f8/$f10/$f16/$f18.  Declaring `f32 scale` and
 * assigning it fixed SIX rows in one edit (13 -> 7), because...
 *
 * ============================ ...AND -g3 GIVES EVERY NAMED LOCAL A STACK SLOT
 * ...even one that is fully copy-propagated away and never touches memory.
 * `scale` is never stored, yet it still consumes 4 bytes of frame, and that is
 * what moved sp40[] from 0x44 to golden's 0x40.  So the frame formula
 *      frame = round8(outgoing_args + 8 + locals)
 * counts REGISTER-ONLY named locals too.  Corollary, and this is the useful
 * part: an unexplained 4/8-byte hole in a golden frame is a LOCAL DECLARATION
 * you have not written yet, not padding.  Reverse-engineer it by solving the
 * layout (locals flush to the top of the frame, declaration order at DECREASING
 * addresses, each at its natural alignment):
 *      sp54[3] f32 -> 0x54..0x5F
 *      sp52    s16 -> 0x52..0x53
 *      r1      u8  -> 0x51
 *      scale   f32 -> 0x4C..0x4F   (align 4 below 0x51)
 *      sp40[3] f32 -> 0x40..0x4B   <-- only lands here if `scale` exists
 * This ordering is FORCED: any other permutation of the five moves sp54 or sp52
 * off their golden offsets, or pushes sp40 below 0x40 and grows the frame.
 *
 * =============================================== THE ONE REMAINING RESIDUAL (7)
 * Pure intra-block scheduling.  Same 100 instructions, same registers, same
 * frame, same stack offsets; the pair {lui at, lwc1 $f0} sits at positions 1-2
 * in golden and 6-7 in ours:
 *   golden: addiu sp / lui at / lwc1 f0 / sw ra / sw a2 / sw a3 / lwc1 f4,0(a1) / lwc1 f6,0(a0)
 *   ours:   addiu sp / sw ra / sw a2 / sw a3 / lwc1 f4,0(a1) / lwc1 f6,0(a0) / lui at / lwc1 f0
 * Everything from instruction 8 to 99 is byte-identical.  Note golden's schedule
 * is locally WORSE (it leaves a load-use stall between `lwc1 $f6,0(a0)` and
 * `sub.s`), which ours fills with the constant load -- so golden's ucode had the
 * constant load already committed near the top of the block.
 *
 * SPELLINGS TRIED THIS WAVE (all still exactly 7, all with `scale` present):
 *   - `f32 scale = D_800A0494;` declaration initialiser instead of a statement
 *   - `scale * (arg1[i] - arg0[i])` operand swap
 *   - `(*arg1 - *arg0)` for component 0 instead of `arg1[0] - arg0[0]`
 *   - components computed in the order 0,2,1 (13 -- strictly worse, and it
 *     proves the source order IS 0,1,2)
 * PLUS everything in the previous note (loop form, struct-typed sp54, moving the
 * externs to the top of the TU) -- none of which are affected by `scale`.
 *
 * PERMUTER: 3336 iterations from this base reached 245 (base 275) and its best
 * candidate is REJECTED -- it moves `scale = D_800A0494;` to AFTER the first use
 * of `scale`, i.e. it reads an uninitialised variable.  That is UB, not a
 * spelling, and it only "works" by making the load a separate scheduling unit.
 *
 * BAIL SIGNATURE: single intra-block scheduling tie on a 2-instruction constant
 * load, flat at 7 rows across 10 honest spellings and 3336 permuter iterations.
 * REOPEN WITH: a model of IDO's list-scheduler priority that explains why a
 * %hi/%lo float constant load outranks the -g3 parameter-homing stores.  Cheap
 * next experiment: find a MATCHED function in the repo whose golden also puts a
 * `lui/lwc1` pair before `sw ra` and read its source.
 * Left as #pragma GLOBAL_ASM.  NOT FAKED.
 */
