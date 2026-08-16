/* func_1510AA44 -- game_137ED0.c -- 916 bytes / 229 insns / frame 0x40
 * STATUS: **MATCHED** (score 0 with and without -R; whole-TU .text/.rodata/.data IDENTICAL
 * to expected/).  Shipped LIVE in conker/src/game_137ED0.c -- this file is the record only.
 * game_137ED0.c is now a fully decompiled TU (0 pragmas, 4/4 functions live).
 *
 * WHAT IT IS: the per-frame behaviour handler for actor behaviour 0x2E (its address sits at
 * 0x80088EB8 = D_80088C90 + 46*12, word0 of the 12-byte behaviour record).  It is a CLOCK:
 * field 0x3C is a 12-hour time-of-day counter in 60Hz ticks (2592000 ticks = 43200 s =
 * 720 min = 12 h), 0xA8 is the hour-hand rotation (2.5 deg per 5 minutes -> 360 deg / 12 h),
 * 0x8 is the minute-hand rotation (6 deg per minute), 0x7C/0x80 are the chime countdown and
 * the last-chimed second, 0x84 is a "clock has been seeded from D_800BE3E4" latch, and
 * func_15114D24(.., 0x4CC, 0x7FFF, ..) is the bong.  It chimes on the hour (quarter index
 * (min/15)&3 == 0) with the hour count, and once on each other quarter.
 *
 * ================= FRAME DECODE (golden .s, framesize 0x40) =========================
 *   0x00..0x17  arg build, 6 words (the func_15114D24 call takes 6 args; 0x10/0x14 used)
 *   0x18..0x1F  saved regs, $ra at 0x1C  (no $s registers are saved at all)
 *   0x20..0x2F  compiler TEMP area   ($f2 spilled to 0x24 across the call)
 *   0x30..0x3F  declared-auto homes, FOUR words, ending exactly at framesize
 *               0x3C = 1st declared, 0x38 = 2nd, 0x34 = 3rd, 0x30 = 4th
 *   0x40        $a0 parameter home (caller's arg-build slot, outside this frame)
 *
 * HOW THAT WAS READ, and the third-slot law in action.  The first draft declared SIX
 * locals; it built at framesize 0x48 and moved `min`'s spill from 0x38 to 0x40 while
 * `angle`'s spill stayed at 0x24.  A slot that MOVES is a home, a slot that stays is a
 * compiler temp -- so 0x38 is `min`'s home (=> `min` is the SECOND declared local) and
 * 0x24 is a temp that no declaration change can reach.  Four words of home area therefore
 * means exactly four autos, and dropping the two that were inlineable (`quarter`,
 * `oldQuarter`) restored framesize 0x40 with every stack displacement on golden.
 * ====================================================================================
 */

/* ---- declarations added to game_137ED0.c ------------------------------------- */

typedef struct {
    u8  pad00[0x8];
    f32 unk8;      /* minute-hand rotation, degrees */
    u8  pad0C[0x30];
    s32 unk3C;     /* time of day, 60Hz ticks, 0 .. 2592000 (12 h) */
    u8  pad40[0x28];
    f32 unk68;
    u8  pad6C[0x10];
    s32 unk7C;     /* chimes remaining */
    s32 unk80;     /* second at which the last chime fired */
    s32 unk84;     /* seeded-from-RTC latch */
    u8  pad88[0x20];
    f32 unkA8;     /* hour-hand rotation, degrees */
    u8  padAC[0x5C];
    f32 unk108;
} ClockActor;

extern u32 D_800BE3E4;   /* unsigned: golden uses divu/mfhi for the % 43200 */

/* ---- MATCHING BODY ----------------------------------------------------------- */

