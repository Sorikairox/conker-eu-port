#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
extern u8 g_vec3_zero[]; /* was D_800A5860 */

typedef struct {
    /* 0x00 */ u8 pad0[0x58];
    /* 0x58 */ f32 unk58[2];
    /* 0x60 */ u8 pad60[0x48];
    /* 0xA8 */ f32 unkA8;
} struct_eu_15E000;

void vec_damp_y_per_tick(f32 *arg0, f32 arg1);
void vec_damp_xz_per_tick(f32 *arg0, f32 arg1);
void vec_damp_xyz_per_tick(f32 *arg0, f32 arg1);


/* was func_151307F0 */
s32 particle_spawn_ex(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5) {
    u8 *obj;
    s32 type;

    switch (arg1) {
    case 0:
        type = 0x2B;
        break;
    case 1:
        type = 0x52;
        break;
    case 2:
        type = 0x47;
        break;
    default:
        type = 0x2B;
        break;
    }
    obj = node_alloc(type, arg5, arg3 + 0xA8, 1, arg4, 1);
    if (obj == NULL) {
        return 0;
    }
    memcpy(obj + 0x10, arg0, 0x70);
    if (arg2 != 0) {
        *(struct_eu_bytes24 *)(obj + 0x80) = *(struct_eu_bytes24 *)arg2;
    } else {
        obj[0x9C] = 0;
    }
    return (s32)obj;
}

s32 particle_spawn_ex(s32, u8, s32, s32, u8, s32);
/* was func_151308E4 */
s32 particle_spawn_basic(s32 arg0, u8 arg1, s32 arg2, u8 arg3, s32 arg4) {
    return particle_spawn_ex(arg0, arg1, 0, arg2, arg3, arg4);
}

s32 particle_spawn_basic(s32 arg0, u8 arg1, s32 arg2, u8 arg3, s32 arg4);

/* was func_1513092C */
s32 particle_spawn_default(s32 arg0, u8 arg1, s32 arg2) {
    return particle_spawn_basic(arg0, arg1, arg2, 0xFF, 0);
}

extern s32 (*g_particle_update_fns[])(u8 *, f32 *); /* was D_80089B00 */
extern void (*g_particle_death_fns[])(u8 *); /* was D_80089BA0 */

/*
 * particle_update: per-tick update of a 0x2B / 0x52 / 0x47 particle (record from particle_spawn_ex). Flag word +0x68:
 * 1 life timer +0x1A counts down by the frame ticks (g_frame_ticks), dead below 0; 2 vertical speed +0x5C gains
 * gravity +0x64; 4 position +0x40 moves by the velocity +0x58 (scaled by g_frame_step_f); 0x200 alpha +0x2B fades
 * as timer * +0x30 below timer +0x2E; 0x400 size +0x38 / +0x3C changes by +0x34 below timer +0x32 (0x800 =
 * multiply once per tick, else add per tick; 0x80000 = only +0x38, 0x100000 = only +0x3C). Frame counter +0x1C
 * advances by speed +0x20 over the animation length of g_sprite_anim_table[+0x2D] (x 0x10000): 0x10 / 0x20 = die at the
 * end / start, 8 = bounce, else wrap. Then update handler g_particle_update_fns[+0x72] (with the old position; 0 = die);
 * a dead particle runs death handler g_particle_death_fns[+0x73] and is freed.
 */
