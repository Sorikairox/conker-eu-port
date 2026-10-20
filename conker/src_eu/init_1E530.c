#include <ultra64.h>

#include "functions.h"
#include "variables.h"
// s121/s123: Rare n_audio reverb (DK64 src/global_asm/audio/n_reverb.c, built -g)
#include "synthinternal_rare.h"
#define n_alFxPull func_1001E530
#define n_alFxParamHdl func_1001ED6C
#define _n_loadOutputBuffer func_1001F28C
#define _n_loadBuffer func_1001F5A4
#define _n_saveBuffer func_1001F79C
#define _n_filterBuffer(a, b, c, d) func_1001F978((struct55 *) (a), b, c, d)
#define _doModFunc(a, b) func_1001FA78((void *) (a), b)
#define func_global_asm_8073F8A0 func_100210C0
#define _init_lpfilter init_lpfilter
#define D_global_asm_807FF0F4 D_800428C4
#define D_global_asm_807FF0F6 D_800428C6

#define RANGE 2.0f

/* DK64 N_ALAuxBus / N_ALSynth (only the fields used here) */
typedef struct {
    u8 filter[0x10]; // Conker ALFilter is 0x10 (aux bus stride 0x44)
    s32 sourceCount;
    s32 maxSources;
    void **sources;
    ALFx *fx;
    ALFx *fx_array[AL_MAX_AUX_BUS_SOURCES];
    void *unk44;
} RareAuxBus;
typedef struct {
    u8 pad0[0x48];
    RareAuxBus *auxBus;
    s32 numPVoices;
    s32 maxAuxBusses;
    s32 outputRate;
} RareSynth;
#define n_syn ((RareSynth *) D_8002BA44)

Acmd *_n_loadOutputBuffer(ALFx *r, ALDelay *d, s32 arg2, s32 buff, Acmd *p);
Acmd *_n_loadBuffer(ALFx *r, s32 arg1, s16 *curr_ptr, s32 buff,s32 count, Acmd *p);
Acmd *_n_saveBuffer(ALFx *r, s32 arg1, s16 *curr_ptr, s32 buff, Acmd *p);
Acmd *func_1001F978(struct55 *arg0, s32 arg1, s32 arg2, Acmd *p);
f32 func_1001FA78(f32 arg0[4][4], s32 arg1);
Acmd *func_global_asm_8073F8A0(s32 sampleOffset, Acmd *cmdptr, s32 fxBus, s32 *numpulls);
void init_lpfilter(ALLowPass *arg0);