void func_1510AA44(ClockActor *arg0) {
    s32 oldMin;
    s32 min;
    s32 sec;
    f32 angle;

    oldMin = arg0->unk3C / 3600 % 60;
    if (arg0->unk84 == 0) {
        if (D_800BE3E4 != 0) {
            arg0->unk84 = 1;
            arg0->unk3C = D_800BE3E4 * 180 % 43200;
            arg0->unk3C = arg0->unk3C * 60;
            oldMin = arg0->unk3C / 3600 % 60;
        }
    }
    if (oldMin < 0) {
        oldMin += 60;
    }
    arg0->unk3C = arg0->unk3C + D_800BE9E4;
    if (arg0->unk3C >= 2592000) {
        arg0->unk3C = arg0->unk3C - 2592000;
    }
    sec = arg0->unk3C / 60;
    min = sec / 60;
    angle = (f32) (sec / 300) * 2.5f;
    if (angle > 360.0f) {
        arg0->unk3C = arg0->unk3C - 2592000;
    }
    min = min % 60;
    if (min < 0) {
        min += 60;
    }
    if (oldMin != min) {
        if (oldMin / 15 != min / 15) {
            if ((min / 15 & 3) == 0) {
                arg0->unk7C = (s32) (angle / 30.0f);
                if (arg0->unk7C == 0) {
                    arg0->unk7C = 12;
                }
            } else {
                arg0->unk7C = 1;
            }
            arg0->unk80 = -1;
        }
    }
    if (arg0->unk7C != 0) {
        if (arg0->unk80 != sec) {
            arg0->unk80 = sec;
            arg0->unk7C = arg0->unk7C - 1;
            func_15114D24((s32) arg0, 0x4CC, 0x7FFF, 0xC8, 0x3E8, 0xC);
        }
    }
    arg0->unk68 = 5.0f;
    arg0->unk108 = 5.0f;
    arg0->unk8 = -((f32) min * 6.0f);
    arg0->unkA8 = -angle;
}

/* ================================ MEASURED LOG ================================
 *   6 locals (oldMin,min,sec,quarter,oldQuarter,angle), `min != oldMin`  ->   75, frame 0x48
 *   4 locals (oldMin,min,sec,angle),                    `min != oldMin`  ->   75, frame 0x40
 *   4 locals,                                           `oldMin != min`  ->   65
 *   4 locals, `oldMin != min`, unk8 store BEFORE unkA8 store             ->    0  MATCH
 *
 * THE LAST STEP -- the statement-order lever, found by the permuter after 375 iterations.
 * The 65 residual was nine rows, all ONE step of the FP temp rotation
 * ($f4,$f6,$f8,$f10,$f16,$f18) in the tail block; every opcode, immediate, branch polarity
 * and delay slot already matched.  IDO allocates FP temps in SOURCE-STATEMENT order, so
 * whichever of the two final stores is written first claims $f4.  Golden writes
 *     arg0->unk8  = -((f32) min * 6.0f);   -- 5 temps: mtc1, cvt, 6.0f, mul, neg
 *     arg0->unkA8 = -angle;                -- 1 temp:  neg
 * The two statements are independent stores to distinct members, so the swap is pure
 * ordering -- no forcer, no dead local, no cast games.  Note the EMISSION order is the
 * opposite (golden emits swc1 0xa8 before swc1 0x8): the scheduler reverses them, which is
 * exactly why reading store order off the .s pointed the wrong way here.
 *
 * DEAD LEVERS on this function (all measured, all exactly 65, so do not retry them):
 *   implicit vs explicit (s32)/(f32) casts at all three conversion sites; `360.0f < angle`
 *   vs `angle > 360.0f`; `arg0->unk108 = arg0->unk68 = 5.0f` chained; moving the two 5.0f
 *   stores to the end or between the others; `angle` split into two statements; compound
 *   `-=` / `--` vs plain; `min %= 60`; and ALL FIVE remaining permutations of the
 *   declaration list that keep `min` second (decl order is inert here).
 * Regressions worth recording: `(s32)(angle * (1.0f/30.0f))` 470, `(f32)-min * 6.0f` 460,
 * `0.0f - angle` 545, `arg0->unk3C / 60 / 60 % 60` for oldMin 2575.
 * ============================================================================== */
