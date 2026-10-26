#include <libaudio.h>
#include <os_internal.h>
#include <ultraerror.h>
#include <assert.h>
#include "n_libaudio.h"
#include "n_seqp.h"
#include "cseq.h"
#include "n_cseqp.h"

// alLink, expanded inline in this version of the library
#define N_AL_LINK(e, after)                     \
    {                                           \
        ALLink *ln = (ALLink *)(e);             \
        ALLink *to = (ALLink *)(after);         \
                                                \
        ln->next = to->next;                    \
        ln->prev = to;                          \
        if (to->next != NULL) {                 \
            to->next->prev = ln;                \
        }                                       \
        to->next = ln;                          \
    }


       ALMicroTime      __n_CSPVoiceHandler(void *node);
static void              __n_CSPHandleNextSeqEvent(N_ALCSPlayer *seqp);
void                    __n_CSPHandleMIDIMsg(N_ALCSPlayer *seqp, N_ALEvent *event);
static void             __n_CSPHandleMetaMsg(N_ALCSPlayer *seqp, N_ALEvent *event);
       void             __n_CSPRepostEvent(ALEventQueue *evtq, N_ALEventListItem *item);
       void              __n_setUsptFromTempo(N_ALCSPlayer *seqp, f32 tempo);


void n_alCSPNew(N_ALCSPlayer *seqp, ALSeqpConfig *c)
{
    s32                 i;
    N_ALEventListItem  *items;
    N_ALVoiceState     *vs;
    N_ALVoiceState     *voices;

    ALHeap *hp = c->heap;

    /*
     * initialize member variables
     */
    seqp->bank          = 0;
    seqp->target        = NULL;
    seqp->drvr          = n_syn;
    seqp->chanMask      = 0xffff;
    func_10017B30(seqp);
    seqp->uspt          = 488;
    seqp->nextDelta     = 0;
    seqp->state         = AL_STOPPED;
    seqp->vol           = 0x7FFF;              /* full volume  */
    seqp->debugFlags    = c->debugFlags;
    seqp->frameTime     = AL_USEC_PER_FRAME;   /* should get this from driver */
    seqp->curTime       = 0;
    seqp->initOsc       = c->initOsc;
    seqp->updateOsc     = c->updateOsc;
    seqp->stopOsc       = c->stopOsc;

#if 1
    seqp->unk7C = 0.0f;
    seqp->unk80 = 1.0f;
    seqp->unk84 = 0;
    seqp->unk8D = 0;
    seqp->unk8C = c->maxVoices;
#endif

    seqp->nextEvent.type = AL_SEQP_API_EVT;  /* this will start the voice handler "spinning" */

    /*
     * init the channel state
     */
    seqp->maxChannels = c->maxChannels;
    seqp->chanState = alHeapAlloc(hp, c->maxChannels, sizeof(ALChanState) );
    __n_initChanState((N_ALSeqPlayer*)seqp);  /* sct 11/6/95 */

    /*
     * init the voice state array
     */
    voices = alHeapAlloc(hp, c->maxVoices, sizeof(N_ALVoiceState));
    seqp->vFreeList = 0;
    for (i = 0; i < c->maxVoices; i++) {
      vs = &voices[i];
      vs->next = seqp->vFreeList;
      seqp->vFreeList = vs;
    }

    seqp->vAllocHead = 0;
    seqp->vAllocTail = 0;

    /*
     * init the event queue
     */
    items = alHeapAlloc(hp, c->maxEvents, sizeof(N_ALEventListItem));
    n_alEvtqNew(&seqp->evtq, items, c->maxEvents);


    /*
     * add ourselves to the driver
     */
    seqp->node.next       = NULL;
    seqp->node.handler    = __n_CSPVoiceHandler;
    seqp->node.clientData = seqp;
#if 1
    n_alSynAddSndPlayer (&seqp->node);
#endif
#if 0
    n_alSynAddSeqPlayer( &seqp->node);
#endif
}

