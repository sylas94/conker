#include <n_libaudio.h>


typedef struct {
    s32 pad0;
    u8  unk4;
    s8  unk5; // used
} struct152;

typedef struct {
    s32 pad0;
    struct152 *unk4;
} struct153;

typedef struct {
    u8  pad0[0xC];
    struct153 *unkC;
    u8  pad10[0x24];
    f32 unk34;  // used
} struct154;

extern N_ALUnknownStruct1 *D_8002BA20;
extern N_ALUnknownStruct1 *D_8002BA24;
extern N_ALUnknownStruct1 *D_8002BA28;
extern N_ALSndPlayer *D_8002BA2C;
extern s16 D_8002BA30;

void func_10017298(N_ALUnknownStruct1 *arg0);
void func_10016F80(ALEventQueue *evtq, N_ALUnknownStruct1 *state, u16 typeMask);
s32  func_10015878(N_ALSndPlayer *sp);

void func_10015550(N_ALCSPlayer *csp, s32 arg1) {
    N_ALEvent event;

    event.type = 14;
    event.msg.midi.ticks = arg1;

    n_alEvtqPostEvent(&csp->evtq, &event, 0, 2);
}

/* Argument of func_100155A0; mirrors SndPlayerConfig in init_8180.c. */
typedef struct {
    /* 0x00 */ s32     maxSounds;
    /* 0x04 */ s32     maxEvents;
    /* 0x08 */ s32     unk8;
    /* 0x0C */ ALHeap *heap;
    /* 0x10 */ void   *waveRom;
    /* 0x14 */ u16     maxChannels;
} SndPlayerConfig;

/* N_ALSndPlayer plus the wave-table slot at 0x54 that n_libaudio.h lacks. */
typedef struct {
    /* 0x00 */ N_ALSndPlayer sndp;
    /* 0x54 */ void         *unk54;
} SndPlayer;

extern u16 *D_800428B8;

/* N_ALUnknownStruct1 with the header's pad34/pad44/pad4F spelled out. */
typedef struct {
    /* 0x00 */ u8    pad0[0x34];
    /* 0x34 */ f32   unk34;
    /* 0x38 */ void *unk38;
    /* 0x3C */ u8    pad3C[0x8];
    /* 0x44 */ s16   unk44;
    /* 0x46 */ u8    pad46[0x9];
    /* 0x4F */ u8    unk4F;
    /* 0x50 */ u8    unk50;
    /* 0x51 */ u8    unk51;
    /* 0x52 */ u8    pad52;
    /* 0x53 */ u8    unk53;
} struct157;

#ifndef MIN
#define MIN(a,b) (((a)<(b))?(a):(b))
#endif
#ifndef MAX
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif

/* The sound-state record.  N_ALUnknownStruct1 in n_libaudio.h models the same object
 * but pads over most of what _n_handleEvent touches; every offset below is proven by a
 * load or store in the ROM.  0x10 really is an N_ALVoice: every n_alSyn* call in here
 * is passed `state + 0x10`, and `state + 0x2C` is that voice's fxBus. */
typedef struct SndState {
    /* 0x00 */ struct SndState *next;
    /* 0x04 */ struct SndState *prev;
    /* 0x08 */ u8               pad8[0x4];
    /* 0x0C */ ALSound         *snd;
    /* 0x10 */ N_ALVoice        voice;
    /* 0x30 */ f32              ratio;    /* key-map cents ratio            */
    /* 0x34 */ f32              pitch;    /* pitch requested by the client  */
    /* 0x38 */ struct157      **owner;
    /* 0x3C */ ALBank          *bank;
    /* 0x40 */ s32              retries;
    /* 0x44 */ s16              unk44;    /* client volume  */
    /* 0x46 */ s16              unk46;    /* envelope volume */
    /* 0x48 */ s32              segEnd;
    /* 0x4C */ s16              unk4C;    /* sound index within the instrument */
    /* 0x4E */ u8               priority;
    /* 0x4F */ u8               unk4F;    /* pan   */
    /* 0x50 */ u8               unk50;    /* fxmix */
    /* 0x51 */ u8               unk51;    /* fx bus */
    /* 0x52 */ u8               unk52;
    /* 0x53 */ u8               unk53;    /* flags */
    /* 0x54 */ u8               unk54;    /* play state */
} SndState;

