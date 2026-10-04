/* =====================================================================================
 * PARK: func_151733E4  (TU game_1A0790 -- the TU's only remaining #pragma GLOBAL_ASM)
 *
 * FILE SHAPE: BODY TO SPLICE.  Everything below the header goes in place of the line
 *                 #pragma GLOBAL_ASM("asm/nonmatchings/game_1A0790/func_151733E4.s")
 *             in conker/src/game_1A0790.c.  It is NOT a standalone TU -- it relies on
 *             that file's `extern u8 D_800DD2E4[];`, `extern struct104 *D_800B0DF0;`
 *             and `extern struct151732E0_state D_8008CC70;`.  Scoring this file on its
 *             own gives a CCFAIL that looks like a broken park.  To score:
 *                 splice into a copy of conker/src/game_1A0790.c, then
 *                 python3 tools/fastscore.py game_1A0790 func_151733E4 <copy>
 *
 * BEST SCORE     mism=357    n=307/312 (we are 5 instructions SHORT)
 * FRAME          -96 (0x60)  vs golden 0x70   -- 16 bytes of locals missing
 *                (an earlier 7-separate-pointer spelling gave 0x68; neither matches)
 * OPT_FLAGS      -O2 -g3 (default; game_1A0790 has no Makefile override)
 *
 * WHAT IS ALREADY RIGHT
 * ---------------------
 * The control-flow skeleton matches end to end: the arg4 == -1 split, both pointer
 * set-up blocks in golden's slot order, the two-iteration loop with the
 * `q = (i == 0) ? &arg0 : &arg1` select (bnez + &arg1 in the delay slot), the 4-way
 * compare chain in golden's case order with the beql peephole, the jal func_15173994
 * with `lw $a0, arg2home($sp)` in the delay slot, all ten
 * `base + (other - base) * arg3 / 4096` lerps with the exact bgez/addiu 0xFFF/sra 12
 * signed-divide-by-4096 pattern, the `multu` (not `mult`), the lbu/lhu/lh widths, and
 * both `-1 -> D_800B0DF0->unk0/unk2` fallbacks including the redundant
 * `sll 16 ; sra 16 ; or` s16 re-truncation and the trailing bnel.
 *
 * THE BLOCKER: TWO CALLEE-SAVED REGISTERS GO TO THE WRONG CANDIDATES
 * -----------------------------------------------------------------
 * Both builds use exactly nine s-registers.  Golden spends them on
 *      s0=q  s1=&D_8008CC70  s2=i  s3=arg3  s4=2  s5=dst  s6=&arg0  s7=0x7C  fp=0x7D
 * and puts 0x7E / 0x7F in $at inside the loop.  We spend them on
 *      s0=q  s1=i  s2=2  s3=&D_8008CC70  s4=&arg0  s5=0x7C s6=0x7D s7=0x7E s8=0x7F
 * so IDO has nothing left for arg3 (it stays in $a3 and is spilled to its own arg-home
 * slot around the one call) and nothing for dst (it becomes a 7th stack pointer).
 * i.e. golden's loop-invariant hoisting budget was 4 candidates, ours is 6, because
 * golden had already committed s3 and s5 to arg3 and dst.
 *
 * Two visible consequences, both purely downstream of that:
 *   (a) golden RELOADS arg0/arg1 from their home slots before each of the first five
 *       lerps and recomputes `<<4` each time; we load them once and CSE the shifts.
 *       (Golden stops reloading after the first `sh` store, which is what makes this
 *       look like register pressure / rematerialisation rather than aliasing.)
 *   (b) golden's loop test is `addiu s2,s2,1 ; slti at,s2,2 ; bnez at` while ours is
 *       `addiu s1,s1,1 ; bne s1,s2` -- ours reuses the hoisted literal 2 as the bound,
 *       which is where 1 of the 5 missing instructions goes.  Golden's `or s3,a3,zero`
 *       is another.
 *
 * REMAINING DIFF ROWS (first 28 of 357; from idx1 on everything is shifted by the
 * missing `or $s3,$a3,$zero`, so the row-by-row list past idx20 is not informative)
 *   idx0    ours=27bdffa0 gold=27bdff90   frame 0x60 vs 0x70
 *   idx1    ours=afb00018 gold=afb30024   golden saves $s3 first (it writes it at once)
 *   idx2    ours=8fb00070 gold=afb00018
 *   idx3    ours=afbf003c gold=8fb00080   5th arg at 0x80($sp) for golden, 0x70 for us
 *   idx4    ours=afbe0038 gold=00e09825   <== the missing `or $s3,$a3,$zero`
 *   idx5..14                              the whole save block shifted by one
 *   idx15   ours=3c010000 gold=afa60078
 *   idx16   ours=a4270000 gold=3c01800e   we do `sh $a3`, golden does `sh $s3`
 *   idx17   ours=2401ffff gold=a433d2f0
 *   idx18   ours=16010019 gold=2401ffff
 *   idx19   ours=00008825 gold=16010018   i lands in $s1 for us, $s2 for golden
 *   idx20+                                register renames + the one-instruction shift
 *
 * DO-NOT-REPEAT  (every spelling measured, with its score)
 * -------------------------------------------------------
 *   356/307  if / else-if chain on *q          -- WRONG SHAPE: gives `bne <const>,v0`
 *                                                 with inline bodies.  A `switch` gives
 *                                                 golden's `beq v0,<const>` + case bodies
 *                                                 after the loop increment.  KEEP SWITCH.
 *   357/307  `q = i ? &arg1 : &arg0`           -- gives beqz + &arg0 in the delay slot.
 *                                                 `q = (i == 0) ? &arg0 : &arg1` gives
 *                                                 golden's bnez + &arg1.  KEEP THIS FORM.
 *   357/307  7 separate pointers, p0 declared first  (frame 0x68)
 *   357/307  same, p0 declared last                  (frame 0x68)
 *   357/307  p0 as `u8 *` with p4..pE as (u16*)(p0+n) (frame 0x60)
 *   357/307  dst as `lerpState *`, p4..pE as &dst->aN (frame 0x60)   <== THIS FILE
 *   357/307  + `s32 frac = arg3;` local copy used in all ten multiplies (no effect --
 *              IDO coalesces frac with the parameter; this lever is dead)
 *   357/307  + `i = 0; while (i < 2) { ... i++; }` instead of the for loop (no effect)
 *   357/307  + both of the above together
 *   357/307  + two extra named locals assigned before use (frame UNCHANGED -- so the
 *              "-g3 named local costs 4 bytes" law does NOT bite in this TU either)
 *   357/307  + `(other - base) * arg3 / 4096 + base` on the four u16 lerps
 *   357/307  + the same swap on the two s16 lerps
 *              (IDO canonicalises commutative addu; operand order is NOT source-
 *               controllable here, do not chase the `addu v0,t9` / `addu t9,v0` rows)
 *   582/282  DIAGNOSTIC ONLY: dropping cases 0x7E/0x7F.  Confounded -- it also removes
 *            the only call, so every callee-saved requirement disappears.  Useless.
 *
 * WHAT WOULD MOVE IT
 *   Find the spelling that makes IDO rank `arg3` and `dst` above the 0x7E / 0x7F
 *   compare constants when it hands out callee-saved registers.  Concretely: two more
 *   s-registers must be taken away from the loop-invariant hoister.
 *     1. arg3 declared `s16` -- MEASURED AND FALSIFIED.  322 / n=310 looks like an
 *        improvement but it is not: it buys the 3 instructions purely by adding a
 *        `sw $a3 ; sll 16 ; sra 16` re-extension prologue that GOLDEN DOES NOT HAVE
 *        (golden's first use of a3 is a bare `or $s3,$a3,$zero`), and arg3 still fails
 *        to get $s3 -- it now spills with `sh`/`lh` instead.  arg3 IS s32.  Do not
 *        propose the prototype change to the lead.
 *     2. arg4 declared `s16` -- measured, no change at all (357 / n=307).
 *     3. arg2 not homed -- if arg2 could stay in a register the pressure profile changes.
 *     4. tools/decomp-permuter seeded with the spliced TU.
 *   Also still unexplained: golden reserves 24 bytes of unused locals (0x58..0x6C) above
 *   its six pointer slots; we reserve 4.  I did NOT chase this by declaring filler
 *   locals -- per the standing ruling, "declare N unreferenced bytes to make the frame
 *   fit" is a STOP.  What would name those bytes is finding the two locals that golden
 *   really has and we do not, and the arg3/dst register question above is the same
 *   question seen from the other side.
 *
 * HONESTY NOTE ON `&arg0` / `&arg1`
 *   Taking the address of a parameter is on the banned list when it is done "purely to
 *   defeat register allocation".  That is not the case here: golden homes a0/a1/a2 to
 *   0x70/0x74/0x78($sp), loads the switch operand with `lw $v0,0($s0)`, WRITES it back
 *   with `sw ...,0($s0)`, and then re-reads arg0/arg1 from those homes for the lerps.
 *   No direct-variable spelling can produce an indirect load/store through a selected
 *   pointer; the original really does rewrite its own parameters through a pointer.
 *
 * SEMANTICS (high confidence)
 *   D_8008CC70 is an ARRAY of 16-byte colour/parameter records:
 *       +0..+3  u8   (rgba-ish, func_151738C4 copies 3 of them to D_800DBEA8)
 *       +4,+6,+8,+A u16
 *       +C,+E   s16, where -1 means "inherit from D_800B0DF0->unk2 / ->unk0"
 *   func_151733E4(a, b, ctx, frac, out) linearly interpolates record[a] -> record[b] by
 *   frac/4096 and writes the result either into record[out] (when out != -1) or into the
 *   loose globals D_800DD2E4/E8/EA/EC/EE/F2/F4 (when out == -1).  frac itself is latched
 *   into D_800DD2F0.  Before interpolating, each of a and b is passed through a small
 *   remap: 0x7C -> 1, 0x7D -> 2, 0x7E -> func_15173994(ctx), 0x7F -> 2 (i.e. 0x7C..0x7F
 *   are symbolic "current palette" selectors rather than real indices).
 *   This is the LIGHTING / FOG palette cross-fader.
 * ===================================================================================== */

