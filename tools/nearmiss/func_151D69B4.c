/* ============================================================================
 * func_151D69B4  (game_203E20.c)  --  PARKED, 2026-08-21.
 *
 * FILE KIND: BODY-TO-SPLICE.  The text below (from the first `typedef` to the
 * final `}`) replaces exactly this one line of conker/src/game_203E20.c:
 *     #pragma GLOBAL_ASM("asm/nonmatchings/game_203E20/func_151D69B4.s")
 * Nothing else in the TU is touched; the sibling pragma for func_151D6BFC
 * stays.  Every typedef and extern needed is present below as LIVE C.
 *
 * SCORE (fastscore.py game_203E20 func_151D69B4, in-file splice, -O2 -g3):
 *     mism = 57      n = 146/146      frame = -224 (0xE0) == golden
 *
 * WHAT IS ALREADY EXACT
 *   * instructions 0..75 -- the WHOLE first struct build and the whole
 *     func_15153F18 call -- are byte-identical to golden.
 *   * the frame is exact: 0xE0 = outgoing(0x20) + saved $s0/$ra(0x8) +
 *     Spawn15150178 b(0x48) + Spawn15153F18 a(0x4C) + Struct1504715C sp(0x24).
 *   * the INSTRUCTION MULTISET of the whole function equals golden's, modulo
 *     the 17 relocation-bearing words (jal targets and %hi/%lo pairs are zero
 *     in an unlinked .o).  Measured with a Counter diff: extra 17 / missing 17,
 *     and every one of those 34 words is a reloc word.
 *   * REGISTER ALLOCATION IS EXACT, including the temp-register rotation:
 *     golden's second region assigns $t7=0xF, $t8=6, $t9=0xFF, $t0=-0x40,
 *     $t1=0xC, $t2=0x3C, $t3=0x2D, $t4=0xC8, $t5=0x37, $t6=1, $t7=9, $t8=1,
 *     with $t4/$t5/$t6 reserved for the three `lh` loads -- this file
 *     reproduces that exactly.
 *
 * THE ONLY REMAINING BLOCKER: the LIST SCHEDULER'S INTERLEAVE of the second
 * struct build.  Golden starts the post-call region with the CSE'd 1.0f:
 *     gold  lui $at,0x3F80 / mtc1 $at,$f0 / addiu $t7,0xF / lh $t4,0x10($s0)
 *     ours  lh $t4,0x10($s0) / lui $at,0x3F80 / mtc1 $at,$f0 / mtc1 $t4,$f6
 * i.e. golden schedules the 1.0f pair and one immediate BEFORE the first `lh`,
 * ours schedules the `lh` first.  Everything after that is the same 70
 * instructions in a different interleave, which is where all 57 rows live.
 *
 * ============================ DO NOT REPEAT =================================
 * All scores in-file, n=146/146 unless noted.
 *
 *  variant                                                        mism
 *  ------------------------------------------------------------  ------
 *  (s32)&sp cast in BOTH calls  (the first thing tried)             113   <-- and n=147, frame 0xE8
 *      IDO CSEs the integer expression `(s32)&sp` into a stack
 *      temp (`sw $a2,0x2C(sp)` / `lw $a2,0x2C(sp)`), which adds an
 *      8-byte compiler temp at the BOTTOM of the local area and
 *      shifts every local by 8.  Passing `&sp` with a POINTER
 *      parameter type re-materialises the address at each call
 *      site: 113 -> 57 and the frame becomes exact.  THIS WAS THE
 *      SINGLE BIGGEST LEVER; do not undo it.
 *  block-2 statement order = twin func_150C2700 (game_EF410)         57
 *  block-2 order with b.unk10 moved next to unk08/unk0C (SHIPPED)    57
 *  block-2 order with b.unk10 after b.unk16                          56
 *  hill climb, move-one neighbourhood, 2 full rounds (~1100 evals)    54
 *      best order 10,14,16,08,3C,00,0C,02,04,06,20,22,2C,2D,38,
 *                 39,40,44,18,1C,24,28,30,34
 *      REJECTED AS A REGRESSION EVEN THOUGH THE ROW COUNT IS LOWER:
 *      its multiset diff is extra 29 / missing 29 -- it emits
 *      `lh $t4,0x14($s0)` and `addiu $t5,0xF`, i.e. it loads a
 *      DIFFERENT vec component first and shifts the whole temp
 *      rotation by one.  The shipped 57 has the multiset and the
 *      registers exactly right.  ORDERING IS ESSENTIALLY INERT
 *      HERE (57 -> 54 over ~1100 permutations): stop permuting.
 *  b.unk3C = 1.0f as the FIRST statement of block 2                  54
 *      Interesting but a dead end: it DOES put `lui $at,0x3F80 /
 *      mtc1 $at,$f0` at instructions 76/77 exactly as golden has
 *      them -- but it then also emits `swc1 $f0,0x64($sp)` at
 *      instruction 80, whereas golden stores 0x64 at instruction
 *      129 (16th store).  So IDO materialises the CSE'd float at
 *      its FIRST USE, not at the top of the region, and there is no
 *      statement order that puts the load first and the store 16th.
 *      The hoist golden shows must come from something other than
 *      statement order.
 *  b.unk14/b.unk16 (0xF, 6) moved before the vec                     58
 *  b.unk18/b.unk1C (the 10.0f/6.0f pair) moved early                 57
 *  b.unk44 and b.unk3C both first                                    56
 *
 * ================== HOW THE DATA MODEL WAS RECOVERED ========================
 * Two matched twins supply the entire model and should be re-read before any
 * further work:
 *   * conker/src/game_16EE20.c func_15142180 -- builds `struct
 *     conker15142180` and calls func_15153F18(&s, &s.unk08, 0, 0xFF, 1).
 *     That struct is Spawn15153F18 below, field for field, and its statement
 *     order is the order used here.
 *   * conker/src/game_EF410.c func_150C2700 -- builds `Struct150C2700` and
 *     calls func_15150178(&s, s.unk18, 0, argE, 1).  NB its field comments are
 *     labelled +0x10 too high (the struct really starts at 0x00); once that is
 *     corrected it is Spawn15150178 below, field for field.
 *   * conker/src/game_17CAF0.c holds the MATCHED definitions of both callees:
 *     func_15150178 / func_15153F18 both take (Angles*, Arg*, s32, u8, s32),
 *     so the single local struct in each block is really `Angles` (4 s16) then
 *     the Arg struct at +8 -- which is why both calls pass (&s, &s.unk08, ...).
 *   * conker/src/game_1312F0.c gives Struct1504715C (0x24 bytes) and the
 *     one-argument call form `func_1504715C(&sp)` used here (also in
 *     game_981E0.c func_15074C00).
 *
 * The two float pools are genuine externs, not a rodata-migration candidate:
 * golden RELOADS each of them with its own lui %hi / lwc1 %lo pair, and they
 * are real named symbols in asm/data/24FD10.rodata.s
 * (D_800AB25C=2.49, D_800AB260=2.03, D_800AB264=0.608, D_800AB268=0.257,
 *  D_800AB26C=0.4, D_800AB270, D_800AB274).  The inline literals 17.0f, 3.5f,
 * 10.0f, 6.0f, 44.0f, 88.0f, 1.0f all have low16==0 and materialise with
 * lui+mtc1, so this function needs NO yaml rodata migration.
 *
 * SEMANTICS: func_151D69B4(obj) reads obj->unk10/12/14 as an s16 x/y/z
 * position, converts it to float, and fires two particle bursts at that point
 * (func_15153F18 = one family, func_15150178 = another), both passing the
 * 0x24-byte block that func_1504715C filled as the third argument.
 * ==========================================================================*/

