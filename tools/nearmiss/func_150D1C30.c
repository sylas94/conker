/* ============================================================================
 * PARKED NEAR-MISS  func_150D1C30  (game_FF0E0.c) -- LAST pragma in this TU.
 * 2026-08-13 WAVE 3:  445 -> 400, at the exact golden size of 828 bytes, frame
 * 0xf0 == golden.  Measured with the stale-object guard (rm the .o AND the
 * asm-processor intermediate, make, assert the object exists), everything
 * through buildlock.  Calibration: with the #pragma in place the harness
 * prints CURRENT (0).  400 with -R and 400 without -R.
 *
 * WAVE 4 (2026-08-13) DID NOT MOVE IT.  Base re-verified at 400 / 828 B before
 * anything else.  Sixteen further variants across five NEW axes all reproduce
 * the SAME two rows -- see "WAVE 4" below.  The one real result of wave 4 is
 * NEGATIVE and structural: the "restore a block boundary at the join" theory in
 * the brief is REFUTED for two of its four listed boundary kinds, and the flag
 * axis is closed.  Read WAVE 4 before spending another wave on the CFG.
 *
 * ============ THE GAIN: THE ELSE ARM NEEDS ITS OWN POINTER LOCAL ============
 * Wave 2's residual was eleven rows, nine of them the $v0/$v1 swap between the
 * loaded pointer and the unrolled cursor copy.  ALL NINE ARE NOW GONE.  The
 * whole else arm -- both peeled slots and all four main-body slots -- matches
 * golden register for register.
 *
 * The diagnosis came from the `bind part' measurement, decoded rather than
 * ranked.  Binding `part' in the else arm (558) does NOT put the loaded pointer
 * in $v0; it puts it in $s0 and the CURSOR STILL TAKES $v0:
 *      golden  280: lw v0,0x24(s2)   284: move v1,s2
 *      bind    280: lw s0,0x24(s2)   284: move v0,s2
 * i.e. in our compile the cursor is allocated FIRST whatever the loaded pointer
 * is doing.  Golden allocates the loaded pointer first, and the only thing that
 * outranks a compiler-generated induction cursor is a SOURCE VARIABLE.  `part'
 * cannot be it -- its web then spans both arms of the outer if, is live across
 * the if arm's calls, and is forced into a callee-saved register (that is the
 * whole 558).  So golden has a SECOND pointer local, used only in the else arm,
 * where there are no calls, so it is free to live in $v0.
 *
 * THE FRAME OBJECTION WAS WRONG, and this is the transferable lesson.  Wave 2
 * ruled a new local out because sum(sizeof(local)) is exactly 104 == the home
 * area.  But a local declared LAST lands in the compiler-temp slack below the
 * home area and the frame does not move:
 *      `Part150D1C30 *p' declared LAST ......... 400, frame 0xf0, size 828
 *      `Part150D1C30 *p' declared SECOND ....... 473, frame 0xf0 but EVERY sp
 *          offset shifts down 4 (0xa8->0xa4, 0x9c->0x98, ... 0x88->0x84)
 *      a SECOND extra local (`s32 k' as a separate else-arm counter),
 *          either declaration order .............. 811, frame 0xf8
 * so there is room for EXACTLY ONE spare 4-byte local, and only in last place.
 * (The same wave closed func_150825C0 by adding TWO f32 locals in last place
 * without moving its frame -- see tools/nearmiss/func_150825C0.c.)
 *
 * ================= THE RESIDUAL: TWO ROWS, ONE PEEPHOLE =====================
 *   golden  2a8: beqz  v0,2b8      ours  2a8: beqzl v0,2bc
 *           2ac: nop                     2ac: lw    v0,0x24(s1)
 * 400 = 2 x 200 (replaced instruction).  Everything else in the function is
 * byte-identical, registers included.
 *
 * WHAT THE PEEPHOLE IS.  as1 converts `beqz X,L / nop' into `beqzl X,L+4' by
 * DUPLICATING the last instruction of the fall-through block into the (now
 * nullified-on-fall-through) delay slot and moving the join label past it.  It
 * does this at FIVE of the six unrolled guards in golden too -- guard 1 gets
 * `beql v0,zero,2a4' with `lw v0,0x28(v1)', guards 3..6 likewise.  Only guard 2
 * is left alone, and guard 2 is exactly the peel/main-body seam: its join label
 * 2b8 is the first instruction of the four-times-unrolled main body
 * (`lw v0,0x24(s1)', s1 = sub + t0, t0 = 2*4 hoisted to the ENTRY block as
 * `li s3,2 / sll t0,s3,0x2').  So golden keeps a block boundary at 2b8 that our
 * compile does not, and as1 therefore finds `sb s4,0x9(t9)' as the fall-through
 * block's last instruction -- unsafe to duplicate ($t9 undefined on the taken
 * path) -- and gives up.  Ours sees the load there instead and fills.
 * The two rows are ONE cause; whatever restores that boundary takes 400 -> 0.
 *
 * ============ MEASURED NEGATIVES, wave 3, all on the 400 base ==============
 * EIGHT mutually exclusive variants score EXACTLY 400 with the IDENTICAL
 * two-row residual.  Per the seven-axis rule these are NOT one axis -- they
 * span subscript spelling, guard spelling, loop shape, which local is which,
 * assignment placement and physical line layout -- so the residual is
 * invariant under all six of those axes:
 *   `p = ...; if (p != NULL)'  (the shipped form) .................... 400
 *   `if (p)' bare truthiness ........................................ 400
 *   `if ((p = ((Part **)sub)[i + 9]) != NULL)' assignment in guard ... 400
 *   `p = (&sub->unk24)[i]' member-address subscript .................. 400
 *   bound `i < 6' instead of `i != 6' ............................... 400
 *   `i = 0; do { ... i++; } while (i != 6);' ........................ 400
 *   the two pointer locals SWAPPED (if arm uses the last-declared one,
 *     else arm uses `part') ......................................... 400
 *   every statement split onto its own physical line ................ 400
 * and these are worse:
 *   the whole else-arm loop on ONE physical line ............ 520 (828 B)
 *     -- it swaps entry-block rows 3c/48 (`addiu s2,s0,0x28' vs
 *        `sll t0,s3,0x2'), which PROVES -g3 line layout is a live axis
 *        here; it just does not reach the peephole
 *   else arm binds `part' (one web across both arms) ....... 558 (828 B)
 *     -- also swaps $s0/$s1 in the prologue
 *   `p' declared second instead of last .................... 473 (828 B)
 *   `s32 k' as a separate else-arm counter ................. 811 (828 B, 0xf8)
 *   else arm given the if arm's `for (i = 0;;) { ... i++; if (i == 6)
 *     break; }' treatment ............................ 3520 (728 B)
 *     -- this DESTROYS the unroll: `move v0,zero' replaces golden's
 *        `li s3,2', i.e. the 2+4 peel is a property of the `for (i = 0;
 *        i != 6; i++)' header shape.  Do not touch that header.
 *   `if (p == NULL) continue;' ............................ 5656 (788 B, 0xd8)
 *   index off `arg0' rather than `sub' ................... 1130 (824 B)
 *
 * STILL TRUE FROM WAVE 2 -- do not re-measure:
 *   the if arm's `for (i = 0;;) { ... i++; if (i == 6) break; }' shape is
 *   worth 980 (it stops the constant 6 becoming a LICM candidate that evicts
 *   golden's fourth hoisted invariant &sp9C), and `for (i = 0;;)' rather than
 *   a separate `i = 0;' statement is worth a further 210.  Both are in the
 *   shipped source below.
 *
 * FRAME DECODE (framesize 0xf0), unchanged and still exact:
 *   0x00..0x3b arg build (func_150AC9C0 takes 15 args -> slots 0x10..0x38)
 *   0x48 $f20, 0x50..0x74 $s0..$s8/$ra
 *   0x88..0xef HOME AREA, top-down in declaration order:
 *       0xec sub / 0xe8 part / 0xa8 mtx[4][4] / 0xa4 i /
 *       0xa0 spA0 0x9c sp9C 0x98 sp98 / 0x94 sp94 0x90 sp90 0x8c sp8C 0x88 sp88
 *   and `p', declared last, takes 0x84 out of the temp slack.
 *
 * NOT A ROUTE: conker/permuter_tu.sh SELFTEST FAILS on this TU (compile.sh's
 * IDO invocation dies with `as1: Error: <tmp>/tu.c, line 255: No such file or
 * directory'), so every score it would report is meaningless.
 *
 * ############################################################################
 * ###################### WAVE 4 -- ALL NEGATIVE ##############################
 * ############################################################################
 *
 * (1) THE PEEPHOLE'S PRE-CONDITION, READ OFF THE OBJECT RATHER THAN GUESSED.
 * The transform is: for `beqz X,L / nop', COPY the instruction that sits AT L
 * into the (branch-likely, taken-only) delay slot and move the label to L+4.
 * The copy at L stays for the fall-through path, so both paths execute it once
 * and NO instruction is added -- which is why our object is the same 828 bytes
 * as golden with one row `beqz->beqzl' and one row `nop->lw'.  Verified on all
 * six guards; e.g. guard 6 `beql v0,zero,30c / lw ra,0x74(sp)' has its copy at
 * 308 and the label at 30c.
 *
 * (2) "A LABEL REACHED FROM MORE THAN ONE PLACE" IS **NOT** A BOUNDARY FOR as1.
 * REFUTED inside this very function.  Golden's epilogue join 30c has THREE
 * predecessors -- `b 30c' at 278 (from the if arm), guard 6's branch, and the
 * fall-through -- and as1 still moved the label and duplicated `lw ra,0x74(sp)'
 * into BOTH branch delay slots.  So multi-predecessor does not inhibit it, and
 * hunting for a second reference to the join at 2b8 is a dead end.
 *
 * (3) THE TRANSFORM IS SELECTIVE, SO THE *REFUSAL* IS THE COMMON CASE.
 * Scanned every /* addr word *\/ line of conker/asm/nonmatchings (all golden):
 *     5121 conditional branches in golden have a `nop' delay slot;
 *     of those, 708 target a plain `lw', 330 an `addiu', 82 a `lbu', 75 an
 *     `or', 42 an `lwc1' -- i.e. hundreds of golden sites where the target
 *     instruction was trivially duplicable and as1 declined.
 * Whatever gates it is therefore NOT "is the target duplicable".  A scanner
 * script is at scratchpad w4-k7x2q9/scan_nop.py if a later wave wants to mine
 * those 708 sites against MATCHED C.  That is the one route left that has real
 * information in it, and it is a whole wave's work on its own.
 *
 * (4) THE STRUCTURAL DIFFERENCE BETWEEN GUARD 2 AND GUARDS 3..6, EXACTLY.
 * Undo every conversion and the else arm reads:
 *     LA: lw v0,0x28(v1)        <- guard 1's ORIGINAL join
 *         li s4,1
 *         beqz v0,LB            (guard 2)   <- TWO instructions above it, and
 *         nop                                  the nearer one does NOT define
 *         lw t9,0x14(v0)                       the tested register
 *         sb s4,0x9(t9)
 *     LB: lw v0,0x24(s1)        <- 4x main-body head
 *         beqz v0,LC            (guard 3)   <- ONE instruction above it, and it
 *         nop                                  DOES define the tested register
 * Guard 2 is the only guard in the function that has a spare, non-defining
 * instruction (`li s4,1') between the join label and the branch.  After guard
 * 1 converts, that `li' is itself sitting on the moved label LA and is pinned.
 * This is a better-specified statement of the residual than "the seam", and it
 * is the shape any future explanation has to account for.
 *
 * (5) MEASURED NEGATIVES, WAVE 4, all on the 400 base, all 828 B / frame 0xf0
 *     unless noted, and ALL with the identical two-row residual (the 2a8 row
 *     was read straight out of objdump for each):
 *   no local at all, `((Part **)sub)[i+9]' written TWICE so the pointer is a
 *     pure CSE temp .......................................... 445  (828 B)
 *     -- and 445 with `!= 0' instead of `!= NULL' too; this is wave 2's score,
 *        i.e. the $v0/$v1 swap comes back.  The DECLARED local is load-bearing.
 *   `Part150D1C30 *q;' declared in the ELSE BLOCK's own scope (C89 block-head
 *     declaration), function-level `p' deleted ............... 400  (828 B)
 *     -- byte-for-byte the same object as the shipped form, same two rows.
 *        This is a MORE PLAUSIBLE original spelling than "declared last" and
 *        it explains the placement (a block-scope local is laid out after all
 *        function-scope locals, i.e. in the temp slack).  Kept out of the
 *        shipped source only because it changes nothing measurable.
 *   same, with no blank line after the declaration .......... 400
 *   extra nested `{ }' around the whole else-arm loop ....... 400
 *   extra nested `{ }' around the store statement ........... 400
 *   `if (p != NULL) { ... }' folded onto one physical line ... 400
 *   `p = ...;' and `if (...) {' folded onto one line ........ 400
 *   if arm's `i++; if (i == 6)' -> `if (++i == 6)' ........... 400
 *   if arm's `i++; if (i == 6) { break; }' on one line ...... 400
 *   else arm `i = 0; do { ... } while (++i != 6);' .......... 400
 *   else arm `for (i = 0; i != 6; i = i + 1)' ............... 400
 *   `void *p' + cast at the use ............................. 400
 *   `for (i = 9; i != 15; i++)' with `[i]' .................. 930  (828 B)
 *   separate `s32 j' for the else arm, declared in the else
 *     block's scope ......................................... 811  (828 B)
 *   ELSE ARM SPLIT INTO AN EXPLICIT 2 + 4 SEAM (`for (i=0;i!=2;i++)' then
 *     `for (; i!=6; i++)') ................................. 8214  (864 B)
 *     -- this is the direct test of the brief's "peel/main-body seam" idea and
 *        it DESTROYS the unroll (36 bytes bigger).  You cannot hand IDO the
 *        seam; the seam is the unroller's, and writing it out changes it.
 *
 * (6) THE FLAG AXIS IS CLOSED.  Whole-TU rebuilds with OPT_FLAGS overridden
 *     (legitimate in this repo -- the Makefile already overrides per file):
 *       -O2 -g3 ... 400 (828 B)      <- shipped
 *       -O2 -g2 ... 27305 (816 B)    -O2 -g1 ... 27305 (816 B)
 *       -O2 -g0 ... 2038 (824 B)     -O2 ...... 2038 (824 B)
 *       -O1 -g3 ... 23460 (736 B)    -O3 -g3 .. 11547 (828 B)
 *     -g3 is right and nothing else is close.  Note -O2 without -g3 emits 824
 *     bytes: the guard-2 nop does not exist there at all.
 *
 * (7) NOT A ROUTE: you cannot see as1's input.  `cc -S' and `cc -K' both kill
 *     the recompiled ugen (`Fatal error in: /usr/lib/ugen ... Signal 11'), and
 *     the pipeline's kept intermediates (/tmp/ctm*) are binary "binasm", not
 *     text assembly -- as1 itself errors with `binasm: No such file or
 *     directory' when run bare.  Snapshotting /tmp during a compile confirms
 *     there is no text .s stage to inspect or hand-edit.
 *
 * ############################################################################
 * ############ WAVE 5 -- THE MINING IS DONE; BAIL AT 400, WITH A #############
 * ############ CONSTRUCTIVE PROOF THAT THE GATE IS NOT LOCAL   ##############
 * ############################################################################
 *
 * The brief's "one route with real information in it" -- mine the sites where
 * as1 declined to convert -- has now been run to the end.  It is CLOSED, and
 * closed by a counterexample rather than by inconclusive statistics.
 *
 * (A) THE CORPUS.  Disassembled all 464 objects of expected/build/src (i.e.
 *     every golden function, not just the 2387 asm/nonmatchings ones), and
 *     classified every conditional branch three ways:
 *        FILL  14692  non-likely branch, delay slot NOT a nop
 *        CONV   8451  likely branch whose delay-slot WORD == word at (target-4)
 *                     -- the fingerprint of "copy the insn at L into the
 *                        taken-only slot and point the branch at L+4"
 *        DECL   2503  non-likely branch, nop slot, target a plain instruction
 *     (scanner: scratchpad w5-m3p8vq/mine.py, mine2.py, mine3.py, an1.py, an4.py)
 *
 * (B) TWO THIRDS OF THE 2503 DECLINES ARE NOT EVIDENCE AT ALL.  They are as1's
 *     OWN macro expansions, which it never revisits:
 *        797  div/divu/rem guards -- `div zero,x,y / bnez y,L / nop / break 7'
 *        541  target is `lui' (the %hi half of a lui/%lo relocation pair)
 *        137  multu   47 mflo   20 div   9 mfhi   2 divu
 *     Wave 4's headline number ("708 of 5121 target a plain lw, so the gate is
 *     not duplicability") survives but shrinks: the honest population is
 *        CLEAN: CONV 8308 / DECL 950  ->  as1 declines 10.3% of the time,
 *        of which 422 sites are in LIVE C we compile ourselves.
 *     ~175 of those 422 are in TUs the Makefile builds at `-g' or `-O1'
 *     (init_1AAE0 66, game_221290 49, init_20000 26, init_1C060 24), so the
 *     real -O2 -g3 decline population is roughly 250 sites.
 *
 * (C) NO FEATURE IS DETERMINISTIC.  Decline rate on the CLEAN population:
 *        cand mnemonic      lw 14.5%  sw 17.0%  lwc1 10.4%  move 9.5%
 *                           lbu 6.6%  li 3.9%   addiu 3.3%  lb 4.7%
 *        block length       2 -> 5.9%   3 -> 9.1%   4 -> 9.9%   >=8 -> 15.6%
 *        tested reg defined in the branch's own basic block:
 *                           yes 10.9%   no 5.4%   (LIVE C: 12.6% / 5.0%)
 *        forward 23.7% / backward 12.7%; label predecessor count: flat
 *     Every candidate discriminator the brief listed was tested and every one
 *     is a weak correlation, not a gate.  In particular `def_in_block' -- the
 *     one this wave derived from the function itself (see (D)) -- comes out
 *     BACKWARDS on the clean data.
 *
 * (D) THE 2x2 THAT KILLS THE "FILLED FROM ABOVE FIRST" MODEL.
 *     FILL / CONV / DECL against (prev insn independent of the branch) x
 *     (prev insn immovable, i.e. sitting on a label or in a delay slot):
 *        indep=T immovable=T   FILL 2706  CONV  909  DECL  133   3.5% decl
 *        indep=T immovable=F   FILL 5509  CONV 1581  DECL 1027  12.7% decl
 *        indep=F immovable=T   FILL 2421  CONV 1148  DECL  353   9.0% decl
 *        indep=F immovable=F   FILL 4056  CONV 4813  DECL  990  10.0% decl
 *     Wave 4's "sharpest clue" (guard 2 is the only guard with a spare
 *     NON-DEFINING instruction between the join label and the branch) predicts
 *     the top-left cell should be the decline cell.  It is the LOWEST at 3.5%.
 *     The clue is real about this function and false as a game-wide rule.
 *
 * (E) THE COUNTEREXAMPLE -- THIS IS THE RESULT.  You CAN drive the peephole
 *     directly: compile a standalone probe with the repo's exact IDO flags
 *     (scratchpad w5-m3p8vq/probe.sh, p1.c, p2.c).  Undo the conversions in
 *     both listings and golden's guard 2 and probe fA's guard 2 are the SAME
 *     WINDOW, instruction class for instruction class:
 *
 *         Lprev:  lw   RD, off(RB)      <- a label MOVED here by the preceding
 *                 li   RC, 1               guard's own conversion
 *                 beqz RD, L
 *                 nop
 *                 lw   RT, 0x14(RD)
 *                 sb   RC, 0x9(RT)
 *         L:      lw   RD, off2(RB2)
 *
 *       golden 150D1ED0  RD=v0 RC=s4 RB=v1 RB2=s1 off=0x28 off2=0x24  DECLINED
 *       probe fA 0x18    RD=v0 RC=v1 RB=a0 RB2=a0 off=4    off2=8     CONVERTED
 *
 *     Same as1, same flags, same window, opposite decisions.  Sub-hypotheses
 *     that die with it, each refuted by a probe rather than by a correlation:
 *       * "the moved label pins the spare instruction"      -- fA has it too
 *       * "the tested reg must be defined in the block"     -- fA's is not
 *       * "the target's base register must be caller-saved" -- probe fC's
 *         guard 2 duplicates `lw v0,0(s0)', s0 callee-saved, and CONVERTS
 *       * "the peel/unrolled-body seam is special"          -- fC/fD have the
 *         identical 2-peel + 4x-unrolled else arm under an outer if, and their
 *         seam guard CONVERTS
 *     Therefore the decision is NOT a function of the local instruction
 *     pattern.  It depends on state that is not recoverable from the emitted
 *     stream -- and our object and golden's are BYTE-IDENTICAL except for the
 *     two words in question, so there is no local edit that can address it.
 *
 * (F) WHAT WOULD STILL BE A ROUTE, for anyone who returns here.  Only two:
 *       1. a global change to the if arm's internal scheduling state that
 *          leaves its ~700 bytes of output identical -- unsearchable by hand,
 *          and the permuter's selftest FAILS on this TU (see above), so it
 *          cannot be searched mechanically either;
 *       2. an IDO driver flag not on the OPT_FLAGS axis.  Note the Makefile
 *          line 221 already interpolates an EMPTY `$(LOOP_UNROLL)' into the
 *          GLOBAL_ASM compile path and never sets it anywhere in the repo.
 *          Nothing here suggests it is the answer; it is simply the only
 *          untested knob left.
 *
 * BAIL: leave the #pragma in place at 400 / 828 B.  Two rows, both from one
 * assembler decision, with a proof that the decision is not addressable from
 * the C.  Do not spend another wave on the CFG, the spelling, or the flags.
 * ============================================================================ */

