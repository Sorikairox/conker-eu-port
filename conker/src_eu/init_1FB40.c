#include <n_libaudio.h>


// s127: main bus pull (n_alMainBusPull-like): Conker's per-bus loop starting at the last active aux bus,
// per-bus mix gains from g_audio_bus_one_side/g_audio_bus_invert and the bus fx pole filter (load ADPCM + two pole filters)
#include "n_abi.h"

typedef struct {
    /* 0x00 */ s16 pad0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ u8 pad4[4];
    /* 0x08 */ s16 unk8[0x10];
    /* 0x28 */ s32 unk28;
    /* 0x2C */ void *unk2C;
    /* 0x30 */ void *unk30;
} FB40Fx;

typedef struct {
    /* 0x00 */ u8 pad0[0x40];
    /* 0x40 */ FB40Fx *fx;
} FB40AuxBus;

typedef struct {
    /* 0x00 */ void *pad0;
    /* 0x04 */ Acmd *(*handler)(s32 sampleOffset, Acmd *p, s32 bus);
} FB40MainBus;

extern N_ALSynth *g_audio_synth; /* was D_8002BA44 */
extern s32 g_mp3_stream_state; /* was D_800E0E04 */
extern u8 g_audio_bus_one_side[]; /* was D_800428C4 */
extern u8 g_audio_bus_invert[]; /* was D_800428C6 */
s32 mp3_stream_synth_pull(s32 arg0, Acmd **arg1);
void n_fx_lowpass_update_coefs(FB40Fx *fx, f32 rate);

/* was func_1001FB40 */
Acmd *n_main_bus_pull(s32 sampleOffset, Acmd *cmdList) {
    Acmd *ptr = cmdList;
    s32 i;
    s32 j;

    if (g_mp3_stream_state == 0 || mp3_stream_synth_pull(0xB8, &ptr) == 0) {
        aClearBuffer(ptr++, 0x4E0, 0x2E0);
        aClearBuffer(ptr++, 0x7C0, 0x2E0);
    }

    j = 0;
    for (i = 1; i < g_audio_synth->maxAuxBusses; i++) {
        if (((FB40AuxBus *)g_audio_synth->auxBus)[i].fx->unk2 > 0) {
            j = i;
        }
    }

    for (i = 0; i < g_audio_synth->maxAuxBusses; i++, j++) {
        if (j >= g_audio_synth->maxAuxBusses) {
            j = 0;
        }
        if (i != 0) {
            aClearBuffer(ptr++, 0x7C0, 0x2E0);
        }
        ptr = ((FB40MainBus *)g_audio_synth->mainBus)->handler(sampleOffset, ptr, j);
        if (g_audio_bus_one_side[j]) {
            if (g_audio_bus_invert[j]) {
                aMix(ptr++, 0, 0x8000, 0x7C0, 0x4E0);
            } else {
                aMix(ptr++, 0, 0x7FFF, 0x7C0, 0x650);
            }
        } else {
            if (g_audio_bus_invert[j]) {
                aMix(ptr++, 0, 0x8000, 0x7C0, 0x650);
            } else {
                aMix(ptr++, 0, 0x7FFF, 0x7C0, 0x650);
            }
            aMix(ptr++, 0, 0x7FFF, 0x7C0, 0x4E0);
        }
        if (((FB40AuxBus *)g_audio_synth->auxBus)[j].fx->unk2 > 0) {
            FB40Fx *fx = ((FB40AuxBus *)g_audio_synth->auxBus)[j].fx;

            if (fx->unk28) {
                n_fx_lowpass_update_coefs(fx, g_audio_synth->outputRate);
            }
            n_aLoadADPCM(ptr++, 0x20, osVirtualToPhysical(fx->unk8));
            n_aPoleFilter(ptr++, 0, 0x4E0, 0, osVirtualToPhysical(fx->unk2C) & 0xFFFFFF);
            n_aPoleFilter(ptr++, 0, 0x650, 0, osVirtualToPhysical(fx->unk30) & 0xFFFFFF);
            fx->unk28 = 0;
        }
    }
    return ptr;
}
