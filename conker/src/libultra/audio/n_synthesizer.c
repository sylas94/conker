#include "n_synthInternals.h"

extern f32 D_8002C750;

typedef struct { u32 w0; u32 w1; } Cmd;

static s32 __n_nextSampleTime(ALPlayer **client);
s32 _n_timeToSamplesNoRound(s32 micros);
Cmd *func_1001FB40(s32 arg0, Cmd *arg1);
s32  func_1001E4A0(s16 arg0, s32 arg1, s32 arg2);
void func_1001E530(s32 arg0, void *arg1, s32 arg2);

typedef struct AuxBusData_s {
    u8    pad0[0x2];
    u16   unk2;     /* 0x02 */
    u8    pad4[0x28];
    void *unk2C;    /* 0x2C */
    void *unk30;    /* 0x30 */
    u8    pad34[0x4];
} AuxBusData;       /* 0x38 */

typedef struct {
    u8          pad0[0x14];
    s32         unk14;  /* 0x14 */
    s32         unk18;  /* 0x18 */
    s32         unk1C;  /* 0x1C */
    u8          pad20[0x20];
    AuxBusData *unk40;  /* 0x40 */
} AuxBus;           /* 0x44 */

typedef struct {
    u8    pad0[0x4];
    s32   unk4;     /* 0x04 */
    u8    pad8[0xC];
} MainBus;          /* 0x14 */

typedef struct {
    u8    pad0[0x10];
    s32   unk10;    /* 0x10 */
    u8    pad14[0xBC];
} PVoiceArr;        /* 0xD0 */

typedef struct UpdElem_s {
    struct UpdElem_s *unk0;
    u8    pad4[0x20];
} UpdElem;          /* 0x24 */

typedef struct {
    void    *unk0;  /* 0x00 */
    ALLink   unk4;  /* 0x04 */
    ALLink   unkC;  /* 0x0C */
    ALLink   unk14; /* 0x14 */
    s32      unk1C; /* 0x1C */
    s32      unk20; /* 0x20 */
    s32      unk24; /* 0x24 */
    s32      unk28; /* 0x28 */
    s32      unk2C; /* 0x2C */
    s32      unk30; /* 0x30 */
    s32      unk34; /* 0x34 */
    s32      unk38; /* 0x38 */
    s32      unk3C; /* 0x3C */
    void    *unk40; /* 0x40 */
    MainBus *unk44; /* 0x44 */
    AuxBus  *unk48; /* 0x48 */
    s32      unk4C; /* 0x4C */
    s32      unk50; /* 0x50 */
    s32      unk54; /* 0x54 */
    s32      unk58; /* 0x58 */
} SynN;

typedef struct {
    u8    pad0[0x4];
    s32   unk4;     /* 0x04 */
    s32   unk8;     /* 0x08 */
    s32   unkC;     /* 0x0C */
    s32   unk10;    /* 0x10 */
    s32   unk14;    /* 0x14 */
    s32   unk18;    /* 0x18 */
    s32   unk1C;    /* 0x1C */
    s32   unk20;    /* 0x20 */
    s32   unk24;    /* 0x24 */
    s32   unk28;    /* 0x28 */
    s32   unk2C;    /* 0x2C */
    u8    unk30[1]; /* 0x30 */
} SynConfig;

#define SYN ((SynN *)n_syn)
#define CFG ((SynConfig *)c)

