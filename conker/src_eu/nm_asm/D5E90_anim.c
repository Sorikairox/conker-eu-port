/*
 * NON_MATCHING C for the skeleton / animation evaluator of the raw asm file asm/D5E90.s (P51):
 * anim_eval_joint_matrices with its private helpers func_150A8680 (no animation: copy the root matrix),
 * func_150A8EF8 .. func_150A93A0 (key-frame decoder + per-object joint adjustments), func_150A8DF8 (Euler angles
 * to quaternion), func_150A88F4 .. func_150A8DF4 (blend of two animations) and func_150A94E0 .. func_150A99BC
 * (one animation), func_150A98E0 / func_150A99BC / func_150A9A4C (joint matrices times parent matrices).
 *
 * Built only with NON_MATCHING=1 (Makefile: NM_ASM_C_FUNCS_D5E90 line for this file, and the linker script line
 * that places D5E90_anim.c.o); the asm copy of anim_eval_joint_matrices is weakened so this definition wins.
 * The file must not contain the word G-L-O-B-A-L_ASM (see the Makefile note on nm_asm files).
 *
 * Float operations are written in the asm's order (no reassociation): each line rounds like one mul.s / add.s.
 * The asm keeps its work tables below the stack pointer; here they are one stack array laid out the same way
 * (g_anim_trans_table = g_anim_trans_free at the bottom, then g_anim_scale_table, then g_anim_euler_table, each 12 * count bytes), so the
 * globals that point at them are comparable across the tables but not with the asm's stack addresses.
 */
#include <ultra64.h>

#include "functions.h"
#include "variables.h"

extern u8 *g_anim_joint_mtx_arena;  /* joint matrix arena (first matrix of this model); was D_800888E0 */
extern s32 **g_anim_arena_ptr_slot; /* where the arena pointer lives (arg0); advanced by n matrices; was D_800888E4 */
extern u8 *g_anim_skeleton;  /* skeleton: 16-byte entries {parent slot, matrix slot, channel, -, f32 x, y, z}; was D_800888E8 */
extern s16 *g_anim_last_trans_offsets; /* translation offsets of the last decoded animation (NULL: none); was D_800888EC */
extern s32 g_anim_decode_mode;  /* decoder mode: 0 = animation 1 (state +0x8 / +0x18), 4 = animation 2 (+0xC / +0x1C); was D_800888F0 */
extern s32 g_anim_root_motion;  /* root motion (z channel with descriptor flag 0x40), 1/1024 units; was D_800888F4 */
extern s32 g_anim_root_motion_total;  /* root motion total (descriptor +0xA); was D_800888F8 */
extern s32 g_anim_root_motion_a;  /* root motion of animation 1 while blending (g_anim_blend_next_keys); was D_800888FC; was D_80088904 */
extern s32 g_anim_root_motion_end;  /* root motion end value (set past the last key frame); was D_80088900 */
extern s32 g_anim_blend_next_keys;  /* blend the current and the next key-frame pair (state +0x47 & 0x10, no animation 2); was D_80088904 */
extern s16 *g_anim_trans_free; /* next free translation-offset table; was D_80088908 */
extern s16 *g_anim_decode_scales; /* scale table of the current decode; was D_8008890C */
extern s16 *g_anim_euler_table; /* Euler angle table (3 x s16 per channel), animation 1 then animation 2; was D_80088910 */
extern s16 *g_anim_scale_table; /* scale table (3 x u16 per channel, 0 = 1.0, 0x4000 = 1.0); was D_80088914 */
extern s16 *g_anim_trans_table; /* translation offset table (3 x s16 per channel, 1/16 units); was D_80088918 */
extern s32 g_anim_channel0_angle; /* was D_8008891C */ /* output: descriptor flag 0x20: angle 1 of channel 0 (object +0x7C); also the base of
                         * the per-joint callback table {void (*)(void), flag} indexed by remap[slot] * 8 */
