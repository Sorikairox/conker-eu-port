#include <n_libaudio.h>

void __n_resetPerfChanState(N_ALSeqPlayer *seqp, s32 chan);

// alUnlink / alLink, expanded inline in this version of the library
#define N_AL_UNLINK(e)                          \
    {                                           \
        ALLink *ln = (ALLink *)(e);             \
                                                \
        if (ln->next != NULL) {                 \
            ln->next->prev = ln->prev;          \
        }                                       \
        if (ln->prev != NULL) {                 \
            ln->prev->next = ln->next;          \
        }                                       \
    }

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

// player with sample-loading callbacks (layout partly known)
typedef s32 (*struct_eu_1AAE0_cb)(void *arg0, s32 arg1);
typedef struct {
    u8 pad0[0x28];
    struct_eu_1AAE0_cb (*unk28)(void);
    u8 pad2C[0x4];
    void (*unk30)(void *arg0);
} struct_eu_1AAE0;

// __n_unmapVoice
/* was func_1001AAE0 */
void n_seqp_unmap_voice(N_ALSeqPlayer *seqp, N_ALVoice *voice) {
    N_ALVoiceState *prev = 0;
    N_ALVoiceState *vs;

    for (vs = seqp->vAllocHead; vs != 0; vs = vs->next) {
        if (&vs->voice == voice) {
            if (prev) {
                prev->next = vs->next;
            } else {
                seqp->vAllocHead = vs->next;
            }
            if (vs == seqp->vAllocTail) {
                seqp->vAllocTail = prev;
            }
            vs->next = seqp->vFreeList;
            seqp->vFreeList = vs;
            seqp->usedVoices--;
            return;
        }
        prev = vs;
    }
}

void __n_seqpReleaseVoice(N_ALSeqPlayer *seqp, N_ALVoice *voice, ALMicroTime deltaTime) {
    N_ALEvent evt;
    N_ALVoiceState *vs = (N_ALVoiceState *)voice->unk10;
    ALLink *thisNode;
    ALLink *nextNode;
    N_ALEventListItem *thisItem;
    N_ALEventListItem *nextItem;

    /*
     * if in attack phase, remove all pending volume
     * events for this voice from the queue
     */
    if (vs->envPhase == AL_PHASE_ATTACK) {
        thisNode = seqp->evtq.allocList.next;
        while (thisNode != 0) {
            nextNode = thisNode->next;
            thisItem = (N_ALEventListItem *)thisNode;
            nextItem = (N_ALEventListItem *)nextNode;
            if (thisItem->evt.type == 6 /* volume */) {
                if (thisItem->evt.msg.vol.voice == voice) {
                    if (nextItem) {
                        nextItem->delta = nextItem->delta + thisItem->delta;
                    }
                    N_AL_UNLINK(thisNode);
                    N_AL_LINK(thisNode, &seqp->evtq.freeList);
                }
            }
            thisNode = nextNode;
        }
    }

    vs->velocity = 0;
    vs->envPhase = AL_PHASE_RELEASE;
    vs->envGain = 0;
    vs->envEndTime = seqp->curTime + deltaTime;

    n_alSynSetPriority(voice, 0); /* make candidate for stealing */
    n_alSynSetVol(voice, 0, deltaTime);
    evt.type = 5;
    evt.msg.note.voice = voice;

    deltaTime += 32000;
    n_alEvtqPostEvent(&seqp->evtq, &evt, deltaTime, 0);
}

// removes a pending type 5 (voice) event for this voice if it is due after time
// removes a pending type 5 (voice) event for this voice if it is due after time
/* was func_1001ADA4 */
u8 n_seqp_cancel_voice_kill(N_ALSeqPlayer *seqp, N_ALVoice *voice, ALMicroTime time) {
    N_ALEventListItem *thisNode;
    N_ALEventListItem *nextNode;
    N_ALEventListItem *thisItem;
    ALMicroTime deltaTime = 0;
    u8 ret = 1;

    thisNode = (N_ALEventListItem *)seqp->evtq.allocList.next;
    while (thisNode != NULL) {
        nextNode = (N_ALEventListItem *)thisNode->node.next;
        thisItem = thisNode;
        deltaTime += thisItem->delta;
        if (thisItem->evt.type == 5) {
            if (thisItem->evt.msg.vol.voice == voice) {
                if (time < deltaTime) {
                    if (nextNode != NULL) {
                        nextNode->delta = nextNode->delta + thisItem->delta;
                    }
                    N_AL_UNLINK(thisNode);
                    N_AL_LINK(thisNode, &seqp->evtq.freeList);
                } else {
                    ret = 0;
                }
                break;
            }
        }
        thisNode = nextNode;
    }
    return ret;
}

