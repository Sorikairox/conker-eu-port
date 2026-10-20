#include <ultra64.h>

#include "functions.h"
#include "variables.h"

// MP3-style stream decoder state (game_221290). Needs OPT_FLAGS := -g.
typedef struct struct_eu_221290 {
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ s32 (*unk4)(s32, u8 *, s32, s32);
    /* 0x0008 */ s32 unk8;
    /* 0x000C */ s32 unkC;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001C */ u8 unk1C[0x2000];
    /* 0x201C */ s32 unk201C;
    /* 0x2020 */ s32 unk2020;
    /* 0x2024 */ u8 pad2024[0x2070 - 0x2024];
    /* 0x2070 */ u8 unk2070[6][0x488];
    /* 0x3BA0 */ s32 unk3BA0;
    /* 0x3BA4 */ s32 unk3BA4;
    /* 0x3BA8 */ u8 pad3BA8[0x3BB4 - 0x3BA8];
    /* 0x3BB4 */ s32 unk3BB4;
    /* 0x3BB8 */ u8 pad3BB8[0x3BC8 - 0x3BB8];
    /* 0x3BC8 */ s32 unk3BC8;
    /* 0x3BCC */ u8 pad3BCC[0x3C98 - 0x3BCC];
    /* 0x3C98 */ s32 unk3C98[2];
    /* 0x3CA0 */ s32 unk3CA0[2];
    /* 0x3CA8 */ s32 unk3CA8[2];
    /* 0x3CB0 */ u8 pad3CB0[0x3F88 - 0x3CB0];
    /* 0x3F88 */ s32 unk3F88;
    /* 0x3F8C */ s32 unk3F8C;
    /* 0x3F90 */ u8 pad3F90[0x4664 - 0x3F90];
    /* 0x4664 */ f32 unk4664[576];
    /* 0x4F64 */ f32 unk4F64[576];
    /* 0x5864 */ u8 pad5864[0x6A64 - 0x5864];
    /* 0x6A64 */ u8 unk6A64[0x900];
    /* 0x7364 */ u8 pad7364[0x8474 - 0x7364];
    /* 0x8474 */ s32 unk8474;
    /* 0x8478 */ s32 (*unk8478)(struct struct_eu_221290 *);
} struct_eu_221290;

extern struct_eu_221290 D_800E1CB0;
extern s16 D_800AEF8C[][3][576];
extern s32 D_800E0E04;
extern void (*D_800E1230)(s32, u8 *, s32);

