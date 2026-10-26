#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
void water_jet_spray_spawn(u8 *arg0);


s32 fxrec_broadcast(s32, s32);

/* was func_150B42B0 */
void water_jets_stop_all(void) {
    s8 sp24[4];

    fxrec_broadcast(0, 5);
    sp24[0] = 0;
    effect_nodes_broadcast((s32) sp24, 0x18U);
    sp24[0] = 2;
    effect_nodes_broadcast((s32) sp24, 0x18U);
    sp24[0] = 4;
    effect_nodes_broadcast((s32) sp24, 0x18U);
    sp24[0] = 1;
    effect_nodes_broadcast((s32) sp24, 0x18U);
    sp24[0] = 3;
    effect_nodes_broadcast((s32) sp24, 0x18U);
    sp24[0] = 5;
    effect_nodes_broadcast((s32) sp24, 0x18U);
}

s32 sfx_emitter_stop_at(u16, s16, s16, s16, s32);
void fxrec_die_retire(u8 *);

/* was func_150B4354 */
void water_jet_die_retire(u8 *arg0) {
    sfx_emitter_stop_at(0x221, (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x10)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x14)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x18)), 0xFA0);
    fxrec_die_retire(arg0);
}

s32 sfx_emitter_stop_at(u16, s16, s16, s16, s32);
void fxrec_die_free(u8 *);

/* was func_150B43C8 */
void water_jet_die_free(u8 *arg0) {
    sfx_emitter_stop_at(0x221, (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x10)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x14)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x18)), 0xFA0);
    fxrec_die_free(arg0);
}

s32 memcpy(s32 *, s32 *, s32);

