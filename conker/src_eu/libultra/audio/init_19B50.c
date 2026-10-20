#include <n_libaudio.h>
#include "n_sndp.h"


void func_10019B50(N_ALCSPlayer *seqp, s32 arg1, s32 chan, s32 vol) {
    N_ALSoundState *state;
    s16 tmp;
    seqp->chanState[chan].vol = vol;
    for(state = seqp->vAllocHead; state != NULL; state = state->voice.node.next) {
        if ((state->chan == chan) && (state->unk38 != 3)) {
            tmp = __n_vsVol(state, seqp);
            n_alSynSetVol(&state->voice.node.prev, tmp, __n_vsDelta(state, seqp->curTime));
        }
    }
}

void func_10019C28(N_ALCSPlayer *seqp, s32 arg1, s32 chan, s32 pan) {
    N_ALSoundState *state;
    u8 tmp;
    seqp->chanState[chan].pan = pan;
    for (state = seqp->vAllocHead; state != NULL; state = state->voice.node.next) {
        if ((state->chan == chan)) {
            tmp = __n_vsPan(state, seqp);
            func_1001E2A0(&state->voice.node.prev, tmp);
        }
    }
}

void func_10019CD0(N_ALCSPlayer *seqp, s32 arg1, s32 chan, s32 priority) {
    seqp->chanState[chan].priority = priority;
}

void func_10019CFC(N_ALCSPlayer *seqp, s32 arg1, s32 arg2, s32 arg3) {
    if (seqp->unk84 != 0) {
        osSendMesg(seqp->unk84, (arg3 & 7) | 0x10 | ((seqp->node.samplesLeft << 5) & -0x100), 0);
    }
}

void func_10019D6C(N_ALCSPlayer *seqp, s32 arg1, s32 chan, s32 arg3) {
    seqp->chanState[chan].unk8 = arg3;
}

s32 func_1001CA90(u8 *, f32);
f32 func_1001CEA4(s32);
void func_10019D98(u8 *arg0, u8 arg1) {
    u8 *sp2C;
    s16 sp2A;
    s8 sp29;
    f32 sp24;
    sp29 = (*(s8 *)((u8 *)(((*(s32 *)((u8 *)arg0 + 0x60)) + (arg1 * 0x3C))) + 0x15)) - 0x40;
    sp24 = (*(f32 *)((u8 *)(((*(s32 *)((u8 *)arg0 + 0x60)) + (arg1 * 0x3C))) + 0x18));
    if ((sp2C = (*(u8 **)((u8 *)arg0 + 0x64))) != NULL) {
        do {
            if ((*(u8 *)((u8 *)sp2C + 0x35)) == arg1) {
                sp2A = (s16) (*(u8 *)((u8 *)(((*(s32 *)((u8 *)arg0 + 0x60)) + (arg1 * 0x3C))) + 0x14));
                n_alSynSetPan(sp2C + 4, (u8) sp2A);
                if (sp2A != 0) {
                    func_1001CA90(sp2C + 4, func_1001CEA4(((*(u8 *)((u8 *)sp2C + 0x36)) - (*(u8 *)((u8 *)((*(u8 **)((u8 *)((*(u8 **)((u8 *)sp2C + 0x24))) + 4))) + 4))) + sp29) * 440.0f * sp24);
                }
            }
        } while ((sp2C = (*(u8 **)((u8 *)sp2C + 0))) != NULL);
    }
}

void func_10019ED8(N_ALCSPlayer *seqp, s32 arg1, s32 chan, s32 arg3) {
    seqp->chanState[chan].unk14 = arg3;
    func_10019D98(seqp, chan);
}

void func_10019F38(N_ALCSPlayer *seqp, s32 arg1, s32 chan, s32 arg3) {
    seqp->chanState[chan].unk15 = arg3;
    func_10019D98(seqp, chan);
}

