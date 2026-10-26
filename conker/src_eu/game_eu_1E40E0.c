#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
extern u8 g_render_mode_pairs[]; /* was D_800A4EA8 */


typedef struct { f32 x, y, z; } V368D0;
typedef struct { V368D0 pos; s16 u80; s16 u82; s32 u84; u8 pad88; s8 u89; u8 pad8A[2]; s32 pad8C; } SA68D0;
typedef struct { u8 *u44; u8 u48; u8 pad49[3]; V368D0 pos; f32 u58, u5C, u60, u64, u68, u6C; } SB68D0;
void *memcpy(void *, const void *, u32);
/* was func_151B68D0 */
void obj_ribbon_trail_spawn(u8 *arg0, u8 arg1, s32 arg2) {
    SA68D0 a;
    s32 pad; // fakematch: frame padding between the two spawn structs
    SB68D0 b;
    u8 *r;

    a.u89 = 10;
    a.pos.x = *(f32 *)(arg0 + 0x14);
    a.pos.y = *(f32 *)(arg0 + 0x18);
    a.pos.z = *(f32 *)(arg0 + 0x1C);
    a.u80 = 300;
    a.u82 = 6;
    b.u44 = arg0;
    b.u48 = arg0[0x3B];
    b.pos = a.pos;
    b.u58 = 0.0f;
    b.u5C = 0.0f;
    b.u64 = -16384.0f;
    b.u60 = -16384.0f;
    b.u68 = 0.0f;
    a.u84 = 0xD;
    r = fxrec_spawn(&a, 0x30, 0x1C, 0xB, 0xB, 0xB, 0, 0, 0, arg1, arg2);
    if (r != NULL) {
        memcpy(*(void **)(r + 0x98), &b, sizeof(b));
    }
}

// trail_ring_age_update: update handler (s32 (u8 *obj), the ribbon_trail_follow_update table) of the trail objects: the ring +0x94
// holds 28-byte points {pos, life +0xC, alpha +0x10, distance +0x18}; write index +0x2E, read index +0x2D, count
// +0x2C, capacity +0x25. Returns 0 (done) when fewer than 2 points are left and flag 8 of +0x1E is set. Walking back
// from the newest point, each life runs down by the frame time D_800BE9A4; at a dead point all older points are
// dropped (read index moves up to it). Then each point's alpha is its distance from the oldest point * 0.494
// (at most 0x9B), and +0x54 gets the oldest point (0, 0, 0 when empty). Returns 1.
/* was func_151B69D0 */
s32 trail_ring_age_update(u8 *obj) {
    s32 count = (s8) obj[0x2C];
    u8 *ring = *(u8 **) (obj + 0x94);
    s32 i;
    s32 rd;
    s32 a;
    f32 base;

    if (count < 2 && (*(u16 *) (obj + 0x1E) & 8)) {
        return 0;
    }
    rd = (s8) obj[0x2D];
    i = (s8) obj[0x2E];
    if (i != rd) {
        do {
            i--;
            if (i < 0) {
                i = obj[0x25] - 1;
            }
            *(f32 *) (ring + i * 0x1C + 0xC) -= D_800BE9A4;
            if (*(f32 *) (ring + i * 0x1C + 0xC) < 0.0f) {
                rd = (s8) obj[0x2D];
                while (i != rd) {
                    obj[0x2D] = rd + 1;
                    rd = (s8) obj[0x2D];
                    if (obj[0x25] == rd) {
                        obj[0x2D] = 0;
                        rd = (s8) obj[0x2D];
                    }
                    obj[0x2C] = (s8) obj[0x2C] - 1;
                }
            }
            rd = (s8) obj[0x2D];
        } while (i != rd);
        count = (s8) obj[0x2C];
    }
    if (count > 0) {
        i = rd;
        base = *(f32 *) (ring + rd * 0x1C + 0x18);
        do {
            a = (*(f32 *) (ring + i * 0x1C + 0x18) - base) * 0.49400002f;
            if (a < 0x9C) {
                ring[i * 0x1C + 0x10] = a;
            } else {
                ring[i * 0x1C + 0x10] = 0x9B;
            }
            i++;
            if (i >= obj[0x25]) {
                i = 0;
            }
        } while (i != (s8) obj[0x2E]);
        count = (s8) obj[0x2C];
    }
    if (count > 0) {
        i = (s8) obj[0x2D];
        *(s32 *) (obj + 0x54) = *(s32 *) (ring + i * 0x1C + 0);
        *(s32 *) (obj + 0x58) = *(s32 *) (ring + i * 0x1C + 4);
        *(s32 *) (obj + 0x5C) = *(s32 *) (ring + i * 0x1C + 8);
    } else {
        *(f32 *) (obj + 0x54) = 0.0f;
        *(f32 *) (obj + 0x58) = 0.0f;
        *(f32 *) (obj + 0x5C) = 0.0f;
    }
    return 1;
}

f32 vec3_length(void *);

