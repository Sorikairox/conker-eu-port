#define n_alFxNew n_alFxNew_proto /* s123: header prototype differs (DK64 signature below) */
#include "n_synthInternals.h"
#undef n_alFxNew

#if 0
f32 PI = 3.1415927410125732;
f32 g_audio_fx_sqrt2 = 1.4142136573791504; /* was D_8002C774 */
f32 g_audio_semitone_up = 1.0594631433486938; /* was D_8002C778 */
f32 g_audio_semitone_down = 0.9438742995262146; /* was D_8002C77C */
f32 g_audio_lp_coef_scale_0 = 26768.0; /* was D_8002C780 */
f32 g_audio_lp_coef_scale_1 = 26768.0; /* was D_8002C784 */
f32 g_audio_fx_delay_scale_alias = 173123.40625; /* was D_8002C788 */
f32 g_audio_fx_k_caec = 0.0; /* was D_8002C78C */
#endif

extern f32 g_audio_fx_pi; /* was D_8002C770 */
extern f32 g_audio_fx_sqrt2; /* was D_8002C774 */
extern f32 g_audio_semitone_up; /* was D_8002C778 */
extern f32 g_audio_semitone_down; /* was D_8002C77C */
extern f32 g_audio_lp_coef_scale_0; /* was D_8002C780 */
extern f32 g_audio_lp_coef_scale_1; /* was D_8002C784 */
extern f32 g_audio_fx_delay_scale_alias; /* was D_8002C788 */
extern f32 g_audio_fx_k_caec; /* was D_8002C78C */

f32 math_atan2f(f32, f32);


/* was func_1001CBF0 */
void n_fx_calc_biquad_lowpass(f32 arg0, f32 arg1, f32 arg2, f32 arg3[3], f32 arg4[3]) {
    f32 sp24;
    f32 sp20;
    f32 sp1C;

    if (arg1 >= (arg0 - 200.0f)) {
        arg1 = arg0 - 200.0f;
    }

    sp24 = math_atan2f(arg1 * g_audio_fx_pi, arg0);
    sp20 = sp24 * sp24;
    sp1C = (sp24 * g_audio_fx_sqrt2) / arg2;
    arg3[0] = sp20 / (1.0f + sp20 + sp1C);
    arg3[1] = arg3[0] * 2.0f;
    arg3[2] = arg3[0];
    arg4[1] = ((sp20 - 1.0f) * 2.0f) / (1.0f + sp20 + sp1C);
    arg4[2] = ((1.0f + sp20) - sp1C) / (1.0f + sp20 + sp1C);
}

void init_lpfilter(ALLowPass *arg0) {
    s32 i;
    s32 sp10;
    s16 spE;
    f32 temp_f8;
    f32 sp4;
    f32 sp0;

    sp10 = arg0->fc * 16384.0f;
    spE = sp10 >> 15;
    arg0->fgain = 16384.0f - spE;
    arg0->fstate = 0;

    for (i = 0; i < 8; i++)
    {
        arg0->fcvec.fccoef[i] = 0;
    }
    arg0->fcvec.fccoef[i++] = spE;

    sp0 = 16384.0f;
    sp4 = temp_f8 = spE / sp0;

    for (;i < 16; i++)
    {
        sp4 *= temp_f8;
        arg0->fcvec.fccoef[i] = sp4 * sp0;
    }
}

/* was func_1001CEA4 */
f32 audio_semitones_to_ratio(s32 arg0) {
    f32 sp4;
    f32 sp0 = 1.0f;

    if (arg0 >= 0) {
        sp4 = g_audio_semitone_up;
    } else {
        sp4 = g_audio_semitone_down;
        arg0 = -arg0;
    }

    while (arg0 != 0) {
        if ((arg0 & 1) != 0) {
            sp0 = sp0 * sp4;
        }
        sp4 *= sp4;
        arg0 = arg0 >> 1;
    };

    return sp0;
}

