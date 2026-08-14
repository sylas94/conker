/* ============================================================================
 * PARKED STATE: func_150144B8 (game_40490.c) -- score 207, REPRODUCED 2026-08-14.
 * Baseline confirmed in my own build before any change: 207 with -R and 207 without.
 *
 * ############################################################################
 * ###  2026-08-14 WAVE 2: CAUSE SOLVED AND PROVEN.  207 IS A HARD FLOOR    ###
 * ###  UNTIL game_40490's .rodata IS MIGRATED.  DO NOT RESPELL FURTHER.    ###
 * ############################################################################
 *
 * THE ANSWER: golden's source does NOT reference a named global here at all.
 * It multiplies by the FLOAT LITERAL 0.01745329238f (= pi/180, degrees->radians).
 * `D_80096688' is not a variable -- it is splat's minted name for IDO's ANONYMOUS
 * .rodata literal pool slot for this TU.  Two reads of a NAMED extern cost an
 * 8-byte homed CSE temp; two uses of a LITERAL cost ZERO, and both emit the
 * identical one-`lui`/one-`lwc1`/two-`mul.s` stream.
 *
 * MEASURED (standalone IDO harness, same flags; frame in decimal, target 192):
 *     tmp.unk1C *= D_80096688;  tmp.unk20 *= D_80096688;        200   <- current
 *     tmp.unk1C *= 0.01745329238f;  tmp.unk20 *= 0.01745329238f; 192  <- GOLDEN
 * and the literal build's stack offsets are golden's exactly:
 *     addiu a0,sp,56(0x38)=&x | a1,sp,164(0xA4) | a2,sp,168(0xA8) | sw t3,144(0x90)
 * i.e. the literal build is byte-identical to golden, frame included.
 *
 * MINIMAL SYNTHETIC PROOF (~2 s/build, in $HOME/nmwave/syn3):
 *     int p(void){ float a[2], big[14]; snk(&a[0],&a[1]); a[0]*=X; a[1]*=X;
 *                  snk2(big,a,8); return 0; }
 *     X = extern float G (same symbol twice)      frame 96   (+8 CSE temp)
 *     X = 0.017453292f  (same literal twice)      frame 88   <- free
 *     X = 0.015625f     (power of two, inlined)   frame 88
 *     a[0]*=G; a[1]*=H; (two different externs)   frame 88
 *     extern CONST float / static const float     frame 96   (const does NOT help)
 * SPELLINGS SWEPT THIS WAVE, ALL 96 (i.e. all still +8) -- DO NOT REPEAT:
 *   block-scoped `float g = G;`; comma operator; `a=a*G` explicit; swapped order;
 *   array-symbol `Ga[0]` twice; `*(float *)&G` twice; the two statements separated
 *   by an unrelated statement; both uses inside ONE expression; the whole thing
 *   with no surrounding call at all; and an integer double-read `(int)G+(int)G`
 *   (also 96, so it is the READ not the float-ness).
 *
 * === WHY IT CANNOT BE SHIPPED YET: THE POOL IS INTERLEAVED WITH 4 PRAGMAS ===
 * game_40490's anonymous literal pool is asm/data/23B040.rodata.s 0x80096630..0x800966B4,
 * contiguous, referenced by NO other TU (verified by grep over asm/nonmatchings + src),
 * and laid out in SOURCE ORDER of the functions that use it:
 *     0x80096630..3C  func_150130B4   <-- STILL #pragma (and needs a jump table)
 *     0x80096640,44   func_15013778   <-- STILL #pragma
 *     0x80096648..84  func_150139AC .. func_150142EC   (already live C)
 *     0x80096688,8C   func_150144B8   <-- THIS FUNCTION
 *     0x80096690,94   func_1501474C   <-- STILL #pragma
 *     0x80096698..B0  func_15014B60   <-- STILL #pragma
 *     0x800966B4      func_150151D4   (already live C)
 * (0x80096610..0x8009662C immediately before the pool is func_150130B4's JUMP TABLE.)
 * Emitting only THIS function's two literals from C would shift every later pool
 * address, so the migration is all-or-nothing: the four pragma'd functions must be
 * decompiled (with their constants as literals, in this order) and the whole pool
 * moved to C in ONE commit, plus the conker.us.yaml `[0x23B0F0, .rodata, game_40490]`
 * line and a splat --modes ld regeneration.
 * => func_150144B8 is a WHOLE-TU CAMPAIGN, not a near-miss.  Its 207 is a floor.
 * DO NOT spend another wave respelling the multiply; the spelling is already known
 * and is blocked purely on rodata placement.
 * The same reasoning retires the "PARADOX THAT IS STILL OPEN" section below --
 * golden pays no 8 bytes because golden has no memory CSE, because it has no global.
 *
 * === THE SHADOW HYPOTHESIS WAS TESTED FIRST AND IS A CLEAN NEGATIVE HERE ===
 * The wave brief said this function "reaches D_80082E30 / D_80082EA0 / D_80082ECC".
 * IT DOES NOT.  Those three are touched by func_15013000 / func_1501370C / func_1501396C,
 * which are OTHER functions in this same parked TU.  func_150144B8 itself reaches only:
 *     D_80082FA0   variables.h:371  `extern s32  D_80082FA0;`  -- CORRECT, scalar; golden
 *                  does lui/lw %hi/%lo of it as a scalar, which is what this decl gives.
 *     D_80096688   f32, file-local extern, read TWICE
 *     D_8009668C   f32, file-local extern, read once
 * None of the three is an array-declared-but-really-a-pointer symbol, none of them uses
 * the cast-through-address idiom, and there is no address-as-VALUE site in the function.
 * So there is NO shadow to apply.  Score before = 207, score after = 207 (no change made,
 * because there is nothing to change).  RECORDED AS A NEGATIVE, as asked.
 *
 * === WHAT THE RESIDUAL ACTUALLY IS: ONE 8-BYTE FRAME DELTA, NOTHING ELSE ===
 * ZERO instruction differences.  Every opcode, every register, every ordering matches
 * golden.  The whole 207 is that golden's frame is 0xC0 and this build's is 0xC8, so all
 * 22 sp-relative offsets and the two `addiu sp,sp,+/-N` read 8 too high:
 *     golden  addiu sp,sp,-0xc0 ... addiu a0,sp,0x44 ... addiu a1,sp,0x88
 *     build   addiu sp,sp,-0xc8 ... addiu a0,sp,0x4c ... addiu a1,sp,0x90
 * asm-differ marks them `i` (immediate) and `s` (stack) only; no `r`, no inserted or
 * deleted rows.  DIFFROWS = 22 of 165 instructions (660 bytes / 4).
 *
 * === THE LOCALS ARE ALREADY RIGHT.  DO NOT RE-DERIVE THEM. ===
 * Golden's home area is [0x38, 0xC0) = 0x88 bytes, laid out top-down in declaration order,
 * and this reconstruction reproduces it EXACTLY, just shifted +8:
 *     tmp (0x38) @0x88 | temp_v0 (4) @0x84 | mtx (0x40) @0x44 | z @0x40 | y @0x3C | x @0x38
 * (proved from golden: `addiu a0,sp,0x44` = &mtx, `addiu t9/t0/t1,sp,0x38/0x3C/0x40` =
 * &x/&y/&z, `sw s0,0x88(sp)` = tmp.unk0, memcpy size 0x38, frame 0xC0.)
 * Saved regs are s0@0x30 / ra@0x34 in BOTH.  So the 8 bytes sit strictly between the saved
 * registers and the home area: it is a COMPILER TEMP, not a mis-counted local.
 * Removing or adding a local moves mtx/x/y/z off golden's offsets -- verified, don't.
 *
 * === THE TRIGGER IS ISOLATED: THE TWICE-READ f32 GLOBAL D_80096688 ===
 * Bisected with a standalone IDO harness (../ido/ido5.3_recomp/cc, same flags, ~8 s/build;
 * it reproduces the in-project frame exactly: frame=200, x_at=64).  Measured, frame in
 * decimal, target is frame=192 / x_at=56:
 *     full function                                              200 / 64
 *     drop `tmp.unk1C *= D_80096688;`   (leaves ONE read)        192 / 56   <-- golden's frame
 *     drop `tmp.unk20 *= D_80096688;`   (leaves ONE read)        192 / 56   <-- golden's frame
 *     drop BOTH                                                  192 / 56
 *     `tmp.unk1C *= D_80096688; tmp.unk20 *= D_8009668C;`        192 / 56   (2 DIFFERENT globals)
 *     `tmp.unk1C = D_80096688; tmp.unk20 = D_80096688;`          200 / 64   (no arithmetic at all!)
 *     `tmp.unk24 *= D_80096688; tmp.unk28 *= D_80096688;`        200 / 64   (other destinations)
 *     three or four such multiplies                              200 / 64   (does NOT keep growing)
 * So it is not the multiply, not the destination, not address-taken-ness: it is READING THE
 * SAME f32 GLOBAL TWICE.  IDO CSEs the two `lwc1 %lo(D_80096688)(at)` into one live value
 * and gives that CSE a homed compiler temp, costing 8 bytes of frame.
 * NOTE the contrast: the constant 0.015625f is ALSO used twice (tmp.unk14/tmp.unk18, one
 * `lui at,0x3c80; mtc1` feeding two mul.s) and costs ZERO -- deleting both those lines
 * leaves the frame at 200.  An IMMEDIATE CSE is free; a MEMORY-LOAD CSE is 8 bytes.
 *
 * === THE PARADOX THAT IS STILL OPEN ===
 * Golden ALSO reads D_80096688 once and uses it twice:
 *     lui at,%hi(D_80096688) / lwc1 $f0,%lo(D_80096688)(at)
 *     lwc1 $f4,0xA4(sp) / lwc1 $f8,0xA8(sp) / mul.s $f6,$f4,$f0 / nop / mul.s $f10,$f8,$f0
 *     swc1 $f6,0xA4(sp) / swc1 $f10,0xA8(sp)
 * ...yet pays no 8 bytes for it.  So golden's source produces that single load WITHOUT
 * creating a homed CSE temp.  Finding that spelling is the whole remaining problem.
 *
 * === SPELLINGS ALREADY TRIED AND MEASURED (ALL 200/64 -- DO NOT REPEAT) ===
 *   tmp.unk1C = tmp.unk1C * D_80096688;      | tmp.unk1C = D_80096688 * tmp.unk1C;
 *   *(f32 *)&tmp.unk1C *= D_80096688;        | *(&tmp.unk1C) *= D_80096688;
 *   ((struct17 *)&tmp.unk1C)->unk0 *= ...;   | ((f32 *)&tmp)[7] *= ...;
 *   tmp.unk1C *= *(f32 *)&D_80096688;        | tmp.unk1C *= (f32)D_80096688;
 *   both on one source line; each in its own { } block; the two swapped; a `;` between
 *   them; an unrelated statement between them; both moved later in the function (just
 *   before func_15149130, and just after `tmp.unk0 = arg0;`);
 *   `f32 scale; scale = D_80096688; ... *= scale;` with `scale` declared LAST (200/64 --
 *      note `scale` is NOT homed, uopt folds it straight back into the same CSE) and
 *      declared FIRST (200/60 -- homed, breaks the layout);  `register f32 scale;` (200/64);
 *   `{ f32 t; t = tmp.unk20 * D_80096688; tmp.unk20 = t; }`;
 *   redeclaring the global as `extern f32 D_80096688[]` + `[0]`, as a struct member `.v`,
 *      and as `D_80096680[2]` -- all 200/64.
 * Also negative (each still 200/64, i.e. not the cause): removing func_150A8050,
 * func_150A7960, func_15145974, func_150484A0, the `%` modulo, the `1.0f /` division, the
 * unk14/unk18 pair, the unk2C/unk30/unk34 trio, unk24, unk28, unk10/unk12, unk8/unkC, the
 * early return; x/y/z regrouped as one `struct17 vec;`; x/y/z on one declarator line; `mtx`
 * as a flat `f32 mtx[16]`; `temp_v0` moved in the declaration order; the anonymous payload
 * struct hoisted to a named typedef; a struct ASSIGNMENT instead of memcpy (1832, worse --
 * IDO inlines it); memcpy with sizeof(tmp), with `(void *)((s32)temp_v0 + 0x28)`, with
 * `&((u8 *)temp_v0)[0x28]`, with a `(void *)` source cast, and at sizes 0x30/0x34/0x3C/
 * 0x40/0x54 -- all 200.  Dropping the memcpy entirely also gives 192/56, but memcpy is
 * spelled identically in NINE already-matched functions of this same TU (func_150139AC,
 * func_15014094, func_15014220, func_150142EC, func_15014F6C, func_15015104, func_150151D4,
 * func_15015354, func_15015644), so the memcpy spelling is not the lever.
 *
 * === FRAME MODEL CALIBRATION (from three MATCHED functions in this TU, for the next agent) ===
 *   func_15014220 frame 0x40: homes 0x10 @0x30, ra@0x2C
 *   func_15014F6C frame 0x98: homes 0x5C @0x3C, s0@0x30 ra@0x34
 *   func_150156F4 frame 0xB0: homes 0x7C @0x34, s0@0x28 ra@0x2C
 *   func_150144B8 golden 0xC0: homes 0x88 @0x38, s0@0x30 ra@0x34
 * Layout low->high is [outgoing args][compiler temps][saved regs][align pad][homes], homes
 * anchored at framesize and filled top-down in declaration order.
 *
 * === NEXT MOVES, IN PRIORITY ORDER ===
 * 1. Find the C spelling that yields one `lwc1` of a global feeding two `mul.s` with NO
 *    homed CSE temp.  A permuter run scoped to just these two statements is the right tool;
 *    the search space is small and the target is a single 8-byte frame delta.
 * 2. Grep the already-matched corpus for any function that reads one f32 global twice in a
 *    single basic block and check its frame against the model above.  If such a function
 *    exists and pays 0, diff its source shape against this one -- that is the answer.
 *    If EVERY such function pays 8, then the 8 bytes here is coming from somewhere else and
 *    the multiplies are only the marginal consumer, and the search should move on.
 * DO NOT re-run the shadow hypothesis, the local-count probe, or the memcpy spellings.
 * ============================================================================ */
