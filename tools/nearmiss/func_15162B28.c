/*
 * PARKED NEAR-MISS -- func_15162B28  (game_18D770.c, 976 B, 250 instructions)
 *
 * BEST MEASURED SCORE: 10   (was 205 when this file was parked)
 * Measured with:  cd conker && python3 ../tools/asm-differ/diff.py -o func_15162B28 \
 *                     -R --max-lines 4096      -- and again WITHOUT -R; both give 10.
 * Frame size is already correct (56 bytes, == golden).  Instruction COUNT is already
 * correct: golden 250, mine 250, with ZERO inserts / deletes / reorders.
 *
 * ------------------------------------------------------------------ THE RESIDUAL
 * TWO rows, and they are the SAME row twice: the local `old` is allocated to $a2
 * where golden puts it in $v1.
 *
 *   golden                                mine
 *   lbu  v1,60(a0)      old = ...         lbu  a2,60(a0)
 *   beq  a1,v1,+0x374   old != cur        beq  a1,a2,+0x374
 *
 * Everything else now agrees, including the two allocations that were wrong when this
 * file was parked: `cur` is in $a1 (correct) and `cb` is in $v1 (correct).
 * Golden COALESCES `old` into $v1 -- the same register it later gives `cb`
 * (`lb v1,40(v0)` in the beql delay slot) -- because `old` is dead at the switch.
 * Mine declines that coalesce and takes a fresh $a2 instead.
 *
 * The duplicated-delay-slot knock-on described in the original park note is GONE:
 * it was a symptom of the register allocation, exactly as the cookbook predicts, and
 * it disappeared for free once `cur` landed in $a1.
 *
 * ------------------------------------------------------ WHAT ACTUALLY MOVED THE SCORE
 * Two levers, both plain C, both in the body below:
 *
 *  1. `f32 rise` declared INSIDE the `else if (p->unkC < p->unk14)` block instead of
 *     at the top of the function.            205 -> 45.  This is the single biggest
 *     lever on this function.  Scoping `fall` the same way is a NO-OP (see negatives),
 *     so this is not "block-scope floats" in general -- it is specifically `rise`.
 *  2. Seeding `cur` first and copying it into `old`
 *         cur = p->unk24;
 *         old = cur;
 *     instead of `old = p->unk24;`.          40 -> 15.
 *     Combined with the `old != cur` operand order:  15 -> 10.
 *
 * NOTE the operand order flips its sign as the seed changes -- it is not a fixed
 * preference.  With `old = p->unk24;` the better order is `cur != old` (40 vs 45);
 * with the staged `cur`/`old` seed the better order is `old != cur` (10 vs 15).
 * Re-measure it after ANY other change rather than assuming.
 *
 * ------------------------------------------------------------- MEASURED NEGATIVES
 * Every line below was built, compiled and scored with asm-differ (both with and
 * without -R, which always agreed).  Do not re-explore these by hand.
 *
 *   205  parked baseline: `rise` at top level, `old != cur`
 *   205  scope `fall` into its block but NOT `rise`      (isolates `rise` as the lever)
 *    45  scope `rise`, keep `old != cur`
 *    45  scope BOTH `rise` and `fall`, `old != cur`
 *    45  switch on p->unk24 instead of `cur`, on the 10-base
 *    40  scope `rise`, `cur != old`                      (the pre-staging plateau)
 *    40  ... + `cb` declared first
 *    40  ... + `cur` declared before `old`
 *    40  ... + switch on p->unk24 instead of `cur`
 *    40  ... + `cur = ...; if (...)` on one source line
 *    40  ... + every switch case on one source line
 *    40  ... + scope `fall` too
 *    40  ... + `1.f` instead of `1.0f`   (float-literal spelling lever: no effect here)
 *    40  ... + no `cur` local at all (test/switch straight off p->unk24)
 *    40  ... + declaration initialisers (`Sub15162B28 *p = &arg0->unk18;` etc.)
 *    40  ... + `p` initialised in its declaration only
 *    40  ... + `old` initialised from arg0->unk18.unk24
 *    40  ... + `old` declared s32
 *    43  ... + `old` and `cur` both s32 / both u32
 *    53  ... + `cur` declared s32   (and both-s32 on the 40 base)
 *    58  `p` declared first / `old` adjacent to `cb` / `old` declared last
 *   133  `fall` computed via a named intermediate, symmetric with `rise`
 *   395  staging through `cb` (`cb = p->unk24; old = cb;`) either operand order
 *  2398  drop the `p` local, spell every access as `arg0->unk18.<field>`
 *    15  staged `cur`/`old` + `cur != old`  (and: on one line / chained
 *         `old = cur = p->unk24;` / cases one-lined / curtest one-lined / `old` s32 /
 *         `old` u32 -- all exactly 15)
 *    18  staged + `cb` declared s32
 *    10  staged + `old != cur`   <-- THE BODY BELOW, and also: seed on one line,
 *         chained assignment, cases one-lined, curtest one-lined, `cb` declared first,
 *         `cur` declared first, `fall` scoped, declaration initialisers -- nine
 *         independent spellings, ALL exactly 10.
 *
 * ------------------------------------------------------------------ PERMUTER STATUS
 * conker/permuter_tu.sh selftest PASSES on game_18D770 (all five checks).  Note that
 * it used to FAIL check (b2) here; that was a harness bug (a `| head -5` SIGPIPE-killing
 * the round-trip compile on this warning-dense TU), fixed in permuter_tu.sh.  This TU is
 * a legitimate permuter target.
 *
 * The permuter was run in four stages (base 200 -> 40 -> 10), ~7,500 iterations total
 * with --stack-diffs and PERMUTER_TU_REQUIRE_FRAME=56.  It found lever 2 on its own.
 * From the 10-scoring base it ran 2,557 further iterations with NO improvement.
 * Its only sub-10 candidates were fakes and are NOT reproduced here:
 *   score 35  `cur = (new_var = p->unk24);`   -- new_var written, never read (dead local)
 *   score 33  `s8 *new_var = &p->unk26;` used for case 1 only -- an asymmetric forcer
 *
 * ------------------------------------------------------------------------- VERDICT
 * This is the cookbook's register-colouring wall in its purest form: 2 rows, 100%
 * register-only, 0 structural, and nine independent source spellings that leave the
 * score EXACTLY unchanged.  The remaining question is narrow and well posed --
 * "what makes IDO coalesce `old` into `cb`'s register instead of taking a fresh $a2?"
 * -- so this is worth one more attempt by someone with a new idea about IDO's
 * coalescing order, but it is NOT worth another undirected permuter run.
 */

#include <ultra64.h>
#include "functions.h"
#include "variables.h"

s32 func_151149AC(u32);
void func_1516441C(struct225 *arg0, struct227 *arg1);
void func_15187FC0(s32 arg0, s32 *arg1);
void func_15188010(s32 arg0, f32 *arg1);
void func_1511172C(s32 arg0);
void func_1515F170(s32 arg0, u8 arg1);

extern u8 D_800886F0[];
extern u8 D_800886F4[];
extern u8 D_800886F8[];
extern void (*D_8008B358[])(struct225 *, s32, u8);
extern void (*D_8008B37C[])(s32);

typedef struct {
    s32 unk0;
    u8 unk4;
} SubA15161F4C;

typedef struct {
    s32 unk0;
    union {
        s32 w4;
        u8 b4;
    } u4;
    u8 unk8;
    u8 unk9;
} ArgB15161F4C;