extern s32 g_anim_key_fraction;  /* key-frame fraction (0..1024) of a decode with descriptor flag 0x10; was D_80088920 */
extern f32 g_anim_sine_table[]; /* sine table: 513 entries over a quarter turn; was D_150AA11C */

/* The animation state (object +0x2D0) */
#define ANIM_F32(a, o) (*(f32 *)((u8 *)(a) + (o)))
#define ANIM_S16(a, o) (*(s16 *)((u8 *)(a) + (o)))
#define ANIM_PTR(a, o) (*(u8 **)((u8 *)(a) + (o)))

/* The descriptors (state +0x40 / +0x210) are animation headers read raw from the ROM by anim_start_entry, and the
 * key-frame stream is raw ROM data (anim_copy_keyframes): both are read as big-endian bytes (on the N64 the same as the
 * asm's lh / lhu / ldl / ldr; in a little-endian port they stay correct as long as the loader does not swap them). */
#define DESC_U16(p) ((u16)(((p)[0] << 8) | (p)[1]))
#define DESC_S16(p) ((s16)(((p)[0] << 8) | (p)[1]))
#define BE_S16(p) ((s16)(((p)[0] << 8) | (p)[1]))

/* work tables (on the stack, like the asm's below its frame): 3 tables of 12 * count bytes, then the asm's
 * 0x100-byte gap. Sized for count <= 72 (header byte 1 = joints + 1; obj_build_model_instance's remap buffer has 0x44 slots,
 * Conker's animations have 29); the asm sizes them by the count. */
#define NM_ANIM_MAXCNT 72

/* floor.w.s then cvt.s.w */
static f32 nmAnimFloor(f32 x) {
    s32 i = (s32)x;

    if ((f32)i > x) {
        i--;
    }
    return (f32)i;
}

/* cvt.w.s in round-to-nearest-even mode, for 0 <= x < 2^22 */
static s32 nmAnimRound(f32 x) {
    f32 t = x + 8388608.0f;

    t = t - 8388608.0f;
    return (s32)t;
}

/* bits [pos, pos + n) of the big-endian bit stream at p (n = 1..15); the asm keeps a 64-bit window that it
 * reloads whole bytes further on when the field would cross its end, which reads the same bits */
static s32 nmAnimBits(u8 *p, s32 pos, s32 n) {
    u8 *q = p + (pos >> 3);
    u32 w = (q[0] << 16) | (q[1] << 8) | q[2];

    return (w >> (24 - (pos & 7) - n)) & ((1 << n) - 1);
}

/*
 * func_150A8EF8: decode one animation at a frame time into the angle table *rotp and the scale table *sclp (both
 * advanced), the translation offsets (descriptor flag 0x80, g_anim_trans_free) and the root position out[0..2]
 * (1/1024 units, y raised by height). Key frames: data and data + next (the next key frame), mixed by the frame
 * fraction w / 1024. Then the per-object adjustments of buf (func_150A939C) on what this call wrote.
 */
