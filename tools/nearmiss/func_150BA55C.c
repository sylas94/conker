/* func_150BA55C  (game_E7970, 916 bytes)  --  PARKED at 1411 / 41600.
 *
 * TWO blockers, one of them the same rodata-migration issue as game_EEB10/func_150C16C0.
 *
 * (1) RODATA MIGRATION (worth 4512 -> 1411).  The eleven constants this function uses are
 *     game_E7970's own float pool at 0x2448F0..0x244918.  Written as `extern f32 D_8009FE*`
 *     (the usual escape) IDO hoists the loop-invariant ADDRESSES of D_8009FE38/D_8009FE3C
 *     into $s4/$s3 and never gets the VALUES into $f30/$f28, so golden's sixth callee-saved
 *     FP register is never allocated, spD8 gets promoted into $f28 instead of staying in
 *     memory, and the whole float colouring rotates.  Written as literals (as below) the
 *     colouring is exactly golden's.  Probe: converting only D_8009FE38/3C to literals and
 *     leaving the other nine extern already took 4512 -> 1621.
 *     BUT unlike game_EEB10 this is NOT a one-line yaml fix: splat's block
 *         conker.us.yaml:1246  - [0x2448D0, rodata]
 *     also contains D_8009FE28/D_8009FE2C, and D_8009FE2C belongs to game_E7380
 *     (func_150BA37C already references it), while D_8009FE5C..D_8009FE64 are used by this
 *     TU's other, already-matched functions as externs.  A migration would have to SPLIT
 *     the block at 0x2448F0 and again at 0x24491C.  Not attempted: the wave brief forbids
 *     editing conker.us.yaml.
 *
 *     ---- WAVE 63 CORRECTION: THE ABOVE SCOPING IS WRONG.  IT IS A SINGLE CUT. ----
 *     Block [0x2448D0, rodata] is 0x50 bytes, 0x2448D0..0x24491F, and it is exactly
 *     D_8009FE10..D_8009FE58 plus one zero pad word.  Every symbol was grepped across all
 *     of conker/asm and conker/src; the ownership is perfectly contiguous:
 *
 *       +0x00  2448D0  D_8009FE10   675          game_E7380  (func_150B9ED0 only)
 *       +0x04  2448D4  D_8009FE14   -1.022000074 game_E7380  (func_150B9ED0 only)
 *       +0x08  2448D8  D_8009FE18   0.5420000553 game_E7380  (func_150B9ED0 only)
 *       +0x0C  2448DC  D_8009FE1C   0.0373999998 game_E7380  (func_150B9ED0 only)
 *       +0x10  2448E0  D_8009FE20   0.0234999992 game_E7380  (func_150B9ED0 only)
 *       +0x14  2448E4  D_8009FE24   0.9404039979 game_E7380  (func_150B9ED0 only)
 *       +0x18  2448E8  D_8009FE28   1.084000111  game_E7380  (func_150B9ED0 only)
 *       +0x1C  2448EC  D_8009FE2C  -0.6000000238 game_E7380  (src, func_150BA37C -- MATCHED)
 *       ----------------- cut here, at 0x2448F0 -----------------
 *       +0x20  2448F0  D_8009FE30   0.3143000007 game_E7970  (func_150BA55C only)
 *       +0x24  2448F4  D_8009FE34   0.58100003   game_E7970  (func_150BA55C only)
 *       +0x28  2448F8  D_8009FE38  -9.322500229  game_E7970  (func_150BA55C only)
 *       +0x2C  2448FC  D_8009FE3C   18.64500046  game_E7970  (func_150BA55C only)
 *       +0x30  244900  D_8009FE40   0.09400000423 game_E7970 (func_150BA55C only)
 *       +0x34  244904  D_8009FE44   0.05100000277 game_E7970 (func_150BA55C only)
 *       +0x38  244908  D_8009FE48   0.08000000566 game_E7970 (func_150BA55C only)
 *       +0x3C  24490C  D_8009FE4C   0.1000000015 game_E7970  (func_150BA55C only)
 *       +0x40  244910  D_8009FE50   0.324000001  game_E7970  (func_150BA55C only)
 *       +0x44  244914  D_8009FE54  -0.5630000234 game_E7970  (func_150BA55C only)
 *       +0x48  244918  D_8009FE58   0.9448540211 game_E7970  (func_150BA55C only)
 *       +0x4C  24491C  (pad)        0            NO referrers anywhere
 *
 *     So it is ONE cut at 0x2448F0 producing TWO whole-block, sole-owned migrations:
 *         - [0x2448D0, rodata]   ->   - [0x2448D0, .rodata, game_E7380]
 *                                     - [0x2448F0, .rodata, game_E7970]
 *     The old note's second cut at 0x24491C is unnecessary -- 0x24491C is unreferenced pad,
 *     and D_8009FE5C..D_8009FE64 are NOT in this block at all (D_8009FE5C is that pad word;
 *     D_8009FE60 onward live in the NEXT block, [0x244920, rodata], which is untouched).
 *
 *     WHAT STILL GATES THE FLIP.  Both halves carry the constants of a function that is
 *     still a #pragma, so neither line can be applied yet:
 *       * 0x2448D0 -> game_E7380 needs func_150B9ED0 at 0 (currently 1014, see
 *         func_150B9ED0.c) AND needs func_150BA37C's -0.6f to land at exactly +0x1C, i.e.
 *         func_150B9ED0 must emit its seven literals in pool order first.  Definition order
 *         in the TU already puts func_150B9ED0 before func_150BA37C, so that works out.
 *       * 0x2448F0 -> game_E7970 needs THIS function at 0 (currently 1411).
 *       * Watch the trailing pad word on the game_E7970 half: 11 floats = 0x2C, and golden's
 *         half is 0x30.  Confirm the section-end alignment reproduces it before gating.
 *
 * (2) UNRESOLVED 8 BYTES OF FRAME.  Ours is 0x110, golden 0x108; every local slot is
 *     therefore 8 high and that is most of the remaining 1411.  The NAMED locals are
 *     accounted for: golden's local region 0x98..0x107 is 112 bytes and the 15 named
 *     locals below occupy exactly 100, leaving 12 bytes of compiler temp; we get 20.
 *     Tried and did NOT move it: dropping the second random to an inline call in the
 *     argument list; hoisting the `% 0x29` call out of func_1518A3C0's argument list into
 *     a named local (the documented 8-byte-hidden-temp lever).  Something else is buying
 *     an extra 8-byte temp.
 *
 * WHAT IS ALREADY RIGHT: the validity-check prologue and accumulator/`while (1.0f < t)`
 * skeleton (shared with game_E2880/func_150B54A8, which CLOSED), the func_1515C244 +
 * func_15143794 bone-offset idiom (matched sibling game_133190/func_15107A20), all thirteen
 * func_1518A3C0 arguments, the divisor hoisting (`% 0x7FU` hoists into $s6 WITH the
 * div-by-zero trap because it is loop-invariant, `% 0x29U` does not and so has no trap),
 * and the file-local func_150ADA20 return-type shadow (without it every random gets an
 * `andi 0xFF` at the save site).
 */