// jump table
// s127: DK64 n_csplayer.c func_global_asm_80733180 (__CSPVoiceHandler) with Conker's event ids
// (pause 0x10, stop 0x11, stopping 0x12, noteoff 0x16, trem 0x17, vib 0x18, fx 0x19/0x1A),
// pause/resume (state 3, saved delta in unk88) and a per-channel release on stop
typedef struct {
    /* 0x00 */ ALInstrument *instrument;
    /* 0x04 */ s16 bendRange;
    /* 0x06 */ u8 pan;
    /* 0x07 */ u8 priority;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 vol;
    /* 0x0A */ u8 fxmix;
    /* 0x0B */ u8 unkB;
    /* 0x0C */ u8 sustain;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 unkE;
    /* 0x0F */ u8 padF[5];
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u8 unk16;
    /* 0x17 */ u8 unk17;
    /* 0x18 */ f32 pitchBend;
    /* 0x1C */ ALMicroTime attackTime;
    /* 0x20 */ ALMicroTime decayTime;
    /* 0x24 */ ALMicroTime releaseTime;
    /* 0x28 */ u8 unk28;
    /* 0x29 */ u8 attackVolume;
    /* 0x2A */ u8 decayVolume;
    /* 0x2B */ s8 unk2B;
    /* 0x2C */ u8 tremType;
    /* 0x2D */ u8 tremRate;
    /* 0x2E */ u8 tremDepth;
    /* 0x2F */ u8 tremDelay;
    /* 0x30 */ u8 vibType;
    /* 0x31 */ u8 vibRate;
    /* 0x32 */ u8 vibDepth;
    /* 0x33 */ u8 vibDelay;
    /* 0x34 */ u8 pad34;
    /* 0x35 */ u8 unk35;
    /* 0x36 */ u8 unk36;
    /* 0x37 */ u8 pad37;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ u8 pad3A[2];
} CSPChanState;

typedef struct {
    /* 0x00 */ u8 pad0[0x34];
    /* 0x34 */ void (*unk34)(ALInstrument *);
} CSPSynth;

#define CSP_CHAN(c) (((CSPChanState *)seqp->chanState)[c])

void  n_seqp_unmap_voice(N_ALSeqPlayer *seqp, N_ALVoice *voice);
s32   n_seqp_cancel_voice_kill(N_ALSeqPlayer *seqp, N_ALVoice *voice, ALMicroTime killTime);
u8    n_seqp_voice_fx_mix(N_ALVoiceState *vs, N_ALCSPlayer *seqp);
s32   n_evtq_flush_type_first(ALEventQueue *evtq, s16 type);
void  func_1001CA90(N_ALVoice *v, f32 pitch);
f32   func_1001CEA4(s32 arg0);
void *func_1001D9B0(s32 arg0);
void *func_1001DA28(s32 arg0);
void  func_1001DAA0(void *fx, s16 paramID, void *param);
void  func_1001DAE4(void *fx, s16 paramID, void *param);

