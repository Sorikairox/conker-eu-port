extern s16 D_8002BF60[];
void func_151F3C34(s32 arg0);
// audio_mixer_init: clears the mixer state D_800E0D80 (0xA0 bytes), allocates its buffers from heap `heap` (0x50,
// 0x440 and 8 bytes at +0x08 / +0x74 / +0x5C), centres the pan (64, +0x0C / +0x94 / +0x96), sets full volume
// (0x7FFF at +0x0E / +0x88), the left / right gains from the pan table (+0x10 / +0x12) and +0x14 = 0x7FFC, and
// installs func_151F3C4C as the mixer callback (func_151F3C34; the asm also leaves 0x7FFF / 64 in a1 / a2).
void func_15016170(s32 heap) {
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
