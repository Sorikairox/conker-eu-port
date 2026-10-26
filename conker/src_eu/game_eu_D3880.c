#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* P130: shadow triangle projection (hand asm shadow_level_triangles, shadow_object_triangles and their private vertex
 * transform shadow_project_vertex_entry) */
extern f32 D_800D3AA0;  /* [2] f32: shadow u / v scale */
extern f32 D_800D3AA8;  /* shadow far clip depth: w <= this -> outcode 0x10 */
extern f32 D_800D3AAC;  /* shadow near clip depth: w >= this -> outcode 0x20 */
extern s32 D_800D3AB0;  /* triangle table: 3 vertex pointers (offsets for world objects) per triangle */
extern s32 D_800D3AB4;  /* end of the level triangle bit mask (u32 *) */
extern s32 D_800DC270;  /* per triangle: s16 x min, z min, x max, z max */
extern s32 D_800DF514;  /* number of world object ids */
extern s32 D_800DF518;  /* shadow box: x min */
extern s32 D_800DF51C;  /* x max */
extern s32 D_800DF520;  /* z min */
extern s32 D_800DF524;  /* z max */

/* one projected shadow vertex (20 bytes, 3 per triangle) */
typedef struct {
    f32 u, v, w;  /* light space: u, v scaled by D_800D3AA0[0] / [1], w = depth */
    s32 vtx;      /* source vertex (s16 x, y, z) */
    s32 clip;     /* outcode: 1 / 4 v out (+ / -), 8 / 2 u out (+ / -), 0x10 beyond far, 0x20 before near */
} ShadowVtx;

typedef struct {
    f32 su, sv, farW, nearW;  /* D_800D3AA8, D_800D3AAC */
    f32 *m;
} ShadowProj;

// shadow_project_vertex: (hand asm shadow_project_vertex_entry, private t4 -> f13..f15 / t3 call) transforms the s16 vertex v by
// the light matrix m (row vectors: u = x m0 + y m4 + z m8 + m12, v = .. m1 m5 m9 m13, w = .. m2 m6 m10 m14), scales
// u and v, and returns its outcode. u / v are outside when |u| > -w (NaN too); the sign of u is taken before the
// scale, the sign of v after it (as the asm).
static s32 shadow_project_vertex(ShadowProj *p, s16 *v, ShadowVtx *o) {
    union { f32 f; s32 i; } su, sv;
    f32 x = v[0], y = v[1], z = v[2];
    f32 *m = p->m;
    f32 w, u, vv;
    s32 clip;

    w = ((x * m[2] + m[14]) + y * m[6]) + z * m[10];
    if (w <= p->farW) {
        clip = 0x10;
    } else if (p->nearW <= w) {
        clip = 0x20;
    } else {
        clip = 0;
    }
    su.f = ((x * m[0] + m[12]) + y * m[4]) + z * m[8];
    u = su.f * p->su;
    vv = (((x * m[1] + m[13]) + y * m[5]) + z * m[9]) * p->sv;
    sv.f = vv;
    if (!(((u < 0.0f) ? -u : u) <= -w)) {
        clip |= (su.i < 0) ? 2 : 8;
    }
    if (!(((vv < 0.0f) ? -vv : vv) <= -w)) {
        clip |= (sv.i < 0) ? 4 : 1;
    }
    o->u = u;
    o->v = vv;
    o->w = w;
    o->vtx = (s32) v;
    o->clip = clip;
    return clip;
}

// shadow_emit_triangle: (part of shadow_level_triangles / shadow_object_triangles) projects triangle tri, whose vertex pointers are
// the table entries + base, into out[0..2] when its x / z bounds touch the shadow box D_800DF518..D_800DF524, its
// three outcodes share no bit and it faces the light ((v0 - v2)(u0 - u1) > (u0 - u2)(v0 - v1), NaN counts as facing).
// Returns 1 when written.
static s32 shadow_emit_triangle(ShadowProj *p, s32 tri, s32 base, ShadowVtx *out) {
    s16 *box = (s16 *) (D_800DC270 + tri * 8);
    s32 *vtx = (s32 *) (D_800D3AB0 + tri * 12);
    ShadowVtx t[3];
    s32 all;

    if (D_800DF51C < box[0] || D_800DF524 < box[1] || box[2] < D_800DF518 || box[3] < D_800DF520) {
        return 0;
    }
    all = shadow_project_vertex(p, (s16 *) (vtx[0] + base), &t[0]);
    all &= shadow_project_vertex(p, (s16 *) (vtx[1] + base), &t[1]);
    all &= shadow_project_vertex(p, (s16 *) (vtx[2] + base), &t[2]);
    if (all != 0) {
        return 0;
    }
    if ((t[0].v - t[2].v) * (t[0].u - t[1].u) <= (t[0].u - t[2].u) * (t[0].v - t[1].v)) {
        return 0;
    }
    out[0] = t[0];
    out[1] = t[1];
    out[2] = t[2];
    return 1;
}