N_ALVoiceState *__n_mapVoice(N_ALSeqPlayer *seqp, u8 key, u8 vel, u8 channel)
{
    N_ALVoiceState  *vs = seqp->vFreeList;

    if (seqp->usedVoices > seqp->maxVoices) {
        return NULL;
    }

    if (vs) {

        seqp->vFreeList = vs->next;

        vs->next = 0;

        if (!seqp->vAllocHead)
            seqp->vAllocHead = vs;
        else
            seqp->vAllocTail->next = vs;

        seqp->vAllocTail = vs;

        vs->channel             = channel;
        vs->key                 = key;
        vs->velocity            = vel;
        vs->voice.unk10         = vs; // this isn't right

        seqp->usedVoices++;
    }

    return vs;
}

// __n_lookupVoice
// __n_lookupVoice
/* was func_1001AFEC */
N_ALVoiceState *n_seqp_lookup_voice(N_ALSeqPlayer *seqp, u8 key, u8 channel) {
    N_ALVoiceState *vs = seqp->vAllocHead;

    while (vs != NULL) {
        if ((vs->key == key) && (vs->channel == channel) &&
            (vs->phase != AL_PHASE_RELEASE) && (vs->phase != AL_PHASE_SUSTREL)) {
            return vs;
        }
        vs = vs->next;
    }
    return NULL;
}

// __n_lookupSoundQuick
/* was func_1001B07C */
ALSound *n_seqp_lookup_sound_quick(N_ALSeqPlayer *seqp, u8 key, u8 vel, u8 chan) {
    ALInstrument *inst = seqp->chanState[chan].instrument;
    s32 l = 1;
    s32 r;
    s32 i;
    ALKeyMap *keymap;

    if (inst == NULL) {
        return NULL;
    }
    r = inst->soundCount;
    while (r >= l) {
        i = (l + r) / 2;
        keymap = inst->soundArray[i - 1]->keyMap;
        if ((key >= keymap->keyMin) && (key <= keymap->keyMax) &&
            (vel >= keymap->velocityMin) && (vel <= keymap->velocityMax)) {
            return inst->soundArray[i - 1];
        } else if ((key < keymap->keyMin) ||
                   ((vel < keymap->velocityMin) && (key <= keymap->keyMax))) {
            r = i - 1;
        } else {
            l = i + 1;
        }
    }
    return NULL;
}

s16 __n_vsVol(N_ALVoiceState *vs, N_ALSeqPlayer *seqp)
{
    u32     t1,t2;

    t1 = (vs->tremelo*vs->velocity*vs->envGain) >> 6;
    t2 = (vs->sound->sampleVolume*seqp->vol*
          seqp->chanState[vs->channel].vol) >> 14;

    if (seqp->chanState[vs->channel].unkD != 0xFF) {
        t2 = ((seqp->chanState[vs->channel].unkD * t2) + 1) >> 8;
    }

    t1 *= t2;
    t1 >>= 15;

    return t1;
}

// fx mix for a voice, scaled by the player's unk7C/unk80
/* was func_1001B310 */
u8 n_seqp_voice_fx_mix(N_ALVoiceState *vs, N_ALCSPlayer *seqp) {
    s32 hi;
    s32 mix;

    hi = seqp->chanState[vs->channel].fxmix & 0x80;
    mix = ((seqp->chanState[vs->channel].fxmix & 0x7F) + (s32)(seqp->unk7C * 127.0f)) * seqp->unk80;
    return MAX(0, MIN(127, mix)) | hi;
}