#include <ultra64.h>
/* include/functions.h declares func_150ADA20 as returning u8; the golden code saves its
 * result across further calls without zero-extending it, so the real return type is a word.
 * The shared header is left alone and the correct prototype is made file-local. */
#define func_150ADA20 func_150ADA20_u8_decl_in_functions_h
#include "functions.h"
#undef func_150ADA20
s32 func_150ADA20(void);
#include "variables.h"

extern f32 D_8009FE64;
void func_15143E94(s32 arg0, s32 arg1);
void func_15165F80(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);
void func_1514C678(f32 arg0, f32 arg1, s32 arg2, f32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, f32 arg9, s32 argA, s32 argB);


void func_150BA4C0(struct127 *arg0, u8 arg1, s32 arg2) {
    struct {
        struct127 *unk0;
        u8 unk4;
        f32 unk8;
    } sp3C;
    struct260 *temp_v0;

    sp3C.unk0 = arg0;
    sp3C.unk4 = arg0->unique_id;
    sp3C.unk8 = 0.0f;

    temp_v0 = func_15149130((func_150ADA20() % 9U) + 0xF, -1, 0x52, -1, 1, 0x3F, (struct37 *)0xC, arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy((void *)((s32)temp_v0 + 0x28), &sp3C, 0xC);
    }
}

extern f32 D_800BE9A4;

extern void func_1515C244(struct127 *, f32 *, f32 *, f32 *);
extern void func_15143794(s32, s32, f32, f32 *);
extern void func_1518A3C0(f32 *, f32 *, f32, f32 *, f32 *, f32, f32, s32, s32, s32, s32, u8, s32);

typedef struct {
    /* 0x00 */ struct127 *obj;
    /* 0x04 */ u8  id;
    /* 0x05 */ u8  pad5[3];
    /* 0x08 */ f32 unk8;
} Src150BA55C;

typedef struct {
    /* 0x00 */ u8  pad0;
    /* 0x01 */ u8  unk1;
    /* 0x02 */ u8  pad2[0xA];
    /* 0x0C */ u8  unkC;
    /* 0x0D */ u8  padD;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8  pad10[0x18];
    /* 0x28 */ Src150BA55C src;
} Emitter150BA55C;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec150BA55C;