#include <ultra64.h>

#include "functions.h"
#include "variables.h"

void func_151A9390(s32 arg0, s32 arg1, struct134 *arg2, s32 arg3, f32 arg4, f32 arg5, s32 arg6, s32 arg7, s32 arg8);
extern void (*D_80082E30[])(struct178 *);
extern void (*D_80082F28[])(struct16 *, f32);
extern f32 D_80096650;
extern f32 D_80096648;
extern f32 D_8009664C;
extern f32 D_80096654;
extern f32 D_80096658;
extern f32 D_8009665C;
extern f32 D_80096660;
extern f32 D_80096664;
extern f32 D_80096668;
extern f32 D_8009666C;
extern f32 D_80096670;
extern f32 D_80096674;
extern f32 D_80096678;
extern f32 D_80096680;
extern f32 D_80096684;
extern f32 D_80096688;
extern f32 D_8009668C;
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

// fat struct definition:
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15013778.s")

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
        tmp.unk4 = (f32)(((s16 *)arg0)[3] * ((s16 *)arg0)[3]) * D_80096648;
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
    tmp.unk48 = D_8009664C;

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
        temp_f = (f32)arg0->unk1C * D_80096650;
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

    tmpA = arg0->unk6 * D_80096654;
    tmpB = arg0->unk8 * D_80096658;

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
    sp30.unk3C = D_8009665C;

    sp30.unk0 = arg0->unk0;
    sp30.unk4 = arg0->unk2;
    sp30.unk8 = arg0->unk4;

    sp30.unk24 = 0x12C;
    sp30.unk38 = 0.0f;
    sp30.unk40 = D_80096660;
    sp30.unk44 = D_80096664;

    sp30.unk2C = (func_150ADA20() % 0x38U) + 0xC8;

    sp30.unkC = D_80096668 * tmpA;
    sp30.unk14 = D_8009666C * tmpA;
    sp30.unk18 = (D_80096674 * tmpB) + ((sp30.unk10 = D_80096670 * tmpB), 0);
    sp30.unk1C = D_80096678 * tmpB;

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

    func_151A9390((u8)(bit16 | bit1 | bit2 | bit4 | bit8), *((u8 *)arg0 + 0x1F), arg0, 0, *(f32 *)&D_8009667C, 100.0f, -1, 0xFF, 1);
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

    temp_f4 = (f32)(arg0->unk1C & 0xFFFFU) * D_80096680;
    temp_f6 = (f32)(((u32)arg0->unk1C >> 16) & 0xFFFFU) * D_80096680;
    temp_f2 = (f32)(arg0->unk20 & 0xFFFFU) * D_80096680;
    temp_f8 = (f32)(((u32)arg0->unk20 >> 16) & 0xFFFFU) * D_80096680;

    temp_f0 = func_1514462C((s32)arg0);

    tmp.unk0 = arg0;
    tmp.unk4 = (temp_f4 * temp_f0) * D_80096684;
    tmp.unk8 = (temp_f6 * temp_f0) * D_80096684;
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
    tmp.unk1C *= D_80096688;
    tmp.unk20 *= D_80096688;

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
    tmp.unk28 = ((f32)((arg0->unk1C >> 16) & 0xFF) * 0.00390625f) * D_8009668C;

    temp_v0 = func_15149130(0x12C, -1, 0x2A, -1, 0, 0, (struct37 *)0x38, 0xFF, 0);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x38);
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_1501474C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15014B60.s")

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
extern f32 D_800966B4;

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
    tmp.unk20 = D_800966B4;
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
