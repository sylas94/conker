/* func_150D5124  --  game_100810.c  --  199 insns / 796 bytes (+2 pad nops)
 *
 * STATUS: JUSTREG.  BEST 105, REPRODUCED THIS WAVE FROM A CLEAN BUILD.
 * (This function was previously parked only as a comment block inside
 *  conker/src/game_100810.c between the func_150D4D58 and func_150D5124 pragmas.
 *  That comment carried the C but not a compilable form and not the header work;
 *  this file supersedes it.  The 105 here is the SAME 105 -- independently rebuilt,
 *  not copied from the note.)
 *
 * Scored with: conker/ $ python3 ../tools/asm-differ/diff.py -o func_150D5124 -R --max-lines 4096
 *
 * THE RESIDUAL IS 100% REGISTER NAMING.  Every opcode, every immediate, every branch
 * polarity, every delay slot and the frame (addiu sp,sp,-0x18; sw ra,0x14(sp); no homed
 * locals at all) are already identical.  The only difference is that t6 and t7 are
 * exchanged, and the exchange starts at ONE instruction and then persists to the end of
 * the function.  Symbol-bounded word compare: 20 rows out of 199, all of the form
 * "same instruction, t6<->t7".
 *
 * WHERE IT STARTS -- the volume ramp at 0x180:
 *     0174  =  beq  a3,v1,JOIN            (volume == targetVolume -> skip)
 *     0178  =  slt  at,a3,v1
 *     017c  =  beqz at,ELSE
 *     0180  G  lui  t6,%hi(D_800BE9E4)    M  lui  t7,%hi(D_800BE9E4)   <- else's %hi, in the
 *     0184  =  lui  t5,%hi(D_800BE9E4)                                    delay slot
 *     0188  =  lw   t5,%lo(D_800BE9E4)(t5)
 *     018c  G  sll  t7,t5,0x8             M  sll  t6,t5,0x8
 *     0190  G  addu a3,a3,t7              M  addu a3,a3,t6
 *     ...
 *     01a8  G  lw   t6,%lo(D_800BE9E4)(t6) M lw  t7,%lo(D_800BE9E4)(t7)
 *     01ac  G  sll  t8,t6,0x8             M  sll  t8,t7,0x8
 *     01b0  =  subu a3,a3,t8
 *
 * So the four ramp temps are allocated in these orders:
 *     GOLDEN: t5 = then-load, t6 = else-load, t7 = then-shift, t8 = else-shift
 *             i.e. BOTH LOADS FIRST, then both shifts.
 *     IDO   : t5 = then-load, t6 = then-shift, t7 = else-load, t8 = else-shift
 *             i.e. depth-first, the whole then-block before the else-block.
 * t5 and t8 agree in both; only the middle two are exchanged, and every later temp pair
 * inherits the exchange (arg0-reload vs src->unk0 at 0x224/0x22c, and so on).
 *
 * WHAT IS CONFIRMED CORRECT AND MUST NOT BE "FIXED":
 *  - The volume ramp reads D_800BE9E4 TWICE (two lui/lw pairs, no CSE) while the pitch
 *    ramp reads it ONCE (one lw, hoisted into a delay slot, shared by both branches).
 *    That asymmetry is NOT a bug in the reconstruction -- this source reproduces both
 *    exactly.  It falls out of the shift amounts: the volume branches both shift by 8
 *    (identical whole expressions -> uopt hoists neither), the pitch branches shift by 8
 *    and by 3 (different expressions sharing one load -> uopt hoists the load).
 *  - Locals: 6 declared, NONE homed (framesize 0x18 is just the 0x10 arg-save area plus
 *    ra at 0x14).  The named-local register assignment already matches golden exactly:
 *    t1=src, t2=soundId, a3=volume, t0=pitch, v1=targetVolume, a1=targetPitch.  Do not
 *    reorder the declarations -- that is what puts them there.
 *  - Signature: 7 args, the last three passed on the stack at sp+0x28/0x2C/0x30.  arg2
 *    is never spilled to its home (a2 stays live), arg0/arg1/arg3 are.
 *
 * NEGATIVE RESULTS -- every one of these rebuilt clean and scored EXACTLY 105, i.e. no
 * effect whatsoever on the allocation:
 *     else branch spelled `volume -= D_800BE9E4 << 8;` (then keeps `* 256`)      105
 *     else branch spelled `volume = volume - D_800BE9E4 * 256;` (then compound)  105
 *     both branches spelled `256 * D_800BE9E4` (multiply operand order reversed) 105
 * Earlier negatives recorded in the in-TU comment, kept here so the comment can be
 * deleted:  `<<` vs `*` in both branches; compound vs plain RMW in both branches (110);
 * `a<b` vs `b>a` operand order on the clamps; `!=` guard vs a three-way `else if` (1055);
 * split vs chained `*arg4 = arg0->unk20 = pitch`.
 *
 * ALSO RULED OUT this wave by reading golden rather than building:
 *   - Swapping the two ramp branches (`if (volume >= targetVolume) { -= } else { += }`)
 *     is not it: golden's test is `slt at,a3,v1` + `beqz at,ELSE`, which pins the source
 *     to `if (volume < targetVolume) { += } else { -= }`.  The inverted spelling produces
 *     `bnez`, not `beqz`.
 *   - Replacing the outer `!=` guard with `else if` is not it: golden opens the ramp with
 *     `beq a3,v1,JOIN`, an explicit equality test, operands in that order.
 *
 * WHAT I WOULD TRY NEXT: this is a decomp-permuter job, not a hand job -- the search space
 * is "make IDO create the else-branch's load temp before the then-branch's shift temp",
 * and no ordinary source rearrangement reaches it.  tools/decomp-permuter is already set
 * up for ido (see the conker-permuter-setup memory); import this file and let it churn on
 * the two ramp blocks.  Do NOT ship anything that reaches 0 by splitting a value across
 * two variables purely for its register effect -- that is the banned construct that a
 * previous agent correctly refused at 685.
 */