void func_150BA55C(Emitter150BA55C *arg0) {
    Src150BA55C *src;
    struct127 *obj;
    s32 ang;
    Vec150BA55C spF0;
    f32 spEC;
    f32 spE8;
    Vec150BA55C spDC;
    f32 spD8;
    Vec150BA55C spCC;
    Vec150BA55C spC0;
    Vec150BA55C spB4;
    f32 spread;
    s32 r1;
    s32 r3;
    f32 rf1;
    f32 rf2;

    obj = arg0->src.obj;
    src = &arg0->src;
    if ((obj->interaction_state == 0) || (obj->unique_id != src->id)) {
        arg0->unkE = -1;
        return;
    }
    if (obj->unk1D4 == NULL) {
        return;
    }
    src->unk8 += (0.3143f + (func_150ADA68() * 0.58100003f)) * D_800BE9A4;
    if (1.0f < src->unk8) {
        spD8 = (obj->xz_scale + obj->y_scale) * 0.5f;
        func_1515C244(obj, &spF0.x, &spEC, &spE8);
        ang = (obj->unk76 >> 8) - 0x40;
        spDC.y = 0.0f;
        do {
            r1 = func_150ADA20();
            func_15143794((s16)(((r1 % 0x7FU) + ang) - 0x3F), (s16)((func_150ADA20() % 0x1FU) - 0x32), spEC, &spCC.x);
            spCC.y *= obj->unkF0;
            spCC.x += spF0.x;
            spCC.y += spF0.y;
            spCC.z += spF0.z;
            spC0.x = func_150ADA68() * 360.0f;
            spC0.y = func_150ADA68() * 360.0f;
            spC0.z = func_150ADA68() * 360.0f;
            spread = (func_150ADA68() * 0.094000004f) + 0.051000003f;
            spB4.x = (spCC.x - spF0.x) * spread;
            spB4.y = (spCC.y - spF0.y) * spread;
            spB4.z = (spCC.z - spF0.z) * spread;
            spDC.x = (func_150ADA68() * 18.645f) - 9.3225f;
            spDC.z = (func_150ADA68() * 18.645f) - 9.3225f;
            rf1 = func_150ADA68();
            rf2 = func_150ADA68();
            r3 = func_150ADA20();
            func_1518A3C0(&spCC.x, &spC0.x, ((rf1 * 0.080000006f) + 0.1f) * spD8, &spB4.x, &spDC.x,
                          (rf2 * 0.324f) - 0.563f, 0.944854f, 7,
                          (r3 % 0x29U) + 0x3C, 0, 0, arg0->unkC, arg0->unk1);
            src->unk8 -= 1.0f;
        } while (1.0f < src->unk8);
    }
}

void func_15149514(s32 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_150BA8F0(s32 arg0, s32 arg1, u8 arg2) {
    func_15149514(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}

extern f32 D_8009FE60;
void func_1504715C(s32 *arg0);
void func_15046C80(struct17 *arg0, s32 arg1, f32 arg2, s32 *arg3);

s32 func_150BA930(struct17 *arg0, struct127 *arg1, s32 *arg2, s32 arg3) {
    struct17 sp24;

    arg0->unk0 = arg1->x_position;
    if (D_8009FE60 < arg1->unk180) {
        arg0->unk4 = arg1->unk180;
    } else {
        arg0->unk4 = arg1->y_position;
    }
    arg0->unk8 = arg1->z_position;
    if (arg2 == 0) {
        return 1;
    }
    sp24.unk0 = arg0->unk0;
    sp24.unk4 = arg0->unk4 + 100.0f;
    sp24.unk8 = arg0->unk8;
    func_1504715C(arg2);
    func_15046C80(&sp24, 0, arg0->unk4 - 100.0f, arg2);
}

s32 func_150BAA00(s32 arg0, s32 arg1) {
    return 0x9;
}

void func_150BAA14(struct127 *arg0, s32 arg1, s32 arg2) {
    struct17 sp6C;
    s32 sp48[9];
    s32 sp44;
    u8 sp43;

    if (arg0->unk1D4 == 0) {
        return;
    }

    sp43 = func_150BA930(&sp6C, arg0, sp48, (u8)arg1);
    func_151D5404(&sp6C, 1307.0f, 2000.0f, 0.0005f, 0xC, 0xF, 0xFF, 0);
    func_15143E94(5, 0x4022);

    if (sp43 != 0) {
        sp44 = (s32)(D_800DBFF0[D_80082FA4].unk380 * D_8009FE64);
        func_15165F80(-1, (s32)sp6C.unk0, (s32)(sp6C.unk4 + 6.0f), (s32)sp6C.unk8,
                      0x19, 0x12, 0, 0xFF, 1);
        *((f32 *)&sp44 - 3) = func_150ADA68();
        func_1514C678(sp6C.unk0, sp6C.unk4, *(s32 *)&sp6C.unk8,
                      (*((f32 *)&sp44 - 3) * 50.0f) + 40.0f, sp44 + 0x3C, sp44 - 0x3C,
                      (func_150ADA20() % 11U) + 0x1E, 5, 0, 0.0f, 0, 0xFF);
    }
}
