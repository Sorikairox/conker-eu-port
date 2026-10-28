/*
 * NON_MATCHING C for functions of the raw asm file asm/D5E90.s (a splat `asm` segment, not a pragma-included function).
 * Compiled and linked only with NON_MATCHING=1 (Makefile: NM_ASM_*): the asm copy of each function listed
 * in NM_ASM_C_FUNCS_D5E90 is weakened in build_nm/asm/D5E90.s.o, so this definition wins. The default build
 * never sees this file.
 *
 * The hand-written asm uses private register conventions between its helpers (points in f3-f5 / f6-f11,
 * box in f0-f2, triangle in f23-f31, plane in f19-f22, outcode masks in v1/a0/t8); here they are static
 * functions with ordinary arguments.
 */
#include <ultra64.h>

#include "functions.h"
#include "variables.h"

/* box half extents (g_quadtree_box_half_x/50/54) and the y/x, z/x ratios used for the box diagonals (g_quadtree_box_ratio_yx/5C) */
extern f32 g_tri_plane_nx; /* plane of the last tested triangle: normal x, y, z, then d; was D_800CC630 */
extern f32 g_tri_plane_ny; /* was D_800CC634 */
extern f32 g_tri_plane_nz; /* was D_800CC638 */
extern f32 g_tri_plane_d; /* was D_800CC63C */
extern f32 g_nm_tri_bbox_slack; /* slack of the point-in-triangle bounding-box test; was D_8009FAB0 */

#define NM_FABS(x) ((x) < 0.0f ? -(x) : (x))

typedef struct {
    f32 x, y, z;
} TriPt;

/* Triangle / box intersection after D. Voorhies, "Triangle-Cube Intersection" (Graphics Gems III), for a
 * box centred on the origin with half extents (hx, hy, hz). */

/* face_plane: one bit per box face the point is outside of */
static s32 nmD5E90_outcode(TriPt *p) {
    s32 r = 0;

    if (!(p->x <= g_quadtree_box_half_x)) r |= 1;
    if (p->x < -g_quadtree_box_half_x) r |= 2;
    if (!(p->y <= g_quadtree_box_half_y)) r |= 4;
    if (p->y < -g_quadtree_box_half_y) r |= 8;
    if (!(p->z <= g_quadtree_box_half_z)) r |= 0x10;
    if (p->z < -g_quadtree_box_half_z) r |= 0x20;
    return r;
}

/* bevel_2d: the 12 edge planes */
static s32 nmD5E90_bevel2d(TriPt *p) {
    s32 r = 0;
    f32 s;

    s = g_quadtree_box_half_x + g_quadtree_box_half_y;
    if (!(p->x + p->y <= s)) r |= 1;
    if (!(p->x - p->y <= s)) r |= 2;
    if (!(-(p->x + p->y) <= s)) r |= 8;
    if (!(-(p->x - p->y) <= s)) r |= 4;
    s = g_quadtree_box_half_x + g_quadtree_box_half_z;
    if (!(p->x + p->z <= s)) r |= 0x10;
    if (!(p->x - p->z <= s)) r |= 0x20;
    if (!(-(p->x + p->z) <= s)) r |= 0x80;
    if (!(-(p->x - p->z) <= s)) r |= 0x40;
    s = g_quadtree_box_half_y + g_quadtree_box_half_z;
    if (!(p->y + p->z <= s)) r |= 0x100;
    if (!(p->y - p->z <= s)) r |= 0x200;
    if (!(-(p->y + p->z) <= s)) r |= 0x800;
    if (!(-(p->y - p->z) <= s)) r |= 0x400;
    return r;
}

/* bevel_3d: the 8 corner planes */
static s32 nmD5E90_bevel3d(TriPt *p) {
    s32 r = 0;
    f32 s = g_quadtree_box_half_x + g_quadtree_box_half_y + g_quadtree_box_half_z;
    f32 a = p->x + p->y;
    f32 b = p->x - p->y;
    f32 ppp = a + p->z;
    f32 ppm = a - p->z;
    f32 pmp = b + p->z;
    f32 pmm = b - p->z;

    if (!(ppp <= s)) r |= 1;
    if (!(ppm <= s)) r |= 2;
    if (!(pmp <= s)) r |= 4;
    if (!(pmm <= s)) r |= 8;
    if (!(-ppp <= s)) r |= 0x80;
    if (!(-ppm <= s)) r |= 0x40;
    if (!(-pmp <= s)) r |= 0x20;
    if (!(-pmm <= s)) r |= 0x10;
    return r;
}

/* check_point: is b + (a - b) * t inside every face plane except the ones cleared from mask */
static s32 nmD5E90_checkPoint(TriPt *a, TriPt *b, f32 t, s32 mask) {
    TriPt q;

    q.x = (a->x - b->x) * t + b->x;
    q.y = (a->y - b->y) * t + b->y;
    q.z = (a->z - b->z) * t + b->z;
    return nmD5E90_outcode(&q) & mask;
}

/* check_line: 0 if the segment a-b crosses a box face inside the box (diff = the end points' outcodes) */
static s32 nmD5E90_checkLine(TriPt *a, TriPt *b, s32 diff) {
    f32 inv;

    if (diff & 3) {
        inv = 1.0f / (a->x - b->x);
        if ((diff & 1) && nmD5E90_checkPoint(a, b, (g_quadtree_box_half_x - b->x) * inv, 0x3E) == 0) return 0;
        if ((diff & 2) && nmD5E90_checkPoint(a, b, -(g_quadtree_box_half_x + b->x) * inv, 0x3D) == 0) return 0;
    }
    if (diff & 0xC) {
        inv = 1.0f / (a->y - b->y);
        if ((diff & 4) && nmD5E90_checkPoint(a, b, (g_quadtree_box_half_y - b->y) * inv, 0x3B) == 0) return 0;
        if ((diff & 8) && nmD5E90_checkPoint(a, b, -(g_quadtree_box_half_y + b->y) * inv, 0x37) == 0) return 0;
    }
    if (diff & 0x30) {
        inv = 1.0f / (a->z - b->z);
        if ((diff & 0x10) && nmD5E90_checkPoint(a, b, (g_quadtree_box_half_z - b->z) * inv, 0x2F) == 0) return 0;
        if ((diff & 0x20) && nmD5E90_checkPoint(a, b, -(g_quadtree_box_half_z + b->z) * inv, 0x1F) == 0) return 0;
    }
    return 1;
}

/* sign bits of (a - b) x (a - p); components with |c| < 1 are dropped from *mask */
static s32 nmD5E90_sign3(TriPt *p, TriPt *a, TriPt *b, s32 *mask) {
    f32 ex = a->x - b->x, ey = a->y - b->y, ez = a->z - b->z;
    f32 px = a->x - p->x, py = a->y - p->y, pz = a->z - p->z;
    f32 cx = ey * pz - ez * py;
    f32 cy = ez * px - ex * pz;
    f32 cz = ex * py - ey * px;
    s32 r = 0;

    if (cx < 0.0f) r |= 4;
    if (cy < 0.0f) r |= 2;
    if (cz < 0.0f) r |= 1;
    if (NM_FABS(cx) < 1.0f) *mask &= 3;
    if (NM_FABS(cy) < 1.0f) *mask &= 5;
    if (NM_FABS(cz) < 1.0f) *mask &= 6;
    return r;
}

/* point_triangle_intersection: 0 if p (on the triangle's plane) is inside the triangle, else 1 */
static s32 nmD5E90_pointInTri(TriPt *p, TriPt *v) {
    f32 eps = g_nm_tri_bbox_slack;
    f32 lo, hi;
    s32 k, mask, s1, s2, s3;

    for (k = 0; k < 3; k++) {
        f32 c0 = ((f32 *) &v[0])[k], c1 = ((f32 *) &v[1])[k], c2 = ((f32 *) &v[2])[k];
        f32 pc = ((f32 *) p)[k];

        lo = hi = c0;
        if (c1 < c0) {
            lo = c1;
        } else {
            hi = c1;
        }
        if (c2 < lo) {
            lo = c2;
        } else if (!(c2 <= hi)) {
            hi = c2;
        }
        if (!(pc <= hi + eps) || pc < lo - eps) {
            return 1;
        }
    }
    mask = 7;
    s1 = nmD5E90_sign3(p, &v[0], &v[1], &mask);
    s2 = nmD5E90_sign3(p, &v[1], &v[2], &mask);
    s3 = nmD5E90_sign3(p, &v[2], &v[0], &mask);
    if ((s1 & mask) != (s2 & mask) || (s2 & mask) != (s3 & mask)) {
        return 1;
    }
    return 0;
}

/* plane of the triangle, also stored in g_tri_plane_nx..3C */
static void nmD5E90_plane(TriPt *v, f32 *n) {
    f32 dy12 = v[0].y - v[1].y, dz13 = v[0].z - v[2].z, dy13 = v[0].y - v[2].y;
    f32 dz12 = v[0].z - v[1].z, dx12 = v[0].x - v[1].x, dx13 = v[0].x - v[2].x;

    n[0] = dy12 * dz13 - dz12 * dy13;
    n[1] = dz12 * dx13 - dx12 * dz13;
    n[2] = dx12 * dy13 - dy12 * dx13;
    n[3] = n[0] * v[0].x + n[1] * v[0].y + n[2] * v[0].z;
    g_tri_plane_nx = n[0];
    g_tri_plane_ny = n[1];
    g_tri_plane_nz = n[2];
    g_tri_plane_d = n[3];
}

/* one of the 4 box diagonals (1, sy * ky, sz * kz) against the triangle's plane: 0 if it hits the triangle */
static s32 nmD5E90_diagonal(TriPt *v, f32 *n, f32 sy, f32 sz) {
    f32 ny = n[1] * g_quadtree_box_ratio_yx;
    f32 nz = n[2] * g_quadtree_box_ratio_zx;
    f32 denom = n[0] + sy * ny + sz * nz;
    f32 t;
    TriPt q;

    if (denom == 0.0f) {
        denom = 0.0001f;
    }
    t = n[3] / denom;
    if (NM_FABS(t) <= g_quadtree_box_half_x) {
        q.x = t;
        q.y = sy * (t * g_quadtree_box_ratio_yx);
        q.z = sz * (t * g_quadtree_box_ratio_zx);
        if (nmD5E90_pointInTri(&q, v) == 0) {
            return 0;
        }
    }
    return 1;
}

/* Triangle (9 floats, the 3 vertices relative to the box centre) vs the box g_quadtree_box_half_x/50/54.
 * Returns 0 if they intersect, 1 if the triangle is outside. When the test gets past the vertex-in-box
 * check, the triangle's plane is left in g_tri_plane_nx..3C. Used by quadtree_tri_box_test (quadtree culling). */
