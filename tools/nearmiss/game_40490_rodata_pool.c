/* ============================================================================
 * game_40490 .rodata MIGRATION -- MIGRATION-READY TU.  DO NOT DROP THIS INTO
 * src/ ON ITS OWN: it emits its own .rodata, which conker.ld /DISCARD/s until
 * the yaml line below is added, and the yaml line cannot be added until
 * func_150130B4 is also live C.  See "WHAT IS STILL MISSING" at the end.
 *
 * Everything here was MEASURED on 2026-08-14 (wave: rodata migration spike).
 * This file is src/game_40490.c with all sixteen `extern f32 D_800966xx`
 * declarations replaced by true float LITERALS, plus four of the five stubbed
 * functions decompiled.  Only func_150130B4 remains behind #pragma.
 *
 * ############################################################################
 * ### THE HEADLINE: THE MIGRATION HYPOTHESIS IS CONFIRMED, ON EVERY AXIS.  ###
 * ############################################################################
 *
 * 1. STAGE 1 -- EXCLUSIVE OWNERSHIP: PASS.
 *    game_40490's .rodata run is ROM 0x23B040..0x23B180 (vram 0x80096580 ..
 *    0x800966C0), 0x140 bytes.  A single-pass grep over src/ + asm/nonmatchings
 *    + asm/data for every symbol in and around the run shows EVERY symbol in it
 *    is referenced ONLY by game_40490 functions:
 *      D_80096580 / D_8009658C / D_800965A0 / D_800965B0  -> func_150130B4
 *      D_800965D4 / D8 / DC / E0                          -> func_150130B4
 *      jtbl_800965E4                                      -> func_150130B4
 *      D_80096630..D_800966B4 (the float pool)            -> the 11 users below
 *      0x800966B8 / BC  = IDO's own 16-byte tail padding (see 4)
 *    The first FOREIGN symbol is jtbl_800966C0, which belongs to game_433F0
 *    (func_15015F40); jtbl_80096760 / D_80096800 / D_80096804 / jtbl_80096808
 *    belong to game_43D00.  All of them sit at or after 0x23B180.
 *    => No foreign interleave.  This run does NOT hit the contiguity law that
 *       permanently killed game_12C1E0.  Pre-flight parts 0/1/2 all pass:
 *       start 0x23B040 is 16-aligned, length 0x140 is a multiple of 16, and the
 *       last 8 bytes are zero padding.
 *
 * 2. STAGE 2 -- CAN THE ALREADY-MATCHING FUNCTIONS BE HELD AT 0 UNDER LITERALS?
 *    YES.  This is the fact nobody had, and it is unambiguous.
 *    Measured by symbol-bounded objdump byte compare against
 *    conker/expected/build/src/game_40490.c.o, object force-rebuilt, whole TU
 *    under tools/buildlock.sh:
 *
 *      func_150139AC  0x28C  2 rows   ALL 2 are pool addends -> 0 real
 *      func_15013C38  0x100  1 row    ALL 1                  -> 0 real
 *      func_15013DE8  0x1B4 10 rows   ALL 10                 -> 0 real
 *      func_15014144  0x0DC  1 row    ALL 1                  -> 0 real
 *      func_150142EC  0x1CC  2 rows   ALL 2                  -> 0 real
 *      func_150151D4  0x12C  1 row    ALL 1                  -> 0 real
 *      func_150144B8  0x294  2 rows   ALL 2                  -> 0 real   (NEW)
 *
 *    "Pool addend" means the ONLY difference is the 16-bit immediate of one
 *    `lwc1`: mine reads `lwc1 $fN,<pool offset>(at)` where golden reads
 *    `lwc1 $fN,0(at)`.  That is not a codegen difference at all -- it is where
 *    the relocation ADDEND lives.  Golden relocates against a named symbol
 *    (`%lo(D_80096648)`, addend 0); a TU-local pool relocates against the
 *    `.rodata` SECTION symbol with the addend encoded in the instruction, which
 *    is how MIPS o32 REL relocations work.  Proof that this is the whole story:
 *
 *      readelf -rW on both objects gives the SAME relocation offsets, in the
 *      SAME order, with the SAME types, one-for-one:
 *          mine  00000a88 R_MIPS_HI16 .rodata      00000a8c R_MIPS_LO16 .rodata
 *          gold  00000a88 R_MIPS_HI16 D_80096648   00000a8c R_MIPS_LO16 D_80096648
 *      Every HI16 immediate is 0 on BOTH sides (every pool offset is < 0x8000),
 *      so only the LO16 halves ever differ.  At link time `%lo(.rodata+0xC8)`
 *      with .rodata at 0x80096580 resolves to 0x6648 -- golden's exact bytes.
 *
 *    Frames, registers, scheduling, symbol sizes: IDENTICAL everywhere
 *    (size delta 0 on every function in the TU).
 *
 * 3. THE POOL COMES OUT IN GOLDEN'S EXACT ORDER, BYTE FOR BYTE.
 *    With func_15013778, func_150144B8, func_1501474C and func_15014B60 live,
 *    the object's own .rodata is these 30 words, which is EXACTLY golden's
 *    0x80096640..0x800966B4 in order, with no gaps and nothing extra:
 *      3e4d013a 3d4ccccc 40490fdb c61c4000 3a83126f 3d4ccccd 3ca3d70a 47c34ff3
 *      3d3851ec 3f333333 41b4cccd 415c9375 4267e042 422adb23 42ed86a8 c61c4000
 *      3a83126f 2f0bcdfe 3c8efa35 3f490fdb 3c8efa35 3c8efa35 37800080 37800080
 *      3e1c4000 3a83126f 37800080 3eea6000 358637bd c61c4000
 *    plus 8 bytes of zero -> 128 bytes, a multiple of 16.
 *
 *    FOUR REUSABLE LAWS FALL OUT OF THAT (all measured here, all new):
 *    (a) IDO does NOT dedup identical float literals ACROSS functions.
 *        -10000.0f gets three separate slots (func_150139AC, func_15014144,
 *        func_150151D4) and 0.001f gets two (func_15013C38, func_150142EC) --
 *        exactly as golden has them.  This is why a duplicate value in a rodata
 *        run is a reliable tell for "literal, not global".
 *    (b) IDO DOES share one slot for repeated references to the same literal
 *        WITHIN a function: func_150142EC uses 0.001f four times and gets one
 *        slot; func_150144B8 uses 0.017453292f twice and gets one slot.
 *        But func_1501474C uses 0.017453292f twice and gets TWO slots -- the
 *        two uses are in separate call arguments (sinf/cosf), so the sharing is
 *        per hoisted VALUE-web, not per function.
 *    (c) The pool is ordered by the order IDO MATERIALISES the constants, which
 *        is NOT source-statement order.  Two independent confirmations:
 *          - func_15013DE8's `sp30.unk18 = (42.714f*tmpB) + ((sp30.unk10 =
 *            57.969f*tmpB), 0);` writes 42.714f first in the source TEXT, and
 *            IDO still pools 57.969f (0x70) before 42.714f (0x74), matching
 *            golden.  The comma sub-expression is materialised first.
 *          - func_15014B60 writes payload.unk14 (which uses 1.5259022e-05f)
 *            BEFORE the unk18/unk1C/unk20 block (which uses 0.15258789f and
 *            0.001f), yet golden AND this build both pool 0.15258789f/0.001f
 *            first, because those two are hoisted out of the three-use web.
 *        => you do not have to guess the original statement order from the pool
 *           order.  Write the natural source; IDO reproduces the pool.
 *    (d) IDO pads .rodata to a multiple of 16 (68B -> 80B, 120B -> 128B here),
 *        which is where the two zero floats at 0x800966B8/BC come from.  They
 *        are game_40490's OWN padding, not the next TU's alignment.  That is
 *        why the migrated range must END at 0x23B180, not 0x23B178.
 *
 * 4. THE YAML EDIT, VALIDATED AND THEN REVERTED (tree left clean).
 *    conker/conker.us.yaml, replacing the single line `- [0x23B040, rodata]`:
 *
 *      - [0x23B040, .rodata, game_40490] # jtbl_800965E4 + float pool, 0x140 B incl. IDO's 8-byte tail pad
 *      - [0x23B180, rodata] # jtbl_800966C0 (game_433F0) onwards
 *
 *    Then `python3 ../tools/split_conker.py conker.us.yaml --modes ld --keep-auto-syms`
 *    from conker/.  MEASURED: the generated conker.ld changes by exactly two
 *    lines and nothing else --
 *      -  build/asm/data/23B040.rodata.s.o(.rodata);
 *      +  build/src/game_40490.c.o(.rodata);
 *      +  build/asm/data/23B180.rodata.s.o(.rodata);
 *    ALWAYS pass --keep-auto-syms: splat rewrites undefined_syms_auto.txt and
 *    undefined_funcs_auto.txt EMPTY on an ld-only run, and the wrapper is what
 *    restores them (it printed "restored ... (splat had rewritten it empty)"
 *    both times here).  Verified afterwards: 8009 / 127 lines, byte-identical.
 *    The real migration also needs a FULL split so that asm/data/23B180.rodata.s
 *    is generated and asm/data/23B040.rodata.s is dropped; `--modes ld` does
 *    neither.
 *
 * ############################################################################
 * ### WHAT IS STILL MISSING: func_150130B4, AND NOTHING ELSE STRUCTURAL.   ###
 * ############################################################################
 * The pool arithmetic closes exactly, which is a strong check on the plan:
 *      target .rodata size                       0x140 = 320 B
 *      this file's 30 literals                          120 B
 *      => func_150130B4 must contribute exactly         192 B
 *      and it does:  D_80096580 (3 words) + D_8009658C (5) + D_800965A0 (4)
 *                  + D_800965B0 (9)                     =  84 B  static arrays
 *                  + D_800965D4/D8/DC/E0                =  16 B  floats
 *                  + jtbl_800965E4 (19 words)           =  76 B  jump table
 *                  + D_80096630/34/38/3C                =  16 B  floats
 *                                                       = 192 B  exactly.
 * Note the golden ORDER inside func_150130B4's own contribution: the four
 * static word arrays first, then four floats, then the jump table, then four
 * more floats.  That is a single first-use-ordered pool with the switch table
 * emitted at the point the switch occurs -- consistent with law (c) above, so
 * writing the function naturally should reproduce it.
 *
 * RESIDUALS THAT REMAIN (they do NOT block the migration; they block SHIPPING):
 *   func_1501474C  21 real rows (+2 addend).  UNCHANGED by the migration --
 *       measured 21 with externs, 21 with literals.  It is the two stack-arg
 *       `li` constants of the trailing func_15149130 call being materialised
 *       early instead of late; see tools/nearmiss/func_1501474C.c.
 *   func_15013778  17 rows.  UNCHANGED by the migration -- the brief's
 *       hypothesis that literals would move the float-constant materialisation
 *       ORDER is a CLEAN NEGATIVE: golden still emits `mtc1 zero,$f12` (0.0f)
 *       before `lui at,0x3f80` (1.0f) and this build still emits them the other
 *       way round.  See tools/nearmiss/func_15013778.c; its exhaustive 90-build
 *       statement-position grid still stands.
 *   func_15014B60   4 real rows (+7 addend), DOWN FROM 49.  The +8 frame is
 *       GONE -- frame, every stack offset, every register and the 4-instruction
 *       A0/A4 block move all now match golden exactly, which confirms the
 *       brief's hypothesis: the residual really was the named-extern memory-CSE
 *       home, and the literal removes it.  What is left is one branch-delay-slot
 *       choice at the bottom of the six-iteration loop:
 *           golden: sw v0,36(s1) | addiu s0,s0,1 | slti at,s0,6 | bnez | addiu s1,s1,4
 *           mine:   addiu s0,s0,1 | slti at,s0,6 | addiu s1,s1,4 | bnez | sw v0,32(s1)
 *       i.e. the scheduler sank the store past the pointer increment into the
 *       delay slot (rewriting 36 -> 32 to compensate).  Same multiset, same
 *       registers, size delta 0.  Tried and measured, no change: joining the
 *       whole func_151602C0 call onto one source line (11, unchanged).  NOT
 *       tried: block-scoping `header` inside the loop (the park records 45 vs
 *       49 for that under externs, i.e. it moves something).
 *
 * HOW TO FINISH THE CAMPAIGN
 *   1. Decompile func_150130B4 (1624 B, needs jtbl_800965E4 and the four static
 *      word arrays as file-scope `static const` data) into this file.
 *   2. Close func_1501474C, func_15013778 and func_15014B60 -- or accept that
 *      they cannot ship yet, because ALL ELEVEN pool users must be live C
 *      simultaneously for the pool to be byte-complete.  There is no partial
 *      migration: the granularity is the whole TU block.
 *   3. Add the yaml line, run a FULL split, rebuild, and let the ROM sha1 be
 *      the authority.
 *
 * WHY THIS FILE IS NOT IN src/: with literals but WITHOUT the yaml line, the
 * TU's .rodata is /DISCARD/ed while sixteen .text relocations point into it.
 * That breaks the link (or silently produces a wrong ROM) for the whole
 * project.  src/game_40490.c was therefore reverted to its extern form and
 * re-verified byte-identical to expected/ before this wave ended.
 * ============================================================================ */
