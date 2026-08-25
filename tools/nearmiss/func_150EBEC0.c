/* NEAR-MISS PARK -- func_150EBEC0  (TU game_119370, 325 words)
 * ============================================================================
 * STATUS     : PARKED.  fastscore mism = 194, n = 325/325 (EXACT instruction
 *              count), frame = 0x110 (EXACT).  First differing row: idx 17.
 *              Rows 0..16 match exactly.
 * FILE KIND  : SELF-CONTAINED BODY TO SPLICE.  Replace the single line
 *              [the GLOBAL-ASM pragma line naming
 *               asm/nonmatchings/game_119370/func_150EBEC0.s -- deliberately not
 *               spelled out here, so this comment can never be picked up
 *               as a live pragma by asm-processor after the splice]
 *              in conker/src/game_119370.c with EVERYTHING in this file below
 *              this header comment -- the declaration block AND the function.
 *              Nothing has to be added anywhere else, and nothing may be left
 *              out: none of D_800A1500..D_800A1564 exists in variables.h,
 *              functions.h or structs.h, so splicing the function alone is a
 *              hard CCFAIL ("D_800A1500 undefined").  That TU also holds the
 *              already-decompiled func_150EC3D4 and func_150EC45C -- leave them
 *              alone; the pragma line is the only thing replaced.
 * VERIFIED    : that exact splice into a clean copy of the TU, scored with
 *                python3 tools/fastscore.py game_119370 func_150EBEC0 <copy>
 *              reproduces  mism=194  frame=-272  n=325/325, first diff idx 17.
 *
 * WHAT THIS FUNCTION IS
 * ----------------------------------------------------------------------------
 * A particle/effect spawner in the same family as the MATCHED
 *   conker/src/game_12B250.c  (func_150FDDA0 / func_150FE0B8)
 *   conker/src/game_12B7D0.c, game_12BD10.c, game_12C1E0.c, game_10CD70.c
 * Those matched siblings supply every callee prototype and the whole idiom set
 * (((u8 *)&argN)[3] for the trailing pair, `% NU` unsigned modulo, Header /
 * Header2, the func_15145EA4 pointer-pair, the 27-argument func_151C229C).
 * READ THEM FIRST -- they are what got this to 194 in one pass.
 *
 * WHAT IS SOLVED
 * ----------------------------------------------------------------------------
 *  * Every callee signature, every constant, every argument slot verified against
 *    golden's stack stores.  All the float pool constants resolved:
 *      D_800A154C=0.0076923  D_800A1550=2586  D_800A1554=1758  D_800A1558=0.001
 *      D_800A155C=1357  D_800A1560=0.1  D_800A1564=1077
 *      inline (low16==0): 130.0f 18.0f 29.0f 400.0f 262.0f 100.0f 80.0f 968.0f 4000.0f
 *      D_800A1500/D_800A150C are struct17 globals; D_800A1518/D_800A1530 are
 *      struct17 ARRAYS indexed by arg1 (the sll/subu/sll = *12 stride);
 *      D_800A1548 is a u8 array {2,4,0,0} indexed by arg1.
 *  * The discarded `func_150ADA20();` before the func_151C229C call is REAL --
 *    golden calls it and never reads $v0 (its sibling uses the value as arg11;
 *    here arg11 is the constant 0xFF).  Removing it loses an instruction.
 *  * frame 0x110, ra @0x74, outgoing-arg area 0x00..0x6F (func_151C229C has 27
 *    arguments), locals top-anchored at 0x110.
 *  * Locals, in declaration order (first-declared = highest address):
 *      s32 sp10C; struct17 sp100; struct17 spF4; struct17 spE8; struct17 *spE4;
 *      struct17 spD8; s32 spD0[2]; s32 spC8[2]; s32 spC4; s32 spC0;
 *      struct17 spB4; f32 spB0; f32 spAC; Header header; Header2 header2;
 *      f32 sp90[2]; f32 sp8C; u8 *sp7C; f32 sp84;
 *    Everything from 0x90 up is confirmed byte-exact against golden.
 *
 * REMAINING DIFF (194 rows) AND THE BLOCKER
 * ----------------------------------------------------------------------------
 * ONE root cause, and it is a COMMON-SUBEXPRESSION-ELIMINATION mismatch:
 *
 *   golden caches exactly one value in the compiler-temp area:
 *       addu $v0,$v1,$t9        ; v0 = &D_800A1548[ ((u8*)&arg1)[3] ]
 *       sw   $v0,0x7C($sp)
 *       ...  (six calls later)
 *       lw   $t8,0x7C($sp) ; lbu $a1,0($t8)
 *   and it RECOMPUTES  &spE8  three times (addiu $tX,$sp,0xE8) and
 *   &D_800A1518[idx] twice, fresh each time.
 *
 *   we do the opposite: IDO CSEs `&spE8` and `(s32)&D_800A1518[idx]` across the
 *   call sequence into two temps, and does NOT keep the D_800A1548 pointer.
 *   Those two extra temps are what pushed the frame to 0x118 in the first pass
 *   and what makes the integer temp rotation run one register ahead of golden
 *   from idx 17 onward (golden lui $t0 / we lui $t1, and the offset persists).
 *
 * So: the whole residual is "stop IDO CSE-ing &spE8 and &D_800A1518[idx] across
 * the calls, and let it keep &D_800A1548[idx] instead".  Both of the CSE'd
 * expressions appear literally twice in this source:
 *      spC0 = (s32)&spE8;   ... func_15102B38(..., (s32)&spE8, ...)
 *      spC4 = (s32)&D_800A1518[idx];  ... func_15102B38(..., (s32)&D_800A1518[idx], ...)
 * Golden's source must spell at least one side of each pair differently, or must
 * carry something else that changes IDO's PRE decision.  Trying to break the CSE
 * with `&spE8.unk0`, an explicit (struct17 *) cast, etc. is USELESS -- IDO
 * normalises all of them to the identical address expression (measured: byte-for-
 * byte identical objects).
 *
 * DO-NOT-REPEAT  (measured, with fastscore mism / frame / n)
 * ----------------------------------------------------------------------------
 *  first pass, every scalar a named local (21 decls)   318  frame 0x118  n=326
 *  drop the u8 *sp7C local entirely                    332  frame 0x118  n=328
 *  + trailing `s32 unused;` local                      318  frame 0x120
 *  sp7C typed s32 instead of u8 *                      318  frame 0x118
 *  (s16)(func_150ADA20() & 0xFF) inlined into
 *      func_15143874 instead of via a named local      234  frame 0x118  n=325
 *  spC0 = (s32)&spE8.unk0                              234  byte-identical
 *  func_15102B38 arg spelled (s32)&spE8.unk0           234  byte-identical
 *  spC0 = (s32)(struct17 *)&spE8                       234  byte-identical
 *  u8 arg1 / u8 arg2 parameters instead of the
 *      ((u8 *)&argN)[3] idiom                          281  frame 0x120  (WORSE:
 *                                                      the cast idiom is right,
 *                                                      exactly as in the siblings)
 *  full 32-way grid over which of {sp7C,sp80,sp84,
 *      sp88,sp8C} are named locals vs inline temps:
 *        none dropped / drop sp80 / drop sp88          234  frame 0x118
 *        drop sp80+sp84 (+more)                        261..266  frame 0x110 n=324
 *        drop sp80+sp88   <-- BEST                     196  frame 0x110 n=325
 *        drop sp80+sp84+sp88+sp8C                      261
 *  6 declaration orders of {sp8C, sp84, sp7C}:
 *        sp8C, sp7C, sp84   <-- current                194  frame 0x110 n=325
 *        sp7C, sp8C, sp84 / sp8C, sp84, sp7C           196
 *        the other three                               198
 *
 * NEXT MOVES
 * ----------------------------------------------------------------------------
 *  1. Attack the CSE directly.  The instruction count and frame are already
 *     exact, so any spelling that leaves those alone and removes one of the two
 *     spurious temps should collapse a large block of the 194 rows at once.
 *     Watch `sw $tX,0x78($sp)` (our &spE8 temp) and `sw $vX,0x84($sp)` (our
 *     &D_800A1518 temp) in the objdump -- they should both disappear and be
 *     replaced by a single `sw $v0,0x7C($sp)` holding &D_800A1548[idx].
 *  2. Only after that, look at the residual register naming.  Do NOT chase
 *     register numbers before the temp set matches -- the whole integer rotation
 *     is displaced by the extra temps.
 *  3. This function is a good permuter candidate once (1) is solved:
 *     conker/permuter_tu.sh setup game_119370 func_150EBEC0 <spliced TU> <dir>
 *     with PERMUTER_TU_REQUIRE_FRAME=272 (the base already satisfies it).
 *
 * DECLARATIONS
 * ----------------------------------------------------------------------------
 * They are already in this file, immediately below this comment -- splice them
 * with the function.  struct17, struct127, struct225, Header and Header2 come
 * from structs.h; func_150ADA20 (u8) and func_150ADA68 (f32) from functions.h.
 * ============================================================================
 */