/* was func_151B6B84 */
s32 ribbon_trail_follow_update(u8 *arg0) {
    struct {
        f32 u84;
        f32 u88;
        f32 u8C;
        u8 pad90[0x10];
        f32 uA0;
        f32 uA4;
        f32 uA8;
        u8 padAC[0x4];
        s32 uB0;
        u8 * uB4;
    } sp;
    f32 sp58;
    f32 sp50;
    f32 sp48;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f24;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f6;
    f32 var_f16;
    f32 var_f18;
    f32 var_f20;
    s8 temp_v0_3;
    u8 *temp_a2;
    u8 *temp_t2;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_a2 = (*(u8 **)((u8 *)arg0 + 0x98));
    temp_v0 = (*(u8 **)((u8 *)temp_a2 + 0));
    if (((*(s32 *)((u8 *)temp_v0 + 0)) == 0) || ((*(u8 *)((u8 *)temp_a2 + 4)) != (*(u8 *)((u8 *)temp_v0 + 0x3B))) || ((*(f32 *)((u8 *)temp_v0 + 0x3C)) < 15.0f)) {
        (*(s8 *)((u8 *)arg0 + 0x30)) = 0;
        (*(u16 *)((u8 *)arg0 + 0x1E)) = (u16) ((*(u16 *)((u8 *)arg0 + 0x1E)) | 8);
        return 1;
    }
    (*(f32 *)((u8 *)arg0 + 0x10)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x14));
    (*(f32 *)((u8 *)arg0 + 0x14)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x18));
    (*(f32 *)((u8 *)arg0 + 0x18)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x1C));
    sp.uA0 = (*(f32 *)((u8 *)arg0 + 0x10)) - (*(f32 *)((u8 *)temp_a2 + 8));
    sp.uA4 = (*(f32 *)((u8 *)arg0 + 0x14)) - (*(f32 *)((u8 *)temp_a2 + 0xC));
    sp.uB0 = (*(s32 *)((u8 *)arg0 + 0x94));
    sp.uB4 = temp_a2;
    sp.uA8 = (*(f32 *)((u8 *)arg0 + 0x18)) - (*(f32 *)((u8 *)temp_a2 + 0x10));
    temp_f0 = vec3_length(&sp.uA0);
    (*(f32 *)((u8 *)sp.uB4 + 0x14)) = (f32) ((*(f32 *)((u8 *)sp.uB4 + 0x14)) + (temp_f0 * 0.003722f * D_800BE9A4));
    temp_f2 = (*(f32 *)((u8 *)sp.uB4 + 0x14));
    (*(f32 *)((u8 *)sp.uB4 + 0x1C)) = (f32) ((*(f32 *)((u8 *)sp.uB4 + 0x1C)) + (temp_f0 * 4.409548f));
    sp58 = temp_f2;
    if (temp_f2 > 1.0f) {
        temp_t2 = sp.uB4 + 8;
        temp_f2_2 = 1.0f / sp58;
        (*(f32 *)((u8 *)(&sp.u84) + 0)) = (*(f32 *)((u8 *)temp_t2 + 0));
        (*(s32 *)((u8 *)(&sp.u84) + 4)) = (s32) (*(s32 *)((u8 *)temp_t2 + 4));
        var_f18 = (*(f32 *)((u8 *)sp.uB4 + 0x18)) + D_800BE9A4;
        (*(s32 *)((u8 *)(&sp.u84) + 8)) = (s32) (*(s32 *)((u8 *)temp_t2 + 8));
        temp_f12 = (*(f32 *)((u8 *)sp.uB4 + 0x20));
        var_f20 = (*(f32 *)((u8 *)sp.uB4 + 0x24));
        var_f16 = temp_f12;
        temp_f24 = -(var_f18 * temp_f2_2);
        sp50 = ((*(f32 *)((u8 *)sp.uB4 + 0x1C)) - temp_f12) * temp_f2_2;
        sp48 = temp_f0 * temp_f2_2;
        do {
            temp_v0_2 = ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x1C) + sp.uB0;
            (*(f32 *)((u8 *)temp_v0_2 + 0)) = (f32) (*(f32 *)((u8 *)(&sp.u84) + 0));
            (*(s32 *)((u8 *)temp_v0_2 + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u84) + 4));
            (*(s8 *)((u8 *)temp_v0_2 + 0x10)) = 0x9B;
            (*(f32 *)((u8 *)temp_v0_2 + 0x14)) = var_f16;
            (*(s32 *)((u8 *)temp_v0_2 + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u84) + 8));
            temp_f6 = 13.0f - var_f18;
            var_f18 += temp_f24;
            (*(f32 *)((u8 *)temp_v0_2 + 0xC)) = temp_f6;
            if (var_f16 > 16384.0f) {
                do {
                    (*(f32 *)((u8 *)temp_v0_2 + 0x14)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x14)) - 32768.0f);
                } while ((*(f32 *)((u8 *)temp_v0_2 + 0x14)) > 16384.0f);
            }
            (*(f32 *)((u8 *)temp_v0_2 + 0x18)) = var_f20;
            (*(s8 *)((u8 *)arg0 + 0x2E)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2E)) + 1);
            if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2E))) {
                (*(s8 *)((u8 *)arg0 + 0x2E)) = 0;
            }
            temp_v0_3 = (*(s8 *)((u8 *)arg0 + 0x2D));
            (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) + 1);
            if (temp_v0_3 == (*(s8 *)((u8 *)arg0 + 0x2E))) {
                (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) (temp_v0_3 + 1);
                if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2D))) {
                    (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
                }
                (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) - 1);
            }
            sp.u84 += sp.uA0 * temp_f2_2;
            sp.u88 += sp.uA4 * temp_f2_2;
            var_f16 += sp50;
            sp.u8C += sp.uA8 * temp_f2_2;
            var_f20 += sp48;
            (*(f32 *)((u8 *)sp.uB4 + 0x14)) = (f32) ((*(f32 *)((u8 *)sp.uB4 + 0x14)) - 1.0f);
        } while ((*(f32 *)((u8 *)sp.uB4 + 0x14)) > 1.0f);
        (*(f32 *)((u8 *)temp_t2 + 0)) = (f32) (*(f32 *)((u8 *)(&sp.u84) + 0));
        (*(s32 *)((u8 *)temp_t2 + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u84) + 4));
        (*(s32 *)((u8 *)temp_t2 + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u84) + 8));
        (*(f32 *)((u8 *)sp.uB4 + 0x20)) = var_f16;
        (*(f32 *)((u8 *)sp.uB4 + 0x24)) = var_f20;
        (*(f32 *)((u8 *)sp.uB4 + 0x18)) = var_f18;
    }
    return 1;
}
s32 gfx_set_combine_mode(s32, s32, s8 *);
s32 gfx_geometry_mode_cached(s32, s32, s32);
s32 gfx_load_texture_cached(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s8 *, s32);
u8 *gfx_other_mode_cached(s32, s32, s32, s8 *);
void vtx_slot_buffer_get(s32 *, s16, s32, s32 *, u8 *);
u8 *gfx_env_color_cached(u8 *, s32, s32, s32, s32, s8 *);
extern s32 D_80091084;
extern s32 D_800D30BC;

typedef struct {
    f32 pos[3];         /* +0x00 */
    u8 pad0C[4];
    u8 alpha;           /* +0x10 */
    u8 pad11[3];
    f32 width;          /* +0x14 texture s at this point */
    u8 pad18[4];
} RibbonPoint;          /* 0x1C bytes, trail +0x94 */