/* The sound player's event.  N_ALEvent's `type` is declared s16 but is read UNSIGNED
 * here (the bit-flag event codes run up to 0x8000), and the payload after `state` is a
 * plain word that some events read as a float. */
typedef struct {
    /* 0x00 */ u16       type;
    /* 0x04 */ SndState *state;
    /* 0x08 */ union { s32 i; f32 f; } arg;
    /* 0x0C */ s32       arg2;
} SndEvent;

void _n_handleEvent(SndEvent *event);

void func_100155A0(SndPlayerConfig *c) {
    u32 i;
    void *ptr;
    N_ALEvent event;

    D_8002BA2C->maxSounds = c->unk8;
    D_8002BA2C->target = 0;
    D_8002BA2C->drvr = n_syn;
    D_8002BA2C->frameTime = 16000;

    ptr = alHeapAlloc(c->heap, c->maxSounds, sizeof(N_ALUnknownStruct1));
    D_8002BA2C->sndState = ptr;
    ((SndPlayer *)D_8002BA2C)->unk54 = c->waveRom;

    ptr = alHeapAlloc(c->heap, c->maxEvents, sizeof(N_ALEventListItem));
    n_alEvtqNew(&D_8002BA2C->evtq, ptr, c->maxEvents);

    D_8002BA28 = D_8002BA2C->sndState;

    /* alLink() each sound-state record onto its predecessor to build the free
     * list.  The block-scoped ln/lst are the alLink() macro's own locals: they
     * own stack homes 0x28/0x24, which is why the two &arr[i] computations are
     * not shared.  The second operand really is &arr[i] - 1 and not &arr[i - 1]
     * -- golden scales i by 0x58 and THEN subtracts 0x58. */
    for (i = 1; i < c->maxSounds; i++) {
        N_ALUnknownStruct1 *arr = D_8002BA2C->sndState;
        {
            ALLink *ln = (ALLink *)&arr[i];
            ALLink *lst = (ALLink *)(&arr[i] - 1);
            ln->next = lst->next;
            ln->prev = lst;
            if (lst->next) {
                lst->next->prev = ln;
            }
            lst->next = ln;
        }
    }

    D_800428B8 = alHeapAlloc(c->heap, 2, c->maxChannels);
    for (i = 0; i < c->maxChannels; i++) {
        D_800428B8[i] = 0x7FFF;
    }

    D_8002BA2C->node.next = NULL;
    D_8002BA2C->node.handler = func_10015878;
    D_8002BA2C->node.clientData = D_8002BA2C;
    n_alSynAddPlayer(&D_8002BA2C->node);

    event.type = 32;
    n_alEvtqPostEvent(&D_8002BA2C->evtq, &event, D_8002BA2C->frameTime, 3);
    D_8002BA2C->nextDelta = n_alEvtqNextEvent(&D_8002BA2C->evtq, &D_8002BA2C->nextEvent);
}

s32 func_10015878(N_ALSndPlayer *sp) {
    N_ALSndPlayer *alsp;
    N_ALEvent event;

    alsp = sp;
    do {
        switch (alsp->nextEvent.type) {
        case 32:
            event.type = 32;
            n_alEvtqPostEvent(&alsp->evtq, &event, alsp->frameTime, 3);
            break;
        default:
            _n_handleEvent((SndEvent *)&alsp->nextEvent);
            break;
        }
        alsp->nextDelta = n_alEvtqNextEvent(&alsp->evtq, &alsp->nextEvent);
    } while (alsp->nextDelta == 0);

    alsp->curTime += alsp->nextDelta;
    return alsp->nextDelta;
}

extern N_ALSynth *n_syn;

void     func_10002088(s32 fmt, ...);
s32      func_1001BD34(void *drvr, void **ptrRef, s32 idx);
void     func_1001BE1C(void *drvr, ALInstrument *inst, s32 idx);
void     func_10012C5C(ALSound *snd, s32 arg1, s32 waveRom);
void     func_1001E2A0(N_ALVoice *v, u8 pan);
void     func_1001E350(N_ALVoice *v, u8 fxmix);
void     func_10016E90(N_ALUnknownStruct1 *arg0);
void     func_10016F00(struct154 *arg0);
struct157 *func_10017438(s32 arg0, s16 arg1, u16 arg2, u8 arg3, f32 arg4, u8 arg5, u8 arg6,
                         struct157 **arg7);