/* was func_150B443C */
u8 *water_jet_spawn(s32 *arg0, u8 *arg1, s16 arg2) {
    struct {
        s32 u44;
        u8 pad48[0x3C];
        f32 u84;
        f32 u88;
        s8 u8C;
        u8 pad8D[0x3];
        f32 u90;
        s8 u94;
        u8 pad95[0x3];
        f32 u98;
        s32 u9C;
        u8 padA0[0x8];
        s16 uA8;
        s16 uAA;
        s32 uAC;
        u8 padB0[0x1];
        s8 uB1;
    } sp;
    u8 *sp40;
    u8 *temp_v0;

    memcpy(&sp.u44, arg0, 0x40);
    sp.u8C = 0;
    sp.uAA = 2;
    sp.uA8 = 0x1F4;
    sp.u88 = 0.0f;
    sp.uB1 = (s8) arg2;
    sp.u94 = 0;
    sp.u98 = 0.0f;
    sp.u90 = (*(f32 *)((u8 *)arg0 + 0x14)) + (*(f32 *)((u8 *)arg0 + 0x18));
    sp.u84 = sp.u90;
    (*(f32 *)((u8 *)(&sp.u9C) + 0)) = (f32) (*(f32 *)((u8 *)arg1 + 0));
    (*(f32 *)((u8 *)(&sp.u9C) + 4)) = (f32) (*(f32 *)((u8 *)arg1 + 4));
    (*(f32 *)((u8 *)(&sp.u9C) + 8)) = (f32) (*(f32 *)((u8 *)arg1 + 8));
    sp.uAC = 9;
    temp_v0 = fxrec_spawn(&sp.u9C, 0x58, 0x24, 7, 7, 7, 0, 0, 0, 0xFFU, 1);
    sp40 = temp_v0;
    if (temp_v0 != NULL) {
        sfx_emitter_start(0x221U, (s16) (s32) (*(f32 *)((u8 *)arg1 + 0)), (s16) (s32) (*(f32 *)((u8 *)arg1 + 4)), (s16) (s32) (*(f32 *)((u8 *)arg1 + 8)), 0x61A8, 0xFA0U, 0x258, (s32) sfx_cb_keep_until_silent, NULL, 0, 8, random_int() & 0x40);
        memcpy((*(s32 **)((u8 *)sp40 + 0x98)), &sp.u44, 0x58);
    }
    return sp40;
}
typedef struct { f32 x, y, z; } V3s64;
/* was func_150B45C8 */
s32 water_jet_points_update(u8 *arg0) {
    s32 temp_v1;
    s32 var_a1;
    s32 var_a2;
    u8 *temp_a3;
    u8 *temp_t6;
    u8 *temp_v0;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x98));
    temp_v1 = (*(s32 *)((u8 *)arg0 + 0x94));
    if (((*(s8 *)((u8 *)arg0 + 0x2C)) < 2) && ((*(u8 *)((u8 *)temp_v0 + 0x1C)) & 1)) {
        return 0;
    }
    var_a2 = (*(s8 *)((u8 *)arg0 + 0x2E));
    if (var_a2 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
        do {
            var_a2 -= 1;
            var_a1 = 0;
            if (var_a2 < 0) {
                var_a2 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
            }
            temp_a3 = (0, temp_v1) + (var_a2 * 0x24); // fakematch: comma flips addu operand order
            (*(s16 *)((u8 *)temp_a3 + 0x1C)) = 0xFF;
            (*(s16 *)((u8 *)temp_a3 + 0x1E)) = (s16) ((*(s16 *)((u8 *)temp_a3 + 0x1E)) - g_frame_ticks);
            if ((*(s16 *)((u8 *)temp_a3 + 0x1E)) < 0) {
                var_a1 = 1;
            }
            (*(f32 *)((u8 *)temp_a3 + 0x10)) = (f32) (((*(f32 *)((u8 *)temp_v0 + 0xC)) * g_frame_step_f) + (*(f32 *)((u8 *)temp_a3 + 0x10)));
            (*(f32 *)((u8 *)temp_a3 + 0)) = (f32) (((*(f32 *)((u8 *)temp_a3 + 0xC)) * g_frame_step_f) + (*(f32 *)((u8 *)temp_a3 + 0)));
            (*(f32 *)((u8 *)temp_a3 + 4)) = (f32) (((*(f32 *)((u8 *)temp_a3 + 0x10)) * g_frame_step_f) + (*(f32 *)((u8 *)temp_a3 + 4)));
            (*(f32 *)((u8 *)temp_a3 + 8)) = (f32) (((*(f32 *)((u8 *)temp_a3 + 0x14)) * g_frame_step_f) + (*(f32 *)((u8 *)temp_a3 + 8)));
            (*(f32 *)((u8 *)temp_a3 + 0x18)) = (f32) (((*(f32 *)((u8 *)temp_v0 + 0x28)) * g_frame_step_f) + (*(f32 *)((u8 *)temp_a3 + 0x18)));
            if ((var_a1 != 0) && (var_a2 != (*(s8 *)((u8 *)arg0 + 0x2D)))) {
                do {
                    (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2D)) + 1);
                    if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2D))) {
                        (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
                    }
                    (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) - 1);
                } while (var_a2 != (*(s8 *)((u8 *)arg0 + 0x2D)));
            }
        } while (var_a2 != (*(s8 *)((u8 *)arg0 + 0x2D)));
    }
    if ((*(s8 *)((u8 *)arg0 + 0x2C)) > 0) {
        *(V3s64 *)(arg0 + 0x54) = *(V3s64 *)(((*(s8 *)((u8 *)arg0 + 0x2D)) * 0x24) + (0, temp_v1)); // fakematch: comma flips addu operand order
    } else {
        (*(f32 *)((u8 *)arg0 + 0x54)) = 0.0f;
        (*(f32 *)((u8 *)arg0 + 0x58)) = 0.0f;
        (*(f32 *)((u8 *)arg0 + 0x5C)) = 0.0f;
    }
    return 1;
}