ALMicroTime __n_vsDelta(N_ALVoiceState *vs, ALMicroTime t) {
  /*
   * If we are interrupting a previously set envelope segment, we
   * need to recalculate the segment end time given the current
   * time. Note: this routine assumes that the voice is currently
   * playing.
   */

  s32 delta = vs->envEndTime - t;

  if (delta >= 0) {
      return delta;
  } else {
      return AL_GAIN_CHANGE_TIME;
  }
}

ALPan __n_vsPan(N_ALVoiceState *vs, N_ALSeqPlayer *seqp)
{
    s32 tmp;

    tmp = seqp->chanState[vs->channel].pan - AL_PAN_CENTER +
        vs->sound->samplePan;
    tmp = MAX(tmp, AL_PAN_LEFT);
    tmp = MIN(tmp, AL_PAN_RIGHT);

    return (ALPan) tmp;
}

// not vanilla
void __n_initFromBank(N_ALSeqPlayer *seqp, ALBank *b) {
    s32 i;
    ALInstrument *inst = 0;

    /* init to the first available instrument */
    for (i = 1; !inst; i++) {
        inst = b->instArray[i];
    }

    for (i = 0; i < seqp->maxChannels; i++) {
        __n_resetPerfChanState(seqp, i);
    }

    if (b->percussion) {
        __n_resetPerfChanState(seqp, i);
    }
}

void __n_initChanState(N_ALSeqPlayer *seqp)
{
    int i;

    for (i = 0; i < seqp->maxChannels; i++)
    {
        seqp->chanState[i].instrument = 0;
        __n_resetPerfChanState (seqp, i);
    }
}

void __n_resetPerfChanState(N_ALSeqPlayer *seqp, s32 chan) {
    seqp->chanState[chan].fxmix = 0;
    seqp->chanState[chan].pan = AL_PAN_CENTER;
    seqp->chanState[chan].vol = AL_VOL_FULL;
    seqp->chanState[chan].priority = AL_DEFAULT_PRIORITY;
    seqp->chanState[chan].sustain = 0;
    seqp->chanState[chan].bendRange = 200;
    seqp->chanState[chan].pitchBend = 1.0f;
    seqp->chanState[chan].unk17 = 0;
    seqp->chanState[chan].unkD = 255;
    seqp->chanState[chan].unkE = 255;
    seqp->chanState[chan].unkF = 0;
    seqp->chanState[chan].unkB = 0;
    seqp->chanState[chan].unk16 = 0;
    seqp->chanState[chan].unk15 = 0;
    seqp->chanState[chan].unk14 = 0;
    seqp->chanState[chan].unk8 = 0;
}

// s129: DK64 n_seqplayer.c __n_setInstChanState turned into Conker's program-change handler:
// loads the instrument (n_synth_load_instrument), releases the channel's previous one, prepares the
// sounds' envelopes, copies the instrument params into the channel; returns 1 when the load failed
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
    /* 0x38 */ s32 unk38;
} CSPSynth;

#define CSP_CHAN(c) (((CSPChanState *)seqp->chanState)[c])

s32 n_synth_load_instrument(struct_eu_1AAE0 *arg0, ALInstrument **arg1, s32 arg2);
void n_bnkf_patch_sound(ALSound *sound, ALInstrument *inst, s32 arg2);

