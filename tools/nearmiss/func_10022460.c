/* init_22460 / func_10022460  ==  Rare's rework of n_alResamplePull
 *
 * STATUS: the FUNCTION IS BYTE-PERFECT.  This file is a complete, compilable TU
 * that re-scores 0 with NO hand edits.  It is parked here rather than shipped
 * because installing it BREAKS THE ROM for a reason that has nothing to do with
 * the C -- see BLOCKER below.
 *
 * SCORE
 *   raw  (tools/fastscore.py)                 = 650   <- MEANINGLESS, wrong opt level
 *   raw  (-g scorer, see "HOW TO SCORE")      = 190
 *   pad-corrected                             = 0
 *     golden .s is 164 words: 145 real + 19 trailing inter-TU pad nops.
 *     Our stream is 145 words, so fastscore's length term is |145-164|*10 = 190
 *     and the ROW count is ZERO.  Confirmed with the real loop:
 *       make build/src/init_22460.c.o  +  asm-differ -o func_10022460 -R  ->  score 0
 *       verify_match.sh: "score with -R = 0", "score without -R = 0",
 *                        "all 1 FUNC symbols in the TU score 0"
 *
 * HOW TO SCORE THIS FILE
 *   conker/Makefile sets  init_22460.c.o: OPT_FLAGS := -g  (NOT the default -O2 -g3),
 *   and tools/fastscore.py hardcodes -O2 -g3.  Scoring this with plain fastscore
 *   reports 650 and is pure noise.  Make a copy of fastscore.py with
 *       OPT = ["-g", "-mips2", "-o32"]
 *   and the asm_processor argv changed from  "-O2","-g3"  to  "-g".
 *   Every libultra/audio + init_1xxxx / init_2xxxx TUs in this range needs the same.
 *
 * BLOCKER (why this is parked, and it is NOT a source problem)
 *   conker.us.yaml gives this TU the range 0x22460..0x226F0 = 0x290 bytes, but the
 *   function is only 145 instructions = 0x244 bytes.  The remaining 76 bytes are
 *   inter-TU padding (zeros) that today reach .text only because the #pragma
 *   GLOBAL_ASM splices the whole .s, pad nops included.  Replace the pragma with C
 *   and the object's .text drops 0x290 -> 0x250 (IDO's own 16-byte alignment gives
 *   back only 12 of the 76 bytes).  build/conker.ld concatenates
 *       build/src/init_22460.c.o(.text);
 *       build/asm/libultra/libc/bzero.s.o(.text);
 *   with no explicit address in between, so the whole of libultra.a slides down:
 *   MEASURED  bzero linked at 0x100226B0 instead of symbol_addrs' 0x100226F0, and
 *   `make VERSION=us all` reports  build/conker.us.bin: FAILED.
 *   verify_match.sh flags exactly this: ".text SECTION SIZE ours=0x250 golden=0x290".
 *
 *   Fixing it is a SPLAT-LEVEL change, not a source change, and conker/asm and
 *   conker/expected are BOTH gitignored (generated), so a hand-written pad .s there
 *   would not survive `make extract`.  The tracked options are:
 *     (a) split 0x226A4..0x226F0 out of this TU in conker.us.yaml as its own
 *         asm/bin subsegment, or
 *     (b) use asm-processor's INLINE  GLOBAL_ASM( ... )  block form (asm_processor.py
 *         line 967 accepts a bare "GLOBAL_ASM(" line) to emit 19 .word 0 after the
 *         function, which keeps everything inside this tracked .c.
 *   Neither was attempted: both change build infrastructure and would move bytes for
 *   every other TU mid-wave.
 *
 * WHAT CLOSED IT (do not re-litigate)
 *   1. The near-twin init_22040.c (0 pragmas, matched) declares this function as
 *      `Cmd *func_10022460(Voice *, s16 *, Cmd *)`, and the offsets 0x48/0x4C/0x50/
 *      0x54/0x58 land exactly on N_PVoice's rs_state/rs_ratio/rs_upitch/rs_delta/
 *      rs_first.  It is n_alResamplePull.
 *   2. USE THE ABI MACROS, not hand-written ->w0/->w1 stores.  aDMEMMove and
 *      n_aResample each carry a BLOCK-SCOPED `Acmd *_a`, and at -g those get their own
 *      stack homes (0x20 and 0x1C) -- exactly the two slots golden has below
 *      finCount.  (init_214F0.c records the same observation for its three homes.)
 *      Hand-written stores scored 308: they lost the two homes AND emitted the
 *      end-of-then-branch store in the `b` delay slot where golden has a nop,
 *      i.e. 144 instructions instead of 145.
 *   3. The float compare is `f->rs_ratio > D_8002C840`, NOT the algebraically
 *      identical `D_8002C840 < f->rs_ratio`.  IDO -g hands out fp temps in
 *      evaluation order, so whichever operand is written FIRST gets $f4; golden
 *      gives $f4 to rs_ratio and $f8 to the double.  Writing it the other way costs
 *      17 rows: it rotates every fp temp in the else-branch by one step
 *      (the ldc1/lwc1/cvt/c.lt.d quad and then every mul/div/trunc after it).
 *
 * DO NOT REPEAT
 *   - Do not score this with unmodified tools/fastscore.py.
 *   - Do not hand-roll the two command words; use aDMEMMove / n_aResample.
 *   - Do not "fix" the comparison back to `D_8002C840 < f->rs_ratio`.
 *   - Do not declare Cmd/Voice shadow structs here; N_PVoice and Acmd are exact.
 *   - Local declaration order is load-bearing (top-down homes 0x34/0x32/0x2C/0x28/0x24).
 */
#include "n_synthInternals.h"

extern f64 D_8002C840;
extern f32 D_8002C848;

Acmd *func_100214F0(N_PVoice *, s16 *, s32, Acmd *);

Acmd *func_10022460(N_PVoice *f, s16 *outp, Acmd *p) {
    Acmd *ptr;
    s16 inp;
    s32 inCount;
    s32 incr;
    f32 finCount;

    ptr = p;
    inp = N_AL_TEMP_1;
    if (f->rs_upitch != 0) {
        ptr = func_100214F0(f, &inp, SAMPLES, p);
        aDMEMMove(ptr++, inp, *outp, N_AL_DIVIDED);
    } else {
        if (f->rs_ratio > D_8002C840) {
            f->rs_ratio = D_8002C848;
        }
        f->rs_ratio = (s32) (f->rs_ratio * 32768.0f);
        f->rs_ratio = f->rs_ratio / 32768.0f;
        finCount = f->rs_delta + f->rs_ratio * 184.0f;
        inCount = finCount;
        f->rs_delta = finCount - inCount;
        ptr = func_100214F0(f, &inp, inCount, p);
        incr = f->rs_ratio * 32768.0f;
        n_aResample(ptr++, osVirtualToPhysical(f->rs_state), f->rs_first, incr, inp, 0);
        f->rs_first = 0;
    }
    return ptr;
}
