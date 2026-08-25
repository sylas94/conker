/* ===================== PARKED -- 33 (was 1000000 / pragma) =====================
 * FILE KIND: SPLICE PAYLOAD.  The whole of this file (comment included) is what a
 * future wave drops in place of the single line
 *     #pragma GLOBAL_ASM("asm/nonmatchings/game_209B50/func_151DC6A0.s")
 * in conker/src/game_209B50.c.  Nothing else in that TU is touched, and no other
 * header is required: every typedef and extern this needs is LIVE C below.
 *
 * VERIFIED END TO END FROM THIS COMMITTED FILE by the mechanical splice
 * (conker/src/game_209B50.c with the pragma line replaced by this file's text,
 * scored with tools/fastscore.py, OPT_FLAGS -O2 -g3 default):
 *
 *     mism=33   frame=-128 (0x80, EXACT)   n=135/135 (EXACT)
 *
 * Differing word indices: 40,41,43,44,46,47,48,50,51,52,54,55,56,57,58,59,60,61,
 * 62,63,64,65,66,67,68,69,70,71,72,73,74,75,76.  Indices 0-39 and 77-134 are
 * word-for-word golden, INCLUDING every relocated field, both calls' argument
 * builds, all 22 struct-field stores and the whole epilogue.
 *
 * ------------------------------ THE BLOCKER ------------------------------
 * ALL 33 rows are ONE scheduler tie-break plus its cascade.  At the top of the
 * basic block that begins right after `jal func_15103254`:
 *
 *     ours    [40] lw    $t4, 0x80($sp)     <- struct-copy SOURCE  (arg0 reload)
 *             [41] addiu $a1, $sp, 0x40     <- struct-copy DEST    (&sp40)
 *     golden  [40] addiu $a1, $sp, 0x40
 *             [41] lw    $t4, 0x80($sp)
 *
 * With `lw $t4` one slot earlier, IDO's list scheduler fits only SEVEN `li`s into
 * the three lw/sw pairs of the 12-byte struct copy (t9,t8,t0,t1,t2,t3,t6) and
 * defers `li $t5,0xC8` to index 76.  Golden, starting one slot later, fits EIGHT
 * (…,t6,t5) and everything from 42 to 76 slides by one word.  Fix index 40 and
 * the other 32 rows follow for free -- the instruction MULTISET is already
 * identical, only the position of `li $t5,0xC8` differs.
 *
 * WHY IT LOOKS UNREACHABLE FROM C.  The order src-address-then-dest-address is
 * what IDO emits for the construct `X.f = *(T *)p;`, and that is confirmed by
 * GOLDEN CODE in the very same TU: the MATCHED sibling func_151DC8BC does
 *     sp34.unk0 = *(struct dc8bc_a *)arg0;
 * and compiles to `lw t8,72(sp)` (src) then `addiu t7,sp,52` (dest) -- same order
 * as ours.  So golden's func_151DC6A0 is NOT using that construct, or IDO's
 * scheduler broke the tie the other way for a reason not visible in the operand
 * spelling.  Ten spellings of the copy were measured (below) and every one emits
 * src-first.  A LIST-SCHEDULER PRIORITY ARGUMENT SAYS OURS IS THE "SENSIBLE" ONE:
 * `lw $t4` has the longer path to the end of the block (it feeds three loads),
 * so a critical-path scheduler should issue it first -- which is what we get and
 * what golden does NOT do.  That is why I think this is the positional /
 * tie-break class rather than a missing source idiom.
 *
 * THE PERMUTER IS STRUCTURALLY UNUSABLE HERE -- measured, per the standing rule:
 *     isolated (single-function file) : mism=43  n=136/135
 *     in-file  (real TU)              : mism=33  n=135/135
 * The instruction COUNT differs, so the permuter would be optimising a different
 * function.  Do not run it without first making its base.c the whole TU.
 *
 * ------------------------- HOW IT GOT FROM 1e6 TO 33 -------------------------
 * (Everything here is settled; do not re-derive it.)
 *  * THE TWIN.  func_150D66A4 in the MATCHED game_1028F0.c is the tail of this
 *    function almost verbatim:
 *        temp0 = func_150ADA20(); temp1 = func_150ADA20();
 *        func_15182670(0xFF,0xFF,0xFF,(u8)(temp0 % 0x38 + 0xC8), temp1 % 6 + 0x19, ...)
 *    and func_15150178's two parameter structs are spelled out in the MATCHED
 *    game_17CAF0.c (struct Local15150178Angles = 4 x s16; struct Local1514FF44Arg,
 *    whose unkC/unkE/unk10/unk14/unk18/unk1A/unk1C/unk20/unk24/unk25/unk28/unk2C/
 *    unk31/unk34/unk38/unk3C are exactly the 22 fields written below).  That gave
 *    n=135/135 on the FIRST build.
 *  * `u32` locals for the two func_150ADA20 results are REQUIRED.  functions.h
 *    declares `u8 func_150ADA20(void)`, so nesting the calls in the argument list
 *    spills BYTE temps (`sb $v0,0x2a($sp)`, frame 0x78); assigning to `u32` locals
 *    gives the word spills at 0x2C/0x30 and frame 0x80.  `% 5U` does NOT fix the
 *    nested form (measured 74).
 *  * THE LOCAL LAYOUT IS FULLY DETERMINED and all four slots are load-bearing:
 *        sp+0x2C rand0   sp+0x30 rand1   sp+0x34 randf
 *        sp+0x38 sp38 (8 bytes)          sp+0x40 sp40 (0x40 bytes)
 *    "first-declared highest" fixes the declaration order to
 *        Spawn sp40; Angles sp38; f32 randf; u32 rand1; u32 rand0;
 *    `randf` is register-only (it never touches its slot) but still costs its 4
 *    bytes at -O2 -g3, and that is what pushes rand0 down to 0x2C.  All 6
 *    permutations of the three scalars were measured: 39/41/43/45/45/45; this one
 *    is the unique 39, and it is the only one that puts rand0 at 0x2C.
 *
 * ------------------------- DO NOT REPEAT (all measured) -------------------------
 *   lever tried                                              score
 *   ---------------------------------------------------------------
 *   THIS FILE (best)                                          33
 *   angles block moved to each of 19 positions        47/39/39/33/33/33/40/41/…
 *   struct-copy statement moved to each of 22 positions  33,47,40,44,45,48,50,51,
 *                                                        50,52,59,61,62,60,62,63,
 *                                                        63,64,58,59,63,64
 *                                     -- and NONE of the 22 fixes index 40
 *   hill climb, all 21 adjacent field swaps, 8 rounds          33 (local optimum)
 *   every adjacent line-join in the body (41 joins)            33 (dead flat)
 *   all field lines joined into one line                       47
 *   call+copy on one line / call on one line / no blank line   33
 *   copy spelled  *(V*)&sp40 = *(V*)arg0                       33
 *   copy spelled  *(V*)&sp40.unk0 = …                          33
 *   copy spelled  *(V*)((s32)&sp40) = …                        33
 *   copy spelled  *(V*)((u8*)&sp40 + 0) = …                    33
 *   copy spelled  sp40.unk0 = *((V*)arg0 + 0)                  33
 *   copy spelled  sp40.unk0 = ((V*)arg0)[0]                    33
 *   copy spelled  ((V*)&sp40)[0] = ((V*)arg0)[0]               33
 *   copy spelled  (&sp40)[0].unk0 = *(V*)arg0                  33
 *   copy as THREE separate word assignments                   130 (frame 0x88,
 *                                        arg0 promoted to $s0 -- clearly wrong)
 *   one COMBINED struct {angles; spawn;} at sp+0x38            33 (all 3 variants)
 *   combined struct with f32 unk8[3] + array-decay 2nd arg     33 (all 3 variants)
 *   4th scalar local (V *src) -- fits at 0x28, frame stays     33 (decl last)
 *                                                              39 (decl first)
 *   arg0 typed s32 / void * / struct Vec3 *                    33 (all)
 *   nested calls + %U unsigned literals                        74
 *   nested calls (byte temps)                                  72/74
 *   Angles declared before Spawn                               58
 *   3 scalars in the other 5 orders                            41/43/45/45/45
 *
 * NEXT MOVES, in the order I would try them:
 *  1. Find a MATCHED function anywhere in the corpus whose 12-byte struct copy
 *     emits DEST-address first, and read its C.  That single example decides it.
 *     grep for `lw $at, 0x0(` / `sw $at, 0x0(` pairs in golden .s files where the
 *     dest `addiu` precedes the src `lw`.
 *  2. Make the permuter usable by giving it the whole TU as base.c (the isolated
 *     build is off by one instruction, so today's setup cannot be trusted here).
 *  3. Re-open only if a new law about IDO's block-entry scheduling tie-break
 *     appears; nothing in the current cookbook covers it.
 * ============================================================================ */

