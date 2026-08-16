/* ====== PARKED -- NEAR MISS, mism 65 / SHAPE_MISS 0 / 150 instructions ======
 * func_151CC524  (game_1F4650.c, 600 bytes, frame 0xE0)      wave 2026-08-17
 * SPAWNER CORPUS CAMPAIGN.  Read with func_151CC840.c.  The SOURCE BELOW IS
 * UNCHANGED from 2026-08-16 -- it is still the best position and no spelling
 * found this wave beats it.  What changed is that the residual is now NAMED,
 * MEASURED and REPRODUCED, and one of the two readings carried since 2026-08-16
 * has been REFUTED.  The #pragma GLOBAL_ASM is STILL LIVE; nothing in
 * conker/src was changed for this function.
 *
 * ==========================================================================
 * THE RESIDUAL, PROVEN: GOLDEN'S BLOCK 0 ALLOCATES THREE MORE INTEGER TEMP
 * WEBS THAN OURS, AND THOSE THREE WEBS EMIT NO INSTRUCTIONS.
 * ==========================================================================
 * Everything else about this function is now accounted for.  idx0..idx23 (the
 * whole of block 0, up to and including the flag branch) is byte-identical to
 * golden.  From idx24 to the end every differing row is the same instruction
 * with the register renamed, and the renaming is ONE uniform rotation, ours+3:
 *     t0->t3 t1->t4 t2->t5 t3->t6 t4->t7 t5->t8 t6->t9 t7->t0 t8->t1 t9->t2
 *     (74 of 74 register pairs)
 *
 * THE POSITIVE CONTROL, and it is the important measurement of the wave.
 * Add THREE ordinary integer stores to block 0 -- any three; the probe used
 *     sp2C.unkC = arg1;  sp2C.unkD = arg2;  sp88.unk1B = arg3;
 * -- and the ENTIRE register assignment from the join block to the end becomes
 * golden's, exactly, merely displaced by the 4 instructions the probe stores
 * cost (n 150 -> 154):
 *     lw $t3 (reserved)  li1 $t6  ori $t2  lbu $t4  addiu $t5  sllv $t7
 *     or $t8  unk16 $t9  unk1A $t1  unk1E $t2  unk18 $t0 SHARED with unk22
 *     and the five `li 255` at t7/t8/t9/t0/t1
 * Every one of those is golden's register.  So the remaining problem is not
 * "which registers" and not "the shape" -- it is exactly three temp webs.
 *
 * THE PHASE LADDER (each +/-1 integer web in block 0 == +/-1 pool slot).
 * Read the register the `ori rt,$v0,0x390` lands in; golden's is $t2:
 *     one FEWER web  (sp2C.unk0 = NULL) ....... ori $t8
 *     THIS SOURCE ............................. ori $t9
 *     +1 integer store in block 0 ............. ori $t0
 *     +2 ...................................... ori $t1
 *     +3 ...................................... ori $t2   == GOLDEN
 *
 * ==========================================================================
 * WHERE THE THREE WEBS MUST LIVE -- the twin localises it to two statements
 * ==========================================================================
 * func_151CC840's golden has NO deficit at the same site.  Its block 0 is our
 * block 0 MINUS the two `swc1 $f0` stores to unk50/unk54, and its join block
 * starts at $t9 exactly as ours does (ori $t9, lw $t0, lbu $t1, addiu $t2,
 * li1 $t3, sllv $t4, or $t5, unk16 $t6, unk18 $t7, unk1A $t8).  The only
 * source difference between the two block 0s is:
 *
 *     sp88.unk50 = 0.0f;
 *     sp88.unk54 = 0.0f;
 *
 * and OUR compile proves those two statements are web-free for us: deleting
 * them leaves the pool at $t9 (n 146, ori still $t9), and adding them to a
 * source that lacks them does not move it either.  So GOLDEN'S SOURCE FOR
 * THOSE TWO LINES IS NOT `sp88.unk50 = 0.0f; sp88.unk54 = 0.0f;`.  It is some
 * form that emits the same two `swc1 $f0, 0xD8/0xDC($sp)` and burns three
 * integer temp webs.  That is the whole open question, and it is a much
 * smaller one than the question this file carried last wave.
 *
 * THE MECHANISM TO LOOK FOR, calibrated on the matched-shape sibling
 * func_151CB5FC: an operation whose result is COALESCED ONTO A FIXED REGISTER
 * still consumes a rotation slot, while a pure copy does not.  CB5FC's block 0
 * allocates t6,t7,t8 for three parameter narrowings and then jumps to t0 for
 * `lw arg0` -- one invisible slot, t9, consumed by `sra $a3,$t8,24`, whose
 * result is coalesced onto $a3; its two `or $a1,$t6,$zero` / `or $a2,$t7,$zero`
 * copies are free.  In CC524's block 0 the fixed-register writes are
 * `lui $at` (130.0f), `mtc1 $zero,$f0`, `mtc1 $at,$f4`, the $v0 ternary arms
 * and the four `sw $aN` home stores.  THREE of those are webs in golden and
 * are not in ours.  Which three is not yet identified.
 *
 * ==========================================================================
 * GOLDEN t-REGISTER OCCURRENCE COUNTS (free evidence, costs no builds)
 * ==========================================================================
 * func_151CC524, 150 instructions:
 *     t0:5  t1:6  t2:8  t3:3  t4:10 t5:8  t6:12 t7:10 t8:10 t9:8   v0:7 at:22
 *   ** $t3 occurs exactly THREE times ** -- `lw $t3,0xE0($sp)` at idx24 and
 *   `lbu ...,0x23D($t3)` at idx27 and idx75.  That is the func_150130B4
 *   RESERVED-REGISTER signature: a rotation-pool register in a 150-instruction
 *   function appears ~8-10 times.  Golden reserves $t3 for the arg0 base
 *   across ~50 instructions.
 *   BUT THE RESERVATION IS NOT THE PROBLEM HERE: OUR source reserves the same
 *   register.  Ours: t0:3 t1:10 t2:8 t3:10 t4:8 t5:8 t6:10 t7:7 t8:8 t9:8 --
 *   our $t0 has the same 3 occurrences and maps onto golden's $t3 under the
 *   +3 rotation.  Subtract block 0's two uses each of t6/t7/t8 (identical on
 *   both sides) and the BODY census is an EXACT multiset match under the
 *   rotation.  Do not repeat the func_150130B4 reservation hunt here.
 * Same measurement on the other family members, for the record:
 *   func_151CC840 311 instr: t0:13 t1:16 t2:12 t3:18 t4:12 t5:14 t6:16 t7:17
 *                            t8:16 t9:18   (no reserved outlier)
 *   func_151CAD28 250 instr: t0:18 t1:11 t2:18 t3:18 t4:18 t5:16 t6:13 t7:16
 *                            t8:11 t9:16
 *   func_151CB5FC 199 instr: t0:8 t1:12 t2:10 t3:7 t4:14 t5:10 t6:13 t7:12
 *                            t8:12 t9:8
 *
 * ==========================================================================
 * THE WEB CURRENCY -- what does and does not consume a rotation slot
 * ==========================================================================
 * COSTS ONE SLOT (and two instructions, which is why none of them is usable):
 *   any integer-valued store into either aggregate.
 * COSTS ZERO SLOTS -- all measured this wave, do not re-probe:
 *   * FLOAT stores of every kind: `= 0.0f`, a fresh lui+mtc1 constant, a
 *     chained `unk50 = unk54 = 0.0f`, descending order, the read-back
 *     `unk54 = unk50` (byte-identical to the base), and an integer literal
 *     `= 0` into an f32 field (that one changes n, 150 -> 149).
 *   * CONSTANT-FOLDED `|` CHAINS.  0x390 spelled as `0x310|0x80`,
 *     `0x300|0x80|0x10`, `0x200|0x100|0x80|0x10`, the reverse order, with a
 *     `|0x0` term, and `(1<<9)|(1<<8)|(1<<7)|(1<<4)`: SEVEN spellings, all
 *     byte-identical.  The "0x390 is four flag bits and 0x10 is one, so the
 *     twins differ by three ors" hypothesis is DEAD.
 *   * PARAMETER TYPES.  All 32 u8/s32 combinations of arg1..arg5 and all 8
 *     u8/s8 combinations of arg1..arg3: byte-identical (65) except arg4 s32
 *     (66) and arg5 s32 (frame grows to 0xE8).  None moves the phase.
 *   * REDUNDANT STORES ARE ELIMINATED **WITH THEIR WEB**.  `sp88.unk12 = 0x12C;`
 *     written twice is byte-identical to once; `sp88.unk41 = 0xA;` repeated in
 *     the first spawn is byte-identical.  So a redundant store is not a free
 *     web.  (DEAD stores that are later overwritten are NOT eliminated: an
 *     early `sp88.unk48 = 0.0f;` or `sp88.unk10 = 0x9A;` costs real
 *     instructions.)
 *   * STATEMENT REORDERING inside block 0 (five orders), casts, `(u8*)`/`(s32)`
 *     deref spellings, `((f32*)&sp88)[0x14]` and `(u8*)&sp88 + 0x50` address
 *     forms.
 * NOT FREE but worth knowing: `*(f32 *)((s32)&sp88 + 0x50) = 0.0f;` DOES burn
 *   one integer web -- but it also costs one instruction (n 151), and using it
 *   twice pushes the frame to 0xE8.  It is the only phase lever found that is
 *   not an ordinary store.
 * THE PHASE IS LOCAL: deleting the second spawn, reordering it, adding stores
 *   to it, or appending a third spawn all leave the ori at $t9.
 *
 * ==========================================================================
 * REFUTED THIS WAVE: "golden evaluates 1 / 0xFF / 7 BEFORE the unk14 expression"
 * ==========================================================================
 * That reading (2026-08-16) came from seeing t9/t0/t1 immediately BEFORE t2 in
 * the cycle.  Re-derived against the twin and against func_151CAD28 and
 * func_151CB5FC, whose join blocks run FORWARD through exactly our source
 * order, the sequence is t2(ori) t3(lw) t4(lbu) t5(+0xB) t6(li 1) t7(sllv)
 * t8(or) t9(unk16) t0(unk18) t1(unk1A) -- i.e. GOLDEN'S SOURCE ORDER IS OURS.
 * Hoisting is also impossible on its own terms: with the flag inline the
 * hoisted stores land in block 0, which golden's asm rules out (no `li 1`,
 * `li 0xFF`, `li 7` before .L151CC584), and with the flag as a separate
 * statement the `ori`-first shape is lost (IDO sinks the immediate, LAW 4).
 * Measured again, both if/else and ternary spellings of the flag statement:
 *     nothing hoisted ............... 65 / shape 3   (the reassociated form)
 *     unk16 hoisted ................. 59 / shape 3   (= the old "alternative")
 *     unk16+unk18 hoisted ........... 136 / shape 7, n 151 (0xFF CSE broken)
 *     all three hoisted ............. 136 / shape 9, n 151
 * RANK BY SHAPE: this file's 65/shape 0 still wins.
 *
 * ==========================================================================
 * NEGATIVES INHERITED AND STILL STANDING (do not repeat)
 * ==========================================================================
 * * CARRIER SPELLINGS ARE BYTE-IDENTICAL: `void *`, `s32`, `u8 *`, `register`,
 *   assignment-in-condition, `if (p == NULL) {} else`, `if (p)`.  `static` is
 *   wrong (n=158, it goes to .bss).
 * * FLAG-CARRIER TYPES ARE BYTE-IDENTICAL: s32/u32/s16/u16/u8/s8 named local,
 *   and if/else == ternary == `arg4 ? ...` == inverted arms.
 * * `arg0 = func_1515548C(...)` promotes arg0 to $s0 and grows the frame to
 *   0xE8; the flag in arg4 gives n=152.
 * * func_1515548C's prototype is inert (all 16 u8/s32 combinations of
 *   parameters 2,3,4,7).
 * * The `(u16)(temp | 0x390)` cast stays DELETED: 65 without / 120 with.
 * * PERMUTER: 9,296 iterations under PERMUTER_TU_REQUIRE_FRAME=224 produced
 *   nothing below the base.  Given the residual is three invisible webs in
 *   block 0, its randomizer cannot reach this.
 *
 * SIGNATURE + PROTOTYPE (unchanged, re-verified)
 *   void func_151CC524(void *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5)
 *   The TU prototypes it `(void *, s32, s32, s32, u8, u8)` at line ~355 and
 *   must be changed WITH the definition.  MEASURED SAFE: with both twins'
 *   prototypes corrected to all-u8, func_151C9DE8, func_151CAB78,
 *   func_151CB49C and func_151CC77C are byte-identical.
 * ==========================================================================
 */

