s32 func_150ADA20(void); /* also in functions.h: declared again so difftest knows its arity (the asm leaves rec + 0x10 in a1) */
/* footprint trail point (0x24 bytes, ring of t[0x25] points at t +0x94; head t +0x2E, tail +0x2D, count +0x2C) */
typedef struct {
    f32 x;        /* 0x00 */
    f32 z;        /* 0x04 */
    f32 y;        /* 0x08: ground height under the point */
    f32 width;    /* 0x0C */
    s16 alpha;    /* 0x10 */
    s16 hold;     /* 0x12 */
    s16 u14;      /* 0x14: 0xFF */
    s16 u16;      /* 0x16: texture phase (rec +0x28) */
    s16 life;     /* 0x18 */
    s16 pad1A;
    f32 vx;       /* 0x1C: drift (sideways) */
    f32 vz;       /* 0x20 */
} TrailPointFD60;

// foot_trail_update: P191: per-frame update of a foot trail effect t (side t +0x20: 6 = left, 7 = right) of the
// player owning the trail record rec (t +0x98; rec +0 = the owner object, whose +0x18 is the player): returns 0
// when the player is gone (no state / model) or the owner id no longer matches. The first frame takes the foot
// position (func_1519F500 into t +0x10) as the record's last point; later frames re-take it (when that fails the
// trail is ended, func_1519F9FC, and a new trail effect func_151491F4(300, -1, 11, 0, 6, 8, 0xFF, 0) is started for
// the side). The distance moved times rec +0x8 accumulates in rec +0xC; while it is above 1 a point is laid every
// unit: position interpolated from the last point, width rec +0x38 + rec +0x3C * phase, alpha / hold / life /
// phase from the record (rec +0x28 advances by +0x44 + random [0, +0x45]), a sideways drift (the move direction
// turned left or right, times rec +0x4C), moved by drift * phase and dropped onto the ground (func_15045AF0 from
// 100 above the water surface, or above the player when there is no surface; points beyond +-20000 or without
// ground are not added). The point before the newest one gets the average of its drift and the new one. Returns 1.
// Rare reads the unit direction uninitialised when the foot did not move (asm: stack garbage); here it is 0.
s32 func_1519FD60(u8 *t) {
    u8 *rec = *(u8 **) (t + 0x98);
    TrailPointFD60 *pts = *(TrailPointFD60 **) (t + 0x94);
    u8 *owner = *(u8 **) rec;
    struct127 *pl = *(struct127 **) (owner + 0x18);
    TrailPointFD60 *q;
    struct {
        u8 *owner;
        u8 side;
    } key;
    u8 *slots;
    u8 *e;
    s32 started;
    f32 d0, d1, d2;
    f32 len;
    f32 inv = 0.0f;
    f32 n;
    f32 phase, phaseStep;
    f32 pos[3];
    f32 probe[3];
    f32 drift[2];
    f32 w, wStep;
    f32 step0, step1, step2;
    s32 h, k;
    s32 ok;
    s32 r;

    if (pl->interaction_state == 0) {
        return 0;
    }
    if (pl->unk1D4 == NULL) {
        return 0;
    }
    if (owner[0x1C] != pl->unique_id) {
        return 0;
    }
    started = 0;
    if (!(*(u16 *) (t + 0x1E) & 4)) {
        if (func_1519F500(rec, t[0x23], t + 0x10) == 0) {
            return 1;
        }
        started = 1;
        *(f32 *) (rec + 0x10) = *(f32 *) (t + 0x10);
        *(f32 *) (rec + 0x14) = *(f32 *) (t + 0x14);
        *(f32 *) (rec + 0x18) = *(f32 *) (t + 0x18);
        *(u16 *) (t + 0x1E) |= 4;
    }
    if (!started && func_1519F500(rec, t[0x23], t + 0x10) == 0) {
        func_1519F9FC(t);
        key.owner = *(u8 **) rec;
        key.side = *(s32 *) (t + 0x20);
        slots = key.owner + 0x58;
        e = (u8 *) func_151491F4(300, -1, 11, 0, 6, 8, 0xFF, 0);
        if (e != NULL) {
            memcpy((s32) (e + 0x28), (u8 **) &key, 8);
        }
        if (*(s32 *) (t + 0x20) == 6) {
            *(u8 **) (slots + 4) = e;
        } else {
            *(u8 **) (slots + 0xC) = e;
        }
        return 1;
    }

    *(f32 *) (rec + 0x20) = pl->x_position;
    *(f32 *) (rec + 0x24) = pl->z_position;
    d0 = *(f32 *) (t + 0x10) - *(f32 *) (rec + 0x10);
    d1 = *(f32 *) (t + 0x14) - *(f32 *) (rec + 0x14);
    d2 = *(f32 *) (t + 0x18) - *(f32 *) (rec + 0x18);
    if (fabsf(d0) > 0.0001f || fabsf(d1) > 0.0001f || fabsf(d2) > 0.0001f) {
        len = sqrtf(d0 * d0 + d1 * d1 + d2 * d2);
        inv = 1.0f / len;
        *(f32 *) (rec + 0xC) = *(f32 *) (rec + 0xC) + len * *(f32 *) (rec + 0x8);
    }
    if (!(1.0f < *(f32 *) (rec + 0xC))) {
        return 1;
    }
    n = 1.0f / *(f32 *) (rec + 0xC);
    phase = *(f32 *) (rec + 0x1C) + D_800BE9A4;
    phaseStep = phase * n;
    pos[0] = *(f32 *) (rec + 0x10);
    pos[1] = *(f32 *) (rec + 0x14);
    pos[2] = *(f32 *) (rec + 0x18);
    w = *(f32 *) (rec + 0x38) + *(f32 *) (rec + 0x3C) * phase;
    wStep = *(f32 *) (rec + 0x38) - w;
    if (*(s32 *) (t + 0x20) == 7) {
        drift[0] = -d2 * inv * *(f32 *) (rec + 0x4C);
        drift[1] = d0 * inv * *(f32 *) (rec + 0x4C);
    } else {
        drift[0] = d2 * inv * *(f32 *) (rec + 0x4C);
        drift[1] = -d0 * inv * *(f32 *) (rec + 0x4C);
    }
    h = *(s8 *) (t + 0x2E) - 1;
    if (h < 0) {
        h = t[0x25] - 1;
    }
    if (h != *(s8 *) (t + 0x2D) && *(s8 *) (t + 0x2C) != 0) {
        k = h - 1;
        if (k < 0) {
            k = t[0x25] - 1;
        }
        pts[k].vx = (pts[k].vx + drift[0]) * 0.5f;
        pts[k].vz = (pts[k].vz + drift[1]) * 0.5f;
    }
    step0 = d0 * n;
    step1 = d1 * n;
    step2 = d2 * n;
    wStep = wStep * n;
    do {
        q = &pts[*(s8 *) (t + 0x2E)];
        q->vx = drift[0];
        q->vz = drift[1];
        q->x = pos[0];
        q->z = pos[2];
        q->life = *(s16 *) (rec + 0x2E);
        q->width = w;
        q->alpha = *(s16 *) (rec + 0x30);
        q->u14 = 0xFF;
        q->hold = *(s16 *) (rec + 0x32);
        q->u16 = *(s16 *) (rec + 0x28);
        r = func_150ADA20();
        *(s16 *) (rec + 0x28) = *(s16 *) (rec + 0x28) + rec[0x44] + (u32) r % (u32) (rec[0x45] + 1);
        q->x = q->x + q->vx * phase;
        q->z = q->z + q->vz * phase;
        probe[0] = q->x;
        if (pl->unk118 < -9500.0f) {
            probe[1] = pl->y_position + 100.0f;
        } else {
            probe[1] = pl->unk118 + 100.0f;
        }
        probe[2] = q->z;
        ok = 1;
        if (fabsf(probe[0]) > 20000.0f || fabsf(probe[2]) > 20000.0f) {
            ok = 0;
        } else if (func_15045AF0(probe, 0, probe[1] - 200.0f, t + 0x60) != 0) {
            q->y = *(f32 *) (t + 0x60);
        } else {
            ok = 0;
        }
        if (ok) {
            *(s8 *) (t + 0x2E) += 1;
            if (t[0x25] == *(s8 *) (t + 0x2E)) {
                *(s8 *) (t + 0x2E) = 0;
            }
            *(s8 *) (t + 0x2C) += 1;
            if (*(s8 *) (t + 0x2D) == *(s8 *) (t + 0x2E)) {
                /* ring full: drop the oldest point */
                *(s8 *) (t + 0x2D) += 1;
                if (t[0x25] == *(s8 *) (t + 0x2D)) {
                    *(s8 *) (t + 0x2D) = 0;
                }
                *(s8 *) (t + 0x2C) -= 1;
            }
        }
        pos[0] += step0;
        pos[1] += step1;
        pos[2] += step2;
        w += wStep;
        phase -= phaseStep;
        *(f32 *) (rec + 0xC) = *(f32 *) (rec + 0xC) - 1.0f;
    } while (1.0f < *(f32 *) (rec + 0xC));
    *(f32 *) (rec + 0x10) = pos[0];
    *(f32 *) (rec + 0x14) = pos[1];
    *(f32 *) (rec + 0x18) = pos[2];
    *(f32 *) (rec + 0x1C) = phase;
    return 1;
}
