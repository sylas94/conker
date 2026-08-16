/*
 * NEAR-MISS: game_F4B20 / func_150C7670 (204 bytes, 51 instructions)
 * BEST: fastscore mism=58, n=50/51.  STRUCTURAL miss -- .text is 4 bytes short,
 * so verify_match.sh would fail this on SECTION SIZE.  Do not ship.
 *   Measure with: python3 tools/fastscore.py game_F4B20 func_150C7670 <cand.c>
 *
 * ============================================================== BEST SOURCE
 *   extern f32 D_800A04C0;                       // 2.29700017f, asm/data/244F80.rodata.s
 *
 *   typedef struct { u8 pad00[0x14]; u8 *unk14; } Mid150C7670;
 *   typedef struct {
 *       u8 pad00[0x70];
 *       u8 unk70;
 *       u8 pad71[0xFF];
 *       Mid150C7670 *unk170;
 *   } Obj150C7670;
 *
 *   s32 func_150C7670(Obj150C7670 *arg0) {
 *       f32 temp;
 *
 *       temp = arg0->unk170->unk14[0x2F];
 *       arg0->unk70 = temp * D_800A04C0;
 *       return 1;
 *   }
 *
 * ESTABLISHED (byte-identical): the whole arithmetic body, every integer and FP
 * register, every branch target and delay slot, both IDO unsigned conversion
 * templates (u8 -> f32 via mtc1/bgez/cvt.s.w + 2^32 fixup, and f32 -> u8 via
 * 0x4F000000 / |0x80000000), and the named-f32-local rule (`temp` must be the
 * PRE-multiply value so it lands in $f0; see func_150C71C0's note, where $f0 is
 * used as a READING RULE on golden).
 *
 * ================================================== THE RESIDUAL (unchanged)
 *   golden  0x08  addiu v0,zero,1     hoisted into the ENTRY block, between
 *                                     `lui at,0x4f80` and `lw t7,0x14(t6)`
 *           0xc0  nop                 the freed slot before `jr ra`
 *   ours    0xbc  addiu v0,zero,1     stays in the final block
 * i.e. golden's entry block had ONE MORE ready instruction than ours while
 * waiting on `lw t6,0x170(a0)` (golden fills 2 load-delay slots, ours 1).  The
 * return constant must be defined in the IR near the top of the function, not
 * at the `return`.
 *
 * ================================================ RULED OUT THIS WAVE (new)
 * 1. OPT FLAGS.  Screened the whole ladder with tools/fastscore.py monkeypatched
 *    (scratchpad flagscore.py).  NONE reaches 0, and -O2 -g3 is the best AND the
 *    only one with a plausible length:
 *        -O2 -g3   58  (n=50/51)   <-- keep, this is the TU's real flag set
 *        -O3 -g3   58  (n=50/51)
 *        -O2 -g2/-g1/-g   128 (n=59/51, and it grows a frame)
 *        -O2 / -O2 -g0    22  (n=49/51 -- LOWER mism but 2 instructions SHORT,
 *                              a textbook case of the score lying about shape)
 *        -O1 -g3   62  (n=53/51)
 *    So this is NOT a per-TU OPT_FLAGS override case.
 * 2. A SECOND PARAMETER.  `s32 func_150C7670(Obj *arg0, s32 arg1)` scores 4 with
 *    n=51/51 -- and that is a TRAP worth recording.  The length is only correct
 *    because IDO homes the unused param (`sw a1,0x4(sp)`) as instruction 0; the
 *    `li v0,1` is still stranded at the end.  Golden has no such store, which
 *    PROVES the signature takes exactly one argument.  Do not chase the 4.
 * 3. Return-value spellings, all 58 and all byte-identical to the base:
 *      `s32 ret = 1;` as a declaration initialiser, before or after `f32 temp`
 *      `register s32 ret = 1;`
 *      `s32 ret; ret = 1; ... return ret;`
 *      `return 1 != 0;`
 *      `if (1) { store } return 1;`
 *      house style: `void *arg0` + `(s32)arg0 + off` casts + `register` sub
 *        pointer (59, worse -- func_15154A88's style does not transfer)
 *    IDO copy-propagates every single-def constant back to the `return`.
 *
 * PERMUTER: 11796 iterations from this base produced NOTHING below 160 (its
 * scale).  This is the one target of the four where the permuter found no
 * foothold at all, consistent with the miss being a whole missing instruction
 * rather than a register tie.
 *
 * ============================================================= REOPEN WITH
 * The func_150163D0 law from this wave is the most promising lead:
 *   an instruction that survives where it looks redundant means TWO reaching
 *   defs, and two reaching defs come from a variable that is clobbered on one
 *   path.
 * Here the mirror question is: what makes IDO define the return value in the
 * ENTRY block?  The known-matched analogue func_150D88AC (game_105760.c) does
 * hoist it, and its source is an if/else -- i.e. a SOURCE-LEVEL branch, so the
 * `return 1` join has multiple predecessors at optimiser time.  Our function's
 * only branches are the float-conversion templates, which IDO expands AFTER the
 * optimiser, so at optimiser time it is a single basic block and `v0 = 1` is
 * last.  The reopen hypothesis is therefore: the original source contains a
 * source-level branch that IDO folded away, or a second `return 1`.  Enumerate
 * matched functions in the 0xF4xxx-0xF9xxx callback cluster whose golden hoists
 * `li v0,1` and check whether ALL of them have a source-level if/else.
 * Left as #pragma GLOBAL_ASM.  NOT FAKED.
 */
