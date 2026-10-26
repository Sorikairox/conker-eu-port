#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
s32 flare_node_depth_test(u8 *arg0, u32 *arg1);


u8 *allocate_memory(s32, s32, s32, s32);

/* was func_1517E080 */
u8 *flare_node_add(s32 arg0, s32 arg1) {
    s32 *sp18;
    s32 *var_t0;
    s32 var_v0;
    s32 var_v1;
    u8 *temp_v0;

    var_v1 = g_flare_nodes;
    if (var_v1 != 0) {
        var_v0 = (*(s32 *)((u8 *)var_v1 + 0x24));
        if (var_v0 != 0) {
            do {
                var_v1 = var_v0;
                var_v0 = (*(s32 *)((u8 *)var_v0 + 0x24));
            } while (var_v0 != 0);
        }
        var_t0 = var_v1 + 0x24;
    } else {
        var_t0 = &g_flare_nodes;
    }
    sp18 = var_t0;
    temp_v0 = allocate_memory(0x34, 1, 0, 1);
    if (temp_v0 == NULL) {
        return NULL;
    }
    *var_t0 = (s32) temp_v0;
    (*(s32 *)((u8 *)temp_v0 + 0x24)) = 0;
    (*(s16 *)((u8 *)temp_v0 + 0x28)) = 0;
    (*(s8 *)((u8 *)temp_v0 + 0x2E)) = 0;
    (*(f32 *)((u8 *)temp_v0 + 0x10)) = 0.0f;
    (*(f32 *)((u8 *)temp_v0 + 0xC)) = 0.0f;
    (*(s8 *)((u8 *)temp_v0 + 0x2F)) = (s8) arg0;
    (*(s8 *)((u8 *)temp_v0 + 0x30)) = (s8) arg1;
    return temp_v0;
}

void heap_free(void *);

// object_node_remove: unlinks node arg0 (an object's +0x154) from the list g_flare_nodes (next at +0x24, appended
// by flare_node_add) and frees it (heap_free); a node that is not in the list is left alone (not freed).
// arg1 (the owner) is not read.
/* was func_1517E6A4 */
void flare_node_remove(f32 *arg0, structEU_16DC80 *arg1) {
    u8 *node = (u8 *) arg0;
    u8 *prev;

    if (node == (u8 *) g_flare_nodes) {
        g_flare_nodes = *(s32 *) (node + 0x24);
    } else {
        prev = (u8 *) g_flare_nodes;
        while (prev != NULL && *(u8 **) (prev + 0x24) != node) {
            prev = *(u8 **) (prev + 0x24);
        }
        if (prev == NULL) {
            return;
        }
        *(s32 *) (prev + 0x24) = *(s32 *) (node + 0x24);
    }
    heap_free(node);
}

/* was func_1517E71C */
void flare_nodes_read_zbuffer(void) {
    f32 temp_f0;
    f32 temp_f2;
    s32 var_v0;

    var_v0 = g_flare_nodes;
    if (var_v0 != 0) {
        do {
            temp_f0 = *(f32 *)(var_v0 + 0xC);
            if ((temp_f0 >= 0.0f) && (temp_f0 < (f32) g_framebuffer_width)) {
                temp_f2 = *(f32 *)(var_v0 + 0x10);
                if ((temp_f2 >= 0.0f) && (temp_f2 < (f32) g_framebuffer_height)) {
                    *(u16 *)(var_v0 + 0x2A) = *(u16 *)(*(u8 **)&g_zbuffer + ((s32) temp_f0 * 2) + ((u32) (s32) temp_f2 * (u32) g_framebuffer_width * 2));
                }
            }
            var_v0 = *(s32 *)(var_v0 + 0x24);
        } while (var_v0 != 0);
    }
}

s32 flare_world_to_screen(f32 x, f32 y, f32 z, f32 *outX, f32 *outY);
Gfx *flare_lens_draw(Gfx *gdl, u8 *node, s32 r, s32 g, s32 b, s32 alpha, u8 *flag);
extern u8 g_flare_ring_red[2]; /* was D_8008D3A4 */
extern u8 g_flare_ring_green[2]; /* was D_8008D3A8 */
extern u8 g_flare_ring_blue[2]; /* was D_8008D3AC */
extern u8 g_flare_sprite_mode_set; /* was D_800DE190 */

/* Node list g_flare_nodes (0x34-byte nodes, see flare_node_add): +0xC/+0x10 screen x/y, +0x24 next,
 * +0x2A/+0x2C u16, +0x2E flags (1 = world-projected, 2 = clears g_sun_flash_alpha when hidden), +0x2F colour index,
 * +0x30 enabled. Each visible node is drawn by flare_lens_draw. */