struct225 *func_151602C0(Header *header, Header2 *header2, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 arg6, u8 arg7, s32 offset, u8 arg9, s32 argA);
struct225 *func_1516037C(Header *src, struct226 *arg1, s32 size, u8 arg3, s32 arg4);
void func_151603FC(struct225 *arg0);
s32  func_15160600(struct225 *arg0);
s32  func_1516065C(struct225 *arg0);
s32  func_15160684(struct225 *arg0);
s32  func_151607A4(struct225 *arg0);
void func_15160954(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, struct225 *arg4);
s32  func_15161238(struct127 *arg0, struct127 *arg1);
struct225 *func_1516127C(s32 arg0, u8 arg1, s32 arg2);
struct225 *func_15161334(s32 arg0, u8 arg1, s32 arg2);
struct225 *func_15161408(s32 arg0, u8 arg1, s32 arg2);
struct225 *func_15161494(s32 arg0, u8 arg1, s32 arg2);
struct225 *func_15161540(s32 arg0, u8 arg1, s32 arg2);
struct225 *func_151615F8(s32 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5);
void func_151616D0(u8 arg0, u8 arg1, s32 arg2);
void func_15161714(struct225 *arg0);
void func_15161740(struct225 *arg0);
void func_1516176C(struct225 *arg0);
void func_15161798(struct225 *arg0);
void func_151617C4(struct225 *arg0);
void func_151617E4(struct225 *arg0);
void func_15161804(struct225 *arg0);
void func_15161860(struct225 *arg0);
void func_151618BC(u16 arg0, s16 arg1, u8 arg2, s32 arg3, struct17 *arg4, s16 arg5, s16 arg6);
struct225 *func_151619A0(s32 arg0, s16 arg1, u8 arg2, s32 arg3);
s32  func_15161A68(struct225 *arg0);
struct225 *func_15161E24(struct127 *arg0, u8 arg1, u8 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, u8 arg8, s32 arg9);
void func_15161F2C(struct225 *arg0);
struct225 *func_15162034(s32 arg0, u8 arg1, s32 arg2);
void func_15162110(s32 arg0);
struct225 *func_15162740(s32 arg0, u8 arg1, u8 arg2, u8 arg3, s16 arg4, s8 arg5, u8 arg6, s32 arg7);
struct225 *func_1516284C(Header *header, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5, u8 arg6, s32 size, u8 arg8, u8 arg9, s32 argA);
void func_15162EF8(struct239 *arg0);
void func_15162F50(struct239 *arg0);
struct225 *func_15162FAC(s32 arg0, u8 arg1, u8 arg2, u8 arg3, s16 arg4, s8 arg5, u8 arg6, s32 arg7);
struct225 *func_15163414(Header *header, f32* arg1, f32* arg2, f32* arg3, s8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB, s32 argC, u8 argD, s32 argE);
struct225 *func_15163604(s32 arg0, u8 arg1, u8 arg2, s16 arg3, u8 arg4, s32 arg5, u8 arg6, s32 arg7);
s32  func_15163704(struct225 *arg0);
void func_1516381C(s32 arg0, u8 arg1, u8 arg2, s32 arg3);
void func_1516387C(s32 arg0, u8 arg1, s8 arg2, s16 arg3, u8 arg4, s32 arg5, u8 arg6, s32 arg7);
s32  func_151639D0(struct225 *arg0, s32 arg1, u8 arg2);
void func_15163A18(struct225 *arg0, s32 arg1, u8 arg2);
struct225 *func_15163A60(u8 arg0, u8 arg1, s32 arg2);
s32  func_15163B98(struct230 *arg0);
struct225 *func_15163BE8(s32 arg0, u8 arg1, s32 arg2);
s32  func_15163CD0(struct225 *arg0);
void func_15163CF8(struct227 *arg0, struct225 *arg1);
void func_15163DEC(struct225 *arg0, struct228 *arg1);
s32  func_15163F50(struct225 *arg0, struct225 *arg1);
struct225 *func_15164208(s32 arg0, u8 arg1, u8 arg2, s32 arg3);
s32  func_1516429C(struct237 *arg0);
void func_151643A8(struct225 *arg0, s32 arg1, u8 arg2);
s32  func_151643F8(struct225 *arg0);
void func_151644F4(struct242 *arg0, struct17 *arg1, s32 arg2, f32 arg3, f32 arg4);
s32  func_151644A8(struct242 *arg0);

struct225 *func_151602C0(Header *header, Header2 *header2, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 arg6, u8 arg7, s32 offset, u8 arg9, s32 argA) {
    struct225 *ret;
    struct226 *sp30;

    ret = NULL;
    sp30 = func_1515D5F8(header2->unk0, header2->unk4, header2->unk8, arg2, arg3, arg4, arg5, arg6, arg7, 0);
    if (sp30 != 0) {
        ret = func_1516037C(header, sp30, offset, arg9, argA);
        if (ret != 0) {
            ret->unkE |= 2;
        } else {
            func_1515F10C(sp30);
        }
    }
    return ret;
}

struct225 *func_1516037C(Header *header, struct226 *arg1, s32 offset, u8 arg3, s32 arg4) {
    struct225 *ret = func_15167A68(53, arg4, offset + 24, 1, arg3, 1);
    if (ret == 0) {
        return NULL;
    }
    memcpy(&ret->unkE, header, 6);
    ret->unk14 = arg1;
    return ret;
}

void func_151603FC(struct225 *arg0) {
    s32 pad;
    u8 ret = 0;

    if ((arg0->unkE & 1) != 0) {
        arg0->unk10 -= D_800BE9E4;
        if (arg0->unk10 < 0) {
            ret = 1;
        }
    }
    if ((ret == 0) && (arg0->unkF != -1) && (D_8008B0F0[arg0->unkF]() == 0)) {
        ret = 1;
    }
    if (ret) {
        func_1516972C(arg0);
    }
}

// requires jump table
#pragma GLOBAL_ASM("asm/nonmatchings/game_18D770/func_151604A0.s")

s32 func_15160600(struct225 *arg0) {
    arg0->unk14->unk2F = func_151422DC(0, &D_800A6690, 0, 0xFF, 0xFF, &D_800A6698, 575);
    return 1;
}

s32 func_1516065C(struct225 *arg0) {
    func_15163CF8(&arg0->unk18, arg0);
    return 1;
}

s32 func_15160684(struct225 *arg0) {
    func_15163DEC(arg0, &arg0->unk18);
    return 1;
}

void func_150A7960(f32 *arg0, f32 arg1, s32 arg2, f32 arg3, f32 *arg4, f32 *arg5, f32 *arg6);

s32 func_151606A8(struct225 *arg0) {
    struct227 **p;
    union { f32 m[16]; f64 _a; } u;
    f32 sp3C;
    f32 sp38;
    f32 sp34;

    p = &arg0->unk18;
    func_150A8050((f32 (*)[4])&u.m[0], (*p)->unk0, (*p)->unk4, (*p)->unk8);

    u.m[12] = ((struct240 *)*p)->unk10;
    u.m[13] = ((struct240 *)*p)->unk12;
    u.m[14] = ((struct240 *)*p)->unk14;

    func_150A7960(&u.m[0], D_800A66B4[0], *(s32 *)&D_800A66B4[1], D_800A66B4[2], &sp34, &sp38, &sp3C);
    arg0->unk14->unkE = (s16)sp34;
    arg0->unk14->unk10 = (s16)sp38;
    arg0->unk14->unk12 = (s16)sp3C;
    return 1;
}

#pragma GLOBAL_ASM_DISABLED("asm/nonmatchings/game_18D770/func_151606A8.s")
// NON-MATCHING: something along these lines...
// void func_150A7960(s32, f32, f32, f32, f32*, f32*, f32*);
// s32 func_151606A8(struct225 *arg0) {
//     struct227 *temp_v0;
//     struct226 *temp_v0_2;
//
//     f32 tmp[16];
//
//     f32 sp3C;
//     f32 sp38;
//     f32 sp34;
//
//     temp_v0 = arg0->unk18;
//     func_150A8050(&tmp[1], temp_v0->unk0, temp_v0->unk4, temp_v0->unk8);
//
//     temp_v0_2 = arg0->unk18;
//     tmp[13] = temp_v0_2->unk10;
//     tmp[14] = temp_v0_2->unk12;
//     tmp[15] = temp_v0_2->unk14;
//
//     func_150A7960(&tmp, D_800A66B4[0], D_800A66B4[1], D_800A66B4[2], &sp34, &sp38, &sp3C);
//     arg0->unk14->unkE = sp34;
//     arg0->unk14->unk10 = sp38;
//     arg0->unk14->unk12 = sp3C;
//     return 1;
// }