static void nmAnimDecode(s32 mode, u8 *anim, u8 *desc, u8 *data, s32 next, f32 time, s16 **rotp, s16 **sclp,
                         f32 *out, s32 height, u16 *buf) {
    s16 *rot = *rotp;
    s16 *scl = *sclp;
    s16 *rot0 = rot;
    s16 *tr;
    s16 *t;
    s16 *end;
    u8 *p0;
    u8 *p1;
    u8 *rd;
    u8 *mask;
    s32 cnt, w, n, pos, a, b, d, v, k, bit;
    u32 fl;
    f32 last, len, base;

    g_anim_decode_mode = mode;
    g_anim_decode_scales = scl;
    if (data == NULL) {
        data = (u8 *)g_anim_euler_table;
    }
    rd = desc + 0xA;
    cnt = desc[1];
    p0 = data;
    p1 = data + next;

    /* frame fraction */
    last = ANIM_F32(anim, g_anim_decode_mode + 0x18) - 1.0f;
    if (!(last <= time)) {
        len = (f32)(desc[8] + 1);
        base = last / len;
        base = nmAnimFloor(base);
        base = base * len;
        if (!(time < base)) {
            time = time - base;
            len = last - base;
        }
        time = time / len;
    }
    len = nmAnimFloor(time);
    len = time - len;
    w = nmAnimRound(len * 1024.0f);
    if (desc[7] & 0x10) {
        g_anim_key_fraction = w;
        p1 = p0;
        w = 0;
    }

    fl = desc[7];
    rd += (fl & 0x40) >> 5;
    rd += (fl & 0x20) >> 4;
    tr = NULL;
    if (fl & 0x80) {
        /* translation offsets: one bit per channel joint (first 64), 3 x s16 per set bit from the stream */
        t = g_anim_trans_free;
        tr = t;
        end = t + (cnt - 1) * 3;
        mask = rd;
        rd += (((u32)(cnt - 1 + 15)) >> 4) << 1;
        bit = 0;
        do {
            if (bit < 64 && (mask[bit >> 3] & (0x80 >> (bit & 7)))) {
                for (k = 0; k < 3; k++) {
                    a = BE_S16(p0 + 2 * k);
                    b = BE_S16(p1 + 2 * k);
                    t[k] = (((b - a) * w) >> 10) + a;
                }
                p0 += 6;
                p1 += 6;
            } else {
                /* sdl / sdr: 8 bytes */
                t[0] = 0;
                t[1] = 0;
                t[2] = 0;
                t[3] = 0;
            }
            t += 3;
            bit++;
        } while (t != end);
        if (g_anim_decode_mode == 0) {
            g_anim_trans_free = t;
        }
    }
    g_anim_last_trans_offsets = tr;

    /* root position: bases desc[0] / [2] / [4] << 12 plus fields of desc[6] >> 4, desc[6] & 0xF, desc[7] & 0xF bits */
    pos = 0;
    n = desc[6] >> 4;
    v = (s8)desc[0] << 12;
    if (n != 0) {
        a = nmAnimBits(p0, pos, n);
        b = nmAnimBits(p1, pos, n);
        pos += n;
        v += ((a << 10) + (b - a) * w) >> 5;
    }
    out[0] = (f32)v;
    n = desc[6] & 0xF;
    v = (s8)desc[2] << 12;
    if (n != 0) {
        a = nmAnimBits(p0, pos, n);
        b = nmAnimBits(p1, pos, n);
        pos += n;
        v += ((a << 10) + (b - a) * w) >> 5;
    }
    v += height << 12;
    out[1] = (f32)v;
    n = desc[7] & 0xF;
    v = (s8)desc[4] << 12;
    if (n != 0) {
        a = nmAnimBits(p0, pos, n);
        b = nmAnimBits(p1, pos, n);
        pos += n;
        d = b - a;
        if (!(desc[7] & 0x40)) {
            v += ((a << 10) + d * w) >> 5;
        } else {
            /* root motion: the z channel goes to g_anim_root_motion instead (animation 1 only) */
            v = 0;
            if (g_anim_decode_mode == 0) {
                g_anim_root_motion_total = DESC_S16(desc + 0xA);
                if (ANIM_F32(anim, g_anim_decode_mode + 0x18) - 1.0f < ANIM_F32(anim, g_anim_decode_mode + 8)) {
                    g_anim_root_motion_end = DESC_S16(desc + 0xA);
                    d = g_anim_root_motion_end - a;
                }
                g_anim_root_motion = (a << 10) + d * w;
            }
        }
    }
    out[2] = (f32)v;

    /* channels: 3 angles per joint after the root; descriptor u16 = base & 0xFFF0 | bit width, 0x10: a scale follows */
    k = (cnt - 1) * 3;
    do {
        n = DESC_U16(rd);
        v = n & 0xFFF0;
        n &= 0xF;
        if (n != 0) {
            a = nmAnimBits(p0, pos, n);
            b = nmAnimBits(p1, pos, n);
            pos += n;
            d = (s32)((u32)(b - a) << 21) >> 21;
            v += (a + ((d * w) >> 10)) << 5;
        }
        *rot = v;
        if (v & 0x10) {
            n = DESC_U16(rd + 2);
            rd += 4;
            rot++;
            v = n & 0xFFF0;
            n &= 0xF;
            if (n != 0) {
                a = nmAnimBits(p0, pos, n);
                b = nmAnimBits(p1, pos, n);
                pos += n;
                v += ((a << 7) + (((b - a) * w) >> 3)) >> 2;
            }
            *scl++ = v;
        } else {
            *scl++ = 0;
            rot++;
            rd += 2;
        }
    } while (--k != 0);

    /* func_150A939C: per-object adjustments {u16 byte offset, s16 value} up to 0x1000: offsets below 0x800 add to
     * the angles, others scale the scale table (0 = 0x4000) by value / 0x4000 */
    for (;;) {
        n = buf[0];
        if (n == 0x1000) {
            break;
        }
        if (n < 0x800) {
            t = (s16 *)((u8 *)rot0 + n);
            *t += (s16)buf[1];
        } else {
            t = (s16 *)((u8 *)g_anim_decode_scales + (n & 0x7FF));
            v = *t;
            if (v == 0) {
                v = 0x4000;
            }
            *t = (u32)(v * (s16)buf[1]) >> 14;
        }
        buf += 2;
    }
    *rotp = rot;
    *sclp = scl;
}

