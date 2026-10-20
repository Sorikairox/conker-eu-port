#include "synthinternal_rare.h"
#ifndef N_AL_TEMP_2
#define N_AL_TEMP_1 368
#define N_AL_TEMP_2 736
#endif
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

