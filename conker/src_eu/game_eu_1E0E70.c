#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 memcpy(u8 *, s32, s32);
extern f32 D_800AA770;

/* was func_151B3660 */
u8 *cord_spawn(s32 arg0, f32 arg1, s32 arg2, u8 arg3, s32 arg4) {
    u8 *temp_v0;
    f32 temp_f0;
    u8 *sp24;

    temp_v0 = node_alloc(0x33, arg4, arg2 + 0x150, 1, (u8) (s32) arg3, 1U);
    if (temp_v0 == NULL) {
        return NULL;
    }
    sp24 = temp_v0;
    memcpy(temp_v0 + 0x10, arg0, 0x38);
    temp_f0 = (*(f32 *)((u8 *)temp_v0 + 0x38));
    (*(u8 *)((u8 *)temp_v0 + 0x10)) = (u8) ((*(u8 *)((u8 *)temp_v0 + 0x10)) | 0xE);
    (*(f32 *)((u8 *)temp_v0 + 0x138)) = (f32) (2.0f * ((temp_f0 * temp_f0) / D_800AA770));
    (*(s32 *)((u8 *)temp_v0 + 0x13C)) = (s32) (temp_f0 * arg1 * 4096.0f);
    bzero(temp_v0 + 0x140, 0x10);
    return sp24;
}

typedef struct { u8 pad0[0x10]; u8 flags; u8 pad11; s16 y; f32 x14[3]; f32 x20[3]; s8 x2C; s8 x2D; u8 pad2E[6]; s8 x34; } Obj_151B3734;
extern s32 (*D_8008FE90[])(Obj_151B3734 *, f32 *, s32);
extern s32 (*D_8008FE98[])(Obj_151B3734 *);
/* was func_151B3734 */
void cord_update(Obj_151B3734 *arg0) {
    s32 pad; // fakematch: moves the byte spill slot
    u8 done = 0;

    if (arg0->flags & 1) {
        arg0->y -= D_800BE9E4;
        if (arg0->y < 0) {
            done = 1;
        }
    }
    if (!done) {
        if (arg0->x2C != -1) {
            if (!D_8008FE90[arg0->x2C](arg0, arg0->x14, 1)) {
                done = 1;
            }
        }
        if (arg0->x2D != -1) {
            if (!D_8008FE90[arg0->x2D](arg0, arg0->x20, 0)) {
                done = 1;
            }
        }
        if ((arg0->flags & 4) || (arg0->flags & 8)) {
            arg0->flags |= 2;
        } else if (arg0->x34 != -1) {
            if (!D_8008FE98[arg0->x34](arg0)) {
                done = 1;
            }
        }
    }
    if (done) {
        node_destroy((struct102 *)arg0);
    }
}

void vtx_slot_buffer_get(s32 *, s16, s32, Vtx **, u8 *);
s32 gfx_geometry_mode_cached(s32, s32, s32);
s32 gfx_env_color_cached(s32, s32, s32, s32, s32, s8 *);
s32 gfx_prim_color_cached(s32, s32, s32, s32, s32, s32, s32, s8 *);
s32 gfx_set_combine_mode(s32, u8, s8 *);
s32 gfx_load_texture_cached(s32, s32 *, s32, s32, s32, s32, s32, s32, s32, s8 *, s32);
s32 gfx_other_mode_cached(s32, s32, s32, s8 *);
/* rope style getters (by obj +0x2E): geometry mode set / clear, prim colour, env colour, combine, render mode,
   render-mode pair index; 0 = draw nothing */
extern s32 (*D_8008FEB0[])(u8 *, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *, u8 *,
                           u8 *);
extern s32 D_80091198;   /* rope texture descriptor */
extern s32 D_800D30BC;
extern s32 g_render_mode_pairs[]; /* render mode pairs (2 words each); was D_800A4EA8 */

/* n = (b - a) x (p - cam), scaled to the rope width obj +0x30 (0 when degenerate) */
#define ROPE_NORMAL(px, py, pz) \
    do { \
        ex = bx - ax; \
        ey = by - ay; \
        ez = bz - az; \
        cx = (px) - cam[0]; \
        cy = (py) - cam[1]; \
        cz = (pz) - cam[2]; \
        nx = ey * cz - cy * ez; \
        ny = ez * cx - cz * ex; \
        nz = ex * cy - cx * ey; \
        len2 = nx * nx + ny * ny + nz * nz; \
        if (len2 == 0.0f) { \
            nx = ny = nz = 0.0f; \
        } else { \
            k = *(f32 *) (obj + 0x30) / sqrtf(len2); \
            nx *= k; \
            ny *= k; \
            nz *= k; \
        } \
    } while (0)

