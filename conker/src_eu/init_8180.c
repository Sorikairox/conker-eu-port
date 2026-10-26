#include <n_libaudio.h>

#include "macros.h"

typedef struct {
  u8 unk0[8][0xEC];
} struct247; // something naudio related? size 0x760

void n_cseq_set_loc(void *arg0, void *arg1);

extern N_ALCSPlayer *g_music_players[]; /* was D_8003C900 */
extern ALCSeq        g_music_seqs[]; /* was D_8003CA58 */
extern struct247     g_music_seq_markers[]; /* was D_8003CD48 */

// FIXME: create header file for audio related functions
s32  func_10017A80(N_ALCSPlayer *csp);
void n_csp_set_msg_queue(N_ALCSPlayer *csp, s32 arg1);
void n_csp_set_chan_notify(N_ALCSPlayer *arg0, s32 arg1, u8 arg2);
void n_csp_reset_chan_levels(N_ALCSPlayer *csp);
void n_csp_mute_chan(N_ALCSPlayer *csp, s32 arg1);
void n_csp_unmute_chan(N_ALCSPlayer *csp, s32 arg1);
void n_csp_fade_chan(N_ALCSPlayer *arg0, s32 arg1, u8 arg2, u8 arg3);
void n_csp_set_chan_fx_enable(N_ALCSPlayer *arg0, s32 arg1, u8 arg2);
void n_csp_set_chan_level(N_ALCSPlayer *arg0, s32 arg1, u8 arg2);
void n_csp_set_chan_pan(N_ALCSPlayer *arg0, u8 arg1, u8 arg2);
void n_csp_set_fx_mix_offset_scale(N_ALCSPlayer *csp, f32 arg1, f32 arg2);
void n_csp_set_chan_fx_bus(N_ALCSPlayer *csp, u8 chan, u8 arg2);
void n_csp_set_fx_param(N_ALCSPlayer *arg0, u8 arg1, u8 arg2, u8 arg3, s32 arg4);
void n_cseq_find_markers(N_ALCSPlayer *arg0, s32 arg1, u32 arg2, u32 arg3);
void n_csp_set_vol(N_ALCSPlayer *arg0, s16 arg1);
void n_csp_stop(N_ALCSPlayer *seqp);

typedef struct {
    s32 unk0;
    s32 unk4;
} SeqRom8180;

extern u16 g_music_seq_ids[]; /* was D_8003CDDC */
extern u8 *g_music_seq_data[]; /* was D_8003CDE8 */
extern SeqRom8180 *g_music_seq_file; /* was D_8003D0E0 */
extern u16 g_music_seq_sizes[]; /* was D_8003CCB0 */
void *allocate_memory(s32 size, s32 arg1, s32 arg2, s32 arg3);
void heap_free(s32 arg0);
s32 rom_dma_read(s32 devAddr, void *dramAddr, u32 size, s32 arg3);
void n_csp_set_seq(N_ALCSPlayer *csp, ALCSeq *seq);

// this one is a monster
// Audio init: audio heap, synth + audio manager (audio_mgr_init), the instrument bank, the sequence
// table (sizes rounded up to even into g_music_seq_sizes), three sequence players and the sound player.
typedef struct {
    s32 maxVVoices;
    s32 maxPVoices;
    s32 maxUpdates;
    s32 maxFXbusses;
    void *dmaproc;
    void *unk14;
    void *unk18;
    void *unk1C;
    void *unk20;
    s32 unk24;
    ALHeap *heap;
    s32 outputRate;
    u8 fxTypes[4];
    s32 *params[2];
} AmSynConfig;
typedef struct {
    s32 frequency;
    u32 unk4;
    u32 unk8;
} AmConfig;
typedef struct {
    /* 0x00 */ u32 maxStates;
    /* 0x04 */ s32 maxEvents;
    /* 0x08 */ s32 maxSounds;
    /* 0x0C */ ALHeap *heap;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u16 unk14;
} SndpConfig8180;
extern ALHeap g_audio_heap;          /* the audio heap; was D_8003E710 */
extern u8 g_audio_heap_arena[];            /* its 0x3E000-byte arena; was D_80044B20 */
extern s32 g_sound_bank0;             /* the first bank of the instrument bank file; was D_8003E708 */
u8 *asset_lookup_rom(s32 *arg0, s32 arg1, ...);
s32 asset_load_into(s32 arg0, s32 arg1, s32 arg2, ...);
s32 asset_get_size(s32 arg0, ...);
void audio_mgr_init(AmSynConfig *c, s32 pri, AmConfig *arg2);
void rom_dma_read_chunked(u32 devAddr, u8 *dramAddr, u32 size);
void n_alBnkfNew(ALBankFile *file, u8 *table, s32 arg2);
void audio_osc_pool_create(ALSeqpConfig *arg0, s32 arg1);
void n_csp_set_bank(N_ALCSPlayer *csp, s32 arg1);
s32 n_sndp_init(SndpConfig8180 *c);
void audio_set_output_mode(u8 arg0);
void audio_set_bus_mix_type(s32 arg0, u32 arg1);

