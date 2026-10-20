#include "n_synthInternals.h"
// relies on jump table
// s123: DK64 src/global_asm/audio/n_env.c n_alEnvmixerPull (built -g); DK64 include/structs.h CustomPVoice
typedef struct CustomResampler {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    void* unk14;
    f32 unk18;
    s32 unk1C;
    f32 unk20;
    s32 unk24;
    void* unk28;
    s16 unk2C;
    s16 unk2E;
    s16 unk30;
    s16 unk32;
} CustomResampler;

typedef struct CustomPVoice_unk70 {
    u8 pad0[0xB8];
} CustomPVoice_unk70;

typedef struct CustomPVoice_unk7C_unkC {
    u8 pad0[0x90]; /* Conker +8 */
    s32 unk88;
} CustomPVoice_unk7C_unkC;

typedef struct CustomPVoice_unk7C CustomPVoice_unk7C;
struct CustomPVoice_unk7C {
    CustomPVoice_unk7C *unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    union {
        struct {
            s16 unkC;
            s16 unkE;
        };
        CustomPVoice_unk7C_unkC *unkC_ptr;
        f32 unkC_f32;
        s32 unkC_s32;
    };
    union {
        struct {
            s16 unk10;
            u8 unk12;
            u8 unk13;
        };
        s32 unk10_s32;
    };
    u8 unk14;
    u8 unk15;
    u8 pad16[0x18 - 0x16];
    f32 unk18;
    s32 unk1C;
    void *unk20;
};

typedef struct CustomPVoice_unk20_unkC {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} CustomPVoice_unk20_unkC;

typedef struct CustomPVoice_unk20_unk10 {
    s32 unk0;
    s32 unk4;
} CustomPVoice_unk20_unk10;

typedef struct CustomPVoice_unk20 {
    s32 unk0;
    s32 unk4;
    u8 unk8;
    u8 pad9[0xC - 0x9];
    CustomPVoice_unk20_unkC *unkC;
    union {
        CustomPVoice_unk20_unk10 *unk10;
        s32 unk10_s32;
    };
} CustomPVoice_unk20;

typedef s32   (*CustomPVoice_unk28)(s32, s32, CustomResampler *);

