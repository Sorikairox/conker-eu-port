#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_1515C2F0 */
void *streak_spawn(s32 *arg0, s32 arg1, void *arg2, s32 arg3, u8 arg4, s32 arg5) {
    u8 *temp_v0;

    arg0[4] = 10;
    temp_v0 = func_15147FF0(arg0, arg1 + 0x40, 0x10, 8, 8, 8, 0, 0, arg3, arg4, arg5);
    if (temp_v0 == NULL) {
        return NULL;
    }
    memcpy(*(void **)(temp_v0 + 0x98), arg2, 0x3C);
    return temp_v0;
}

#ifdef NON_MATCHING
/* P175 */
extern s32 (*D_8008B420[])(u8 *, u8 *); /* motion handlers; D_8008B424 = the same table shifted by one */

// particle_streak_step: per-frame step of a streak particle (kind 8 of D_8008A5A0, created by streak_spawn).
/* The points (obj +0x94, 0x10 bytes: x, y, z, vy) form a ring of +0x25 entries from the oldest +0x2D to the head
 * +0x2E (exclusive), count +0x2C. Each live point moves by the record's velocity (rec = obj +0x98: vx +4, vz +0xC)
 * and falls by the gravity rec +0x10 into its vy, all scaled by the frame time D_800BE9A4. Then the motion handler
 * rec +0x38 (D_8008B420, -1 = none) runs with (obj, rec); the oldest point is stored in obj +0x54 (0 when the ring
 * is empty). Returns 0 when the handler ends the particle, else 1. */
