#include <n_libaudio.h>

void func_10016F80(ALEventQueue *evtq, s32 arg1, u16 arg2);


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

void func_10015550(N_ALCSPlayer *csp, s32 arg1) {
    N_ALEvent event;

    event.type = 14;
    event.msg.midi.ticks = arg1;

    n_alEvtqPostEvent(&csp->evtq, &event, 0, 2);
}

// s127: DK64 n_sndplayer.c func_global_asm_80735AA0 (sound player init) with Conker's 0x58-byte sound
// states, the D_8002BA44 driver, an extra config word at sndp 0x54 and the 4-arg n_alEvtqPostEvent
// s127: DK64 n_sndplayer.c func_global_asm_80735DBC (_n_handleEvent) with Conker's changes: sounds are
// loaded on demand (event 0x4000 -> func_1001BD34, retried while unk40 > 0), no-sound events are
// re-posted, fx bus (0x2000) and 0x8000 events, the dead "freed too early" prints in the stop case
typedef struct {
    /* 0x00 */ s32 pad0[4];
    /* 0x10 */ s32 unk10[1];
} SndTbl155;

typedef struct {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ SndTbl155 *unkC;
} SndBank155;

typedef struct SndState155_s {
    /* 0x00 */ ALLink node;
    /* 0x08 */ u8 pad8[4];
    /* 0x0C */ ALSound *sound;
    /* 0x10 */ N_ALVoice voice;
    /* 0x30 */ f32 basepitch;
    /* 0x34 */ f32 pitch;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ SndBank155 *unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s16 vol;
    /* 0x46 */ s16 envvol;
    /* 0x48 */ ALMicroTime endtime;
    /* 0x4C */ s16 unk4C;
    /* 0x4E */ u8 priority;
    /* 0x4F */ u8 pan;
    /* 0x50 */ u8 fxmix;
    /* 0x51 */ u8 fxbus;
    /* 0x52 */ u8 unk52;
    /* 0x53 */ u8 flags;
    /* 0x54 */ u8 state;
    /* 0x55 */ u8 pad55[3];
} SndState155;

typedef struct {
    /* 0x00 */ u16 type;
    /* 0x04 */ SndState155 *state;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
} SndEvt155;

#define SND_VOL155(state, sound, keymap) \
    ((((s16 *)D_80042C58)[(keymap)->keyMin & 0x1f] * ((state)->envvol * (state)->vol * (sound)->sampleVolume / 0x3f01)) / 0x7fff)
#define SND_MIN155(a, b) ((a) < (b) ? (a) : (b))
#define SND_MAX155(a, b) ((a) > (b) ? (a) : (b))

ALSound *func_1001BD34(N_ALSynth *drvr, SndTbl155 **arg1, s16 arg2);
void func_1001BE1C(N_ALSynth *drvr, SndTbl155 *arg1, s16 arg2);
void func_10002088(const char *fmt, ...);
void func_1001E2A0(N_ALVoice *v, u8 pan);
void func_1001E350(N_ALVoice *v, u8 arg1);
void func_10016E90();
void func_10016F00();
N_ALUnknownStruct1 *func_10017438(s32 arg0, s16 arg1, u16 arg2, u8 arg3, f32 arg4, u8 arg5, u8 arg6, s32 *arg7);

void _n_handleEvent(SndEvt155 *event);

typedef struct {
    /* 0x00 */ u32 maxStates;
    /* 0x04 */ s32 maxEvents;
    /* 0x08 */ s32 maxSounds;
    /* 0x0C */ ALHeap *heap;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u16 unk14;
} SndpConfig155;


typedef struct {
    /* 0x00 */ N_ALSndPlayer sndp;
    /* 0x54 */ s32 unk54;
} SndPlayer155;

extern N_ALSynth *D_8002BA44;
extern u16 *D_80042C58;
s32 func_10015878(N_ALSndPlayer *sp);