/* func_150A8DF8: half-angle sine / cosine of a 16-bit angle (the asm's sign test picks the quarter) */
static void nmAnimHalfSinCos(s16 h, f32 *s, f32 *c) {
    s32 i = ((u32)(s32)h >> 6) & 0x1FF;
    f32 t;

    if (h >= 0) {
        *s = g_anim_sine_table[i];
        *c = g_anim_sine_table[0x200 - i];
    } else {
        t = g_anim_sine_table[i];
        *s = g_anim_sine_table[0x200 - i];
        *c = 0.0f - t;
    }
}

/* func_150A8DF8 and its caller: Euler angles (x, y, z halfwords) to a quaternion (w, x, y, z) */
static void nmAnimQuat(s16 *r, f32 *q) {
    f32 sx, cx, sy, cy, sz, cz, a, b, c, d;

    nmAnimHalfSinCos(r[0], &sx, &cx);
    nmAnimHalfSinCos(r[1], &sy, &cy);
    nmAnimHalfSinCos(r[2], &sz, &cz);
    a = cx * cy;
    b = cx * sy;
    c = sx * cy;
    d = sx * sy;
    q[0] = a * cz + d * sz;
    q[1] = c * cz - b * sz;
    q[2] = b * cz + c * sz;
    q[3] = a * sz - d * cz;
}

/* full-turn sine / cosine of a 16-bit angle (11-bit table index, 2 bits of quarter) */
static void nmAnimSinCos(u16 h, f32 *s, f32 *c) {
    s32 q = (h >> 5) & 0x600;
    s32 i = (h >> 5) & 0x1FF;
    f32 t;

    if (q == 0x600) {
        *c = g_anim_sine_table[i];
        t = g_anim_sine_table[0x200 - i];
        *s = 0.0f - t;
    } else if (q == 0x400) {
        t = g_anim_sine_table[i];
        *s = 0.0f - t;
        t = g_anim_sine_table[0x200 - i];
        *c = 0.0f - t;
    } else if (q == 0x200) {
        t = g_anim_sine_table[i];
        *c = 0.0f - t;
        *s = g_anim_sine_table[0x200 - i];
    } else {
        *s = g_anim_sine_table[i];
        *c = g_anim_sine_table[0x200 - i];
    }
}

