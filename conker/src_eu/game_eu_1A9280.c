#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 game_gu_random();
extern u8 D_80096091[];
/* was func_1517BA70 */
s32 ambient_placer_flicker(u8 *arg0, u8 *arg1, s32 *arg2, s32 arg3) {
    s32 d;
    s32 lim;
    s32 r;

    *arg2 = *arg2 * 3 / 2;
    lim = D_80096091[arg0[8] * 0xA] << 8;
    if (*arg2 >= lim) {
        *arg2 -= lim;
    }
    *(s16 *)(arg1 + 0) = *(s16 *)(arg0 + 0);
    *(s16 *)(arg1 + 2) = *(s16 *)(arg0 + 2);
    *(s16 *)(arg1 + 4) = *(s16 *)(arg0 + 4);
    d = 0x29 - *(s8 *)(arg0 + 0xD);
    if (d == 0) {
        *(s8 *)(arg0 + 0xD) = *(s8 *)(arg0 + 0xD) - game_gu_random() % 8 + 4;
    } else if (d < 0) {
        r = game_gu_random();
        *(s8 *)(arg0 + 0xD) = *(s8 *)(arg0 + 0xD) - (game_gu_random() % -d >> 1) - r % 8 + 4;
    } else {
        r = game_gu_random();
        *(s8 *)(arg0 + 0xD) += (game_gu_random() % d >> 1) + r % 8 - 4;
    }
    *(s16 *)(arg1 + 0) = *(s16 *)(arg0 + 0);
    *(s16 *)(arg1 + 2) = *(s16 *)(arg0 + 2);
    *(s16 *)(arg1 + 4) = *(s16 *)(arg0 + 4);
    return 0;
}

/* was func_1517BC58 */
s32 ambient_placer_rise_fade(s16 *arg0, s16 *arg1, s32 *arg2, u8 *arg3) {
    s32 t;
    if (*arg2 >= 0x600) {
        arg1[1] = (arg0[1] + (*arg2 >> 6)) - 0x18;
        arg1[0] = (arg0[0] + (*arg2 >> 8)) - 6;
        t = ((*arg3 << 7) / ((*arg2 >> 6) - 0x17)) >> 4;
        if (t < *arg3) {
            *arg3 = t;
        }
        *arg2 = 0x600;
    } else {
        arg1[0] = arg0[0];
        arg1[1] = arg0[1];
    }
    arg1[2] = arg0[2];
    return 0;
}

/* was func_1517BD18 */
s32 ambient_placer_loop_mid(s16 *arg0, s16 *arg1, s32 *arg2, s32 arg3) {
    if (*arg2 >= 0x300) {
        if (*arg2 >= 0x501) {
            *arg2 -= 0x200;
        } else {
            *arg2 = 0x300;
        }
    }
    arg1[0] = arg0[0];
    arg1[1] = arg0[1];
    arg1[2] = arg0[2];
    return 0;
}

/* was func_1517BD68 */
s32 ambient_placer_hop(s16 *arg0, s16 *arg1, s32 *arg2, s32 arg3) {
    s32 v;
    s32 d;

    v = *arg2;
    if (v >= 0xD00) {
        return 1;
    }
    d = v - 0x600;
    if (v >= 0x100) {
        d = 0x190000 - d * d;
        arg1[1] = arg0[1] + d / 7680;
        v = *arg2;
        if (v >= 0x200) {
            if (v >= 0xA01) {
                *arg2 = v - 0x800;
            } else {
                *arg2 = 0x200;
            }
        }
    } else {
        arg1[1] = arg0[1];
    }
    arg1[0] = arg0[0];
    arg1[2] = arg0[2];
    return 0;
}

typedef struct {
    s16 pos[3];     /* +0 x, y, z */
    u8 mode;        /* +6 mode << 5 | slot (low nibble: the slot / voice 0..14) */
    u8 phase;       /* +7 index into D_800DE0C0 (animation phase) */
    u16 sound;      /* +8 */
    u8 kind;        /* +A placer kind (column of D_8008D2A0) */
    u8 flare;       /* +B 0x21 / 0x22: flare-up state (0x22 counts down to 0x21) */
    s8 halfWidth;   /* +C quad half width */
    s8 height;      /* +D quad height / 4 */
} AmbientEmitterRec;  /* 14 bytes (ambient_emitter_add layout) */
extern AmbientEmitterRec *D_800DE148;
extern s32 D_8008D254;   /* sort key: 0 = x, else z */

