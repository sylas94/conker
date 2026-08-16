/* ===========================================================================
 * func_150FF840  --  game_12C1E0.c  --  812 bytes / 203 instructions
 * PARKED at 5 (with AND without -R, window bounded to the symbol's 203 words).
 * draft1 3950 -> 3950 -> 325 -> 5.
 *
 * STATE: ONE instruction too long (816 vs golden 812).  Everything else is
 * byte-identical.  The single residual:
 *   golden  ca4: beqz  t2,d78          |  live C  ca0: beqzl t2,d7c
 *           ca8:  lwc1 $f16,0x11c(sp)  |          ca4:  lbu  t3,0x133(sp)
 * i.e. golden fills the second `if`'s branch delay slot with a speculated load
 * from the BODY (sp11C.unk0) and uses a plain beqz; the live C picks the THIRD
 * `if`'s condition load out of the branch TARGET, which forces `beqzl` and
 * duplicates `lbu t3,0x133(sp)` (once annulled, once at d78) -- that duplicate
 * is the extra instruction.  as1 PEEPHOLE / delay-slot-filler class.
 *
 * ---------------------------------------------------------------------------
 * THE TWO LEVERS THAT PAID.  BOTH ARE TYPE FIXES, BOTH ARE REUSABLE.
 * ---------------------------------------------------------------------------
 * (1) 3950 -> 325: functions.h declares `u8 func_150ADA20(void)`.  golden spills
 *     the RAW result of the two rand calls as WORDS (`sw $v0,0x58(sp)` /
 *     `lw $t1,0x58(sp)`) and feeds the full 32-bit value to `divu`; with the u8
 *     return type IDO narrows the spill to `sb $v0,0x5e(sp)` / `lbu`, i.e. it
 *     performs the modulo on the low byte only.  Fixed with the sanctioned
 *     FILE-LOCAL SHADOW (functions.h is included by 106 TUs):
 *         #define func_150ADA20 func_150ADA20_wrong_decl_in_functions_h
 *         #include "functions.h"
 *         #undef func_150ADA20
 *         s32 func_150ADA20(void);
 *     VERIFIED SAFE: every already-matched function in the TU
 *     (func_150FED30/FEFD0/FF084/FF288/FF2AC/FF6B4/FFB6C/FFBDC/FFC3C/FFCC8/FFD2C)
 *     still compares byte-identical to expected/ afterwards.
 *
 * (2) 325 -> 5: `&sp11C` is handed to SEVEN callees.  Where the callee's
 *     parameter is typed `s32`, IDO treats `&sp11C` as an integer VALUE,
 *     common-subexpression-eliminates the seven `addiu a?,sp,0x11c` and spills
 *     the result to a stack temp, reloading it with `lw a1,0x54(sp)`.  golden
 *     recomputes `addiu a1,sp,0x11c` at every site.  Retyping the parameters to
 *     real pointers stops the CSE.  Retyped, all in game_12C1E0.c:
 *         func_150FFCC8(s32 x5)      -> (struct127 *, struct17 * x4)
 *         func_150FFB6C(.., s32, ..) -> (struct17 *, struct17 *, struct127 *, s32)
 *         func_151D5A18 / func_151D3E6C file-local prototypes likewise
 *         the file-local func_15102B38 prototype: arg8 s32 -> struct17 *
 *     VERIFIED SAFE: func_150FFB6C and func_150FFCC8 still compare
 *     byte-identical to expected/ after the retype.
 *
 * ---------------------------------------------------------------------------
 * FRAME DECODE (SETTLED -- reproduces 0x128 exactly)
 * ---------------------------------------------------------------------------
 * framesize 0x128.  arg-build [0x00,0x3C) (func_15081690 takes 15 args).
 * saved s0 0x48, ra 0x4C.  temps [0x50,0x64).  Params at 0x128(a0) 0x12C(a1)
 * 0x130(a2) 0x134(a3) 0x138(arg4); arg1/arg2/arg3 are read as ((u8*)&argN)[3]
 * (golden homes them with `sw`, so they are word params, not u8 params).
 * Home area TOP-DOWN in declaration order, ENDING at 0x128:
 *   [0x11C,0x128) struct17 sp11C     [0x110,0x11C) struct17 sp110
 *   [0x104,0x110) struct17 sp104     [0x0F8,0x104) struct17 spF8
 *   [0x0F0,0x0F8) Vec2     spF0      [0x0E4,0x0F0) struct17 spE4
 *   [0x0D8,0x0E4) struct17 spD8      [0x0CC,0x0D8) struct17 spCC
 *   [0x068,0x0CC) Ray      ray (0x64 -- identical layout to Ray151C196C in
 *                              game_1ED0F0.c, which is how the size was pinned)
 *   [0x064,0x068) void *   dest
 *
 * ---------------------------------------------------------------------------
 * RODATA: this function is NOT rodata-blocked -- and the literal spelling HURTS
 * ---------------------------------------------------------------------------
 * D_800A2170/2174/2178/217C/2180/2184/2188 all have nonzero low 16 bits, but
 * none of them is hoisted out of a loop (this function has no loop), so the
 * `extern f32` spelling produces exactly golden's `lui %hi / lwc1 %lo` pair.
 * MEASURED: respelling all seven as literals (which is what a .rodata migration
 * would produce) takes the score 5 -> 1170 and does NOT fix the beqzl.  golden
 * also emits a SEPARATE `lui` per constant, whereas a local literal pool lets
 * IDO share one `lui %hi(.rodata)` across several `%lo` loads.  Both facts say
 * golden reads these as external symbols here.  DO NOT migrate for this one.
 *
 * ---------------------------------------------------------------------------
 * MEASURED NEGATIVES (bounded window, 203 words)
 * ---------------------------------------------------------------------------
 *  3950  draft1 (u8 func_150ADA20, s32 pointer params).
 *  3950  dropping the explicit `(s32)` casts on &sp11C.  BYTE-IDENTICAL -- the
 *        cast is not what creates the CSE, the callee's parameter TYPE is.
 *   325  + the func_150ADA20 file-local retype.
 *     5  + the pointer retypes.  CURRENT.
 *  1170  + respelling D_800A2170..D_800A2188 as float literals (rodata probe).
 *
 * ---------------------------------------------------------------------------
 * WAVE 2 (2026-08-14).  BASE RE-CONFIRMED 5 / 816 B (golden 812).  ALL SCORES
 * BOUNDED TO 203 WORDS.  Per-symbol byte compare of the whole TU re-run and
 * ALL ELEVEN already-matched functions are still IDENTICAL to expected/.
 * ---------------------------------------------------------------------------
 * THE RESIDUAL, RE-READ FROM THE BUILD (the old note above was half right):
 *   golden  c98 lbu   t2,0x12f(sp)   |  live  c90 lbu   t2,0x12f(sp)
 *           c9c lui   at,%hi(217C)   |        c94 lwc1  $f14,0x110(sp)
 *           ca0 lwc1  $f14,0x110(sp) |        c98 lui   at,%hi(217C)
 *           ca4 beqz  t2,d78         |        c9c beqzl t2,d78
 *           ca8  lwc1 $f16,0x11c(sp) |        ca0  lbu  t3,0x133(sp)   (annulled)
 *           cac lwc1  $f0,%lo(217C)  |        ca4 lwc1  $f0,%lo(217C)
 * and at the merge golden's branch TARGET *is* the `lbu t3,0x133(sp)`, while in
 * live the lbu sits one slot ABOVE the target and is therefore emitted TWICE
 * (annulled copy in the likely-branch slot + real copy at d74).  That duplicate
 * is the whole 4-byte excess.
 * MECHANISM (as1 delay-slot filler): golden's fall-through block begins with a
 * plain, movable `lwc1 $f16,0x11c(sp)`, so as1 fills the slot from the
 * fall-through and keeps a plain `beqz`.  In live the fall-through begins with
 * `lwc1 $f0,%lo(D_800A217C)(at)` -- the second half of a lui/%lo MACRO PAIR,
 * which as1 will not move into a delay slot -- so it falls back to filling from
 * the TARGET, which forces the annulled `beqzl` and the duplicate.
 * The upstream cause is a SCHEDULING difference: golden issues the three scale
 * constants (217C/2180/2184) as a block at the top of the if-body and hoists
 * BOTH operands of statement 1 (sp110.unk0 AND sp11C.unk0) above the branch;
 * live hoists only sp110.unk0 and loads the constants lazily.
 *
 * MEASURED THIS WAVE (all bounded 203, all vs the 5 base):
 *     5   `u8 arg1, u8 arg2, u8 arg3` params with plain `arg1`/`arg2`/`arg3`
 *         instead of `s32 argN` + `((u8 *)&argN)[3]`.  816 B, IDENTICAL OUTPUT.
 *         This is the BETTER-EVIDENCED form and is what is now live: IDO at
 *         -g3 homes a sub-word register param with a full-word `sw` and gives
 *         it DWARF offset +3, so `sw a1,0x12c(sp)` / `lbu t2,0x12f(sp)` is
 *         exactly u8-param homing.  The address-taken cast idiom is not needed
 *         and is not what blocks the delay slot.
 *     5   `struct17 spCC[3]` replacing spE4/spD8/spCC (the three are contiguous
 *         at 0xCC/0xD8/0xE4, so the array reproduces the frame exactly) with
 *         &spCC[0..2] at the func_150FFB6C calls.  816 B, IDENTICAL OUTPUT.
 *   175   naming the three scale constants in f32 locals (`f32 k0,k1,k2;`
 *         assigned at the top of the if-body).  832 B -- +4 instructions.
 *         f32 autos are NOT free here (unlike func_150FF2D4, which has no home
 *         area at all): the home area grows and the frame moves.  HARD NEGATIVE.
 *
 * RULED OUT BY THE GOLDEN INSTRUCTIONS THEMSELVES (do not re-test):
 *   `sp11C.unk0 + (sp110.unk0 * K)`  -- golden is `add.s $f6,$f4,$f16`, i.e.
 *        (mul) + sp11C.unk0, so the mul is the LEFT operand.
 *   `(K * sp110.unk0)`               -- golden is `mul.s $f4,$f14,$f0`, i.e.
 *        sp110.unk0 is the LEFT operand.
 *   column-major statement order     -- golden's stores run 0xcc,0xd0,0xd4,
 *        0xd8,... i.e. strictly row-major spCC,spD8,spE4.
 *   D_800A217C/2180/2184 as one array -- golden emits a SEPARATE
 *        `lui at,%hi(D_800A2180)` per constant, so they are separate symbols.
 *
 * RESIDUAL CLASS: as1 PEEPHOLE (delay-slot filler source) driven by a
 * SCHEDULING difference in the first four instructions of the if-body.  There
 * is no register-allocation error anywhere in the function; the whole 203-word
 * body is golden's apart from that one window.  BAILED at 5.
 * =========================================================================== */

