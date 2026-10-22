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
#ifdef NON_MATCHING
#include <ultra64.h>

#include "functions.h"
#include "variables.h"

/* box half extents (D_800CC64C/50/54) and the y/x, z/x ratios used for the box diagonals (D_800CC658/5C) */
extern f32 D_800CC630; /* plane of the last tested triangle: normal x, y, z, then d */
extern f32 D_800CC634;
extern f32 D_800CC638;
extern f32 D_800CC63C;
extern f32 D_8009FAB0; /* slack of the point-in-triangle bounding-box test */

#define NM_FABS(x) ((x) < 0.0f ? -(x) : (x))

typedef struct {
    f32 x, y, z;
} TriPt;

/* Triangle / box intersection after D. Voorhies, "Triangle-Cube Intersection" (Graphics Gems III), for a
 * box centred on the origin with half extents (hx, hy, hz). */

/* face_plane: one bit per box face the point is outside of */
static s32 nmD5E90_outcode(TriPt *p) {
    s32 r = 0;

    if (!(p->x <= D_800CC64C)) r |= 1;
    if (p->x < -D_800CC64C) r |= 2;
    if (!(p->y <= D_800CC650)) r |= 4;
    if (p->y < -D_800CC650) r |= 8;
    if (!(p->z <= D_800CC654)) r |= 0x10;
    if (p->z < -D_800CC654) r |= 0x20;
    return r;
}

/* bevel_2d: the 12 edge planes */
static s32 nmD5E90_bevel2d(TriPt *p) {
    s32 r = 0;
    f32 s;

    s = D_800CC64C + D_800CC650;
    if (!(p->x + p->y <= s)) r |= 1;
    if (!(p->x - p->y <= s)) r |= 2;
    if (!(-(p->x + p->y) <= s)) r |= 8;
    if (!(-(p->x - p->y) <= s)) r |= 4;
    s = D_800CC64C + D_800CC654;
    if (!(p->x + p->z <= s)) r |= 0x10;
    if (!(p->x - p->z <= s)) r |= 0x20;
    if (!(-(p->x + p->z) <= s)) r |= 0x80;
    if (!(-(p->x - p->z) <= s)) r |= 0x40;
    s = D_800CC650 + D_800CC654;
    if (!(p->y + p->z <= s)) r |= 0x100;
    if (!(p->y - p->z <= s)) r |= 0x200;
    if (!(-(p->y + p->z) <= s)) r |= 0x800;
    if (!(-(p->y - p->z) <= s)) r |= 0x400;
    return r;
}

