#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_151B57F0 */
struct260 *electric_bolt_spawn(s16 arg0, u8 arg1, s32 arg2) {
    extern f32 D_800AA7F8;
    struct260 *temp_v0;
    struct {
        u8 pad0[1408];
        u8 *unk580;
        u8 unk584;
        u8 pad585[3];
        u8 *unk588;
        u8 unk58C;
        u8 pad58D[3];
        f32 unk590;
        f32 unk594;
        f32 unk598;
        f32 unk59C;
        f32 unk5A0;
        u8 pad5A4[8];
    } tmp;

    tmp.unk584 = 0x17;
    tmp.unk58C = 0x16;
    tmp.unk580 = obj_find_by_setup_id(0x17);
    tmp.unk588 = obj_find_by_setup_id(tmp.unk58C);
    tmp.unk598 = 250.0f;
    tmp.unk590 = 18.0f;
    tmp.unk594 = 0.0f;
    tmp.unk5A0 = D_800AA7F8;
    tmp.unk59C = 1.0f / tmp.unk598;
    temp_v0 = effect_node_create(arg0, -1, -1, 1, 1, 0x15, 0x5A8, arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x5A8);
    }
    return temp_v0;
}

s32 gfx_load_texture_cached(s32, s32 *, s32, s32, s32, s32, s32, s32, s32, u8 *, s32);
s32 gfx_geometry_mode_cached(s32, s32, s32);
s32 gfx_env_color_cached(s32, s32, s32, s32, s32, u8 *);
s32 gfx_prim_color_cached(s32, s32, s32, s32, s32, s32, s32, u8 *);
s32 gfx_set_combine_mode(s32, s32, u8 *);
s32 gfx_other_mode_cached(s32, s32, s32, u8 *);
f32 vec3_length(f32 *);
f32 sinf(f32);
extern f32 D_800AA7E0[3]; /* bolt end offset on object A (-3, 11, -4) */
extern f32 D_800AA7EC[3]; /* bolt end offset on object B (0, -5, -7) */
extern u8 D_8008FF20;     /* matrix index of object A */
extern u8 D_8008FF24;     /* matrix index of object B */
extern s32 D_80091318;
extern s32 D_800D30BC;
extern s32 g_render_mode_pairs[]; /* was D_800A4EA8 */

/* One bolt vertex: position, s, t, colour red. */
#define BOLT_VTX(v, px, py, pz, s, t) \
    do { \
        *(s16 *) ((v) + 0x0) = (s32) (px); \
        *(s16 *) ((v) + 0x2) = (s32) (py); \
        *(s16 *) ((v) + 0x4) = (s32) (pz); \
        (v)[0xC] = 0xFF; \
        (v)[0xD] = 0; \
        (v)[0xE] = 0; \
        (v)[0xF] = 0xFF; \
        *(s16 *) ((v) + 0x8) = (s); \
        *(s16 *) ((v) + 0xA) = (t); \
    } while (0)

