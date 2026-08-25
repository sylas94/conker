/* PARKED near-miss: func_15008340  (TU game_357F0 -- a SINGLE-function TU, so this file is a
 * STANDALONE TU: score it exactly as it stands with
 *     python3 tools/fastscore.py game_357F0 func_15008340 tools/nearmiss/func_15008340.c
 *
 * SCORE 11 (fastscore, -O2 -g3 tree default).  n = 320/320 words.  frame -0x50 == golden.
 * Everything structural is EXACT: the switch dispatch, all four arm bodies, every stack slot,
 * every integer register, every relocated symbol.  The 11 residual rows are two register /
 * scheduler ties, described below.
 *
 * WHAT THIS FUNCTION IS
 *   void func_15008340(shape *arg0, f32 *outX, f32 *outZ, f32 *outTop, f32 *outBottom)
 *   picks a random point inside a spawn volume selected by arg0->unk15 & 3:
 *     0 = disc (random angle + random radius)      2 = rotated box (unk10 = degrees, unk6/unkA
 *     1 = sphere-ish (same, but Y extent = unk6)       are the half-extents, unk8 the height)
 *     3/default = the point itself
 *   Caller evidence: conker/src/game_39750.c carries a commented draft calling
 *   func_15008340(arg0, &tmp.unk30, &tmp.unk38, &tmp.unk4, &tmp.unk0) -- confirms 4 f32* outs.
 *
 * WHAT WAS RECOVERED (all measured, none guessed)
 *   * The dispatch is  switch (arg0->unk15 & 3)  with a  default:  arm -- not an if/else chain
 *     and not an explicit  case 3:  (see DO-NOT-REPEAT).
 *   * SOURCE ORDER OF THE ARMS IS default, 2, 0, 1.  Golden lays the bodies out in that order and
 *     allocates the three block-scope local regions in the REVERSE of it (case 1 lowest at 0x20,
 *     case 0 at 0x30, case 2 at 0x40).
 *   * LOCAL-SLOT LAW -- this is what took the frame from -0x60 to -0x50.  At -O2 -g3 EVERY named
 *     local costs 4 bytes of frame even when it lives entirely in a register, and inside a block
 *     the FIRST-declared local gets the HIGHEST address.  Golden has EXACTLY FOUR locals in each
 *     of the three arms:
 *         case 2: ang(0x4C) sn(0x48) cs(0x44) dx(0x40)   -- all four spilled
 *         case 0: rnd(0x3C) ang(0x38) sn(0x34) cs(0x30)  -- rnd never leaves a register
 *         case 1: rnd(0x2C) ang(0x28) sn(0x24) cs(0x20)  -- rnd never leaves a register
 *     Hence the SECOND random draw in case 2 must reuse "ang", and "rnd" in cases 0/1 must serve
 *     both the angle draw and the radius.  Declaring the obvious 5-6 locals per arm gives -0x60
 *     and a score of 41; declaring only the 3 that are actually spilled gives -0x48 and 53.
 *   * (u32)(osGetCount() * func_150ADA20()) & 0xFFFF is the in-corpus spelling of the RNG draw --
 *     copied verbatim from the MATCHED conker/src/game_36680.c:521, as is the
 *     "rnd *= C; x = (rnd + rnd) * C2;" angle idiom.
 *   * "+ -arg0->unk6" really is an INTEGER negate (negu + cvt.s.w + add.s).  Spelling it
 *     "- (f32)arg0->unk6" CSEs the conversion and emits sub.s instead: +275.
 *
 * REMAINING DIFF ROWS (idx, ours | golden)
 *   A. case 2 -- a 3-cycle in the FP temp allocation (7 rows).  Identical instructions, different
 *      registers; golden takes f12/f14/f16 for the three reloads and lands dy in $f0, mine takes
 *      f2/f14/f16 and lands dy in $f12:
 *        idx 90   lwc1 $f2,0x44(sp)      | lwc1 $f12,0x44(sp)    (reload of cs)
 *        idx 95   cvt.s.w $f0,$f8        | cvt.s.w $f2,$f8       ((f32)arg0->unkA)
 *        idx 106  add.s $f10,$f0,$f0     | add.s $f10,$f2,$f2
 *        idx 114  add.s $f12,$f4,$f6     | add.s $f0,$f4,$f6     (the dy result)
 *        idx 115  mul.s $f8,$f14,$f2     | mul.s $f8,$f14,$f12
 *        idx 117  mul.s $f10,$f12,$f16   | mul.s $f10,$f0,$f16
 *        idx 120  mul.s $f10,$f12,$f2    | mul.s $f10,$f0,$f12
 *      Rows 0-89 are byte-identical, so nothing upstream explains the divergence.
 *   B. cases 0 and 1 -- ONE delay-slot tie-break, twice (4 rows):
 *        idx 173  lwc1 $f12,0x38(sp)     | swc1 $f0,0x34(sp)
 *        idx 175  swc1 $f0,0x34(sp)      | lwc1 $f12,0x38(sp)
 *        idx 254 / 256   the same pair at 0x28 / 0x24
 *      Golden emits [store sinf result][jal cosf][reload ang in the delay slot]; mine emits
 *      [reload ang][jal cosf][store sinf result in the delay slot].  Golden itself uses MY order
 *      in case 2 from an identical source shape, so the tie is context-driven, not spelling-
 *      driven.  The matched corpus (game_138520.c func_1510C8A8, game_142560.c func_15117DA4)
 *      emits golden's order for the same "ang = ...; sn = sinf(ang); cs = cosf(ang);" idiom, but
 *      in both of those "ang" lives in $f20 so the argument setup is a mov.s, not an lwc1.
 *
 * DO-NOT-REPEAT -- every spelling measured, with its score
 *   dispatch:   switch D201 = 201D = 2D01 = 11 | switch 012D 287 | switch D012 276 | 0D12 287
 *               switch with explicit "case 3:" 295 (order 3201) / 344 (order 2013, n=324)
 *               if/else 012D 314 | if/else 201D 315 | if/else D012 CCFAIL (syntax)
 *   locals:     4/4/4 with rnd declared first in arms 0/1 = 11 (THIS FILE)
 *               3/3/4 = 53 (frame -0x48) | 5/5/6 = 41 (frame -0x60)
 *               [ang,rnd,sn,cs] in arms 0/1 = 13 | "r" first with ang doubling as the draw = 15
 *   draw:       rnd=RND; rnd*=C; ang=(rnd+rnd)*C2 = 11 | rnd=RND*C; ang=(rnd+rnd)*C2 = 11
 *               ang=RND*C; ang=(ang+ang)*C2 = 15 | rnd += rnd then *C2 = 79
 *               u32 rnd = 17/21 | s32 rnd = 417 (n drops to 308)
 *   radius:     rnd = rnd * C3 * arg0->unk6 = 11 | rnd *= C3; rnd *= unk6 = 80
 *               radius into "ang" instead of "rnd" = 17
 *   case 2:     dy folded into "ang" = 11 | dy assigned inside the *arg1 expression = 211
 *               dx via a store/read-back temp burn = 299 (n=324) | operand-swapped products = 12
 *               dx/dy split across two statements = 11 | "+ (0 - unkA)" = 11 | "+ (f32)-unkA" = 11
 *               "D_80095B10 * arg0->unk10" (angle operand swap) = 11
 *               inlining the angle into both sinf/cosf calls (hoping for a CSE temp) = 240,
 *               n=328: IDO does NOT CSE across a call, it recomputes -- that theory is dead.
 *   formatting: ALL 43 adjacent-statement line joins enumerated one at a time -> every one is
 *               exactly 11.  Confirms the cookbook's "the line-join lever is PER-FUNCTION"; it is
 *               dead on this function.  Do not re-enumerate.
 *   permuter:   146k iterations, compiler_type = ido, seeded from this exact file.  Its only
 *               improvement (11 -> 9, fixing 2 of the 7 rows in residue A) works by inserting a
 *               dead "if (ang) { }" code-motion barrier -- a BANNED forcer, so it was rejected.
 *               No zero found.  Import dir left at conker/nonmatchings/func_15008340/.
 *
 * BEST THEORY OF THE BLOCKER
 *   Both residues are allocator / scheduler tie-breaks.  By the cookbook's own diagnostic,
 *   residue B carries the SAME registers in a different ORDER (scheduler) and residue A carries
 *   DIFFERENT registers (allocator).  The frame size, the whole slot map and the instruction
 *   count are already pinned exactly, so there is no slot-count or statement-count dial left:
 *   adding or removing ANY local moves the frame off -0x50 and costs 30-40 rows immediately.
 *   If someone returns to this: run the permuter with the empty-if / dead-statement passes
 *   disabled, or find a spelling in which case 2's second random value is an unnamed compiler
 *   temp while that block still ends up with exactly four 4-byte slots.
 */