/* was func_1001CF38 */
void n_fx_lowpass_update_coefs(ALLowPass *arg0, f32 arg1) {
    s32 i;
    f32 sp30[3];
    f32 sp24[3];

    if (arg0->fgain == 0) {
        return;
    }
    if (arg0->fgain < 10) {
        arg0->fgain = 10;
    }
    n_fx_calc_biquad_lowpass(arg1,  arg0->fc + 10.0f, arg0->fgain / 10.0f, &sp30, &sp24);

    for(i = 3; i < 8; i++) {
        arg0->fcvec.fccoef[i] = 0;
    }
    arg0->fcvec.fccoef[0] = sp30[0] * (g_audio_lp_coef_scale_0 - (arg0->fgain * 128.0f));
    arg0->fcvec.fccoef[1] = sp30[1] * (g_audio_lp_coef_scale_1 - (arg0->fgain * 128.0f));
    arg0->fcvec.fccoef[2] = 0;

    arg0->fcvec.fccoef[8] = sp24[1] * -16384.0f;
    arg0->fcvec.fccoef[9] = sp24[2] * -16384.0f;

    for (i = 10; i < 16; i++) {
        arg0->fcvec.fccoef[i] = 0;
    }
}

// s123: DK64 src/global_asm/audio/n_drvrNew.c n_alFxNew (built -g)
#define D_global_asm_80756458 g_audio_fx_default_params
#define _init_lpfilter(x) init_lpfilter((ALLowPass *) (x))
extern s32 g_audio_fx_default_params; /* was D_8002BF30 */
extern f32 g_audio_fx_delay_scale; /* 173123.4f; was D_8002CAE8 */
typedef struct {
    u8 pad0[0x2C]; /* Conker layout (DK64 has outputRate at 0x18) */
    s32 outputRate;
    ALFxId fxTypes[4];
    s32 *params[2];
} RareSynConfig;
#define ALSynConfig RareSynConfig
typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    u8 unk1C[4]; // TODO: How many elements?
    s32 unk20[1]; // TODO: How many elements?
} Struct8073C040_arg1;

typedef struct Struct8073C040_SP28_sub20 {
    s16 unk0;
    u8 pad2[0x2C - 2];
    void *unk2C;
    void *unk30;
} Struct8073C040_SP28_sub20;

typedef struct Struct8073C040_SP28_sub24 {
    u8 pad0[0x14];
    void *unk14;
    void *unk18;
    u8 pad1C[0x24 - 0x1C];
    f32 unk24;
    s32 unk28;
} Struct8073C040_SP28_sub24;

typedef struct Struct8073C040_SP28 {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 padE[2];
    f32 unk10;
    f32 unk14;
    s32 unk18;
    f32 unk1C;
    Struct8073C040_SP28_sub20 *unk20;
    Struct8073C040_SP28_sub24 *unk24;
} Struct8073C040_SP28;

typedef struct Struct8073C040_SP24 {
    u32 unk0;
    Struct8073C040_SP28 *unk4;
    u8 unk8;
    u8 pad9[0x20 - 0x9];
    s16 *unk20;
    s16 *unk24;
    s16 *unk28;
    s16 *unk2C;
} Struct8073C040_SP24;

