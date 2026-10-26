#include <n_libaudio.h>

extern s32  g_mp3_log_callback_alias; /* was D_800E0E00 */
extern s32  g_mp3_stream_state; /* was D_800E0E04 */
extern s32  g_mp3_stream_ramp_time; /* was D_800E0E10 */
extern s16  g_mp3_stream_target_pan; /* was D_800E0E14 */
extern s16  g_mp3_stream_requested_pan; /* was D_800E0E16 */
extern u8   g_mp3_stream_wait_frames; /* was D_800E0E18 */
extern u8   g_mp3_tables_loaded; /* was D_800E0E2C */
extern s32  g_mp3_huff_trees; /* was D_800E0E20 */
extern s32  g_mp3_huff_fast_table; /* was D_800E0E24 */
extern s32  g_mp3_huff_node_data; /* was D_800E0E28 */
extern s32  *g_mp3_pow43_buf; /* was D_800E0E30 */ // 0x8000
extern s32  g_mp3_stream; /* was D_800E0D80 */ // libaudio struct?
extern s16  g_mp3_stream_lp_cutoff; /* was D_800E0DB0 */
extern s16  g_mp3_stream_lp_gain; /* was D_800E0DB2 */
extern s32  g_mp3_stream_lp_update; /* was D_800E0DD8 */
extern s32  g_mp3_stream_rom_size; /* was D_800E0DE0 */
extern s32  g_mp3_stream_rom_pos; /* was D_800E0DE4 */
extern s32  g_mp3_stream_read_cb; /* was D_800E0DFC */
extern s32  g_mp3_stream_target_volume; /* was D_800E1238 */
extern void *g_audio_synth; /* was D_8002BA44 */


/* was func_151F2960 */
void mp3_stream_start(s32 arg0, s32 arg1) {
    if (g_mp3_stream_read_cb == 0) {
        return;
    }
    g_mp3_stream_state = 4;
    if (g_mp3_tables_loaded == 0) {
      g_mp3_tables_loaded = 1;
        g_mp3_pow43_buf = allocate_memory(0x8000, 0xFF, 2, 1);
        if (g_mp3_pow43_buf == 0) {
            g_mp3_tables_loaded = 0;
            return;
        }
        g_mp3_huff_trees = asset_load(0, 2, 0x17, 4);
        if (g_mp3_huff_trees != 0) {
            heap_set_block_tag(g_mp3_huff_trees, 0xFF);
        }
        g_mp3_huff_fast_table = asset_load(0, 2, 0x17, 5);
        if (g_mp3_huff_fast_table != 0) {
            heap_set_block_tag(g_mp3_huff_fast_table, 0xFF);
        }
        g_mp3_huff_node_data = asset_load(0, 2, 0x17, 6);
        if (g_mp3_huff_node_data != 0) {
            heap_set_block_tag(g_mp3_huff_node_data, 0xFF);
        }
        if ((g_mp3_huff_trees == 0) || (g_mp3_huff_fast_table == 0) || (g_mp3_huff_node_data == 0)) {
            if (g_mp3_huff_trees != 0) {
                heap_free(g_mp3_huff_trees);
            }
            if (g_mp3_huff_fast_table != 0) {
                heap_free(g_mp3_huff_fast_table);
            }
            if (g_mp3_huff_node_data != 0) {
                heap_free(g_mp3_huff_node_data);
            }
            heap_free(g_mp3_pow43_buf);
            g_mp3_pow43_buf = 0;
            g_mp3_tables_loaded = 0;
            return;
        }
        mp3dec_init();
    }
    g_mp3_stream = arg0;
    g_mp3_stream_rom_size = arg1;
    g_mp3_stream_rom_pos = 0;
    g_mp3_stream_ramp_time = 0;
    g_mp3_stream_wait_frames = 5;
    g_mp3_stream_state = 5;
}

/* was func_151F2BA8 */
void mp3_stream_stop(void) {
    u32 mask = osSetIntMask(1);
    g_mp3_stream_state = 3;
    osSetIntMask(mask);
}

/* was func_151F2BE8 */
void mp3_stream_pause(void) {
    u32 mask = osSetIntMask(1);
    if (g_mp3_stream_state == 5) {
        g_mp3_stream_state = 6;
    } else {
        g_mp3_stream_state = 2;
    }
    osSetIntMask(mask);
}

/* was func_151F2C4C */
void mp3_stream_resume(void) {
    u32 mask = osSetIntMask(1);
    if (g_mp3_stream_state == 2) {
        g_mp3_stream_wait_frames = 5;
        g_mp3_stream_state = 7;
    } else if (g_mp3_stream_state == 6) {
        g_mp3_stream_wait_frames = 5;
        g_mp3_stream_state = 5;
    }
    osSetIntMask(mask);
}