/* Perfect Dark src/lib/mp3/mp3.h layout (same offsets) */
struct asistream_scalefac {
	/*0x3d08*/ u32 l[22];
	/*0x3d60*/ u32 unk3d60;
	/*0x3d64*/ u32 s[3][13];
};
struct asistream_4f64 {
	f32 unk00[18];
};
struct asistream {
	/*0x0000*/ s32 unk00;
	/*0x0004*/ s32 (*dmafunc)(s32 arg0, void *arg1, s32 arg2, s32 arg3);
	/*0x0008*/ s32 filesize;
	/*0x000c*/ s32 unk0c;
	/*0x0010*/ s32 unk10;
	/*0x0014*/ s32 unk14;
	/*0x0018*/ s32 unk18;
	/*0x2000*/ u8 unk1c[0x2000];
	/*0x201c*/ s32 unk201c;
	/*0x2020*/ s32 unk2020;
	/*0x2024*/ u8 buffer[0x40];
	/*0x2064*/ s32 offset;
	/*0x2068*/ u32 unk2068;
	/*0x206c*/ u32 unk206c;
	/*0x2070*/ u16 unk2070[6][580];
	/*0x3ba0*/ s32 unk3ba0;
	/*0x3ba4*/ u32 version;
	/*0x3ba8*/ u32 layer;
	/*0x3bac*/ u32 crctype;
	/*0x3bb0*/ u32 bitrateindex;
	/*0x3bb4*/ u32 samplerateindex;
	/*0x3bb8*/ u32 haspadding;
	/*0x3bbc*/ u32 privatebit;
	/*0x3bc0*/ u32 channelmode;
	/*0x3bc4*/ u32 channelmodeext;
	/*0x3bc8*/ u32 copyright;
	/*0x3bcc*/ u32 isoriginal;
	/*0x3bd0*/ u32 emphasis;
	/*0x3bd4*/ s32 doneinitial;
	/*0x3bd8*/ u32 initialversion;
	/*0x3bdc*/ u32 initiallayer;
	/*0x3be0*/ u32 initialcrctype;
	/*0x3be4*/ u32 initialsamplerateindex;
	/*0x3be8*/ u32 initialchannelmode;
	/*0x3bec*/ u32 initialcopyright;
	/*0x3bf0*/ u32 initialisoriginal;
	/*0x3bf4*/ u32 main_data_begin;
	/*0x3bf8*/ u32 scfsi[1][32];
	/*0x3c78*/ u32 part2_3_length[2][1];
	/*0x3c80*/ u32 big_value[2][1];
	/*0x3c88*/ s32 global_gain[2][1];
	/*0x3c90*/ u32 scalefac_compress[2][1];
	/*0x3c98*/ u32 window_switching[2][1];
	/*0x3ca0*/ u32 block_type[2][1];
	/*0x3ca8*/ u32 mixed_block_flag[2][1];
	/*0x3cb0*/ u32 table_select[2][1][3];
	/*0x3cc8*/ u32 subblock_gain[2][1][3];
	/*0x3ce0*/ u32 region0_count[2][1];
	/*0x3ce8*/ u32 region1_count[2][1];
	/*0x3cf0*/ u32 preflag[2][1];
	/*0x3cf8*/ u32 scalefac_scale[2][1];
	/*0x3d00*/ u32 count1table_select[2][1];
	struct asistream_scalefac scalefac[2][1];
	/*0x3ef8*/ u32 unk3ef8;
	/*0x3efc*/ u32 unk3efc[6];
	/*0x3f14*/ u32 unk3f14[26];
	/*0x3f7c*/ s32 bitrate;
	/*0x3f80*/ s32 samplerate;
	/*0x3f84*/ s32 unk3f84;
	/*0x3f88*/ s32 unk3f88;
	/*0x3f8c*/ s32 numchannels;
	/*0x3f90*/ s32 numgranules;
	/*0x3f94*/ s16 unk3f94[1][578];
	/*0x4418*/ u8 unk4418[1][578];
	/*0x465c*/ s32 unk465c[1];
	/*0x4660*/ s32 unk4660[1];
	/*0x4664*/ struct asistream_4f64 unk4664[1][32];
	/*0x4f64*/ struct asistream_4f64 unk4f64[2][32];
	/*0x6164*/ u8 unk6164[0x900];
	/*0x6a64*/ struct asistream_4f64 unk6a64[2][32];
	/*0x7c64*/ u8 unk7c64[0x810];
	/*0x8474*/ s32 unk8474;
	/*0x8478*/ s32 (*decodeframefunc)(struct asistream *stream);
	/*0x847c*/ s32 (*setsideinfofunc)(struct asistream *stream);
};

extern f32 D_800B0A8C[8];
extern f32 D_800B0AAC[8];

#define CHANNELMODE_STEREO      0
#define CHANNELMODE_JOINTSTEREO 1
#define CHANNELMODE_DUALMONO    2
#define CHANNELMODE_SINGLEMONO  3

#define VERSION_2 0x0
#define VERSION_1 0x1

#define LAYER_3 1
#define LAYER_2 2
#define LAYER_1 3

#define CRC_PROTECTED   0
#define CRC_UNPROTECTED 1

struct mp3decfourbytes {
	u8 bytes[2];
	s8 unk02;
	s8 unk03;
};

