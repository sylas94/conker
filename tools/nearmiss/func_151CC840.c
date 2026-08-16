/* ====== PARKED -- NEAR MISS, mism 73 / SHAPE_MISS 1 / 311 instructions ======
 * func_151CC840  (game_1F4650.c, 1244 bytes, frame 0xE0)     wave 2026-08-17
 *
 * READ tools/nearmiss/func_151CC524.c FIRST -- it carries the FAMILY LAWS and
 * the wave-2026-08-17 web-accounting result that both twins now turn on.  The
 * SOURCE BELOW IS UNCHANGED from 2026-08-16; the #pragma GLOBAL_ASM is STILL
 * LIVE and nothing in conker/src was changed for this function.
 *
 * ==========================================================================
 * WHAT IS NOW KNOWN, and it is NOT the same residual as the twin's
 * ==========================================================================
 * The twin's residual is a single uniform +3 rotation established in block 0.
 * THIS function's is NOT uniform, and its first 103 instructions -- the whole
 * of block 0, the flag branch, the unk14 build, the 0xFF block, the first
 * spawn and its memcpy -- are BYTE-IDENTICAL to golden, registers included.
 *
 * Golden's join block here starts at $t9 exactly as ours does:
 *     ori $t9  lw $t0  lbu $t1  addiu $t2  li1 $t3  sllv $t4  or $t5
 *     unk16 $t6  unk18 $t7  unk1A $t8
 * i.e. THERE IS NO BLOCK-0 WEB DEFICIT HERE.  That is what localises the
 * twin's deficit to the only two statements CC524's block 0 has and this one's
 * does not (`sp88.unk50 = 0.0f; sp88.unk54 = 0.0f;`) -- see the twin's file.
 *
 * THE DRIFT STARTS AT SPAWN 2 (idx103) and it is a WEB-ORDER difference, not a
 * rotation.  At the `sp88.unk14 &= ~0x6;` read-modify-write that opens spawn 2:
 *     ours   andi $t4   unk10(0x9D) $t5   0x58 $t6   1 $t7   arg5 $t0
 *     golden andi $t6   arg5 $t7          1 $t8      unk10(0x9D) $t9   0x58 $t0
 * Read as allocation order (the pool runs t6,t7,t8,t9,t0,...):
 *     golden: andi, arg5, 1, unk10, 0x58        -- five webs
 *     ours:   andi, unk10, 0x58, 1, _, _, arg5  -- seven
 * So golden is TWO webs ahead of us entering spawn 2 and evaluates the call's
 * stack arguments in a different order than we do.  Later spawns swing the
 * other way (spawn 4: ours andi $t0 vs golden andi $t8, and golden emits
 * `addiu $t0,$zero,0x9C` where we emit `ori t8,t0,0x4` -- a statement-order
 * difference between `unk10 = 0x9C` and `unk14 |= 4`).  THAT is where the next
 * wave's cheap wins are on this function: it is per-spawn statement order
 * inside a shape that is otherwise exact, not the twin's structural puzzle.
 *
 * ==========================================================================
 * LADDER (unchanged, each rung measured; fastscore / shapescore, in-TU splice)
 * ==========================================================================
 *     2026-08-15 parked source (1 carrier, 0x5C payload, u16 cast) . 109 / 9
 *     2 carriers, named flag local, u16 cast, RMW combined ......... 107 / 9
 *     2 carriers, named flag local, u16 cast, RMW split ............  94 / 3
 *     2 carriers, INLINE TERNARY, no cast, RMW split, unk16 post ...  73 / 1
 * The three structural facts that got it here, all re-verified:
 *   1. PAYLOAD STRUCT IS 0x58 (= the memcpy length), giving TWO 4-byte carriers
 *      in golden's 0xE0 frame; declaration order sp88, temp_v0, sp2C puts the
 *      payload at 0x2C and the descriptor at 0x88.
 *   2. INLINE TERNARY for the flag (-> $v0, and it blocks IDO's constant
 *      sinking for free) plus a declared `void *temp_v0` for the call result.
 *   3. THE FLAG-WORD EDITS ARE TWO STATEMENTS (LAW 8):
 *          sp88.unk14 &= ~0x6;   sp88.unk14 |= N;
 *      worth 9 points and 6 shape rows over `= (unk14 & ~6) | N`; IDO folds the
 *      intermediate store so n is unchanged -- a spelling, not a forcer.
 * `sp88.unk16 = 1` belongs AFTER the unk14 assignment here (worth 9), the
 * OPPOSITE of the twin.  Re-derive per function; never inherit.
 *
 * THE `(u16)` CAST -- VERDICT: DELETED.  73 without / 120 with.  (Honesty note
 * kept: on the named-flag-local variant of this function the cast is still
 * worth 11 points, 105 -> 94.  That variant is not the parked one and the cast
 * must be re-adjudicated if anyone revives it.)
 *
 * GOLDEN t-REGISTER OCCURRENCE COUNTS (311 instructions), measured this wave:
 *     t0:13 t1:16 t2:12 t3:18 t4:12 t5:14 t6:16 t7:17 t8:16 t9:18  v0:35 at:28
 * No register is an outlier, so -- unlike func_150130B4 and unlike the twin's
 * $t3 -- golden reserves NOTHING here.  Do not run the reservation hunt.
 *
 * SIGNATURE: void func_151CC840(void *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4,
 *                               u8 arg5)
 * TU prototype at line ~356 says (void*, s32, s32, s32, u8, u8) and must be
 * changed with the definition.  MEASURED SAFE: with both twins corrected to
 * all-u8, func_151C9DE8, func_151CAB78, func_151CB49C and func_151CC77C are
 * byte-identical (disassembly sha1).
 *
 * NO RODATA: every float here is lui+mtc1 materialisable (12.0, 7.0, 6.0, 55.0,
 * -55.0, 44.0, -44.0, 130.0, 0.0), so unlike the twin it needs no `extern f32`.
 *
 * SPAWN TABLE (a1 to func_1515548C is 0 for every spawn here, 9 on the twin):
 *   #  unk10  unk8/unkC   unk0     unk4     unk14 op
 *   1  0x64   12.0/12.0    0.0      0.0     initial build
 *   2  0x9D    7.0/ 7.0   55.0      0.0     &= ~6
 *   3  0x9D    -          -55.0     0.0     &= ~6 ; |= 2
 *   4  0x9C    -            0.0    55.0     &= ~6 ; |= 4
 *   5  0x9C    -            0.0   -55.0     &= ~6
 *   6  0x9E    6.0/ 6.0   44.0     44.0     |= 6      (NO mask -- golden has no andi)
 *   7  0x9E    -          -44.0    44.0     &= ~6 ; |= 4
 *   8  0x9E    -          -44.0   -44.0     &= ~6
 *   9  0x9E    -           44.0   -44.0     &= ~6 ; |= 2
 * ==========================================================================
 */