/* was func_150B4774 */
s32 water_jet_emit_update(u8 *arg0) {
    struct {
        f32 u80;
        f32 u84;
        f32 u88;
    } sp;
    f32 temp_f0;
    f32 temp_f16;
    f32 temp_f26;
    f32 temp_f28;
    f32 temp_f2;
    f32 var_f20;
    f32 var_f22;
    f32 var_f4;
    f32 var_f4_2;
    f32 var_f6;
    s32 temp_s3;
    s8 temp_v0_5;
    u8 temp_a0;
    u8 temp_t4;
    u8 temp_t6;
    u8 temp_t8;
    u8 *temp_s2;
    u8 *temp_s5;
    u8 *temp_t9;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 *temp_v0_4;

    temp_s2 = (*(u8 **)((u8 *)arg0 + 0x98));
    temp_s3 = (*(s32 *)((u8 *)arg0 + 0x94));
    temp_a0 = (*(u8 *)((u8 *)temp_s2 + 0x50)) + ((random_int() % (u32) ((*(u8 *)((u8 *)temp_s2 + 0x10)) + 1)) * g_frame_ticks);
    (*(u8 *)((u8 *)temp_s2 + 0x50)) = temp_a0;
    (*(f32 *)((u8 *)temp_s2 + 0x4C)) = (f32) ((angle_byte_cos((temp_a0 - 0x40) & 0xFF) * (*(f32 *)((u8 *)temp_s2 + 0x18))) + (*(f32 *)((u8 *)temp_s2 + 0x14)));
    (*(f32 *)((u8 *)temp_s2 + 0x44)) = (f32) ((*(f32 *)((u8 *)temp_s2 + 0x44)) + ((*(f32 *)((u8 *)temp_s2 + 0x20)) * g_frame_step_f));
    temp_f16 = (*(f32 *)((u8 *)temp_s2 + 0x44));
    if (temp_f16 > 1.0f) {
        temp_f2 = 1.0f / temp_f16;
        var_f20 = g_frame_step_f;
        (*(f32 *)((u8 *)(&sp.u80) + 0)) = (*(f32 *)((u8 *)temp_s2 + 0));
        temp_s5 = arg0 + 0x10;
        (*(s32 *)((u8 *)(&sp.u80) + 4)) = (s32) (*(s32 *)((u8 *)temp_s2 + 4));
        (*(s32 *)((u8 *)(&sp.u80) + 8)) = (s32) (*(s32 *)((u8 *)temp_s2 + 8));
        var_f22 = (*(f32 *)((u8 *)temp_s2 + 0x40));
        temp_f26 = var_f20 * temp_f2;
        temp_f28 = ((*(f32 *)((u8 *)temp_s2 + 0x4C)) - var_f22) * temp_f2;
        do {
            (*(f32 *)((u8 *)temp_s2 + 0x54)) = (f32) ((*(f32 *)((u8 *)temp_s2 + 0x54)) + (*(f32 *)((u8 *)temp_s2 + 0x3C)));
            if ((*(f32 *)((u8 *)temp_s2 + 0x54)) > 1.0f) {
                water_jet_spray_spawn(arg0);
            }
            temp_t9 = temp_s3 + ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x24);
            (*(s32 *)((u8 *)temp_t9 + 0)) = (s32) (*(s32 *)((u8 *)temp_s5 + 0));
            (*(s32 *)((u8 *)temp_t9 + 4)) = (s32) (*(s32 *)((u8 *)temp_s5 + 4));
            (*(s32 *)((u8 *)temp_t9 + 8)) = (s32) (*(s32 *)((u8 *)temp_s5 + 8));
            (*(f32 *)((u8 *)((temp_s3 + ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x24))) + 0xC)) = (f32) (sp.u80 * var_f22);
            (*(f32 *)((u8 *)((temp_s3 + ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x24))) + 0x10)) = (f32) (sp.u84 * var_f22);
            (*(f32 *)((u8 *)((temp_s3 + ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x24))) + 0x14)) = (f32) (sp.u88 * var_f22);
            (*(f32 *)((u8 *)((temp_s3 + ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x24))) + 0x18)) = (f32) (*(f32 *)((u8 *)temp_s2 + 0x2C));
            (*(s16 *)((u8 *)((temp_s3 + ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x24))) + 0x1C)) = 0xFF;
            (*(s16 *)((u8 *)((temp_s3 + ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x24))) + 0x1E)) = (s16) (*(s16 *)((u8 *)temp_s2 + 0x36));
            (*(u8 *)((u8 *)((temp_s3 + ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x24))) + 0x20)) = (u8) (*(u8 *)((u8 *)temp_s2 + 0x48));
            temp_f0 = random_float();
            temp_t4 = (*(u8 *)((u8 *)temp_s2 + 0x30));
            var_f6 = (f32) temp_t4;
            if ((s32) temp_t4 < 0) {
                var_f6 += 4294967296.0f;
            }
            temp_t6 = (*(u8 *)((u8 *)temp_s2 + 0x31));
            var_f4 = (f32) temp_t6;
            if ((s32) temp_t6 < 0) {
                var_f4 += 4294967296.0f;
            }
            temp_t8 = (*(u8 *)((u8 *)temp_s2 + 0x48));
            var_f4_2 = (f32) temp_t8;
            if ((s32) temp_t8 < 0) {
                var_f4_2 += 4294967296.0f;
            }
            (*(u8 *)((u8 *)temp_s2 + 0x48)) = (u8) (u32) (var_f4_2 + (var_f6 + (temp_f0 * var_f4)));
            temp_v0 = temp_s3 + ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x24);
            (*(f32 *)((u8 *)temp_v0 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x10)) + ((*(f32 *)((u8 *)temp_s2 + 0xC)) * var_f20));
            temp_v0_2 = temp_s3 + ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x24);
            (*(f32 *)((u8 *)temp_v0_2 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0)) + ((*(f32 *)((u8 *)temp_v0_2 + 0xC)) * var_f20));
            temp_v0_3 = temp_s3 + ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x24);
            (*(f32 *)((u8 *)temp_v0_3 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v0_3 + 4)) + ((*(f32 *)((u8 *)temp_v0_3 + 0x10)) * var_f20));
            temp_v0_4 = temp_s3 + ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x24);
            (*(f32 *)((u8 *)temp_v0_4 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v0_4 + 8)) + ((*(f32 *)((u8 *)temp_v0_4 + 0x14)) * var_f20));
            (*(s8 *)((u8 *)arg0 + 0x2E)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2E)) + 1);
            if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2E))) {
                (*(s8 *)((u8 *)arg0 + 0x2E)) = 0;
            }
            temp_v0_5 = (*(s8 *)((u8 *)arg0 + 0x2D));
            (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) + 1);
            if (temp_v0_5 == (*(s8 *)((u8 *)arg0 + 0x2E))) {
                (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) (temp_v0_5 + 1);
                if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2D))) {
                    (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
                }
                (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) - 1);
            }
            var_f22 += temp_f28;
            var_f20 -= temp_f26;
            (*(f32 *)((u8 *)temp_s2 + 0x44)) = (f32) ((*(f32 *)((u8 *)temp_s2 + 0x44)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s2 + 0x44)) > 1.0f);
        (*(f32 *)((u8 *)temp_s2 + 0x40)) = var_f22;
    }
    return 1;
}
s32 gfx_set_combine_mode(s32, s32, s8 *);
s32 gfx_geometry_mode_cached(s32, s32, s32);
s32 gfx_load_texture_cached(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s8 *, s32);
u8 *gfx_other_mode_cached(s32, s32, s32, s8 *);
void vtx_slot_buffer_get(s32 *, s16, s32, s32 *, u8 *);
u8 *gfx_env_color_cached(u8 *, s32, s32, s32, s32, s8 *);
extern s32 D_800915E8;
extern s32 g_gfx_tlut_mode; /* was D_800D30BC */