/* one rope vertex: position, texture (s, t), colour (255, 100, 100, 255) */
#define ROPE_VTX(px, py, pz, s, t) \
    do { \
        v->v.ob[0] = (px); \
        v->v.ob[1] = (py); \
        v->v.ob[2] = (pz); \
        v->v.tc[0] = (s); \
        v->v.tc[1] = (t); \
        v->v.cn[0] = 0xFF; \
        v->v.cn[1] = 100; \
        v->v.cn[2] = 100; \
        v->v.cn[3] = 0xFF; \
        v++; \
    } while (0)

// rope_draw: draws the 10-point rope (obj +0x48, 0x18 bytes per point) as a camera-facing ribbon for view `id`
// (camera at D_800DBFF0 + id * 0x9A0 + 0x2F8). Nothing when obj +0x10 has flag 4, 8 or 2, when vtx_slot_buffer_get gives
// no vertices (0x190 bytes from the cache at obj +0x140) or when the style getter D_8008FEB0[obj +0x2E] returns 0.
// The getter's values set the geometry mode, prim / env colours, combine, render mode (| 0x80000 | 0x2CA0 |
// D_800D30BC with the g_render_mode_pairs pair) and the texture D_80091198. Each point gets two vertices offset by +-n
// (ROPE_NORMAL), s = 0 / 0x3C0 across, t growing by obj +0x13C per point; each segment loads 4 vertices and draws
// two triangles. Returns the display list end.
/* was func_151B3878 */
s32 cord_draw(s32 gfx, u8 *obj, s16 id) {
    Vtx *v;
    f32 *cam;
    f32 *pts;
    s32 geoSet, geoClr, envR, envG, envB, envA, primR, primG, primB, primA, combine, rmode;
    u8 rmodePair, tex;
    s8 flag;
    s32 t;
    s32 i;
    f32 ax, ay, az;
    f32 bx, by, bz;
    f32 ex, ey, ez;
    f32 cx, cy, cz;
    f32 nx, ny, nz;
    f32 len2;
    f32 k;

    if (obj[0x10] & 4) {
        return gfx;
    }
    if (obj[0x10] & 8) {
        return gfx;
    }
    if (obj[0x10] & 2) {
        return gfx;
    }
    vtx_slot_buffer_get((s32 *) (obj + 0x140), id, 0x190, &v, NULL);
    if (v == NULL) {
        return gfx;
    }
    cam = (f32 *) ((u8 *) D_800DBFF0 + id * 0x9A0 + 0x2F8);
    flag = 1;
    if (!D_8008FEB0[obj[0x2E]](obj, &geoSet, &geoClr, &envR, &envG, &envB, &envA, &primR, &primG, &primB, &primA,
                               &rmode, &rmodePair, &tex)) {
        return gfx;
    }
    gfx = gfx_geometry_mode_cached(gfx, geoSet, geoClr);
    gfx = gfx_env_color_cached(gfx, primR, primG, primB, primA, &flag);
    gfx = gfx_prim_color_cached(gfx, 0, 0, envR, envG, envB, envA, &flag);
    gfx = gfx_set_combine_mode(gfx, tex, &flag);
    gfx = gfx_load_texture_cached(gfx, &D_80091198, 0, 0, 0, 0, 0x36, 0, 0, &flag, 3);
    gfx = gfx_other_mode_cached(gfx, rmode | 0x80000 | D_800D30BC | 0x2CA0,
                        g_render_mode_pairs[rmodePair * 2 + 1] | g_render_mode_pairs[rmodePair * 2], &flag);

    /* the first point, offset across the first segment */
    pts = (f32 *) (obj + 0x48);
    ax = pts[0];
    ay = pts[1];
    az = pts[2];
    bx = pts[6];
    by = pts[7];
    bz = pts[8];
    ROPE_NORMAL(ax, ay, az);
    ROPE_VTX(ax + nx, ay + ny, az + nz, 0, 0);
    ROPE_VTX(ax - nx, ay - ny, az - nz, 0x3C0, 0);

    /* one segment per following point */
    t = *(s32 *) (obj + 0x13C);
    for (i = 0; i < 9; i++) {
        ax = pts[i * 6 + 0];
        ay = pts[i * 6 + 1];
        az = pts[i * 6 + 2];
        bx = pts[i * 6 + 6];
        by = pts[i * 6 + 7];
        bz = pts[i * 6 + 8];
        ROPE_NORMAL(bx, by, bz);
        ROPE_VTX(bx + nx, by + ny, bz + nz, 0, t);
        ROPE_VTX(bx - nx, by - ny, bz - nz, 0x3C0, t);
        t += *(s32 *) (obj + 0x13C);
        ((s32 *) gfx)[0] = 0x01004008; /* gSPVertex(v - 4, 4, 0) */
        ((s32 *) gfx)[1] = (s32) (v - 4);
        gfx += 8;
        ((s32 *) gfx)[0] = 0x05000204; /* gSP1Triangle(0, 1, 2) */
        ((s32 *) gfx)[1] = 0;
        gfx += 8;
        ((s32 *) gfx)[0] = 0x05020604; /* gSP1Triangle(1, 3, 2) */
        ((s32 *) gfx)[1] = 0;
        gfx += 8;
    }
    return gfx;
}

