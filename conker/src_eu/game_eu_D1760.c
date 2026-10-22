#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D1760/func_150A3F50.s")

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

#pragma GLOBAL_ASM("src_eu/nm_asm/func_150A44A4_tail.s")
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D1760/func_150A44A4.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D1760/func_150A48C0.s")

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

#pragma GLOBAL_ASM("src_eu/nm_asm/func_150A49D0_tail.s")
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D1760/func_150A49D0.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D1760/func_150A4FE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D1760/func_150A5480.s")