#include <ultra64.h>

#include "functions.h"
#include "variables.h"

void func_151A9390(s32 arg0, s32 arg1, struct134 *arg2, s32 arg3, f32 arg4, f32 arg5, s32 arg6, s32 arg7, s32 arg8);
extern void (*D_80082E30[])(struct178 *);
extern void (*D_80082F28[])(struct16 *, f32);
extern u8 D_800C35E8;
void func_15145974(struct17 *arg0, f32 *arg1, f32 *arg2);
extern void func_1510F800(s32);
s32 func_151BE850(struct17 *arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6);
s32 func_15149550(void *, s32, s32, u8, u8, s32);
extern void func_150A7960(f32 *, f32, f32, f32, f32 *, f32 *, f32 *);
typedef struct {
    s8 unk0;
    u8 pad1[3];
    struct17 unk4;
    struct17 unk10;
    f32 unk1C;
    s8 unk20;
    u8 pad21[3];
} Struct150156F4Payload;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    s16 unk14;
    s16 unk16;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    u8 unk30;
    u8 unk31;
    u8 unk32;
    u8 unk33;
    u8 unk34;
    u8 pad35[3];
} Struct150139ACEntry;

typedef struct {
    struct16 *unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    s16 unk24;
    s16 unk26;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    u8 unk40;
    u8 unk41;
    u8 unk42;
    u8 pad43;
    u16 unk44;
    u8 pad46[2];
    f32 unk48;
    u8 pad4C[0x14];
    s32 unk60;
    u8 unk64;
    u8 unk65;
    u8 pad66[2];
    s32 unk68;
    s32 unk6C;
} Struct150139ACLocal;

