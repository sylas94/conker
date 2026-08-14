/* ===========================================================================
 * func_150FF2D4  --  game_12C1E0.c  --  416 bytes / 104 instructions
 * PARKED at 325 (with AND without -R, window bounded to 104 words).
 * draft1 525 -> 505 -> 325.
 *
 * STATE: FRAME EXACT (0x38, zero home area -- the three f32 locals get no stack
 * home).  ONE instruction short (412 vs 412... mine 412, golden 416).  Exactly
 * two residual regions:
 *   (a) `lw a2,0x4c(sp)` (the arg5 reload) is emitted one slot EARLIER than
 *       golden, which puts it before `lui at,%hi(D_800A2120)` instead of after
 *       `lwc1 $f2,%lo(D_800A2120)(at)`.  Pure scheduling.
 *   (b) golden's then-branch is
 *           670: mul.s $f16,$f2,$f12    678: mul.s $f18,$f10,$f12
 *           67c: nop                    680: b 698   684: lui at,0x4208
 *       i.e. it DUPLICATES `lui at,0x4208` (34.0f) into the branch delay slot
 *       and pads the second mul with a nop; the live C leaves the delay slot
 *       empty, lets as1 pull the `b` up, and shares one `lui` at the merge.
 *       That duplicate is the missing instruction.  as1 PEEPHOLE class.
 *
 * ---------------------------------------------------------------------------
 * WHAT THE ASM SAYS (all confirmed by build)
 * ---------------------------------------------------------------------------
 * 15 params.  framesize 0x38 = arg-build [0x00,0x28) (func_151D5174 takes 10)
 * + temps [0x28,0x30) + saved s0 0x30 / ra 0x34.  NO home area at all, so the
 * function has NO integer autos; the three f32 locals (zdir/xdir/inv) live only
 * in $f16/$f18/$f12 and cost nothing -- an f32 auto whose address is never
 * taken gets no stack home here.
 * s0 = arg2 throughout.  The tail call is
 *   func_151D5174(arg13, arg2, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12)
 * and the head is
 *   if (*arg0) *arg0 = func_150FF6E0(arg1,arg2,arg3,arg4,arg12,arg13,arg14);
 * The second test reuses the stored byte: golden emits `andi $v1,$v0,0xff`
 * beside `sb $v0,0($a0)` rather than a second `lbu`, i.e. IDO forwards the
 * store to the following `if (*arg0 == 0)` load.  Writing it as two plain
 * `*arg0` tests reproduces that exactly.
 *
 * ---------------------------------------------------------------------------
 * MEASURED NEGATIVES/POSITIVES  (bounded window, 104 words)
 * ---------------------------------------------------------------------------
 *   525  draft1: the reciprocal written inline twice,
 *        `zdir = arg5->unk8 * (1.0f / sqrtf(...))`.  IDO CSEs the division but
 *        emits `mul.s $f16,$f12,$f2` -- operands the wrong way round.
 *   505  + naming the reciprocal (`inv = 1.0f / sqrtf(...); zdir = ...unk8*inv`).
 *        Fixes both `mul.s` operand orders.
 *   505  flipping the guard to `D_800A2120 < fabsf(arg5->unk0)` from
 *        `fabsf(arg5->unk0) > D_800A2120`.  BYTE-IDENTICAL -- does NOT move the
 *        `lw a2,0x4c(sp)`.
 *   325  CURRENT = 505 measured on a build where func_150FF6E0 had also changed;
 *        325 is the bounded, per-symbol number.  (The 4096-line window bleeds
 *        into the next function -- always bound the window on this TU.)
 *
 * RODATA: NOT blocked.  D_800A2120 (9.999999747e-05, low16 != 0) is read once,
 * outside any loop, so `extern f32` produces exactly golden's lui/lwc1 pair.
 *
 * RESIDUAL CLASS: SCHEDULING (a) + as1 PEEPHOLE (b).
 *
 * ---------------------------------------------------------------------------
 * WAVE 2 (2026-08-14).  BASE RE-CONFIRMED 325 / 412 B (golden 416), bounded 104.
 * ---------------------------------------------------------------------------
 * THE TWO RESIDUAL WINDOWS, EXACT:
 *  (a)  golden 608 move a1,s0 | 60c lui at,%hi(2120) | 610 lwc1 $f2,%lo |
 *              614 lw a2,0x4c(sp) | 618 lwc1 $f14,0(a2)
 *       live   608 move a1,s0 | 60c lw a2,0x4c(sp)   | 610 lui at,%hi |
 *              614 lwc1 $f2,%lo | 618 lwc1 $f14,0(a2)
 *       One adjacent-pair swap.  Note golden's schedule is the *worse* one by
 *       critical path (it puts `lw a2` immediately before its use), so this is
 *       not a priority-order effect I can reach from the source.
 *  (b)  golden 678 mul.s $f18 | 67c nop | 680 b 698 | 684 lui at,0x4208
 *              688 mtc1 at,$f16 | 68c mtc1 zero,$f18 | 690 nop |
 *              694 lui at,0x4208 | 698 mtc1 at,$f0
 *       live   678 mul.s $f18 | 67c b 690 | 680 nop |
 *              684 mtc1 at,$f16 | 688 mtc1 zero,$f18 | 68c nop |
 *              690 lui at,0x4208 | 694 mtc1 at,$f0
 *       golden TAIL-DUPLICATES the merge block's leading `lui at,0x4208` into
 *       the then-arm's branch delay slot (splitting the li.s macro across the
 *       merge); live pulls the `b` up one slot and puts a nop in the slot,
 *       sharing one lui.  That duplicate is the only missing instruction.
 *
 * MEASURED THIS WAVE (bounded 104, vs the 325 base):
 *   325  `(D_800A2120 < fabsf(arg5->unk0)) || (D_800A2120 < fabsf(arg5->unk8))`
 *        IDENTICAL OUTPUT (re-measured on the current base -- the old note that
 *        this was byte-identical still holds after the wave-1 structural wins).
 *   325  naming the threshold: `f32 eps; ... eps = D_800A2120;` at the top of
 *        the `if (*arg0 == 0)` block, both compares against `eps`.
 *        IDENTICAL OUTPUT, AND THE FRAME DID NOT MOVE.  Two facts banked:
 *          - an f32 auto whose address is never taken costs ZERO frame here
 *            (0x38 with 3 autos and with 4), confirming the "no home area"
 *            reading; and
 *          - IDO SINKS the constant load to its use, so source position of the
 *            constant is not the lever for residual (a).
 *
 * THE SOURCE IS NOW CONFIRMED CORRECT BY THE ASYMMETRY OF THE TWO LOADS.
 * golden loads arg5->unk0 ONCE (`lwc1 $f14,0(a2)` at 618, reused at 64c and
 * 660) but arg5->unk8 TWICE (630 in the guard, 650 in the square).  That is
 * exactly what you get with NO local copies: the 618 load dominates both arms,
 * while the 630 load sits inside the short-circuit block that the first
 * `bc1t 64c` skips, so it is not available at 650.  A `f32 dz = arg5->unk8;`
 * local would collapse the second load and is therefore WRONG.  Likewise
 * ruled out by the instructions: `(arg5->unk8*arg5->unk8)` first in the sqrt
 * argument (golden squares unk0 first), `(34.0f*xdir)+x_position` (golden is
 * `add.s $f8,$f4,$f6` = x_position + product), scaling by 34.0f inside the
 * arms (golden's $f0=34.0 is materialised after the merge and used twice).
 *
 * RESIDUAL CLASS: SCHEDULING (a) + as1 PEEPHOLE (b).  BAILED at 325.
 *
 * FOOTNOTE -- THE ONE PLACE AN EXTRA AUTO IS FREE.  This function has NO home
 * area (framesize 0x38 = arg-build 0x28 + temps 0x8 + s0/ra), so an f32 auto
 * whose address is never taken costs nothing: adding a fourth (`f32 eps;`) left
 * the frame at 0x38 and the output byte-identical.  That is NOT true of its two
 * TU neighbours -- in func_150FF6E0 one extra s32 takes the frame 0x88 -> 0x90,
 * and in func_150FF840 three extra f32s take it 0x128 -> +16 bytes of code.
 * Do not generalise "f32 autos are free" beyond this function.
 * =========================================================================== */