typedef struct CustomPVoice {
    ALLink node;
    ALVoice *vvoice;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    CustomPVoice_unk20 *unk20;
    s32 unk24;
    u8 padConker[8]; /* Conker: +8 vs DK64 from here */
    CustomPVoice_unk28 unk28;
    CustomResampler resampler;
    s16 unk60;
    s16 unk62;
    u16 unk64;
    s16 unk66;
    s16 unk68;
    u16 unk6A;
    s16 unk6C;
    s16 unk6E;
    union {
        CustomPVoice_unk70 *unk70;
        s32 unk70_s32;
    };
    s32 unk74;
    s32 unk78;
    CustomPVoice_unk7C *unk7C;
    s32 *unk80;
    s32 unk84;
    s32 unk88;
    u8 padC94[5];
    u8 unk8C; /* Conker 0x99 */
    u8 pad9A[6];
    s16 unk90;
    s16 unk92;
    u8 pad94[0x98 - 0x94];
    s32 unk98;
    u8 pad9C[0xB8 - 0x9C];
    s32 unkB8;
    s32 unkBC;
} CustomPVoice;
#define n_alEnvmixerPull func_10020000
#define _pullSubFrame func_10020ABC
#define func_global_asm_807407A8 func_10021C40
#define __n_freeParam _n_freeParam
#define D_global_asm_807FF0F0 D_800428C0
#define D_global_asm_807FF0F1 D_800428C1
#define D_global_asm_807FF0F2 D_800428C2
#define n_eqpower D_8002BF60
extern u8 D_800428C0;
extern u8 D_800428C1;
extern u8 D_800428C2;
extern s16 D_8002BF60[];
#define N_EQPOWER_LENGTH 128
Acmd *_pullSubFrame(N_PVoice *filter, s16 *inp, s16 *outp, s32 outCount, Acmd *p);
void __n_freeParam(ALParam *);
s16 _getVol(s16, s32, s16, u16);
void func_global_asm_807407A8(CustomPVoice *, s32, void *);
Acmd *n_alEnvmixerPull(N_PVoice *arg0, s32 arg1, Acmd *arg2) {
    s32 sp54;
    CustomPVoice *sp50;
    s16 sp4E;
    s32 sp48;
    s32 sp44;
    s32 sp40;
    s16 sp3E;
    s32 sp38;
    CustomPVoice_unk7C *sp34;
    s32 sp30;
    CustomPVoice_unk7C *sp2C;
    s32 sp28;
    CustomPVoice_unk7C *sp24;
    CustomPVoice_unk7C *sp20;

    sp54 = arg2;
    sp50 = arg0;
    sp44 = arg1;
    sp3E = 0;
    sp30 = 0xB8;
    sp4E = 0;
    while (sp50->unk7C) {
        sp48 = sp44;
        sp44 = sp50->unk7C->unk4;
        sp40 = (((sp44 - sp48) + 0xB7) / 184U) * 0xB8;
        if (sp40 == 0) {
            sp44 = sp48;
        }
        if (sp40 > sp30 ) break;
        switch (sp50->unk7C->unk8) {
        case 13:
            sp2C = sp50->unk7C;
            if (sp2C->unkA != 0) {
                sp50->resampler.unk1C = 1;
            }
            func_global_asm_807407A8(sp50, 5, sp2C->unk20);
            sp50->unk84 = 1;
            sp50->unk78 = 1;
            sp50->unk70_s32 = 0;
            sp50->unk74 = (((sp2C->unk1C + 0xB7) / 184) * 0xB8);
            sp28 = (sp2C->unk10 + sp2C->unk10) / 2;
            sp50->resampler.unk2E = sp28;
            sp50->resampler.unk2C = sp2C->unk12;
            sp50->unk60 = (n_eqpower[sp2C->unk13 & 0x7F] & 0xFFFC);
            if (D_global_asm_807FF0F0 != 0) {
                sp50->unk60 |= (sp2C->unk13 >> 7);
            }
            sp50->unk62 = (n_eqpower[0x7F - (sp2C->unk13 & 0x7F)] & 0xFFFC);
            if (D_global_asm_807FF0F2 != 0) {
                sp50->resampler.unk2C = ((sp50->resampler.unk2C >> 1) + 0x20);
            } else if (D_global_asm_807FF0F1 != 0) {
                sp50->resampler.unk2C = 0x40;
            }
            if (sp2C->unk1C != 0) {
                sp50->resampler.unk30 = 1;
                sp50->resampler.unk32 = 1;
            } else {
                sp50->resampler.unk30 = ((n_eqpower[sp50->resampler.unk2C] * sp50->resampler.unk2E) >> 0xF);
                sp50->resampler.unk32 = ((n_eqpower[0x7F - sp50->resampler.unk2C] * sp50->resampler.unk2E) >> 0xF);
            }
            sp50->resampler.unk18 = sp2C->unkC_f32;
            sp50->unk92 = sp2C->unk15;
            sp50->unk90 = sp2C->unk18;
            sp50->unkB8 = 1;
            sp50->unk8C = sp2C->unk14;
            break;
        case 11:
        case 12:
        case 16:
            sp54 = _pullSubFrame(sp50, &sp4E, &sp3E, sp40, sp54);
            if (sp50->unk70_s32 >= sp50->unk74) {
                sp50->unk68 = ((n_eqpower[sp50->resampler.unk2C] * sp50->resampler.unk2E) >> 0xF);
                sp50->unk6E = ((n_eqpower[0x7F - sp50->resampler.unk2C] * sp50->resampler.unk2E) >> 0xF);
                sp50->unk70_s32 = sp50->unk74;
                sp50->resampler.unk30 = sp50->unk68;
                sp50->resampler.unk32 = sp50->unk6E;
            } else {
                sp50->resampler.unk30 = _getVol(sp50->resampler.unk30, sp50->unk70_s32, sp50->unk66, sp50->unk64);
                sp50->resampler.unk32 = _getVol(sp50->resampler.unk32, sp50->unk70_s32, sp50->unk6C, sp50->unk6A);
            }
            if (sp50->resampler.unk30 == 0) {
                sp50->resampler.unk30 = 1;
            }
            if (sp50->resampler.unk32 == 0) {
                sp50->resampler.unk32 = 1;
            }
            if (sp50->unk7C->unk8 == 0xC) {
                if (D_global_asm_807FF0F2 != 0) {
                    sp50->resampler.unk2C = ((sp50->unk7C->unkE >> 1) + 0x20);
                } else if (D_global_asm_807FF0F1 != 0) {
                    sp50->resampler.unk2C = 0x40;
                } else {
                    sp50->resampler.unk2C = sp50->unk7C->unkC_s32;
                }
            }
            if (sp50->unk7C->unk8 == 0xB) {
                sp50->unk70_s32 = 0;
                sp38 = sp50->unk7C->unkC_s32;
                sp38 = (sp38 + sp38) / 2;
                sp50->resampler.unk2E = sp38;
                sp50->unk74 = (((sp50->unk7C->unk10_s32 + 0xB7) / 184) * 0xB8);
            }
            if (sp50->unk7C->unk8 == 0x10) {
                if (((((sp50->unk60 & 1) ^ (sp50->unk62 & 1)) ^ ((sp50->unk7C->unkC_s32 + 1) >> 7)) != 0) && (D_global_asm_807FF0F0 != 0)) {
                    if (sp50->resampler.unk2C >= 0x41) {
                        sp50->unk60 ^= 1;
                        if (sp50->resampler.unk2C < 0x6F) {
                            sp50->unk60 |= 2;
                        }
                    } else {
                        sp50->unk62 ^= 1;
                        if (sp50->resampler.unk2C >= 0x11) {
                            sp50->unk62 |= 2;
                        }
                    }
                }
                sp50->unk60 = ((n_eqpower[(sp50->unk7C->unkC_s32 & 0x7F)] & 0xFFFC) | (sp50->unk60 & 3));
                sp50->unk62 = ((n_eqpower[0x7F - (sp50->unk7C->unkC_s32 & 0x7F)] & 0xFFFC) | (sp50->unk62 & 3));
            }
            sp50->unk78 = 1;
            break;
        case 14:
            sp24 = sp50->unk7C;
            if (sp24->unkA != 0) {
                sp50->resampler.unk1C = 1;
            }
            func_global_asm_807407A8(sp50, 5, sp24->unkC_s32);
            sp50->unk84 = 1;
            break;
        case 15:
            sp54 = _pullSubFrame(sp50, &sp4E, &sp3E, sp40, sp54);
            n_alEnvmixerParam(sp50, 4, 0);
            break;
        case 0:
            sp20 = sp50->unk7C;
            sp20->unkC_ptr->unk88 = 0;
            _n_freePVoice(sp20->unkC_s32);
            break;
        case 7:
            sp54 = _pullSubFrame(sp50, &sp4E, &sp3E, sp40, sp54);
            sp50->resampler.unk18 = sp50->unk7C->unkC_f32;
            break;
        case 8:
            sp54 = _pullSubFrame(sp50, &sp4E, &sp3E, sp40, sp54);
            sp50->resampler.unk1C = 1;
            break;
        case 5:
            sp54 = _pullSubFrame(sp50, &sp4E, &sp3E, sp40, sp54);
            func_global_asm_807407A8(sp50, 5, sp50->unk7C->unkC_s32);
            break;
        default:
            sp54 = _pullSubFrame(sp50, &sp4E, &sp3E, sp40, sp54);
            n_alEnvmixerParam(sp50, sp50->unk7C->unk8, sp50->unk7C->unkC_s32);
            break;
        }
        sp3E += sp40 * 2;
        sp30 -= sp40;
        sp34 = sp50->unk7C;
        sp50->unk7C = sp50->unk7C->unk0;
        if (sp50->unk7C == NULL) {
            sp50->unk80 = 0;
        }
        __n_freeParam(sp34);
    }
    sp54 = _pullSubFrame(sp50, &sp4E, &sp3E, sp30, sp54);
    if (sp50->unk70_s32 > sp50->unk74) {
        sp50->unk70_s32 = sp50->unk74;
    }
    return sp54;
}


