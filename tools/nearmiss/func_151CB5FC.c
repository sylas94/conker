/* ================== PARKED -- NEAR MISS, score 76 / 199 instructions ==================
 * func_151CB5FC  (game_1F4650.c, 796 bytes, frame 0xE8)   wave 2026-08-14
 *
 * The #pragma GLOBAL_ASM is STILL LIVE in conker/src/game_1F4650.c.  Nothing in the
 * repo was changed for this function.  This file is the working state + the negatives.
 *
 * BEST MEASURED: mism = 76 (tools/fastscore.py, in-TU splice), frame -232 = golden,
 * instruction count 199/199 = golden.  Everything structural is settled; what is left
 * is a SCHEDULER TIE inside one basic block.
 *
 * ---------------------------------------------------------------------------------
 * WHAT IS PROVEN (do not re-derive)
 * ---------------------------------------------------------------------------------
 * SIGNATURE.  The prologue narrows a1 and a2 with `andi 0xFF` and a3 with `sll/sra 24`,
 * and reads the 5th parameter as `lbu 0xFB(sp)`.  So it is
 *     void func_151CB5FC(void *arg0, u8 arg1, u8 arg2, s8 arg3, u8 arg4)
 * NOT the `(void *, s32, u8, s8, u8)` the TU currently declares twice (lines ~358 and
 * ~519).  Both declarations must be corrected together or the definition will not
 * compile; the only caller passes a literal 2, so the change is codegen-neutral there.
 *
 * FRAME / DECLARATION LIST, read off the offsets (frame law, cookbook line 1140).
 * Frame 0xE8; homes end at 0xE8; sp90 base 0x90 (a0 = sp+0x90 at every call), sp34
 * base 0x34 (a1 = sp+0x34 at every memcpy).  sp34 spans 0x34..0x8B (0x58, the memcpy
 * length).  That leaves 0x8C..0x8F, i.e. ONE 4-byte home between the two aggregates.
 * 0x58 + 4 + 0x58 = 180 homes + 52 below = 232.  MEASURED, not assumed:
 *     sp90, void*, sp34                      -> sp34 @ 0x34, frame 232   (right)
 *     sp90, s32,   sp34                      -> sp34 @ 0x2C, frame 224   (wrong)
 *     sp90, void*, s32,   sp34               -> sp34 @ 0x30, frame 232   (wrong)
 *     sp90, s32,   sp34, void*               -> sp34 @ 0x34, frame 232   (right)  <-- used
 *     sp90, void*, sp34, s32                 -> sp34 @ 0x34, frame 232   (right, same score)
 * So the temp AREA is elastic: two scalars can coexist with 180 bytes of "expected"
 * homes because the compiler-temp region shrinks by 8 to compensate.  Reading a frame
 * as "sum(locals) is fixed, therefore N locals" is only valid once the temp area is
 * pinned -- here it was not, and the first reading (one scalar) was wrong.
 *
 * SEMANTICS.  Four particle spawns; sp90 is the emitter descriptor, sp34 the 0x58-byte
 * payload memcpy'd to +0x70 of whatever func_1515548C returns.  N_AL-style constants:
 * sp90.unk14 = (1 << (arg0[0x23D] + 0xB)) | ((arg2 ? 0x40 : 0) | 0x32), cleared of bit 1
 * before spawns 3/4; sp90.unk10 alternates 0x7B/0x7C; sp90.unk1E alternates 0xFF/0;
 * sp90.unk0 flips 88.0f -> -88.0f; sp34.unkE 0 -> 1.
 * sp34.unk18/unk20 index two 2-entry float tables by (D_80082FA0 == 1):
 *     D_800AAD84 = { -25.0f, -31.0f }      D_800AADAC = { 0.04f, 0.0322580635f }
 *
 * ---------------------------------------------------------------------------------
 * THE RESIDUAL, named
 * ---------------------------------------------------------------------------------
 * 76 differing words in these index ranges:
 *     (22,23) (30) (45,46) (50..110) (117..119) (129) (141) (148) (157,158) (177) (189)
 * The whole of idx 0..21, 24..29, 31..44, 47..49 is EXACT -- prologue, both value-
 * producing if/elses, the sp90.unk14 shift/or chain, every stack offset, every call
 * and every memcpy.
 *
 * Two independent causes, both scheduler/allocator ties:
 *
 * (1) idx45/46 -- WHERE THE `lui v0,%hi(D_80082FA0)` / `lw v0` PAIR IS SCHEDULED.
 *     Golden puts it at idx 76/77, between the last constant materialisation of the
 *     sp90 block and the first store of that block.  Every spelling I tried puts it at
 *     idx 45/46, immediately after the unk14 chain.  Everything in (50..110) is the
 *     downstream renaming caused by v0 being live 40 instructions longer than golden's.
 *     This also drags the 88.0f/91.0f `lui/mtc1` pairs ~25 instructions early.
 *
 * (2) idx22/23/30 -- WHICH OF v0/v1 HOLDS THE (arg3 == -1) ? 0 : 4 VALUE.
 *     Golden uses v1.  This is coupled to (1): the only spellings that put it in v1 are
 *     the ones where the SAME declared local also carries the arg2 flag, and those are
 *     exactly the spellings that get the `or` operand order wrong (see negatives).
 *     I could not find a spelling that satisfies both at once -- that is the wall.
 *
 * ---------------------------------------------------------------------------------
 * NEGATIVES -- every one measured, do not repeat
 * ---------------------------------------------------------------------------------
 * LINE-JOIN LEVER IS INERT ON THIS FUNCTION.  All 48 adjacent statement pairs joined
 *   one at a time -> ALL exactly 76.  Dead flat, like func_1505A3A8 / func_15162B28.
 *   (cookbook "The line-join lever is PER-FUNCTION".)  Do not spend a wave on it.
 *
 * `|` ASSOCIATION IS CANONICALISED, WITH ONE EXCEPTION.  Five spellings of
 *   sp90.unk14 -- `t|0x32|sh`, `(t|0x32)|sh`, `sh|(t|0x32)`, `sh|t|0x32`,
 *   `(u16)((t|0x32)|sh)` -- were BYTE-IDENTICAL to each other (167 at the time).
 *   IDO sinks the constant and emits `or` then `ori` regardless of parenthesisation.
 *   The exception that mattered: when the arg2 flag is an INLINE TERNARY rather than a
 *   named local, `sh | ((arg2 != 0) ? 0x40 : 0 | 0x32)` emits `ori` FIRST and then
 *   `or t8,t2,t7` -- golden's order (84 -> 76).  With a named local IDO applies the
 *   `<variable> op <temp>` canonicalisation (cookbook line 1357) and puts the temp
 *   first, `or t8,t7,t2`, and no rewriting escapes it (84 was the floor for all 5
 *   named-local spellings tried).
 *
 * A VALUE-PRODUCING if/else IS NOT THE SAME AS A TERNARY STORED DIRECTLY.
 *   `sp34.unkC = (arg3 == -1) ? 0 : 4;` SINKS the `sb` into both arms (two stores).
 *   Golden materialises into v1 and stores once, later -- that requires a named local.
 *   This is what forced the second scalar into the declaration list.
 *
 * READING D_80082FA0 ONCE INTO THE SPARE LOCAL MADE IT WORSE, NOT BETTER.
 *   `temp = D_80082FA0 == 1; unk18 = A[temp]; unk20 = B[temp];`  -> 105
 *   `temp = D_80082FA0; unk18 = A[temp == 1]; ...`               -> 105
 *   Two separate reads (IDO CSEs them into one load anyway)      -> 76
 *   Extending temp's live range re-colours registers as early as idx14.
 *
 * STATEMENT ORDER IS EXHAUSTED IN THE REGION THAT MATTERS.
 *   8 orderings of the block-1 statement group  -> 76/79/80/89/91/91/93 + 2 worse
 *   18 insertion positions for the two array statements inside the sp90 constant
 *       block and block 1                       -> 76/79/80/91/91/93/163/163...
 *   6 orderings of the sp90 constant block itself (ascending, golden's emission
 *       order, and four hybrids)                -> 89/90/90/165/166/166 (ascending won)
 *   None of these moved the `lui v0` placement by a single slot.
 *
 * ROUTE IF SOMEONE PICKS THIS UP: the question is not "which statement order" -- it is
 * "what makes IDO refuse to hoist a %hi/%lo global load 30 instructions".  Find a
 * MATCHED function in the corpus that reads a global late inside a long straight-line
 * store block and read its source shape.  Do not re-run the orderings above.
 * ====================================================================================
 */