/* was func_151B3FE4 */
void cord_handle_message(u8 *arg0, s32 arg1, u8 arg2) {
    void (*fp)(void *, s32, u8) = D_8008FF08[arg0[0x44]];
    if (fp != NULL) {
        fp(arg0, arg1, arg2);
    }
}

// rope_nodes_reset: lays the 10 rope nodes (obj + 0x48, 0x18 bytes: pos, vel) evenly from the start point +0x14
// towards the end point +0x20 (step = (end - start) / 9, D_800AA774 .. D_800AA77C), zeroes their velocities and
// clears flag 2 at +0x10. Returns 1. (Table entry next to cord_shape_arc; also the fallback of cord_shape_ellipse /
// cord_update_sag, which call it with their own a0.)
/* was func_151B402C */
s32 cord_nodes_reset_straight(u8 *obj) {
    f32 *start = (f32 *) (obj + 0x14);
    f32 *end = (f32 *) (obj + 0x20);
    f32 p[3];
    f32 step[3];
    f32 *node;
    s32 i;

    step[0] = (end[0] - start[0]) * 0.11111111f;
    step[1] = (end[1] - start[1]) * 0.11111111f;
    step[2] = (end[2] - start[2]) * 0.11111111f;
    p[0] = start[0];
    p[1] = start[1];
    p[2] = start[2];
    for (i = 0; i < 10; i++) {
        node = (f32 *) (obj + 0x48 + i * 0x18);
        node[0] = p[0];
        node[1] = p[1];
        node[2] = p[2];
        node[3] = 0.0f;
        node[4] = 0.0f;
        node[5] = 0.0f;
        p[0] += step[0];
        p[1] += step[1];
        p[2] += step[2];
    }
    obj[0x10] &= ~2;
    return 1;
}
/* was func_151B42A0 */
s32 cord_shape_arc(u8 *arg0) {
    f32 sp80;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 temp_f0;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f14_2;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f22_2;
    f32 temp_f22_3;
    f32 temp_f24;
    f32 temp_f24_2;
    f32 temp_f24_3;
    f32 temp_f26;
    f32 temp_f26_2;
    f32 temp_f28;
    f32 temp_f28_2;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f30;
    f32 temp_f4;
    f32 temp_f6;
    f32 var_f20;
    s32 var_s1;
    u8 *temp_s0;
    u8 *var_s2;

    temp_f26 = (*(f32 *)((u8 *)arg0 + 0x20));
    temp_f2 = (*(f32 *)((u8 *)arg0 + 0x14));
    temp_f28 = (*(f32 *)((u8 *)arg0 + 0x24));
    temp_f12 = (*(f32 *)((u8 *)arg0 + 0x18));
    temp_f18 = temp_f26 - temp_f2;
    temp_f0 = fabsf(temp_f18);
    sp80 = temp_f28 - temp_f12;
    temp_f14 = (*(f32 *)((u8 *)arg0 + 0x1C));
    temp_f30 = (*(f32 *)((u8 *)arg0 + 0x28));
    temp_f20 = temp_f30 - temp_f14;
    if ((temp_f0 > 0.0001f) || (fabsf(temp_f20) > 0.0001f)) {
        temp_f16 = temp_f2 + (temp_f18 * 0.5f);
        sp70 = temp_f16;
        temp_f4 = temp_f2 - temp_f16;
        temp_f22 = temp_f12 + (sp80 * 0.5f);
        sp64 = temp_f4;
        temp_f24 = temp_f14 + (temp_f20 * 0.5f);
        sp74 = temp_f22;
        temp_f10 = temp_f26 - temp_f16;
        sp78 = temp_f24;
        sp58 = temp_f10;
        sp6C = temp_f14 - temp_f24;
        sp5C = temp_f28 - temp_f22;
        sp68 = temp_f12 - temp_f22;
        temp_f6 = temp_f30 - temp_f24;
        sp60 = temp_f6;
        temp_f22_2 = 1.0f / sqrtf((temp_f18 * temp_f18) + (temp_f20 * temp_f20));
        temp_f26_2 = temp_f20 * temp_f22_2;
        temp_f28_2 = temp_f18 * temp_f22_2;
        temp_f14_2 = ((temp_f6 * temp_f26_2) + (temp_f10 * temp_f28_2)) - ((sp6C * temp_f26_2) + (temp_f4 * temp_f28_2));
        temp_f24_2 = sp5C - sp68;
        var_s1 = 0;
        var_s2 = arg0 + 0x48;
        var_f20 = math_atan2f(temp_f24_2, temp_f14_2) - 3.1415927f;
        temp_f22_3 = sqrtf((temp_f14_2 * temp_f14_2) + (temp_f24_2 * temp_f24_2)) * 0.5f;
        do {
            temp_s0 = var_s2;
            temp_f24_3 = sinf(var_f20);
            temp_f2_2 = temp_f22_3 * cosf(var_f20);
            var_s1 += 0x18;
            var_s2 += 0x18;
            (*(f32 *)((u8 *)temp_s0 + 0)) = (f32) ((temp_f2_2 * temp_f28_2) + sp70);
            (*(f32 *)((u8 *)temp_s0 + 4)) = (f32) ((temp_f22_3 * temp_f24_3) + sp74);
            (*(f32 *)((u8 *)temp_s0 + 8)) = (f32) ((temp_f2_2 * temp_f26_2) + sp78);
            var_f20 += 0.34906587f;
        } while (var_s1 != 0xF0);
    }
    return 1;
}
extern f32 D_800AA78C;
/* was func_151B44D8 */
s32 cord_end_get_obj_pos(u8 *arg0, f32 *arg1, u8 arg2)
{
  s32 var_v1 = 1;
  u8 *p;
  if (arg2 != 0) {
    u8 *o;
    f32 *dst = arg1;
    p = arg0 + 0x150;
    if (**(s32 **)(arg0 + 0x150) != 0 && p[4] == (o = *(u8 **)p)[0x3B]) {
      dst[0] = *(f32 *)(o + 0x14);
      dst[1] = *(f32 *)(*(u8 **)p + 0x18);
      dst[2] = *(f32 *)(*(u8 **)p + 0x1C);
      arg0[0x10] &= 0xFFFB;
    } else {
      var_v1 = 0;
      arg0[0x10] |= 0xC;
    }
  } else {
    arg1[0] = 0.0f;
    arg1[1] = D_800AA78C;
    arg1[2] = 0.0f;
    arg0[0x10] &= 0xFFF7;
  }
  return var_v1;
}

