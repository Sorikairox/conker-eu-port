#include <ultra64.h>
#include "functions.h"
#include "variables.h"


typedef struct {
    u8 *p;
    u8 u4;
    s8 u5;
    u8 pad6[2];
    f32 v8[3];
    f32 u14;
    s16 u18;
    s16 u1A;
    s16 u1C;
    u8 pad1E[2];
    f32 u20;
    f32 u24;
    s8 u28;
    s8 u29;
    s8 u2A;
    s8 u2B;
    u8 u2C;
    s8 u2D;
    s8 u2E;
    u8 pad2F;
} S3940;
s32 ribbon_trail_spawn();
s32 light_create_obj_joint(u8 *, s32, f32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, u8, s32);
void obj_attached_effect_start(u8 *, u8);
void owner_smoke_start(u8 *arg0, u8 arg1);
/* was func_151A3940 */
void obj_burning_fx_start(u8 *arg0, u8 arg1) {
    S3940 s;
    f32 v[3];

    s.p = arg0;
    s.u4 = arg0[0x3B];
    s.u5 = 1;
    s.v8[0] = 0.0f;
    s.v8[1] = 0.0f;
    s.v8[2] = 0.0f;
    s.u2B = 1;
    s.u2C = 0xFF;
    s.u2D = 8;
    s.u2E = 0x1F;
    s.u18 = 0xAA;
    s.u1A = 0x28;
    s.u1C = 7;
    s.u28 = 2;
    s.u29 = 4;
    s.u2A = 1;
    s.u14 = 0.018000001f;
    s.u20 = 30.0f;
    s.u24 = 0.98100007f;
    ribbon_trail_spawn(&s, arg1);
    obj_attached_effect_start(arg0, arg1);
    owner_smoke_start(arg0, arg1);
    actor_sound_play(0x1AA, arg0, 0x55F0, 0x3E8, 0xFA0);
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    light_create_obj_joint(arg0, 1, v, 2, 0x12C, 0x50, 0xFF, 0xFF, 0x75, 0xFF, 0, -1, 0, 0, arg1, 1);
}

typedef struct { f32 x, y, z; } V33AB4;
typedef struct { V33AB4 pos; s16 u0C; u16 u0E; s32 u10; s8 u14; s8 u15; u8 pad16[2]; s32 u18; } SA3AB4;
typedef struct {
    u8 raw[0x30];
    u8 u30;
    u8 pad31[3];
    V33AB4 u34;
    f32 u40;
    u8 u44;
    u8 pad45[3];
    f32 u48;
    u8 u4C;
    u8 pad4D[3];
} SB3AB4;

s32 ribbon_trail_bone_pos(u8 *arg0, u8 *arg1);

s32 ribbon_trail_spawn(arg0, arg1) u8 *arg0; u8 arg1; {
    SA3AB4 a;
    SB3AB4 b;
    u8 *r;

    if (*(s32 *)arg0 == 0) {
        return 0;
    }
    memcpy(&b, arg0, 0x30);
    b.u44 = 0;
    a.u15 = 0x32;
    a.u0E = 2;
    a.u0C = 1000;
    b.u30 = 6;
    b.u4C = 0;
    b.u40 = 0.0f;
    b.u48 = 0.0f;
    if (ribbon_trail_bone_pos((u8 *)&b, (u8 *)&a.pos)) {
        b.u34 = a.pos;
        a.u0E |= 4;
    }
    a.u10 = 8;
    r = (u8 *)fxrec_spawn(&a, 0x50, 0x18, 6, 6, 6, 0, 0, 0, arg1, 0);
    if (r != NULL) {
        memcpy(*(void **)(r + 0x98), &b, 0x50);
    }
    return (s32)r;
}

typedef struct { f32 x, y, z; } V3;
typedef struct {
    V3 pos;
    f32 unkC;
    s16 unk10;
    s16 unk12;
    u8 unk14;
    u8 pad15[3];
} Trail18;
typedef struct {
    u8 pad0[0x1C];
    s16 unk1C;
    u8 pad1E[6];
    f32 unk24;
    u8 pad28[2];
    s8 unk2A;
    u8 pad2B[5];
    u8 flags;
    u8 pad31[0x1B];
    u8 unk4C;
} TrailDef18;
typedef struct {
    u8 pad0[0x25];
    u8 count;
    u8 pad26[6];
    s8 n;
    s8 head;
    s8 tail;
    u8 pad2F[0x25];
    V3 pos;
    u8 pad60[0x34];
    Trail18 *trails;
    TrailDef18 *def;
} TrailObj18;