/* was func_151F2CDC */
s32 mp3_stream_get_state(void) {
    s32 ret = 0;
    u32 mask = osSetIntMask(1);
    if ((g_mp3_stream_state == 1) || (g_mp3_stream_state == 5) || (g_mp3_stream_state == 6) || (g_mp3_stream_state == 7) || (g_mp3_stream_state == 2)) {
        ret = g_mp3_stream_state;
    }
    osSetIntMask(mask);
    return ret;
}

/* was func_151F2D6C */
void mp3_stream_set_volume(s32 arg0, s32 arg1) {
    u32 mask = osSetIntMask(1);
    if (arg0 < 0) {
        g_mp3_stream_target_volume = 0;
    } else if (arg0 >= 0x8000) {
        g_mp3_stream_target_volume = 0x7FFF;
    } else {
        g_mp3_stream_target_volume = arg0;
    }
    g_mp3_stream_ramp_time = arg1;
    osSetIntMask(mask);
}

/* was func_151F2DFC */
void mp3_stream_set_pan(s32 arg0, s32 arg1) {
    if (arg0 >= 0x80) {
        arg0 = (u16)0x7F;
    } else {
        if (arg0 < 0) {
            arg0 = (u16)0;
        }
    }
    g_mp3_stream_requested_pan = arg0;
    if (arg1 != 0) {
        g_mp3_stream_target_pan = (s16) g_mp3_stream_requested_pan;
    }
}

/* was func_151F2E4C */
void mp3_stream_set_fx(s32 arg0, s32 arg1) {
    g_mp3_stream_lp_gain = arg0;
    g_mp3_stream_lp_cutoff = arg1;
    if (g_mp3_stream_lp_update == 0) {
        g_mp3_stream_lp_update = 2;
    }
}

extern s32 g_audio_unused_c05e; /* was D_8002C05E */
extern s32 g_level_id; /* was D_800BE9F0 */
extern s32 g_mp3_stream_decoder; /* was D_800E11B4 */
extern s32 *g_mp3_stream_env_state; /* was D_800E11B8 */
extern s16 g_mp3_stream_pan; /* was D_800E11BC */
extern s16 g_mp3_stream_volume; /* was D_800E11BE */
extern s16 g_mp3_stream_cvol_l; /* was D_800E11C0 */
extern s16 g_mp3_stream_cvol_r; /* was D_800E11C2 */
extern s16 g_mp3_stream_dry_amt; /* was D_800E11C4 */
extern s16 g_mp3_stream_wet_amt; /* was D_800E11C6 */
extern u16 g_mp3_stream_lratl; /* was D_800E11C8 */
extern s16 g_mp3_stream_lratm; /* was D_800E11CA */
extern s16 g_mp3_stream_ltgt; /* was D_800E11CC */
extern u16 g_mp3_stream_rratl; /* was D_800E11CE */
extern s16 g_mp3_stream_rratm; /* was D_800E11D0 */
extern s16 g_mp3_stream_rtgt; /* was D_800E11D2 */
extern u8 g_mp3_stream_env_first; /* was D_800E11D4 */
extern u8 g_mp3_stream_skip_mix; /* was D_800E11D5 */
extern s32 g_mp3_stream_env_delta; /* was D_800E11D8 */
extern s32 g_mp3_stream_env_seg_end; /* was D_800E11DC */
extern s32 *g_mp3_stream_lp_state; /* was D_800E120C */
extern s16 *g_mp3_stream_pcm_buf; /* was D_800E1218 */
extern s32 g_mp3_stream_pcm_len; /* was D_800E121C */
extern s32 g_mp3_stream_pcm_pos; /* was D_800E1220 */
extern s32 g_mp3_stream_dec_bufs[]; /* was D_800E1224 */
extern s32 g_mp3_stream_synth_ofs; /* was D_800E1228 */
extern u8 g_mp3_stream_stereo; /* was D_800E1249 */
extern s16 g_audio_eqpower[]; /* was D_8002BF60 */
s16 _getRate(f32 vol, f32 tgt, s32 count, u16 *ratel);
void n_fx_lowpass_update_coefs(void *, f32); /* P95: f32 parameter */
s32 mp3main_init(s32, s32, s32);
s32 mp3main_decode_next_frame(s32, s16 **, s32 *);
void mp3_stream_prefetch(void);
void mp3_stream_update_vol_pan();

