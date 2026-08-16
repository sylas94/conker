/* ===========================================================================
 * func_1000CEAC  --  init_B1B0.c  (1100 B, -O2 -g3, no OPT_FLAGS override:
 * Makefile line 160 `init_B1B0.o: OPT_FLAGS := -O2` is COMMENTED OUT and the
 * $(BUILD_DIR)/$(SRC_DIR)/init_B1B0.c.o rule is not overridden anywhere, so the
 * global -O2 -g3 applies.  Verified this session: pragma-in build scores 0.)
 *
 * BEST SCORE 2141 (with -R and without -R, identical).  Cold start 7660;
 * previous park 2710; this session 2710 -> 2259 -> 2141.
 * **THE FRAME NOW MATCHES GOLDEN EXACTLY (0x98).**  The stack-offset multiset
 * differs from golden in ONE slot only (see below).  Everything that is left is
 * one register-allocation rotation and its three scheduling consequences.
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
 * MEASURED NEUTRAL: giving D_800418B0 its true `s32[3][16]` type with the
 * file-local header-shadow idiom scores EXACTLY the same as the cast macro
 * below, so the cast costs nothing.  Flat `D_800418B0[(arg0*16)+i]` is worse.
 *
 * ===========================================================================
 * THE FRAME IS SOLVED -- READ THIS BEFORE TOUCHING THE DECLARATION LIST
 * ===========================================================================
 * The old park was stuck at frame 0xa0 vs golden's 0x98 and called the surplus
 * "one extra compiler temp".  IT IS NOT.  It is the LOCAL HOME AREA, and the
 * count is readable straight off golden:
 *
 *   frame = arg-build 0x18 + pad 8 + saved regs 0x28  (= 0x48)
 *         + compiler temps (52 bytes here)
 *         + 4 * (number of declared locals)      <- rounded up to 8
 *
 *   golden 0x98 = 0x48 + 52 + 28   ->  SEVEN declared locals
 *   old    0xa0 = 0x48 + 52 + 36   ->  nine
 *
 * PROVEN, not inferred.  Two independent measurements:
 *  (a) the home area is laid out TOP-DOWN in DECLARATION ORDER ending at
 *      framesize, and a spilled local is spilled TO ITS OWN HOME.  Moving
 *      `ptrC` from declaration position 6 to position 5 moved its spill slot
 *      from 0x88 to 0x8c -- exactly framesize-4*position.  Golden spills ptrC
 *      to 0x80 with framesize 0x98, i.e. 0x98-0x18: **ptrC is golden's SIXTH
 *      declared local**.  That pins the list.
 *  (b) dropping locals one at a time walks the frame down in 4-byte steps
 *      (visible only every other step because of the 8-byte rounding):
 *          9 locals  0xa0     8 locals  0xa0 (0x9c rounded)     7 locals  0x98
 *      measured with three different pairs of deletions, all giving 0x98.
 *
 * So golden's declaration list is exactly SEVEN entries with ptrC sixth:
 *      1 sp94 (OSMesg; its address goes to osRecvMesg)   home 0x94
 *      2 (register-resident, home never touched)         home 0x90
 *      3 sp8C  = the "vol" local (s0, spilled/reloaded)  home 0x8c
 *      4 (register-resident)                             home 0x88
 *      5 (register-resident)                             home 0x84
 *      6 ptrC  = (u16 *)p->unkC, SPILLED here            home 0x80
 *      7 (register-resident)                             home 0x7c
 * Since `mask` and `i` are simultaneously live they cannot be one variable, and
 * ptr8 must be a local (golden holds it in s6 across osRecvMesg), so the only
 * arrangement that fits is: NO `p` local (index D_800417B0[arg0] directly, 4
 * loads, which is what golden emits) and NO separate `chan` -- **`chan` and the
 * loop counter `i` are THE SAME VARIABLE**.  That is independently corroborated
 * by golden's `move a2,v1` (chan copy) and `move a2,zero` (i = 0) using the SAME
 * register a2; with a separate `chan` we emitted a3 there, and the merge snapped
 * it to a2.  The merge needs one signedness cast, because golden compares the
 * channel UNSIGNED (`sltiu at,v1,2`) and the loop bound SIGNED (`slti
 * at,a2,0x10`).  All four spellings -- `(u32)i < 2`, `i < 2U`, `(u32)i <= 1`,
 * and `u32 i` with `(s32)i < 16` in both loops -- score IDENTICALLY 2141, so the
 * binary cannot choose between them; `(u32)i < 2` is written below.
 *
 * The six declaration orders that keep ptrC sixth (permuting ptr8/i/mask over
 * positions 4,5,7) ALL score 2141; positions 4/5/7 are never-touched homes, so
 * the binary cannot distinguish them either.  ptrC at position 5 costs 8.
 *
 * ---------------------------------------------------------------------------
 * WHAT IS LEFT, AND THE ONE CAUSE BEHIND ALL OF IT
 * ---------------------------------------------------------------------------
 * The stack-offset multiset now differs from golden in ONE displacement:
 *      golden spills t0 (&D_800418B0[arg0*16]) around the two mute calls to
 *      0x58 = compiler-temp slot #4;  we use 0x54 = slot #3.
 * i.e. GOLDEN HAS EXACTLY ONE MORE COMPILER TEMP THAN WE DO, numbered before
 * that one.  The same single missing web explains every remaining diff:
 *
 * (1) CALLEE-SAVED ROTATION
 *        golden  s3=&D_800418B0  s4=&D_800BE9E4  s5=2  s6=ptr8  s7=1
 *        ours    s3=&D_800418B0  s4=2  s5=ptr8  s6=1  s7=&D_800BE9E4
 *     Defs+uses counted on BOTH sides -- identical:
 *        &D_800418B0 1+3=4   &D_800BE9E4 1+2=3   2 1+1=2  ptr8 1+1=2  1 1+1=2
 *     (&D_800BE9E4 and the constant 1 are each TWO disjoint webs; the tail loop
 *     re-materialises them at 0x2008/0x201c because the "first osRecvMesg
 *     failed" path bypasses the preheader.)
 *     Golden's s3..s7 order is 4,3,2,2,2 = MONOTONE DESCENDING, exactly what the
 *     project's "IDO ranks webs by defs+uses" law predicts.  OURS is 4,2,2,2,3 --
 *     a 3-reference web placed below three 2-reference webs.  OUR map is the
 *     one unreachable from the counts, not golden's.
 * (2) THE SAME PATHOLOGY IN THE CALLER-SAVED SET, in BOTH loops:
 *        message loop  golden msg=v0 chan=v1 chancopy=a2 mask=v0 ACptr=t2
 *                      ours   msg=t0 chan=v0 chancopy=a2 mask=t1 ACptr=t3
 *        tail loop     golden cursor=v0 offset=v1 value=a0 base=a1 limit=a2
 *                      ours   value=v0  offset=v1 base=a0  limit=a1 cursor=t2
 *     In each loop the MOST-REFERENCED web (msg / mask / the strength-reduced
 *     cursor, 5..8 refs) takes v0 in golden and is demoted to a t-register in
 *     ours, and everything else slides up one rank.  Again not reachable from
 *     defs+uses.
 * (3) DOWNSTREAM, DO NOT CHASE SEPARATELY.  Golden's `move t1,v0` at 0x1e5c is
 *     the allocator splitting mask out of the clobbered v0 -- one extra
 *     instruction (we are 1096 bytes to golden's 1100).  Without it our
 *     `default:` arm starts 4 bytes earlier, the multu->mflo gap gains a slot,
 *     the scheduler pulls `sw s0,0(a3)` in as filler, the branch delay slot is
 *     then free and as1 duplicates `addiu a2,a2,1` into it.  The same free
 *     back-edge delay slot is what lets golden's as1 emit the branch-likely
 *     `bnezl t3,.L1000D008 / andi t8,v0,0x1` and order the `srl`/`andi` before
 *     the `slti`.  All three are consequences of (2).
 *
 * ---------------------------------------------------------------------------
 * LEVERS THAT PAID
 * ---------------------------------------------------------------------------
 *  7660 base draft
 *  6320  `u32 chan`; `chan = msg & 7` hoisted above `if (msg & 0x10)`;
 *        `sp8C = 0x514` written first in the chan<2 block; `sp90` local
 *  3360  delete the `timers` local, index D_800418B0_2D[arg0][i] directly
 *  2765  put the `for` loop INSIDE `if (mask != 0)` rather than as a sibling
 *  2710  test the ARRAY EXPRESSION, assign the variable inside:
 *            if (ptrC[chan] != 0) { mask = ptrC[chan]; ... }
 *  ---- this session ----
 *  2267  READ p->unk8 BEFORE p->unkC (443 points).  Golden's preamble is
 *        `lw t7,0xc(v0)` / `lw s6,8(v0)` and spills ptrC in the `jal
 *        osRecvMesg` DELAY SLOT.  With unkC read first IDO spills ptrC eagerly
 *        and fills the delay slot with `move a2,zero` instead.  The emitted
 *        LOAD order stays 0xc-then-8 either way -- it is the SPILL that moves.
 *  2259  declare ptr8 before ptrC
 *  2149  SEVEN locals: drop `p`, merge `chan` into `i`  -> FRAME 0x98 = golden
 *  2141  put ptrC back at declaration position 6
 *
 * RULED OUT -- ALL RE-MEASURED ON THE 7-LOCAL BASE (the old park's negatives
 * were measured on a defective base and several of them FLIPPED; e.g.
 * `default:` last looked like an 86-point WIN at 2710 and is a 269-point LOSS
 * here.  Re-measure before trusting any of these.)
 *   `default:` arm written last                                        2410
 *   inner loop as do { } while                                         2361
 *   `mask = mask >> 1` instead of `mask >>= 1`                         2526
 *   loop condition operands swapped, (mask!=0)&&(i<16)                 3166
 *   `mask = ptrC[i]; if (mask != 0)` instead of testing the array expr 2196
 *   `i = (s32)sp94 & 7` moved inside `if (msg & 0x10)`                 2431
 *   ditto with the whole chan<2 block re-nested (guard-side probe)     2431
 *   read p->unkC before p->unk8                                        2456
 *   keep a `p` local and inline ptr8 as ((s32*)p->unk8)[i]             2633
 *   a `msg` local replacing sp90, >>5 as an unnamed CSE temp           2536
 *   ditto with `msg = msg >> 1` write-back                             2526
 *   a `msg` local IN ADDITION to sp90 (8 locals)         2628, frame back to 0xa0
 *   drop sp90 instead of p (7 locals, wrong home for ptrC)             2609
 *   drop p AND sp90 (7 locals)                                         2585
 *   merge chan into `mask` instead of into `i`                         2606
 *   extra `m = mask;` copy at the top of the body (chasing `move t1,v0`)
 *                                                       u16 2568 / s32 2528
 *   `mask >>= 1` moved into the for-step / `if (mask & 1)` / `i < 2U` /
 *      `(u32)i <= 1` / `u32 i` with (s32) casts / `0x8000 + (...)` /
 *      `sp94 =` moved before the two stores / D_80041880 stored first
 *                                                            all exactly 2141
 *   case 2 store reordering 2464, default-arm store first 2635, `s32 chan`
 *      2454, `u32 i` (9-local base) 2399, `(mask & 1) == 1` 2449, flat
 *      D_800418B0 indexing 2264, `D_800BE9E4 * sp8C` 2264   (9-local base)
 *   `while (osRecvMesg(...) == 0)` rewritten as `for(;;){ if(...) break; }`
 *                                                                      9951
 *   `D_800418AC[arg0] = 0` hoisted above the two pointer reads          2426
 *   `func_10008F58(arg0 & 0xFF)` instead of `(u8)arg0`                  2701
 *   `mask = (u16)(mask >> 1)`                                           2526
 *   NEUTRAL at exactly 2141 (the binary cannot see them): `7 & (s32)sp94`,
 *      `(0x10 & (s32)sp94)`, `if ((s32)sp94 & 0x10)`, `!D_800417B0[arg0]`,
 *      `D_800418AC[arg0] = D_800418AC[arg0] | (mask & 0x7F)`,
 *      `D_80041970[arg0][i] = D_80041970[arg0][i] | 1`, `(u8)arg0` on
 *      D_800419A0, `mask = (u16)ptrC[i]`
 *
 * ===========================================================================
 * THE PERMUTER RESULT, AND WHY IT IS REFUSED  (read before re-running it)
 * ===========================================================================
 * Set up and selftested PASS on this exact file (5300 iterations, -j 9,
 * PERMUTER_TU_REQUIRE_FRAME=152, which is finally usable because the base now
 * satisfies it).  Its single best output, re-scored on the REAL asm-differ, is
 *
 *      `u16 mask` -> `u32 mask`   ...   1795   (frame still 0x98)
 *
 * and that is the ONLY edit in it.  It is semantically identical (mask is
 * loaded by `lhu` so it is already 0..0xffff and `>>= 1` never widens it) and
 * it IS a big score win -- and it must be REFUSED, because it can never reach
 * zero.  Golden contains TWO redundant u16 truncations that only a u16-typed
 * variable produces:
 *      1e38  andi v0,v1,0xffff      <- mask = ptrC[i]   (after an lhu!)
 *      1f88  andi t3,v0,0xffff      <- mask >>= 1
 * With `u32 mask` the first becomes `move t1,v0` and the second disappears.
 * The win comes from that shortened chain shaking some t-registers into place,
 * not from getting the allocation right: the s-register rotation and the
 * msg=t0 demotion below are UNCHANGED in it.  This is the
 * "refuse a better score that makes the output less like golden" rule, and it
 * is also a frame-style plateau -- so if you re-run the permuter, gate the mask
 * type or it will converge straight back onto this.
 * (`mask = (u16)ptrC[i]` and `mask = (u16)(mask >> 1)` were also measured: the
 * first is a no-op cast scoring exactly 2141, the second is 2526.)
 *
 * WHAT I WOULD TRY NEXT
 *   * Anything that legitimately creates ONE more compiler temp early in the
 *     function, ranked above the &D_800418B0 web.  NOT a no-op: the N-no-ops
 *     test applies -- several mutually-exclusive throwaway constructs all move
 *     the score the same way, which evidences "one folded temp web exists here"
 *     and nothing about any particular construct.
 *   * Do NOT re-chase the frame.  It is exact.  Do NOT chase (3) separately.
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
    s32 i;
    s32 *ptr8;
    u16 *ptrC;
    u16 mask;

    if (D_800417B0[arg0] == NULL) {
        return;
    }
    ptr8 = (s32 *)D_800417B0[arg0]->unk8;
    ptrC = (u16 *)D_800417B0[arg0]->unkC;
    D_800418AC[arg0] = 0;

    while (osRecvMesg(&D_80041E58[arg0], &sp94, 0) == 0) {
        i = (s32)sp94 & 7;
        if (((s32)sp94 & 0x10) != 0) {
            if ((u32)i < 2) {
                sp8C = 0x514;
                sp90 = (s32)sp94 >> 5;
                if (D_80041890[arg0] != 0) {
                    D_800418A0[arg0] = sp90 - D_80041890[arg0];
                }
                D_80041890[arg0] = sp90;
                D_80041880[arg0] = sp90;
                sp94 = (OSMesg)sp90;
            }
            if (ptrC[i] != 0) {
                mask = ptrC[i];
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

    if (D_800417B0[arg0]->unk30 == 0) {
        D_800418AC[arg0] |= 0x80;
        if (D_800417B0[arg0]->unk15 == 0) {
            func_10008F58((u8)arg0);
            D_800417B0[arg0]->unk15 = 1;
        }
    } else if (D_800417B0[arg0]->unk15 == 1) {
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
