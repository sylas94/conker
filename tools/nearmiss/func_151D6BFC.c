/* ============================================================================
 * func_151D6BFC  (game_203E20.c)  --  PARKED ONE INSTRUCTION SHORT.
 *   parked 2026-08-21; re-measured and re-diagnosed 2026-08-22 (pad-rule wave).
 *
 * FILE KIND: BODY-TO-SPLICE.  The text below (from the first `typedef` to the
 * final `}`) replaces exactly this one line of conker/src/game_203E20.c:
 *     #pragma GLOBAL_ASM("asm/nonmatchings/game_203E20/func_151D6BFC.s")
 * Nothing else in the TU is touched; the sibling pragma for func_151D69B4
 * stays.  Every typedef and extern needed is present below as LIVE C.
 *
 * SCORE (fastscore.py game_203E20 func_151D6BFC, in-file splice, -O2 -g3),
 * re-verified 2026-08-22 end to end from this committed file by the mechanical
 * splice a future wave would do:
 *     mism = 42      n = 152/153      frame = -168 (0xA8) == golden
 * Scored identically with the sibling pragma live AND with tools/nearmiss/
 * func_151D69B4.c spliced in beside it, so the two parks do not interact.
 *
 * *** THE 42 IS TWO DIFFERENCES, NOT 42 PROBLEMS. ***
 * Differing rows: 87, 88, 90, 91, 104, 112, 116, 118, and then 128..151.
 *
 *   (A) ONE MISSING INSTRUCTION at 128.  Golden has an extra `nop`; rows
 *       129..151 are nothing but the index shift it causes, and 104/112/116/118
 *       are the same four branches with their displacement off by one.
 *
 *           idx  ours                          golden
 *           126  mflo  $t0                     mflo  $t0
 *           127  sw    $t0,0x44($sp)           sw    $t0,0x44($sp)
 *           128  b     .L151D6E10              nop                 <-- THE DIFF
 *           129  lbu   $t6,0xAF($sp)  (delay)  b     .L151D6E10
 *           130  ...                           lbu   $t6,0xAF($sp) (delay)
 *
 *   (B) A 5-INSTRUCTION SCHEDULE PERMUTATION at 87..91 (rows 87,88,90,91).
 *       Same instruction multiset, different order.  THE PREVIOUS HEADER SAID
 *       "instructions 0..127 are byte-identical"; that was WRONG -- 0..86 and
 *       89 and 92..103 are identical, but 87/88/90/91 are not.
 *           idx  ours                        golden
 *           87   lui   $t2,%hi(D_800AB250)   lw    $v1,0xA8($sp)
 *           88   lw    $v1,0xA8($sp)         lui   $t2,%hi(D_800AB250)
 *           89   lw    $t2,%lo(D_800AB250)   lw    $t2,%lo(D_800AB250)
 *           90   addiu $t5,$zero,0x8         sw    $v1,0x3C($sp)
 *           91   sw    $v1,0x3C($sp)         addiu $t5,$zero,0x8
 *       (B) is INERT to everything tried: 7 statement orders of the msg-init
 *       block (including swapping msg.text and msg.unk04, which changes NOT ONE
 *       BYTE), 4 typings of D_800AB250, and every arm spelling.  It is probably
 *       the same root cause as (A) -- both are scheduling, both are immovable.
 *
 * ================= WHAT (A) IS, AND WHAT IT IS NOT =========================
 * THE PREVIOUS DIAGNOSIS WAS WRONG.  It called this an "R4300 mflo hazard pad"
 * because the build carries `-Wab,-r4300_mul`.  **THE FLAG HAS NOTHING TO DO
 * WITH IT.**  Building the same probe four ways -- `-Wab,-r4300_mul`,
 * `-Wb,-r4300_mul` (ugen only), `-Wa,-r4300_mul` (as1 only), and NO FLAG AT
 * ALL -- produces four BYTE-IDENTICAL objects, every pad included.  These nops
 * are unconditional IDO 5.3 `-mips2` codegen.  Do not chase the flag.
 *
 * The real rule (full derivation, corpus table and refutation list in
 * tools/ido_cookbook.md, section "THE mflo/mfhi PAD RULE, SOLVED"):
 *
 *   An mflo/mfhi must be followed by two instructions before its basic block
 *   ends.  If the block ends WITHOUT a branch -- falls through into a join
 *   label, or ends the function at `jr $ra` -- IDO appends nops to make up the
 *   shortfall.  If the block ends IN A BRANCH, no pad is added.
 *
 * Corpus check over all 2,387 asm/nonmatchings/*.s (2,699 mflo/mfhi sites):
 * 332 fall-through-terminated sites, of which 7 are padded 0->2 and 19 are
 * padded 1->2, and ZERO are left short.  715 branch-terminated sites have 0 or
 * 1 instructions before the branch and NO pad.
 *
 * PROVED IN-FILE ON THIS FUNCTION: delete the outer `else { msg.unk0C = 0; }`
 * so the `<3` arm falls through to the join, and the nop appears exactly where
 * golden has it (`mflo $t0 | sw $t0,68(sp) | nop | lbu $t6,175(sp)`).  Put the
 * else back and it vanishes.  So we can produce the nop ON DEMAND -- but only
 * by removing the branch, and golden HAS the branch.
 *
 * ============ WHY THIS FUNCTION IS A GENUINE ANOMALY =======================
 * Golden's padded block ends in an UNCONDITIONAL `b`.  In the entire game only
 * TWO of 2,325 branch-terminated sites are padded:
 *     game_18A8F0/func_1515E544.s  mflo;sw;nop;blez  (also un-decompiled)
 *     game_203E20/func_151D6BFC.s  mflo;sw;nop;b     (this one)
 * A byte-exact standalone replica of this function's tail -- same beqz+delay
 * load, multu, mflo/nop/nop/div, mflo, dependent store, unconditional `b`, and
 * tail-duplicated delay slot -- comes out UNPADDED.  So the shape is not
 * reachable from the C.
 *
 * REFUTED THIS WAVE (do NOT re-test; each has a probe that kills it):
 *   * conditional-branch terminator pads      -- probe t7 (`blez`, 1 real, none)
 *   * branch-LIKELY terminator pads           -- probe u6 (`bltzl`, 1 real, none)
 *   * tail-duplicated delay slot pads         -- probes t1/t8/t10/u7, none
 *   * nesting: innermost-last arm followed by the OUTER else -- probe fH, none
 *   * optimisation level (-O2, -O1, -O2 -g3)  -- none produces it
 *   * switch+break / do{}while(0)+break / goto out of the arm / empty else arms
 *   * 11 arm spellings, 7 msg-init orders, 4 D_800AB250 typings
 * Previously refuted and still refuted: the branch itself, the delay-slot
 * contents, the dependent store, and the mflo destination register.
 *
 * *** MEASUREMENT TRAP -- READ BEFORE BELIEVING A LOWER NUMBER ***
 * This variant scores mism=19 n=153/153 -- better on BOTH headline numbers --
 * and is STRICTLY WORSE:
 *     ...else if (temp < 3) { prod = msg.unk0C*temp; msg.unk0C = prod/3;
 *                             goto done; }
 *        goto done;
 *     }
 *     msg.unk0C = 0;
 *   done: ;
 * It turns `beqz $v0` into a branch-likely `beqzl` that swallows the null-path
 * store into its delay slot, losing an instruction EARLIER in the function;
 * that loss cancels the still-missing nop so rows 138..152 re-align by
 * coincidence.  Row 128 is untouched.  ALWAYS DUMP THE ROW INDICES.
 * (`chain-in-inner-if`, mism=27 n=153/153, is the same illusion.)
 *
 * ============================ DO NOT REPEAT =================================
 * Every one of these still prints mism=42 n=152/153 (i.e. changes nothing) or
 * is worse.  All measured in-file.
 *
 *  variant                                                          mism
 *  --------------------------------------------------------------  ------
 *  prod = n*temp; n = prod/3;              (SHIPPED)                  42
 *  n = (n * temp) / 3;                     inline                     42
 *  prod = n*temp/3; n = prod;                                         42
 *  prod = n; n = prod*temp/3;                                         42
 *  prod = temp * n; n = prod/3;            operands swapped           43
 *  prod = n*temp; q = prod/3; n = q;       extra quotient local       42
 *  n = (s32)((u32)prod / 3U);              unsigned                   43
 *  temp = snd->unk64; temp = temp + 1;     split increment            42
 *  temp <= 2 instead of temp < 3                                      42
 *  (u32)temp < 3U                                                     43
 *  temp == 1 || temp == 2                                             61  (n=155)
 *  !(temp >= 3)                                                       42
 *  n = n + 0x64 instead of n += 0x64                                  42
 *  msg.unk0C *= temp; msg.unk0C /= 3;      compound ops               53
 *  fully nested if/else instead of else-if chain                      42
 *  else-if chain wrapped in do{...}while(0) with breaks                42
 *  switch(temp) with case 0xFF / case 0 / default                     77  (frame 0xB0, wrong)
 *  extra `if (temp < 0)` after the arm     DOES produce a pad, w/ bgezl 51 (n=155)
 *  memcpy(*(void**)(ret+0x48), ...) inline instead of via `dst`       42
 *  6 declaration orders of the five scalars                           42
 *  msg.text / msg.unk04 assignment order   BYTE-IDENTICAL both ways   42
 *  msg.unk08 before msg.text                                          49
 *  msg.unk0C computed first                                           54
 *  D_800AB250 as u32 / as array elem / as *(s32*)&                    42  (all identical)
 *  msg.unk08 = msg.unk04->unk3B                                       42
 *  msg.unk08 = p.unk3C->unk3B                                         50  (n=153, wrong rows)
 *  msg.unk04 typed void*                                              42
 *  if (snd == NULL) {...} else {...}       inverted outer test        61
 *  void *ret declared BEFORE Params (i.e. ret at the top)             75
 *  whole struct accessed through a `Msg *mp` pointer local            96  (frame 0xB0, wrong)
 *  func_150859AC result hoisted into its own `amt` local              93  (frame 0xB0, wrong)
 *  separate `s32 text` + `Vars vars` locals instead of one Msg        42  (also exact frame)
 *  inner test inverted: if (temp != 0xFF) {..} else {+= 0x64;}        58
 *  second test inverted: if (temp != 0) {..} else {n = 0;}            53
 *  `else { if (temp < 3) ... }` instead of `else if`                  42
 *  7th argument passed as 0 instead of arg1  (diagnostic only)        51  (n=151/153)
 *  extra statement inside the <3 branch      (diagnostic only)        49  (n=154/153)
 *
 * ====================== FRAME ARITHMETIC (SOLVED, KEEP IT) ==================
 * Golden frame 0xA8 decomposes as
 *     0x00..0x1F  outgoing args (both calls take 8 args)
 *     0x20..0x27  saved $ra (0x24)
 *     0x28..0x37  FIVE named 4-byte scalars
 *     0x38..0x4B  Msg151D6BFC msg   (0x14)
 *     0x4C..0x4F  the fifth scalar, declared between `p` and `msg`
 *     0x50..0xA7  Params151D6BFC p  (0x58)
 * IDO gives the FIRST-declared local the HIGHEST address and charges 4 bytes
 * for every named local at -O2 -g3 even when it stays in a register, so the
 * declaration order below is load-bearing: p, ret, msg, snd, temp, prod, dst.
 * The first attempt used only three scalars (snd, ret, temp) and came out at
 * frame 0xA0 with every local 8 bytes low -- that is what `prod` and `dst`
 * fix.  BOTH ARE FULLY REFERENCED (prod holds the product, dst holds the
 * memcpy destination), so this is statement splitting, not dead filler; the
 * owner ruling on unreferenced bytes is not engaged.
 *
 * An equally exact alternative exists and is worth trying first next wave, in
 * case its different alias structure moves the nop: declare `s32 text;` and a
 * separate 0x10-byte `Vars vars;` instead of the single Msg struct
 * (order: p, ret, vars, text, snd, temp, prod, dst -> six scalars, vars at
 * 0x3C, text at 0x38).  It reproduces the same frame and the same mism=42.
 *
 * ================== HOW THE DATA MODEL WAS RECOVERED ========================
 *   * conker/src/game_1C0B10.c func_151938FC is the MATCHED TWIN of the whole
 *     first half: it builds the identical 0x58-byte `Struct151938FCParams`
 *     (same 0x220405 / 0x40200 / 0x80 / 0x20 / eight 0xFF constants, same
 *     obj-pointer-at-0x3C + obj->unk3B-at-0x40 + 1-at-0x41 tail) and the
 *     statement order used below is its statement order.
 *   * conker/src/game_17CAF0.c func_15152520 builds the same block again.
 *   * conker/src/game_183640.c holds the matched definition of func_15157010
 *     (u8 *arg0 is memcpy'd 0x58 bytes; arg2 is an f32 passed in a GPR).
 *   * conker/src/game_FC5F0.c holds the matched definition of func_150CFF10
 *     AND three matched sibling wrappers (func_150D0134 / func_150D02B4 /
 *     func_150D04C4) that supply the exact tail idiom used here:
 *         ret = func_150CFF10(...);
 *         if (ret != 0) memcpy(*(void **)((u8 *)ret + 0x48), &frame.unk0, N);
 *     In that callee, arg3 is the size of the object's variable block, which
 *     lands at ret+0x50 with a pointer to it stored at ret+0x48 -- hence the
 *     0x10 here matching the 0x10 bytes we memcpy.
 *
 * D_800AB250 IS NOT A POINTER.  asm/data/24FD10.rodata.s shows the word at
 * 0x800AB250 is 0x35303000, i.e. the 4-byte string literal "500" sitting just
 * before D_800AB254 = "$ %d" (already used by func_151D7000 in this TU).
 * Golden does `lui/lw` of the CONTENT and stores that word into the frame, so
 * the code copies the literal text "500" onto the stack and hands the stack
 * copy to func_150CFF10 as its text argument.  Declaring `extern s32
 * D_800AB250` is the type that reproduces the load; `extern u32`, an array
 * element, and `*(s32 *)&D_800AB250` all generate the IDENTICAL object.
 *
 * SEMANTICS: func_151D6BFC(obj, alpha, ctx) spawns one particle burst on obj
 * and then a floating "500" score popup whose amount is scaled by a global
 * counter (func_1509B570(0x83)->unk64 + 1: 0xFF adds 100, 0 zeroes it, 1 or 2
 * scale it by n/3).
 *
 * ===================== WHERE THE NEXT WAVE SHOULD GO ========================
 * NOT to game_215960/func_151EB06C.  The previous header sent the next wave
 * there as "the same idiom with the same pad, but simpler".  It IS the same
 * idiom, but its pad is the ORDINARY fall-through case --
 *     mflo $t8 ; sw $t8,0x90($sp) ; nop ; .L151EB4F8:
 * -- so it is not a blocker at all and teaches nothing about this function.
 * Whoever decompiles it gets the nop for free just by letting the arm fall
 * through to the join.
 *
 * For THIS function the honest position is: the rule is known, and golden's
 * shape (a padded block that ends in an unconditional `b`) is one of only two
 * such sites in the game and is not reachable from any C we can write.  The
 * two live leads left are (a) whatever makes difference (B) at rows 87..91 --
 * fix that and the tail may follow, since both are scheduling -- and (b) the
 * `s32 text` + `Vars vars` split noted above, which has a different alias
 * structure at the same exact frame.  Attack (B) first; it is 4 rows, it is
 * upstream of the nop, and no spelling tried so far has moved it at all.
 * ==========================================================================*/

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
} Vec3F151D6BFC;

