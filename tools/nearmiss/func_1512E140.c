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
 * func_1512E140  (game_15B5F0.c, 880 B)   BEST = 780   (cold start 2669)
 * Baseline in this file scores 780 with AND without -R.
 * asm-differ:  cd conker && python3 ../tools/asm-differ/diff.py \
 *                  -o func_1512E140 -R --max-lines 4096
 *
 * FRAME DECODE (validated, framesize 0x50 reproduces EXACTLY):
 *   0x00-0x1F  outgoing arg build (6 args to func_150495B0 -> 24 rounded to 32)
 *   0x20 s0, 0x24 ra                    -> fixed region 0x28
 *   home area ends at 0x50, top-down in declaration order:
 *      0x4C  local#1  f32 var    (register-only, never spilled)
 *      0x48  local#2  f32 sp48   (ADDRESS-TAKEN: addiu a0,sp,0x48)
 *      0x44  local#3  s32 sp44   (memory-resident: sw zero / sw t8 / lw t1)
 *   Adding a 4th register-only local does NOT change framesize (temp area
 *   absorbs it) but DOES shift sp48/sp44 down by 4 if it is declared before
 *   them -- measured, so the order above is pinned by the 0x48/0x44 offsets.
 *
 * RESIDUAL: exactly ONE instruction is in the wrong basic block.
 *   golden 0x54:  mtc1 zero,$f12     (inside the first body block, between
 *                 lwc1 $f6,0x354(s0) and sub.s $f8,$f4,$f6)
 *   mine   0x120: mtc1 zero,$f12     (head of the join block J1, duplicated by
 *                 as1 into the bc1fl/bnezl delay slots at 0xbc and 0xdc)
 *   The float 0.0 constant used by the two `c.eq.s $f12,$fN` comparisons
 *   (unk6F0/unk6F4 != 0.0f) is materialised by golden in the ENTRY body block
 *   and by IDO-here in the dominator-of-uses block.  Because golden's web
 *   occupies $f12 from 0x54, `var` is pushed to $f16; here `var` gets $f14 and
 *   every later FP temp rotates by one slot -> 48 register-only diff lines.
 *   CLASS: BASIC BLOCK (constant home block), with a downstream ALLOCATION
 *   consequence.  Nothing else differs: byte offsets realign at 0x124 and the
 *   whole tail is instruction-for-instruction identical.
 *
 * RULED OUT (each measured on the real differ, --max-lines 4096):
 *   2669  first cold draft (nested if/else for the 95.0f pick, plain
 *         if/else-if for the unk6F0/unk6F4 clamp)  -> framesize came out 0x48
 *   1490  `(A && B) ? 95.0f : unk348` + nested-ternary clamp; framesize 0x50
 *         EXACT.  All four zeros spelled 0.0f -> one shared web, so
 *         `arg0->unk25C = 0` and `var = 0` became swc1 $f12 / mov.s $f14,$f12
 *         instead of golden's separate mtc1 zero,$f8 / mtc1 zero,$f16.
 *    780  comparisons `!= 0.0f`, assignments `= 0`  <-- THIS FILE
 *    780  comparisons `!= 0`,    assignments `= 0.0f`   (mirror image; the
 *         binary only evidences "two independent zero webs", not which
 *         spelling sits on which side -- N-no-ops style tie)
 *   1490  comparisons `!= 0`,    assignments `= 0`      (webs re-merge)
 *   1025  comparisons `!= 0.0` (double)  -> c.eq.d / cvt.d.s appear
 *    780  `if (a != 0.0f) if (b != 0.0f)` nested instead of `&&`  (no change)
 *    780  dead `var = 0.0f;` as the first body statement (IDO deletes the
 *         store AND the constant node -> no hoist; hypothesis dead)
 *    822  `f32 zero;  zero = 0.0f;` local used as the comparison operand ->
 *         IDO constant-propagates it away, mtc1 still at J1, and the extra
 *         local pushed sp48/sp44 to 0x44/0x40
 *    780  extra `s32 flags = arg0->unk5F0;` declared first (GPR-only, neutral)
 *    785  `f32 sp48[2]` with &sp48[0] passed (offsets stay right, +5)
 *
 * CORPUS EVIDENCE (matched, live-C functions):
 *   game_176A00 func_1514BC08 -- three separate `x < 0.0f` tests each get
 *     their own `mtc1 zero,$fN` a few instructions before the compare, in the
 *     SAME basic block.  IDO does not share 0.0 across distant blocks.
 *   game_113480 func_150E5FD0 -- one `mtc1 zero,$f0` at instruction 4 shared
 *     by many later uses, but its FIRST source use (`sp94.unk34 = 0.0f;`) is
 *     already in the entry block.
 *   => IDO puts the constant in the block of its first ucode use.  For golden
 *   to have it at 0x54 there must be a 0.0f mention in the source before the
 *   `var = 95.0f / var = arg0->unk348` if/else that emits no extra
 *   instruction.  Not found; that is the open question.
 *
 * NOT TRIED (next wave): permuter seeded from this file; and mining the
 * corpus for a live-C function whose 0.0 constant is materialised in a
 * strictly earlier block than its first use.
 *
 * RODATA: -10000.0f (0xC61C4000, low16 != 0, NOT lui-able) is a compiler
 * literal pool.  asm/data/2481E0.rodata.s holds exactly one glabel
 * (D_800A3720) with .float payload and 12 bytes of zero padding, and the
 * symbol is referenced ONLY by func_1512E140.  Writing the literal makes the
 * object grow a .rodata section (golden's expected object has none); the ROM
 * link needs  - [0x2481E0, .rodata, game_15B5F0]  in conker/conker.us.yaml
 * plus splat --modes ld, exactly like the existing game_138520 (0x247780) and
 * game_1ED0F0 (0x24F480) float-pool lines.  Do NOT swap it for
 * `extern f32 D_800A3720` -- that is the measured-bad "fix a pool with an
 * extern" trap.
 * ===================================================================== */