// One block-scoped Acmd temp per command (each takes its own -g stack slot, like the libaudio a* macros).
#define CMD(p, a, b) { Acmd *_a = (p)++; _a->words.w0 = (a); _a->words.w1 = (b); }

/* was func_151F2E88 */
s32 mp3_stream_synth_pull(s32 count, Acmd **cmdp) {
    s32 i;
    s32 diff;
    s32 n;
    s16 *buf;
    s16 *src;
    s32 len;
    s32 outL;
    s32 outR;

    n = 0;
    src = NULL;
    outL = 0x4E0;
    outR = 0x650;
    if (g_mp3_stream_target_pan != g_mp3_stream_requested_pan) {
        diff = g_mp3_stream_requested_pan - g_mp3_stream_target_pan;
        if ((diff >= -2) && (diff < 3)) {
            g_mp3_stream_target_pan += diff;
        } else if (diff >= 3) {
            g_mp3_stream_target_pan += 2;
        } else {
            g_mp3_stream_target_pan -= 2;
        }
    }
    if (g_mp3_stream_state == 5) {
        mp3_stream_prefetch();
        if (g_mp3_stream_wait_frames == 0) {
            g_mp3_stream_decoder = mp3main_init(0, g_mp3_stream_read_cb, g_mp3_stream_rom_size);
            if (g_mp3_stream_decoder == 0) {
                g_mp3_stream_rom_pos = 0;
                g_mp3_stream_ramp_time = 0;
                g_mp3_stream_wait_frames = 5;
                mp3_stream_prefetch();
                g_mp3_stream_state = 5;
                return 0;
            } else {
                g_mp3_stream_state = 1;
                g_mp3_stream_env_first = 1;
                g_mp3_stream_skip_mix = 1;
                g_mp3_stream_pcm_buf = NULL;
                g_mp3_stream_pcm_len = 0;
                g_mp3_stream_pcm_pos = 0;
                g_mp3_stream_synth_ofs = 0;
                bzero(*(void **)((u8 *)&g_mp3_stream + 0x74), 0x440);
            }
        } else {
            g_mp3_stream_wait_frames -= 1;
        }
    }
    if (g_mp3_stream_state == 7) {
        mp3_stream_prefetch();
        if (g_mp3_stream_wait_frames == 0) {
            g_mp3_stream_state = 1;
        } else {
            g_mp3_stream_wait_frames -= 1;
        }
    }
    if (g_mp3_stream_state == 1) {
        if ((count + g_mp3_stream_pcm_pos) > g_mp3_stream_pcm_len) {
            g_mp3_stream_pcm_len -= g_mp3_stream_pcm_pos;
            if ((g_mp3_stream_pcm_len != 0) && (g_mp3_stream_pcm_buf != NULL)) {
                src = g_mp3_stream_pcm_buf + g_mp3_stream_pcm_pos;
                len = g_mp3_stream_pcm_len;
            }
            g_mp3_stream_pcm_pos = 0;
            g_mp3_stream_pcm_len = 0;
            if (mp3main_decode_next_frame(g_mp3_stream_decoder, &buf, &n) != 0) {
                g_mp3_stream_pcm_buf = buf;
                for (i = 0; i < n; i++) {
                    CMD(*cmdp, 0x08000000, osVirtualToPhysical((void *)g_mp3_stream_dec_bufs[i]));
                    CMD(*cmdp, (g_mp3_stream_synth_ofs & 0xFFFF) | 0x07000000, osVirtualToPhysical(buf));
                    buf += 0x244;
                }
                g_mp3_stream_synth_ofs = (g_mp3_stream_synth_ofs - 0x24) & 0x1E;
                g_mp3_stream_pcm_len = 0x240;
                g_mp3_stream_stereo = n == 2;
            } else {
            }
        }
        mp3_stream_prefetch();
        if (g_mp3_stream_stereo == 0) {
            outL = 0;
        }
        if (src != NULL) {
            CMD(*cmdp, ((((len + len)) & 0xFFF) << 0xC) | 0x04000000 | (outL & 0xFFF), osVirtualToPhysical(src));
            if (g_mp3_stream_stereo != 0) {
                src += 0x244;
                CMD(*cmdp, ((((len + len)) & 0xFFF) << 0xC) | 0x04000000 | (outR & 0xFFF), osVirtualToPhysical(src));
            }
            outL += (len + len);
            outR += (len + len);
            count -= len;
        }
        if ((count > 0) && (g_mp3_stream_pcm_buf != NULL)) {
            src = g_mp3_stream_pcm_buf + g_mp3_stream_pcm_pos;
            CMD(*cmdp, ((((count + count)) & 0xFFF) << 0xC) | 0x04000000 | (outL & 0xFFF), osVirtualToPhysical(src));
            if (g_mp3_stream_stereo != 0) {
                src += 0x244;
                CMD(*cmdp, ((((count + count)) & 0xFFF) << 0xC) | 0x04000000 | (outR & 0xFFF), osVirtualToPhysical(src));
            }
            g_mp3_stream_pcm_pos += count;
        }
        mp3_stream_update_vol_pan(&g_mp3_stream);
        if (g_mp3_stream_stereo == 0) {
            CMD(*cmdp, 0x020004E0, 0x2E0);
            CMD(*cmdp, 0x020007C0, 0x2E0);
            if (g_mp3_stream_skip_mix == 0) {
                if (g_mp3_stream_lp_gain > 0) {
                    if (g_mp3_stream_lp_update != 0) {
                        n_fx_lowpass_update_coefs((u8 *)&g_mp3_stream + 0x30, 22020.0f); /* P95: float literal (asm passes the bits 0x46AC0800) */
                    }
                    CMD(*cmdp, 0x0B000020, osVirtualToPhysical((u8 *)&g_mp3_stream + 0x38) & 0xFFFFFF);
                    if (g_mp3_stream_lp_update == 2) {
                        g_mp3_stream_lp_update = 0;
                    }
                    CMD(*cmdp, ((g_mp3_stream_lp_update & 0xFF) << 0x10) | 0x0E000000, osVirtualToPhysical(g_mp3_stream_lp_state) & 0xFFFFFF & 0xFFFFFF);
                    g_mp3_stream_lp_update = 0;
                }
                if (g_mp3_stream_env_first != 0) {
                    g_mp3_stream_env_first = 0;
                    g_mp3_stream_ltgt = (g_mp3_stream_volume * g_audio_eqpower[g_mp3_stream_pan]) >> 15;
                    g_mp3_stream_lratm = _getRate(g_mp3_stream_cvol_l, g_mp3_stream_ltgt, g_mp3_stream_env_seg_end, (u16 *)((u8 *)&g_mp3_stream + 0x18));
                    g_mp3_stream_rtgt = (g_mp3_stream_volume * g_audio_eqpower[128 - g_mp3_stream_pan - 1]) >> 15;
                    g_mp3_stream_rratm = _getRate(g_mp3_stream_cvol_r, g_mp3_stream_rtgt, g_mp3_stream_env_seg_end, (u16 *)((u8 *)&g_mp3_stream + 0x1E));
                    CMD(*cmdp, (g_mp3_stream_cvol_l & 0xFFFF) | 0x09060000, ((g_mp3_stream_dry_amt & 0xFFFF) << 0x10) | (g_mp3_stream_wet_amt & 0xFFFF));
                    CMD(*cmdp, (g_mp3_stream_rtgt & 0xFFFF) | 0x09040000, ((g_mp3_stream_rratm & 0xFFFF) << 0x10) | (g_mp3_stream_rratl & 0xFFFF));
                    CMD(*cmdp, (g_mp3_stream_ltgt & 0xFFFF) | 0x09000000, ((g_mp3_stream_lratm & 0xFFFF) << 0x10) | (g_mp3_stream_lratl & 0xFFFF));
                    CMD(*cmdp, (g_mp3_stream_cvol_r & 0xFFFF) | 0x03010000, osVirtualToPhysical(g_mp3_stream_env_state));
                } else {
                    CMD(*cmdp, 0x03000000, osVirtualToPhysical(g_mp3_stream_env_state));
                }
                g_mp3_stream_env_delta += 0xB8;
                if (g_mp3_stream_env_delta > g_mp3_stream_env_seg_end) {
                    g_mp3_stream_env_delta = g_mp3_stream_env_seg_end;
                }
            } else {
                g_mp3_stream_skip_mix = 0;
            }
        }
    } else if ((g_mp3_stream_state == 3) && (g_level_id != 0x35)) {
        if (g_mp3_tables_loaded != 0) {
            heap_free(g_mp3_huff_trees);
            heap_free(g_mp3_huff_fast_table);
            heap_free(g_mp3_huff_node_data);
            g_mp3_tables_loaded = 0;
        }
        if (g_mp3_pow43_buf != NULL) {
            heap_free(g_mp3_pow43_buf);
            g_mp3_pow43_buf = NULL;
        }
        g_mp3_stream_state = 0;
        return 0;
    } else {
        return 0;
    }
    return 1;
}

