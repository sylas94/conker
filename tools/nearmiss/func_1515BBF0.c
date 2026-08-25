/* tools/nearmiss/func_1515BBF0.c  --  game_188F90        *** PARKED: RANKING TIE ***
 *
 * KIND: WHOLE-TU REPLACEMENT.  This file is a complete, compilable copy of
 *       conker/src/game_188F90.c with func_1515BBF0's #pragma GLOBAL_ASM
 *       replaced by live C.  Score it DIRECTLY, in one command, no edits:
 *
 *         python3 tools/fastscore.py game_188F90 func_1515BBF0 tools/nearmiss/func_1515BBF0.c
 *
 *       (It used to be a snippet that also needed a hand-applied struct edit.
 *        It does not any more -- the typedefs it needs travel with it, right
 *        above the function.  Nothing else in the TU has been touched.)
 *
 * SCORE: raw mism = 43, n=150/152.  The golden .s carries a TRAILING
 *        `jr $ra / nop` pair (0x1515BE48/BE4C) that belongs to the next stub,
 *        so 20 of that 43 is pure phantom length penalty.
 *        PAD-CORRECTED = 23 real rows.
 * Progress: 68 raw (58 real) -> 43 raw (33 real) -> 43 raw (23 real) -> stuck.
 *
 * Instructions idx0..idx116 -- the prologue through func_1513F4E4 and the
 * unk11&2 branch, ~78% of the function -- are BYTE-EXACT including every
 * register name and every sp offset.
 *
 * ==========================  FRAME LAW (see also func_15166B50.c)  ==========
 * IDO reserves a stack slot for EVERY declared local, even ones that end up
 * living only in registers, laid out TOP-DOWN in declaration order.  The golden
 * frame is 0x78 with `flag` at sp+0x73 and the eight s16 outputs at 0x70..0x62;
 * a naive local set gives frame 0x70 and every sp offset 8 too low.  The fix is
 * THREE word-sized scratch locals: one BEFORE `flag` and TWO AFTER the eight
 * s16s.  `mode` is a plausible identity for one; the other two are unidentified.
 *
 * ==========================  WHAT IS LEFT (23 rows)  ========================
 * All 23 are idx117..idx142: the func_15142FBC call setup and the three Gfx
 * words after it.  There is really only ONE fault, and it is a TEMP-REGISTER
 * ROTATION OFFSET OF 4 that begins exactly at idx117:
 *
 *     ours   lbu t1 / sll t2 / lui+addiu t3 / lw t4 / lw t5   -> tail t6,t7,t8,t9
 *     golden lbu t5 / sll t6 / lui+addiu t7 / lw t8 / lw t9   -> tail t0,t1,t2,t3
 *
 * Both sides allocate exactly FIVE temps in this region and both then run the
 * tail off the next four.  Same instructions, same order, same offsets.  The
 * ONLY difference is where the rotation counter stands when idx117 is reached
 * -- ours at t1, golden at t5 -- and everything else follows mechanically:
 *   (a) golden's counter recycles $t9 for `lw t9,0x0(v0)` immediately after
 *       `or t3,t9,t0` has read it.  That WAR hazard PINS the schedule, which is
 *       why golden emits the whole othermode-H OR chain BEFORE the two arg-2
 *       `lw`s and lands the second OR in a fresh $t3 rather than back in $v1.
 *       Ours gets fresh t4/t5 for the loads, so the scheduler hoists them.
 *       The interleave is a SYMPTOM of the rotation, not an independent bug.
 *   (b) the 13 tail rows are the same rotation, offset 6 (= -4 mod 10).
 * Since idx0..idx116 are byte-identical, the 4 extra allocations golden makes
 * must happen INSIDE that byte-identical prefix and be eliminated before
 * emission.  No source spelling found so far reproduces them.
 *
 * ==========================  DO NOT REPEAT  =================================
 * Everything below was MEASURED.  `tail=` is the register of the tail's first
 * `lui ...,0x100`; golden is t0, and NOTHING has ever moved it off t6.
 *
 * OR-chain spelling (all tail=t6):
 *   mode = mode | 0x80000 | D_800D2C9C;  then `mode | 0x2CA0` .... 23  <- this file
 *   (mode | 0x80000) | D_800D2C9C          ...................... 23 (BYTE-IDENTICAL)
 *   mode |= 0x80000 | D_800D2C9C           ...................... 23
 *   `0x2CA0 | mode` / `(mode | 0x2CA0)` at the call site ......... 23
 *   mode |= 0x80000; mode |= D_800D2C9C;   ...................... 25
 *   mode = mode | 0x80000; mode = mode | D_800D2C9C; ............ 25
 *   D_800D2C9C | mode | 0x80000            ...................... 25
 *   mode | 0x80000 | D_800D2C9C | 0x2CA0 inline ................. 88 (151 instrs:
 *       IDO lands the second OR in $a1 and needs an extra ori/or pair)
 *   mode | 0x82CA0 | D_800D2C9C            ...................... 27
 *
 * arg 2 (all tail=t6, all 23 and BYTE-IDENTICAL to each other):
 *   .unk4 | .unk0   /   .unk0 | .unk4  (IDO canonicalises the order)
 *   (&D_800A4AC8[i])->unk4 | ...      /   D_800A4AC8[(s32)i]...
 *   struct fields typed u32 instead of s32
 *   hoisted into a scratch local before the call .... 27 (worse)
 *   hoisted into a scratch local after the mode chain ... 23
 *   a `Struct800A4AC8 *e` pointer local ............ 37 (worse)
 *
 * declarations -- a TOTAL ranking tie, 14 variants, every one 23/tail=t6:
 *   scratch pair as s32, u32, "u8 *", "Gfx *", f32, `s32 d[2]`, `s16 d[4]`;
 *   `mode` moved through all three scratch slots; `flag` as u8/s8/char.
 *   Only COUNT and SIZE are observable.  Omitting the scratch locals: 58 real
 *   rows, frame -112.  A FOURTH scratch local: frame -128, 50 real rows.
 *   Moving `flag = 1;` after the first call: breaks at idx6, 77 real rows.
 *
 * tail shape (all 23/tail=t6):
 *   a used "Gfx *g" local driving the last three writes and the return, in each
 *   of the three scratch slots;  `g = gfx;` copy;  `gfx+1 / gfx+2 / return
 *   gfx+3` instead of `gfx++`.
 *
 * prototypes / types (all 23/tail=t6):
 *   func_15142FBC as (Gfx*,u32,u32,u8*) and (Gfx*,s32,s32,void*);
 *   `mode` as u32;  D_800D2C9C as u32;  func_15142E24 taking Struct80090B60*
 *   with the (s32) cast dropped;  `(s32)(D_80090B60 + i)` for the cast;
 *   `(arg1->unk11 & 2) != 0`.
 *
 * an inline ternary for the if/else: IDO allocates an EXTRA 4-byte temp slot,
 *   frame -128, 41 real rows.
 *
 * The third parameter `arg2` really is unused: golden homes it with
 * `sw $a2, 0x80($sp)` and never reads it back, and this file reproduces that
 * store exactly.  Do not invent a use for it.
 *
 * ==========================  THE PERMUTER DOES NOT WORK HERE  ===============
 * conker/permuter_tu.sh selftest FAILS check (b2) on this TU, and it is a REAL
 * failure, not the known head-SIGPIPE false negative:  pycparser's round trip
 * of base.c swaps `sw t7,0x4(v0)` and `sw t6,0x0(v0)` in the gSPVertex
 * expansion.  Golden stores w1 (0x4) BEFORE w0 (0x0) and this file already does;
 * the round trip does not.  So the permuter would search a landscape that is one
 * row wrong IN EXACTLY THE TAIL REGION THAT IS AT FAULT.
 * Measured anyway: 12 workers, 2955 iterations, ONE output the whole run, best
 * permuter score 655 vs base
 * 665 -- and that "win" re-scores at fastscore 43, i.e. NO improvement.  A
 * textbook case of asm-differ rewarding a diff alignment.  If the permuter is to
 * be used here at all, the gSPVertex expansion must first be written in a form
 * pycparser preserves.
 *
 * ==========================  WHAT TO TRY NEXT  =============================
 * Stop spelling the call.  The lever is whatever advances IDO's temp-register
 * rotation four extra times inside idx0..idx116 without changing a byte there.
 * Candidates not yet tested: a differently-shaped expression for one of the
 * SEVEN earlier calls (their args are all `arg1->unkNN` byte loads that IDO
 * CSEs -- `arg1->unk10` in particular is read twice in the func_15142E24 call
 * and CSEd to one `lbu`, which is exactly the kind of allocation that can
 * advance the counter and then vanish), or a different struct layout that makes
 * those loads take a different number of temps.
 *
 * Cross-reference: the sister target func_15036310 (game_637C0) was closed on
 * 2026-08-20 by exactly this kind of reasoning -- see tools/nearmiss/
 * func_15036310.c.  Its lesson: when a residue looks like "one register
 * rotation", check first whether an operand or statement is spelled in the
 * wrong ORDER at the source level.  Three commuted/reversed spellings, each
 * semantically identical, were worth 4 + 2 + 4 rows there.
 */
