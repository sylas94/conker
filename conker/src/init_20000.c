#include "n_synthInternals.h"

typedef struct { u32 w0; u32 w1; } Cmd;

extern s16 D_8002BC10[];
extern s16 D_8002BD0E[];

/* Output-mode flags set by init_17870.c: C0 = stereo/headphone, C1 = mono, C2 = headphone. */
extern u8 D_800428C0;
extern u8 D_800428C1;
extern u8 D_800428C2;

Cmd *func_10020ABC(N_PVoice *filter, s16 *outp, s16 *inp, s32 sampleOffset, Cmd *p);
s16  _getVol(s16 ivol, s32 samples, s16 ratem, u16 ratel);
s32  func_10021C40(N_PVoice *f, s32 paramID, void *param);

/* n_alEnvmixerPull: drain the voice's parameter list, emitting one RSP sub-frame per
   parameter delta, then emit the remainder of the 184-sample frame. */
Cmd *func_10020000(N_PVoice *f, s32 sampleOffset, Cmd *p) {
    Cmd      *ptr = p;
    N_PVoice *e = f;
    s16       outp;
    u32       lastDelta;
    u32       delta = sampleOffset;
    s32       deltaSamples;
    s16       inp = 0;
    s32       vol;
    ALParam  *thisCmd;
    s32       count = FIXED_SAMPLE;

    outp = 0;

    while (e->em_ctrlList != NULL) {
        lastDelta = delta;
        delta = e->em_ctrlList->delta;
        deltaSamples = ((delta - lastDelta + 0xB7) / 0xB8) * 0xB8;
        if (deltaSamples == 0) {
            delta = lastDelta;
        }
        if (deltaSamples > count) {
            break;
        }

        switch (e->em_ctrlList->type) {
            case AL_FILTER_START_VOICE_ALT: {
                ALStartParamAlt *startParam = (ALStartParamAlt *)e->em_ctrlList;
                s32              startVol;

                if (startParam->unity) {
                    e->rs_upitch = 1;
                }
                func_10021C40(e, AL_FILTER_SET_WAVETABLE, startParam->wave);
                e->em_motion = AL_PLAYING;
                e->em_first = 1;
                e->em_delta = 0;
                e->em_segEnd = ((startParam->samples + 0xB7) / 0xB8) * 0xB8;
                startVol = (startParam->volume + startParam->volume) / 2;
                e->em_volume = startVol;
                e->em_pan = startParam->pan;
                e->em_dryamt = D_8002BC10[startParam->fxMix & 0x7F] & 0xFFFC;
                if (D_800428C0 != 0) {
                    e->em_dryamt |= startParam->fxMix >> 7;
                }
                e->em_wetamt = D_8002BD0E[-(startParam->fxMix & 0x7F)] & 0xFFFC;
                if (D_800428C2 != 0) {
                    e->em_pan = (e->em_pan >> 1) + 0x20;
                } else if (D_800428C1 != 0) {
                    e->em_pan = 0x40;
                }
                if (startParam->samples != 0) {
                    e->em_cvolL = 1;
                    e->em_cvolR = 1;
                } else {
                    e->em_cvolL = (D_8002BC10[e->em_pan] * e->em_volume) >> 15;
                    e->em_cvolR = (D_8002BD0E[-e->em_pan] * e->em_volume) >> 15;
                }
                e->rs_ratio = startParam->pitch;
                e->unkA2 = startParam->unk15;
                e->unkA0 = startParam->unk18;
                e->unkC8 = 1;
                e->unk99 = startParam->unk14;
                break;
            }

            case AL_FILTER_SET_VOLUME:
            case AL_FILTER_SET_PAN:
            case AL_FILTER_SET_FXAMT:
                ptr = func_10020ABC(e, &outp, &inp, deltaSamples, ptr);
                if (e->em_delta >= e->em_segEnd) {
                    e->em_ltgt = (D_8002BC10[e->em_pan] * e->em_volume) >> 15;
                    e->em_rtgt = (D_8002BD0E[-e->em_pan] * e->em_volume) >> 15;
                    e->em_delta = e->em_segEnd;
                    e->em_cvolL = e->em_ltgt;
                    e->em_cvolR = e->em_rtgt;
                } else {
                    e->em_cvolL = _getVol(e->em_cvolL, e->em_delta, e->em_lratm, e->em_lratl);
                    e->em_cvolR = _getVol(e->em_cvolR, e->em_delta, e->em_rratm, e->em_rratl);
                }
                if (e->em_cvolL == 0) {
                    e->em_cvolL = 1;
                }
                if (e->em_cvolR == 0) {
                    e->em_cvolR = 1;
                }
                if (e->em_ctrlList->type == AL_FILTER_SET_PAN) {
                    if (D_800428C2 != 0) {
                        e->em_pan = ((s16)e->em_ctrlList->data.i >> 1) + 0x20;
                    } else if (D_800428C1 != 0) {
                        e->em_pan = 0x40;
                    } else {
                        e->em_pan = e->em_ctrlList->data.i;
                    }
                }
                if (e->em_ctrlList->type == AL_FILTER_SET_VOLUME) {
                    e->em_delta = 0;
                    vol = e->em_ctrlList->data.i;
                    vol = (vol + vol) / 2;
                    e->em_volume = vol;
                    e->em_segEnd = ((e->em_ctrlList->moredata.i + 0xB7) / 0xB8) * 0xB8;
                }
                if (e->em_ctrlList->type == AL_FILTER_SET_FXAMT) {
                    if (((e->em_dryamt & 1) ^ (e->em_wetamt & 1) ^
                         ((e->em_ctrlList->data.i + 1) >> 7)) != 0) {
                        if (D_800428C0 != 0) {
                            if (e->em_pan > 0x40) {
                                e->em_dryamt ^= 1;
                                if (e->em_pan < 0x6F) {
                                    e->em_dryamt |= 2;
                                }
                            } else {
                                e->em_wetamt ^= 1;
                                if (e->em_pan > 0x10) {
                                    e->em_wetamt |= 2;
                                }
                            }
                        }
                    }
                    e->em_dryamt =
                        (D_8002BC10[e->em_ctrlList->data.i & 0x7F] & 0xFFFC) | (e->em_dryamt & 3);
                    e->em_wetamt =
                        (D_8002BD0E[-(e->em_ctrlList->data.i & 0x7F)] & 0xFFFC) | (e->em_wetamt & 3);
                }
                e->em_first = 1;
                break;

            case AL_FILTER_START_VOICE: {
                ALStartParam *startParam = (ALStartParam *)e->em_ctrlList;

                if (startParam->unity) {
                    e->rs_upitch = 1;
                }
                func_10021C40(e, AL_FILTER_SET_WAVETABLE, startParam->wave);
                e->em_motion = AL_PLAYING;
                break;
            }

            case AL_FILTER_STOP_VOICE:
                ptr = func_10020ABC(e, &outp, &inp, deltaSamples, ptr);
                n_alEnvmixerParam(e, AL_FILTER_RESET, 0);
                break;

            case AL_FILTER_FREE_VOICE: {
                N_ALFreeParam *freeParam = (N_ALFreeParam *)e->em_ctrlList;

                freeParam->pvoice->offset = 0;
                _n_freePVoice(freeParam->pvoice);
                break;
            }

            case AL_FILTER_SET_PITCH:
                ptr = func_10020ABC(e, &outp, &inp, deltaSamples, ptr);
                e->rs_ratio = e->em_ctrlList->data.f;
                break;

            case AL_FILTER_SET_UNITY_PITCH:
                ptr = func_10020ABC(e, &outp, &inp, deltaSamples, ptr);
                e->rs_upitch = 1;
                break;

            case AL_FILTER_SET_WAVETABLE:
                ptr = func_10020ABC(e, &outp, &inp, deltaSamples, ptr);
                func_10021C40(e, AL_FILTER_SET_WAVETABLE, (void *)e->em_ctrlList->data.i);
                break;

            default:
                ptr = func_10020ABC(e, &outp, &inp, deltaSamples, ptr);
                n_alEnvmixerParam(e, e->em_ctrlList->type, (void *)e->em_ctrlList->data.i);
                break;
        }

        inp += deltaSamples * 2;
        count -= deltaSamples;
        thisCmd = e->em_ctrlList;
        e->em_ctrlList = e->em_ctrlList->next;
        if (e->em_ctrlList == NULL) {
            e->em_ctrlTail = NULL;
        }
        _n_freeParam(thisCmd);
    }

    ptr = func_10020ABC(e, &outp, &inp, count, ptr);
    if (e->em_delta > e->em_segEnd) {
        e->em_delta = e->em_segEnd;
    }
    return ptr;
}