/* was func_1513095C */
void particle_sprite_update(u8 *arg0) {
    s32 dead = FALSE;
    u32 flags;
    f32 old[3];
    s32 n;
    s32 spd, len, fr;
    s8 h;

    if (*(u32 *)(arg0 + 0x68) & 1) {
        *(s16 *)(arg0 + 0x1A) -= g_frame_ticks;
        if (*(s16 *)(arg0 + 0x1A) < 0) {
            dead = TRUE;
        }
    }
    if (*(u32 *)(arg0 + 0x68) & 2) {
        *(f32 *)(arg0 + 0x5C) += *(f32 *)(arg0 + 0x64) * g_frame_step_f;
    }
    old[0] = *(f32 *)(arg0 + 0x40);
    old[1] = *(f32 *)(arg0 + 0x44);
    old[2] = *(f32 *)(arg0 + 0x48);
    flags = *(u32 *)(arg0 + 0x68);
    if (flags & 4) {
        *(f32 *)(arg0 + 0x40) += *(f32 *)(arg0 + 0x58) * g_frame_step_f;
        *(f32 *)(arg0 + 0x44) += *(f32 *)(arg0 + 0x5C) * g_frame_step_f;
        *(f32 *)(arg0 + 0x48) += *(f32 *)(arg0 + 0x60) * g_frame_step_f;
        flags = *(u32 *)(arg0 + 0x68);
    }
    if ((flags & 0x200) && *(s16 *)(arg0 + 0x1A) < *(s16 *)(arg0 + 0x2E)) {
        s16 a = *(s16 *)(arg0 + 0x1A) * *(s16 *)(arg0 + 0x30);
        if (a < arg0[0x2B]) {
            arg0[0x2B] = a;
        }
        flags = *(u32 *)(arg0 + 0x68);
    }
    if ((flags & 0x400) && *(s16 *)(arg0 + 0x1A) < *(s16 *)(arg0 + 0x32)) {
        if (flags & 0x800) {
            if (flags & 0x80000) {
                for (n = g_frame_ticks; n != 0; n--) {
                    *(f32 *)(arg0 + 0x38) *= *(f32 *)(arg0 + 0x34);
                }
            } else if (flags & 0x100000) {
                for (n = g_frame_ticks; n != 0; n--) {
                    *(f32 *)(arg0 + 0x3C) *= *(f32 *)(arg0 + 0x34);
                }
            } else {
                for (n = g_frame_ticks; n != 0; n--) {
                    *(f32 *)(arg0 + 0x38) *= *(f32 *)(arg0 + 0x34);
                    *(f32 *)(arg0 + 0x3C) *= *(f32 *)(arg0 + 0x34);
                }
            }
        } else {
            if (!(flags & 0x80000)) {
                *(f32 *)(arg0 + 0x3C) += *(f32 *)(arg0 + 0x34) * (f32)g_frame_ticks;
            }
            if (!(flags & 0x100000)) {
                *(f32 *)(arg0 + 0x38) += *(f32 *)(arg0 + 0x34) * (f32)g_frame_ticks;
            }
        }
    }
    if (!dead && (spd = *(s32 *)(arg0 + 0x20)) != 0) {
        len = (g_sprite_anim_table[arg0[0x2D]][0] << 16) - 1;
        fr = *(s32 *)(arg0 + 0x1C) + spd * g_frame_ticks;
        *(s32 *)(arg0 + 0x1C) = fr;
        if (len < fr) {
            flags = *(u32 *)(arg0 + 0x68);
            if (flags & 0x10) {
                dead = TRUE;
            } else if (flags & 8) {
                *(s32 *)(arg0 + 0x1C) = len - fr % len;
                *(s32 *)(arg0 + 0x20) = -spd;
            } else {
                do {
                    fr -= len;
                    *(s32 *)(arg0 + 0x1C) = fr;
                } while (len < fr);
            }
        } else if (fr < 0) {
            flags = *(u32 *)(arg0 + 0x68);
            if (flags & 0x20) {
                dead = TRUE;
            } else if (flags & 8) {
                *(s32 *)(arg0 + 0x1C) = -fr % len;
                *(s32 *)(arg0 + 0x20) = -spd;
            } else {
                do {
                    fr += len;
                    *(s32 *)(arg0 + 0x1C) = fr;
                } while (fr < 0);
            }
        }
    }
    h = *(s8 *)(arg0 + 0x72);
    if (h != -1 && !dead) {
        if (g_particle_update_fns[h](arg0, old) == 0) {
            dead = TRUE;
        }
    }
    if (dead) {
        h = *(s8 *)(arg0 + 0x73);
        if (h != -1) {
            g_particle_death_fns[h](arg0);
        }
        node_destroy((struct102 *)arg0);
    }
}

extern s32 (*g_particle_visible_fns[])(u8 *, s32); /* was D_80089BA4 */
extern f32 g_particle_sprite_size_k; /* was D_800A3BDC */
extern u8 g_render_mode_pairs[]; /* was D_800A4EA8 */
extern s32 g_gfx_tlut_mode; /* was D_800D30BC */
s32 world_to_screen(f32 *pos, f32 *scr, f32 *oz, f32 *ow, f32 *oinv, u8 view);
void particle_calc_prim_color(s32 arg0_, s32 arg1_, s32 arg2_, s32 arg3_, s32 arg4_);
void particle_calc_colors(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);
void light_compute_point_colour(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 *arg5, s32 arg6, s32 arg7);
Gfx *gfx_set_combine_mode(Gfx *arg0, u8 arg1, u8 *arg2);
Gfx *gfx_geometry_mode_cached(Gfx *gfx, s32 set, s32 clear);
Gfx *gfx_prim_color_cached(s32, s32, s32, s16, s32, s32, s32, u8 *);
Gfx *gfx_env_color_cached(Gfx *gfx, s32 r, s32 g, s32 b, s32 a, u8 *arg5);
s32 gfx_load_texture_cached(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7, s32 arg8, u8 *arg9, s32 argA);
u8 *gfx_other_mode_cached(Gfx *, s32, s32, u8 *);

/*
 * particle_draw_sprite: draw handler of the sprite particles (draw tables at 0x8008C10C / 0x8008C6BC / 0x8008C8F8):
 * one textured rectangle for particle `p` in view `view`. Skipped when flag 0x40000 hides it in this view (+0x76
 * view mask), when the visibility handler g_particle_visible_fns[+0x74] (0x8000) says no, or when flag 0x20000's owner +0x6C
 * is not in this view. Projects the position (+0x40, plus +0x4C when 0x1000) with world_to_screen, sizes the
 * half-extents from +0x38 / +0x3C (clamped to at most +0x7C with 0x200000, at least +0x78 with 0x400000), culls
 * against the view's screen box, then emits pipe sync (once), prim depth, combine / colour (particle_calc_prim_color +
 * light_compute_point_colour lighting with 0x10000, else particle_calc_colors), texture g_sprite_textures[+0x2D] and the rectangle with
 * flipped S (0x40) / T (0x80) and clipped texture start at the left / top screen edge. Returns the new DL end.
 */