/* was func_151A3BCC */
s32 ribbon_trail_update_points(TrailObj18 *arg0) {
    TrailDef18 *def = arg0->def;
    Trail18 *trails = arg0->trails;
    s32 i;
    Trail18 *t;
    s16 life;

    if (arg0->n < 2 && (def->flags & 1)) {
        return 0;
    }
    def->unk4C += def->unk2A * D_800BE9E4;
    i = arg0->tail;
    while (i != arg0->head) {
        i--;
        if (i < 0) {
            i = arg0->count - 1;
        }
        t = &trails[i];
        life = t->unk12;
        if (life > 0) {
            t->unk12 = life - D_800BE9E4;
        } else {
            t->unk10 -= D_800BE9E4 * def->unk1C;
        }
        t->unk14 = 0xFF;
        t->unkC += D_800BE9A4 * def->unk24;
        if (t->unk10 < 0) {
            def->flags &= ~2;
            while (i != arg0->head) {
                arg0->head++;
                if (arg0->head == arg0->count) {
                    arg0->head = 0;
                }
                arg0->n--;
            }
            trails[arg0->head].unk10 = 0;
        }
    }
    if (arg0->n > 0) {
        arg0->pos = trails[arg0->head].pos;
    } else {
        arg0->pos.x = 0.0f; arg0->pos.y = 0.0f; arg0->pos.z = 0.0f;
    }
    return 1;
}

f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
void ribbon_trail_stop(u8 *);
struct260 *effect_node_create_nodraw(s16 arg0, s8 arg1, s8 arg2, u8 arg3, u8 arg4, s32 arg5, u8 arg6, s32 arg7);
/* the .s's late_rodata D_800A9138 is dropped in the NM link */
static const f32 D_800A9138[1] = { 9.99999975e-05f }; /* 0x38D1B717 (array: IDO puts scalar float statics in .data) */

// trail_emitter_update: object update of a trail emitter made by ribbon_trail_spawn (state SB3AB4 at +0x98, ring of 0x18
// byte trail points at +0x94, position +0x10). Ends (returns 0) when the owner record is gone or its id (+0x3B)
// changed. The first time (flag 4 in +0x1E) it fetches the start position (ribbon_trail_bone_pos). When the source can no
// longer be read, the emitter is released (ribbon_trail_stop) and a fade record (effect_node_create_nodraw type 0x12C, the 0x30
// spec copied to +0x28) takes over. Otherwise the travelled distance * rate (+0x14) is added to +0x40 and one point
// is dropped per unit of it, interpolated from the last point to the new position, with the width going from
// +0x20 + +0x24 * t to +0x20, colour +0x18 / +0x1A and a random-walk shade +0x44; the ring head / count / tail
// (+0x2E / +0x2C / +0x2D, size +0x25) advance as in fxrec_spawn's trail objects.
/* was func_151A3D70 */
s32 ribbon_trail_update(u8 *obj) {
    SB3AB4 *st = *(SB3AB4 **) (obj + 0x98);
    u8 *ring = *(u8 **) (obj + 0x94);
    u8 *owner = *(u8 **) st;
    u8 *pt;
    u8 spec[0x30];
    struct260 *fade;
    f32 dx, dy, dz;
    f32 dist, inv;
    f32 t, dt;
    f32 width, dwidth;
    f32 sx, sy, sz;
    V33AB4 pos;
    s32 started = 0;

    if (*(s32 *) owner == 0) {
        return 0;
    }
    if (st->raw[4] != owner[0x3B]) {
        return 0;
    }
    if (!(*(u16 *) (obj + 0x1E) & 4)) {
        if (ribbon_trail_bone_pos((u8 *) st, obj + 0x10) == 0) {
            return 1;
        }
        started = 1;
        st->u34 = *(V33AB4 *) (obj + 0x10);
        *(u16 *) (obj + 0x1E) |= 4;
    }
    if (!started && ribbon_trail_bone_pos((u8 *) st, obj + 0x10) == 0) {
        ribbon_trail_stop(obj);
        memcpy(spec, st, 0x30);
        fade = effect_node_create_nodraw(0x12C, -1, 0xA, 0, 5, 0x30, obj[0xC], 0);
        if (fade != NULL) {
            memcpy((u8 *) fade + 0x28, spec, 0x30);
        }
        return 1;
    }
    dx = *(f32 *) (obj + 0x10) - st->u34.x;
    dy = *(f32 *) (obj + 0x14) - st->u34.y;
    dz = *(f32 *) (obj + 0x18) - st->u34.z;
    if (fabsf(dx) > D_800A9138[0] || fabsf(dy) > D_800A9138[0] || fabsf(dz) > D_800A9138[0]) {
        st->u40 += sqrtf(dx * dx + dy * dy + dz * dz) * *(f32 *) (st->raw + 0x14);
    }
    dist = st->u40;
    if (1.0f < dist) {
        inv = 1.0f / dist;
        pos = st->u34;
        t = st->u48 + D_800BE9A4;
        dt = t * inv;
        width = *(f32 *) (st->raw + 0x20) + *(f32 *) (st->raw + 0x24) * t;
        sx = dx * inv;
        sy = dy * inv;
        sz = dz * inv;
        dwidth = (*(f32 *) (st->raw + 0x20) - width) * inv;
        do {
            pt = ring + *(s8 *) (obj + 0x2E) * 0x18;
            *(V33AB4 *) pt = pos;
            *(f32 *) (pt + 0xC) = width;
            *(s16 *) (pt + 0x10) = *(s16 *) (st->raw + 0x18);
            *(s16 *) (pt + 0x12) = *(s16 *) (st->raw + 0x1A);
            pt[0x15] = st->u44;
            st->u44 = st->u44 + st->raw[0x28] + (u32) random_int() % (st->raw[0x29] + 1);
            pt[0x14] = 0xFF;
            (*(s8 *) (obj + 0x2E))++;
            if (obj[0x25] == *(s8 *) (obj + 0x2E)) {
                *(s8 *) (obj + 0x2E) = 0;
            }
            (*(s8 *) (obj + 0x2C))++;
            if (*(s8 *) (obj + 0x2D) == *(s8 *) (obj + 0x2E)) {
                (*(s8 *) (obj + 0x2D))++;
                if (obj[0x25] == *(s8 *) (obj + 0x2D)) {
                    *(s8 *) (obj + 0x2D) = 0;
                }
                (*(s8 *) (obj + 0x2C))--;
            }
            width += dwidth;
            pos.x += sx;
            pos.y += sy;
            pos.z += sz;
            t -= dt;
            st->u40 -= 1.0f;
        } while (1.0f < st->u40);
        st->u34 = pos;
        st->u48 = t;
    }
    return 1;
}

