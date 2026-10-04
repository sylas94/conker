#include "n_synthInternals.h"
#include <R4300.h>

#define ADPCMFBYTES 9
#define LFSAMPLES 4

void func_10007DA0(void);
extern s32 D_8003C8E0;
Acmd *func_10021E4C(Acmd *p, N_PVoice *f, s32 nframes, s32 nbytes, s16 dmemOut, s16 dmemIn, s32 flags);

/* n_alAdpcmPull, with Rare's no-wavetable silence path and a debug trap on a
 * codebook outside the first 8MB of RDRAM. */
Acmd *func_100214F0(N_PVoice *f, s16 *outp, s32 outCount, Acmd *p) {
    Acmd *ptr = p;
    s16 inp;
    s32 tsam;
    s32 nframes;
    s32 nbytes;
    s32 overFlow;
    s32 startZero;
    s32 nOver;
    s32 nSam;
    s32 op;
    s32 nLeft;
    s32 bEnd;
    s32 decoded = 0;
    s32 looped = 0;
    N_PVoice *e = f;

    if (outCount == 0) {
        return ptr;
    }

    inp = N_AL_DECODER_IN;
    if (e->dc_table == NULL) {
        aClearBuffer(ptr++, *outp, outCount << 1);
        return ptr;
    }

    if (K0_TO_PHYS(e->dc_table->waveInfo.adpcmWave.book->book) > 0x800000) {
        D_8003C8E0 = 0xF000003;
        func_10007DA0();
    }

    n_aLoadADPCM(ptr++, e->dc_bookSize, K0_TO_PHYS(e->dc_table->waveInfo.adpcmWave.book->book));

    looped = (outCount + e->dc_sample > e->dc_loop.end) && (e->dc_loop.count != 0);
    if (looped) {
        nSam = e->dc_loop.end - e->dc_sample;
    } else {
        nSam = outCount;
    }

    if (e->dc_lastsam) {
        nLeft = ADPCMFSIZE - e->dc_lastsam;
    } else {
        nLeft = 0;
    }
    tsam = nSam - nLeft;
    if (tsam < 0) {
        tsam = 0;
    }

    nframes = (tsam + ADPCMFSIZE - 1) >> LFSAMPLES;
    nbytes = nframes * ADPCMFBYTES;

    if (looped) {
        ptr = func_10021E4C(ptr, e, tsam, nbytes, *outp, inp, e->dc_first);

        if (e->dc_lastsam) {
            *outp += (e->dc_lastsam << 1);
        } else {
            *outp += (ADPCMFSIZE << 1);
        }

        e->dc_lastsam = e->dc_loop.start & 0xF;
        e->dc_memin = (s32)e->dc_table->base + ADPCMFBYTES * ((s32)(e->dc_loop.start >> LFSAMPLES) + 1);
        e->dc_sample = e->dc_loop.start;

        bEnd = *outp;
        while (outCount > nSam) {
            outCount -= nSam;
            op = (bEnd + ((nframes + 1) << (LFSAMPLES + 1)) + 16) & ~0x1F;
            bEnd += nSam << 1;

            if (e->dc_loop.count != -1 && e->dc_loop.count != 0) {
                e->dc_loop.count--;
            }

            nSam = MIN(outCount, e->dc_loop.end - e->dc_loop.start);
            tsam = nSam - ADPCMFSIZE + e->dc_lastsam;
            if (tsam < 0) {
                tsam = 0;
            }
            nframes = (tsam + ADPCMFSIZE - 1) >> LFSAMPLES;
            nbytes = nframes * ADPCMFBYTES;
            ptr = func_10021E4C(ptr, e, tsam, nbytes, op, inp, e->dc_first | A_LOOP);
            aDMEMMove(ptr++, op + (e->dc_lastsam << 1), bEnd, nSam << 1);
        }

        e->dc_lastsam = (outCount + e->dc_lastsam) & 0xF;
        e->dc_sample += outCount;
        e->dc_memin += ADPCMFBYTES * nframes;
        return ptr;
    }

    nSam = nframes << LFSAMPLES;
    overFlow = e->dc_memin + nbytes - ((s32)e->dc_table->base + e->dc_table->len);
    if (overFlow < 0) {
        overFlow = 0;
    }
    nOver = (overFlow / ADPCMFBYTES) << LFSAMPLES;
    if (nOver > nSam + nLeft) {
        nOver = nSam + nLeft;
    }
    nbytes -= overFlow;

    if ((nOver - (nOver & 0xF)) < outCount) {
        decoded = 1;
        ptr = func_10021E4C(ptr, e, nSam - nOver, nbytes, *outp, inp, e->dc_first);
        if (e->dc_lastsam) {
            *outp += (e->dc_lastsam << 1);
        } else {
            *outp += (ADPCMFSIZE << 1);
        }
        e->dc_lastsam = (outCount + e->dc_lastsam) & 0xF;
        e->dc_sample += outCount;
        e->dc_memin += ADPCMFBYTES * nframes;
    } else {
        e->dc_lastsam = 0;
        e->dc_memin += ADPCMFBYTES * nframes;
    }

    if (nOver) {
        e->dc_lastsam = 0;
        if (decoded) {
            startZero = (nLeft + nSam - nOver) << 1;
        } else {
            startZero = 0;
        }
        aClearBuffer(ptr++, startZero + *outp, nOver << 1);
    }
    return ptr;
}

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