/* was func_1513100C */
Gfx *particle_draw_sprite(Gfx *gfx, u8 *p, s16 view) {
    u8 sync;
    u8 blend;
    u8 combine;
    s16 prim[4];  /* r, g, b, a: sp EA E8 E6 E4 */
    s16 env[4];   /* sp E2 E0 DE DC */
    u8 rgb[3];
    f32 pos[3];
    f32 scr[3];
    f32 oz;
    f32 ow;
    f32 inv;
    u8 *cam;
    u8 *zv;
    u8 *spr;
    u32 flags;
    f32 hw;
    f32 hh;
    f32 m;
    f32 left;
    f32 right;
    f32 top;
    f32 bottom;
    f32 left4;
    f32 top4;
    f32 right4;
    f32 bottom4;
    f32 w;
    f32 h;
    s32 dsdx;
    s32 dtdy;
    s32 s0;
    s32 t0;
    s32 yi;
    s32 ds;
    s32 dt;
    s32 v;
    s16 x;
    s16 y;
    s16 d;
    Gfx *g;

    if ((*(u32 *)(p + 0x68) & 0x40000) && !(p[0x76] & (1 << view))) {
        return gfx;
    }
    sync = 1;
    blend = *(u16 *)(p + 0x18) >> 8;
    combine = *(u16 *)(p + 0x18);
    if ((*(u32 *)(p + 0x68) & 0x8000) && (s8)p[0x74] != -1) {
        if (!g_particle_visible_fns[(s8)p[0x74]](p, view)) {
            return gfx;
        }
    }
    flags = *(u32 *)(p + 0x68);
    if ((flags & 0x20000) && *(u8 **)(p + 0x6C) != NULL && !(*(s16 *)(*(u8 **)(p + 0x6C) + 2) & (1 << view))) {
        return gfx;
    }
    if (flags & 0x1000) {
        pos[0] = *(f32 *)(p + 0x40) + *(f32 *)(p + 0x4C);
        pos[1] = *(f32 *)(p + 0x44) + *(f32 *)(p + 0x50);
        pos[2] = *(f32 *)(p + 0x48) + *(f32 *)(p + 0x54);
    } else {
        pos[0] = *(f32 *)(p + 0x40);
        pos[1] = *(f32 *)(p + 0x44);
        pos[2] = *(f32 *)(p + 0x48);
    }
    if (!world_to_screen(pos, scr, &oz, &ow, &inv, view)) {
        return gfx;
    }
    cam = (u8 *)g_player_cams + view * 0x180;
    hw = *(f32 *)(p + 0x38) * inv * *(f32 *)(cam + 0x1C) * g_particle_sprite_size_k;
    hh = *(f32 *)(p + 0x3C) * inv * *(f32 *)(cam + 0x20) * g_particle_sprite_size_k;
    flags = *(u32 *)(p + 0x68);
    if (flags & 0x200000) {
        m = *(f32 *)(p + 0x7C);
        if (m < hw) {
            hw = m;
        }
        if (m < hh) {
            hh = m;
        }
    }
    if (flags & 0x400000) {
        m = *(s16 *)(p + 0x78);
        if (hw < m) {
            hw = m;
        }
        if (hh < m) {
            hh = m;
        }
    }
    right = scr[0] + hw;
    if (!(*(f32 *)(cam + 0x2C) <= right)) {
        return gfx;
    }
    left = scr[0] - hw;
    if (!(left <= *(f32 *)(cam + 0x30))) {
        return gfx;
    }
    bottom = scr[1] + hh;
    if (!(*(f32 *)(cam + 0x24) <= bottom)) {
        return gfx;
    }
    top = scr[1] - hh;
    if (!(top <= *(f32 *)(cam + 0x28))) {
        return gfx;
    }
    left4 = left * 4.0f;
    top4 = top * 4.0f;
    right4 = right * 4.0f;
    bottom4 = bottom * 4.0f;

    if (sync) {
        gfx->words.w0 = 0xE7000000; /* pipe sync */
        gfx->words.w1 = 0;
        gfx++;
        sync = 0;
    }
    /* prim depth from the view's z-buffer scale / offset (s16 at +0x44 / +0x4C of the g_dl_buf_index entry) */
    zv = (u8 *)g_player_cams + view * 0x180 + g_dl_buf_index * 16;
    gfx->words.w0 = 0xEE000000;
    gfx->words.w1 = (s32)((*(s16 *)(zv + 0x4C) + oz * inv * *(s16 *)(zv + 0x44)) * 32.0f) << 16;
    gfx++;

    spr = (u8 *)&g_sprite_textures[p[0x2D]];
    w = g_sprite_textures[p[0x2D]].unk6;
    h = g_sprite_textures[p[0x2D]].unk8;
    if (left4 < right4) {
        dsdx = (s32)(4096.0f * w / (right4 - left4));
    } else {
        dsdx = 0;
    }
    if (0.0f < bottom4 - top4) {
        dtdy = (s32)(4096.0f * h / (bottom4 - top4));
    } else {
        dtdy = 0;
    }
    s0 = 0;
    t0 = 0;
    flags = *(u32 *)(p + 0x68);
    if (flags & 0x40) { /* flip S */
        s0 = (g_sprite_textures[p[0x2D]].unk6 - 1) << 5;
        dsdx = -dsdx & 0xFFFF;
    }
    if (flags & 0x80) { /* flip T */
        t0 = (g_sprite_textures[p[0x2D]].unk8 - 1) << 5;
        dtdy = -dtdy & 0xFFFF;
    }
    if (flags & 0x10000) {
        particle_calc_prim_color((s32)&prim[0], (s32)&prim[1], (s32)&prim[2], (s32)&prim[3], (s32)p);
        light_compute_point_colour(view, (s32)pos[0], (s32)pos[1], (s32)pos[2], 0xFF, rgb, 0, 0);
        env[0] = rgb[0];
        env[1] = rgb[1];
        env[2] = rgb[2];
        env[3] = p[0x2B];
    } else {
        particle_calc_colors((s32)&prim[0], (s32)&prim[1], (s32)&prim[2], (s32)&prim[3], (s32)&env[0], (s32)&env[1],
                      (s32)&env[2], (s32)&env[3], (s32)p);
    }
    gfx = gfx_set_combine_mode(gfx, blend, &sync);
    gfx = gfx_geometry_mode_cached(gfx, *(s32 *)(p + 0x10), *(s32 *)(p + 0x14) | 0x10000 | 0x100000);
    gfx = gfx_prim_color_cached((s32)gfx, 0, 0, prim[0], prim[1], prim[2], prim[3], &sync);
    gfx = gfx_env_color_cached(gfx, env[0], env[1], env[2], env[3], &sync);
    gfx = (Gfx *)gfx_load_texture_cached((s32)gfx, (s32)spr, *(s32 *)(p + 0x1C), 2, 0, 0, p[0x2D], 0, 0, &sync,
                               (*(u32 *)(p + 0x68) & 0x800000) ? 0x3E : 3);
    g = (Gfx *)gfx_other_mode_cached(gfx, ((*(u32 *)(p + 0x68) & 0x100) ? 0x100000 : 0) | g_gfx_tlut_mode | 0x2CA0,
                             *(s32 *)(g_render_mode_pairs + combine * 8 + 4) | *(s32 *)(g_render_mode_pairs + combine * 8) | 4, &sync);

    /* texture rectangle: lower right, upper left (10.2 screen coordinates clamped at 0) */
    x = (s32)right4;
    y = (s32)bottom4;
    g[0].words.w0 = 0xE4000000 | ((y > 0 ? y : 0) & 0xFFF) | (((x > 0 ? x : 0) & 0xFFF) << 12);
    x = (s32)left4;
    yi = (s32)top4;
    y = yi;
    g[0].words.w1 = (((x > 0 ? x : 0) & 0xFFF) << 12) | ((y > 0 ? y : 0) & 0xFFF);
    g[1].words.w0 = 0xE1000000;
    /* rectangle starting left of / above the screen: advance the texture start by the clipped part */
    if (x < 0) {
        d = dsdx;
        v = (x * d) >> 7;
        if (d < 0) {
            ds = v > 0 ? v : 0;
        } else {
            ds = v < 0 ? v : 0;
        }
    } else {
        ds = 0;
    }
    if (yi < 0) {
        d = dtdy;
        v = (y * d) >> 7;
        if (d < 0) {
            dt = v > 0 ? v : 0;
        } else {
            dt = v < 0 ? v : 0;
        }
    } else {
        dt = 0;
    }
    g[1].words.w1 = ((t0 - dt) & 0xFFFF) | ((s0 - ds) << 16);
    g[2].words.w0 = 0xF1000000;
    g[2].words.w1 = (dsdx << 16) | (dtdy & 0xFFFF);
    return g + 3;
}