/* was func_10008180 */
void audio_system_init(void) {
    AmConfig amc;
    ALSeqpConfig seqc;
    AmSynConfig c;
    SndpConfig8180 sndc;
    ALBankFile *bankFile;
    ALSeqFile *hdr;
    ALSeqFile *seqFile;
    u8 *seqRom;
    u8 *ctlRom;
    u8 *tblRom;
    s32 size;
    s32 len;
    s32 i;

    alHeapInit(&g_audio_heap, g_audio_heap_arena, 0x3E000);
    c.maxVVoices = 0x2C;
    c.maxPVoices = 0x28;
    c.maxUpdates = 0x40;
    c.maxFXbusses = 2;
    c.dmaproc = NULL;
    c.fxTypes[0] = 6;
    c.fxTypes[1] = 6;
    c.outputRate = 0;
    c.heap = &g_audio_heap;
    amc.frequency = 22020;
    amc.unk4 = 1;
    amc.unk8 = 0xBB0;
    c.unk24 = (s32)asset_lookup_rom(NULL, 2, 0x17, 2);
    audio_mgr_init(&c, 12, &amc);

    size = asset_get_size(2, 0x17, 0);
    bankFile = allocate_memory(size, 0xFF, 2, 0);
    asset_load_into((s32)bankFile, size, 2, 0x17, 0);
    ctlRom = asset_lookup_rom(NULL, 2, 0x17, 1);
    tblRom = asset_lookup_rom(NULL, 2, 0x17, 2);
    n_alBnkfNew(bankFile, tblRom, (s32)ctlRom);
    g_sound_bank0 = (s32)bankFile->bankArray[0];

    seqRom = asset_lookup_rom(NULL, 2, 0x17, 3);
    hdr = allocate_memory(0x10, 1, 2, 0);
    rom_dma_read_chunked((u32)seqRom, (u8 *)hdr, 0x10);
    size = hdr->seqCount * 8 + 4;
    heap_free((s32)hdr);
    g_music_seq_file = allocate_memory(size, 0xFF, 2, 0);
    rom_dma_read_chunked((u32)seqRom, (u8 *)g_music_seq_file, (size + 0xF) & ~0xF);
    alSeqFileNew((ALSeqFile *)g_music_seq_file, seqRom);
    seqFile = (ALSeqFile *)g_music_seq_file;
    for (i = 0; i < 150; i++) {
        len = seqFile->seqArray[i].len & 0xFFFF;
        g_music_seq_sizes[i] = len;
        if (len & 1) {
            g_music_seq_sizes[i] = len + 1;
        }
    }

    seqc.maxVoices = 0x2C;
    seqc.maxEvents = 0x68;
    seqc.debugFlags = 0;
    seqc.maxChannels = 0x10;
    seqc.heap = &g_audio_heap;
    audio_osc_pool_create(&seqc, 0x58);
    for (i = 0; i < 3; i++) {
        g_music_seq_ids[i] = 0xFFFF;
        g_music_seq_data[i] = NULL;
        g_music_players[i] = alHeapDBAlloc(NULL, 0, &g_audio_heap, 1, sizeof(N_ALCSPlayer));
        n_alCSPNew(g_music_players[i], &seqc);
        n_csp_set_bank(g_music_players[i], (s32)bankFile->bankArray[0]);
    }

    sndc.maxEvents = 0x40;
    sndc.maxStates = 0x40;
    sndc.maxSounds = 0x14;
    sndc.unk14 = 8;
    sndc.heap = &g_audio_heap;
    sndc.unk10 = (s32)tblRom;
    n_sndp_init(&sndc);
    audio_set_output_mode(4);
    audio_set_bus_mix_type(0, 2);
    audio_set_bus_mix_type(1, 2);
}
/* was func_100084D8 */
void music_player_play(u8 idx) {
    if ((n_alCSPGetState(g_music_players[idx]) == 0) || (n_alCSPGetState(g_music_players[idx]) == 3)) {
        n_csp_play(g_music_players[idx]);
    }
}

