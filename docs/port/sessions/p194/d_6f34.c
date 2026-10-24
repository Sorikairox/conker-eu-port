s32 func_151152A4(u8 *obj, s32 sound, s32 vol, s16 r0, s16 r1, s32 flags);
void func_1511712C(u8 *rec);
/* mover sounds, indexed by +0x3C >> 10 (12 bytes): start, stop, arrival and its lead distance */
typedef struct {
    s16 start;   /* 0x0 */
    s16 pad2;
    s16 stop;    /* 0x4 */
    s16 pad6;
    s16 arrive;  /* 0x8: played when the remaining distance drops below lead */
    s16 lead;    /* 0xA: in steps of the speed (times +0x3C & 0xFFFF03FF / 2) */
} MoverSounds;
extern MoverSounds D_80089600[];

// mover_linear_update: P194. World mesh record (D_800DBEF4, 0xA0 bytes) handler (func_15116F04 calls it while +0x73
// bit 1 is set): moves the position (+0x10 / +0x12 / +0x14, s16) towards the target (+0x7C / +0x80 / +0x84, s32)
// by (+0x3C & 0xFFFF03FF) * D_800BE9E4 / 2 per axis, clamped at the target, and stores the moves of this call in
// +0x5A..+0x5E. Bits 10.. of +0x3C pick the sound entry D_80089600: the start sound plays (func_151152A4) when the
// mover starts (no sound handle +0x74); entries with an arrival sound use func_1511712C instead. At the target the
// moves are zeroed and a playing sound (+0x74) is replaced by the stop sound, then +0x74 = 0.
void func_15116F34(u8 *rec) {
    s16 *pos = (s16 *) (rec + 0x10);
    s32 *target = (s32 *) (rec + 0x7C);
    s16 *moved = (s16 *) (rec + 0x5A);
    s32 snd = *(s32 *) (rec + 0x3C) >> 10;
    s32 step;
    s32 i;

    if (pos[0] == target[0] && pos[1] == target[1] && pos[2] == target[2]) {
        moved[2] = 0;
        moved[1] = 0;
        moved[0] = 0;
        if (*(u16 *) (rec + 0x74) != 0) {
            if (snd != 0 && D_80089600[snd].stop != 0) {
                func_151152A4(rec, D_80089600[snd].stop, 0x5DC0, 0x7D0, 0xFA0, 4);
            }
            *(u16 *) (rec + 0x74) = 0;
        }
        return;
    }
    if (snd != 0 && D_80089600[snd].arrive != 0) {
        func_1511712C(rec);
        return;
    }
    step = *(s32 *) (rec + 0x3C) & 0xFFFF03FF;
    if (snd != 0 && *(u16 *) (rec + 0x74) == 0 && D_80089600[snd].start != 0) {
        func_151152A4(rec, D_80089600[snd].start, 0x5DC0, 0x7D0, 0xFA0, 0);
    }
    step = (step * D_800BE9E4) >> 1;
    for (i = 0; i < 3; i++) {
        moved[i] = pos[i];
        if (pos[i] != target[i]) {
            if (target[i] < pos[i]) {
                pos[i] -= step;
                if (pos[i] < target[i]) {
                    pos[i] = target[i];
                }
            } else {
                pos[i] += step;
                if (pos[i] > target[i]) {
                    pos[i] = target[i];
                }
            }
        }
        moved[i] = pos[i] - moved[i];
    }
}
