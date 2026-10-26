#include <ultra64.h>

#include "functions.h"
#include "variables.h"


extern s16 g_audio_eqpower[]; /* EU pan gain table (128 s16, US D_8002BC10): left = [pan], right = [127 - pan]; was D_8002BF60 */
void mp3_stream_set_read_cb(s32 arg0);

// audio_mixer_init: clears the mixer state g_mp3_stream (0xA0 bytes), allocates its buffers from heap `heap` (0x50,
// 0x440 and 8 bytes at +0x08 / +0x74 / +0x5C), centres the pan (64, +0x0C / +0x94 / +0x96), sets full volume
// (0x7FFF at +0x0E / +0x88), the left / right gains from the pan table (+0x10 / +0x12) and +0x14 = 0x7FFC, and
// installs mp3_stream_rom_read as the mixer callback (mp3_stream_set_read_cb; the asm also leaves 0x7FFF / 64 in a1 / a2).
/* was func_15016170 */
void audio_fx_mixer_init(s32 heap) {
    struct186 *m = &g_mp3_stream;
    s32 pan;
    s32 vol;

    bzero(m, sizeof(struct186));
    m->unk8 = (s32) alHeapDBAlloc(NULL, 0, (ALHeap *) heap, 1, 0x50);
    m->unk74 = (s32) alHeapDBAlloc(NULL, 0, (ALHeap *) heap, 1, 0x440);
    m->unk5C = (s32) alHeapDBAlloc(NULL, 0, (ALHeap *) heap, 1, 8);
    m->unkC = 64;
    m->unk96 = 64;
    m->unkE = 0x7FFF;
    m->unk84 = 0;
    m->unk88 = 0x7FFF;
    m->unk9A = 0;
    m->unk32 = 0;
    m->unk30 = 0;
    m->unk94 = m->unk96;
    pan = m->unkC;
    vol = m->unkE;
    m->unk10 = (g_audio_eqpower[pan] * vol) >> 15;
    m->unk12 = (g_audio_eqpower[127 - pan] * vol) >> 15;
    ((u8 *) m)[0x24] = 1; /* byte store (struct186 declares a u16 here) */
    m->unk14 = 0x7FFC;
    m->unk16 = 0;
    mp3_stream_set_read_cb((s32) mp3_stream_rom_read);
}
// looks straightforward.. but... isnt
// void audio_fx_mixer_init(s32 arg0) {
//     s32 idx;
//     s16 tmp;
//     bzero(&g_mp3_stream, 160);
//     g_mp3_stream.unk8 = alHeapDBAlloc(0, 0, arg0, 1, 80);
//     g_mp3_stream.unk74 = alHeapDBAlloc(0, 0, arg0, 1, 1088);
//     g_mp3_stream.unk5C = alHeapDBAlloc(0, 0, arg0, 1, 8);
//     g_mp3_stream.unk96 = 64;
//     g_mp3_stream.unkC = 64;
//     g_mp3_stream.unk84 = 0;
//     g_mp3_stream.unkE = 0x7FFF;
//     g_mp3_stream.unk88 = 0x7FFF;
//     g_mp3_stream.unk9A = 0;
//     g_mp3_stream.unk32 = 0;
//     g_mp3_stream.unk30 = 0;
//     g_mp3_stream.unk94 = g_mp3_stream.unk96;
//     idx = g_mp3_stream.unkC;
//     tmp = g_mp3_stream.unkE;
//     g_mp3_stream.unk10 = (D_8002BC10[idx] * tmp) >> 15;
//     g_mp3_stream.unk12 = (D_8002BD0E[-idx] * tmp) >> 15;
//     g_mp3_stream.unk24 = 1;
//     g_mp3_stream.unk14 = 0x7FFC;
//     g_mp3_stream.unk16 = 0;
//     mp3_stream_set_read_cb(mp3_stream_rom_read, tmp, 64);
// }