typedef struct {
    u8 pad0[0x24];
    u8 u24;
    u8 u25;
    u8 u26;
    u8 u27;
    u8 u28;
    u8 u29;
    u8 u2A;
    u8 u2B;
    u8 u2C;
    u8 pad2D[0x43];
    u8 u70;
    u8 u71;
} struct_15E000_col;
/* was func_151318EC */
void particle_calc_prim_color(s32 arg0_, s32 arg1_, s32 arg2_, s32 arg3_, s32 arg4_) {
    s16 *arg0 = (s16 *)arg0_;
    s16 *arg1 = (s16 *)arg1_;
    s16 *arg2 = (s16 *)arg2_;
    s16 *arg3 = (s16 *)arg3_;
    struct_15E000_col *arg4 = (struct_15E000_col *)arg4_;

    switch (arg4->u70) {
    case 1:
        *arg0 = *arg1 = *arg2 = 0;
        *arg3 = (arg4->u27 * arg4->u2B) >> 8;
        break;
    case 2:
        *arg0 = arg4->u24;
        *arg1 = arg4->u25;
        *arg2 = arg4->u26;
        *arg3 = (arg4->u27 * arg4->u2B) >> 8;
        break;
    case 3:
        *arg0 = arg4->u28;
        *arg1 = arg4->u29;
        *arg2 = arg4->u2A;
        *arg3 = (arg4->u27 * arg4->u2B) >> 8;
        break;
    case 4:
    case 6:
        *arg0 = *arg1 = *arg2 = *arg3 = 0;
        break;
    case 5:
        *arg0 = *arg1 = *arg2 = 0;
        *arg3 = arg4->u2B;
        break;
    case 7:
        *arg0 = arg4->u24;
        *arg1 = arg4->u25;
        *arg2 = arg4->u26;
        *arg3 = arg4->u2B;
        break;
    case 8:
        *arg0 = arg4->u24;
        *arg1 = arg4->u25;
        *arg2 = arg4->u26;
        *arg3 = 0;
        break;
    default:
        *arg0 = (arg4->u24 * arg4->u2C) >> 8;
        *arg1 = (arg4->u25 * arg4->u2C) >> 8;
        *arg2 = (arg4->u26 * arg4->u2C) >> 8;
        *arg3 = 0;
        break;
    }
}