void n_alSynNew(ALSynConfig *c) {
    s32 i;
    s32 j;
    PVoiceArr *pvoice;
    PVoiceArr *pvoiceBase;
    s32 heap;
    UpdElem *updBase;
    UpdElem *upd;
    ALLink *link;
    ALLink *to;

    heap = CFG->unk28;
    SYN->unk0 = 0;
    SYN->unk4C = CFG->unk4;
    SYN->unk20 = 0;
    SYN->unk1C = 0;
    SYN->unk54 = CFG->unk2C;
    SYN->unk58 = 0xB8;
    SYN->unk24 = CFG->unk10;
    SYN->unk28 = CFG->unk14;
    SYN->unk2C = CFG->unk18;
    SYN->unk30 = CFG->unk1C;
    SYN->unk34 = CFG->unk20;
    SYN->unk38 = CFG->unk24;
    if (CFG->unkC >= 3) {
        SYN->unk50 = 2;
    } else if (CFG->unkC <= 0) {
        SYN->unk50 = 1;
    } else {
        SYN->unk50 = CFG->unkC;
    }
    SYN->unk48 = alHeapDBAlloc(0, 0, (ALHeap *)heap, SYN->unk50, 0x44);
    for (i = 0; i < SYN->unk50; i++) {
        SYN->unk48[i].unk14 = 0;
        SYN->unk48[i].unk18 = 0;
        if (CFG->unk30[i]) {
            SYN->unk48[i].unk1C = func_1001E4A0(i, (s32)c, heap);
        } else {
            SYN->unk48[i].unk1C = 0;
        }
        SYN->unk48[i].unk40 = alHeapDBAlloc(0, 0, (ALHeap *)heap, 1, 0x38);
        SYN->unk48[i].unk40->unk2 = 0;
        SYN->unk48[i].unk40->unk2C = alHeapDBAlloc(0, 0, (ALHeap *)heap, 1, 8);
        SYN->unk48[i].unk40->unk30 = alHeapDBAlloc(0, 0, (ALHeap *)heap, 1, 8);
    }
    SYN->unk44 = alHeapDBAlloc(0, 0, (ALHeap *)heap, 1, 0x14);
    SYN->unk44->unk4 = (s32)func_1001E530;
    SYN->unk4.next = 0;
    SYN->unk4.prev = 0;
    SYN->unk14.next = 0;
    SYN->unk14.prev = 0;
    SYN->unkC.next = 0;
    SYN->unkC.prev = 0;
    pvoiceBase = alHeapDBAlloc(0, 0, (ALHeap *)heap, CFG->unk4, 0xD0);
    for (i = 0; i < CFG->unk4; i++) {
        pvoice = &pvoiceBase[i];
        link = (ALLink *)pvoice;
        to = &SYN->unk4;
        link->next = to->next;
        link->prev = to;
        if (to->next) to->next->prev = link;
        to->next = link;
        pvoice->unk10 = 0;
        alN_PVoiceNew((N_PVoice *)pvoice, (ALDMANew)SYN->unk24, (ALHeap *)heap);
    }
    for (j = 0; j < SYN->unk50; j++) {
        SYN->unk48[j].unk14 = 0;
        SYN->unk48[j].unk18 = 0;
    }
    updBase = alHeapDBAlloc(0, 0, (ALHeap *)heap, CFG->unk8, 0x24);
    SYN->unk40 = 0;
    for (i = 0; i < CFG->unk8; i++) {
        upd = &updBase[i];
        upd->unk0 = SYN->unk40;
        SYN->unk40 = upd;
    }
    SYN->unk3C = heap;
}
// void n_alSynNew(struct07 *arg0) {
//     s32 sp44;
//     // s32 sp40;
//     // void *sp3C;
//     // s32 sp38;
//     s32 sp34;
//     // s32 sp30;
//     // void *sp2C;
//     // void *sp28;
//     // void *sp24;
//     // s32 temp_t2;
//     // s32 temp_t3;
//     // s32 temp_t4;
//     // s32 temp_t9;
//
//     sp34 = arg0->unk28;
//     D_8002BA44->unk0 = 0;
//     D_8002BA44->unk4C = arg0->unk4;
//     D_8002BA44->unk20 = 0;
//     D_8002BA44->unk1C = 0;
//     D_8002BA44->unk54 = arg0->unk2C;
//     D_8002BA44->unk58 = 184;
//     D_8002BA44->unk24 = arg0->unk10;
//     D_8002BA44->unk28 = arg0->unk14;
//     D_8002BA44->unk2C = arg0->unk18;
//     D_8002BA44->unk30 = arg0->unk1C;
//     D_8002BA44->unk34 = arg0->unk20;
//     D_8002BA44->unk38 = arg0->unk24;
//     if (arg0->unkC >= 3) {
//         D_8002BA44->unk50 = 2;
//     } else if (arg0->unkC <= 0) {
//         D_8002BA44->unk50 = 1;
//     } else {
//         D_8002BA44->unk50 = (s32) arg0->unkC;
//     }
//     D_8002BA44->unk48 = alHeapDBAlloc(0, 0, sp34, D_8002BA44->unk50, 0x44);
//     sp44 = 0;
//     if (D_8002BA44->unk50 > 0) {
// loop_6:
//         (D_8002BA44->unk48 + (sp44 * 0x44))->unk14 = 0;
//         (D_8002BA44->unk48 + (sp44 * 0x44))->unk18 = 0;
//         if ((arg0 + sp44)->unk30 != 0) {
//             (D_8002BA44->unk48 + (sp44 * 0x44))->unk1C = func_1001E4A0(sp44, arg0, sp34);
//         } else {
//             (D_8002BA44->unk48 + (sp44 * 0x44))->unk1C = 0;
//         }
//         (D_8002BA44->unk48 + (sp44 * 0x44))->unk40 = alHeapDBAlloc(0, 0, sp34, 1, 0x38);
//         (D_8002BA44->unk48 + (sp44 * 0x44))->unk40->unk2 = (u16)0;
//         (D_8002BA44->unk48 + (sp44 * 0x44))->unk40->unk2C = alHeapDBAlloc(0, 0, sp34, 1, 8);
//         (D_8002BA44->unk48 + (sp44 * 0x44))->unk40->unk30 = alHeapDBAlloc(0, 0, sp34, 1, 8);
//         temp_t4 = sp44 + 1;
//         sp44 = temp_t4;
//         if (temp_t4 < D_8002BA44->unk50) {
//             goto loop_6;
//         }
//     }
//     D_8002BA44->unk44 = alHeapDBAlloc(0, 0, sp34, 1, 0x14);
//     D_8002BA44->unk44->unk4 = (s32)func_1001E530;
//     D_8002BA44->unk4 = 0;
//     D_8002BA44->unk8 = 0;
//     D_8002BA44->unk14 = 0;
//     D_8002BA44->unk18 = 0;
//     D_8002BA44->unkC = 0;
//     D_8002BA44->unk10 = 0;
//     sp38 = alHeapDBAlloc(0, 0, sp34, arg0->unk4, 0xD0);
//     sp44 = 0;
//     if (arg0->unk4 > 0) {
// loop_11:
//         sp3C = (sp44 * 0xD0) + sp38;
//         sp28 = sp3C;
//         sp24 = D_8002BA44 + 4;
//         sp28->unk0 = (s32) *sp24;
//         sp28->unk4 = sp24;
//         if (*sp24 != 0) {
//             (*sp24)->unk4 = sp28;
//         }
//         *sp24 = sp28;
//         sp3C->unk10 = 0;
//         func_1001D6E8(sp3C, D_8002BA44->unk24, sp34);
//         temp_t3 = sp44 + 1;
//         sp44 = temp_t3;
//         if (temp_t3 < arg0->unk4) {
//             goto loop_11;
//         }
//     }
//     sp40 = 0;
//     if (D_8002BA44->unk50 > 0) {
// loop_15:
//         (D_8002BA44->unk48 + (sp40 * 0x44))->unk14 = 0;
//         (D_8002BA44->unk48 + (sp40 * 0x44))->unk18 = 0;
//         temp_t2 = sp40 + 1;
//         sp40 = temp_t2;
//         if (temp_t2 < D_8002BA44->unk50) {
//             goto loop_15;
//         }
//     }
//     sp30 = alHeapDBAlloc(0, 0, sp34, arg0->unk8, 0x24);
//     D_8002BA44->unk40 = 0;
//     sp44 = 0;
//     if (arg0->unk8 > 0) {
// loop_17:
//         sp2C = (sp44 * 0x24) + sp30;
//         *sp2C = (s32) D_8002BA44->unk40;
//         D_8002BA44->unk40 = sp2C;
//         temp_t9 = sp44 + 1;
//         sp44 = temp_t9;
//         if (temp_t9 < arg0->unk8) {
//             goto loop_17;
//         }
//     }
//     D_8002BA44->unk3C = sp34;
// }

