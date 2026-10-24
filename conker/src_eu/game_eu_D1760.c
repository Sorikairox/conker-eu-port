#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
/*
 * P54: func_150A3F50 / func_150A48C0 / func_150A5480 are hand-written asm (one shared register convention): each
 * walks a set of triangles and runs the per-triangle floor test func_150A408C (a label inside func_150A3F50.s,
 * here floor_tri) on the integer point (x, z). A triangle passes when (x, z) is inside its x / z bounds (+-2) and
 * between the two edges at z; its floor height (24.8, clamped to the triangle's y range) goes to the next 16-byte
 * entry of D_800D3720: +0 height, +4 pointer to the 3 vertex offsets, +8 vertex base, +0xC tag. The count stops at
 * 0x27 (later hits overwrite entry 0x27). Returns the count.
 * - func_150A3F50: area 0 / 1 (level). D_800DBE62 == 0: every triangle 0 .. D_800DBE4C - 1 (the asm leaves the tag
 *   = the caller's $gp; 0 here). Else D_800D39A4 = 0 and the BSP tree D_800DC278 (+4 sibling offset, +6 radius,
 *   +8 / +0xA centre x / z, +0xC child offset, leaf byte list at +0xE: b < 0x80 = previous index + b, else 15-bit
 *   index ((b & 0x7F) << 8 | next byte), 0 = end): only the first leaf reached is tested, tag 0. The first delta
 *   adds to the caller's $v1 (0 here; level data starts each leaf with an absolute index).
 * - func_150A48C0: area 2, the world objects in the u16 list ids[0 .. count - 1] (D_800DBEF4 + id * 0xA0: +0x56
 *   triangle count, +0x58 first triangle; vertex base D_800DC328[id], skipped when 0), tag = id.
 * - func_150A5480: area 3, the 25 records D_800CC2D0 except D_800D39FC - 1, with +0 != 0, +0xF8 & 0x4000,
 *   +0x264 (vertex base) and +0x268 (bounds) set; byte +4 = model: D_800C5D38[m] triangles, offsets D_800C6070[m].
 */
extern u8 D_800DBE62;
extern s32 D_800DBE4C;          /* level triangle count */
extern s32 D_800D39A4;
extern s32 D_800D3720;          /* candidate floors, 16 bytes each */
extern s32 D_800DC26C;          /* triangle vertex offsets (3 words per triangle) */
extern s32 D_800DC270;          /* triangle x/z bounds (4 halfwords per triangle) */
extern s32 D_800DC278;          /* BSP tree */
extern u8 D_800D39FC;
extern u16 D_800C5D38[];

static s32 floor_div(s32 a, s32 b) {
    if (b == 0) return (a < 0) ? 1 : -1; /* VR4300 lo for a zero divisor */
    if (b == -1) return (s32)(0u - (u32)a);
    return a / b;
}
#define FLOOR_MUL(a, b) ((s32)((u32)(a) * (u32)(b)))
#define FLOOR_SHL8(a) ((s32)((u32)(a) << 8))