/* Volume actually sent to the synth: the sound's own sample volume, scaled by the
   envelope segment volume, the client volume and the channel volume. */
#define SND_VOL                                                                  \
    (((s16)D_800428B8[keyMap->keyMin & 0x1F] *                                   \
      (state->unk46 * state->unk44 * snd->sampleVolume / 0x3F01)) / 0x7FFF)

/* Drain one event out of the sound player's queue.  Every arm works on the sound-state
   record named by the event; `state->unk54` is the play state (1 = playing, 2 = releasing,
   4/5 = waiting for a voice).  The loop re-enters itself with a synthesised event when an
   arm hands the record straight on to the next stage. */
void _n_handleEvent(SndEvent *event) {
    ALVoiceConfig vc;                /* 0x9C */
    ALSound      *snd;               /* 0x98 */
    ALKeyMap     *keyMap;            /* 0x94 */
    u8            pan;               /* 0x93 */
    SndEvent      evt;               /* 0x80 */
    SndEvent      copy;              /* 0x70 */
    s32           delta;             /* 0x6C */
    s32           fxmix;             /* 0x68 */
    s32           vol;               /* 0x64 */
    s32           tmp;               /* 0x60 */
    s32           noRoom;            /* 0x5C */
    s32           typeMask;          /* 0x58 */
    s32           done = 1;          /* 0x54 */
    s32           voice = 0;         /* 0x50 */
    SndState     *state = NULL;      /* 0x4C */
    SndState     *next = NULL;       /* 0x48 */
    s32           looping;           /* 0x44 */

    do {
        if (next != NULL) {
            copy.state = state;
            copy.type = event->type;
            copy.arg.i = event->arg.i;
            event = &copy;
        }
        state = event->state;
        if (state == NULL) {
        }
        snd = state->snd;
        next = state->next;

        if ((snd == NULL) && (event->type != 0x4000)) {
            if (state->retries > 0) {
                if ((event->type != 4) && (event->type != 8) && (event->type != 0x100) &&
                    (event->type != 0x10) && (event->type != 0x800) &&
                    (event->type != 0x2000)) {
                    state->retries--;
                }
                n_alEvtqPostEvent(&D_8002BA2C->evtq, (N_ALEvent *)event, 0x8235, 2);
            } else {
                func_10016E90((N_ALUnknownStruct1 *)state);
            }
        } else {
            switch (event->type) {
                case 0x4000:
                    if (snd == NULL) {
                        snd = (ALSound *)func_1001BD34(D_8002BA2C->drvr,
                                                       (void **)&state->bank->instArray[0],
                                                       state->unk4C);
                        state->snd = snd;
                        if (snd == NULL) {
                            event->type = 0x4000;
                            state->unk54 = 5;
                            state->retries--;
                            n_alEvtqPostEvent(&D_8002BA2C->evtq, (N_ALEvent *)event, 0x8235, 2);
                            break;
                        }
                    }
                    if (snd != NULL) {
                        if ((u32)snd->envelope < 0x1000000) {
                            func_10012C5C(snd, (s32)snd, (s32)((SndPlayer *)D_8002BA2C)->unk54);
                        }
                        if (((s32)snd->envelope & 0xFF000003) != 0x80000000) {
                            break;
                        }
                        keyMap = snd->keyMap;
                        state->snd = snd;
                        looping = (snd->envelope->decayTime == -1);
                        state->priority = looping + 0x40;
                        state->unk53 = (keyMap->keyMax & 0xF0) | 1;
                        if (state->unk53 & 0x20) {
                            state->ratio = alCents2Ratio(keyMap->keyBase * 100 - 6000);
                        } else {
                            state->ratio =
                                alCents2Ratio(keyMap->keyBase * 100 + keyMap->detune - 6000);
                        }
                        if (looping) {
                            state->unk53 |= 2;
                        }
                    }
                    event->type = 1;
                    /* fallthrough */
                case 1:
                    if ((state->unk54 != 5) && (state->unk54 != 4)) {
                        return;
                    }
                    keyMap = snd->keyMap;
                    vc.fxBus = state->unk51;
                    vc.priority = state->priority;
                    vc.unityPitch = 0;
                    vc.unk8 = (s32)state->bank->instArray[0]->soundArray[state->unk4C];
                    noRoom = (D_8002BA30 >= D_8002BA2C->maxSounds);
                    if ((noRoom == 0) || (state->unk53 & 0x10)) {
                        voice = n_alSynAllocVoice(&state->voice, &vc);
                    }
                    if (voice == 0) {
                        if (((state->unk53 & 0x12) != 0) || (state->retries > 0)) {
                            state->unk54 = 4;
                            state->retries--;
                            n_alEvtqPostEvent(&D_8002BA2C->evtq, (N_ALEvent *)event, 0x8235, 2);
                        } else {
                            func_10016E90((N_ALUnknownStruct1 *)state);
                        }
                        return;
                    }
                    state->unk53 |= 4;
                    state->unk46 = snd->envelope->attackVolume;
                    state->unk51 = vc.fxBus;
                    delta = (s32)((f32)snd->envelope->attackTime / state->pitch / state->ratio);
                    state->segEnd = D_8002BA2C->curTime + delta;
                    if (SND_VOL <= 0) {
                        vol = 0;
                    } else {
                        vol = SND_VOL - 1;
                    }
                    tmp = state->unk4F + snd->samplePan - 0x40;
                    pan = MIN(MAX(tmp, 0), 0x7F);
                    fxmix = (state->unk50 & 0x7F) + ((keyMap->keyMax & 0xF) << 3);
                    fxmix = (MAX(0, fxmix) > 0x7F) ? 0x7F : MAX(0, fxmix);
                    fxmix |= state->unk50 & 0x80;
                    func_1001BE1C(D_8002BA2C->drvr, state->bank->instArray[0], state->unk4C);
                    n_alSynStartVoiceParams(&state->voice, snd->wavetable,
                                            state->pitch * state->ratio, vol, pan, fxmix, 0,
                                            0.0f, 0, delta);
                    state->unk54 = 1;
                    D_8002BA30++;
                    if ((state->unk53 & 2) == 0) {
                        if (delta == 0) {
                            state->unk46 = snd->envelope->decayVolume;
                            if (SND_VOL <= 0) {
                                vol = 0;
                            } else {
                                vol = SND_VOL - 1;
                            }
                            delta = (s32)((f32)snd->envelope->decayTime / state->ratio /
                                          state->pitch);
                            state->segEnd = D_8002BA2C->curTime + delta;
                            n_alSynSetVol(&state->voice, vol, delta);
                            evt.type = 2;
                            evt.state = state;
                            n_alEvtqPostEvent(&D_8002BA2C->evtq, (N_ALEvent *)&evt, delta, 2);
                            if (state->unk53 & 0x20) {
                                func_10016F00((struct154 *)state);
                            }
                        } else {
                            evt.type = 0x40;
                            evt.state = state;
                            delta = (s32)((f32)snd->envelope->attackTime / state->pitch /
                                          state->ratio);
                            n_alEvtqPostEvent(&D_8002BA2C->evtq, (N_ALEvent *)&evt, delta, 2);
                        }
                    }
                    break;

                case 2:
                case 0x400:
                case 0x1000:
                    if ((event->type != 0x1000) || ((state->unk53 & 2) != 0)) {
                        switch (state->unk54) {
                            case 1:
                                if (1) {
                                    func_10016F80(&D_8002BA2C->evtq,
                                                  (N_ALUnknownStruct1 *)state, 0x40);
                                } else {
                                    func_10002088(
                                        (s32)"snd %d has been freed too early - %d\n\n\n\n\n",
                                        state->unk54, state->unk54);
                                    func_10002088(
                                        (s32)"-2 sound has been freed too early - %d\n\n\n\n\n",
                                        state->unk54);
                                }
                                delta = (s32)((f32)snd->envelope->releaseTime / state->ratio /
                                              state->pitch);
                                n_alSynSetVol(&state->voice, 0, delta);
                                if (delta != 0) {
                                    evt.type = 0x80;
                                    evt.state = state;
                                    n_alEvtqPostEvent(&D_8002BA2C->evtq, (N_ALEvent *)&evt,
                                                      delta, 2);
                                    state->unk54 = 2;
                                } else {
                                    func_10016E90((N_ALUnknownStruct1 *)state);
                                }
                                break;
                            case 4:
                            case 5:
                                func_10016E90((N_ALUnknownStruct1 *)state);
                                break;
                            default:
                                break;
                        }
                        if (event->type == 2) {
                            event->type = 0x1000;
                        }
                    }
                    break;

                case 4:
                    state->unk4F = event->arg.i;
                    if (state->unk54 == 1) {
                        tmp = state->unk4F + snd->samplePan - 0x40;
                        pan = MIN(MAX(tmp, 0), 0x7F);
                        func_1001E2A0(&state->voice, pan);
                    }
                    break;

                case 16:
                    state->pitch = event->arg.f;
                    if (state->unk54 == 1) {
                        n_alSynSetPitch(&state->voice, state->pitch * state->ratio);
                        if (state->unk53 & 0x20) {
                            func_10016F00((struct154 *)state);
                        }
                    }
                    break;

                case 0x100:
                    keyMap = snd->keyMap;
                    state->unk50 = event->arg.i;
                    if (state->unk54 == 1) {
                        fxmix = (state->unk50 & 0x7F) + ((keyMap->keyMax & 0xF) << 3);
                        fxmix = (MAX(0, fxmix) > 0x7F) ? 0x7F : MAX(0, fxmix);
                        fxmix |= state->unk50 & 0x80;
                        n_alSynSetFXMix(&state->voice, fxmix);
                    }
                    break;

                case 0x2000:
                    state->unk51 = event->arg.i;
                    if (state->unk51 >= n_syn->maxAuxBusses) {
                        state->unk51 = 0;
                    }
                    if (state->unk54 == 1) {
                        state->voice.fxBus = state->unk51;
                    }
                    break;

                case 8:
                    keyMap = snd->keyMap;
                    state->unk44 = event->arg.i;
                    if (state->unk54 == 1) {
                        if (SND_VOL <= 0) {
                            vol = 0;
                        } else {
                            vol = SND_VOL - 1;
                        }
                        n_alSynSetVol(&state->voice, vol,
                                      (state->segEnd - D_8002BA2C->curTime) < 1000
                                          ? 1000
                                          : (state->segEnd - D_8002BA2C->curTime));
                    }
                    break;

                case 0x800:
                    keyMap = snd->keyMap;
                    if (state->unk54 == 1) {
                        delta = (s32)((f32)snd->envelope->releaseTime / state->ratio /
                                      state->pitch);
                        if (SND_VOL <= 0) {
                            vol = 0;
                        } else {
                            vol = SND_VOL - 1;
                        }
                        n_alSynSetVol(&state->voice, vol, delta);
                    }
                    break;

                case 0x40:
                    if ((state->unk53 & 2) == 0) {
                        keyMap = snd->keyMap;
                        state->unk46 = snd->envelope->decayVolume;
                        if (SND_VOL <= 0) {
                            vol = 0;
                        } else {
                            vol = SND_VOL - 1;
                        }
                        delta = (s32)((f32)snd->envelope->decayTime / state->ratio /
                                      state->pitch);
                        state->segEnd = D_8002BA2C->curTime + delta;
                        n_alSynSetVol(&state->voice, vol, delta);
                        evt.type = 2;
                        evt.state = state;
                        n_alEvtqPostEvent(&D_8002BA2C->evtq, (N_ALEvent *)&evt, delta, 2);
                        if (state->unk53 & 0x20) {
                            func_10016F00((struct154 *)state);
                        }
                    }
                    break;

                case 0x80:
                    func_10016E90((N_ALUnknownStruct1 *)state);
                    break;

                case 0x200:
                    if (state->unk53 & 0x10) {
                        func_10017438(event->arg2, event->arg.i, state->unk44, state->unk4F,
                                      state->pitch, state->unk50, state->unk51, state->owner);
                    }
                    break;

                case 0x8000:
                    state->unk52 = event->arg.i;
                    if (state->unk54 == 1) {
                        func_1001E350(&state->voice, state->unk52);
                    }
                    break;

                default:
                    break;
            }
        }

        typeMask = event->type & 0x42D1;
        if (((state = next) != NULL) && (typeMask == 0)) {
            done = state->unk53 & 1;
        }
    } while ((done == 0) && (state != NULL) && (typeMask == 0));
}