extern f32 D_800AAEC4;
extern f32 D_800AAEC8;
extern f32 D_800AAECC;
extern f32 D_800AAED0;

void func_151CC524(void *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5) {
    typedef struct {
        f32 unk0;
        f32 unk4;
        f32 unk8;
        f32 unkC;
        u8  unk10;
        u8  pad11;
        s16 unk12;
        u16 unk14;
        s16 unk16;
        s16 unk18;
        u8  unk1A;
        u8  unk1B;
        u8  unk1C;
        u8  unk1D;
        u8  unk1E;
        u8  unk1F;
        u8  unk20;
        u8  unk21;
        u8  unk22;
        u8  unk23;
        s32 unk24;
        s32 unk28;
        s32 unk2C;
        s32 unk30;
        s32 unk34;
        s32 unk38;
        s32 unk3C;
        u8  unk40;
        u8  unk41;
        u8  pad42[2];
        u8  unk44;
        u8  pad45[3];
        f32 unk48;
        f32 unk4C;
        f32 unk50;
        f32 unk54;
    } struct_151CC524_sp88;
    typedef struct {
        void *unk0;
        f32 unk4;
        f32 unk8;
        u8  unkC;
        u8  unkD;
        u8  padE[0x4A];
    } struct_151CC524_sp2C;
    struct_151CC524_sp88 sp88;
    void *temp_v0;
    struct_151CC524_sp2C sp2C;

    sp2C.unk0 = arg0;
    sp2C.unk4 = 0.0f;
    sp2C.unkD = 0;
    sp2C.unkC = 0;
    sp2C.unk8 = 130.0f;

    sp88.unk50 = 0.0f;
    sp88.unk54 = 0.0f;
    sp88.unk12 = 0x12C;
    sp88.unk14 = (1 << (*(u8 *)((s32)arg0 + 0x23D) + 0xB)) | (((arg4 != 0) ? 0x40 : 0) | 0x390);
    sp88.unk16 = 1;
    sp88.unk18 = 0xFF;
    sp88.unk1A = 7;
    sp88.unk1B = arg1;
    sp88.unk1C = arg2;
    sp88.unk1D = arg3;
    sp88.unk1E = 0x82;
    sp88.unk1F = 0xFF;
    sp88.unk20 = 0xFF;
    sp88.unk21 = 0xFF;
    sp88.unk22 = 0xFF;
    sp88.unk23 = 0xFF;
    sp88.unk24 = 0;
    sp88.unk28 = 0x200004;
    sp88.unk2C = 0x1F0601;
    sp88.unk30 = 8;
    sp88.unk34 = 0x44;
    sp88.unk38 = 0x80;
    sp88.unk3C = 0x20;
    sp88.unk40 = 0;
    sp88.unk41 = 0xA;

    sp88.unk44 = *(u8 *)((s32)arg0 + 0x23D);
    sp88.unk10 = 0x9A;
    sp88.unk0 = 0.0f;
    sp88.unk48 = D_800AAEC4;
    sp88.unk4C = 1.0f;
    sp88.unk8 = 28.0f;
    sp88.unkC = D_800AAEC8;
    sp88.unk4 = -37.0f;
    temp_v0 = func_1515548C(&sp88, 9, 0, 0, 0x58, arg5, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x70, &sp2C, 0x58);
    }

    sp88.unk10 = 0x9B;
    sp88.unk4 = 0.0f;
    sp88.unk48 = 1.0f;
    sp88.unk4C = D_800AAECC;
    sp88.unk8 = D_800AAED0;
    sp88.unkC = 28.0f;
    sp88.unk0 = -37.0f;
    temp_v0 = func_1515548C(&sp88, 9, 0, 0, 0x58, arg5, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x70, &sp2C, 0x58);
    }
}