/* func_150A408C: floor test of triangle i (tables vofs / bnd, vertices at base + offset); n = entries so far */
static s32 floor_tri(s32 x, s32 z, s32 i, u8 *vofs, u8 *bnd, s32 base, s32 tag, s32 n) {
    s16 *b = (s16 *)(bnd + i * 8);
    s32 *vo;
    s16 *p;
    s32 ax, ay, az, bx, by, bz, cx, cy, cz, t;
    s32 dzAC, dz, k, xAC, dz2, dzB, lx, ux, x2, d1, d2, s;
    s32 ymax, ymin, yAC, ly, uy, y2, v;
    u8 *e;

    if (x < b[0] - 2 || z < b[1] - 2 || b[2] + 2 < x || b[3] + 2 < z) return n;
    vo = (s32 *)(vofs + i * 12);
    p = (s16 *)(vo[0] + base); ax = p[0]; ay = p[1]; az = p[2];
    p = (s16 *)(vo[1] + base); bx = p[0]; by = p[1]; bz = p[2];
    p = (s16 *)(vo[2] + base); cx = p[0]; cy = p[1]; cz = p[2];
    /* A = the lowest z */
    if (az < bz ? (cz < az) : !(bz < cz)) {
        t = ax; ax = cx; cx = t;
        t = ay; ay = cy; cy = t;
        t = az; az = cz; cz = t;
    } else if (!(az < bz)) {
        t = ax; ax = bx; bx = t;
        t = ay; ay = by; by = t;
        t = az; az = bz; bz = t;
    }
    if (z < az) return n;
    /* C = the highest z */
    if (cz < bz) {
        t = bx; bx = cx; cx = t;
        t = by; by = cy; cy = t;
        t = bz; bz = cz; cz = t;
    }
    if (cz < z) return n;
    dzAC = cz - az + 1;
    k = floor_div(FLOOR_SHL8(cx - ax), dzAC);
    dz = z - az;
    xAC = (FLOOR_MUL(dz, k) >> 8) + ax;
    dzB = z - bz;
    if (dzB < 0) {
        dz2 = bz - az + 1; s = z - az; lx = ax; ux = bx;
    } else {
        dz2 = cz - bz + 1; s = dzB; lx = bx; ux = cx;
    }
    k = floor_div(FLOOR_SHL8(ux - lx), dz2);
    x2 = (FLOOR_MUL(s, k) >> 8) + lx;
    d1 = x2 - x;
    d2 = xAC - x;
    t = (d1 < d2) ? 1 : -1;
    d1 -= t;
    d2 += t;
    if ((d2 ^ d1) >= 0) return n;

    e = (u8 *)&D_800D3720 + n * 16;
    *(s32 *)(e + 4) = (s32)vo;
    ymax = ay;
    if (ymax < by) ymax = by;
    if (ymax < cy) ymax = cy;
    ymax = FLOOR_SHL8(ymax);
    ymin = (by < ay) ? by : ay;
    if (cy < ymin) ymin = cy;
    k = floor_div(FLOOR_SHL8(cy - ay), dzAC);
    yAC = FLOOR_SHL8(ay) + FLOOR_MUL(dz, k);
    if (dzB < 0) {
        ly = ay; uy = by;
    } else {
        ly = by; uy = cy;
    }
    ymin = FLOOR_SHL8(ymin);
    k = floor_div(FLOOR_SHL8(uy - ly), dz2);
    y2 = FLOOR_MUL(s, k) + FLOOR_SHL8(ly);
    k = floor_div(FLOOR_SHL8(yAC - y2), xAC - x2);
    v = y2 + (FLOOR_MUL(x - x2, k) >> 8);
    if (ymax < v) v = ymax;
    if (v < ymin) v = ymin;
    *(s32 *)(e + 0) = v;
    *(s32 *)(e + 8) = base;
    *(s32 *)(e + 0xC) = tag;
    if (n != 0x27) n++;
    return n;
}

s32 func_150A3F50(s32 x, s32 z) {
    u8 *vofs = (u8 *)D_800DC26C;
    u8 *bnd = (u8 *)D_800DC270;
    u8 *node;
    s32 n = 0;
    s32 i, d, off;
    u32 c;

    if (D_800DBE62 == 0) {
        for (i = 0; i != D_800DBE4C; i++) {
            n = floor_tri(x, z, i, vofs, bnd, 0, 0, n);
        }
        return n;
    }
    D_800D39A4 = 0;
    node = (u8 *)D_800DC278;
    for (;;) {
        d = (s32)((u32)x - (u32)*(s16 *)(node + 8));
        if (d <= 0) d = (s32)(0u - (u32)d);
        if (!(*(u16 *)(node + 6) < d)) {
            d = (s32)((u32)z - (u32)*(s16 *)(node + 0xA));
            if (d < 0) d = (s32)(0u - (u32)d);
            if (!(*(u16 *)(node + 6) < d)) {
                off = *(s16 *)(node + 0xC);
                if (off == 0) break;
                node += off;
                continue;
            }
        }
        off = *(s16 *)(node + 4);
        if (off == 0) return n;
        node += off;
    }
    node += 0xE;
    i = 0;
    while ((c = node[0]) != 0) {
        if (c & 0x80) {
            node++;
            i = ((c & 0x7F) << 8) | node[0];
        } else {
            i += c;
        }
        n = floor_tri(x, z, i, vofs, bnd, 0, 0, n);
        node++;
    }
    return n;
}

