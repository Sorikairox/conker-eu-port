#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
extern s32 D_800D3668;
extern s32 D_800D3A8C;
extern f32 D_800D3A00;
extern f32 D_800D3A90;
extern u8 *D_800DC278;
#endif


#ifdef NON_MATCHING
/* P186 */
extern u8 D_800D3A08[]; /* per-vertex cull flags, 4 bytes per vertex: x' < 0, inside the side planes, in front */

/* mesh_dl_cull_copy: P186: C for the hand-written asm func_150A55A0 (+ its loop func_150A563C / func_150A5654 /
 * func_150A5678 / func_150A57D4, which nothing else enters). Copies the F3DEX2 display list `dl` to gdl and drops
 * what the view (matrix mtx: f32[4][4], row vectors; x' = column 0, depth z' = column 2) cannot see:
 * - G_VTX (0x01): the vertices (address w1 + base, count (w0 >> 8) & 0xFFF0 bytes, always loaded from flag slot 0)
 *   get flags [0] = sign bit of x', [1] = |z'| > |x'| * D_800D3A00 (inside the side planes), [2] = !(z' >= 0)
 *   (in front). The command is copied; it replaces an output G_VTX directly before it (no triangle in between).
 * - G_TRI1 (0x05, vertex indices * 2 in bytes 1..3): dropped when no vertex is in front; kept when one is inside,
 *   or when the three x' signs differ (1 or 2 negative), else dropped.
 * - 0xF3 (G_LOADBLOCK): copied; a previous one with no kept triangle since is turned into a no-op (8 zero bytes).
 * - G_ENDDL (0xDF): not copied; returns the output end. Everything else is copied. arg3 / arg4 are not read. */
