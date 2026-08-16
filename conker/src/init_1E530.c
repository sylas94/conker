#include <ultra64.h>

#include "n_libaudio.h"
#include "variables.h"
#include "n_abi.h"

/* This TU deliberately does NOT include "functions.h".
 *
 * Two reasons, both forced:
 *   - functions.h and n_libaudio.h give n_alInit/n_alClose incompatible prototypes,
 *     so they cannot both be included; n_syn (and its 0x48 auxBus field) is what this
 *     file actually needs.
 *   - functions.h line 1005 declares
 *         void func_1001E530(s32 arg0, void *arg1, s32 arg2);
 *     which the ROM contradicts: the function returns its command-list cursor
 *     (`lw v0,0x7C(sp)` in the epilogue) and takes a sample pointer first.  That
 *     declaration is wrong and should be corrected separately -- it is not corrected
 *     here because functions.h is a dependency of every GLOBAL_ASM object.
 * The one thing this file lost by dropping the header is func_1001FA78, re-declared
 * below exactly as functions.h has it.
 */
f32 func_1001FA78(f32 arg0[4][4], s32 arg1);

/* ALLowPass as this TU actually uses it.
 *
 * src/libultra/audio/synthInternals.h declares the tail of ALLowPass as
 *     POLEF_STATE *fstate;   0x28
 *     s32          first;    0x2C
 * and that is wrong in two ways, both provable from the ROM:
 *   - the two NAMES are swapped.  0x28 is the POLEF first-frame flag: init_lpfilter
 *     zeroes it (`sw zero,0x28(a0)` in the golden object), func_1001F978 passes its
 *     low byte as the POLEF `f` operand and clears it again after use.
 *   - 0x2C is an ARRAY of state pointers, one per bus -- func_1001F978 indexes it
 *     with its `bus` parameter (`lw a0,0x2C(a0+bus*4)`).  A scalar pointer there
 *     would need a second load and cannot produce that instruction.
 * Shadowed file-locally rather than edited into the shared header, because
 * init_1CBF0.c is byte-identical under either naming and must not be disturbed.
 */
typedef struct {
    s16   fc;                   /* 0x00 */
    s16   fgain;                /* 0x02 */
    s32   unk4;                 /* 0x04 */
    union {
        s16  fccoef[16];
        s64  force_aligned;
    } fcvec;                    /* 0x08 */
    s32   first;                /* 0x28 */
    void *fstate[1];            /* 0x2C */
} LowPass;

/* The resampler stage hanging off a voice.  Only the four fields below are touched
 * here; the 0x14 slot is an ARRAY (func_1001F28C loads state[bus] as
 * `lw a0,0x14(unk24 + bus*4)`), which together with `first` at 0x28 fixes the two
 * pointers at 0x14/0x18 and leaves ratio/upitch at 0x1C/0x20.
 */
typedef struct {
    u8    pad0[0x14];
    void *state[2]; /* 0x14 */
    f32   ratio;    /* 0x1C */
    s32   upitch;   /* 0x20 */
    f32   delta;    /* 0x24 */
    s32   first;    /* 0x28 */
} Resampler;

/* One synthesiser voice, stride 0x28 (func_1001E530 and func_1001ED6C both index the
 * array at SynBufs::unk4 with a 0x28 multiply).  0x10/0x14/0x1C are the f32 triple
 * that func_1001FA78 -- declared as an f32[4][4] -- reads as arg0[1][0], arg0[1][1]
 * and arg0[1][3]: increment, phase and depth of the pitch LFO.  0x08/0x0A/0x0C are
 * the three mix gains (dry, wet-return and FX send).
 */
typedef struct {
    s32        unk0;    /* 0x00 */
    s32        unk4;    /* 0x04 */
    s16        unk8;    /* 0x08 */
    s16        unkA;    /* 0x0A */
    s16        unkC;    /* 0x0C */
    u8         padE[0x2];
    f32        unk10;   /* 0x10 */
    f32        unk14;   /* 0x14 */
    s32        unk18;   /* 0x18 */
    f32        unk1C;   /* 0x1C */
    LowPass   *unk20;   /* 0x20 */
    Resampler *unk24;   /* 0x24 */
} Voice;                /* 0x28 */

