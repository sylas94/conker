#include <os_internal.h>
#include <ultraerror.h>
#include "n_synthInternals.h"

s32 _allocatePVoice(N_PVoice **pvoice, s16 priority);

typedef struct {
    u8      pad0[0x14];
    ALLink  link;       /* 0x14 */
    u8      pad1C[0x28];
} AuxBusElem;           /* size 0x44 */

typedef struct {
    u8      pad0[0x90];
    s32     offset;     /* 0x90 */
} PVoiceOff;


// s32 _allocatePVoice( N_PVoice **pvoice, s16 priority);
s32 n_alSynAllocVoice(N_ALVoice *voice, ALVoiceConfig *vc) {
    N_PVoice *pvoice = 0;
    ALParam *update;
    s32 stolen;

    voice->priority   = vc->priority;
    voice->unityPitch = vc->unityPitch;
    voice->table      = 0;
    voice->fxBus      = vc->fxBus;
    voice->state      = AL_STOPPED;
    voice->pvoice     = 0;
    voice->unk14      = (void *)vc->unk8;

    stolen = _allocatePVoice(&pvoice, vc->priority);

    if (pvoice != 0) {
        if (stolen != 0) {
            *(s32 *)((u8 *)pvoice + 0x90) = 0x228;
            (*(N_ALVoice **)((u8 *)pvoice + 0x10))->pvoice = 0;
            *(N_ALVoice **)((u8 *)pvoice + 0x10) = voice;
            voice->pvoice = pvoice;

            update = __n_allocParam();
            if (update) {
                update->delta      = n_syn->paramSamples;
                update->type       = AL_FILTER_SET_VOLUME;
                update->data.i     = 0;
                update->moredata.i = 0x170;
                n_alEnvmixerParam(voice->pvoice, AL_FILTER_ADD_UPDATE, update);
            } else {
            }
            update = __n_allocParam();
            if (update) {
                update->delta = n_syn->paramSamples + ((PVoiceOff *)pvoice)->offset;
                update->type  = AL_FILTER_STOP_VOICE;
                update->next  = 0;
                n_alEnvmixerParam(voice->pvoice, AL_FILTER_ADD_UPDATE, update);
            } else {
            }
        } else {
            ALLink *element;
            ALLink *ln;
            ALLink *to;

            *(s32 *)((u8 *)pvoice + 0x90) = 0;
            *(N_ALVoice **)((u8 *)pvoice + 0x10) = voice;
            voice->pvoice = pvoice;

            element = (ALLink *)((u8 *)pvoice + 8);
            if (element->next) element->next->prev = element->prev;
            if (element->prev) element->prev->next = element->next;

            ln = (ALLink *)((u8 *)pvoice + 8);
            to = &((AuxBusElem *)n_syn->auxBus)[vc->fxBus].link;
            ln->next = to->next;
            ln->prev = to;
            if (to->next) to->next->prev = ln;
            to->next = ln;

            *(s32 *)((u8 *)pvoice + 0x28) = 0;
        }
    }
    return (pvoice != 0);
}
// NON-MATCHING: plenty to figure out with the nlibaudio struct changes
// s32 n_alSynAllocVoice( N_ALVoice *voice, ALVoiceConfig *vc)
// {
//     N_PVoice  *pvoice = 0;
//     ALFilter *f;
//     ALParam *update;
//     s32 stolen;
//     N_PVoice *sp20;
//
// #ifdef _DEBUG
//     /* need two updates if voice is stolen */
//     if (n_syn->paramList == 0) {
//         __osError(ERR_ALSYN_NO_UPDATE, 0);
//         return 0;
//     } else if (n_syn->paramList->next == 0) {
//         __osError(ERR_ALSYN_NO_UPDATE, 0);
//         return 0;
//     }
// #endif
//
//     voice->priority     = vc->priority;
//     voice->unityPitch   = vc->unityPitch;
//     voice->table        = 0;
//     voice->fxBus        = vc->fxBus;
//     voice->state        = AL_STOPPED;
//     voice->pvoice       = 0;
//
//     voice->clientPrivate = vc->unk8;
//
//     stolen = _allocatePVoice( &pvoice, vc->priority);
//
//     if (pvoice) {    /* if we were able to allocate a voice */
//         if (stolen) {
//
//             pvoice->offset = 0x228; //512;
//             pvoice->vvoice->pvoice = 0; /* zero stolen voice */
//
// #if 1
//             pvoice->vvoice = voice;
//             voice->pvoice  = pvoice;
// #endif
//
//             /*
//              * ramp down stolen voice
//              */
//             update = __n_allocParam();
//             if (update) {
// #ifdef SAMPLE_ROUND
//                 update->delta      = SAMPLE184( n_syn->paramSamples );
// #else
//                 update->delta      = n_syn->paramSamples;
// #endif
//                 update->type       = AL_FILTER_SET_VOLUME;
//                 update->data.i     = 0;
//                 update->moredata.i = 0x170; //pvoice->offset - 64;
//
//                 n_alEnvmixerParam(voice->pvoice, AL_FILTER_ADD_UPDATE, update);
//             }
//             /*
//              * stop stolen voice
//              */
//             update = __n_allocParam();
//             if (update) {
// #ifdef SAMPLE_ROUND
//                 update->delta  = SAMPLE184( n_syn->paramSamples + pvoice->offset);
// #else
//                 update->delta  = n_syn->paramSamples + pvoice->offset;
// #endif
//                 update->type   = AL_FILTER_STOP_VOICE;
//                 update->next   = 0;
//                 n_alEnvmixerParam(voice->pvoice, AL_FILTER_ADD_UPDATE, update);
//
//             } else {
// #ifdef _DEBUG
//                 __osError(ERR_ALSYN_NO_UPDATE, 0);
// #endif
//             }
//
//         } else {
//             pvoice->offset = 0;
// #if 1
//             pvoice->vvoice = voice;
//             voice->pvoice  = pvoice;
//
//             sp20 = pvoice->vvoice; // + 8;
//             if (sp20->node.next != 0) {
//                 sp20->node.prev = sp20->node;
//             }
//             // if (sp20->unk4 != 0) {
//             //     *sp20->unk4 = (s32) sp20->unk0;
//             // }
//             // temp_t1 = pvoice + 8;
//             // sp1C = temp_t1;
//             // sp18 = D_8002BA44->unk48[vc->unk2].unk14;
//             // *temp_t1 = (s32) *sp18;
//             // sp1C->unk4 = sp18;
//             // if (*sp18 != 0) {
//             //     (*sp18)->unk4 = sp1C;
//             // }
//             // *sp18 = sp1C;
//             // pvoice->unk28 = 0;
// #endif
//         }
//
// #if 0
//         pvoice->vvoice = voice;     /* assign new voice  */
//         voice->pvoice  = pvoice;
// #endif
//
//     }
//
//     return (pvoice != 0);
// }