#define NM_E7FC_U8(n, o) (*((u8 *)(n) + (o)))
#define NM_E7FC_U16(n, o) (*(u16 *)((u8 *)(n) + (o)))
/* was func_1517E7FC */
Gfx *flare_nodes_draw(Gfx *gdl, s32 arg1) {
    u8 rr[2], gg[2], bb[2];
    u8 *node;
    u8 *flag;
    f32 *pos;
    u32 t;
    s32 hide;
    s32 alpha = -1; /* the asm starts from a stale stack word; every drawn node sets it first */
    u8 fl;

    rr[0] = g_flare_ring_red[0];
    rr[1] = g_flare_ring_red[1];
    gg[0] = g_flare_ring_green[0];
    gg[1] = g_flare_ring_green[1];
    bb[0] = g_flare_ring_blue[0];
    bb[1] = g_flare_ring_blue[1];
    g_flare_sprite_mode_set = 0;
    for (node = (u8 *)g_flare_nodes; node != NULL; node = *(u8 **)(node + 0x24)) {
        if (NM_E7FC_U8(node, 0x30) == 0) {
            continue;
        }
        hide = 0;
        fl = NM_E7FC_U8(node, 0x2E);
        if (fl & 1) {
            if (g_level_lights_mode == 0) {
                hide = 1;
            } else {
                pos = (f32 *)g_flare_level_points[*((u8 *)g_level_header + 0x10)];
                if (flare_world_to_screen(pos[0], pos[1], pos[2], (f32 *)(node + 0xC), (f32 *)(node + 0x10)) != 1) {
                    hide = 1;
                }
                alpha = (NM_E7FC_U16(node, 0x2A) == 0xFFFC) ? 0xFF : -1;
                fl = NM_E7FC_U8(node, 0x2E);
            }
        } else {
            if (flare_node_depth_test(node, &t) != 1) {
                hide = 1;
            }
            alpha = ((s32)(NM_E7FC_U16(node, 0x2C) - t) < 0x1E) ? 0x100 : -1;
            fl = NM_E7FC_U8(node, 0x2E);
        }
        flag = (fl & 2) ? &g_sun_flash_alpha : NULL;
        if (!hide) {
            fl = NM_E7FC_U8(node, 0x2F);
            gdl = flare_lens_draw(gdl, node, rr[fl], gg[fl], bb[fl], alpha, flag);
        } else if (flag != NULL) {
            *flag = 0;
        }
    }
    return gdl;
}
Gfx *flare_render_mode_set(Gfx *arg0);
Gfx *gfx_load_texture_tile(Gfx *, void *, s32, s32, s32, s32, s32, s32, s32, s32);
Gfx *sprite_draw_at_screen(Gfx *gfx, void *spr, f32 x, f32 y);
extern u8 g_sprite_prim_r; /* sprite primitive colour r, g, b, a; was D_800D31C8 */
extern u8 g_sprite_prim_g; /* was D_800D31C9 */
extern u8 g_sprite_prim_b; /* was D_800D31CA */
extern u8 g_flare_sprite[]; /* flare sprite; was D_8009075C */
extern u8 g_flare_ring_sizes[]; /* flare ring sizes, 7 per row; was D_800A7630 */
extern f32 D_80038400;
extern f32 D_80038404;
extern u8 g_flare_sprite_mode_set; /* flare sprite mode set this frame; was D_800DE190 */

/* sprite_draw_at_screen sprite request */
typedef struct {
    /* 0x00 */ u8 pad00[6];
    /* 0x06 */ s16 scaleX;
    /* 0x08 */ s16 scaleY;
    /* 0x0A */ u8 alpha;
    /* 0x0B */ u8 u0B;
    /* 0x0C */ u8 u0C;
    /* 0x0D */ u8 u0D;
    /* 0x0E */ u8 pad0E[2];
    /* 0x10 */ void *tex;
} SprEA18;

