#include <ultra64.h>
#include "functions.h"
#include "variables.h"

/* File-local views: struct108 (the camera object) and struct127 both hide the
 * fields this function touches inside pad[] runs (0x25C, 0x344, 0x3B4, 0x3B8,
 * 0x6F0, 0x6F4, 0x920, 0x92C on the camera; 0x95 and 0x17C on the object), so a
 * local widened view is used rather than retyping the shared headers. */
typedef struct Obj15B5F0 {
    /* 0x000 */ u8  pad0[0x18];
    /* 0x018 */ f32 unk18;
    /* 0x01C */ u8  pad1C[0x68];
    /* 0x084 */ u16 unk84;
    /* 0x086 */ u8  pad86[0xF];
    /* 0x095 */ u8  unk95;
    /* 0x096 */ u8  pad96[0x6];
    /* 0x09C */ s32 unk9C;
    /* 0x0A0 */ u8  padA0[0xD];
    /* 0x0AD */ u8  unkAD;
    /* 0x0AE */ u8  padAE[0x54];
    /* 0x102 */ u8  unk102;
    /* 0x103 */ u8  pad103[0x34];
    /* 0x137 */ u8  unk137;
    /* 0x138 */ u8  pad138[0x44];
    /* 0x17C */ f32 unk17C;
    /* 0x180 */ f32 unk180;
} Obj15B5F0;

typedef struct Cam15B5F0 {
    /* 0x000 */ u8  pad0[0x2C];
    /* 0x02C */ s32 unk2C;
    /* 0x030 */ u8  pad30[0x54];
    /* 0x084 */ s32 unk84;
    /* 0x088 */ u8  pad88[0x1B4];
    /* 0x23C */ u8  unk23C;
    /* 0x23D */ u8  pad23D[0x1F];
    /* 0x25C */ f32 unk25C;
    /* 0x260 */ u8  pad260[0x9C];
    /* 0x2FC */ f32 unk2FC;
    /* 0x300 */ u8  pad300[0x44];
    /* 0x344 */ f32 unk344;
    /* 0x348 */ f32 unk348;
    /* 0x34C */ u8  pad34C[0x8];
    /* 0x354 */ f32 unk354;
    /* 0x358 */ u8  pad358[0x8];
    /* 0x360 */ f32 unk360;
    /* 0x364 */ u8  pad364[0x8];
    /* 0x36C */ u16 *unk36C;
    /* 0x370 */ u8  pad370[0x44];
    /* 0x3B4 */ f32 unk3B4;
    /* 0x3B8 */ f32 unk3B8;
    /* 0x3BC */ u8  pad3BC[0x14];
    /* 0x3D0 */ Obj15B5F0 *unk3D0;
    /* 0x3D4 */ Obj15B5F0 *unk3D4;
    /* 0x3D8 */ u8  pad3D8[0x218];
    /* 0x5F0 */ s32 unk5F0;
    /* 0x5F4 */ u8  pad5F4[0xFC];
    /* 0x6F0 */ f32 unk6F0;
    /* 0x6F4 */ f32 unk6F4;
    /* 0x6F8 */ u8  pad6F8[0x44];
    /* 0x73C */ s16 unk73C;
    /* 0x73E */ u8  pad73E[0x76];
    /* 0x7B4 */ f32 unk7B4;
    /* 0x7B8 */ u8  pad7B8[0x3C];
    /* 0x7F4 */ u16 unk7F4;
    /* 0x7F6 */ u8  pad7F6[0x12A];
    /* 0x920 */ u16 unk920;
    /* 0x922 */ u8  pad922[0xA];
    /* 0x92C */ u8  unk92C;
} Cam15B5F0;

extern u8  D_800C3671;
extern f32 D_800DC004;

void func_150495B0(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5);