Acmd *n_alAudioFrame(Acmd *cmdList, s32 *cmdLen, s16 *outBuf, s32 outLen) {
    ALPlayer *client;
    Cmd *cmdp;
    s32 sp34;
    s16 *outp;
    Cmd *cmd0;
    Cmd *cmd1;

    cmdp = (Cmd *)cmdList;
    outp = outBuf;
    if (n_syn->head == 0) {
        *cmdLen = 0;
        return cmdList;
    }
    while ((n_syn->paramSamples = __n_nextSampleTime(&client)),
           ((u32)(n_syn->paramSamples - n_syn->curSamples) < (u32)outLen)) {
        n_syn->paramSamples = n_syn->paramSamples & ~0xF;
        client->samplesLeft += _n_timeToSamplesNoRound(client->handler(client));
    }
    n_syn->paramSamples = n_syn->paramSamples & ~0xF;
    while (outLen > 0) {
        sp34 = (n_syn->maxOutSamples < outLen) ? n_syn->maxOutSamples : outLen;
        cmdp = func_1001FB40(n_syn->curSamples, cmdp);
        cmd0 = cmdp++;
        cmd0->w0 = 0xD000000;
        cmd1 = cmdp++;
        cmd1->w0 = 0x62E0000;
        cmd1->w1 = (u32)outp;
        outLen = outLen - sp34;
        outp += sp34 * 2;
        n_syn->curSamples = n_syn->curSamples + sp34;
    }
    *cmdLen = ((u8 *)cmdp - (u8 *)cmdList) >> 3;
    _n_collectPVoices();
    return (Acmd *)cmdp;
}
// void *n_alAudioFrame(void *arg0, void *arg1, s32 arg2, u32 arg3) {
//     void *sp3C;
//     void *sp38;
//     s32 sp34;
//     s32 sp30;
//     void *sp2C;
//     void *sp28;
//     s32 temp_t5_2;
//     void *temp_t0;
//     void *temp_t1;
//     void *temp_t2;
//     void *temp_t5;
//     void *temp_t7;
//     void *temp_t8;
//     void *temp_t9;
//
//     sp38 = arg0;
//     sp30 = arg2;
//     if (*D_8002BA44 == 0) {
//         *arg1 = 0;
//         return arg0;
//     }
//     D_8002BA44->unk1C = func_10019A04(&sp3C);
//     temp_t2 = D_8002BA44;
//     if ((u32) (temp_t2->unk1C - temp_t2->unk20) < arg3) {
// loop_3:
//         temp_t7 = D_8002BA44;
//         temp_t7->unk1C = (s32) (temp_t7->unk1C & -0x10);
//         sp3C->unk10 = (s32) (sp3C->unk10 + _n_timeToSamplesNoRound(sp3C->unk8(sp3C)));
//         D_8002BA44->unk1C = func_10019A04(&sp3C);
//         temp_t5 = D_8002BA44;
//         if ((u32) (temp_t5->unk1C - temp_t5->unk20) < arg3) {
//             goto loop_3;
//         }
//     }
//     temp_t9 = D_8002BA44;
//     temp_t9->unk1C = (s32) (temp_t9->unk1C & -0x10);
//     if ((s32) arg3 > 0) {
// loop_5:
//         temp_t5_2 = D_8002BA44->unk58;
//         if (temp_t5_2 < (s32) arg3) {
//             sp34 = temp_t5_2;
//         } else {
//             sp34 = (s32) arg3;
//         }
//         sp38 = func_1001FB40(D_8002BA44->unk20, sp38);
//         temp_t0 = sp38;
//         sp38 = temp_t0 + 8;
//         sp2C = temp_t0;
//         *sp2C = 0xD000000;
//         temp_t1 = sp38;
//         sp38 = temp_t1 + 8;
//         sp28 = temp_t1;
//         sp28->unk0 = 0x62E0000;
//         sp28->unk4 = sp30;
//         arg3 = arg3 - sp34;
//         sp30 = sp30 + (sp34 * 2 * 2);
//         temp_t8 = D_8002BA44;
//         temp_t8->unk20 = (s32) (temp_t8->unk20 + sp34);
//         if ((s32) arg3 > 0) {
//             goto loop_5;
//         }
//     }
//     *arg1 = (s32) ((s32) (sp38 - arg0) >> 3);
//     _collectPVoices();
//     return sp38;
// }