// lens_flare_draw: draws the lens flare of a sun node (screen position +0xC / +0x10). With fade (g_sun_flash_alpha) it moves
// *fade (by 5 * g_frame_ticks) towards (120 - d) * 176 / 120 for distances d = (dx^2 + dy^2) * falloff / 10 from the
// screen centre under 120 (0 when hidden: brightness -1). The flare strength +0x28 moves (by 10 * g_frame_ticks)
// towards 0x1ADB00 / (d + 10000) * brightness / 256 (0 off screen or hidden). If d < 200000, +0x28 > 0 and the node
// is within 2000 of the screen, draws `count` rings (sprite g_flare_sprite, mode set once a frame) along the line from
// the node through the centre (k * 2 / 5 of the offset), alpha +0x28 * +0x30 / 256, sizes g_flare_ring_sizes[row * 7 + k].
/* was func_1517EA18 */
Gfx *flare_lens_draw(Gfx *gdl, u8 *node, s32 row, s32 count, s32 falloff, s32 bright, u8 *fade) {
    SprEA18 spr;
    f32 dx, dy;
    f32 f;
    f32 size;
    s32 ix, iy;
    s32 d;
    s32 target;
    s32 cur;
    s32 step;
    s32 alpha;
    s32 i;
    s32 j;
    u8 *sizes;

    dx = *(f32 *) (node + 0xC) - g_framebuffer_width * 0.5f;
    dy = *(f32 *) (node + 0x10) - g_framebuffer_height * 0.5f;
    if (fade != NULL) {
        if (bright == -1) {
            target = 0;
        } else {
            ix = dx;
            iy = dy;
            d = (ix * ix + iy * iy) * falloff / 10;
            if (d < 120) {
                target = (120 - d) * 176 / 120;
            } else {
                target = 0;
            }
        }
        cur = *fade;
        step = g_frame_ticks * 5;
        if (((target - cur) < 0 ? -(target - cur) : (target - cur)) < step) {
            cur = target;
        } else if (cur < target) {
            cur += step;
        } else {
            cur -= step;
        }
        *fade = cur;
    }
    ix = dx;
    iy = dy;
    d = (ix * ix + iy * iy) * falloff / 10;
    if (*(f32 *) (node + 0xC) < 2.0f || (f32) (g_framebuffer_width - 2) <= *(f32 *) (node + 0xC) ||
        *(f32 *) (node + 0x10) < 0.0f || (f32) g_framebuffer_height <= *(f32 *) (node + 0x10)) {
        target = 0;
    } else if (bright == -1) {
        target = 0;
    } else {
        target = 0x1ADB00 / (d + 10000) * bright / 256;
    }
    step = g_frame_ticks * 10;
    cur = *(s16 *) (node + 0x28);
    if (((target - cur) < 0 ? -(target - cur) : (target - cur)) < step) {
        *(s16 *) (node + 0x28) = target;
    } else if (target < cur) {
        *(s16 *) (node + 0x28) = cur - step;
    } else {
        *(s16 *) (node + 0x28) = cur + step;
    }
    if (d >= 200000 || *(s16 *) (node + 0x28) <= 0 || !(fabsf(*(f32 *) (node + 0xC)) < 2000.0f) ||
        !(fabsf(*(f32 *) (node + 0x10)) < 2000.0f)) {
        return gdl;
    }
    g_sprite_prim_r = 0xFF;
    g_sprite_prim_g = 0xFF;
    g_sprite_prim_b = 0xFF;
    spr.tex = g_flare_sprite;
    spr.u0B = 0;
    spr.u0C = 0;
    spr.u0D = 0;
    if (g_flare_sprite_mode_set == 0) {
        gdl = gfx_load_texture_tile(flare_render_mode_set(gdl), g_flare_sprite, 0, 0, 0, 0, 2, 0x100, 0x100, 3);
        g_flare_sprite_mode_set = 1;
    }
    alpha = (*(s16 *) (node + 0x28) * node[0x30]) >> 8;
    sizes = &g_flare_ring_sizes[row * 7];
    for (i = 0, j = 2; i < count; i++, j += 2) {
        f = j;
        spr.alpha = alpha;
        size = sizes[i] << 12;
        g_sprite_keep_prim_colour = 0;
        spr.scaleX = size * D_80038400 / 255.0f;
        spr.scaleY = size * D_80038404 / 255.0f;
        gdl = sprite_draw_at_screen(gdl, &spr, *(f32 *) (node + 0xC) - dx * f / 5.0f,
                            *(f32 *) (node + 0x10) - dy * f / 5.0f + sizes[i] * 0.015625f);
        gDPPipeSync(gdl++);
    }
    return gdl;
}

/* was func_1517EFBC */
Gfx *flare_render_mode_set(Gfx *arg0) {
    gDPPipeSync(arg0++);
    gDPSetCombine(arg0++, 0xFFB3FF, 0xFF65FEFF);
    gDPSetOtherMode(arg0++, 0x2C0F, 0x504344);
    return arg0;
}