#include <ultra64.h>
#include "functions.h"
#include "variables.h"


typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Vec150D1F6C;

typedef struct {
    Vec150D1F6C unk0;
    f32 unkC;
} Arg150D1F6C;

typedef struct {
    u8 pad0[0x18];
    Vec150D1F6C unk18;
    u8 pad24[0x18];
    f32 unk3C;
    s32 unk40;
    u8 unk44;
} Sub150D1F6C;

typedef struct {
    u8 pad0[0x40];
    Vec150D1F6C unk40;
} Obj150D1F6C;

/* --- func_150D1C30 -------------------------------------------------- */

typedef struct {
    u8  pad0[0x9];
    u8  unk9;
    u8  padA[0x4];
    s16 unkE;
    s16 unk10;
    s16 unk12;
    u8  pad14[0x1B];
    u8  unk2F;
} Node150D1C30;

typedef struct {
    u8  pad0[0x14];
    Node150D1C30 *unk14;
} Part150D1C30;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    Part150D1C30 *unk24;
    Part150D1C30 *unk28;
    Part150D1C30 *unk2C;
    Part150D1C30 *unk30;
    Part150D1C30 *unk34;
    Part150D1C30 *unk38;
    f32 unk3C;
    s32 unk40;
    u8  unk44;
} Sub150D1C30;