#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern s8 D_8008FD8C;
extern void func_100111C8(u16);

typedef struct {
    struct127 *unk0;
    u8 pad4;
    u8 unk5;
} Src150D5124;

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    u8 pad8[4];
    s32 unkC;
    u8 pad10[8];
    Src150D5124 *unk18;
    s32 unk1C;
    s16 unk20;
    u8 pad22[2];
    u16 unk24;
} Snd150D5124;

/* NOTE FOR WHOEVER LANDS THIS: game_100810.c line 59 currently carries
       extern void func_150D5124(void);
   purely so func_150D4C2C can pass it to func_1000FD38 as a callback.  It has to be
   replaced by the real prototype (and the typedefs moved above func_150D4C2C), otherwise
   cfe errors with "redeclaration of 'func_150D5124' ... Incompatible function return
   type".  Doing that does not disturb the other functions in the TU. */

s32 func_150D5124(Snd150D5124 *arg0, s32 arg1, u32 *arg2, s32 arg3, s32 *arg4,
                  s32 arg5, u16 *arg6) {
    Src150D5124 *src;
    s32 soundId;
    s32 volume;
    s32 pitch;
    s32 targetVolume;
    s32 targetPitch;

    targetVolume = 0;
    targetPitch = 0;
    soundId = arg0->unk1C;
    src = arg0->unk18;
    volume = arg0->unkC;
    pitch = *arg4;

    if (soundId == 0x5B3) {
        if (src->unk0 != 0) {
            targetVolume = src->unk0->unk28 * 25.0f;
            if (targetVolume > 5000) {
                targetVolume = 5000;
            } else if (targetVolume < 500) {
                targetVolume = 0;
            }
            targetPitch += src->unk0->unk28 * 5.0f;
            if (targetPitch > 1000) {
                targetPitch = 1000;
            }
        }
        if (src->unk5 == 2) {
            targetVolume += 7000;
        } else if (src->unk5 == 1) {
            targetPitch = 400;
            targetVolume += 7000;
        } else {
            targetPitch = 400;
            if (targetVolume != 0) {
                volume = targetVolume;
            }
        }
    } else if (soundId == 0x5BC) {
        targetVolume = 24000;
        if (src->unk5 == 0) {
            volume = targetVolume;
        } else {
            targetVolume = 400;
        }
    } else if (soundId == 0x5B4) {
        if (src->unk5 == 0) {
            targetVolume = 16000;
            targetPitch = 400;
            volume = targetVolume;
        } else if ((src->unk5 == 1) || (D_8008FD8C >= 5)) {
            targetVolume = 12000;
        } else {
            targetPitch = 400;
        }
    }

    if (volume != targetVolume) {
        if (volume < targetVolume) {
            volume += D_800BE9E4 * 256;
            if (volume > targetVolume) {
                volume = targetVolume;
            }
        } else {
            volume -= D_800BE9E4 * 256;
            if (volume < targetVolume) {
                volume = targetVolume;
            }
        }
    }
    if (pitch != targetPitch) {
        if (pitch < targetPitch) {
            pitch += D_800BE9E4 * 256;
            if (pitch > targetPitch) {
                pitch = targetPitch;
            }
        } else {
            pitch -= D_800BE9E4 * 8;
            if (pitch < targetPitch) {
                pitch = targetPitch;
            }
        }
    }

    if (volume < 500) {
        volume = 0;
    } else if (*arg6 == 0) {
        arg0->unk0 = soundId;
        *arg6 = soundId;
    }

    arg0->unk2 = src->unk0->x_position;
    arg0->unk4 = src->unk0->y_position;
    arg0->unk6 = src->unk0->z_position;

    if (D_800C35EA == 1) {
        arg0->unkC = volume >> 1;
        *arg2 = *arg2 >> 1;
    } else {
        arg0->unkC = volume;
    }
    *arg4 = arg0->unk20 = pitch;

    if (*arg2 == 0) {
        if (arg0->unk24 != 0) {
            func_100111C8(arg0->unk24);
            arg0->unk24 = 0;
        }
        *arg6 = 0;
    }
    return 0;
}