void func_10019F98(N_ALCSPlayer *seqp, s32 arg1, s32 chan, s32 arg3) {
    N_ALSoundState *state;
    seqp->chanState[chan].unk16 = arg3;
    for (state = seqp->vAllocHead; state != NULL; state = state->voice.node.next) {
        if (state->chan == chan) {
            func_1001E350(&state->voice.node.prev, arg3);
        }
    }
}

// s129: DK64 n_csplayer.c AL_MIDI_SUSTAIN_CTRL case as a controller handler (chanState 0x28 flag
// selects the channel's release time over the envelope's)
typedef struct {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ ALMicroTime releaseTime;
    /* 0x28 */ u8 unk28;
    /* 0x29 */ u8 pad29[0x13];
} ChanState19B50;

void func_1001A030(N_ALCSPlayer *seqp, s32 arg1, s32 chan, u32 byte2) {
    N_ALVoiceState *vs;

    seqp->chanState[chan].sustain = byte2;
    for (vs = seqp->vAllocHead; vs != NULL; vs = vs->next) {
        if ((vs->channel == chan) && (vs->phase != AL_PHASE_RELEASE)) {
            if (byte2 > AL_SUSTAIN) {
                if (vs->phase == AL_PHASE_NOTEON) {
                    vs->phase = AL_PHASE_SUSTAIN;
                }
            } else {
                if (vs->phase == AL_PHASE_SUSTAIN) {
                    vs->phase = AL_PHASE_NOTEON;
                } else if (vs->phase == AL_PHASE_SUSTREL) {
                    vs->phase = AL_PHASE_RELEASE;
                    if (((ChanState19B50 *)seqp->chanState)[chan].unk28) {
                        __n_seqpReleaseVoice((N_ALSeqPlayer *)seqp, &vs->voice,
                                             ((ChanState19B50 *)seqp->chanState)[chan].releaseTime < AL_USEC_PER_FRAME ? AL_USEC_PER_FRAME : ((ChanState19B50 *)seqp->chanState)[chan].releaseTime);
                    } else {
                        __n_seqpReleaseVoice((N_ALSeqPlayer *)seqp, &vs->voice,
                                             vs->sound->envelope->releaseTime < AL_USEC_PER_FRAME ? AL_USEC_PER_FRAME : vs->sound->envelope->releaseTime);
                    }
                }
            }
        }
    }
}

void func_1001A224(N_ALCSPlayer *seqp, s32 arg1, s32 chan, s32 arg3) {
    N_ALSoundState *state;

    seqp->chanState[chan].fxmix = (seqp->chanState[chan].fxmix & 0x7F) | (arg3 << 7);
    for (state = seqp->vAllocHead; state != NULL; state = state->voice.node.next) {
        if ((state->chan == chan) && (state->unk38 != 3)) {
            n_alSynSetFXMix(&state->voice.node.prev, seqp->chanState[chan].fxmix);
        }
    }
}

void func_1001A2F8(N_ALCSPlayer *seqp, s32 arg1, s32 chan, s32 arg3) {
    arg3 = arg3 & 0x7F;
    seqp->chanState[chan].fxmix = (seqp->chanState[chan].fxmix & 0x80) | arg3;
    func_1001A224(seqp, arg1, chan, seqp->chanState[chan].fxmix >> 7);
}

void func_1001A39C(N_ALCSPlayer *seqp, s32 arg1, s32 chan, u32 arg3) {
    if (arg3 < n_syn->maxAuxBusses) {
        seqp->chanState[chan].unkB = arg3;
    }
}

// FIXME:
typedef struct {
    u8 pad0[0x36];
    u8 unk36;
} struct24;

void func_1001A3E0(struct24 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    arg0->unk36 = arg3;
}

void func_1001A3FC(struct24 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_1001263C(arg0->unk36 * 100 + arg3, 0x7FFF, 0x40);
}