s32 n_alEnvmixerParam(N_PVoice *filter, s32 paramID, void *param) {
    N_PVoice  *e = filter;

    switch (paramID) {
      case (AL_FILTER_ADD_UPDATE):
          if (e->em_ctrlTail) {
              e->em_ctrlTail->next = (ALParam *)param;
          } else {
              e->em_ctrlList = (ALParam *)param;
          }
          e->em_ctrlTail = (ALParam *)param;
          break;
      case (AL_FILTER_RESET):
          e->em_first = 1;
          e->em_motion = AL_STOPPED;
          e->em_volume = 1;
          e->em_segEnd = 0;
          e->rs_delta  = 0.0;
          e->rs_first  = 1;
          e->rs_upitch = 0;
          n_alLoadParam(e, AL_FILTER_RESET, param);
          break;
      case (AL_FILTER_START):
          e->em_motion = AL_PLAYING;
          break;
      default:
#if 1
          n_alLoadParam(e, paramID, param);
#else
          n_alResampleParam(e, paramID, param); // TODO
#endif
          break;
  }
  return 0;
}

// _pullSubFrame
s16 _getRate(f32 vol, f32 tgt, s32 count, u16 *ratel);
Acmd *func_10022040(N_PVoice *, s16 *, s32, Acmd *);
Acmd *_pullSubFrame(N_PVoice *filter, s16 *inp, s16 *outp, s32 outCount, Acmd *p)
{
	Acmd *ptr = p;
	N_PVoice *e = filter;

	if (e->dc_table) {
		((u8 *) e->dc_table)[10] = 1;
	}

	if (e->em_motion != AL_PLAYING || !outCount) {
		return ptr;
	}

	ptr = func_10022040(e, inp, outCount, p);

	if (e->em_first) {
		e->em_first = 0;

		e->em_ltgt = (e->em_volume * n_eqpower[e->em_pan]) >> 15;
		e->em_lratm = _getRate(e->em_cvolL, e->em_ltgt, e->em_segEnd, &(e->em_lratl));
		e->em_rtgt = (e->em_volume * n_eqpower[N_EQPOWER_LENGTH - e->em_pan - 1]) >> 15;
		e->em_rratm = _getRate(e->em_cvolR, e->em_rtgt, e->em_segEnd, &(e->em_rratl));

		n_aSetVolume(ptr++, A_LEFT  | A_VOL, e->em_cvolL, e->em_dryamt, e->em_wetamt);
		n_aSetVolume(ptr++, A_RIGHT | A_VOL, e->em_rtgt, e->em_rratm,  e->em_rratl);
		n_aSetVolume(ptr++, A_RATE, e->em_ltgt, e->em_lratm, e->em_lratl);
		n_aEnvMixer (ptr++, A_INIT, e->em_cvolR, osVirtualToPhysical(e->em_state));
	} else {
		n_aEnvMixer(ptr++, A_CONTINUE, 0, osVirtualToPhysical(e->em_state));
	}

	*inp += (FIXED_SAMPLE << 1);
	e->em_delta += FIXED_SAMPLE;

	if ((e->em_dryamt & 2) || (e->em_wetamt & 2)) {
		e->em_dryamt &= ~2;
		e->em_wetamt &= ~2;
		e->em_first = 1;
	}

	return ptr;
}