Acmd *n_alFxPull(s32 sampleOffset, Acmd *p, s32 arg2)
{
	Acmd *ptr = p;
	ALFx *r = (ALFx *)n_syn->auxBus[arg2].fx;
	s16 i, buff1, buff2, input, output;
	s16 *in_ptr;
    s16 *out_ptr;
    s16 *prev_out_ptr = 0;
	ALDelay *d;
	s32 sp58 = 0;
	u32 j;

	/*
	 * pull channels going into this effect first
	 */
	ptr = func_global_asm_8073F8A0(sampleOffset, p, arg2, &sp58);

	input  = N_AL_AUX_L_OUT;
	output = N_AL_AUX_R_OUT;
	buff1  = N_AL_TEMP_0;
	buff2  = N_AL_TEMP_1;

	if (D_global_asm_807FF0F4[arg2] == 0) {
		aMix(ptr++, 0, 0xc000, N_AL_AUX_L_OUT, input);
		aMix(ptr++, 0, 0x4000, N_AL_AUX_R_OUT, input);
	}

	/* and write the mixed value to the delay line at r->input */
	ptr = _n_saveBuffer(r, 0, r->input[0], input, ptr);

	if (D_global_asm_807FF0F4[arg2]) {
		ptr = _n_saveBuffer(r, 1, r->input[1], 0x930, ptr);
	}

	for (j = 0; j <= D_global_asm_807FF0F4[arg2]; j++) {
		aClearBuffer(ptr++, output, FIXED_SAMPLE << 1); /* clear the AL_AUX_R_OUT */

		for (i = 0; i < r->section_count; i++) {
			d = &r->delay[i];  /* get the ALDelay structure */
			in_ptr = &r->input[j][-d->input];
			out_ptr = &r->input[j][-d->output];

			if (D_global_asm_807FF0F6[arg2] && D_global_asm_807FF0F4[arg2]) {
				d->ffcoef = -d->ffcoef;
				d->fbcoef = -d->fbcoef;
			}

			if (in_ptr == prev_out_ptr) {
				s16 t = buff2;
				buff2 = buff1;
				buff1 = t;
			} else {  /* load data at in_ptr into buff1 */
				ptr = _n_loadBuffer(r, j, in_ptr, buff1, FIXED_SAMPLE, ptr);
			}

			ptr = _n_loadOutputBuffer(r, d, j, buff2, ptr);

			if (d->ffcoef) {
				aMix(ptr++, 0, (u16)d->ffcoef, buff1, buff2);

				if (!d->rs && !d->lp) {
					ptr = _n_saveBuffer(r, j, out_ptr, buff2, ptr);
				}
			}

			if (d->fbcoef) {
				aMix(ptr++, 0, (u16)d->fbcoef, buff2, buff1);
				ptr = _n_saveBuffer(r, j, in_ptr, buff1, ptr);
			}

			if (d->lp) {
				ptr = _n_filterBuffer(d->lp, j, buff2, ptr);
			}

			if (!d->rs) {
				ptr = _n_saveBuffer(r, j, out_ptr, buff2, ptr);
			}

			if (d->gain) {
				if (D_global_asm_807FF0F4[arg2]) {
					aMix(ptr++, 0, (u16)d->gain, buff2, output);
				} else {
					u32 sp34 = d->gain * 1.4141999483109f;

					if (sp34 > 0x7fff) {
						sp34 = 0x7fff;
					}

					aMix(ptr++, 0, (u16)sp34, buff2, output);
				}
			}

			prev_out_ptr = &r->input[j][d->output];
		}

		if (D_global_asm_807FF0F4[arg2] && j == 0) {
			ptr = _n_loadBuffer(r, 1, r->input[1], input, FIXED_SAMPLE, ptr);

			if (D_global_asm_807FF0F6[arg2]) {
				aMix(ptr++, 0, 0x5a82, output, 0x650);
			} else {
				aMix(ptr++, 0, 0x5a82, output, 0x4e0);
			}
		} else {
			// empty
		}

		/*
		 * output already in AL_AUX_R_OUT
		 *      just copy to AL_AUX_L_OUT
		 */
		aDMEMMove(ptr++, output, N_AL_AUX_L_OUT, FIXED_SAMPLE << 1);

		/*
		 * bump the master delay line input pointer
		 * modulo the length
		 */
		r->input[j] += FIXED_SAMPLE;

		if (r->input[j] > &r->base[j][r->length]) {
			r->input[j] -= r->length;
		}
	}

	return ptr;
}

s32 n_alFxParamHdl(void *filter, s32 paramID, void *param)
{
	ALFx *f = (ALFx *) filter;
	s32 p = paramID & 7;
	s32 s = paramID >> 3;
	s32 val = *(s32*)param;
	f32 rsgain;

	if (s >= f->section_count) {
		return 0;
	}

#define INPUT_PARAM         0
#define OUTPUT_PARAM        1
#define FBCOEF_PARAM        2
#define FFCOEF_PARAM        3
#define GAIN_PARAM          4
#define CHORUSRATE_PARAM    5
#define CHORUSDEPTH_PARAM   6
#define LPFILT_PARAM        7

	switch (p) {
	case INPUT_PARAM:
		f->delay[s].input = ((s32)val * n_syn->outputRate / 1000) & 0xfffffff8;
		break;
	case OUTPUT_PARAM:
		f->delay[s].output = ((s32)val * n_syn->outputRate / 1000) & 0xfffffff8;
		break;
	case FBCOEF_PARAM:
		f->delay[s].fbcoef = (s16)val;
		break;
	case FFCOEF_PARAM:
		f->delay[s].ffcoef = (s16)val;
		break;
	case GAIN_PARAM:
		f->delay[s].gain = (s16)val;
		break;
	case CHORUSRATE_PARAM:
		f->delay[s].rsinc = ((((f32)val)/1000) * RANGE)/n_syn->outputRate;
		break;
	case CHORUSDEPTH_PARAM:
		rsgain = val;
		break;
	case LPFILT_PARAM:
		if (f->delay[s].lp) {
			f->delay[s].lp->fc = (s16)val;
			_init_lpfilter(f->delay[s].lp);
		}
		break;
	}

	if (f->delay[s].input >= f->length - 16) {
		f->delay[s].input = f->length - 16;
	}

	if (f->delay[s].input >= f->length - 8) {
		f->delay[s].input = f->length - 8;
	}

	if (f->delay[s].input >= f->delay[s].output) {
		f->delay[s].output = f->delay[s].input + 8;
	}

	/**
	 * the following constant is derived from:
	 *
	 *      ratio = 2^(cents/1200)
	 *
	 * and therefore for hundredths of a cent
	 *                     x
	 *      ln(ratio) = ---------------
	 *              (120,000)/ln(2)
	 * where
	 *      120,000/ln(2) = 173123.40...
	 */
#define CONVERT 173123.404906676f
#define LENGTH  (f->delay[s].output - f->delay[s].input)

	if (f->delay[s].rs) {
		if (p != 6) {
			if (LENGTH != 0) {
				rsgain = (f32)f->delay[s].rsgain / (f->delay[s].output - f->delay[s].input) * CONVERT;
			} else {
				rsgain = 0;
			}
		}

		f->delay[s].rsgain = (f->delay[s].output - f->delay[s].input) * (rsgain / CONVERT);
	}

	return 0;
}