/* func_150A9A4C: joint matrix l (rows 0-2 + translation; column 3 untouched) times the parent p[12] */
static void nmAnimMtxMul(f32 *l, f32 *p) {
    f32 a, b, c;

    a = l[0];
    b = l[1];
    c = l[2];
    l[0] = (a * p[0] + b * p[3]) + c * p[6];
    l[1] = (c * p[7] + a * p[1]) + b * p[4];
    l[2] = (a * p[2] + b * p[5]) + c * p[8];
    a = l[4];
    b = l[5];
    c = l[6];
    l[4] = (a * p[0] + b * p[3]) + c * p[6];
    l[5] = (c * p[7] + a * p[1]) + b * p[4];
    l[6] = (a * p[2] + b * p[5]) + c * p[8];
    a = l[8];
    b = l[9];
    c = l[10];
    l[8] = (a * p[0] + b * p[3]) + c * p[6];
    l[9] = (c * p[7] + a * p[1]) + b * p[4];
    l[10] = (a * p[2] + b * p[5]) + c * p[8];
    a = l[12];
    b = l[13];
    c = l[14];
    l[12] = ((a * p[0] + p[9]) + b * p[3]) + c * p[6];
    l[13] = ((a * p[1] + p[10]) + b * p[4]) + c * p[7];
    l[14] = ((a * p[2] + p[11]) + b * p[5]) + c * p[8];
}

/* rows 0-2 and the translation of a 4x4 float matrix */
static void nmAnimLoad12(f32 *p, f32 *m) {
    p[0] = m[0];
    p[1] = m[1];
    p[2] = m[2];
    p[3] = m[4];
    p[4] = m[5];
    p[5] = m[6];
    p[6] = m[8];
    p[7] = m[9];
    p[8] = m[10];
    p[9] = m[12];
    p[10] = m[13];
    p[11] = m[14];
}

/* translation of a joint: bone offset (skeleton +4) plus the animation's offset / 16 */
static void nmAnimTrans(f32 *mt, u8 *e, s16 *tt) {
    f32 x = *(f32 *)(e + 4);
    f32 y = *(f32 *)(e + 8);
    f32 z = *(f32 *)(e + 0xC);

    if (tt != NULL) {
        x = x + (f32)tt[0] * 0.0625f;
        y = y + (f32)tt[1] * 0.0625f;
        z = z + (f32)tt[2] * 0.0625f;
        mt[12] = x;
        mt[13] = y;
        mt[14] = z;
    } else {
        ((s32 *)mt)[12] = *(s32 *)(e + 4);
        ((s32 *)mt)[13] = *(s32 *)(e + 8);
        ((s32 *)mt)[14] = *(s32 *)(e + 0xC);
    }
}

/*
 * anim_eval_joint_matrices: the joint matrices of a model instance.
 * arena: &g_obj_mtx_next (advanced by n matrices); m: root matrix; anim: animation state (object +0x2D0; 0: copy m
 * into one matrix, func_150A8680); skel: skeleton entries (g_model_skeletons[id]); n: joints; buf: per-object angle /
 * scale adjustments (obj_adjust_list_build); remap: per-slot callback index (model header +0x29) or NULL; height: added
 * to the root y.
 * Animation 1 alone, or blended (quaternion slerp-free nlerp) with the next key-frame pair (g_anim_blend_next_keys) or with
 * animation 2 (+0x3C weight / 1024). Each joint matrix is (scale x rotation, bone offset) times its parent's;
 * column 3 of the matrices is not written.
 */
