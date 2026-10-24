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
// mover_linear_update_arrival: P194. func_15116F34 for movers whose sound entry has an arrival sound: the same step
// (start sound when no handle +0x74, per-axis move clamped at the target, moves in +0x5A..+0x5E), and it keeps the
// largest remaining distance of the moving axes (0 at least; an overshoot counts as negative). The arrival sound
// D_80089600[+0x3C >> 10].arrive plays once that distance minus lead * (+0x3C & 0xFFFF03FF) / 2 is in (-step, 0],
// or in this call's start frame when it is <= 0.
void func_1511712C(u8 *rec) {
    s16 *pos = (s16 *) (rec + 0x10);
    s32 *target = (s32 *) (rec + 0x7C);
    s16 *moved = (s16 *) (rec + 0x5A);
    s32 snd = *(s32 *) (rec + 0x3C) >> 10;
    s32 speed = *(s32 *) (rec + 0x3C) & 0xFFFF03FF;
    s32 started = FALSE;
    s32 remain = 0;
    s32 left;
    s32 step;
    s32 i;

    if (snd != 0 && *(u16 *) (rec + 0x74) == 0 && D_80089600[snd].start != 0) {
        func_151152A4(rec, D_80089600[snd].start, 0x5DC0, 0x7D0, 0xFA0, 0);
        started = TRUE;
    }
    step = (s32) (speed * D_800BE9E4) >> 1;
    for (i = 0; i < 3; i++) {
        moved[i] = pos[i];
        if (pos[i] != target[i]) {
            if (target[i] < pos[i]) {
                pos[i] -= step;
                left = pos[i] - target[i];
            } else {
                pos[i] += step;
                left = target[i] - pos[i];
            }
            if (left < 0) {
                pos[i] = target[i];
            }
            if (remain < left) {
                remain = left;
            }
        }
        moved[i] = pos[i] - moved[i];
    }
    if (snd != 0 && D_80089600[snd].arrive != 0) {
        remain -= (s32) (D_80089600[snd].lead * speed) >> 1;
        if (remain <= 0 && (-step < remain || started)) {
            func_151152A4(rec, D_80089600[snd].arrive, 0x5DC0, 0x7D0, 0xFA0, 0);
        }
    }
}