/* The per-bus DRAM ring buffers, plus the voice array they feed.  unk0 is the ring
 * length in 16-bit samples, so unk0*2 is its length in bytes; unk20[bus] is the ring
 * base and unk28[bus] the current head.  Both transfer helpers below treat a DRAM
 * address below the base as belonging to the previous lap and fold it forward by one
 * ring length, then split the DMA at the wrap point when it would run past the end.
 * Both arrays are two entries: they are 8 bytes apart and both are indexed by bus.
 */
typedef struct {
    s32    unk0;      /* 0x00 */
    Voice *unk4;      /* 0x04 */
    u8     unk8;      /* 0x08 -- voice count */
    u8     pad9[0x17];
    u32    unk20[2];  /* 0x20 */
    s32    unk28[2];  /* 0x28 */
} SynBufs;

/* n_libaudio.h leaves N_ALAuxBus_s opaque; the stride is 0x44 (n_alSynNew allocates
 * it that way) and the FX state pointer this file wants sits at 0x1C. */
typedef struct {
    u8       pad0[0x1C];
    SynBufs *unk1C;   /* 0x1C */
    u8       pad20[0x24];
} FxBus;              /* 0x44 */

Acmd *func_100210C0(s16 *outp, Acmd *p, s32 bus, s32 *cmdCount);
Acmd *func_1001F28C(SynBufs *g, Voice *v, s32 bus, s32 arg3, Acmd *p);
Acmd *func_1001F5A4(SynBufs *g, s32 bus, u32 dramOffset, s32 dmemOffset, s32 nbytes,
                    Acmd *p);
Acmd *func_1001F79C(SynBufs *g, s32 bus, u32 dramOffset, s32 dmemOffset, Acmd *p);
Acmd *func_1001F978(LowPass *lp, s32 bus, s32 arg2, Acmd *p);
void init_lpfilter(LowPass *lp);

/* Build one 0xB8-sample frame of the audio command list for aux bus `bus`: mix the
   previous frame's tails down, then for every voice on every sub-bus pull its source
   samples in, resample them, apply the dry/wet/FX gains and save the result back to
   the voice's DRAM ring, advancing each ring head by 0x170 bytes and wrapping it. */