void camera_view_rotation_matrix(s32, f32 (*)[4], f32, f32, f32);
void mtxf_transform_point_w(f32 (*)[4], f32, f32, f32, f32 *, f32 *, f32 *, f32 *);

// world_to_screen: projects (x, y, z) with the current player's camera (g_player_views[g_cur_view_player]: view matrix from
// camera_view_rotation_matrix with -pitch +0x388, -yaw +0x380 and +0x5EC) into its viewport (g_player_cams + player * 0x180: half
// width +0xC, half height +0x10). In front (w > 10): *outX / *outY = viewport centre + projected x / - projected y,
// returns 1; else both 0 and returns 0.
/* was func_1517F01C */
s32 flare_world_to_screen(f32 x, f32 y, f32 z, f32 *outX, f32 *outY) {
    f32 mtx[4][4];
    u8 *cam;
    u8 *vp;
    f32 hw;
    f32 hh;
    f32 inv;
    f32 sx;
    f32 sy;
    f32 sz;
    f32 w;

    cam = (u8 *) g_player_views + g_cur_view_player * 0x9A0;
    camera_view_rotation_matrix(g_cur_view_player, mtx, -*(f32 *) (cam + 0x388), -*(f32 *) (cam + 0x380), *(f32 *) (cam + 0x5EC));
    vp = (u8 *) g_player_cams + g_cur_view_player * 0x180;
    hw = *(f32 *) (vp + 0xC);
    hh = *(f32 *) (vp + 0x10);
    mtxf_transform_point_w(mtx, x, y, z, &sx, &sy, &sz, &w);
    if (10.0f < w) {
        inv = 1.0f / w;
        sx = sx * hw * inv;
        sy = sy * hh * inv;
        *outX = hw + sx;
        *outY = hh - sy;
        return 1;
    }
    *outX = 0.0f;
    *outY = 0.0f;
    return 0;
}

s32 sprite_project_point(f32, f32, f32, u8 *, u8 *, f32 *, f32 *, f32);
extern s32 g_zbuf_decode_table; /* was D_800899D0 */

/* was func_1517F18C */
s32 flare_node_depth_test(u8 *arg0, u32 *arg1) {
    struct {
        f32 u28;
        f32 u2C;
    } sp;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f2;
    u16 temp_a3;
    u8 *temp_a1;
    u8 *temp_a2;

    if (sprite_project_point((*(f32 *)((u8 *)arg0 + 0)), (*(f32 *)((u8 *)arg0 + 4)), (*(f32 *)((u8 *)arg0 + 8)), arg0 + 0xC, arg0 + 0x10, &sp.u2C, &sp.u28, 4000.0f) == 1) {
        if ((*(u8 *)((u8 *)arg0 + 0x2E)) & 4) {
            temp_f2 = (*(f32 *)((u8 *)arg0 + 0)) - g_player_views->unk2F8;
            temp_f12 = (*(f32 *)((u8 *)arg0 + 4)) - g_player_views->unk2FC;
            temp_f14 = (*(f32 *)((u8 *)arg0 + 8)) - g_player_views->unk300;
            if ((((temp_f2 * (*(f32 *)((u8 *)arg0 + 0x14))) + (temp_f12 * (*(f32 *)((u8 *)arg0 + 0x18))) + (temp_f14 * (*(f32 *)((u8 *)arg0 + 0x1C)))) / sqrtf((temp_f2 * temp_f2) + (temp_f12 * temp_f12) + (temp_f14 * temp_f14))) < (*(f32 *)((u8 *)arg0 + 0x20))) {
                return 1;
            }
        }
        temp_a3 = (*(u16 *)((u8 *)arg0 + 0x2A));
        temp_a1 = ((s32 *)((u8 *)&g_zbuf_decode_table + (((s32) temp_a3 >> 0xD) * 8)));
        *arg1 = (u32) ((*(s32 *)((u8 *)temp_a1 + 4)) + ((((s32) temp_a3 >> 2) & 0x7FF) << (*(s32 *)((u8 *)temp_a1 + 0)))) >> 3;
        temp_a2 = g_player_cams + (g_dl_buf_index * 0x10);
        (*(s16 *)((u8 *)arg0 + 0x2C)) = (s16) (u32) (((f32) (*(s16 *)((u8 *)temp_a2 + 0x4C)) + ((sp.u2C / sp.u28) * (f32) (*(s16 *)((u8 *)temp_a2 + 0x44)))) * 32.0f);
        return 1;
    }
    return 0;
}