/* was func_1001B7D0 */
s32 n_cseqp_set_inst_chan_state(N_ALCSPlayer *seqp, s32 id, s32 chan) {
    ALSound *sound;
    ALInstrument *inst;
    s32 i;

    inst = (ALInstrument *)n_synth_load_instrument((struct_eu_1AAE0 *)seqp->drvr, &seqp->bank->instArray[id], -1);
    if (CSP_CHAN(chan).instrument != NULL) {
        ((CSPSynth *)seqp->drvr)->unk34(seqp->bank->instArray[CSP_CHAN(chan).unk38]);
        CSP_CHAN(chan).instrument = NULL;
    }
    if (inst != NULL) {
        for (i = 0; i < inst->soundCount; i++) {
            sound = inst->soundArray[i];
            if ((u32)sound->envelope < 0x100000) {
                n_bnkf_patch_sound(sound, inst, ((CSPSynth *)seqp->drvr)->unk38);
            }
        }
        sound = inst->soundArray[0];
    }
    if (inst != NULL) {
        if (inst->soundCount == 0) {
            return 0;
        }
        if (sound != NULL) {
            CSP_CHAN(chan).attackTime = sound->envelope->attackTime;
            CSP_CHAN(chan).decayTime = sound->envelope->decayTime;
            CSP_CHAN(chan).releaseTime = sound->envelope->releaseTime;
            CSP_CHAN(chan).attackVolume = sound->envelope->attackVolume;
            CSP_CHAN(chan).decayVolume = sound->envelope->decayVolume;
        }
        CSP_CHAN(chan).pan = inst->pan;
        CSP_CHAN(chan).vol = inst->volume;
        CSP_CHAN(chan).priority = inst->priority;
        CSP_CHAN(chan).bendRange = inst->bendRange;
        CSP_CHAN(chan).tremType = inst->tremType;
        CSP_CHAN(chan).tremRate = inst->tremRate;
        CSP_CHAN(chan).tremDepth = inst->tremDepth;
        CSP_CHAN(chan).tremDelay = inst->tremDelay;
        CSP_CHAN(chan).vibType = inst->vibType;
        CSP_CHAN(chan).vibRate = inst->vibRate;
        CSP_CHAN(chan).vibDepth = inst->vibDepth;
        CSP_CHAN(chan).vibDelay = inst->vibDelay;
        CSP_CHAN(chan).unk36 = 0;
        CSP_CHAN(chan).instrument = inst;
    } else {
        CSP_CHAN(chan).unk36 = 1;
    }
    CSP_CHAN(chan).unk2B = 0;
    CSP_CHAN(chan).unk28 = 0;
    CSP_CHAN(chan).unk35 = 0;
    CSP_CHAN(chan).unk38 = id;
    if (inst == NULL) {
        return 1;
    }
    return 0;
}

/* was func_1001BD34 */
s32 n_synth_load_instrument(struct_eu_1AAE0 *arg0, ALInstrument **arg1, s32 arg2) {
    struct_eu_1AAE0_cb cb;
    s32 ret = 0;

    cb = arg0->unk28();
    if (cb != NULL) {
        if (arg2 == -1) {
            ret = cb(arg1, 1);
        } else {
            ret = cb(&(*arg1)->soundArray[arg2], 0);
        }
        if (ret != 0 && (ret & 0xFF000003) != 0x80000000) {
            return 0;
        }
    } else {
        return 0;
    }
    return ret;
}

/* was func_1001BE1C */
void n_synth_release_instrument(struct_eu_1AAE0 *arg0, ALInstrument *arg1, s32 arg2) {
    if (arg2 == -1) {
        arg0->unk30(arg1);
    } else {
        arg0->unk30(arg1->soundArray[arg2]);
    }
}

void __n_seqpStopOsc(N_ALSeqPlayer *seqp, N_ALVoiceState *vs) {
    N_ALEventListItem *thisNode;
    N_ALEventListItem *nextNode;
    s16 evtType;

    thisNode = (N_ALEventListItem *)seqp->evtq.allocList.next;
    while (thisNode) {
        nextNode = (N_ALEventListItem *)thisNode->node.next;
        evtType = thisNode->evt.type;
        if (evtType == 0x17 || evtType == 0x18) { /* AL_TREM_OSC_EVT, AL_VIB_OSC_EVT */
            if (thisNode->evt.msg.osc.vs == vs) {
                (*seqp->stopOsc)((void *)thisNode->evt.msg.osc.oscState);
                N_AL_UNLINK(thisNode);
                if (nextNode) {
                    nextNode->delta += thisNode->delta;
                }
                N_AL_LINK(thisNode, &seqp->evtq.freeList);
                if (evtType == 0x17) {
                    vs->flags = vs->flags & 0xFE;
                } else {
                    vs->flags = vs->flags & 0xFD;
                }
                if (!vs->flags) {
                    return; /* there should be no more events */
                }
            }
        }
        thisNode = nextNode;
    }
}