/* was func_15131A84 */
void particle_calc_env_color(s32 arg0_, s32 arg1_, s32 arg2_, s32 arg3_, s32 arg4_) {
    s16 *arg0 = (s16 *)arg0_;
    s16 *arg1 = (s16 *)arg1_;
    s16 *arg2 = (s16 *)arg2_;
    s16 *arg3 = (s16 *)arg3_;
    struct_15E000_col *arg4 = (struct_15E000_col *)arg4_;

    switch (arg4->u71) {
    case 1:
    case 5:
        *arg0 = *arg1 = *arg2 = 0;
        *arg3 = 0;
        break;
    case 2:
        *arg0 = *arg1 = *arg2 = arg4->u2C;
        *arg3 = 0;
        break;
    case 8:
        *arg0 = *arg1 = *arg2 = 0;
        *arg3 = arg4->u2B;
        break;
    case 3:
        *arg0 = arg4->u24;
        *arg1 = arg4->u25;
        *arg2 = arg4->u26;
        *arg3 = 0;
        break;
    case 4:
    case 6:
        *arg0 = arg4->u28;
        *arg1 = arg4->u29;
        *arg2 = arg4->u2A;
        *arg3 = arg4->u2B;
        break;
    case 7:
        *arg0 = *arg1 = *arg2 = arg4->u2C;
        *arg3 = arg4->u2B;
        break;
    case 9:
        *arg0 = arg4->u24;
        *arg1 = arg4->u25;
        *arg2 = arg4->u26;
        *arg3 = arg4->u2B;
        break;
    default:
        *arg0 = *arg1 = *arg2 = arg4->u2C;
        *arg3 = (arg4->u27 * arg4->u2B) >> 8;
        break;
    }
}

/* was func_15131BBC */
void particle_calc_colors(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    particle_calc_env_color(arg4, arg5, arg6, arg7, arg8);
    particle_calc_prim_color(arg0, arg1, arg2, arg3, arg8);
}

/* was func_15131C1C */
s32 particle_upd_damp_vel_y(struct_eu_15E000 *arg0, s32 arg1) {
    vec_damp_y_per_tick(arg0->unk58, arg0->unkA8);
    return 1;
}

/* was func_15131C4C */
s32 particle_upd_damp_vel_xz(struct_eu_15E000 *arg0, s32 arg1) {
    vec_damp_xz_per_tick(arg0->unk58, arg0->unkA8);
    return 1;
}

/* was func_15131C7C */
s32 particle_upd_damp_vel(struct_eu_15E000 *arg0, s32 arg1) {
    vec_damp_xyz_per_tick(arg0->unk58, arg0->unkA8);
    return 1;
}

/* was func_15131CAC */
void particle_die_retire(struct102 *arg0) {
    node_retire(arg0);
}

/* was func_15131CCC */
void particle_die_free(struct102 *arg0) {
    node_unlink_free(arg0);
}

/* was func_15131CEC */
void particle_run_hook_bb4(u8 *arg0) {
    s32 idx = (*(s32 *)(arg0 + 0x68) & 0x4000) ? arg0[0x75] : 0;
    g_particle_hook_fns_bb4[idx](arg0);
}

/* was func_15131D38 */
void particle_run_hook_be4(u8 *arg0) {
    s32 idx = (*(s32 *)(arg0 + 0x68) & 0x4000) ? arg0[0x75] : 0;
    g_particle_hook_fns_be4[idx](arg0);
}

/* was func_15131D84 */
s32 particle_upd_kill(s32 arg0, s32 arg1) {
    return 0;
}