/* ==========================================================================
 * FAMILY LAWS -- game_1F4650 spawner corpus.  REVISION 2 (2026-08-16).
 * This block REPLACES the 2026-08-15 version.  LAW 1 as written there was
 * WRONG and cost a wave; the correction is the first entry below.
 * Applies to func_151CAB78 (matched), func_150CF680 (matched, game_FC5F0),
 * func_151CB5FC, func_151CC524, func_151CC840, func_151CAD28.
 * ==========================================================================
 *
 * LAW 1 (REPLACED) -- THE AGGREGATE MODEL IS PART OF THE FRAME DECODE.
 *   OLD, WRONG: "temp area is 8 bytes <=> ZERO scalar locals, 16 <=> one or
 *   more; exception: one local reused for both roles also lands 0x2C."
 *   Both the rule and its exception were artifacts of declaring the payload
 *   struct 0x5C when it is 0x58.  What is actually measured:
 *     * The payload aggregate is EXACTLY the memcpy length (0x58 here).  Model
 *       it at the length the code copies, never at "whatever pads the frame".
 *     * Homes are laid out in DECLARATION ORDER from the top of the frame down;
 *       a scalar declared BETWEEN the two aggregates sits between them.
 *     * With payload 0x58, golden's 0xE0 frame holds TWO 4-byte scalar homes.
 *       Declaration order decides the bases -- MEASURED on func_151CC524
 *       (target: payload 0x2C, descriptor 0x88):
 *           sp88, X, sp2C, Y ......... pay 0x2C  desc 0x88  frame 0xE0  RIGHT
 *           sp88, X, sp2C ............ pay 0x2C  desc 0x88  frame 0xE0  RIGHT
 *           sp88, sp2C, X, Y ......... pay 0x30  desc 0x88  frame 0xE0  wrong
 *           X, Y, sp88, sp2C ......... pay 0x2C  desc 0x88  frame 0xE8  wrong
 *           (payload 0x5C, any order) . nothing reaches pay 0x2C with 2 scalars
 *     * An INLINE TERNARY costs one 4-byte carrier, the same as a declared
 *       scalar.  One ternary + one pointer local == two declared scalars.
 *   So: COUNT CARRIERS, NOT DECLARATIONS, and pin the aggregate sizes first.
 *
 * LAW 2 (REFINED) -- $v0 vs $v1 IS ABOUT ROLE SHARING, NOT LOCAL COUNT.
 *   A local that receives BOTH the flag and the func_1515548C result becomes one
 *   variable whose call-result web is ABI-preferenced onto $v0, which pushes the
 *   flag web to $v1.  Give the flag its own carrier -- its own local OR an inline
 *   ternary -- and the flag takes $v0, which is what both twins' golden does.
 *   MEASURED, all with the corrected 0x58 payload:
 *       one local, both roles ............ flag $v1   (this is the old trap)
 *       flag local + pointer local ....... flag $v0
 *       inline ternary + pointer local ... flag $v0
 *   Corollary for func_151CB5FC: its golden flag is in $v1 because ITS source
 *   shares one carrier, not because it "has named locals".  Retire that note.
 *
 * LAW 3 -- THE u8 PARAMETER TELL (unchanged, re-verified).  `lbu 0xE7($sp)`
 *   with no prologue `andi` means the parameter is u8 and is only ever stored to
 *   a byte field.  Fix the TU's forward prototype WITH the definition, then
 *   re-score every matched caller: for both twins the change is byte-neutral for
 *   func_151C9DE8, func_151CAB78, func_151CB49C and func_151CC77C.
 *
 * LAW 4 (SHARPENED) -- THE OR CHAIN.  golden `ori tX,$vN,K` then `or tY,tX,tZ`
 *   (constant FIRST) cannot come from a flat `|` chain through a NAMED local:
 *   IDO reassociates and sinks the 16-bit immediate to the end.  The escape is an
 *   INLINE TERNARY operand -- free, and it is what golden does.  The `(u16)` cast
 *   also blocks the sinking but is a NET LOSS once the frame model is right
 *   (see the SUSPECT verdict at the top of both twins).  Parenthesisation and
 *   operand order alone remain inert (10 spellings byte-identical).
 *
 * LAW 5 -- THE SHARED STRUCTS.  Both aggregates are 0x58 bytes.  DESCRIPTOR
 *   (func_1515548C arg0; identical in CAB78/CB5FC/CC524/CC840/CAD28):
 *     +0x00 f32 x   +0x04 f32 y   +0x08 f32 sizeA  +0x0C f32 sizeB
 *     +0x10 u8 kind +0x12 s16 lifetime(0x12C)      +0x14 u16 FLAGS
 *     +0x16 s16 (1) +0x18 s16 (0xFF) +0x1A u8 (7)
 *     +0x1B u8 arg1 +0x1C u8 arg2 +0x1D u8 arg3    +0x1E u8 kind2
 *     +0x1F..+0x23 u8 colour (0xFF)   +0x24 s32 0  +0x28 s32 0x200004
 *     +0x2C s32 0x1F0601  +0x30 s32  +0x34 s32     +0x38 s32 0x80
 *     +0x3C s32 0x20  +0x40 u8 0  +0x41 u8  +0x44 u8 arg0[0x23D]
 *     +0x48 f32  +0x4C f32  +0x50 f32  +0x54 f32
 *   +0x14 IS u16 (read back with `lhu` + `andi 0xFFF9`).  +0x14 is always built
 *   as (1 << (arg0[0x23D] + 0xB)) | (<flag> | <small const>).
 *   PAYLOAD (memcpy'd to result+0x70) -- **0x58 BYTES, the memcpy length**:
 *     +0x00 void* owner (= arg0)  +0x04 f32  +0x08 f32 (130.0f)  +0x0C u8
 *     +0x0D u8  ... rest is uninitialised stack, copied anyway.
 *   Payload source order matching golden in CAB78/CC524/CC840:
 *       unk0, unk4, unkD, unkC, unk8      (unkD BEFORE unkC)
 *
 * LAW 6 -- PER-SPAWN TAIL ORDER.  Each spawn rewrites a handful of descriptor
 *   fields then calls:  <unk14 edit>, unk10, [unk44 first spawn only],
 *   unk0/unk4/unk8/unkC with the ZERO-valued float first.  The two per-function
 *   order wins recorded last wave were re-measured on the corrected model and
 *   they MOVED, so re-measure them per function, never inherit them:
 *       `unk16 = 1` before unk14: worth +6 on CC524's named-local variant but
 *       -9 on CC840, where it must come AFTER (the opposite of last wave).
 *       `unk44` before `unk10`: still per-function.
 *
 * LAW 7 -- TOOLING.  Read BOTH numbers, always:
 *       python3 tools/fastscore.py  <tu> <func> <src>    (raw mism)
 *       python3 tools/shapescore.py <tu> <func> <src>    (shape_miss)
 *   This wave they moved in opposite directions on both twins (65/shape 0 beats
 *   59/shape 3).  And when the residual is register naming, compute the ours->
 *   golden register PERMUTATION: if it is a single uniform rotation, you are
 *   looking for ONE allocation-order fact, not N independent decisions.
 *
 * LAW 8 (NEW) -- A DEAD STORE THE COMPILER FOLDS IS AN HONEST SOURCE CHOICE.
 *   On func_151CC840 the flag-word edits are worth 9-13 points and 6 shape rows
 *   written as TWO statements (`f.unk14 &= ~0x6;` then `f.unk14 |= N;`) rather
 *   than one `f.unk14 = (f.unk14 & ~6) | N;`.  IDO folds the intermediate store,
 *   so n is unchanged -- this is not a forcer, it is a different (and evidently
 *   original) spelling.  Use golden's store COUNT at that address to decide:
 *   two stores in golden (as in func_151CAD28) means two source statements.
 * ==========================================================================
 */

