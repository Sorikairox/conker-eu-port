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

// shadow_project_vertex: (hand asm func_150A661C, private t4 -> f13..f15 / t3 call) transforms the s16 vertex v by
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

// shadow_emit_triangle: (part of func_150A6070 / func_150A6324) projects triangle tri, whose vertex pointers are
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
s32 func_150A6070(u32 *mask, s32 out, f32 *m, s32 end) {
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

// shadow_object_triangles: (hand asm) as func_150A6070 for D_800DF514 (>= 1) world objects: ids[i] selects the
// 0xA0-byte record D_800DBEF4 + id * 0xA0 (u16 triangle count +0x56, first triangle +0x58, >= 1 triangle) whose
// vertex offsets are relative to D_800DC328[id].
s32 func_150A6324(u16 *ids, s32 out, f32 *m, s32 end) {
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