#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
/* 0x00 */ s16 unk0;
/* 0x02 */ s16 unk2;
/* 0x04 */ s16 unk4;
/* 0x06 */ s16 unk6;
/* 0x08 */ s16 unk8;
/* 0x0A */ s16 unkA;
/* 0x0C */ s16 unkC;
/* 0x0E */ s16 unkE;
/* 0x10 */ f32 unk10;
/* 0x14 */ u8  unk14;
/* 0x15 */ u8  unk15;
} Struct357F0;

// bit of a beast

#define RND ((f32)((u32)(osGetCount() * func_150ADA20()) & 0xFFFF))

void func_15008340(Struct357F0 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *arg4) {
    switch (arg0->unk15 & 3) {
    default:
        *arg1 = arg0->unk0;
        *arg2 = arg0->unk4;
        *arg3 = (f32)arg0->unk2 + (f32)arg0->unk8;
        *arg4 = (f32)arg0->unk2 - (f32)arg0->unk8;
        break;
    case 2:
        {
            f32 ang;
            f32 sn;
            f32 cs;
            f32 dx;

            ang = arg0->unk10 * D_80095B10;
            sn = sinf(ang);
            cs = cosf(ang);
            dx = RND * D_80095B14 * ((f32)arg0->unk6 + (f32)arg0->unk6) + -arg0->unk6;
            ang = RND * D_80095B18 * ((f32)arg0->unkA + (f32)arg0->unkA) + -arg0->unkA;
            *arg1 = (f32)arg0->unk0 + (dx * cs + ang * sn);
            *arg2 = (f32)arg0->unk4 + (ang * cs - dx * sn);
            *arg3 = (f32)arg0->unk2 + (f32)arg0->unk8;
            *arg4 = arg0->unk2;
        }
        break;
    case 0:
        {
            f32 rnd;
            f32 ang;
            f32 sn;
            f32 cs;

            rnd = RND;
            rnd *= D_80095B1C;
            ang = (rnd + rnd) * D_80095B20;
            sn = sinf(ang);
            cs = cosf(ang);
            rnd = RND;
            rnd = rnd * D_80095B24 * arg0->unk6;
            *arg1 = (f32)arg0->unk0 + rnd * cs;
            *arg2 = (f32)arg0->unk4 - rnd * sn;
            *arg3 = (f32)arg0->unk2 + (f32)arg0->unk8;
            *arg4 = arg0->unk2;
        }
        break;
    case 1:
        {
            f32 rnd;
            f32 ang;
            f32 sn;
            f32 cs;

            rnd = RND;
            rnd *= D_80095B28;
            ang = (rnd + rnd) * D_80095B2C;
            sn = sinf(ang);
            cs = cosf(ang);
            rnd = RND;
            rnd = rnd * D_80095B30 * arg0->unk6;
            *arg1 = (f32)arg0->unk0 + rnd * cs;
            *arg2 = (f32)arg0->unk4 - rnd * sn;
            *arg3 = (f32)arg0->unk2 + (f32)arg0->unk6;
            *arg4 = (f32)arg0->unk2 - (f32)arg0->unk6;
        }
        break;
    }
}