// ribbon_trail_draw: draws the trail's points (+0x94, ring of +0x25 entries, newest before +0x2E, oldest +0x2D;
// nothing below 2 points, +0x2C) as a camera-facing ribbon of half-width 10: each point gets two vertices offset by
// +-10 * normalize((prev - next) x (point - camera)) (no offset when that is 0), texture s = the point's width
// value, t 0 / 0x7FF, white with the point's alpha; one G_VTX of 4 + two triangles per segment. With +0x1E bit 1
// the ribbon starts at the trail's own position (+0x10, alpha 0x80, s 0). Vertices come from vtx_slot_buffer_get (the
// trail's +0x84 buffer, (count << 5) + 0xA0 bytes; none -> gfx unchanged); render state: texture D_80091084,
// combine 0x4E, geometry 0x200005 / 0x1F0600, othermode D_800D30BC | 0x82CA0 / g_render_mode_pairs words 6 | 7.
/* was func_151B6ED8 */
u8 *ribbon_trail_w10_draw(u8 *trail, u8 *gfx, s16 arg2) {
    RibbonPoint *pts;
    f32 *cam;
    Vtx *v;
    s32 *g;
    f32 a[3];
    f32 b[3];
    f32 widthA;
    f32 widthB;
    f32 dx, dy, dz;
    f32 ex, ey, ez;
    f32 nx, ny, nz;
    f32 len2;
    f32 k;
    u8 alphaA;
    u8 alphaB;
    s32 cur;
    s32 next;
    s32 s;
    s8 flag;

    if (*(s8 *) (trail + 0x2C) < 2) {
        return gfx;
    }
    vtx_slot_buffer_get((s32 *) (trail + 0x84), arg2, (trail[0x25] << 5) + 0xA0, (s32 *) &v, 0);
    if (v == NULL) {
        return gfx;
    }
    pts = *(RibbonPoint **) (trail + 0x94);
    cam = camera_get_pos(arg2);
    flag = 1;
    gfx = (u8 *) gfx_load_texture_cached(gfx, &D_80091084, 0, 0, 0, 0, 0x1F, 0, 0, &flag, 3);
    gfx = gfx_env_color_cached(gfx, 0xFF, 0xFF, 0xFF, 0xFF, &flag);
    gfx = (u8 *) gfx_set_combine_mode((s32) gfx, 0x4E, &flag);
    gfx = (u8 *) gfx_geometry_mode_cached((s32) gfx, 0x200005, 0x1F0600);
    gfx = gfx_other_mode_cached((s32) gfx, D_800D30BC | 0x80000 | 0x2CA0, ((s32 *) g_render_mode_pairs)[7] | ((s32 *) g_render_mode_pairs)[6],
                        &flag);

    if (*(u16 *) (trail + 0x1E) & 2) {
        next = *(s8 *) (trail + 0x2E) - 1;
        if (next < 0) {
            next = trail[0x25] - 1;
        }
        a[0] = *(f32 *) (trail + 0x10);
        a[1] = *(f32 *) (trail + 0x14);
        a[2] = *(f32 *) (trail + 0x18);
        alphaA = 0x80;
        widthA = 0.0f;
    } else {
        cur = *(s8 *) (trail + 0x2E) - 1;
        if (cur < 0) {
            cur = trail[0x25] - 1;
        }
        next = cur - 1;
        if (next < 0) {
            next = trail[0x25] - 1;
        }
        a[0] = pts[cur].pos[0];
        a[1] = pts[cur].pos[1];
        a[2] = pts[cur].pos[2];
        widthA = pts[cur].width;
        alphaA = pts[cur].alpha;
    }
    b[0] = pts[next].pos[0];
    b[1] = pts[next].pos[1];
    b[2] = pts[next].pos[2];
    alphaB = pts[next].alpha;
    widthB = pts[next].width;

    /* the first pair, at a */
    dx = a[0] - cam[0];
    dy = a[1] - cam[1];
    dz = a[2] - cam[2];
    ey = a[1] - b[1];
    ez = a[2] - b[2];
    ex = a[0] - b[0];
    nx = ey * dz - dy * ez;
    ny = ez * dx - dz * ex;
    nz = ex * dy - dx * ey;
    len2 = nx * nx + ny * ny + nz * nz;
    if (0.0f == len2) {
        nx = ny = nz = 0.0f;
    } else {
        k = 10.0f / sqrtf(len2);
        nx *= k;
        ny *= k;
        nz *= k;
    }
    s = (s32) widthA;
    v->v.ob[0] = (s32) (a[0] + nx);
    v->v.ob[1] = (s32) (a[1] + ny);
    v->v.ob[2] = (s32) (a[2] + nz);
    v->v.tc[0] = s;
    v->v.tc[1] = 0;
    v->v.cn[0] = 0xFF;
    v->v.cn[1] = 0xFF;
    v->v.cn[2] = 0xFF;
    v->v.cn[3] = alphaA;
    v->v.flag = 0;
    v++;
    v->v.ob[0] = (s32) (a[0] - nx);
    v->v.ob[1] = (s32) (a[1] - ny);
    v->v.ob[2] = (s32) (a[2] - nz);
    v->v.tc[0] = s;
    v->v.tc[1] = 0x7FF;
    v->v.cn[0] = 0xFF;
    v->v.cn[1] = 0xFF;
    v->v.cn[2] = 0xFF;
    v->v.cn[3] = alphaA;
    v->v.flag = 0;
    v++;

    /* one pair per point at b, back to the oldest (+0x2D) */
    do {
        dx = b[0] - cam[0];
        dy = b[1] - cam[1];
        dz = b[2] - cam[2];
        cur = next;
        next = cur - 1;
        ey = a[1] - b[1];
        ez = a[2] - b[2];
        ex = a[0] - b[0];
        nx = ey * dz - dy * ez;
        ny = ez * dx - dz * ex;
        nz = ex * dy - dx * ey;
        len2 = nx * nx + ny * ny + nz * nz;
        s = (s32) widthB;
        if (0.0f == len2) {
            nx = ny = nz = 0.0f;
        } else {
            k = 10.0f / sqrtf(len2);
            nx *= k;
            ny *= k;
            nz *= k;
        }
        v->v.ob[0] = (s32) (b[0] + nx);
        v->v.ob[1] = (s32) (b[1] + ny);
        v->v.ob[2] = (s32) (b[2] + nz);
        v->v.tc[0] = s;
        v->v.tc[1] = 0;
        v->v.cn[0] = 0xFF;
        v->v.cn[1] = 0xFF;
        v->v.cn[2] = 0xFF;
        v->v.cn[3] = alphaB;
        v->v.flag = 0;
        v++;
        v->v.ob[0] = (s32) (b[0] - nx);
        v->v.ob[1] = (s32) (b[1] - ny);
        v->v.ob[2] = (s32) (b[2] - nz);
        v->v.tc[0] = s;
        v->v.tc[1] = 0x7FF;
        v->v.cn[0] = 0xFF;
        v->v.cn[1] = 0xFF;
        v->v.cn[2] = 0xFF;
        v->v.cn[3] = alphaB;
        v->v.flag = 0;
        v++;
        g = (s32 *) gfx;
        g[0] = 0x01004008;      /* G_VTX: the last 4 vertices (previous pair, this pair) to slots 0..3 */
        g[1] = (s32) (v - 4);
        g[2] = 0x05000204;      /* G_TRI1 0, 1, 2 */
        g[3] = 0;
        g[4] = 0x05020604;      /* G_TRI1 1, 3, 2 */
        g[5] = 0;
        gfx += 0x18;
        if (next < 0) {
            next = trail[0x25] - 1;
        }
        if (cur != *(s8 *) (trail + 0x2D)) {
            a[0] = b[0];
            a[1] = b[1];
            a[2] = b[2];
            b[0] = pts[next].pos[0];
            b[1] = pts[next].pos[1];
            b[2] = pts[next].pos[2];
            alphaB = pts[next].alpha;
            widthB = pts[next].width;
        }
    } while (cur != *(s8 *) (trail + 0x2D));
    return gfx;
}