s32 func_151607A4(struct225 *arg0) {
    struct227 *temp_a1 = &arg0->unk18;
    if (arg0->unk28 != 0) {
        if (temp_a1->unkC < 0.0f) {
            temp_a1->unk4 = (temp_a1->unk4 + (temp_a1->unk8 * D_800BE9A4));
            if (temp_a1->unk0 < temp_a1->unk4) {
                temp_a1->unk4 = temp_a1->unk0;
                temp_a1->unk10 -= 1;
                if (temp_a1->unk10 != 0) {
                    func_15160954(&temp_a1->unk4, &temp_a1->unk0, &temp_a1->unk8, &temp_a1->unkC, arg0);
                }
            }
        } else {
            temp_a1->unkC -= D_800BE9A4;
        }
    } else if (func_150ADA68() < D_800A6AD4) {
        temp_a1->unk10 = (func_150ADA20() % 5U) + 1;
        func_15160954(&temp_a1->unk4, &temp_a1->unk0, &temp_a1->unk8, &temp_a1->unkC, arg0);
    }
    arg0->unk14->unk2F = arg0->unk1C;
    return 1;
}

void func_15160954(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, struct225 *arg4) {
    s32 pad0;
    struct17 tmp;
    s32 pad1;

    *arg0 = 0.0f;
    *arg2 = *arg1 / ((func_150ADA68() * 12.0f) + 8.0f);
    *arg3 = (func_150ADA68() * 28.0f) + 1.0f;

    tmp.unk0 = arg4->unk14->unkE;
    tmp.unk4 = arg4->unk14->unk10;
    tmp.unk8 = arg4->unk14->unk12;

    if (arg4->unk2A != 0) {
        func_151618BC(25000, 0, 0, 0, &tmp, 500, 1500);
    }
}

struct vec3w_15160A58 { s32 unk0; s32 unk4; s32 unk8; };

struct225 *func_15160A58(struct127 *arg0, u8 arg1, struct vec3w_15160A58 *arg2, u8 arg3, s16 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, s8 argB, s32 argC, u8 argD, u8 argE, s32 argF) {
    struct225 *temp_v0;
    Header header;
    struct {
        struct127 *unk0;
        u8 unk4;
        u8 unk5;
        u8 pad6[0x2];
        struct vec3w_15160A58 unk8;
        s8 unk14;
        u8 unk15;
        u8 pad16[0x2];
    } sp44;
    Header2 header2;

    if (arg0 == NULL) {
        return NULL;
    }

    header.unk0 = arg3;
    header.unk1 = 5;
    header.unk2 = arg4;
    header.unk4 = 0x10;

    sp44.unk0 = arg0;
    sp44.unk4 = arg0->unique_id;
    sp44.unk5 = arg1;
    sp44.unk8 = *arg2;

    header2.unk0 = 0;
    header2.unk4 = 0;
    header2.unk8 = 0;

    sp44.unk14 = argB;
    sp44.unk15 = argD;

    temp_v0 = func_151602C0(&header, &header2, arg5, arg6, arg7, arg8, 0xFF, 0, argC + 0x18, argE, argF);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &sp44, 0x18);
    }
    return temp_v0;
}

#if 0
struct225 *func_15160A58(void *arg0, u8 arg1, void *arg2, u8 arg3, s16 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s8 argB, s32 argC, u8 argD, u8 argE, s32 argF) {
//     s32 sp64;
//
//     s8 sp60;
//     s16 sp5E;
//     s8 sp5D;
//     u8 sp5C;
//     u8 sp59;
//     s8 sp58;
//     ? sp4C;
//     u8 sp49;
//     u8 sp48;
//     void *sp44;
//
//     ?32 sp40;
//     ?32 sp3C;
//     ?32 sp38;
//     struct225 *temp_v0;
//     s32 result;
//
//     if (arg0 == 0) {
//         return NULL;
//     }
//     sp5C = arg3;
//     sp5D = 5;
//     sp60 = 0x10;
//     sp5E = arg4;
//     sp44 = arg0;
//     sp49 = arg1;
//     sp48 = arg0->unk3B;
//     sp4C.unk0 = (s32) arg2->unk0;
//     sp4C.unk4 = (s32) arg2->unk4;
//     sp4C.unk8 = (s32) arg2->unk8;
//     sp38 = 0;
//     sp3C = 0;
//     sp40 = 0;
//     sp58 = argB;
//     sp59 = argD;
//     temp_v0 = func_151602C0(&sp5C, &sp38, arg5, arg6, arg7, arg8, 0xFF, 0, argC + 0x18, argE, argF);
//     if (temp_v0 != NULL) {
//         memcpy(&temp_v0->unk18, &sp44, 0x18);
//     }
//     return temp_v0;
// }
#endif

// ??
#pragma GLOBAL_ASM("asm/nonmatchings/game_18D770/func_15160B74.s")

// another struct definition
struct225 *func_15160CDC(struct127 *arg0, u8 arg1, struct vec3w_15160A58 *arg2, struct vec3w_15160A58 *arg3, f32 arg4, u8 arg5, s16 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, u8 argB, u8 argC, u8 argD, u8 argE, s32 argF) {
    struct225 *temp_v0;
    Header header;
    struct {
        struct127 *unk0;
        u8 unk4;
        u8 unk5;
        u8 pad6[0x2];
        struct vec3w_15160A58 unk8;
        struct vec3w_15160A58 unk14;
        f32 unk20;
        u8 unk24;
        u8 unk25;
        u8 pad26[0x2];
    } sp4C;
    Header2 header2;
    s32 sp3C;
    s32 sp38;

    if (arg0 == NULL) {
        return NULL;
    }

    header.unk0 = arg5;
    header.unk1 = 6;
    header.unk2 = arg6;
    header.unk4 = 0x11;

    sp4C.unk0 = arg0;
    sp4C.unk4 = arg0->unique_id;
    sp4C.unk5 = arg1;
    sp4C.unk8 = *arg2;
    sp4C.unk14 = *arg3;
    sp4C.unk20 = arg4;

    sp3C = (argB != 0) ? 1 : 0;
    sp38 = (argD != 0) ? 2 : 0;
    sp4C.unk24 = sp38 | sp3C;
    sp4C.unk25 = argC;

    header2.unk0 = 0;
    header2.unk4 = 0;
    header2.unk8 = 0;

    temp_v0 = func_151602C0(&header, &header2, arg7, arg8, arg9, argA, 0xFF, 0, sizeof(sp4C), argE, argF);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &sp4C, sizeof(sp4C));
    }
    return temp_v0;
}

// similar to func_15160B74
#pragma GLOBAL_ASM("asm/nonmatchings/game_18D770/func_15160E30.s")

s32 func_15161238(struct127 *arg0, struct127 *arg1) {
    if (arg0->interaction_state == 0) {
        return 0;
    }
    if (arg0->id == 0xFF) {
        return 0;
    }
    if (arg0 == arg1) {
        return 0;
    }
    return 1;
}

struct225 *func_1516127C(s32 arg0, u8 arg1, s32 arg2) {
    struct225 *temp_v0;
    Header header;
    f32 src[4];

    src[0] = 50.0f;
    src[1] = 40.0f;
    src[2] = func_150ADA68() * D_800A6AD8;

    header.unk0 = 0;
    header.unk1 = 1;
    header.unk2 = 300;
    header.unk4 = 5;

    src[3] = D_800A6ADC;

    temp_v0 = func_1516037C(&header, arg0, sizeof(src), arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &src, sizeof(src));
    }
    return temp_v0;
}

struct225 *func_15161334(s32 arg0, u8 arg1, s32 arg2) {
    struct225 *temp_v0;
    Header header;
    f32 tmp1[8];

    tmp1[1] = 1.0f;
    tmp1[3] = 1.0f;

    header.unk0 = 0;
    header.unk1 = 2;
    header.unk2 = 300;
    header.unk4 = 6;

    tmp1[0] = 20.0f;
    tmp1[2] = 50.0f;
    tmp1[4] = 0.0f;
    tmp1[5] = 10.0f;
    tmp1[6] = D_800A6AE0;
    tmp1[7] = 127.0f;

    temp_v0 = func_1516037C(&header, arg0, sizeof(tmp1), arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &tmp1, sizeof(tmp1));
    }
    return temp_v0;
}

struct225 *func_15161408(s32 arg0, u8 arg1, s32 arg2) {
    struct225 *temp_v0;
    Header header;
    s32 tmp;

    tmp = func_151149AC(249); // what does this return?

    header.unk0 = 0;
    header.unk1 = 3;
    header.unk2 = 300;
    header.unk4 = 8;

    temp_v0 = func_1516037C(&header, arg0, sizeof(tmp), arg1, arg2);

    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &tmp, sizeof(tmp));
    }
    return temp_v0;
}