extern Struct150139ACEntry D_80095FA0[];

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    s16 unk20;
    s16 unk22;
    s16 unk24;
    u8 unk26;
    u8 unk27;
    u8 unk28;
    u8 unk29;
    s16 unk2A;
    u8 unk2C;
    u8 unk2D;
    u8 unk2E;
    u8 unk2F;
    s32 unk30;
    u8 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    f32 unk44;
} Struct15013DE8;


void func_15012FE0(void) {
    D_800BE570 = 0;
    D_800BE574 = 0;
    D_800BE575 = 0;
}

void func_15013000(void) {
    D_800DCDC4 = 0;
    D_800DCD90 = 0.0f;
    {
        void (*func)(struct178 *);
        s32 base;
        struct178 *arg;
        u32 i;
        s32 offset;
        u8 kind;

        for (i = 0, offset = 0; i < (u32)D_800D3094; i++) {
            base = *(s32 *)&D_800D3098;
            kind = ((u8 *)base)[offset + 0x15] >> 2;
            func = D_80082E30[kind];
            if (func != NULL) {
                arg = (struct178 *)(offset + base);
                func(arg);
            }
            offset += sizeof(struct178);
        }
    }
}
// requires jump table
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_150130B4.s")

s32 func_1501370C(struct16 *arg0) {
    u8 idx = arg0->unk17;
    void (*func)(void) = D_80082EA0[idx];

    if (func != NULL) {
        func();
    }
    return 1;
}

s32 func_1501374C(struct16 *arg0) {
    arg0->unk16 |= 4;
    func_1515D088(arg0);
    return 1;
}

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
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
} Struct15013778;

s32 func_15013778(struct134 *arg0) {
    struct260 *temp_v0;
    Struct15013778 tmp;
    f32 mtx[4][4];
    f32 scale;

    if ((s16)arg0->unk8 != 0) {
        tmp.unk18 = (f32)(s16)arg0->unk8 + (f32)(s16)arg0->unk8;
        scale = 1.0f / tmp.unk18;
        tmp.unk1C = (f32)(s16)arg0->unk6;
        tmp.unk20 = *(f32 *)&arg0->unkC;
        tmp.unk24 = *(f32 *)&arg0->unk10;
        tmp.unk28 = 0.0f;
        tmp.unk2C = 0.20019999f;
        tmp.unk30 = 0.049999997f;
        tmp.unk0 = (f32)arg0->unk0;
        tmp.unk4 = (f32)(s16)arg0->unk2;
        tmp.unk8 = (f32)arg0->unk4;

        func_150A8050(mtx, *(f32 *)&arg0->unkC, *(f32 *)&arg0->unk10, 0.0f);
        func_150A7960(mtx[0], 0.0f, tmp.unk18, 0.0f, &tmp.unkC, &tmp.unk10, &tmp.unk14);

        tmp.unkC = tmp.unkC * scale;
        tmp.unk10 = tmp.unk10 * scale;
        tmp.unk14 = tmp.unk14 * scale;

        temp_v0 = func_15149130(0x12C, -1, 0x19, -1, 0, 0x17, (struct37 *)0x34, 0xFF, 0);
        if (temp_v0 != NULL) {
            memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x34);
        }

        func_1000FA64(0x67C, arg0->unk0, (s16)arg0->unk2 + (s16)arg0->unk8, arg0->unk4, 0x2EE0,
                      (s16)arg0->unk8 * 2, (s16)arg0->unk8 / 2, (s32)func_1000EF40, NULL, 0, 8, 0);
    }
    return 1;
}

s32 func_1501396C(struct16 *arg0) {
    u8 idx = arg0->unk17;
    void (*func)(void) = D_80082ECC[idx];

    if (func != NULL) {
        func();
    }
    return 1;
}