s32 cord_nodes_reset_straight(u8 *);

/* was func_151B458C */
s32 cord_shape_ellipse(u8 *arg0) {
    f32 sp110;
    f32 sp108;
    f32 sp104;
    f32 sp100;
    f32 spFC;
    f32 spF8;
    f32 spF4;
    f32 spF0;
    f32 spEC;
    f32 spE8;
    f32 spD0;
    f32 spAC;
    f32 spA4;
    f32 sp98;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp5C;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f10;
    f32 temp_f10_2;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f14;
    f32 temp_f14_2;
    f32 temp_f16;
    f32 temp_f16_2;
    f32 temp_f16_3;
    f32 temp_f18;
    f32 temp_f18_2;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f22_2;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f26_2;
    f32 temp_f28;
    f32 temp_f28_2;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f2_4;
    f32 temp_f30;
    f32 temp_f30_2;
    f32 temp_f4;
    f32 temp_f6;
    f32 var_f20;
    s32 var_s1;
    u8 *var_s2;

    temp_f28 = (*(f32 *)((u8 *)arg0 + 0x20));
    temp_f2 = (*(f32 *)((u8 *)arg0 + 0x14));
    temp_f30 = (*(f32 *)((u8 *)arg0 + 0x24));
    temp_f12 = (*(f32 *)((u8 *)arg0 + 0x18));
    temp_f20 = temp_f28 - temp_f2;
    temp_f0 = fabsf(temp_f20);
    sp110 = temp_f30 - temp_f12;
    temp_f16 = (*(f32 *)((u8 *)arg0 + 0x28));
    temp_f14 = (*(f32 *)((u8 *)arg0 + 0x1C));
    sp5C = temp_f16;
    temp_f26 = temp_f16 - temp_f14;
    if ((temp_f0 > 0.0001f) || (fabsf(temp_f26) > 0.0001f)) {
        temp_f16_2 = temp_f2 + (temp_f20 * 0.5f);
        sp100 = temp_f16_2;
        temp_f18 = temp_f12 + (sp110 * 0.5f);
        spF4 = temp_f2 - temp_f16_2;
        temp_f22 = temp_f14 + (temp_f26 * 0.5f);
        sp104 = temp_f18;
        sp108 = temp_f22;
        spE8 = temp_f28 - temp_f16_2;
        spEC = temp_f30 - temp_f18;
        spF8 = temp_f12 - temp_f18;
        spFC = temp_f14 - temp_f22;
        temp_f10 = sp5C - temp_f22;
        temp_f0_2 = sqrtf((temp_f20 * temp_f20) + (temp_f26 * temp_f26));
        spF0 = temp_f10;
        temp_f2_2 = 1.0f / temp_f0_2;
        temp_f28_2 = temp_f26 * temp_f2_2;
        temp_f30_2 = temp_f20 * temp_f2_2;
        temp_f16_3 = ((temp_f10 * temp_f28_2) + (spE8 * temp_f30_2)) - ((spFC * temp_f28_2) + (spF4 * temp_f30_2));
        temp_f18_2 = spEC - spF8;
        spD0 = temp_f16_3;
        temp_f4 = (temp_f16_3 * temp_f16_3) + (temp_f18_2 * temp_f18_2);
        temp_f0_3 = sqrtf(temp_f4);
        sp64 = temp_f4;
        spA4 = temp_f4;
        temp_f2_3 = 1.0f / temp_f0_3;
        spAC = temp_f0_3 * 0.5f;
        temp_f10_2 = (*(f32 *)((u8 *)arg0 + 0x138));
        sp68 = temp_f10_2;
        temp_f22_2 = spD0 * temp_f2_3;
        temp_f24 = temp_f18_2 * temp_f2_3;
        temp_f6 = temp_f4 * 0.25f;
        sp6C = temp_f6;
        if (temp_f10_2 < sp6C) {
            return cord_nodes_reset_straight(arg0); /* P274: was (temp_f12, temp_f14); the asm passes its own a0 */
        }
        var_f20 = 0.0f;
        var_s1 = 0;
        var_s2 = arg0 + 0x48;
        sp98 = sqrtf(sp68 - temp_f6);
        do {
            temp_f26_2 = sinf(var_f20);
            var_s1 += 0x18;
            temp_f2_4 = spAC * cosf(var_f20);
            temp_f12_2 = sp98 * temp_f26_2;
            temp_f14_2 = (temp_f2_4 * temp_f22_2) - (temp_f12_2 * temp_f24);
            (*(f32 *)((u8 *)var_s2 + 0)) = (f32) ((temp_f14_2 * temp_f30_2) + sp100);
            (*(f32 *)((u8 *)var_s2 + 4)) = (f32) (((temp_f2_4 * temp_f24) - (temp_f12_2 * temp_f22_2)) + sp104);
            (*(f32 *)((u8 *)var_s2 + 8)) = (f32) ((temp_f14_2 * temp_f28_2) + sp108);
            var_s2 += 0x18;
            var_f20 += 0.34906587f;
        } while (var_s1 != 0xF0);
        goto block_6;
    }
block_6:
    return 1;
}