struct225 *func_15161494(s32 arg0, u8 arg1, s32 arg2) {
    struct225 *temp_v0;
    Header header;
    f32 tmp[4];

    header.unk0 = 0;
    header.unk1 = 1;
    header.unk2 = 300;
    header.unk4 = 5;

    tmp[0] = 127.0f;
    tmp[1] = 100.0f;
    tmp[2] = 0.0f;
    tmp[3] = D_800A6AE4;

    temp_v0 = func_1516037C(&header, arg0, sizeof(tmp), arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &tmp, sizeof(tmp));
    }
    return temp_v0;
}

struct225 *func_15161540(s32 arg0, u8 arg1, s32 arg2) {
    struct225 *temp_v0;
    Header header;
    f32 tmp[4];

    tmp[0] = 28.0f;
    tmp[1] = 27.0f;
    tmp[2] = func_150ADA68() * D_800A6AE8;
    tmp[3] = D_800A6AEC;

    header.unk0 = 0;
    header.unk1 = 1;
    header.unk2 = 300;
    header.unk4 = 5;

    temp_v0 = func_1516037C(&header, arg0, sizeof(tmp), arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &tmp, sizeof(tmp));
    }
    return temp_v0;
}

struct225 *func_151615F8(s32 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5) {
    struct225 *temp_v0;
    Header header;
    struct232 tmp1;
    f32 tmp;

    if (arg2 < 0) {
        return 0;
    }
    if (arg2 >= 9) {
        return 0;
    }

    tmp = D_800A66C0[arg2];
    tmp1.unk4 = tmp;
    tmp1.unk8 = 0.0f;
    tmp1.unkC = 0.0f;
    tmp1.unk0 = tmp;
    tmp1.unk10 = 0;
    tmp1.unk12 = arg1;

    header.unk0 = 0;
    header.unk1 = 4;
    header.unk2 = 300;
    header.unk4 = arg3;

    temp_v0 = func_1516037C(&header, arg0, sizeof(tmp1), arg4, arg5);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &tmp1, sizeof(tmp1));
    }
    return temp_v0;
}

void func_151616D0(u8 arg0, u8 arg1, s32 arg2) {
    struct234 tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg2;

    func_1516944C(53, &tmp, arg1);
}

void func_15161714(struct225 *arg0) {
    func_1514EDF0(arg0, arg0->unk18);
    func_151617C4(arg0);
}

void func_15161740(struct225 *arg0) {
    func_1514EDF0(arg0, arg0->unk18);
    func_151617E4(arg0);
}

void func_1516176C(struct225 *arg0) {
    func_1514EDF0(arg0, arg0->unk18);
    func_151617C4(arg0);
}

void func_15161798(struct225 *arg0) {
    func_1514EDF0(arg0, arg0->unk18);
    func_151617E4(arg0);
}

void func_151617C4(struct225 *arg0) {
    func_15169804(arg0);
}

void func_151617E4(struct225 *arg0) {
    func_15169824(arg0);
}

void func_15161804(struct225 *arg0) {
    if ((arg0->unkE & 2) != 0) {
        func_1515F10C(arg0->unk14, arg0);
    }
    D_8008B208[arg0->unk12](arg0);
}

void func_15161860(struct225 *arg0) {
    if ((arg0->unkE & 2) != 0) {
        func_1515F10C(arg0->unk14, arg0);
    }
    D_8008B2B0[arg0->unk12](arg0);
}

void func_151618BC(u16 arg0, s16 arg1, u8 arg2, s32 arg3, struct17 *arg4, s16 arg5, s16 arg6) {
    typedef struct {
        s32 unk0[10];
    } temp151618BC;
    temp151618BC sp38;

    sp38 = *(temp151618BC *)D_800A66E4;
    func_10010F88(sp38.unk0[func_150ADA20() % 10U], arg0, arg1, arg2, arg3, (s32)arg4->unk0, (s32)arg4->unk4, (s32)arg4->unk8, arg5, arg6);
}

struct225 *func_151619A0(s32 arg0, s16 arg1, u8 arg2, s32 arg3) {
    struct225 *temp_v0;
    Header header;
    s32 tmp;
    Header2 header2;

    tmp = arg0;

    header.unk0 = 3;
    header.unk1 = 9;
    header.unk2 = arg1;
    header.unk4 = 20;

    header2.unk0 = 0;
    header2.unk4 = 0;
    header2.unk8 = 0;

    temp_v0 = func_151602C0(&header, &header2, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0, sizeof(tmp), arg2, arg3);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &tmp, sizeof(tmp));
    }
    return temp_v0;
}

s32 func_15161A68(struct225 *arg0) {
    struct233 **tmp = &D_800C3958; // fakematch?

    if (D_800C35EA == 1) {
        f32 clamped;
        f32 capped;
        struct233 *temp_v0 = *tmp + (s32) arg0->unk18;

        arg0->unk14->unkE = temp_v0->unk0;
        arg0->unk14->unk10 = temp_v0->unk4;
        arg0->unk14->unk12 = temp_v0->unk8;

        if (temp_v0->unk24 < 0.0f) {
            clamped = 0.0f;
        } else {
            if (temp_v0->unk24 > 255.0f) {
                capped = 255.0f;
            } else {
                capped = temp_v0->unk24;
            }
            clamped = capped;
        }
        temp_v0->unk24 = clamped;
        arg0->unk14->unk5 = clamped;
        if (temp_v0->unk28 < 0.0f) {
            clamped = 0.0f;
        } else {
            if (temp_v0->unk28 > 255.0f) {
                capped = 255.0f;
            } else {
                capped = temp_v0->unk28;
            }
            clamped = capped;
        }
        temp_v0->unk28 = clamped;
        arg0->unk14->unk6 = clamped;
        if (temp_v0->unk2C < 0.0f) {
            clamped = 0.0f;
        } else {
            if (temp_v0->unk2C > 255.0f) {
                capped = 255.0f;
            } else {
                capped = temp_v0->unk2C;
            }
            clamped = capped;
        }
        temp_v0->unk2C = clamped;
        arg0->unk14->unk7 = clamped;

        if (temp_v0->unk18 < 0.0f) {
            clamped = 0.0f;
        } else {
            if (temp_v0->unk18 > 255.0f) {
                capped = 255.0f;
            } else {
                capped = temp_v0->unk18;
            }
            clamped = capped;
        }
        temp_v0->unk18 = clamped;
        arg0->unk14->unk2F = clamped;

    }
    return 1;
}

struct225 *func_15161E24(struct127 *arg0, u8 arg1, u8 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, u8 arg8, s32 arg9) {
    struct225 *temp_v0;
    Header header;
    struct244 tmp;
    Header2 header2;

    if (arg0 == NULL) {
        return 0;
    }

    header.unk0 = arg2;
    header.unk1 = 10;
    header.unk2 = arg3;
    header.unk4 = 21;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0->unique_id;
    tmp.unk5 = arg1;

    header2.unk0 = arg0->x_position;
    header2.unk4 = arg0->y_position;
    header2.unk8 = arg0->z_position;

    temp_v0 = func_151602C0(&header, &header2, arg4, arg5, arg6, arg7, 0xFF, 0, sizeof(tmp), arg8, arg9);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &tmp, sizeof(tmp));
    }
    return temp_v0;
}

void func_15161F2C(struct225 *arg0) {
    func_15163F50(arg0, &arg0->unk18);
}

void func_15161F4C(struct225 *arg0, s32 arg1, u8 arg2) {
    SubA15161F4C *ref = (SubA15161F4C *)((u8 *)arg0 + 0x18);
    ArgB15161F4C *msg = (ArgB15161F4C *)arg1;
    void (*fn)(struct225 *, s32, u8);

    if (arg2 == 0) {
        if ((msg->unk0 == ref->unk0) || (msg->u4.b4 == ref->unk4)) {
            struct225 *dying = arg0;

            func_1516972C(dying);
        }
    } else if (arg2 == 0x2D) {
        if (ref->unk0 == msg->unk0) {
            ref->unk0 = msg->u4.w4;
            ref->unk4 = msg->unk9;
        } else if (ref->unk0 == msg->u4.w4) {
            ref->unk0 = msg->unk0;
            ref->unk4 = msg->unk8;
        }
    }

    fn = D_8008B358[*(u8 *)((u8 *)arg0 + 0x1D)];
    if (fn != NULL) {
        fn(arg0, arg1, arg2);
    }
}

