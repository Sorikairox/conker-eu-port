#include "synthinternal_rare.h"
#define _n_loadOutputBuffer func_1001F28C
#define _n_loadBuffer func_1001F5A4
#define _n_saveBuffer func_1001F79C
#define _n_filterBuffer(a, b, c, d) func_1001F978((struct55 *) (a), b, c, d)
#define _doModFunc(a, b) func_1001FA78((void *) (a), b)
#define func_global_asm_8073F8A0 func_100210C0
#define D_global_asm_807FF0F4 D_800428C4
#define D_global_asm_807FF0F6 D_800428C6
Acmd *_n_loadOutputBuffer(ALFx *r, ALDelay *d, s32 arg2, s32 buff, Acmd *p);
Acmd *_n_loadBuffer(ALFx *r, s32 arg1, s16 *curr_ptr, s32 buff,s32 count, Acmd *p);
Acmd *_n_saveBuffer(ALFx *r, s32 arg1, s16 *curr_ptr, s32 buff, Acmd *p);
Acmd *func_global_asm_8073F8A0(s32 sampleOffset, Acmd *cmdptr, s32 fxBus, s32 *numpulls);
extern u8 D_global_asm_807FF0F4[];
extern u8 D_global_asm_807FF0F6[];
Acmd *n_alFxPull(s32 sampleOffset, Acmd *p, s32 arg2)
{
	Acmd *ptr = p;
	ALFx *r = (ALFx *)n_syn->auxBus[arg2].fx;
	s16 i, buff1, buff2, input, output;
	s16 *in_ptr;
    s16 *out_ptr;
    s32 pad;
    s16 *prev_out_ptr = 0;
	ALDelay *d;
    s32 pad1;
	s32 sp58 = 1;
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