void vtx_slot_buffer_get(s32 *, s16, s32, s32 *, u8 *);
s32 gfx_load_texture_cached(s32, s32 *, s32, s32, s32, s32, s32, s32, s32, u8 *, s32);
s32 gfx_geometry_mode_cached(s32, s32, s32);
s32 gfx_env_color_cached(s32, s32, s32, s32, s32, u8 *);
s32 gfx_prim_color_cached(s32, s32, s32, s32, s32, s32, s32, u8 *);
s32 gfx_set_combine_mode(s32, s32, u8 *);
s32 gfx_other_mode_cached(s32, s32, s32, u8 *);
extern s32 D_80091084;
extern s32 D_800D30BC;

/* One strip vertex of ribbon_trail_draw: position, s = shade << 6, t = 0x7C0 (outer edge) or 0 (inner), white, alpha. */
#define TRAIL6_VTX(v, px, py, pz, s, t, a) \
    do { \
        *(s16 *) ((v) + 0x0) = (s32) (px); \
        *(s16 *) ((v) + 0x2) = (s32) (py); \
        *(s16 *) ((v) + 0x4) = (s32) (pz); \
        *(s16 *) ((v) + 0x8) = (s); \
        *(s16 *) ((v) + 0xA) = (t); \
        (v)[0xC] = 0xFF; \
        (v)[0xD] = 0xFF; \
        (v)[0xE] = 0xFF; \
        (v)[0xF] = (a); \
        *(s16 *) ((v) + 0x6) = 0; \
    } while (0)