void func_10016E90(N_ALUnknownStruct1 *arg0) {
    if ((arg0->unk53 & 4) != 0) {
        n_alSynStopVoice(&arg0->unk10);
        n_alSynFreeVoice(&arg0->unk10);
    }
    func_10017298(arg0);
    func_10016F80(&D_8002BA2C->evtq, arg0, 0xFFFF);
}

void func_10016F00(struct154 *arg0) {
    N_ALEvent event;
    f32 res;

    res = alCents2Ratio(arg0->unkC->unk4->unk5) * arg0->unk34;

    event.type = 16;
    /* TODO: check if this is the right struct */
    event.msg.vol.voice = arg0;
    event.msg.vol.delta = *(s32*)&res;

    n_alEvtqPostEvent(&D_8002BA2C->evtq, &event, 33333, 2);
}

/* The sound player's view of a queued N_ALEvent (libultra's ALSndpEvent).  The
 * type is tested as a BIT MASK here, so it is read unsigned -- golden uses lhu
 * on a field N_ALEvent declares s16. */
typedef struct {
    /* 0x00 */ u16                 type;
    /* 0x04 */ N_ALUnknownStruct1 *state;
} SndpEvent;

/* libultra's static _removeEvents(), with a type mask added: unlink every
 * pending event belonging to `state` whose type matches, and put its list item
 * back on the queue's free list. */
