#include "n_synthInternals.h"

extern f32 D_8002C814;

// relies on jump table
#pragma GLOBAL_ASM("asm/nonmatchings/init_20000/func_10020000.s")

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

typedef struct { u32 w0; u32 w1; } Cmd;

/*
 * Shadow of ALWaveTable: Rare uses the two bytes the union's alignment leaves
 * free after base/len/type/flags as a "wave is in use" marker.
 */
typedef struct {
    u8 pad0[0xA];
    /* 0x0A */ u8 inUse;
} WaveTable;

extern s16 D_8002BC10[];
extern s16 D_8002BD0E[];

Cmd *func_10022040(N_PVoice *voice, s16 *outp, s32 arg2, Cmd *p);
s16 _getRate(f32 arg0, f32 arg1, s32 arg2, u16 *arg3);

// _pullSubFrame
Cmd *func_10020ABC(N_PVoice *filter, s16 *outp, s32 outCount, s32 sampleOffset, Cmd *p) {
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
    *arg3 = (u32) (D_8002C814 * sp0); // 65535.0f
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