// another struct
s32 func_150139AC(struct16 *arg0, s32 idx) {
    Struct150139ACLocal tmp;
    Struct150139ACEntry *entry;
    struct260 *temp_v0;

    idx = *(s32 *)&arg0->unk18;
    arg0->unk16 |= 4;
    tmp.unk0 = arg0;
    tmp.unkC = 0.0f;

    switch (arg0->unk15 & 3) {
    default:
        tmp.unk4 = 1.0f;
        tmp.unk10 = 1000.0f;
        break;
    case 2:
        tmp.unk4 = (f32)(((s16 *)arg0)[5] * ((s16 *)arg0)[3]) * 4.0f;
        tmp.unk10 = (f32)(((s16 *)arg0)[4] + ((s16 *)arg0)[1]);
        break;
    case 0:
    case 1:
        tmp.unk4 = (f32)(((s16 *)arg0)[3] * ((s16 *)arg0)[3]) * 3.1415927f;
        tmp.unk10 = (f32)(((s16 *)arg0)[4] + ((s16 *)arg0)[1]);
        break;
    }

    entry = &D_80095FA0[idx];
    tmp.unk14 = entry->unk4;
    tmp.unk18 = entry->unk8;
    tmp.unk1C = entry->unkC;
    tmp.unk20 = entry->unk10;
    tmp.unk28 = entry->unk18;
    tmp.unk2C = entry->unk1C;
    tmp.unk60 = 0;
    tmp.unk64 = 0;
    tmp.unk65 = 0;
    tmp.unk68 = 0;
    tmp.unk24 = entry->unk14;
    tmp.unk26 = entry->unk16;
    tmp.unk30 = entry->unk20;
    tmp.unk34 = entry->unk24;
    tmp.unk38 = entry->unk28;
    tmp.unk3C = entry->unk2C;
    tmp.unk8 = entry->unk0;
    tmp.unk40 = entry->unk30;
    tmp.unk41 = entry->unk31;
    tmp.unk42 = entry->unk32;
    tmp.unk48 = -10000.0f;

    if (entry->unk34 != 0) {
        func_1510F800(0);
        tmp.unk6C = func_1510FD20((s32)((s16 *)arg0)[0], (s32)((s16 *)arg0)[2]);
    } else {
        tmp.unk6C = 0;
    }

    if (entry->unk33 != 0) {
        tmp.unk44 = func_1000FA64(0x4D, ((s16 *)arg0)[0], ((s16 *)arg0)[1], ((s16 *)arg0)[2], 0x5DC0, 0x3E8, 0x12C, 0, NULL, 0, 0, 0);
    } else {
        tmp.unk44 = 0;
    }

    temp_v0 = func_151491F4(0x12C, -1, 6, 0, 0xA, 0x70, 0xFF, 0);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, sizeof(tmp));
    }
    return 1;
}

s32 func_15013C38(struct16 *arg0) {
    s32 idx;
    f32 temp_f;
    void (*func)(struct16 *, f32);

    arg0->unk16 |= 4;
    idx = *(s32 *)&arg0->unk18;

    if ((((u8 *)D_800D2E4C)[0x11] & 4) && (D_800BE9F0 == 0x13)) {
        return 1;
    }

    if (D_800C35EA == 1) {
        if ((D_800C35E8 == 0xF) || (D_800C35E8 == 0x10) || (D_800C35E8 == 0x11)) {
            return 1;
        }
    }

    if (idx >= 6) {
        return 1;
    }

    func = D_80082F28[idx];
    if (func != NULL) {
        temp_f = (f32)arg0->unk1C * 0.001f;
        func(arg0, temp_f);
    }

    return 1;
}

s32 func_15013D38(struct47 *arg0) {
    struct17 tmp;
    struct17 *tmp_ptr;
    s32 temp_v0;

    tmp_ptr = &tmp;
    arg0->unk16 |= 4;
    tmp.unk0 = (f32)arg0->unk0;
    tmp.unk4 = (f32)arg0->unk2;
    tmp.unk8 = (f32)arg0->unk4;

    temp_v0 = arg0->unk18;
    func_151BE850(tmp_ptr, arg0->unk10, temp_v0 ? temp_v0 : 1, arg0->unk1F, 1, 0xFF, 1);
    return 1;
}
// #NON-MATCHING: looks close but think its wrong
// s32 func_151BE850(struct17 *arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6);
// s32 func_15013D38(struct47 *arg0) {
//     s32 tmp1;
//     s32 tmp2;
//     s32 tmp3;
//     s32 tmp4;
//     struct17 *tmp;
//
//     arg0->unk16 |= 4;
//
//     tmp->unk0 = arg0->unk0;
//     tmp->unk4 = arg0->unk2;
//     tmp->unk8 = arg0->unk4;
//
//     tmp4 = 1;
//     tmp1 = arg0->unk18;
//     if (tmp1) {
//         tmp4 = tmp1;
//     }
//
//     tmp2 = arg0->unk10;
//     tmp3 = arg0->unk1F;
//
//     func_151BE850(tmp, tmp2, tmp4, tmp3, 0xff, 1, 1);
//     return 1;
// }

s32 func_15013DE8(struct47 *arg0) {
    Struct15013DE8 sp30;
    f32 tmpA;
    f32 tmpB;

    arg0->unk16 |= 4;

    tmpA = arg0->unk6 * 0.05f;
    tmpB = arg0->unk8 * 0.02f;

    sp30.unk22 = 0x1A4D + ((sp30.unk20 = 0x6231), 0);
    sp30.unk26 = 0;
    sp30.unk27 = 0;
    sp30.unk28 = 0;
    sp30.unk29 = 0xFF;
    sp30.unk2A = 0;
    sp30.unk2D = 0xFF;
    sp30.unk30 = 0;
    sp30.unk2E = 0;
    sp30.unk2F = 0;
    sp30.unk34 = 0;
    sp30.unk3C = 99999.9f;

    sp30.unk0 = arg0->unk0;
    sp30.unk4 = arg0->unk2;
    sp30.unk8 = arg0->unk4;

    sp30.unk24 = 0x12C;
    sp30.unk38 = 0.0f;
    sp30.unk40 = 0.045f;
    sp30.unk44 = 0.7f;

    sp30.unk2C = (func_150ADA20() % 0x38U) + 0xC8;

    sp30.unkC = 22.6f * tmpA;
    sp30.unk14 = 13.786f * tmpA;
    sp30.unk18 = (42.714f * tmpB) + ((sp30.unk10 = 57.969f * tmpB), 0);
    sp30.unk1C = 118.763f * tmpB;

    func_15149550(&sp30, 0xA, 1, arg0->unk18 ? 2 : 1, 0xFF, 1);
    return 1;
}