void func_10016F80(ALEventQueue *evtq, N_ALUnknownStruct1 *state, u16 typeMask) {
    ALLink            *thisNode;
    ALLink            *nextNode;
    N_ALEventListItem *thisItem;
    N_ALEventListItem *nextItem;
    SndpEvent         *evt;
    s32                mask;

    mask = osSetIntMask(1);

    thisNode = evtq->allocList.next;
    while (thisNode) {
        nextNode = thisNode->next;
        thisItem = (N_ALEventListItem *)thisNode;
        nextItem = (N_ALEventListItem *)nextNode;
        evt = (SndpEvent *)&thisItem->evt;
        if ((evt->state == state) && (evt->type & typeMask)) {
            if (nextItem) {
                nextItem->delta += thisItem->delta;
            }
            {
                ALLink *ln = thisNode;
                if (ln->next) {
                    ln->next->prev = ln->prev;
                }
                if (ln->prev) {
                    ln->prev->next = ln->next;
                }
            }
            {
                ALLink *ln = thisNode;
                ALLink *lst = &evtq->freeList;
                ln->next = lst->next;
                ln->prev = lst;
                if (lst->next) {
                    lst->next->prev = ln;
                }
                lst->next = ln;
            }
        }
        thisNode = nextNode;
    }
    osSetIntMask(mask);
}


