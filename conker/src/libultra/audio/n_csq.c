/* The Conker build of n_alCSeqNextEvent takes a 3rd argument that the SDK
 * header prototype omits; shadow the header declaration so the real
 * definition below is not rejected as an incompatible redeclaration. */
#define n_alCSeqNextEvent n_alCSeqNextEvent_HDR
#include <n_libaudio.h>
#undef n_alCSeqNextEvent

u8 __getTrackByte(ALCSeq *seq, s32 track);
u32 __readVarLen(ALCSeq *seq, s32 track);
u8 __n_alCSeqGetTrackEvent(ALCSeq *seq, s32 track, N_ALEvent *event, s32 arg3);

void n_alCSeqNew(ALCSeq *seq, u8 *ptr) {
    u32 i;
    u32 offset;
    u32 flag;

    seq->base = (ALCMidiHdr *)ptr;
    seq->validTracks = 0;
    seq->lastDeltaTicks = 0;
    seq->lastTicks = 0;
    seq->deltaFlag = 1;

    for (i = 0; i < 16; i++) {
        seq->lastStatus[i] = 0;
        seq->curBUPtr[i] = 0;
        seq->curBULen[i] = 0;
        offset = seq->base->trackOffset[i];
        if (offset) {
            flag = 1 << i;
            seq->validTracks |= flag;
            seq->curLoc[i] = ptr + offset;
            seq->evtDeltaTicks[i] = __readVarLen(seq, i);
        } else {
            seq->curLoc[i] = 0;
        }
    }
    seq->qnpt = 1.0f / (f32)seq->base->division;
}

void n_alCSeqNextEvent(ALCSeq *seq, N_ALEvent *evt, s32 arg2) {
    u32 i;
    u32 minDelta;
    s32 minTrack;
    u32 ticks;

    minDelta = -1;
    minTrack = -1;
    ticks = seq->lastDeltaTicks;

    for (i = 0; i < 16; i++) {
        if ((seq->validTracks >> i) & 1) {
            if (seq->deltaFlag) {
                seq->evtDeltaTicks[i] -= ticks;
            }
            if (seq->evtDeltaTicks[i] < minDelta) {
                minDelta = seq->evtDeltaTicks[i];
                minTrack = i;
            }
        }
    }

    if (minTrack != -1) {
        __n_alCSeqGetTrackEvent(seq, minTrack, evt, arg2);
    } else {
        evt->type = AL_CSP_LOOPSTART;
    }

    evt->msg.midi.ticks = minDelta;
    seq->lastTicks += minDelta;
    seq->lastDeltaTicks = minDelta;

    if (evt->type != AL_CSP_LOOPSTART) {
        seq->evtDeltaTicks[minTrack] += __readVarLen(seq, minTrack);
    }
    seq->deltaFlag = 1;
}

u8 __n_alCSeqGetTrackEvent(ALCSeq *seq, s32 track, N_ALEvent *event, s32 arg3) {
    u32 backup;
    u8 status;
    u8 firstByte;
    u8 loopCount;
    u8 *ptr;
    u8 c;
    u32 flag;

    status = __getTrackByte(seq, track);
    if (status == AL_MIDI_Meta) {
        c = __getTrackByte(seq, track);
        if (c == AL_MIDI_META_TEMPO) {
            event->type = AL_TEMPO_EVT;
            event->msg.tempo.status = status;
            event->msg.tempo.type = c;
            event->msg.tempo.byte1 = __getTrackByte(seq, track);
            event->msg.tempo.byte2 = __getTrackByte(seq, track);
            event->msg.tempo.byte3 = __getTrackByte(seq, track);
            seq->lastStatus[track] = 0;
        } else if (c == AL_MIDI_META_EOT) {
            flag = 1 << track;
            seq->validTracks ^= flag;
            if (seq->validTracks != 0) {
                event->type = AL_CSP_LOOPSTART;
            } else {
                event->type = AL_SEQ_END_EVT;
            }
        } else if (c == AL_CMIDI_LOOPSTART_CODE) {
            status = __getTrackByte(seq, track);
            event->msg.midi.duration = status << 8;
            status = __getTrackByte(seq, track);
            event->msg.midi.duration += status;
            seq->lastStatus[track] = 0;
            event->type = AL_CSP_LOOPEND;
        } else if (c == AL_CMIDI_LOOPEND_CODE) {
            ptr = seq->curLoc[track];
            firstByte = *ptr++;
            loopCount = *ptr;
            if (loopCount == 0 || arg3 == 0) {
                *ptr = firstByte;
                seq->curLoc[track] = ptr + 5;
            } else {
                if (loopCount != 0xFF) {
                    *ptr = loopCount - 1;
                }
                ptr++;
                backup = *ptr++ << 24;
                backup += *ptr++ << 16;
                backup += *ptr++ << 8;
                backup += *ptr++;
                seq->curLoc[track] = ptr - backup;
            }
            seq->lastStatus[track] = 0;
            event->type = AL_CSP_NOTEOFF_EVT;
        }
    } else {
        event->type = AL_SEQ_MIDI_EVT;
        if (status & 0x80) {
            event->msg.midi.status = (status & 0xF0) | track;
            event->msg.midi.byte1 = __getTrackByte(seq, track);
            seq->lastStatus[track] = event->msg.midi.status;
        } else {
            event->msg.midi.status = seq->lastStatus[track];
            event->msg.midi.byte1 = status;
        }
        if ((event->msg.midi.status & 0xF0) != AL_MIDI_ProgramChange &&
            (event->msg.midi.status & 0xF0) != AL_MIDI_ChannelPressure) {
            event->msg.midi.byte2 = __getTrackByte(seq, track);
            if ((event->msg.midi.status & 0xF0) == AL_MIDI_NoteOn) {
                event->msg.midi.duration = __readVarLen(seq, track);
            }
        } else {
            event->msg.midi.byte2 = 0;
        }
    }
    return 1;
}
void func_100186DC(ALCSeq *seq, ALCSeqMarker *marker) {
    s32 i;

    seq->validTracks = marker->validTracks;
    seq->lastTicks = marker->lastTicks;
    seq->lastDeltaTicks = marker->lastDeltaTicks;

    for (i = 0; i < 16; i++) {
        seq->curLoc[i] = marker->curLoc[i];
        seq->curBUPtr[i] = marker->curBUPtr[i];
        seq->curBULen[i] = marker->curBULen[i];
        seq->lastStatus[i] = marker->lastStatus[i];
        seq->evtDeltaTicks[i] = marker->evtDeltaTicks[i];
    }
}