/* ---- parked source: this is the 5 build, verbatim ---- */

/* at the top of the TU, replacing the plain `#include "functions.h"`: */
#define func_150ADA20 func_150ADA20_wrong_decl_in_functions_h
#include "functions.h"
#undef func_150ADA20
s32 func_150ADA20(void);

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
} Vec2_150FF840;

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ struct17 unk08;
    /* 0x14 */ struct17 unk14;
    /* 0x20 */ struct17 unk20;
    /* 0x2C */ struct17 unk2C;
    /* 0x38 */ struct17 unk38;
    /* 0x44 */ u8 unk44[0x12];
    /* 0x56 */ s16 unk56;
    /* 0x58 */ u8 unk58;
    /* 0x59 */ u8 unk59;
    /* 0x5A */ u8 unk5A;
    /* 0x5B */ u8 pad5B;
    /* 0x5C */ void *unk5C;
    /* 0x60 */ s32 unk60;
} Ray150FF840;

extern s32 D_800A2130;
extern struct17 D_800A213C;
extern f32 D_800A2170;
extern f32 D_800A2174;
extern f32 D_800A2178;
extern f32 D_800A217C;
extern f32 D_800A2180;
extern f32 D_800A2184;
extern f32 D_800A2188;
void func_150FFCC8(struct127 *, struct17 *, struct17 *, struct17 *, struct17 *);
void func_150FFB6C(struct17 *, struct17 *, struct127 *, s32);
void func_150FFC3C(struct127 *);
void func_150FFD84(struct17 *, struct17 *, s32, s32);
void func_15102B38(struct127 *, u8, struct17 *, struct17 *, Vec2_150FF840 *, s16, u8, f32, struct17 *, u8, s32, s16, u8, s32);
void func_15081690(struct127 *, f32, f32, f32, f32, f32, f32, void *, f32, s32, s32, s32, s32, s32, s32);
void func_15081E78(struct127 *, void *, s32);

