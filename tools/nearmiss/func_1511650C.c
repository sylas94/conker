/* ============================================================================
 * func_1511650C   (game_142560.c, 223 instructions / 0x378 bytes)
 *
 * STATUS: NEAR MISS, score 405, and 405 is ENTIRELY ACCOUNTED FOR:
 *             61 register-name differences  x 5 = 305
 *              1 missing `nop`              x 100 = 100
 *         Every other instruction, in every basic block, matches golden
 *         one-for-one in the same order. There is no structural difference
 *         left: no branch sense, no schedule, no operand order, no frame.
 *         Frame is 0x38 and correct on BUILD #1.
 *
 * MEASURE IT WITH --max-lines 223, NOT 245.  The symbol is 0x1511650C..
 * 0x15116884 = 223 instructions = 892 bytes; --max-lines 245 opens a 980-byte
 * window that runs into func_15116888 and CONTAMINATES the score. That trap
 * bit hard here -- see "THE SCORE LIED" below.
 *
 *   cd conker && python3 ../tools/asm-differ/diff.py -o func_1511650C -R --max-lines 223
 *
 * ---------------------------------------------------------------------------
 * SETTLED (do not re-derive)
 * ---------------------------------------------------------------------------
 * Signature comes free from two ALREADY-MATCHED callers (game_EB340.c:57,
 * game_F4D20.c:12/14):  func_1511650C(struct131 *, s32, s32, f32)
 *   arg1 = flag word (bit 0), arg2 = sfx id, arg3 = distance (500/1000/400f).
 * arg3 is an f32 in an INTEGER register (4th arg): `sw a3,0x44(sp)` then
 * `lwc1 $f6,0x44(sp)`.
 *
 * RODATA PRE-FILTER: PASSED, nothing blocked. All six constants live in
 * asm/data/247A30.rodata.s, an EXTERNAL already-split rodata file, so the
 * `extern` escape applies (the TU already does this for D_800A2F8C etc.):
 *     D_800A2FB8  .double -0.0032       -> extern f64   (ldc1)
 *     D_800A2FC0  0.1f      3DCCCCCD    -> extern f32   low16 != 0
 *     D_800A2FC4  12767.0f  46477C00    -> extern f32   low16 != 0
 *     D_800A2FC8  20000.0f  469C4000    -> extern f32   low16 != 0
 *     D_800A2FCC  0.01f     3C23D70A    -> extern f32   low16 != 0
 *     D_800A2FD0  0.01f     3C23D70A    -> extern f32   SAME VALUE, DISTINCT
 *                                          SYMBOL -- must be spelled by name,
 *                                          a literal 0.01f would fold the two.
 *   Inlined (low16 == 0, lui+mtc1): 1.0f (0x3F800000), 500.0f (0x43FA0000),
 *   and 0x4F000000 from the (u32) conversion helper.
 *
 * ACTOR INDEXING: there is NO index here. D_800CC2D0 is passed WHOLE as the
 * 4th argument of func_15116888 (`lui a3 / addiu a3 %lo(D_800CC2D0)`), which
 * is why there is no multu, no div and no ladder. The `addiu a2,s0,0x7c` and
 * the D_800CC2D0 address are both hoisted ABOVE the `bnez` guarding the call
 * (delay-slot fill from the target, dest dead on fall-through) -- that is
 * automatic, do not try to force it.
 *
 * FILE-LOCAL RETYPE (verified safe): functions.h declares func_10010F88 void;
 * it returns the sfx handle (`sh v0,0x74(s0)`). Shadowed file-locally.
 * func_10010F88 / func_1000F91C / func_100111C8 appear NOWHERE ELSE in
 * game_142560.c, so no already-matched function in the TU is affected.
 *
 * SCORE LADDER (all at --max-lines 223 unless noted)
 *   665 (ml=245)  draft 1 -- frame, every branch and the whole schedule already
 *                 correct; only register names + the nop wrong.
 *   405           STATEMENT-SPLIT LAW: golden does `lh v0,0x3c(s0)` then
 *                 `addu v0,v0,a0` -- the add writes into the register that
 *                 already held one operand. `n = arg0->unk3C.h + amount;`
 *                 emits `lh t0` + `addu v0,t0,a0` and burns a t-register,
 *                 which rotated EVERY later temp by +1. Splitting into
 *                 `n = arg0->unk3C.h; n += amount;` fixed the whole middle
 *                 rotation at once. Worth 260.
 *
 * ---------------------------------------------------------------------------
 * THE SCORE LIED -- READ THIS BEFORE "IMPROVING" ON 405
 * ---------------------------------------------------------------------------
 * Splitting the clamped ratio and the final volume into TWO f32 locals scores
 * 70 (ml=223) versus 405. IT IS WORSE. With two variables IDO SINKS
 * `vol = ratio * arg3 - 500.0f` into BOTH arms of the `arg0->unk74` test,
 * duplicating `lwc1 arg3 / mul.s / mtc1 500.0f / sub.s` and adding ~10
 * instructions golden does not have; asm-differ then re-aligns and reports a
 * small number. Golden computes it ONCE before `bnez a0` (`sub.s $f12,$f8,$f10`
 * in the branch delay slot) and REUSES THE RATIO'S REGISTER $f12 -- i.e. it is
 * ONE variable, written twice. Confirmed by eye on the per-instruction diff.
 * This is the "refuse a better score that makes the output less like golden"
 * rule firing for real. 405 is the honest state.
 *
 * ---------------------------------------------------------------------------
 * THE RESIDUAL: one FP-allocation decision, plus the nop it drags with it
 * ---------------------------------------------------------------------------
 * The FIRST divergence is a single register:
 *      golden   trunc.w.d $f18,$f10 ; mfc1 a1,$f18
 *      mine     trunc.w.d $f16,$f10 ; mfc1 a1,$f16
 * Everything downstream is that one choice cascading. IDO gives the three
 * long-lived FP values the registers left over after the trunc temp:
 *      golden  trunc=$f18  ->  1.0f=$f16, unk64=$f14, vol=$f12
 *      mine    trunc=$f16  ->  1.0f=$f14, unk64=$f12, vol=$f2  (ran out)
 * `vol` landing in $f2 is the tell that the pool was one short. Get the trunc
 * temp to $f18 and all 61 register diffs should fall at once.
 * The lone missing instruction is `nop` at 0x151165FC+4, between
 * `mtc1 at,$f16` (1.0f) and `lwc1 $f14,0x64(s0)`. It is not a hazard for any
 * register in sight (f16 is not read for 8 instructions); as1 simply had
 * nothing to schedule there, while in mine the `lwc1` fills it. Strongly
 * suspected to be the same root cause as the $f18/$f16 choice.
 *
 * The integer side is one small localised swap in the unk3C store:
 *      golden  lw t2 / sll t1 / andi t3,t2 / or t4,t3,t1
 *      mine    lw t1 / sll t3 / andi t2,t1 / or t4,t2,t3
 * i.e. golden creates the `n << 16` temp BEFORE the `& 0xFFFF` temp. Swapping
 * the `|` operands in the source does NOT change it (measured, no-op).
 *
 * ---------------------------------------------------------------------------
 * MEASURED NEGATIVES -- 22 variants, every one asserted to actually patch,
 * with a CONTROL that moved the score (500.0f -> 501.0f gave 605, proving the
 * harness was live and the repeated 405s are real no-ops, not a dead harness).
 * ---------------------------------------------------------------------------
 *  WORSE:
 *    845  invert the top test to `if (arg0->unk4F & 4) { call } else { 0 }`
 *         -- golden's `bnez t7,<call>` really is the NEGATIVE spelling.
 *    880  compute `d` inline inside the `timer <= 0` arm. `d` is its own
 *         statement BEFORE the `if`: golden has the whole mul.d/trunc.w.d
 *         above `bgtz v1`.
 *    570  a `tmp` local for `arg0->unk3C.w & 0xFFFF`.
 *    475  an f64 intermediate (`dd = n * K; d = (s32)dd;`).
 *     70  the two-f32-locals split -- worse, see THE SCORE LIED above.
 *  EXACT NO-OPS (all 405, all patched and asserted):
 *    `timer = ...` before vs after `d = ...`
 *    `(n << 16) | (w & 0xFFFF)` vs `(w & 0xFFFF) | (n << 16)`
 *    declaration order amount/n/d/timer -> n/timer/amount/d
 *    declaration order of vol / pitch / ratio (3 permutations)
 *    `if (1.0f < vol)` vs `if (vol > 1.0f)`
 *    `d = (s32)(D_800A2FB8 * n)` and `d = (s32)((f64)n * D_800A2FB8)`
 *    a `f32 h = arg0->unk64;` local instead of three field reads
 *    a `u16 sfx = arg0->unk74;` local (the idiom the matched sibling
 *        func_15114D24 in game_13D350.c uses) + calls through it
 *    struct spelled as `s16 unk3C; u16 unk3E;` with a `*(s32*)&` write
 *    struct spelled as `s32 unk3C;` with a `*(s16*)&` read
 *    `amount = call; amount >>= 3;`
 *    dropping the `timer` local entirely (field read three times)
 *    nesting `if (arg1 & 1) { if (amount < 0) ... }`
 *    `if (arg2 != 0) { tail }` instead of the early `return`
 *    explicit `(u16)pitch` / `(s16)vol` at the call sites
 *    `vol = vol * arg3; vol = vol - 500.0f;`
 *    `pitch` typed s32 instead of u32
 *
 * TO CLOSE: find the construct that advances IDO's FP temp allocation by one
 * before the `trunc.w.d`. Everything else about this function is settled.
 * ========================================================================== */