Acmd *func_1001E530(s16 *outp, Acmd *p, s32 bus) {
    Acmd    *ptr = p;
    SynBufs *g = ((FxBus *)n_syn->auxBus)[bus].unk1C;
    s16      i;
    s16      dmemB;
    s16      dmemA;
    s16      dmemL;
    s16      dmemR;
    s32      srcAddr;
    s32      endAddr;
    s32      prevEnd = 0;
    Voice   *chan;
    s32      cmdCount = 0;
    u32      b;

    ptr = func_100210C0(outp, p, bus, &cmdCount);
    dmemL = 0x7C0;
    dmemR = 0x930;
    dmemB = 0;
    dmemA = 0x170;
    if (D_800428C4[bus] == 0) {
        aMix(ptr++, 0, 0xC000, 0x7C0, dmemL);
        aMix(ptr++, 0, 0x4000, 0x930, dmemL);
    }
    ptr = func_1001F79C(g, 0, g->unk28[0], dmemL, ptr);
    if (D_800428C4[bus] != 0) {
        ptr = func_1001F79C(g, 1, g->unk28[1], 0x930, ptr);
    }
    for (b = 0; b <= D_800428C4[bus]; b++) {
        aClearBuffer(ptr++, dmemR, 0x170);
        for (i = 0; i < g->unk8; i++) {
            chan = &g->unk4[i];
            srcAddr = g->unk28[b] + -chan->unk0 * 2;
            endAddr = g->unk28[b] + -chan->unk4 * 2;
            if (D_800428C6[bus] && D_800428C4[bus]) {
                chan->unk8 = -chan->unk8;
                chan->unkA = -chan->unkA;
            }
            if (srcAddr == prevEnd) {
                s16 tmp = dmemA;
                dmemA = dmemB;
                dmemB = tmp;
            } else {
                ptr = func_1001F5A4(g, b, srcAddr, dmemB, 0xB8, ptr);
            }
            ptr = func_1001F28C(g, chan, b, dmemA, ptr);
            if (chan->unk8 != 0) {
                aMix(ptr++, 0, (u16)chan->unk8, dmemB, dmemA);
                if (chan->unk24 == 0 && chan->unk20 == 0) {
                    ptr = func_1001F79C(g, b, endAddr, dmemA, ptr);
                }
            }
            if (chan->unkA != 0) {
                aMix(ptr++, 0, (u16)chan->unkA, dmemA, dmemB);
                ptr = func_1001F79C(g, b, srcAddr, dmemB, ptr);
            }
            if (chan->unk20 != 0) {
                ptr = func_1001F978(chan->unk20, b, dmemA, ptr);
            }
            if (chan->unk24 == 0) {
                ptr = func_1001F79C(g, b, endAddr, dmemA, ptr);
            }
            if (chan->unkC != 0) {
                if (D_800428C4[bus] != 0) {
                    aMix(ptr++, 0, (u16)chan->unkC, dmemA, dmemR);
                } else {
                    u32 vol;

                    vol = chan->unkC * 1.4142f;
                    if (vol >= 0x8000) {
                        vol = 0x7FFF;
                    }
                    aMix(ptr++, 0, (u16)vol, dmemA, dmemR);
                }
            }
            prevEnd = g->unk28[b] + chan->unk4 * 2;
        }
        if (D_800428C4[bus] != 0 && b == 0) {
            ptr = func_1001F5A4(g, 1, g->unk28[1], dmemL, 0xB8, ptr);
            if (D_800428C6[bus]) {
                aMix(ptr++, 0, 0x5A82, dmemR, 0x650);
            } else {
                aMix(ptr++, 0, 0x5A82, dmemR, 0x4E0);
            }
        } else {
            /* Original-game empty else, and it is load-bearing SOURCE, not a codegen
               hack.  IDO -g emits an if/else's merge label plus an explicit
               `b <end of the enclosing if>; nop` only when the enclosing if HAS an
               else; with the else deleted the two labels collapse and this function
               compiles to 525 instructions against golden's 527 -- i.e. deleting it
               drops us BELOW golden, which is the definition of load-bearing.  Both
               ways were measured: with it, zero instruction mismatches; without it,
               two instructions short at exactly this merge point.  A standalone
               4-construct probe confirms an empty compound statement, a bare `;` and
               deeper if-nesting all fail to reproduce it -- only an empty else (or a
               goto to the next statement) does. */
        }
        aDMEMMove(ptr++, dmemR, 0x7C0, 0x170);
        g->unk28[b] += 0x170;
        if (g->unk28[b] > g->unk20[b] + g->unk0 * 2) {
            g->unk28[b] -= g->unk0 * 2;
        }
    }
    return ptr;
}

/* n_alSynSetFXParam's back end.  `arg1` packs a parameter selector in its low 3 bits
   and a voice index in the rest; `arg2` points at the new value.  The switch writes the
   selected field of voice `idx` -- delay start/end (converted from milliseconds to
   8-byte-aligned sample offsets), the three mix gains, the LFO increment, or the
   low-pass cutoff -- then re-clamps the delay window against the bus's ring length and
   re-derives the LFO depth from the new window width.  Case 6 is the odd one: it only
   loads the f32 local, and the `sel != 6` test below is what stops that local being
   overwritten before it is used.

   `val` IS DECLARED `int`, NOT `s32`, AND THAT IS LOAD-BEARING SOURCE, not a spelling
   trick.  In this codebase ultratypes.h has `typedef long s32`, so `n_syn->outputRate`
   is a `long` while a plain `int` local is not: C89's usual arithmetic conversions then
   put a widening node on the LEFT operand of the multiply below.  IDO canonicalises a
   commutative `variable * temp` by evaluating the temp first, so with `s32 val` the
   global deref is evaluated first and `multu` comes out as (outputRate, val); the
   conversion node makes the left side a temp too, restoring golden's evaluation order
   and its (val, outputRate) operands.  Measured: `int` 0, `s32` 101 -- and the 101 is
   pure register naming, identical instruction count and order.  The only other spelling
   that reaches 0 is a no-op `(s32)val` cast, which was refused as a forcer. */