static void shadow_proj_init(ShadowProj *p, f32 *m) {
    p->su = (&D_800D3AA0)[0];
    p->sv = (&D_800D3AA0)[1];
    p->farW = D_800D3AA8;
    p->nearW = D_800D3AAC;
    p->m = m;
}

// shadow_level_triangles: (hand asm) projects the level triangles whose bit is set in mask (bit i of word i / 32,
// words up to D_800D3AB4) with the light matrix m into shadow vertices at out. A triangle that reaches end is
// written but not counted and ends the walk. Returns the end of the counted vertices.
/* was func_150A6070 */
s32 shadow_level_triangles(u32 *mask, s32 out, f32 *m, s32 end) {
    ShadowProj p;
    ShadowVtx *o = (ShadowVtx *) out;
    u32 *stop = (u32 *) D_800D3AB4;
    u32 bits;
    s32 tri = 0;

    shadow_proj_init(&p, m);
    for (; mask != stop; mask++) {
        bits = *mask;
        if (bits == 0) {
            tri += 32;
            continue;
        }
        for (; bits != 0; bits >>= 1, tri++) {
            if ((bits & 1) && shadow_emit_triangle(&p, tri, 0, o)) {
                if ((s32) (o + 3) >= end) {
                    return (s32) o;
                }
                o += 3;
            }
        }
        tri = (tri + 31) & 0xFFE0; /* the asm: last bit index + 32, rounded down to 32 */
    }
    return (s32) o;
}

// shadow_object_triangles: (hand asm) as shadow_level_triangles for D_800DF514 (>= 1) world objects: ids[i] selects the
// 0xA0-byte record D_800DBEF4 + id * 0xA0 (u16 triangle count +0x56, first triangle +0x58, >= 1 triangle) whose
// vertex offsets are relative to D_800DC328[id].
/* was func_150A6324 */
s32 shadow_object_triangles(u16 *ids, s32 out, f32 *m, s32 end) {
    ShadowProj p;
    ShadowVtx *o = (ShadowVtx *) out;
    u16 *last = ids + D_800DF514;
    u8 *obj;
    s32 base;
    s32 tri, stop;

    shadow_proj_init(&p, m);
    do {
        base = D_800DC328[*ids];
        obj = (u8 *) D_800DBEF4 + *ids * 0xA0;
        ids++;
        tri = *(u16 *) (obj + 0x58);
        stop = tri + *(u16 *) (obj + 0x56);
        do {
            if (shadow_emit_triangle(&p, tri, base, o)) {
                if ((s32) (o + 3) >= end) {
                    return (s32) o;
                }
                o += 3;
            }
            tri++;
        } while (tri != stop);
    } while (ids != last);
    return (s32) o;
}

/* P197 */
extern f32 D_800D9F40; /* screen width (also the near-depth bound here) */
extern f32 D_800D3A00[2];

/* cvt.w.s with the default FCSR mode: round to nearest, ties to even */
#define VIEW66F0_RINT(f)                                                                             \
    (((f) >= 8388608.0f || (f) <= -8388608.0f) ? (s32)(f)                                            \
     : ((f) >= 0.0f) ? (s32)(((f) + 8388608.0f) - 8388608.0f)                                       \
                     : -(s32)((-(f) + 8388608.0f) - 8388608.0f))

/*
 * view_sphere_depth: P197: view test of a box around (x, y, z) (hand asm, FR=1 odd FPRs as singles, epilogue
 * view_test_epilogue), the frustum variant of camera_view_test_sphere without a camera record: m (4x4 floats) maps the point to
 * (u, v, w); outside when w - r > -D_800D9F40 (in front of the near bound) or w + r < -far, or when u / v scaled by
 * D_800D3A00[0] / [1] leave +-(depth + half size) with the half sizes r / ry scaled by 0.70710677 (sqrt(1/2)),
 * depth = -w (the asm's c.ule / c.olt: a NaN passes every test). Returns 0 when outside, else round(-w) (0 stays 0).
 */