s32 n_alEnvmixerParam(N_PVoice *filter, s32 paramID, void *param) {
    N_PVoice  *e = filter;

    switch (paramID) {
      case (AL_FILTER_ADD_UPDATE):
          if (e->em_ctrlTail) {
              e->em_ctrlTail->next = (ALParam *)param;
          } else {
              e->em_ctrlList = (ALParam *)param;
          }
          e->em_ctrlTail = (ALParam *)param;
          break;
      case (AL_FILTER_RESET):
          e->em_first = 1;
          e->em_motion = AL_STOPPED;
          e->em_volume = 1;
          e->em_segEnd = 0;
          e->rs_delta  = 0.0;
          e->rs_first  = 1;
          e->rs_upitch = 0;
          n_alLoadParam(e, AL_FILTER_RESET, param);
          break;
      case (AL_FILTER_START):
          e->em_motion = AL_PLAYING;
          break;
      default:
#if 1
          n_alLoadParam(e, paramID, param);
#else
          n_alResampleParam(e, paramID, param); // TODO
#endif
          break;
  }
  return 0;
}

/*
 * Shadow of ALWaveTable: Rare uses the two bytes the union's alignment leaves
 * free after base/len/type/flags as a "wave is in use" marker.
 */
typedef struct {
    u8 pad0[0xA];
    /* 0x0A */ u8 inUse;
} WaveTable;

