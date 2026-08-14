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