/* P292 */

// rope_update_sag: entry 5 of the rope handler table at EU 0x8008FE90 (siblings cord_nodes_reset_straight / cord_shape_ellipse).
// The rope of obj runs from end0 (+0x14) to end1 (+0x20); its 10 points (+0x48, 0x18 bytes: pos, vel) hang on an
// ellipse in the vertical plane through both ends (half axes |end1 - end0| / 2 and sqrt(+0x138 - len^2 / 4), +0x138 =
// the squared half rope length). When the ends are closer than 0.0001 horizontally nothing moves; when they are too
// far apart the rope goes taut (cord_nodes_reset_straight, whose result is returned). Each point i takes the ellipse point at
// angle i * 0.349 (20 degrees): placed there with zero speed while flag 2 of +0x10 is set (then cleared), or with the
// rest speed D_800A5860 while g_camera_timers is set; otherwise it springs towards it (pull (old - target) * sin(angle) *
// +0x40, acceleration * +0x3C over the frame time D_800BE9A4). Returns 1 except for the taut case.
/* was func_151B4854 */
s32 cord_update_sag(u8 *obj) {
    f32 *seg;
    f32 old[3];
    f32 target[3];
    f32 x0, y0, z0;
    f32 dx, dy, dz;
    f32 mx, my, mz;
    f32 a0x, a0y, a0z;
    f32 a1x, a1y, a1z;
    f32 inv;
    f32 px, pz;
    f32 du, dv;
    f32 lenSq;
    f32 len;
    f32 halfLen;
    f32 cosA, sinA;
    f32 sag;
    f32 quarter;
    f32 angle;
    f32 angle2;
    f32 s, c, s2;
    f32 u, v;
    f32 pull[3];
    f32 acc[3];
    f32 k;
    s32 i;
    u8 ret;

    ret = 1;
    x0 = *(f32 *) (obj + 0x14);
    y0 = *(f32 *) (obj + 0x18);
    z0 = *(f32 *) (obj + 0x1C);
    dx = *(f32 *) (obj + 0x20) - x0;
    dy = *(f32 *) (obj + 0x24) - y0;
    dz = *(f32 *) (obj + 0x28) - z0;
    if (fabsf(dx) > 0.0001f || fabsf(dz) > 0.0001f) {
        mx = x0 + dx * 0.5f;
        my = y0 + dy * 0.5f;
        mz = z0 + dz * 0.5f;
        a0x = x0 - mx;
        a1x = *(f32 *) (obj + 0x20) - mx;
        a1y = *(f32 *) (obj + 0x24) - my;
        a0y = y0 - my;
        a0z = z0 - mz;
        a1z = *(f32 *) (obj + 0x28) - mz;
        inv = 1.0f / sqrtf(dx * dx + dz * dz);
        pz = dz * inv;
        px = dx * inv;
        du = (a1z * pz + a1x * px) - (a0z * pz + a0x * px);
        dv = a1y - a0y;
        lenSq = du * du + dv * dv;
        len = sqrtf(lenSq);
        inv = 1.0f / len;
        halfLen = len * 0.5f;
        cosA = du * inv;
        sinA = dv * inv;
        quarter = lenSq * 0.25f;
        if (*(f32 *) (obj + 0x138) < quarter) {
            ret = cord_nodes_reset_straight(obj);
        } else {
            sag = sqrtf(*(f32 *) (obj + 0x138) - quarter);
            angle = 0.0f;
            angle2 = 0.0f;
            seg = (f32 *) (obj + 0x48);
            for (i = 0; i < 10; i++) {
                ((s32 *) old)[0] = ((s32 *) seg)[0];
                ((s32 *) old)[1] = ((s32 *) seg)[1];
                ((s32 *) old)[2] = ((s32 *) seg)[2];
                s = sinf(angle);
                c = cosf(angle);
                s2 = sinf(angle2);
                u = halfLen * c;
                v = sag * s;
                target[0] = (u * cosA - v * sinA) * px + mx;
                target[1] = (u * sinA - v * cosA) + my;
                target[2] = (u * cosA - v * sinA) * pz + mz;
                if (obj[0x10] & 2) {
                    ((s32 *) seg)[0] = ((s32 *) target)[0];
                    ((s32 *) seg)[1] = ((s32 *) target)[1];
                    ((s32 *) seg)[2] = ((s32 *) target)[2];
                    seg[3] = 0.0f;
                    seg[4] = 0.0f;
                    seg[5] = 0.0f;
                } else if (*(s32 *) g_camera_timers != 0) {
                    ((s32 *) seg)[0] = ((s32 *) target)[0];
                    ((s32 *) seg)[1] = ((s32 *) target)[1];
                    ((s32 *) seg)[2] = ((s32 *) target)[2];
                    ((s32 *) seg)[3] = ((s32 *) D_800A5860)[0];
                    ((s32 *) seg)[4] = ((s32 *) D_800A5860)[1];
                    ((s32 *) seg)[5] = ((s32 *) D_800A5860)[2];
                } else {
                    k = *(f32 *) (obj + 0x40);
                    pull[0] = (old[0] - target[0]) * s2 * k;
                    pull[1] = (old[1] - target[1]) * s2 * k;
                    pull[2] = (old[2] - target[2]) * s2 * k;
                    seg[0] = target[0] + pull[0];
                    seg[1] = target[1] + pull[1];
                    seg[2] = target[2] + pull[2];
                    k = *(f32 *) (obj + 0x3C);
                    acc[0] = k * pull[0];
                    acc[1] = k * pull[1];
                    acc[2] = k * pull[2];
                    seg[0] = seg[0] + (seg[3] * D_800BE9A4 + 0.5f * acc[0] * D_800BE9A4 * D_800BE9A4);
                    seg[1] = seg[1] + (seg[4] * D_800BE9A4 + 0.5f * acc[1] * D_800BE9A4 * D_800BE9A4);
                    seg[2] = seg[2] + (seg[5] * D_800BE9A4 + 0.5f * acc[2] * D_800BE9A4 * D_800BE9A4);
                    seg[3] = seg[3] + acc[0] * D_800BE9A4;
                    seg[4] = seg[4] + acc[1] * D_800BE9A4;
                    seg[5] = seg[5] + acc[2] * D_800BE9A4;
                }
                angle2 += 0.34906587f;
                angle += 0.34906587f;
                seg += 6;
            }
        }
    }
    obj[0x10] &= ~2;
    return ret;
}