// electric_bolt_draw: g_effect_node_draw_fns draw handler (kind 1) of the bolt record of electric_bolt_spawn (state at +0x28: object
// A +0x580 / id +0x584, object B +0x588 / id +0x58C, half width +0x590, min / max length +0x594 / +0x598, 1 / max
// +0x59C, wobble +0x5A0). When either object is gone or reused, the record is marked dead (+0xE = -1). Otherwise,
// when both have matrices (+0x1D4), the ends are D_800AA7E0 / D_800AA7EC transformed by matrix D_8008FF20 /
// D_8008FF24 (mtx_transform_point_or_origin). The bolt is a camera-facing strip of 10 quads from A to B (vertex buffer D_800BE9C0 of
// the record, 0x2C0 bytes each) whose width wobbles with 1 - sin(phase) * amplitude, the phase stepping pi / 10 and
// t by 204.8 per quad; the amplitude is 0 below the min length, ramps up to the wobble at the max length.
/* was func_151B58D8 */
s32 electric_bolt_draw(s32 gfx, u8 *obj, s16 player) {
    u8 *st;
    u8 *v;
    f32 *cam;
    u8 *a;
    u8 *b;
    u8 dead;
    u8 flag;
    s32 i;
    f32 pa[3], pb[3], dir[3], p[3], n[3];
    f32 dist, amp, w, phase, phase2, t, t2, len2, k;
    f32 mx, my, mz, cx, cy, cz, sx, sy, sz, ox, oy, oz;

    dead = 0;
    st = obj + 0x28;
    a = *(u8 **) (st + 0x580);
    if (*(s32 *) a == 0 || st[0x584] != a[0x3B]) {
        dead = 1;
    }
    b = *(u8 **) (st + 0x588);
    if (*(s32 *) b == 0 || st[0x58C] != b[0x3B]) {
        dead = 1;
    }
    if (!dead && *(u8 **) (*(u8 **) (st + 0x580) + 0x1D4) != NULL && *(u8 **) (b + 0x1D4) != NULL) {
        mtx_transform_point_or_origin(D_800AA7E0, pa, *(u8 **) (*(u8 **) (st + 0x580) + 0x1D4) + D_8008FF20 * 0x40);
        mtx_transform_point_or_origin(D_800AA7EC, pb, *(u8 **) (*(u8 **) (st + 0x588) + 0x1D4) + D_8008FF24 * 0x40);
        v = st + D_800BE9C0 * 0x2C0;
        cam = (f32 *) ((u8 *) D_800DBFF0 + player * 0x9A0 + 0x2F8);
        flag = 1;
        gfx = gfx_geometry_mode_cached(gfx, 0x200005, 0x60600);
        gfx = gfx_load_texture_cached(gfx, &D_80091318, 0, 0, 0, 0, 0x56, 0, 0, &flag, 3);
        gfx = gfx_env_color_cached(gfx, 0xFF, 0xFF, 0xFF, 0xFF, &flag);
        gfx = gfx_prim_color_cached(gfx, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF, &flag);
        gfx = gfx_set_combine_mode(gfx, 0x2E, &flag);
        gfx = gfx_other_mode_cached(gfx, D_800D30BC | 0x80000 | 0x2CA0, g_render_mode_pairs[5 * 2 + 1] | g_render_mode_pairs[5 * 2], &flag);
        dir[0] = pb[0] - pa[0];
        dir[1] = pb[1] - pa[1];
        dir[2] = pb[2] - pa[2];
        dist = vec3_length(dir);
        mx = dir[0] * 0.5f + pa[0] - cam[0];
        my = dir[1] * 0.5f + pa[1] - cam[1];
        mz = dir[2] * 0.5f + pa[2] - cam[2];
        cx = dir[1] * mz - my * dir[2];
        cy = dir[2] * mx - mz * dir[0];
        cz = dir[0] * my - mx * dir[1];
        len2 = cx * cx + cy * cy + cz * cz;
        if (len2 == 0.0f) {
            n[0] = 0.0f;
            n[1] = 0.0f;
            n[2] = 0.0f;
        } else {
            k = *(f32 *) (st + 0x590) / sqrtf(len2);
            n[0] = cx * k;
            n[1] = cy * k;
            n[2] = cz * k;
        }
        sx = dir[0] * 0.1f;
        sy = dir[1] * 0.1f;
        sz = dir[2] * 0.1f;
        if (dist < *(f32 *) (st + 0x594)) {
            amp = 0.0f;
        } else if (dist < *(f32 *) (st + 0x598)) {
            amp = (dist - *(f32 *) (st + 0x594)) * *(f32 *) (st + 0x59C) * *(f32 *) (st + 0x5A0);
        } else {
            amp = *(f32 *) (st + 0x5A0);
        }
        p[0] = pa[0];
        p[1] = pa[1];
        p[2] = pa[2];
        phase = 0.0f;
        t = 0.0f;
        for (i = 0; i < 10; i++) {
            w = 1.0f - sinf(phase) * amp;
            ox = n[0] * w;
            BOLT_VTX(v, ox + p[0], n[1] * w + p[1], n[2] * w + p[2], 0, t);
            BOLT_VTX(v + 0x10, p[0] - ox, p[1] - n[1] * w, p[2] - n[2] * w, 0x7C0, t);
            phase2 = phase + 0.31415927f;
            w = 1.0f - sinf(phase2) * amp;
            ox = n[0] * w;
            oy = n[1] * w;
            oz = n[2] * w;
            t2 = t + 204.8f;
            BOLT_VTX(v + 0x20, p[0] + sx - ox, p[1] + sy - oy, p[2] + sz - oz, 0x7C0, t2);
            BOLT_VTX(v + 0x30, p[0] + sx + ox, p[1] + sy + oy, p[2] + sz + oz, 0, t2);
            v += 0x40;
            ((s32 *) gfx)[0] = 0x01004008; /* gSPVertex(v - 4, 4, 0) */
            ((s32 *) gfx)[1] = (s32) (v - 0x40);
            ((s32 *) gfx)[2] = 0x05000204; /* gSP1Triangle(0, 1, 2) */
            ((s32 *) gfx)[3] = 0;
            ((s32 *) gfx)[4] = 0x05000406; /* gSP1Triangle(0, 2, 3) */
            ((s32 *) gfx)[5] = 0;
            gfx += 0x18;
            p[1] += sy;
            p[0] += sx;
            p[2] += sz;
            phase = phase2;
            t = t2;
        }
    }
    if (dead) {
        *(s16 *) (obj + 0xE) = -1;
    }
    return gfx;
}

/* was func_151B604C */
void electric_bolt_handle_message(u8 *arg0, u8 *arg1, u8 arg2)
{
  u8 *v = arg0 + 0x28;
  if (arg2 == 0x2D)
  {
    if (*(s32 *)arg1 == *(s32 *)(v + 0x580)) { *(s32 *)(v + 0x580) = *(s32 *)(arg1 + 4); v[0x584] = arg1[9]; }
    else if (*(s32 *)(arg1 + 4) == *(s32 *)(v + 0x580)) { *(s32 *)(v + 0x580) = *(s32 *)arg1; v[0x584] = arg1[8]; }
    if (*(s32 *)arg1 == *(s32 *)(v + 0x588)) { *(s32 *)(v + 0x588) = *(s32 *)(arg1 + 4); v[0x58C] = arg1[9]; }
    else if (*(s32 *)(arg1 + 4) == *(s32 *)(v + 0x588)) {
      s32 blk_t; // fakematch: block-local declaration = basic-block boundary (s69)
      *(s32 *)(v + 0x588) = *(s32 *)arg1; v[0x58C] = arg1[8]; }
  }
  else if (arg2 == 0)
  {
    s32 k = *(s32 *)arg1;
    if ((k == *(s32 *)(v + 0x580)) || (k == *(s32 *)(v + 0x588)) || (v[0x584] == arg1[4]) || (v[0x58C] == arg1[4])) { node_destroy((struct102 *)arg0); }
  }
}