Cmd *func_10022040(N_PVoice *voice, s16 *outp, s32 arg2, Cmd *p);
s16 _getRate(f32 arg0, f32 arg1, s32 arg2, u16 *arg3);

/* _pullSubFrame.  `inp` is never read here -- the caller advances it -- but it really is
   a pointer: n_alEnvmixerPull passes &inp, not a sample count. */
Cmd *func_10020ABC(N_PVoice *filter, s16 *outp, s16 *inp, s32 sampleOffset, Cmd *p) {
    Cmd *ptr;
    N_PVoice *e;

    ptr = p;
    e = filter;

    if (e->dc_table != NULL) {
        ((WaveTable *)e->dc_table)->inUse = 1;
    }

    if ((e->em_motion != AL_PLAYING) || (sampleOffset == 0)) {
        return ptr;
    }

    ptr = func_10022040(e, outp, sampleOffset, p);

    if (e->em_first != 0) {
        Cmd *volLCmd;
        Cmd *volRCmd;
        Cmd *rateCmd;
        Cmd *envCmd;

        e->em_first = 0;

        e->em_ltgt = (D_8002BC10[e->em_pan] * e->em_volume) >> 15;
        e->em_lratm = _getRate(e->em_cvolL, e->em_ltgt, e->em_segEnd, &e->em_lratl);
        e->em_rtgt = (D_8002BD0E[-e->em_pan] * e->em_volume) >> 15;
        e->em_rratm = _getRate(e->em_cvolR, e->em_rtgt, e->em_segEnd, &e->em_rratl);

        volLCmd = ptr++;
        volLCmd->w0 = (e->em_cvolL & 0xFFFF) | 0x09060000;
        volLCmd->w1 = ((e->em_dryamt & 0xFFFF) << 16) | (e->em_wetamt & 0xFFFF);

        volRCmd = ptr++;
        volRCmd->w0 = (e->em_rtgt & 0xFFFF) | 0x09040000;
        volRCmd->w1 = ((e->em_rratm & 0xFFFF) << 16) | (e->em_rratl & 0xFFFF);

        rateCmd = ptr++;
        rateCmd->w0 = (e->em_ltgt & 0xFFFF) | 0x09000000;
        rateCmd->w1 = ((e->em_lratm & 0xFFFF) << 16) | (e->em_lratl & 0xFFFF);

        envCmd = ptr++;
        envCmd->w0 = (e->em_cvolR & 0xFFFF) | 0x03010000;
        envCmd->w1 = osVirtualToPhysical(e->em_state);
    } else {
        Cmd *contCmd;

        contCmd = ptr++;
        contCmd->w0 = 0x03000000;
        contCmd->w1 = osVirtualToPhysical(e->em_state);
    }

    outp[0] += 0x170;
    e->em_delta += 0xB8;

    if ((e->em_dryamt & 2) || (e->em_wetamt & 2)) {
        e->em_dryamt &= ~2;
        e->em_wetamt &= ~2;
        e->em_first = 1;
    }

    return ptr;
}

s16 _getRate(f32 arg0, f32 arg1, s32 arg2, u16 *arg3) {
    s16 spE;
    s16 spC;
    f32 sp8;
    f32 sp4;
    f32 sp0;

    if (arg2 == 0) {
        if (arg0 <= arg1) {
            *arg3 = 0xFFFF;
            return 0x7FFF;
        } else {
            *arg3 = 0;
            return -0x8000;
        }
    }
    sp8 = 1.0f / (f32) arg2;

    if (arg1 < 1.0f) {
        arg1 = 1.0f;
    }
    if (arg0 <= 0.0f) {
        arg0 = 1.0f;
    }
    sp4 = (arg1 - arg0) * sp8 * 8.0f;
    spE = (s16) (s32) sp4;
    sp0 = sp4 - (f32) spE;
    spE = spE - 1;
    sp0 = sp0 + 1.0f;
    spC = (s16) (s32) sp0;
    spE = spE + spC;
    sp0 = sp0 - (f32) spC;
    *arg3 = (u32) (65535.0f * sp0);
    return spE;
}

s16 _getVol(s16 ivol, s32 samples, s16 ratem, u16 ratel)
{
    s32 tmp1;
#ifdef AUD_PROFILE
    lastCnt[++cnt_index] = osGetCount();
#endif

    samples >>= 3;
    if (samples == 0){
        return ivol;
    }

    tmp1 = ratel * samples;
    tmp1 >>= 16;
    tmp1 += ratem * samples;
    ivol += tmp1;

#ifdef AUD_PROFILE
    PROFILE_AUD(vol_num, vol_cnt, vol_max, vol_min);
#endif
    return ivol;
}