ALParam *__n_allocParam(void) {
    ALParam *update = 0;

    if (n_syn->paramList) {
        update = n_syn->paramList;
        n_syn->paramList = n_syn->paramList->next;
        update->next = 0;
    }
    return update;
}


void _n_freeParam(ALParam *param)
{
  param->next = n_syn->paramList;
  n_syn->paramList = param;
}

void _n_collectPVoices(void)
{
    N_PVoice *pvoice;
    ALLink *element;
    ALLink *ln;
    ALLink *to;
    ALLink *element2;

    while ((pvoice = (N_PVoice *)n_syn->pLameList.next) != 0) {
        element = (ALLink *)pvoice;
        if (element->next)
            element->next->prev = element->prev;
        if (element->prev)
            element->prev->next = element->next;

        ln = (ALLink *)pvoice;
        to = &n_syn->pFreeList;
        ln->next = to->next;
        ln->prev = to;
        if (to->next)
            to->next->prev = ln;
        to->next = ln;

        element2 = (ALLink *)&pvoice->vvoice;
        if (element2->next)
            element2->next->prev = element2->prev;
        if (element2->prev)
            element2->prev->next = element2->next;

        pvoice->vvoice = 0;
        *(s32 *)((u8 *)pvoice + 0xC) = 0;
    }
}

