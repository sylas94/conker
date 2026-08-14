/* func_1501BBB8  --  game_48FD0.c  --  278 insns / 1112 bytes  --  COLD DECOMPILE
 *
 * BASELINE: pragma (no C at all).   BEST THIS WAVE: 6520.
 * Scored with: conker/ $ python3 ../tools/asm-differ/diff.py -o func_1501BBB8 -R --max-lines 4096
 * (the object tail after this symbol is verified 0 at the pragma baseline, so the whole-tail
 *  score is a valid gradient; a strict symbol-bounded word compare is run alongside it).
 *
 * WHAT IT IS: the per-frame controller poll.  Latches the previous frame's buttons into
 * D_800BE718, blocks on the SI message queue, reads the four OSContPads, zeroes any pad whose
 * errno is set while building the "controller present" bitmask D_800BE740, remaps pad->player
 * through D_80084060, ORs in the queued/synthetic buttons from D_800BE720, computes the two
 * newly-pressed masks (D_800BE930 from D_800BE708, D_800BE710 from D_800BE700) and applies an
 * 8-unit stick dead zone (subtracting 7 with the sign of the axis).  Returns &D_800BE730,
 * which the caller stores: game_45B80.c  `*D_800BE728 = func_1501BBB8();`
 *
 * ======================= WHAT IS SETTLED (do not re-derive) =======================
 *
 * FRAME.  framesize 0x60.  pads[4] lives at sp+0x38, so exactly 16 bytes of scalars are
 * declared BEFORE it; `held` is spilled to 0x54 across the func_151DD8C0 call, i.e.
 * ordinal (0x60-0x54)/4 = 3, so it is the THIRD declaration.  Locals declared AFTER pads are
 * not pinned by the frame law, but the TOTAL footprint is: 7 scalars + pads[4] = 52 bytes is
 * what reproduces framesize 0x60 (measured).  The declaration order below is the one that puts
 * pads at 0x38 and held at 0x54 and must not be shuffled.
 *
 * THE MIDDLE LOOP IS PAIRED IN SOURCE, NOT COMPILER-UNROLLED.  It steps i by 2 and handles
 * players i and i+1 per iteration (dst pointer +0xC, D_80084060 pointer +2).  PROOF that this
 * is source and not an unroller: the other three loops in this same function are also 4-trip
 * and are NOT unrolled.  Also measured, all no-ops on the instruction count (248 either way):
 *     LOOP_UNROLL=-Wo,-loopunroll,2 / ,200 / bare   -> 248 insns (flag accepted, no effect)
 *     LOOP_UNROLL=-Wo,-nounroll                     -> "uopt: Warning: unrecognized option"
 *     OPT_FLAGS=-O2 -> 247,  -O1 -> 460,  -g -> 487  (none unroll; -O3 is rejected by
 *                                                     asm_processor, which needs -O0/-O1/-O2/-g)
 * The second half's guard is spelled `i < n - 1` (golden: addiu t9,t3,-1 / slt at,a3,t9).
 * Writing the equivalent `i + 1 < n` instead makes IDO compute i+1 and compare -- wrong.
 * The loop exit is `i != 4` (golden: bne a3,t4 with 4 in a register); `i < 4` gives slti/bnez.
 *
 * LOOP BOUNDS ARE SPELLED WITH THE *NEXT* SYMBOL.  Golden bounds three loops with
 * %hi/%lo(D_800BE760), (D_800BE930) and (D_800BE708) -- addend 0 -- where the natural
 * `i < 4` gives %hi/%lo(D_800BE748)+24, (D_800BE918)+24, (D_800BE700)+8.  The linked words are
 * IDENTICAL (all four are absolute linker-script symbols, and base+24 == the next symbol), but
 * the *object* relocation differs, so expected/ can only be matched by naming the end symbol.
 * In the original these were statics with section-relative relocs; splat resolved the final
 * address to the symbol sitting there.  Each loop also has to be a do/while: written as a `for`
 * with the address bound, IDO emits an entry GUARD that golden does not have.
 *
 * MEASURED PROGRESSION (each step a separate build):
 *     first draft, pads declared first                                    10514
 *     pads moved to 5th declaration (pads lands at 0x38, offsets match)   10200
 *     loop 0 bound -> `for (i=0; &D_800BE748[i] < (OSContPad*)D_800BE760;` 11555  (adds a guard)
 *     loop 0 bound -> do/while with the same address bound                10190  (exact match)
 *     middle loop paired in source                                        10230
 *     `i != 4` + `i < n - 1`                                               9195
 *     n via `n = 4; if (D_800BE9F0 != 0x1D) n = D_8008FD90;` (not a
 *        ternary -- golden hoists the 4 and uses `beq ... join`)
 *        + then-branch order stick_x, stick_y, button, |=, clear           8920
 *     loops 2 and 3 -> do/while with end-symbol bounds, and the four
 *        dead-zone tests flipped to `if (abs >= 8) compute else 0`
 *        (golden: slti at,v0,8 then bnez at -> the ZERO store)             6520   <= parked
 *     held written as if/else instead of `held = 0;` first                 6325   but the frame
 *        regresses: &pads[0] moves into s0, sp -0x60 -> -0x68.  NOT parked; the frame is worth
 *        more than the 195.  Golden puts `move t1,zero` in a bnel likely-slot, so the else form
 *        IS right -- it only becomes affordable once the register pressure below is fixed.
 *
 * ======================= THE ONE OPEN BLOCKER =======================
 *
 * The four `D_800BE740 |= K;` sites.  Golden, per site:
 *      lbu  t9, 0x0(v0)                 <- v0 = &D_800BE740, built at the top and live
 *      lui  at, %hi(D_800BE740)
 *      ori  t6, t9, 0x1
 *      sb   t6, %lo(D_800BE740)(at)
 * i.e. the LOAD uses the CSE'd base register but the STORE is emitted symbolically.  Every
 * spelling I can produce reuses the base for the store too (3 instructions, not 4), so I am
 * 4 instructions short and everything downstream is shifted by 4, which is most of the residual
 * 6520 and is very likely also what pushes &pads[0] into s0 (golden rematerialises
 * `addiu t5,sp,0x38` after the calls; mine has 4 fewer instructions of distance and CSEs it
 * across them into a callee-saved register, which is the only reason the frame is 8 too big).
 *
 * NEGATIVE RESULTS, all built with the project's exact IDO flags via a standalone probe
 * (-O2 -g3 -mips2 -o32).  EVERY ONE of these emitted `sb rt,0(base)` -- none produced the
 * `lui at` form while a base register for the symbol was live:
 *     D_800BE740 |= K;                                  (baseline)
 *     D_800BE740 = D_800BE740 | K;                      (also tried in the real TU: identical)
 *     array spelling: extern u8 A[]; A[0] = 0; A[0] |= K;
 *     read hoisted into an int local: t = G; G = t | K;  (IDO then hoists the load out entirely)
 *     G = *(u8 *)&G | K;                                (cast on the READ)
 *     *(u8 *)&G = G | K;                                (cast on the STORE)
 *     struct member at offset 0: S.f = 0; S.f |= K;
 *     s32-typed global instead of u8
 *     OR of a variable instead of a constant
 *     the `= 0` moved after the four blocks
 *     u8 *f = &G; *f = 0; ... G |= K;    and    ... G = *f | K;    and    ... *f |= K;
 *     extern volatile u8 G;                             (still 0(base) for the store)
 * So the difference is NOT the |= spelling, NOT the width, NOT volatile, NOT the cast, and NOT
 * the position of the zeroing store.  Whatever it is lives in how the ORIGINAL TU DECLARED this
 * byte.  NEXT PERSON: this is the whole ballgame -- fix these 4 instructions and re-measure
 * before touching anything else, because the register allocation downstream is almost certainly
 * knock-on.  Do not chase the a2-vs-a1 / t5-vs-t4 register names until it is fixed.
 *
 * REMAINING SMALL ITEMS once that is solved:
 *   - loop-0 source pointer is a2 in golden, a1 here (pure allocation).
 *   - then-branch of the middle loop: golden schedules the D_800BE720[port]=0 clear into the
 *     `b` delay slot and stores stick_y third; mine puts stick_y in the delay slot.  Same
 *     source order, different scheduling -- expected to fall out with the 4-instruction fix.
 *   - `held` should end up in t1 + a spill to its home at 0x54, not in s0.
 */