/* ---------------------------------------------------------------------------
 * DECLARATIONS REQUIRED BY THE BODY BELOW.
 * None of these D_ symbols are in variables.h / functions.h / structs.h --
 * splicing the function without them is a hard CCFAIL ("D_800A1500 undefined").
 * They are part of this file: splice EVERYTHING below this banner, not just the
 * function.  game_119370.c declares nothing above its pragma except the three
 * standard includes, so this block is the complete requirement.
 * struct17, struct127, struct225, Header and Header2 all come from structs.h.
 * func_150ADA20 (u8) and func_150ADA68 (f32) are already in functions.h.
 * ------------------------------------------------------------------------- */
extern struct17 D_800A1500;
extern struct17 D_800A150C;
extern struct17 D_800A1518[];
extern struct17 D_800A1530[];
extern u8 D_800A1548[];
extern f32 D_800A154C;
extern f32 D_800A1550;
extern f32 D_800A1554;
extern f32 D_800A1558;
extern f32 D_800A155C;
extern f32 D_800A1560;
extern f32 D_800A1564;

extern s32 func_15145EA4(s32 *arg0, s32 *arg1, s32 arg2, s32 arg3);
extern s32 func_150AC9C0(f32, f32, f32, f32, f32, f32, void *, void *, f32 *, f32 *, f32 *, s32, s32 *, s32, f32);
extern void func_15143874(s32, f32, f32 *, f32 *);
extern struct225 *func_151602C0(Header *, Header2 *, s32, s32, s32, s32, u8, u8, s32, u8, s32);
extern void func_15102B38(s32, u8, s32, s32, f32 *, s32, s32, f32, s32, s32, s32, s32, u8, s32);
s32 func_151C229C(struct17 *arg0, struct17 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, s32 arg11, struct127 *arg12, s32 arg13, s32 arg14, s32 arg15, s32 arg16, s32 arg17, s32 arg18, s32 arg19, s32 arg20, f32 arg21, s32 arg22, s32 arg23, s32 arg24, s32 arg25, s32 arg26);