N_ALUnknownStruct1 *func_10017100(s32 arg0, s16 arg1) {
    N_ALUnknownStruct1 *sp24;
    u32 mask;
    N_ALUnknownStruct1 *sp1C;

    mask = osSetIntMask(1);
    sp24 = D_8002BA28;
    if (sp24 != 0) {
        D_8002BA28 = sp24->node.next;
        sp1C = sp24;
        if (sp1C->node.next) {
            sp1C->node.next->prev = sp1C->node.prev;
        }
        if (sp1C->node.prev) {
            sp1C->node.prev->next = sp1C->node.next;
        }
        if (D_8002BA20) {
            sp24->node.next = D_8002BA20;
            sp24->node.prev = NULL;
            D_8002BA20->node.prev = sp24;
            D_8002BA20 = sp24;
        } else {
            sp24->node.prev = 0;
            sp24->node.next = sp24->node.prev;
            D_8002BA20 = sp24;
            D_8002BA24 = sp24;
        }
        osSetIntMask(mask);
        sp24->unkC = 0;
        sp24->unk4C = arg1;
        sp24->unk3C = arg0;
        sp24->unk4E = 64;
        sp24->unk54 = 5;
        sp24->unk40 = 2;
        sp24->unk53 = 0;
        sp24->unk38 = 0;
        sp24->unk30 = 1.0f;
    } else {
        osSetIntMask(mask);
    }
    return sp24;
}