s16 _getRate(f32 arg0, f32 arg1, s32 arg2, u16 *arg3) {
    s16 spE;
    s16 spC;
    f32 sp8;
    f32 sp4;
    f32 sp0;

    if (arg2 == 0) {
        if (arg0 <= arg1) {
            *arg3 = 0xFFFF;
            return 0x7FFF;
        } else {
            *arg3 = 0;
            return -0x8000;
        }
    }
    sp8 = 1.0f / (f32) arg2;

    if (arg1 < 1.0f) {
        arg1 = 1.0f;
    }
    if (arg0 <= 0.0f) {
        arg0 = 1.0f;
    }
    sp4 = (arg1 - arg0) * sp8 * 8.0f;
    spE = (s16) (s32) sp4;
    sp0 = sp4 - (f32) spE;
    spE = spE - 1;
    sp0 = sp0 + 1.0f;
    spC = (s16) (s32) sp0;
    spE = spE + spC;
    sp0 = sp0 - (f32) spC;
    *arg3 = (u32) (65535.0f * sp0); // 65535.0f
    return spE;
}

s16 _getVol(s16 ivol, s32 samples, s16 ratem, u16 ratel)
{
    s32 tmp1;
#ifdef AUD_PROFILE
    lastCnt[++cnt_index] = osGetCount();
#endif

    samples >>= 3;
    if (samples == 0){
        return ivol;
    }

    tmp1 = ratel * samples;
    tmp1 >>= 16;
    tmp1 += ratem * samples;
    ivol += tmp1;

#ifdef AUD_PROFILE
    PROFILE_AUD(vol_num, vol_cnt, vol_max, vol_min);
#endif
    return ivol;
}
