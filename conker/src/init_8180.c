#include <n_libaudio.h>

#include "macros.h"

typedef struct {
  u8 pad0[0x760];
} struct247; // something naudio related?

// Conker's extended ALSynConfig (see n_alSynNew / func_10008F90).
typedef struct {
    /* 0x00 */ s32     maxVVoices;
    /* 0x04 */ s32     maxPVoices;
    /* 0x08 */ s32     maxUpdates;
    /* 0x0C */ s32     maxFXbusses;
    /* 0x10 */ void   *dmaNew;
    /* 0x14 */ void   *unk14;
    /* 0x18 */ void   *unk18;
    /* 0x1C */ void   *unk1C;
    /* 0x20 */ void   *unk20;
    /* 0x24 */ void   *waveRom;
    /* 0x28 */ ALHeap *heap;
    /* 0x2C */ s32     outputRate;
    /* 0x30 */ u8      fxType[4];
    /* 0x34 */ void   *unk34;
    /* 0x38 */ void   *unk38;
} SynDriverConfig;

// Third argument of func_10008F90.
typedef struct {
    /* 0x00 */ s32 frequency;
    /* 0x04 */ s32 numFields;
    /* 0x08 */ s32 maxACMDSize;
} AudioSpec;

// Argument of func_100155A0 (the naudio sound player).
typedef struct {
    /* 0x00 */ s32     maxSounds;
    /* 0x04 */ s32     maxEvents;
    /* 0x08 */ s32     unk8;
    /* 0x0C */ ALHeap *heap;
    /* 0x10 */ void   *waveRom;
    /* 0x14 */ u16     maxChannels;
} SndPlayerConfig;

extern N_ALCSPlayer *D_8003C900[];
extern N_ALCSPlayer *D_8003C90C; // one past the end of D_8003C900
extern u16           D_8003C910[];
extern u16           D_8003CA3C[];
extern void         *D_8003CA48[];
extern ALCSeq        D_8003CA58[];
extern ALSeqFile    *D_8003CD40;
extern struct247     D_8003CD48[];
extern ALBank       *D_8003E368;
extern ALHeap        D_8003E370;
extern u8            D_80044B20[];

s32  allocate_memory(s32 size, s32 arg1, s32 arg2, s32 arg3);
s32  func_1502B020(s32 *arg0, s32 count, s32 dir, s32 idx);
s32  func_1502B9B4(s32 count, s32 dir, s32 idx);
s32  func_1502B8E0(void *dst, s32 size, s32 count, s32 dir, s32 idx);
void func_10008F90(SynDriverConfig *cfg, s32 pri, AudioSpec *spec);
void func_10012934(ALBankFile *file, u8 *table, s32 arg2);
void func_100046E4(s32 devAddr, void *dramAddr, u32 size);
void func_10004074(void *ptr);
void func_100131FC(ALSeqpConfig *cfg, s32 count);
void func_10015550(N_ALCSPlayer *csp, s32 arg1);
void func_100155A0(SndPlayerConfig *cfg);
void func_10017870(u8 arg0);
void func_10017944(s32 arg0, u32 arg1);

// FIXME: create header file for audio related functions
s32  func_10017A80(N_ALCSPlayer *csp);
void func_10017AF0(N_ALCSPlayer *csp, s32 arg1);
void func_10017B04(N_ALCSPlayer *arg0, s32 arg1, u8 arg2);
void func_10017B30(N_ALCSPlayer *csp);
void func_10017BB8(N_ALCSPlayer *csp, s32 arg1);
void func_10017C00(N_ALCSPlayer *csp, s32 arg1);
void func_10017C68(N_ALCSPlayer *arg0, s32 arg1, u8 arg2, u8 arg3);
void func_10017CE0(N_ALCSPlayer *arg0, s32 arg1, u8 arg2);
void func_10017D30(N_ALCSPlayer *arg0, s32 arg1, u8 arg2);
void func_10017D80(N_ALCSPlayer *arg0, u8 arg1, u8 arg2);
void func_10017DF0(N_ALCSPlayer *csp, f32 arg1, f32 arg2);
void func_10017E4C(N_ALCSPlayer *csp, u8 chan, u8 arg2);
void func_10017F10(N_ALCSPlayer *arg0, u8 arg1, u8 arg2, u8 arg3, s32 arg4);
void func_100186DC(void *arg0, void *arg1);
void func_10018790(N_ALCSPlayer *arg0, s32 arg1, u32 arg2, u32 arg3);
void func_10018D00(N_ALCSPlayer *arg0, s16 arg1);
void func_10018D50(N_ALCSPlayer *seqp);