#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern s32 (*D_8008B078[])(void *);
extern s32 (*D_8008B07C[])(void *);
s32 func_1514401C(u8, void *, void *, u8);

struct Struct1515C158Inner {
    u8 pad0[0x8];
    struct Struct1515C158Inner *next;
    u8 padC[0x38];
    s32 unk44;
    s32 unk48;
};

extern u8 D_800DCE50[];

typedef struct {
    u8 pad0[0x10];
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 pad13;
    s16 unk14;
    u8 pad16[0x2];
    s32 unk18;
    s32 unk1C;
    u8 pad20[0x18];
    s8 unk38;
    s8 unk39;
} Struct1515BAE0;

void func_1515BAE0(Struct1515BAE0 *arg0) {
    s32 temp;
    u8 failed;

    failed = 0;
    if (arg0->unk11 & 1) {
        arg0->unk14 -= D_800BE9E4;
        if (arg0->unk14 < 0) {
            failed = 1;
        }
    }
    if (failed == 0) {
        temp = arg0->unk38;
        if (temp != -1) {
            if (D_8008B078[temp](arg0) == 0) {
                failed = 1;
            }
        }
        if (arg0->unk1C != 0) {
            failed = func_1514401C(arg0->unk10, &arg0->unk1C, &arg0->unk18, arg0->unk12);
        }
    }
    if (failed) {
        temp = arg0->unk39;
        if (temp != -1) {
            if (D_8008B07C[temp](arg0) != 0) {
                func_1516972C((struct102 *) arg0);
            }
        } else {
            func_1516972C((struct102 *) arg0);
        }
    }
}