typedef struct {
    u8  a0;
    u8  a1;
    u8  a2;
    u8  a3;
    u16 a4;
    u16 a6;
    u16 a8;
    u16 aA;
    s16 aC;
    s16 aE;
} lerpState;

typedef struct {
    s16 b0;
    s16 b2;
} lerpArg;

extern s16 D_800DD2F0;
extern u16 D_800DD2E8;
extern u16 D_800DD2EA;
extern u16 D_800DD2EC;
extern u16 D_800DD2EE;
extern s16 D_800DD2F2;
extern s16 D_800DD2F4;
s8 func_15173994(s32);

#define LS ((lerpState *)&D_8008CC70)
#define LA ((lerpArg *)D_800B0DF0)

void func_151733E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    lerpState *dst;
    u16 *p4;
    u16 *p6;
    u16 *p8;
    u16 *pA;
    s16 *pC;
    s16 *pE;
    s32 *q;
    s32 i;
    s16 va;
    s16 vb;

    D_800DD2F0 = arg3;
    if (arg4 == -1) {
        dst = (lerpState *)D_800DD2E4;
        p4 = &D_800DD2EC;
        p6 = &D_800DD2EE;
        p8 = &D_800DD2E8;
        pA = &D_800DD2EA;
        pC = &D_800DD2F2;
        pE = &D_800DD2F4;
    } else {
        dst = &LS[arg4];
        p4 = &dst->a4;
        p6 = &dst->a6;
        p8 = &dst->a8;
        pA = &dst->aA;
        pC = &dst->aC;
        pE = &dst->aE;
    }
    for (i = 0; i < 2; i++) {
        q = (i == 0) ? &arg0 : &arg1;
        switch (*q) {
            case 0x7C:
                *q = 1;
                break;
            case 0x7D:
                *q = 2;
                break;
            case 0x7E:
                *q = func_15173994(arg2);
                break;
            case 0x7F:
                *q = 2;
                break;
        }
    }
    dst->a0 = LS[arg0].a0 + (LS[arg1].a0 - LS[arg0].a0) * arg3 / 4096;
    dst->a1 = LS[arg0].a1 + (LS[arg1].a1 - LS[arg0].a1) * arg3 / 4096;
    dst->a2 = LS[arg0].a2 + (LS[arg1].a2 - LS[arg0].a2) * arg3 / 4096;
    dst->a3 = LS[arg0].a3 + (LS[arg1].a3 - LS[arg0].a3) * arg3 / 4096;
    *p4 = LS[arg0].a4 + (LS[arg1].a4 - LS[arg0].a4) * arg3 / 4096;
    *p6 = LS[arg0].a6 + (LS[arg1].a6 - LS[arg0].a6) * arg3 / 4096;
    *p8 = LS[arg0].a8 + (LS[arg1].a8 - LS[arg0].a8) * arg3 / 4096;
    *pA = LS[arg0].aA + (LS[arg1].aA - LS[arg0].aA) * arg3 / 4096;
    if (LS[arg0].aC == -1) {
        va = LA->b2;
    } else {
        va = LS[arg0].aC;
    }
    if (LS[arg1].aC == -1) {
        vb = LA->b2;
    } else {
        vb = LS[arg1].aC;
    }
    *pC = va + (vb - va) * arg3 / 4096;
    if (LS[arg0].aE == -1) {
        va = LA->b0;
    } else {
        va = LS[arg0].aE;
    }
    if (LS[arg1].aE == -1) {
        vb = LA->b0;
    } else {
        vb = LS[arg1].aE;
    }
    *pE = va + (vb - va) * arg3 / 4096;
}