s32 func_15013F9C(s32 arg0) {
    func_151CD2C0(arg0, 0xFF, 1);
    return 1;
}

s32 func_15013FC4(struct133 *arg0) {
    u8 idx = arg0->unk1B;
    void (*func)(void) = D_80082F40[idx];

    if (func != NULL) {
        func();
    }
    return 1;
}

s32 func_15014004(struct134 *arg0) {
    s32 temp_v1 = arg0->unk1C;
    if (temp_v1 < 0) {
        return 1;
    }
    if (temp_v1 >= 6) {
        return 1;
    }
    D_800E0900[temp_v1] = arg0;
    return 1;
}

s32 func_15014040(struct134 *arg0) {
    s32 temp_v0 = arg0->unk18;
    arg0->unk16 |= 4;
    if (temp_v0 == 0) {
        D_800D9A20 = arg0;
    } else if (temp_v0 == 1) {
        D_800D9A24 = arg0;
    }
    return 1;
}

s32 func_1501407C(s32 arg0) {
    D_800D987C = (u8)0;
    return 1;
}

s32 func_15014094(struct134 *arg0) {
    struct {
        struct134 *unk0;
        f32 unk4;
        f32 unk8;
        s32 unkC;
        u8 pad10[0x1C];
        s8 unk2C;
        u8 pad2D[7];
    } tmp;
    struct260 *temp_v0;

    arg0->unk16 |= 4;
    tmp.unk0 = arg0;
    tmp.unk4 = func_15144598(arg0);
    tmp.unk8 = 0.0f;

    func_1510F800(0);
    tmp.unkC = func_1510FD20(arg0->unk0, arg0->unk4);
    tmp.unk2C = 0;

    temp_v0 = func_15149130(0x12C, -1, 0x21, -1, 0, 0, (struct37 *)0x34, 0xFF, 1);
    if (temp_v0 != NULL) {
        memcpy((void *)((s32)temp_v0 + 0x28), &tmp, 0x34);
    }
}

s32 func_15014144(struct134 *arg0) {
    s32 flags;
    s32 bit8;
    s32 bit4;
    s32 bit2;
    s32 bit1;
    s32 bit16;

    flags = arg0->unk18;

    if (flags & 8) {
        bit8 = 8;
    } else {
        bit8 = 0;
    }

    if (flags & 4) {
        bit4 = 4;
    } else {
        bit4 = 0;
    }

    if (flags & 2) {
        bit2 = 0;
    } else {
        bit2 = 2;
    }

    if (flags & 1) {
        bit1 = 1;
    } else {
        bit1 = 0;
    }

    if (flags & 0x10) {
        bit16 = 0x10;
    } else {
        bit16 = 0;
    }

    func_151A9390((u8)(bit16 | bit1 | bit2 | bit4 | bit8), *((u8 *)arg0 + 0x1F), arg0, 0, -10000.0f, 100.0f, -1, 0xFF, 1);
    return 1;
}

s32 func_15014220(struct16 *arg0) {
    struct {
        f32 unk0;
        struct16 *unk4;
        u8 unk8;
    } tmp;
    struct260 *temp_v0;

    arg0->unk16 |= 4;
    tmp.unk8 = 1;
    tmp.unk4 = arg0;
    tmp.unk0 = 0.0f;

    temp_v0 = func_15149130(0x12C, -1, 0x26, -1, 0, 0x24, (struct37 *)0xC, 0xFF, 0);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0xC);
    }
    return 1;
}

s32 func_150142AC(struct134 *arg0) {
    s32 idx;

    idx = ((u8 *)arg0)[0x1B];
    arg0->unk16 |= 4;
    if ((idx < 0) || (idx >= 3)) {
        return 1;
    }
    D_800D9AA0[idx] = arg0;
    return 1;
}

s32 func_150142EC(struct134 *arg0) {
    struct {
        struct134 *unk0;
        f32 unk4;
        f32 unk8;
        f32 unkC;
        f32 unk10;
        f32 unk14;
    } tmp;
    struct260 *temp_v0_2;
    f32 temp_f4;
    f32 temp_f6;
    f32 temp_f2;
    f32 temp_f8;
    register f32 temp_f0;

    arg0->unk16 |= 4;
    if (D_80082FA0 >= 2) {
        return 1;
    }

    if ((((u8 *)D_800D2E4C)[0x11] & 4) && (D_800BE9F0 == 0x13)) {
        return 1;
    }

    temp_f4 = (f32)(arg0->unk1C & 0xFFFFU) * 0.001f;
    temp_f6 = (f32)(((u32)arg0->unk1C >> 16) & 0xFFFFU) * 0.001f;
    temp_f2 = (f32)(arg0->unk20 & 0xFFFFU) * 0.001f;
    temp_f8 = (f32)(((u32)arg0->unk20 >> 16) & 0xFFFFU) * 0.001f;

    temp_f0 = func_1514462C((s32)arg0);

    tmp.unk0 = arg0;
    tmp.unk4 = (temp_f4 * temp_f0) * 1.271516e-10f;
    tmp.unk8 = (temp_f6 * temp_f0) * 1.271516e-10f;
    tmp.unkC = temp_f2;
    tmp.unk10 = temp_f8;
    tmp.unk14 = 0.0f;

    temp_v0_2 = func_15149130(0x12C, -1, 0x29, -1, 0, 0, (struct37 *)0x18, 0xFF, 0);
    if (temp_v0_2 != NULL) {
        memcpy((u8 *)temp_v0_2 + 0x28, &tmp, 0x18);
    }
    return 1;
}
// structs.h types unk6/unk8 as u16 and unk18/unk1C as s32; this actor reads them
// signed / unsigned respectively.
typedef struct {
    s16 unk0;
    u16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    u16 unkA;
    s32 unkC;
    s32 unk10;
    u16 unk14;
    u8  unk16;
    u8  unk17;
    u32 unk18;
    u32 unk1C;
} Struct150144B8;