// trail_ribbon_draw: D_8008A644 draw handler (kind 6) of the trail emitter of ribbon_trail_update (ring of 0x18-byte
// points +0x94, def +0x98, ring size +0x25, count +0x2C, tail +0x2D, head +0x2E). With def +0x30 bit 1 it first
// writes a fade-in ramp into the alpha of the oldest def +0x2B points (step def +0x2C), with bit 2 it scales the
// newest def +0x2D points by a fade-out ramp (step def +0x2E). Sets texture D_80091084 and fixed render state, then
// draws a camera-facing strip from the emitter position (+0x10, when +0x1E bit 1; else from the newest point) back
// to the tail: each point gets two vertices, +-the normal of (point - camera) x (segment) scaled to the point's
// width +0xC, s = (point +0x15 + def +0x4C) << 6, alpha = point +0x10 * +0x14 >> 8. Where s grows from one point to
// the next (the texture wrapped), the pair is duplicated and the drawn copy gets s - 0x4000. Vertices come from
// vtx_slot_buffer_get (2 + 2 per point, +0xA0 spare). Returns the display list end; nothing with fewer than 2 points.
/* was func_151A4194 */
s32 ribbon_trail_draw(u8 *obj, s32 gfx, s16 player) {
    u8 *pts;
    u8 *def;
    u8 *v;
    u8 *p;
    f32 *cam;
    u8 flag;
    s32 i, cur, prev;
    s16 cnt;
    u8 ramp;
    u8 s0, s1, a0, a1;
    f32 ax, ay, az;
    f32 bx, by, bz;
    f32 dx, dy, dz;
    f32 ex, ey, ez;
    f32 cx, cy, cz;
    f32 nx, ny, nz;
    f32 len2, k;

    if (*(s8 *) (obj + 0x2C) < 2) {
        return gfx;
    }
    vtx_slot_buffer_get((s32 *) (obj + 0x84), player, obj[0x25] * 0x20 + 0xA0, (s32 *) &v, NULL);
    if (v == NULL) {
        return gfx;
    }
    cam = (f32 *) ((u8 *) D_800DBFF0 + player * 0x9A0 + 0x2F8);
    def = *(u8 **) (obj + 0x98);
    pts = *(u8 **) (obj + 0x94);
    flag = 1;
    if (def[0x30] & 2) {
        cnt = def[0x2B];
        i = *(s8 *) (obj + 0x2D);
        ramp = 0;
        do {
            pts[i * 0x18 + 0x14] = ramp;
            i++;
            cnt--;
            ramp += def[0x2C];
            if (i == obj[0x25]) {
                i = 0;
            }
        } while (cnt != 0 && i != *(s8 *) (obj + 0x2E));
    }
    if (def[0x30] & 4) {
        i = *(s8 *) (obj + 0x2E) - 1;
        if (i < 0) {
            i = obj[0x25] - 1;
        }
        ramp = 0;
        cnt = def[0x2D];
        do {
            p = pts + i * 0x18;
            p[0x14] = (p[0x14] * ramp) >> 8;
            cnt--;
            i--;
            ramp += def[0x2E];
            if (i < 0) {
                i = obj[0x25] - 1;
            }
        } while (cnt != 0 && i != *(s8 *) (obj + 0x2E));
    }
    gfx = gfx_load_texture_cached(gfx, &D_80091084, 0, 0, 0, 0, 0x1F, 0, 0, &flag, 3);
    gfx = gfx_geometry_mode_cached(gfx, 1, 0x160600);
    gfx = gfx_env_color_cached(gfx, 0xFF, 0xFF, 0xFF, 0xFF, &flag);
    gfx = gfx_prim_color_cached(gfx, 0, 0, 0, 0, 0, 0, &flag);
    gfx = gfx_set_combine_mode(gfx, 6, &flag);
    gfx = gfx_other_mode_cached(gfx, D_800D30BC | 0x80000 | 0x2CA0, 0x5049D8, &flag);

    if (*(u16 *) (obj + 0x1E) & 2) {
        cur = *(s8 *) (obj + 0x2E) - 1;
        if (cur < 0) {
            cur = obj[0x25] - 1;
        }
        ax = *(f32 *) (obj + 0x10);
        ay = *(f32 *) (obj + 0x14);
        az = *(f32 *) (obj + 0x18);
        p = pts + cur * 0x18;
    } else {
        prev = *(s8 *) (obj + 0x2E) - 1;
        if (prev < 0) {
            prev = obj[0x25] - 1;
        }
        cur = prev - 1;
        if (cur < 0) {
            cur = obj[0x25] - 1;
        }
        p = pts + prev * 0x18;
        ax = *(f32 *) (p + 0x0);
        ay = *(f32 *) (p + 0x4);
        az = *(f32 *) (p + 0x8);
    }
    a0 = (*(s16 *) (p + 0x10) * p[0x14]) >> 8;
    s0 = p[0x15] + def[0x4C];
    p = pts + cur * 0x18;
    bx = *(f32 *) (p + 0x0);
    by = *(f32 *) (p + 0x4);
    bz = *(f32 *) (p + 0x8);
    s1 = p[0x15] + def[0x4C];
    a1 = (*(s16 *) (p + 0x10) * p[0x14]) >> 8;

    /* the first point (emitter or newest point) */
    dx = ax - cam[0];
    dy = ay - cam[1];
    dz = az - cam[2];
    ex = ax - bx;
    ey = ay - by;
    ez = az - bz;
    cx = ey * dz - dy * ez;
    cy = ez * dx - dz * ex;
    cz = ex * dy - dx * ey;
    len2 = cx * cx + cy * cy + cz * cz;
    if (len2 == 0.0f) {
        nx = ny = nz = 0.0f;
    } else {
        k = *(f32 *) (p + 0xC) / sqrtf(len2);
        nx = cx * k;
        ny = cy * k;
        nz = cz * k;
    }
    TRAIL6_VTX(v, ax + nx, ay + ny, az + nz, s0 << 6, 0x7C0, a0);
    v += 0x10;
    TRAIL6_VTX(v, ax - nx, ay - ny, az - nz, s0 << 6, 0, a0);
    v += 0x10;

    /* one segment per older point */
    do {
        dx = bx - cam[0];
        dy = by - cam[1];
        dz = bz - cam[2];
        ex = ax - bx;
        ey = ay - by;
        ez = az - bz;
        cx = ey * dz - dy * ez;
        cy = ez * dx - dz * ex;
        cz = ex * dy - dx * ey;
        len2 = cx * cx + cy * cy + cz * cz;
        if (len2 == 0.0f) {
            nx = ny = nz = 0.0f;
        } else {
            k = *(f32 *) (pts + cur * 0x18 + 0xC) / sqrtf(len2);
            nx = cx * k;
            ny = cy * k;
            nz = cz * k;
        }
        TRAIL6_VTX(v, bx + nx, by + ny, bz + nz, s1 << 6, 0x7C0, a1);
        v += 0x10;
        TRAIL6_VTX(v, bx - nx, by - ny, bz - nz, s1 << 6, 0, a1);
        v += 0x10;
        ((s32 *) gfx)[0] = 0x01004008; /* gSPVertex(v - 4, 4, 0) */
        ((s32 *) gfx)[1] = (s32) (v - 0x40);
        gfx += 8;
        ((s32 *) gfx)[0] = 0x05000204; /* gSP1Triangle(0, 1, 2) */
        ((s32 *) gfx)[1] = 0;
        gfx += 8;
        ((s32 *) gfx)[0] = 0x05020604; /* gSP1Triangle(1, 3, 2) */
        ((s32 *) gfx)[1] = 0;
        gfx += 8;
        if (s0 < s1) {
            /* the texture wrapped: draw this pair at s - 0x4000, start the next segment from a fresh copy */
            memcpy(v, v - 0x20, 0x20);
            *(s16 *) (v - 0x18) -= 0x4000;
            v += 0x10;
            *(s16 *) (v - 0x18) -= 0x4000;
            v += 0x10;
        }
        prev = cur;
        cur--;
        if (cur < 0) {
            cur = obj[0x25] - 1;
        }
        if (prev != *(s8 *) (obj + 0x2D)) {
            ax = bx;
            ay = by;
            az = bz;
            s0 = s1;
            p = pts + cur * 0x18;
            bx = *(f32 *) (p + 0x0);
            by = *(f32 *) (p + 0x4);
            bz = *(f32 *) (p + 0x8);
            s1 = p[0x15] + def[0x4C];
            a1 = (*(s16 *) (p + 0x10) * p[0x14]) >> 8;
        }
    } while (prev != *(s8 *) (obj + 0x2D));
    return gfx;
}