void func_10017298(N_ALUnknownStruct1 *arg0) {
    N_ALUnknownStruct1 *sp4;

    if (D_8002BA20 == arg0) {
        D_8002BA20 = arg0->node.next;
    }
    if (D_8002BA24 == arg0) {
        D_8002BA24 = arg0->node.prev;
    }

    sp4 = arg0;
    if (sp4->node.next) {
        sp4->node.next->prev = sp4->node.prev;
    }

    if (sp4->node.prev) {
        sp4->node.prev->next = sp4->node.next;
    }

    if (D_8002BA28) {
        arg0->node.next = D_8002BA28;
        arg0->node.prev = NULL;
        D_8002BA28->node.prev = arg0;
        D_8002BA28 = arg0;
    } else {
        arg0->node.prev = NULL;
        arg0->node.next = arg0->node.prev;
        D_8002BA28 = arg0;
    }
    if (arg0->unk53 & 4) {
        D_8002BA30 -= 1;
    }
    arg0->unk54 = 0;
    if (arg0->unk38) {
        if (*arg0->unk38 == (s32)arg0) {
            *arg0->unk38 = 0;
        }
        arg0->unk38 = NULL;
    }
}

s32 func_100173C4(N_ALUnknownEvent2 *arg0) {
    s32 ret;
    s32 mask;

    ret = 0;
    if (arg0->unk0) {
        mask = __osDisableInt();
        if (arg0->unk0) {
            ret = arg0->unk0->unk54;
        }
        __osRestoreInt(mask);
    }
    return ret;
}

/* Allocate a sound-state record, stamp the caller's parameters into it and post
 * the 0x4000 event.
 *
 * `count` and `delta` are both LOAD-BEARING despite never taking a non-zero
 * value: golden really does zero them and then read them back (sh/lh 0x2E, sw
 * zero/lw + addiu 1 at 0x28).  Delete-and-measure: dropping `count` and its
 * empty guard takes the function from 87 instructions to 83, dropping `delta`
 * takes it to 85 -- both BELOW golden's 87, so they are original source, not
 * register forcers.  The retry loop is the same story: arg1 is reset to 0 on
 * every pass, so the `arg1 != 0 && state != NULL` back-edge can never be
 * taken. */
struct157 *func_10017438(s32 arg0, s16 arg1, u16 arg2, u8 arg3, f32 arg4, u8 arg5, u8 arg6, struct157 **arg7) {
    struct157 *state;
    struct157 *result;
    s16 count;
    s32 delta;
    N_ALEvent event;

    result = NULL;
    count = 0;
    if (arg1 != 0) {
        do {
            state = (struct157 *)func_10017100(arg0, arg1 - 1);
            if (state != NULL) {
                D_8002BA2C->target = (s32)state;
                event.type = 0x4000;
                event.msg.unknown1.unk0 = (N_ALUnknownStruct1 *)state;
                state->unk4F = arg3;
                state->unk44 = arg2;
                state->unk34 = arg4;
                state->unk50 = arg5;
                state->unk51 = arg6;
                delta = 0;
                n_alEvtqPostEvent(&D_8002BA2C->evtq, &event, delta + 1, 2);
                result = state;
            }
            arg1 = 0;
        } while (arg1 != 0 && state != NULL);
        if (result != NULL) {
            result->unk53 |= 1;
            result->unk38 = arg7;
            if (count != 0) {
            }
        }
    }
    if (arg7 != NULL) {
        *arg7 = result;
    }
    return result;
}


void func_10017594(N_ALUnknownStruct1 *arg0) {
    N_ALEvent event;

    if (arg0) {
        event.type = 1024;
        event.msg.unknown1.unk0 = arg0;
        event.msg.unknown1.unk0->unk53 &= -0x11;
        n_alEvtqPostEvent(&D_8002BA2C->evtq, &event, 0, 2);
    }
}