/* was func_150AB278 */
s32 collision_tri_box_test(struct_eu_bytes24 arg0) {
    TriPt *v = (TriPt *) arg0.unk0;
    f32 n[4];
    s32 o1, o2, o3;

    o1 = nmD5E90_outcode(&v[0]);
    if (o1 == 0) goto inside;
    o2 = nmD5E90_outcode(&v[1]);
    if (o2 == 0) goto inside;
    o3 = nmD5E90_outcode(&v[2]);
    if (o3 == 0) goto inside;
    if (o1 & o2 & o3) return 1;
    o1 |= nmD5E90_bevel2d(&v[0]) << 8;
    o2 |= nmD5E90_bevel2d(&v[1]) << 8;
    o3 |= nmD5E90_bevel2d(&v[2]) << 8;
    if (o1 & o2 & o3) return 1;
    o1 |= nmD5E90_bevel3d(&v[0]) << 24;
    o2 |= nmD5E90_bevel3d(&v[1]) << 24;
    o3 |= nmD5E90_bevel3d(&v[2]) << 24;
    if (o1 & o2 & o3) return 1;
    if ((o1 & o2) == 0 && nmD5E90_checkLine(&v[0], &v[1], o1 | o2) == 0) goto inside;
    if ((o1 & o3) == 0 && nmD5E90_checkLine(&v[0], &v[2], o1 | o3) == 0) goto inside;
    if ((o2 & o3) == 0 && nmD5E90_checkLine(&v[1], &v[2], o2 | o3) == 0) goto inside;
    nmD5E90_plane(v, n);
    if (n[2] < 0.0f) {
        n[0] = -n[0];
        n[1] = -n[1];
        n[2] = -n[2];
        n[3] = -n[3];
    }
    if (nmD5E90_diagonal(v, n, 1.0f, 1.0f) == 0) return 0;
    if (nmD5E90_diagonal(v, n, 1.0f, -1.0f) == 0) return 0;
    if (nmD5E90_diagonal(v, n, -1.0f, 1.0f) == 0) return 0;
    if (nmD5E90_diagonal(v, n, -1.0f, -1.0f) == 0) return 0;
    return 1;

inside:
    nmD5E90_plane(v, n);
    return 0;
}
/* ---- fast_cosf / fast_sinf: cosf / sinf (P24) ----
 * sin: |x| < 2^-12 -> x; |x| < 1.5 -> odd polynomial; |x| < 2^28 -> reduce by n = round(x / pi) with a two-part
 * pi (g_fast_sinf_pi_hi + g_fast_sinf_pi_lo), polynomial, negate for odd n; else (and inf/NaN) 0. cos(x) = sin(x + pi/2).
 * The asm tests the float bits: (bits >> 22) & 0x1FF is the exponent plus the top mantissa bit. */
extern f32 g_fast_sinf_half_pi; /* pi/2; was D_8009FAE0 */
extern f32 g_fast_sinf_small_k3, g_fast_sinf_small_k2, g_fast_sinf_small_k1, g_fast_sinf_small_k0; /* small-range coefficients; was D_8009FAE4; was D_8009FAE8; was D_8009FAEC; was D_8009FAF0 */
extern f32 g_fast_sinf_inv_pi; /* 1/pi; was D_8009FAF4 */
extern f32 g_fast_sinf_pi_hi, g_fast_sinf_pi_lo; /* pi high / low part; was D_8009FAF8; was D_8009FAFC */
extern f32 g_fast_sinf_red_k4, g_fast_sinf_red_k3, g_fast_sinf_red_k2, g_fast_sinf_red_k1; /* reduced-range coefficients; was D_8009FB00; was D_8009FB04; was D_8009FB08; was D_8009FB0C */

/* cvt.w.s with the default FCSR mode: round to nearest, ties to even */
static s32 nmD5E90_rint(f32 f) {
    if (f >= 8388608.0f || f <= -8388608.0f) {
        return (s32)f; /* already integral */
    }
    if (f >= 0.0f) {
        return (s32)((f + 8388608.0f) - 8388608.0f);
    }
    return -(s32)((-f + 8388608.0f) - 8388608.0f);
}

/* was func_150AD78C */
f32 fast_sinf(f32 x) {
    union {
        f32 f;
        s32 w;
    } u;
    s32 e;
    s32 n;
    f32 nf;
    f32 x2;
    f32 r;

    u.f = x;
    e = (u.w >> 22) & 0x1FF;
    if (e < 0xFF) {
        if (e < 0xE6) {
            return x;
        }
        x2 = x * x;
        r = ((g_fast_sinf_small_k3 * x2 + g_fast_sinf_small_k2) * x2 + g_fast_sinf_small_k1) * x2 + g_fast_sinf_small_k0;
        return r * (x2 * x) + x;
    }
    if (e >= 0x136) {
        return 0.0f;
    }
    n = nmD5E90_rint(g_fast_sinf_inv_pi * x);
    nf = (f32)n;
    x = x - g_fast_sinf_pi_hi * nf;
    x = x - g_fast_sinf_pi_lo * nf;
    x2 = x * x;
    r = (((g_fast_sinf_red_k4 * x2 + g_fast_sinf_red_k3) * x2 + g_fast_sinf_red_k2) * x2 + g_fast_sinf_red_k1) * x2;
    r = r * x + x;
    if (n & 1) {
        r = -r;
    }
    return r;
}

/* was func_150AD780 */
f32 fast_cosf(f32 x) {
    return fast_sinf(x + g_fast_sinf_half_pi);
}

/* ---- P56: wall engine collision_walls_slide / collision_ledge_probe (-> func_150AB708) and ray cast collision_ray_cast ----
 * Hand asm with private register conventions: the helpers pass points / boxes / planes in FPRs, the engine keeps
 * its state in s0-s7 / fp / gp / f23-f31 across helpers and jumps through 4 continuation pointers that each entry
 * stub stores at sp+0x1D0..0x1DC (map: docs/port/sessions/P53.md section 5). P56 first translated it register by
 * register (D5E90_walls.inc / D5E90_ray.inc, tools/port/asm2c_hand.py); since P294 all of it is readable C below
 * (helpers P281-P288, ray cast P291, engine P294) and the .inc files are gone. */
#include <libc/math.h>

extern u8 g_nmw_k_deg_to_rad[], g_nmw_ledge_vertical_slope[], g_nmw_ledge_grab_radius_sq[], g_nmw_k_rad_to_deg[], g_model_tri_counts[], g_wall_ledge_grab_z[], g_wall_ledge_angle_neg[]; /* was D_800C5D38; was D_8009FAC0; was D_8009FAC8; was D_8009FACC; was D_8009FAD0; was D_800CC1B0; was D_800CC1B4 */
extern u8 g_wall_ledge_angle_pos[], g_obj_attached_world_obj[], g_wall_coll_no_floor_skip[], g_wall_coll_soft_edges[], g_wall_coll_no_clamp[], g_wall_coll_height[], g_wall_coll_lift[]; /* was D_800CC1F2; was D_800CC1F3; was D_800CC1F4; was D_800CC1F8; was D_800CC1FC; was D_800CC1B8; was D_800CC1C0 */
extern u8 g_world_obj_box_ids[], g_level_tri_table[], g_coll_tri_xz_bounds[], g_coll_tri_y_bounds[], g_zone_tree[], g_world_obj_rider_masks[]; /* was D_800DC3C4; was D_800DC26C; was D_800D3C00; was D_800DC270; was D_800DC274; was D_800DC278 */
s32 obj_collision_cylinder(struct127 *, s16 *, s16 *, s16 *);
s32 func_150A69A8(s32, s32, s32 *, s32);
s32 world_objects_transform_mesh(s32, s32 *, s32);
void collision_select_area(s32);

/* BSP node of the level collision tree (g_quadtree_roots): a square of half size `half` around (cx, cz); `next` = byte
 * offset to the next sibling (0: last), `child` = byte offset to the first child (0: leaf, the triangle list follows). */
typedef struct {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ s16 next;
    /* 0x06 */ u16 half;
    /* 0x08 */ s16 cx;
    /* 0x0A */ s16 cz;
    /* 0x0C */ s16 child;
    /* 0x0E */ u8 list[1]; /* leaf: triangle indices, 0-terminated: 0x80 | hi, lo = absolute; 1..0x7F = previous + n */
} NmrNode;

/* collidable object (g_world_objs[g_world_obj_count], 0xA0 bytes): the fields the ray cast reads */
#define NMR_OBJ_SIZE 0xA0
#define NMR_OBJ_S16(o, off) (*(s16 *) ((u8 *) (o) + (off)))
#define NMR_OBJ_U16(o, off) (*(u16 *) ((u8 *) (o) + (off)))
#define NMR_OBJ_CX 0x10       /* s16 centre x, y, z (0x10 / 0x12 / 0x14) */
#define NMR_OBJ_FLAGS 0x40    /* u32 flags of every triangle when the table below is NULL */
#define NMR_OBJ_TRIFLAGS 0x44 /* u32 * per-triangle flags, indexed from the first triangle */
#define NMR_OBJ_MODE 0x4F     /* u8: (mode & 0x60) == 0x20 -> not collidable */
#define NMR_OBJ_RADIUS1 0x50  /* u16 radii: the larger one bounds the object */
#define NMR_OBJ_RADIUS2 0x52
#define NMR_OBJ_NTRIS 0x56    /* u16 triangle count */
#define NMR_OBJ_TRI0 0x58     /* u16 first triangle (index into the shared triangle tables) */
#define NMR_OBJ_OFF 0x6E      /* u8: != 0 -> not collidable */

typedef union {
    f32 f;
    u32 u;
    s32 i;
} NmwReg;


/* P281 / P285 / P288: the wall engine's private helpers (register conventions of the asm in each comment). */
/* box_outcode (func_150AA950): one bit per face of the box (+/- hx, hy, hz) the point (x, y, z) lies beyond:
 * 1 / 2 = x above hx / below -hx, 4 / 8 = y, 0x10 / 0x20 = z (ordered compares: a NaN coordinate sets no bit) */
static s32 nmw_box_outcode(f32 x, f32 y, f32 z, f32 hx, f32 hy, f32 hz) {
    s32 code = 0;

    if (x > hx) code |= 1;
    if (x < -hx) code |= 2;
    if (y > hy) code |= 4;
    if (y < -hy) code |= 8;
    if (z > hz) code |= 0x10;
    if (z < -hz) code |= 0x20;
    return code;
}

/* box_edge_outcode (func_150AA9B0): one bit per edge plane of the box (the 12 planes |a| + |b| = ha + hb of the
 * axis pairs xy, xz, yz) the point lies beyond: per pair a + b, a - b, -(a + b), -(a - b) give bits 1, 2, 8, 4
 * (xy), 0x10, 0x20, 0x80, 0x40 (xz), 0x100, 0x200, 0x800, 0x400 (yz) */
static s32 nmw_box_edge_outcode(f32 x, f32 y, f32 z, f32 hx, f32 hy, f32 hz) {
    s32 code = 0;
    f32 e, s, d;

    e = hx + hy;
    s = x + y;
    d = x - y;
    if (s > e) code |= 1;
    if (d > e) code |= 2;
    if (-s > e) code |= 8;
    if (-d > e) code |= 4;
    e = hx + hz;
    s = x + z;
    d = x - z;
    if (s > e) code |= 0x10;
    if (d > e) code |= 0x20;
    if (-s > e) code |= 0x80;
    if (-d > e) code |= 0x40;
    e = hy + hz;
    s = y + z;
    d = y - z;
    if (s > e) code |= 0x100;
    if (d > e) code |= 0x200;
    if (-s > e) code |= 0x800;
    if (-d > e) code |= 0x400;
    return code;
}

