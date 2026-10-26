#include <ultra64.h>

#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
extern s16 D_8002BF60[]; /* EU pan gain table (128 s16, US D_8002BC10): left = [pan], right = [127 - pan] */
void func_151F3C34(s32 arg0);

// audio_mixer_init: clears the mixer state D_800E0D80 (0xA0 bytes), allocates its buffers from heap `heap` (0x50,
// 0x440 and 8 bytes at +0x08 / +0x74 / +0x5C), centres the pan (64, +0x0C / +0x94 / +0x96), sets full volume
// (0x7FFF at +0x0E / +0x88), the left / right gains from the pan table (+0x10 / +0x12) and +0x14 = 0x7FFC, and
// installs func_151F3C4C as the mixer callback (func_151F3C34; the asm also leaves 0x7FFF / 64 in a1 / a2).
/* was func_15016170 */
void audio_fx_mixer_init(s32 heap) {
    struct186 *m = &D_800E0D80;
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
    m->unk10 = (D_8002BF60[pan] * vol) >> 15;
    m->unk12 = (D_8002BF60[127 - pan] * vol) >> 15;
    ((u8 *) m)[0x24] = 1; /* byte store (struct186 declares a u16 here) */
    m->unk14 = 0x7FFC;
    m->unk16 = 0;
    func_151F3C34((s32) func_151F3C4C);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_43620/audio_fx_mixer_init.s")
#endif
// looks straightforward.. but... isnt
// void audio_fx_mixer_init(s32 arg0) {
//     s32 idx;
//     s16 tmp;
//     bzero(&D_800E0D80, 160);
//     D_800E0D80.unk8 = alHeapDBAlloc(0, 0, arg0, 1, 80);
//     D_800E0D80.unk74 = alHeapDBAlloc(0, 0, arg0, 1, 1088);
//     D_800E0D80.unk5C = alHeapDBAlloc(0, 0, arg0, 1, 8);
//     D_800E0D80.unk96 = 64;
//     D_800E0D80.unkC = 64;
//     D_800E0D80.unk84 = 0;
//     D_800E0D80.unkE = 0x7FFF;
//     D_800E0D80.unk88 = 0x7FFF;
//     D_800E0D80.unk9A = 0;
//     D_800E0D80.unk32 = 0;
//     D_800E0D80.unk30 = 0;
//     D_800E0D80.unk94 = D_800E0D80.unk96;
//     idx = D_800E0D80.unkC;
//     tmp = D_800E0D80.unkE;
//     D_800E0D80.unk10 = (D_8002BC10[idx] * tmp) >> 15;
//     D_800E0D80.unk12 = (D_8002BD0E[-idx] * tmp) >> 15;
//     D_800E0D80.unk24 = 1;
//     D_800E0D80.unk14 = 0x7FFC;
//     D_800E0D80.unk16 = 0;
//     func_151F3C34(func_151F3C4C, tmp, 64);
// }