void func_10017604(u8 arg0) {
    s32 mask;
    N_ALEvent event;
    N_ALUnknownStruct1 *ptr;

    mask = osSetIntMask(1);
    ptr = D_8002BA20;
    while (ptr) {
        event.type = 1024;
        event.msg.unknown1.unk0 = ptr;
        if ((ptr->unk53 & arg0) == arg0) {
            event.msg.unknown1.unk0->unk53 &= -0x11;
            n_alEvtqPostEvent(&D_8002BA2C->evtq, &event, 0, 2);
        }
        ptr = ptr->node.next;
    }
    osSetIntMask(mask);
}
// NON-MATCHING: stack isnt quite right
// void func_10017604(u8 arg0) {
//     s32 mask;
//     struct31 *sp20;
//     u16 foo;
//     s16 sp1C;
//     struct31 *sp18;
//
//     mask = osSetIntMask(1);
//     sp18 = D_8002BA20;
//     if (sp18 != 0) {
//         do
//         {
//             sp1C = 1024;
//             sp20 = sp18;
//             if ((sp18->unk53 & arg0) == arg0) {
//                 sp20->unk53 = sp20->unk53 & -0x11;
//                 n_alEvtqPostEvent(D_8002BA2C + 20, &sp1C, 0, 2);
//             }
//             sp18 = sp18->unk0;
//         }
//         while (sp18);
//     }
//     osSetIntMask(mask);
// }

void func_100176C4(void) {
    func_10017604(1);
}

void func_100176EC(void) {
    func_10017604(3);
}

void func_10017714(s32 arg0, s16 type, s32 arg2) {
    N_ALEvent event;

    if (arg0 != 0) {
        event.type = type;
        event.msg.vol.voice = arg0;
        event.msg.vol.delta = arg2;
        n_alEvtqPostEvent(&D_8002BA2C->evtq, &event, 0, 2);
    }
}

/* The chan-config record hanging off N_ALUnknownStruct1.unkC (declared s32 in
 * the header); unk2's low 5 bits are the MIDI channel. */
typedef struct {
    /* 0x0 */ u8 pad0[0x2];
    /* 0x2 */ u8 unk2;
} struct155;

typedef struct {
    /* 0x0 */ s32 pad0;
    /* 0x4 */ struct155 *unk4;
} struct156;

void func_10017780(u8 arg0, u16 arg1) {
    s32 mask;
    N_ALUnknownStruct1 *ptr;
    s32 count;
    N_ALEvent event;

    mask = osSetIntMask(1);
    ptr = D_8002BA20;
    D_800428B8[arg0] = arg1;
    for (count = 0; ptr != 0; count++, ptr = ptr->node.next) {
        if ((ptr->unkC != 0) && ((((struct156 *)ptr->unkC)->unk4->unk2 & 0x1F) == arg0)) {
            event.type = 0x800;
            event.msg.unknown1.unk0 = ptr;
            n_alEvtqPostEvent(&D_8002BA2C->evtq, &event, 0, 2);
        }
    }
    osSetIntMask(mask);
}

// NON-MATCHING: far from matching
// void func_10017780(u8 arg0, u16 arg1) {
//     s32 sp34;
//     struct31 *sp30;
//     s32 sp2C;
//     struct31 *sp20;
//     s16 sp1C;
//     struct31 *temp_t4;
//     struct31 *temp_t4_2;
//
//     sp34 = osSetIntMask(1);
//     sp30 = D_8002BA20;
//     D_800428B8[arg0] = arg1;
//     sp2C = 0;
//     if (sp30 != 0) {
//         do
//         {
//             temp_t4 = sp30->unkC;
//             // if ((temp_t4 != 0) && ((temp_t4->unk4->unk2 & 0x1F) == arg0)) {
//             //     sp1C = 1024;
//             //     sp20 = sp30;
//             //     n_alEvtqPostEvent(D_8002BA2C + 20, &sp1C, 0, 2);
//             // }
//             sp2C = sp2C + 1;
//             temp_t4_2 = sp30->unk0;
//             sp30 = temp_t4_2;
//         }
//         while (temp_t4_2 != 0);
//     }
//     osSetIntMask(sp34);
// }