/* bevel_3d: the 8 corner planes */
static s32 nmD5E90_bevel3d(TriPt *p) {
    s32 r = 0;
    f32 s = D_800CC64C + D_800CC650 + D_800CC654;
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
        if ((diff & 1) && nmD5E90_checkPoint(a, b, (D_800CC64C - b->x) * inv, 0x3E) == 0) return 0;
        if ((diff & 2) && nmD5E90_checkPoint(a, b, -(D_800CC64C + b->x) * inv, 0x3D) == 0) return 0;
    }
    if (diff & 0xC) {
        inv = 1.0f / (a->y - b->y);
        if ((diff & 4) && nmD5E90_checkPoint(a, b, (D_800CC650 - b->y) * inv, 0x3B) == 0) return 0;
        if ((diff & 8) && nmD5E90_checkPoint(a, b, -(D_800CC650 + b->y) * inv, 0x37) == 0) return 0;
    }
    if (diff & 0x30) {
        inv = 1.0f / (a->z - b->z);
        if ((diff & 0x10) && nmD5E90_checkPoint(a, b, (D_800CC654 - b->z) * inv, 0x2F) == 0) return 0;
        if ((diff & 0x20) && nmD5E90_checkPoint(a, b, -(D_800CC654 + b->z) * inv, 0x1F) == 0) return 0;
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
    f32 eps = D_8009FAB0;
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

/* plane of the triangle, also stored in D_800CC630..3C */
static void nmD5E90_plane(TriPt *v, f32 *n) {
    f32 dy12 = v[0].y - v[1].y, dz13 = v[0].z - v[2].z, dy13 = v[0].y - v[2].y;
    f32 dz12 = v[0].z - v[1].z, dx12 = v[0].x - v[1].x, dx13 = v[0].x - v[2].x;

    n[0] = dy12 * dz13 - dz12 * dy13;
    n[1] = dz12 * dx13 - dx12 * dz13;
    n[2] = dx12 * dy13 - dy12 * dx13;
    n[3] = n[0] * v[0].x + n[1] * v[0].y + n[2] * v[0].z;
    D_800CC630 = n[0];
    D_800CC634 = n[1];
    D_800CC638 = n[2];
    D_800CC63C = n[3];
}

/* one of the 4 box diagonals (1, sy * ky, sz * kz) against the triangle's plane: 0 if it hits the triangle */
static s32 nmD5E90_diagonal(TriPt *v, f32 *n, f32 sy, f32 sz) {
    f32 ny = n[1] * D_800CC658;
    f32 nz = n[2] * D_800CC65C;
    f32 denom = n[0] + sy * ny + sz * nz;
    f32 t;
    TriPt q;

    if (denom == 0.0f) {
        denom = 0.0001f;
    }
    t = n[3] / denom;
    if (NM_FABS(t) <= D_800CC64C) {
        q.x = t;
        q.y = sy * (t * D_800CC658);
        q.z = sz * (t * D_800CC65C);
        if (nmD5E90_pointInTri(&q, v) == 0) {
            return 0;
        }
    }
    return 1;
}

/* Triangle (9 floats, the 3 vertices relative to the box centre) vs the box D_800CC64C/50/54.
 * Returns 0 if they intersect, 1 if the triangle is outside. When the test gets past the vertex-in-box
 * check, the triangle's plane is left in D_800CC630..3C. Used by func_15049260 (quadtree culling). */
s32 func_150AB278(struct_eu_bytes24 arg0) {
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
/* ---- func_150AD780 / func_150AD78C: cosf / sinf (P24) ----
 * sin: |x| < 2^-12 -> x; |x| < 1.5 -> odd polynomial; |x| < 2^28 -> reduce by n = round(x / pi) with a two-part
 * pi (D_8009FAF8 + D_8009FAFC), polynomial, negate for odd n; else (and inf/NaN) 0. cos(x) = sin(x + pi/2).
 * The asm tests the float bits: (bits >> 22) & 0x1FF is the exponent plus the top mantissa bit. */
extern f32 D_8009FAE0; /* pi/2 */
extern f32 D_8009FAE4, D_8009FAE8, D_8009FAEC, D_8009FAF0; /* small-range coefficients */
extern f32 D_8009FAF4; /* 1/pi */
extern f32 D_8009FAF8, D_8009FAFC; /* pi high / low part */
extern f32 D_8009FB00, D_8009FB04, D_8009FB08, D_8009FB0C; /* reduced-range coefficients */

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

f32 func_150AD78C(f32 x) {
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
        r = ((D_8009FAE4 * x2 + D_8009FAE8) * x2 + D_8009FAEC) * x2 + D_8009FAF0;
        return r * (x2 * x) + x;
    }
    if (e >= 0x136) {
        return 0.0f;
    }
    n = nmD5E90_rint(D_8009FAF4 * x);
    nf = (f32)n;
    x = x - D_8009FAF8 * nf;
    x = x - D_8009FAFC * nf;
    x2 = x * x;
    r = (((D_8009FB00 * x2 + D_8009FB04) * x2 + D_8009FB08) * x2 + D_8009FB0C) * x2;
    r = r * x + x;
    if (n & 1) {
        r = -r;
    }
    return r;
}

f32 func_150AD780(f32 x) {
    return func_150AD78C(x + D_8009FAE0);
}

/* ---- P56: wall engine func_150AB6D0 / func_150AC8C4 (-> func_150AB708) and ray cast func_150ACEA0 ----
 * Hand asm with private register conventions: the helpers pass points / boxes / planes in FPRs, the engine keeps
 * its state in s0-s7 / fp / gp / f23-f31 across helpers and jumps through 4 continuation pointers that each entry
 * stub stores at sp+0x1D0..0x1DC (map: docs/port/sessions/P53.md section 5). Rather than a hand rewrite, the code is
 * a mechanical register-level translation (tools/port/asm2c_hand.py, regenerate with tools/port/gen_d5e90_walls.sh):
 * GPRs are u32 locals, FPRs the union array F, one C statement per instruction, branch delay slots honoured,
 * internal jal / jr through the `dispatch` switch over the code addresses a register can hold, external callees as
 * C calls. The asm frame (0x268 / 0x70 bytes) is a local buffer; sp holds its address.
 * Includes: D5E90_walls.inc = func_150AA950 .. func_150AB264 (triangle / box test of func_150AAF00 and helpers)
 * + func_150AB6D0 .. func_150ACE90; D5E90_ray.inc = func_150ACEA0 .. func_150ADC40 (with func_150AD844). */
#include <libc/math.h>

extern u8 D_8009FAC0[], D_8009FAC8[], D_8009FACC[], D_8009FAD0[], D_800C5D38[], D_800CC1B0[], D_800CC1B4[];
extern u8 D_800CC1B8[], D_800CC1C0[], D_800CC1F2[], D_800CC1F3[], D_800CC1F4[], D_800CC1F8[], D_800CC1FC[];
extern u8 D_800D3C00[], D_800DC26C[], D_800DC270[], D_800DC274[], D_800DC278[], D_800DC3C4[];
s32 func_1507C7C0(struct127 *, s16 *, s16 *, s16 *);
s32 func_150A69A8(s32, s32, s32 *, s32);
s32 func_150A49D0(s32, s32 *, s32);
void func_1510F800(s32);

typedef union {
    f32 f;
    u32 u;
    s32 i;
} NmwReg;

#define NMW_RET 0xFFFFFFF0u
/* ASM2C_TRACE=1 tools/port/gen_d5e90_walls.sh puts NMW_TRACE(label) at every label (debugging: ring at 0x80700000) */
#define NMW_TRACE(a) { u32 *tr_ = (u32 *) 0x80700000; tr_[1 + (tr_[0]++ & 0x3FFF)] = (a); }
#define NMW_P(a) ((u8 *) (a))
#define LW(a) (*(u32 *) NMW_P(a))
#define LH(a) ((u32) (s32) *(s16 *) NMW_P(a))
#define LHU(a) ((u32) *(u16 *) NMW_P(a))
#define LB(a) ((u32) (s32) *(s8 *) NMW_P(a))
#define LBU(a) ((u32) *(u8 *) NMW_P(a))
#define SW(a, v) (*(u32 *) NMW_P(a) = (u32) (v))
#define SH(a, v) (*(u16 *) NMW_P(a) = (u16) (v))
#define SB(a, v) (*(u8 *) NMW_P(a) = (u8) (v))
#define HI(x) (((u32) (x) + 0x8000) & 0xFFFF0000)
#define LO(x) ((u32) (s32) (s16) ((u32) (x) & 0xFFFF))
#define MULT(a, b) (lo = (u32) ((s32) (a) * (s32) (b)))
/* VR4300 div: by zero lo = (rs < 0 ? 1 : -1); only lo is read */
#define DIV(a, b) (lo = ((b) == 0 ? ((s32) (a) < 0 ? 1 : (u32) -1) \
                       : ((a) == 0x80000000 && (b) == (u32) -1) ? 0x80000000 : (u32) ((s32) (a) / (s32) (b))))