void func_1512E140(Cam15B5F0 *arg0) {
    f32 var;
    f32 sp48;
    s32 sp44;

    if (D_800C3671 != 0) {
        return;
    }
    if (((arg0->unk2C & 0x100) == 0) && (arg0->unk92C != 0) && ((arg0->unk920 & 8) == 0)) {
        return;
    }

    sp48 = arg0->unk2FC - arg0->unk354;

    if ((arg0->unk5F0 & 0x10) && (*arg0->unk36C & 0x10)) {
        var = 95.0f;
    } else {
        var = arg0->unk348;
    }
    if (arg0->unk5F0 & 0x400) {
        var = var * 1.5f;
    }

    if ((arg0->unk84 & 0x10) == 0) {
        if (arg0->unk3D0->unk180 < arg0->unk3D0->unk17C) {
            if (((arg0->unk3D0->unk17C - 40.0f) < (arg0->unk354 + var)) &&
                (arg0->unk354 < (arg0->unk3D0->unk17C - 40.0f))) {
                var = (arg0->unk3D0->unk17C - 40.0f) - arg0->unk354;
                sp44 = 1;
            } else {
                sp44 = 0;
            }
        }
    }

    if ((arg0->unk6F0 != 0.0f) && (arg0->unk6F4 != 0.0f)) {
        var = (var < arg0->unk6F0) ? arg0->unk6F0 : ((arg0->unk6F4 < var) ? arg0->unk6F4 : var);
    }
    if (arg0->unk7F4 != 0) {
        var = D_800DC004;
    }

    if (arg0->unk23C != 0) {
        arg0->unk25C = 0;
        sp48 = var;
    } else {
        if (((arg0->unk5F0 & 0x40) && (arg0->unk2C != 0x100)) || (arg0->unk2C & 0x1000000)) {
            var = 0;
        } else if ((600.0f < (arg0->unk3D0->unk18 - arg0->unk3D0->unk180)) &&
                   ((arg0->unk5F0 & 0x400) == 0) &&
                   (arg0->unk3D0->unkAD == 0) &&
                   (arg0->unk3D0->unk102 == 0) &&
                   (arg0->unk3D4->unk9C == 0) &&
                   (arg0->unk3D4->unk95 == 0) &&
                   (arg0->unk3D0->unk137 == 0) &&
                   (arg0->unk3D0->unk84 != 0x194) &&
                   ((arg0->unk5F0 & 0x80) == 0)) {
            return;
        }
        if ((arg0->unk2C & 0x100) || (sp44 != 0)) {
            func_150495B0(&sp48, var, &arg0->unk25C, 5.0f, 9.0f, arg0->unk7B4);
        } else {
            func_150495B0(&sp48, var, &arg0->unk25C, arg0->unk3B4, arg0->unk3B8, arg0->unk7B4);
        }
    }

    arg0->unk2FC = arg0->unk354 + sp48;
    arg0->unk344 = arg0->unk2FC - arg0->unk354;
    if ((arg0->unk3D0->unkAD == 1) && (arg0->unk73C != 0) && (arg0->unk360 != -10000.0f)) {
        if (arg0->unk2FC < (arg0->unk360 + 5.0f)) {
            arg0->unk2FC = arg0->unk360 + 5.0f;
            arg0->unk344 = 5.0f;
        }
    }
}