extern f32 D_800AAD84[];
extern f32 D_800AADAC[];

void func_151CB5FC(void *arg0, u8 arg1, u8 arg2, s8 arg3, u8 arg4) {
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
    } struct_151CB5FC_sp90;
    typedef struct {
        void *unk0;
        f32 unk4;
        f32 unk8;
        u8  unkC;
        u8  unkD;
        u8  unkE;
        u8  padF;
        f32 unk10;
        f32 unk14;
        f32 unk18;
        f32 unk1C;
        f32 unk20;
        u8  pad24[0x30];
        s8  unk54;
        u8  pad55[3];
    } struct_151CB5FC_sp34;
    struct_151CB5FC_sp90 sp90;
    s32 temp;
    struct_151CB5FC_sp34 sp34;
    void *temp_v0;

    sp34.unk0 = arg0;
    sp34.unk4 = 255.0f;
    sp34.unk8 = 255.0f;
    sp34.unkD = arg1;
    if (arg3 == -1) {
        temp = 0;
    } else {
        temp = 4;
    }
    sp34.unkC = temp;
    sp34.unk54 = arg3;
    sp34.unk14 = 255.0f;
    sp34.unk10 = 0.0f;

    sp90.unk12 = 0x12C;
    sp90.unk8 = 49.0f;
    sp90.unkC = 18.0f;
    sp90.unk14 = (1 << (*(u8 *)((s32)arg0 + 0x23D) + 0xB)) | (((arg2 != 0) ? 0x40 : 0) | 0x32);
    sp90.unk16 = 1;
    sp90.unk18 = 0xFF;
    sp90.unk1A = 7;
    sp90.unk1B = 0xFF;
    sp90.unk1C = 0xFF;
    sp90.unk1D = 0xFF;
    sp90.unk1F = 0xFF;
    sp90.unk20 = 0xFF;
    sp90.unk21 = 0xFF;
    sp90.unk22 = 0xFF;
    sp90.unk23 = 0xFF;
    sp90.unk24 = 0;
    sp90.unk28 = 0x200004;
    sp90.unk2C = 0x1F0601;
    sp90.unk30 = 7;
    sp90.unk34 = 0x22;
    sp90.unk38 = 0x80;
    sp90.unk3C = 0x20;
    sp90.unk40 = 0;
    sp90.unk41 = 7;

    sp34.unkE = 0;
    sp90.unk1E = 0xFF;
    sp90.unk10 = 0x7B;
    sp34.unk1C = 0.0f;
    sp90.unk44 = *(u8 *)((s32)arg0 + 0x23D);
    sp90.unk0 = 88.0f;
    sp90.unk4 = 91.0f;
    sp34.unk18 = D_800AAD84[D_80082FA0 == 1];
    sp34.unk20 = D_800AADAC[D_80082FA0 == 1];
    temp_v0 = func_1515548C(&sp90, 5, 0, 0, 0x58, arg4, 0);
    if (temp_v0 != NULL) {
        memcpy((u8 *) temp_v0 + 0x70, &sp34, 0x58);
    }

    sp90.unk1E = 0;
    sp90.unk10 = 0x7C;
    temp_v0 = func_1515548C(&sp90, 5, 0, 0, 0x58, arg4, 0);
    if (temp_v0 != NULL) {
        memcpy((u8 *) temp_v0 + 0x70, &sp34, 0x58);
    }

    sp90.unk14 &= ~0x2;
    sp90.unk1E = 0xFF;
    sp90.unk10 = 0x7B;
    sp34.unkE = 1;
    sp90.unk0 = -88.0f;
    sp90.unk4 = 91.0f;
    temp_v0 = func_1515548C(&sp90, 5, 0, 0, 0x58, arg4, 0);
    if (temp_v0 != NULL) {
        memcpy((u8 *) temp_v0 + 0x70, &sp34, 0x58);
    }

    sp90.unk1E = 0;
    sp90.unk10 = 0x7C;
    temp_v0 = func_1515548C(&sp90, 5, 0, 0, 0x58, arg4, 0);
    if (temp_v0 != NULL) {
        memcpy((u8 *) temp_v0 + 0x70, &sp34, 0x58);
    }
}

