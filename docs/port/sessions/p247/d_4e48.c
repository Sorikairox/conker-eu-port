#ifdef NON_MATCHING
/* P247: bone-attached particle emitter made by func_15134DAC (+0x18..+0x53 = the 0x3C-byte spec it copies). */
typedef struct {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s32 active;          /* bit 0: emitting */
    /* 0x14 */ s32 unk14;
    /* 0x18 */ u8 objId;            /* the object's +0x3B id when attached */
    /* 0x19 */ u8 pad19[3];
    /* 0x1C */ u8 *obj;             /* object the emitter rides on */
    /* 0x20 */ u8 bone;             /* matrix index in the object's model (+0x1D4) */
    /* 0x21 */ u8 pad21[3];
    /* 0x24 */ f32 offsetA[3];      /* emission points in bone space */
    /* 0x30 */ f32 offsetB[3];
    /* 0x3C */ u8 flags;            /* bit 1: limited lifetime (+0x42) */
    /* 0x3D */ u8 pad3D;
    /* 0x3E */ s16 restart;         /* timer value after a (re)start */
    /* 0x40 */ s16 period;          /* the timer restarts below -period */
    /* 0x42 */ s16 life;
    /* 0x44 */ u16 sound;
    /* 0x46 */ s8 startFn;          /* D_80089EBC index (-1: none): called on restart, 0 = stop */
    /* 0x47 */ s8 emitFn;           /* D_80089ED8 index (-1: none): emits one particle */
    /* 0x48 */ s8 rateFn;           /* D_80089EFC index (-1: none): sets rateScale */
    /* 0x49 */ u8 pad49[3];
    /* 0x4C */ f32 rate;            /* particles per frame unit */
    /* 0x50 */ u8 kind;
    /* 0x51 */ s8 tickFn;           /* D_80089F0C index (-1: none): per-frame check, 0 = stop */
    /* 0x52 */ u8 pad52[2];
    /* 0x54 */ s16 timer;
    /* 0x56 */ u8 pad56[2];
    /* 0x58 */ f32 posA[3];         /* world positions of the emission points at the last emission */
    /* 0x64 */ f32 posB[3];
    /* 0x70 */ f32 count;           /* particles owed */
    /* 0x74 */ f32 rateScale;
    /* 0x78 */ f32 phase;
} BoneEmitter;

extern s32 (*D_80089EBC[])(BoneEmitter *);
extern void (*D_80089ED8[])(f32 *, f32 *, f32 *, f32 *, f32, BoneEmitter *);
extern f32 (*D_80089EFC[])(BoneEmitter *);
extern s32 (*D_80089F0C[])(BoneEmitter *);
void func_15135424(s32, s32, s32, s32, s32);