/* was func_151B4D88 */
s32 cord_end_get_bone_pos(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3) {
    s32 var_a2;
    s32 temp_t6;
    u8 *temp_v0;
    u8 *temp_v1;
    u8 *var_a0;
    u8 *var_a2_2;

    temp_t6 = arg3 & 0xFF;
    temp_v0 = (*(u8 **)((u8 *)arg1 + 0));
    temp_v1 = (*(u8 **)((u8 *)arg1 + 0x14));
    if (((*(s32 *)((u8 *)temp_v0 + 0x1D4)) == 0) || ((*(s32 *)((u8 *)temp_v1 + 0x1D4)) == 0)) {
        (*(u8 *)((u8 *)arg0 + 0x10)) = (u8) ((*(u8 *)((u8 *)arg0 + 0x10)) | 0xC);
        return 1;
    }
    if (((*(s32 *)((u8 *)temp_v0 + 0)) == 0) || ((*(u8 *)((u8 *)arg1 + 4)) != (*(u8 *)((u8 *)temp_v0 + 0x3B))) || ((*(s32 *)((u8 *)temp_v1 + 0)) == 0) || ((*(u8 *)((u8 *)arg1 + 0x18)) != (*(u8 *)((u8 *)temp_v1 + 0x3B)))) {
        return 0;
    }
    var_a2 = 8;
    if (temp_t6 != 0) {
        var_a2 = 4;
    }
    (*(u8 *)((u8 *)arg0 + 0x10)) = (u8) ((*(u8 *)((u8 *)arg0 + 0x10)) & ~var_a2);
    if (temp_t6 != 0) {
        var_a0 = arg1 + 8;
    } else {
        var_a0 = arg1 + 0x1C;
    }
    if (temp_t6 != 0) {
        var_a2_2 = (*(s32 *)((u8 *)temp_v0 + 0x1D4)) + ((*(u8 *)((u8 *)arg1 + 5)) << 6);
    } else {
        var_a2_2 = (*(s32 *)((u8 *)temp_v1 + 0x1D4)) + ((*(u8 *)((u8 *)arg1 + 0x19)) << 6);
    }
    mtx_transform_point_or_origin(var_a0, arg2, var_a2_2);
    return 1;
}
/* was func_151B4E8C */
s32 cord_nodes_reset_x_line(u8 *arg0) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f14_2;
    f32 temp_f14_3;
    f32 temp_f14_4;
    f32 var_f14;
    s32 var_v0;
    u8 *var_v1;

    temp_f0 = (*(f32 *)((u8 *)arg0 + 0x14));
    (*(f32 *)((u8 *)arg0 + 0x48)) = temp_f0;
    (*(f32 *)((u8 *)arg0 + 0x4C)) = 0.0f;
    (*(f32 *)((u8 *)arg0 + 0x50)) = 0.0f;
    var_v0 = 2;
    temp_f12 = -(temp_f0 - (*(f32 *)((u8 *)arg0 + 0x20))) * 0.1f;
    var_v1 = arg0 + 0x30;
    (*(f32 *)((u8 *)arg0 + 0x68)) = 0.0f;
    (*(f32 *)((u8 *)arg0 + 0x64)) = 0.0f;
    temp_f14 = temp_f0 + temp_f12;
    (*(f32 *)((u8 *)arg0 + 0x60)) = temp_f14;
    var_f14 = temp_f14 + temp_f12;
    do {
        (*(f32 *)((u8 *)var_v1 + 0x48)) = var_f14;
        (*(f32 *)((u8 *)var_v1 + 0x4C)) = 0.0f;
        (*(f32 *)((u8 *)var_v1 + 0x50)) = 0.0f;
        temp_f14_2 = var_f14 + temp_f12;
        var_v0 += 4;
        (*(f32 *)((u8 *)var_v1 + 0x64)) = 0.0f;
        (*(f32 *)((u8 *)var_v1 + 0x68)) = 0.0f;
        (*(f32 *)((u8 *)var_v1 + 0x60)) = temp_f14_2;
        temp_f14_3 = temp_f14_2 + temp_f12;
        (*(f32 *)((u8 *)var_v1 + 0x7C)) = 0.0f;
        (*(f32 *)((u8 *)var_v1 + 0x80)) = 0.0f;
        (*(f32 *)((u8 *)var_v1 + 0x94)) = 0.0f;
        (*(f32 *)((u8 *)var_v1 + 0x78)) = temp_f14_3;
        temp_f14_4 = temp_f14_3 + temp_f12;
        (*(f32 *)((u8 *)var_v1 + 0x98)) = 0.0f;
        var_v1 += 0x60;
        (*(f32 *)((u8 *)var_v1 + 0x30)) = temp_f14_4;
        var_f14 = temp_f14_4 + temp_f12;
    } while (var_v0 != 0xA);
    (*(u8 *)((u8 *)arg0 + 0x10)) = (u8) ((*(u8 *)((u8 *)arg0 + 0x10)) & 0xFFFD);
    return 1;
}
/* was func_151B4F3C */
s32 cord_style_default(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4, s32 *arg5, s32 *arg6, s32 *arg7, s32 *arg8, s32 *arg9, s32 *argA, s32 *argB, s8 *argC, s8 *argD) {
    *arg1 = 0x220005;
    *arg2 = 0x40600;
    *arg3 = 0xFF;
    *arg4 = 0xFF;
    *arg5 = 0xFF;
    *arg6 = 0xFF;
    *arg7 = 0xFF;
    *arg8 = 0xFF;
    *arg9 = 0xFF;
    *argA = 0xFF;
    *argB = 0;
    *argC = 5;
    *argD = 0x2B;
    return 1;
}