typedef struct {
    u8  pad0[0x6C];
    u8  unk6C;
} Obj150D1C30;

extern f32 D_800A08F0[][3];
extern void func_150A7960(f32 mtx[4][4], f32 x, f32 y, f32 z, f32 *ox, f32 *oy, f32 *oz);
extern s32 func_150AC9C0(f32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1, void *arg6,
                         void *arg7, f32 *arg8, f32 *arg9, f32 *arg10, f32 *arg11,
                         s32 *arg12, s32 arg13, f32 arg14);

void func_150D1C30(struct260 *arg0) {
    Sub150D1C30 *sub;
    Part150D1C30 *part;
    f32 mtx[4][4];
    s32 i;
    f32 spA0;
    f32 sp9C;
    f32 sp98;
    f32 sp94;
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    Part150D1C30 *p;

    sub = (Sub150D1C30 *)((u8 *)arg0 + 0x28);
    if (((Obj150D1C30 *)arg0)->unk6C & 1) {
        sub->unkC += sub->unk18 * D_800BE9A4;
        sub->unk10 += sub->unk1C * D_800BE9A4;
        sub->unk14 += sub->unk20 * D_800BE9A4;
        func_150A8050(mtx, sub->unkC, sub->unk10, sub->unk14);

        for (i = 0;;) {
            part = ((Part150D1C30 **)sub)[i + 9];
            if (part != NULL) {
                func_150A7960(mtx, D_800A08F0[i][0], D_800A08F0[i][1], D_800A08F0[i][2],
                              &sp98, &sp9C, &spA0);
                if (func_150AC9C0(sub->unk0, sub->unk4, sub->unk8, sp98, sp9C, spA0, NULL, NULL,
                                  &sp8C, &sp90, &sp94, &sp88, NULL, 0, 0.0f) != 0) {
                    part->unk14->unk9 = 0;
                    part->unk14->unkE = sp8C;
                    part->unk14->unk10 = sp90;
                    part->unk14->unk12 = sp94;
                    part->unk14->unk2F = sub->unk3C * sp88;
                } else {
                    part->unk14->unk9 = 1;
                }
            }
            i++;
            if (i == 6) {
                break;
            }
        }
    } else {
        for (i = 0; i != 6; i++) {
            p = ((Part150D1C30 **)sub)[i + 9];
            if (p != NULL) {
                p->unk14->unk9 = 1;
            }
        }
    }
}