/* was func_151B7664 */
void ribbon_trail_handle_message(u8 *arg0, s32 *arg1, u8 arg2)
{
  s32 *p;
  s32 id;
  s32 t;
  p = *((s32 **) (arg0 + 0x98));
  id = p[0];
  t = id;
  if (arg2 == 0)
  {
    if (t == arg1[0])
    {
      s32 blk_t; // fakematch: block-local declaration = basic-block boundary (unfilled jr ra delay slot, s69)
      arg0[0x30] = 0;
      *((u16 *) (arg0 + 0x1E)) |= 8;
    }
  }
  else
    if (arg2 == 0x2D)
  {
    t = arg1[0];
    if (t == *p)
    {
      p[0] = arg1[1];
      ((u8 *) p)[4] = ((u8 *) arg1)[9];
      return;
    }
    if (arg1[1] == *p)
    {
      p[0] = t;
      ((u8 *) p)[4] = ((u8 *) arg1)[8];
    }
  }
}

s32 random_int(void);
f32 random_float(void);
s32 particle_spawn_ex(void *spec, s32 count, s32 arg2, s32 arg3, s32 alpha, s32 arg5);
extern f32 D_800AA85C;
/* particle spec read by particle_spawn_ex (offsets from its start) */
typedef struct {
    /* 0x00 */ s32 type;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 life;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 color[8];   /* two RGBA colours */
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 unk1D;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 size[2];
    /* 0x30 */ f32 pos[3];
    /* 0x3C */ f32 vel[3];
    /* 0x48 */ f32 accel[3];
    /* 0x54 */ f32 unk54;
    /* 0x58 */ s32 flags;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s8 unk60[6];
} SmokePuffSpec;
// obj_smoke_puff_spawn: one random smoke puff particle at obj's position (particle_spawn_ex, alpha arg1, arg2 passed
// on): size 89..139 (random_float * 50 + 89), life 30..39, colours DD D3 CD FF / 57 55 5A (200..255 alpha),
// random mirror flags 0x40 / 0x80. Called by obj_effect_smoke_ribbon (with obj_ribbon_trail_spawn), handler 8 of obj_effect_run_handler.
/* was func_151B76F4 */
void obj_smoke_puff_spawn(u8 *obj, s32 alpha, s32 arg2) {
    SmokePuffSpec p;
    s32 flipX;
    s32 flipY;
    f32 size;

    p.unk1D = 0x29;
    p.unk8 = 0xE03;
    p.type = 0x200005;
    p.unk4 = 0;
    p.unkC = 0;
    p.unk10 = 0;
    p.unk1E = 0x12;
    p.unk20 = 0xE;
    flipX = (random_int() & 1) ? 0x40 : 0;
    flipY = (random_int() & 1) ? 0x80 : 0;
    p.flags = flipY | 1 | flipX | 0xCE00 | 0x10000;
    p.unk60[0] = 3;
    p.unk60[1] = 3;
    p.unk60[2] = -1;
    p.unk60[3] = -1;
    p.unk60[4] = -1;
    p.unk60[5] = 0;
    p.unk22 = 0x28;
    p.color[0] = 0xDD;
    p.color[1] = 0xD3;
    p.color[2] = 0xCD;
    p.color[3] = 0xFF;
    p.color[4] = 0x57;
    p.color[5] = 0x55;
    p.color[6] = 0x5A;
    p.unk1C = 0xFF;
    p.unk54 = 0.0f;
    p.unk24 = D_800AA85C;
    p.pos[0] = *(f32 *) (obj + 0x14);
    p.pos[1] = *(f32 *) (obj + 0x18);
    p.pos[2] = *(f32 *) (obj + 0x1C);
    p.vel[0] = 0.0f;
    p.vel[1] = 0.0f;
    p.vel[2] = 0.0f;
    p.color[7] = (u32) random_int() % 0x38 + 0xC8;
    p.life = (u32) random_int() % 10 + 0x1E;
    size = random_float() * 50.0f + 89.0f;
    p.accel[0] = 0.0f;
    p.accel[1] = 0.0f;
    p.size[0] = size;
    p.size[1] = size;
    p.accel[2] = 0.0f;
    particle_spawn_ex(&p, 1, 0, 0, alpha & 0xFF, arg2);
}