typedef struct {
    f32 pos[3];         /* +0x00 */
    u8 pad0C[0xC];
    f32 width;          /* +0x18 ribbon half-width at this point */
    u16 fade;           /* +0x1C alpha ramp (x style +0x26 >> 8) */
    u8 pad1E[2];
    u8 s;               /* +0x20 texture s (<< 6) */
    u8 pad21[3];
} BeamPoint;            /* 0x24 bytes, trail +0x94 */

// beam_ribbon_draw: draws the trail's points (+0x94, ring of +0x25 entries, newest before +0x2E, oldest +0x2D;
// nothing below 2 points, +0x2C) as a camera-facing ribbon (camera = g_player_views view `arg2` + 0x2F8): each point
// gets two vertices offset by +-width * normalize((prev - next) x (point - camera)), texture s = the point's +0x20
// << 6, t 0x43C0 / 0x4000, white with alpha (fade * style +0x26) >> 8. Style (+0x98) bits 2 / 4 first rewrite the
// fade ramps from the oldest (start 0, step +0x33, +0x32 points) / the newest (step +0x35, +0x34 points). When s
// grows between two points the last pair is repeated with s - 0x4000 (texture wrap). With +0x1E bit 1 the ribbon
// starts at the trail's own position (+0x10). Vertices from vtx_slot_buffer_get (+0x84 buffer, (count << 5) + 0xA0 bytes;
// none -> gfx unchanged); render state: texture D_800915E8, combine 0x4D, grey +0x24, geometry 1 / 0x160600,
// othermode g_gfx_tlut_mode | 0x82CA0 / 0x5049D8.
/* was func_150B4BF0 */
u8 *water_jet_ribbon_draw(u8 *trail, u8 *gfx, s16 arg2) {
    BeamPoint *pts;
    BeamPoint *p;
    u8 *style;
    f32 *cam;
    Vtx *v;
    s32 *g;
    f32 a[3];
    f32 b[3];
    f32 dx, dy, dz;
    f32 ex, ey, ez;
    f32 nx, ny, nz;
    f32 len2;
    f32 k;
    s16 alphaA;
    s16 alphaB;
    s16 n;
    s32 i;
    s32 cur;
    s32 next;
    s32 prevS;
    s32 curS;
    u8 ramp;
    s8 flag;

    if (*(s8 *) (trail + 0x2C) < 2) {
        return gfx;
    }
    vtx_slot_buffer_get((s32 *) (trail + 0x84), arg2, (trail[0x25] << 5) + 0xA0, (s32 *) &v, 0);
    if (v == NULL) {
        return gfx;
    }
    cam = (f32 *) ((u8 *) g_player_views + arg2 * 0x9A0 + 0x2F8);
    style = *(u8 **) (trail + 0x98);
    pts = *(BeamPoint **) (trail + 0x94);
    flag = 1;

    if (style[0x1C] & 2) {
        ramp = 0;
        n = style[0x32];
        i = *(s8 *) (trail + 0x2D);
        do {
            n--;
            pts[i].fade = ramp;
            ramp += style[0x33];
            i++;
            if (i == trail[0x25]) {
                i = 0;
            }
        } while (n != 0 && i != *(s8 *) (trail + 0x2E));
    }
    if (style[0x1C] & 4) {
        ramp = 0;
        n = style[0x34];
        i = *(s8 *) (trail + 0x2E) - 1;
        if (i < 0) {
            i = trail[0x25] - 1;
        }
        do {
            n--;
            pts[i].fade = ramp;
            ramp += style[0x35];
            i--;
            if (i < 0) {
                i = trail[0x25] - 1;
            }
        } while (n != 0 && i != *(s8 *) (trail + 0x2E));
    }

    gfx = (u8 *) gfx_load_texture_cached(gfx, &D_800915E8, 0, 0, 0, 0, 0x92, 0, 0, &flag, 3);
    gfx = (u8 *) gfx_geometry_mode_cached((s32) gfx, 1, 0x160600);
    gfx = (u8 *) gfx_set_combine_mode((s32) gfx, 0x4D, &flag);
    gfx = gfx_env_color_cached(gfx, style[0x24], style[0x24], style[0x24], 0xFF, &flag);
    gfx = gfx_other_mode_cached((s32) gfx, g_gfx_tlut_mode | 0x80000 | 0x2CA0, 0x5049D8, &flag);

    if (*(u16 *) (trail + 0x1E) & 2) {
        next = *(s8 *) (trail + 0x2E) - 1;
        if (next < 0) {
            next = trail[0x25] - 1;
        }
        a[0] = *(f32 *) (trail + 0x10);
        a[1] = *(f32 *) (trail + 0x14);
        a[2] = *(f32 *) (trail + 0x18);
        p = &pts[next];
        alphaA = (p->fade * *(s16 *) (style + 0x26)) >> 8;
        prevS = p->s;
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
        alphaA = (pts[cur].fade * *(s16 *) (style + 0x26)) >> 8;
        prevS = pts[cur].s;
        p = &pts[next];
    }
    b[0] = p->pos[0];
    b[1] = p->pos[1];
    b[2] = p->pos[2];
    alphaB = (p->fade * *(s16 *) (style + 0x26)) >> 8;
    curS = p->s;

    /* the first pair, at a (width and s of the next point) */
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
        k = p->width / sqrtf(len2);
        nx *= k;
        ny *= k;
        nz *= k;
    }
    v->v.ob[0] = (s32) (a[0] + nx);
    v->v.ob[1] = (s32) (a[1] + ny);
    v->v.ob[2] = (s32) (a[2] + nz);
    v->v.tc[0] = p->s << 6;
    v->v.tc[1] = 0x43C0;
    v->v.cn[0] = 0xFF;
    v->v.cn[1] = 0xFF;
    v->v.cn[2] = 0xFF;
    v->v.cn[3] = alphaA;
    v->v.flag = 0;
    v++;
    v->v.ob[0] = (s32) (a[0] - nx);
    v->v.ob[1] = (s32) (a[1] - ny);
    v->v.ob[2] = (s32) (a[2] - nz);
    v->v.tc[0] = p->s << 6;
    v->v.tc[1] = 0x4000;
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
            k = p->width / sqrtf(len2);
            nx *= k;
            ny *= k;
            nz *= k;
        }
        v->v.ob[0] = (s32) (b[0] + nx);
        v->v.ob[1] = (s32) (b[1] + ny);
        v->v.ob[2] = (s32) (b[2] + nz);
        v->v.tc[0] = p->s << 6;
        v->v.tc[1] = 0x43C0;
        v->v.cn[0] = 0xFF;
        v->v.cn[1] = 0xFF;
        v->v.cn[2] = 0xFF;
        v->v.cn[3] = alphaB;
        v->v.flag = 0;
        v++;
        v->v.ob[0] = (s32) (b[0] - nx);
        v->v.ob[1] = (s32) (b[1] - ny);
        v->v.ob[2] = (s32) (b[2] - nz);
        v->v.tc[0] = p->s << 6;
        v->v.tc[1] = 0x4000;
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
        if (prevS < curS) {
            /* s wrapped: the next segment starts from a copy of this pair, this pair ends at s - 0x4000 */
            memcpy((s32 *) v, (s32 *) (v - 2), 0x20);
            v[-2].v.tc[0] -= 0x4000;
            v++;
            v[-2].v.tc[0] -= 0x4000;
            v++;
        }
        cur = next;
        next = cur - 1;
        p--;
        if (next < 0) {
            next = trail[0x25] - 1;
            p = &pts[next];
        }
        a[0] = pts[cur].pos[0];
        a[1] = pts[cur].pos[1];
        a[2] = pts[cur].pos[2];
        b[0] = p->pos[0];
        b[1] = p->pos[1];
        b[2] = p->pos[2];
        prevS = (u8) curS;
        alphaB = (p->fade * *(s16 *) (style + 0x26)) >> 8;
        curS = p->s;
    } while (cur != *(s8 *) (trail + 0x2D));
    return gfx;
}