typedef struct {
    /* 0x00 */ u8  pad0[0x3B];
    /* 0x3B */ u8  unk3B;
} Obj151D6BFC;

/* The 0x58-byte spawn parameter block func_15157010 memcpy's into its object.
   Identical to Struct151938FCParams in game_1C0B10.c. */
typedef struct {
    /* 0x00 */ u8  unk00;
    /* 0x01 */ s8  unk01;
    /* 0x02 */ u8  unk02;
    /* 0x03 */ s8  unk03;
    /* 0x04 */ s8  unk04;
    /* 0x05 */ u8  pad05;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ u8  unk2C;
    /* 0x2D */ u8  unk2D;
    /* 0x2E */ u8  pad2E[2];
    /* 0x30 */ u8  unk30;
    /* 0x31 */ u8  unk31;
    /* 0x32 */ u8  unk32;
    /* 0x33 */ u8  unk33;
    /* 0x34 */ u8  unk34;
    /* 0x35 */ u8  unk35;
    /* 0x36 */ u8  unk36;
    /* 0x37 */ u8  unk37;
    /* 0x38 */ u8  unk38;
    /* 0x39 */ u8  pad39[3];
    /* 0x3C */ Obj151D6BFC *unk3C;
    /* 0x40 */ u8  unk40;
    /* 0x41 */ u8  unk41;
    /* 0x42 */ u8  pad42[2];
    /* 0x44 */ Vec3F151D6BFC unk44;
    /* 0x50 */ u8  pad50[4];
    /* 0x54 */ s16 unk54;
    /* 0x56 */ s16 unk56;
} Params151D6BFC; /* 0x58 */