/* was func_150A66F0 */
s32 view_sphere_depth(f32 *m, f32 x, f32 y, f32 z, f32 r, f32 ry, f32 far) {
    f32 u, v, w, depth, lim, rs, rys;

    w = (m[2] * x + m[6] * y) + (m[10] * z + m[14]);
    if (w - r > -D_800D9F40) {
        return 0;
    }
    if (w + r < -far) {
        return 0;
    }
    depth = -w;
    u = (m[0] * x + m[4] * y) + (m[8] * z + m[12]);
    rs = r * 0.70710677f;
    lim = depth + rs;
    if ((u - rs) * D_800D3A00[0] > lim) {
        return 0;
    }
    if ((u + rs) * D_800D3A00[0] < -lim) {
        return 0;
    }
    v = (m[1] * x + m[5] * y) + (m[9] * z + m[13]);
    rys = ry * 0.70710677f;
    if ((v - rys) * D_800D3A00[1] > lim) {
        return 0;
    }
    if ((v + rys) * D_800D3A00[1] < -lim) {
        return 0;
    }
    return VIEW66F0_RINT(depth);
}

/* was func_150A6834 */
void view_test_epilogue(void) {

}
extern f32 D_800D9F40; /* screen width (also the near-depth bound here) */
s32 world_objects_in_box(s32, s32, s32 *, s32, s32, s32, s32, s32);

/* cvt.w.s with the default FCSR mode: round to nearest, ties to even */
#define VIEW6840_RINT(f)                                                                             \
    (((f) >= 8388608.0f || (f) <= -8388608.0f) ? (s32)(f)                                            \
     : ((f) >= 0.0f) ? (s32)(((f) + 8388608.0f) - 8388608.0f)                                       \
                     : -(s32)((-(f) + 8388608.0f) - 8388608.0f))

/*
 * P38: view test of a sphere / box (hand asm, FR=1 odd FPRs as singles). cam: camera record (D_800BE628 + i * 0x180,
 * side planes at +0x88..+0xB4), m: view matrix (4x4 floats). (x, y, z) is transformed by m into (u, v, w):
 * outside when w - r > -D_800D9F40 (in front of the near bound), w + r < -far, or a side plane test
 * u * p0 + w * p2 < -r (planes +0x88/+0x90, +0x94/+0x9C) or v * p0 + w * p2 < -ry (+0xA4/+0xA8, +0xB0/+0xB4)
 * (NaN counts as outside). Returns 0 when outside, else round(w), or 1 when that is 0.
 */
/* was func_150A6840 */
s32 camera_view_test_sphere(s32 cam, s32 *mtx, f32 x, f32 y, f32 z, f32 r, f32 ry, f32 far) {
    f32 *m = (f32 *)mtx;
    u8 *c = (u8 *)cam;
    f32 u, v, w;
    s32 ret;

    w = (m[2] * x + m[6] * y) + (m[10] * z + m[14]);
    if (!(w - r <= -D_800D9F40)) {
        return 0;
    }
    if (w + r < -far) {
        return 0;
    }
    u = (m[0] * x + m[4] * y) + (m[8] * z + m[12]);
    if (!(u * *(f32 *)(c + 0x88) + w * *(f32 *)(c + 0x90) >= -r)) {
        return 0;
    }
    if (!(u * *(f32 *)(c + 0x94) + w * *(f32 *)(c + 0x9C) >= -r)) {
        return 0;
    }
    v = (m[1] * x + m[5] * y) + (m[9] * z + m[13]);
    if (!(v * *(f32 *)(c + 0xA4) + w * *(f32 *)(c + 0xA8) >= -ry)) {
        return 0;
    }
    if (!(v * *(f32 *)(c + 0xB0) + w * *(f32 *)(c + 0xB4) >= -ry)) {
        return 0;
    }
    ret = VIEW6840_RINT(w);
    if (ret == 0) {
        ret = 1;
    }
    return ret;
}

/* world_objects_in_box(a0, a1, a2, 0, a0, a1, -10000, a3) (same .s as camera_view_test_sphere) */
s32 func_150A69A8(s32 arg0, s32 arg1, s32 *arg2, s32 arg3) {
    return world_objects_in_box(arg0, arg1, arg2, 0, arg0, arg1, -10000, arg3);
}

/* P54: func_150A6840_tail.s no longer needed (world_objects_in_box is C) */

/*
 * P65: world_objects_in_box over the point box (x, z) .. (x, z) and y -10000 .. 20000 (all heights). Called by
 * collision_query_dynamic_cells with outCount = &count. The .s also holds a second, unreferenced entry at 0x150A6A18 (no caller,
 * no symbol: it would pass its caller's stack words as the box), not translated.
 */
/* was func_150A69E0 */
s32 world_objects_at_point(s32 x, s32 z, s32 *outCount, s32 n) {
    return world_objects_in_box(x, z, outCount, n, x, z, -10000, 20000);
}

