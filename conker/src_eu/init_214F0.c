#include "n_synthInternals.h"

// s125: DK64 src/global_asm/audio/n_load.c (n_alAdpcmPull, n_alLoadParam, func_global_asm_80740A90), built -g
#define ADPCMFBYTES      9
#define LFSAMPLES        4
#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

Acmd *n_adpcm_decode_chunk(Acmd *, N_PVoice *, s32, s32, s16, s16, s32);

// n_alAdpcmPull
/* was func_100214F0 */
Acmd *n_adpcm_pull(N_PVoice *filter, s16 *outp, s32 outCount, Acmd *p)
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

#ifdef PORT
	/* P353: K0_TO_PHYS of a heap pointer: its N64 physical address (osVirtualToPhysical, pc_os.c); the mask kept the
	 * wasm address, a value that depended on where the build placed the n64_rdram mirror */
	aLoadADPCM(ptr++, f->dc_bookSize, osVirtualToPhysical(f->dc_table->waveInfo.adpcmWave.book->book));
#else
	aLoadADPCM(ptr++, f->dc_bookSize, ((u32) f->dc_table->waveInfo.adpcmWave.book->book & 0x1FFFFFFF));
#endif

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
		ptr = n_adpcm_decode_chunk(ptr, f, tsam, nbytes, *outp, inp, f->dc_first);

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
			ptr = n_adpcm_decode_chunk(ptr, f, tsam, nbytes, op, inp, f->dc_first | A_LOOP);

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
		ptr = n_adpcm_decode_chunk(ptr, f, nSam - nOver, nbytes, *outp, inp, f->dc_first);

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
/* was func_10021C40 */
s32 n_adpcm_load_param(N_PVoice *a, s32 paramID, void *param)
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

/* was func_10021E4C; locals renamed in P353 (were sp1C..sp2C, arg0..arg6) */
Acmd *n_adpcm_decode_chunk(Acmd *cmd, N_PVoice *pv, s32 nsam, s32 nbytes, s16 dmem_out, s16 dmem_in, s32 flags) {
    s32 misalign;
    s32 dma_addr;
    Acmd *cmd_load;
    Acmd *cmd_loop;
    Acmd *cmd_adpcm;

    if (nbytes > 0) {
        dma_addr = pv->dc_dma(pv->dc_memin, nbytes, pv->dc_dmaState);
        if (dma_addr == 0) {
            pv->em_first = 1;
            pv->em_volume = 0;
            pv->dc_first = 0;
            return cmd;
        }
        misalign = dma_addr & 7;
        nbytes += misalign;
        cmd_load = cmd++;
        cmd_load->words.w0 = ((((nbytes - (nbytes & 7)) + 8) & 0xFFF) << 0xC) | 0x04000000 | (dmem_in & 0xFFF);
        cmd_load->words.w1 = (s32) (dma_addr - misalign);
        ;
    } else {
        misalign = 0;
    }
    if (flags & 2) {
        cmd_loop = cmd++;
        cmd_loop->words.w0 = 0x0F000000;
#ifdef PORT
        cmd_loop->words.w1 = (s32) osVirtualToPhysical(pv->dc_lstate);   /* P353: K0_TO_PHYS = N64 physical */
#else
        cmd_loop->words.w1 = (s32) ((s32) pv->dc_lstate & 0x1FFFFFFF);
#endif
    }
    cmd_adpcm = cmd++;
#ifdef PORT
    cmd_adpcm->words.w0 = (osVirtualToPhysical(pv->dc_state) & 0xFFFFFF) | 0x01000000;   /* P353: K0_TO_PHYS = N64 physical */
#else
    cmd_adpcm->words.w0 = ((s32) pv->dc_state & 0x1FFFFFFF & 0xFFFFFF) | 0x01000000;
#endif
    cmd_adpcm->words.w1 = (s32) (((flags & 0xF) << 0x1C) | (((nsam * 2) & 0xFFF) << 0x10) | ((misalign & 0xF) << 0xC) | (dmem_out & 0xFFF));
    pv->dc_first = 0;
    return cmd;
}
