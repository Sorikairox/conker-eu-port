#include <n_libaudio.h>

extern s32  D_800E0E00;
extern s32  D_800E0E04;
extern s32  D_800E0E10;
extern s16  D_800E0E14;
extern s16  D_800E0E16;
extern u8   D_800E0E18;
extern u8   D_800E0E2C;
extern s32  D_800E0E20;
extern s32  D_800E0E24;
extern s32  D_800E0E28;
extern s32  *D_800E0E30; // 0x8000
extern s32  D_800E0D80; // libaudio struct?
extern s16  D_800E0DB0;
extern s16  D_800E0DB2;
extern s32  D_800E0DD8;
extern s32  D_800E0DE0;
extern s32  D_800E0DE4;
extern s32  D_800E0DFC;
extern s32  D_800E1238;
extern void *D_8002BA44;


/* was func_151F2960 */
void mp3_stream_start(s32 arg0, s32 arg1) {
    if (D_800E0DFC == 0) {
        return;
    }
    D_800E0E04 = 4;
    if (D_800E0E2C == 0) {
      D_800E0E2C = 1;
        D_800E0E30 = allocate_memory(0x8000, 0xFF, 2, 1);
        if (D_800E0E30 == 0) {
            D_800E0E2C = 0;
            return;
        }
        D_800E0E20 = asset_load(0, 2, 0x17, 4);
        if (D_800E0E20 != 0) {
            heap_set_block_tag(D_800E0E20, 0xFF);
        }
        D_800E0E24 = asset_load(0, 2, 0x17, 5);
        if (D_800E0E24 != 0) {
            heap_set_block_tag(D_800E0E24, 0xFF);
        }
        D_800E0E28 = asset_load(0, 2, 0x17, 6);
        if (D_800E0E28 != 0) {
            heap_set_block_tag(D_800E0E28, 0xFF);
        }
        if ((D_800E0E20 == 0) || (D_800E0E24 == 0) || (D_800E0E28 == 0)) {
            if (D_800E0E20 != 0) {
                heap_free(D_800E0E20);
            }
            if (D_800E0E24 != 0) {
                heap_free(D_800E0E24);
            }
            if (D_800E0E28 != 0) {
                heap_free(D_800E0E28);
            }
            heap_free(D_800E0E30);
            D_800E0E30 = 0;
            D_800E0E2C = 0;
            return;
        }
        mp3dec_init();
    }
    D_800E0D80 = arg0;
    D_800E0DE0 = arg1;
    D_800E0DE4 = 0;
    D_800E0E10 = 0;
    D_800E0E18 = 5;
    D_800E0E04 = 5;
}

/* was func_151F2BA8 */
void mp3_stream_stop(void) {
    u32 mask = osSetIntMask(1);
    D_800E0E04 = 3;
    osSetIntMask(mask);
}

/* was func_151F2BE8 */
void mp3_stream_pause(void) {
    u32 mask = osSetIntMask(1);
    if (D_800E0E04 == 5) {
        D_800E0E04 = 6;
    } else {
        D_800E0E04 = 2;
    }
    osSetIntMask(mask);
}

/* was func_151F2C4C */
void mp3_stream_resume(void) {
    u32 mask = osSetIntMask(1);
    if (D_800E0E04 == 2) {
        D_800E0E18 = 5;
        D_800E0E04 = 7;
    } else if (D_800E0E04 == 6) {
        D_800E0E18 = 5;
        D_800E0E04 = 5;
    }
    osSetIntMask(mask);
}

/* was func_151F2CDC */
s32 mp3_stream_get_state(void) {
    s32 ret = 0;
    u32 mask = osSetIntMask(1);
    if ((D_800E0E04 == 1) || (D_800E0E04 == 5) || (D_800E0E04 == 6) || (D_800E0E04 == 7) || (D_800E0E04 == 2)) {
        ret = D_800E0E04;
    }
    osSetIntMask(mask);
    return ret;
}

/* was func_151F2D6C */
void mp3_stream_set_volume(s32 arg0, s32 arg1) {
    u32 mask = osSetIntMask(1);
    if (arg0 < 0) {
        D_800E1238 = 0;
    } else if (arg0 >= 0x8000) {
        D_800E1238 = 0x7FFF;
    } else {
        D_800E1238 = arg0;
    }
    D_800E0E10 = arg1;
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
    D_800E0E16 = arg0;
    if (arg1 != 0) {
        D_800E0E14 = (s16) D_800E0E16;
    }
}

/* was func_151F2E4C */
void mp3_stream_set_fx(s32 arg0, s32 arg1) {
    D_800E0DB2 = arg0;
    D_800E0DB0 = arg1;
    if (D_800E0DD8 == 0) {
        D_800E0DD8 = 2;
    }
}