Acmd *_n_loadOutputBuffer(ALFx *r, ALDelay *d, s32 arg2, s32 buff, Acmd *p)
{
	Acmd *ptr = p;
	s32 ratio, count, rbuff = N_AL_TEMP_2;
	s16 *out_ptr;
	f32 fincount, fratio, delta;
	s32 ramalign = 0, length;
	s32 incount = FIXED_SAMPLE;
	s16 tmp;

	if (d->rs) {
		length = d->output - d->input;
		delta = _doModFunc(d, incount);
		delta /= length;
		delta = (s32)(delta * UNITY_PITCH);
		delta = delta / UNITY_PITCH;
		fratio = 1.0f - delta;
		fincount = d->rs->delta + (fratio * (f32)incount);
		count = (s32) fincount;
		d->rs->delta = fincount - (f32)count;
		out_ptr = &r->input[arg2][(s32)-(d->output - d->rsdelta)];
		ramalign = ((s32)out_ptr & 0x7) >> 1;
		ptr = _n_loadBuffer(r, arg2, out_ptr - ramalign, rbuff, count + ramalign, ptr);

		ratio = (s32)(fratio * UNITY_PITCH);

		tmp = buff >> 8;
		n_aResample(ptr++, osVirtualToPhysical(d->rs->state[arg2]), d->rs->first, ratio, rbuff + (ramalign << 1), tmp);

		d->rs->first = 0;
		d->rsdelta += count - incount;
	} else {
		out_ptr = &r->input[arg2][(s32)-d->output];
		ptr = _n_loadBuffer(r, arg2, out_ptr, buff, FIXED_SAMPLE, ptr);
	}

	return ptr;
}

Acmd *_n_loadBuffer(ALFx *r, s32 arg1, s16 *curr_ptr, s32 buff,s32 count, Acmd *p)
{
	Acmd *ptr = p;
	s32 after_end, before_end;
	s16 *updated_ptr, *delay_end;

	delay_end = &r->base[arg1][r->length];

	if (curr_ptr < r->base[arg1]) {
		curr_ptr += r->length;
	}

	updated_ptr = curr_ptr + count;

	if (updated_ptr > delay_end) {
		after_end = updated_ptr - delay_end;
		before_end = delay_end - curr_ptr;

		n_aLoadBuffer(ptr++, before_end << 1, buff, osVirtualToPhysical(curr_ptr));
		n_aLoadBuffer(ptr++, after_end << 1, buff + (before_end << 1), osVirtualToPhysical(r->base[arg1]));
	} else {
		n_aLoadBuffer(ptr++, count << 1, buff, osVirtualToPhysical(curr_ptr));
	}

	return ptr;
}
Acmd *_n_saveBuffer(ALFx *arg0, s32 arg1, s16 *arg2, s32 arg3, Acmd *arg4) {
    Acmd *sp34;
    s32 sp30;
    s32 sp2C;
    u32 sp28;
    u32 sp24;
    Acmd *sp20;
    Acmd *sp1C;
    Acmd *sp18;

    sp34 = arg4;
    sp24 = &arg0->base[arg1][arg0->length];
    if ((u32)arg2 < (u32)arg0->base[arg1]) {
        arg2 += arg0->length;
    }
    sp28 = &arg2[184];
    if (sp28 > sp24) {
        sp30 = (s32) (sp28 - sp24) >> 1;
        sp2C = (s32) (sp24 - (s32)arg2) >> 1;
        sp20 = sp34++;
        sp20->words.w0 = (((sp2C * 2) & 0xFFF) << 0xC) | 0x06000000 | (arg3 & 0xFFF);
        sp20->words.w1 = osVirtualToPhysical((void *) arg2);
        sp1C = sp34++;
        sp1C->words.w0 = (((sp30 * 2) & 0xFFF) << 0xC) | 0x06000000 | ((arg3 + (sp2C * 2)) & 0xFFF);
        sp1C->words.w1 = osVirtualToPhysical(arg0->base[arg1]);
        if (1) {}
    } else {
        sp18 = sp34++;
        sp18->words.w0 = (arg3 & 0xFFF) | 0x06170000;
        sp18->words.w1 = osVirtualToPhysical((void *) arg2);
    }
    return sp34;
}