#include <ultra64.h>
#include "functions.h"
/* variables.h types D_800BE748 as u16[]; it is really the four-entry OSContPad array
   that osContGetReadData latches into, so the TU needs the file-local shadow: */
#define D_800BE748 D_800BE748_u16_decl_in_variables_h
#include "variables.h"
#undef D_800BE748
extern OSContPad D_800BE748[];

extern u16 D_800BE700[];
extern u16 D_800BE708[];
extern u16 D_800BE718[];
extern u8 D_800BE740;
extern OSContPad D_800BE918[];
extern u16 D_800BE930[];
extern u8 D_800E0B95;
void func_1501C57C(void);
void func_151DD8C0(void);

struct14 *func_1501BBB8(void) {
    s32 i;
    s32 n;
    s32 held;
    s32 port;
    OSContPad pads[4];
    s32 btn;
    s32 sx;
    s32 sy;

    i = 0;
    do {
        D_800BE718[i] = D_800BE748[i].button;
        i++;
    } while (&D_800BE748[i] < (OSContPad *)D_800BE760);

    osRecvMesg(&D_800BE900, &D_800BE990, OS_MESG_BLOCK);
    osContGetReadData(pads);
    func_1501C57C();

    D_80084064 = 1;
    D_800BE740 = 0;
    if (pads[0].errno != 0) {
        pads[0].button = 0;
        pads[0].stick_x = 0;
        pads[0].stick_y = 0;
    } else {
        D_800BE740 |= 1;
    }
    if (pads[1].errno != 0) {
        pads[1].button = 0;
        pads[1].stick_x = 0;
        pads[1].stick_y = 0;
    } else {
        D_800BE740 |= 2;
    }
    if (pads[2].errno != 0) {
        pads[2].button = 0;
        pads[2].stick_x = 0;
        pads[2].stick_y = 0;
    } else {
        D_800BE740 |= 4;
    }
    if (pads[3].errno != 0) {
        pads[3].button = 0;
        pads[3].stick_x = 0;
        pads[3].stick_y = 0;
    } else {
        D_800BE740 |= 8;
    }

    n = 4;
    if (D_800BE9F0 != 0x1D) {
        n = D_8008FD90;
    }

    for (i = 0; i != 4; i += 2) {
        port = D_80084060[i];
        if ((port < 4) && (i < n)) {
            D_800BE748[i].stick_x = pads[port].stick_x;
            D_800BE748[i].stick_y = pads[port].stick_y;
            D_800BE748[i].button = pads[port].button;
            D_800BE748[i].button |= D_800BE720[port];
            D_800BE720[port] = 0;
        } else {
            D_800BE748[i].button = 0;
            D_800BE748[i].stick_x = 0;
            D_800BE748[i].stick_y = 0;
        }
        port = D_80084060[i + 1];
        if ((port < 4) && (i < n - 1)) {
            D_800BE748[i + 1].stick_x = pads[port].stick_x;
            D_800BE748[i + 1].stick_y = pads[port].stick_y;
            D_800BE748[i + 1].button = pads[port].button;
            D_800BE748[i + 1].button |= D_800BE720[port];
            D_800BE720[port] = 0;
        } else {
            D_800BE748[i + 1].button = 0;
            D_800BE748[i + 1].stick_x = 0;
            D_800BE748[i + 1].stick_y = 0;
        }
    }

    i = 0;
    do {
        btn = D_800BE748[i].button;
        D_800BE930[i] = ~D_800BE708[i] & btn;
        D_800BE918[i].button = btn;
        D_800BE708[i] = btn;
        sx = D_800BE748[i].stick_x;
        if (((sx < 0) ? -sx : sx) >= 8) {
            D_800BE918[i].stick_x = sx - ((sx < 0) ? -1 : 1) * 7;
        } else {
            D_800BE918[i].stick_x = 0;
        }
        sy = D_800BE748[i].stick_y;
        if (((sy < 0) ? -sy : sy) >= 8) {
            D_800BE918[i].stick_y = sy - ((sy < 0) ? -1 : 1) * 7;
        } else {
            D_800BE918[i].stick_y = 0;
        }
        i++;
    } while (&D_800BE918[i] < (OSContPad *)D_800BE930);

    held = 0;
    if ((D_800E0B94 == 2) || (D_800E0B95 == 2)) {
        held = 1;
        func_151DD8C0();
    }

    i = 0;
    do {
        btn = D_800BE748[i].button;
        D_800BE710[i] = ~D_800BE700[i] & btn;
        D_800BE700[i] = btn;
        if (held == 0) {
            sx = D_800BE748[i].stick_x;
            if (((sx < 0) ? -sx : sx) >= 8) {
                D_800BE748[i].stick_x = sx - ((sx < 0) ? -1 : 1) * 7;
            } else {
                D_800BE748[i].stick_x = 0;
            }
            sy = D_800BE748[i].stick_y;
            if (((sy < 0) ? -sy : sy) >= 8) {
                D_800BE748[i].stick_y = sy - ((sy < 0) ? -1 : 1) * 7;
            } else {
                D_800BE748[i].stick_y = 0;
            }
        }
        i++;
    } while (&D_800BE700[i] != (u16 *)D_800BE708);
    return &D_800BE730;
}