struct102 *emitter_trail_spawn(u8 *arg0, s32 arg1, u8 arg2, s32 arg3);
/* effect spec for emitter_trail_spawn (0x30 bytes) */
typedef struct {
    /* 0x00 */ s32 u0;
    /* 0x04 */ s32 u4;
    /* 0x08 */ u8 objId;
    /* 0x09 */ u8 pad9[3];
    /* 0x0C */ u8 *obj;
    /* 0x10 */ u8 u10;
    /* 0x11 */ u8 pad11[3];
    /* 0x14 */ f32 offset[3];
    /* 0x20 */ f32 u20;
    /* 0x24 */ f32 u24;
    /* 0x28 */ s16 u28;
    /* 0x2A */ u8 u2A;
    /* 0x2B */ u8 u2B;
    /* 0x2C */ s8 u2C;
    /* 0x2D */ u8 u2D;
    /* 0x2E */ u8 pad2E[2];
} S4B40;
/*
 * obj_attached_effect_start: P190. Starts a emitter_trail_spawn effect attached to obj (id obj[0x3B], offset 0, 14.7,
 * 3.0, 100, 10, 1, -1, 0) with arg1 as its byte argument; nothing for a NULL obj.
 */
/* was func_151A4B40 */
void obj_attached_effect_start(u8 *obj, u8 arg1) {
    S4B40 s;

    if (obj != NULL) {
        s.u0 = 0;
        s.u4 = 0;
        s.objId = obj[0x3B];
        s.obj = obj;
        s.u10 = 1;
        s.offset[0] = 0.0f;
        s.offset[1] = 0.0f;
        s.offset[2] = 0.0f;
        s.u20 = 14.7f;
        s.u24 = 3.0f;
        s.u28 = 100;
        s.u2A = 10;
        s.u2B = 1;
        s.u2C = -1;
        s.u2D = 0;
        emitter_trail_spawn((u8 *)&s, 0, arg1, 0);
    }
}

s32 particle_spawn_basic(void *, s32, s32, u8, s32);
/* was func_151A4BE8 */
void spark_burst_particle_spawn(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 *arg6) {
    struct {
        s32 u34;
        s32 u38;
        s16 u3C;
        s16 u3E;
        s32 u40;
        s32 u44;
        u8 u48;
        s8 u49;
        s8 u4A;
        u8 u4B;
        s8 u4C;
        s8 u4D;
        s8 u4E;
        u8 u4F;
        u8 u50;
        s8 u51;
        s16 u52;
        s16 u54;
        s16 u56;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        u8 pad70[0xC];
        f32 u7C;
        f32 u80;
        f32 u84;
        f32 u88;
        s32 u8C;
        u8 pad90[4];
        s8 u94;
        s8 u95;
        s8 u96;
        s8 u97;
        u8 pad98[0xC];
    } sp;
    f32 k;
    s16 sh[6];
    s32 obj;

    sp.u51 = 0x27;
    sp.u3C = 0x1401;
    sp.u34 = 0x200005;
    sp.u38 = 0;
    sp.u3E = (random_int() % 5U) + 0xF;
    sp.u40 = 0;
    sp.u44 = 0;
    sp.u48 = 0x8A;
    sp.u49 = 0;
    sp.u4A = 0;
    sp.u4B = 0xFF;
    sp.u4C = 0;
    sp.u4D = 0;
    sp.u4E = 0;
    sp.u52 = 1;
    sp.u54 = 0xFF;
    sp.u56 = 1;
    sp.u58 = 1.0f;
    sp.u5C = sp.u60 = (random_float() * 50.0f) + 500.0f;
    sp.u64 = arg0;
    sp.u68 = arg1;
    sp.u6C = arg2;
    k = 0.087f * D_800BEDC8;
    sp.u7C = -arg3 * k;
    sp.u80 = -arg4 * k;
    sp.u8C = 0xD;
    sp.u94 = 1;
    sp.u95 = 1;
    sp.u84 = -arg5 * k;
    sp.u88 = 0.0f;
    if (random_int() & 1) {
        sp.u8C |= 0x40;
    }
    if (random_int() & 1) {
        sp.u8C |= 0x80;
    }
    sp.u4F = 0xFF;
    sp.u50 = 0xFF;
    sp.u96 = 0;
    sp.u97 = -1;
    sh[0] = 0x10;
    sh[1] = 0xF;
    sh[2] = 0xD;
    sh[3] = 0x13;
    sh[4] = 0x11;
    sh[5] = -0x18;
    obj = particle_spawn_basic(&sp, 0, 0xC, arg6[0xC], 1);
    if (obj != 0) {
        memcpy(obj + 0xA8, sh, 0xC);
    }
}