// Brings up the whole audio system: audio heap, synthesis driver + audio
// thread, the instrument bank, the sequence-file directory (with every
// sequence length rounded up to an even byte count), the three compressed
// sequence players and finally the sound-effect player.
void func_10008180(void) {
    SndPlayerConfig sndCfg;
    ALSeqFile      *seqHdr;
    s32             seqDirSize;
    SynDriverConfig synCfg;
    s32             i;
    ALSeqpConfig    seqCfg;
    AudioSpec       spec;
    ALBankFile     *bankFile;
    s32             bankSize;
    s32             sampleRom;
    s32             waveRom;
    s32             seqRom;

    alHeapInit(&D_8003E370, D_80044B20, 0x3E000);

    synCfg.maxVVoices = 0x2C;
    synCfg.maxPVoices = 0x28;
    synCfg.maxUpdates = 0x40;
    synCfg.maxFXbusses = 2;
    synCfg.dmaNew = NULL;
    synCfg.fxType[0] = 6;
    synCfg.fxType[1] = 6;
    synCfg.outputRate = 0;
    synCfg.heap = &D_8003E370;
    spec.frequency = 22020;
    spec.numFields = 1;
    spec.maxACMDSize = 0xC00;
    synCfg.waveRom = (void *)func_1502B020(NULL, 2, 0x17, 2);
    func_10008F90(&synCfg, 0xC, &spec);

    bankSize = func_1502B9B4(2, 0x17, 0);
    bankFile = (ALBankFile *)allocate_memory(bankSize, 0xFF, 2, 0);
    func_1502B8E0(bankFile, bankSize, 2, 0x17, 0);

    sampleRom = func_1502B020(NULL, 2, 0x17, 1);
    waveRom = func_1502B020(NULL, 2, 0x17, 2);
    func_10012934(bankFile, (u8 *)waveRom, sampleRom);
    D_8003E368 = bankFile->bankArray[0];

    seqRom = func_1502B020(NULL, 2, 0x17, 3);
    seqHdr = (ALSeqFile *)allocate_memory(0x10, 1, 2, 0);
    func_100046E4(seqRom, seqHdr, 0x10);
    seqDirSize = (seqHdr->seqCount * 8) + 4;
    func_10004074(seqHdr);
    D_8003CD40 = (ALSeqFile *)allocate_memory(seqDirSize, 0xFF, 2, 0);
    func_100046E4(seqRom, D_8003CD40, ALIGN16(seqDirSize));
    alSeqFileNew(D_8003CD40, (u8 *)seqRom);

    for (i = 0; i < 150; i++) {
        D_8003C910[i] = D_8003CD40->seqArray[i].len;
        if (D_8003C910[i] & 1) {
            D_8003C910[i] = D_8003C910[i] + 1;
        }
    }

    seqCfg.maxVoices = 0x2C;
    seqCfg.maxEvents = 0x68;
    seqCfg.debugFlags = 0;
    seqCfg.maxChannels = 0x10;
    seqCfg.heap = &D_8003E370;
    func_100131FC(&seqCfg, 0x58);

    i = 0;
    do {
        D_8003CA3C[i] = 0xFFFF;
        D_8003CA48[i] = NULL;
        D_8003C900[i] = alHeapAlloc(&D_8003E370, 1, 0x90);
        n_alCSPNew(D_8003C900[i], &seqCfg);
        func_10015550(D_8003C900[i], (s32)bankFile->bankArray[0]);
        i++;
    } while (&D_8003C90C != &D_8003C900[i]); // stop at the end of the player table

    sndCfg.maxEvents = 0x40;
    sndCfg.maxSounds = 0x40;
    sndCfg.unk8 = 0x14;
    sndCfg.maxChannels = 8;
    sndCfg.heap = &D_8003E370;
    sndCfg.waveRom = (void *)waveRom;
    func_100155A0(&sndCfg);

    func_10017870(4);
    func_10017944(0, 2);
    func_10017944(1, 2);
}

void func_100084D8(u8 idx) {
    if ((n_alCSPGetState(D_8003C900[idx]) == 0) || (n_alCSPGetState(D_8003C900[idx]) == 3)) {
        func_10017AA0(D_8003C900[idx]);
    }
}

s32 func_1000853C(u8 idx) {
    return n_alCSPGetState(D_8003C900[idx]);
}

void func_10008570(u8 idx, s32 arg1) { // arg1 is OSMesgQueue ?
    func_10017AF0(D_8003C900[idx], arg1);
}

void func_100085A4(s32 arg0, s32 arg1, s32 arg2) {
}

void func_100085B8(u8 idx, s32 arg1, u8 arg2) {
    func_10017B04(D_8003C900[idx], arg1, arg2);
}

void func_100085F8(u8 idx, s32 arg1) {
    func_10017BB8(D_8003C900[idx], arg1);
}

void func_1000862C(u8 idx, s32 arg1) {
    func_10017C00(D_8003C900[idx], arg1);
}

void func_10008660(u8 idx, u8 chan, u8 arg2, s32 arg3) {
    if (arg3 > 0) {
        arg3 = (arg3 * 10) / 60;
        if (arg3 == 0) {
            arg3 = 1; // final?
        } else if (arg3 >= 128) {
            arg3 = 127; // more to come?
        }
    } else {
        arg3 = 0; // empty?
    }
    func_10017C68(D_8003C900[idx], chan, arg2, arg3);
}