typedef struct {
    /* 0x00 */ u8  pad0[0xC];
    /* 0x0C */ s16 pan;
    /* 0x0E */ s16 volume;
    /* 0x10 */ s16 cvolL;
    /* 0x12 */ s16 cvolR;
    /* 0x14 */ u8  pad14[0x4];
    /* 0x18 */ u16 lratl;
    /* 0x1A */ s16 lratm;
    /* 0x1C */ s16 ltgt;
    /* 0x1E */ u16 rratl;
    /* 0x20 */ s16 rratm;
    /* 0x22 */ s16 rtgt;
    /* 0x24 */ u8  unk24;
    /* 0x28 */ s32 delta;
    /* 0x2C */ s32 segEnd;
    /* 0x30 */ u8  pad30[0x58];
    /* 0x88 */ s32 unk88; // target volume
    /* 0x8C */ u8  pad8C[0x4];
    /* 0x90 */ u32 unk90; // ramp time
    /* 0x94 */ s16 unk94; // target pan
} struct_151F39E4;

extern s16 g_audio_eqpower[]; /* was D_8002BF60 */ // eqpower
extern u8 g_audio_mono; /* was D_800428C1 */
extern u8 g_audio_headphones; /* was D_800428C2 */
s16 _getVol(s16 ivol, s32 samples, s16 ratem, u16 ratel);
void mp3_stream_stop(void);