/* was func_150B5540 */
void water_jet_stop(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);

    arg0[0x30] = 0;
    *(u16 *)(arg0 + 0x1E) &= 0xFFFD;
    temp_v0[0x1C] |= 1;
}

u8 *trail_spawn(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, u8 *argB, s32 argC, u8 argD, s32 argE);
extern s32 D_8009FFC0;

/* was func_150B5568 */
void water_jet_spray_spawn(u8 *arg0) {
    struct {
        f32 uC0;
        f32 uC4;
        f32 uC8;
        f32 uCC;
        f32 uD0;
        u8 padD4[0x4];
        s8 uD8;
        s8 uD9;
        u8 uDA;
        s8 uDB;
        u8 padDC[0x4];
        s32 uE0;
        u8 padE4[0x8];
        s16 uEC;
        s16 uEE;
        u8 padF0[0x5];
        s8 uF5;
        u8 padF6[0xA];
        s32 u100;
        s32 u104;
        s32 u108;
        s32 u10C;
        s32 u110;
        s32 u114;
        s32 u118;
        s8 u11C;
        s8 u11D;
    } sp;
    f32 spB4;
    f32 temp_f12;
    f32 temp_f18;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f28;
    f32 temp_f2;
    f32 temp_f30;
    s32 temp_s1;
    s32 temp_s2;
    u8 *temp_s0;
    u8 *temp_s3;

    temp_s3 = (*(u8 **)((u8 *)arg0 + 0x98));
    temp_s0 = ((s32 *)((u8 *)&D_8009FFC0 + ((*(u8 *)((u8 *)temp_s3 + 0x38)) * 0x24)));
    sp.u100 = 0;
    sp.u104 = 1;
    sp.u108 = 0x160600;
    sp.u10C = 3;
    sp.u110 = 0x10;
    sp.u114 = 0x80;
    sp.u118 = 0x20;
    sp.u11C = 0;
    sp.u11D = 9;
    sp.uEE = 1;
    sp.uD9 = 6;
    sp.uD8 = 8;
    sp.uDA = (*(u8 *)((u8 *)temp_s3 + 0x24));
    sp.uDB = (s8) (*(s16 *)((u8 *)temp_s3 + 0x26));
    (*(s32 *)((u8 *)(&sp.uE0) + 0)) = (s32) (*(s32 *)((u8 *)arg0 + 0x10));
    (*(s32 *)((u8 *)(&sp.uE0) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 0x14));
    (*(s32 *)((u8 *)(&sp.uE0) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 0x18));
    do {
        temp_f20 = (random_float() * (*(f32 *)((u8 *)temp_s0 + 8))) + (*(f32 *)((u8 *)temp_s0 + 4));
        temp_s1 = random_int() & 0xFF;
        temp_s2 = random_int() & 0xFF;
        temp_f22 = angle_byte_cos((temp_s1 - 0x40) & 0xFF);
        temp_f24 = angle_byte_cos(temp_s1 & 0xFF);
        temp_f26 = angle_byte_cos((temp_s2 - 0x40) & 0xFF);
        temp_f2 = (*(f32 *)((u8 *)temp_s0 + 0));
        temp_f12 = temp_f2 * angle_byte_cos(temp_s2 & 0xFF);
        temp_f28 = (*(f32 *)((u8 *)temp_s3 + 0)) + (temp_f12 * temp_f22);
        temp_f30 = (*(f32 *)((u8 *)temp_s3 + 4)) - (temp_f2 * temp_f26);
        spB4 = (*(f32 *)((u8 *)temp_s3 + 8)) + (temp_f12 * temp_f24);
        sp.uF5 = (random_int() % (u32) ((*(s16 *)((u8 *)temp_s0 + 0x22)) + 1)) + (*(s16 *)((u8 *)temp_s0 + 0x20));
        sp.uEC = (random_int() % (u32) ((*(s16 *)((u8 *)temp_s0 + 0x1E)) + 1)) + (*(s16 *)((u8 *)temp_s0 + 0x1C));
        sp.uC0 = (random_float() * (*(f32 *)((u8 *)temp_s0 + 0x10))) + (*(f32 *)((u8 *)temp_s0 + 0xC));
        temp_f18 = (random_float() * (*(f32 *)((u8 *)temp_s0 + 0x18))) + (*(f32 *)((u8 *)temp_s0 + 0x14));
        sp.uC4 = temp_f20 * temp_f28;
        sp.uD0 = temp_f18;
        sp.uC8 = temp_f20 * temp_f30;
        sp.uCC = temp_f20 * spB4;
        trail_spawn(&sp.uE0, &sp.uC0, 0, 1, 7, 0, 0, 0, 0, 0, 0, &sp.u100, 0, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
        (*(f32 *)((u8 *)temp_s3 + 0x54)) = (f32) ((*(f32 *)((u8 *)temp_s3 + 0x54)) - 1.0f);
    } while ((*(f32 *)((u8 *)temp_s3 + 0x54)) > 1.0f);
}
/* was func_150B586C */
void water_jet_message(u8 *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 5) {
        water_jet_stop(arg0);
    }
}