/*
 * spark_burst_update: particle update handler 0 (D_80089B00, called by particle_sprite_update with the old position).
 * The 12-byte parameter block at +0xA8 (copied by the spawner above) gives three thresholds on the life timer
 * +0x1A: below +0xAC the alpha +0x2B follows timer * +0xAE; below +0xB0 both sizes +0x38 / +0x3C grow by
 * +0xB2 per tick; below +0xA8 it switches to update handler 1 / draw modes 2, sets +0x18 = 0x5203 and the
 * colour byte +0x2C = timer * +0xAA. Always keeps the particle (returns 1).
 */
/* was func_151A4DEC */
s32 spark_burst_update(u8 *arg0, f32 *oldPos) {
    s16 t = *(s16 *)(arg0 + 0x1A);
    f32 d;

    if (t < *(s16 *)(arg0 + 0xAC)) {
        arg0[0x2B] = t * *(s16 *)(arg0 + 0xAE);
    }
    if (t < *(s16 *)(arg0 + 0xB0)) {
        d = (f32)(*(s16 *)(arg0 + 0xB2) * D_800BE9E4);
        *(f32 *)(arg0 + 0x38) += d;
        *(f32 *)(arg0 + 0x3C) += d;
        t = *(s16 *)(arg0 + 0x1A);
    }
    if (t < *(s16 *)(arg0 + 0xA8)) {
        arg0[0x72] = 1;
        arg0[0x70] = 2;
        arg0[0x71] = 2;
        *(s16 *)(arg0 + 0x18) = 0x5203;
        arg0[0x2C] = t * *(s16 *)(arg0 + 0xAA);
    }
    return 1;
}

/* was func_151A4EB0 */
s32 spark_burst_update_tail(u8 *arg0, s32 arg1)
{
  s16 temp_a1;
  u8 *temp_v1;
  temp_v1 = arg0 + 0xA8;
  if ((*((s16 *) (arg0 + 0x1A))) < (*((s16 *) (((u8 *) arg0) + 0xAC))))
  {
    *((s8 *) (((u8 *) arg0) + 0x2B)) = (s8) ((*((s16 *) (((u8 *) arg0) + 0xAE))) * (*((s16 *) (arg0 + 0x1A))));
  }
  if ((*((s16 *) (arg0 + 0x1A))) < (*((s16 *) (((u8 *) temp_v1) + 8))))
  {
    f32 temp_f0;
    temp_f0 = (f32) ((*((s16 *) (((u8 *) temp_v1) + 0xA))) * D_800BE9E4);
    *((f32 *) (((u8 *) arg0) + 0x38)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x38))) + temp_f0);
    *((f32 *) (((u8 *) arg0) + 0x3C)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x3C))) + temp_f0);
  }
  *((s8 *) (((u8 *) arg0) + 0x2C)) = (s8) ((*((s16 *) (((u8 *) temp_v1) + 2))) * (*((s16 *) (((u8 *) arg0) + 0x1A))));
  return 1;
}

/* was func_151A4F4C */
void owner_smoke_start(u8 *arg0, u8 arg1) {
    struct260 *temp_v0;
    struct {
        u8 *unk0;
        u8 unk4;
        f32 unk8;
        f32 unkC;
        u8 unk10;
        f32 unk14;
        f32 unk18;
        f32 unk1C;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = 0.722f;
    tmp.unkC = 0.0f;
    tmp.unk10 = 1;
    tmp.unk14 = 0.0f;
    tmp.unk18 = 0.0f;
    tmp.unk1C = 0.0f;
    temp_v0 = effect_node_create_nodraw(300, -1, 5, 0, 1, 0x20, arg1, 0);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x20);
    }
}

void emit_particle_burst_req(u8 *tmpl, s32 arg1, u8 room, u8 kind);

/* emit_particle_burst_req's particle template (sp2C in the asm) */
typedef struct {
    /* 0x00 */ s16 count;
    /* 0x02 */ s16 u02;
    /* 0x04 */ u8 u04;
    /* 0x06 */ s16 u06;
    /* 0x08 */ s32 u08;
    /* 0x0C */ s32 u0C;
    /* 0x10 */ s16 u10;
    /* 0x12 */ s16 u12;
    /* 0x14 */ s32 u14;
    /* 0x18 */ s32 u18;
    /* 0x1C */ u8 colour[10];
    /* 0x26 */ s16 u26;
    /* 0x28 */ s16 u28;
    /* 0x2A */ s16 u2A;
    /* 0x2C */ f32 u2C;
    /* 0x30 */ f32 u30;
    /* 0x34 */ f32 u34;
    /* 0x38 */ f32 pos[3];
    /* 0x44 */ s16 angle;
    /* 0x46 */ s16 u46;
    /* 0x48 */ s16 u48;
    /* 0x4A */ s16 u4A;
    /* 0x4C */ f32 u4C;
    /* 0x50 */ f32 u50;
    /* 0x54 */ f32 u54;
    /* 0x58 */ f32 u58;
    /* 0x5C */ s32 mode;
    /* 0x60 */ s8 u60;
    /* 0x61 */ s8 u61;
    /* 0x62 */ u8 u62;
    /* 0x63 */ u8 u63;
    /* 0x64 */ u8 u64;
} SmokeTmpl4FE8;