s32 func_1001ED6C(SynBufs *arg0, s32 arg1, s32 *arg2) {
    SynBufs *g = arg0;
    s32 sel = arg1 & 7;
    s32 idx = arg1 >> 3;
    int val = *arg2;
    f32 rate;

    if (idx >= g->unk8) {
        return 0;
    }
    switch (sel) {
    case 0:
        g->unk4[idx].unk0 = val * n_syn->outputRate / 1000 & ~7;
        break;
    case 1:
        g->unk4[idx].unk4 = val * n_syn->outputRate / 1000 & ~7;
        break;
    case 2:
        g->unk4[idx].unkA = val;
        break;
    case 3:
        g->unk4[idx].unk8 = val;
        break;
    case 4:
        g->unk4[idx].unkC = val;
        break;
    case 5:
        g->unk4[idx].unk10 = val / 1000.0f * 2.0f / n_syn->outputRate;
        break;
    case 6:
        rate = val;
        break;
    case 7:
        if (g->unk4[idx].unk20 != 0) {
            g->unk4[idx].unk20->fc = val;
            init_lpfilter(g->unk4[idx].unk20);
        }
        break;
    }
    if (g->unk4[idx].unk0 >= (u32)(g->unk0 - 0x10)) {
        g->unk4[idx].unk0 = g->unk0 - 0x10;
    }
    if (g->unk4[idx].unk0 >= (u32)(g->unk0 - 8)) {
        g->unk4[idx].unk0 = g->unk0 - 8;
    }
    if (g->unk4[idx].unk0 >= (u32)g->unk4[idx].unk4) {
        g->unk4[idx].unk4 = g->unk4[idx].unk0 + 8;
    }
    if (g->unk4[idx].unk24 != 0) {
        if (sel != 6) {
            if (g->unk4[idx].unk4 - g->unk4[idx].unk0 != 0) {
                rate = g->unk4[idx].unk1C /
                       (u32)(g->unk4[idx].unk4 - g->unk4[idx].unk0) * 173123.4062f;
            } else {
                rate = 0.0f;
            }
        }
        g->unk4[idx].unk1C =
            (u32)(g->unk4[idx].unk4 - g->unk4[idx].unk0) * (rate / 173123.4062f);
    }
    return 0;
}

/* The pitch/resample stage of one voice's command list.  When the voice has a
   resampler attached, run the pitch LFO for this 0xB8-sample frame, fold it into a
   fractional resample ratio, pull the (possibly ring-wrapped) source samples into
   DMEM with func_1001F5A4 and emit the A_RESAMPLE command; when it does not, just
   pull the frame straight through.  `slop` is the 8-byte DMA alignment slack of the
   source address, in samples, which is paid for at both ends: read that many extra
   samples in, then skip that many samples of DMEM on the way out. */
Acmd *func_1001F28C(SynBufs *g, Voice *v, s32 bus, s32 arg3, Acmd *p) {
    Acmd *ptr = p;
    s32 pitch;
    s32 nsamples;
    s32 dmem = 0x2E0;
    s32 dram;
    f32 pos;
    f32 incr;
    f32 lfo;
    s32 slop = 0;
    s32 span;
    s32 count = 0xB8;
    s16 seg;

    if (v->unk24 != 0) {
        span = v->unk4 - v->unk0;
        lfo = func_1001FA78((f32 (*)[4])v, count);
        lfo = lfo / span;
        lfo = (s32)(lfo * 32768.0f);
        lfo = lfo / 32768.0f;
        incr = 1.0f - lfo;
        pos = v->unk24->delta + incr * count;
        nsamples = (s32)pos;
        v->unk24->delta = pos - nsamples;
        dram = g->unk28[bus] + -(v->unk4 - v->unk18) * 2;
        slop = (dram & 7) >> 1;
        ptr = func_1001F5A4(g, bus, dram - slop * 2, dmem, nsamples + slop, ptr);
        pitch = incr * 32768.0f;
        seg = arg3 >> 8;
        n_aResample(ptr++, osVirtualToPhysical(v->unk24->state[bus]),
                    v->unk24->first, pitch, dmem + slop * 2, seg);
        v->unk24->first = 0;
        v->unk18 += nsamples - count;
    } else {
        dram = g->unk28[bus] + -v->unk4 * 2;
        ptr = func_1001F5A4(g, bus, dram, arg3, 0xB8, ptr);
    }
    return ptr;
}