/* was func_1515C388 */
s32 streak_update_points(u8 *obj) {
    u8 *rec = *(u8 **) (obj + 0x98);
    u8 *pts = *(u8 **) (obj + 0x94);
    u8 done = 0;
    f32 *p;
    f32 vy;
    s32 i;

    if (*(s8 *) (obj + 0x2C) != 0) {
        for (i = *(s8 *) (obj + 0x2D); i != *(s8 *) (obj + 0x2E);) {
            p = (f32 *) (pts + i * 0x10);
            p[0] += *(f32 *) (rec + 4) * D_800BE9A4;
            vy = p[3];
            p[1] += vy * D_800BE9A4 + *(f32 *) (rec + 0x10) * D_800BE9A4 * D_800BE9A4 * 0.5f;
            p[2] += *(f32 *) (rec + 0xC) * D_800BE9A4;
            p[3] = vy + *(f32 *) (rec + 0x10) * D_800BE9A4;
            i++;
            if (i == obj[0x25]) {
                i = 0;
            }
        }
    }
    if (*(s8 *) (rec + 0x38) != -1) {
        done = D_8008B420[*(s8 *) (rec + 0x38)](obj, rec) == 0;
    }
    if (*(s8 *) (obj + 0x2C) > 0) {
        p = (f32 *) (pts + *(s8 *) (obj + 0x2D) * 0x10);
        *(s32 *) (obj + 0x54) = ((s32 *) p)[0];
        *(s32 *) (obj + 0x58) = ((s32 *) p)[1];
        *(s32 *) (obj + 0x5C) = ((s32 *) p)[2];
    } else {
        *(f32 *) (obj + 0x54) = 0.0f;
        *(f32 *) (obj + 0x58) = 0.0f;
        *(f32 *) (obj + 0x5C) = 0.0f;
    }
    if (done) {
        return 0;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_1897A0/streak_update_points.s")
#endif
extern s32 (*D_8008B424[])(u8 *, u8 *);

/* was func_1515C534 */
s32 streak_update_fade(u8 *arg0) {
    u8 *b;
    s32 i;
    u8 done;
    s16 t;

    b = *(u8 **)(arg0 + 0x98);
    done = 0;
    if (((s8 *)b)[0x39] != -1) {
        done = D_8008B424[((s8 *)b)[0x39]](arg0, b) == 0;
    }
    if (!done) {
        if (b[0x14] & 4) {
            t = *(s16 *)(arg0 + 0x1C);
            if (t < *(s16 *)(b + 0x2C)) {
            dummy: ; // fakematch: label splits the block (permuter)
                if (t * *(s16 *)(b + 0x2E) < b[0x1A]) {
                    b[0x1A] = t * *(s16 *)(b + 0x2E);
                }
            }
        }
        if ((b[0x14] & 8) && *(s16 *)(arg0 + 0x1C) < *(s16 *)(b + 0x30) && b[0x32] == 0) {
            for (i = D_800BE9E4; i != 0; i--) {
                *(f32 *)b *= *(f32 *)(b + 0x34);
            }
        }
    }
    if (done) {
        return 0;
    }
    return 1;
}
#ifdef NON_MATCHING
/* P175 */
void func_151D6310(s32 *, s16, s32, Vtx **, u8 *);
void func_151441A4(s16 *, s16 *, s16 *, s16 *, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8);
void func_151442FC(s16 *, s16 *, s16 *, s16 *, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8);
s32 func_15142E24(s32, s32 *, s32, s32, s32, s32, s32, s32, s32, s8 *, s32);
s32 gfx_set_combine_mode(s32, u8, s8 *);
s32 func_15142B7C(s32, s32, s32);
s32 func_15142CF0(s32, s32, s32, s16, s32, s32, s32, s8 *);
s32 func_15142C10(s32, s32, s32, s32, s32, s8 *);
s32 func_15142FBC(s32, s32, s32, s8 *);
f32 sqrtf(f32);
extern s32 D_80091228[];  /* streak texture descriptor */
extern s32 D_800D30BC;
extern s32 D_800A4EA8[];  /* render mode pairs (2 words each) */

/* One streak vertex: position, flag 0, texture (s, t), colour white with alpha a. */
#define STREAK_VTX(v, px, py, pz, s, t, a) \
    do { \
        (v)->v.ob[0] = (s32) (px); \
        (v)->v.ob[1] = (s32) (py); \
        (v)->v.ob[2] = (s32) (pz); \
        (v)->v.tc[0] = (s); \
        (v)->v.tc[1] = (t); \
        (v)->v.cn[0] = 0xFF; \
        (v)->v.cn[1] = 0xFF; \
        (v)->v.cn[2] = 0xFF; \
        (v)->v.cn[3] = (a); \
        (v)->v.flag = 0; \
    } while (0)

/* Half-width offset of a streak point: the normal of (segment a - b) x (point - camera), scaled to rec +0. */
#define STREAK_NORMAL(px, py, pz) \
    do { \
        dx = (px) - cam[0]; \
        dy = (py) - cam[1]; \
        dz = (pz) - cam[2]; \
        ex = ax - bx; \
        ey = ay - by; \
        ez = az - bz; \
        cx = ey * dz - dy * ez; \
        cy = ez * dx - dz * ex; \
        cz = ex * dy - dx * ey; \
        len2 = cx * cx + cy * cy + cz * cz; \
        if (len2 == 0.0f) { \
            nx = ny = nz = 0.0f; \
        } else { \
            k = *(f32 *) (rec + 0) / sqrtf(len2); \
            nx = cx * k; \
            ny = cy * k; \
            nz = cz * k; \
        } \
    } while (0)

// particle_streak_draw: draws a streak particle as a camera-facing ribbon (kind 8 of D_8008A644).
/* The points (obj +0x94, 0x10 bytes: x, y, z, vy) run from the newest (+0x2E - 1) back to the oldest (+0x2D), ring
 * of +0x25 entries, count +0x2C. Each point gets two vertices offset by +-n (STREAK_NORMAL; camera of view arg2 at
 * D_800DBFF0 + arg2 * 0x9A0 + 0x2F8): texture s runs 0..0x800 along the ribbon, t = 0x3FF / 0 across it, and the
 * alpha fades from 0 at the head to rec +0x1A at the tail. Each segment emits one 4-vertex load and two triangles.
 * Vertices come from func_151D6310 (2 per point + 10 spare). Sets the texture D_80091228 (combine 0x3E), combine
 * rec +0x21, geometry mode rec +0x24 / +0x28, the env / prim colours from rec +0x15..+0x1F (func_151441A4 /
 * func_151442FC), render mode 0x80000 | 0x2CA0 | D_800D30BC (| 0x100000 with rec +0x14 flag 1) with the
 * D_800A4EA8 entry rec +0x20. Returns the display list end; draws nothing with fewer than 2 points. */
/* was func_1515C6F4 */
s32 streak_draw(u8 *obj, s32 gfx, s16 arg2) {
    u8 *rec;
    u8 *pts;
    f32 *cam;
    Vtx *v;
    f32 *p1;
    s32 i;
    s32 j;
    s32 ds;
    s32 da;
    s32 s;
    s32 a;
    s8 flag;
    s16 r0, g0, b0, a0;
    s16 r1, g1, b1, a1;
    f32 ax, ay, az;
    f32 bx, by, bz;
    f32 dx, dy, dz;
    f32 ex, ey, ez;
    f32 cx, cy, cz;
    f32 nx, ny, nz;
    f32 len2;
    f32 k;

    if (*(s8 *) (obj + 0x2C) < 2) {
        return gfx;
    }
    func_151D6310((s32 *) (obj + 0x84), arg2, obj[0x25] * 0x20 + 0xA0, &v, NULL);
    if (v == NULL) {
        return gfx;
    }
    rec = *(u8 **) (obj + 0x98);
    flag = 1;
    pts = *(u8 **) (obj + 0x94);
    cam = (f32 *) ((u8 *) D_800DBFF0 + arg2 * 0x9A0 + 0x2F8);
    func_151441A4(&r0, &g0, &b0, &a0, rec[0x1B], rec[0x1C], rec[0x1D], rec[0x1E], rec[0x17], rec[0x18], rec[0x19],
                  rec[0x1A], rec[0x1F], rec[0x15]);
    func_151442FC(&r1, &g1, &b1, &a1, rec[0x1B], rec[0x1C], rec[0x1D], rec[0x1E], rec[0x17], rec[0x18], rec[0x19],
                  rec[0x1A], rec[0x1F], rec[0x16]);
    gfx = func_15142E24(gfx, D_80091228, 0, 0, 0, 0, 0x42, 0, 0, &flag, 0x3E);
    gfx = gfx_set_combine_mode(gfx, rec[0x21], &flag);
    gfx = func_15142B7C(gfx, *(s32 *) (rec + 0x24), *(s32 *) (rec + 0x28));
    gfx = func_15142CF0(gfx, 0, 0, r0, g0, b0, a0, &flag);
    gfx = func_15142C10(gfx, r1, g1, b1, a1, &flag);
    gfx = func_15142FBC(gfx, ((rec[0x14] & 1) ? 0x100000 : 0) | 0x80000 | D_800D30BC | 0x2CA0,
                        D_800A4EA8[rec[0x20] * 2 + 1] | D_800A4EA8[rec[0x20] * 2], &flag);

    i = *(s8 *) (obj + 0x2E) - 1;
    if (i < 0) {
        i = obj[0x25] - 1;
    }
    j = i - 1;
    if (j < 0) {
        j = obj[0x25] - 1;
    }
    ax = ((f32 *) (pts + i * 0x10))[0];
    ay = ((f32 *) (pts + i * 0x10))[1];
    az = ((f32 *) (pts + i * 0x10))[2];
    p1 = (f32 *) (pts + j * 0x10);
    bx = p1[0];
    by = p1[1];
    bz = p1[2];
    ds = 0x800 / (*(s8 *) (obj + 0x2C) - 1);
    da = 0xFF / (*(s8 *) (obj + 0x2C) - 1);

    /* the newest point: alpha 0, s = 0 */
    STREAK_NORMAL(ax, ay, az);
    STREAK_VTX(v, ax + nx, ay + ny, az + nz, 0, 0x3FF, 0);
    v++;
    STREAK_VTX(v, ax - nx, ay - ny, az - nz, 0, 0, 0);
    v++;

    /* one segment per older point */
    s = ds;
    a = da;
    do {
        i = j;
        j--;
        STREAK_NORMAL(bx, by, bz);
        STREAK_VTX(v, bx + nx, by + ny, bz + nz, s, 0x3FF, (u32) (rec[0x1A] * a) >> 8);
        v++;
        STREAK_VTX(v, bx - nx, by - ny, bz - nz, s, 0, (u32) (rec[0x1A] * a) >> 8);
        v++;
        s += ds;
        a += da;
        ((s32 *) gfx)[0] = 0x01004008; /* gSPVertex(v - 4, 4, 0) */
        ((s32 *) gfx)[1] = (s32) (v - 4);
        gfx += 8;
        ((s32 *) gfx)[0] = 0x05000204; /* gSP1Triangle(0, 1, 2) */
        ((s32 *) gfx)[1] = 0;
        gfx += 8;
        ((s32 *) gfx)[0] = 0x05020604; /* gSP1Triangle(1, 3, 2) */
        ((s32 *) gfx)[1] = 0;
        gfx += 8;
        p1 -= 4;
        if (j < 0) {
            j = obj[0x25] - 1;
            p1 = (f32 *) (pts + j * 0x10);
        }
        ax = bx;
        ay = by;
        az = bz;
        bx = p1[0];
        by = p1[1];
        bz = p1[2];
    } while (i != *(s8 *) (obj + 0x2D));
    return gfx;
}
#undef STREAK_VTX
#undef STREAK_NORMAL
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_1897A0/streak_draw.s")
#endif
#ifdef NON_MATCHING
/* was func_1515CF9C */
s32 streak_push_point(u8 *arg0, u8 *arg1) {
    s32 temp_v1;
    s8 temp_v0;
    u8 *temp_t1;

    temp_v0 = (*(s8 *)((u8 *)arg0 + 0x2C));
    if (temp_v0 < ((*(u8 *)((u8 *)arg0 + 0x25)) - 1)) {
        temp_v1 = (*(s32 *)((u8 *)arg0 + 0x94));
        (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) (temp_v0 + 1);
        temp_t1 = temp_v1 + ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x10);
        (*(s32 *)((u8 *)temp_t1 + 0)) = (s32) (*(s32 *)((u8 *)arg0 + 0x10));
        (*(s32 *)((u8 *)temp_t1 + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 0x14));
        (*(s32 *)((u8 *)temp_t1 + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 0x18));
        (*(f32 *)((u8 *)((temp_v1 + ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x10))) + 0xC)) = (f32) (*(f32 *)((u8 *)arg1 + 8));
        (*(s8 *)((u8 *)arg0 + 0x2E)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2E)) + 1);
        if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2E))) {
            (*(s8 *)((u8 *)arg0 + 0x2E)) = 0;
        }
    } else {
        (*(s8 *)((u8 *)arg1 + 0x39)) = -1;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_1897A0/streak_push_point.s")
#endif
// s32 streak_push_point(void *arg0, void *arg1) {
//     s32 temp_v1;
//     s8 temp_v0;
//     void *temp_t1;
//
//     temp_v0 = arg0->unk2C;
//     if ((s32) temp_v0 < (arg0->unk25 - 1)) {
//         temp_v1 = arg0->unk94;
//         arg0->unk2C = (s8) (temp_v0 + 1);
//         temp_t1 = temp_v1 + (arg0->unk2E * 0x10);
//         temp_t1->unk0 = (s32) arg0->unk10;
//         temp_t1->unk4 = (s32) arg0->unk14;
//         temp_t1->unk8 = (s32) arg0->unk18;
//         (temp_v1 + (arg0->unk2E * 0x10))->unkC = (f32) arg1->unk8;
//         arg0->unk2E = (s8) (arg0->unk2E + 1);
//         if (arg0->unk25 == arg0->unk2E) {
//             arg0->unk2E = (u8)0;
//         }
//     } else {
//         arg1->unk39 = (u8)-1;
//     }
//     return 1;
// }

/* was func_1515D030 */
s32 streak_pop_point(struct_eu_1897A0 *arg0, s32 arg1) {
    s32 ret = 1;

    if (arg0->unk2C >= 3) {
        arg0->unk2C--;
        arg0->unk2E--;
        if (arg0->unk2E < 0) {
            arg0->unk2E = arg0->unk25 - 1;
        }
    } else {
        ret = 0;
    }
    return ret;
}

/* was func_1515D088 */
struct260 *fx_source_emitter_spawn(s32 *arg0) {
    struct260 *temp_v0;
    struct {
        s32 *unk0;
        f32 unk4;
        u8 unk8;
    } sp30;

    sp30.unk8 = arg0[6];
    if (sp30.unk8 < 0 || sp30.unk8 >= 2) {
        return NULL;
    }
    sp30.unk0 = arg0;
    sp30.unk4 = 0.0f;
    temp_v0 = func_151491F4(300, -1, 0x11, 0, 0xD, 0xC, 0xFF, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &sp30, 0xC);
    }
    return temp_v0;
}