/* was func_15131D98 */
void particle_update_wobble_offset(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3) {
    (*(f32 *)((u8 *)arg0 + 0x4C)) = (f32) ((*(f32 *)((u8 *)arg1 + 0)) * angle_byte_cos((*(u8 *)((u8 *)arg2 + 0)) - 0x40));
    (*(f32 *)((u8 *)arg0 + 0x54)) = (f32) ((*(f32 *)((u8 *)arg1 + 4)) * angle_byte_cos((*(u8 *)((u8 *)arg2 + 1)) - 0x40));
    (*(u8 *)((u8 *)arg2 + 0)) = (u8) (((*(u8 *)((u8 *)arg3 + 0)) * g_frame_ticks) + (*(u8 *)((u8 *)arg2 + 0)));
    (*(u8 *)((u8 *)arg2 + 1)) = (u8) (((*(u8 *)((u8 *)arg3 + 1)) * g_frame_ticks) + (*(u8 *)((u8 *)arg2 + 1)));
}

/* was func_15131E58 */
void vec_damp_y_per_tick(f32 *arg0, f32 arg1) {
    s32 i = g_frame_ticks;

    while (i > 0) {
        i--;
        arg0[1] *= arg1;
    }
}

/* was func_15131E88 */
void vec_damp_xz_per_tick(f32 *arg0, f32 arg1) {
    s32 i = g_frame_ticks;

    while (i > 0) {
        i--;
        arg0[0] *= arg1;
        arg0[2] *= arg1;
    }
}

/* was func_15131EC8 */
void vec_damp_xyz_per_tick(f32 *arg0, f32 arg1) {
    s32 i = g_frame_ticks;

    while (i > 0) {
        i--;
        arg0[0] *= arg1;
        arg0[1] *= arg1;
        arg0[2] *= arg1;
    }
}

s32 particle_surface_hit_dispatch(); // callers pass s32 / pointers; the NM definition below takes (u8 *, u8 *, u8 *)

/* was func_15131F14 */
/* P373: particle update handler (g_particle_update_fns [27], called by particle_sprite_update as s32 (particle, old
 * position); 0 = the particle dies and its death handler runs). The asm tail-calls particle_surface_hit_dispatch and returns with its
 * v0 untouched. The C used to be void, and the port's indirect call of a void function reads 0, so every particle
 * of this kind died in its first update (same class as P372's flame_flicker). */
s32 particle_check_surface_hit(s32 particle, s32 old_pos) { /* particle was arg0, old_pos was arg1 */
    return particle_surface_hit_dispatch(particle, old_pos, particle + 0xA8);
}

extern s32 (*g_particle_hit_fns[])(u8 *, s32, u8 *, u8 *); /* was D_80089C14 */ // only entry 0: particle_hit_bounce (reads cfg as arg3)
s32 pos_in_world_bounds(f32 *);
s32 collision_floor_probe(f32 *, s32, f32, f32 *);

// surface_hit_dispatch: when the hit config `cfg` is on (bit 0 of cfg[0]) with a handler (g_particle_hit_fns[(s8) cfg[1]],
// -1 = none) and the object (+0x40 / 0x44 / 0x48 x / y / z) is below `other`'s y (+4): probes the point (obj x,
// other y, obj z) (pos_in_world_bounds; 0 = outside: returns 0) and the floor down to obj y - 0.06 * obj +0x3C
// (collision_floor_probe, height into obj + 0x80); on a hit calls the handler with (obj, other, {x, floor height, z}, cfg)
// and returns its low byte. Returns 1 in every other case.
/* was func_15131F34 */
s32 particle_surface_hit_dispatch(u8 *obj, u8 *other, u8 *cfg) {
    f32 p[3];
    f32 q[3];

    if (!(cfg[0] & 1) || (s8) cfg[1] == -1 || g_particle_hit_fns[(s8) cfg[1]] == NULL) {
        return 1;
    }
    if (!(*(f32 *) (obj + 0x44) < *(f32 *) (other + 4))) {
        return 1;
    }
    p[0] = *(f32 *) (obj + 0x40);
    p[1] = *(f32 *) (other + 4);
    p[2] = *(f32 *) (obj + 0x48);
    if (pos_in_world_bounds(p) == 0) {
        return 0;
    }
    if (collision_floor_probe(p, 0, *(f32 *) (obj + 0x44) - *(f32 *) (obj + 0x3C) * 0.060000002f, (f32 *) (obj + 0x80)) == 0) {
        return 1;
    }
    q[0] = p[0];
    q[1] = *(f32 *) (obj + 0x80);
    q[2] = p[2];
    return g_particle_hit_fns[(s8) cfg[1]](obj, (s32) other, (u8 *) q, cfg) & 0xFF;
}

/* was func_1513206C */
/* P373: particle update handler (g_particle_update_fns [28], called by particle_sprite_update as s32 (particle, old
 * position); 0 = the particle dies and its death handler runs). The asm tail-calls particle_surface_hit_dispatch and returns with its
 * v0 untouched. The C used to be void, and the port's indirect call of a void function reads 0, so every particle
 * of this kind died in its first update (same class as P372's flame_flicker). */
s32 particle_upd_damp_hit(struct_eu_15E000 *particle, s32 old_pos) { /* particle was arg0, old_pos was arg1 */
    vec_damp_xyz_per_tick(particle->unk58, particle->unkA8);
    return particle_surface_hit_dispatch(particle, old_pos, (u8 *)particle + 0xB0);
}