void n_alFxNew(ALFx **arg0, ALSynConfig *arg1, s16 arg2, s32 arg3) {
    u16 i, j, k;
    s32 *sp2C;
    Struct8073C040_SP28 *sp28;
    Struct8073C040_SP24 *sp24;

    sp2C = NULL;
    sp24 = alHeapAlloc(arg3, 1U, 0x30);
    *arg0 = sp24;
    switch (arg1->fxTypes[arg2]) {
        case 6:
            sp2C = arg1->params[arg2];
            break;
        default:
            sp2C = &D_global_asm_80756458;
            break;
    }
    j = 0;
    sp24->unk8 = sp2C[j++];
    sp24->unk0 = sp2C[j++];
    sp24->unk4 = alHeapAlloc(arg3, sp24->unk8, 0x28);
    sp24->unk20 = alHeapAlloc(arg3, sp24->unk0, 2);
    sp24->unk28 = sp24->unk20;
    sp24->unk24 = alHeapAlloc(arg3, sp24->unk0, 2);
    sp24->unk2C = (void *) sp24->unk24;
    for (k = 0; k < sp24->unk0; k++) {
        sp24->unk24[k] = 0;
        sp24->unk20[k] = sp24->unk24[k];
    }
    for (i = 0; i < sp24->unk8; i++) {
        sp28 = &sp24->unk4[i];
        sp28->unk0 = sp2C[j++];
        sp28->unk4 = sp2C[j++];
        sp28->unkA = sp2C[j++];
        sp28->unk8 = sp2C[j++];
        sp28->unkC = sp2C[j++];
        if (sp2C[j]) {
            sp28->unk10 = ((sp2C[j++] / 1000.0f) * 2.0f) / ((ALSynConfig*) arg1)->outputRate;
            sp28->unk1C = (sp2C[j++] / g_audio_fx_delay_scale) /* rodata of another object */ * (u32)(sp28->unk4 - sp28->unk0);
            sp28->unk14 = 1.0f;
            sp28->unk18 = 0;
            sp28->unk24 = alHeapAlloc(arg3, 1U, 0x38);
            sp28->unk24->unk14 = alHeapAlloc(arg3, 1U, 0x20);
            sp28->unk24->unk18 = alHeapAlloc(arg3, 1U, 0x20);
            sp28->unk24->unk24 = 0.0f;
            sp28->unk24->unk28 = 1;
        } else {
            sp28->unk24 = NULL;
            j++;
            j++;
        }
        if (sp2C[j]) {
            sp28->unk20 = alHeapAlloc(arg3, 1U, 0x38);
            sp28->unk20->unk2C = alHeapAlloc(arg3, 1U, 8);
            sp28->unk20->unk30 = alHeapAlloc(arg3, 1U, 8);
            sp28->unk20->unk0 = (s16) sp2C[j];
            j++;
            _init_lpfilter(sp28->unk20);
        } else {
            sp28->unk20 = NULL;
            j++;
        }
    }
}


#undef ALSynConfig

void alN_PVoiceNew(N_PVoice *mv, ALDMANew dmaNew, ALHeap *hp) {
    mv->dc_state = alHeapDBAlloc(0, 0, hp, 1, sizeof(ADPCM_STATE));
    mv->dc_lstate = alHeapDBAlloc(0, 0, hp, 1, sizeof(ADPCM_STATE));
    mv->dc_dma = dmaNew(&mv->dc_dmaState);
    mv->dc_lastsam = 0;
    mv->dc_first = 1;
    mv->dc_memin = 0;

    mv->rs_state = alHeapDBAlloc(0, 0, hp, 1, sizeof(RESAMPLE_STATE));
    mv->rs_delta  = 0.0;
    mv->rs_first  = 1;
    mv->rs_ratio = 1.0;
    mv->rs_upitch = 0;

    mv->em_state = alHeapAlloc(hp, 1, sizeof(ENVMIX_STATE));
    mv->em_first = 1;
    mv->em_motion = AL_STOPPED;
    mv->em_volume = 1;
    mv->em_ltgt = 1;
    mv->em_rtgt = 1;
    mv->em_cvolL = 1;
    mv->em_cvolR = 1;
    mv->em_dryamt = 0;
    mv->em_wetamt = 0;
    mv->em_lratm = 1;
    mv->em_lratl = 0;
    mv->em_lratm = 1;
    mv->em_lratl = 0;
    mv->em_delta = 0;
    mv->em_segEnd = 0;
    mv->em_pan = 0;
    mv->em_ctrlList = 0;
    mv->em_ctrlTail = 0;
    // non-vanilla
    mv->unk99 = 0;
    mv->unkA2 = 0;
    mv->unkA0 = 0;
    mv->unkCC = alHeapDBAlloc(0, 0, hp, 1, 8);
    mv->unkC8 = 0;
}