struct Vec3_151DC6A0 { s32 unk0[3]; };

struct Angles151DC6A0 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
};

struct Spawn151DC6A0 {
    struct Vec3_151DC6A0 unk0;
    s16 unkC;
    s16 unkE;
    f32 unk10;
    f32 unk14;
    s16 unk18;
    s16 unk1A;
    f32 unk1C;
    f32 unk20;
    u8  unk24;
    u8  unk25;
    u8  pad26[2];
    f32 unk28;
    f32 unk2C;
    u8  unk30;
    u8  unk31;
    u8  pad32[2];
    f32 unk34;
    u8  unk38;
    u8  pad39[3];
    f32 unk3C;
};

extern f32 D_800AB518;
extern f32 D_800AB51C;
extern f32 D_800AB520;
extern f32 D_800AB524;

extern void func_15103254(s16 arg0, u8 arg1, f32 arg2, s32 arg3, u8 arg4, u8 arg5, s32 arg6);
extern void func_15150178(struct Angles151DC6A0 *arg0, struct Spawn151DC6A0 *arg1, s32 arg2,
                          u8 arg3, s32 arg4);
extern void func_151D3F14(struct127 *arg0, u8 arg1, s32 arg2);
extern void func_15182670(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6,
                          s32 arg7);

void func_151DC6A0(struct127 *arg0, u8 arg1, s32 arg2) {
    struct Spawn151DC6A0 sp40;
    struct Angles151DC6A0 sp38;
    f32 randf;
    u32 rand1;
    u32 rand0;

    rand0 = func_150ADA20();
    rand1 = func_150ADA20();
    randf = func_150ADA68();
    func_15103254((s16)((rand0 % 5) + 0xC), (u8)((rand1 % 0x38) + 0xC8),
                  (randf * 600.0f) + D_800AB518, (s32)arg0, 0xFF, arg1, arg2);

    sp40.unk0 = *(struct Vec3_151DC6A0 *)arg0;
    sp40.unkC = 0xC;
    sp40.unkE = 7;
    sp38.unk0 = 0;
    sp38.unk2 = 0xFF;
    sp38.unk4 = -0x40;
    sp38.unk6 = 0x3C;
    sp40.unk10 = 8.0f;
    sp40.unk14 = 10.0f;
    sp40.unk18 = 0x24;
    sp40.unk1A = 0x3C;
    sp40.unk1C = D_800AB51C;
    sp40.unk20 = D_800AB520;
    sp40.unk24 = 0xC8;
    sp40.unk25 = 0x37;
    sp40.unk28 = 280.0f;
    sp40.unk2C = 390.0f;
    sp40.unk30 = 0;
    sp40.unk31 = 0xC;
    sp40.unk34 = D_800AB524;
    sp40.unk38 = 1;
    sp40.unk3C = 1.0f;
    func_15150178(&sp38, &sp40, 0, arg1, arg2);
    func_151D3F14(arg0, arg1, arg2);
    rand0 = func_150ADA20();
    rand1 = func_150ADA20();
    func_15182670(0xFF, 0xFF, 0xFF, (u8)((rand0 % 0x33) + 0x96), (rand1 % 5) + 8, 0, arg1,
                  arg2);
}