void func_10018790(ALCSeq *seq, ALCSeqMarker *markers, u32 count, u32 base) {
    N_ALEvent event;
    ALCSeq tmp;
    s32 j;
    s32 i;
    ALCSeqMarker lclMarker;

    n_alCSeqNew(&tmp, (u8 *)seq->base);

    for (i = 0; i < count; i++) {
        markers[i].lastTicks = 0;
    }

    do {
        lclMarker.validTracks = tmp.validTracks;
        lclMarker.lastTicks = tmp.lastTicks;
        lclMarker.lastDeltaTicks = tmp.lastDeltaTicks;
        for (j = 0; j < 16; j++) {
            lclMarker.curLoc[j] = tmp.curLoc[j];
            lclMarker.curBUPtr[j] = tmp.curBUPtr[j];
            lclMarker.curBULen[j] = tmp.curBULen[j];
            lclMarker.lastStatus[j] = tmp.lastStatus[j];
            lclMarker.evtDeltaTicks[j] = tmp.evtDeltaTicks[j];
        }
        n_alCSeqNextEvent(&tmp, &event, 0);
        if (event.type == AL_CSP_LOOPEND) {
            if ((s32)event.msg.midi.duration >> 8 >= base &&
                (s32)event.msg.midi.duration >> 8 < base + count) {
                if (markers[((s32)event.msg.midi.duration >> 8) - base].lastTicks == 0) {
                    markers[((s32)event.msg.midi.duration >> 8) - base] = lclMarker;
                    if (--i <= 0) {
                        return;
                    }
                }
            }
        }
    } while (event.type != AL_SEQ_END_EVT);
}

u8 __getTrackByte(ALCSeq *seq, s32 track) {
    u8 theByte;

    if (seq->curBULen[track]) {
        theByte = *seq->curBUPtr[track];
        seq->curBUPtr[track]++;
        seq->curBULen[track]--;
    } else {
        theByte = *seq->curLoc[track];
        seq->curLoc[track]++;
        if (theByte == AL_CMIDI_BLOCK_CODE) {
            u8 loBackUp, hiBackUp, theLen, nextByte;
            u32 backup;

            nextByte = *seq->curLoc[track];
            seq->curLoc[track]++;
            if (nextByte != AL_CMIDI_BLOCK_CODE) {
                hiBackUp = nextByte;
                loBackUp = *seq->curLoc[track];
                seq->curLoc[track]++;
                theLen = *seq->curLoc[track];
                seq->curLoc[track]++;
                backup = (u32) hiBackUp;
                backup <<= 8;
                backup += loBackUp;
                seq->curBUPtr[track] = seq->curLoc[track] - (backup + 4);
                seq->curBULen[track] = (u32)theLen;
                theByte = *seq->curBUPtr[track];
                seq->curBUPtr[track]++;
                seq->curBULen[track]--;
            }
        }
    }
    return theByte;
}

u32 __readVarLen(ALCSeq *seq, s32 track) {
    u32 value;
    u32 c;

    value = __getTrackByte(seq, track);
    if (value & 0x80) {
        value &= 0x7F;
        do
        {
            c = __getTrackByte(seq, track);
            value = (value << 7) + (c & 0x7F);
        } while (c & 0x80);
    }
    return value;
}