/* =====================================================================
 * func_1512E140  (game_15B5F0.c, 880 B)   BEST = 780   (this file, unchanged)
 * game_15B5F0.c holds NOTHING ELSE -- closing this makes the TU complete.
 * asm-differ:  cd conker && python3 ../tools/asm-differ/diff.py \
 *                  -o func_1512E140 -R --max-lines 4096      (780, -R and not)
 * expected/ must be seeded first: it is gitignored and was ABSENT this wave.
 *   mkdir -p expected/build/src
 *   (pragma in place) make -C conker build/src/game_15B5F0.c.o VERSION=us
 *   cp conker/build/src/game_15B5F0.c.o expected/build/src/
 *
 * FRAME DECODE (re-derived and re-validated; framesize 0x50 EXACT):
 *   0x00-0x17 outgoing args (6 to func_150495B0; 0x10/0x14 hold args 5,6)
 *   0x20 s0, 0x24 ra;  0x28-0x43 compiler temp area
 *   home area 0x44-0x4F, top-down in declaration order:
 *      0x4C  #1 f32 var    (register-only, home never touched)
 *      0x48  #2 f32 sp48   (address-taken: addiu a0,sp,0x48)
 *      0x44  #3 s32 sp44   (memory-resident: sw zero / sw t8 / lw t1)
 *   The temp area has slack: a 4th REGISTER-ONLY local declared LAST is
 *   completely invisible (measured: `s32 unused_probe;` 4th -> 780, size 876,
 *   identical bytes).  Declared FIRST it costs 42 (822).  So the frame pins
 *   the first three declarations and says nothing about a 4th.
 *
 * ================= THE RESIDUAL, RE-DERIVED FROM SCRATCH =================
 * Our function is 876 bytes, golden is 880: we are EXACTLY ONE INSTRUCTION
 * SHORT, and it is
 *      golden 0x54:  mtc1 zero,$f12
 * sitting in the entry body block between `lwc1 $f6,0x354(s0)` and
 * `sub.s $f8,$f4,$f6`, where it also fills the lwc1 load-delay slot.
 * $f12 then holds 0.0 all the way to the two `c.eq.s $f12,$fN` at 0x12c/0x140
 * (the `unk6F0 != 0.0f && unk6F4 != 0.0f` test).  Because golden reserves
 * $f12 across that whole span, `var` is pushed to $f16 and every later FP
 * temp rotates one slot -- that rotation is the entire 780.
 * Ours materialises the same constant at the head of the continuation block
 * (0x120), where the branch-likely filler then triples it into the delay
 * slots at 0xbc and 0xdc.  Byte offsets realign at 0x124 and the tail is
 * instruction-for-instruction identical.
 * CLASS: constant HOME BLOCK, with a downstream allocation consequence.
 *
 * ============ NEW THIS WAVE: THE BLOCKER IS LOCATED ============
 * Diagnostic builds (semantics-changing, run only to locate the mechanism;
 * `first mtc1-zero offset` is the readout -- 0x54 == golden's placement):
 *   base                                          0xbc   876 B  780
 *   delete the whole sp44 block                   0x54   756 B      <-- hoists
 *   delete the 95.0f if/else                      0x90   832 B
 *   delete the 1.5f multiply                      0xa0   852 B
 *   delete both early-return guards               0x80   816 B
 *   sp44 block present but `if (1)` outer guard   0xcc   852 B
 *   sp44 block, inner FP work deleted             0x54   824 B      <-- hoists
 *   sp44 block, inner `unk180 < unk17C` deleted   0x54   856 B      <-- hoists
 *   sp44 block, outer `unk84 & 0x10` deleted      0xcc   852 B
 *   drop the `- 40.0f` web                        0x54   864 B      <-- hoists
 *   drop the `unk180` web                         0xbc   872 B
 *   drop the `(unk354 + var)` web                 0xbc   872 B
 *   drop the `var` live-in                        0xbc   880 B
 *   use sp48 in place of unk354 inside the block  0x54   876 B      <-- hoists
 *                                                  (but sp48's home moves
 *                                                   0x48 -> 0x40: confounded)
 * READING: IDO will hoist the shared 0.0f to the entry body block only when
 * the FP web pressure of the sp44 region is one lower than ours.  Golden
 * carries the SAME seven FP webs there ($f2 unk17C, $f18 unk180, $f4 40.0f,
 * $f0 unk354, $f14 unk17C-40, $f6 unk354+var, $f16 var) AND the constant in
 * $f12 -- eight.  So golden's SOURCE must present that region to uopt with
 * one fewer internal temp than ours does while emitting the identical 25
 * instructions.  That is the open question, and it is now a sharp one.
 *
 * CORPUS EVIDENCE gathered this wave (mine.py over all 464 built objects:
 * find live-C functions whose `mtc1 zero,$fN` is separated from its first use
 * by a branch target).  Only SIX exist in the whole tree.  The informative one:
 *   game_1B6DB0 func_15189900 @0xa0 -- `mtc1 zero,$f2` is hoisted ABOVE an
 *   if/else, and the C is
 *        temp_v0->unk64 = 0.0f;
 *        if (temp_v0->unk10.unk18 < 0.0f) { ... }
 *   i.e. ONE 0.0f web shared by a STORE and a COMPARE, def placed at the
 *   earliest point after the last `jal` (FP regs are caller-saved, so a call
 *   is a hard barrier for a constant web).
 *   game_117490 func_150EA11C @0x144 -- a 0.0f used by four field stores is
 *   materialised as the SECOND instruction of the function.
 *   => IDO does hoist float constants to the earliest dominating point.  It
 *   is a pressure/heuristic decision, not a spelling one, which is why 50
 *   spellings all landed on 876 bytes.
 *
 * RULED OUT THIS WAVE (real differ, --max-lines 4096, all size 876 unless
 * noted; none moved the mtc1 off 0xbc):
 *    780  base (comparisons != 0.0f, assignments = 0)
 *    780  `0.f` spelling; `!(x == 0.0f)`; `(f32)0`; `if(unk7F4)`; `var *= 1.5f`
 *    780  `!(arg0->unk84 & 0x10)`; the two sp44 guards merged with &&
 *    780  `>` with swapped operands on either sp44 comparison
 *    780  `f32 zero;` 4th local, `zero = 0.0f;` before OR after the sp48
 *         statement, used as the comparison operand (IDO const-propagates it)
 *    780  4th local `lim = unk17C - 40.0f`; 4th local `obj = arg0->unk3D0`
 *    780  `s32 unused_probe;` declared 4th (bit-identical -> a trailing
 *         register-only local is FREE; do not read anything into one)
 *    760  4-local `diff` first + `sp48 = diff`
 *    750  local for unk180 only;  790  local for unk6F0 only
 *    740  locals for BOTH unk17C and unk180, declared 4th+5th   <-- see below
 *    790  4-local `diff = unk2FC; sp48 = diff - unk354`
 *    822  a,b locals declared FIRST;  824  a,b + lim;  824  obj + a,b
 *    830  drop `(unk354+var)`;  855  drop the var assignment (both 872 B)
 *    860  4th local for `unk354 + var`;  935  `unk25C = 0.0f`
 *    975/1019  4th local for arg0->unk354 in the block
 *   1115  single sp44 condition;  1175  `sp44 = 1` before the var assignment
 *   1364  clamp as if/else-if instead of nested ternary (864 B)
 *   1475  `var = 0.0f`;  1490  `(f32)0` compares / all-0.0f (webs re-merge)
 *   1726  sp44 block with no inner FP;  2270  sp44 && written as nested ifs
 *    980  `sp48 = unk2FC; sp48 -= unk354;` (884 B, two extra instructions)
 *    995  outer guard rewritten as `goto skip;`
 *   3236  sp48 statement moved below the 95.0f block
 *
 * *** DO NOT SHIP THE 740. ***  Two different declaration orders of the same
 * pair of locals (a,b and b,a) both score EXACTLY 740, and a single local for
 * unk180 alone scores 750 -- that is the N-no-ops signature: the binary is
 * evidencing one folded temp web, not any particular construct.  Size stays
 * 876 in every one of them, so none of them is the missing instruction.
 *
 * NOT TRIED: the permuter seeded from this file (it now has a sharp target:
 * SIZE 880 with `mtc1 zero` at 0x54 -- reject any output still at 876).
 *
 * RODATA: -10000.0f (0xC61C4000, low16 != 0, NOT lui-able) is a compiler
 * literal pool.  asm/data/2481E0.rodata.s holds exactly one glabel
 * (D_800A3720) with .float payload + 12 bytes of zero padding, referenced
 * ONLY by func_1512E140.  Writing the literal makes our object grow a
 * .rodata section (golden's expected object has NONE -- verified this wave:
 * readelf -SW shows game_15B5F0.c.o with only .text 0x370).  The ROM link
 * therefore needs  - [0x2481E0, .rodata, game_15B5F0]  in conker/conker.us.yaml
 * plus splat --modes ld, exactly like game_138520 (0x247780) and game_1ED0F0
 * (0x24F480).  The range holds ONE symbol whose only consumer is this
 * function, so the migration is self-contained -- no still-stubbed neighbour
 * would lose its constant.  Do NOT swap it for `extern f32 D_800A3720`.
 * ===================================================================== */