// fat struct
#ifdef NON_MATCHING
void func_15143794(s16, s16, f32, void *);
s32 func_151530A8(s32 *, u8, s32);

/* was func_1515D130 */
void fx_source_emitter_update(u8 *arg0) {
    struct {
        s32 u5C;
        s32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
        s16 u88;
        s16 u8A;
        s16 u8C;
        s16 u8E;
        s32 u90;
        s32 u94;
        s16 u98;
        s16 u9A;
        s16 u9C;
        s8 u9E;
        s8 u9F;
        s8 uA0;
        s8 uA1;
        s8 uA2;
        s8 uA3;
        s8 uA4;
        s8 uA5;
        s8 uA6;
        s8 uA7;
        s8 uA8;
        s8 uA9;
        s8 uAA;
        s8 uAB;
        s8 uAC;
        s8 uAD;
        s8 uAE;
        s8 uAF;
        s8 uB0;
        s8 uB1;
        s8 uB2;
        s8 uB3;
        s8 uB4;
        u8 padB5[0x3];
        s32 uB8;
        s32 uBC;
        s16 uC0;
        s16 uC2;
        s16 uC4;
        s8 uC6;
        u8 padC7[0x1];
        f32 uC8;
        s8 uCC;
        s8 uCD;
    } sp;
    s32 temp_s2;
    u8 *temp_s0;
    u8 *temp_s1;

    temp_s0 = ((*(u8 *)((u8 *)arg0 + 0x30)) << 6) + ((u8 *)&D_800A6880);
    temp_s1 = arg0 + 0x28;
    (*(f32 *)((u8 *)temp_s1 + 4)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 4)) + ((*(f32 *)((u8 *)temp_s0 + 0)) + (random_float() * (*(f32 *)((u8 *)temp_s0 + 4)))));
    if ((*(f32 *)((u8 *)temp_s1 + 4)) > 1.0f) {
        do {
            sp.u5C = (*(s32 *)((u8 *)temp_s0 + 8));
            sp.u60 = (*(s32 *)((u8 *)temp_s0 + 0xC));
            sp.u70 = (*(f32 *)((u8 *)temp_s0 + 0x10));
            sp.u74 = (*(f32 *)((u8 *)temp_s0 + 0x14));
            sp.u78 = (*(f32 *)((u8 *)temp_s0 + 0x18));
            sp.u7C = (*(f32 *)((u8 *)temp_s0 + 0x1C));
            sp.u80 = (*(f32 *)((u8 *)temp_s0 + 0x20));
            sp.u88 = 0;
            sp.u8A = 0xFF;
            sp.u8C = -0x3F;
            sp.u8E = 0x50;
            sp.u84 = (*(f32 *)((u8 *)temp_s0 + 0x24));
            sp.u90 = (*(s32 *)((u8 *)temp_s0 + 0x28));
            sp.u94 = (*(s32 *)((u8 *)temp_s0 + 0x2C));
            sp.u98 = (*(s16 *)((u8 *)temp_s0 + 0x30));
            sp.u9C = 1;
            sp.u9E = 0xC;
            sp.u9F = 2;
            sp.uA0 = 3;
            sp.uA1 = 0xB4;
            sp.uA4 = 0x9B;
            sp.u9A = (*(s16 *)((u8 *)temp_s0 + 0x32));
            sp.uA2 = 0;
            sp.uA3 = 0;
            sp.uA5 = 0x32;
            sp.uA6 = 0x64;
            sp.uA7 = 0;
            sp.uA8 = 0x64;
            sp.uA9 = 0xFF;
            sp.uAA = 0xFF;
            sp.uAB = 0xFF;
            sp.uAC = 0xFF;
            sp.uAD = 0;
            sp.uAE = 0;
            sp.uAF = 0;
            sp.uB0 = 0;
            sp.uB1 = 0xFF;
            sp.uB2 = 0;
            sp.uB3 = 1;
            sp.uB4 = 0x24;
            sp.uB8 = 0x200005;
            sp.uBC = 0x60600;
            sp.uC0 = (*(s16 *)((u8 *)temp_s0 + 0x34));
            sp.uC2 = (*(s16 *)((u8 *)temp_s0 + 0x36));
            sp.uC6 = 0;
            sp.uC4 = (*(s16 *)((u8 *)temp_s0 + 0x38));
            sp.uCC = -1;
            sp.uCD = 0;
            sp.uC8 = (*(f32 *)((u8 *)temp_s0 + 0x3C));
            temp_s2 = random_int();
            func_15143794((s16) (temp_s2 & 0xFF), (s16) (0x40 - (random_int() & 0x7F)), (f32) (*(s16 *)((u8 *)((*(u8 **)((u8 *)temp_s1 + 0))) + 6)), &sp.u64);
            sp.u64 += (f32) (*(s16 *)((u8 *)((*(u8 **)((u8 *)temp_s1 + 0))) + 0));
            sp.u68 += (f32) (*(s16 *)((u8 *)((*(u8 **)((u8 *)temp_s1 + 0))) + 2));
            sp.u6C += (f32) (*(s16 *)((u8 *)((*(u8 **)((u8 *)temp_s1 + 0))) + 4));
            func_151530A8(&sp.u5C, (*(u8 *)((u8 *)arg0 + 0xC)), (*(u8 *)((u8 *)arg0 + 1)));
            (*(f32 *)((u8 *)temp_s1 + 4)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 4)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s1 + 4)) > 1.0f);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_1897A0/fx_source_emitter_update.s")
#endif