typedef struct {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ u8  unk1C;
    /* 0x1D */ u8  pad1D[0x7];
} Struct1504715C; /* 0x24 */

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 unk32;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ s16 unk36;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ s8  unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ s16 unk44;
    /* 0x46 */ s16 unk46;
    /* 0x48 */ s32 unk48;
} Spawn15153F18; /* 0x4C */

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ u8  unk2C;
    /* 0x2D */ s8  unk2D;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ s8  unk38;
    /* 0x39 */ u8  unk39;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ s8  unk40;
    /* 0x44 */ f32 unk44;
} Spawn15150178; /* 0x48 */

typedef struct {
    /* 0x00 */ u8  pad0[0x10];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
} Obj151D69B4;

extern void func_1504715C(Struct1504715C *);
extern void func_15153F18(Spawn15153F18 *, f32 *, Struct1504715C *, u8, s32);
extern void func_15150178(Spawn15150178 *, f32 *, Struct1504715C *, u8, s32);
extern f32 D_800AB25C;
extern f32 D_800AB260;
extern f32 D_800AB264;
extern f32 D_800AB268;
extern f32 D_800AB26C;
extern f32 D_800AB270;
extern f32 D_800AB274;

void func_151D69B4(Obj151D69B4 *arg0) {
    Struct1504715C sp;
    Spawn15153F18 a;
    Spawn15150178 b;

    func_1504715C(&sp);

    a.unk08 = arg0->unk10;
    a.unk0C = arg0->unk12;
    a.unk10 = arg0->unk14;
    a.unk2C = 3;
    a.unk2E = 3;
    a.unk02 = 0xFF;
    a.unk04 = -0x2B;
    a.unk06 = 0x20;
    a.unk14 = D_800AB25C;
    a.unk18 = D_800AB260;
    a.unk1C = D_800AB264;
    a.unk20 = D_800AB268;
    a.unk24 = 17.0f;
    a.unk28 = 3.5f;
    a.unk00 = 0;
    a.unk30 = 3;
    a.unk32 = 2;
    a.unk34 = 0x28;
    a.unk36 = 0x14;
    a.unk38 = 0x9B;
    a.unk3A = 0x64;
    a.unk40 = D_800AB26C;
    a.unk44 = 0x10;
    a.unk46 = 0xF;
    a.unk48 = 0;
    a.unk3C = 9;
    func_15153F18(&a, &a.unk08, &sp, 0xFF, 1);

    b.unk08 = arg0->unk10;
    b.unk0C = arg0->unk12;
    b.unk10 = arg0->unk14;
    b.unk14 = 0xF;
    b.unk16 = 6;
    b.unk00 = 0;
    b.unk02 = 0xFF;
    b.unk04 = -0x40;
    b.unk06 = 0xC;
    b.unk20 = 0x3C;
    b.unk22 = 0x2D;
    b.unk2C = 0xC8;
    b.unk2D = 0x37;
    b.unk38 = 1;
    b.unk39 = 9;
    b.unk3C = 1.0f;
    b.unk40 = 0;
    b.unk44 = 1.0f;
    b.unk18 = 10.0f;
    b.unk1C = 6.0f;
    b.unk24 = D_800AB270;
    b.unk28 = D_800AB274;
    b.unk30 = 44.0f;
    b.unk34 = 88.0f;
    func_15150178(&b, &b.unk08, &sp, 0xFF, 1);
}