void func_1001A45C(N_ALCSPlayer *seqp, u8 chan) {
    N_ALSoundState *state;
    s16 tmp;
    for (state = seqp->vAllocHead; state != NULL; state = state->voice.node.next) {
        if ((state->chan == chan) && (state->unk38 != 3)) {
            tmp = __n_vsVol(state, seqp);
            n_alSynSetVol(&state->voice.node.prev, tmp, __n_vsDelta(state, seqp->curTime));
        }
    }
}
// s129: Conker controller handler (DK64 has no counterpart): sets up the chanState 0x0D..0x10 ramp
// and starts it through func_1001A704 with byte1 = 0xFE
typedef struct {
    /* 0x00 */ u8 pad0[0xD];
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 unkE;
    /* 0x0F */ u8 unkF;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ u8 pad14[0x28];
} ChanRamp19B50;

#define RAMP(c) (((ChanRamp19B50 *)seqp->chanState)[c])

float fabsf(float);
#pragma intrinsic (fabsf)
void func_1001A704(N_ALCSPlayer *seqp, s32 arg1, s32 chan, s32 arg3);

void func_1001A508(N_ALCSPlayer *seqp, s32 arg1, s32 chan, s32 arg3) {
    f32 diff;

    if (RAMP(chan).unkF == 0) {
        RAMP(chan).unkF = 0x88;
    }
    if (RAMP(chan).unkE != arg3) {
        diff = arg3 - RAMP(chan).unkD;
        RAMP(chan).unk10 = diff / (RAMP(chan).unkF & 0x7F);
        RAMP(chan).unk10 = fabsf(RAMP(chan).unk10);
        if (RAMP(chan).unkE == RAMP(chan).unkD) {
            RAMP(chan).unkE = arg3;
        } else {
            RAMP(chan).unkE = arg3;
            return;
        }
    } else {
        return;
    }
    ((N_ALEvent *)arg1)->msg.midi.byte1 = 0xFE;
    func_1001A704(seqp, arg1, chan, arg3);
}

void func_1001A704(N_ALCSPlayer *seqp, s32 arg1, s32 chan, s32 arg3) {
    u8 sp2F;
    u8 sp2E;
    s32 sp28;
    s32 sp24;
    f32 sp20;
    f32 sp1C;

    sp2F = seqp->chanState[chan].unkD;
    sp2E = seqp->chanState[chan].unkE;
    sp20 = seqp->chanState[chan].unk10;
    sp28 = sp2E - sp2F;
    if (sp28 > 0) {
        if (seqp->chanState[chan].unkF & 0x80) {
            sp20 = sp20 * 2.0f;
        }
        sp24 = sp20;
        if (sp24 == 0) {
            sp24 = 1;
            sp1C = 1.0f / sp20;
        } else {
            sp1C = sp24 / sp20;
        }
        if (sp28 > sp24) {
            sp28 = sp24;
        }
    } else {
        sp24 = sp20;
        if (sp24 == 0) {
            sp24 = 1;
            sp1C = sp20;
        } else {
            sp1C = sp24 / sp20;
        }
        sp24 = -sp24;
        if (sp28 < sp24) {
            sp28 = sp24;
        }
    }
    sp2F = sp28 + sp2F;
    seqp->chanState[chan].unkD = sp2F;
    if (sp2F != sp2E) {
        n_alEvtqPostEvent(&seqp->evtq, arg1, seqp->uspt * 100 * sp1C, 2);
    }
    if (sp2F != 0) {
        seqp->chanMask |= (1 << chan);
    } else {
        seqp->chanMask &= ~(1 << chan);
    }
    func_1001A45C(seqp, chan);
}

void func_1001A9DC(N_ALCSPlayer *seqp, s32 arg1, s32 chan, s32 arg3) {
    seqp->chanState[chan].unkF = arg3;
}

void func_1001AA08(N_ALCSPlayer *seqp, s32 arg1, s32 chan, s32 arg3) {
    seqp->chanState[chan].unkD = arg3;
    seqp->chanState[chan].unkE = arg3;
    if (arg3 == 0) {
        seqp->chanMask &= (1 << chan) ^ 0xFFFF; // disable
    } else {
        seqp->chanMask |= 1 << chan;
    }
    func_1001A45C(seqp, chan);
}