void _n_freePVoice(N_PVoice *pvoice)
{
    ALLink *element;
    ALLink *ln;
    ALLink *to;

    element = (ALLink *)pvoice;
    if (element->next)
        element->next->prev = element->prev;
    if (element->prev)
        element->prev->next = element->next;

    ln = (ALLink *)pvoice;
    to = &n_syn->pLameList;
    ln->next = to->next;
    ln->prev = to;
    if (to->next)
        to->next->prev = ln;
    to->next = ln;
}

s32 _n_timeToSamplesNoRound(s32 micros) {
    f32 tmp = (((f32) micros * (f32) n_syn->outputRate) / D_8002C750) + 0.5f; // 1000000.0f
    return (s32) tmp;
}

s32 _n_timeToSamples( s32 micros)
{
  return _n_timeToSamplesNoRound( micros) & ~0xf;
}

static s32 __n_nextSampleTime(ALPlayer **client)
{
    u32 delta = 0x7fffffff;     /* max delta for s32 */
    ALPlayer *cl;

    *client = 0;

    for (cl = n_syn->head; cl != 0; cl = cl->next) {
        if ((u32)(cl->samplesLeft - n_syn->curSamples) < delta) {
            *client = cl;
            delta = cl->samplesLeft - n_syn->curSamples;
        }
    }

    return (*client)->samplesLeft;
}