/* ---- parked source: this is the 325 build, verbatim ---- */

extern f32 D_800A2120;
extern f32 sqrtf(f32);
extern f32 fabsf(f32);
s32 func_150FF6E0(struct17 *, struct17 *, struct17 *, struct17 *, struct17 *, struct127 *, struct126 *);
void func_151D5174(struct127 *, struct17 *, struct17 *, struct17 *, struct17 *, struct17 *, struct17 *, s32 *, s32 *, struct17 *);

void func_150FF2D4(u8 *arg0, struct17 *arg1, struct17 *arg2, struct17 *arg3, struct17 *arg4, struct17 *arg5, struct17 *arg6, struct17 *arg7, struct17 *arg8, struct17 *arg9, s32 *arg10, s32 *arg11, struct17 *arg12, struct127 *arg13, struct126 *arg14) {
    f32 zdir;
    f32 xdir;
    f32 inv;

    if (*arg0 != 0) {
        *arg0 = func_150FF6E0(arg1, arg2, arg3, arg4, arg12, arg13, arg14);
    }
    if (*arg0 == 0) {
        if ((fabsf(arg5->unk0) > D_800A2120) || (fabsf(arg5->unk8) > D_800A2120)) {
            inv = 1.0f / sqrtf((arg5->unk0 * arg5->unk0) + (arg5->unk8 * arg5->unk8));
            zdir = arg5->unk8 * inv;
            xdir = -arg5->unk0 * inv;
        } else {
            zdir = 1.0f;
            xdir = 0.0f;
        }
        arg2->unk0 = arg13->x_position + (34.0f * xdir);
        arg2->unk4 = arg13->y_position + 49.0f;
        arg2->unk8 = arg13->z_position + (34.0f * zdir);
        *arg12 = *arg2;
    }
    func_151D5174(arg13, arg2, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12);
}