/* was func_151F39E4 */
void mp3_stream_update_vol_pan(struct_151F39E4 *arg0) {
    if ((arg0->volume != arg0->unk88) || (arg0->pan != arg0->unk94)) {
        if (arg0->delta >= arg0->segEnd) {
            arg0->ltgt = (g_audio_eqpower[arg0->pan] * arg0->volume) >> 15;
            arg0->rtgt = (g_audio_eqpower[127 - arg0->pan] * arg0->volume) >> 15;
            arg0->delta = arg0->segEnd;
            arg0->cvolL = arg0->ltgt;
            arg0->cvolR = arg0->rtgt;
        } else {
            arg0->cvolL = _getVol(arg0->cvolL, arg0->delta, arg0->lratm, arg0->lratl);
            arg0->cvolR = _getVol(arg0->cvolR, arg0->delta, arg0->rratm, arg0->rratl);
        }
        if (arg0->cvolL == 0) {
            arg0->cvolL = 1;
        }
        if (arg0->cvolR == 0) {
            arg0->cvolR = 1;
        }
        arg0->volume = arg0->unk88;
        if ((arg0->volume == 0) && (arg0->unk90 != 0)) {
            mp3_stream_stop();
        }
        if (arg0->pan != arg0->unk94) {
            if (g_audio_headphones != 0) {
                arg0->pan = (arg0->unk94 >> 1) + 0x20;
            } else if (g_audio_mono != 0) {
                arg0->pan = 0x40;
            } else {
                arg0->pan = arg0->unk94;
            }
        }
        arg0->delta = 0;
        arg0->segEnd = ((arg0->unk90 + 183) / 184) * 184;
        arg0->unk24 = 1;
    }
}

/* was func_151F3C1C */
void mp3_stream_set_text_cb(s32 arg0) {
    g_mp3_log_callback_alias = arg0;
}

/* was func_151F3C34 */
void mp3_stream_set_read_cb(s32 arg0) {
    g_mp3_stream_read_cb = arg0;
}

/* was func_151F3C4C */
s32 mp3_stream_rom_read(s32 arg0, void *arg1, s32 arg2, s32 arg3) {
    s32 sp1C;
    s32 (*dma)(s32, s32, s32);

    if (arg3 != -1) {
        g_mp3_stream_rom_pos = arg3;
    }
    if ((g_mp3_stream_rom_pos + arg2) > g_mp3_stream_rom_size) {
        arg2 = g_mp3_stream_rom_size - g_mp3_stream_rom_pos;
    }
    dma = ((ALDMAproc (*)(void *))(((void **)g_audio_synth)[9]))(&sp1C);
    sp1C = dma(g_mp3_stream + g_mp3_stream_rom_pos, arg2, 0);
    if (sp1C == 0) {
        return 0;
    }
    sp1C += 0x80000000;
    osInvalDCache((void *)sp1C, arg2);
    bcopy((void *)sp1C, arg1, arg2);
    g_mp3_stream_rom_pos += arg2;
    return arg2;
}

/* was func_151F3D78 */
void mp3_stream_prefetch(void) {
    s32 sp1C;
    void (*dma)(s32, s32, s32);

    dma = ((ALDMAproc (*)(void *))(((void **)g_audio_synth)[9]))(&sp1C);
    dma(g_mp3_stream + g_mp3_stream_rom_pos, 0x810, 0);
}
