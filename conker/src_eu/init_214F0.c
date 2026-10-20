#include "n_synthInternals.h"

// s125: DK64 src/global_asm/audio/n_load.c (n_alAdpcmPull, n_alLoadParam, func_global_asm_80740A90), built -g
#define ADPCMFBYTES      9
#define LFSAMPLES        4
#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

Acmd *func_10021E4C(Acmd *, N_PVoice *, s32, s32, s16, s16, s32);

// n_alAdpcmPull
Acmd *func_100214F0(N_PVoice *filter, s16 *outp, s32 outCount, Acmd *p)
{
	Acmd *ptr = p;
	s16 inp;
	s32 tsam;
	s32 nframes;
	s32 nbytes;
	s32 overFlow;
	s32 startZero;
	s32 nOver;
	s32 nSam;
	s32 op;
	s32 nLeft;
	s32 bEnd;
	s32 decoded = 0;
	s32 looped = 0;

	N_PVoice *f = filter;

	if (outCount == 0) {
		return ptr;
	}

	inp = N_AL_DECODER_IN;

	if (f->dc_table == NULL) {
		aClearBuffer(ptr++, *outp, outCount << 1);
		return ptr;
	}

	if (((u32) f->dc_table->waveInfo.adpcmWave.book->book & 0x1FFFFFFF) > 0x800000) {
		aClearBuffer(ptr++, *outp, outCount << 1);
		return ptr;
	}

	aLoadADPCM(ptr++, f->dc_bookSize, ((u32) f->dc_table->waveInfo.adpcmWave.book->book & 0x1FFFFFFF));

	looped = (outCount + f->dc_sample > f->dc_loop.end) && (f->dc_loop.count != 0);

	if (looped) {
		nSam = f->dc_loop.end - f->dc_sample;
	} else {
		nSam = outCount;
	}

	if (f->dc_lastsam) {
		nLeft = ADPCMFSIZE - f->dc_lastsam;
	} else {
		nLeft = 0;
	}

	tsam = nSam - nLeft;

	if (tsam<0) {
		tsam = 0;
	}

	nframes = (tsam + ADPCMFSIZE - 1) >> LFSAMPLES;
	nbytes =  nframes*ADPCMFBYTES;

	if (looped) {
		ptr = func_10021E4C(ptr, f, tsam, nbytes, *outp, inp, f->dc_first);

		if (f->dc_lastsam) {
			*outp += (f->dc_lastsam<<1);
		} else {
			*outp += (ADPCMFSIZE<<1);
		}

		f->dc_lastsam = f->dc_loop.start &0xf;
		f->dc_memin = f->dc_table->base + ADPCMFBYTES * ((s32) (f->dc_loop.start>>LFSAMPLES) + 1);
		f->dc_sample = f->dc_loop.start;

		bEnd = *outp;

		while (outCount > nSam) {
			outCount -= nSam;

			op = (bEnd + ((nframes+1)<<(LFSAMPLES+1)) + 16) & ~0x1f;

			bEnd += (nSam<<1);

			if (f->dc_loop.count != -1 && f->dc_loop.count != 0) {
				f->dc_loop.count--;
			}

			nSam = MIN(outCount, f->dc_loop.end - f->dc_loop.start);
			tsam = nSam - ADPCMFSIZE + f->dc_lastsam;

			if (tsam < 0) {
				tsam = 0;
			}

			nframes = (tsam+ADPCMFSIZE - 1) >> LFSAMPLES;
			nbytes =  nframes*ADPCMFBYTES;
			ptr = func_10021E4C(ptr, f, tsam, nbytes, op, inp, f->dc_first | A_LOOP);

			aDMEMMove(ptr++, op + (f->dc_lastsam << 1), bEnd, nSam << 1);
		}

		f->dc_lastsam = (outCount + f->dc_lastsam) & 0xf;
		f->dc_sample += outCount;
		f->dc_memin += ADPCMFBYTES*nframes;

		return ptr;
	}

	nSam = nframes << LFSAMPLES;

	overFlow = f->dc_memin + nbytes - (s32)(f->dc_table->base + f->dc_table->len);

	if (overFlow < 0) {
		overFlow = 0;
	}

	nOver = (overFlow / ADPCMFBYTES) << LFSAMPLES;

	if (nOver > nSam + nLeft) {
		nOver = nSam + nLeft;
	}

	nbytes -= overFlow;

	if (nOver - (nOver & 0xf) < outCount) {
		decoded = 1;
		ptr = func_10021E4C(ptr, f, nSam - nOver, nbytes, *outp, inp, f->dc_first);

		if (f->dc_lastsam) {
			*outp += f->dc_lastsam << 1;
		} else {
			*outp += ADPCMFSIZE << 1;
		}

		f->dc_lastsam = (outCount + f->dc_lastsam) & 0xf;
		f->dc_sample += outCount;
		f->dc_memin += ADPCMFBYTES * nframes;
	} else {
		f->dc_lastsam = 0;
		f->dc_memin += ADPCMFBYTES * nframes;
	}

	if (nOver) {
		f->dc_lastsam = 0;

		if (decoded) {
			startZero = (nLeft + nSam - nOver) << 1;
		} else {
			startZero = 0;
		}

		aClearBuffer(ptr++, startZero + *outp, nOver << 1);
	}

	return ptr;
}