struct225 *func_15162034(s32 arg0, u8 arg1, s32 arg2) {
    struct225 *temp_v0;
    Header header;
    f32 src[8];

    header.unk0 = 0;
    header.unk1 = 2;
    header.unk2 = 0x12C;
    header.unk4 = 6;

    src[1] = 15.0f;
    src[0] = 22.0f;

    src[2] = 45.0f;
    src[3] = 1.0f;
    src[4] = 0.0f;
    src[5] = 10.0f;
    src[6] = D_800A6AF0;
    src[7] = 127.0f;

    temp_v0 = func_1516037C(&header, arg0, sizeof(src), arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &src, sizeof(src));
    }
    return temp_v0;
}

void func_15162110(s32 arg0) {
    struct236 *temp_v0;
    f32 src[8];

    src[1] = 15.0f;
    src[2] = 0.0f;
    src[4] = 15.0f;
    src[5] = 0.0f;
    src[6] = 0.0f;
    src[0] = 42.5f;
    src[3] = 37.5f;
    src[7] = D_800A6AF4;

    temp_v0 = func_15149130(300, -1, 30, -1, 0, 0, sizeof(src), 0xFF, 1);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk28, &src, sizeof(src));
    }
}

void func_151621B8(struct236 *arg0) {
    struct235 *temp_v0;
    f32 temp_f0;

    temp_v0 = &arg0->unk28;
    temp_f0 = sinf(temp_v0->unk18);

    func_1515D4D4(
        (u8)(temp_v0->unk0 + (temp_f0 * temp_v0->unkC)),
        (u8)(temp_v0->unk4 + (temp_f0 * temp_v0->unk10)),
        (u8)(temp_v0->unk8 + (temp_f0 * temp_v0->unk14)),
        0);
    temp_v0->unk18 += temp_v0->unk1C * D_800BE9A4;
    temp_v0->unk18 = func_15144B68(temp_v0->unk18);
}
// NON-MATCHING: not quite right here
// struct235 *func_151621B8(struct236 *arg0) {
//     struct235 *temp_v0;
//     f32 temp_f0;
//     u8 temp_a0;
//     u8 temp_a1;
//     u8 temp_a2;
//
//     temp_v0 = &arg0->unk28;
//     temp_f0 = sinf(temp_v0->unk18);
//
//     temp_a0 = temp_v0->unk0 + (temp_f0 * temp_v0->unkC);
//     temp_a1 = temp_v0->unk4 + (temp_f0 * temp_v0->unk10);
//     temp_a2 = temp_v0->unk8 + (temp_f0 * temp_v0->unk14);
//
//
//     func_1515D4D4(temp_a0, temp_a1, temp_a2, 0);
//     temp_v0->unk18 += temp_v0->unk1C * D_800BE9A4;
//     temp_v0->unk18 = func_15144B68(temp_v0->unk18);
//
//     return temp_v0;
// }

struct vec3w { s32 unk0; s32 unk4; s32 unk8; };

struct225 *func_151623F4(struct226 *arg0, u8 arg1, u8 arg2, u8 arg3, s8 arg4, s16 arg5, u8 arg6, s32 arg7) {
    struct {
        struct vec3w a;
        struct vec3w b;
        f32 c;
        f32 d;
    } sp30;
    Header header;
    struct225 *temp_v0;

    if (arg1 >= 3) {
        return NULL;
    }

    sp30.a = *(struct vec3w *)D_800A670C[arg1];
    sp30.b = *(struct vec3w *)D_800A6730[arg1];

    sp30.c = 0.0f;
    sp30.d = D_800A6754[arg1];
    header.unk0 = arg3;
    header.unk1 = arg4;
    header.unk2 = arg5;
    header.unk4 = arg2;

    temp_v0 = func_1516037C(&header, arg0, 0x20, arg6, arg7);
    if (temp_v0 != NULL) {
        memcpy((void *)((s32)temp_v0 + 0x18), &sp30, 0x20);
    }
    return temp_v0;
}
s32 func_15162510(void *arg0) {
    typedef struct {
        f32 unk0;
        f32 unk4;
        f32 unk8;
        f32 unkC;
        f32 unk10;
        f32 unk14;
        f32 unk18;
        f32 unk1C;
    } Struct15162510;
    register Struct15162510 *temp_v1;
    f32 temp_f0;

    temp_v1 = (Struct15162510 *)((s32)arg0 + 0x18);
    temp_f0 = sinf(*(f32 *)((s32)arg0 + 0x30));

    (*(struct226 **)((s32)arg0 + 0x14))->unk5 = temp_v1->unk0 + (temp_f0 * temp_v1->unkC);
    (*(struct226 **)((s32)arg0 + 0x14))->unk6 = temp_v1->unk4 + (temp_f0 * temp_v1->unk10);
    (*(struct226 **)((s32)arg0 + 0x14))->unk7 = temp_v1->unk8 + (temp_f0 * temp_v1->unk14);

    temp_v1->unk18 += temp_v1->unk1C * D_800BE9A4;
    temp_v1->unk18 = func_15144B68(temp_v1->unk18);
    return 1;
}
// s32 func_15162510(struct237 *arg0) {
//     struct235 *temp_v1;
//     f32 temp_f0;
//
//     temp_f0 = sinf(arg0->unk18.unk18);
//     temp_v1 = &arg0->unk18;
//
//     arg0->unk14->unk5 = temp_v1->unk0 + (temp_f0 * arg0->unk0[2]);
//     arg0->unk14->unk6 = temp_v1->unk4 + (temp_f0 * temp_v1->unk10);
//     arg0->unk14->unk7 = temp_v1->unk8 + (temp_f0 * temp_v1->unk14);
//
//     temp_v1->unk18 += temp_v1->unk1C * D_800BE9A4;
//     temp_v1->unk18 = func_15144B68(temp_v1->unk18);
//     return 1;
// }

struct225 *func_15162740(s32 arg0, u8 arg1, u8 arg2, u8 arg3, s16 arg4, s8 arg5, u8 arg6, s32 arg7) {
    struct225 *temp_v0;
    Header header;
    f32 src[8];

    if (arg1 >= 24) {
        return 0;
    }

    src[0] = D_800A67C0[arg1];
    src[1] = D_800A6760[arg1];
    src[2] = D_800A6820[arg1];
    src[3] = 1.0f;
    src[4] = 0.0f;
    src[5] = 10.0f;
    src[6] = D_800A6AF8;
    src[7] = 127.0f;

    header.unk0 = arg3;
    header.unk1 = arg5;
    header.unk2 = arg4;
    header.unk4 = arg2;

    temp_v0 = func_1516037C(&header, arg0, sizeof(src), arg6, arg7);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &src, sizeof(src));
    }
    return temp_v0;
}

struct225 *func_1516284C(Header *header, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5, u8 arg6, s32 offset, u8 arg8, u8 arg9, s32 argA) {
    struct225 *temp_v0;
    f32 src[8];

    if (arg8 >= 0x18) {
        return 0;
    }

    src[0] = D_800A67C0[arg8];
    src[1] = D_800A6760[arg8];
    src[2] = D_800A6820[arg8];
    src[3] = 1.0f;
    src[4] = 0.0f;
    src[5] = 10.0f;
    src[6] = D_800A6AFC;
    src[7] = 127.0f;
    temp_v0 = func_151602C0(header, arg1, 0, arg2, arg3, arg4, arg5, arg6, offset + sizeof(src), arg9, argA);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &src, sizeof(src));
    }
    return temp_v0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_18D770/func_1516295C.s")
