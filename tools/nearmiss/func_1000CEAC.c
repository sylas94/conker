/* ===========================================================================
 * func_1000CEAC  --  init_B1B0.c  (1100 B, -O2 -g3, no OPT_FLAGS override:
 * Makefile line 160 `init_B1B0.o: OPT_FLAGS := -O2` is COMMENTED OUT, and the
 * $(BUILD_DIR)/$(SRC_DIR)/init_B1B0.c.o rule is not overridden anywhere, so the
 * global -O2 -g3 applies.  Verified: pragma-in build scores 0.)
 *
 * BEST SCORE 2710 (with -R and without -R, identical).  Cold start was 7660.
 * Structure is essentially byte-for-byte: the residual is almost entirely
 * ALLOCATION (different s-registers / t-registers), plus 8 bytes of frame and
 * three isolated scheduling/peephole rows listed at the bottom.
 *
 * ---------------------------------------------------------------------------
 * WHAT THE FUNCTION IS
 * ---------------------------------------------------------------------------
 * Per-player (arg0 in 0..2) audio "message pump".  Drains the player's
 * OSMesgQueue D_80041E58[arg0]; each message is a bitfield:
 *      bit 4        -> "this is a note/tick message"
 *      bits 0..2    -> channel index (0..7); < 2 means it also carries a clock
 *      bits 5..     -> a signed timestamp (msg >> 5)
 * For a tick message it looks up a 16-bit voice mask ((u16*)p->unkC)[chan] and
 * walks the 16 bits; for each set bit it dispatches on ((s32*)p->unk8)[i]
 * (0 / 1 / 2 / default) to poke the D_800417C0 / D_800418B0 / D_80041970
 * per-voice tables.  After the drain it toggles the player's mute state via
 * func_10008F58 / func_100084D8 and decays all 16 D_800418B0 timers by
 * D_800417C0[arg0][i] * D_800BE9E4 (dt), clamping at 0.
 *
 * ---------------------------------------------------------------------------
 * DATA LAYOUT DECODED OFF THE GOLDEN ADDRESSING (contiguous, exact)
 * ---------------------------------------------------------------------------
 *   D_800417C0  s32[3][16]  base + (n<<6) + i*4      ends 0x80041880
 *   D_80041880  s32[3]      base + (n<<2)            ends 0x8004188C
 *   D_80041890  s32[3]      base + (n<<2)            ends 0x8004189C
 *   D_800418A0  s32[3]      %hi/%lo + (n<<2)         ends 0x800418AC
 *   D_800418AC  u8[3]       base + n     (variables.h already)
 *   D_800418B0  s32[3][16]  base + (n<<6) + i*4  (variables.h has s32[])
 *   D_80041970  u8[3][16]   base + (n<<4) + i        ends 0x800419A0
 *   D_800419A0  u8          (variables.h already)     <- the block closes exactly
 * The fact that D_80041970's end lands exactly on D_800419A0 is the proof the
 * [3][16] shapes are right.
 *
 * ---------------------------------------------------------------------------
 * FRAME DECODE (golden 0x98, this file 0xa0 -- 8 bytes too big)
 * ---------------------------------------------------------------------------
 *   0x00-0x17  arg build (func_1507E7E4 takes 5 args -> arg5 at 0x10)
 *   0x20-0x44  saved s0,s1,s2,s3,s4,s5,s6,s7,fp,ra
 *   0x48-0x8B  compiler temps.  Golden's live spill slots: 0x58 (the
 *              &D_800418B0[arg0*16] pointer across the two calls), 0x64
 *              (&D_80041E58[arg0]), 0x68 (&D_800418AC[arg0]), 0x70
 *              (&D_800417B0[arg0]), 0x80 (p->unkC).
 *   0x8C-0x97  local home area, 12 bytes = 3 words, TOP-DOWN in declaration
 *              order:  [0x94] first-declared, [0x90] second, [0x8C] third.
 *              0x94 = the OSMesg (its address is passed to osRecvMesg).
 *              0x90 = never touched (register-resident; see sp90 below).
 *              0x8C = the "vol" local: `lw s0,0x8c(sp)` in the loop preheader
 *                     and `sw s0,0x8c(sp)` on loop exit, and NEVER stored
 *                     before the load -- i.e. GOLDEN READS IT UNINITIALISED
 *                     when the first message is not a chan<2 tick.  That is an
 *                     original-game bug and is reproduced here (sp8C is only
 *                     assigned inside `if (chan < 2)`), NOT to be "fixed".
 *
 * MEASURED marginal cost of a declared local in this function (each a separate
 * single-variable build):
 *   remove `s32 *timers` (tail-loop pointer)      frame 0xa8 -> 0xa0, 6320->3360
 *   remove `struct151 *p`                          frame 0xa0 -> 0xa0, 2765->2769
 *   add    `s32 raw`                               frame 0xa0 -> 0xa8, 2765->2910
 *   remove `s32 sp90`                              frame 0xa0 -> 0xa0, 2765->3219
 * So the frame is NOT a simple count of declared autos: pure register-resident
 * pointers (p) cost 0, but a local that acquires a spill temp costs 8.  The
 * remaining 8 bytes are ONE surplus compiler temp slot, not a surplus auto.
 * Golden's temp slots sit at 0x58/0x64/0x68/0x70/0x80; this file's at
 * 0x54/0x68/0x70/0x74/0x8c -- same COUNT (5), different numbering.
 *
 * ---------------------------------------------------------------------------
 * LEVERS THAT PAID (each verified by a single-variable build)
 * ---------------------------------------------------------------------------
 *  7660 base draft
 *  6320  `u32 chan` instead of `s32 chan`      -> golden's `sltiu at,v1,2`
 *        + `chan = msg & 7` hoisted ABOVE `if (msg & 0x10)`  (golden computes
 *          `andi v1,v0,7` before `andi t4,v0,0x10`)
 *        + `sp8C = 0x514` written FIRST in the chan<2 block (golden's
 *          `li s0,0x514` precedes the `beqz a0` on D_80041890[arg0])
 *        + `sp90` introduced to hold `(s32)msg >> 5` once (golden has ONE
 *          `sra t5,v0,5` + `move v0,t5`; without the local IDO emits TWO sra)
 *  3360  delete the `timers` local, index D_800418B0_2D[arg0][i] directly.
 *        This alone made the ENTIRE tail loop match instruction-for-
 *        instruction (including golden's `sw t0,0x58(sp)` spills of the
 *        &D_800418B0[arg0*16] pointer around both calls).
 *  2765  put the `for` loop INSIDE `if (mask != 0)` rather than as a sibling.
 *        Golden's first `beqz v1` jumps straight to the D_800419A0 store, and
 *        `move a2,zero` (i = 0) sits INSIDE the mask!=0 block at 1e44.
 *  2710  test the ARRAY EXPRESSION and assign the variable inside:
 *            if (ptrC[chan] != 0) { mask = ptrC[chan]; ... }
 *        instead of `mask = ptrC[chan]; if (mask != 0)`.  This is what makes
 *        IDO emit golden's `andi v0,v1,0xffff`: with two uses the CSE temp for
 *        ptrC[chan] is int-typed, so storing it into the u16 `mask` truncates.
 *        The single-assignment form emits a bare `move` and is 55 points worse.
 *
 * RULED OUT (each measured):
 *   `s32 raw; raw = ptrC[chan]; if (raw) { mask = raw; ... }`          2910
 *   inline `(s32)sp94 >> 5` everywhere instead of the sp90 local        3219
 *   inline `D_800417B0[arg0]` instead of the `p` local                  2769
 *   `s32 chan` (signed)                                     (part of the 7660)
 *
 * ---------------------------------------------------------------------------
 * RESIDUAL AT 2710 -- classify: ALLOCATION dominates
 * ---------------------------------------------------------------------------
 * (a) ALLOCATION.  Golden's callee-saved map is
 *        s0=vol  s1=0x8000  s2=arg0  s3=&D_800418B0  s4=&D_800BE9E4
 *        s5=2    s6=ptr8    s7=1     fp=arg0<<2
 *     this file gets s5=ptr8, s6=1, s7=&D_800BE9E4 (s4 unused for that web).
 *     Every t-register in the switch bodies then renames in lockstep; that is
 *     where the bulk of the 2710 lives.  IDO ranks webs by defs+uses; the two
 *     maps differ by exactly one web, so ONE more (or one fewer) compiler temp
 *     in the mask block should snap the whole map into place.
 * (b) SCHEDULING, 1 row: golden fills the `jal osRecvMesg` delay slot with
 *     `sw t7,0x80(sp)` (the p->unkC spill) and puts `move a2,zero` before the
 *     jal; this file spills p->unkC early at 1d5c and puts `move a2,zero` in
 *     the delay slot.  Same instructions, swapped.
 * (c) SCHEDULING/BASIC BLOCK, 2 rows in the `default:` arm: golden emits
 *        sb t3,0(v0) / mflo t5 / sw t5,0(t6) / b .L1000D130 / sw s0,0(a3)
 *     this file emits the `sw s0,0(a3)` (D_800417C0[arg0][i] = vol) BEFORE the
 *     mflo, which frees the branch delay slot, so IDO branches past the loop
 *     increment and DUPLICATES `addiu a2,a2,1` into the delay -> one extra
 *     instruction.  Only the default arm does this; case 0/1/2 all match.
 * (d) as1 PEEPHOLE, loop back edge.  Golden:
 *        slti at,a2,0x10 ; beqz at,exit ; move v0,t3 ; bnezl t3,.L1000D008 ;
 *        andi t8,v0,0x1            <- the loop's first insn duplicated in the
 *                                     branch-likely delay slot, so the loop
 *                                     head is the `beqz t8` at .L1000D008
 *     this file:
 *        slti at,a2,0x10 ; beqz at,exit ; andi t9,v0,0xffff ; bnez t9,head ;
 *        move t9,...               <- head is the `andi`, no branch-likely
 *     Golden also orders `mask >>= 1` (srl+andi) BEFORE the `slti`; this file
 *     interleaves the slti first.
 * (e) `li a2,1` (golden) vs `move a2,s6` (here) for the third argument of
 *     func_1507E7E4 -- this file's constant-1 web reaches the call site and is
 *     reused; golden's does not.  Downstream of (a).
 *
 * NEXT MOVES if picked up: (1) find the one extra/missing compiler temp in the
 * mask block -- that is the single cause behind (a) and the 8 frame bytes;
 * (2) try `default:` written LAST in the switch (the emitted block order
 * default,case0,case1,case2 is reproduced by `default:` FIRST, which is what is
 * written here, but the WEB NUMBERING may differ); (3) permuter seeded with
 * this file (it is hand-reduced, which is the condition under which the
 * permuter has been decisive here).
 * =========================================================================== */