/* NOTE (wave 2): the `s32 argN` + `((u8 *)&argN)[3]` form below and the plain
 * `u8 arg1, u8 arg2, u8 arg3` form with bare `arg1`/`arg2`/`arg3` both build to
 * BYTE-IDENTICAL output (5 / 816 B).  The u8 form is the better-evidenced one
 * (IDO at -g3 homes a sub-word register param with a full-word `sw` and gives it
 * DWARF offset +3, which is exactly `sw a1,0x12c(sp)` / `lbu t2,0x12f(sp)`), and
 * it also makes the func_151D3F14/func_15102B38 u8 parameters type-correct.
 * Use whichever; the cast idiom is NOT what blocks the delay slot. */
void func_150FF840(struct127 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    struct17 sp11C;
    struct17 sp110;
    struct17 sp104;
    struct17 spF8;
    Vec2_150FF840 spF0;
    struct17 spE4;
    struct17 spD8;
    struct17 spCC;
    Ray150FF840 ray;
    void *dest;

    func_150FFCC8(arg0, &sp11C, &sp110, &sp104, &spF8);
    func_151D5148(arg0);
    if ((arg0->unk1D4 != 0) && ((arg0->unk74 & 0xF) != 0xF)) {
        func_151D3F14(&sp11C, ((u8 *)&arg3)[3], arg4);
        spF0.unk4 = ((func_150ADA68() * D_800A2170) + 4800.0f) * D_800A2174;
        spF0.unk0 = ((func_150ADA68() * 220.0f) + 320.0f) * D_800A2178;
        func_15102B38(arg0, D_80088BB0, (struct17 *)&D_800A2130, &D_800A213C, &spF0,
                      (func_150ADA20() % 3U) + 4, (func_150ADA20() & 0x7F) + 0x80,
                      (func_150ADA68() * 450.0f) + 780.0f, &sp11C, 0xFF, 0, -1,
                      ((u8 *)&arg3)[3], arg4);
        func_150FFD84(&sp11C, &sp110, ((u8 *)&arg3)[3], arg4);
    }
    if (((u8 *)&arg1)[3] != 0) {
        spCC.unk0 = (sp110.unk0 * D_800A217C) + sp11C.unk0;
        spCC.unk4 = (sp110.unk4 * D_800A217C) + sp11C.unk4;
        spCC.unk8 = (sp110.unk8 * D_800A217C) + sp11C.unk8;
        spD8.unk0 = (sp110.unk0 * D_800A2180) + sp11C.unk0;
        spD8.unk4 = (sp110.unk4 * D_800A2180) + sp11C.unk4;
        spD8.unk8 = (sp110.unk8 * D_800A2180) + sp11C.unk8;
        spE4.unk0 = (sp110.unk0 * D_800A2184) + sp11C.unk0;
        spE4.unk4 = (sp110.unk4 * D_800A2184) + sp11C.unk4;
        spE4.unk8 = (sp110.unk8 * D_800A2184) + sp11C.unk8;
        func_150FFB6C(&spCC, &sp11C, arg0, 0x32);
        func_150FFB6C(&spD8, &sp11C, arg0, 0x30);
        func_150FFB6C(&spE4, &sp11C, arg0, 0x31);
    }
    if (((u8 *)&arg2)[3] != 0) {
        if (arg0->unk31C != 0) {
            dest = (u8 *)arg0->unk31C + 0xB0;
        } else {
            dest = &ray;
        }
        func_15081690(arg0, sp11C.unk0, sp11C.unk4, sp11C.unk8,
                      sp110.unk0 * D_800A2188, sp110.unk4 * D_800A2188,
                      sp110.unk8 * D_800A2188, dest, 2000.0f, 0, 0, 0, -1, 0, 0);
        func_15081E78(arg0, dest, 0x10);
    }
    func_150FFC3C(arg0);
}

/* and the two live functions had to be retyped (both still byte-identical): */
/*  void func_150FFB6C(struct17 *arg0, struct17 *arg1, struct127 *arg2, s32 arg3)
 *  void func_150FFCC8(struct127 *arg0, struct17 *arg1, struct17 *arg2,
 *                     struct17 *arg3, struct17 *arg4)
 *  void func_151D5A18(struct127 *, struct17 *, struct17 *, struct17 *,
 *                     struct17 *, s32, u8);
 *  void func_151D3E6C(struct127 *, struct17 *, struct17 *, s32);
 */