// s32 func_1516295C(s32 arg0, u8 arg1, u8 arg2, u8 arg3, s16 arg4, s8 arg5, s8 arg6, s8 arg7, s8 arg8, s8 arg9, s32 argA, u8 argB, s32 argC) {
//     struct225 *temp_v0;
//     Header header;
//     struct238 src;
//
//     f32 temp_f0;
//     f32 temp_f12;
//     f32 temp_f16;
//     f32 temp_f18;
//     f32 temp_f2;
//     f32 temp_f8;
//
//     if (arg1 >= 5) {
//         return 0;
//     }
//
//     temp_f2 = D_800A6880[arg1];
//     temp_f12 = D_800A6894[arg1];
//     temp_f8 = D_800A68A8[arg1];
//     temp_f0 = D_800A68BC[arg1];
//     temp_f18 = D_800A68D0[arg1];
//     temp_f16 = D_800A68E4[arg1] ;
//
//     src.unk0 = temp_f2; // sp30
//     src.unk4 = temp_f12;
//     src.unk8 = temp_f2 - temp_f12;
//     src.unkC = temp_f8;
//     src.unk10 = temp_f0;
//     src.unk14 = temp_f18 + temp_f0;
//     src.unk18 = temp_f18 + temp_f0 + temp_f16;
//     src.unk1C = temp_f18 + temp_f0 + temp_f16 + temp_f18;
//
//     src.unk25 = arg6;
//     src.unk26 = arg7;
//     src.unk27 = arg8;
//     src.unk28 = arg9;
//
//     if (src.unkC < temp_f0) {
//         src.unk24 = 0;
//     } else if (src.unkC < src.unk14) {
//         src.unk24 = 1;
//     } else if (src.unkC < src.unk18) {
//         src.unk24 = 2;
//     } else if (src.unkC < src.unk1C) {
//         src.unk24 = 3;
//     } else {
//         src.unk24 = 4;
//     }
//
//     header.unk0 = arg3;
//     header.unk1 = arg5;
//     header.unk2 = arg4;
//     header.unk4 = arg2;
//
//     src.unk20 = 1.0f / temp_f18;
//
//     temp_v0 = func_1516037C(&header, arg0, argA + 0x30, argB, argC);
//     if (temp_v0 != NULL) {
//         memcpy(&temp_v0->unk18, &src, 0x30);
//     }
//     return temp_v0;
// }

// a biggun'
typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u8  unk24;
    /* 0x25 */ s8  unk25;
    /* 0x26 */ s8  unk26;
    /* 0x27 */ s8  unk27;
    /* 0x28 */ s8  unk28;
} Sub15162B28;

typedef struct {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ struct226 *unk14;
    /* 0x18 */ Sub15162B28 unk18;
} Struct15162B28;

extern void (*D_8008B364[])(void);

s32 func_15162B28(Struct15162B28 *arg0) {
    u8 old;
    Sub15162B28 *p;
    f32 fall;
    u8 cur;
    s8 cb;

    p = &arg0->unk18;
    cur = p->unk24;
    old = cur;
    if (p->unkC < p->unk10) {
        arg0->unk14->unk2F = p->unk4;
        p->unk24 = 0;
    } else if (p->unkC < p->unk14) {
        f32 rise;

        rise = (p->unkC - p->unk10) * p->unk20;
        arg0->unk14->unk2F = p->unk4 + p->unk8 * rise;
        p->unk24 = 1;
    } else if (p->unkC < p->unk18) {
        arg0->unk14->unk2F = p->unk0;
        p->unk24 = 2;
    } else {
        fall = 1.0f - (p->unkC - p->unk18) * p->unk20;
        arg0->unk14->unk2F = p->unk4 + p->unk8 * fall;
        p->unk24 = 3;
    }
    cur = p->unk24;
    if (old != cur) {
        switch (cur) {
        case 0:
            cb = p->unk25;
            break;
        case 1:
            cb = p->unk26;
            break;
        case 2:
            cb = p->unk27;
            break;
        case 3:
            cb = p->unk28;
            break;
        default:
            cb = -1;
            break;
        }
        if (cb != -1) {
            D_8008B364[cb]();
        }
    }
    p->unkC += D_800BE9A4;
    while (p->unkC > p->unk1C) {
        p->unkC -= p->unk1C;
    }
    return 1;
}

void func_15162EF8(struct239 *arg0) {
    s8 sp1C[9]; // FIXME: what size should this be?
    struct240 *temp_v0;

    temp_v0 = func_151149AC(arg0->unk48);
    if (temp_v0 != NULL) {
        temp_v0->unk7C |= 1;
    }
    sp1C[0] = arg0->unk12 - 21;
    func_151403A8(&sp1C, 36);
}

void func_15162F50(struct239 *arg0) {
    s8 sp1C[9]; // FIXME: what size should this be?
    struct240 *temp_v0;

    temp_v0 = func_151149AC(arg0->unk48);
    if (temp_v0 != NULL) {
        temp_v0->unk7C &= ~1;
    }
    sp1C[0] = arg0->unk12 - 21;
    func_151403A8(&sp1C, 37);
}

struct225 *func_15162FAC(s32 arg0, u8 arg1, u8 arg2, u8 arg3, s16 arg4, s8 arg5, u8 arg6, s32 arg7) {
    struct225 *temp_v0;
    Header header;
    struct241 src;

    if (arg1 >= 3) {
        return NULL;
    }

    src.unk0 = 0.0f;
    src.unk4 = D_800A68F8[arg1];
    src.unk8 = 0.0f;
    src.unk14 = 0;
    src.unk20 = 0.0f;
    src.unkC = D_800A6904[arg1];
    src.unk10 = D_800A6910[arg1];
    src.unk24 = D_800A6934[arg1];
    src.unk28 = D_800A6940[arg1];
    src.unk2C = D_800A694C[arg1];
    src.unk18 = D_800A691C[arg1];
    src.unk1C = D_800A6928[arg1];
    src.unk30 = D_800A6958[arg1];

    header.unk0 = arg3;
    header.unk1 = arg5;
    header.unk2 = arg4;
    header.unk4 = arg2;

    temp_v0 = func_1516037C(&header, arg0, sizeof(src), arg6, arg7);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &src, sizeof(src));
    }
    return temp_v0;
}

// big one
#pragma GLOBAL_ASM("asm/nonmatchings/game_18D770/func_151630F4.s")

struct225 *func_15163414(Header *header, f32* arg1, f32* arg2, f32* arg3, s8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB, s32 argC, u8 argD, s32 argE) {
    struct225 *temp_v0;
    struct245 data;
    Header2 header2;

    data.unk0 = arg1;
    data.unk4 = arg2;
    data.unk8 = arg3;
    data.unkC = arg4;
    data.unkD = arg5;

    header2.unk0 = *arg1;
    header2.unk4 = *arg2;
    header2.unk8 = *arg3;

    temp_v0 = func_151602C0(header, &header2, arg6, arg7, arg8, arg9, argA, argB, argC + sizeof(data), argD, argE);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &data, sizeof(data));
    }
    return temp_v0;
}

s32 func_15163504(struct225 *arg0) {
    struct245 *data;
    s32 ret;

    data = (struct245 *)&arg0->unk18;
    ret = 1;
    arg0->unk14->unkE = *(f32 *)data->unk0;
    arg0->unk14->unk10 = *(f32 *)data->unk4;
    arg0->unk14->unk12 = *(f32 *)data->unk8;
    if (data->unkC != -1) {
        return D_8008B36C[data->unkC]();
    }
    return ret;
}

void func_151635A8(struct225 *arg0, s32 arg1, u8 arg2) {
    void (**handlers)(struct225 *, s32, u8);
    struct245 *data;

    handlers = (void (**)(struct225 *, s32, u8))D_8008B370;
    data = (struct245 *)&arg0->unk18;
    if (handlers[data->unkD] != NULL) {
        handlers[data->unkD](arg0, arg1, arg2);
    }
}

struct225 *func_15163604(s32 arg0, u8 arg1, u8 arg2, s16 arg3, u8 arg4, s32 arg5, u8 arg6, s32 arg7) {
    struct225 *temp_v0;
    Header header;
    f32 src[4];

    if (arg1 < 0) {
        return 0;
    }
    if (arg1 >= 14) {
        return 0;
    }

    src[0] = D_800A6964[arg1];
    src[1] = D_800A699C[arg1];
    src[2] = func_150ADA68() * D_800A6B00;
    src[3] = D_800A69D4[arg1];

    header.unk0 = arg4;
    header.unk1 = 1;
    header.unk2 = arg3;
    header.unk4 = arg2;

    temp_v0 = func_1516037C(&header, arg0, sizeof(src), arg6, arg7);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &src, sizeof(src));
    }
    return temp_v0;
}