extern s32 (*D_8008FF30[])(u8 *, void *);   /* attach handlers: 0 glow_attach_follow_obj, 1 glow_attach_follow_model_point */
extern s32 D_800AA840[4];                    /* glow particle variants (low byte used) */
extern f32 D_800AA860;
/* glow particle spec read by particle_spawn_ex (same layout as SmokePuffSpec, one more byte at 0x66) */
typedef struct {
    /* 0x00 */ s32 type;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 life;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 color[8];
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 unk1D;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 size[2];
    /* 0x30 */ f32 pos[3];
    /* 0x3C */ f32 vel[3];
    /* 0x48 */ f32 accel[3];
    /* 0x54 */ f32 unk54;
    /* 0x58 */ s32 flags;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s8 unk60[7];
} GlowSpec;
/* object spawn request for fxrec_spawn (as SA68D0) */
typedef struct {
    f32 pos[3];
    s16 u80;
    s16 u82;
    s32 u84;
    u8 u88;
    u8 u89;
} AttachSpawn;
/* the spawned object's +0x98 data block: glow handle, pointer to the copied attach data, attach type */
typedef struct {
    s32 glow;
    void *data;
    u8 type;
} AttachData;
// obj_attached_glow_spawn: spawns a helper object (fxrec_spawn, extra size + 0x10) that follows something:
// its data block gets a copy of `size` bytes of `src` and the attach type; the type's handler (D_8008FF30[type],
// 0 = follow an object, 1 = follow a model point) places it, and if it fails the object is freed (returns NULL).
// Then a big glow particle (particle_spawn_ex; variant D_800AA840[rand & 3], size rand * 800 + D_800AA860, life 300,
// random mirror flags) is started and its handle kept in the data block. Returns the object.
// Callers: obj_effect_attached_glow (effect handler 12 of obj_effect_run_handler, type 0), beam_trail_spawn (type 1).
/* was func_151B78D8 */
u8 *obj_attached_glow_spawn(void *src, u8 type, s32 size, u8 alpha, s32 arg4) {
    AttachSpawn a;
    AttachData d;
    AttachData *data;
    GlowSpec p;
    s32 flipX;
    s32 flipY;
    f32 glowSize;
    u8 *obj;

    d.glow = 0;
    d.data = NULL;
    d.type = type;
    a.u89 = 0x14;
    *(V368D0 *) a.pos = *(V368D0 *) D_800A5860;
    a.u80 = 300;
    a.u82 = 0x14;
    a.u84 = 0x10;
    a.u88 = 2;
    obj = (u8 *) fxrec_spawn(&a, size + 0x10, 0x14, 0, 0xE, 0xE, 0, 0, 0, alpha, arg4);
    if (obj != NULL) {
        data = *(AttachData **) (obj + 0x98);
        memcpy(data, &d, sizeof(d));
        data->data = (u8 *) data + 0x10;
        memcpy(data->data, src, size);
        if (D_8008FF30[type](obj, obj + 0x10) == 0) {
            node_destroy((struct102 *) obj);
            return NULL;
        }
        p.unk8 = 0x1303;
        p.type = 0x200005;
        p.unk1D = D_800AA840[random_int() & 3];
        p.unk4 = 0;
        p.life = 300;
        p.unkC = 0;
        p.unk10 = 0;
        p.color[0] = 0xFF;
        p.color[1] = 0xFF;
        p.color[2] = 0xFF;
        p.color[3] = 0xFF;
        p.color[4] = 0xFF;
        p.color[5] = 0xFF;
        p.color[6] = 0xFF;
        p.color[7] = 0xFF;
        p.unk1C = 0xFF;
        glowSize = random_float() * 800.0f + D_800AA860;
        p.size[1] = glowSize;
        p.size[0] = glowSize;
        p.pos[0] = a.pos[0];
        p.pos[1] = a.pos[1];
        p.pos[2] = a.pos[2];
        *(V368D0 *) p.vel = *(V368D0 *) D_800A5860;
        *(V368D0 *) p.accel = *(V368D0 *) D_800A5860;
        p.unk1E = 1;
        p.unk20 = 0xFF;
        p.unk22 = 1;
        p.unk54 = 0.0f;
        p.unk24 = 1.0f;
        flipX = (random_int() & 1) ? 0x40 : 0;
        flipY = (random_int() & 1) ? 0x80 : 0;
        p.flags = (flipY | flipX) | 0xC000 | 0x40000;
        p.unk60[0] = 6;
        p.unk60[1] = 5;
        p.unk60[2] = -1;
        p.unk60[3] = -1;
        p.unk60[4] = -1;
        p.unk60[5] = 0;
        p.unk5C = 0;
        p.unk60[6] = -1;
        data->glow = particle_spawn_ex(&p, 1, 0, 0, alpha, arg4);
    }
    return obj;
}

/* was func_151B7C28 */
s32 glow_attach_follow_obj(u8 *arg0, u8 *arg1)
{
  u8 *temp_a2;
  u8 *new_var;
  u8 *temp_v1;
  new_var = *((u8 **) (arg0 + 0x98)); temp_v1 = *((u8 **) (new_var + 4)); temp_a2 = *((u8 **) temp_v1);
  if (*((s32 *) temp_a2) == 0) goto ret0;
  if (temp_v1[4] != temp_a2[0x3B]) { ret0: return 0; }
  *((f32 *) (arg1 + 0)) = *((f32 *) (temp_a2 + 0x14));
  *((f32 *) (arg1 + 4)) = *((f32 *) (temp_a2 + 0x18));
  *((f32 *) (arg1 + 8)) = *((f32 *) (temp_a2 + 0x1C));
  return 1;
}

/* was func_151B7C7C */
s32 glow_attach_follow_model_point(u8 *arg0, f32 *arg1) {
    u8 *p;
    u8 *q;
    u8 *obj;
    f32 mf[4][4];

    p = *(u8 **)(arg0 + 0x98);
    q = *(u8 **)(p + 4);
    obj = *(u8 **)q;
    mtxf_rotate_xyz_deg(mf, *(f32 *)(obj + 0x20), *(f32 *)(obj + 0x24), *(f32 *)(obj + 0x28));
    mf[3][0] = *(f32 *)(obj + 0x38);
    mf[3][1] = *(f32 *)(obj + 0x3C);
    mf[3][2] = *(f32 *)(obj + 0x40);
    mf[0][0] *= *(f32 *)(obj + 0x18);
    mf[0][1] *= *(f32 *)(obj + 0x18);
    mf[0][2] *= *(f32 *)(obj + 0x18);
    mf[1][0] *= *(f32 *)(obj + 0x1C);
    mf[1][1] *= *(f32 *)(obj + 0x1C);
    mf[1][2] *= *(f32 *)(obj + 0x1C);
    mf[2][0] *= *(f32 *)(obj + 0x18);
    mf[2][1] *= *(f32 *)(obj + 0x18);
    mf[2][2] *= *(f32 *)(obj + 0x18);
    mtxf_transform_point(mf, 0.0f, 0.0f, -250.0f, &arg1[0], &arg1[1], &arg1[2]);
    return 1;
}