ALMicroTime __n_CSPVoiceHandler(void *node)
{
    N_ALCSPlayer    *seqp = (N_ALCSPlayer *) node;
    N_ALEvent        evt;
    N_ALVoice       *voice;
    ALMicroTime      delta;
    N_ALVoiceState  *vs;
    void            *oscState;
    f32              oscValue;
    u8               chan;

    do {
        switch (seqp->nextEvent.type) {
        case 0: /* AL_SEQ_REF_EVT */
            __n_CSPHandleNextSeqEvent(seqp);
            break;

        case 9: /* AL_SEQP_API_EVT */
            evt.type = 9;
            n_alEvtqPostEvent(&seqp->evtq, &evt, seqp->frameTime, 1);
            break;

        case 5: /* AL_NOTE_END_EVT */
            voice = seqp->nextEvent.msg.note.voice;

            n_alSynStopVoice(voice);
            n_alSynFreeVoice(voice);
            vs = (N_ALVoiceState *)voice->unk10;

            if (vs->flags) {
                __n_seqpStopOsc((N_ALSeqPlayer *)seqp, vs);
            }

            n_seqp_unmap_voice((N_ALSeqPlayer *)seqp, voice);
            break;

        case 6: /* AL_SEQP_ENV_EVT */
            voice = seqp->nextEvent.msg.vol.voice;
            vs = (N_ALVoiceState *)voice->unk10;

            if (vs->envPhase == AL_PHASE_ATTACK) {
                vs->envPhase = AL_PHASE_DECAY;
            }

            delta = seqp->nextEvent.msg.vol.delta;
            vs->envEndTime = seqp->curTime + delta;
            vs->envGain = seqp->nextEvent.msg.vol.vol;
            n_alSynSetVol(voice, __n_vsVol(vs, (N_ALSeqPlayer *)seqp), delta);
            break;

        case 0x17: /* AL_TREM_OSC_EVT */
            vs = seqp->nextEvent.msg.osc.vs;
            oscState = seqp->nextEvent.msg.osc.oscState;
            delta = (*seqp->updateOsc)(oscState, &oscValue);
            vs->tremelo = (u8)oscValue;
            n_alSynSetVol(&vs->voice, __n_vsVol(vs, (N_ALSeqPlayer *)seqp), __n_vsDelta(vs, seqp->curTime));
            evt.type = 0x17;
            evt.msg.osc.vs = vs;
            evt.msg.osc.oscState = oscState;
            n_alEvtqPostEvent(&seqp->evtq, &evt, delta, 0);
            break;

        case 0x18: /* AL_VIB_OSC_EVT */
            vs = seqp->nextEvent.msg.osc.vs;
            oscState = seqp->nextEvent.msg.osc.oscState;
            chan = seqp->nextEvent.msg.osc.chan;
            delta = (*seqp->updateOsc)(oscState, &oscValue);
            vs->vibrato = oscValue;
            n_alSynSetPitch(&vs->voice, vs->pitch * vs->vibrato * CSP_CHAN(chan).pitchBend);

            if (CSP_CHAN(chan).unk14) {
                func_1001CA90(&vs->voice,
                        440.0f
                        * func_1001CEA4(CSP_CHAN(chan).unk15 + (vs->key - vs->sound->keyMap->keyBase) - 64)
                        * CSP_CHAN(chan).pitchBend
                        * vs->vibrato);
            }

            evt.type = 0x18;
            evt.msg.osc.vs = vs;
            evt.msg.osc.oscState = oscState;
            evt.msg.osc.chan = chan;
            n_alEvtqPostEvent(&seqp->evtq, &evt, delta, 0);
            break;

        case 2:    /* AL_SEQP_MIDI_EVT */
        case 0x16: /* AL_CSP_NOTEOFF_EVT */
            __n_CSPHandleMIDIMsg(seqp, &seqp->nextEvent);
            break;

        case 7: /* AL_SEQP_META_EVT */
            __n_CSPHandleMetaMsg(seqp, &seqp->nextEvent);
            break;

        case 10: /* AL_SEQP_VOL_EVT */
            seqp->vol = seqp->nextEvent.msg.spvol.vol;

            for (vs = seqp->vAllocHead; vs != 0; vs = vs->next) {
                n_alSynSetVol(&vs->voice,
                        __n_vsVol(vs, (N_ALSeqPlayer *)seqp),
                        __n_vsDelta(vs, seqp->curTime));
            }
            break;

        case 0x19:
            seqp->unk7C = seqp->nextEvent.msg.unknown0.unk0;
            seqp->unk80 = seqp->nextEvent.msg.unknown0.unk4;

            for (vs = seqp->vAllocHead; vs != NULL; ) {
                if (vs->envPhase != 3) {
                    n_alSynSetFXMix(&vs->voice, n_seqp_voice_fx_mix(vs, seqp));
                }
                vs = vs->next;
            }
            break;

        case 0x1A:
            if (seqp->nextEvent.msg.unknown2.unk1 < 8) {
                void *fx = func_1001D9B0(seqp->nextEvent.msg.unknown2.unk0);

                if (fx) {
                    func_1001DAA0(fx,
                            (seqp->nextEvent.msg.unknown2.unk2 << 3) | (seqp->nextEvent.msg.unknown2.unk1 & 7),
                            &seqp->nextEvent.msg.unknown2.unk4);
                }
            } else {
                void *fx = func_1001DA28(seqp->nextEvent.msg.unknown2.unk0);

                if (fx) {
                    func_1001DAE4(fx, seqp->nextEvent.msg.unknown2.unk1, &seqp->nextEvent.msg.unknown2.unk4);
                }
            }
            break;

        case 15: /* AL_SEQP_PLAY_EVT */
            if (seqp->state != AL_PLAYING) {
                s32 oldState = seqp->state;

                if (seqp->target != NULL) {
                    N_ALEvent pevt;
                    s32 deltaTicks;

                    seqp->state = AL_PLAYING;
                    if (__alCSeqNextDelta(seqp->target, &deltaTicks)) {
                        pevt.type = 0;
                        if (oldState == 3) {
                            deltaTicks = *(s32 *)seqp->unk88;
                        }
                        n_alEvtqPostEvent(&seqp->evtq, &pevt, deltaTicks, 0);
                    }
                }
            }
            break;

        case 0x10: /* pause */
            if (seqp->state == AL_PLAYING) {
                seqp->state = 3;
                *(s32 *)seqp->unk88 = n_evtq_flush_type_first(&seqp->evtq, 0);
            }
            break;

        case 0x11: /* AL_SEQP_STOP_EVT */
            if (seqp->state == AL_STOPPING) {
                for (vs = seqp->vAllocHead; vs != 0; vs = seqp->vAllocHead) {
                    n_alSynStopVoice(&vs->voice);
                    n_alSynFreeVoice(&vs->voice);

                    if (vs->flags) {
                        __n_seqpStopOsc((N_ALSeqPlayer *)seqp, vs);
                    }

                    n_seqp_unmap_voice((N_ALSeqPlayer *)seqp, &vs->voice);
                }

                seqp->state = AL_STOPPED;

                for (chan = 0; chan < 16; chan++) {
                    if (CSP_CHAN(chan).unk36) {
                    }
                    if (CSP_CHAN(chan).instrument) {
                        ((CSPSynth *)seqp->drvr)->unk34(seqp->bank->instArray[CSP_CHAN(chan).unk38]);
                        CSP_CHAN(chan).instrument = NULL;
                    }
                }
            }
            break;

        case 0x12: /* AL_SEQP_STOPPING_EVT */
            if (seqp->state == AL_PLAYING || seqp->state == 3) {
                n_evtq_flush_type_first(&seqp->evtq, 0);
                n_evtq_flush_type_first(&seqp->evtq, 0x16);
                n_evtq_flush_type_first(&seqp->evtq, 2);

                for (vs = seqp->vAllocHead; vs != 0; vs = vs->next) {
                    if (n_seqp_cancel_voice_kill((N_ALSeqPlayer *)seqp, &vs->voice, KILL_TIME)) {
                        __n_seqpReleaseVoice((N_ALSeqPlayer *)seqp, &vs->voice, KILL_TIME);
                    }
                }

                for (chan = 0; chan < 16; chan++) {
                    CSP_CHAN(chan).unkD = CSP_CHAN(chan).unkE;

                    if (CSP_CHAN(chan).unkD == 0) {
                        seqp->chanMask &= (1 << chan) ^ 0xffff;
                    } else {
                        seqp->chanMask |= 1 << chan;
                    }
                }

                seqp->state = AL_STOPPING;
                evt.type = 0x11;
                n_alEvtqPostEvent(&seqp->evtq, &evt, AL_EVTQ_END, 0);
            }
            break;

        case 12: /* AL_SEQP_PRIORITY_EVT */
            chan = seqp->nextEvent.msg.sppriority.chan;
            CSP_CHAN(chan).priority = seqp->nextEvent.msg.sppriority.priority;
            break;

        case 13: /* AL_SEQP_SEQ_EVT */
            seqp->target = seqp->nextEvent.msg.spseq.seq;
            seqp->chanMask = 0xffff;

            if (seqp->bank) {
                __n_initFromBank((N_ALSeqPlayer *)seqp, seqp->bank);
            }
            break;

        case 14: /* AL_SEQP_BANK_EVT */
            seqp->bank = seqp->nextEvent.msg.spbank.bank;
            __n_initFromBank((N_ALSeqPlayer *)seqp, seqp->bank);
            break;

        case 4: /* AL_SEQ_END_EVT */
        case 3: /* AL_TEMPO_EVT */
        case 1: /* AL_SEQ_MIDI_EVT */
            break;
        }

        seqp->nextDelta = n_alEvtqNextEvent(&seqp->evtq, &seqp->nextEvent);
    } while (seqp->nextDelta == 0);

    seqp->curTime += seqp->nextDelta;
    return seqp->nextDelta;
}

