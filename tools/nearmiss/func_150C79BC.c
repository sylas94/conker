/* NEAR-MISS: game_F4D20 / func_150C79BC  (724 B)
 *
 *   raw fastscore    : 85 real mismatched rows
 *   n= gap           : 181/181 -- ZERO.  There is NO trailing pad on this function.
 *   pad-corrected    : 85, but see below -- the TRUE delta is ~1 instruction.
 *
 * MEASUREMENT TRAP (cost this wave ~30 min, worth recording):
 *   tools/fastscore.py runs `objdump -d`, which COLLAPSES runs of zero words into a
 *   literal "..." line.  This function has two `mflo; nop; nop` sequences, so plain
 *   fastscore silently DROPS 4 instructions, reports n=177/181, and mis-aligns every
 *   index after the first collapse -- inventing ~100 phantom mismatches AND a phantom
 *   "4-word pad" that does not exist.  Re-score with `objdump -dz`
 *   (scratchpad/fs2.py) before believing any number on this function.
 *
 * WHAT IS ALREADY PROVEN CORRECT (do not re-derive):
 *   - frame 0x60, args area 0x30, saved s0/s1/ra at 0x34/0x38/0x3C, locals 0x40-0x5F.
 *   - EXACTLY 5 word-locals then the u8 LAST: locals grow downward byte-granularly, so
 *     5 words (0x5C,0x58,0x54,0x50,0x4C) put the u8 at 0x4B, which is where gold's
 *     `sb $v0, 0x4B($sp)` is.  4 or 6 words puts it at 0x4F / 0x47 and is wrong.
 *   - the 5 words are x, y, z, r, t (t = the u8 first argument of func_15179FE0 bound
 *     to a local).  Binding `t` is what moves the CSE temp from 0x40 to gold's 0x44.
 *   - source reads the struct in the order unk2F8, unk2FC, unk300.  This is pinned by
 *     the FP pair rotation: gold gives 2F8->f4/f6, 2FC->f8/f10, 300->f16/f18, i.e.
 *     source order maps 1:1 onto the f4/f6, f8/f10, f16/f18 pair sequence.  Writing
 *     x and z first (2F8,300,2FC) swaps f8/f10 with f16/f18 and is wrong -- this is
 *     what forces `y` to exist as a named local at all.
 *   - func_150ADA20 really returns a WORD (divu/sltiu with no zero-extension) and
 *     func_15048A40 really returns f32; both are mis-declared in functions.h, so both
 *     use the established file-local prototype-shadow idiom (game_10CD70.c,
 *     game_10B7D0.c, game_142560.c all do exactly this).
 *   - func_15179FE0's full 11-arg signature is known from game_1A7260.c:36.
 *   - D_800887F4 is a genuine extern: the golden object has ONLY .text, no .data/.bss,
 *     so it is NOT a TU-local static.
 *
 * THE ONE REMAINING DEFECT (all 85 rows are its cascade):
 *   gold hoists `lui $t1, %hi(D_800887F4)` -- the ELSE arm's load address -- into the
 *   ENTRY block (at idx19, before `bnez $at`), and uses $v1 for both `y-2500` and
 *   `y-1583`.  We emit that lui inside the else block and use $t2/$t7 for the diffs.
 *   Net instruction COUNT is identical (181/181); only the position differs, which
 *   shifts every subsequent index by one and manufactures the other ~84 rows.
 *   Structurally the two listings are line-for-line identical otherwise.
 *
 * DO NOT REPEAT (all measured, all flat or worse):
 *   - separate sx/sz locals for the spawn coords: IDO abandons saved registers
 *     entirely (x/z land in t-regs and get spilled) -- 194 and much worse shape.
 *   - binding `y-2500` and `y-1583` to one shared local `d`: flat at 88, does NOT
 *     move the diffs into $v1.  Naming is inert here.
 *   - a bare nested block around the pointer/deref: reorders codegen (proven on
 *     target 1 in this same wave).
 *   - dummy filler locals: they DO change the frame, but only the count matters.
 *
 * PERMUTER RUN (done -- selftest PASSED all of a/b/b2/c/d/e; base 555, ~5200 iters, -j4):
 *   best it found was 250, via `if ((t = D_800887F4) == 0)` -- an assignment-in-condition
 *   that hijacks the UNRELATED local `t`.  That is the banned forcer class verbatim
 *   ("(obj = base->unk28C)"), so it is REFUSED as an author.  As a LOCATOR it is still
 *   informative and it agrees with the hand analysis: binding the THEN arm's D_800887F4
 *   load to a variable is what shifts the allocation, i.e. the blocker really is where
 *   the flag's address/value gets materialised, not the surrounding shape.  Note 250 is
 *   still far from 0, so even the forcer does not finish it.
 *
 * NEXT MOVE: re-run the permuter seeded from THIS file with a longer budget, and/or attack
 *   the `%hi` placement directly.  Everything except that one hoist is already exact.
 */