#include <ultra64.h>

#include "functions.h"
#include "variables.h"

extern s32 D_800417C0[3][16];
extern s32 D_80041880[3];
extern s32 D_80041890[3];
extern s32 D_800418A0[3];
extern u8 D_80041970[3][16];
extern void func_1507E7E4(void *, s32, s32, s32, s32);

#define D_800418B0_2D ((s32 (*)[16])D_800418B0)

void func_1000CEAC(s32 arg0) {
    OSMesg sp94;
    s32 sp90;
    s32 sp8C;
    struct151 *p;
    u16 *ptrC;
    s32 *ptr8;
    u32 chan;
    s32 i;
    u16 mask;

    p = D_800417B0[arg0];
    if (p == NULL) {
        return;
    }
    ptrC = (u16 *)p->unkC;
    ptr8 = (s32 *)p->unk8;
    D_800418AC[arg0] = 0;

    while (osRecvMesg(&D_80041E58[arg0], &sp94, 0) == 0) {
        chan = (s32)sp94 & 7;
        if (((s32)sp94 & 0x10) != 0) {
            if (chan < 2) {
                sp8C = 0x514;
                sp90 = (s32)sp94 >> 5;
                if (D_80041890[arg0] != 0) {
                    D_800418A0[arg0] = sp90 - D_80041890[arg0];
                }
                D_80041890[arg0] = sp90;
                D_80041880[arg0] = sp90;
                sp94 = (OSMesg)sp90;
            }
            if (ptrC[chan] != 0) {
                mask = ptrC[chan];
                D_800418AC[arg0] |= mask & 0x7F;
                for (i = 0; (i < 16) && (mask != 0); i++) {
                    if ((mask & 1) != 0) {
                        switch (ptr8[i]) {
                        default:
                            D_80041970[arg0][i] |= 1;
                            D_800418B0_2D[arg0][i] = sp8C * D_800BE9E4;
                            D_800417C0[arg0][i] = sp8C;
                            break;
                        case 0:
                            D_80041970[arg0][i] ^= 1;
                            D_800418B0_2D[arg0][i] = 0x8000;
                            D_800417C0[arg0][i] = sp8C;
                            break;
                        case 1:
                            sp8C >>= 1;
                            D_80041970[arg0][i] ^= 1;
                            if (D_80041970[arg0][i] == 0) {
                                D_800418B0_2D[arg0][i] = (sp8C * D_800BE9E4) + 0x8000;
                            }
                            D_800417C0[arg0][i] = sp8C;
                            break;
                        case 2:
                            D_80041970[arg0][i & 7] ^= 1;
                            D_80041970[arg0][i | 8] = D_80041970[arg0][i & 7] ^ 1;
                            D_800418B0_2D[arg0][i & 7] = 0x8000;
                            D_800418B0_2D[arg0][i | 8] = 0x8000;
                            D_800417C0[arg0][i] = 0;
                            break;
                        }
                    }
                    mask >>= 1;
                }
            }
            D_800419A0 = arg0;
        } else if ((D_80041F04 & 1) != 0) {
            func_1507E7E4(D_800CC2D0, 0x44, 1, 0x12, 5);
        }
    }

    p = D_800417B0[arg0];
    if (p->unk30 == 0) {
        D_800418AC[arg0] |= 0x80;
        if (p->unk15 == 0) {
            func_10008F58((u8)arg0);
            D_800417B0[arg0]->unk15 = 1;
        }
    } else if (p->unk15 == 1) {
        func_100084D8((u8)arg0);
        D_800417B0[arg0]->unk15 = 0;
    }
    for (i = 0; i < 16; i++) {
        if (D_800418B0_2D[arg0][i] != 0) {
            D_800418B0_2D[arg0][i] -= D_800417C0[arg0][i] * D_800BE9E4;
            if (D_800418B0_2D[arg0][i] < 0) {
                D_800418B0_2D[arg0][i] = 0;
            }
        }
    }
}