extern void (*jtbl_8002C4CC[])(void);
// jump table
// s125: DK64 n_csplayer.c func_global_asm_80733A88 (__CSPHandleNextSeqEvent); Conker event ids
// (track end 0x13, loop start 0x14, loop end 0x15, seqp stop 0x11) and a state 3 check
static void __n_CSPHandleNextSeqEvent(N_ALCSPlayer *seqp)
{
    N_ALEvent evt;

    if (seqp->target == NULL || seqp->state == 3)
        return;

    n_alCSeqNextEvent(seqp->target, &evt, 1);

    switch (evt.type)
    {
      case 1:
          __n_CSPHandleMIDIMsg(seqp, &evt);
          __n_CSPPostNextSeqEvent(seqp);
          break;

      case 3:
          __n_CSPHandleMetaMsg(seqp, &evt);
          __n_CSPPostNextSeqEvent(seqp);
          break;

      case 4:
          seqp->state = AL_STOPPING;
          evt.type    = 0x11;
          n_alEvtqPostEvent(&seqp->evtq, &evt, AL_EVTQ_END, 0);
          break;

      case 0x13:
      case 0x14:
      case 0x15:
          __n_CSPPostNextSeqEvent(seqp);
          break;
      default:
          break;
    }
}
// jump table
// s127: DK64 n_csplayer.c func_global_asm_80733D8C (__CSPHandleMIDIMsg) with Conker's changes: channels
// with unk36 set re-queue every non-program-change message, controller handlers come from a
// table (D_8002BDA0), program change goes through n_cseqp_set_inst_chan_state and may re-queue itself
typedef ALMicroTime (*CSPOscInit)(void **oscState, f32 *initVal, u8 oscType, u8 rate, u8 depth, u8 delay, u8 arg6);
extern ALMicroTime D_80042BB0[];
extern void (*D_8002BDA0[])(N_ALCSPlayer *, N_ALEvent *, u8, u8);
extern void (*D_8002C310[])(N_ALCSPlayer *, N_ALEvent *, u8, u8);
ALSound *n_seqp_lookup_sound_quick(N_ALCSPlayer *seqp, u8 key, u8 vel, u8 chan);
N_ALVoiceState *n_seqp_lookup_voice(N_ALCSPlayer *seqp, u8 key, u8 chan);
s32 n_cseqp_set_inst_chan_state(N_ALCSPlayer *seqp, s32 id, u8 chan);