s32 func_151F8088(struct asistream *stream, s32 arg1); /* mp3main_read_frame */
s32 func_151F78B4(struct asistream *stream); /* mp3dec_decode_frame */
s32 func_151F9150(u8 *buffer, s32 *offset, s32 numbits); /* mp3util_get_bits */

extern const u8 D_800AEF64[];          /* var70057b74 */
extern const u8 D_800AEF6C[2][16];     /* var70057b7c */
extern const u32 D_800B0ACC[2][15];    /* g_BitRateTable */
extern const u32 D_800B0B44[2][4];     /* g_SampleRateTable */




#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F3DE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F42E8.s")
/* mp3dec_unpack_scale_fac (Perfect Dark src/lib/mp3/decoder.c) */
s32 func_151F4F38(struct asistream *stream, u32 gr, u32 ch)
{
	s32 i;
	s32 sfb;
	s32 window;

	if (stream->window_switching[gr][ch] != 0 && stream->block_type[gr][ch] == 2) {
		if (stream->mixed_block_flag[gr][ch] != 0) {
			for (sfb = 0; sfb < 8; sfb++) {
				stream->scalefac[gr][ch].l[sfb] =
					D_800AEF6C[0][stream->scalefac_compress[gr][ch]]
					? func_151F9150(stream->unk1c, &stream->unk2020, D_800AEF6C[0][stream->scalefac_compress[gr][ch]])
					: 0;
			}

			for (sfb = 3; sfb < 6; sfb++) {
				for (window = 0; window < 3; window++) {
					stream->scalefac[gr][ch].s[window][sfb] =
						D_800AEF6C[0][stream->scalefac_compress[gr][ch]]
						? func_151F9150(stream->unk1c, &stream->unk2020, D_800AEF6C[0][stream->scalefac_compress[gr][ch]])
						: 0;
				}
			}

			for (sfb = 6; sfb < 12; sfb++) {
				for (window = 0; window < 3; window++) {
					stream->scalefac[gr][ch].s[window][sfb] =
						D_800AEF6C[1][stream->scalefac_compress[gr][ch]]
						? func_151F9150(stream->unk1c, &stream->unk2020, D_800AEF6C[1][stream->scalefac_compress[gr][ch]])
						: 0;
				}
			}
		} else {
			for (i = 0; i < 2; i++) {
				for (sfb = D_800AEF64[5 + i]; sfb < D_800AEF64[6 + i]; sfb++) {
					for (window = 0; window < 3; window++) {
						stream->scalefac[gr][ch].s[window][sfb] =
							D_800AEF6C[i][stream->scalefac_compress[gr][ch]]
							? func_151F9150(stream->unk1c, &stream->unk2020, D_800AEF6C[i][stream->scalefac_compress[gr][ch]])
							: 0;
					}
				}
			}
		}

		for (window = 0; window < 3; window++) {
			stream->scalefac[gr][ch].s[window][12] = 0;
		}
	} else {
		for (i = 0; i < 4; i++) {
			if (stream->scfsi[ch][i] == 0 || gr == 0) {
				for (sfb = D_800AEF64[i]; sfb < D_800AEF64[i + 1]; sfb++) {
					stream->scalefac[gr][ch].l[sfb] =
						D_800AEF6C[i < 2 ? 0 : 1][stream->scalefac_compress[gr][ch]]
						? func_151F9150(stream->unk1c, &stream->unk2020, D_800AEF6C[i < 2 ? 0 : 1][stream->scalefac_compress[gr][ch]])
						: 0;
				}
			} else {
				for (sfb = D_800AEF64[i]; sfb < D_800AEF64[1 + i]; sfb++) {
					stream->scalefac[1][ch].l[sfb] = stream->scalefac[0][ch].l[sfb];
				}
			}
		}

		stream->scalefac[gr][ch].unk3d60 = 0;
	}

	return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F578C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F63C4.s")
s32 func_151F6970(struct_eu_221290 *arg0, s32 ch) {
    s16 *table;
    f32 *dst;
    f32 *src;
    s32 i;

    table = D_800AEF8C[arg0->unk3BA4][arg0->unk3BB4];
    dst = arg0->unk4F64;
    src = arg0->unk4664;
    i = 0;
    if ((arg0->unk3C98[ch] != 0) && (arg0->unk3CA0[ch] == 2)) {
        if (arg0->unk3CA8[ch] != 0) {
            while (i++ < 36) {
                *dst++ = *src++;
            }
        }
        while (i < 576) {
            dst[table[i++]] = *src++;
        }
    } else {
        while (i++ < 576) {
            *dst++ = *src++;
        }
    }
    return 1;
}
/* mp3dec_reduce_aliases */
s32 func_151F6B28(struct asistream *stream, u32 gr, u32 ch)
{
	s32 i;

	if (stream->window_switching[gr][ch] && stream->block_type[gr][ch] == 2) {
		return 1;
	}

	for (i = 1; i < 32; i++) {
		struct asistream_4f64 *sp08 = &stream->unk4f64[ch][i];
		f32 sp04;
		f32 sp00;

		sp04 = sp08->unk00[0];
		sp00 = sp08->unk00[-1];
		sp08->unk00[-1] = sp00 * D_800B0AAC[0] - D_800B0A8C[0] * sp04;
		sp08->unk00[0] = sp04 * D_800B0AAC[0] + D_800B0A8C[0] * sp00;

		sp04 = sp08->unk00[1];
		sp00 = sp08->unk00[-2];
		sp08->unk00[-2] = sp00 * D_800B0AAC[1] - D_800B0A8C[1] * sp04;
		sp08->unk00[1] = sp04 * D_800B0AAC[1] + D_800B0A8C[1] * sp00;

		sp04 = sp08->unk00[2];
		sp00 = sp08->unk00[-3];
		sp08->unk00[-3] = sp00 * D_800B0AAC[2] - D_800B0A8C[2] * sp04;
		sp08->unk00[2] = sp04 * D_800B0AAC[2] + D_800B0A8C[2] * sp00;

		sp04 = sp08->unk00[3];
		sp00 = sp08->unk00[-4];
		sp08->unk00[-4] = sp00 * D_800B0AAC[3] - D_800B0A8C[3] * sp04;
		sp08->unk00[3] = sp04 * D_800B0AAC[3] + D_800B0A8C[3] * sp00;

		sp04 = sp08->unk00[4];
		sp00 = sp08->unk00[-5];
		sp08->unk00[-5] = sp00 * D_800B0AAC[4] - D_800B0A8C[4] * sp04;
		sp08->unk00[4] = sp04 * D_800B0AAC[4] + D_800B0A8C[4] * sp00;

		sp04 = sp08->unk00[5];
		sp00 = sp08->unk00[-6];
		sp08->unk00[-6] = sp00 * D_800B0AAC[5] - D_800B0A8C[5] * sp04;
		sp08->unk00[5] = sp04 * D_800B0AAC[5] + D_800B0A8C[5] * sp00;

		sp04 = sp08->unk00[6];
		sp00 = sp08->unk00[-7];
		sp08->unk00[-7] = sp00 * D_800B0AAC[6] - D_800B0A8C[6] * sp04;
		sp08->unk00[6] = sp04 * D_800B0AAC[6] + D_800B0A8C[6] * sp00;

		sp04 = sp08->unk00[7];
		sp00 = sp08->unk00[-8];
		sp08->unk00[-8] = sp00 * D_800B0AAC[7] - D_800B0A8C[7] * sp04;
		sp08->unk00[7] = sp04 * D_800B0AAC[7] + D_800B0A8C[7] * sp00;
	}

	return 1;
}
/* mp3dec_set_side_info (Perfect Dark src/lib/mp3/decoder.c) */
s32 func_151F6FD0(struct asistream *stream)
{
	s32 sp34;
	s32 ch;
	s32 scfsi_band;
	s32 sp28;
	s32 gr;
	s32 region;
	s32 window;

	if (stream->version != VERSION_2) {
		stream->unk206c = stream->channelmode == CHANNELMODE_SINGLEMONO ? 17 : 32;
	} else {
		stream->unk206c = stream->channelmode == CHANNELMODE_SINGLEMONO ? 9 : 17;
	}

	sp34 = stream->dmafunc(stream->unk00, &stream->buffer[stream->unk2068], stream->unk206c, -1);

	if (stream->unk206c != sp34) {
		return 0;
	}

	stream->unk18 += stream->unk206c;

	stream->numchannels = stream->channelmode == CHANNELMODE_SINGLEMONO ? 1 : 2;
	stream->numgranules = stream->version != VERSION_2 ? 2 : 1;

	if (stream->version != VERSION_2) {
		stream->main_data_begin = func_151F9150(stream->buffer, &stream->offset, 9);

		// skip private bits
		stream->numchannels == 1
			? func_151F9150(stream->buffer, &stream->offset, 5)
			: func_151F9150(stream->buffer, &stream->offset, 3);
	} else {
		stream->main_data_begin = func_151F9150(stream->buffer, &stream->offset, 8);

		stream->numchannels == 1
			? func_151F9150(stream->buffer, &stream->offset, 1)
			: func_151F9150(stream->buffer, &stream->offset, 2);
	}

	if (stream->version != VERSION_2) {
		for (ch = 0; ch < stream->numchannels; ch++) {
			for (scfsi_band = 0; scfsi_band < 4; scfsi_band++) {
				stream->scfsi[ch][scfsi_band] = func_151F9150(stream->buffer, &stream->offset, 1);
			}
		}
	}

	if (stream->version != VERSION_2) {
		sp28 = 4;
	} else {
		sp28 = 9;
	}

	for (gr = 0; gr < stream->numgranules; gr++) {
		for (ch = 0; ch < stream->numchannels; ch++) {
			stream->part2_3_length[gr][ch] = func_151F9150(stream->buffer, &stream->offset, 12);
			stream->big_value[gr][ch] = func_151F9150(stream->buffer, &stream->offset, 9);
			stream->global_gain[gr][ch] = func_151F9150(stream->buffer, &stream->offset, 8);
			stream->scalefac_compress[gr][ch] = sp28 ? func_151F9150(stream->buffer, &stream->offset, sp28) : 0;
			stream->window_switching[gr][ch] = func_151F9150(stream->buffer, &stream->offset, 1);

			if (stream->window_switching[gr][ch]) {
				stream->block_type[gr][ch] = func_151F9150(stream->buffer, &stream->offset, 2);
				stream->mixed_block_flag[gr][ch] = func_151F9150(stream->buffer, &stream->offset, 1);

				for (region = 0; region < 2; region++) {
					stream->table_select[gr][ch][region] = func_151F9150(stream->buffer, &stream->offset, 5);
				}

				stream->table_select[gr][ch][2] = 0;

				for (window = 0; window < 3; window++) {
					stream->subblock_gain[gr][ch][window] = func_151F9150(stream->buffer, &stream->offset, 3);
				}
			} else {
				stream->block_type[gr][ch] = 0;
				stream->mixed_block_flag[gr][ch] = 0;

				for (region = 0; region < 3; region++) {
					stream->table_select[gr][ch][region] = func_151F9150(stream->buffer, &stream->offset, 5);
				}

				stream->region0_count[gr][ch] = func_151F9150(stream->buffer, &stream->offset, 4);
				stream->region1_count[gr][ch] = func_151F9150(stream->buffer, &stream->offset, 3);
			}

			if (stream->version != VERSION_2) {
				stream->preflag[gr][ch] = func_151F9150(stream->buffer, &stream->offset, 1);
			}

			stream->scalefac_scale[gr][ch] = func_151F9150(stream->buffer, &stream->offset, 1);
			stream->count1table_select[gr][ch] = func_151F9150(stream->buffer, &stream->offset, 1);
		}
	}

	stream->bitrate = D_800B0ACC[stream->version][stream->bitrateindex];
	stream->samplerate = D_800B0B44[stream->version][stream->samplerateindex];

	if (stream->version != VERSION_2) {
		stream->unk3f84 = stream->bitrate * 144 / stream->samplerate;
	} else {
		stream->unk3f84 = stream->bitrate * 72 / stream->samplerate;
	}

	stream->unk3f88 = (stream->unk3f84 + stream->haspadding) - (stream->unk2068 + stream->unk206c);

	return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F78B4.s")
s32 func_151F7F60(struct_eu_221290 *arg0) {
    s32 sp1C;
    s32 sp18;

    sp1C = 0x1000;
    if ((arg0->unk201C + arg0->unk3F88) >= 0x1FFC) {
        bcopy(arg0->unk1C + sp1C, arg0->unk1C, sp1C);
        arg0->unk201C -= sp1C;
        arg0->unk2020 -= sp1C * 8;
    }
    sp18 = arg0->unk4(arg0->unk0, arg0->unk1C + arg0->unk201C, arg0->unk3F88, -1);
    if (sp18 < arg0->unk3F88) {
        bzero(arg0->unk1C + sp18, arg0->unk3F88 - sp18);
    }
    arg0->unk18 += arg0->unk3F88;
    arg0->unk201C += arg0->unk3F88;
    return arg0->unk201C - arg0->unk3F88;
}
/* mp3main_read_frame (Perfect Dark src/lib/mp3/main.c, plus a 0xFF/0xF3 sync byte check) */
s32 func_151F8088(struct asistream *stream, s32 arg1)
{
	s32 sp24;
	s32 sp20;
	s32 sp1c;
	u8 mask;

	if (arg1 != -1) {
		stream->unk18 = arg1;
	}

	sp24 = arg1;
	sp20 = 0;
	mask = 0xff;

	while (1) {
		sp1c = stream->dmafunc(stream->unk00, &stream->buffer[sp20], 1, sp24);

		if (sp1c <= 0) {
			return 0;
		}

		sp24 = -1;
		stream->unk18++;

		if (stream->buffer[sp20] != 0xff && stream->buffer[sp20] != 0xf3) {
			return 0;
		}

		if ((stream->buffer[sp20] & mask) != mask) {
			mask = 0xff;
			sp20 = 0;
			continue;
		}

		sp20++;

		if (mask == 0xf0) {
			break;
		}

		mask = 0xf0;
	}

	sp1c = stream->dmafunc(stream->unk00, &stream->buffer[2], 2, -1);

	if (sp1c <= 0) {
		return 0;
	}

	stream->unk18 += 2;

	stream->offset = 12;

	stream->version = func_151F9150(stream->buffer, &stream->offset, 1);
	stream->layer = func_151F9150(stream->buffer, &stream->offset, 2);
	stream->crctype = func_151F9150(stream->buffer, &stream->offset, 1);
	stream->bitrateindex = func_151F9150(stream->buffer, &stream->offset, 4);
	stream->samplerateindex = func_151F9150(stream->buffer, &stream->offset, 2);
	stream->haspadding = func_151F9150(stream->buffer, &stream->offset, 1);
	stream->privatebit = func_151F9150(stream->buffer, &stream->offset, 1);
	stream->channelmode = func_151F9150(stream->buffer, &stream->offset, 2);
	stream->channelmodeext = func_151F9150(stream->buffer, &stream->offset, 2);
	stream->copyright = func_151F9150(stream->buffer, &stream->offset, 1);
	stream->isoriginal = func_151F9150(stream->buffer, &stream->offset, 1);
	stream->emphasis = func_151F9150(stream->buffer, &stream->offset, 2);

	if (stream->bitrateindex == 15 || stream->samplerateindex == 3) { /* bad/reserved values */
		return func_151F8088(stream, -1);
	}

	if (!stream->doneinitial) {
		stream->doneinitial = 1;

		stream->initialversion = stream->version;
		stream->initiallayer = stream->layer;
		stream->initialcrctype = stream->crctype;
		stream->initialsamplerateindex = stream->samplerateindex;
		stream->initialchannelmode = stream->channelmode;
		stream->initialcopyright = stream->copyright;
		stream->initialisoriginal = stream->isoriginal;
	} else if (stream->version != stream->initialversion
			|| stream->layer != stream->initiallayer
			|| stream->crctype != stream->initialcrctype
			|| stream->samplerateindex != stream->initialsamplerateindex
			|| stream->channelmode != stream->initialchannelmode
			|| stream->isoriginal != stream->initialisoriginal) {
		return func_151F8088(stream, -1);
	}

	stream->unk2068 = 4;

	if (stream->crctype == CRC_PROTECTED) {
		sp1c = stream->dmafunc(stream->unk00, &stream->buffer[4], 2, -1);

		if (sp1c <= 0) {
			return 0;
		}

		stream->unk18 += 2;
		stream->offset += 16;
		stream->unk2068 = 6;
	}

	if (stream->layer == LAYER_3) {
		stream->decodeframefunc = func_151F78B4;
		stream->setsideinfofunc = func_151F6FD0;
	} else if (stream->layer == LAYER_2) {
		return 0;
	} else if (stream->layer == LAYER_1) {
		return 0;
	}

	if (!stream->setsideinfofunc(stream)) {
		return 0;
	}

	return 1;
}
struct_eu_221290 *func_151F85C4(s32 arg0, s32 (*arg1)(s32, u8 *, s32, s32), s32 arg2) {
    struct_eu_221290 *sp1C;

    sp1C = &D_800E1CB0;
    if (sp1C == NULL) {
        return NULL;
    }
    sp1C->unkC = -1;
    sp1C->unk10 = -1;
    sp1C->unk14 = -1;
    sp1C->unk0 = arg0;
    sp1C->unk4 = arg1;
    sp1C->unk8 = arg2;
    sp1C->unk201C = 0;
    sp1C->unk2020 = 0;
    sp1C->unk3BA0 = 0;
    if (func_151F8088((struct asistream *)sp1C, 0) == 0) {
        return NULL;
    }
    sp1C->unk8474 = 0;
    bzero(sp1C->unk6A64, 0x900);
    return sp1C;
}
s32 func_151F86B0(struct_eu_221290 *arg0, u8 **arg1, s32 *arg2) {
    struct_eu_221290 *sp12C;
    s32 sp128;
    u8 sp28[0x100];
    s32 sp24;

    sp12C = arg0;
    sp12C->unk3BA0++;
    if (sp12C->unk3BA0 >= 6) {
        sp12C->unk3BA0 = 0;
    }
    if (func_151F8088((struct asistream *)sp12C, sp12C->unk8474) == 0) {
        D_800E0E04 = 3;
        return 0;
    }
    sp12C->unk8474 = -1;
    sp128 = sp12C->unk8478(sp12C);
    if (sp128 == 0) {
    } else {
        *arg1 = sp12C->unk2070[sp12C->unk3BA0];
        *arg2 = sp12C->unk3F8C;
        if (sp12C->unk3BC8 != 0) {
            sp24 = 0;
            do {
                if (sp12C->unk4(sp12C->unk0, &sp28[sp24], 1, -1) == 0) {
                    break;
                }
            } while (sp28[sp24++]);
            if (D_800E1230 != NULL) {
                D_800E1230(0, sp28, strlen(sp28) + 1);
            }
        }
    }
    return sp128;
}
