/* func_151438D8  (game_16EE20.c)  --  *** CLOSED: score 0, SHIPPED into
 * conker/src/game_16EE20.c.  This file is now a RECORD, not a backlog item. ***
 *
 * The live definition is in the TU; do not re-decompile.  Verification run:
 *     score 0 WITH -R and WITHOUT -R
 *     .text / .rodata / .data / .bss all byte-IDENTICAL to
 *     expected/build/src/game_16EE20.c.o
 *     relocation table = the SAME 5 entries at the SAME offsets
 *     (R_MIPS_HI16/LO16 D_800D3094, R_MIPS_26 func_15143D18,
 *      R_MIPS_HI16/LO16 D_800D3098); they only appear at a different POSITION
 *     in the table because the expected object got them from the appended
 *     GLOBAL_ASM block instead of inline C.  Position in the reloc table does
 *     not affect linking -- each entry carries its own r_offset.
 *     pragma count 26 -> 25, the correct one removed, nothing else lost.
 *
 * ===========================================================================
 * WHAT ACTUALLY CLOSED IT -- SYSTEMIC, REUSABLE, AND MEASURED BOTH WAYS
 * ===========================================================================
 * The C body below was already correct at the previous park (score 20, "residual =
 * ALLOCATION, 4 instructions").  The 20 was NOT allocation.  It was the SPELLING OF
 * THE WRONG-HEADER WORKAROUND.
 *
 * variables.h declares      extern struct178 D_800D3098[73];
 * but the symbol really holds a POINTER (golden does `lw $t9, %lo(D_800D3098)(...)`
 * then adds i*0x34).  Twelve other TUs work around that with the cast-through-address
 * idiom `*(s32 *) &D_800D3098`, and the previous park copied it:
 *
 *     #define OBJTBL ((ObjRec *) *(s32 *) &D_800D3098)      -> score 20   (measured)
 *
 * Replacing it with the SANCTIONED file-local shadow from CLAUDE.md:
 *
 *     #define D_800D3098 D_800D3098_array_decl_in_variables_h
 *     #include "variables.h"
 *     #undef  D_800D3098
 *     ...
 *     extern ObjRec *D_800D3098;
 *     #define OBJTBL D_800D3098                             -> score 0    (measured)
 *
 * Both spellings were built in the same session, same tree, same flags.  The entire
 * 20 was these four instructions, at the two `result = &OBJTBL[i];` sites only:
 *
 *     golden  2350: lw   t6,0(a2)    mine(cast)  2350: lw   t8,0(a2)
 *             2354: mflo t8                      2354: mflo t6
 *             2358: addu t0,t8,t6                2358: addu t0,t8,t6     <- SAME WORD
 *     (identically at 2370/2374 with t7/t9)
 *
 * i.e. only which temp register receives the base load vs. the mflo is swapped; the
 * `addu` word itself is byte-identical.  Reading this as a register-allocation
 * residual is what parked it.  It is really an EXPRESSION-SHAPE residual: the cast
 * `((T *) *(s32 *) &SYM)` makes IDO evaluate base-then-offset, while a plain
 * `extern T *SYM` evaluates offset-then-base at pointer-VALUE sites (it makes no
 * difference at the eleven pointer-as-load-base sites, which matched in both spellings).
 *
 * >>> RULE: when a shared header types a pointer as an array, NEVER reach it with
 * >>> `*(s32 *) &SYM` in a function you are trying to match.  Shadow the header
 * >>> declaration and re-declare the real type.  The cast idiom is fine for reading
 * >>> code and fine at load-base sites, but it costs the operand order wherever the
 * >>> address is produced as a VALUE.
 *
 * ===========================================================================
 * READING NOTES ON GOLDEN (kept: they pin the struct and the API)
 * ===========================================================================
 *  - `sw a2,0x68(sp)` in the prologue + `lhu v0,0x6A(sp)` later  =>  arg2 is u16.
 *  - `addiu a0,sp,0x60` / `addiu a1,sp,0x64` passed to func_15143D18  =>  arg0 and
 *    arg1 are passed BY ADDRESS and are modified by the callee; every later read of
 *    arg1 reloads from 0x64(sp), which is why the loop's back-edge test reloads it.
 *  - all twelve `andi v0,<bit>` are hoisted into the loop preheader (they are
 *    loop-invariant); six stay in t1..t5/ra and six spill to 0x20..0x34.
 *  - `checked`/`matched` are u16: every accumulate is `ori` followed by `andi ,0xFFFF`.
 *    In the 0x1 block the andi folds away because both are provably still 0.
 *  - bit 0x800 is never tested; 0x7FF is the "all eleven fields compared" sentinel and
 *    0x1000 selects require-all vs. require-any.  That is the source's own design.
 *  - `arg3->unk15 == (OBJTBL[i].unk15 >> 2)` really is asymmetric in golden
 *    (`lbu` both sides, `sra` by 2 on the table side only).  u8 promotes to signed int,
 *    hence `sra` rather than `srl`.  This is original-game behaviour; do not "fix" it.
 *  - struct178 in the shared header types 0x06..0x33 as one u8 blob, which cannot
 *    express the s16/f32/u8/s32 members this search compares, so ObjRec below is a
 *    file-local shadow of it.  Stride 0x34 is confirmed by `li a3,0x34` + `multu`.
 */