/* box_corner_outcode (func_150AAA88): one bit per corner plane of the box (|x| + |y| + |z| = hx + hy + hz):
 * x + y + z, x + y - z, x - y + z, x - y - z give bits 1, 2, 4, 8, their negations 0x80, 0x40, 0x20, 0x10 */
static s32 nmw_box_corner_outcode(f32 x, f32 y, f32 z, f32 hx, f32 hy, f32 hz) {
    s32 code = 0;
    f32 e, a, b, c, d;

    e = hx + hy + hz;
    a = x + y + z;
    b = x + y - z;
    c = x - y + z;
    d = x - y - z;
    if (a > e) code |= 1;
    if (b > e) code |= 2;
    if (c > e) code |= 4;
    if (d > e) code |= 8;
    if (-a > e) code |= 0x80;
    if (-b > e) code |= 0x40;
    if (-c > e) code |= 0x20;
    if (-d > e) code |= 0x10;
    return code;
}


/* lerp_outcode (func_150AAB24): box_outcode of the point b + (a - b) * t, masked */
static s32 nmw_lerp_outcode(f32 *a, f32 *b, f32 t, f32 hx, f32 hy, f32 hz, s32 mask) {
    f32 x = (a[0] - b[0]) * t + b[0];
    f32 y = (a[1] - b[1]) * t + b[1];
    f32 z = (a[2] - b[2]) * t + b[2];

    return nmw_box_outcode(x, y, z, hx, hy, hz) & mask;
}

/* segment_misses_box (func_150AAB58): 0 if the segment a-b crosses one of the box faces named in diff (the end
 * points' outcode bits 1 / 2 = +x / -x .. 0x10 / 0x20 = +z / -z) at a point inside all the other face planes, else 1 */
static s32 nmw_segment_misses_box(f32 *a, f32 *b, s32 diff, f32 hx, f32 hy, f32 hz) {
    f32 inv;

    if (diff & 3) {
        inv = 1.0f / (a[0] - b[0]);
        if ((diff & 1) && nmw_lerp_outcode(a, b, (hx - b[0]) * inv, hx, hy, hz, 0x3E) == 0) return 0;
        if ((diff & 2) && nmw_lerp_outcode(a, b, -(hx + b[0]) * inv, hx, hy, hz, 0x3D) == 0) return 0;
    }
    if (diff & 0xC) {
        inv = 1.0f / (a[1] - b[1]);
        if ((diff & 4) && nmw_lerp_outcode(a, b, (hy - b[1]) * inv, hx, hy, hz, 0x3B) == 0) return 0;
        if ((diff & 8) && nmw_lerp_outcode(a, b, -(hy + b[1]) * inv, hx, hy, hz, 0x37) == 0) return 0;
    }
    if (diff & 0x30) {
        inv = 1.0f / (a[2] - b[2]);
        if ((diff & 0x10) && nmw_lerp_outcode(a, b, (hz - b[2]) * inv, hx, hy, hz, 0x2F) == 0) return 0;
        if ((diff & 0x20) && nmw_lerp_outcode(a, b, -(hz + b[2]) * inv, hx, hy, hz, 0x1F) == 0) return 0;
    }
    return 1;
}

/* triangle_to_local (func_150AC824): the triangle whose 3 vertex offsets (from base) are at tri (s16 x, y, z each),
 * relative to the centre (cx, cy, cz) and turned by the heading (sine si, cosine co) about y:
 * x' = dx co + dz si, y' = dy, z' = dz co - dx si; out = the 9 floats (f23-f31 in the asm) */
static void nmw_tri_to_local(u32 *tri, u32 base, f32 cx, f32 cy, f32 cz, f32 si, f32 co, f32 *out) {
    s32 i;
    s16 *v;
    f32 dx, dy, dz;

    for (i = 0; i < 3; i++) {
        v = (s16 *) (tri[i] + base);
        dx = (f32) v[0] - cx;
        dy = (f32) v[1] - cy;
        dz = (f32) v[2] - cz;
        out[3 * i + 0] = dx * co + dz * si;
        out[3 * i + 1] = dy;
        out[3 * i + 2] = dz * co - dx * si;
    }
}

/* box_diagonal_misses (part of func_150AAF00): the box diagonal (1, sy * ky, sz * kz) with ky / kz = g_quadtree_box_ratio_yx /
 * g_quadtree_box_ratio_zx meets the plane n (n[0..2] . p = n[3]) at x = t; 0 if |t| is not beyond hx (NaN passes too) and that
 * point lies in the triangle v, else 1. A zero denominator is replaced by 0.0001. */
static s32 nmw_box_diagonal_misses(TriPt *v, f32 *n, f32 sy, f32 sz, f32 hx) {
    f32 ny = n[1] * g_quadtree_box_ratio_yx;
    f32 nz = n[2] * g_quadtree_box_ratio_zx;
    f32 denom = n[0] + sy * ny + sz * nz;
    f32 t;
    TriPt q;

    if (denom == 0.0f) {
        denom = 0.0001f;
    }
    t = n[3] / denom;
    if (NM_FABS(t) > hx) {
        return 1;
    }
    q.x = t;
    q.y = sy * (t * g_quadtree_box_ratio_yx);
    q.z = sz * (t * g_quadtree_box_ratio_zx);
    return nmD5E90_pointInTri(&q, v);
}

/* triangle_misses_box (func_150AAF00): the wall engine's copy of collision_tri_box_test with the box half extents in
 * registers (hx, hy, hz) instead of g_quadtree_box_half_x..54: 0 if the triangle v (vertices relative to the box centre) meets
 * the box, 1 if not. Same steps: a vertex inside -> hit; all vertices beyond one face / edge bevel / corner bevel ->
 * miss; an edge crossing the box -> hit; else the 4 box diagonals against the triangle's plane (made to face +z).
 * The plane is left in g_tri_plane_nx..3C whenever it is computed (the hit paths reload it from there). */
static s32 nmw_tri_misses_box(TriPt *v, f32 hx, f32 hy, f32 hz) {
    s32 o1, o2, o3;
    f32 n[4];

    o1 = nmw_box_outcode(v[0].x, v[0].y, v[0].z, hx, hy, hz);
    if (o1 == 0) goto hit;
    o2 = nmw_box_outcode(v[1].x, v[1].y, v[1].z, hx, hy, hz);
    if (o2 == 0) goto hit;
    o3 = nmw_box_outcode(v[2].x, v[2].y, v[2].z, hx, hy, hz);
    if (o3 == 0) goto hit;
    if (o1 & o2 & o3) return 1;
    o1 |= nmw_box_edge_outcode(v[0].x, v[0].y, v[0].z, hx, hy, hz) << 8;
    o2 |= nmw_box_edge_outcode(v[1].x, v[1].y, v[1].z, hx, hy, hz) << 8;
    o3 |= nmw_box_edge_outcode(v[2].x, v[2].y, v[2].z, hx, hy, hz) << 8;
    if (o1 & o2 & o3) return 1;
    o1 |= nmw_box_corner_outcode(v[0].x, v[0].y, v[0].z, hx, hy, hz) << 24;
    o2 |= nmw_box_corner_outcode(v[1].x, v[1].y, v[1].z, hx, hy, hz) << 24;
    o3 |= nmw_box_corner_outcode(v[2].x, v[2].y, v[2].z, hx, hy, hz) << 24;
    if (o1 & o2 & o3) return 1;
    if ((o1 & o2) == 0 && nmw_segment_misses_box(&v[0].x, &v[1].x, o1 | o2, hx, hy, hz) == 0) goto hit;
    if ((o1 & o3) == 0 && nmw_segment_misses_box(&v[0].x, &v[2].x, o1 | o3, hx, hy, hz) == 0) goto hit;
    if ((o2 & o3) == 0 && nmw_segment_misses_box(&v[1].x, &v[2].x, o2 | o3, hx, hy, hz) == 0) goto hit;
    nmD5E90_plane(v, n);
    if (!(n[2] >= 0.0f)) {
        n[0] = -n[0];
        n[1] = -n[1];
        n[2] = -n[2];
        n[3] = -n[3];
    }
    if (nmw_box_diagonal_misses(v, n, 1.0f, 1.0f, hx) == 0) return 0;
    if (nmw_box_diagonal_misses(v, n, 1.0f, -1.0f, hx) == 0) return 0;
    if (nmw_box_diagonal_misses(v, n, -1.0f, 1.0f, hx) == 0) return 0;
    if (nmw_box_diagonal_misses(v, n, -1.0f, -1.0f, hx) == 0) return 0;
    return 1;

hit:
    nmD5E90_plane(v, n);
    return 0;
}

/* ---- P294: the wall engine (func_150AB708 behind the entries collision_walls_slide / collision_ledge_probe), readable ----
 * A sliding move of a record (struct127, 0x32C bytes) from its position (rec+0x14..0x1C) towards a target, against
 * the collision triangles near the swept box (map: docs/port/sessions/P53.md section 5). The asm kept its state in
 * s0-s7 / fp / gp, f29-f31 and a 0x268-byte frame and jumped through 4 continuation pointers the entry stub stored
 * at sp+0x1D0..0x1DC; here the frame is NmwState (asm frame offsets in the comments) and the continuations are the
 * `ledge` flag:
 *   collision_walls_slide (walls):  box = move + radius, triangles pushed out of (face or nearest edge), result written back;
 *   collision_ledge_probe (ledges): box around the record turned by its heading, triangles only looked at (ledge grab
 *                           data in g_wall_ledge_h_neg..21C / g_wall_ledge_grab_z..B8, g_obj_attached_world_obj[record] = 1), nothing written back. */
#define NMW_F32(sym) (*(f32 *) (sym))
#define NMW_REC_SIZE 812 /* struct127 */

