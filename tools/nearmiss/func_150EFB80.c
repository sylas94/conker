/* ===========================================================================
 * func_150EFB80  --  game_11C2B0.c  --  840 bytes  --  cold decompile
 * PARKED at 935 (with AND without -R).  Base: draft2 (u8 type fix on top of
 * draft1 @ 945).
 *
 * VERDICT: RODATA-BLOCKED.  Single cause, fully diagnosed (see below).
 * Everything from the prologue through the end of the pre-loop init block is
 * BYTE-IDENTICAL to golden; the entire residual is one loop-invariant
 * allocation decision forced by having to spell two float constants as
 * `extern f32` instead of as literals.
 *
 * ---------------------------------------------------------------------------
 * FRAME DECODE (this part is SETTLED and reproduces exactly)
 * ---------------------------------------------------------------------------
 * framesize 0xF0.  arg-build [0x00,0x20).  saved regs [0x20,0x78):
 *   f20 20 f22 28 f24 30 f26 38 f28 40 f30 48 | s0 50 s1 54 s2 58 s3 5C
 *   s4 60 s5 64 s6 68 s7 6C fp 70 ra 74
 * Home area is laid out TOP-DOWN in declaration order and ENDS at framesize:
 *   [0xEC,0xF0) decl#1   4B   -> sub    (s0 = arg0+0x28)
 *   [0xE8,0xEC) decl#2   4B   -> rand0  (s1)
 *   [0xE4,0xE8) decl#3   4B   -> rand1  (s2)
 *   [0xC8,0xE4) decl#4  0x1C  -> param  (s4 = sp+0xC8; ->unk10 at 0xD8 = C8+10)
 *   [0x8C,0xC8) decl#5  0x3C  -> spawn  (a2 of func_1515C2F0; unk04 at 0x90=s7)
 * sum = 4+4+4+0x1C+0x3C = 0x64;  0xF0-0x64 = 0x8C = lowest referenced slot. QED.
 * temp area = [0x78,0x8C) = 20 bytes.
 *
 * The two struct sizes were CALIBRATED against the matched sibling
 * func_15152B38 (game_17CAF0.c, framesize 0xB0): there param sits at
 * [0x94,0xB0) -- ending exactly at framesize, so 0x1C -- and spawn at
 * [0x58,0x94), so 0x3C; and its source really does declare
 * `param; spawn; count; rand0; rand1;`.  func_1515C2F0 also does
 * `memcpy(ret->unk98, arg2, 0x3C)`, independently confirming spawn == 0x3C.
 *
 * ---------------------------------------------------------------------------
 * THE RESIDUAL -- one cause, ~8 rows + the address shift they cause
 * ---------------------------------------------------------------------------
 * Golden hoists the DIVISOR CONSTANT 0x65 into $s8 for the loop:
 *      f20:  li    s8,0x65
 *      ffc:  divu  zero,v0,s8      + bnez s8 / break 7   (as1 div-by-0 guard)
 *      fdc:  lui   at,%hi(D_800A1828)  ;  fe0: lwc1 $f4,%lo(D_800A1828)(at)
 * Mine hoists the ADDRESS of D_800A1828 into $s8 instead:
 *      ed8:  lui   s8,%hi(D_800A1828)  ; f24: addiu s8,s8,%lo(D_800A1828)
 *      fe0:  lwc1  $f4,0(s8)
 *      ffc:  li    at,0x65 ; divu zero,v0,at   (no guard: at is a known literal)
 *
 * All 9 callee-saved regs are occupied identically in both builds
 * (s0=sub s1=rand0 s2=rand1 s3=arg0 s4=&param s5=3 s6=0x1F s7=&spawn.unk04);
 * only what lands in s8 differs.  Both candidates save exactly one instruction
 * per iteration, so it is a pure ranking tie-break, and the ranking is by
 * SOURCE POSITION OF FIRST USE:
 *      mine   : 3(stmt1), 0x1F(stmt6), &D_800A1828(stmt7), 0x65(stmt8) -> first 3 win
 *      golden : 3,        0x1F,        0x65                            -> first 3 win
 * Golden's list can only look like that if &D_800A1828 / &D_800A182C are NOT
 * variable-address candidates at all -- i.e. in the original they are FLOAT
 * LITERALS that IDO emitted into this TU's own .rodata, which the optimizer
 * references as constants and never hoists.  We cannot spell them as literals
 * because live-C .rodata is /DISCARD/ed project-wide, and neither value is
 * lui-able:
 *      D_800A1828 = 0xC4DC2000 = -1761.0f  (low16 0x2000 != 0)
 *      D_800A182C = 0x3A83126F =  0.001f   (low16 0x126F != 0)
 *      D_800A1824 = 0x3A83126F =  0.001f   (also non-inlinable, but it is read
 *                                           OUTSIDE the loop so it costs nothing)
 * Block: conker/asm/data/246140.rodata.s, symbols D_800A1824/1828/182C at
 * 0x800A1824..0x800A182F.  Migration granularity is the whole 246140 rodata
 * block, and that block still has many stubbed consumers in game_11C2B0.c
 * (16 GLOBAL_ASM pragmas remain in the TU, incl. func_150F0318/0380/03E8/03F8/
 * 0A24/0BEC/1170/16DC/1A00/1B48/1D10/20F0), so it cannot be migrated for this
 * function alone.
 *
 * ---------------------------------------------------------------------------
 * MEASURED NEGATIVES (all measured against the 935 base unless noted)
 * ---------------------------------------------------------------------------
 *  945  draft1: same as below but spawn.unk17/unk1F declared s8.
 *               `li t5,0x9d`->`-0x63` and `li t8,0xff`->`-1`.  FIXED: both are u8.
 * 1140  RODATA PROBE (base 935): D_800A1828 replaced by the low16-zero literal
 *       -1760.0f.  Score got WORSE, not better -- because a lui-able literal
 *       inlines as lui+mtc1 and deletes the lwc1 golden has.  This is the
 *       probe REFUTING "wrong C shape": the `lwc1 %lo(sym)(at)` form is right.
 *  935  `extern const f32` instead of `extern f32` on D_800A1828/D_800A182C.
 *       ZERO effect -- const does not change IDO's address-hoist candidacy.
 * 1570  DIAGNOSTIC (base 935, deliberately wrong, DO NOT SHIP): swap the
 *       `spawn.unk1A = ... % 0x65U ...` and `spawn.unk10 = ...` statements.
 *       This CONFIRMS the whole diagnosis: with 0x65 textually first, the build
 *       emits `li s8,0x65` at f20 -- golden's exact instruction at golden's
 *       exact address -- AND `lui at,%hi(D_800A1828)` / `lwc1 $f4,
 *       %lo(D_800A1828)(at)` in golden's exact form.  So the emitted FORMS are
 *       all reachable; only the candidate ORDER is not, because it is keyed to
 *       source position of first use and golden's order requires the two floats
 *       to not be candidates at all.  The swap costs 1570 because it reverses
 *       the func_150ADA20 / func_150ADA68 call order, which golden pins.
 *       => The ONLY unlock is migrating the 246140 rodata block into
 *          game_11C2B0's live .rodata so the constants can be spelled as
 *          float literals.  Nothing in the C is wrong.
 *
 * RESIDUAL CLASS: ALLOCATION (loop-invariant register assignment), forced
 * upstream by the rodata spelling.  Not reachable by statement shuffling:
 * the only lever that would reorder the candidate list is moving the
 * `% 0x65U` statement ahead of the D_800A1828 statement, and that would swap
 * the func_150ADA20/func_150ADA68 call order, which golden pins.
 * =========================================================================== */