// void *func_1001F79C(void *arg0, s32 arg1, u32 arg2, s32 arg3, void *arg4) {
//     void *sp34;
//     s32 sp30;
//     s32 sp2C;
//     u32 sp28;
//     u32 sp24;
//     void *sp20;
//     void *sp1C;
//     void *sp18;
//     void *temp_t0;
//     void *temp_t7;
//     void *temp_t7_2;
//
//     sp34 = arg4;
//     sp24 = (arg0 + (arg1 * 4))->unk20 + (*arg0 * 2);
//     if (arg2 < (u32) (arg0 + (arg1 * 4))->unk20) {
//         arg2 = arg2 + (*arg0 * 2);
//     }
//     sp28 = arg2 + 0x170;
//     if (sp24 < sp28) {
//         sp30 = (s32) (sp28 - sp24) >> 1;
//         sp2C = (s32) (sp24 - arg2) >> 1;
//         temp_t0 = sp34;
//         sp34 = temp_t0 + 8;
//         sp20 = temp_t0;
//         *temp_t0 = (s32) ((((sp2C * 2) & 0xFFF) << 0xC) | 0x6000000 | (arg3 & 0xFFF));
//         sp20->unk4 = osVirtualToPhysical(arg2);
//         temp_t7 = sp34;
//         sp34 = temp_t7 + 8;
//         sp1C = temp_t7;
//         sp1C->unk0 = (s32) ((((sp30 * 2) & 0xFFF) << 0xC) | 0x6000000 | ((arg3 + (sp2C * 2)) & 0xFFF));
//         sp1C->unk4 = osVirtualToPhysical((arg0 + (arg1 * 4))->unk20);
//     } else {
//         temp_t7_2 = sp34;
//         sp34 = temp_t7_2 + 8;
//         sp18 = temp_t7_2;
//         sp18->unk0 = (s32) ((arg3 & 0xFFF) | 0x6170000);
//         sp18->unk4 = osVirtualToPhysical(arg2);
//     }
//     return sp34;
// }

Acmd *func_1001F978(struct55 *arg0, s32 arg1, s32 arg2, Acmd *p) {
    Acmd *ptr = p;
    s16 tmp = arg2 >> 8;

    aLoadADPCM(ptr++, 32, osVirtualToPhysical(&arg0->unk8));
    aPoleFilter(ptr++, arg0->unk28, arg0->unk2, (osVirtualToPhysical(((s32 **)&arg0->unk2C)[arg1]) & 0xFFFFFF) | ((tmp & 0xFF) << 24));
    arg0->unk28 = 0;
    return ptr;
}

f32 func_1001FA78(f32 arg0[4][4], s32 arg1) {
    f32 tmp;

    arg0[1][1] += arg0[1][0] * arg1;
    if (arg0[1][1] > 2.0f) {
        arg0[1][1] -= 4.0f;
    }
    else {
        arg0[1][1] = arg0[1][1]; // ???
    }

    tmp = arg0[1][1];
    tmp = tmp < 0.0f ? -tmp : tmp;
    tmp = tmp - 1.0f;

    return tmp * arg0[1][3];
}