/* the effect data at obj + 0x28 (filled by owner_smoke_start) */
typedef struct {
    /* 0x00 */ u8 *owner;
    /* 0x04 */ u8 ownerId;      // owner's +0x3B when attached
    /* 0x08 */ f32 rate;        // puffs per frame
    /* 0x0C */ f32 accum;
    /* 0x10 */ u8 bone;         // matrix index in owner + 0x1D4
    /* 0x14 */ f32 offset[3];
} SmokeData4FE8;

// owner_smoke_update: effect handler (table D_8008A890) for the smoke trail started by owner_smoke_start. Ends the effect
// (+0xE = -1, +0xD |= 1) when the owner is gone (type 0 / 8, or +0x3B no longer the saved id). Otherwise, while the
// owner has matrices (+0x1D4) and its +0x74 low nibble is not 0xF, accumulates rate * D_800BE9A4; once over 1 it emits
// the whole number of puffs (emit_particle_burst_req, count = int part) at the bone position (mtx_transform_point_or_origin), facing the
// owner's yaw (+0x76 high byte), with random flip bits 0x40 / 0x80.
/* was func_151A4FE8 */
void owner_smoke_update(u8 *obj) {
    SmokeData4FE8 *d = (SmokeData4FE8 *) (obj + 0x28);
    u8 *owner;
    SmokeTmpl4FE8 t;
    s16 yaw;
    f32 pos[3];

    if (*(s32 *) d->owner == 0 || *(s32 *) d->owner == 8 || d->ownerId != d->owner[0x3B]) {
        *(s16 *) (obj + 0xE) = -1;
        obj[0xD] |= 1;
        return;
    }
    owner = d->owner;
    if (*(u8 **) (owner + 0x1D4) == NULL) {
        return;
    }
    if ((owner[0x74] & 0xF) == 0xF) {
        return;
    }
    d->accum += d->rate * D_800BE9A4;
    if (!(1.0f < d->accum)) {
        return;
    }
    owner = d->owner;
    yaw = (*(u16 *) (owner + 0x76) >> 8) - 0x40;
    mtx_transform_point_or_origin(d->offset, pos, *(u8 **) (owner + 0x1D4) + (d->bone << 6));
    t.u02 = 0;
    t.count = (s32) d->accum;
    d->accum -= (f32) t.count;
    t.u04 = 0x28;
    t.u06 = 0xC01;
    t.u08 = 0x200005;
    t.u0C = 0;
    t.u10 = 0x17;
    t.u12 = 0xD;
    t.u14 = 0;
    t.u18 = 0;
    t.colour[0] = 0;
    t.colour[1] = 0;
    t.colour[2] = 0;
    t.colour[3] = 0xFF;
    t.colour[4] = 0;
    t.colour[5] = 0;
    t.colour[6] = 0;
    t.u30 = 300.0f;
    t.u34 = 400.0f;
    t.pos[0] = pos[0];
    t.pos[1] = pos[1];
    t.pos[2] = pos[2];
    t.u26 = 1;
    t.u28 = 0;
    t.u2A = 1;
    t.u64 = 0;
    t.angle = yaw - 0x19;
    t.u46 = -0x2C;
    t.u48 = 0x32;
    t.u4A = 0x32;
    t.mode = 7;
    t.u62 = 1;
    t.u63 = 0;
    t.u54 = -0.5f;
    t.u58 = -0.5f;
    t.u4C = 0.0f;
    t.u2C = 1.0f;
    t.u50 = 15.0f;
    if (random_int() & 1) {
        t.mode |= 0x40;
    }
    if (random_int() & 1) {
        t.mode |= 0x80;
    }
    t.colour[7] = 0xFF;
    t.colour[8] = 0;
    t.colour[9] = 0xFF;
    t.u60 = -1;
    t.u61 = -1;
    emit_particle_burst_req((u8 *) &t, 0xFF, obj[0xC], obj[1]);
}

void ribbon_trail_stop(u8 *);
/* was func_151A5290 */
void ribbon_trail_handle_msg(u8 *arg0, u8 *arg1, u8 arg2) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);
    s32 temp_a0;

    if (arg2 == 0) {
        if ((*(s32 *)(temp_v0 + 0) == *(s32 *)(arg1 + 0)) || (*(u8 *)(temp_v0 + 4) == *(u8 *)(arg1 + 4))) {
            ribbon_trail_stop(arg0);
        }
    } else if (arg2 == 0x2D) {
        temp_a0 = *(s32 *)(arg1 + 0);
        if (temp_a0 == *(s32 *)(temp_v0 + 0)) {
            *(s32 *)(temp_v0 + 0) = *(s32 *)(arg1 + 4);
            *(u8 *)(temp_v0 + 4) = *(u8 *)(arg1 + 9);
            return;
        }
        if (*(s32 *)(arg1 + 4) == *(s32 *)(temp_v0 + 0)) {
            *(s32 *)(temp_v0 + 0) = temp_a0;
            *(u8 *)(temp_v0 + 4) = *(u8 *)(arg1 + 8);
        }
    }
}