typedef struct {
    s32 unk0;
    u8  unk4;
    u8  unk5;
    u16 unk6;
    u16 unk8;
    u16 unkA;
} Struct80090B60;

typedef struct {
    s32 unk0;
    s32 unk4;
} Struct800A4AC8;

typedef struct {
    u8 pad0[0x10];
    u8 unk10;
    u8 unk11;
    u8 pad12[0x6];
    s32 unk18;
    u8 pad1C[0x4];
    u8 unk20;
    u8 unk21;
    u8 unk22;
    u8 unk23;
    u8 unk24;
    u8 unk25;
    u8 unk26;
    u8 unk27;
    u8 unk28;
    u8 unk29;
    u8 unk2A;
    u8 unk2B;
    u8 unk2C;
    u8 pad2D[0x3];
    s32 unk30;
    s32 unk34;
    u8 pad38[0x18];
    Vtx unk50;
} Struct1515BBF0;

extern Struct80090B60 D_80090B60[];
extern Struct800A4AC8 D_800A4AC8[];
extern s32 D_800D2C9C;

void func_151441A4(s16 *, s16 *, s16 *, s16 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_151442FC(s16 *, s16 *, s16 *, s16 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
Gfx *func_15142B7C(Gfx *, s32, s32);
Gfx *func_15142C10(Gfx *, s32, s32, s32, s32, u8 *);
Gfx *func_15142CF0(Gfx *, s32, s32, s32, s32, s32, s32, u8 *);
Gfx *func_15142E24(Gfx *, s32, s32, s32, s32, s32, s32, u8, s32, u8 *, s32);
Gfx *func_1513F4E4(Gfx *, u8, u8 *);
Gfx *func_15142FBC(Gfx *, s32, s32, u8 *);

Gfx *func_1515BBF0(Gfx *gfx, Struct1515BBF0 *arg1, s32 arg2) {
    s32 mode;
    u8 flag;
    s16 sp70;
    s16 sp6E;
    s16 sp6C;
    s16 sp6A;
    s16 sp68;
    s16 sp66;
    s16 sp64;
    s16 sp62;
    s32 d1;
    s32 d2;

    flag = 1;
    func_151441A4(&sp70, &sp6E, &sp6C, &sp6A, arg1->unk20, arg1->unk21, arg1->unk22, arg1->unk23,
                  arg1->unk24, arg1->unk25, arg1->unk26, arg1->unk27, arg1->unk28, arg1->unk29);
    func_151442FC(&sp68, &sp66, &sp64, &sp62, arg1->unk20, arg1->unk21, arg1->unk22, arg1->unk23,
                  arg1->unk24, arg1->unk25, arg1->unk26, arg1->unk27, arg1->unk28, arg1->unk2A);
    gfx = func_15142B7C(gfx, arg1->unk30, arg1->unk34);
    gfx = func_15142C10(gfx, sp68, sp66, sp64, sp62, &flag);
    gfx = func_15142CF0(gfx, 0, 0, sp70, sp6E, sp6C, sp6A, &flag);
    gfx = func_15142E24(gfx, (s32)&D_80090B60[arg1->unk10], arg1->unk18, 0, 0, 0, arg1->unk10, 0, 0,
                        &flag, 3);
    gfx = func_1513F4E4(gfx, arg1->unk2C, &flag);
    if (arg1->unk11 & 2) {
        mode = 0x100000;
    } else {
        mode = 0;
    }
    mode = mode | 0x80000 | D_800D2C9C;
    gfx = func_15142FBC(gfx, mode | 0x2CA0,
                        D_800A4AC8[arg1->unk2B].unk4 | D_800A4AC8[arg1->unk2B].unk0, &flag);
    gSPVertex(gfx++, &arg1->unk50, 4, 0);
    gSP1Triangle(gfx++, 0, 1, 2, 0);
    gSP1Triangle(gfx++, 0, 2, 3, 0);
    return gfx;
}

extern void *func_15167A68(s32, s32, s32, s32, s32, s32);

struct Struct1515BE50_src {
    u8 pad0[0x14];
    f32 unk14;
    f32 unk18;
    f32 unk1C;
};

struct Struct1515BE50_ret {
    u8 pad0[0x10];
    s32 unk10;
    s32 unk14;
    u8 pad18[0x8];
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    s32 unk44;
    s32 unk48;
};

s32 func_1515BE50(struct Struct1515BE50_src **arg0, s32 arg1, s32 arg2, s32 arg3) {
    struct Struct1515BE50_ret *temp_v0;
    struct Struct1515BE50_ret *sp2C;

    if (*arg0 == 0) {
        return 0;
    }
    temp_v0 = (struct Struct1515BE50_ret *)func_15167A68(0x32, arg3, arg1 + 0x50, 1, (u8)arg2, 1);
    if (temp_v0 == 0) {
        return 0;
    }
    sp2C = temp_v0;
    memcpy((s32)temp_v0 + 0x18, arg0, 8);
    sp2C->unk20 = (*arg0)->unk14;
    sp2C->unk24 = (*arg0)->unk18;
    sp2C->unk28 = (*arg0)->unk1C;
    sp2C->unk2C = (*arg0)->unk14;
    sp2C->unk30 = (*arg0)->unk18;
    sp2C->unk34 = (*arg0)->unk1C;
    sp2C->unk44 = 0;
    sp2C->unk48 = -1;
    sp2C->unk10 = 1;
    sp2C->unk14 = 0;
    sp2C->unk38 = 0.0f;
    sp2C->unk3C = 0.0f;
    sp2C->unk40 = 0.0f;
    return sp2C;
}

extern void func_1514EDF0(struct225 *, s32);

void func_1515BF50(struct225 *arg0) {
    func_1514EDF0(arg0, (s32)arg0->unk18);
    func_15169804((struct102 *)arg0);
}

void func_1515BF7C(struct225 *arg0) {
    func_1514EDF0(arg0, (s32)arg0->unk18);
    func_15169824((struct102 *)arg0);
}

struct Struct1515BFA8Src {
    s32 unk0;
    u8 pad4[0x10];
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    u8 pad20[0x1B];
    u8 unk3B;
};

struct Vec1515BFA8 {
    f32 x;
    f32 y;
    f32 z;
};

struct Struct1515BFA8 {
    u8 pad0[0x18];
    struct Struct1515BFA8Src *unk18;
    u8 unk1C;
    u8 unk1D;
    s16 unk1E;
    struct Vec1515BFA8 unk20;
    struct Vec1515BFA8 unk2C;
    struct Vec1515BFA8 unk38;
};

void func_1515BFA8(struct Struct1515BFA8 *arg0) {
    s32 remove;
    struct Struct1515BFA8Src *src;

    remove = 0;
    if (arg0->unk1D & 1) {
        arg0->unk1E -= D_800BE9E4;
        if (arg0->unk1E < 0) {
            remove = 1;
        }
    }
    src = arg0->unk18;
    if ((src->unk0 == 0) || (src->unk3B != arg0->unk1C)) {
        remove = 1;
    }
    if (remove == 0) {
        arg0->unk2C = arg0->unk20;
        src = arg0->unk18;
        arg0->unk20.x = src->unk14;
        arg0->unk20.y = src->unk18;
        arg0->unk20.z = src->unk1C;
        arg0->unk38.x = (arg0->unk2C.x - arg0->unk20.x) * D_800BE9A8;
        arg0->unk38.y = (arg0->unk2C.y - arg0->unk20.y) * D_800BE9A8;
        arg0->unk38.z = (arg0->unk2C.z - arg0->unk20.z) * D_800BE9A8;
    }
    if (remove != 0) {
        func_1516972C((struct102 *)arg0);
    }
}

void func_1515C0B8(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x18, arg0 + 0x1C, arg0);
}

s32 func_1514ECE0(void *, s16, void *);

s32 func_1515C0F8(struct102 *arg0, s32 *arg1) {
    s32 *temp;
    s32 v;

    if (arg0 == 0) {
        return 0;
    }
    if (func_1514ECE0(*(void **)((u8 *)arg0 + 0x2F4), 0x16, &temp) != 0) {
        v = *(s32 *)((u8 *)temp + 0x10);
        *arg1 = v + 0x38;
        return 1;
    }
    return 0;
}

void func_1515C158(void) {
    s32 i;
    struct Struct1515C158Inner *node;

    i = 0;
    do {
        node = *(struct Struct1515C158Inner **)&D_800DCE50[i + 0xC8];
        i += 0x1A0;
        if (node != 0) {
            do {
                node->unk44 = 0;
                node->unk48 = -1;
                node = node->next;
            } while (node != 0);
        }
    } while ((u8 *)&D_800DD190 != &D_800DCE50[i]);
}

struct Struct1515C1A0 {
    u8 pad0[4];
    u8 unk4;
    u8 pad5[0xF];
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    u8 pad20[0xB2];
    s16 unkD2;
    s16 unkD4;
    s16 unkD6;
};

void func_1515C1A0(struct Struct1515C1A0 *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    u8 temp_v0;
    f32 temp_f0;

    temp_v0 = arg0->unk4;
    if ((temp_v0 < 0xBB) && (temp_v0 != 0xFF)) {
        *arg2 = arg0->unkD2;
        *arg3 = arg0->unkD4;
        arg1[0] = arg0->unk14;
        arg1[1] = arg0->unk18 + arg0->unkD6;
        arg1[2] = arg0->unk1C;
    } else {
        temp_f0 = 1.0f;
        *arg2 = temp_f0;
        *arg3 = temp_f0;
        arg1[0] = arg0->unk14;
        arg1[1] = arg0->unk18;
        arg1[2] = arg0->unk1C;
    }
}

struct Struct1515C244 {
    u8 pad0[4];
    u8 unk4;
    u8 pad5[0xF];
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    u8 pad20[0xC4];
    s16 unkE4;
    s16 unkE6;
    s16 unkE8;
};

void func_1515C244(struct Struct1515C244 *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    u8 temp_v0;
    f32 temp_f0;

    temp_v0 = arg0->unk4;
    if ((temp_v0 < 0xBB) && (temp_v0 != 0xFF)) {
        *arg2 = arg0->unkE4;
        *arg3 = arg0->unkE6;
        arg1[0] = arg0->unk14;
        arg1[1] = arg0->unk18 + arg0->unkE8;
        arg1[2] = arg0->unk1C;
    } else {
        temp_f0 = 1.0f;
        *arg2 = temp_f0;
        *arg3 = temp_f0;
        arg1[0] = arg0->unk14;
        arg1[1] = arg0->unk18;
        arg1[2] = arg0->unk1C;
    }
}