/* _n_loadBuffer: DMA `nbytes/2` samples of bus `bus` from its DRAM ring buffer into
   DMEM at `dmemOffset`, splitting into two A_LOADBUFF commands when the source run
   crosses the end of the ring. */
Acmd *func_1001F5A4(SynBufs *g, s32 bus, u32 dramOffset, s32 dmemOffset, s32 nbytes,
                    Acmd *p) {
    Acmd *ptr = p;
    s32 count2;
    s32 count1;
    u32 end;
    u32 bufEnd;

    bufEnd = g->unk20[bus] + g->unk0 * 2;
    if (dramOffset < g->unk20[bus]) {
        dramOffset += g->unk0 * 2;
    }
    end = (nbytes * 2) + dramOffset;
    if (end > bufEnd) {
        count2 = (s32)(end - bufEnd) >> 1;
        count1 = (s32)(bufEnd - dramOffset) >> 1;
        n_aLoadBuffer(ptr++, count1 * 2, dmemOffset, osVirtualToPhysical(dramOffset));
        n_aLoadBuffer(ptr++, count2 * 2, dmemOffset + count1 * 2,
                      osVirtualToPhysical(g->unk20[bus]));
    } else {
        n_aLoadBuffer(ptr++, nbytes * 2, dmemOffset, osVirtualToPhysical(dramOffset));
    }
    return ptr;
}

/* _n_saveBuffer: the A_SAVEBUFF mirror of func_1001F5A4.  The length is the fixed
   0x170-byte (184-sample) synthesis frame rather than a parameter. */
Acmd *func_1001F79C(SynBufs *g, s32 bus, u32 dramOffset, s32 dmemOffset, Acmd *p) {
    Acmd *ptr = p;
    s32 count2;
    s32 count1;
    u32 end;
    u32 bufEnd;

    bufEnd = g->unk20[bus] + g->unk0 * 2;
    if (dramOffset < g->unk20[bus]) {
        dramOffset += g->unk0 * 2;
    }
    end = dramOffset + 0x170;
    if (end > bufEnd) {
        count2 = (s32)(end - bufEnd) >> 1;
        count1 = (s32)(bufEnd - dramOffset) >> 1;
        n_aSaveBuffer(ptr++, count1 * 2, dmemOffset, osVirtualToPhysical(dramOffset));
        n_aSaveBuffer(ptr++, count2 * 2, dmemOffset + count1 * 2,
                      osVirtualToPhysical(g->unk20[bus]));
    } else {
        n_aSaveBuffer(ptr++, 0x170, dmemOffset, osVirtualToPhysical(dramOffset));
    }
    return ptr;
}

/* _n_filterBuffer: emit the two-command low-pass tail of a bus's command list --
   DMA the 32-byte pole-filter coefficient vector into ADPCM coefficient DMEM, then
   run A_POLEF over it.  `arg2` carries the DRAM segment in its high bits; only
   bits 8..15 reach the command, as the top byte of the POLEF state address. */
Acmd *func_1001F978(LowPass *lp, s32 bus, s32 arg2, Acmd *p) {
    Acmd *ptr = p;
    s16 seg = arg2 >> 8;

    n_aLoadADPCM(ptr++, 32, osVirtualToPhysical(lp->fcvec.fccoef));
    n_aPoleFilter(ptr++, lp->first, lp->fgain, seg,
                  osVirtualToPhysical(lp->fstate[bus]));
    lp->first = 0;
    return ptr;
}

f32 func_1001FA78(f32 arg0[4][4], s32 arg1) {
    f32 tmp;

    arg0[1][1] += arg0[1][0] * arg1;
    if (arg0[1][1] > 2.0f) {
        arg0[1][1] -= 4.0f;
    }
    else {
        /* Original-game redundancy: this self-assignment is real code -- it emits a
           load/store round-trip of arg0[1][1] plus the branch over it (see also
           game_16EE20.c:496). It is not a codegen hack; do not delete. */
        arg0[1][1] = arg0[1][1];
    }

    tmp = arg0[1][1];
    tmp = tmp < 0.0f ? -tmp : tmp;
    tmp = tmp - 1.0f;

    return tmp * arg0[1][3];
}