void func_100086FC(u8 idx, u8 arg1, u8 arg2) {
    func_10017CE0(D_8003C900[idx], arg1, arg2);
}

void func_10008744(u8 idx, u8 arg1, u8 arg2) {
    func_10017D80(D_8003C900[idx], arg1, arg2);
}

void func_10008790(u8 idx, s32 mask, u8 arg2, s32 arg3) {
    s32 chan;

    for (chan = 0; chan < 16; chan++)
    {
        if ((1 << chan) & mask) {
            func_10008660(idx, chan, arg2, arg3);
        }
    }
}

void func_10008824(u8 idx, u8 arg1, u8 arg2) {
    func_10017D30(D_8003C900[idx], arg1, arg2);
}

void func_1000886C(u8 idx, s32 mask, u8 arg2) {
    s32 chan;

    for (chan = 0; chan < 16; chan++)
    {
        if ((1 << chan) & mask) {
            func_10008824(idx, chan, arg2);
        }
    }
}

void func_100088F0(u8 idx, s32 mask, s32 enable) {
    s32 chan;

    for (chan = 0; chan < 16; chan++)
    {
        if ((1 << chan) & mask) {
            if (enable) {
                func_1000862C(idx, chan);
            } else {
                func_100085F8(idx, chan);
            }
        }
    }
}

void func_10008988(u8 idx, s32 mask, s32 enable) {
    s32 chan;

    for(chan = 0; chan < 16; chan++) // 16 channels
    {
        if ((1 << chan) & mask) {
            if (enable != 0) {
                D_8003C900[idx]->chanMask |= mask; // enable
            } else {
                D_8003C900[idx]->chanMask &= (mask ^ 0xFFFF); // disable
            }
        }
    }
}

// is this n_alCSPGetChlVol ?
u8 func_10008A4C(u8 idx, u8 chan) {
    return D_8003C900[idx]->chanState[chan].unkD; // do we assume this is volume?
}

void func_10008A94(u8 idx, s32 mask, s32 arg2) {
    s32 chan;

    for(chan = 0; chan < 16; chan++)
    {
        if (((1 << chan) & mask) != 0) {
            func_10017E4C(D_8003C900[idx], chan, arg2);
        }
    }
}

void func_10008B2C(u8 idx) {
      n_alCSPGetTempo(D_8003C900[idx]);
}

void func_10008B60(u8 idx, u8 arg1, u8 arg2, u8 arg3, s32 arg4) {
    func_10017F10(D_8003C900[idx], arg1, arg2, arg3, arg4);
}

void func_10008BC0(u8 idx, f32 arg1, f32 arg2) {
    func_10017DF0(D_8003C900[idx], arg1, arg2);
}

void func_10008C04(u8 idx, u8 arg1, s32 arg2) {
    func_10018790(&D_8003CA58[idx], &D_8003CD48[idx], arg1, arg2);
}

void func_10008C6C(u8 idx, u8 arg1) {
    func_100186DC(&D_8003CA58[idx], &D_8003CD48[idx].pad0[arg1 * 0xEC]);
}

#pragma GLOBAL_ASM("asm/nonmatchings/init_8180/func_10008CE8.s")
// NON-MATCHING: 80% of the way there
// s32 func_10008CE8(u8 idx, u16 arg1) {
//     s32 sp3C;
//     ALCSeq *temp_s0_3;
//     u32 i;
//
//     i = 0;
//     func_10018C60(&D_8003C900[idx]);
//     while ((n_alCSPGetState(&D_8003C900[idx]) != 0) && (i < 2000000)) {
//         i++;
//     };
//
//     if (i >= 2000000) {
//         func_10018C60(&D_8003C900[idx]);
//         while ((n_alCSPGetState(&D_8003C900[idx]) != 0) && (i < 4000000)) {
//             i++;
//         }
//     }
//
//     if (arg1 != D_8003CA3C[idx]) {
//         if (D_8003CA48[idx] != NULL) {
//             func_10004074(&D_8003CA48[idx]); // de-init?
//             D_8003CA48[idx] = NULL;
//         }
//
//         sp3C = D_8003CD40[arg1].unk4;
//         temp_s0_3 = allocate_memory(&D_8003C910[arg1], 0xFF, 2, 2);
//         if (temp_s0_3 == NULL) {
//             return -1;
//         }
//         func_10004514(sp3C, temp_s0_3, ALIGN16(D_8003C910[arg1]), 1);
//         D_8003CA3C[idx] = arg1;
//       }
//
//     n_alCSeqNew(&D_8003CA58[idx], &D_8003CA48[idx]);
//     func_10018CB0(&D_8003C900[idx], &D_8003CA58[idx]);
//     func_10017B30(&D_8003C900[idx]);
//
//     return 0;
// }

void func_10008EE0(u8 idx, s32 arg1) {
    func_10018D00(D_8003C900[idx], arg1);
}

void func_10008F24(u8 idx) {
    // AL_TRACK_END
    func_10018C60(D_8003C900[idx]);
}

void func_10008F58(u8 idx) {
    func_10018D50(D_8003C900[idx]);
}