/* was func_151320AC */
/* P373: particle update handler (g_particle_update_fns [29], called by particle_sprite_update as s32 (particle, old
 * position); 0 = the particle dies and its death handler runs). The asm tail-calls particle_surface_hit_dispatch and returns with its
 * v0 untouched. The C used to be void, and the port's indirect call of a void function reads 0, so every particle
 * of this kind died in its first update (same class as P372's flame_flicker). */
s32 particle_upd_damp_xz_hit(struct_eu_15E000 *particle, s32 old_pos) { /* particle was arg0, old_pos was arg1 */
    vec_damp_xz_per_tick(particle->unk58, particle->unkA8);
    return particle_surface_hit_dispatch(particle, old_pos, (u8 *)particle + 0xB0);
}

/* was func_151320EC */
s32 particle_hit_bounce(u8 *arg0, s32 arg1, u8 *arg2, u8 *arg3) {
    *(f32 *)(arg0 + 0x44) = *(f32 *)(arg0 + 0x3C) * 0.060000002f + *(f32 *)(arg2 + 4);
    *(f32 *)(arg0 + 0x58) *= *(f32 *)(arg3 + 4);
    *(f32 *)(arg0 + 0x5C) = -*(f32 *)(arg3 + 4) * *(f32 *)(arg0 + 0x5C);
    *(f32 *)(arg0 + 0x60) *= *(f32 *)(arg3 + 4);
    if (fabsf(*(f32 *)(arg0 + 0x5C)) < 1.9970001f) {
        *(f32 *)(arg0 + 0x58) = 0.0f;
        *(f32 *)(arg0 + 0x5C) = 0.0f;
        *(f32 *)(arg0 + 0x60) = 0.0f;
        *(f32 *)(arg0 + 0x64) = 0.0f;
        arg3[0] &= ~1;
        *(s32 *)(arg0 + 0x68) &= ~6;
    }
    return 1;
}

extern void (*g_particle_msg_fns[])(u8 *, u8 *, u8); /* was D_80089C18 */
/* was func_1513219C */
void particle_run_msg_hook(u8 *arg0, u8 *arg1, u8 arg2) {
    void (*f)(u8 *, u8 *, u8);
    if (*(s32 *)(arg0 + 0x68) & 0x4000) {
        f = g_particle_msg_fns[arg0[0x75]];
        if (f != NULL) {
            f(arg0, arg1, arg2);
        }
    }
}

/* was func_151321F4 */
void particle_calc_wobble(u8 *arg0, u8 *arg1, f32 arg2, u8 *arg3, f32 *arg4, f32 *arg5)
{
  u8 temp_a0;
  f32 r;
  temp_a0 = ((*((s8 *) (((u8 *) arg1) + 0))) * g_frame_ticks) + (*((u8 *) (((u8 *) arg0) + 0)));
  temp_a0 = (*((u8 *) (((u8 *) arg0) + 0)) = temp_a0);  // fakematch: chained store assignment pins temp_a0 to a0
  *((u8 *) (((u8 *) arg0) + 1)) = (u8) (((*((s8 *) (((u8 *) arg1) + 1))) * g_frame_ticks) + (*((u8 *) (((u8 *) arg0) + 1))));
  temp_a0 = temp_a0 - 0x40;
  r = angle_byte_cos(temp_a0);
  *arg4 = ((*((f32 *) (((u8 *) arg3) + 0))) * (0, r)) + arg2;  // fakematch: comma flips mul.s operand order
  r = angle_byte_cos((*((u8 *) (((u8 *) arg0) + 1))) - 0x40);
  *arg5 = ((*((f32 *) (((u8 *) arg3) + 4))) * (0, r)) + arg2;  // fakematch: comma flips mul.s operand order
}

/* was func_151322BC */
void particle_broadcast(s32 arg0, u8 arg1) {
    const s32 sp1C[3] = {0x2B, 0x47, 0x52};

    node_broadcast_types(sp1C, 0x3, arg0, arg1);
}

/* was func_1513230C */
s32 particle_upd_wobble_size(u8 *arg0, s32 arg1) {
    particle_calc_wobble(arg0 + 0xA8, arg0 + 0xAA, *(f32 *)(arg0 + 0xAC), arg0 + 0xB0, arg0 + 0x38, arg0 + 0x3C);
    return 1;
}

/* was func_1513235C */
s32 particle_upd_expand_fade(u8 *arg0, s32 arg1) {
    f32 temp_f12;
    f32 temp_f2;

    temp_f2 = (*(f32 *)((u8 *)arg0 + 0xA8));
    temp_f12 = (*(f32 *)((u8 *)arg0 + 0xB0)) * sqrtf(temp_f2);
    (*(f32 *)((u8 *)arg0 + 0x3C)) = temp_f12;
    (*(f32 *)((u8 *)arg0 + 0x38)) = temp_f12;
    (*(s8 *)((u8 *)arg0 + 0x2B)) = (s8) (u32) ((*(f32 *)((u8 *)arg0 + 0xB4)) - ((*(f32 *)((u8 *)arg0 + 0xB8)) * temp_f2 * temp_f2));
    (*(f32 *)((u8 *)arg0 + 0xA8)) = (f32) (temp_f2 + g_frame_step_f);
    if ((*(f32 *)((u8 *)arg0 + 0xAC)) < (*(f32 *)((u8 *)arg0 + 0xA8))) {
        return 0;
    }
    return 1;
}