void func_150D1F6C(struct260 *arg0, s32 arg1, u8 arg2) {
    Sub150D1F6C *sub;
    Arg150D1F6C *arg;

    sub = (Sub150D1F6C *)((s32)arg0 + 0x28);
    if (arg2 == 0x32) {
        arg = (Arg150D1F6C *)arg1;
        sub->unk18 = arg->unk0;
        sub->unk3C = arg->unkC;
    dummy_label_150D1F6C_1: ;
    } else {
        if ((arg2 == 0x30) || (arg2 == 0x31)) {
            if (arg1 == sub->unk40) {
                if (arg2 == 0x30) {
                    sub->unk44 |= 1;
                } else {
                    sub->unk44 &= ~1;
                dummy_label_150D1F6C_2: ;
                }
            }
        } else if (arg2 == 0x4E) {
            ((Obj150D1F6C *)arg0)->unk40 = *(Vec150D1F6C *)&D_800A5480;
        } else if (arg2 == 0x4F) {
            func_1516972C((struct102 *)arg0);
        }
    }
}

void func_150D2054(struct260 *arg0) {
    s32 i;
    s32 *p;
    void *ptr;

    p = (s32 *)((u8 *)arg0 + 0x28);
    i = 0;
    do {
        ptr = (void *)p[i + 9];
        if (ptr != NULL) {
            func_1516972C((struct102 *)ptr);
        }
        i++;
        i = (u8)i;
    } while (i < 6);
}

extern void func_150D2054(struct260 *);

void func_150D20B0(struct260 *arg0) {
    func_150D2054(arg0);
    func_15149368(arg0);
}

void func_150D20DC(struct260 *arg0) {
    func_150D2054(arg0);
    func_1514933C(arg0);
}