// obj_attached_glow_update: update handler of the obj_attached_glow_spawn helper objects. Each frame with a time step
// (D_800BE9E4 > 0): the attach type's handler (D_8008FF30) moves the object (pos +0x10) - on failure returns 0 (the
// caller frees it); the glow particle (data->glow, pos +0x40) follows. The move is logged in the trail ring +0x94
// (20-byte entries {pos, step length (vec3_length), alpha 0xFF}; write index +0x2E, read index +0x2D, count +0x2C,
// capacity +0x25): when the write index catches the read index, the oldest entry is dropped. Returns 1.
/* was func_151B7DA4 */
s32 obj_attached_glow_update(u8 *obj) {
    u8 *ring = *(u8 **) (obj + 0x94);
    AttachData *data = *(AttachData **) (obj + 0x98);
    f32 old[3];
    f32 d[3];
    f32 len;
    u8 *e;

    if (D_800BE9E4 > 0) {
        old[0] = *(f32 *) (obj + 0x10);
        old[1] = *(f32 *) (obj + 0x14);
        old[2] = *(f32 *) (obj + 0x18);
        if (D_8008FF30[data->type](obj, obj + 0x10) == 0) {
            return 0;
        }
        if (data->glow != 0) {
            *(s32 *) ((u8 *) data->glow + 0x40) = *(s32 *) (obj + 0x10);
            *(s32 *) ((u8 *) data->glow + 0x44) = *(s32 *) (obj + 0x14);
            *(s32 *) ((u8 *) data->glow + 0x48) = *(s32 *) (obj + 0x18);
        }
        d[0] = *(f32 *) (obj + 0x10) - old[0];
        d[1] = *(f32 *) (obj + 0x14) - old[1];
        d[2] = *(f32 *) (obj + 0x18) - old[2];
        len = vec3_length(d);
        e = ring + (s8) obj[0x2E] * 20;
        *(s32 *) (e + 0) = *(s32 *) (obj + 0x10);
        *(s32 *) (e + 4) = *(s32 *) (obj + 0x14);
        *(s32 *) (e + 8) = *(s32 *) (obj + 0x18);
        *(f32 *) (e + 0xC) = len;
        e[0x10] = 0xFF;
        obj[0x2E] = (s8) obj[0x2E] + 1;
        if (obj[0x25] == (s8) obj[0x2E]) {
            obj[0x2E] = 0;
        }
        obj[0x2C] = (s8) obj[0x2C] + 1;
        if ((s8) obj[0x2D] == (s8) obj[0x2E]) {
            obj[0x2D] = (s8) obj[0x2D] + 1;
            if (obj[0x25] == (s8) obj[0x2D]) {
                obj[0x2D] = 0;
            }
            obj[0x2C] = (s8) obj[0x2C] - 1;
        }
    }
    return 1;
}

// trail_ring_trim_fade: update handler (s32 (u8 *obj), returns 1) of the trail objects whose ring +0x94 holds 20-byte
// entries {pos, step length +0xC, alpha +0x10} (write index +0x2E, read index +0x2D, count +0x2C, size +0x25). With
// 2+ points it walks back from the newest point summing the step lengths; once the sum passes 1198 the oldest kept
// point is pulled along its step so the trail is exactly 1198 long, that step shortened by the same fraction, and all
// older points dropped (read index advanced, count decremented). Then each point's alpha is set to 255 * (length from
// it to the trail's end) / total length, newest first.
/* was func_151B7F48 */
s32 trail_ring_trim_fade(u8 *obj) {
    u8 *ring = *(u8 **) (obj + 0x94);
    u8 *e;
    f32 *prev;
    f32 total;
    f32 len;
    f32 frac;
    f32 inv;
    f32 scale;
    f32 rem;
    s32 i;
    s32 cur;

    if ((s8) obj[0x2C] >= 2) {
        i = (s8) obj[0x2E] - 1;
        if (i < 0) {
            i = obj[0x25] - 1;
        }
        total = 0.0f;
        while (i != (s8) obj[0x2D]) {
            cur = i;
            i--;
            if (i < 0) {
                i = obj[0x25] - 1;
            }
            e = ring + cur * 20;
            len = *(f32 *) (e + 0xC);
            total += len;
            if (1198.0f < total) {
                if (len != 0.0f) {
                    frac = (total - 1198.0f) / len;
                    prev = (f32 *) (ring + i * 20);
                    prev[0] = prev[0] - (prev[0] - ((f32 *) e)[0]) * frac;
                    prev[1] = prev[1] - (prev[1] - ((f32 *) e)[1]) * frac;
                    prev[2] = prev[2] - (prev[2] - ((f32 *) e)[2]) * frac;
                    *(f32 *) (e + 0xC) = *(f32 *) (e + 0xC) * (1.0f - frac);
                }
                total = 1198.0f;
                while (i != (s8) obj[0x2D]) {
                    obj[0x2D] = (s8) obj[0x2D] + 1;
                    if (obj[0x25] == (s8) obj[0x2D]) {
                        obj[0x2D] = 0;
                    }
                    obj[0x2C] = (s8) obj[0x2C] - 1;
                }
            }
        }
        if (total == 0.0f) {
            inv = 0.0f;
        } else {
            inv = 1.0f / total;
        }
        if ((s8) obj[0x2C] >= 2) {
            scale = 255.0f * inv;
            rem = total;
            i = (s8) obj[0x2E] - 1;
            for (;;) {
                if (i < 0) {
                    i = obj[0x25] - 1;
                }
                e = ring + i * 20;
                e[0x10] = (u32) (rem * scale);
                rem -= *(f32 *) (e + 0xC);
                if (i == (s8) obj[0x2D]) {
                    break;
                }
                i--;
            }
        }
    }
    return 1;
}

s32 gfx_set_combine_mode(s32, s32, s8 *);
s32 gfx_geometry_mode_cached(s32, s32, s32);
s32 gfx_load_texture_cached(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s8 *, s32);
u8 *gfx_other_mode_cached(s32, s32, s32, s8 *);
void vtx_slot_buffer_get(s32 *, s16, s32, s32 *, u8 *);
extern s32 D_800914B0;
extern s32 D_800D30BC;