void __n_CSPHandleMIDIMsg(N_ALCSPlayer *seqp, N_ALEvent *event)
{
    N_ALVoice          *voice;
    s32                 status;
    u8                  chan;
    u8                  key;
    u8                  byte1;
    u8                  byte2;
    ALMIDIEvent        *midi = &event->msg.midi;
    N_ALEvent           evt;
    ALMicroTime         deltaTime;
    N_ALVoiceState     *vstate;
    CSPChanState       *chanstate;
    s32                 sp90;
    ALVoiceConfig       config;
    ALSound            *sound;
    s16                 cents;
    f32                 pitch;
    f32                 oscValue;
    u8                  fxmix;
    u8                  sp76;
    ALPan               pan;
    s16                 vol;
    f32                 sp70;
    void               *oscState;
    ALInstrument       *inst;
    N_ALVoiceState     *vs;

    status = midi->status & AL_MIDI_StatusMask;
    chan = midi->status & AL_MIDI_ChannelMask;
    byte1 = key = midi->byte1;
    byte2 = midi->byte2;

    if (CSP_CHAN(chan).unk36 && status != AL_MIDI_ProgramChange) {
        evt.type = 2;
        evt.msg.midi = *midi;
        n_alEvtqPostEvent(&seqp->evtq, &evt, 33333, 0);
        return;
    }

    switch (status) {
    case AL_MIDI_NoteOn:
        if (byte2 != 0) {
            oscState = 0;

            if (seqp->state != AL_PLAYING || (seqp->chanMask & (1 << chan)) == 0) {
                if (midi->duration) {
                    evt.type = 2;
                    evt.msg.midi.status = chan | AL_MIDI_NoteOff;
                    evt.msg.midi.byte1 = key;
                    evt.msg.midi.byte2 = 0;
                    deltaTime = seqp->uspt * midi->duration;
                    D_80042BB0[chan] = deltaTime;
                    n_alEvtqPostEvent(&seqp->evtq, &evt, deltaTime, 0);
                }
                break;
            }

            chanstate = &CSP_CHAN(chan);

            sound = n_seqp_lookup_sound_quick(seqp, key, byte2, chan);
            if (sound == NULL) {
                break;
            }
            ALFlagFailIf(!sound, seqp->debugFlags & NO_SOUND_ERR_MASK, ERR_ALSEQP_NO_SOUND);

            config.priority = chanstate->priority;
            config.fxBus = chanstate->unkB;
            config.unityPitch = 0;
            config.unk8 = 0;

            vstate = __n_mapVoice((N_ALSeqPlayer *)seqp, key, byte2, chan);
            ALFlagFailIf(!vstate, seqp->debugFlags & NO_VOICE_ERR_MASK, ERR_ALSEQP_NO_VOICE);

            voice = &vstate->voice;

            n_alSynAllocVoice(voice, &config);

            vstate->sound = sound;
            vstate->envPhase = AL_PHASE_ATTACK;

            if (chanstate->sustain > AL_SUSTAIN) {
                vstate->phase = AL_PHASE_SUSTAIN;
            } else {
                vstate->phase = AL_PHASE_NOTEON;
            }

            cents = (key - sound->keyMap->keyBase) * 100 + sound->keyMap->detune;

            if (chanstate->unk28) {
                cents += chanstate->unk2B;
            }

            vstate->pitch = alCents2Ratio(cents);

            if (chanstate->unk28) {
                vstate->envGain = chanstate->attackVolume;
                vstate->envEndTime = seqp->curTime + chanstate->attackTime;
            } else {
                vstate->envGain = sound->envelope->attackVolume;
                vstate->envEndTime = seqp->curTime + sound->envelope->attackTime;
            }

            vstate->flags = 0;

            if (chanstate->unk28) {
                sp90 = chanstate->tremType;
            } else {
                inst = CSP_CHAN(chan).instrument;
                sp90 = inst->tremType;
            }

            oscValue = (f32)AL_VOL_FULL;

            if (sp90) {
                if (seqp->initOsc) {
                    if (chanstate->unk28) {
                        deltaTime = ((CSPOscInit)seqp->initOsc)(&oscState, &oscValue, chanstate->tremType,
                                chanstate->tremRate, chanstate->tremDepth, chanstate->tremDelay, chanstate->unk35);
                    } else {
                        deltaTime = ((CSPOscInit)seqp->initOsc)(&oscState, &oscValue, inst->tremType,
                                inst->tremRate, inst->tremDepth, inst->tremDelay, chanstate->unk35);
                    }

                    if (deltaTime) {
                        evt.type = 0x17;
                        evt.msg.osc.vs = vstate;
                        evt.msg.osc.oscState = oscState;
                        n_alEvtqPostEvent(&seqp->evtq, &evt, deltaTime, 0);
                        vstate->flags |= 0x01;
                        *(void **)vstate->pad3C = oscState;
                    }
                }
            }

            vstate->tremelo = (u8)oscValue;

            oscValue = 1.0f;

            if (chanstate->unk28) {
                sp90 = chanstate->vibType;
            } else {
                sp90 = inst->vibType;
            }

            if (sp90) {
                if (seqp->initOsc) {
                    if (chanstate->unk28) {
                        deltaTime = ((CSPOscInit)seqp->initOsc)(&oscState, &oscValue, chanstate->vibType,
                                chanstate->vibRate, chanstate->vibDepth, chanstate->vibDelay, chanstate->unk35);
                    } else {
                        deltaTime = ((CSPOscInit)seqp->initOsc)(&oscState, &oscValue, inst->vibType,
                                inst->vibRate, inst->vibDepth, inst->vibDelay, chanstate->unk35);
                    }

                    if (deltaTime) {
                        evt.type = 0x18;
                        evt.msg.osc.vs = vstate;
                        evt.msg.osc.oscState = oscState;
                        evt.msg.osc.chan = chan;
                        n_alEvtqPostEvent(&seqp->evtq, &evt, deltaTime, 0);
                        vstate->flags |= 0x02;
                        *(void **)&vstate->pad3C[4] = oscState;
                    }
                }
            }

            vstate->vibrato = oscValue;

            pitch = vstate->pitch * chanstate->pitchBend * vstate->vibrato;

            fxmix = n_seqp_voice_fx_mix(vstate, seqp);

            sp76 = chanstate->unk14;

            if (sp76) {
                sp70 = 440 * func_1001CEA4(cents / 100 + chanstate->unk15 - 64) * chanstate->pitchBend;
            } else {
                sp70 = 127.0f;
            }

            pan = __n_vsPan(vstate, (N_ALSeqPlayer *)seqp);
            vol = __n_vsVol(vstate, (N_ALSeqPlayer *)seqp);

            if (chanstate->unk28) {
                deltaTime = chanstate->attackTime;
            } else {
                deltaTime = sound->envelope->attackTime;
            }

            n_alSynStartVoiceParams(voice, sound->wavetable,
                    pitch, vol, pan, fxmix, sp76, sp70, chanstate->unk16, deltaTime);

            evt.type = AL_SEQP_ENV_EVT;
            evt.msg.vol.voice = voice;

            if (chanstate->unk28) {
                evt.msg.vol.vol = chanstate->decayVolume;
                evt.msg.vol.delta = chanstate->decayTime;
            } else {
                evt.msg.vol.vol = sound->envelope->decayVolume;
                evt.msg.vol.delta = sound->envelope->decayTime;
            }

            n_alEvtqPostEvent(&seqp->evtq, &evt, deltaTime, 0);

            if (midi->duration) {
                evt.type            = 0x16;
                evt.msg.midi.status = chan | AL_MIDI_NoteOff;
                evt.msg.midi.byte1  = key;
                evt.msg.midi.byte2  = 0;
                deltaTime = seqp->uspt * midi->duration;
                D_80042BB0[chan] = deltaTime;
                n_alEvtqPostEvent(&seqp->evtq, &evt, deltaTime, 0);
            }

            if ((chanstate->unk17 & 1) && seqp->unk84) {
                osSendMesg((OSMesgQueue *)seqp->unk84, (OSMesg)((D_80042BB0[chan] & 0xffffff00) | (chanstate->unk17 >> 2)), OS_MESG_NOBLOCK);
            }

            break;
        }

    case AL_MIDI_NoteOff:
        vstate = n_seqp_lookup_voice(seqp, key, chan);
        ALFlagFailIf(!vstate, seqp->debugFlags & NOTE_OFF_ERR_MASK, ERR_ALSEQP_OFF_VOICE);

        chanstate = &CSP_CHAN(chan);

        if (vstate->phase == AL_PHASE_SUSTAIN) {
            vstate->phase = AL_PHASE_SUSTREL;
        } else {
            vstate->phase = AL_PHASE_RELEASE;

            if (chanstate->unk28) {
                __n_seqpReleaseVoice((N_ALSeqPlayer *)seqp, &vstate->voice, chanstate->releaseTime);
            } else {
                __n_seqpReleaseVoice((N_ALSeqPlayer *)seqp, &vstate->voice, vstate->sound->envelope->releaseTime);
            }
        }

        if ((chanstate->unk17 & 2) && seqp->unk84) {
            osSendMesg((OSMesgQueue *)seqp->unk84, (OSMesg)(key << 16 | 8 | chanstate->unk17 >> 2), OS_MESG_NOBLOCK);
        }

        break;

    case AL_MIDI_PolyKeyPressure:
        vstate = n_seqp_lookup_voice(seqp, key, chan);
        ALFailIf(!vstate, ERR_ALSEQP_POLY_VOICE);

        vstate->velocity = byte2;
        n_alSynSetVol(&vstate->voice,
                __n_vsVol(vstate, (N_ALSeqPlayer *)seqp),
                __n_vsDelta(vstate, seqp->curTime));
        break;

    case AL_MIDI_ChannelPressure:
        for (vs = seqp->vAllocHead; vs != 0; vs = vs->next) {
            if (vs->channel == chan) {
                vs->velocity = byte1;
                n_alSynSetVol(&vs->voice,
                        __n_vsVol(vs, (N_ALSeqPlayer *)seqp),
                        __n_vsDelta(vs, seqp->curTime));
            }
        }
        break;

    case AL_MIDI_ControlChange:
        {
            void (*handler)(N_ALCSPlayer *, N_ALEvent *, u8, u8);

            if (byte1 < 0x5D) {
                handler = D_8002BDA0[byte1];
            } else if (byte1 >= 0xFC) {
                handler = D_8002C310[-byte1]; // the four 0xFC-0xFF handlers follow the 0x5D low ones
            } else {
                handler = NULL;
            }

            if (handler) {
                if (1) { // fakematch: dead debug branch, keeps the chan == 2 compare
                } else if (chan == 2) {
                }
                handler(seqp, event, chan, byte2);
            }
        }
        break;

    case AL_MIDI_ProgramChange:
        sp90 = (CSP_CHAN(chan).unk8 << 7) + key;
        if (sp90 < seqp->bank->instCount) {
            if (n_cseqp_set_inst_chan_state(seqp, sp90, chan)) {
                evt.type = 2;
                evt.msg.midi.ticks = 0;
                evt.msg.midi.status = chan | AL_MIDI_ProgramChange;
                evt.msg.midi.byte1 = key;
                evt.msg.midi.byte2 = 0;
                n_alEvtqPostEvent(&seqp->evtq, &evt, 33333, 0);
            }
        } else {
        }
        break;

    case AL_MIDI_PitchBendChange:
        {
            s32 bendVal;
            f32 bendRatio;
            s32 cents;
            N_ALVoiceState *vs;

            bendVal = ((byte2 << 7) + byte1) - 8192;
            cents = (CSP_CHAN(chan).bendRange * bendVal) / 8192;
            bendRatio = alCents2Ratio(cents);
            CSP_CHAN(chan).pitchBend = bendRatio;

            for (vs = seqp->vAllocHead; vs != 0; vs = vs->next) {
                if (vs->channel == chan) {
                    n_alSynSetPitch(&vs->voice, vs->pitch * bendRatio * vs->vibrato);
                    if (CSP_CHAN(chan).unk14) {
                        func_1001CA90(&vs->voice, 440 * func_1001CEA4(CSP_CHAN(chan).unk15 + (vs->key - vs->sound->keyMap->keyBase) - 64) * bendRatio * vs->vibrato);
                    }
                }
            }
        }
        break;

    default:
        break;
    }
}