s32 func_15163704(struct225 *arg0) {
    struct227 *temp_v0;
    f32 tmp;
    s32 pad1;

    temp_v0 = &arg0->unk18;
    tmp = sinf(temp_v0->unk8);
    arg0->unk14->unk2F = temp_v0->unk0 + (temp_v0->unk4 * tmp);

    temp_v0->unk8 += temp_v0->unkC * D_800BE9A4;
    temp_v0->unk8 = func_15144B68(temp_v0->unk8);

    if (temp_v0->unk8 > D_800A6B04) {
        return 0;
    }
    return 1;
}

void func_1516381C(s32 arg0, u8 arg1, u8 arg2, s32 arg3) {
    Header tmp;
    tmp.unk0 = 0;
    tmp.unk1 = -1;
    tmp.unk2 = 300;
    tmp.unk4 = arg1;
    func_1516037C(&tmp, arg0, 0, arg2, arg3);
}

void func_1516387C(s32 arg0, u8 arg1, s8 arg2, s16 arg3, u8 arg4, s32 offset, u8 arg6, s32 arg7) {
    Header tmp;
    tmp.unk0 = arg1;
    tmp.unk1 = arg2;
    tmp.unk2 = arg3;
    tmp.unk4 = arg4;

    func_1516037C(&tmp, arg0, offset, arg6, arg7);
}

s32 func_151638E0(struct225 *arg0) {
    struct227 *temp_v1;
    s32 sp20[3];
    f32 sp1C;

    temp_v1 = &arg0->unk18;
    func_15187FC0(*(s32 *)temp_v1, sp20);
    func_15188010(*(s32 *)temp_v1, &sp1C);
    arg0->unk14->unk2F = temp_v1->unk4 + (temp_v1->unk8 * sp1C);
    return 1;
}
// NON-MATCHING: struct isnt quite right..
// s32 func_151638E0(struct225 *arg0) {
//     struct227 *temp_v1;
//     f32 sp20[3];
//     f32 sp1C;
//
//     temp_v1 = &arg0->unk18;
//     func_15187FC0(arg0->unk18, &sp20); // missing a lw here
//     func_15188010(temp_v1, &sp1C);
//     arg0->unk14->unk2F = (temp_v1->unk4 + (temp_v1->unk8 * sp1C));
//     return 1;
// }

s32 func_151639D0(struct225 *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 0x27) {
        arg0->unk14->unk9 = 1;
    } else if (arg2 == 0x28) {
        arg0->unk14->unk9 = 0;
    }
}

void func_15163A18(struct225 *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 0x27) {
        arg0->unk14->unk9 = 0;
    } else if (arg2 == 0x28) {
        arg0->unk14->unk9 = 1;
    }
}

struct225 *func_15163A60(u8 arg0, u8 arg1, s32 arg2) {
    struct225 *temp_v0_2;
    Header header;
    f32 tmp1[4];
    struct226 *temp_v0;
    Header2 header2;

    temp_v0 = func_151149AC(arg0); // maybe different types?
    if (temp_v0 == 0) {
        return 0;
    }
    tmp1[0] = D_800A6964[6]; // D_800A697C
    tmp1[1] = D_800A699C[6]; // D_800A69B4
    tmp1[2] = func_150ADA68() * D_800A6B08;
    tmp1[3] = D_800A69D4[6]; // D_800A69EC;

    header2.unk0 = temp_v0->unk10;
    header2.unk4 = temp_v0->unk12;
    header2.unk8 = temp_v0->unk14;

    header.unk0 = 2;
    header.unk1 = 17;
    header.unk2 = 300;
    header.unk4 = 5;

    temp_v0_2 = func_151602C0(&header, &header2, D_800A6964[6], 0, 0xFF, 0, 0xFF, 0, 20, arg1, arg2);
    if (temp_v0_2 != 0) {
        memcpy(&temp_v0_2->unk18, &tmp1, 16);
        memcpy(&temp_v0_2->unk28, &temp_v0, 4);
    }
    return temp_v0_2;
}

s32 func_15163B98(struct230 *arg0) {
    struct228* tmp;
    if (func_1516065C(arg0) == 0) {
        return 0;
    } else {
        tmp = arg0->unk28;
        if (tmp->unk6E == 1) {
            return 0;
        } else {
            return 1;
        }
    }
}

struct225 *func_15163BE8(s32 arg0, u8 arg1, s32 arg2) {
    struct225 *temp_v0;
    f32 src[4];

    src[0] = D_800A6964[6];
    src[1] = D_800A699C[6];
    src[2] = func_150ADA68() * D_800A6B0C;
    src[3] = D_800A69D4[6];

    temp_v0 = func_15160A58(arg0, 1, &D_800A6A0C, 2, 300, 100, 0, 0xFF, 0, 0xFF, 0, 0, sizeof(src), 1, arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk30, &src, sizeof(src));
    }
    return temp_v0;
}

s32 func_15163CD0(struct225 *arg0) {
    func_15163CF8(&arg0->unk30, arg0);
    return 1;
}

void func_15163CF8(struct227 *arg0, struct225 *arg1) {
    f32 tmp = sinf(arg0->unk8);
    arg1->unk14->unk2F = arg0->unk0 + (arg0->unk4 * tmp);
    arg0->unk8 = arg0->unk8 + (arg0->unkC * D_800BE9A4);
    arg0->unk8 = func_15144B68(arg0->unk8);
}

void func_15163DEC(struct225 *arg0, struct228 *arg1) {
    arg1->unk10 = arg1->unk10 - D_800BE9A4;
    if (arg1->unk10 < 0.0f) {
        arg1->unk10 = func_150ADA68() * arg1->unk14;
        if ((func_150ADA20() & 3) != 0) {
            arg1->unkC = (func_150ADA68() * (arg1->unk0 - arg1->unk4)) + arg1->unk4;
        } else {
            arg1->unkC = (func_150ADA68() * (arg1->unk8 - arg1->unk0)) + arg1->unk0;
        }
    }
    arg1->unk1C += (arg1->unkC - arg1->unk1C) * arg1->unk18;
    arg0->unk14->unk2F = arg1->unk1C;
}

s32 func_15163F50(struct225 *arg0, struct225 *arg1) {
    struct127 *temp_v1;

    temp_v1 = arg1->unk0;
    if (temp_v1->interaction_state == 0) {
        return 0;
    }
    if (temp_v1->id == 0xFF) {
        return 0;
    }
    if (temp_v1->unique_id != arg1->unk4) {
        return 0;
    }
    arg0->unk14->unkE = temp_v1->x_position;
    arg0->unk14->unk10 = temp_v1->y_position;
    arg0->unk14->unk12 = temp_v1->z_position;
    return 1;
}

typedef struct {
    s32 field_0x0;
    union {
        s32 w;
        u8 b;
    } field_0x4;
    u8 field_0x8;
    u8 field_0x9;
} ActorRefMessage;

typedef struct {
    s32 field_0x0;
    u8 field_0x4;
} ActorRefPayload;

typedef struct {
    u8 pad_0[0x18];
    ActorRefPayload field_0x18;
} ActorRefObject;