s32 _allocatePVoice(N_PVoice **pvoice, s16 priority) {
    N_PVoice *pv;
    N_PVoice *v;
    s32 stolen = 0;

    if ((pv = (N_PVoice *)n_syn->pLameList.next) != 0) {
        ALLink *element;
        ALLink *ln;
        ALLink *to;
        *pvoice = pv;
        element = (ALLink *)pv;
        if (element->next) element->next->prev = element->prev;
        if (element->prev) element->prev->next = element->next;
        ln = (ALLink *)pv;
        to = &n_syn->pAllocList;
        ln->next = to->next;
        ln->prev = to;
        if (to->next) to->next->prev = ln;
        to->next = ln;
    } else if ((pv = (N_PVoice *)n_syn->pFreeList.next) != 0) {
        ALLink *element;
        ALLink *ln;
        ALLink *to;
        *pvoice = pv;
        element = (ALLink *)pv;
        if (element->next) element->next->prev = element->prev;
        if (element->prev) element->prev->next = element->next;
        ln = (ALLink *)pv;
        to = &n_syn->pAllocList;
        ln->next = to->next;
        ln->prev = to;
        if (to->next) to->next->prev = ln;
        to->next = ln;
    } else {
        for (pv = (N_PVoice *)n_syn->pAllocList.next; pv != 0; pv = (N_PVoice *)pv->node.next) {
            v = pv;
            if (priority >= (*(N_ALVoice **)((u8 *)v + 0x10))->priority && *(s32 *)((u8 *)v + 0x90) == 0) {
                *pvoice = v;
                priority = (*(N_ALVoice **)((u8 *)v + 0x10))->priority;
                stolen = 1;
            }
        }
    }
    return stolen;
}
