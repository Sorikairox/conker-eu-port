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
void func_1001AAE0(N_ALSeqPlayer *seqp, N_ALVoice *voice) {
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
u8 func_1001ADA4(N_ALSeqPlayer *seqp, N_ALVoice *voice, ALMicroTime time) {
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
N_ALVoiceState *func_1001AFEC(N_ALSeqPlayer *seqp, u8 key, u8 channel) {
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
ALSound *func_1001B07C(N_ALSeqPlayer *seqp, u8 key, u8 vel, u8 chan) {
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
u8 func_1001B310(N_ALVoiceState *vs, N_ALCSPlayer *seqp) {
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

#pragma GLOBAL_ASM("asm/nonmatchings/init_1AAE0/func_1001B7D0.s")
s32 func_1001BD34(struct_eu_1AAE0 *arg0, ALInstrument **arg1, s32 arg2) {
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

void func_1001BE1C(struct_eu_1AAE0 *arg0, ALInstrument *arg1, s32 arg2) {
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