#include <ultra64.h>
/* include/functions.h declares func_150ADA20 as returning u8 and func_15048A40 as
 * returning void.  The golden code here feeds func_150ADA20's result straight into
 * `divu`/`sltiu` and uses func_15048A40's f32 result, neither of which those
 * declarations can produce.  Per project policy the shared header is left alone and the
 * correct prototypes are made file-local. */
#define func_150ADA20 func_150ADA20_u8_decl_in_functions_h
#define func_15048A40 func_15048A40_void_decl_in_functions_h
#include "functions.h"
#undef func_150ADA20
#undef func_15048A40
u32 func_150ADA20(void);
f32 func_15048A40(u8 arg0);
#include "variables.h"


extern void func_1511650C(struct131 *arg0, s32, s32, f32);
extern struct131 *func_151149AC(u8);

void func_150C7870(struct131 *arg0) {
    if (!(((u8 *)D_800D2E4C)[0xA] & 8)) {
        if (!(((u8 *)D_800DBEF4)[0x73] & 4)) {
            func_1511650C(arg0, 1, 0x353, 1000.0f);
        } else {
            func_1511650C(arg0, 1, 0x43, 400.0f);
        }
    }
}

typedef struct {
    u8  pad00[0x3C];
    s32 unk3C;
    u8  pad40[0x33];
    u8  unk73;
    u8  pad74[0x16C];
    s32 unk1E0;
    u8  pad1E4[0x38];
    s32 unk21C;
} GameObj150C78E0;

typedef struct {
    u8  pad00[0x3C];
    s32 unk3C;
} SubObj150C78E0;

extern void func_151150BC(GameObj150C78E0 *);

void func_150C78E0(GameObj150C78E0 *arg0) {
    SubObj150C78E0 *temp;

    if (!(arg0->unk73 & 4)) {
        temp = (SubObj150C78E0 *)((u8 *)D_800DBEF4 + 0x1E0);
        arg0->unk3C = -(temp->unk3C & 0xFFFF0000) & 0xFFFF0000;
        func_151150BC(arg0);
    }
}

void func_150C7930(GameObj150C78E0 *arg0) {
    SubObj150C78E0 *temp;

    temp = (SubObj150C78E0 *)((u8 *)D_800DBEF4 + 0x1E0);
    arg0->unk3C = temp->unk3C & 0xFFFF0000;
    func_151150BC(arg0);
}

extern s32 func_15116110(GameObj150C78E0 *);

typedef struct {
    u8  pad00[0x13];
    s8  unk13;
} Obj7C;

typedef struct {
    u8  pad00[0x3C];
    s16 unk3C;
} SubObj7968;

typedef struct {
    u8  pad00[0x73];
    u8  unk73;
    u8  pad74[0x8];
    Obj7C *unk7C;
} GameObj150C7968;

void func_150C7968(GameObj150C7968 *arg0) {
    SubObj7968 *temp;
    Obj7C *obj;
    s32 t;

    func_15116110((GameObj150C78E0 *)arg0);
    if (!(arg0->unk73 & 4)) {
        temp = (SubObj7968 *)((u8 *)D_800DBEF4 + 0x1E0);
        obj = arg0->unk7C;
        t = temp->unk3C >> 4;
        if (obj != 0) {
            obj->unk13 = t;
        }
    }
}