/* ==========================================================================
 * RECONNAISSANCE -- func_151CAD28 (next family member, 1000 bytes, 250 instr)
 * Decoded from asm/nonmatchings/game_1F4650/func_151CAD28.s only; NOT compiled.
 * Re-read it under LAW 1 REVISION 2 before trusting the local count below.
 *
 * SIGNATURE: void func_151CAD28(void *arg0, u8 arg1)  -- only a0/a1 homed
 *   (0x100/0x104); arg1 read as `lbu 0x107($sp)`.
 * FRAME 0x100: ra @0x24, carrier area 0x28..0x4B, payload @0x4C (0x58), 4 bytes
 *   @0xA4, descriptor @0xA8 (0x58).  Under the corrected law that area is
 *   CARRIERS (locals + ternary temps), and the payload is 0x58 = its memcpy.
 * PAYLOAD @0x4C: +0x00 = arg0 ; +0x04 = 0.0f ; +0x08 = 130.0f ; +0x0C = 0 ;
 *   +0x0D = 0.
 * DESCRIPTOR @0xA8:
 *   unk10 = (D_80082FA0 > 0) ? 0x72 : 0x65   <- `blez`, the CAB78 idiom, result
 *                                               stored straight to the byte field
 *   unk12 = 0x12C ; unk14 = (1 << (arg0[0x23D] + 0xB)) | 0x50   <- NO flag
 *   ternary, golden emits `sllv` then `ori` (constant LAST), the ORDINARY flat
 *   chain: do NOT reach for the ternary/cast escape here.
 *   unk16 = 1 ; unk18 = 0xFF ; unk1A = 7 ; unk1B = 0 ; unk1C = 0xFF ; unk1D = 0 ;
 *   unk1E = 0x82 ; unk1F..unk23 = 0xFF ; unk24 = 0 ; unk28 = 0x200004 ;
 *   unk2C = 0x1F0601 ; unk30 = 8 ; unk34 = 0x44 ; unk38 = 0x80 ; unk3C = 0x20 ;
 *   unk40 = 0 ; unk41 = 0xA ; unk44 = arg0[0x23D] ; unk8 = unkC = 25.0f
 * PER-SPAWN: unk0/unk4 rewritten (25.0f/-25.0f pairs); the flag word is edited
 *   with the same compound RMW as func_151CC840.  At 151CAE54..151CAE60 golden
 *   emits `andi t2,t6,0xFFF9 ; sh t2,0xBC ; ori t4,t2,0x6 ; sh t4,0xBC` -- TWO
 *   stores, i.e. two source statements (LAW 8).
 * CALL: func_1515548C(&desc, (u8)((arg1 != 0) ? 4 : 0), 0, 0, 0x58, 0xFF, 1)
 *   -- ternary INLINE in the argument list; golden narrows with `andi $a1,$v0,0xFF`.
 *
 * NOT THIS FAMILY (checked, so nobody re-checks): func_151CB110 (frame 0xB0,
 * saves s0-s7 + f20-f30, loop-heavy) and func_151CBC60 (frame 0x18, float
 * physics calling func_151CC1D4) are ordinary functions; rank them on their own.
 * ==========================================================================
 */
