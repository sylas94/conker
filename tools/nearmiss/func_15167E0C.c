/* func_15167E0C  --  game_1944C0.c  --  195 instructions, frame 0x20
 *
 * STATUS: NEAR-MISS. best 685 (was 885 on entry). Structure is BYTE-EXACT:
 * same instruction count, same addresses, same branch forms
 * (beql/bgezl/blezl/bnel/bltzl), frame 0x20, `finished` spilled to 0x1b(sp),
 * a0 homed to 0x20(sp) across the indirect call. Everything OUTSIDE the three
 * 24.8 accumulate steps (i.e. 0xdfc..0xebc and 0xf64..0x1104, ~160 of 195
 * instructions) is IDENTICAL including all register names.
 *
 * RESIDUAL CLASS: ALLOCATION (register-class assignment), confined to
 * 0xebc..0xf60.
 *
 * ---------------------------------------------------------------------------
 * FRAME DECODE (quoted from golden)
 *   /* 1952BC 15167E0C 27BDFFE0 * /  addiu $sp, $sp, -0x20
 *   /* 1952C0 15167E10 AFBF0014 * /  sw    $ra, 0x14($sp)
 *   /* 19535C 15167EAC A3A7001B * /  sb    $a3, 0x1B($sp)     <- `finished`, u8
 *   /* 195354 15167EA4 AFA40020 * /  sw    $a0, 0x20($sp)     <- param home (>= framesize)
 * framesize 0x20 = arg-build 0x10 (0x00..0x0f) + saved-reg block 8 (0x10..0x17,
 * $ra at 0x14) + locals.  Locals therefore END at 0x20; the only spilled local
 * is the u8 at 0x1b, so exactly 4 bytes of earlier-declared locals sit above it
 * (0x1c..0x1f) and the total rounds 0x18+5=0x1d up to 0x20.  Declaration list
 * that reproduces this: {void (*func)(struct102*); u8 finished; s32 limit;}
 * -> func 0x1c..0x1f, finished 0x1b, limit unspilled.  CONFIRMED by build.
 *
 * CALLEE SIGNATURE (the single direct callee) verified against the TU's own
 * live C: func_1516972C(struct102 *) -- conker/include/functions.h:811, and
 * D_8008C9C8[] / D_8008CA20[] are already declared `void (*[])(struct102 *)`
 * at the top of game_1944C0.c. Golden passes only $a0, and reloads it from
 * 0x20(sp) after each indirect call, so both tables and func_1516972C take
 * exactly one pointer arg. No prototype guesswork was needed.
 *
 * ---------------------------------------------------------------------------
 * THE ONE OPEN QUESTION -- register CLASS of the accumulate temporaries.
 *
 * IDO puts a small set of values in a "pool" (v0, v1, a1, a2, a3, then t0)
 * and the rest in the t0..t9 round-robin. Measured: with N register-resident
 * locals in the `if (arg0->unk38 != 0)` block, `finished` lands in a3 for
 * N <= 3 and is pushed to t0 at N == 4 (which re-registers the WHOLE function,
 * +610). So the target has exactly THREE pool values in that block.
 *
 *   TARGET :  packed -> v0 (Y), v1 (X), v0 (Z)   product -> a1 (all 3)
 *             sum    -> t2, t8, t5  (ordinary temps, different each axis)
 *   BEST   :  packed -> v1 (all 3)               product -> a1 (all 3)  MATCHES
 *             sum    -> v0 (all 3)
 *
 * So `product` (== field * D_800BE9E4, hoisted to its own local) is SOLVED --
 * `mflo a1` now matches at all three sites. What remains: the target spends
 * TWO pool registers on the packed value and ZERO on the sum; the best C
 * spends one on each. Target's packed-Y and packed-X live ranges OVERLAP
 * (packed-X is built at 0xefc, before packed-Y is consumed at 0xf04), which is
 * what forces the second pool register and pushes the sum out to temps.
 *
 * Writing that overlap into the source (hoisting the X pack above the Y store)
 * does NOT reproduce it -- it perturbs the schedule far more than it gains.
 *
 * ---------------------------------------------------------------------------
 * MEASURED LADDER (all bounded to --max-lines 195 = the symbol's own 195
 * instructions; a control variant was included in every batch and always
 * reproduced its known score exactly, so the harness is proven live):
 *
 *   885  entry baseline: one local per axis holding the SUM
 *                        subY = ((hi<<8)|lo) + vel*dt; hi = subY>>8; lo = subY;
 *  1495  + a 4th local (`prod`)            -- 4 locals push `finished` a3 -> t0
 *  1405  2 locals (pos,vel), pos computed before vel
 *  1405  ... same, declaration order (vel,pos)          [decl order: NO EFFECT]
 *  1680  "literal" read: both packs hoisted, vel after
 *  1285  3 packed locals + vel (4 locals)
 *  1065  split-assignment form  pos = arg0->unk22; pos = (pos<<8)|arg0->unk2E;
 *   860  F: 2 locals, VEL COMPUTED BEFORE PACK in each axis, sum as CSE
 *   860  ... same, declaration order (vel,pos)          [decl order: NO EFFECT]
 *  1170  ABA: packed var A for Y and Z, B for X
 *  1285  ABB / ABC (one packed local per axis)
 *   685  AAB: packed var A for Y and X, B for Z          <-- BEST
 *  1685  AAB + hoist X pack above Y store (to force overlap)
 *  1685  ... same, decl order (vel,pkA,pkB)
 *  1515  hoist X pack only
 *  1665  both packs up front, vel per axis
 *  2235  multiply written inline instead of a `vel` local
 *         (confirms the entry note: the `sh 0x22` store kills the cached
 *          arg0->unk30 load and IDO emits a SECOND multu)
 *
 * DECLARATION SCOPE -- measured, ALL IRRELEVANT (every one scored 685):
 *   685  pkA/pkB/vel inside the `if (arg0->unk38 != 0)` block   [G8, control]
 *   685  all three hoisted to the function's top declaration list
 *   685  only `vel` at function top
 *   685  only pkA/pkB at function top
 *   685  all three at top, declared BEFORE `limit`
 *   735  `finished` declared LAST instead of second
 *   860  same but a single packed local (AAA instead of AAB)
 * The 735 result is the frame law confirming itself: `finished` must be the
 * SECOND declaration so that exactly 4 bytes (the function pointer) sit above
 * its home, putting it at 0x1b. Move it and the home moves and the score rises.
 *
 * PERMUTER -- run, exhausted, did NOT close it.
 *   import.py + permuter.py --stop-on-zero -j 12, 76,083 iterations from the
 *   685 seed. Best found = 640, and that 640 is REJECTED: it buys its 45
 *   points with `GameSpriteObject *new_var = arg0;` aliasing plus wrapping the
 *   three accumulate steps in `do { ... } while (0);` -- both are on the
 *   banned-construct list. Every legitimate permutation plateaued at 685.
 *   (Clean up: the import creates conker/nonmatchings/, which is untracked and
 *   must be rm -rf'd afterwards; it is NOT gitignored.)
 *
 * KEY NEGATIVE RESULTS, do not re-derive:
 *  - Declaration ORDER of the in-block locals is irrelevant here (860==860,
 *    1405==1405, 1170==1170, 1685==1685), and so is declaration SCOPE (five
 *    different placements all gave 685). Only the COUNT and the live ranges
 *    matter. This is the opposite of the usual frame-ordinal lever, because
 *    none of these locals is ever spilled -- the ordinal law still governs
 *    `finished`, which IS spilled (735 when moved).
 *  - Hoisting to create live-range overlap always LOSES (1515..1685) EVEN
 *    THOUGH IT DOES FLIP THE REGISTER CLASS THE RIGHT WAY. Verified by
 *    dumping the H1 diff: with the overlap the packed value really does take
 *    TWO pool registers (a1 and a2) and the sum really is evicted -- but IDO
 *    picks a1/a2 rather than v0/v1, which then displaces `finished` out of a3
 *    and re-registers the whole function. The mechanism is right and the
 *    pool-assignment ORDER is not steerable from C. This is the wall.
 *  - Writing the multiply inline costs a second multu (2235).
 *  - `vel` must be computed BEFORE the pack in each axis (860 vs 1405).
 *
 * HONESTY FLAG on the 685: AAB uses packed-var A for the Y and X axes and a
 * second var B for Z. There is no semantic reason for that split -- it is
 * chosen only for its register effect, so it is NOT shippable as-is even if it
 * reached 0. The honest shape is the single `pos` variant (F, 860). If the
 * permuter closes this, re-derive a source shape that is semantically
 * motivated before shipping.
 *
 * ---------------------------------------------------------------------------
 * CURRENT BEST C (685) -- the struct is derived purely from load/store widths:
 *   lw 0x10 -> ptr        lh/sh 0x1c,1e,20,22,24,26,28,30,32,38 -> s16
 *   lbu/sb 0x2c,2d,2e,3f -> u8      lb 0x2f,3a,48 -> s8      lhu/sh 0x44 -> u16
 */