#define CVTW(f) nmD5E90_rint(f)

static f32 nmw_u2f(u32 u) {
    NmwReg r;

    r.u = u;
    return r.f;
}
#define U2F(x) nmw_u2f(x)

/* the register file and frame of one machine run */
#define NMW_REGS                                                                                         \
    u32 at = 0, v0 = 0, v1 = 0, a0 = 0, a1 = 0, a2 = 0, a3 = 0, t0 = 0, t1 = 0, t2 = 0, t3 = 0, t4 = 0, \
        t5 = 0, t6 = 0, t7 = 0, t8 = 0, t9 = 0, s0 = 0, s1 = 0, s2 = 0, s3 = 0, s4 = 0, s5 = 0, s6 = 0,  \
        s7 = 0, gp = 0, fp = 0, ra = NMW_RET, sp, pc, lo = 0;                                            \
    s32 c, cc = 0, k_;                                                                                   \
    NmwReg F[32]

/* f12 / f14 = target x / y, a2 = target z (float bits; the callers' prototype is (f32, f32, s32, u8 *, s32)), a3 = record, stack word 0x10 = mark touched objects.
 * Returns 1 if a wall moved the record (rec+0x14..0x1C written back). */
static s32 nmw_walls(u32 entry, f32 x, f32 y, u32 zbits, u32 rec, s32 mark) {
    NMW_REGS;
    u32 stk[(0x268 + 0x20) / 4];

    for (k_ = 0; k_ < 32; k_++) {
        F[k_].u = 0;
    }
    sp = (u32) stk + 0x268;
    SW(sp + 0x10, mark);
    F[12].f = x;
    F[14].f = y;
    a2 = zbits;
    a3 = rec;
    pc = entry;
    goto dispatch;
#include "D5E90_walls.inc"
bad: /* a code address the translation does not know: cannot happen */
    return 0xBAD00000 | (pc & 0xFFFFF);
done:
    return v0;
}

