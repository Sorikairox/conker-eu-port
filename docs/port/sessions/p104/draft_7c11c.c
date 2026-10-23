f32 sinf(f32);
f32 cosf(f32);
void func_1517BE0C(s32 arg0, s32 arg1);
s32 func_150AD9A0(s32 dx, s32 dy, s32 dz);
void func_15170A70(s32 x, s32 y, s32 z, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
s32 func_10003C6C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_100043B4(s32 *arg0, u32 arg1);
s32 allocate_memory(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_10004074(s32);

// Ambient emitters (fires, torches, ...): 14-byte records at *D_800DE148, D_800DDD20 of them, sorted by x or z
// (func_1517BE0C re-sorts them when the axis changes).
typedef struct {
    s16 x, y, z;
    u8 unk6;      // low nibble: voice 0..14; also the vertex colour (| 0x9F)
    u8 unk7;      // phase index into D_800DE0C0
    u8 pad8[2];
    u8 unkA;      // kind: callback table index
    u8 unkB;      // 0x21 / 0x22: flare-up state (counts down to 0x21)
    s8 unkC;      // half width
    s8 unkD;      // height / 4
} EmitterRec;

// Emitter voices: 16-byte records at D_800DDA90.
typedef struct {
    s32 romAddr;
    s32 size;
    s32 handle;
    u8 heard;     // set when an emitter of this voice was in range this frame (read by func_1517E3CC)
    u8 padD[3];
} EmitterVoice;

extern EmitterRec *D_800DE148;
extern s32 D_800DE188;              // quads built this frame
extern u32 D_800DE070[15];          // nearest emitter distance per voice (0x7FFF = none)
extern u8 D_800DDFF0[15];
extern u8 D_80096090[];             // 10-byte records: +1 u8 count, +2 u16 step
extern u16 D_80096092[];
extern s16 D_800DE0C0[15][4];        // animation phases
extern u8 D_800DE0B0[15];
extern u8 D_8008D2A0[];             // s16 callback indices, [voice kind][emitter kind] at 32 / 4 byte strides
extern u8 D_8008D25C[];             // 12-byte records, +0 callback
extern u8 D_800DE010[15];
extern u8 D_800DE020[15];
extern s16 D_800DDFB0[15][2];
extern u8 D_800DE000[15];
extern u8 D_800DE040[15];
extern s32 D_8008D254;
extern f32 D_800A7620;              // 315.0
extern f32 D_800A7624;              // degrees -> radians

typedef s32 (*EmitterCallback)(EmitterRec *e, Vtx *quad, s32 *phase, u8 *alpha);

#define EMITTER_IN_RANGE(i) \
    (byZ == 0 \
     ? (dir == 1 ? ((i) < D_800DDD20 && D_800DE148[i].x < xmax) : (dir == -1 && (i) >= 0 && xmin < D_800DE148[i].x)) \
     : (dir == 1 ? ((i) < D_800DDD20 && D_800DE148[i].z < zmax) : (dir == -1 && (i) >= 0 && zmin < D_800DE148[i].z)))

/* Emitters around (x, y, z) within radius: one camera-facing quad each (4 Vtx at D_800DDD10[D_800BE9C0]), their
 * voices loaded / marked "heard", flare-ups near the player (px, py, pz) and D_800DD8A0, phase animation, and the
 * quads turned to the camera angle (degrees). */
void func_1517C11C(s32 x, s32 y, s32 z, s32 radius, f32 angle, s32 px, s32 py, s32 pz) {
    EmitterRec *e;
    EmitterVoice *v;
    Vtx *quad;
    s32 *slot;
    EmitterCallback cb;
    s16 xmin, xmax, zmin, zmax;
    s16 target, key;
    s32 byZ, dir;
    s32 lo, hi, mid;
    s32 idx;
    u32 count, n;
    s32 dist, dist2;
    s32 voice;
    s32 phase;
    s32 step;
    s32 a;
    s32 i, k;
    s32 period;
    u8 *flags;
    s32 bit;
    s32 r;
    s32 f;
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

    // Binary search for the first emitter on the near side of the range.
    if (byZ == 0) {
        target = (dir == 1) ? xmin : xmax;
    } else {
        target = (dir == 1) ? zmin : zmax;
    }
    while (lo <= hi) {
        mid = (lo + hi) / 2;
        key = (byZ == 0) ? D_800DE148[mid].x : D_800DE148[mid].z;
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

    if (!EMITTER_IN_RANGE(mid)) {
        D_800DDD10[D_800BE9C0] = 0;
        return;
    }
    n = ((u32) D_800DDD20 < (u32) D_800DDD0C) ? (u32) D_800DDD20 : (u32) D_800DDD0C;
    D_800DDD10[D_800BE9C0] = allocate_memory(n << 6, 4, 2, 0);
    if (D_800DDD10[D_800BE9C0] == 0) {
        return;
    }

    count = 0;
    idx = mid;
    if (D_800DDD0C != 0 && EMITTER_IN_RANGE(idx)) {
        do {
            e = &D_800DE148[idx];
            dist = func_150AD9A0(e->x - x, e->y - y, e->z - z);
            if (dist < radius) {
                voice = e->unk6 & 0xF;
                if ((u32) dist < D_800DE070[voice]) {
                    D_800DE070[voice] = dist;
                }
                dist2 = func_150AD9A0(e->x - px, e->y - py, e->z - pz);
                if (dist2 >= 0x8D) {
                    if (dist2 < 0xF0) {
                        dist = radius - ((radius - dist) * (dist2 - 0x8C)) / 100;
                    }

                    // Voice: load it into its slot (26 words: handle, then 25 frame addresses), or mark it heard.
                    slot = &(&D_800DD478)[voice * 26];
                    v = &((EmitterVoice *) &D_800DDA90)[voice];
                    if (slot[0] == 0) {
                        if (v->romAddr != 0) {
                            u8 *rec = &D_80096090[D_800DDFF0[voice] * 10];
                            s32 size = rec[1] * *(u16 *) (rec + 2);

                            v->handle = func_10003C6C(v->size, 1, 2, 1, 0);
                            if (v->handle != 0) {
                                slot[0] = func_10003C6C(size, 4, 1, 0, 0);
                                if (slot[0] != 0) {
                                    func_10004514(v->romAddr, (void *) v->handle, v->size, 1);
                                    v->heard = 1;
                                    step = *(u16 *) &D_80096090[D_800DDFF0[voice] * 10 + 2];
                                    slot[1] = slot[0] + step;
                                    for (k = 2; k < 26; k++) {
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
                    phase = D_800DE0C0[0][e->unk7];
                    if (phase < 0) {
                        phase = 0;
                    }
                    // Flare-up when D_800DD8A0 (a point, x != 0) comes near.
                    if (D_800DD8A0[0] != 0 &&
                        func_150AD9A0(e->x - D_800DD8A0[0], e->y - D_800DD8A0[1], e->z - D_800DD8A0[2]) < 0x50 &&
                        D_800DDFF0[voice] == 0 && e->unkB != 0x21) {
                        e->unkB = 0x21;
                        func_15170A70(e->x, e->y + 0x44, e->z, 0, 0, 0xFF, 0);
                    }
                    if (e->unkB >= 0x21) {
                        if (e->unkB >= 0x22) {
                            e->unkB--;
                        }
                    } else if (dist < 0x30 && D_800DDFF0[voice] == 0) {
                        e->unkB = 0x22;
                        func_15170A70(e->x, e->y + 0x44, e->z, 0, 0, 0xFF, 0);
                    }
                    quad[3].v.flag = e->unkD;
                    quad[2].v.flag = e->unkC;
                    a = (u32) (radius - dist) >> 1;
                    if (a >= 0x100) {
                        a = 0xFF;
                    }
                    quad[0].v.cn[3] = a;

                    cb = *(EmitterCallback *) &D_8008D25C[*(s16 *) &D_8008D2A0[(D_800DE0B0[voice] << 5) + (e->unkA << 2)] * 12];
                    if (cb != NULL) {
                        if (cb(e, quad, &phase, &quad[0].v.cn[3]) != 0) {
                            goto next;
                        }
                    } else {
                        quad[0].v.ob[0] = e->x;
                        quad[0].v.ob[1] = e->y;
                        quad[0].v.ob[2] = e->z;
                    }
                    for (k = 0; k < 4; k++) {
                        quad[k].v.cn[0] = quad[k].v.cn[1] = quad[k].v.cn[2] = e->unk6 | 0x9F;
                    }
                    quad[1].v.cn[3] = quad[2].v.cn[3] = quad[3].v.cn[3] = quad[0].v.cn[3];
                    if (e->unkB >= 0x21) {
                        quad[0].v.flag = D_800DE010[voice] + voice * 26;
                    } else {
                        quad[0].v.flag = voice * 26 + (phase >> 8);
                    }
                    quad[1].v.flag = D_800DE020[voice];
                    quad[1].v.tc[0] = quad[2].v.tc[0] = D_800DDFB0[voice][0];
                    quad[2].v.tc[1] = quad[3].v.tc[1] = D_800DDFB0[voice][1];
                    count++;
                }
            }
        next:
            if (count >= (u32) D_800DDD0C) {
                break;
            }
            idx += dir;
        } while (EMITTER_IN_RANGE(idx));
    }
    D_800DE188 = count;

    // Phase animation per voice: ping-pong (D_800DDC04 bit set, random flips with D_800DDC08) or wrap-around.
    if (D_800BEAC0 == 0) {
        for (i = 0; i < 15; i++) {
            period = (D_800DE000[i] << 8) - 1;
            if (period < 0x101) {
                continue;
            }
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
                        D_800DE0C0[i][k] -= step;
                        if (D_800DE0C0[i][k] <= 0) {
                            D_800DE0C0[i][k] = -D_800DE0C0[i][k];
                            *flags ^= 1 << k;
                        }
                    } else {
                        D_800DE0C0[i][k] += step;
                        if (D_800DE0C0[i][k] >= period) {
                            D_800DE0C0[i][k] = period * 2 - D_800DE0C0[i][k];
                            *flags ^= 1 << k;
                        }
                    }
                }
            } else {
                step = D_800BE9E4 * 48;
                for (k = 0; k < 4; k++) {
                    D_800DE0C0[i][k] += step;
                    if (D_800DE0C0[i][k] >= period) {
                        D_800DE0C0[i][k] -= period;
                    }
                }
            }
        }
    }

    // A random visible emitter of the first frame sparks.
    r = (u32) func_151EFDD0() % (u32) D_800DDD0C;
    if ((u32) r < (u32) D_800DE188) {
        quad = (Vtx *) (D_800DDD10[D_800BE9C0] + r * 64);
        f = (u16) quad[0].v.flag;
        if (f % 26 == 0 && D_800DDFF0[f / 26] == 0) {
            func_15170A70(quad[0].v.ob[0], quad[0].v.ob[1] + 0x44, quad[0].v.ob[2], 0, 1, 0xFF, 0);
        }
    }

    // Turn every quad to the camera: corners at +-(w cos, w sin) around the base, top at y + 4 * height.
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
            h = (u16) quad[3].v.flag << 2;
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