typedef struct {
    u8 *rec;             /* 0x140 the moving record */
    s32 nObjs;           /* s1: area kind 2: objects func_150A69A8 listed in g_world_obj_box_ids (else 0) */
    s32 cur;             /* 0x148 kind 2: current object index; kind 3: current record (pointer); else 0 */
    s32 curFirst;        /* 0x14C kind 2: the object's first triangle; kind 3: end of the records */
    u32 vbase;           /* 0x150 base of the triangles' vertex offsets (0: absolute) */
    s32 listPos;         /* 0x154 kind 2: position in g_world_obj_box_ids */
    s32 count;           /* 0x154 kind 3: triangles of the current record's model */
    s32 recNo;           /* 0x144 kind 3: 1 + index of the current record */
    s32 margin;          /* 0x158 widening of the xz box (s16 from obj_collision_cylinder) */
    s32 radius;          /* 0x15C (s16 from obj_collision_cylinder) */
    f32 radiusF;         /* 0x160 walls: how far triangles push the position away */
    s32 moved;           /* 0x164 result: 1 once a triangle pushed the position */
    s32 mark;            /* 0x168 kind 2: mark the objects touched */
    u32 noSlope;         /* 0x16C the triangle's flag 0x1000000: no "too flat to be a wall" test */
    u32 mask;            /* 0x28 triangle flags that must all be set (ledges: 0x0E000000) */
    f32 co, si;          /* 0x2C / 0x30 the frame's heading: walls: -dz, dx of the move (normalised); ledges: the
                          * record's heading (-cos, sin) */
    f32 pos[3];          /* 0x34 the position being resolved (starts at the record's) */
    f32 tgt[3];          /* 0x40 the target */
    u32 keepFall;        /* 0x4C rec+0x20 copy; walls clear rec+0x20 when this was zeroed */
    NmwReg dy;           /* 0x50 rec+0x20 (bits), after the first push pos y - target y */
    f32 yoff;            /* 0x54 g_wall_coll_lift: box centre above the record */
    f32 half[3];         /* 0x58 box half extents (g_quadtree_box_half_x..54, set by quadtree_set_test_box) */
    s32 prev;            /* 0x64 previous triangle of the leaf list (relative entries) */
    s32 nVisited;        /* 0x68 / gp */
    u16 visited[100];    /* 0x6C level triangles already tested (a triangle can be in several leaves) */
    f32 mid[3];          /* 0x134 box centre (y without yoff in walls mode) */
    NmrNode *node;       /* s0 next BSP node to walk (NULL: none) */
    u8 *cursor;          /* s7 position in the leaf's triangle list (NULL: walk to the next leaf) */
    s32 xmin, xmax;      /* s2 / s3 integer xz box of the move */
    s32 zmin, zmax;      /* s4 / s5 */
    s32 y;               /* fp rint(pos y) */
    s32 tri;             /* s6 current triangle */
    TriPt tv[3];         /* 0x20C its vertices in the box frame */
    f32 ledgeLo, ledgeHi; /* 0x1E0 / 0x1E4 ledges: 64 / 65, the ledge height window */
    f32 ledgeBest;       /* 0x208 ledges: squared xz distance of the nearest ledge so far */
#ifdef PORT
    u32 portFlags;       /* P352 option "Ledge grab everywhere": the current triangle's flags */
    s32 portAnyLedge;    /* P352: 1 = ledge mode takes every level triangle (the mask is 0), 0 = the N64 rule */
#endif
} NmwState;

/* move_box (func_150AC6A4): the integer xz box from the position p to the target widened by the margin, y = rint(p y);
 * also the move's heading (si, co) = (dx, -dz) / |(dx, dz)| when it has an xz length, and dy */
static void nmw_set_box(NmwState *w, f32 px, f32 py, f32 pz) {
    f32 dx, dz, l, x0, x1, z0, z1;

    w->y = nmD5E90_rint(py);
    dx = px - w->tgt[0];
    w->dy.f = py - w->tgt[1];
    dz = pz - w->tgt[2];
    l = dx * dx + dz * dz;
    if (l != 0.0f) {
        l = sqrtf(l);
        w->si = dx / l;
        w->co = -dz / l;
    }
    if (w->tgt[0] >= px) {
        x0 = px;
        x1 = w->tgt[0];
    } else {
        x0 = w->tgt[0];
        x1 = px;
    }
    if (w->tgt[2] >= pz) {
        z0 = pz;
        z1 = w->tgt[2];
    } else {
        z0 = w->tgt[2];
        z1 = pz;
    }
    w->xmin = (s32) x0 - w->margin;
    w->xmax = (s32) x1 + w->margin;
    w->zmin = (s32) z0 - w->margin;
    w->zmax = (s32) z1 + w->margin;
}

/* next_record (part of func_150ABBD0): area kind 3, the next record after w->cur that is not the mover, exists,
 * has flag 0x4000 at +0xF8 and a vertex base at +0x264; selects its model's triangles (g_level_tri_table = g_model_coll_tris[kind],
 * count g_model_tri_counts[kind]). 0 when the records run out. */
static s32 nmw_next_record(NmwState *w) {
    u8 *r = (u8 *) w->cur;
    s32 no = w->recNo;
    u32 base;

    for (;;) {
        r += NMW_REC_SIZE;
        no++;
        if (r == (u8 *) w->curFirst) {
            return 0;
        }
        if (r == w->rec || *(u32 *) r == 0 || !(*(u32 *) (r + 0xF8) & 0x4000)) {
            continue;
        }
        base = *(u32 *) (r + 0x264);
        if (base != 0) {
            break;
        }
    }
    w->cur = (s32) r;
    w->recNo = no;
    w->vbase = base;
    *(s32 *) g_level_tri_table = g_model_coll_tris[r[4]];
    w->count = ((u16 *) g_model_tri_counts)[r[4]];
    w->tri = 0;
    return 1;
}

/* walk_tree (func_150ABB24 .. ABBCC): from w->node, the next BSP leaf whose square (centre, half size) meets the xz box;
 * sets the list cursor and the node to continue from. 0 when the tree is done. Kind 2 starts the list at the
 * object's first triangle (the asm adds the index to the list pointer). */
static s32 nmw_walk_tree(NmwState *w) {
    NmrNode *node = w->node;
    s32 step;

    for (;;) {
        if (w->xmax < node->cx - node->half || node->cx + node->half < w->xmin ||
            w->zmax < node->cz - node->half || node->cz + node->half < w->zmin) {
            step = node->next;
            node = (NmrNode *) ((u8 *) node + step);
            if (step == 0) {
                return 0;
            }
        } else if (node->child != 0) {
            node = (NmrNode *) ((u8 *) node + node->child);
        } else {
            break;
        }
    }
    w->cursor = node->list;
    w->node = node->next == 0 ? NULL : (NmrNode *) ((u8 *) node + node->next);
    if (w->nObjs != 0) {
        w->cursor += w->curFirst;
        w->prev = w->curFirst - 1;
    }
    return 1;
}

/* next_triangle (func_150ABBD0 .. ABE60): the next triangle (w->tri) whose bounds meet the box (xz overlap, y within
 * 200 of rint(pos y)) and whose flags hold the mask; level triangles are tested once (visited list, 100 entries).
 * Kind 3 runs over the records' own models instead of the tree. Kind 2: list entries past the current object's
 * triangles move to the next listed object (whose flags +0x40 apply to that first triangle; the others use the
 * level's g_coll_tri_flags). 0 when there is none left. */
static s32 nmw_next_triangle(NmwState *w) {
    s16 *xz;
    s16 *yr;
    u8 *obj;
    u32 flags;
    s32 t, b, i, first, n;

    for (;;) {
        if (w->nObjs == 0 && w->cur != 0) {
            if (++w->tri == w->count && !nmw_next_record(w)) {
                return 0;
            }
            t = w->tri;
            xz = (s16 *) *(u32 *) ((u8 *) w->cur + 0x268) + t * 4;
            yr = (s16 *) *(u32 *) ((u8 *) w->cur + 0x26C);
        } else {
            if (w->cursor == NULL && !nmw_walk_tree(w)) {
                return 0;
            }
            b = *w->cursor++;
            if (b == 0) { /* end of the leaf (func_150AC770) */
                w->cursor = NULL;
                if (w->node == NULL) {
                    return 0;
                }
                continue;
            }
            t = b & 0x7F;
            if (t == b) {
                t += w->prev;
            } else {
                t = (t << 8) | *w->cursor++;
            }
            if (w->nObjs != 0) {
                obj = (u8 *) g_world_objs + w->cur * NMR_OBJ_SIZE;
                first = w->curFirst;
                n = NMR_OBJ_U16(obj, NMR_OBJ_NTRIS);
                if (t >= n + first) {
                    if (++w->listPos == w->nObjs) {
                        return 0;
                    }
                    w->cur = ((u16 *) g_world_obj_box_ids)[w->listPos];
                    obj = (u8 *) g_world_objs + w->cur * NMR_OBJ_SIZE;
                    t = w->curFirst = NMR_OBJ_U16(obj, NMR_OBJ_TRI0);
                    w->vbase = g_world_obj_blocks[w->cur];
                    w->cursor += t - first - n;
                    flags = *(u32 *) (obj + NMR_OBJ_FLAGS);
                    goto test_flags;
                }
            }
            flags = g_coll_tri_flags != 0 ? ((u32 *) g_coll_tri_flags)[t] : 0;
        test_flags:
            w->prev = t;
            if ((flags & w->mask) != w->mask) {
                continue;
            }
#ifdef PORT
            w->portFlags = flags;
#endif
            w->noSlope = flags & 0x1000000;
            xz = *(s16 **) g_coll_tri_xz_bounds + t * 4;
            yr = *(s16 **) g_coll_tri_y_bounds;
        }
        w->tri = t;
        if (!(xz[0] < w->xmax) || !(w->xmin < xz[2]) || !(xz[1] < w->zmax) || !(w->zmin < xz[3])) {
            continue;
        }
        if (!(yr[t * 2] < w->y + 200) || !(w->y - 200 < yr[t * 2 + 1])) {
            continue;
        }
        if (w->cur == 0 && w->nObjs == 0) {
            for (i = 0; i < w->nVisited; i++) {
                if (w->visited[i] == t) {
                    break;
                }
            }
            if (i < w->nVisited) {
                continue;
            }
            if (w->nVisited != 100) {
                w->visited[w->nVisited++] = t;
            }
        }
        return 1;
    }
}

/* projects_inside (func_150AC200): p projected onto the plane n (n . q = n[3]) inside the triangle w->tv? The three
 * edge cross products (e = a - b, q - b for the edges v1-v0, v2-v1, v0-v2) are compared on the axis where the first
 * one is largest: inside when their signs agree. *side = the second edge's component on that axis (the asm leaves
 * it in f4, and its caller reads it). */