/* was func_151B81E8 */
u8 *glow_trail_draw(u8 *arg0, u8 *arg1, s16 arg2) {
    struct {
        u8 * u90;
        u8 pad94[0x3];
        s8 u97;
        f32 u98;
        u8 pad9C[0x24];
        s32 uC0;
        f32 * uC4;
        u8 padC8[0x8];
        f32 uD0;
        f32 uD4;
        f32 uD8;
        f32 uDC;
        f32 uE0;
        f32 uE4;
    } sp;
    f32 sp7C;
    s32 *temp_v1;
    f32 *temp_v0;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f14;
    f32 temp_f14_2;
    f32 temp_f16;
    f32 temp_f16_2;
    f32 temp_f18;
    f32 temp_f18_2;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f22;
    f32 temp_f22_2;
    f32 temp_f24;
    f32 temp_f24_2;
    f32 temp_f26;
    f32 temp_f26_2;
    f32 temp_f28;
    f32 temp_f28_2;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f8;
    f32 var_f12;
    f32 var_f12_2;
    f32 var_f2;
    f32 var_f2_2;
    f32 var_f30;
    f32 var_f30_2;
    s32 temp_a0;
    s32 var_a0;
    s32 var_a1;
    u8 temp_t4;
    u8 var_a2;
    u8 *temp_s0;
    u8 *temp_t6;
    u8 *temp_t8;
    u8 *temp_t8_2;
    u8 *temp_v0_2;
    u8 *temp_v1_2;
    u8 *temp_v1_3;
    u8 *temp_v1_4;
    u8 *var_s0;

    var_s0 = arg1;
    if ((*(s8 *)((u8 *)arg0 + 0x2C)) < 2) {

    } else {
        sp.uC0 = (*(s32 *)((u8 *)arg0 + 0x94));
        vtx_slot_buffer_get(arg0 + 0x84, arg2, ((*(u8 *)((u8 *)arg0 + 0x25)) << 5) + 0xA0, &sp.u90, 0);
        if (sp.u90 == NULL) {

        } else {
            temp_v0 = camera_get_pos((s32) arg2);
            sp.u97 = 1;
            sp.uC4 = temp_v0;
            temp_v1 = ((u8 *)&g_render_mode_pairs);
            var_a0 = (*(s8 *)((u8 *)arg0 + 0x2E)) - 1;
            var_s0 = gfx_other_mode_cached(gfx_set_combine_mode(gfx_geometry_mode_cached(gfx_load_texture_cached(var_s0, &D_800914B0, 0, 0, 0, 0, 0x78, 0, 0, &sp.u97, 3), 0x200005, 0x1F0600), 0x56, &sp.u97), D_800D30BC | 0x80000 | 0x2CA0, (*(s32 *)((u8 *)temp_v1 + 0x1C)) | (*(s32 *)((u8 *)temp_v1 + 0x18)), &sp.u97);
            if (var_a0 < 0) {
                var_a0 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
            }
            var_a1 = var_a0 - 1;
            if (var_a1 < 0) {
                var_a1 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
            }
            temp_v0_2 = sp.uC0 + (var_a0 * 0x14);
            (*(f32 *)((u8 *)(&sp.uD0) + 0)) = (*(f32 *)((u8 *)temp_v0_2 + 0));
            (*(s32 *)((u8 *)(&sp.uD0) + 4)) = (s32) (*(s32 *)((u8 *)temp_v0_2 + 4));
            temp_v1_2 = sp.uC0 + (var_a1 * 0x14);
            (*(s32 *)((u8 *)(&sp.uD0) + 8)) = (s32) (*(s32 *)((u8 *)temp_v0_2 + 8));
            temp_t4 = (*(u8 *)((u8 *)temp_v0_2 + 0x10));
            (*(f32 *)((u8 *)(&sp.uDC) + 0)) = (*(f32 *)((u8 *)temp_v1_2 + 0));
            (*(s32 *)((u8 *)(&sp.uDC) + 4)) = (s32) (*(s32 *)((u8 *)temp_v1_2 + 4));
            (*(s32 *)((u8 *)(&sp.uDC) + 8)) = (s32) (*(s32 *)((u8 *)temp_v1_2 + 8));
            temp_f24 = sp.uD0 - (*(f32 *)((u8 *)sp.uC4 + 0));
            var_a2 = (*(u8 *)((u8 *)temp_v1_2 + 0x10));
            temp_f26 = sp.uD4 - (*(f32 *)((u8 *)sp.uC4 + 4));
            temp_f28 = sp.uD8 - (*(f32 *)((u8 *)sp.uC4 + 8));
            temp_f20 = sp.uD4 - sp.uE0;
            temp_f22 = sp.uD8 - sp.uE4;
            temp_f18 = sp.uD0 - sp.uDC;
            temp_f2 = (temp_f20 * temp_f28) - (temp_f26 * temp_f22);
            temp_f12 = (temp_f22 * temp_f24) - (temp_f28 * temp_f18);
            temp_f16 = (temp_f18 * temp_f26) - (temp_f24 * temp_f20);
            temp_f10 = (temp_f2 * temp_f2) + (temp_f12 * temp_f12) + (temp_f16 * temp_f16);
            sp7C = temp_f10;
            sp.u98 = temp_f10;
            if (temp_f10 != 0.0f) {
                temp_f14 = 29.0f / sqrtf(temp_f10);
                var_f2 = temp_f2 * temp_f14;
                var_f12 = temp_f12 * temp_f14;
                var_f30 = temp_f16 * temp_f14;
            } else {
                var_f30 = 0.0f;
                var_f2 = 0.0f;
                var_f12 = 0.0f;
            }
            (*(s16 *)((u8 *)sp.u90 + 0)) = (s16) (s32) (sp.uD0 + var_f2);
            (*(s16 *)((u8 *)sp.u90 + 2)) = (s16) (s32) (sp.uD4 + var_f12);
            (*(s16 *)((u8 *)sp.u90 + 4)) = (s16) (s32) (sp.uD8 + var_f30);
            (*(s16 *)((u8 *)sp.u90 + 8)) = 5;
            (*(s16 *)((u8 *)sp.u90 + 0xA)) = 0;
            (*(u8 *)((u8 *)sp.u90 + 0xF)) = temp_t4;
            (*(s16 *)((u8 *)sp.u90 + 6)) = 0;
            temp_t6 = sp.u90 + 0x10;
            sp.u90 = temp_t6;
            (*(s16 *)((u8 *)temp_t6 + 0)) = (s16) (s32) (sp.uD0 - var_f2);
            (*(s16 *)((u8 *)sp.u90 + 2)) = (s16) (s32) (sp.uD4 - var_f12);
            (*(s16 *)((u8 *)sp.u90 + 4)) = (s16) (s32) (sp.uD8 - var_f30);
            (*(s16 *)((u8 *)sp.u90 + 8)) = 0x1FA4;
            (*(s16 *)((u8 *)temp_t6 + 0xA)) = 0;
            (*(u8 *)((u8 *)sp.u90 + 0xF)) = temp_t4;
            (*(s16 *)((u8 *)sp.u90 + 6)) = 0;
            sp.u90 += 0x10;
            do {
                temp_f24_2 = sp.uDC - (*(f32 *)((u8 *)sp.uC4 + 0));
                temp_a0 = var_a1;
                temp_f26_2 = sp.uE0 - (*(f32 *)((u8 *)sp.uC4 + 4));
                var_a1 -= 1;
                temp_f28_2 = sp.uE4 - (*(f32 *)((u8 *)sp.uC4 + 8));
                temp_f20_2 = sp.uD4 - sp.uE0;
                temp_f22_2 = sp.uD8 - sp.uE4;
                temp_f18_2 = sp.uD0 - sp.uDC;
                temp_f2_2 = (temp_f20_2 * temp_f28_2) - (temp_f26_2 * temp_f22_2);
                temp_f12_2 = (temp_f22_2 * temp_f24_2) - (temp_f28_2 * temp_f18_2);
                temp_f16_2 = (temp_f18_2 * temp_f26_2) - (temp_f24_2 * temp_f20_2);
                temp_f8 = (temp_f2_2 * temp_f2_2) + (temp_f12_2 * temp_f12_2) + (temp_f16_2 * temp_f16_2);
                sp7C = temp_f8;
                sp.u98 = temp_f8;
                if (temp_f8 != 0.0f) {
                    temp_f14_2 = 29.0f / sqrtf(temp_f8);
                    var_f2_2 = temp_f2_2 * temp_f14_2;
                    var_f12_2 = temp_f12_2 * temp_f14_2;
                    var_f30_2 = temp_f16_2 * temp_f14_2;
                } else {
                    var_f30_2 = 0.0f;
                    var_f2_2 = 0.0f;
                    var_f12_2 = 0.0f;
                }
                (*(s16 *)((u8 *)sp.u90 + 0)) = (s16) (s32) (sp.uDC + var_f2_2);
                (*(s16 *)((u8 *)sp.u90 + 2)) = (s16) (s32) (sp.uE0 + var_f12_2);
                (*(s16 *)((u8 *)sp.u90 + 4)) = (s16) (s32) (sp.uE4 + var_f30_2);
                (*(s16 *)((u8 *)sp.u90 + 8)) = 5;
                (*(s16 *)((u8 *)sp.u90 + 0xA)) = 0;
                (*(u8 *)((u8 *)sp.u90 + 0xF)) = var_a2;
                (*(s16 *)((u8 *)sp.u90 + 6)) = 0;
                temp_t8 = sp.u90 + 0x10;
                sp.u90 = temp_t8;
                (*(s16 *)((u8 *)temp_t8 + 0)) = (s16) (s32) (sp.uDC - var_f2_2);
                (*(s16 *)((u8 *)sp.u90 + 2)) = (s16) (s32) (sp.uE0 - var_f12_2);
                (*(s16 *)((u8 *)sp.u90 + 4)) = (s16) (s32) (sp.uE4 - var_f30_2);
                (*(s16 *)((u8 *)sp.u90 + 8)) = 0x1FA4;
                (*(s16 *)((u8 *)temp_t8 + 0xA)) = 0;
                (*(u8 *)((u8 *)sp.u90 + 0xF)) = var_a2;
                (*(s16 *)((u8 *)sp.u90 + 6)) = 0;
                sp.u90 += 0x10;
                (*(s32 *)((u8 *)var_s0 + 0)) = 0x01004008;
                temp_s0 = var_s0 + 8;
                temp_v1_3 = temp_s0;
                (*(u8 **)((u8 *)var_s0 + 4)) = (u8 *) (sp.u90 - 0x40);
                var_s0 = temp_s0 + 8;
                (*(s32 *)((u8 *)temp_v1_3 + 0)) = 0x06000204;
                (*(s32 *)((u8 *)temp_v1_3 + 4)) = 0x20604;
                if (var_a1 < 0) {
                    var_a1 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
                }
                if (temp_a0 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
                    temp_t8_2 = sp.uC0 + (temp_a0 * 0x14);
                    (*(f32 *)((u8 *)(&sp.uD0) + 0)) = (*(f32 *)((u8 *)temp_t8_2 + 0));
                    (*(s32 *)((u8 *)(&sp.uD0) + 4)) = (s32) (*(s32 *)((u8 *)temp_t8_2 + 4));
                    temp_v1_4 = sp.uC0 + (var_a1 * 0x14);
                    (*(s32 *)((u8 *)(&sp.uD0) + 8)) = (s32) (*(s32 *)((u8 *)temp_t8_2 + 8));
                    (*(f32 *)((u8 *)(&sp.uDC) + 0)) = (*(f32 *)((u8 *)temp_v1_4 + 0));
                    (*(s32 *)((u8 *)(&sp.uDC) + 4)) = (s32) (*(s32 *)((u8 *)temp_v1_4 + 4));
                    (*(s32 *)((u8 *)(&sp.uDC) + 8)) = (s32) (*(s32 *)((u8 *)temp_v1_4 + 8));
                    var_a2 = (*(u8 *)((u8 *)temp_v1_4 + 0x10));
                }
            } while (temp_a0 != (*(s8 *)((u8 *)arg0 + 0x2D)));
        }
    }
    return var_s0;
}
/* was func_151B887C */
void glow_handle_message(u8 *arg0, s32 arg1, u8 arg2) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);
    void (*temp_v1)(u8 *, s32, u8) = D_8008FF38[temp_v0[8]];

    if (temp_v1 != NULL) {
        temp_v1(arg0, arg1, arg2);
    }
}

/* was func_151B88C8 */
void glow_attach_obj_on_message(u8 *arg0, s32 *arg1, u8 arg2) {
    u8 *q = *(u8 **)(arg0 + 0x98);
    u8 *p = *(u8 **)(q + 4);
    s32 id;
    if (arg2 == 0) {
        id = arg1[0];
        if (id == *(s32 *)p || p[4] == ((u8 *)arg1)[4]) {
            node_destroy(arg0);
        }
    }
}

/* was func_151B8920 */
void glow_free_particle(u8 *arg0) {
    struct102 **temp_v0 = *(struct102 ***)(arg0 + 0x98);
    struct102 *temp_a1 = *temp_v0;

    if (temp_a1 != NULL) {
        node_destroy(temp_a1);
    }
}

/* was func_151B8950 */
void glow_retire(s32 arg0) {
    glow_free_particle(arg0);
    fxrec_die_retire(arg0);
}

/* was func_151B897C */
void glow_delete(s32 arg0) {
    glow_free_particle(arg0);
    fxrec_die_free(arg0);
}