/* ---- shipped form, for the record; the live copy is in conker/src/game_16EE20.c ---- */

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ u8  unk14;
    /* 0x15 */ u8  unk15;
    /* 0x16 */ u8  unk16;
    /* 0x17 */ u8  unk17;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ u8  unk24[0x10];
} ObjRec; /* size 0x34 */

extern ObjRec *D_800D3098;
#define OBJTBL D_800D3098

void func_15143D18(s32 *, s32 *, s32, s32);

ObjRec *func_151438D8(s32 arg0, s32 arg1, u16 arg2, ObjRec *arg3) {
    s32 i;
    ObjRec *result;
    u16 checked;
    u16 matched;

    result = NULL;
    if (arg3 == NULL) {
        return NULL;
    }
    func_15143D18(&arg0, &arg1, 0, D_800D3094);
    for (i = arg0; i < arg1; i++) {
        checked = 0;
        matched = 0;
        if (arg2 & 0x1) {
            if ((arg3->unk0 == OBJTBL[i].unk0) && (arg3->unk2 == OBJTBL[i].unk2) && (arg3->unk4 == OBJTBL[i].unk4)) {
                checked |= 0x1;
                matched |= 0x1;
            }
        } else {
            checked |= 0x1;
        }
        if (arg2 & 0x2) {
            if ((arg3->unk6 == OBJTBL[i].unk6) && (arg3->unk8 == OBJTBL[i].unk8) && (arg3->unkA == OBJTBL[i].unkA)) {
                checked |= 0x2;
                matched |= 0x2;
            }
        } else {
            checked |= 0x2;
        }
        if (arg2 & 0x4) {
            if (arg3->unkC == OBJTBL[i].unkC) {
                checked |= 0x4;
                matched |= 0x4;
            }
        } else {
            checked |= 0x4;
        }
        if (arg2 & 0x8) {
            if (arg3->unk10 == OBJTBL[i].unk10) {
                checked |= 0x8;
                matched |= 0x8;
            }
        } else {
            checked |= 0x8;
        }
        if (arg2 & 0x10) {
            if (arg3->unk14 == OBJTBL[i].unk14) {
                checked |= 0x10;
                matched |= 0x10;
            }
        } else {
            checked |= 0x10;
        }
        if (arg2 & 0x20) {
            if (arg3->unk15 == (OBJTBL[i].unk15 >> 2)) {
                checked |= 0x20;
                matched |= 0x20;
            }
        } else {
            checked |= 0x20;
        }
        if (arg2 & 0x40) {
            if (arg3->unk16 == OBJTBL[i].unk16) {
                checked |= 0x40;
                matched |= 0x40;
            }
        } else {
            checked |= 0x40;
        }
        if (arg2 & 0x80) {
            if (arg3->unk17 == OBJTBL[i].unk17) {
                checked |= 0x80;
                matched |= 0x80;
            }
        } else {
            checked |= 0x80;
        }
        if (arg2 & 0x100) {
            if (arg3->unk18 == OBJTBL[i].unk18) {
                checked |= 0x100;
                matched |= 0x100;
            }
        } else {
            checked |= 0x100;
        }
        if (arg2 & 0x200) {
            if (arg3->unk1C == OBJTBL[i].unk1C) {
                checked |= 0x200;
                matched |= 0x200;
            }
        } else {
            checked |= 0x200;
        }
        if (arg2 & 0x400) {
            if (arg3->unk20 == OBJTBL[i].unk20) {
                checked |= 0x400;
                matched |= 0x400;
            }
        } else {
            checked |= 0x400;
        }
        if (arg2 & 0x1000) {
            if (checked == 0x7FF) {
                result = &OBJTBL[i];
            }
        } else {
            if (matched != 0) {
                result = &OBJTBL[i];
            }
        }
    }
    return result;
}