static s32 nmw_projects_inside(NmwState *w, f32 *n, f32 *p, f32 *side) {
    f32 cr[3][3];
    f32 q[3], e[3], u[3];
    f32 s;
    TriPt *a;
    TriPt *b;
    s32 k, bits;

    s = (n[3] - n[0] * p[0] - n[1] * p[1] - n[2] * p[2]) / (n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
    q[0] = s * n[0] + p[0];
    q[1] = s * n[1] + p[1];
    q[2] = s * n[2] + p[2];
    for (k = 0; k < 3; k++) {
        a = &w->tv[(k + 1) % 3];
        b = &w->tv[k];
        e[0] = a->x - b->x;
        e[1] = a->y - b->y;
        e[2] = a->z - b->z;
        u[0] = q[0] - b->x;
        u[1] = q[1] - b->y;
        u[2] = q[2] - b->z;
        cr[k][0] = e[1] * u[2] - e[2] * u[1];
        cr[k][1] = e[2] * u[0] - e[0] * u[2];
        cr[k][2] = e[0] * u[1] - e[1] * u[0];
    }
    if (NM_FABS(cr[0][0]) <= NM_FABS(cr[0][1])) {
        k = NM_FABS(cr[0][2]) > NM_FABS(cr[0][1]) ? 2 : 1;
    } else {
        k = NM_FABS(cr[0][2]) > NM_FABS(cr[0][0]) ? 2 : 0;
    }
    bits = 0;
    if (cr[0][k] < 0.0f) bits |= 1;
    if (cr[1][k] < 0.0f) bits |= 2;
    if (cr[2][k] < 0.0f) bits |= 4;
    *side = cr[1][k];
    return bits == 0 || bits == 7;
}

/* edge_push (func_150AC3CC .. AC5D4): the point of the triangle's edges nearest to p (box frame); when it is nearer
 * than the radius, move the position away from it by the difference (turned back to world axes). 1 if pushed. */
static s32 nmw_edge_push(NmwState *w, f32 *p) {
    f32 best = 65536.0f;
    f32 bp[3];
    f32 d[3], c[3], u[3];
    f32 t, dist, k;
    TriPt *a;
    TriPt *b;
    s32 i;

    for (i = 0; i < 3; i++) {
        a = &w->tv[(i + 1) % 3];
        b = &w->tv[i];
        d[0] = b->x - a->x;
        d[1] = b->y - a->y;
        d[2] = b->z - a->z;
        t = (d[0] * p[0] + d[1] * p[1] + d[2] * p[2] - d[0] * a->x - d[1] * a->y - d[2] * a->z) /
            (d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
        if (t < 0.0f) {
            t = 0.0f;
        } else if (t > 1.0f) {
            t = 1.0f;
        }
        c[0] = a->x + t * d[0];
        c[1] = a->y + t * d[1];
        c[2] = a->z + t * d[2];
        dist = sqrtf((c[0] - p[0]) * (c[0] - p[0]) + (c[1] - p[1]) * (c[1] - p[1]) + (c[2] - p[2]) * (c[2] - p[2]));
        if (!(dist >= best)) {
            best = dist;
            bp[0] = c[0];
            bp[1] = c[1];
            bp[2] = c[2];
        }
    }
    if (best >= w->radiusF) {
        return 0;
    }
    u[0] = p[0] - bp[0];
    u[1] = p[1] - bp[1];
    u[2] = p[2] - bp[2];
    k = (w->radiusF - best) / sqrtf(u[0] * u[0] + u[1] * u[1] + u[2] * u[2]);
    u[0] = u[0] * k;
    u[1] = u[1] * k;
    u[2] = u[2] * k;
    w->pos[0] = w->pos[0] + (u[0] * w->co - u[2] * w->si);
    w->pos[1] = w->pos[1] + u[1];
    w->pos[2] = w->pos[2] + (u[2] * w->co + u[0] * w->si);
    return 1;
}

/* wall_triangle (func_150ABE68 .. AC694, walls): test the current triangle against the box at the middle of the
 * move; on contact mark it (kind 2 objects / kind 3 records), skip it when the move's first vertex test says it
 * faces away or (without the noSlope flag / g_wall_coll_no_floor_skip) it is floor-like (normal y / |n| >= 0.5), clamp the
 * position to 60 units from the target (unless g_wall_coll_no_clamp), then push the position out of the face (when the
 * target or the position projects inside the triangle, or g_wall_coll_soft_edges and the second edge's sign component <= 0.8)
 * or away from the nearest edge. 1 if the position moved. */
static s32 nmw_wall_triangle(NmwState *w) {
    u32 *tri = (u32 *) (*(u32 *) g_level_tri_table + w->tri * 12);
    u8 *obj;
    f32 n[4];
    f32 p[3];
    f32 len2, len, a, b, c, side, dist, k, h, ox, oy, oz, sx, sz;
    s32 in;

    w->mid[0] = (w->tgt[0] + w->pos[0]) * 0.5f;
    w->mid[1] = (w->tgt[1] + w->pos[1]) * 0.5f;
    w->mid[2] = (w->tgt[2] + w->pos[2]) * 0.5f;
    nmw_tri_to_local(tri, w->vbase, w->mid[0], w->mid[1] + w->yoff, w->mid[2], w->si, w->co, &w->tv[0].x);
    if (nmw_tri_misses_box(w->tv, w->half[0], w->half[1], w->half[2])) {
        return 0;
    }
    if (w->nObjs != 0 && w->mark != 0) {
        obj = (u8 *) g_world_objs + w->cur * NMR_OBJ_SIZE;
        obj[0x4F] |= 0x80;
        (*(u32 **) g_world_obj_rider_masks)[w->cur] |= 1 << ((s32) (w->rec - (u8 *) g_objects) / NMW_REC_SIZE & 31);
    } else if (w->cur != 0) {
        w->rec[0x275] = w->recNo;
    }
    n[0] = g_tri_plane_nx;
    n[1] = g_tri_plane_ny;
    n[2] = g_tri_plane_nz;
    n[3] = g_tri_plane_d;
    len2 = n[0] * n[0] + n[1] * n[1] + n[2] * n[2];
    if (len2 == 0.0f) {
        len2 = 1.0f;
    }
    len = sqrtf(len2);
    a = w->mid[0] - w->tgt[0];
    b = w->mid[1] - w->tgt[1];
    c = w->mid[2] - w->tgt[2];
    if (n[0] * (a * w->co + w->tv[0].x + c * w->si) + n[1] * (w->tv[0].y + b) +
            n[2] * (w->tv[0].z - a * w->si + c * w->co) >= 0.0f) {
        return 0;
    }
    if (w->noSlope == 0 && *g_wall_coll_no_floor_skip == 0 && n[1] / len >= 0.5f) {
        return 0;
    }
    ox = w->pos[0];
    oy = w->pos[1];
    if (*g_wall_coll_no_clamp == 0) {
        oz = w->pos[2];
        a = ox - w->tgt[0];
        b = oy - w->tgt[1];
        c = oz - w->tgt[2];
        *g_wall_coll_no_clamp = 0;
        dist = sqrtf(a * a + b * b + c * c);
        if (dist != 0.0f && !(dist <= 60.0f)) {
            k = 60.0f / dist;
            w->pos[0] = a * k + w->tgt[0];
            w->mid[0] = (w->pos[0] + w->tgt[0]) * 0.5f;
            w->pos[1] = b * k + w->tgt[1];
            w->mid[1] = (w->pos[1] + w->tgt[1]) * 0.5f;
            w->pos[2] = c * k + w->tgt[2];
            w->mid[2] = (w->pos[2] + w->tgt[2]) * 0.5f;
        }
    } else {
        oz = w->mid[2]; /* the asm's f8 still holds the box centre z here, not the position's */
    }
    /* the target relative to the (unclamped) position, in the box frame */
    a = w->tgt[0] - ox;
    p[1] = w->tgt[1] - oy;
    c = w->tgt[2] - oz;
    p[0] = a * w->co + c * w->si;
    p[2] = c * w->co - a * w->si;
    in = nmw_projects_inside(w, n, p, &side);
    /* the position relative to the box centre, in the box frame */
    sx = w->pos[0] - w->mid[0];
    p[1] = w->pos[1] - w->mid[1];
    sz = w->pos[2] - w->mid[2];
    p[0] = sx * w->co + sz * w->si;
    p[2] = sz * w->co - sx * w->si;
    if (!(*g_wall_coll_soft_edges != 0 && side <= 0.8f) && in != 1 && nmw_projects_inside(w, n, p, &side) != 1) {
        return nmw_edge_push(w, p);
    }
    /* face push (func_150AC5D8): out along the normal until the plane is radius away */
    h = n[3] + w->radiusF * len - n[0] * p[0] - n[1] * p[1] - n[2] * p[2];
    if (h <= 0.0f) {
        return 0;
    }
    if (!(n[1] / len >= -0.2f) && !(w->dy.f <= 0.0f)) {
        w->keepFall = 0;
    }
    h = h / len2;
    sx = n[0] * w->co - n[2] * w->si;
    sz = n[2] * w->co + n[0] * w->si;
    w->pos[0] = h * sx + w->pos[0];
    w->pos[1] = h * n[1] + w->pos[1];
    w->pos[2] = h * sz + w->pos[2];
    return 1;
}

/* ledge_triangle (func_150AC960 .. ACE8C, ledges): a triangle in the box around the record (turned by its heading)
 * that is flat enough (normal y / |n| > D_8009FAC4) and whose plane height (+ yoff) is within the 64..65 window
 * around the half move: its xz edges (x along the heading) are lines z = slope x + icept; the one passing nearest to
 * the record (foot of the perpendicular, clamped to the edge) is the ledge candidate. When it beats the best so far,
 * has an end on each side of the record (x > 0 and x < 0) and |slope| < 4: the grab point is where the line meets
 * the circle of radius^2 g_nmw_ledge_grab_radius_sq (the root on the record's side), stored with the ledge height and the edge's
 * angle in g_wall_ledge_h_neg / g_wall_ledge_angle_neg (icept negative) or g_wall_ledge_h_pos / g_wall_ledge_angle_pos, and g_obj_attached_world_obj[record] = 1. */
#ifdef PORT
s32 ledge_grab_everywhere_for(u8 *rec); /* game_eu_71E70.c */
/* P352 option "Ledge grab everywhere": 1 when the ledge stored on that side (g_wall_ledge_h_neg / _pos) came from a
 * triangle the level did not mark as a ledge (flags 0x0E000000); obj_state_walk then asks ledge_grab_unmarked_ok. */
s32 port_ledge_unmarked_neg, port_ledge_unmarked_pos;
#endif
static void nmw_ledge_triangle(NmwState *w) {
    u32 *tri = (u32 *) (*(u32 *) g_level_tri_table + w->tri * 12);
    f32 *v = &w->tv[0].x;
    f32 nx, ny, nz, d, len, top, hm, x0, z0, x1, z1, dx, m, ic, fx, fz, footx, footz, d2, best, tmp;
    f32 bestFoot[2], bestSlope, bestX0, bestX1;
    NmwReg bestIcept;
    f32 a, bq, cq, disc, sq, t, lx, wx, wz, height, ang;
    s32 first, i, sides, j0, j1;

    w->mid[1] = (w->tgt[1] + w->pos[1]) * 0.5f + w->yoff;
    nmw_tri_to_local(tri, w->vbase, w->pos[0], w->mid[1], w->pos[2], w->si, w->co, v);
    if (nmw_tri_misses_box(w->tv, w->half[0], w->half[1], w->half[2])) {
        return;
    }
#ifdef PORT
    /* P352 "Ledge grab everywhere": a triangle the level did not mark as a ledge is skipped when the record is under
     * it (its xz footprint holds the record's x / z = the box origin): that is a floor above the record, not an edge
     * in front of it. Edges of marked ledges keep the N64 rule. */
    if (w->portAnyLedge && (w->portFlags & 0x0E000000) != 0x0E000000) {
        f32 c0 = v[0] * v[5] - v[2] * v[3];
        f32 c1 = v[3] * v[8] - v[5] * v[6];
        f32 c2 = v[6] * v[2] - v[8] * v[0];
        if ((c0 >= 0.0f && c1 >= 0.0f && c2 >= 0.0f) || (c0 <= 0.0f && c1 <= 0.0f && c2 <= 0.0f)) {
            return;
        }
    }
#endif
    nx = g_tri_plane_nx;
    ny = g_tri_plane_ny;
    nz = g_tri_plane_nz;
    d = g_tri_plane_d;
    len = sqrtf(nx * nx + ny * ny + nz * nz);
    if (len == 0.0f || ny / len <= NMW_F32(g_nmw_k_deg_to_rad + 4)) {
        return;
    }
    top = d / ny + w->yoff;
    hm = (w->tgt[1] - w->pos[1]) * 0.5f;
    if (top + hm <= w->ledgeLo || top - hm >= w->ledgeHi) {
        return;
    }
    first = 1;
    best = len;
    for (i = 0; i < 3; i++) {
        j0 = 3 * i;
        j1 = 3 * ((i + 1) % 3);
        x0 = v[j0];
        z0 = v[j0 + 2];
        x1 = v[j1];
        z1 = v[j1 + 2];
        dx = x1 - x0;
        if (!(NM_FABS(dx) >= 4.0f) && !(NM_FABS(z1 - z0) >= 4.0f) && (first == 0 || i < 2)) {
            continue; /* a short edge, unless it is the last chance */
        }
        if (dx == 0.0f) {
            m = NMW_F32(g_nmw_ledge_vertical_slope);
            ic = x1;
            fx = x1;
            fz = 0.0f;
        } else {
            m = (z1 - z0) / dx;
            if (m == 0.0f) {
                ic = z1;
                fx = 0.0f;
                fz = z1;
            } else {
                ic = z0 - m * x0;
                tmp = m * m + 1.0f;
                fx = -ic * m / tmp;
                fz = ic / tmp;
            }
        }
        footx = fx;
        footz = fz;
        if (!(x0 <= x1)) {
            tmp = x0, x0 = x1, x1 = tmp;
            tmp = z0, z0 = z1, z1 = tmp;
        }
        if (!(x0 <= fx)) {
            fx = x0;
            fz = z0;
        } else if (!(x1 >= fx)) {
            fx = x1;
            fz = z1;
        } else {
            if (!(z0 <= z1)) {
                tmp = x0, x0 = x1, x1 = tmp;
                tmp = z0, z0 = z1, z1 = tmp;
            }
            if (!(z0 <= fz)) {
                fx = x0;
                fz = z0;
            } else if (!(z1 >= fz)) {
                fx = x1;
                fz = z1;
            }
        }
        d2 = fx * fx + fz * fz;
        if (first || !(d2 >= best)) {
            bestFoot[0] = footx;
            bestFoot[1] = footz;
            best = d2;
            bestSlope = m;
            bestIcept.f = ic;
            first = 0;
            bestX0 = x0;
            bestX1 = x1;
        }
    }
    if (best >= w->ledgeBest) {
        return;
    }
    w->ledgeBest = best;
    sides = 0;
    if (bestX0 > 0.0f || bestX1 > 0.0f) {
        sides |= 1;
    }
    if (bestX0 < -0.0f || bestX1 < -0.0f) {
        sides |= 2;
    }
    if (sides != 3 || NM_FABS(bestSlope) >= 4.0f || ny == 0.0f) {
        return;
    }
    height = d / ny + (w->mid[1] - 54.0f);
    m = bestSlope;
    a = 1.0f + m * m;
    bq = 2.0f * (m * bestFoot[0] - bestFoot[1]);
    cq = bestFoot[0] * bestFoot[0] - NMW_F32(g_nmw_ledge_grab_radius_sq) + bestFoot[1] * bestFoot[1];
    disc = bq * bq - 4.0f * a * cq;
    if (!(disc > 0.0f)) {
        disc = 0.0f;
    }
    sq = sqrtf(disc);
    if (bestIcept.f > 0.0f) {
        sq = -sq;
    }
    t = (sq - bq) / (2.0f * a);
    lx = -m * t;
    wx = lx * w->co - t * w->si;
    wz = lx * w->si + t * w->co;
    g_wall_ledge_grab_x = wx + *(f32 *) (w->rec + 0x14);
    NMW_F32(g_wall_ledge_grab_z) = wz + *(f32 *) (w->rec + 0x1C);
    ang = math_atan2f(1.0f, m) * NMW_F32(g_nmw_k_rad_to_deg) - 90.0f;
    if (bestIcept.i < 0) {
        g_wall_ledge_h_neg = height;
        NMW_F32(g_wall_ledge_angle_neg) = ang;
#ifdef PORT
        port_ledge_unmarked_neg = (w->portFlags & 0x0E000000) != 0x0E000000;
#endif
    } else {
        g_wall_ledge_h_pos = height;
        NMW_F32(g_wall_ledge_angle_pos) = ang;
#ifdef PORT
        port_ledge_unmarked_pos = (w->portFlags & 0x0E000000) != 0x0E000000;
#endif
    }
    ((s16 *) g_obj_attached_world_obj)[(s32) (w->rec - (u8 *) g_objects) / NMW_REC_SIZE] = 1;
}

/* wall_engine (func_150AB708): see the block comment above. Area kind g_collision_cur_area: 2 = the objects func_150A69A8
 * lists near the target (sorted by world_objects_transform_mesh; nothing listed or no vertex base -> 0), 3 = the other records'
 * models, else the level. Returns 1 if a wall moved the record (walls; ledges return 0). */
static s32 nmw_engine(u8 *rec, f32 x, f32 y, u32 zbits, s32 mark, s32 ledge) {
    NmwState w;
    union {
        s32 w;
        s16 h[2];
    } yo;
    s16 mg, rd;
    NmwReg z;
    f32 dx, dz, ang;

    z.u = zbits;
    w.rec = rec;
    w.mask = ledge ? 0x0E000000 : 0;
#ifdef PORT
    /* P352 option "Ledge grab everywhere": the N64 only lets a player catch the edges of triangles the level marks
     * as ledges (flags 0x0E000000, on a few levels). With the option a single-player player record takes every
     * level triangle (areas 0 / 1) in ledge mode; world objects (area 2: doors, lifts, water surfaces) keep the rule. */
    w.portFlags = 0x0E000000;
    w.portAnyLedge = 0;
    if (ledge && g_collision_cur_area != 2 && ledge_grab_everywhere_for(rec)) {
        w.mask = 0;
        w.portAnyLedge = 1;
    }
#endif
    w.vbase = 0;
    w.moved = 0;
    w.mark = mark;
    w.cur = 0;
    w.tgt[0] = x;
    w.tgt[1] = y;
    w.tgt[2] = z.f;
    obj_collision_cylinder((struct127 *) rec, &yo.h[0], &mg, &rd);
    w.nObjs = 0;
    if (g_collision_cur_area == 2) {
        w.nObjs = func_150A69A8(nmD5E90_rint(x), nmD5E90_rint(z.f), &yo.w, nmD5E90_rint(y) + yo.h[0]);
        if (w.nObjs == 0) {
            return 0;
        }
        world_objects_transform_mesh(w.nObjs, (s32 *) g_world_obj_box_ids, 0);
        w.cur = *(u16 *) g_world_obj_box_ids;
        w.curFirst = NMR_OBJ_U16((u8 *) g_world_objs + w.cur * NMR_OBJ_SIZE, NMR_OBJ_TRI0);
        w.vbase = g_world_obj_blocks[w.cur];
        if (w.vbase == 0) {
            return 0;
        }
        w.listPos = 0;
    } else if (g_collision_cur_area == 3) {
        w.curFirst = (s32) ((u8 *) g_objects + 25 * NMW_REC_SIZE);
        w.cur = (s32) ((u8 *) g_objects - NMW_REC_SIZE);
        w.tri = -1;
        w.count = 0;
        w.recNo = 0;
    }
    w.noSlope = 0;
    if (ledge) {
        w.radius = rd + 10;
        w.margin = mg + 10;
        w.ledgeLo = 64.0f;
        w.ledgeHi = 65.0f;
        w.ledgeBest = 65536.0f; /* collision_ledge_probe sets it before joining the engine */
        w.yoff = NMW_F32(g_wall_coll_lift);
        { /* P317: volatile zero: IDO folds `0.0f + x` (the asm adds $f3, taken as 0.0; P310) */
            volatile f32 p317z = 0.0f;
            quadtree_set_test_box((f32) w.margin * 2.0f, NMW_F32(g_wall_coll_height) + p317z, (f32) w.radius * 2.0f);
        }
    } else {
        w.radiusF = rd;
        w.radius = rd;
        w.margin = mg;
        w.yoff = NMW_F32(g_wall_coll_lift);
        dx = x - *(f32 *) (rec + 0x14);
        dz = z.f - *(f32 *) (rec + 0x1C);
        quadtree_set_test_box((f32) w.margin * 2.0f, NMW_F32(g_wall_coll_height), (f32) w.radius * 2.0f + sqrtf(dx * dx + dz * dz));
    }
    w.nVisited = 0;
    w.si = 0.0f;
    w.co = -1.0f;
    w.pos[0] = *(f32 *) (rec + 0x14);
    w.pos[1] = *(f32 *) (rec + 0x18);
    w.pos[2] = *(f32 *) (rec + 0x1C);
    nmw_set_box(&w, w.pos[0], w.pos[1], w.pos[2]);
    w.keepFall = w.dy.u = *(u32 *) (rec + 0x20);
    w.half[0] = g_quadtree_box_half_x;
    w.half[1] = g_quadtree_box_half_y;
    w.half[2] = g_quadtree_box_half_z;
    w.node = *(NmrNode **) g_zone_tree;
    w.cursor = NULL;
    if (ledge) {
        ang = *(f32 *) (rec + 0x40) * NMW_F32(g_nmw_k_deg_to_rad);
        w.si = sinf(ang);
        w.co = -cosf(ang);
    }
    while (nmw_next_triangle(&w)) {
        if (ledge) {
            nmw_ledge_triangle(&w);
        } else if (nmw_wall_triangle(&w)) {
            w.moved = 1;
            nmw_set_box(&w, w.pos[0], w.pos[1], w.pos[2]);
        }
    }
    if (!ledge) {
        *(f32 *) (rec + 0x14) = w.pos[0];
        *(f32 *) (rec + 0x18) = w.pos[1];
        *(f32 *) (rec + 0x1C) = w.pos[2];
        if (w.keepFall == 0) {
            *(u32 *) (rec + 0x20) = 0;
        }
    }
    return w.moved;
}

/* was func_150AB6D0 */
s32 collision_walls_slide(f32 x, f32 y, s32 zbits, u8 *rec, s32 mark) {
    return nmw_engine(rec, x, y, zbits, mark, 0);
}

/* ledges: returns at once (v0 = 0 here, the caller's v0 in the asm) if rec+0x20 > 0 (rising), else clears
 * g_obj_attached_world_obj[record] and runs the engine in ledge mode */
/* was func_150AC8C4 */
s32 collision_ledge_probe(f32 x, f32 y, s32 zbits, u8 *rec, s32 mark) {
    if (*(s32 *) (rec + 0x20) > 0) {
        return 0;
    }
    ((s16 *) g_obj_attached_world_obj)[(s32) (rec - (u8 *) g_objects) / NMW_REC_SIZE] = 0;
    return nmw_engine(rec, x, y, zbits, mark, 1);
}

/* P285 / P294: test entry for tools/port/difftest/nmasm_walls.py --unit (NM build only): calls the C of the private
 * wall helper at `entry` (its asm address) with the asm's registers: io[0..31] = f0..f31, io[32..57] = v0 v1 a0 a1
 * a2 a3 t0..t9 s0..s7 gp fp, io[58..] = the frame words sp+0..0x264 (in only); register outputs are written back
 * to io. Returns v0. */
#define NMW_IO_F(k) (((NmwReg *) io)[k].f)
#define NMW_IO_FP(k) (&((NmwReg *) io)[k].f)
#define NMW_IO_FRAME(off) (io[58 + (off) / 4])
s32 nmw_unit(u32 entry, u32 *io) {
    NmwState w;
    f32 side;
    s32 k;

    switch (entry) {
        case 0x150AA950:
            return nmw_box_outcode(NMW_IO_F(3), NMW_IO_F(4), NMW_IO_F(5), NMW_IO_F(0), NMW_IO_F(1), NMW_IO_F(2));
        case 0x150AA9B0:
            return nmw_box_edge_outcode(NMW_IO_F(3), NMW_IO_F(4), NMW_IO_F(5), NMW_IO_F(0), NMW_IO_F(1), NMW_IO_F(2));
        case 0x150AAA88:
            return nmw_box_corner_outcode(NMW_IO_F(3), NMW_IO_F(4), NMW_IO_F(5), NMW_IO_F(0), NMW_IO_F(1), NMW_IO_F(2));
        case 0x150AAB58: /* diff in v1 */
            return nmw_segment_misses_box(NMW_IO_FP(6), NMW_IO_FP(9), io[33], NMW_IO_F(0), NMW_IO_F(1), NMW_IO_F(2));
        case 0x150AACF4:
            return nmD5E90_pointInTri((TriPt *) NMW_IO_FP(3), (TriPt *) NMW_IO_FP(23));
        case 0x150AAE80: /* plane -> f19..f22 */
            nmD5E90_plane((TriPt *) NMW_IO_FP(23), NMW_IO_FP(19));
            return io[32];
        case 0x150AAF00:
            return nmw_tri_misses_box((TriPt *) NMW_IO_FP(23), NMW_IO_F(0), NMW_IO_F(1), NMW_IO_F(2));
        case 0x150AC824: /* offsets at t0, vertex base sp+0x150 -> f23..f31 */
            nmw_tri_to_local((u32 *) io[38], NMW_IO_FRAME(0x150), NMW_IO_F(20), NMW_IO_F(21), NMW_IO_F(22),
                             NMW_IO_F(18), NMW_IO_F(19), NMW_IO_FP(23));
            return io[32];
        case 0x150AC200: /* plane f19..f22, point f26..f28, triangle sp+0x20C.. -> t0, f4 */
            for (k = 0; k < 9; k++) {
                ((NmwReg *) &w.tv[0].x)[k].u = NMW_IO_FRAME(0x20C + 4 * k);
            }
            io[38] = nmw_projects_inside(&w, NMW_IO_FP(19), NMW_IO_FP(26), &side);
            NMW_IO_F(4) = side;
            return io[32];
    }
    return 0xBAD00000 | (entry & 0xFFFFF);
}

/* ray_hits_triangle (func_150AD844, the ray cast's private helper): the ray org + t * dir (t >= 0) against triangle
 * `tri` of the current collision set (g_level_tri_table: 3 vertex offsets from vbase per triangle, vertices s16 x, y, z;
 * g_coll_tri_xz_bounds: s16 min x, min z, max x, max z per triangle; g_coll_tri_y_bounds: s16 min y, max y). Misses (0) when the ray
 * is parallel to the plane, the plane is behind the origin, the hit point is outside the triangle's bounds widened
 * by 1, it is not nearer than best[0], or it lies outside the triangle (edge cross products, see below). On a hit (1): best[0] = distance, best[1..3] = hit point. */
static s32 nmr_ray_hits_triangle(u32 tri, u32 vbase, f32 *org, f32 *dir, f32 *best) {
    u32 *offs = (u32 *) (*(u32 *) g_level_tri_table + tri * 12);
    s16 *box = (s16 *) (*(u32 *) g_coll_tri_xz_bounds + tri * 8);
    s16 *ybox = (s16 *) (*(u32 *) g_coll_tri_y_bounds + tri * 4);
    f32 v[3][3];
    f32 e1x, e1y, e1z, e2x, e2y, e2z;
    f32 nx, ny, nz, d, denom, t;
    f32 hx, hy, hz, dist;
    f32 c1, c2, c3, a1, a2, a3;
    s16 *p;
    s32 i, pos;

    for (i = 0; i < 3; i++) {
        p = (s16 *) (offs[i] + vbase);
        v[i][0] = p[0];
        v[i][1] = p[1];
        v[i][2] = p[2];
    }
    /* plane n . x + d = 0 */
    e1x = v[1][0] - v[0][0];
    e1y = v[1][1] - v[0][1];
    e1z = v[1][2] - v[0][2];
    e2x = v[2][0] - v[0][0];
    e2y = v[2][1] - v[0][1];
    e2z = v[2][2] - v[0][2];
    nx = e1y * e2z - e1z * e2y;
    ny = e1z * e2x - e1x * e2z;
    nz = e1x * e2y - e1y * e2x;
    d = -(nx * v[0][0]) - ny * v[0][1] - nz * v[0][2];
    denom = nx * dir[0] + ny * dir[1] + nz * dir[2];
    if (denom == 0.0f) {
        return 0;
    }
    t = (-(nx * org[0]) - ny * org[1] - nz * org[2] - d) / denom;
    if (t < 0.0f) {
        return 0;
    }
    hx = org[0] + t * dir[0];
    hy = org[1] + t * dir[1];
    hz = org[2] + t * dir[2];
    if ((f32) (box[0] - 1) > hx || (f32) (box[2] + 1) < hx) {
        return 0;
    }
    if ((f32) (box[1] - 1) > hz || (f32) (box[3] + 1) < hz) {
        return 0;
    }
    if ((f32) (ybox[0] - 1) > hy || (f32) (ybox[1] + 1) < hy) {
        return 0;
    }
    dist = sqrtf((hx - org[0]) * (hx - org[0]) + (hy - org[1]) * (hy - org[1]) + (hz - org[2]) * (hz - org[2]));
    if (dist >= best[0]) {
        return 0;
    }
    /* edge v0-v1 against the hit point: the cross product component that is largest in magnitude (of c1 / c3, or
     * of c2 / c3) is kept, the two others are redone with the edges v1-v2 and v2-v0 */
    e1x = v[1][0] - v[0][0];
    e1y = v[1][1] - v[0][1];
    e1z = v[1][2] - v[0][2];
    c1 = e1y * (hz - v[0][2]) - e1z * (hy - v[0][1]);
    c2 = e1z * (hx - v[0][0]) - e1x * (hz - v[0][2]);
    c3 = e1x * (hy - v[0][1]) - e1y * (hx - v[0][0]);
    a1 = NM_FABS(c1);
    a2 = NM_FABS(c2);
    a3 = NM_FABS(c3);
    if (a1 > a2 ? !(a3 > a1) : !(a3 > a2)) {
        if (a1 > a2) { /* keep c1: the y-z projection */
            c2 = (v[2][1] - v[1][1]) * (hz - v[1][2]) - (v[2][2] - v[1][2]) * (hy - v[1][1]);
            c3 = (v[0][1] - v[2][1]) * (hz - v[2][2]) - (v[0][2] - v[2][2]) * (hy - v[2][1]);
        } else { /* keep c2: the z-x projection */
            c1 = (v[2][2] - v[1][2]) * (hx - v[1][0]) - (v[2][0] - v[1][0]) * (hz - v[1][2]);
            c3 = (v[0][2] - v[2][2]) * (hx - v[2][0]) - (v[0][0] - v[2][0]) * (hz - v[2][2]);
        }
    } else { /* keep c3: the x-y projection */
        c1 = (v[2][0] - v[1][0]) * (hy - v[1][1]) - (v[2][1] - v[1][1]) * (hx - v[1][0]);
        c2 = (v[0][0] - v[2][0]) * (hy - v[2][1]) - (v[0][1] - v[2][1]) * (hx - v[2][0]);
    }
    pos = (c1 >= 0.0f) + (c2 >= 0.0f) + (c3 >= 0.0f);
    if (pos != 0 && pos != 3) {
        return 0;
    }
    best[0] = dist;
    best[1] = hx;
    best[2] = hy;
    best[3] = hz;
    return 1;
}


/* the ray cast's state: origin, direction scaled to length 65536, best hit (distance, point), the hit */
typedef struct {
    f32 org[3];
    f32 dir[3];
    f32 best[4];
    s32 kind;    /* 0 none, 1 level triangle, 2 object triangle */
    u32 hitRec;  /* g_level_tri_table record (3 vertex offsets) of the hit triangle */
    u32 hitTri;  /* its index */
    u32 lastRec; /* the asm's gp: the record of the last tested triangle (read by the flags output, see below) */
} NmrRay;

/* test triangle `tri` (vertices at vbase + its offsets) against the ray; on a hit the ray's best and hit change */
static s32 nmr_test_triangle(NmrRay *ray, u32 tri, u32 vbase) {
    ray->lastRec = *(u32 *) g_level_tri_table + tri * 12;
    if (!nmr_ray_hits_triangle(tri, vbase, ray->org, ray->dir, ray->best)) {
        return 0;
    }
    ray->hitRec = ray->lastRec;
    ray->kind = 1;
    ray->hitTri = tri;
    return 1;
}

/* does the xz line (dep = slope * ind + icept) separate the corners of a triangle's xz bounds? ind / dep point at
 * the min of the independent / dependent coordinate in its g_coll_tri_xz_bounds entry (s16 min x, min z, max x, max z) */
static s32 nmr_line_splits_box(s16 *ind, s16 *dep, f32 slope, f32 icept) {
    f32 k1 = slope * (f32) ind[0];
    f32 k2 = slope * (f32) ind[2];
    s32 above = 0;

    if ((icept - (f32) dep[0]) + k1 >= 0.0f) {
        above++;
    }
    if ((k1 + icept) - (f32) dep[2] >= 0.0f) {
        above++;
    }
    if (k2 + (icept - (f32) dep[2]) >= 0.0f) {
        above++;
    }
    if ((k2 + icept) - (f32) dep[0] >= 0.0f) {
        above++;
    }
    return above != 0 && above != 4;
}

/* the BSP leaf (from the root, skipping `skip`) whose square holds (x, z); NULL if none */
static NmrNode *nmr_find_leaf(f32 x, f32 z, NmrNode *skip) {
    NmrNode *node = *(NmrNode **) g_quadtree_roots;
    f32 cx, cz, h;

    for (;;) {
        cx = node->cx;
        cz = node->cz;
        h = node->half;
        if (node != skip && !(cx - h > x) && !(x > cx + h) && !(cz - h > z) && z <= cz + h) {
            if (node->child == 0) {
                return node;
            }
            node = (NmrNode *) ((u8 *) node + node->child);
        } else {
            if (node->next == 0) {
                return NULL;
            }
            node = (NmrNode *) ((u8 *) node + node->next);
        }
    }
}

/*
 * ray_cast (collision_ray_cast, Rare hand asm): nearest hit of the ray (x0, y0, z0) + t * (dx, dy, dz), t >= 0, with the
 * level's collision triangles and the collidable objects' triangles, within maxDist (0: unlimited, 2^48).
 * Level: walks the BSP leaves the ray crosses in xz (from the leaf holding the origin, each next leaf found from a
 * point 10 units past the exit side of the current square, until a hit, no leaf, or the exit point is maxDist or
 * more away in xz); in each leaf the triangles whose xz bounds the ray's xz line crosses are tested
 * (func_150AD844). Objects: those whose bounding sphere the ray's line meets (in front of the origin) are listed in
 * g_world_obj_box_ids, sorted by world_objects_transform_mesh, and all their triangles tested the same way.
 * Outputs (each optional): *outRec = the hit triangle's g_level_tri_table record, *outX / Y / Z = the point, outVerts = its
 * 3 vertices (s16 x, y, z each), *outDist, *outObj = the object index (-1: level), *outFlags = the triangle's flags
 * (level: g_coll_tri_flags[tri]; object: its table +0x44 [tri - first], or +0x40 for all). Returns 1 on a hit, else 0.
 * collision_select_area(0 / 2) marks the level / object phases (profiler).
 */
/* was func_150ACEA0 */
s32 collision_ray_cast(f32 x0, f32 y0, f32 z0, f32 dx, f32 dy, f32 dz, s32 outRec, s32 outVerts, s32 outX, s32 outY,
                  s32 outZ, s32 outDist, s32 outObj, s32 outFlags, f32 maxDist) {
    NmrRay ray;
    NmrNode *leaf;
    u8 *list;
    u8 *obj;
    u8 *objEnd;
    u16 *idx;
    u16 *idxEnd;
    s16 *ind;
    s16 *dep;
    s16 *v;
    u32 *rec;
    u32 *triFlags;
    f32 len, slope, icept, cx, cz, h, ex, ez, t;
    f32 ox, oy, oz, rr, b, c, disc, sq, dd, tx, ty, tz;
    s32 posX, negZ, xMajor;
    s32 hitObj;
    u32 tri, triEnd, vbase, prev, flags;
    s32 n, i, r;

    collision_select_area(0);
    if (*(u32 *) &dx == 0 && dy == 0.0f && dz == 0.0f) {
        return 0;
    }
    ray.org[0] = x0;
    ray.org[1] = y0;
    ray.org[2] = z0;
    len = sqrtf(dx * dx + dy * dy + dz * dz);
    len = 65536.0f / len;
    ray.dir[0] = dx * len;
    ray.dir[1] = dy * len;
    ray.dir[2] = dz * len;
    ray.kind = 0;
    hitObj = -1;
    posX = ray.dir[0] >= 0.0f;
    negZ = !(ray.dir[2] >= 0.0f);

    /* the ray's xz line: z = slope * x + icept when |dx| > |dz| (xMajor), else x = slope * z + icept */
    xMajor = !(NM_FABS(ray.dir[0]) <= NM_FABS(ray.dir[2]));
    if (xMajor) {
        t = (x0 + ray.dir[0]) - x0;
        if (t == 0.0f) {
            t = 0.0001f;
        }
        slope = ((z0 + ray.dir[2]) - z0) / t;
        icept = z0 - slope * x0;
    } else {
        t = (z0 + ray.dir[2]) - z0;
        if (t == 0.0f) {
            t = 0.0001f;
        }
        slope = ((x0 + ray.dir[0]) - x0) / t;
        icept = x0 - slope * z0;
    }
    ray.best[0] = maxDist;
    if (ray.best[0] == 0.0f) {
        ray.best[0] = 281474976710656.0f; /* 65536^3 */
    }

    /* level */
    prev = 0; /* the asm's t3: the first entry of a leaf is relative to the caller's t3 (0) or the last exit side */
    leaf = nmr_find_leaf(x0, z0, NULL);
    while (leaf != NULL) {
        ind = (s16 *) *(u32 *) g_coll_tri_xz_bounds + (xMajor ? 0 : 1);
        dep = (s16 *) *(u32 *) g_coll_tri_xz_bounds + (xMajor ? 1 : 0);
        list = leaf->list;
        while ((tri = *list++) != 0) {
            if (tri & 0x80) {
                tri = ((tri & 0x7F) << 8) + *list++;
            } else {
                tri += prev;
            }
            prev = tri;
            if (nmr_line_splits_box(ind + tri * 4, dep + tri * 4, slope, icept)) {
                nmr_test_triangle(&ray, tri, 0);
            }
        }
        if (ray.kind != 0) {
            break;
        }
        /* exit point of the ray from this square, pushed 10 units on into the next one */
        cx = leaf->cx;
        cz = leaf->cz;
        h = leaf->half;
        if (ray.dir[0] == 0.0f) {
            ex = x0;
            prev = 0;
            ez = negZ ? (cz - h) - 10.0f : (cz + h) + 10.0f;
        } else if (ray.dir[2] == 0.0f) {
            ez = z0;
            prev = 1;
            ex = posX ? (cx + h) + 10.0f : (cx - h) - 10.0f;
        } else {
            ex = posX ? cx + h : cx - h;
            ez = (ex - x0) / ray.dir[0] * ray.dir[2] + z0;
            if (ez < cz - h || !(ez <= cz + h)) { /* leaves through a z side */
                prev = 0;
                ez = negZ ? cz - h : cz + h;
                ex = (ez - z0) / ray.dir[2] * ray.dir[0] + x0;
            } else {
                prev = 1;
            }
            ex = posX ? ex + 10.0f : ex - 10.0f;
            ez = negZ ? ez - 10.0f : ez + 10.0f;
        }
        if (maxDist != 0.0f && !(sqrtf((x0 - ex) * (x0 - ex) + (z0 - ez) * (z0 - ez)) < maxDist)) {
            break;
        }
        leaf = nmr_find_leaf(ex, ez, leaf);
    }

    /* objects */
    collision_select_area(2);
    obj = (u8 *) g_world_objs;
    objEnd = obj + g_world_obj_count * NMR_OBJ_SIZE;
    if (obj != objEnd) {
        dd = (ray.dir[0] * ray.dir[0] + ray.dir[1] * ray.dir[1] + ray.dir[2] * ray.dir[2]) * 4.0f;
        tx = 2.0f * ray.dir[0];
        ty = 2.0f * ray.dir[1];
        tz = 2.0f * ray.dir[2];
        n = 0;
        i = 0;
        idx = (u16 *) g_world_obj_box_ids;
        do {
            if (obj[NMR_OBJ_OFF] == 0 && (obj[NMR_OBJ_MODE] & 0x60) != 0x20) {
                /* |o + t d - c|^2 = r^2 with the doubled direction: b = 2 d.(o - c), c = |o - c|^2 - r^2 */
                ox = x0 - (f32) NMR_OBJ_S16(obj, NMR_OBJ_CX);
                oy = y0 - (f32) NMR_OBJ_S16(obj, NMR_OBJ_CX + 2);
                oz = z0 - (f32) NMR_OBJ_S16(obj, NMR_OBJ_CX + 4);
                r = NMR_OBJ_U16(obj, NMR_OBJ_RADIUS1);
                if (r < NMR_OBJ_U16(obj, NMR_OBJ_RADIUS2)) {
                    r = NMR_OBJ_U16(obj, NMR_OBJ_RADIUS2);
                }
                rr = (f32) r;
                rr = rr * rr;
                b = tx * ox + ty * oy + tz * oz;
                c = ox * ox + oy * oy + oz * oz - rr;
                disc = b * b - c * dd;
                if (!(disc < 0.0f)) {
                    sq = sqrtf(disc);
                    if (-b + sq >= 0.0f || !(-b - sq < 0.0f)) {
                        *idx++ = i;
                        n++;
                    }
                }
            }
            obj += NMR_OBJ_SIZE;
            i++;
        } while (obj != objEnd);

        if (n != 0) {
            world_objects_transform_mesh(n, (s32 *) g_world_obj_box_ids, 0);
            ind = (s16 *) *(u32 *) g_coll_tri_xz_bounds + (xMajor ? 0 : 1);
            dep = (s16 *) *(u32 *) g_coll_tri_xz_bounds + (xMajor ? 1 : 0);
            idx = (u16 *) g_world_obj_box_ids;
            idxEnd = idx + n;
            do {
                vbase = g_world_obj_blocks[*idx];
                obj = (u8 *) g_world_objs + *idx * NMR_OBJ_SIZE;
                tri = NMR_OBJ_U16(obj, NMR_OBJ_TRI0);
                triEnd = NMR_OBJ_U16(obj, NMR_OBJ_NTRIS) + tri;
                do {
                    if (nmr_line_splits_box(ind + tri * 4, dep + tri * 4, slope, icept) &&
                        nmr_test_triangle(&ray, tri, vbase)) {
                        hitObj = *idx;
                        ray.kind = 2;
                    }
                    tri++;
                } while (tri != triEnd);
                idx++;
            } while (idx != idxEnd);
        }
    }

    if (ray.kind == 0) {
        return 0;
    }
    if (outRec != 0) {
        *(u32 *) outRec = ray.hitRec;
    }
    if (outX != 0) {
        *(f32 *) outX = ray.best[1];
    }
    if (outY != 0) {
        *(f32 *) outY = ray.best[2];
    }
    if (outZ != 0) {
        *(f32 *) outZ = ray.best[3];
    }
    if (outVerts != 0 && ray.hitRec != 0) {
        rec = (u32 *) ray.hitRec;
        for (i = 0; i < 3; i++) {
            if (hitObj == -1) {
                v = (s16 *) rec[i];
            } else {
                ray.lastRec = (u32) g_world_objs + hitObj * NMR_OBJ_SIZE;
                v = (s16 *) (g_world_obj_blocks[hitObj] + rec[i]);
            }
            ((s16 *) outVerts)[3 * i + 0] = v[0];
            ((s16 *) outVerts)[3 * i + 1] = v[1];
            ((s16 *) outVerts)[3 * i + 2] = v[2];
        }
    }
    if (outDist != 0) {
        *(f32 *) outDist = ray.best[0];
    }
    if (outObj != 0) {
        *(s32 *) outObj = hitObj;
    }
    if (outFlags != 0) {
        if (ray.kind == 1) {
            flags = ((u32 *) g_coll_tri_flags)[ray.hitTri];
        } else {
            /* Rare's asm reads the object from gp, which holds the object only when the vertex output ran; without
             * it gp is still the last tested triangle's g_level_tri_table record (kept: ray.lastRec) */
            obj = (u8 *) ray.lastRec;
            triFlags = *(u32 **) (obj + NMR_OBJ_TRIFLAGS);
            if (triFlags != NULL) {
                flags = triFlags[ray.hitTri - NMR_OBJ_U16(obj, NMR_OBJ_TRI0)];
            } else {
                flags = *(u32 *) (obj + NMR_OBJ_FLAGS);
            }
        }
        *(u32 *) outFlags = flags;
    }
    return 1;
}