s32 func_100155A0(SndpConfig155 *c) {
    u32 i;
    ALEventListItem *items;
    N_ALEvent evt;
    SndState155 *sndState;

    D_8002BA2C->maxSounds = c->maxSounds;
    D_8002BA2C->target = 0;
    D_8002BA2C->drvr = D_8002BA44;
    D_8002BA2C->frameTime = 16000;
    items = alHeapAlloc(c->heap, c->maxStates, sizeof(SndState155));
    D_8002BA2C->sndState = items;
    ((SndPlayer155 *)D_8002BA2C)->unk54 = c->unk10;
    items = alHeapAlloc(c->heap, c->maxEvents, sizeof(N_ALEventListItem));
    n_alEvtqNew(&D_8002BA2C->evtq, items, c->maxEvents);
    D_8002BA28 = D_8002BA2C->sndState;
    for (i = 1; i < c->maxStates; i++) {
        ALLink *ln;
        ALLink *to;

        sndState = D_8002BA2C->sndState;
        ln = (ALLink *)(i + sndState);
        to = (ALLink *)(i + sndState - 1);
        ln->next = to->next;
        ln->prev = to;
        if (to->next != NULL) {
            to->next->prev = ln;
        }
        to->next = ln;
    }

    D_80042C58 = alHeapAlloc(c->heap, 2, c->unk14);
    for (i = 0; i < c->unk14; i++) {
        D_80042C58[i] = 0x7FFF;
    }

    D_8002BA2C->node.next = NULL;
    D_8002BA2C->node.handler = func_10015878;
    D_8002BA2C->node.clientData = D_8002BA2C;
    n_alSynAddPlayer(D_8002BA2C);
    evt.type = 0x20;
    n_alEvtqPostEvent(&D_8002BA2C->evtq, &evt, D_8002BA2C->frameTime, 3);
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
            _n_handleEvent((SndEvt155 *)&alsp->nextEvent);
            break;
        }
        alsp->nextDelta = n_alEvtqNextEvent(&alsp->evtq, &alsp->nextEvent);
    } while (alsp->nextDelta == 0);

    alsp->curTime += alsp->nextDelta;
    return alsp->nextDelta;
}

