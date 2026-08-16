#include "n_synthInternals.h"
#include <R4300.h>

// struct21 *func_100214F0(struct42 *arg0, void *arg1, s32 arg2, void *struct21);
#pragma GLOBAL_ASM("asm/nonmatchings/init_214F0/func_100214F0.s")

/* The ALLoadFilter (ADPCM decoder) stage of an N_PVoice: libultra's
 * _decoderSetParam / _decodeChunk, reworked by Rare.
 *
 * The case bodies really are emitted 5-then-4: IDO -g sorts the dispatch
 * comparisons by case VALUE but lays the bodies out in SOURCE order, and
 * golden tests 4 first while placing case 5's body first. */
s32 func_10021C40(N_PVoice *f, s32 paramID, void *param) {
    switch (paramID) {
        case 5:
            f->dc_table = param;
            f->dc_memin = (s32)f->dc_table->base;
            f->dc_sample = 0;
            f->dc_table->len = f->dc_table->len / 9 * 9;
            if (((u32)f->dc_table->waveInfo.adpcmWave.book & 0xFF000003) != 0x80000000) {
                f->dc_loop.count = 0;
                f->dc_loop.start = f->dc_loop.end = f->dc_loop.count;
                break;
            } else {
                f->dc_bookSize = f->dc_table->waveInfo.adpcmWave.book->order * 2 *
                                 f->dc_table->waveInfo.adpcmWave.book->npredictors * 8;
            }
            if (f->dc_table->waveInfo.adpcmWave.loop) {
                f->dc_loop.start = f->dc_table->waveInfo.adpcmWave.loop->start;
                f->dc_loop.end = f->dc_table->waveInfo.adpcmWave.loop->end;
                f->dc_loop.count = f->dc_table->waveInfo.adpcmWave.loop->count;
                bcopy(&f->dc_table->waveInfo.adpcmWave.loop->state, f->dc_lstate,
                      sizeof(ADPCM_STATE));
            } else {
                f->dc_loop.count = 0;
                f->dc_loop.start = f->dc_loop.end = f->dc_loop.count;
            }
            break;

        case 4:
            f->dc_lastsam = 0;
            f->dc_first = 1;
            f->dc_sample = 0;
            if (f->dc_table) {
                f->dc_memin = (s32)f->dc_table->base;
                f->dc_loop.count = 0;
            }
            break;

        default:
            break;
    }
    return 0;
}

/* Emit the audio command list that DMAs one chunk of ADPCM into DMEM and
 * decodes it.  Each n_abi.h / abi.h macro carries its own block-scoped
 * `Acmd *_a`, which is why golden shows three separate stack homes (0x24,
 * 0x20, 0x1C) for what looks like a single pointer. */
Acmd *func_10021E4C(Acmd *p, N_PVoice *f, s32 nframes, s32 nbytes, s16 dmemOut, s16 dmemIn, s32 flags) {
    s32 offset;
    s32 addr;

    if (nbytes > 0) {
        addr = f->dc_dma(f->dc_memin, nbytes, f->dc_dmaState);
        if (addr == 0) {
            f->em_first = 1;
            f->em_volume = 0;
            f->dc_first = 0;
            return p;
        }
        offset = addr & 7;
        nbytes += offset;
        n_aLoadBuffer(p++, nbytes - (nbytes & 7) + 8, dmemIn, addr - offset);
    } else {
        offset = 0;
    }

    if (flags & A_LOOP) {
        aSetLoop(p++, K0_TO_PHYS(f->dc_lstate));
    }

    n_aADPCMdec(p++, K0_TO_PHYS(f->dc_state), flags, nframes * 2, offset, dmemOut);

    f->dc_first = 0;
    return p;
}