s32 func_150EBEC0(struct127 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp10C;
    struct17 sp100;
    struct17 spF4;
    struct17 spE8;
    struct17 *spE4;
    struct17 spD8;
    s32 spD0[2];
    s32 spC8[2];
    s32 spC4;
    s32 spC0;
    struct17 spB4;
    f32 spB0;
    f32 spAC;
    Header header;
    Header2 header2;
    f32 sp90[2];
    f32 sp8C;
    u8 *sp7C;
    f32 sp84;

    if (arg0 == 0) {
        return 0;
    }
    if (((u8 *)&arg1)[3] >= 2) {
        return 0;
    }
    if (arg0->unk1D4 == 0) {
        return 0;
    }

    spD0[0] = (s32)&D_800A1500;
    spD0[1] = (s32)&D_800A150C;
    spC8[0] = (s32)&sp100;
    spC8[1] = (s32)&spF4;
    func_15145EA4(spD0, spC8, (s32)arg0->unk1D4 + 0x80, 2);

    spF4.unk0 -= sp100.unk0;
    spF4.unk4 -= sp100.unk4;
    spF4.unk8 -= sp100.unk8;

    sp7C = &D_800A1548[((u8 *)&arg1)[3]];
    spC4 = (s32)&D_800A1518[((u8 *)&arg1)[3]];
    spC0 = (s32)&spE8;
    func_15145EA4(&spC4, &spC0, (*sp7C << 6) + (s32)arg0->unk1D4, 1);

    if (func_150AC9C0(sp100.unk0, sp100.unk4, sp100.unk8, spF4.unk0, spF4.unk4, spF4.unk8,
                      0, 0, &spB4.unk0, &spB4.unk4, &spB4.unk8, 0, 0, 0, 0.0f) != 0) {
        func_15143874((s16)(func_150ADA20() & 0xFF), func_150ADA68() * 80.0f, &spAC, &spB0);
        spB4.unk0 += spAC;
        spB4.unk8 += spB0;
        spD8.unk0 = spB4.unk0 - spE8.unk0;
        spD8.unk4 = spB4.unk4 - spE8.unk4;
        spD8.unk8 = spB4.unk8 - spE8.unk8;
        spE4 = &spD8;
    } else {
        spE4 = &spF4;
    }

    sp84 = func_150ADA68();
    sp8C = func_150ADA68();
    func_150ADA20();
    sp10C = func_151C229C(&spE8, spE4, 0, 0, 0, 0, 130.0f, D_800A154C,
                          sp84 * 18.0f + 29.0f, sp8C * 400.0f + 262.0f, 100.0f, 0xFF,
                          arg0, 1, 1, 0, 0, 0, 1, 3, 0x1A, 0.0f, 0xFF, -1, 0,
                          ((u8 *)&arg2)[3], arg3);

    header.unk0 = 3;
    header.unk1 = -1;
    header.unk2 = (func_150ADA20() % 3U) + 3;
    header.unk4 = 0;
    header2.unk0 = (s32)spE8.unk0;
    header2.unk4 = (s32)spE8.unk4;
    header2.unk8 = (s32)spE8.unk8;
    func_151602C0(&header, &header2, (func_150ADA20() % 0xDU) + 0x5A, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, ((u8 *)&arg2)[3], arg3);

    sp90[1] = ((func_150ADA68() * D_800A1550) + D_800A1554) * D_800A1558;
    sp90[0] = ((func_150ADA68() * D_800A155C) + 968.0f) * D_800A1560;
    func_15102B38((s32)arg0, *sp7C, (s32)&D_800A1518[((u8 *)&arg1)[3]], (s32)&D_800A1530[((u8 *)&arg1)[3]], sp90,
                  (func_150ADA20() % 6U) + 6, (func_150ADA20() % 0x34U) + 0xC1,
                  (func_150ADA68() * D_800A1564) + 4000.0f, (s32)&spE8, 0xFF,
                  0, -1, ((u8 *)&arg2)[3], arg3);
    return sp10C;
}