/* per-frame updater of a placer type: may move the quad base / phase / alpha; non-zero = drop the emitter */
typedef s32 (*AmbientUpdater)(AmbientEmitterRec *e, Vtx *quad, s32 *phase, u8 *alpha);
typedef struct {
    s32 romAddr;    /* +0 sample data in ROM (0 = none) */
    s32 size;       /* +4 */
    s32 handle;     /* +8 loaded sample (0 = none) */
    u8 heard;       /* +C an emitter of this voice was in range this frame (cleared by ambient_slots_refresh) */
    u8 padD[3];
} AmbientVoice;     /* D_800DDA90[15] */
extern struct { void *place; AmbientUpdater update; s32 unk8; } D_8008D258[];  /* placers by type (.game_data) */
extern s16 D_8008D2A0[][8][2];  /* per placement row and kind: { placer type, placer param } (.game_data) */
extern u8 D_80096090[];         /* per sound id, 10 bytes: +1 u8 frame count, +2 u16 frame size (.game_data) */
extern u8 D_800DE0B0[15];       /* per slot: placement row */
extern s16 D_800DE0C0[];        /* 15 slots x 4 animation phases (<< 8) */
extern u32 D_800DE070[15];      /* nearest emitter distance per slot (0x7FFF = none) */
extern u8 D_800DDFF0[15];       /* per slot: sound id */
extern u8 D_800DE000[15];       /* per slot: phase period >> 8 */
extern u8 D_800DE010[15];       /* per slot: flare-up frame */
extern u8 D_800DE020[15];
extern s16 D_800DDFB0[15][2];   /* per slot: texture size s, t */
extern u8 D_800DE040[15];       /* per slot: ping-pong direction bits of the 4 phases */
extern s32 D_800DE188;          /* quads built this frame */
extern f32 D_800A7620;          /* 315.0 */
extern f32 D_800A7624;          /* degrees -> radians */
f32 sinf(f32);
f32 cosf(f32);
void *allocate_memory(s32, s32, s32, s32);
s32 approx_dist3_int(s32 dx, s32 dy, s32 dz);
void particle_spark_spawn(s32 x, s32 y, s32 z, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void heap_free(s32);
void ambient_emitters_sort(s32 lo, s32 hi);
s32 game_gu_random(void);

// ambient_emitters_sort: quicksort of the emitter records D_800DE148[lo..hi] (14 bytes) by x, or by z when
// D_8008D254 is set; pivot = the last record (Rare's partition loop, literal).
/* was func_1517BE0C */
void ambient_emitters_sort(s32 lo, s32 hi) {
    AmbientEmitterRec tmp;
    s32 i = lo;
    s32 j = hi;
    s32 k;
    s16 pivot;

    if (!(lo < hi)) {
        return;
    }
    for (;;) {
        k = (D_8008D254 != 0) ? 2 : 0;
        pivot = D_800DE148[hi].pos[k];
        while (D_800DE148[i].pos[k] < pivot && i < hi) {
            i++;
        }
        while (pivot < D_800DE148[j].pos[k] && lo < j) {
            j--;
        }
        if (!(i < j)) {
            break;
        }
        tmp = D_800DE148[i];
        D_800DE148[i] = D_800DE148[j];
        D_800DE148[j] = tmp;
        i++;
        j--;
    }
    tmp = D_800DE148[i];
    D_800DE148[i] = D_800DE148[hi];
    D_800DE148[hi] = tmp;
    ambient_emitters_sort(lo, i - 1);
    ambient_emitters_sort(i + 1, hi);
}

// ambient_emitters_update: per frame, the level's ambient emitters (fires, torches: the records sorted by
// ambient_emitters_sort) within radius of (x, y, z) along the axis the camera angle (degrees) faces: nearest distance per
// slot (D_800DE070), the slot's voice loaded (D_800DD478 slot words + D_800DDA90 voice) or marked "heard" (read by
// ambient_slots_refresh), flare-ups near the point D_800DD8A0 / close to the camera, one camera-facing 4-Vtx quad per
// emitter at D_800DDD10[D_800BE9C0] (count D_800DE188; emitters within 0x8C of the player (px, py, pz) are skipped,
// fade in up to 0xF0), the per-slot phase animation, a random spark, and finally the quads turned to the angle.
// Clears D_800DD8A0[0] when quads were allocated.
/* was func_1517C11C */
void ambient_emitters_update(s32 x, s32 y, s32 z, s32 radius, f32 angle, s32 px, s32 py, s32 pz) {
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
        ambient_emitters_sort(0, D_800DDD20 - 1);
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
            dist = approx_dist3_int(e->pos[0] - x, e->pos[1] - y, e->pos[2] - z);
            if (dist >= radius) {
                goto next;
            }
            voice = e->mode & 0xF;
            if ((u32) dist < D_800DE070[voice]) {
                D_800DE070[voice] = dist;
            }
            dist2 = approx_dist3_int(e->pos[0] - px, e->pos[1] - py, e->pos[2] - pz);
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
                    v->handle = heap_alloc_tagged(v->size, 1, 2, 1, 0);
                    if (v->handle != 0) {
                        slot[0] = heap_alloc_tagged(n, 4, 1, 0, 0);
                        if (slot[0] != 0) {
                            rom_dma_read(v->romAddr, (void *) v->handle, v->size, 1);
                            v->heard = 1;
                            step = *(u16 *) &D_80096090[D_800DDFF0[voice] * 10 + 2];
                            for (k = 1; k < 26; k++) {
                                slot[k] = slot[k - 1] + step;
                            }
                        } else {
                            heap_free(v->handle);
                        }
                    }
                }
            } else if (v->heard == 0) {
                v->heard = 1;
                heap_set_block_tag((s32 *) slot[0], 4);
            }

            quad = (Vtx *) (D_800DDD10[D_800BE9C0] + count * 64);
            phase = D_800DE0C0[e->phase];
            if (phase < 0) {
                phase = 0;
            }
            // Flare-up when the point D_800DD8A0 (set when x != 0) comes near, or when the camera is close.
            if (D_800DD8A0[0] != 0 &&
                approx_dist3_int(e->pos[0] - D_800DD8A0[0], e->pos[1] - D_800DD8A0[1], e->pos[2] - D_800DD8A0[2]) < 0x50 &&
                D_800DDFF0[voice] == 0 && e->flare != 0x21) {
                e->flare = 0x21;
                particle_spark_spawn(e->pos[0], e->pos[1] + 0x44, e->pos[2], 0, 0, 0xFF, 0);
            }
            if (e->flare >= 0x21) {
                if (e->flare >= 0x22) {
                    e->flare--;
                }
            } else if (dist < 0x30 && D_800DDFF0[voice] == 0) {
                e->flare = 0x22;
                particle_spark_spawn(e->pos[0], e->pos[1] + 0x44, e->pos[2], 0, 0, 0xFF, 0);
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
    if (g_game_paused == 0) {
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
                    r = game_gu_random() % 10;
                    if (r == 0) {
                        *flags |= game_gu_random() % 16;
                        step = 0;
                    } else if (r == 1) {
                        *flags &= game_gu_random() % 16;
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
    r = (u32) game_gu_random() % (u32) D_800DDD0C;
    if ((u32) r < (u32) D_800DE188) {
        quad = (Vtx *) (D_800DDD10[D_800BE9C0] + r * 64);
        frame = quad[0].v.flag;
        if (frame % 26 == 0 && D_800DDFF0[frame / 26] == 0) {
            particle_spark_spawn(quad[0].v.ob[0], quad[0].v.ob[1] + 0x44, quad[0].v.ob[2], 0, 1, 0xFF, 0);
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

// the definition is void (asm: v0 is not a result); one signature for wasm
void heap_free(s32);
s32 rzip_inflate(s32, s32, u32);

/* was func_1517D534 */
void ambient_slots_free_all(void)
{
  int pad;
  s32 *var_s0;
  s32 temp_a0;
  s32 temp_a1;
  s32 var_s1;
 do { var_s0 = &D_800DDA90; var_s1 = 0; do { temp_a0 = *((s32 *) (((u8 *) var_s0) + 8)); if (temp_a0 != 0) { temp_a1 = (&D_800DD478)[var_s1 * 0x1A]; if (temp_a1 != 0) { rzip_inflate(temp_a0, temp_a1, D_8003809C); heap_free(*((s32 *) (((u8 *) var_s0) + 8))); } *((s32 *) (((u8 *) var_s0) + 8)) = 0; } var_s1 += 1; var_s0 += 4; } while (var_s1 != 0xF); } while (0);
}

extern s32 D_8008D340;
// sprite_billboard_quad_draw: appends one upright textured quad to the display list gfx and returns the new end.
// The quad takes vertex slot D_800DE188 of this frame's quad buffer D_800DDD10[D_800BE9C0] (nothing is drawn once
// D_800DDD0C slots are used). It stands on (x, y, z), turned by angle (degrees) around the vertical axis, half width
// radius, height 2 * halfHeight. tex is a w x h RGBA16 image followed by its w x h I4 mask: both are loaded with one
// LoadBlock (rows (h * 5 + 3) >> 2), tile 0 = the image, tile 1 = the mask (TMEM offset w * h / 4 words).
/* was func_1517D5E4 */
s32 ambient_billboard_quad_draw(s32 gfx, s16 x, s16 y, s16 z, f32 angle, s32 radius, s32 halfHeight, s32 w, s32 h, s32 tex) {
    u32 *g = (u32 *) gfx;
    u32 slot = D_800DE188;
    Vtx *quad = (Vtx *) (D_800DDD10[D_800BE9C0] + slot * 64);
    u8 tw = w;
    u8 th = h;
    s16 dx;
    s16 dz;
    s16 top;
    f32 r;
    s32 loadRows;
    s32 lrs;
    s32 words;
    s32 dxt;

    if (slot >= (u32) D_800DDD0C) {
        return gfx;
    }
    g[0] = 0xDE000000; /* gSPDisplayList(sprite render setup) */
    g[1] = (u32) &D_8008D340;
    g[2] = 0xFCFFFFFF; /* gDPSetCombineLERP */
    g[3] = 0xFFFCF438;
    g[4] = 0xD9FFFBFF; /* gSPClearGeometryMode(G_CULL_BACK) */
    g[5] = 0;
    g[6] = 0xEF182C3F; /* gDPSetOtherMode */
    g[7] = 0x0C184B50;
    g += 8;

    angle *= 0.017453292f;
    r = radius;
    dx = (s32) (cosf(angle) * r);
    dz = (s32) (sinf(angle) * r);
    quad[0].v.ob[0] = quad[3].v.ob[0] = x + dx;
    quad[0].v.ob[1] = quad[1].v.ob[1] = y;
    quad[0].v.ob[2] = quad[3].v.ob[2] = z - dz;
    quad[1].v.ob[0] = quad[2].v.ob[0] = x - dx;
    top = y + halfHeight + halfHeight;
    quad[2].v.ob[1] = quad[3].v.ob[1] = top;
    quad[1].v.ob[2] = quad[2].v.ob[2] = z + dz;
    quad[1].v.tc[0] = quad[2].v.tc[0] = (tw << 5) - 1;
    quad[2].v.tc[1] = quad[3].v.tc[1] = (th << 5) - 1;

    loadRows = (th * 5 + 3) >> 2;
    lrs = tw * loadRows - 1;
    if (lrs >= 0x7FF) {
        lrs = 0x7FF;
    }
    words = (tw * 2) / 8;
    if (words <= 0) {
        words = 1;
    }
    dxt = (words + 0x7FF) / words;

    g[0] = 0x01004008; /* gSPVertex(quad, 4, 0) */
    g[1] = D_800DDD10[D_800BE9C0] + slot * 64;
    g[2] = 0xFD100000; /* gDPSetTextureImage(RGBA, 16b, 1, tex) */
    g[3] = tex;
    g[4] = 0xF5100000; /* gDPSetTile(G_TX_LOADTILE) */
    g[5] = 0x07080200;
    g[6] = 0xE6000000; /* gDPLoadSync */
    g[7] = 0;
    g[8] = 0xF3000000; /* gDPLoadBlock(G_TX_LOADTILE, 0, 0, lrs, dxt) */
    g[9] = 0x07000000 | ((lrs & 0xFFF) << 12) | (dxt & 0xFFF);
    g[10] = 0xE7000000; /* gDPPipeSync */
    g[11] = 0;
    g[12] = 0xF5100000 | ((((tw * 2 + 7) >> 3) & 0x1FF) << 9); /* gDPSetTile 0: RGBA16 image */
    g[13] = 0x00080200;
    g[14] = 0xF2000000; /* gDPSetTileSize 0 */
    g[15] = ((((tw - 1) << 2) & 0xFFF) << 12) | (((loadRows - 1) << 2) & 0xFFF);
    g[16] = 0xF5800000 | (((((tw >> 1) + 7) >> 3) & 0x1FF) << 9) | (((tw * th) >> 2) & 0x1FF); /* tile 1: I4 mask */
    g[17] = 0x01080200;
    g[18] = 0xF2000000; /* gDPSetTileSize 1 */
    g[19] = 0x01000000 | ((((tw - 1) << 2) & 0xFFF) << 12) | (((th - 1) << 2) & 0xFFF);

    quad = (Vtx *) (D_800DDD10[D_800BE9C0] + slot * 64);
    quad[0].v.flag = quad[1].v.flag = quad[2].v.flag = quad[3].v.flag = 0;

    g[20] = 0x05000402; /* gSP1Triangle(0, 2, 1) */
    g[21] = 0;
    g[22] = 0x05000604; /* gSP1Triangle(0, 3, 2) */
    g[23] = 0;
    g[24] = 0xD9FFFFFF; /* gSPSetGeometryMode(G_SHADING_SMOOTH) */
    g[25] = 0x00200000;
    D_800DE188++;
    return (s32) (g + 26);
}

extern u8 D_800DE158[];

/* was func_1517DAE8 */
void ambient_extra_flame_queue(s16 arg0, s16 arg1, s16 arg2, f32 arg3, s32 arg4, s32 arg5, u8 arg6) {
    u8 *p;
    s32 i = D_8008CEB0;

    if (i < 3) {
        p = D_800DE158 + i * 16;
        *(s16 *)(p + 0) = arg0;
        *(s16 *)(p + 2) = arg1;
        *(s16 *)(p + 4) = arg2;
        *(f32 *)(p + 0xC) = arg3;
        *(s16 *)(p + 8) = arg4;
        *(s16 *)(p + 0xA) = arg5;
        p[6] = arg6;
        D_8008CEB0 = i + 1;
    }
}


/* was func_1517DB6C */
void ambient_extra_flame_queue_cam(s16 arg0, s16 arg1, s16 arg2, s32 arg3, s32 arg4, s32 arg5) {
    ambient_extra_flame_queue(arg0, arg1, arg2, D_800DBFF0[arg3].unk380, arg4, arg5, (s32) D_800DDD1C >> 3);
}

typedef struct { s16 x, y, z; u8 idx; u8 pad7; u16 a; u16 b; f32 s; } EntDC00;
extern s32 D_800DE188;
s32 ambient_billboard_quad_draw(s32, s16, s16, s16, f32, s32, s32, s32, s32, s32);

/* was func_1517DC00 */
s32 ambient_extra_flames_draw(s32 arg0, u16 *arg1) {
    s32 saved;

    saved = D_800DE188;
    D_800DDD1C += 5;
    
    if (D_800DDD1C >= 200) {
        D_800DDD1C -= 200;
    }
    while (D_8008CEB0 != 0) {
        D_8008CEB0--;
        if (arg1 != 0) {
            arg0 = ambient_billboard_quad_draw(arg0, ((EntDC00 *)D_800DE158)[D_8008CEB0].x, ((EntDC00 *)D_800DE158)[D_8008CEB0].y, ((EntDC00 *)D_800DE158)[D_8008CEB0].z, ((EntDC00 *)D_800DE158)[D_8008CEB0].s, ((EntDC00 *)D_800DE158)[D_8008CEB0].a, ((EntDC00 *)D_800DE158)[D_8008CEB0].b, 16, 32, (s32)(arg1 + ((EntDC00 *)D_800DE158)[D_8008CEB0].idx * 640));
        }
    }
    D_800DE188 = saved;
    return arg0;
}

s32 tint_emit_prim_env_colors(s32, s32, s32, s32);
extern s32 D_8008D340;
extern u16 *D_800DE154;

/* was func_1517D7B0 */
void ambient_flames_draw(s32 *arg0, s32 arg1) {
    u32 sp48;
    u32 sp44;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_ra;
    s32 temp_s3;
    s32 temp_t1;
    s32 temp_t1_2;
    s32 temp_t4;
    s32 temp_t6;
    s32 temp_t7_2;
    s32 temp_t7_3;
    s32 temp_t8;
    s32 temp_t8_2;
    s32 temp_t8_3;
    s32 temp_t9;
    s32 temp_v0;
    s32 temp_v0_10;
    s32 temp_v0_11;
    s32 temp_v0_12;
    s32 temp_v0_13;
    s32 temp_v0_14;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v0_8;
    s32 temp_v0_9;
    s32 var_a3;
    s32 var_s1;
    s32 var_t3;
    s32 var_t4;
    s32 var_v0;
    s32 var_v0_2;
    u16 temp_a2_2;
    u16 temp_a3;
    u16 var_s2;
    u32 temp_t7;
    u32 temp_v0_2;
    u32 var_s5;
    u32 var_s5_2;
    u32 var_t5;
    u32 var_v1;
    u8 *temp_a2;
    u8 *temp_a3_2;

    var_s2 = 0xFFFF;
    if (D_800DDD10[D_800BE9C0] != 0) {
        *arg0 = ambient_extra_flames_draw(*arg0, D_800DE154);
        if ((D_800DDD20 != 0) && (D_800DE188 != 0)) {
            temp_v0 = *arg0;
            *arg0 = temp_v0 + 8;
            (*(s32 **)((u8 *)temp_v0 + 4)) = &D_8008D340;
            (*(s32 *)((u8 *)temp_v0 + 0)) = 0xDE000000;
            sp44 = 0;
            var_v1 = 0;
            *arg0 = tint_emit_prim_env_colors(*arg0, 0xFF, 0xFF, 0);
            sp48 = 0;
            if (D_800DE188 != 0) {
                do {
                    var_t3 = 0;
                    var_s5 = 0;
                    temp_v0_2 = D_800DE188 - sp48;
                    var_t5 = temp_v0_2 * 4;
                    if (temp_v0_2 >= 5U) {
                        var_t5 = 0x10;
                    }
                    if (var_t5 != 0) {
                        var_v0 = 0;
                        do {
                            if (arg1 != (*(u16 *)((u8 *)((D_800DDD10[D_800BE9C0] + (sp48 << 6) + var_v0)) + 0x16))) {
                                var_t3 |= 1 << var_s5;
                            }
                            var_s5 += 4;
                            var_v0 += 0x40;
                        } while (var_s5 < var_t5);
                    }
                    if (var_t3 != 0x1111) {
                        temp_v0_3 = *arg0;
                        *arg0 = temp_v0_3 + 8;
                        (*(s32 *)((u8 *)temp_v0_3 + 0)) = (s32) (((var_t5 & 0xFF) << 0xC) | 0x01000000 | ((var_t5 & 0x7F) * 2));
                        temp_t8 = sp48 * 4;
                        (*(s32 **)((u8 *)temp_v0_3 + 4)) = (s32 *) (D_800DDD10[D_800BE9C0] + (temp_t8 * 0x10));
                        var_s5_2 = 0;
                        if (var_t5 != 0) {
                            do {
                                var_s5_2 += 4;
                                if ((var_v1 < var_t5) && ((var_v0_2 = var_v1 * 0x10, temp_a0 = D_800DDD10[D_800BE9C0] + (temp_t8 * 0x10), (var_s2 != (*(u16 *)((u8 *)((temp_a0 + var_v0_2)) + 6)))) || ((1 << var_v1) & var_t3))) {
loop_16:
                                    var_v1 += 4;
                                    var_v0_2 += 0x40;
                                    if (var_v1 < var_t5) {
                                        if ((var_s2 != (*(u16 *)((u8 *)((temp_a0 + var_v0_2)) + 6))) || ((1 << var_v1) & var_t3)) {
                                            goto loop_16;
                                        }
                                    }
                                }
                                if ((var_v1 >= var_t5) && (var_t3 != 0x1111)) {
                                    var_v1 = 0;
                                    if (var_t3 & 1) {
                                        do {
                                            var_v1 += 4;
                                        } while ((1 << var_v1) & var_t3);
                                    }
                                    temp_a2 = D_800DDD10[D_800BE9C0] + (temp_t8 * 0x10) + (var_v1 * 0x10);
                                    temp_a3 = (*(u16 *)((u8 *)temp_a2 + 6));
                                    if ((var_s2 != temp_a3) && (var_v1 < var_t5)) {
                                        var_s2 = temp_a3;
                                        temp_t8_2 = (s32) ((*(s16 *)((u8 *)temp_a2 + 0x28)) + 1) >> 5;
                                        temp_t7_2 = (s32) ((*(s16 *)((u8 *)temp_a2 + 0x2A)) + 1) >> 5;
                                        temp_v0_4 = *arg0;
                                        *arg0 = temp_v0_4 + 8;
                                        (*(s32 *)((u8 *)temp_v0_4 + 0)) = 0xFD100000;
                                        (*(s32 **)((u8 *)temp_v0_4 + 4)) = (s32 *) (&D_800DD478)[var_s2];
                                        temp_a1 = *arg0;
                                        *arg0 = temp_a1 + 8;
                                        (*(s32 **)((u8 *)temp_a1 + 4)) = (s32 *)0x07080200;
                                        (*(s32 *)((u8 *)temp_a1 + 0)) = 0xF5100000;
                                        temp_t1 = *arg0;
                                        *arg0 = temp_t1 + 8;
                                        (*(s32 **)((u8 *)temp_t1 + 4)) = NULL;
                                        (*(s32 *)((u8 *)temp_t1 + 0)) = 0xE6000000;
                                        temp_t6 = (s32) (((s16) temp_t7_2 * 5) + 3) >> 2;
                                        temp_s3 = *arg0;
                                        *arg0 = temp_s3 + 8;
                                        temp_ra = (s16) temp_t8_2 * 2;
                                        var_t4 = 0x7FF;
                                        (*(s32 *)((u8 *)temp_s3 + 0)) = 0xF3000000;
                                        temp_a0_2 = ((s16) temp_t8_2 * temp_t6) - 1;
                                        if (temp_a0_2 < 0x7FF) {
                                            var_t4 = temp_a0_2;
                                        }
                                        temp_v0_5 = temp_ra / 8;
                                        var_s1 = temp_v0_5;
                                        if (temp_v0_5 <= 0) {
                                            var_s1 = 1;
                                        }
                                        if (temp_v0_5 <= 0) {
                                            var_a3 = 1;
                                        } else {
                                            var_a3 = temp_v0_5;
                                        }
                                        (*(s32 **)((u8 *)temp_s3 + 4)) = (s32 *) ((((s32) (var_s1 + 0x7FF) / var_a3) & 0xFFF) | 0x07000000 | ((var_t4 & 0xFFF) << 0xC));
                                        temp_v0_6 = *arg0;
                                        *arg0 = temp_v0_6 + 8;
                                        (*(s32 **)((u8 *)temp_v0_6 + 4)) = NULL;
                                        (*(s32 *)((u8 *)temp_v0_6 + 0)) = 0xE7000000;
                                        temp_v0_7 = *arg0;
                                        *arg0 = temp_v0_7 + 8;
                                        (*(s32 **)((u8 *)temp_v0_7 + 4)) = (s32 *)0x80200;
                                        (*(s32 *)((u8 *)temp_v0_7 + 0)) = (s32) (((((s32) (temp_ra + 7) >> 3) & 0x1FF) << 9) | 0xF5100000);
                                        temp_v0_8 = *arg0;
                                        *arg0 = temp_v0_8 + 8;
                                        (*(s32 *)((u8 *)temp_v0_8 + 0)) = 0xF2000000;
                                        temp_t1_2 = ((((s16) temp_t8_2 - 1) * 4) & 0xFFF) << 0xC;
                                        (*(s32 **)((u8 *)temp_v0_8 + 4)) = (s32 *) (temp_t1_2 | (((temp_t6 - 1) * 4) & 0xFFF));
                                        temp_v0_9 = *arg0;
                                        *arg0 = temp_v0_9 + 8;
                                        (*(s32 *)((u8 *)temp_v0_9 + 0)) = (s32) (((((s32) (((s16) temp_t8_2 >> 1) + 7) >> 3) & 0x1FF) << 9) | 0xF5800000 | (((s32) ((s16) temp_t8_2 * (s16) temp_t7_2) >> 2) & 0x1FF));
                                        (*(s32 **)((u8 *)temp_v0_9 + 4)) = (s32 *)0x01080200;
                                        temp_v0_10 = *arg0;
                                        *arg0 = temp_v0_10 + 8;
                                        (*(s32 *)((u8 *)temp_v0_10 + 0)) = 0xF2000000;
                                        (*(s32 **)((u8 *)temp_v0_10 + 4)) = (s32 *) (temp_t1_2 | 0x01000000 | ((((s16) temp_t7_2 - 1) * 4) & 0xFFF));
                                    }
                                }
                                if (var_v1 < var_t5) {
                                    temp_t4 = 1 << var_v1;
                                    if (!(temp_t4 & var_t3)) {
                                        temp_t8_3 = (temp_t8 + var_v1) * 0x10;
                                        temp_a1_2 = var_v1 * 2;
                                        (*(s16 *)((u8 *)((D_800DDD10[D_800BE9C0] + temp_t8_3)) + 0x36)) = 0;
                                        var_t3 |= temp_t4;
                                        temp_a3_2 = D_800DDD10[D_800BE9C0] + temp_t8_3;
                                        temp_a2_2 = (*(u16 *)((u8 *)temp_a3_2 + 0x36));
                                        (*(u16 *)((u8 *)temp_a3_2 + 0x26)) = temp_a2_2;
                                        (*(u16 *)((u8 *)((D_800DDD10[D_800BE9C0] + temp_t8_3)) + 0x16)) = temp_a2_2;
                                        temp_t7_3 = (temp_a1_2 & 0xFF) << 0x10;
                                        (*(u16 *)((u8 *)((D_800DDD10[D_800BE9C0] + temp_t8_3)) + 6)) = temp_a2_2;
                                        temp_v0_11 = *arg0;
                                        temp_t9 = (temp_a1_2 + 4) & 0xFF;
                                        *arg0 = temp_v0_11 + 8;
                                        (*(s32 *)((u8 *)temp_v0_11 + 0)) = (s32) (temp_t7_3 | (temp_t9 << 8) | ((temp_a1_2 + 2) & 0xFF) | 0x05000000);
                                        (*(s32 **)((u8 *)temp_v0_11 + 4)) = NULL;
                                        temp_v0_12 = *arg0;
                                        *arg0 = temp_v0_12 + 8;
                                        (*(s32 **)((u8 *)temp_v0_12 + 4)) = NULL;
                                        (*(s32 *)((u8 *)temp_v0_12 + 0)) = (s32) (temp_t7_3 | (((temp_a1_2 + 6) & 0xFF) << 8) | temp_t9 | 0x05000000);
                                    }
                                }
                            } while (var_s5_2 < var_t5);
                        }
                    }
                    temp_t7 = sp48 + 4;
                    sp48 = temp_t7;
                } while (temp_t7 < (u32) D_800DE188);
            }
            temp_v0_13 = *arg0;
            *arg0 = temp_v0_13 + 8;
            (*(s32 **)((u8 *)temp_v0_13 + 4)) = (s32 *)0x200000;
            (*(s32 *)((u8 *)temp_v0_13 + 0)) = 0xD9FFFFFF;
            temp_v0_14 = *arg0;
            *arg0 = temp_v0_14 + 8;
            (*(s32 **)((u8 *)temp_v0_14 + 4)) = NULL;
            (*(s32 *)((u8 *)temp_v0_14 + 0)) = 0xE7000000;
        }
    }
}
void ambient_emitters_update(s32, s32, s32, s32, f32, s32, s32, s32);

/* Per-frame refresh of the 15 positional sound slots (records of 0x68 bytes at D_800DD478, word 0 = active) and
 * their voices (16-byte records at D_800DDA90: +8 voice handle, +0xC "heard this frame"). With D_800DDD20 set,
 * every "heard" flag is cleared, ambient_emitters_update marks the slots in range of object 0 / player 0 (radius 1500,
 * player +0x380, +0x2F8 position), and each active slot that was not marked is switched off together with its
 * voice handle. */
/* was func_1517E3CC */
void ambient_slots_refresh(void) {
    u8 *voices = (u8 *) &D_800DDA90;
    u8 *slots = (u8 *) &D_800DD478;
    s32 i;

    if (D_800DDD20 == 0) {
        return;
    }
    for (i = 0; i < 15; i++) {
        voices[i * 0x10 + 0xC] = 0;
    }
    ambient_emitters_update((s32) g_objects[0].x_position, (s32) g_objects[0].y_position, (s32) g_objects[0].z_position,
                  1500, D_800DBFF0->unk380, (s32) D_800DBFF0->unk2F8, (s32) D_800DBFF0->unk2FC,
                  (s32) D_800DBFF0->unk300);
    for (i = 0; i < 15; i++) {
        if (*(s32 *) (slots + i * 0x68) != 0 && voices[i * 0x10 + 0xC] == 0) {
            *(s32 *) (slots + i * 0x68) = 0;
            *(s32 *) (voices + i * 0x10 + 8) = 0;
        }
    }
}

/* was func_1517E5CC */
void ambient_flare_point_set(s32 arg0, s32 arg1, s32 arg2) {
    D_800DD8A0[0] = arg0;
    D_800DD8A0[1] = arg1;
    D_800DD8A0[2] = arg2;
}