/* ---- add to the shadow block at the top of src/game_142560.c ---- */
/*
 *  #define func_10010F88 func_10010F88_void_decl_in_functions_h
 *  #include "functions.h"
 *  #undef  func_10010F88
 *  extern s32 func_10010F88(s32 arg0, u16 arg1, s16 arg2, u8 arg3, s32 arg4,
 *                           s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9);
 */

extern f64 D_800A2FB8;
extern f32 D_800A2FC0;
extern f32 D_800A2FC4;
extern f32 D_800A2FC8;
extern f32 D_800A2FCC;
extern f32 D_800A2FD0;

struct Obj15116888;
s32 func_15116888(s32 arg0, s32 arg1, s32 arg2, struct Obj15116888 *arg3);

struct Obj1511650C {
    u8  pad0[0x10];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    u8  pad16[0x26];
    /* 0x3C */ union { s32 w; s16 h; } unk3C;   /* .h is the high half (BE) */
    u8  pad40[0xF];
    /* 0x4F */ u8  unk4F;
    u8  pad50[0x14];
    /* 0x64 */ f32 unk64;
    u8  pad68[0xC];
    /* 0x74 */ u16 unk74;
    u8  pad76[0x6];
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ s32 unk80;
    u8  pad84[0x1C];
};

void func_1511650C(struct Obj1511650C *arg0, s32 arg1, s32 arg2, f32 arg3) {
    s32 amount;
    s32 n;
    s32 d;
    s32 timer;
    f32 vol;
    u32 pitch;

    if ((arg0->unk4F & 4) == 0) {
        amount = 0;
    } else {
        amount = func_15116888(arg0->unk10, arg0->unk14, (s32)&arg0->unk7C,
                               (struct Obj15116888 *)D_800CC2D0) >> 3;
    }
    if ((arg1 & 1) && (amount < 0)) {
        amount = 0;
    }
    n = arg0->unk3C.h;      /* SPLIT -- see the statement-split law above */
    n += amount;
    if (amount != 0) {
        arg0->unk80 = 0;
    }
    d = (s32)(n * D_800A2FB8);
    timer = arg0->unk80;
    if (timer <= 0) {
        n += d;
        if (n > 0) {
            n--;
            if (n <= 0) {
                if (amount == 0) {
                    if (timer == 0) {
                        arg0->unk80 = 20;
                    } else {
                        arg0->unk80 = 0;
                        n = 0;
                    }
                } else {
                    n = 0;
                }
            }
        } else if (n < 0) {
            n++;
            if (n >= 0) {
                if (amount == 0) {
                    if (timer == 0) {
                        arg0->unk80 = 20;
                    } else {
                        arg0->unk80 = 0;
                        n = 0;
                    }
                } else {
                    n = 0;
                }
            }
        }
    } else if (timer > 0) {
        /* the second test is REDUNDANT but golden emits it: `blezl v1,<end>`
           at the head of the else block. Do not delete it. */
        if (n > 0) {
            n++;
            arg0->unk80 = timer - D_800BE9E4;
            if (arg0->unk80 <= 0) {
                arg0->unk80 = -1;
            }
        } else {
            n--;
            arg0->unk80 = timer - D_800BE9E4;
            if (arg0->unk80 <= 0) {
                arg0->unk80 = -1;
            }
        }
    }
    arg0->unk3C.w = (arg0->unk3C.w & 0xFFFF) | (n << 16);
    func_1511515C((struct Obj1511515C *)arg0);
    if (arg2 == 0) {
        return;
    }
    vol = fabsf(arg0->unk64) * D_800A2FC0;
    if (vol > 1.0f) {
        vol = 1.0f;
    }
    pitch = (u32)((D_800A2FC4 * vol) + D_800A2FC8);
    vol = (vol * arg3) - 500.0f;   /* ONE variable reused -- see THE SCORE LIED */
    if (arg0->unk74 == 0) {
        if (D_800A2FCC < arg0->unk64) {
            arg0->unk74 = func_10010F88(arg2, pitch, vol, 0, -1, arg0->unk10,
                                        arg0->unk12, arg0->unk14, 1000, 6000);
        }
    } else if (D_800A2FD0 < arg0->unk64) {
        func_1000F91C(arg0->unk74, pitch, vol, 0, -1, arg0->unk10, arg0->unk12,
                      arg0->unk14, 200, 2000);
    } else {
        func_100111C8(arg0->unk74);
        arg0->unk74 = 0;
    }
}