void obj_tint_get_colour(u8 *, s32 *, s32 *, s32 *, s32 *);
/* was func_151B4FC4 */
u8 cord_style_owner_colour(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4, s32 *arg5, s32 *arg6, s32 *arg7, s32 *arg8, s32 *arg9, s32 *argA, s32 *argB, s8 *argC, s8 *argD) {
    u8 ret;
    s32 pad[2]; // fakematch: frame slots between ret and t
    u8 *t;
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    u32 sp48; // fakematch: unsigned puts the copy in v0
    s32 v;
    s32 pad2; // fakematch: frame slot below sp48

    ret = 1;
    t = *(u8 **)(arg0 + 0x150);
    obj_tint_get_colour(t, &sp54, &sp50, &sp4C, (s32 *)&sp48);
    if (t[0xA4] & 1) {
        *arg1 = 0x200005;
        *arg2 = 0x60600;
        *arg3 = sp54;
        *arg4 = sp50;
        *arg5 = sp4C;
        *arg6 = 0xFF;
        *arg9 = v = sp48;
        *arg8 = v;
        *arg7 = v;
        *argA = 0xFF;
        *argB = 0x100000;
        *argC = 5;
        *argD = 0x2F;
    } else {
        ret = cord_style_default(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, argA, argB, argC, argD);
    }
    return ret;
}

