/* ===========================================================================
 * func_150C4120  --  conker/src/game_F15D0.c   (900 B, frame 0xF0)
 * PARKED near-miss.  Cold start this wave.
 *
 * BEST SCORE SO FAR: 742  (asm-differ -o func_150C4120 -R --max-lines 4096;
 *                          identical with and without -R)  <-- THE FILE BELOW
 * Progression: 1692 (draft 1, whole instruction stream already correct)
 *              -> 1474 (reuse one variable for the func_15149130 result)
 *              -> 1306 (declare the scalars BEFORE the aggregates)
 *              -> 850  (write the two random bit-picks as inline ternaries so
 *                       they stop being declared, spilled locals)
 *              -> 742  (declare `payload` AFTER the four aggregates, leaving
 *                       only `temp_v0_2` before them)
 *
 * NOTE the task brief said "frame 0x60"; the golden prologue is
 * `addiu $sp,$sp,-0xF0`.
 *
 * ---------------------------------------------------------------------------
 * FRAME DECODE (golden) -- this is what made the function tractable.
 *   framesize 0xF0.
 *     0x00..0x23  arg build (func_15149130 takes 9 args, last at 0x20(sp))
 *     0x2C        ra
 *     0x30, 0x34  two 4-byte COMPILER TEMPS (see RESIDUAL 1)
 *     0x3C..0xEF  local home area = 180 bytes, EXACTLY four aggregates:
 *                     0x3C  16 bytes   Data150C4120   (copied from D_800A0340)
 *                     0x4C  16 bytes   Extra150C4120  (memcpy'd to ret+0xA8)
 *                     0x5C  120 bytes  Local150C4120  (passed to func_15130280)
 *                     0xD4  28 bytes   Payload150C4120(memcpy'd to ret+0x28)
 *                 16+16+120+28 = 180 = 0xB4, and 0x3C+0xB4 = 0xF0 exactly.
 *     0xF0..0xFC  a0..a3 parameter homes IN THE CALLER'S FRAME.  Golden writes
 *                 0xF4/0xF8/0xFC (arg1 is sign-extended to s16, arg2 and arg3
 *                 are re-read after their registers are clobbered) but never
 *                 0xF0, so arg0 is never assigned.
 *   First-declared local gets the HIGHEST address (confirmed against the
 *   matched sibling func_15131EE4 in game_15D730.c, whose `sp40` is declared
 *   before `sp2C` and sits above it).  Hence the declaration order below:
 *   spD4, sp5C, sp4C, sp3C.
 *
 * The three payload sizes are self-checking: func_15149130's arg6 is the
 * payload size (0x1C) and equals the first memcpy length; func_15130280's arg3
 * is the second payload size (0x10) and equals the second memcpy length.
 *
 * SIBLING THAT UNLOCKED THIS: func_15131EE4 in src/game_15D730.c is MATCHED
 * (no pragma) and builds the same pair of structs for the same func_15130280.
 * Local150C4120 is its `Struct15131EE4Local` with the trailing `u8 pad67[9]`
 * replaced by `pad67 / s16 unk68 / pad6A[2] / f32 unk6C / pad70[8]` to reach
 * 0x78 -- golden writes `sh zero,0xC4(sp)` (+0x68) and `swc1 $f8,0xC8(sp)`
 * (+0x6C), which that sibling does not.
 * The ternary shape of the func_15149130 call is copied verbatim from the
 * matched func_150E83AC in src/game_113D60.c line 406.
 *
 * RODATA CLASS: NOT BLOCKED.  Every float constant inlines via lui+mtc1 --
 * 0x442F0000 (700.0f), 0x3E800000 (0.25f), 0x3F800000 (1.0f), 0.0f (mtc1
 * zero).  D_800A03AC / D_800A03B0 / D_800A03B4 are ordinary extern f32 globals
 * reached by lui %hi / lwc1 %lo, not compiler literals.
 *
 * ---------------------------------------------------------------------------
 * RESIDUAL, classified.  The whole instruction stream already matches golden
 * one-for-one; there is no missing, extra or reordered instruction anywhere.
 *
 * 1. ALLOCATION / FRAME (8 bytes, and it is the reason for every remaining
 *    stack-offset row).  My frame is 0xF8, golden's is 0xF0.
 *    The rule I measured: IDO gives every declared scalar local that ends up
 *    SPILLED an 8-byte-granular home at the TOP of the home area (above the
 *    aggregates), whereas an unnamed value spilled by the compiler gets a
 *    packed 4-byte COMPILER TEMP just above `ra`.  Golden's two spilled values
 *    live at 0x30 and 0x34 -- 4 bytes each, compiler temps -- so golden's C
 *    declares NO spilled scalar at all.
 *    I removed one of the two (see MEASURED, variant G).  The one left is the
 *    payload pointer `ret_of_func_15149130 + 0x28`, which is live across
 *    func_15130280 and so spills; golden CSEs the address expression into the
 *    temp at 0x30 (`sw a0,0x30(sp)` in the memcpy delay slot, `lw v1,0x30(sp)`
 *    afterwards).  To reproduce that the value must be an unnamed common
 *    subexpression, but IDO constant-folds `((T *)(base + 0x28))->unkC` into
 *    `base + 0x34`, so the subexpression `base + 0x28` never appears twice and
 *    IDO keeps the base pointer live instead.  THAT FOLD IS THE BLOCKER.
 *
 * 2. as1 TEMP-REGISTER ROTATION (the rest of the rows, all flagged `r`).
 *    From `mfhi` at 0x13C onwards my temp registers run exactly 2 behind
 *    golden's (golden t5/t6/t7/t1, mine t3/t4/t5/t6), and the offset stays
 *    constant to the end of the function.  Per the project note this is a
 *    rotation counter, not a construct: golden consumes two more temp
 *    registers than I do before that point.  It should fall out once
 *    residual 1 is fixed, because the missing consumer is the CSE temp for
 *    `base + 0x28` (golden materialises it into `a0` and spills it, mine
 *    never creates it).
 *
 * ---------------------------------------------------------------------------
 * MEASURED (every variant, with its score and resulting frame)
 *   1692  draft 1.  Whole instruction stream already correct; frame 0x100.
 *   1922  + a declared `Payload150C4120 *payload` holding
 *           `(s32)temp_v0 + 0x28`, plus `(temp | temp_v1) | 0xC000` grouping.
 *         The or/ori grouping fix is RIGHT and is kept -- golden emits
 *         `or t9,v0,v1` then `ori t4,t9,0xc000`, so the source groups the two
 *         random values together first and ORs 0xC000 in last; writing
 *         `temp | 0xC000 | temp_v1` gives `ori` before `or`.  The declared
 *         `payload` costs 8 frame bytes, hence the worse total.
 *   1922  A: the 0x80 pick written as a ternary instead of if/else, with the
 *           other scalars unchanged.  NO CHANGE to score OR frame -- that
 *           value was never spilled, so naming it is free.
 *   1474  C: reuse ONE variable for the func_15149130 result and the +0x28
 *           pointer (drops `struct260 *temp_v0`).  frame 0x100.
 *   1480  D: C + drop `temp_v0_2` by writing
 *           `payload->unkC = (s32)func_15130280(...)` and re-reading
 *           `payload->unkC` for the null test and the memcpy.  frame 0x100 --
 *           `temp_v0_2` was never spilled, so dropping it bought nothing and
 *           cost 6 points.  REJECTED.
 *   1474  F: `payload` typed `s32` instead of a pointer.  No effect.
 *   1306  E: C + declare the scalars BEFORE the four aggregates.  frame still
 *           0x100, but this is what put all four aggregates at golden's exact
 *           addresses (0x3C / 0x4C / 0x5C / 0xD4) -- every local-struct row in
 *           the function became correct.  KEPT.
 *    850  G: E + both random bit-picks written as inline ternaries inside the
 *           unk58 expression, deleting the `temp_v1` and `temp` declarations.
 *           frame 0xF8.  KEPT.
 *    860  I: G + the payload written as the repeated expression
 *           `(s32)payload + 0x28` at both use sites, hoping IDO would CSE it
 *           into a compiler temp.  frame still 0xF8 -- IDO folded the +0xC
 *           into the second use and kept the base pointer live instead.
 *           This is the direct evidence for the blocker in residual 1.
 *    782  J: G + a separate `struct260 *temp_v0` for the call result so
 *           `payload` is assigned exactly ONCE.  frame grew to 0x100 (temp_v0
 *           is spilled too) yet the score IMPROVED by 68 -- the extra spill
 *           consumes the temp registers that residual 2 says golden consumes.
 *           Good evidence that residual 2 really is downstream of residual 1.
 *    782  K: J with temp_v0 declared second instead of first.  IDENTICAL
 *           score -- declaration order among the leading scalars is not the
 *           axis here.
 *    742  L: G + `payload` declared AFTER the four aggregates (only
 *           `temp_v0_2` stays in front).  frame 0xF8.  BEST -- THIS FILE.
 *    994  M: J + payload-last.  frame 0x100.  REJECTED.
 *   1418  N: J + every scalar declared last.  frame 0x100.  REJECTED.
 *    954  O: L + `temp_v0_2` also declared last.  frame 0xF8.  REJECTED --
 *           so `temp_v0_2` genuinely belongs BEFORE the aggregates and
 *           `payload` genuinely belongs AFTER them.
 *
 * TODO next: find a spelling of the second use that keeps `base + 0x28` intact
 * as a common subexpression (so it becomes the 0x30 compiler temp) without
 * declaring a variable for it.  Everything else in this function is already
 * byte-shaped like golden.
 * =========================================================================== */