/* was func_151A5338 */
void owner_smoke_handle_msg(u8 *arg0, s32 *arg1, u8 arg2) {
    u8 *v = arg0 + 0x28;
    if (arg2 == 0) {
        if ((*(s32 *)v == arg1[0]) || (v[4] == ((u8 *)arg1)[4])) {
            node_destroy(arg0);
        }
    } else {
        v = arg0 + 0x28;
        if (arg2 == 0x2D) {
            if (arg1[0] == *(s32 *)v) {
                *(s32 *)v = arg1[1];
                v[4] = ((u8 *)arg1)[9];
            } else if (arg1[1] == *(s32 *)v) {
                *(s32 *)v = arg1[0];
                v[4] = ((u8 *)arg1)[8];
            }
        }
    }
}

/* was func_151A53E4 */
s32 ribbon_trail_bone_pos(u8 *arg0, u8 *arg1) {
    s32 temp_v1;
    u32 idx;
    u8 *temp_v0;

    temp_v0 = *(u8 **)arg0;
    temp_v1 = *(s32 *)(temp_v0 + 0x1D4);
    if (temp_v1 == 0) {
        return 0;
    }
    if ((temp_v0[0x74] & 0xF) == 0xF) {
        return 0;
    }
    idx = arg0[5]; // permuter: unsigned local for the index
    mtx_transform_point_or_origin(arg0 + 8, arg1, temp_v1 + ((idx << 2) << 4));
    return 1;
}

/* was func_151A544C */
void ribbon_trail_stop(u8 *arg0)
{
  u8 *temp_v0;
  temp_v0 = *((u8 **) (arg0 + 0x98));
  arg0[0x30] = 0;
  *((u16 *) (arg0 + 0x1E)) = *((u16 *) (arg0 + 0x1E)) & 0xFFFD;
  temp_v0[0x30] |= 1;
  temp_v0[0x30] |= 4;
}

s32 ribbon_trail_spawn(); // K&R: defined with 2 params, called with 3

/* was func_151A547C */
void ribbon_trail_marker_update(u8 *arg0) {
    u8 *temp_v0;
    u8 sp1B;
    u8 *temp_a0;

    sp1B = 0;
    temp_a0 = arg0 + 0x28;
    if (**(s32 **)(arg0 + 0x28) == 0) {
        sp1B = 1;
    }
    temp_v0 = *(u8 **)temp_a0;
    if (temp_a0[4] != temp_v0[0x3B]) {
        sp1B = 1;
    }
    if ((sp1B == 0) && (*(s32 *)(temp_v0 + 0x1D4) != 0) && ((temp_v0[0x74] & 0xF) != 0xF)) {
        sp1B = 1; // permuter: the flag is stored before and after the call
        ribbon_trail_spawn(temp_a0, arg0[0xC]); /* the asm also loads a2 = arg0; the callee has 2 params */
        sp1B = 1;
    }
    if (sp1B) {
        *(s16 *)(arg0 + 0xE) = -1;
        arg0[0xD] |= 1;
    }
}

/* was func_151A552C */
void ribbon_trail_marker_handle_msg(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *temp_v0 = (u8 *)arg0 + 0x28;
    if ((arg2 == 0) && ((*(s32 *)temp_v0 == *(s32 *)arg1) || (temp_v0[4] == arg1[4]))) {
        node_destroy(arg0);
    }
}

/* was func_151A5580 */
void *screen_tint_create(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 arg6, s32 arg7) {
    u8 *temp_v0 = node_alloc(0x5A, 0, arg7 + 0x20, 0, 0xFF, 1);
    if (temp_v0 == NULL) {
        return NULL;
    }
    temp_v0[0x14] = arg0;
    *(s32 *)(temp_v0 + 0x10) = arg1;
    temp_v0[0x15] = arg2;
    temp_v0[0x16] = arg3;
    temp_v0[0x17] = arg4;
    temp_v0[0x19] = arg6;
    temp_v0[0x18] = 0;
    temp_v0[0x1A] = arg5;
    return temp_v0;
}

/* was func_151A5620 */
void screen_tint_update(u8 *arg0) {
    s32 v0;
    s32 v1;

    v0 = *(s32 *)(arg0 + 0x10);
    if (v0 != 0) {
        v0 = v0 - D_800BE9E4;
        if (v0 <= 0) {
            node_destroy(arg0);
            return;
        }
        *(s32 *)(arg0 + 0x10) = v0;
    }
    if (*(u8 *)(arg0 + 0x19) == 0) {
        audio_mixer_request_mode(2);
    }
    v1 = D_800BE9E4 * 2;
    v0 = *(u8 *)(arg0 + 0x15);
    if (*(u8 *)(arg0 + 0x18) == 0) {
        v0 = v0 - v1;
        if (v0 < 0x90) {
            v0 = 0x90;
            *(u8 *)(arg0 + 0x18) = 1;
        }
    } else {
        v0 = v0 + v1;
        if (v0 >= 0x100) {
            v0 = 0xFF;
            *(u8 *)(arg0 + 0x18) = 0;
        }
    }
    *(u8 *)(arg0 + 0x15) = v0;
}

/* was func_151A56E0 */
void screen_tint_draw_dispatch(s32 arg0, u8 *arg1, s16 arg2) {
    D_8008FCA0[arg1[0x14]](arg0, arg1, arg2);
}