void func_15163FEC(struct225 *arg0, ActorRefMessage *arg1, u8 arg2) {
    ActorRefPayload *payload;
    s32 owner;

    payload = (ActorRefPayload *)((u8 *)arg0 + 0x18);
    if (arg2 == 0) {
        owner = arg1->field_0x0;
        if ((owner == payload->field_0x0) || (arg1->field_0x4.b == payload->field_0x4)) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x2D) {
        if (payload->field_0x0 == arg1->field_0x0) {
            payload->field_0x0 = arg1->field_0x4.w;
            payload->field_0x4 = arg1->field_0x9;
        } else if (payload->field_0x0 == arg1->field_0x4.w) {
            ActorRefMessage *swap = arg1;

            payload->field_0x0 = swap->field_0x0;
            payload->field_0x4 = swap->field_0x8;
        }
    } else if (D_8008B374[arg0->unk2D] != NULL) {
        D_8008B374[arg0->unk2D]((s32)arg0);
    }
}
void func_151640C0(ActorRefObject *arg0, ActorRefMessage *arg1, u8 arg2) {
    ActorRefObject **sp18;
    ActorRefMessage **sp1C;
    s32 temp_v1;
    s32 temp_v0;
    s32 temp_a0;
    s32 temp_a1;
    u8 temp_a3;
    u8 temp_a2;
    sp18 = &arg0;
    sp1C = &arg1;
    if (arg2 == 0x29) {
        temp_v1 = (*sp1C)->field_0x4.w;
        temp_v0 = (s32)*sp18;
        temp_a0 = ((ActorRefPayload *)temp_v1)->field_0x0;
        temp_a1 = ((ActorRefObject *)temp_v0)->field_0x18.field_0x0;
        temp_v0 += 0x18;
        temp_a2 = ((ActorRefPayload *)temp_v0)->field_0x4;
        temp_a3 = ((ActorRefPayload *)temp_v1)->field_0x4;
        if ((temp_a1 == temp_a0) || (temp_a2 == temp_a3) || (((struct127 *)temp_a1)->unique_id == temp_a3)) {
            func_1516972C((struct225 *)*sp18);
        }
    }
}

void func_15164134(struct225 *arg0, ActorRefMessage *arg1, u8 arg2) {
    ActorRefPayload *payload;
    s32 owner;

    payload = (ActorRefPayload *)((u8 *)arg0 + 0x18);
    if (arg2 == 0) {
        owner = arg1->field_0x0;
        if ((owner == payload->field_0x0) || (arg1->field_0x4.b == payload->field_0x4)) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x2D) {
        if (payload->field_0x0 == arg1->field_0x0) {
            payload->field_0x0 = arg1->field_0x4.w;
            payload->field_0x4 = arg1->field_0x9;
        } else if (payload->field_0x0 == arg1->field_0x4.w) {
            ActorRefMessage *swap = arg1;

            payload->field_0x0 = swap->field_0x0;
            payload->field_0x4 = swap->field_0x8;
        }
    } else if (D_8008B37C[*(u8 *)((s32)arg0 + 0x3D)] != NULL) {
        D_8008B37C[*(u8 *)((s32)arg0 + 0x3D)]((s32)arg0);
    }
}

struct225 *func_15164208(s32 arg0, u8 arg1, u8 arg2, s32 arg3) {
    struct225 *temp_v0;
    Header header;
    struct243 src;

    src.unk0 = 0.0f;
    src.unk4 = arg1;

    header.unk0 = 0;
    header.unk1 = 20;
    header.unk2 = 300;
    header.unk4 = 39;

    temp_v0 = func_1516037C(&header, arg0, sizeof(src), arg2, arg3);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &src, sizeof(src));
    }
    return temp_v0;
}

s32 func_1516429C(struct237 *arg0) {
    arg0->unk14->unk2F = arg0->unk18.unk0;
    arg0->unk18.unk0 = arg0->unk18.unk0 - (arg0->unk18.unk0 * D_800A6B10);
    return 1;
}

void func_1516434C(struct225 *arg0, struct227 *arg1, u8 arg2) {
    struct227 *temp = &arg0->unk18;

    if (arg2 == 0x33) {
        if (*(u8 *)((u8 *)arg1 + 4) == *(u8 *)((u8 *)temp + 4)) {
            temp->unk0 = arg1->unk0;
            arg0->unk14->unk5 = *(u8 *)((u8 *)arg1 + 5);
            arg0->unk14->unk6 = *(u8 *)((u8 *)arg1 + 6);
            arg0->unk14->unk7 = *(u8 *)((u8 *)arg1 + 7);
        }
    }
}

void func_151643A8(struct225 *arg0, s32 arg1, u8 arg2) {
    struct227 *tmp;
    tmp = &arg0->unk18;
    if (arg2 == 64) {
        tmp->unk24 |= 1;      // force odd?
    } else if (arg2 == 65) {
        tmp->unk24 &= 0xFFFE; // force even?
    }
}

s32 func_151643F8(struct225 *arg0) {
    func_1516441C(arg0, &arg0->unk18);
    return 1;
}

void func_15145CD0(s32 arg0, struct227 **arg1, f32 **arg2, s32 arg3);

void func_1516441C(struct225 *arg0, struct227 *arg1) {
    struct227 *parg1;
    f32 *pout;
    f32 out[3];

    parg1 = arg1;
    pout = &out[0];
    func_15145CD0(*(s32 *)&arg1->unkC, &parg1, &pout, 1);
    arg0->unk14->unkE = (s32)out[0];
    arg0->unk14->unk10 = (s32)out[1];
    arg0->unk14->unk12 = (s32)out[2];
}

s32 func_151644A8(struct242 *arg0) {
    f32 temp_f0;
    struct17 *temp_v0;

    temp_v0 = arg0->unk20;
    temp_f0 = arg0->unk1C;
    func_151644F4(arg0, &arg0->unk24, arg0->unk18, temp_v0->unk0 * temp_f0, temp_v0->unk8 * temp_f0);
    return 1;
}

void func_150A7960(f32 *arg0, f32 arg1, s32 arg2, f32 arg3, f32 *arg4, f32 *arg5, f32 *arg6);

void func_151644F4(struct242 *arg0, struct17 *arg1, s32 arg2, f32 arg3, f32 arg4) {
    f32 tmp3;
    f32 tmp2;
    f32 tmp1;
    f32 tmp[16];

    func_150A8050((f32 (*)[4])&tmp, arg3, 0.0f, arg4);
    tmp[12] = arg1->unk0;
    tmp[13] = arg1->unk4;
    tmp[14] = arg1->unk8;
    func_150A7960(&tmp[0], 0.0f, arg2, 0.0f, &tmp1, &tmp2, &tmp3);
    arg0->unk14->unkE = (s16)tmp1;
    arg0->unk14->unk10 = (s16)tmp2;
    arg0->unk14->unk12 = (s16)tmp3;
}

// NON-MATCHING: close...
// void func_151644F4(struct242 *arg0, struct17 *arg1, s32 arg2, f32 arg3, f32 arg4) {
//     f32 tmp1;
//     f32 tmp2;
//     f32 tmp3;
//
//     f32 tmp[16];
//
//     func_150A8050(&tmp, arg3, 0.0f, arg4);
//
//     tmp[13] = arg1->unk0;
//     tmp[14] = arg1->unk4;
//     tmp[15] = arg1->unk8;
//     func_150A7960(&tmp, NULL, arg0, NULL, &tmp1, &tmp2, &tmp3);
//
//     arg0->unk14->unkE =  tmp1;
//     arg0->unk14->unk10 = tmp2;
//     arg0->unk14->unk12 = tmp3;
// }

void func_151645C4(u8 arg0) {
    D_800DCDD0 = arg0;
    if (arg0 != 0) {
        switch (D_800BE9F0) {
        case 0xB:
            func_1511172C(4);
            break;
        case 6:
            func_1515F170(10, 1);
            func_1511172C(4);
        case 0x39:
            ((u8 *)&D_800DCD20)[0] = D_800886F0[0];
            ((u8 *)&D_800DCD20)[1] = D_800886F0[1];
            ((u8 *)&D_800DCD20)[2] = D_800886F0[2];
            D_800B0DF0->unk5 = D_800886F4[0];
            D_800B0DF0->unk6 = D_800886F4[1];
            D_800B0DF0->unk7 = D_800886F4[2];
            break;
        case 7:
        case 0xC:
            break;
        }
    } else {
        switch (D_800BE9F0) {
        case 6:
            func_1515F170(10, 0);
        case 7:
        case 0xC:
        case 0x39:
            func_1511172C(6);
            ((u8 *)&D_800DCD20)[0] = D_800886F8[0];
            ((u8 *)&D_800DCD20)[1] = D_800886F8[1];
            ((u8 *)&D_800DCD20)[2] = D_800886F8[2];
            D_800B0DF0->unk5 = 0xFF;
            D_800B0DF0->unk6 = 0xFF;
            D_800B0DF0->unk7 = 0xFF;
            break;
        case 0xB:
            func_1511172C(6);
            break;
        case 0x29:
            func_1511172C(1);
            break;
        }
    }
}