/* was func_1000853C */
s32 music_player_get_state(u8 idx) {
    return n_alCSPGetState(g_music_players[idx]);
}

/* was func_10008570 */
void music_player_set_msg_queue(u8 idx, s32 arg1) { // arg1 is OSMesgQueue ?
    n_csp_set_msg_queue(g_music_players[idx], arg1);
}

/* was func_100085A4 */
void music_stub_noop3(s32 arg0, s32 arg1, s32 arg2) {
}

/* was func_100085B8 */
void music_player_set_chan_flag17(u8 idx, s32 arg1, u8 arg2) {
    n_csp_set_chan_notify(g_music_players[idx], arg1, arg2);
}

/* was func_100085F8 */
void music_chan_mute(u8 idx, s32 arg1) {
    n_csp_mute_chan(g_music_players[idx], arg1);
}

/* was func_1000862C */
void music_chan_unmute(u8 idx, s32 arg1) {
    n_csp_unmute_chan(g_music_players[idx], arg1);
}

/* was func_10008660 */
void music_chan_fade_volume(u8 idx, u8 chan, u8 arg2, s32 arg3) {
    if (arg3 > 0) {
        arg3 = (arg3 * 10) / 50;
        if (arg3 == 0) {
            arg3 = 1; // final?
        } else if (arg3 >= 128) {
            arg3 = 127; // more to come?
        }
    } else {
        arg3 = 0; // empty?
    }
    n_csp_fade_chan(g_music_players[idx], chan, arg2, arg3);
}

/* was func_100086FC */
void music_chan_set_cc41(u8 idx, u8 arg1, u8 arg2) {
    n_csp_set_chan_fx_enable(g_music_players[idx], arg1, arg2);
}

/* was func_10008744 */
void music_chan_set_pan(u8 idx, u8 arg1, u8 arg2) {
    n_csp_set_chan_pan(g_music_players[idx], arg1, arg2);
}

/* was func_10008790 */
void music_chans_fade_volume(u8 idx, s32 mask, u8 arg2, s32 arg3) {
    s32 chan;

    for (chan = 0; chan < 16; chan++)
    {
        if ((1 << chan) & mask) {
            music_chan_fade_volume(idx, chan, arg2, arg3);
        }
    }
}

/* was func_10008824 */
void music_chan_set_volume(u8 idx, u8 arg1, u8 arg2) {
    n_csp_set_chan_level(g_music_players[idx], arg1, arg2);
}

/* was func_1000886C */
void music_chans_set_volume(u8 idx, s32 mask, u8 arg2) {
    s32 chan;

    for (chan = 0; chan < 16; chan++)
    {
        if ((1 << chan) & mask) {
            music_chan_set_volume(idx, chan, arg2);
        }
    }
}

/* was func_100088F0 */
void music_chans_set_muted(u8 idx, s32 mask, s32 enable) {
    s32 chan;

    for (chan = 0; chan < 16; chan++)
    {
        if ((1 << chan) & mask) {
            if (enable) {
                music_chan_unmute(idx, chan);
            } else {
                music_chan_mute(idx, chan);
            }
        }
    }
}