// jump table
void _n_handleEvent(SndEvt155 *event)
{
    ALVoiceConfig config;
    ALSound *sound;
    ALKeyMap *keymap;
    ALPan pan;
    SndEvt155 sp94;
    SndEvt155 sp84;
    ALMicroTime delta;
    s32 fxmix;
    s32 vol;
    s32 tmppan;
    s32 sp70;
    s32 isspecial;
    s32 done = TRUE;
    s32 hasvoice = FALSE;
    SndState155 *state = NULL;
    SndState155 *nextstate = NULL;
    s32 sp44;

    do {
        if (nextstate != NULL) {
            sp84.state = state;
            sp84.type = event->type;
            sp84.unk08 = event->unk08;
            event = &sp84;
        }

        state = event->state;
        if (state == NULL) { // empty check (compiled-out assert in the original)
        }
        sound = state->sound;
        nextstate = (SndState155 *)state->node.next;

        if (sound == NULL && event->type != 0x4000) {
            if (state->unk40 > 0) {
                if (event->type != 4 && event->type != 8 && event->type != 0x100 && event->type != 0x10
                        && event->type != 0x800 && event->type != 0x2000) {
                    state->unk40--;
                }
                n_alEvtqPostEvent(&D_8002BA2C->evtq, (N_ALEvent *)event, 33333, 2);
            } else {
                func_10016E90(state);
            }
        } else {
            switch (event->type) {
            case 0x4000:
                if (sound == NULL) {
                    sound = func_1001BD34(D_8002BA2C->drvr, &state->unk3C->unkC, state->unk4C);
                    state->sound = sound;
                    if (sound == NULL) {
                        event->type = 0x4000;
                        state->state = 5;
                        state->unk40--;
                        n_alEvtqPostEvent(&D_8002BA2C->evtq, (N_ALEvent *)event, 33333, 2);
                        break;
                    }
                }
                if (sound != NULL) {
                    if ((u32)sound->envelope < 0x1000000) {
                        func_10012C5C(sound, sound, ((SndPlayer155 *)D_8002BA2C)->unk54);
                    }
                    if (((u32)sound->envelope & 0xFF000003) != 0x80000000) {
                        break;
                    }
                    keymap = sound->keyMap;
                    state->sound = sound;
                    sp44 = sound->envelope->decayTime == -1;
                    state->priority = sp44 + 0x40;
                    state->flags = (keymap->keyMax & 0xF0) | 1;
                    if (state->flags & 0x20) {
                        state->basepitch = alCents2Ratio(keymap->keyBase * 100 - 6000);
                    } else {
                        state->basepitch = alCents2Ratio(keymap->keyBase * 100 + keymap->detune - 6000);
                    }
                    if (sp44) {
                        state->flags |= 2;
                    }
                }
                event->type = 1;
                /* fallthrough */
            case 1:
                if (state->state != 5 && state->state != 4) {
                    return;
                }
                keymap = sound->keyMap;
                config.fxBus = state->fxbus;
                config.priority = state->priority;
                config.unityPitch = 0;
                config.unk8 = state->unk3C->unkC->unk10[state->unk4C];
                sp70 = D_8002BA30 >= D_8002BA2C->maxSounds;
                if (!sp70 || (state->flags & 0x10)) {
                    hasvoice = n_alSynAllocVoice(&state->voice, &config);
                }
                if (!hasvoice) {
                    if ((state->flags & 0x12) || state->unk40 > 0) {
                        state->state = 4;
                        state->unk40--;
                        n_alEvtqPostEvent(&D_8002BA2C->evtq, (N_ALEvent *)event, 33333, 2);
                    } else {
                        func_10016E90(state);
                    }
                    return;
                }
                state->flags |= 4;
                state->envvol = sound->envelope->attackVolume;
                state->fxbus = config.fxBus;
                delta = sound->envelope->attackTime / state->pitch / state->basepitch;
                state->endtime = D_8002BA2C->curTime + delta;
                vol = SND_MAX155(0, SND_VOL155(state, sound, keymap) - 1);
                tmppan = state->pan + sound->samplePan - AL_PAN_CENTER;
                pan = SND_MIN155(SND_MAX155(tmppan, 0), 127);
                fxmix = (state->fxmix & 0x7f) + (keymap->keyMax & 0xf) * 8;
                fxmix = SND_MIN155(127, SND_MAX155(0, fxmix));
                fxmix |= state->fxmix & 0x80;
                func_1001BE1C(D_8002BA2C->drvr, state->unk3C->unkC, state->unk4C);
                n_alSynStartVoiceParams(&state->voice, sound->wavetable, state->pitch * state->basepitch, vol, pan, fxmix, 0, 0.0f, 0, delta);
                state->state = AL_PLAYING;
                D_8002BA30++;
                if ((state->flags & 2) == 0) {
                    if (delta == 0) {
                        state->envvol = sound->envelope->decayVolume;
                        vol = SND_MAX155(0, SND_VOL155(state, sound, keymap) - 1);
                        delta = sound->envelope->decayTime / state->basepitch / state->pitch;
                        state->endtime = D_8002BA2C->curTime + delta;
                        n_alSynSetVol(&state->voice, vol, delta);
                        sp94.type = 2;
                        sp94.state = state;
                        n_alEvtqPostEvent(&D_8002BA2C->evtq, (N_ALEvent *)&sp94, delta, 2);
                        if (state->flags & 0x20) {
                            func_10016F00(state);
                        }
                    } else {
                        sp94.type = 0x40;
                        sp94.state = state;
                        delta = sound->envelope->attackTime / state->pitch / state->basepitch;
                        n_alEvtqPostEvent(&D_8002BA2C->evtq, (N_ALEvent *)&sp94, delta, 2);
                    }
                }
                break;

            case 2:
            case 0x400:
            case 0x1000:
                if (event->type != 0x1000 || (state->flags & 2)) {
                    switch (state->state) {
                    case AL_PLAYING:
                        func_10016F80(&D_8002BA2C->evtq, (s32)state, 0x40);
                        if (1) { // fakematch: dead debug prints
                        } else {
                            func_10002088("snd %d has been freed too early - %d\n\n\n\n\n", state->state, state->state);
                            func_10002088("-2 sound has been freed too early - %d\n\n\n\n\n", state->state);
                        }
                        delta = sound->envelope->releaseTime / state->basepitch / state->pitch;
                        n_alSynSetVol(&state->voice, 0, delta);
                        if (delta) {
                            sp94.type = 0x80;
                            sp94.state = state;
                            n_alEvtqPostEvent(&D_8002BA2C->evtq, (N_ALEvent *)&sp94, delta, 2);
                            state->state = AL_STOPPING;
                        } else {
                            func_10016E90(state);
                        }
                        break;
                    case 4:
                    case 5:
                        func_10016E90(state);
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
                state->pan = event->unk08;
                if (state->state == AL_PLAYING) {
                    tmppan = state->pan + sound->samplePan - AL_PAN_CENTER;
                    pan = SND_MIN155(SND_MAX155(tmppan, 0), 127);
                    func_1001E2A0(&state->voice, pan);
                }
                break;

            case 0x10:
                state->pitch = *(f32 *)&event->unk08;
                if (state->state == AL_PLAYING) {
                    n_alSynSetPitch(&state->voice, state->pitch * state->basepitch);
                    if (state->flags & 0x20) {
                        func_10016F00(state);
                    }
                }
                break;

            case 0x100:
                keymap = sound->keyMap;
                state->fxmix = event->unk08;
                if (state->state == AL_PLAYING) {
                    fxmix = (state->fxmix & 0x7f) + (keymap->keyMax & 0xf) * 8;
                    fxmix = SND_MIN155(127, SND_MAX155(0, fxmix));
                    fxmix |= state->fxmix & 0x80;
                    n_alSynSetFXMix(&state->voice, fxmix);
                }
                break;

            case 0x2000:
                state->fxbus = event->unk08;
                if (state->fxbus >= D_8002BA44->maxAuxBusses) {
                    state->fxbus = 0;
                }
                if (state->state == AL_PLAYING) {
                    state->voice.fxBus = state->fxbus;
                }
                break;

            case 8:
                keymap = sound->keyMap;
                state->vol = event->unk08;
                if (state->state == AL_PLAYING) {
                    vol = SND_MAX155(0, SND_VOL155(state, sound, keymap) - 1);
                    n_alSynSetVol(&state->voice, vol, SND_MAX155(1000, state->endtime - D_8002BA2C->curTime));
                }
                break;

            case 0x800:
                keymap = sound->keyMap;
                if (state->state == AL_PLAYING) {
                    delta = sound->envelope->releaseTime / state->basepitch / state->pitch;
                    vol = SND_MAX155(0, SND_VOL155(state, sound, keymap) - 1);
                    n_alSynSetVol(&state->voice, vol, delta);
                }
                break;

            case 0x40:
                if ((state->flags & 2) == 0) {
                    keymap = sound->keyMap;
                    state->envvol = sound->envelope->decayVolume;
                    vol = SND_MAX155(0, SND_VOL155(state, sound, keymap) - 1);
                    delta = sound->envelope->decayTime / state->basepitch / state->pitch;
                    state->endtime = D_8002BA2C->curTime + delta;
                    n_alSynSetVol(&state->voice, vol, delta);
                    sp94.type = 2;
                    sp94.state = state;
                    n_alEvtqPostEvent(&D_8002BA2C->evtq, (N_ALEvent *)&sp94, delta, 2);
                    if (state->flags & 0x20) {
                        func_10016F00(state);
                    }
                }
                break;

            case 0x80:
                func_10016E90(state);
                break;

            case 0x200:
                if (state->flags & 0x10) {
                    func_10017438(event->unk0C, event->unk08, state->vol, state->pan,
                            state->pitch, state->fxmix, state->fxbus, (s32 *)state->unk38);
                }
                break;

            case 0x8000:
                state->unk52 = event->unk08;
                if (state->state == AL_PLAYING) {
                    func_1001E350(&state->voice, state->unk52);
                }
                break;

            default:
                break;
            }
        }

        isspecial = event->type & (1 | 0x10 | 0x40 | 0x80 | 0x200 | 0x4000);
        if ((state = nextstate) && !isspecial) {
            done = state->flags & 1;
        }
    } while (!done && state && !isspecial);
}

void func_10016E90(N_ALUnknownStruct1 *arg0) {
    if ((arg0->unk53 & 4) != 0) {
        n_alSynStopVoice(&arg0->unk10);
        n_alSynFreeVoice(&arg0->unk10);
    }
    func_10017298(arg0);
    func_10016F80(&D_8002BA2C->evtq, (s32) arg0, 0xFFFF);
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

void func_10016F80(ALEventQueue *evtq, s32 arg1, u16 arg2) {
    ALLink *thisNode;
    ALLink *nextNode;
    N_ALEventListItem *thisItem;
    N_ALEventListItem *nextItem;
    N_ALEvent *evt;
    s32 mask;

    mask = osSetIntMask(1);

    thisNode = evtq->allocList.next;
    while (thisNode != 0) {
        nextNode = thisNode->next;
        thisItem = (N_ALEventListItem *)thisNode;
        nextItem = (N_ALEventListItem *)nextNode;
        evt = &thisItem->evt;
        if ((*(s32 *)((u8 *)evt + 4) == arg1) && (*(u16 *)evt & arg2)) {
            if (nextItem) {
                nextItem->delta += thisItem->delta;
            }
            {
                ALLink *ln = thisNode;
                if (ln->next != NULL) {
                    ln->next->prev = ln->prev;
                }
                if (ln->prev != NULL) {
                    ln->prev->next = ln->next;
                }
            }
            {
                ALLink *ln = thisNode;
                ALLink *to = &evtq->freeList;
                ln->next = to->next;
                ln->prev = to;
                if (to->next != NULL) {
                    to->next->prev = ln;
                }
                to->next = ln;
            }
        }
        thisNode = nextNode;
    }

    osSetIntMask(mask);
}
// void func_10016F80(void *arg0, s32 arg1, u16 arg2) {
//     void *sp3C;
//     void *sp38;
//     void *sp34;
//     void *sp30;
//     void *sp2C;
//     s32 sp28;
//     void *sp24;
//     void *sp20;
//     void *sp1C;
//
//     sp28 = osSetIntMask(1);
//     sp3C = arg0->unk8;
//     if (sp3C != 0) {
// loop_1:
//         sp38 = *sp3C;
//         sp34 = sp3C;
//         sp30 = sp38;
//         sp2C = sp34 + 0xC;
//         if ((sp2C->unk4 == arg1) && ((sp2C->unk0 & arg2) != 0)) {
//             if (sp30 != 0) {
//                 sp30->unk8 = (s32) (sp30->unk8 + sp34->unk8);
//             }
//             sp24 = sp3C;
//             if (sp24->unk0 != 0) {
//                 sp24->unk0->unk4 = (s32) sp24->unk4;
//             }
//             if (sp24->unk4 != 0) {
//                 *sp24->unk4 = (s32) sp24->unk0;
//             }
//             sp20 = sp3C;
//             sp1C = arg0;
//             sp20->unk0 = (s32) *sp1C;
//             sp20->unk4 = sp1C;
//             if (*sp1C != 0) {
//                 (*sp1C)->unk4 = sp20;
//             }
//             *sp1C = sp20;
//         }
//         sp3C = sp38;
//         if (sp3C != 0) {
//             goto loop_1;
//         }
//     }
//     osSetIntMask(sp28);
// }

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

N_ALUnknownStruct1 *func_10017438(s32 arg0, s16 arg1, u16 arg2, u8 arg3, f32 arg4, u8 arg5, u8 arg6, s32 *arg7) {
    N_ALUnknownStruct1 *sp34;
    N_ALUnknownStruct1 *sp30;
    s16 sp2E;
    s32 sp28;
    struct {
        s16 type;
        N_ALUnknownStruct1 *voice;
        u8 pad[8];
    } ev;

    sp30 = NULL;
    sp2E = 0;
    if (arg1 != 0) {
        do {
            sp34 = func_10017100(arg0, arg1 - 1);
            if (sp34 != NULL) {
                D_8002BA2C->target = (s32) sp34;
                ev.type = 0x4000;
                ev.voice = sp34;
                sp34->pad4F[0] = arg3;
                (*(u16 *)((u8 *)sp34 + 0x44)) = arg2;
                (*(f32 *)((u8 *)sp34 + 0x34)) = arg4;
                sp34->pad4F[1] = arg5;
                sp34->pad4F[2] = arg6;
                sp28 = 0;
                n_alEvtqPostEvent(&D_8002BA2C->evtq, (N_ALEvent *) &ev, sp28 + 1, 2);
                sp30 = sp34;
            }
            arg1 = 0;
        } while ((arg1 != 0) && (sp34 != NULL));
        if (sp30 != NULL) {
            sp30->unk53 |= 1;
            sp30->unk38 = arg7;
            if (sp2E != 0) {
            }
        }
    }
    if (arg7 != NULL) {
        *arg7 = (s32) sp30;
    }
    return sp30;
}
// void *func_10017438(s32 arg0, s16 arg1, u16 arg2, u8 arg3, f32 arg4, u8 arg5, u8 arg6, void *arg7) {
//     void *sp34;
//     void *sp30;
//     s16 sp2E;
//     s32 sp28;
//     void *sp1C;
//     s16 sp18;
//
//     sp30 = NULL;
//     sp2E = 0;
//     if (arg1 != 0) {
// loop_1:
//         sp34 = func_10017100(arg0, arg1 - 1);
//         if (sp34 != 0) {
//             (*(void *)0x8002BA2C)->unk3C = sp34;
//             sp18 = 0x4000;
//             sp1C = sp34;
//             sp34->unk4F = arg3;
//             sp34->unk44 = arg2;
//             sp34->unk34 = arg4;
//             sp34->unk50 = arg5;
//             sp34->unk51 = arg6;
//             sp28 = 0;
//             n_alEvtqPostEvent(D_8002BA2C + 20, &sp18, sp28 + 1, 2);
//             sp30 = sp34;
//         }
//         arg1 = (u16)0;
//         if (arg1 != 0) {
//             if (sp34 != 0) {
//                 goto loop_1;
//             }
//         }
//         if ((sp30 == 0) || (sp30->unk53 = (u8) (sp30->unk53 | 1), sp30->unk38 = arg7, (sp2E != 0))) {
//
//         }
//     }
//     if (arg7 != 0) {
//         *arg7 = sp30;
//     }
//     return sp30;
// }

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
    u32 mask;
    struct {
        s16 type;
        N_ALUnknownStruct1 *cur;
        u8 pad[8];
    } ev;
    N_ALUnknownStruct1 *p;

    mask = osSetIntMask(1);
    p = D_8002BA20;
    if (p != NULL) {
        do {
            ev.type = 0x400;
            ev.cur = p;
            if ((p->unk53 & arg0) == arg0) {
                ev.cur->unk53 &= ~0x10;
                n_alEvtqPostEvent(&D_8002BA2C->evtq, (N_ALEvent *) &ev, 0, 2);
            }
            p = p->node.next;
        } while (p != NULL);
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

extern u16 *D_80042C58;
void func_10017780(u8 arg0, u16 arg1) {
    s32 mask;
    N_ALUnknownStruct1 *p;
    s32 count;
    struct {
        s16 type;
        N_ALUnknownStruct1 *cur;
        u8 pad[8];
    } ev;

    mask = osSetIntMask(1);
    p = D_8002BA20;
    D_80042C58[arg0] = arg1;
    if ((count = 0, p != NULL)) { // fakematch: count init ordered after the p load
        do {
            if ((p->unkC != 0) && ((*(u8 *)(*(s32 *)(p->unkC + 4) + 2) & 0x1F) == arg0)) {
                ev.type = 0x800;
                ev.cur = p;
                n_alEvtqPostEvent(&D_8002BA2C->evtq, (N_ALEvent *) &ev, 0, 2);
            }
        } while ((count++, p = p->node.next) != NULL); // fakematch: count++ in the condition
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