typedef struct {
    s32 unk0[4];
} Data150C4120;

typedef struct {
    u8  unk0;
    u8  unk1;
    u8  unk2;
    u8  unk3;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} Extra150C4120;

typedef struct {
    struct127 *unk0;
    u8  unk4;
    f32 unk8;
    s32 unkC;
    f32 unk10;
    s16 unk14;
    u8  unk16;
    s32 unk18;
} Payload150C4120;

typedef struct {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    s32 unkC;
    s32 unk10;
    u8  unk14;
    u8  unk15;
    u8  unk16;
    u8  unk17;
    u8  unk18;
    u8  unk19;
    u8  unk1A;
    u8  unk1B;
    u8  unk1C;
    u8  unk1D;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    struct17 unk30;
    struct17 unk3C;
    struct17 unk48;
    f32 unk54;
    s32 unk58;
    s32 unk5C;
    u8  unk60;
    u8  unk61;
    u8  unk62;
    s8  unk63;
    s8  unk64;
    u8  unk65;
    u8  unk66;
    u8  pad67;
    s16 unk68;
    u8  pad6A[2];
    f32 unk6C;
    u8  pad70[8];
} Local150C4120;

extern Data150C4120 D_800A0340;
extern f32 D_800A03AC;
extern f32 D_800A03B0;
extern f32 D_800A03B4;

