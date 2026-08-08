#include <n_libaudio.h>

extern s32 D_800E0E04;
extern u8 D_800428C4[];
extern u8 D_800428C6[];

typedef struct { u32 w0; u32 w1; } Cmd;

/* Rare's variant of libultra's ALLowPass (the aux-bus pole filter).
 * 0x0 = cutoff (fc), 0x2 = fgain, 0x8..0x27 = the 16 s16 filter
 * coefficients uploaded with A_LOADADPCM, then one A_POLEF state
 * buffer per main-out channel. */
typedef struct {
    u8  pad0[0x2];
    /* 0x2 */  s16   fgain;
    u8  pad4[0x4];
    /* 0x8 */  s32   fccoef;       /* base of the 0x20-byte coefficient vector */
    u8  padC[0x1C];
    /* 0x28 */ s32   coeffDirty;   /* set when fc/fgain change, cleared once recomputed */
    /* 0x2C */ void *fstateL;      /* A_POLEF state for main out L (0x4E0) */
    /* 0x30 */ void *fstateR;      /* A_POLEF state for main out R (0x650) */
} LowPass;

typedef struct {
    u8  pad0[0x40];
    /* 0x40 */ LowPass *lowPass;
} AuxBus;

typedef Cmd *(*Handler)(s32, Cmd *, s32);

typedef struct {
    u8  pad0[0x4];
    /* 0x4 */ Handler handler;
} MainBus;

typedef struct {
    u8  pad0[0x44];
    /* 0x44 */ MainBus *mainBus;
    /* 0x48 */ AuxBus  *auxBus;
    u8  pad4C[0x4];
    /* 0x50 */ s32      maxAuxBusses;
    /* 0x54 */ s32      outputRate;
} Synth;

void func_1001CF38(void *, f32);

#define S ((Synth *) n_syn)

Cmd *func_1001FB40(s32 sampleOffset, Cmd *cmdList) {
    Cmd *p;
    s32  i;
    s32  bus;
    Cmd *clearMain;
    Cmd *clearAux;
    Cmd *clearAuxPerBus;
    Cmd *mixAuxToL;
    Cmd *mixAuxToR;
    Cmd *mixAuxToR2;
    Cmd *mixAuxToR3;
    Cmd *mixAuxToL2;
    LowPass *lp;
    Cmd *loadCoefs;
    Cmd *polefL;
    Cmd *polefR;

    p = cmdList;
    if ((D_800E0E04 == 0) || (func_151F2E88(0xB8, &p) == 0)) {
        clearMain = p++;
        clearMain->w0 = 0x20004E0;
        clearMain->w1 = 0x2E0;
        clearAux = p++;
        clearAux->w0 = 0x20007C0;
        clearAux->w1 = 0x2E0;
    }
    bus = 0;
    for (i = 1; i < S->maxAuxBusses; i++) {
        if (S->auxBus[i].lowPass->fgain > 0) {
            bus = i;
        }
    }
    for (i = 0; i < S->maxAuxBusses; i++, bus++) {
        if (bus >= S->maxAuxBusses) {
            bus = 0;
        }
        if (i != 0) {
            clearAuxPerBus = p++;
            clearAuxPerBus->w0 = 0x20007C0;
            clearAuxPerBus->w1 = 0x2E0;
        }
        p = S->mainBus->handler(sampleOffset, p, bus);
        if (D_800428C4[bus] != 0) {
            if (D_800428C6[bus] != 0) {
                mixAuxToL = p++;
                mixAuxToL->w0 = 0xC008000;
                mixAuxToL->w1 = 0x7C004E0;
                goto block1;
            }
            mixAuxToR = p++;
            mixAuxToR->w0 = 0xC007FFF;
            mixAuxToR->w1 = 0x7C00650;
        block1:
            ;
        } else {
            if (D_800428C6[bus] != 0) {
                mixAuxToR2 = p++;
                mixAuxToR2->w0 = 0xC008000;
                mixAuxToR2->w1 = 0x7C00650;
                goto block2;
            }
            mixAuxToR3 = p++;
            mixAuxToR3->w0 = 0xC007FFF;
            mixAuxToR3->w1 = 0x7C00650;
        block2:
            mixAuxToL2 = p++;
            mixAuxToL2->w0 = 0xC007FFF;
            mixAuxToL2->w1 = 0x7C004E0;
        }
        if (S->auxBus[bus].lowPass->fgain > 0) {
            lp = S->auxBus[bus].lowPass;
            if (lp->coeffDirty != 0) {
                func_1001CF38(lp, (f32) S->outputRate);
            }
            loadCoefs = p++;
            loadCoefs->w0 = 0xB000020;
            loadCoefs->w1 = osVirtualToPhysical(&lp->fccoef);
            polefL = p++;
            polefL->w0 = 0xE0004E0;
            polefL->w1 = osVirtualToPhysical(lp->fstateL) & 0xFFFFFF & 0xFFFFFF;
            polefR = p++;
            polefR->w0 = 0xE000650;
            polefR->w1 = osVirtualToPhysical(lp->fstateR) & 0xFFFFFF & 0xFFFFFF;
            lp->coeffDirty = 0;
        }
    }
    return p;
}