s32 func_150144B8(Struct150144B8 *arg0) {
    struct {
        Struct150144B8 *unk0;
        s32 unk4;
        s32 unk8;
        s32 unkC;
        s16 unk10;
        s16 unk12;
        f32 unk14;
        f32 unk18;
        f32 unk1C;
        f32 unk20;
        f32 unk24;
        f32 unk28;
        f32 unk2C;
        f32 unk30;
        f32 unk34;
    } tmp;
    struct260 *temp_v0;
    f32 mtx[4][4];
    f32 z;
    f32 y;
    f32 x;

    arg0->unk16 |= 4;
    if (D_80082FA0 >= 2) {
        return 1;
    }

    func_150A8050(mtx, *(f32 *)&arg0->unkC, *(f32 *)&arg0->unk10, 0.0f);
    func_150A7960(mtx[0], 0.0f, 100.0f, 0.0f, &x, &y, &z);
    func_15145974((struct17 *)&x, &tmp.unk1C, &tmp.unk20);
    tmp.unk1C *= 0.017453292f;
    tmp.unk20 *= 0.017453292f;

    tmp.unk8 = arg0->unk18 & 0xFF;
    tmp.unkC = (arg0->unk18 >> 8) & 0xFF;
    tmp.unk4 = ((u32)func_150ADA20() % (u32)(tmp.unkC + 1)) + tmp.unk8;
    tmp.unk0 = arg0;
    tmp.unk10 = (arg0->unk18 >> 16) & 0xFF;
    tmp.unk12 = (arg0->unk18 >> 24) & 0xFF;
    tmp.unk14 = (f32)(arg0->unk1C & 0xFF) * 0.015625f;
    tmp.unk18 = (f32)((arg0->unk1C >> 8) & 0xFF) * 0.015625f;
    tmp.unk2C = (f32)((arg0->unk1C >> 24) & 0xFF);
    tmp.unk30 = 1.0f / tmp.unk2C;
    tmp.unk34 = (f32)arg0->unk8 * tmp.unk30;
    tmp.unk24 = func_150484A0((f32)arg0->unk6, (f32)arg0->unk8);
    tmp.unk28 = ((f32)((arg0->unk1C >> 16) & 0xFF) * 0.00390625f) * 0.7853982f;

    temp_v0 = func_15149130(0x12C, -1, 0x2A, -1, 0, 0, (struct37 *)0x38, 0xFF, 0);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x38);
    }
    return 1;
}

typedef struct {
    f32 x;
    f32 z;
} Vec2_1501474C;

typedef struct {
    Vec2_1501474C unk0;
    Vec2_1501474C unk8;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    u8 unk3C;
    u8 unk3D;
    u8 unk3E;
    u8 unk3F;
} Struct1501474C;

s32 func_1501474C(struct134 *arg0) {
    Struct1501474C payload;
    struct260 *temp_v0;
    Vec2_1501474C pts[4];
    f32 sn;
    f32 cs;
    f32 z;
    f32 y;
    f32 x;

    arg0->unk16 |= 4;
    x = (f32)arg0->unk0;
    z = (f32)arg0->unk4;
    sn = sinf(*(f32 *)&arg0->unk10 * 0.017453292f);
    cs = cosf(*(f32 *)&arg0->unk10 * 0.017453292f);

    pts[0].x = ((f32)(s16)arg0->unk6 * cs) + x + ((f32)(s16)arg0->unkA * sn);
    pts[0].z = ((f32)(s16)arg0->unkA * cs) + z - ((f32)(s16)arg0->unk6 * sn);
    pts[1].x = ((f32)(s16)arg0->unk6 * cs) + x + ((f32)-(s16)arg0->unkA * sn);
    pts[1].z = ((f32)-(s16)arg0->unkA * cs) + z - ((f32)(s16)arg0->unk6 * sn);
    pts[2].x = ((f32)-(s16)arg0->unk6 * cs) + x + ((f32)-(s16)arg0->unkA * sn);
    pts[2].z = ((f32)-(s16)arg0->unkA * cs) + z - ((f32)-(s16)arg0->unk6 * sn);
    pts[3].x = ((f32)-(s16)arg0->unk6 * cs) + x + ((f32)(s16)arg0->unkA * sn);
    pts[3].z = ((f32)(s16)arg0->unkA * cs) + z - ((f32)-(s16)arg0->unk6 * sn);

    payload.unk0 = pts[1];
    payload.unk8 = pts[2];
    payload.unk10 = pts[0].x - pts[1].x;
    payload.unk14 = pts[0].z - pts[1].z;
    payload.unk18 = pts[3].x - pts[2].x;
    payload.unk1C = pts[3].z - pts[2].z;
    payload.unk20 = (f32)((s16)arg0->unk2 + (s16)arg0->unk8);
    payload.unk24 = (f32)(s16)arg0->unk2;
    payload.unk28 = (f32)(arg0->unk1C & 0xFFU) * 0.00390625f * 0.5f;
    payload.unk2C = (f32)(((u32)arg0->unk1C >> 8) & 0xFFU) * 0.00390625f * 0.5f;
    payload.unk30 = 0.0f;
    payload.unk34 = (f32)(((u32)arg0->unk1C >> 16) & 0xFFU) * 0.00390625f * 250.0f;
    payload.unk38 = (f32)(((u32)arg0->unk1C >> 24) & 0xFFU) * 0.00390625f * 250.0f;
    payload.unk3C = arg0->unk18;
    payload.unk3D = (u32)arg0->unk18 >> 8;
    payload.unk3E = (u32)arg0->unk18 >> 16;
    payload.unk3F = (u32)arg0->unk18 >> 24;

    temp_v0 = func_15149130(0x12C, -1, 0x2C, -1, 0, 0, (struct37 *)0x40, 0xFF, 0);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &payload, 0x40);
    }
    return 1;
}

extern u8 D_800A0938[];
struct225 *func_151602C0(Header *header, Header2 *header2, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 arg6, u8 arg7, s32 offset, u8 arg9, s32 argA);

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
    struct225 *unk24[6];
    f32 unk3C;
    struct134 *unk40;
    u8 unk44;
    u8 pad45[3];
} Struct15014B60;