void func_150C4120(struct127 *arg0, s16 arg1, u8 arg2, s32 arg3) {
    void *temp_v0_2;
    Payload150C4120 spD4;
    Local150C4120 sp5C;
    Extra150C4120 sp4C;
    Data150C4120 sp3C;
    Payload150C4120 *payload;

    spD4.unk0 = arg0;
    spD4.unk4 = arg0->unique_id;
    spD4.unk8 = 0.0f;
    spD4.unkC = 0;
    spD4.unk10 = 0.0f;
    spD4.unk14 = -1;
    spD4.unk16 = 0;
    spD4.unk18 = 0;
    if (arg0->id == 0x34) {
        spD4.unk14 = 0x54;
        spD4.unk16 = 1;
    }

    payload = (Payload150C4120 *)func_15149130((arg1 == -1) ? 0x12C : arg1, -1, 0x53, -1,
                                              (arg1 == -1) ? 0 : 1, 0x40, (struct37 *)0x1C, arg2, arg3);
    if (payload != NULL) {
        payload = (Payload150C4120 *)((s32)payload + 0x28);
        memcpy(payload, &spD4, 0x1C);

        sp3C = D_800A0340;
        sp4C.unk0 = func_150ADA20();
        sp4C.unk1 = func_150ADA20();
        sp5C.unk2C = 700.0f;
        sp5C.unk28 = 700.0f;
        sp4C.unk4 = 700.0f;
        sp4C.unk2 = (func_150ADA20() % 6U) + 5;
        sp4C.unk3 = (func_150ADA20() % 6U) + 5;
        sp4C.unk8 = ((func_150ADA68() * 0.25f) + D_800A03AC) * sp4C.unk4;
        sp4C.unkC = ((func_150ADA68() * 0.25f) + D_800A03B0) * sp4C.unk4;

        sp5C.unk1D = sp3C.unk0[func_150ADA20() & 3];
        sp5C.unk8 = 0x2203;
        sp5C.unk0 = 0x200005;
        sp5C.unk4 = 0;
        sp5C.unkC = 0;
        sp5C.unk10 = 0;
        sp5C.unk14 = 0;
        sp5C.unk15 = 0;
        sp5C.unk16 = 0;
        sp5C.unk17 = 0xFF;
        sp5C.unk18 = 0;
        sp5C.unk19 = 0;
        sp5C.unk1A = 0;
        sp5C.unk1B = 0xFF;
        sp5C.unk1C = 0xFF;
        sp5C.unk30 = *(struct17 *)&D_800A5480;
        sp5C.unk3C = *(struct17 *)&D_800A5480;
        sp5C.unk48 = *(struct17 *)&D_800A5480;
        sp5C.unk22 = 1;
        sp5C.unk54 = 0.0f;
        sp5C.unk24 = 1.0f;

        sp5C.unk58 = (((func_150ADA20() & 1) ? 0x40 : 0) | ((func_150ADA20() & 1) ? 0x80 : 0)) | 0xC000;
        sp5C.unkA = 0x12C;
        sp5C.unk1E = 1;
        sp5C.unk20 = 0xFF;
        sp5C.unk60 = 6;
        sp5C.unk61 = 8;
        sp5C.unk64 = -1;
        sp5C.unk62 = 0x26;
        sp5C.unk63 = -1;
        sp5C.unk65 = 0;
        sp5C.unk5C = 0;
        sp5C.unk66 = 0xFF;
        sp5C.unk68 = 0;
        sp5C.unk6C = D_800A03B4;

        temp_v0_2 = func_15130280(&sp5C, 1, 0, 0x10, arg2, arg3);
        payload->unkC = (s32)temp_v0_2;
        if (temp_v0_2 != NULL) {
            memcpy((u8 *)temp_v0_2 + 0xA8, &sp4C, 0x10);
        }
    }
}
