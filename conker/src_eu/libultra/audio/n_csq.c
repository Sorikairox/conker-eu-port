// Rare's n_alCSeqNextEvent takes a third argument
#define n_alCSeqNextEvent n_alCSeqNextEvent_2args
#include <n_libaudio.h>
#undef n_alCSeqNextEvent
void n_alCSeqNextEvent(ALCSeq *seq, N_ALEvent *evt, s32 arg2);

u32 __readVarLen(ALCSeq *seq, s32 track);

void n_alCSeqNew(ALCSeq *seq, u8 *ptr)
{
    u32 i, tmpOff, flagTmp;

    seq->base = (ALCMidiHdr *)ptr;
    seq->validTracks = 0;
    seq->lastDeltaTicks = 0;
    seq->lastTicks = 0;
    seq->deltaFlag = 1;
    for (i = 0; i < 16; i++) {
        seq->lastStatus[i] = 0;
        seq->curBUPtr[i] = 0;
        seq->curBULen[i] = 0;
        tmpOff = seq->base->trackOffset[i];
        if (tmpOff) { /* if the track is valid */
            flagTmp = 1 << i;
            seq->validTracks |= flagTmp;
            seq->curLoc[i] = (u8 *)((u32)ptr + tmpOff);
            seq->evtDeltaTicks[i] = __readVarLen(seq, i);
        } else {
            seq->curLoc[i] = 0;
        }
    }
    seq->qnpt = 1.0f / (f32)seq->base->division;
}
// AL_TRACK_END is one higher in this version of the event enum
#define N_AL_TRACK_END 0x13

s32 __n_alCSeqGetTrackEvent(ALCSeq *seq, u32 track, N_ALEvent *event, s32 arg3);

void n_alCSeqNextEvent(ALCSeq *seq, N_ALEvent *evt, s32 arg2)
{
    u32 i;
    u32 firstTime = 0xFFFFFFFF;
    u32 firstTrack = 0xFFFFFFFF;
    u32 lastTicks = seq->lastDeltaTicks;

    for (i = 0; i < 16; i++) {
        if ((seq->validTracks >> i) & 1) {
            if (seq->deltaFlag) {
                seq->evtDeltaTicks[i] -= lastTicks;
            }
            if (seq->evtDeltaTicks[i] < firstTime) {
                firstTime = seq->evtDeltaTicks[i];
                firstTrack = i;
            }
        }
    }
    if (firstTrack != 0xFFFFFFFF) {
        __n_alCSeqGetTrackEvent(seq, firstTrack, evt, arg2);
    } else {
        evt->type = N_AL_TRACK_END;
    }
    evt->msg.midi.ticks = firstTime;
    seq->lastTicks += firstTime;
    seq->lastDeltaTicks = firstTime;
    if (evt->type != N_AL_TRACK_END) {
        seq->evtDeltaTicks[firstTrack] += __readVarLen(seq, firstTrack);
    }
    seq->deltaFlag = 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/libultra/audio/n_csq/__n_alCSeqGetTrackEvent.s")
// n_alCSeqSetLoc
void func_100186DC(ALCSeq *seq, ALCSeqMarker *m) {
    s32 i;

    seq->validTracks = m->validTracks;
    seq->lastTicks = m->lastTicks;
    seq->lastDeltaTicks = m->lastDeltaTicks;
    for (i = 0; i < 16; i++) {
        seq->curLoc[i] = m->curLoc[i];
        seq->curBUPtr[i] = m->curBUPtr[i];
        seq->curBULen[i] = m->curBULen[i];
        seq->lastStatus[i] = m->lastStatus[i];
        seq->evtDeltaTicks[i] = m->evtDeltaTicks[i];
    }
}

// N_ALEvent as seen by func_10018790: a marker event's id is in the top 24 bits of the word at 0xC
typedef struct {
    s16 type;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} N_ALMarkerEvent;

#define MARKER_ID(evt) ((evt).unkC >> 8)

// Rare: scan a compressed sequence for marker events (type 0x14) and record
// the sequence location of each one in markers[id - firstId]
void func_10018790(u8 **seqData, ALCSeqMarker *markers, u32 count, u32 firstId) {
    N_ALMarkerEvent evt;
    ALCSeq seq;
    s32 j;
    s32 i;
    ALCSeqMarker m;

    n_alCSeqNew(&seq, *seqData);
    for (i = 0; i < count; i++) {
        markers[i].lastTicks = 0;
    }
    do {
        m.validTracks = seq.validTracks;
        m.lastTicks = seq.lastTicks;
        m.lastDeltaTicks = seq.lastDeltaTicks;
        for (j = 0; j < 16; j++) {
            m.curLoc[j] = seq.curLoc[j];
            m.curBUPtr[j] = seq.curBUPtr[j];
            m.curBULen[j] = seq.curBULen[j];
            m.lastStatus[j] = seq.lastStatus[j];
            m.evtDeltaTicks[j] = seq.evtDeltaTicks[j];
        }
        n_alCSeqNextEvent(&seq, (N_ALEvent *)&evt, 0);
        if (evt.type == 0x14) {
            if ((MARKER_ID(evt)) >= firstId && (MARKER_ID(evt)) < firstId + count) {
                if (markers[(MARKER_ID(evt)) - firstId].lastTicks == 0) {
                    markers[(MARKER_ID(evt)) - firstId] = m;
                    if (--i <= 0) {
                        return;
                    }
                }
            }
        }
    } while (evt.type != AL_SEQ_END_EVT);
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
