#include "n_synthInternals.h"

extern f32 D_8002C820;
extern f32 sqrtf(f32);

typedef struct { u32 w0; u32 w1; } Cmd;

/*
 * Local shadows.  n_synthInternals.h declares N_PVoice::unk99 as s8, but this
 * routine reads it as an unsigned priority (lbu), and the aux-bus source list
 * is walked through an ALLink that sits 8 bytes into the record, neither of
 * which the shared header describes.
 */
typedef struct AuxPVoice {
    /* 0x00 */ u8              pad0[0x99];
    /* 0x99 */ u8              priority;
} AuxPVoice;

typedef struct AuxVoice {
    /* 0x00 */ u8              pad0[0x8];
    /* 0x08 */ AuxPVoice      *pvoice;
} AuxVoice;

typedef struct AuxSrc {
    /* 0x00 */ u8              pad0[0x8];
    /* 0x08 */ struct AuxSrc  *next;
    /* 0x0C */ struct AuxSrc  *prev;
    /* 0x10 */ AuxVoice       *vvoice;
} AuxSrc;

typedef struct {
    /* 0x00 */ u8              pad0[0x14];
    /* 0x14 */ AuxSrc         *sources;
    /* 0x18 */ u8              pad18[0x2C];
} AuxBus;

Cmd *func_10020000(AuxSrc *src, s16 *outp, Cmd *p);

Cmd *func_100210C0(s16 *outp, Cmd *p, s32 bus, s32 *cmdCount) {
    Cmd    *ptr;
    AuxBus *b;
    AuxSrc *src;
    s32     count;
    u32     maxPri;
    u32     gain;
    Cmd    *lCmd;
    Cmd    *rCmd;
    Cmd    *save;

    ptr = p;
    b = &((AuxBus *) n_syn->auxBus)[bus];
    count = 0;
    maxPri = 1;
    *cmdCount = 0;

    src = b->sources;
    while (src != 0) {
        src = (AuxSrc *) ((u8 *) src - 8);
        if (src->vvoice != 0 && src->vvoice->pvoice != 0 &&
            src->vvoice->pvoice->priority >= 0x40) {
            ptr = func_10020000(src, outp, ptr);
            (*cmdCount)++;
            count++;
            if (src->vvoice->pvoice->priority > maxPri) {
                maxPri = src->vvoice->pvoice->priority;
            }
        }
        src = src->next;
    }

    if (count != 0) {
        maxPri -= 0x3E;
        if (maxPri >= 7) {
            gain = (u32) (D_8002C820 / sqrtf((f32) maxPri));
        } else {
            gain = (u32) (65536.0f / (f32) maxPri);
        }

        lCmd = ptr++;
        lCmd->w0 = N_AL_MAIN_L_OUT;
        lCmd->w1 = ((gain & 0xFFFF) << 16) | (maxPri & 0xFFFF);

        rCmd = ptr++;
        rCmd->w0 = N_AL_MAIN_R_OUT;
        rCmd->w1 = ((gain & 0xFFFF) << 16) | (maxPri & 0xFFFF);
    }

    src = b->sources;
    while (src != 0) {
        src = (AuxSrc *) ((u8 *) src - 8);
        if ((src->vvoice != 0 &&
             (src->vvoice->pvoice == 0 || src->vvoice->pvoice->priority < 0x40)) ||
            (src->vvoice == 0 && bus == 0)) {
            save = ptr;
            ptr = func_10020000(src, outp, ptr);
            if (ptr != save) {
                (*cmdCount)++;
            }
        }
        src = src->next;
    }

    return ptr;
}