Gfx *func_150A55A0(s32 dl, Gfx *gdl, u8 *mtx, s32 arg3, s32 arg4, s32 base) {
    f32 *m = (f32 *) mtx;
    u32 *src = (u32 *) dl;
    u32 *out = (u32 *) gdl;
    u32 *lastLoad = NULL;
    u8 *f0, *f1, *f2;
    u8 *vtx, *end;
    u8 *fl;
    f32 x, y, z, sz;
    union { f32 f; u32 u; } sx;
    s32 inside, front, neg;
    s8 op;

    for (;;) {
        op = *(s8 *) src;
        if (op == 5) {
            f0 = &D_800D3A08[((u8 *) src)[1] * 2];
            f1 = &D_800D3A08[((u8 *) src)[2] * 2];
            f2 = &D_800D3A08[((u8 *) src)[3] * 2];
            inside = f0[1] + f1[1] + f2[1];
            front = f0[2] + f1[2] + f2[2];
            neg = f0[0] + f1[0] + f2[0];
            if (front == 0 || (inside == 0 && neg != 1 && neg != 2)) {
                src += 2;
                continue;
            }
            lastLoad = NULL;
        } else if (op == 1) {
            if (((s8 *) out)[-8] == 1) {
                out -= 2;
            }
            vtx = (u8 *) (src[1] + base);
            end = vtx + ((src[0] >> 8) & 0xFFF0);
            fl = D_800D3A08;
            do {
                x = *(s16 *) (vtx + 0);
                y = *(s16 *) (vtx + 2);
                z = *(s16 *) (vtx + 4);
                sz = x * m[2] + m[14] + y * m[6] + z * m[10];
                sx.f = x * m[0] + m[12] + y * m[4] + z * m[8];
                vtx += 0x10;
                fl[2] = !(0.0f <= sz);
                fl[0] = sx.u >> 31;
                fl[1] = !(fabsf(sz) <= fabsf(sx.f) * D_800D3A00);
                fl += 4;
            } while (vtx != end);
        } else if (op == -0xD) {
            if (lastLoad != NULL) {
                lastLoad[0] = 0;
                lastLoad[1] = 0;
            }
            lastLoad = out;
        } else if (op == -0x21) {
            return (Gfx *) out;
        }
        out[0] = src[0];
        out[1] = src[1];
        out += 2;
        src += 2;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D2DB0/func_150A55A0.s")
#endif

#ifndef NON_MATCHING /* P186: the loop of func_150A55A0 (folded into its C) */
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D2DB0/func_150A563C.s")
#endif

#ifdef NON_MATCHING
/* P34: C for the hand-written asm blob func_150A5858 .. func_150A5F98 (game_eu_D2DB0, 0x150A5858-0x150A606C).
 * The inner glabels func_150A595C / func_150A5A9C / func_150A5AF0 / func_150A5BE8 / func_150A5C70 / func_150A5C78 /
 * func_150A5C7C are loop labels, func_150A5D08 (state flush) and func_150A5F98 (corner outcode, arguments in
 * t0/t1/t2, result in t3) are private subroutines; nothing outside the blob references them.
 *
 * Level-geometry visibility walk + display-list filter.
 * 1. Clear the per-triangle visibility bytes [D_800D3668, D_800D3A8C).
 * 2. Walk the node tree D_800DC278 (pre-order; node: +0 s16 y0 (and the hide bits), +2 s16 y1 (+ visible bits),
 *    +4 s16 offset to the next node past this subtree, +6 u16 half size, +8 s16 x, +0xA s16 z, +0xC s16 offset to
 *    the first child (0 = leaf), +0xE leaf: triangle index list). Each node clears `mask` in +2; a node with
 *    (+0 & mask) or whose 8 box corners share an outcode bit is hidden with its whole subtree; otherwise +2 |= mask
 *    and, when all corners are inside, the subtree is not tested again. A visible leaf sets vis[i] = 1 for its
 *    triangle indices: byte b < 0x80: i = previous + b; else i = (b & 0x7F) << 8 | next byte. The asm keeps the
 *    previous index in $gp, starting with the caller's $gp (here 0).
 * 3. Copy the level DL `dl` to gdl up to G_ENDDL (not copied), returning the new gdl:
 *    tri commands (0x05: 1, 0x06: 2, 0x10-0x1F: 4 visibility bytes, read in sequence from vis) are kept when
 *    one of their triangles is visible, after flushing the deferred state; G_VTX, G_SETOTHERMODE_H (0xEF),
 *    G_SETCOMBINE, G_SETTIMG, G_TEXTURE, G_LOADBLOCK, G_LOADTLUT, G_SETTILE, G_SETTILESIZE are deferred (and dropped
 *    when equal to the last emitted one); G_RDPPIPESYNC / G_RDPLOADSYNC are dropped (the flush emits its own);
 *    everything else is copied. */
static s32 func_150A5858_outcode(f32 *m, f32 nearZ, f32 kx, f32 ky, s32 x, s32 y, s32 z) {
    f32 fx = x;
    f32 fy = y;
    f32 fz = z;
    f32 w;
    f32 sx;
    f32 sy;
    s32 out;
    union {
        f32 f;
        s32 i;
    } u;

    w = fx * m[2] + m[14] + fy * m[6] + fz * m[10];
    if (w <= nearZ) {
        out = 0x10;
    } else if (0.0f <= w) {
        out = 0x20;
    } else {
        out = 0;
    }
    sx = fx * m[0] + m[12] + fy * m[4] + fz * m[8];
    sy = fx * m[1] + m[13] + fy * m[5] + fz * m[9];
    if (!(w <= (sx < 0.0f ? -sx : sx) * kx)) {
        u.f = sx;
        out |= (u.i < 0) ? 8 : 2;
    }
    if (!(w <= (sy < 0.0f ? -sy : sy) * ky)) {
        u.f = sy;
        out |= (u.i < 0) ? 1 : 4;
    }
    return out;
}

/* c.eq.d on two 64-bit DL words */
static s32 func_150A5858_eqd(u32 ah, u32 al, u32 bh, u32 bl) {
    if (((ah & 0x7FF00000) == 0x7FF00000) && ((ah & 0xFFFFF) | al)) {
        return 0;
    }
    if (((bh & 0x7FF00000) == 0x7FF00000) && ((bh & 0xFFFFF) | bl)) {
        return 0;
    }
    if (!((ah & 0x7FFFFFFF) | al) && !((bh & 0x7FFFFFFF) | bl)) {
        return 1;
    }
    return ah == bh && al == bl;
}

typedef struct {
    u32 hi;
    u32 lo;
} func_150A5858_w;

#define W_NZ(v) (((v).hi | (v).lo) != 0)
#define W_EQ(a, b) ((a).hi == (b).hi && (a).lo == (b).lo)
#define W_EMIT(v) (out[0] = (v).hi, out[1] = (v).lo, out += 2)

Gfx *func_150A5858(s32 dl, Gfx *gdl, u8 *mtx, s32 arg3, s32 arg4, s32 mask) {
    f32 *m = (f32 *)mtx;
    u8 *vis;
    u8 *p;
    u8 *node;
    u8 *subEnd;
    u8 *s1;
    u8 *lst;
    s32 inside;
    s32 prev;
    s32 x, z, y0, y1, half;
    s32 c, andc, sum;
    s32 b;
    s32 idx;
    s32 off;
    f32 nearZ, kx, ky;
    /* 2: deferred DL state */
    func_150A5858_w T[48]; /* sp+0x58: settile pending [0..7], current [8..15]; settilesize pending [16..23], current [24..31] */
    func_150A5858_w cmd, vtx, oth, lastOth, comb, lastComb, timg, lastTimg, timg2, tex, lastTex, ldblk, tlut;
    func_150A5858_w zero;
    u32 *in;
    u32 *out;
    u8 *vp;
    s32 flags;
    s32 afterLoad;
    s32 op;
    u32 vb;
    s32 k;

    p = (u8 *)D_800D3668;
    do {
        ((u32 *)p)[0] = 0;
        ((u32 *)p)[1] = 0;
        p += 8;
    } while (p != (u8 *)D_800D3A8C);

    kx = -(&D_800D3A00)[0];
    ky = -(&D_800D3A00)[1];
    nearZ = D_800D3A90;
    node = D_800DC278;
    vis = (u8 *)D_800D3668;
    prev = 0;
    inside = 4;
    subEnd = NULL;
    while (1) {
        if (!((s32)node < (s32)subEnd)) {
            inside = 4;
        }
        x = *(s16 *)(node + 8);
        y1 = *(s16 *)(node + 2) & ~mask;
        *(s16 *)(node + 2) = y1;
        y0 = *(s16 *)(node + 0);
        if (y0 & mask) {
            goto hidden;
        }
        z = *(s16 *)(node + 0xA);
        if (inside != 1) {
            half = *(u16 *)(node + 6);
            c = func_150A5858_outcode(m, nearZ, kx, ky, x + half, y0, z + half);
            andc = c;
            sum = c;
            c = func_150A5858_outcode(m, nearZ, kx, ky, x + half, y1, z + half);
            sum += c;
            if (c == 0 && sum != 0) {
                goto visible;
            }
            andc &= c;
            c = func_150A5858_outcode(m, nearZ, kx, ky, x - half, y0, z + half);
            sum += c;
            if (c == 0 && sum != 0) {
                goto visible;
            }
            andc &= c;
            c = func_150A5858_outcode(m, nearZ, kx, ky, x - half, y1, z + half);
            sum += c;
            if (c == 0 && sum != 0) {
                goto visible;
            }
            andc &= c;
            c = func_150A5858_outcode(m, nearZ, kx, ky, x + half, y0, z - half);
            sum += c;
            if (c == 0 && sum != 0) {
                goto visible;
            }
            andc &= c;
            c = func_150A5858_outcode(m, nearZ, kx, ky, x + half, y1, z - half);
            sum += c;
            if (c == 0 && sum != 0) {
                goto visible;
            }
            andc &= c;
            c = func_150A5858_outcode(m, nearZ, kx, ky, x - half, y0, z - half);
            sum += c;
            if (c == 0 && sum != 0) {
                goto visible;
            }
            andc &= c;
            c = func_150A5858_outcode(m, nearZ, kx, ky, x - half, y1, z - half);
            andc &= c;
            sum += c;
            if (andc != 0) {
                goto hidden;
            }
            if (sum == 0) {
                subEnd = node + *(s16 *)(node + 4);
                inside = 1;
            }
        }
    visible:
        *(s16 *)(node + 2) = y1 | mask;
        off = *(s16 *)(node + 0xC);
        if (off != 0) {
            node += off;
            continue;
        }
        lst = node + 0xE;
        while ((b = *lst++) != 0) {
            idx = b & 0x7F;
            if (b == idx) {
                idx += prev;
            } else {
                idx = (idx << 8) | *lst++;
            }
            prev = idx;
            if (vis[idx] == 0) {
                vis[idx] = 1;
            }
        }
        goto next;
    hidden:
        {
            u8 *end = node + *(s16 *)(node + 4);

            s1 = node;
            while (1) {
                *(s16 *)(s1 + 2) &= ~mask;
                off = *(s16 *)(s1 + 0xC);
                if (off != 0) {
                    s1 += off;
                    continue;
                }
                off = *(s16 *)(s1 + 4);
                s1 += off;
                if (off == 0) {
                    goto walked;
                }
                if (end == s1) {
                    break;
                }
            }
        }
    next:
        off = *(s16 *)(node + 4);
        node += off;
        if (off == 0) {
            break;
        }
    }
walked:

    for (k = 0; k < 32; k++) {
        T[k].hi = T[k].lo = 0;
    }
    zero.hi = zero.lo = 0;
    vtx = oth = lastOth = comb = lastComb = timg = lastTimg = timg2 = tex = lastTex = ldblk = tlut = zero;
    vp = (u8 *)D_800D3668;
    flags = 0;
    afterLoad = 0;
    in = (u32 *)dl;
    out = (u32 *)gdl;
    while (1) {
        cmd.hi = in[0];
        cmd.lo = in[1];
        in += 2;
        op = (s8)(cmd.hi >> 24);
        if (op >= 0x10 && op < 0x20) {
            vb = (vp[0] << 24) | (vp[1] << 16) | (vp[2] << 8) | vp[3];
            afterLoad = 0;
            vp += 4;
        } else if (op == 1) {
            vtx = cmd;
            flags |= 1;
            continue;
        } else if (op == 5) {
            vb = (s8)vp[0];
            afterLoad = 0;
            vp += 1;
        } else if (op == 6) {
            afterLoad = 0;
            vb = ((s8)vp[0] << 8) | (s8)vp[1];
            vp += 2;
        } else {
            if (op == -0xB || op == -0xE) { /* G_SETTILE / G_SETTILESIZE */
                k = (op == -0xB ? 0 : 16) + ((u8 *)in)[-4];
                flags = 0x200;
                T[k] = W_EQ(cmd, T[k + 8]) ? zero : cmd;
            } else if (op == -0xD) { /* G_LOADBLOCK */
                ldblk = cmd;
                afterLoad = 1;
                tlut = zero;
                flags |= 2;
            } else if (op == -0x11) { /* G_RDPSETOTHERMODE */
                oth = cmd;
                flags |= 0x20;
                if (W_EQ(oth, lastOth)) {
                    oth = zero;
                    flags ^= 0x20;
                }
            } else if (op == -0x4) { /* G_SETCOMBINE */
                comb = cmd;
                flags |= 0x40;
                if (W_EQ(comb, lastComb)) {
                    comb = zero;
                    flags ^= 0x40;
                }
            } else if (op == -0x3) { /* G_SETTIMG */
                if (afterLoad != 0) {
                    timg2 = cmd;
                } else {
                    timg = cmd;
                    if (W_EQ(timg, lastTimg)) {
                        timg = zero;
                    }
                }
            } else if (op == -0x29) { /* G_TEXTURE */
                tex = cmd;
                flags |= 0x80;
                if (func_150A5858_eqd(tex.hi, tex.lo, lastTex.hi, lastTex.lo)) {
                    tex = zero;
                    flags ^= 0x80;
                }
            } else if (op == -0x10) { /* G_LOADTLUT */
                tlut = cmd;
            } else if (op == -0x19 || op == -0x1A) { /* G_RDPPIPESYNC / G_RDPLOADSYNC: dropped */
            } else if (op == -0x21) { /* G_ENDDL */
                return (Gfx *)out;
            } else {
                W_EMIT(cmd);
            }
            continue;
        }
        /* triangle command */
        if ((vb & 0x01010101) == 0) {
            continue;
        }
        if (flags != 0) {
            /* func_150A5D08 */
            if (flags & 0xFFFE) {
                out[0] = 0xE7000000;
                out[1] = 0;
                out += 2;
            }
            if (W_NZ(oth)) {
                W_EMIT(oth);
                lastOth = oth;
            }
            if (!func_150A5858_eqd(tex.hi, tex.lo, 0, 0)) {
                W_EMIT(tex);
                lastTex = tex;
            }
            if (W_NZ(comb)) {
                W_EMIT(comb);
                lastComb = comb;
            }
            if (W_NZ(timg)) {
                W_EMIT(timg);
                lastTimg = timg;
            }
            for (k = 0; k < 8; k++) {
                if (W_NZ(T[k])) {
                    W_EMIT(T[k]);
                    T[k + 8] = T[k];
                    T[k] = zero;
                }
                if (W_NZ(T[k + 16])) {
                    W_EMIT(T[k + 16]);
                    T[k + 24] = T[k + 16];
                    T[k + 16] = zero;
                }
            }
            if (W_NZ(ldblk)) {
                W_EMIT(ldblk);
            }
            if (W_NZ(timg2)) {
                W_EMIT(timg2);
                lastTimg = timg2;
            }
            if (W_NZ(tlut)) {
                out[0] = 0xE6000000;
                out[1] = 0;
                out += 2;
                W_EMIT(tlut);
            }
            if (W_NZ(vtx)) {
                W_EMIT(vtx);
            }
            oth = tex = comb = timg = ldblk = tlut = timg2 = vtx = zero;
            flags = 0;
        }
        W_EMIT(cmd);
    }
}
#undef W_NZ
#undef W_EQ
#undef W_EMIT
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D2DB0/func_150A5858.s")
#endif
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D2DB0/func_150A5BE8.s")
#endif

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D2DB0/func_150A5D08.s")
#endif

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D2DB0/func_150A5F98.s")
#endif