s32 func_150A48C0(s32 x, s32 z, s32 count, s32 *idList) {
    u16 *ids = (u16 *)idList;
    u16 *end;
    u8 *obj;
    u8 *vofs, *bnd;
    s32 n = 0;
    s32 id, base, cnt, i;

    if (count == 0) return 0;
    end = ids + count;
    while (ids != end) {
        id = *ids++;
        obj = (u8 *)D_800DBEF4 + id * 0xA0;
        bnd = (u8 *)D_800DC270 + *(u16 *)(obj + 0x58) * 8;
        vofs = (u8 *)D_800DC26C + *(u16 *)(obj + 0x58) * 12;
        base = D_800DC328[id];
        if (base == 0) continue;
        cnt = *(u16 *)(obj + 0x56);
        for (i = 0; i != cnt; i++) {
            n = floor_tri(x, z, i, vofs, bnd, base, id, n);
        }
    }
    return n;
}

s32 func_150A5480(s32 x, s32 z) {
    u8 *rec = (u8 *)D_800CC2D0;
    u8 *end = rec + 0x4F4C;
    s32 skip = D_800D39FC - 1;
    s32 n = 0;
    s32 idx = -1;
    s32 base, cnt, m, i;
    u8 *bnd, *vofs;

    for (;;) {
        idx++;
        if (end == rec) return n;
        rec += 0x32C;
        if (idx == skip) continue;
        if (*(s32 *)(rec - 0x32C) == 0) continue;
        if (!(*(s32 *)(rec - 0x32C + 0xF8) & 0x4000)) continue;
        base = *(s32 *)(rec - 0x32C + 0x264);
        bnd = *(u8 **)(rec - 0x32C + 0x268);
        if (base == 0) continue;
        m = *(rec - 0x32C + 4);
        cnt = D_800C5D38[m];
        vofs = (u8 *)D_800C6070[m];
        if (bnd == NULL) continue;
        for (i = 0; i != cnt; i++) {
            n = floor_tri(x, z, i, vofs, bnd, base, idx, n);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D1760/func_150A3F50.s")
#endif

#ifdef NON_MATCHING
/*
 * P53: func_150A44A4.s is hand-written: the height of a floor triangle under the point (x, z), in 24.8 fixed point.
 * The triangle is either 3 vertex pointers (tri, when packed == NULL) or 9 inline s16 (packed: x, y, z per vertex;
 * all-zero first or second 8 bytes = no triangle). The vertices are sorted by z, the two edges crossing z = pz give
 * the x / y span, and the result is clamped to the triangle's y range. Returns `out` (as an s32) on a hit, else 0.
 * The asm keeps s5-s7 / fp in f1-f4 while it uses them; integer products wrap (mult / mflo), and a zero x span (a
 * point exactly on a vertical edge) divides by zero on the VR4300 without effect on the result.
 */
#define A44A4_RINT(f)                                                                                \
    (((f) >= 8388608.0f || (f) <= -8388608.0f) ? (s32)(f)                                            \
     : ((f) >= 0.0f) ? (s32)(((f) + 8388608.0f) - 8388608.0f)                                       \
                     : -(s32)((-(f) + 8388608.0f) - 8388608.0f))
#define A44A4_MUL(a, b) ((s32)((u32)(a) * (u32)(b)))
#define A44A4_SHL8(a) ((s32)((u32)(a) << 8))

static s32 a44a4_div(s32 a, s32 b) {
    if (b == 0) return (a < 0) ? 1 : -1; /* VR4300 lo for a zero divisor */
    if (b == -1) return (s32)(0u - (u32)a);
    return a / b;
}

s32 func_150A44A4(f32 x, f32 z, s32 tri, u8 *packed, f32 *out) {
    s32 px, pz;
    s32 ax, ay, az, bx, by, bz, cx, cy, cz, t;
    s32 dz1, rz1, dz2, rz2, rzb, k, x1, x2, sx, ex, sy, ey, d1, d2, s, ymax, ymin, y1, y2, v;
    s16 **vp;
    s32 i;

    px = A44A4_RINT(x);
    pz = A44A4_RINT(z);
    if (packed == NULL) {
        vp = (s16 **)tri;
        ax = vp[0][0]; ay = vp[0][1]; az = vp[0][2];
        bx = vp[1][0]; by = vp[1][1]; bz = vp[1][2];
        cx = vp[2][0]; cy = vp[2][1]; cz = vp[2][2];
    } else {
        for (i = 0; i < 8; i++) {
            if (packed[i] != 0) break;
        }
        if (i == 8) return 0;
        for (i = 8; i < 16; i++) {
            if (packed[i] != 0) break;
        }
        if (i == 16) return 0;
        ax = ((s16 *)packed)[0]; ay = ((s16 *)packed)[1]; az = ((s16 *)packed)[2];
        bx = ((s16 *)packed)[3]; by = ((s16 *)packed)[4]; bz = ((s16 *)packed)[5];
        cx = ((s16 *)packed)[6]; cy = ((s16 *)packed)[7]; cz = ((s16 *)packed)[8];
    }
    /* A = the lowest z */
    if (az < bz ? (cz < az) : !(bz < cz)) {
        t = ax; ax = cx; cx = t;
        t = ay; ay = cy; cy = t;
        t = az; az = cz; cz = t;
    } else if (!(az < bz)) {
        t = ax; ax = bx; bx = t;
        t = ay; ay = by; by = t;
        t = az; az = bz; bz = t;
    }
    if (pz < az) return 0;
    /* C = the highest z */
    if (cz < bz) {
        t = bx; bx = cx; cx = t;
        t = by; by = cy; cy = t;
        t = bz; bz = cz; cz = t;
    }
    if (cz < pz) return 0;
    /* x on the edge A-C and on A-B / B-C at z = pz */
    dz1 = cz - az + 1;
    k = a44a4_div(A44A4_SHL8(cx - ax), dz1);
    rz1 = pz - az;
    x1 = (A44A4_MUL(rz1, k) >> 8) + ax;
    dz2 = cz - bz;
    rzb = pz - bz;
    rz2 = rzb;
    ex = cx;
    sx = bx;
    if (rzb < 0) {
        dz2 = bz - az;
        rz2 = pz - az;
        ex = bx;
        sx = ax;
    }
    dz2 += 1;
    k = a44a4_div(A44A4_SHL8(ex - sx), dz2);
    x2 = (A44A4_MUL(rz2, k) >> 8) + sx;
    d2 = x2 - px;
    d1 = x1 - px;
    s = (d2 < d1) ? 1 : -1;
    d2 -= s;
    d1 += s;
    if ((d1 ^ d2) >= 0) return 0;
    /* y range of the triangle */
    ymax = ay;
    if (ymax < by) ymax = by;
    if (ymax < cy) ymax = cy;
    ymax = A44A4_SHL8(ymax);
    k = a44a4_div(A44A4_SHL8(cy - ay), dz1);
    ymin = ay;
    if (by < ymin) ymin = by;
    if (cy < ymin) ymin = cy;
    y1 = A44A4_SHL8(ay) + A44A4_MUL(rz1, k);
    ey = cy;
    sy = by;
    if (rzb < 0) {
        ey = by;
        sy = ay;
    }
    k = a44a4_div(A44A4_SHL8(ey - sy), dz2);
    ymin = A44A4_SHL8(ymin);
    y2 = A44A4_MUL(rz2, k) + A44A4_SHL8(sy);
    k = a44a4_div(A44A4_SHL8(y1 - y2), x1 - x2);
    v = y2 + (A44A4_MUL(px - x2, k) >> 8);
    if (ymax < v) v = ymax;
    if (v < ymin) v = ymin;
    *out = (1.0f / 256.0f) * (f32)v;
    return (s32)out;
}

/* P54: func_150A44A4_tail.s no longer needed (func_150A3F50 / func_150A48C0 are C) */
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D1760/func_150A44A4.s")
#endif

#ifndef NON_MATCHING /* P54: C above */
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D1760/func_150A48C0.s")
#endif

#ifdef NON_MATCHING
/*
 * func_150A49D0.s is hand-written asm with two entry points: func_150A49D0 (transform the vertices of a
 * list of world objects into world space and refresh their per-triangle bounding boxes) and func_150A4ED4
 * (select the collision tables of one area). The other glabels in the file (func_150A4B50, func_150A4CC8,
 * func_150A4CDC, func_150A4D78) are labels inside func_150A49D0's loop, not functions. The fragment after
 * func_150A4ED4 (.L150A4F74 / D_150A4FD4) is reached from func_150A3F50 and stays asm (func_150A49D0_tail.s).
 */
typedef struct {
    /* 0x00 */ f32 rot[3];      /* degrees */
    /* 0x0C */ u8 pad0C[4];
    /* 0x10 */ s16 pos[3];
    /* 0x16 */ u16 numVerts;
    /* 0x18 */ f32 yOffset;
    /* 0x1C */ u8 pad1C[4];
    /* 0x20 */ s16 *cachedVerts[2]; /* per frame buffer */
    /* 0x28 */ s16 *verts;          /* model-space vertices, 16 bytes each */
    /* 0x2C */ f32 scale[3];
    /* 0x38 */ u8 pad38[0x16];
    /* 0x4E */ u8 kind;             /* 0xFF: use the camera-relative matrix D_800DC338 */
    /* 0x4F */ u8 pad4F[7];
    /* 0x56 */ u16 numTris;
    /* 0x58 */ u16 firstTri;
    /* 0x5A */ u8 pad5A[0x15];
    /* 0x6F */ u8 flags6F;
    /* 0x70 */ u8 flags70;
    /* 0x71 */ u8 pad71[0x2F];
} WorldObj; /* size 0xA0 */

s32 allocate_memory(s32, s32, s32, s32);
void func_10004074(s32);
extern s32 D_800DC26C;          /* triangle vertex offsets (3 words per triangle) */
extern s32 D_800DC270;          /* triangle x/z bounds (4 halfwords per triangle) */
extern s32 D_800DC274;          /* triangle y bounds (2 halfwords per triangle) */
extern s32 D_800DC278;
extern f32 D_800DC338[2][4][4];
extern f32 D_8009FA50;          /* degrees to radians */

/* cvt.w.s with the default FCSR mode: round to nearest, ties to even */
#define BLOB49D0_RINT(f)                                                                             \
    (((f) >= 8388608.0f || (f) <= -8388608.0f) ? (s32)(f)                                            \
     : ((f) >= 0.0f) ? (s32)(((f) + 8388608.0f) - 8388608.0f)                                       \
                     : -(s32)((-(f) + 8388608.0f) - 8388608.0f))

s32 func_150A49D0(s32 count, s32 *idList, s32 force) {
    u16 *ids = (u16 *)idList;
    u16 *last;
    s32 buf;
    WorldObj *obj;
    s32 *slot;
    s16 *out;
    s16 *dst;
    s16 *dstEnd;
    s16 *src;
    s32 *tri;
    s16 *xz;
    s16 *xzEnd;
    s16 *ylim;
    s32 tmp;
    s32 id;
    f32 m00, m01, m02, m10, m11, m12, m20, m21, m22, tx, ty, tz;
    f32 cA, sA, cB, sB, cC, sC;
    f32 x, y, z, r;
    s16 minX, minY, minZ, maxX, maxY, maxZ;
    s16 *v;
    s32 k;

    if (count == 0) {
        return 0;
    }
    buf = D_800BE9C0;
    last = ids + count - 1;
    for (;; ids++) {
        tmp = 0;
        id = *ids;
        D_800DC32C[id] = 3;
        slot = &D_800DC328[id];
        if (*slot != 0) {
            goto next;
        }
        obj = (WorldObj *)((u8 *)D_800DBEF4 + id * 0xA0);
        if (!force) {
            if (obj->flags70 & 1) {
                out = obj->cachedVerts[buf];
                *slot = (s32)out;
                goto bounds;
            }
            out = (s16 *)allocate_memory(obj->numVerts << 4, 1, 0, 2);
            *slot = (s32)out;
            if (out == NULL) {
                goto next;
            }
        } else {
            out = (s16 *)allocate_memory(obj->numVerts << 4, 1, 0, 2);
            tmp = (s32)out;
        }

        if (obj->kind == 0xFF) {
            f32 (*m)[4] = D_800DC338[buf != 0];
            m00 = m[0][0];
            m01 = m[0][1];
            m02 = m[0][2];
            m10 = m[1][0];
            m11 = m[1][1];
            m12 = m[1][2];
            m20 = m[2][0];
            m21 = m[2][1];
            m22 = m[2][2];
            tx = m[3][0];
            ty = m[3][1];
            tz = m[3][2];
        } else {
            r = obj->rot[0] * D_8009FA50;
            cA = func_150AD780(r);
            sA = func_150AD78C(r);
            r = obj->rot[1] * D_8009FA50;
            cB = func_150AD780(r);
            sB = func_150AD78C(r);
            r = obj->rot[2] * D_8009FA50;
            cC = func_150AD780(r);
            sC = func_150AD78C(r);
            m00 = (cC * cB) * obj->scale[0];
            m01 = sC * obj->scale[0];
            m02 = (cC * -sB) * obj->scale[0];
            m10 = ((cA * -sC) * cB + sA * sB) * obj->scale[1];
            m11 = (cA * cC) * obj->scale[1];
            m12 = ((cA * -sC) * -sB + sA * cB) * obj->scale[1];
            m20 = ((-sA * -sC) * cB + cA * sB) * obj->scale[2];
            m21 = (-sA * cC) * obj->scale[2];
            m22 = ((-sA * -sC) * -sB + cA * cB) * obj->scale[2];
            tx = (f32)obj->pos[0];
            ty = (f32)obj->pos[1] + obj->yOffset;
            tz = (f32)obj->pos[2];
        }

        /* world-space vertices: x/y/z halfwords of each 16-byte vertex (do-while: numVerts != 0) */
        src = obj->verts;
        dst = out;
        dstEnd = out + obj->numVerts * 8;
        do {
            x = (f32)src[0];
            y = (f32)src[1];
            z = (f32)src[2];
            r = ((x * m00 + y * m10) + tx) + z * m20;
            dst[0] = BLOB49D0_RINT(r);
            r = ((x * m01 + y * m11) + ty) + z * m21;
            dst[1] = BLOB49D0_RINT(r);
            r = ((x * m02 + y * m12) + tz) + z * m22;
            dst[2] = BLOB49D0_RINT(r);
            dst += 8;
            src += 8;
        } while (dst != dstEnd);

    bounds:
        if (!force && (obj->flags6F & 0x80)) {
            goto next;
        }
        /* bounding box of each triangle (do-while: numTris != 0) */
        xz = (s16 *)D_800DC270 + obj->firstTri * 4;
        ylim = (s16 *)D_800DC274 + obj->firstTri * 2;
        tri = (s32 *)D_800DC26C + obj->firstTri * 3;
        xzEnd = xz + obj->numTris * 4;
        do {
            v = (s16 *)((u8 *)out + tri[0]);
            minX = maxX = v[0];
            minY = maxY = v[1];
            minZ = maxZ = v[2];
            for (k = 1; k < 3; k++) {
                v = (s16 *)((u8 *)out + tri[k]);
                if (v[0] < minX) {
                    minX = v[0];
                } else if (maxX < v[0]) {
                    maxX = v[0];
                }
                if (v[1] < minY) {
                    minY = v[1];
                } else if (maxY < v[1]) {
                    maxY = v[1];
                }
                if (v[2] < minZ) {
                    minZ = v[2];
                } else if (maxZ < v[2]) {
                    maxZ = v[2];
                }
            }
            xz[0] = minX;
            xz[2] = maxX;
            xz[1] = minZ;
            xz[3] = maxZ;
            xz += 4;
            ylim[0] = minY;
            ylim[1] = maxY;
            ylim += 2;
            tri += 3;
        } while (xz != xzEnd);

    next:
        if (tmp != 0) {
            func_10004074(tmp);
        }
        if (ids == last) {
            break;
        }
    }
    return 0;
}

/* Select area `area`'s collision tables. */
void func_150A4ED4(s32 area) {
    D_800DC26C = D_800DC208[area];
    D_800DC270 = D_800DC218[area];
    D_800DC274 = D_800DC228[area];
    D_800DC278 = (s32)D_800DBE08[area];
    D_800DBE4C = D_800DBE18[area];
    D_800DC280 = area;
}

/* P54: func_150A49D0_tail.s no longer needed (func_150A3F50 / func_150A48C0 are C) */
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D1760/func_150A49D0.s")
#endif

#ifdef NON_MATCHING
/*
 * obj_floor_mesh_update: P190 readable C for the hand-written func_150A4FE4.s (saves $gp and every FPR, keeps
 * values in odd FPRs; inner labels func_150A53D4 / func_150A543C are its exit and release paths). Builds the
 * world-space floor mesh of an object record (D_800CC2D0, 0x32C bytes each) that func_150A5480 tests (area 3):
 * - only while the record is live (+0, +0x1D4 matrices, +0xF8 & 0x4000), its model m = byte +4 has a group list
 *   D_800C5C08[m] and another live record is within the radius +0x270 on x / z; otherwise the three buffers
 *   +0x264 / +0x268 / +0x26C are freed and cleared.
 * - +0x264: D_800C5BC0[m] vertices (s16 x / y / z, 0x10 bytes each). The D_800C6318[m] groups (12 bytes: +0 source
 *   s16 vertices, stride 0x10, +4 count, +8 matrix index) are transformed by the 4x4 f32 matrices at +0x1D4
 *   (0x40 bytes each), rounded with cvt.w.s.
 * - +0x268: per triangle (D_800C5D38[m] triangles, vertex byte offsets D_800C6070[m], 3 words each) the x / z
 *   bounds (min x, min z, max x, max z); +0x26C: the y bounds (min y, max y).
 * Buffers are allocated (allocate_memory(size, 1, 1, 2)) when missing; a failed allocation releases all three.
 * Counts of 0 (groups or triangles) loop "forever" in the asm (do-while); the C keeps that shape.
 */
extern u16 D_800C5BC0[];        /* model vertex counts */
extern u16 D_800C6318[];        /* model transform group counts */

#define OBJMESH_F(p, off) (*(f32 *)((u8 *)(p) + (off)))
#define OBJMESH_W(p, off) (*(s32 *)((u8 *)(p) + (off)))

static void objmesh_minmax(s32 v, s32 *lo, s32 *hi) {
    if (v < *lo) {
        *lo = v;
    } else if (*hi < v) {
        *hi = v;
    }
}

static s32 objmesh_rint(f32 f) {
    return BLOB49D0_RINT(f);
}

void func_150A4FE4(struct127 *arg0) {
    u8 *obj = (u8 *)arg0;
    u8 *rec;
    u8 *recEnd = (u8 *)D_800CC2D0 + 25 * 0x32C;
    s32 m, p;
    s32 *group;
    u32 groups, n;
    s16 *verts, *out, *src, *a, *b, *c;
    s16 *bounds, *yRange;
    s32 *tri, *triEnd;
    f32 *mtx;
    f32 r2, dx, dz, x, y, z;
    s32 minX, maxX, minY, maxY, minZ, maxZ;

    if (OBJMESH_W(obj, 0) == 0 || OBJMESH_W(obj, 0x1D4) == 0 || !(OBJMESH_W(obj, 0xF8) & 0x4000)) {
        goto release;
    }
    m = obj[4];
    group = (s32 *)D_800C5C08[m];
    if (group == NULL) {
        goto release;
    }
    /* another live record within the radius (x / z) */
    r2 = OBJMESH_F(obj, 0x270) * OBJMESH_F(obj, 0x270);
    for (rec = (u8 *)D_800CC2D0; rec != recEnd; rec += 0x32C) {
        if (rec == obj || OBJMESH_W(rec, 0) == 0) {
            continue;
        }
        dx = OBJMESH_F(rec, 0x14) - OBJMESH_F(obj, 0x14);
        dz = OBJMESH_F(rec, 0x1C) - OBJMESH_F(obj, 0x1C);
        if (dx * dx + dz * dz <= r2) {
            break;
        }
    }
    if (rec == recEnd) {
        goto release;
    }

    groups = D_800C6318[m] - 1;
    verts = (s16 *)OBJMESH_W(obj, 0x264);
    if (verts == NULL) {
        verts = (s16 *)allocate_memory(D_800C5BC0[m] << 4, 1, 1, 2);
        if (verts == NULL) {
            goto release;
        }
        OBJMESH_W(obj, 0x264) = (s32)verts;
    }
    bounds = (s16 *)OBJMESH_W(obj, 0x268);
    if (bounds == NULL) {
        bounds = (s16 *)allocate_memory(D_800C5D38[m] << 3, 1, 1, 2);
        if (bounds == NULL) {
            goto release;
        }
        OBJMESH_W(obj, 0x268) = (s32)bounds;
    }
    yRange = (s16 *)OBJMESH_W(obj, 0x26C);
    if (yRange == NULL) {
        yRange = (s16 *)allocate_memory(D_800C5D38[m] << 2, 1, 1, 2);
        if (yRange == NULL) {
            goto release;
        }
        OBJMESH_W(obj, 0x26C) = (s32)yRange;
    }

    /* transform the groups' vertices */
    out = verts;
    do {
        src = (s16 *)group[0];
        n = group[1];
        mtx = (f32 *)(OBJMESH_W(obj, 0x1D4) + (group[2] << 6));
        group += 3;
        for (; n != 0; n--) {
            x = src[0];
            y = src[1];
            z = src[2];
            out[0] = objmesh_rint((mtx[0] * x + mtx[4] * y) + (mtx[8] * z + mtx[12]));
            out[1] = objmesh_rint((mtx[1] * x + mtx[5] * y) + (mtx[9] * z + mtx[13]));
            out[2] = objmesh_rint((mtx[2] * x + mtx[6] * y) + (mtx[10] * z + mtx[14]));
            src += 8;
            out += 8;
        }
    } while (groups-- != 0);

    /* per-triangle bounds */
    tri = (s32 *)D_800C6070[m];
    triEnd = tri + D_800C5D38[m] * 3;
    do {
        a = (s16 *)((u8 *)verts + tri[0]);
        b = (s16 *)((u8 *)verts + tri[1]);
        c = (s16 *)((u8 *)verts + tri[2]);
        minX = maxX = a[0];
        minY = maxY = a[1];
        minZ = maxZ = a[2];
        objmesh_minmax(b[0], &minX, &maxX);
        objmesh_minmax(b[1], &minY, &maxY);
        objmesh_minmax(b[2], &minZ, &maxZ);
        objmesh_minmax(c[0], &minX, &maxX);
        objmesh_minmax(c[1], &minY, &maxY);
        objmesh_minmax(c[2], &minZ, &maxZ);
        bounds[0] = minX;
        bounds[1] = minZ;
        bounds[2] = maxX;
        bounds[3] = maxZ;
        yRange[0] = minY;
        yRange[1] = maxY;
        tri += 3;
        bounds += 4;
        yRange += 2;
    } while (tri != triEnd);
    return;

release:
    p = OBJMESH_W(obj, 0x264);
    OBJMESH_W(obj, 0x264) = 0;
    if (p != 0) {
        func_10004074(p);
    }
    p = OBJMESH_W(obj, 0x268);
    OBJMESH_W(obj, 0x268) = 0;
    if (p != 0) {
        func_10004074(p);
    }
    p = OBJMESH_W(obj, 0x26C);
    OBJMESH_W(obj, 0x26C) = 0;
    if (p != 0) {
        func_10004074(p);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D1760/func_150A4FE4.s")
#endif

#ifndef NON_MATCHING /* P54: C above */
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D1760/func_150A5480.s")
#endif