/* ============ ADDENDUM, wave 2026-08-15 (spawner corpus campaign) ============
 * Added by the CC524/CC840 wave.  Nothing above was changed; the source below
 * the original header is untouched and still scores 76.
 *
 * TWO CROSS-CHECKS FROM THE TWINS (see tools/nearmiss/func_151CC524.c, whose
 * "FAMILY LAWS" block is the shared documentation for this whole family):
 *
 * 1. THIS FUNCTION'S FRAME CONFIRMS THAT IT REALLY DOES DECLARE LOCALS, so the
 *    two-scalar declaration list above is not an accident of the search.
 *    Measured on the twins: the corpus frame is
 *        [outgoing args][ra @0x24][TEMP AREA][payload 0x58][4-byte hole][desc 0x58]
 *    and the temp area is 8 bytes when the function declares no scalar locals
 *    (payload lands at 0x2C) and 16 bytes when it declares one or more
 *    (payload lands at 0x34).  func_151CB5FC's payload is at 0x34 -> locals.
 *    func_151CC524 / func_151CC840 have payload at 0x2C -> NO locals, and there
 *    the same `?:` value is coloured $v0 instead of this function's $v1.
 *
 * 2. THEREFORE THE `(arg3 == -1) ? 0 : 4` VALUE BEING IN $v1 HERE IS NOT A BUG
 *    TO FIX -- it is the signature of a function that declares a local, which
 *    this one does.  The open question in the header above (residual cause (2),
 *    "which of v0/v1 holds it") is ANSWERED: v1 is correct for this frame, and
 *    a spelling that moves it to v0 would move the frame off golden.  Spend the
 *    budget on residual cause (1) (the hoisted %hi/%lo) only.
 *
 * 3. ONE NEW LEVER THAT WAS NOT AVAILABLE WHEN THIS WAS PARKED, worth trying on
 *    the %hi/%lo hoist: on func_151CC524 a plain source reorder found by the
 *    permuter -- moving `sp90.unk44 = arg0[0x23D];` BEFORE `sp90.unk10 = ...`
 *    rather than after -- was worth 79 -> 67, and it is exactly a "value read
 *    late in a long store block" move.  The two array reads here
 *    (`sp34.unk18 = D_800AAD84[...]`, `sp34.unk20 = D_800AADAC[...]`) were
 *    swept for POSITION but, per the header, always as a PAIR and always
 *    together with the block-1 statements.  Sweeping the position of the
 *    unk44-style single-field reads (sp90.unk44, sp90.unk0, sp90.unk4)
 *    independently of them was NOT tried and is cheap.
 * =========================================================================== */