// bone_emitter_update: per-frame update (pointer at 0x8008C09C, next to EU 0x15134C9C / 0x15134CEC) of a
// particle emitter attached to a bone of an object (made by func_15134DAC). While emitting
// (+0x10 bit 0) and the object is alive, unchanged (id byte), has a model and is not hidden: counts the timer down
// by D_800BE9E4; when it passes -period it restarts at `restart`, re-reads the two emission points from the bone
// matrix (func_15135424) and calls the start callback (0 stops the emitter). While the timer is positive it adds
// rate * D_800BE9A4 to the owed count (the rate callback only stores rateScale for the emit callbacks) and, when more
// than one particle is owed, emits them evenly spaced along the path both points moved since the last emission:
// each call gets the interpolated points, the points' velocities (step * D_800BEDC8) and a phase that runs from
// phase + D_800BE9A4 down by equal steps; the points and phase are kept for the next frame. Then the tick callback
// and the lifetime (+0x42, flag 2) can stop it. A stopped emitter, or one whose object is gone, is freed
// (func_1516972C).
void func_15134E48(BoneEmitter *e) {
    u8 stop = 0;
    u8 *obj = e->obj;
    u8 *mtx;
    u8 *bone;
    f32 newA[3];
    f32 newB[3];
    f32 curA[3];
    f32 curB[3];
    f32 velA[3];
    f32 velB[3];
    f32 stepA[3];
    f32 stepB[3];
    f32 inv;
    f32 phase;
    f32 phaseStep;
    f32 dA[3];
    f32 dB[3];

    if (*(s32 *) obj == 0 || e->objId != obj[0x3B]) {
        stop = 1;
    }
    if (e->active & 1) {
        if (!stop && (mtx = *(u8 **) (obj + 0x1D4)) != NULL && (obj[0x74] & 0xF) != 0xF) {
            e->timer -= D_800BE9E4;
            bone = mtx + e->bone * 0x40;
            if (e->timer < -e->period) {
                e->timer = e->restart;
                func_15135424((s32) bone, (s32) e->offsetA, (s32) e->offsetB, (s32) e->posA, (s32) e->posB);
                if (e->startFn != -1 && D_80089EBC[e->startFn](e) == 0) {
                    stop = 1;
                    e->timer = -1;
                }
            }
            if (e->timer > 0) {
                if (e->rateFn != -1) {
                    e->rateScale = D_80089EFC[e->rateFn](e);
                }
                e->count += e->rate * D_800BE9A4;
                if (e->count > 1.0f) {
                    inv = 1.0f / e->count;
                    phase = e->phase + D_800BE9A4;
                    phaseStep = phase * inv;
                    curA[0] = e->posA[0];
                    curA[1] = e->posA[1];
                    curA[2] = e->posA[2];
                    curB[0] = e->posB[0];
                    curB[1] = e->posB[1];
                    curB[2] = e->posB[2];
                    func_15135424((s32) bone, (s32) e->offsetA, (s32) e->offsetB, (s32) newA, (s32) newB);
                    dA[0] = newA[0] - e->posA[0];
                    dA[1] = newA[1] - e->posA[1];
                    dA[2] = newA[2] - e->posA[2];
                    dB[0] = newB[0] - e->posB[0];
                    dB[1] = newB[1] - e->posB[1];
                    dB[2] = newB[2] - e->posB[2];
                    velA[0] = dA[0] * D_800BEDC8;
                    velA[1] = dA[1] * D_800BEDC8;
                    velA[2] = dA[2] * D_800BEDC8;
                    velB[0] = dB[0] * D_800BEDC8;
                    velB[1] = dB[1] * D_800BEDC8;
                    velB[2] = dB[2] * D_800BEDC8;
                    stepA[0] = dA[0] * inv;
                    stepA[1] = dA[1] * inv;
                    stepA[2] = dA[2] * inv;
                    stepB[0] = dB[0] * inv;
                    stepB[1] = dB[1] * inv;
                    stepB[2] = dB[2] * inv;
                    do {
                        if (e->emitFn != -1) {
                            D_80089ED8[e->emitFn](curA, curB, velA, velB, phase, e);
                        }
                        curA[0] += stepA[0];
                        curA[1] += stepA[1];
                        curA[2] += stepA[2];
                        curB[0] += stepB[0];
                        curB[1] += stepB[1];
                        curB[2] += stepB[2];
                        phase -= phaseStep;
                        e->count -= 1.0f;
                    } while (e->count > 1.0f);
                    e->posA[0] = curA[0];
                    e->posA[1] = curA[1];
                    e->posA[2] = curA[2];
                    e->posB[0] = curB[0];
                    e->posB[1] = curB[1];
                    e->posB[2] = curB[2];
                    e->phase = phase;
                }
            }
        }
        if (e->tickFn != -1 && D_80089F0C[e->tickFn](e) == 0) {
            stop = 1;
        }
        if (e->flags & 2) {
            e->life -= D_800BE9E4;
            if (e->life < 0) {
                stop = 1;
            }
        }
    }
    if (stop) {
        func_1516972C((struct102 *) e);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_15134E48.s")
#endif