/* ---- live C, as currently in conker/src/game_11C2B0.c (pragma still present,
 * this body is NOT live; restore from here if the TU is reverted) ---- */

extern void func_15143794(s32, s32, f32, f32 *);
extern void *func_1515C2F0(void *, s32, void *, s32, u8, s32);
extern f32 D_800A1824;
extern f32 D_800A1828;
extern f32 D_800A182C;

struct Local150EFB80Header {
    s32 unk0;
    s32 unk4;
    s32 unk8;
};

struct Local150EFB80Param {
    struct Local150EFB80Header unk0;
    s16 unkC;
    u16 unkE;
    s32 unk10;
    u8 pad14;
    s8 unk15;
    u8 pad16[2];
    u8 pad18[4];
};

struct Local150EFB80Spawn {
    f32 unk00;
    f32 unk04;
    f32 unk08;
    f32 unk0C;
    f32 unk10;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 unk17;
    u8 unk18;
    u8 unk19;
    u8 unk1A;
    s8 unk1B;
    s8 unk1C;
    s8 unk1D;
    s8 unk1E;
    u8 unk1F;
    u8 unk20;
    u8 unk21;
    u8 pad22[2];
    s32 unk24;
    s32 unk28;
    s16 unk2C;
    s16 unk2E;
    s16 unk30;
    u8 unk32;
    u8 pad33;
    f32 unk34;
    s8 unk38;
    s8 unk39;
    u8 pad3A[2];
};