extern s32 D_8002C05E;
extern s32 D_800BE9F0;
extern s32 D_800E11B4;
extern s32 *D_800E11B8;
extern s16 D_800E11BC;
extern s16 D_800E11BE;
extern s16 D_800E11C0;
extern s16 D_800E11C2;
extern s16 D_800E11C4;
extern s16 D_800E11C6;
extern u16 D_800E11C8;
extern s16 D_800E11CA;
extern s16 D_800E11CC;
extern u16 D_800E11CE;
extern s16 D_800E11D0;
extern s16 D_800E11D2;
extern u8 D_800E11D4;
extern u8 D_800E11D5;
extern s32 D_800E11D8;
extern s32 D_800E11DC;
extern s32 *D_800E120C;
extern s16 *D_800E1218;
extern s32 D_800E121C;
extern s32 D_800E1220;
extern s32 D_800E1224[];
extern s32 D_800E1228;
extern u8 D_800E1249;
extern s16 D_8002BF60[];
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
    if (D_800E0E14 != D_800E0E16) {
        diff = D_800E0E16 - D_800E0E14;
        if ((diff >= -2) && (diff < 3)) {
            D_800E0E14 += diff;
        } else if (diff >= 3) {
            D_800E0E14 += 2;
        } else {
            D_800E0E14 -= 2;
        }
    }
    if (D_800E0E04 == 5) {
        mp3_stream_prefetch();
        if (D_800E0E18 == 0) {
            D_800E11B4 = mp3main_init(0, D_800E0DFC, D_800E0DE0);
            if (D_800E11B4 == 0) {
                D_800E0DE4 = 0;
                D_800E0E10 = 0;
                D_800E0E18 = 5;
                mp3_stream_prefetch();
                D_800E0E04 = 5;
                return 0;
            } else {
                D_800E0E04 = 1;
                D_800E11D4 = 1;
                D_800E11D5 = 1;
                D_800E1218 = NULL;
                D_800E121C = 0;
                D_800E1220 = 0;
                D_800E1228 = 0;
                bzero(*(void **)((u8 *)&D_800E0D80 + 0x74), 0x440);
            }
        } else {
            D_800E0E18 -= 1;
        }
    }
    if (D_800E0E04 == 7) {
        mp3_stream_prefetch();
        if (D_800E0E18 == 0) {
            D_800E0E04 = 1;
        } else {
            D_800E0E18 -= 1;
        }
    }
    if (D_800E0E04 == 1) {
        if ((count + D_800E1220) > D_800E121C) {
            D_800E121C -= D_800E1220;
            if ((D_800E121C != 0) && (D_800E1218 != NULL)) {
                src = D_800E1218 + D_800E1220;
                len = D_800E121C;
            }
            D_800E1220 = 0;
            D_800E121C = 0;
            if (mp3main_decode_next_frame(D_800E11B4, &buf, &n) != 0) {
                D_800E1218 = buf;
                for (i = 0; i < n; i++) {
                    CMD(*cmdp, 0x08000000, osVirtualToPhysical((void *)D_800E1224[i]));
                    CMD(*cmdp, (D_800E1228 & 0xFFFF) | 0x07000000, osVirtualToPhysical(buf));
                    buf += 0x244;
                }
                D_800E1228 = (D_800E1228 - 0x24) & 0x1E;
                D_800E121C = 0x240;
                D_800E1249 = n == 2;
            } else {
            }
        }
        mp3_stream_prefetch();
        if (D_800E1249 == 0) {
            outL = 0;
        }
        if (src != NULL) {
            CMD(*cmdp, ((((len + len)) & 0xFFF) << 0xC) | 0x04000000 | (outL & 0xFFF), osVirtualToPhysical(src));
            if (D_800E1249 != 0) {
                src += 0x244;
                CMD(*cmdp, ((((len + len)) & 0xFFF) << 0xC) | 0x04000000 | (outR & 0xFFF), osVirtualToPhysical(src));
            }
            outL += (len + len);
            outR += (len + len);
            count -= len;
        }
        if ((count > 0) && (D_800E1218 != NULL)) {
            src = D_800E1218 + D_800E1220;
            CMD(*cmdp, ((((count + count)) & 0xFFF) << 0xC) | 0x04000000 | (outL & 0xFFF), osVirtualToPhysical(src));
            if (D_800E1249 != 0) {
                src += 0x244;
                CMD(*cmdp, ((((count + count)) & 0xFFF) << 0xC) | 0x04000000 | (outR & 0xFFF), osVirtualToPhysical(src));
            }
            D_800E1220 += count;
        }
        mp3_stream_update_vol_pan(&D_800E0D80);
        if (D_800E1249 == 0) {
            CMD(*cmdp, 0x020004E0, 0x2E0);
            CMD(*cmdp, 0x020007C0, 0x2E0);
            if (D_800E11D5 == 0) {
                if (D_800E0DB2 > 0) {
                    if (D_800E0DD8 != 0) {
                        n_fx_lowpass_update_coefs((u8 *)&D_800E0D80 + 0x30, 22020.0f); /* P95: float literal (asm passes the bits 0x46AC0800) */
                    }
                    CMD(*cmdp, 0x0B000020, osVirtualToPhysical((u8 *)&D_800E0D80 + 0x38) & 0xFFFFFF);
                    if (D_800E0DD8 == 2) {
                        D_800E0DD8 = 0;
                    }
                    CMD(*cmdp, ((D_800E0DD8 & 0xFF) << 0x10) | 0x0E000000, osVirtualToPhysical(D_800E120C) & 0xFFFFFF & 0xFFFFFF);
                    D_800E0DD8 = 0;
                }
                if (D_800E11D4 != 0) {
                    D_800E11D4 = 0;
                    D_800E11CC = (D_800E11BE * D_8002BF60[D_800E11BC]) >> 15;
                    D_800E11CA = _getRate(D_800E11C0, D_800E11CC, D_800E11DC, (u16 *)((u8 *)&D_800E0D80 + 0x18));
                    D_800E11D2 = (D_800E11BE * D_8002BF60[128 - D_800E11BC - 1]) >> 15;
                    D_800E11D0 = _getRate(D_800E11C2, D_800E11D2, D_800E11DC, (u16 *)((u8 *)&D_800E0D80 + 0x1E));
                    CMD(*cmdp, (D_800E11C0 & 0xFFFF) | 0x09060000, ((D_800E11C4 & 0xFFFF) << 0x10) | (D_800E11C6 & 0xFFFF));
                    CMD(*cmdp, (D_800E11D2 & 0xFFFF) | 0x09040000, ((D_800E11D0 & 0xFFFF) << 0x10) | (D_800E11CE & 0xFFFF));
                    CMD(*cmdp, (D_800E11CC & 0xFFFF) | 0x09000000, ((D_800E11CA & 0xFFFF) << 0x10) | (D_800E11C8 & 0xFFFF));
                    CMD(*cmdp, (D_800E11C2 & 0xFFFF) | 0x03010000, osVirtualToPhysical(D_800E11B8));
                } else {
                    CMD(*cmdp, 0x03000000, osVirtualToPhysical(D_800E11B8));
                }
                D_800E11D8 += 0xB8;
                if (D_800E11D8 > D_800E11DC) {
                    D_800E11D8 = D_800E11DC;
                }
            } else {
                D_800E11D5 = 0;
            }
        }
    } else if ((D_800E0E04 == 3) && (D_800BE9F0 != 0x35)) {
        if (D_800E0E2C != 0) {
            heap_free(D_800E0E20);
            heap_free(D_800E0E24);
            heap_free(D_800E0E28);
            D_800E0E2C = 0;
        }
        if (D_800E0E30 != NULL) {
            heap_free(D_800E0E30);
            D_800E0E30 = NULL;
        }
        D_800E0E04 = 0;
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

extern s16 D_8002BF60[]; // eqpower
extern u8 D_800428C1;
extern u8 D_800428C2;
s16 _getVol(s16 ivol, s32 samples, s16 ratem, u16 ratel);
void mp3_stream_stop(void);

/* was func_151F39E4 */
void mp3_stream_update_vol_pan(struct_151F39E4 *arg0) {
    if ((arg0->volume != arg0->unk88) || (arg0->pan != arg0->unk94)) {
        if (arg0->delta >= arg0->segEnd) {
            arg0->ltgt = (D_8002BF60[arg0->pan] * arg0->volume) >> 15;
            arg0->rtgt = (D_8002BF60[127 - arg0->pan] * arg0->volume) >> 15;
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
            if (D_800428C2 != 0) {
                arg0->pan = (arg0->unk94 >> 1) + 0x20;
            } else if (D_800428C1 != 0) {
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
    D_800E0E00 = arg0;
}

/* was func_151F3C34 */
void mp3_stream_set_read_cb(s32 arg0) {
    D_800E0DFC = arg0;
}

/* was func_151F3C4C */
s32 mp3_stream_rom_read(s32 arg0, void *arg1, s32 arg2, s32 arg3) {
    s32 sp1C;
    s32 (*dma)(s32, s32, s32);

    if (arg3 != -1) {
        D_800E0DE4 = arg3;
    }
    if ((D_800E0DE4 + arg2) > D_800E0DE0) {
        arg2 = D_800E0DE0 - D_800E0DE4;
    }
    dma = ((ALDMAproc (*)(void *))(((void **)D_8002BA44)[9]))(&sp1C);
    sp1C = dma(D_800E0D80 + D_800E0DE4, arg2, 0);
    if (sp1C == 0) {
        return 0;
    }
    sp1C += 0x80000000;
    osInvalDCache((void *)sp1C, arg2);
    bcopy((void *)sp1C, arg1, arg2);
    D_800E0DE4 += arg2;
    return arg2;
}

/* was func_151F3D78 */
void mp3_stream_prefetch(void) {
    s32 sp1C;
    void (*dma)(s32, s32, s32);

    dma = ((ALDMAproc (*)(void *))(((void **)D_8002BA44)[9]))(&sp1C);
    dma(D_800E0D80 + D_800E0DE4, 0x810, 0);
}
