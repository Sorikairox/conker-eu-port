// ambient_emitters_update: per frame, the level's ambient emitters (fires, torches: the records sorted by
// func_1517BE0C) within radius of (x, y, z) along the axis the camera angle (degrees) faces: nearest distance per
// slot (D_800DE070), the slot's voice loaded (D_800DD478 slot words + D_800DDA90 voice) or marked "heard" (read by
// func_1517E3CC), flare-ups near the point D_800DD8A0 / close to the camera, one camera-facing 4-Vtx quad per
// emitter at D_800DDD10[D_800BE9C0] (count D_800DE188; emitters within 0x8C of the player (px, py, pz) are skipped,
// fade in up to 0xF0), the per-slot phase animation, a random spark, and finally the quads turned to the angle.
// Clears D_800DD8A0[0] when quads were allocated.
void func_1517C11C(s32 x, s32 y, s32 z, s32 radius, f32 angle, s32 px, s32 py, s32 pz) {
    AmbientEmitterRec *e;
    AmbientVoice *v;
    AmbientUpdater update;
    Vtx *quad;
    s32 *slot;
    u8 *flags;
    u8 *info;
    s16 *ph;
    s16 xmin, xmax, zmin, zmax;
    s16 target, limit, key;
    s32 axis;   /* 0 = sorted by x, 2 = by z */
    s32 byZ, dir;
    s32 lo, hi, mid;
    s32 idx;
    u32 count, n;
    s32 dist, dist2;
    s32 voice;
    s32 phase;
    s32 step, period, bit, r, a, i, k;
    u16 frame;
    s16 c, s;
    f32 sn;
    s32 w, h, dx, dz;
    s16 vx, vy, vz;

    D_800DE188 = 0;
    byZ = TRUE;
    dir = 1;
    xmin = x - radius;
    xmax = x + radius;
    zmin = z - radius;
    zmax = z + radius;
    hi = D_800DDD20 - 1;
    lo = 0;
    mid = 0;
    if ((angle > 45.0f && angle < 135.0f) || (angle > 225.0f && angle < D_800A7620)) {
        byZ = FALSE;
        if (angle > 180.0f) {
            dir = -1;
        }
    } else if (angle > 90.0f && angle < 270.0f) {
        dir = -1;
    }
    if (byZ != D_8008D254) {
        D_8008D254 = byZ;
        func_1517BE0C(0, D_800DDD20 - 1);
    }
    axis = byZ ? 2 : 0;
    if (dir == 1) {
        target = byZ ? zmin : xmin;
        limit = byZ ? zmax : xmax;
    } else {
        target = byZ ? zmax : xmax;
        limit = byZ ? zmin : xmin;
    }

/* emitter i is on the sorted list and short of the far edge of the range in the walking direction */
#define AMBIENT_IN_RANGE(i) \
    ((dir == 1) ? ((i) < D_800DDD20 && D_800DE148[i].pos[axis] < limit) \
                : (dir == -1 && (i) >= 0 && limit < D_800DE148[i].pos[axis]))

    // Binary search for the near edge of the range.
    while (lo <= hi) {
        mid = (lo + hi) / 2;
        key = D_800DE148[mid].pos[axis];
        if (target < key) {
            hi = mid - 1;
        } else if (key < target) {
            lo = mid + 1;
        } else {
            break;
        }
    }

    for (i = 0; i < 15; i++) {
        D_800DE070[i] = 0x7FFF;
    }

    if (!AMBIENT_IN_RANGE(mid)) {
        D_800DDD10[D_800BE9C0] = 0;
        return;
    }
    n = ((u32) D_800DDD20 < (u32) D_800DDD0C) ? (u32) D_800DDD20 : (u32) D_800DDD0C;
    D_800DDD10[D_800BE9C0] = (s32) allocate_memory(n << 6, 4, 2, 0);
    if (D_800DDD10[D_800BE9C0] == 0) {
        return;
    }

    count = 0;
    idx = mid;
    if (D_800DDD0C != 0 && AMBIENT_IN_RANGE(idx)) {
        do {
            e = &D_800DE148[idx];
            dist = func_150AD9A0(e->pos[0] - x, e->pos[1] - y, e->pos[2] - z);
            if (dist >= radius) {
                goto next;
            }
            voice = e->mode & 0xF;
            if ((u32) dist < D_800DE070[voice]) {
                D_800DE070[voice] = dist;
            }
            dist2 = func_150AD9A0(e->pos[0] - px, e->pos[1] - py, e->pos[2] - pz);
            if (dist2 < 0x8D) {
                goto next;
            }
            if (dist2 < 0xF0) {
                dist = radius - ((radius - dist) * (dist2 - 0x8C)) / 100;
            }

            // The slot's voice: load the sample and 25 frame buffers (slot words 0..25), or mark it heard.
            slot = &D_800DD478 + voice * 26;
            v = &((AmbientVoice *) &D_800DDA90)[voice];
            if (slot[0] == 0) {
                if (v->romAddr != 0) {
                    info = &D_80096090[D_800DDFF0[voice] * 10];
                    n = info[1] * *(u16 *) (info + 2);
                    v->handle = func_10003C6C(v->size, 1, 2, 1, 0);
                    if (v->handle != 0) {
                        slot[0] = func_10003C6C(n, 4, 1, 0, 0);
                        if (slot[0] != 0) {
                            func_10004514(v->romAddr, (void *) v->handle, v->size, 1);
                            v->heard = 1;
                            step = *(u16 *) &D_80096090[D_800DDFF0[voice] * 10 + 2];
                            for (k = 1; k < 26; k++) {
                                slot[k] = slot[k - 1] + step;
                            }
                        } else {
                            func_10004074(v->handle);
                        }
                    }
                }
            } else if (v->heard == 0) {
                v->heard = 1;
                func_100043B4((s32 *) slot[0], 4);
            }

            quad = (Vtx *) (D_800DDD10[D_800BE9C0] + count * 64);
            phase = D_800DE0C0[e->phase];
            if (phase < 0) {
                phase = 0;
            }
            // Flare-up when the point D_800DD8A0 (set when x != 0) comes near, or when the camera is close.
            if (D_800DD8A0[0] != 0 &&
                func_150AD9A0(e->pos[0] - D_800DD8A0[0], e->pos[1] - D_800DD8A0[1], e->pos[2] - D_800DD8A0[2]) < 0x50 &&
                D_800DDFF0[voice] == 0 && e->flare != 0x21) {
                e->flare = 0x21;
                func_15170A70(e->pos[0], e->pos[1] + 0x44, e->pos[2], 0, 0, 0xFF, 0);
            }
            if (e->flare >= 0x21) {
                if (e->flare >= 0x22) {
                    e->flare--;
                }
            } else if (dist < 0x30 && D_800DDFF0[voice] == 0) {
                e->flare = 0x22;
                func_15170A70(e->pos[0], e->pos[1] + 0x44, e->pos[2], 0, 0, 0xFF, 0);
            }
            quad[3].v.flag = e->height;
            quad[2].v.flag = e->halfWidth;
            a = (u32) (radius - dist) >> 1;
            if (a >= 0x100) {
                a = 0xFF;
            }
            quad[0].v.cn[3] = a;

            update = D_8008D258[D_8008D2A0[D_800DE0B0[voice]][e->kind][0]].update;
            if (update != NULL) {
                if ((*update)(e, quad, &phase, &quad[0].v.cn[3]) != 0) {
                    goto next;
                }
            } else {
                quad[0].v.ob[0] = e->pos[0];
                quad[0].v.ob[1] = e->pos[1];
                quad[0].v.ob[2] = e->pos[2];
            }
            for (k = 0; k < 4; k++) {
                quad[k].v.cn[0] = quad[k].v.cn[1] = quad[k].v.cn[2] = e->mode | 0x9F;
            }
            quad[1].v.cn[3] = quad[2].v.cn[3] = quad[3].v.cn[3] = quad[0].v.cn[3];
            // flag of vertex 0 = frame number in the slot's 26 frames (D_800DE010: the flare-up frame)
            if (e->flare >= 0x21) {
                quad[0].v.flag = D_800DE010[voice] + voice * 26;
            } else {
                quad[0].v.flag = voice * 26 + (phase >> 8);
            }
            quad[1].v.flag = D_800DE020[voice];
            quad[1].v.tc[0] = quad[2].v.tc[0] = D_800DDFB0[voice][0];
            quad[2].v.tc[1] = quad[3].v.tc[1] = D_800DDFB0[voice][1];
            count++;
        next:
            if (count >= (u32) D_800DDD0C) {
                break;
            }
            idx += dir;
        } while (AMBIENT_IN_RANGE(idx));
    }
#undef AMBIENT_IN_RANGE
    D_800DE188 = count;

    // Phase animation per slot: ping-pong (D_800DDC04 bit; D_800DDC08 bit: slower, with random direction flips)
    // or wrap-around.
    if (D_800BEAC0 == 0) {
        for (i = 0; i < 15; i++) {
            period = (D_800DE000[i] << 8) - 1;
            if (period < 0x101) {
                continue;
            }
            ph = &D_800DE0C0[i * 4];
            bit = 1 << i;
            if (bit & D_800DDC04) {
                flags = &D_800DE040[i];
                if (bit & D_800DDC08) {
                    r = func_151EFDD0() % 10;
                    if (r == 0) {
                        *flags |= func_151EFDD0() % 16;
                        step = 0;
                    } else if (r == 1) {
                        *flags &= func_151EFDD0() % 16;
                        step = 1;
                    } else {
                        step = D_800BE9E4 << 5;
                    }
                } else {
                    step = D_800BE9E4 << 6;
                }
                for (k = 0; k < 4; k++) {
                    if (*flags & (1 << k)) {
                        ph[k] -= step;
                        if (ph[k] <= 0) {
                            ph[k] = -ph[k];
                            *flags ^= 1 << k;
                        }
                    } else {
                        ph[k] += step;
                        if (ph[k] >= period) {
                            ph[k] = period * 2 - ph[k];
                            *flags ^= 1 << k;
                        }
                    }
                }
            } else {
                step = D_800BE9E4 * 48;
                for (k = 0; k < 4; k++) {
                    ph[k] += step;
                    if (ph[k] >= period) {
                        ph[k] -= period;
                    }
                }
            }
        }
    }

    // A random quad on its slot's first frame sparks (D_800DDD0C == 0 here divides by zero, as on N64).
    r = (u32) func_151EFDD0() % (u32) D_800DDD0C;
    if ((u32) r < (u32) D_800DE188) {
        quad = (Vtx *) (D_800DDD10[D_800BE9C0] + r * 64);
        frame = quad[0].v.flag;
        if (frame % 26 == 0 && D_800DDFF0[frame / 26] == 0) {
            func_15170A70(quad[0].v.ob[0], quad[0].v.ob[1] + 0x44, quad[0].v.ob[2], 0, 1, 0xFF, 0);
        }
    }

    // Turn every quad to the camera: base corners at +-(w cos, w sin) around the emitter, top at y + 4 * height.
    angle *= D_800A7624;
    c = cosf(angle) * 128.0f;
    sn = sinf(angle);
    if (D_800DE188 != 0) {
        s = sn * 128.0f;
        for (i = 0; (u32) i < (u32) D_800DE188; i++) {
            quad = (Vtx *) (D_800DDD10[D_800BE9C0] + i * 64);
            w = (s16) quad[2].v.flag;
            vx = quad[0].v.ob[0];
            vy = quad[0].v.ob[1];
            vz = quad[0].v.ob[2];
            h = quad[3].v.flag << 2;
            dx = (w * c) >> 5;
            dz = (w * s) >> 5;
            quad[3].v.ob[0] = quad[0].v.ob[0] = vx + dx;
            quad[1].v.ob[1] = quad[0].v.ob[1] = vy;
            quad[3].v.ob[2] = quad[0].v.ob[2] = vz - dz;
            quad[2].v.ob[0] = quad[1].v.ob[0] = vx - dx;
            quad[3].v.ob[1] = quad[2].v.ob[1] = vy + h;
            quad[2].v.ob[2] = quad[1].v.ob[2] = vz + dz;
            quad[0].v.tc[0] = quad[0].v.tc[1] = 0;
            quad[1].v.tc[1] = quad[3].v.tc[0] = 0;
        }
    }
    D_800DD8A0[0] = 0;
}