s32 func_150AB6D0(f32 x, f32 y, s32 zbits, u8 *rec, s32 mark) {
    return nmw_walls(0x150AB6D0, x, y, zbits, (u32) rec, mark);
}

/* returns at once (v0 = 0 here, the caller's v0 in the asm) if rec+0x20 > 0 */
s32 func_150AC8C4(f32 x, f32 y, s32 zbits, u8 *rec, s32 mark) {
    return nmw_walls(0x150AC8C4, x, y, zbits, (u32) rec, mark);
}

/* ray cast: o32 arguments (f12, f14, a2, a3, then the stack words 0x10..0x38 of the caller) */
s32 func_150ACEA0(f32 x0, f32 y0, f32 z0, f32 dx, f32 dy, f32 dz, s32 a6, s32 a7, s32 a8, s32 a9, s32 a10, s32 a11,
                  s32 a12, s32 a13, f32 a14) {
    NMW_REGS;
    u32 stk[(0x70 + 0x40) / 4];

    for (k_ = 0; k_ < 32; k_++) {
        F[k_].u = 0;
    }
    sp = (u32) stk + 0x70;
    SW(sp + 0x10, *(u32 *) &dy);
    SW(sp + 0x14, *(u32 *) &dz);
    SW(sp + 0x18, a6);
    SW(sp + 0x1C, a7);
    SW(sp + 0x20, a8);
    SW(sp + 0x24, a9);
    SW(sp + 0x28, a10);
    SW(sp + 0x2C, a11);
    SW(sp + 0x30, a12);
    SW(sp + 0x34, a13);
    SW(sp + 0x38, *(u32 *) &a14);
    F[12].f = x0;
    F[14].f = y0;
    a2 = *(u32 *) &z0;
    a3 = *(u32 *) &dx;
    pc = 0x150ACEA0;
    goto dispatch;
#include "D5E90_ray.inc"
bad: /* a code address the translation does not know: cannot happen */
    return 0xBAD00000 | (pc & 0xFFFFF);
done:
    return v0;
}
#endif