s32 func_15014B60(struct134 *arg0) {
    Struct15014B60 payload;
    struct260 *temp_v0;
    s32 i;
    Header2 header2;
    Header header;

    arg0->unk16 |= 4;
    payload.unk44 = 1;
    payload.unk40 = arg0;
    payload.unk0 = (f32)arg0->unk0;
    payload.unk4 = (f32)(s16)arg0->unk2;
    payload.unk8 = (f32)arg0->unk4;
    payload.unkC = (f32)((osGetCount() * func_150ADA20()) & 0xFFFFU) * 1.5259022e-05f * 360.0f;
    payload.unk10 = (f32)((osGetCount() * func_150ADA20()) & 0xFFFFU) * 1.5259022e-05f * 360.0f;
    payload.unk14 = (f32)((osGetCount() * func_150ADA20()) & 0xFFFFU) * 1.5259022e-05f * 360.0f;
    payload.unk18 = (f32)(arg0->unk18 & 0xFFFFU) * 0.15258789f * 0.001f;
    payload.unk1C = (f32)(((u32)arg0->unk18 >> 16) & 0xFFFFU) * 0.15258789f * 0.001f;
    payload.unk20 = (f32)(arg0->unk1C & 0xFFFFU) * 0.15258789f * 0.001f;
    payload.unk3C = (f32)(((u32)arg0->unk1C >> 16) & 0xFFFFU) * 0.45776367f * 1e-06f;

    header2.unk0 = arg0->unk0;
    header2.unk4 = (s16)arg0->unk2;
    header2.unk8 = arg0->unk4;

    for (i = 0; i < 6; i++) {
        header.unk0 = 2;
        header.unk1 = -1;
        header.unk2 = 0x12C;
        header.unk4 = 0;
        payload.unk24[i] = func_151602C0(&header, &header2, 5,
                                         (D_800BE9F0 == 0x40) ? 0xFF : D_800A0938[i * 3],
                                         (D_800BE9F0 == 0x40) ? 0 : D_800A0938[(i * 3) + 1],
                                         (D_800BE9F0 == 0x40) ? 0 : D_800A0938[(i * 3) + 2],
                                         0xFF, 0, 0, 0xFF, 0);
    }

    temp_v0 = func_15149130(0x12C, -1, 0x2E, -1, 0, 0x29, (struct37 *)0x48, 0xFF, 0);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &payload, 0x48);
    } else {
        for (i = 0; i < 6; i++) {
            if (payload.unk24[i] != NULL) {
                func_1516972C((struct102 *)payload.unk24[i]);
            }
        }
    }
    return 1;
}

s32 func_15014F6C(struct134 *arg0) {
    struct {
        struct134 *unk0;
        s32 unk4;
        s32 unk8;
        s32 unkC;
        f32 mtx[4][4];
        u8 unk50;
        u8 unk51;
    } tmp;
    struct260 *temp_v0;
    s32 flag;

    arg0->unk16 |= 4;
    tmp.unk51 = arg0->unk20;
    if (arg0->unk1C & 1) {
        flag = 1;
    } else {
        flag = 0;
    }
    tmp.unk50 = flag;
    tmp.unk0 = arg0;
    tmp.unk4 = arg0->unk18 & 0xFFFF;
    tmp.unk8 = ((u32)arg0->unk18 >> 16) & 0xFFFF;
    tmp.unkC = ((u32)func_150ADA20() % (u32)(tmp.unk8 + 1)) + tmp.unk4;
    func_150A8050(tmp.mtx, *(f32 *)&arg0->unkC, *(f32 *)&arg0->unk10, 0);

    tmp.mtx[3][0] = (f32)arg0->unk0;
    tmp.mtx[3][1] = (f32)(s16)arg0->unk2;
    tmp.mtx[3][2] = (f32)arg0->unk4;

    temp_v0 = func_15149130(0x12C, -1, 0x31, -1, 0, 0x2A, (struct37 *)0x54, 0xFF, 0);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x54);
    }
    return 1;
}

s32 func_150150A4(void) {
    struct17 *temp_v0 = func_1515F1B0();
    if (temp_v0 == NULL) {
        return 1;
    }

    func_1515F25C(&D_800DCDC4, temp_v0);
    D_800DCD90 += temp_v0->unk8;
    return 1;
}

s32 func_15015104(struct134 *arg0) {
    struct {
        struct134 *unk0;
        u8 unk4;
        u8 pad5[3];
        s32 unk8;
        u8 unkC;
        u8 padD[3];
        s32 unk10;
    } tmp;
    struct260 *temp_v0;
    s32 temp_v1;
    s32 temp_t0;
    s32 temp_v0_2;

    *(u8 *)&arg0->unk14 = 1;
    tmp.unk0 = arg0;
    tmp.unk4 = arg0->unk1C;

    func_1510F800(0);
    tmp.unk8 = func_1510FD20(arg0->unk0, arg0->unk4);

    temp_v1 = arg0->unk20;
    if (temp_v1 != 0) {
        temp_t0 = 1;
    } else {
        temp_t0 = 0;
    }
    if (temp_v1 != 0) {
        temp_v0_2 = 2;
    } else {
        temp_v0_2 = 0;
    }
    tmp.unkC = temp_v0_2 | temp_t0;
    tmp.unk10 = 0;

    temp_v0 = func_15149130(0x12C, -1, -1, -1, 0, 0x2C, (struct37 *)0x14, 0xFF, 0);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x14);
    }
    return 1;
}

s32 func_150151D4(struct134 *arg0) {
    struct {
        struct134 *unk0;
        f32 unk4;
        s16 unk8;
        f32 unkC;
        f32 unk10;
        f32 unk14;
        f32 unk18;
        f32 unk1C;
        f32 unk20;
        u8 pad24[0x14];
        s32 unk38;
        s8 unk3C;
        s8 unk3D;
        s32 unk40;
        s32 unk44;
    } tmp;
    struct260 *temp_v0;

    arg0->unk16 |= 4;
    *(u8 *)&arg0->unk14 = 1;

    tmp.unk0 = arg0;
    tmp.unk4 = 0.0f;
    tmp.unk8 = -1;
    tmp.unkC = (f32)arg0->unk0;
    tmp.unk10 = (f32)(s16)arg0->unk2;
    tmp.unk14 = (f32)arg0->unk4;
    tmp.unk18 = (f32)(s16)arg0->unk6;
    tmp.unk1C = (f32)(s16)arg0->unk8;
    tmp.unk20 = -10000.0f;
    tmp.unk40 = 0;
    tmp.unk3D = 0;
    tmp.unk3C = 0;
    tmp.unk38 = 0;

    func_1510F800(0);
    tmp.unk44 = func_1510FD20(arg0->unk0, arg0->unk4);

    temp_v0 = func_15149130(0x12C, -1, 0x3C, -1, 0, 0x2D, (struct37 *)0x48, 0xFF, 0);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x48);
    }
    return 1;
}