void __n_CSPHandleMetaMsg(N_ALCSPlayer *seqp, N_ALEvent *event)
{
  ALTempoEvent    *tevt = &event->msg.tempo;
  s32             tempo;
  s32             oldUspt;
  u32             ticks;
  ALMicroTime         tempDelta,curDelta = 0;
  N_ALEventListItem     *thisNode,*nextNode,*firstTemp = 0;
  N_ALEventListItem     *temp0,*temp1,*temp2;

  if (event->msg.tempo.status == AL_MIDI_Meta) {
    if (event->msg.tempo.type == AL_MIDI_META_TEMPO) {
      oldUspt = seqp->uspt;
      tempo = (tevt->byte1 << 16) | (tevt->byte2 <<  8) | (tevt->byte3 <<  0);
      __n_setUsptFromTempo (seqp, (f32)tempo);    /* sct 1/8/96 */

      thisNode = (N_ALEventListItem*)seqp->evtq.allocList.next;
      while (thisNode) {
          curDelta += thisNode->delta;
          nextNode = (N_ALEventListItem*)thisNode->node.next;
          if (thisNode->evt.type == 0x16 ) { // AL_CSP_NOTEOFF_EVT
              // custom
              temp0 = thisNode;
              if (temp0->node.next) {
                  temp0->node.next->prev = temp0->node.prev;
              }
              if (temp0->node.prev) {
                  temp0->node.prev->next = temp0->node.next;
              }
              if (firstTemp != 0) {
                  temp1 = thisNode;
                  if (1) {
                      temp2 = firstTemp;

                      temp1->node.next = temp2->node.next;
                      temp1->node.prev = temp2;

                      if (temp2->node.next != 0) {
                          temp2->node.next->prev = temp1;
                      }
                      temp2->node.next = temp1;
                  }
              } else {
                    thisNode->node.next = 0;
                    thisNode->node.prev = 0;
                    firstTemp = thisNode;
              }

              tempDelta = curDelta;                   /* record the current delta */
              if (nextNode)                           /* don't do this if no nextNode */ {
                  curDelta -= thisNode->delta;        /* subtract out this delta */
                  nextNode->delta += thisNode->delta; /* add it to next event */
              }
              thisNode->delta = tempDelta;            /* set this event delta from current */
          }
          thisNode = nextNode;
      }

      thisNode = firstTemp;
      while (thisNode) {
          nextNode = (N_ALEventListItem*)thisNode->node.next;
          ticks = thisNode->delta/oldUspt;
          thisNode->delta = ticks * seqp->uspt;
          __n_CSPRepostEvent(&seqp->evtq,thisNode);
          thisNode = nextNode;
      }
    }
  }
}