/*
 * P54: world_objects_in_box (hand asm): the world objects (D_800DBEF4, D_800DC320 of them, 0xA0 bytes) whose box
 * (+0x10 / +0x12 / +0x14 centre, +0x50 x/z half size, +0x52 y half size) overlaps (x .. x2, z .. z2) and, unless
 * +0x4F & 0x40, (y .. y2), all bounds strict; skipped: +0x6E != 0, +0x4F & 0x60 == 0x20, index n - 1.
 * Indices with +0x4F & 0x60 == 0 go to the u16 list D_800D3C00 (the count is returned), the others (0x40 / 0x60)
 * to D_800D3C50 (count in *outCount).
 */
extern s32 D_800D3C00;
extern s32 D_800D3C50;

/* was func_150A6A48 */
s32 world_objects_in_box(s32 x, s32 z, s32 *outCount, s32 n, s32 x2, s32 z2, s32 y, s32 y2) {
    u16 *l0 = (u16 *)&D_800D3C00;
    u16 *l1 = (u16 *)&D_800D3C50;
    u8 *obj, *end;
    s32 n0 = 0, n1 = 0, i = 0;
    s32 k, r, c;

    *outCount = 0;
    if (D_800DC320 == 0) return 0;
    obj = (u8 *)D_800DBEF4;
    end = obj + (s32)((u32)D_800DC320 * 0xA0u);
    do {
        if (obj[0x6E] != 0) goto next;
        k = obj[0x4F] & 0x60;
        if (k == 0x20) goto next;
        r = *(u16 *)(obj + 0x50);
        c = *(s16 *)(obj + 0x10);
        if (!(c - r < x2) || !(x < c + r)) goto next;
        c = *(s16 *)(obj + 0x14);
        if (!(c - r < z2) || !(z < c + r)) goto next;
        if ((obj[0x4F] & 0x40) != 0x40) {
            r = *(u16 *)(obj + 0x52);
            c = *(s16 *)(obj + 0x12);
            if (!(c - r < y2) || !(y < c + r)) goto next;
        }
        if (i == n - 1) goto next;
        if (k != 0) {
            n1++;
            *l1++ = i;
        } else {
            n0++;
            *l0++ = i;
        }
    next:
        obj += 0xA0;
        i++;
    } while (obj != end);
    *outCount = n1;
    return n0;
}

/* P128 */
extern s32 D_eu_800BE9F4; /* PVS row index: per row {u16 byte index, s16 bit} (pvs_setup) */
extern s32 D_eu_800BE9F8; /* Huffman tree: 6-byte nodes {s16 symbol (< 0: inner), s16 child 0, s16 child 1} */
extern s16 D_800DC260[]; /* current PVS row per view (player_zone_update) */
extern s32 D_800DC278; /* record list head (func_150A4ED4) */

// pvs_row_apply: (hand asm) decodes PVS row D_800DC260[view] from the Huffman bit stream D_800BE5D0 and writes
// bit `view` of the s16 visibility word (+0) of every record in the D_800DC278 list (next record at +0xC, else +4,
// byte offsets; 0 ends the list). One decoded symbol gives 8 records, LSB first. Bits are read MSB first; the row
// start {byte, bit} comes from D_eu_800BE9F4 (byte 0xFFFF = none loaded yet: read as u16, as in the asm).
// Shift counts use the low 5 bits (srlv).
/* was func_150A6C40 */
void pvs_row_apply(s32 view) {
    u8 *p;
    u8 *rec;
    s16 *node;
    s16 *row;
    s32 cur;
    s32 bit;
    s32 k;
    s32 sym;
    s32 keep;

    if (D_800BE5D0 == 0) {
        return;
    }
    keep = ~(1 << view);
    rec = (u8 *) D_800DC278;
    k = 0;
    row = (s16 *) (D_eu_800BE9F4 + D_800DC260[view] * 4);
    bit = row[1];
    p = (u8 *) D_800BE5D0 + *(u16 *) row;
    cur = *p;
    if (rec == NULL) {
        return;
    }
    for (;;) {
        if (k == 0) {
            node = (s16 *) D_eu_800BE9F8;
            while ((sym = node[0]) < 0) {
                if (bit == 0) {
                    p++;
                    cur = *p;
                    bit = 7;
                } else {
                    bit--;
                }
                node = (s16 *) (D_eu_800BE9F8 + (((cur >> (bit & 0x1F)) & 1) ? node[2] : node[1]));
            }
        }
        *(s16 *) rec = (*(s16 *) rec & keep) | (((sym >> k) & 1) << view);
        if (k < 7) {
            k++;
        } else {
            k = 0;
        }
        if (*(s16 *) (rec + 0xC) != 0) {
            rec += *(s16 *) (rec + 0xC);
        } else if (*(s16 *) (rec + 4) != 0) {
            rec += *(s16 *) (rec + 4);
        } else {
            return;
        }
    }
}