typedef struct {
    char pad_0[0x10];
    struct Some15171F04 *unk10;
    char pad_14[0x8];
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    s16 unk24;
    s16 unk26;
    s16 unk28;
    char pad_2A[0x2];
    u8 unk2C;
    u8 unk2D;
    u8 unk2E;
    s8 unk2F;
    s16 unk30;
    s16 unk32;
    char pad_34[0x4];
    s16 unk38;
    s8 unk3A;
    char pad_3B[0x4];
    u8 unk3F;
    char pad_40[0x4];
    u16 unk44;
    char pad_46[0x2];
    s8 unk48;
} GameSpriteObject;

void func_15167E0C(GameSpriteObject *arg0) {
    void (*func)(struct102 *);
    u8 finished;
    s32 limit;

    finished = 0;
    if (arg0->unk38 != 0x7FFF) {
        arg0->unk38 -= D_800BE9E4;
        if (arg0->unk38 < 0) {
            arg0->unk38 = 0;
            finished = 1;
        }
    }

    if (arg0->unk3A > 0) {
        if (arg0->unk3A < arg0->unk3F) {
            arg0->unk3F -= arg0->unk3A;
        } else {
            arg0->unk38 = 0;
            finished = 1;
        }
    }

    if (arg0->unk2F != -1) {
        func = D_8008C9C8[arg0->unk2F];
        if (func != NULL) {
            func((struct102 *)arg0);
        }
    }

    if (arg0->unk38 != 0) {
        s32 pkA;
        s32 pkB;
        s32 vel;

        arg0->unk30 += arg0->unk32;

        vel = arg0->unk30 * D_800BE9E4;
        pkA = (arg0->unk22 << 8) | arg0->unk2E;
        arg0->unk22 = (pkA + vel) >> 8;
        arg0->unk2E = pkA + vel;

        vel = arg0->unk26 * D_800BE9E4;
        pkA = (arg0->unk20 << 8) | arg0->unk2C;
        arg0->unk20 = (pkA + vel) >> 8;
        arg0->unk2C = pkA + vel;

        vel = arg0->unk28 * D_800BE9E4;
        pkB = (arg0->unk24 << 8) | arg0->unk2D;
        arg0->unk24 = (pkB + vel) >> 8;
        arg0->unk2D = pkB + vel;

        if (arg0->unk1E != 0) {
            limit = (arg0->unk10->unk4 << 8) - 1;
            arg0->unk1C += arg0->unk1E * D_800BE9E4;
            if (limit < arg0->unk1C) {
                if (arg0->unk44 & 0x20) {
                    arg0->unk38 = 0;
                    finished = 1;
                } else {
                    arg0->unk44 |= 0x80;
                    if (arg0->unk44 & 2) {
                        arg0->unk1C = limit - (arg0->unk1C % limit);
                        arg0->unk1E = -arg0->unk1E;
                    } else {
                        do {
                            arg0->unk1C -= limit;
                        } while (limit < arg0->unk1C);
                    }
                }
            } else if (arg0->unk1C < 0) {
                if (arg0->unk44 & 0x40) {
                    arg0->unk38 = 0;
                    finished = 1;
                } else if (arg0->unk44 & 2) {
                    arg0->unk1C = -arg0->unk1C % limit;
                    arg0->unk1E = -arg0->unk1E;
                } else {
                    do {
                        arg0->unk1C += limit;
                    } while (arg0->unk1C < 0);
                }
            }
        }
    } else {
        finished = 1;
    }

    if (finished != 0) {
        if (arg0->unk48 != -1) {
            D_8008CA20[arg0->unk48]((struct102 *)arg0);
        }
        func_1516972C((struct102 *)arg0);
    }
}