void func_151CC840(void *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5) {
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
    } struct_151CC840_sp88;
    typedef struct {
        void *unk0;
        f32 unk4;
        f32 unk8;
        u8  unkC;
        u8  unkD;
        u8  padE[0x4A];
    } struct_151CC840_sp2C;
    struct_151CC840_sp88 sp88;
    void *temp_v0;
    struct_151CC840_sp2C sp2C;

    sp2C.unk0 = arg0;
    sp2C.unk4 = 0.0f;
    sp2C.unkD = 0;
    sp2C.unkC = 0;
    sp2C.unk8 = 130.0f;

    sp88.unk12 = 0x12C;
    sp88.unk14 = (1 << (*(u8 *)((s32)arg0 + 0x23D) + 0xB)) | (((arg4 != 0) ? 0x40 : 0) | 0x10);
    sp88.unk16 = 1;
    sp88.unk18 = 0xFF;
    sp88.unk1A = 7;
    sp88.unk1B = arg1;
    sp88.unk1C = arg2;
    sp88.unk1D = arg3;
    sp88.unk1E = 0xB4;
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

    sp88.unk0 = 0.0f;
    sp88.unk4 = 0.0f;
    sp88.unk44 = *(u8 *)((s32)arg0 + 0x23D);
    sp88.unk10 = 0x64;
    sp88.unkC = 12.0f;
    sp88.unk8 = 12.0f;
    temp_v0 = func_1515548C(&sp88, 0, 0, 0, 0x58, arg5, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x70, &sp2C, 0x58);
    }

    sp88.unk14 &= ~0x6;
    sp88.unk10 = 0x9D;
    sp88.unkC = 7.0f;
    sp88.unk8 = 7.0f;
    sp88.unk0 = 55.0f;
    sp88.unk4 = 0.0f;
    temp_v0 = func_1515548C(&sp88, 0, 0, 0, 0x58, arg5, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x70, &sp2C, 0x58);
    }

    sp88.unk14 &= ~0x6;
    sp88.unk14 |= 2;
    sp88.unk0 = -55.0f;
    sp88.unk4 = 0.0f;
    temp_v0 = func_1515548C(&sp88, 0, 0, 0, 0x58, arg5, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x70, &sp2C, 0x58);
    }

    sp88.unk14 &= ~0x6;
    sp88.unk14 |= 4;
    sp88.unk10 = 0x9C;
    sp88.unk0 = 0.0f;
    sp88.unk4 = 55.0f;
    temp_v0 = func_1515548C(&sp88, 0, 0, 0, 0x58, arg5, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x70, &sp2C, 0x58);
    }

    sp88.unk14 &= ~0x6;
    sp88.unk0 = 0.0f;
    sp88.unk4 = -55.0f;
    temp_v0 = func_1515548C(&sp88, 0, 0, 0, 0x58, arg5, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x70, &sp2C, 0x58);
    }

    sp88.unk14 |= 6;
    sp88.unk10 = 0x9E;
    sp88.unkC = 6.0f;
    sp88.unk8 = 6.0f;
    sp88.unk0 = 44.0f;
    sp88.unk4 = 44.0f;
    temp_v0 = func_1515548C(&sp88, 0, 0, 0, 0x58, arg5, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x70, &sp2C, 0x58);
    }

    sp88.unk14 &= ~0x6;
    sp88.unk14 |= 4;
    sp88.unk0 = -44.0f;
    sp88.unk4 = 44.0f;
    temp_v0 = func_1515548C(&sp88, 0, 0, 0, 0x58, arg5, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x70, &sp2C, 0x58);
    }

    sp88.unk14 &= ~0x6;
    sp88.unk0 = -44.0f;
    sp88.unk4 = -44.0f;
    temp_v0 = func_1515548C(&sp88, 0, 0, 0, 0x58, arg5, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x70, &sp2C, 0x58);
    }

    sp88.unk14 &= ~0x6;
    sp88.unk14 |= 2;
    sp88.unk0 = 44.0f;
    sp88.unk4 = -44.0f;
    temp_v0 = func_1515548C(&sp88, 0, 0, 0, 0x58, arg5, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x70, &sp2C, 0x58);
    }
}

/* FAMILY LAWS: see tools/nearmiss/func_151CC524.c, REVISION 2 (2026-08-16). */