extern void func_1000D96C(s32, s32, s32);
extern void func_1000DE1C(s32, s32);
extern f32 func_150489B0(u8);
extern void func_15179FE0(u8, s16, s16, s16, s8, u16, u16, u8, u8, u8, s32);
extern f32 D_800A04D0;
extern f32 D_800A04D4;
extern s32 D_800887F4;

void func_150C79BC(s32 arg0) {
    s32 x;
    s32 y;
    s32 z;
    s32 r;
    s32 t;
    u8 ang;

    x = (s32)D_800DBFF0[arg0].unk2F8 + 2418;
    y = (s32)D_800DBFF0[arg0].unk2FC;
    z = (s32)D_800DBFF0[arg0].unk300 - 1775;
    if (((y - 2500) >= -199) && (((x * x) + (z * z)) < 1440000)) {
        if (D_800887F4 == 0) {
            func_1000D96C(0x5F, 0xF, 6);
            func_1000DE1C(0x10, 4);
            D_800887F4 = 1;
        }
    } else {
        if (D_800887F4 != 0) {
            func_1000D96C(0xF, 0x5F, 4);
            func_1000D96C(0x10, 0, 3);
            D_800887F4 = 0;
        }
    }
    if ((((s32)D_800DBFF0[arg0].unk2FC - 1583) < 0) && (((x * x) + (z * z)) < 810000) &&
        ((func_150ADA20() & 0xFFFF) < 0x2000)) {
        r = func_150ADA20() % 900;
        ang = func_150ADA20();
        x = (s32)((func_150489B0(ang) * (f32)r) + D_800A04D0);
        z = (s32)((func_15048A40(ang) * (f32)r) + D_800A04D4);
        t = (s32)((f32)((func_150ADA20() & 0xFFFF) * 2) * 0.0000152587890625f);
        func_15179FE0(t, (s16)x, 1583, (s16)z, 7, 1200, 37, 10, 30, 3, 8);
    }
}

typedef struct {
    s32 unk0;
    s32 unk4;
} Entry150C7C90;

typedef struct {
    u8 pad00[0x1C];
    Entry150C7C90 *unk1C;
    u8 pad20[0x1C];
    s32 unk3C;
    u8 pad40[0x3C];
    s32 unk7C;
} GameObj150C7C90;

void func_150C7C90(GameObj150C7C90 *arg0) {
    Entry150C7C90 *entry;
    Entry150C7C90 *selected;
    s32 idx;
    s32 count;
    s32 angle;
    s32 word;
    s32 newWord;

    idx = arg0->unk7C;
    if (idx == 0) {
        selected = arg0->unk1C;
        count = 0;
        if (*(s8 *)&selected->unk0 != -0xE) {
            do {
                count++;
            } while (*(s8 *)&selected[count].unk0 != -0xE);
        }
        arg0->unk7C = count;
        idx = count;
    }
    selected = &arg0->unk1C[idx];
    angle = -0x29D - func_151149AC(arg0->unk3C & 0xFF)->unk12;
    if (arg0->unk3C & 0x8000) {
        angle = 0x344 - angle;
    }
    while (angle < 0) {
        angle += 0x400;
    }
    while (angle >= 0x400) {
        angle -= 0x400;
    }
    selected->unk0 &= ~0xFFF;
    selected->unk0 |= angle;
}

typedef struct {
    u8 pad00[0x10];
    s16 unk10;
    s16 unk12;
    s16 unk14;
} GameObj150C7D7C;

void func_150C7D7C(GameObj150C7D7C *arg0) {
    struct127 *temp_v0;

    temp_v0 = func_15083E90(0xC);
    arg0->unk10 = (s16)(s32)(temp_v0->x_position - 30.0f);
    arg0->unk12 = (s16)(s32)(temp_v0->y_position + 50.0f);
    arg0->unk14 = (s16)(s32)(temp_v0->z_position + 30.0f);
}