// n_alLoadParam
s32 func_10021C40(N_PVoice *a, s32 paramID, void *param)
{

	switch (paramID) {
	case (AL_FILTER_SET_WAVETABLE):
		a->dc_table = (ALWaveTable *) param;
		a->dc_memin = a->dc_table->base;
		a->dc_sample = 0;
		a->dc_table->len = ADPCMFBYTES * ((s32) (a->dc_table->len/ADPCMFBYTES));

		if (((s32) a->dc_table->waveInfo.adpcmWave.book & 0xFF000003) != 0x80000000) {
			a->dc_loop.start = a->dc_loop.end = a->dc_loop.count = 0;
			break;
		} else {
			a->dc_bookSize = 2*a->dc_table->waveInfo.adpcmWave.book->order*
				a->dc_table->waveInfo.adpcmWave.book->npredictors*ADPCMVSIZE;
		}

		if (a->dc_table->waveInfo.adpcmWave.loop) {
			a->dc_loop.start = a->dc_table->waveInfo.adpcmWave.loop->start;
			a->dc_loop.end = a->dc_table->waveInfo.adpcmWave.loop->end;
			a->dc_loop.count = a->dc_table->waveInfo.adpcmWave.loop->count;

			bcopy(a->dc_table->waveInfo.adpcmWave.loop->state, a->dc_lstate, sizeof(ADPCM_STATE));
		} else {
			a->dc_loop.start = a->dc_loop.end = a->dc_loop.count = 0;
		}
		break;
	case (AL_FILTER_RESET):
		a->dc_lastsam = 0;
		a->dc_first   = 1;
		a->dc_sample = 0;

		if (a->dc_table) {
			a->dc_memin  = a->dc_table->base;
			a->dc_loop.count = 0;
		}
		break;
	default:
		break;
	}
	return 0;
}

Acmd *func_10021E4C(Acmd *arg0, N_PVoice *arg1, s32 arg2, s32 arg3, s16 arg4, s16 arg5, s32 arg6) {
    s32 sp2C;
    s32 sp28;
    Acmd *sp24;
    Acmd *sp20;
    Acmd *sp1C;

    if (arg3 > 0) {
        sp28 = arg1->dc_dma(arg1->dc_memin, arg3, arg1->dc_dmaState);
        if (sp28 == 0) {
            arg1->em_first = 1;
            arg1->em_volume = 0;
            arg1->dc_first = 0;
            return arg0;
        }
        sp2C = sp28 & 7;
        arg3 += sp2C;
        sp24 = arg0++;
        sp24->words.w0 = ((((arg3 - (arg3 & 7)) + 8) & 0xFFF) << 0xC) | 0x04000000 | (arg5 & 0xFFF);
        sp24->words.w1 = (s32) (sp28 - sp2C);
        ;
    } else {
        sp2C = 0;
    }
    if (arg6 & 2) {
        sp20 = arg0++;
        sp20->words.w0 = 0x0F000000;
        sp20->words.w1 = (s32) ((s32) arg1->dc_lstate & 0x1FFFFFFF);
    }
    sp1C = arg0++;
    sp1C->words.w0 = ((s32) arg1->dc_state & 0x1FFFFFFF & 0xFFFFFF) | 0x01000000;
    sp1C->words.w1 = (s32) (((arg6 & 0xF) << 0x1C) | (((arg2 * 2) & 0xFFF) << 0x10) | ((sp2C & 0xF) << 0xC) | (arg4 & 0xFFF));
    arg1->dc_first = 0;
    return arg0;
}