/* func_150CFF10's arg1: the message text ("500"), immediately followed by the
   0x10-byte variable block that is memcpy'd into the object's own buffer. */
typedef struct {
    /* 0x00 */ s32 text;
    /* 0x04 */ Obj151D6BFC *unk04;
    /* 0x08 */ u8  unk08;
    /* 0x09 */ u8  pad09[3];
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
} Msg151D6BFC; /* 0x14 */

typedef struct {
    /* 0x00 */ u8  pad0[0x64];
    /* 0x64 */ s32 unk64;
} Snd151D6BFC;

extern void *func_15157010(Params151D6BFC *, s32, f32, s32, s32, s32, u8, s32);
extern void *func_150CFF10(u8, s32, s16, s32, s8, u8, u8, void *);
extern Snd151D6BFC *func_1509B570(s32);
extern s32 D_800AB250;

void func_151D6BFC(Obj151D6BFC *arg0, u8 arg1, s32 arg2) {
    Params151D6BFC p;
    void *ret;
    Msg151D6BFC msg;
    Snd151D6BFC *snd;
    s32 temp;
    s32 prod;
    void *dst;

    p.unk38 = 0;
    p.unk00 = 0x27;
    p.unk01 = -1;
    p.unk02 = 3;
    p.unk03 = 1;
    p.unk04 = -1;
    p.unk06 = 0x96;
    p.unk08 = 0xA5;
    p.unk0C = 0x17;
    p.unk14 = 0x220405;
    p.unk18 = 0x40200;
    p.unk2D = 8;
    p.unk1C = 1;
    p.unk20 = 0x38;
    p.unk10 = 0;
    p.unk2C = 0;
    p.unk24 = 0x80;
    p.unk28 = 0x20;
    p.unk30 = 0xFF;
    p.unk31 = 0xFF;
    p.unk32 = 0xFF;
    p.unk33 = 0xFF;
    p.unk34 = 0xFF;
    p.unk35 = 0xFF;
    p.unk36 = 0xFF;
    p.unk37 = 0xFF;
    p.unk3C = arg0;
    p.unk40 = arg0->unk3B;
    p.unk41 = 1;
    p.unk44 = *(Vec3F151D6BFC *)&D_800A5480;
    p.unk54 = 8;
    p.unk56 = 0x1F;
    func_15157010(&p, 0, 1.0f, 0, 0, 0, arg1, arg2);

    msg.text = D_800AB250;
    msg.unk04 = arg0;
    msg.unk08 = arg0->unk3B;
    msg.unk10 = 8;
    msg.unk12 = 0x1F;
    msg.unk0C = func_150859AC(0, 6);

    snd = func_1509B570(0x83);
    if (snd != NULL) {
        temp = snd->unk64 + 1;
        if (temp == 0xFF) {
            msg.unk0C += 0x64;
        } else if (temp == 0) {
            msg.unk0C = 0;
        } else if (temp < 3) {
            prod = msg.unk0C * temp;
            msg.unk0C = prod / 3;
        }
    } else {
        msg.unk0C = 0;
    }

    ret = func_150CFF10(0x63, (s32)&msg, 0x96, 0x10, 3, 1, arg1, arg2);
    if (ret != 0) {
        dst = *(void **)((u8 *)ret + 0x48);
        memcpy(dst, &msg.unk04, 0x10);
    }
}