s32 func_15015300(struct134 *arg0) {
    void (*func)(void);
    s32 idx = arg0->unk1C;

    if ((idx < 0) || (idx >= 2)) {
        return 1;
    }

    func = D_80082F70[idx];
    if (func != NULL) {
        func();
    }

    return 1;
}

void func_15015354(struct134 *arg0) {
    struct {
        struct134 *unk0;
        s16 unk4;
        u8 pad6[2];
        f32 unk8;
        f32 points[4][3];
        f32 diffs[4][3];
        s32 unk6C;
        s32 unk70;
    } payload;
    struct260 *temp_v0;
    f32 z;
    f32 y;
    f32 x;
    f32 corners[4][3];
    f32 mtx[4][4];
    s32 i;

    payload.unk0 = arg0;
    payload.unk4 = -1;
    payload.unk8 = 0.0f;
    *(u8 *)&arg0->unk14 = 1;
    x = (f32)arg0->unk0;
    y = (f32)(s16)arg0->unk2;
    z = (f32)arg0->unk4;

    corners[0][0] = (f32)(s16)arg0->unk6;
    corners[0][1] = 0.0f;
    corners[0][2] = (f32)(s16)arg0->unkA;
    corners[1][0] = (f32)(s16)arg0->unk6;
    corners[1][1] = 0.0f;
    corners[1][2] = (f32)-(s16)arg0->unkA;
    corners[2][0] = (f32)-(s16)arg0->unk6;
    corners[2][1] = 0.0f;
    corners[2][2] = (f32)-(s16)arg0->unkA;
    corners[3][0] = (f32)-(s16)arg0->unk6;
    corners[3][1] = 0.0f;
    corners[3][2] = (f32)(s16)arg0->unkA;

    func_150A8050(mtx, *(f32 *)&arg0->unkC, *(f32 *)&arg0->unk10, 0.0f);

    mtx[3][0] = x;
    mtx[3][1] = y;
    mtx[3][2] = z;

    for (i = 0; i < 4; i = (i + 1) & 0xFF) {
        func_150A7960(mtx[0], corners[i][0], corners[i][1], corners[i][2],
                      &payload.points[i][0], &payload.points[i][1], &payload.points[i][2]);
    }

    payload.diffs[0][0] = payload.points[1][0] - payload.points[0][0];
    payload.diffs[0][1] = payload.points[1][1] - payload.points[0][1];
    payload.diffs[0][2] = payload.points[1][2] - payload.points[0][2];
    payload.diffs[1][0] = payload.points[2][0] - payload.points[1][0];
    payload.diffs[1][1] = payload.points[2][1] - payload.points[1][1];
    payload.diffs[1][2] = payload.points[2][2] - payload.points[1][2];
    payload.diffs[2][0] = payload.points[3][0] - payload.points[2][0];
    payload.diffs[2][1] = payload.points[3][1] - payload.points[2][1];
    payload.diffs[2][2] = payload.points[3][2] - payload.points[2][2];
    payload.diffs[3][0] = payload.points[0][0] - payload.points[3][0];
    payload.diffs[3][1] = payload.points[0][1] - payload.points[3][1];
    payload.diffs[3][2] = payload.points[0][2] - payload.points[3][2];

    func_1510F800(0);
    payload.unk6C = func_1510FD20(arg0->unk0, arg0->unk4);
    payload.unk70 = 0;

    temp_v0 = func_15149130(0x12C, -1, 0x3D, -1, 0, 0x2E, (struct37 *)0x74, 0xFF, 0);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &payload, 0x74);
    }
}
s32 func_15015644(struct134 *arg0) {
    struct {
        struct134 *unk0;
        f32 unk4;
        s32 unk8;
        s8 unkC;
    } tmp;
    struct260 *temp_v0;

    arg0->unk16 |= 4;
    *(u8 *)&arg0->unk14 = 1;

    tmp.unk0 = arg0;
    tmp.unk4 = func_15144598(arg0);
    func_1510F800(0);
    tmp.unk8 = func_1510FD20(arg0->unk0, arg0->unk4);
    tmp.unkC = 0;

    temp_v0 = func_15149130(0x12C, -1, 0x44, -1, 0, 0x2F, (struct37 *)0x10, 0xFF, 0);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x10);
    }
    return 1;
}

s32 func_150156F4(struct134 *arg0) {
    struct17 points[2];
    f32 mtx[4][4];
    Struct150156F4Payload payload;

    if (D_800BE9F0 == 0xB) {
        if ((u32)arg0->unk18 < 6U) {
            return 1;
        }
    } else if (D_800BE9F0 == 0x2C) {
        if ((u32)arg0->unk18 < 7U) {
            return 1;
        }
    } else if (D_800BE9F0 == 0x26) {
        if ((u32)arg0->unk18 < 2U) {
            return 1;
        }
    }

    func_150A8050(mtx, *(f32 *)&arg0->unkC, *(f32 *)&arg0->unk10, 0.0f);
    mtx[3][0] = (f32)arg0->unk0;
    mtx[3][1] = (f32)(s16)arg0->unk2;
    mtx[3][2] = (f32)arg0->unk4;

    func_150A7960(mtx[0], 0.0f, (f32)(s16)arg0->unk8, 0.0f,
                  &points[1].unk0, &points[1].unk4, &points[1].unk8);

    points[0].unk0 = (f32)arg0->unk0;
    points[0].unk4 = (f32)(s16)arg0->unk2;
    points[0].unk8 = (f32)arg0->unk4;
    payload.unk0 = arg0->unk18;

    payload.unk4 = points[points[0].unk4 < points[1].unk4];
    payload.unk10 = points[points[1].unk4 < points[0].unk4];

    payload.unk20 = 0;
    payload.unk1C = fabsf(points[1].unk4 - points[0].unk4);
    func_151ACBD4(&payload, 0);

    return 1;
}