/* was func_10008988 */
void music_chans_set_enabled(u8 idx, s32 mask, s32 enable) {
    s32 chan;

    for(chan = 0; chan < 16; chan++) // 16 channels
    {
        if ((1 << chan) & mask) {
            if (enable != 0) {
                g_music_players[idx]->chanMask |= mask; // enable
            } else {
                g_music_players[idx]->chanMask &= (mask ^ 0xFFFF); // disable
            }
        }
    }
}

// is this n_alCSPGetChlVol ?
/* was func_10008A4C */
u8 music_chan_get_volume(u8 idx, u8 chan) {
    return g_music_players[idx]->chanState[chan].unkD; // do we assume this is volume?
}

/* was func_10008A94 */
void music_chans_set_cc92(u8 idx, s32 mask, s32 arg2) {
    s32 chan;

    for(chan = 0; chan < 16; chan++)
    {
        if (((1 << chan) & mask) != 0) {
            n_csp_set_chan_fx_bus(g_music_players[idx], chan, arg2);
        }
    }
}

/* was func_10008B2C */
void music_player_get_tempo(u8 idx) {
      n_alCSPGetTempo(g_music_players[idx]);
}

/* was func_10008B60 */
void music_player_set_voice_param(u8 idx, u8 arg1, u8 arg2, u8 arg3, s32 arg4) {
    n_csp_set_fx_param(g_music_players[idx], arg1, arg2, arg3, arg4);
}

/* was func_10008BC0 */
void music_player_set_master_gain(u8 idx, f32 arg1, f32 arg2) {
    n_csp_set_fx_mix_offset_scale(g_music_players[idx], arg1, arg2);
}

/* was func_10008C04 */
void music_seq_new_marker(u8 idx, u8 arg1, s32 arg2) {
    n_cseq_find_markers(&g_music_seqs[idx], &g_music_seq_markers[idx], arg1, arg2);
}

/* was func_10008C6C */
void music_seq_jump_marker(u8 idx, u8 arg1) {
    n_cseq_set_loc(&g_music_seqs[idx], g_music_seq_markers[idx].unk0[arg1]);
}

// s129: (re)start sequence player idx with sequence arg1: wait for the player to stop, load the
// sequence (cached in g_music_seq_data[idx], id in g_music_seq_ids[idx]) and start it

/* was func_10008CE8 */
s32 music_player_start_seq(u8 idx, s32 arg1) {
    s32 devAddr;
    u32 i;

    i = 0;
    n_csp_end_track(g_music_players[idx]);
    while (n_alCSPGetState(g_music_players[idx]) != 0 && i < 2000000) {
        i++;
    }
    if (i >= 2000000) {
        n_csp_end_track(g_music_players[idx]);
        while (n_alCSPGetState(g_music_players[idx]) != 0 && i < 4000000) {
            i++;
        }
    }
    if (arg1 != g_music_seq_ids[idx]) {
        if (g_music_seq_data[idx] != NULL) {
            heap_free((s32)g_music_seq_data[idx]); // the int conversion gives the ref v0 load + move
            g_music_seq_data[idx] = NULL;
        }
        devAddr = g_music_seq_file[arg1].unk4;
        g_music_seq_data[idx] = allocate_memory(g_music_seq_sizes[arg1], 0xFF, 2, 2);
        if (g_music_seq_data[idx] == NULL) {
            return -1;
        }
        rom_dma_read(devAddr, g_music_seq_data[idx], ALIGN16(g_music_seq_sizes[arg1]), 1);
        g_music_seq_ids[idx] = arg1;
    }
    n_alCSeqNew(&g_music_seqs[idx], g_music_seq_data[idx]);
    n_csp_set_seq(g_music_players[idx], &g_music_seqs[idx]);
    n_csp_reset_chan_levels(g_music_players[idx]);
    return 0;
}

/* was func_10008EE0 */
void music_player_set_volume(u8 idx, s32 arg1) {
    n_csp_set_vol(g_music_players[idx], arg1);
}

/* was func_10008F24 */
void music_player_end_track(u8 idx) {
    // AL_TRACK_END
    n_csp_end_track(g_music_players[idx]);
}

/* was func_10008F58 */
void music_player_stop(u8 idx) {
    n_csp_stop(g_music_players[idx]);
}