struct Local150EFB80Obj {
    u8 pad0[0x40];
    struct Local150EFB80Header unk40;
    u8 pad4C[0xDC];
    u8 unk128;
};

struct Local150EFB80Sub {
    struct Local150EFB80Obj *unk0;
    f32 unk4;
};

struct Local150EFB80Arg {
    u8 pad0;
    u8 unk1;
    u8 pad2[0xA];
    u8 unkC;
    u8 padD[0x1B];
    struct Local150EFB80Sub unk28;
};

void func_150EFB80(struct Local150EFB80Arg *arg0) {
    struct Local150EFB80Sub *sub;
    s32 rand0;
    s32 rand1;
    struct Local150EFB80Param param;
    struct Local150EFB80Spawn spawn;

    sub = &arg0->unk28;
    sub->unk4 += (364.0f + (func_150ADA68() * 300.0f)) * D_800A1824;
    if (sub->unk4 > 1.0f) {
        if (sub->unk0->unk128 & 1) {
            param.unk0 = sub->unk0->unk40;
            param.unkE = 5;
            param.unk10 = 0xA;
            spawn.unk14 = 4;
            spawn.unk15 = 2;
            spawn.unk16 = 3;
            spawn.unk17 = 0x9D;
            spawn.unk18 = 0x72;
            spawn.unk19 = 0x2E;
            spawn.unk1B = 0;
            spawn.unk1C = 0;
            spawn.unk1D = 0;
            spawn.unk1E = 0;
            spawn.unk1F = 0xFF;
            spawn.unk20 = 3;
            spawn.unk21 = 0x24;
            spawn.unk24 = 0x200005;
            spawn.unk28 = 0x60600;
            spawn.unk2C = 0xC;
            spawn.unk2E = 0x15;
            spawn.unk30 = 1;
            spawn.unk32 = 0;
            spawn.unk34 = 1.0f;
            spawn.unk38 = -1;
            spawn.unk39 = 0;
            do {
                param.unk15 = (func_150ADA20() % 3U) + 3;
                param.unkC = (func_150ADA20() % 0x10U) + 0x28;
                spawn.unk00 = (func_150ADA68() * 10.0f) + 22.0f;
                rand0 = func_150ADA20();
                rand1 = func_150ADA20();
                func_15143794((s16)(rand0 & 0xFF), (s16)((rand1 % 0x1FU) - 0x37),
                              (func_150ADA68() * 15.0f) + 25.0f, &spawn.unk04);
                spawn.unk10 = ((func_150ADA68() * 740.0f) + D_800A1828) * D_800A182C;
                spawn.unk1A = (func_150ADA20() % 0x65U) + 0x9B;
                func_1515C2F0(&param, 0, &spawn, 0, arg0->unkC, arg0->unk1);
                sub->unk4 -= 1.0f;
            } while (sub->unk4 > 1.0f);
        } else {
            do {
                sub->unk4 -= 1.0f;
            } while (sub->unk4 > 1.0f);
        }
    }
}