void __n_CSPRepostEvent(ALEventQueue *evtq, N_ALEventListItem *item)
{
    ALLink            *node;
    N_ALEventListItem *nextItem;

    for (node = &evtq->allocList; node != 0; node = node->next) {
        if (!node->next) { /* end of the list */
            N_AL_LINK(item, node);
            break;
        } else {
            nextItem = (N_ALEventListItem *)node->next;
            if (item->delta < nextItem->delta) {
                nextItem->delta -= item->delta;
                N_AL_LINK(item, node);
                break;
            }
            item->delta -= nextItem->delta;
        }
    }
}

void __n_setUsptFromTempo (N_ALCSPlayer *seqp, f32 tempo)
{
  if (seqp->target)
    seqp->uspt = (s32)((f32)tempo * seqp->target->qnpt);
  else
    seqp->uspt = 488;    /* This is the initial value set by alSeqpNew. */
}

void __n_CSPPostNextSeqEvent(N_ALCSPlayer *seqp)
{
  N_ALEvent   evt;
  s32    deltaTicks;

  if (seqp->state != AL_PLAYING || seqp->target == NULL)
    return;

  /* Get the next event time in ticks. */
  /* If false is returned, then there is no next delta (ie. end of sequence reached). */
  if (!__alCSeqNextDelta(seqp->target, &deltaTicks))
    return;

  evt.type = AL_SEQ_REF_EVT;
  n_alEvtqPostEvent(&seqp->evtq, &evt, deltaTicks * seqp->uspt, 0);
}