/* was func_150A86B0 */
void anim_eval_joint_matrices(s32 *arena, f32 (*m)[4], s32 anim, s32 skel, s32 n, u8 *arg5, u8 *remap, s32 height) {
    u8 *a = (u8 *)anim;
    u16 *buf = (u16 *)arg5;
    u8 *e;
    u8 *desc;
    s16 *rot;
    s16 *scl;
    s16 *rotB;
    s16 *sclB;
    s16 *sA;
    s16 *sEnd;
    s16 *tA;
    s16 *tB;
    s16 *t;
    s16 *tEnd;
    s16 *tr;
    f32 *mt;
    f32 root[3];
    f32 rootA[3];
    f32 p[12];
    f32 qa[4];
    f32 qb[4];
    f32 r0, r1, r2, r3, dot, k, wf, iw, dx, dy, dz, f;
    f32 xx, xy, xz, wx, wy, wz, yy, yz, zz;
    f32 sx, cx, sy, cy, sz, cz, s6, s7, s8, s9;
    f32 m0, m1, m2, m4, m5, m6, m8, m9, m10;
    s32 i, cnt, w, sa, sb, v, ch, j;
    u32 *cb;
    u8 *idx;
    s16 work[3 * 6 * NM_ANIM_MAXCNT + 0x80];

    g_anim_arena_ptr_slot = (s32 **)arena;
    g_anim_joint_mtx_arena = (u8 *)*arena;
    g_anim_root_motion_total = 0;
    g_anim_blend_next_keys = 0;
    g_anim_root_motion_end = 0;
    if (a == NULL) {
        /* func_150A8680 */
        for (i = 0; i < 16; i++) {
            ((s32 *)g_anim_joint_mtx_arena)[i] = ((s32 *)m)[i];
        }
        *g_anim_arena_ptr_slot = (s32 *)(g_anim_joint_mtx_arena + 0x40);
        return;
    }
    if (ANIM_S16(a, 0x3C) <= 0) {
        g_anim_blend_next_keys = a[0x47] & 0x10;
    }
    cnt = a[0x41];
    g_anim_trans_table = work;
    g_anim_trans_free = work;
    g_anim_scale_table = work + 6 * cnt;
    g_anim_euler_table = work + 12 * cnt;
    g_anim_skeleton = (u8 *)skel;

    rot = g_anim_euler_table;
    scl = g_anim_scale_table;
    nmAnimDecode(0, a, a + 0x40, ANIM_PTR(a, 0x30), a[0x38], ANIM_F32(a, 8), &rot, &scl, root, height, buf);

    if (g_anim_blend_next_keys != 0) {
        /* the next key-frame pair, weight g_anim_key_fraction */
        g_anim_root_motion_a = g_anim_root_motion;
        rootA[0] = root[0];
        rootA[1] = root[1];
        rootA[2] = root[2];
        rotB = rot;
        sclB = scl;
        desc = a + 0x40;
        nmAnimDecode(0, a, desc, ANIM_PTR(a, 0x30) + a[0x38], 0, ANIM_F32(a, 8), &rot, &scl, root, height, buf);
        w = g_anim_key_fraction;
        if (g_anim_root_motion_total != 0) {
            v = g_anim_root_motion_a;
            if (g_anim_root_motion_end == 0) {
                v = (((g_anim_root_motion - g_anim_root_motion_a) * w) >> 10) + g_anim_root_motion_a;
            }
            g_anim_root_motion = v;
        }
    } else if (ANIM_S16(a, 0x3C) > 0) {
        /* animation 2, weight +0x3C */
        rootA[0] = root[0];
        rootA[1] = root[1];
        rootA[2] = root[2];
        rotB = rot;
        sclB = scl;
        desc = a + 0x210;
        nmAnimDecode(4, a, desc, ANIM_PTR(a, 0x34), a[0x39], ANIM_F32(a, 0xC), &rot, &scl, root, height, buf);
        w = ANIM_S16(a, 0x3C);
    } else {
        /* func_150A94E0: one animation */
        e = g_anim_skeleton;
        rot = g_anim_euler_table;
        v = a[0x47] & 0x20;
        if (v != 0) {
            v = rot[1];
        }
        g_anim_channel0_angle = v;
        tr = g_anim_last_trans_offsets;
        sA = g_anim_scale_table;
        i = n;
        do {
            mt = (f32 *)(g_anim_joint_mtx_arena + (e[1] << 6));
            ch = e[2] * 3;
            nmAnimTrans(mt, e, tr != NULL ? tr + ch : NULL);
            nmAnimSinCos(rot[ch], &sx, &cx);
            nmAnimSinCos(rot[ch + 2], &sz, &cz);
            s6 = sx * sz;
            s7 = cx * sz;
            s8 = sx * cz;
            s9 = cx * cz;
            nmAnimSinCos(rot[ch + 1], &sy, &cy);
            m0 = cy * cz;
            m1 = cy * sz;
            m2 = 0.0f - sy;
            if ((u16)sA[ch] != 0) {
                f = (f32)(u16)sA[ch] * (1.0f / 16384.0f);
                m0 = m0 * f;
                m1 = m1 * f;
                m2 = m2 * f;
            }
            mt[0] = m0;
            mt[1] = m1;
            mt[2] = m2;
            m4 = s8 * sy - s7;
            m5 = s6 * sy + s9;
            m6 = sx * cy;
            if ((u16)sA[ch + 1] != 0) {
                f = (f32)(u16)sA[ch + 1] * (1.0f / 16384.0f);
                m4 = m4 * f;
                m5 = m5 * f;
                m6 = m6 * f;
            }
            mt[4] = m4;
            mt[5] = m5;
            mt[6] = m6;
            m8 = s9 * sy + s6;
            m9 = s7 * sy - s8;
            m10 = cx * cy;
            if ((u16)sA[ch + 2] != 0) {
                f = (f32)(u16)sA[ch + 2] * (1.0f / 16384.0f);
                m8 = m8 * f;
                m9 = m9 * f;
                m10 = m10 * f;
            }
            mt[8] = m8;
            mt[9] = m9;
            mt[10] = m10;
            e += 0x10;
        } while (e != g_anim_skeleton + (n << 4));
        goto compose;
    }

    /* func_150A88F4: blend animation 1 (tables at g_anim_euler_table / g_anim_scale_table, root rootA) with B (rotB / sclB, root) */
    sA = g_anim_scale_table;
    e = g_anim_skeleton;
    v = desc[7] & 0x20;
    if (v != 0) {
        v = rotB[1];
    }
    g_anim_channel0_angle = v;
    wf = (f32)w / 1024.0f;
    iw = 1.0f - wf;
    dx = rootA[0] - root[0];
    dy = rootA[1] - root[1];
    dz = rootA[2] - root[2];
    dx = dx * iw;
    dy = dy * iw;
    dz = dz * iw;

    /* scales (0 = 0x4000 when the other one is not 0) */
    t = sclB;
    sEnd = sclB + 3 * n;
    do {
        sb = (u16)*t++;
        sa = (u16)*sA++;
        if (sb == 0) {
            if (sa == 0) {
                continue;
            }
            sb = 0x4000;
        } else if (sa == 0) {
            sa = 0x4000;
        }
        sA[-1] = (((sb - sa) * w) >> 10) + sa;
    } while (t != sEnd);

    /* translation offsets */
    tA = g_anim_trans_table;
    t = tA;
    tEnd = tA + 3 * n;
    tB = g_anim_last_trans_offsets;
    tr = g_anim_trans_table;
    if (tA == g_anim_trans_free) {
        if (tB == NULL) {
            tr = NULL;
        } else {
            do {
                *t = (*t * w) >> 10;
                t++;
            } while (t != tEnd);
        }
    } else if (tB == NULL) {
        do {
            v = *t;
            *t = ((-v * w) >> 10) + v;
            t++;
        } while (t != tEnd);
    } else {
        do {
            *t = (((*tB - *tA) * w) >> 10) + *tA;
            tA++;
            tB++;
            t++;
        } while (t != tEnd);
    }
    root[0] = dx + root[0];
    root[1] = dy + root[1];
    root[2] = dz + root[2];

    sA = g_anim_scale_table;
    rot = g_anim_euler_table;
    i = n;
    do {
        ch = e[2] * 3;
        nmAnimQuat(rot + ch, qa);
        nmAnimQuat(rotB + ch, qb);
        dot = ((qa[0] * qb[0] + qa[1] * qb[1]) + qa[2] * qb[2]) + qa[3] * qb[3];
        qa[0] = qa[0] * iw;
        qa[1] = qa[1] * iw;
        qa[2] = qa[2] * iw;
        qa[3] = qa[3] * iw;
        if (dot < 0.0f) {
            qb[0] = 0.0f - qb[0];
            qb[1] = 0.0f - qb[1];
            qb[2] = 0.0f - qb[2];
            qb[3] = 0.0f - qb[3];
        }
        r0 = qa[0] + qb[0] * wf;
        r1 = qa[1] + qb[1] * wf;
        r2 = qa[2] + qb[2] * wf;
        r3 = qa[3] + qb[3] * wf;
        k = ((r0 * r0 + r1 * r1) + r2 * r2) + r3 * r3;
        k = 2.0f / k;
        f = r1 * k;
        xx = r1 * f;
        wx = r0 * f;
        f = r2 * k;
        wy = r0 * f;
        xy = r1 * f;
        yy = r2 * f;
        f = r3 * k;
        wz = r0 * f;
        xz = r1 * f;
        yz = r2 * f;
        zz = r3 * f;
        mt = (f32 *)(g_anim_joint_mtx_arena + (e[1] << 6));
        m0 = 1.0f - (yy + zz);
        m1 = xy + wz;
        m2 = xz - wy;
        m4 = xy - wz;
        m5 = 1.0f - (xx + zz);
        m6 = yz + wx;
        m8 = xz + wy;
        m9 = yz - wx;
        m10 = 1.0f - (xx + yy);
        if ((u16)sA[ch] != 0) {
            f = (f32)(u16)sA[ch] * (1.0f / 16384.0f);
            m0 = m0 * f;
            m1 = m1 * f;
            m2 = m2 * f;
        }
        mt[0] = m0;
        mt[1] = m1;
        mt[2] = m2;
        if ((u16)sA[ch + 1] != 0) {
            f = (f32)(u16)sA[ch + 1] * (1.0f / 16384.0f);
            m4 = m4 * f;
            m5 = m5 * f;
            m6 = m6 * f;
        }
        mt[4] = m4;
        mt[5] = m5;
        mt[6] = m6;
        if ((u16)sA[ch + 2] != 0) {
            f = (f32)(u16)sA[ch + 2] * (1.0f / 16384.0f);
            m8 = m8 * f;
            m9 = m9 * f;
            m10 = m10 * f;
        }
        mt[8] = m8;
        mt[9] = m9;
        mt[10] = m10;
        nmAnimTrans(mt, e, tr != NULL ? tr + ch : NULL);
        e += 0x10;
    } while (--i != 0);

compose:
    /* func_150A98E0: the first joint's parent is m moved by the root position / 1024, the others' are their
     * parent slot's (already final) matrix; remap[slot] != 0 calls the callback of that table entry */
    root[0] = root[0] * (1.0f / 1024.0f);
    root[1] = root[1] * (1.0f / 1024.0f);
    root[2] = root[2] * (1.0f / 1024.0f);
    nmAnimLoad12(p, (f32 *)m);
    p[9] = p[9] + ((root[0] * p[0] + root[1] * p[3]) + root[2] * p[6]);
    p[10] = p[10] + ((root[0] * p[1] + root[1] * p[4]) + root[2] * p[7]);
    p[11] = p[11] + ((root[0] * p[2] + root[1] * p[5]) + root[2] * p[8]);
    *g_anim_arena_ptr_slot = (s32 *)(g_anim_joint_mtx_arena + (n << 6));
    e = g_anim_skeleton;
    idx = remap;
    j = n;
    for (;;) {
        nmAnimMtxMul((f32 *)(g_anim_joint_mtx_arena + (e[1] << 6)), p);
        j--;
        if (remap != NULL && *idx != 0) {
            /* the asm tail-jumps (never returns) for a 0 flag; every entry of the ROM table has flag 1 */
            cb = (u32 *)&g_anim_channel0_angle + *idx * 2;
            ((void (*)(void))cb[0])();
        }
        if (j == 0) {
            break;
        }
        e += 0x10;
        idx = remap + e[1];
        nmAnimLoad12(p, (f32 *)(g_anim_joint_mtx_arena + (e[0] << 6)));
    }
}