/* was func_15132454 */
s32 particle_spawn_smoke_puff(u8 *arg0, f32 arg1, u8 arg2, s32 arg3) {
    struct {
        f32 u2C;
        f32 u30;
        f32 u34;
        f32 u38;
        f32 u3C;
        s32 u40;
        s32 u44;
        s16 u48;
        s16 u4A;
        s32 u4C;
        s32 u50;
        s8 u54;
        s8 u55;
        s8 u56;
        s8 u57;
        s8 u58;
        s8 u59;
        s8 u5A;
        s8 u5B;
        s8 u5C;
        s8 u5D;
        s16 u5E;
        s16 u60;
        s16 u62;
        f32 u64;
        f32 u68;
        f32 u6C;
        s32 u70;
        u8 pad74[0x8];
        s32 u7C;
        u8 pad80[0x8];
        s32 u88;
        u8 pad8C[0x8];
        f32 u94;
        s32 u98;
        s32 u9C;
        s8 uA0;
        s8 uA1;
        s8 uA2;
        s8 uA3;
        s8 uA4;
        s8 uA5;
        s8 uA6;
    } sp;
    s32 sp28;
    s32 sp20;
    f32 temp_f10;
    s32 temp_v0;
    s32 var_v0;
    s32 var_v1;
    s32 var_v1_2;
    u8 *temp_t4;
    u8 *temp_t6;

    sp.u2C = 0.0f;
    sp.u34 = 594.49f * arg1;
    sp.u30 = (2.0f * random_float()) + 5.0f;
    temp_f10 = (random_float() * 15.0f) + 240.0f;
    sp.u38 = temp_f10;
    sp.u3C = temp_f10 / (sp.u30 * sp.u30);
    sp.u44 = 1;
    sp.u5B = (s8) (u32) temp_f10;
    sp.u5D = 0x69;
    sp.u48 = 0x4417;
    sp.u40 = 0x200004;
    sp.u4C = 0;
    sp.u50 = 0;
    sp.u58 = 0xFF;
    sp.u59 = 0xFF;
    sp.u5A = 0xFF;
    sp.u57 = 0xFF;
    sp.u54 = 0xFF;
    sp.u55 = 0xFF;
    sp.u56 = 0xFF;
    sp.u5C = 0xFF;
    temp_t6 = ((u8 *)&g_vec3_zero);
    (*(s32 *)((u8 *)(&sp.u70) + 0)) = (s32) (*(s32 *)((u8 *)arg0 + 0));
    (*(s32 *)((u8 *)(&sp.u70) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 4));
    (*(s32 *)((u8 *)(&sp.u70) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 8));
    (*(s32 *)((u8 *)(&sp.u7C) + 0)) = (s32) (*(s32 *)((u8 *)temp_t6 + 0));
    (*(s32 *)((u8 *)(&sp.u7C) + 4)) = (s32) (*(s32 *)((u8 *)temp_t6 + 4));
    (*(s32 *)((u8 *)(&sp.u7C) + 8)) = (s32) (*(s32 *)((u8 *)temp_t6 + 8));
    sp.u5E = 1;
    sp.u60 = 0xFF;
    sp.u62 = 1;
    sp.u64 = 1.0f;
    var_v1_2 = 0;
    if (random_int() & 1) {
        var_v1_2 = 0x40;
    }
    sp20 = var_v1_2;
    if (random_int() & 1) {
        var_v0 = 0x80;
    } else {
        var_v0 = 0;
    }
    temp_t4 = ((u8 *)&g_vec3_zero);
    sp.u98 = var_v0 | 0x4C000 | var_v1_2;
    sp.uA0 = 6;
    sp.uA1 = 6;
    sp.uA2 = 0x27;
    sp.uA3 = -1;
    sp.uA4 = -1;
    sp.uA5 = 0;
    sp.u9C = 0;
    sp.uA6 = 0xFF;
    (*(s32 *)((u8 *)(&sp.u88) + 0)) = (s32) (*(s32 *)((u8 *)temp_t4 + 0));
    (*(s32 *)((u8 *)(&sp.u88) + 4)) = (s32) (*(s32 *)((u8 *)temp_t4 + 4));
    (*(s32 *)((u8 *)(&sp.u88) + 8)) = (s32) (*(s32 *)((u8 *)temp_t4 + 8));
    sp.u4A = 0x12C;
    sp.u68 = 0.0f;
    sp.u6C = 0.0f;
    sp.u94 = 0.0f;
    temp_v0 = particle_spawn_ex((s32) &sp.u40, 1U, 0, 0x14, (u8) (s32) arg2, arg3);
    var_v1 = temp_v0;
    if (temp_v0 != 0) {
        sp28 = temp_v0;
        memcpy(temp_v0 + 0xA8, &sp.u2C, 0x14);
        var_v1 = sp28;
    }
    return var_v1;
}