/* was func_151B5128 */
s32 cord_nodes_reset_preset(u8 *arg0) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 var_f0;
    s32 var_v0;
    u8 *var_v1;

    (*(f32 *)((u8 *)arg0 + 0x48)) = -1000.0f;
    temp_f0 = -1000.0f + 222.22223f;
    var_v0 = 2;
    var_v1 = arg0 + 0x30;
    (*(f32 *)((u8 *)arg0 + 0x60)) = temp_f0;
    var_f0 = temp_f0 + 222.22223f;
    (*(f32 *)((u8 *)arg0 + 0x4C)) = 0.0f;
    (*(f32 *)((u8 *)arg0 + 0x50)) = 0.0f;
    (*(f32 *)((u8 *)arg0 + 0x64)) = 0.0f;
    (*(f32 *)((u8 *)arg0 + 0x68)) = 0.0f;
    do {
        (*(f32 *)((u8 *)var_v1 + 0x48)) = var_f0;
        (*(f32 *)((u8 *)var_v1 + 0x4C)) = 0.0f;
        (*(f32 *)((u8 *)var_v1 + 0x50)) = 0.0f;
        temp_f0_2 = var_f0 + 222.22223f;
        var_v0 += 4;
        (*(f32 *)((u8 *)var_v1 + 0x64)) = 0.0f;
        (*(f32 *)((u8 *)var_v1 + 0x68)) = 0.0f;
        (*(f32 *)((u8 *)var_v1 + 0x60)) = temp_f0_2;
        temp_f0_3 = temp_f0_2 + 222.22223f;
        (*(f32 *)((u8 *)var_v1 + 0x7C)) = 0.0f;
        (*(f32 *)((u8 *)var_v1 + 0x80)) = 0.0f;
        (*(f32 *)((u8 *)var_v1 + 0x94)) = 0.0f;
        (*(f32 *)((u8 *)var_v1 + 0x78)) = temp_f0_3;
        temp_f0_4 = temp_f0_3 + 222.22223f;
        (*(f32 *)((u8 *)var_v1 + 0x98)) = 0.0f;
        var_v1 += 0x60;
        (*(f32 *)((u8 *)var_v1 + 0x30)) = temp_f0_4;
        var_f0 = temp_f0_4 + 222.22223f;
    } while (var_v0 != 0xA);
    (*(u8 *)((u8 *)arg0 + 0x10)) = (u8) ((*(u8 *)((u8 *)arg0 + 0x10)) & 0xFFFD);
    return 1;
}
void vtx_slot_buffers_free();

/* was func_151B51CC */
void cord_release(void *arg0) {
    void (*fp)(void *);
    vtx_slot_buffers_free((u8 *)arg0 + 0x140, arg0);
    fp = D_8008FF10[((u8 *)arg0)[0x44]];
    if (fp != NULL) {
        fp(arg0);
    }
}

void cord_release(void *arg0);

/* was func_151B521C */
void cord_free(void *arg0) {
    cord_release(arg0);
    node_unlink_free(arg0);
}

/* was func_151B5248 */
void cord_free_alt(void *arg0) {
    cord_release(arg0);
    node_unlink_free(arg0);
}
