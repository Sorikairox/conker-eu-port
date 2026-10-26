#include <n_libaudio.h>
#include "n_sndp.h"


/* was func_10019B50 */
void n_csp_cc_volume(N_ALCSPlayer *seqp, s32 arg1, s32 chan, s32 vol) {
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

/* was func_10019C28 */
void n_csp_cc_pan(N_ALCSPlayer *seqp, s32 arg1, s32 chan, s32 pan) {
    N_ALSoundState *state;
    u8 tmp;
    seqp->chanState[chan].pan = pan;
    for (state = seqp->vAllocHead; state != NULL; state = state->voice.node.next) {
        if ((state->chan == chan)) {
            tmp = __n_vsPan(state, seqp);
            n_syn_set_voice_pan(&state->voice.node.prev, tmp);
        }
    }
}

/* was func_10019CD0 */
void n_csp_cc_priority(N_ALCSPlayer *seqp, s32 arg1, s32 chan, s32 priority) {
    seqp->chanState[chan].priority = priority;
}

/* was func_10019CFC */
void n_csp_cc_send_marker(N_ALCSPlayer *seqp, s32 arg1, s32 arg2, s32 arg3) {
    if (seqp->unk84 != 0) {
        osSendMesg(seqp->unk84, (arg3 & 7) | 0x10 | ((seqp->node.samplesLeft << 5) & -0x100), 0);
    }
}

/* was func_10019D6C */
void n_csp_cc_bank_select(N_ALCSPlayer *seqp, s32 arg1, s32 chan, s32 arg3) {
    seqp->chanState[chan].unk8 = arg3;
}

s32 n_syn_set_voice_cutoff(u8 *, f32);
f32 audio_semitones_to_ratio(s32);
/* was func_10019D98 */
void n_csp_update_chan_filter(u8 *arg0, u8 arg1) {
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
                    n_syn_set_voice_cutoff(sp2C + 4, audio_semitones_to_ratio(((*(u8 *)((u8 *)sp2C + 0x36)) - (*(u8 *)((u8 *)((*(u8 **)((u8 *)((*(u8 **)((u8 *)sp2C + 0x24))) + 4))) + 4))) + sp29) * 440.0f * sp24);
                }
            }
        } while ((sp2C = (*(u8 **)((u8 *)sp2C + 0))) != NULL);
    }
}

/* was func_10019ED8 */
void n_csp_cc_filter_amount(N_ALCSPlayer *seqp, s32 arg1, s32 chan, s32 arg3) {
    seqp->chanState[chan].unk14 = arg3;
    n_csp_update_chan_filter(seqp, chan);
}

/* was func_10019F38 */
void n_csp_cc_filter_key(N_ALCSPlayer *seqp, s32 arg1, s32 chan, s32 arg3) {
    seqp->chanState[chan].unk15 = arg3;
    n_csp_update_chan_filter(seqp, chan);
}

/* was func_10019F98 */
void n_csp_cc_voice_param17(N_ALCSPlayer *seqp, s32 arg1, s32 chan, s32 arg3) {
    N_ALSoundState *state;
    seqp->chanState[chan].unk16 = arg3;
    for (state = seqp->vAllocHead; state != NULL; state = state->voice.node.next) {
        if (state->chan == chan) {
            n_syn_set_voice_param17(&state->voice.node.prev, arg3);
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

/* was func_1001A030 */
void n_csp_cc_sustain(N_ALCSPlayer *seqp, s32 arg1, s32 chan, u32 byte2) {
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

/* was func_1001A224 */
void n_csp_cc_fx_enable(N_ALCSPlayer *seqp, s32 arg1, s32 chan, s32 arg3) {
    N_ALSoundState *state;

    seqp->chanState[chan].fxmix = (seqp->chanState[chan].fxmix & 0x7F) | (arg3 << 7);
    for (state = seqp->vAllocHead; state != NULL; state = state->voice.node.next) {
        if ((state->chan == chan) && (state->unk38 != 3)) {
            n_alSynSetFXMix(&state->voice.node.prev, seqp->chanState[chan].fxmix);
        }
    }
}

/* was func_1001A2F8 */
void n_csp_cc_fx_mix(N_ALCSPlayer *seqp, s32 arg1, s32 chan, s32 arg3) {
    arg3 = arg3 & 0x7F;
    seqp->chanState[chan].fxmix = (seqp->chanState[chan].fxmix & 0x80) | arg3;
    n_csp_cc_fx_enable(seqp, arg1, chan, seqp->chanState[chan].fxmix >> 7);
}

/* was func_1001A39C */
void n_csp_cc_fx_bus(N_ALCSPlayer *seqp, s32 arg1, s32 chan, u32 arg3) {
    if (arg3 < n_syn->maxAuxBusses) {
        seqp->chanState[chan].unkB = arg3;
    }
}

// FIXME:
typedef struct {
    u8 pad0[0x36];
    u8 unk36;
} struct24;

/* was func_1001A3E0 */
void n_csp_cc_voice_clip_bank(struct24 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    arg0->unk36 = arg3;
}

/* was func_1001A3FC */
void n_csp_cc_play_voice_clip(struct24 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    mp3_voice_play(arg0->unk36 * 100 + arg3, 0x7FFF, 0x40);
}

/* was func_1001A45C */
void n_csp_update_chan_volume(N_ALCSPlayer *seqp, u8 chan) {
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
// and starts it through n_csp_cc_fade_step with byte1 = 0xFE
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
void n_csp_cc_fade_step(N_ALCSPlayer *seqp, s32 arg1, s32 chan, s32 arg3);

/* was func_1001A508 */
void n_csp_cc_fade_target(N_ALCSPlayer *seqp, s32 arg1, s32 chan, s32 arg3) {
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
    n_csp_cc_fade_step(seqp, arg1, chan, arg3);
}

/* was func_1001A704 */
void n_csp_cc_fade_step(N_ALCSPlayer *seqp, s32 arg1, s32 chan, s32 arg3) {
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
    n_csp_update_chan_volume(seqp, chan);
}

/* was func_1001A9DC */
void n_csp_cc_fade_rate(N_ALCSPlayer *seqp, s32 arg1, s32 chan, s32 arg3) {
    seqp->chanState[chan].unkF = arg3;
}

/* was func_1001AA08 */
void n_csp_cc_fade_level(N_ALCSPlayer *seqp, s32 arg1, s32 chan, s32 arg3) {
    seqp->chanState[chan].unkD = arg3;
    seqp->chanState[chan].unkE = arg3;
    if (arg3 == 0) {
        seqp->chanMask &= (1 << chan) ^ 0xFFFF; // disable
    } else {
        seqp->chanMask |= 1 << chan;
    }
    n_csp_update_chan_volume(seqp, chan);
}
