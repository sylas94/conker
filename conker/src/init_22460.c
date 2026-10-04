/* init_22460 -- Rare's rework of n_alResamplePull.  Built with OPT_FLAGS := -g
 * (see conker/Makefile); scoring this TU with the default -O2 -g3 is noise.
 *
 * The trailing GLOBAL_ASM block is NOT code.  conker.us.yaml gives this TU the
 * range 0x22460..0x226F0 (0x290) while the function is 0x244; the remaining
 * 76 bytes are inter-TU padding that used to reach .text only as a side effect
 * of #pragma GLOBAL_ASM splicing the whole .s.  IDO's own 16-byte .text align
 * gives back 12 of them, so 0x40 must be stated explicitly or every object
 * downstream of here slides and the ROM breaks.
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

/* 0x40 of inter-TU padding at 0x100226B0..0x100226F0 -- see header. */
GLOBAL_ASM(
glabel pad_100226B0
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
)
