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

