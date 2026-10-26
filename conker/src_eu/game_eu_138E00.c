#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
void mtxf_mul(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
void camera_compute_frustum_planes(s32);


extern f32 D_800D3A90;
extern f32 D_800D9F3C;
extern f32 D_800D9F40;
extern Mtx D_800D9F48;
extern s16 D_800DD722;
extern s16 D_800DD724;
extern f32 D_800A2FF0;
void game_gu_ortho(void *, float, float, float, float, float, float, float);

/* screen size from D_800DD722/4, then an orthographic projection (guOrtho) over the current camera extent */
/* was func_1510B5F0 */
void camera_set_screen_ortho(s32 arg0) {
    f32 w;
    f32 h;

    D_800D9F40 = (f32)D_800DD722;
    D_800D9F3C = (f32)D_800DD724;
    D_800D3A90 = 100.0f - D_800D9F3C;
    h = ((f32 *)((u8 *)D_800BE628 + 0x10))[0];
    w = ((f32 *)((u8 *)D_800BE628 + 0xC))[0];
    game_gu_ortho(&D_800D9F48, -w, w, -h, h, 1.0f, D_800A2FF0, 1.0f);
}
extern f32 D_800C3A6C;            /* extra angle added to both fields of view */
extern f32 D_800C3A70;            /* viewport width override (0: use arg4 or the screen width) */
extern f32 D_800C3A74;            /* viewport height override (0: the screen height) */
extern f32 D_800D9F40;
extern f32 D_800D9F3C;
void camera_perspective_build(s32 arg0, u16 *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);

/* Per-player projection: camera record r = D_800BE628 + player * 0x180. Field of view r+0x74 / r+0x78 (degrees) =
 * base r+0x6C / r+0x70 + fovX / fovY + D_800C3A6C; the half extents r+0x1C / r+0x20 = r+0x7C * r+0x14 * r+0xC *
 * cot(fov / 2) * scale (r+0x80, r+0x18, r+0x10 for y); then camera_perspective_build builds the matrix into r+0xB8 with the
 * viewport size (D_800C3A70 / width / the screen width, D_800C3A74 / the screen height). */
/* was func_1510B6A8 */
void camera_projection_update(s32 player, f32 fovX, f32 fovY, f32 scale, f32 width) {
    s32 off = player * 0x180;
    u8 *r;
    f32 a, c, w, h;

    r = (u8 *)D_800BE628 + off;
    *(f32 *)(r + 0x74) = *(f32 *)(r + 0x6C) + fovX + D_800C3A6C;
    r = (u8 *)D_800BE628 + off;
    *(f32 *)(r + 0x78) = *(f32 *)(r + 0x70) + fovY + D_800C3A6C;
    r = (u8 *)D_800BE628 + off;
    a = *(f32 *)(r + 0x74) * 0.008726646f; /* pi / 360 */
    c = cosf(a);
    r = (u8 *)D_800BE628 + off;
    *(f32 *)(r + 0x1C) = *(f32 *)(r + 0x7C) * (*(f32 *)(r + 0x14) * ((c * *(f32 *)(r + 0xC)) / sinf(a))) * scale;
    r = (u8 *)D_800BE628 + off;
    a = *(f32 *)(r + 0x78) * 0.008726646f;
    c = cosf(a);
    r = (u8 *)D_800BE628 + off;
    *(f32 *)(r + 0x20) = *(f32 *)(r + 0x80) * (*(f32 *)(r + 0x18) * ((c * *(f32 *)(r + 0x10)) / sinf(a))) * scale;
    if (D_800C3A70 != 0.0f) {
        w = D_800C3A70;
    } else if (width != 0.0f) {
        w = width;
    } else {
        w = D_800D9F40;
    }
    if (D_800C3A74 != 0.0f) {
        h = D_800C3A74;
    } else {
        h = D_800D9F3C;
    }
    r = (u8 *)D_800BE628 + off;
    camera_perspective_build(player, (u16 *)(r + 0xB8), *(f32 *)(r + 0x78), *(f32 *)(r + 0x74), w, h, scale);
}
struct V3 { f32 x, y, z; };
extern struct V3 D_800D9EE0[];
extern u8 D_800D9F10;
/* was func_1510B8AC */
void camera_projection_set_fov(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    camera_projection_update(arg0, arg1, arg2, arg3, 0.0f);
    D_800D9EE0[arg0].x = arg3;
    D_800D9EE0[arg0].y = arg1;
    D_800D9EE0[arg0].z = arg2;
    D_800D9F10 = 1;
}

/* was func_1510B930 */
void camera_projection_apply_pending_fov(void)
{
    s32 i;
    for (i = 0; i <= D_80082FA0; i++) {
        if (D_800D9EE0[i].x != -1.0f) {
            camera_projection_update(i, D_800D9EE0[i].y, D_800D9EE0[i].z, D_800D9EE0[i].x, 0.0f);
            D_800D9EE0[i].x = -1.0f;
        }
    }
    D_800D9F10 = 0;
}

struct PendingF2 { f32 x; f32 y; };
extern struct PendingF2 D_800D9F18[];
extern u8 D_800D9F38;
extern f32 D_800D9F40;
extern f32 D_800D9F3C;
void camera_perspective_build(s32 arg0, u16 *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);

/* Rebuild the player's projection for a viewport of width x height (0: the screen size) now, and remember the size
 * in D_800D9F18[player] (applied again by camera_projection_apply_pending_viewport; D_800D9F38 = pending). */
/* was func_1510B9D8 */
void camera_projection_set_viewport(s32 player, f32 width, f32 height) {
    u8 *r;

    if (width == 0.0f) {
        width = D_800D9F40;
    }
    if (height == 0.0f) {
        height = D_800D9F3C;
    }
    r = (u8 *)D_800BE628 + player * 0x180;
    camera_perspective_build(player, (u16 *)(r + 0xB8), *(f32 *)(r + 0x78), *(f32 *)(r + 0x74), width, height, *(f32 *)(r + 0x84));
    D_800D9F18[player].x = width;
    D_800D9F18[player].y = height;
    D_800D9F38 = 1;
}
// Apply the pending per-player requests queued in D_800D9F18 (x == -1.0f: none) through camera_perspective_build,
// with the player's camera record (D_800BE628, 0x180 bytes each).
extern struct PendingF2 D_800D9F18[];
extern u8 D_800D9F38;
void camera_perspective_build(s32 arg0, u16 *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);

/* was func_1510BA9C */
void camera_projection_apply_pending_viewport(void) {
    s32 i;
    u8 *cam;

    for (i = 0; i <= D_80082FA0; i++) {
        if (D_800D9F18[i].x != -1.0f) {
            cam = (u8 *)D_800BE628 + i * 0x180;
            camera_perspective_build(i, (u16 *)(cam + 0xB8), *(f32 *)(cam + 0x78), *(f32 *)(cam + 0x74), D_800D9F18[i].x,
                          D_800D9F18[i].y, *(f32 *)(cam + 0x84));
            D_800D9F18[i].x = -1.0f;
        }
    }
    D_800D9F38 = 0;
}
/* was func_1510BB78 */
void camera_perspective_build(s32 arg0, u16 *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    s32 sp2C;
    s32 temp_v0;
    s32 temp_v1;

    temp_v1 = arg0 * 0x180;
    sp2C = temp_v1;
    guPerspectiveF(D_800BE628 + temp_v1 + 0xBC, arg1, arg2, arg3, arg4, arg5, arg6);
    temp_v0 = D_800BE628 + temp_v1;
    guMtxF2L(temp_v0 + 0xBC, temp_v0 + (D_800BE9C0 << 6) + 0x100);
}
extern f32 D_800DA030[][4][4];   /* per player: view matrix (float) */
extern f32 D_800DA130[][4][4];   /* per player: product */
extern u8 *D_800DC6D0[];         /* per DL buffer: fixed-point view matrices, 0x40 per player */

/* Per-player matrix refresh (P15, hand C from the asm): converts this frame's fixed-point projection
 * (player record + 0x100 in D_800BE628, 0x180 per player, 0x40 per DL buffer) and view matrix to float,
 * multiplies them into D_800DA130[i] and runs the per-player update camera_compute_frustum_planes(i). */
/* was func_1510BC10 */
void camera_matrices_refresh_all(void) {
    f32 proj[4][4];
    s16 i;

    for (i = 0; i <= D_80082FA0; i++) {
        guMtxL2F(proj, (Mtx *)(D_800BE628 + i * 0x180 + D_800BE9C0 * 0x40 + 0x100));
        guMtxL2F(D_800DA030[i], (Mtx *)(D_800DC6D0[D_800BE9C0] + i * 0x40));
        mtxf_mul(D_800DA030[i], proj, D_800DA130[i]);
        camera_compute_frustum_planes(i);
    }
}
/* was func_1510BD34 */
u8 *view_dl_begin(u8 *arg0, s32 arg1) {
    u8 *temp_a0;
    u8 *temp_a0_10;
    u8 *temp_a0_11;
    u8 *temp_a0_2;
    u8 *temp_a0_3;
    u8 *temp_a0_4;
    u8 *temp_a0_5;
    u8 *temp_a0_6;
    u8 *temp_a0_7;
    u8 *temp_a0_8;
    u8 *temp_a0_9;

    (*(s32 *)((u8 *)arg0 + 0)) = 0xE7000000;
    (*(s32 *)((u8 *)arg0 + 4)) = 0;
    temp_a0_2 = arg0 + 8;
    (*(s32 *)((u8 *)temp_a0_2 + 4)) = 1;
    (*(s32 *)((u8 *)temp_a0_2 + 0)) = 0xF9000000;
    temp_a0_3 = temp_a0_2 + 8;
    (*(s32 *)((u8 *)temp_a0_3 + 0)) = 0xDA380003;
    (*(u8 **)((u8 *)temp_a0_3 + 4)) = D_80089810;
    temp_a0_4 = temp_a0_3 + 8;
    (*(s32 *)((u8 *)temp_a0_4 + 0)) = 0xDB0E0000;
    temp_a0_5 = temp_a0_4 + 8;
    (*(s32 *)((u8 *)temp_a0_4 + 4)) = (s32) (*(u16 *)((u8 *)((D_800BE628 + (arg1 * 0x180))) + 0xB8));
    (*(s32 *)((u8 *)temp_a0_5 + 4)) = 3;
    (*(s32 *)((u8 *)temp_a0_5 + 0)) = 0xDB040004;
    temp_a0_6 = temp_a0_5 + 8;
    (*(s32 *)((u8 *)temp_a0_6 + 0)) = 0xDB04000C;
    (*(s32 *)((u8 *)temp_a0_6 + 4)) = 3;
    temp_a0_7 = temp_a0_6 + 8;
    (*(s32 *)((u8 *)temp_a0_7 + 0)) = 0xDB040014;
    (*(s32 *)((u8 *)temp_a0_7 + 4)) = 0xFFFD;
    temp_a0_8 = temp_a0_7 + 8;
    (*(s32 *)((u8 *)temp_a0_8 + 0)) = 0xDB04001C;
    (*(s32 *)((u8 *)temp_a0_8 + 4)) = 0xFFFD;
    temp_a0_9 = temp_a0_8 + 8;
    (*(s32 *)((u8 *)temp_a0_9 + 0)) = 0xD9EFFFFF;
    (*(s32 *)((u8 *)temp_a0_9 + 4)) = 0;
    temp_a0_10 = temp_a0_9 + 8;
    (*(s32 *)((u8 *)temp_a0_10 + 0)) = 0xDA380007;
    (*(s32 *)((u8 *)temp_a0_10 + 4)) = (s32) (D_800BE628 + (arg1 * 0x180) + (D_800BE9C0 << 6) + 0x100);
    temp_a0_11 = temp_a0_10 + 8;
    (*(s32 *)((u8 *)temp_a0_11 + 0)) = 0xDA380005;
    temp_a0 = temp_a0_11 + 8;
    (*(s32 *)((u8 *)temp_a0_11 + 4)) = (s32) (*(s32 *)((u8 *)&D_800DC6D0 + (D_800BE9C0 * 4)) + (arg1 << 6));
    (*(s32 *)((u8 *)temp_a0 + 0)) = 0xEF082C3F;
    (*(s32 *)((u8 *)temp_a0 + 4)) = 0x552230;
    return temp_a0 + 8;
}
extern f32 D_800D3A00;

/* was func_1510BED8 */
void camera_zoom_factors_calc(s32 arg0) {
    u8 *temp_v0;

    temp_v0 = D_800BE628 + (arg0 * 0x180);
    D_800D3A00 = ((((*(f32 *)((u8 *)temp_v0 + 0x74)) / (*(f32 *)((u8 *)temp_v0 + 0x6C))) - 1.0f) * -1.0f) + (*(f32 *)((u8 *)temp_v0 + 0x64));
    *(((f32 *)((u8 *)&D_800D3A00 + 4))) = ((((*(f32 *)((u8 *)temp_v0 + 0x78)) / (*(f32 *)((u8 *)temp_v0 + 0x70))) - 1.0f) * -1.0f) + (*(f32 *)((u8 *)temp_v0 + 0x68));
}
Gfx *mesh_dl_cull_copy(s32, Gfx *, u8 *, s32, s32, s32);
Gfx *level_dl_visibility_filter(s32, Gfx *, u8 *, s32, s32, s32);
Gfx *wobblers_set_tex_segments(Gfx *);
Gfx *tex_scroll_set_tile_sizes(Gfx *);
Gfx *anim_segments_set(Gfx *);
Gfx *level_parts_set_segments(Gfx *);
Gfx *sky_segments_set(Gfx *);
void tint_channels_update(s16);
Gfx *tint_emit_prim_env_colors(Gfx *gdl, s32 arg1, s32 arg2, s32 arg3);
Gfx *camera_read_depth_row(Gfx *, struct108 *);
Gfx *light_apply_object_lights(Gfx *, s16, s32, s32, s32, s32, s32, s32, u8 *, u8 *, s32, s32, s32, u8 *);
Gfx *light_write_light_cmds(Gfx *, s32, u8, s32, u8 *);
Gfx *fog_identity_stub(Gfx *, s32);
Gfx *occlusion_probes_update(Gfx *, s16);
extern s32 D_800B1214;          /* optional display lists */
extern s32 D_800B1218;
extern u8 D_800BEECA;
extern u8 D_800BEFC0;
extern u8 D_800C3A86;
extern u8 D_800D9FB0[];         /* viewports: [buffer][2] x 16 bytes */
extern u8 g_player_ambient_lights[];         /* per player: [buffer] x 8 bytes; was D_800D9FF0 */
extern s32 D_800DA230[];        /* per player */
extern u8 D_800DA240;
extern u8 D_800DA241;
extern u8 D_800DA248;

/* Build the display list of player `player`'s view. */
/* was func_1510BF50 */
Gfx *player_view_dl_build(Gfx *gdl, s16 player) {
    struct108 *p = &D_800DBFF0[player];
    s32 skipWorld;
    s32 mask;
    u8 *vpPtr;
    s32 *dataPtr;

    D_800BEFC0 = 1;
    skipWorld = FALSE;
    if ((D_800C35EA == 1) && (D_800C3A86 != 0)) {
        skipWorld = TRUE;
    }
    mask = 1 << player;
    if (D_800D18A0 & mask) {
        skipWorld = TRUE;
    }

    gdl = (Gfx *)view_dl_begin((u8 *)gdl, player);
    gdl[0].words.w0 = 0xDC08000A;
    gdl[0].words.w1 = (u32)(D_800D9FB0 + (D_800BE9C0 << 5));
    gdl[1].words.w0 = 0xDC08060A;
    gdl[1].words.w1 = (u32)(D_800D9FB0 + (D_800BE9C0 << 5) + 0x10);
    gdl += 2;
    tint_channels_update(player);
    gdl = fog_identity_stub(tint_emit_prim_env_colors(gdl, 0xFF, 0xFF, player), 1);
    gdl->words.w0 = 0xDA380003;
    gdl->words.w1 = (u32)D_80089810;
    gdl++;

    if (!skipWorld) {
        switch (g_level_id) {
        case 0x14:
            gdl = wobblers_set_tex_segments(gdl);
            break;
        case 0x1A:
            gdl = sky_segments_set(gdl);
            break;
        case 0x13:
            gdl = level_parts_set_segments(gdl);
            break;
        case 0x35:
            gdl = tex_scroll_set_tile_sizes(gdl);
            break;
        case 0x33:
            gdl = anim_segments_set(gdl);
            break;
        }
    }

    collision_select_area(0);
    if (D_800DCD7C == 0) {
        gdl->words.w0 = 0xDC280C0A;
        gdl->words.w1 = (u32)(g_player_ambient_lights + player * 0x10 + D_800BE9C0 * 8);
        gdl++;
    }

    p = (struct108 *)((u8 *)D_800DBFF0 + player * 0x9A0);
    dataPtr = &D_800DA230[player];
    vpPtr = g_player_ambient_lights + player * 0x10;
    gdl = light_apply_object_lights(gdl, player, (s32)p->unk2F8, (s32)p->unk2FC, (s32)p->unk300, 0, *dataPtr, D_800DA240,
                        vpPtr + D_800BE9C0 * 8, &D_800DA241, 1, 0, 0x25, &D_800DA248);

    if (!skipWorld) {
        if (g_level_id != 5) {
            if (D_800BEECA != 0) {
                gDPPipeSync(gdl++);
                if (D_800DBE62 != 0) {
                    if ((g_level_id != 0x14) && (g_level_id != 0x33) && (g_level_id != 0x32)) {
                        gdl = level_dl_visibility_filter(g_level_part_dls[0], gdl, (u8 *)D_800DA030[player], 0, 0, mask);
                    } else {
                        gdl->words.w0 = 0xDE000000;
                        gdl->words.w1 = g_level_part_dls[0];
                        gdl++;
                    }
                    if (D_800B1214 != 0) {
                        gDPPipeSync(gdl++);
                        gdl = fog_identity_stub(tint_emit_prim_env_colors(gdl, 0xFF, 0xFF, player), 1);
                        if (g_level_id == 0x35) {
                            gdl = tex_scroll_set_tile_sizes(gdl);
                        }
                        gdl->words.w0 = 0xDE000000;
                        gdl->words.w1 = D_800B1214;
                        gdl++;
                    }
                    D_800BEFC0 = 0;
                    p = &D_800DBFF0[player];
                    if ((p->pad880[0x38] != 0) && (p->unk84 & 8)) {
                        gdl = camera_read_depth_row(gdl, p);
                        gDPPipeSync(gdl++);
                    }
                } else {
                    gdl->words.w0 = 0xDE000000;
                    gdl->words.w1 = g_level_part_dls[0];
                    gdl++;
                }
            } else {
                gdl->words.w0 = 0xDE000000;
                gdl->words.w1 = g_level_part_dls[0];
                gdl++;
            }
        }
        gdl = light_write_light_cmds(gdl, *dataPtr, D_800DA240, D_800DA241, vpPtr + D_800BE9C0 * 8);
        if (D_800B1218 != 0) {
            gDPPipeSync(gdl++);
            gdl = tint_emit_prim_env_colors(gdl, 0xFF, 0xFF, player);
            gdl->words.w0 = 0xDE000000;
            gdl->words.w1 = D_800B1218;
            gdl++;
        }
    }
    gdl = occlusion_probes_update(gdl, player);
    gDPPipeSync(gdl++);
    return gdl;
}
/* P181 */
s32 texture_cache_lookup(s32, s32 *, s32, s32);
extern s32 D_800B1268[]; /* per texture key: the texture address its G_SETTIMG loads */

// dl_find_texture_vertices: P181: scans display list `dl` for the (skip+1)-th G_SETTIMG (0xFD) of texture
// D_800B1268[key], then walks to the vertex load (G_VTX, 1) of the triangles drawn with it and follows the
// triangle commands (G_TRI1 5, G_TRI2 6, 0x1X four-triangle packs) until the next texture or G_ENDDL. *out gets
// the lowest vertex address used (the loaded block start, moved up to the smallest vertex index of the first
// triangle seen after walking back to the load); the result is the number of vertices from *out to the highest
// index used of the last load. 0 when the texture is not found. The G_VTX scan back steps one command before the
// load (the asm re-reads that command as part of the triangle phase). `vbase` is an uninitialised stack slot in
// the asm (only read when a texture or G_ENDDL ends the list before any vertex load); 0 here.
/* was func_1510C4E0 */
s32 dl_find_texture_vertices(Gfx *dl, s32 key, Vtx **out, s32 skip) {
    s32 idx[12];
    s32 tmp;
    s32 state;
    s32 max;
    s32 nest;
    s32 first;
    s32 found;
    s32 n;
    s32 k;
    s32 lo;
    u32 w0;
    u32 w1;
    u32 vbase;
    s32 c;

    texture_cache_lookup(key, &tmp, 3, 0);
    *out = NULL;
    state = 0;
    max = 0;
    nest = 0;
    first = 0;
    vbase = 0;
    for (;;) {
        c = (s8)(dl->words.w0 >> 24);
        if (state == 0) {
            /* find the texture */
            if (c == -0x21) {
                return 0;
            }
            if (c == -3 && dl->words.w1 == (u32)D_800B1268[key]) {
                if (skip-- < 1) {
                    state++;
                }
            }
            dl++;
        } else if (state == 1) {
            /* find its vertex load: forward to a G_VTX, or back from the first triangle */
            found = 0;
            if (c != 5 && c != 6 && (c >> 4) != 1) {
                for (;;) {
                    if (c == 1) {
                        found = 1;
                        break;
                    }
                    dl++;
                    c = (s8)(dl->words.w0 >> 24);
                    if (c == 5 || c == 6 || (c >> 4) == 1) {
                        break;
                    }
                }
            }
            state++;
            if (!found) {
                first = 1;
                while (c != 1) {
                    if (c == -3) {
                        nest--;
                    }
                    dl--;
                    c = (s8)(dl->words.w0 >> 24);
                }
            }
            dl--;
        } else {
            /* follow the triangles */
            if (c == -0x21) {
                break;
            }
            if (c == -3) {
                if (++nest > 0) {
                    break;
                }
            } else if (c == 1) {
                vbase = dl->words.w1;
                max = 0;
                if (*out == NULL || vbase < (u32)*out) {
                    *out = (Vtx *)vbase;
                }
            } else if (c == 5 || c == 6 || (c >> 4) == 1) {
                w0 = dl->words.w0;
                w1 = dl->words.w1;
                if (c == 5) {
                    idx[0] = (w0 >> 16) & 0xFF;
                    idx[1] = (w0 >> 8) & 0xFF;
                    idx[2] = w0 & 0xFF;
                    n = 3;
                    for (k = 0; k < n; k++) {
                        idx[k] >>= 1;
                    }
                } else if (c == 6) {
                    idx[0] = (w0 >> 16) & 0xFF;
                    idx[1] = (w0 >> 8) & 0xFF;
                    idx[2] = w0 & 0xFF;
                    idx[3] = (w1 >> 16) & 0xFF;
                    idx[4] = (w1 >> 8) & 0xFF;
                    idx[5] = w1 & 0xFF;
                    n = 6;
                    for (k = 0; k < n; k++) {
                        idx[k] >>= 1;
                    }
                } else {
                    idx[0] = (w1 >> 25) & 0x1F;
                    idx[1] = (w1 >> 20) & 0x1F;
                    idx[2] = (w1 >> 15) & 0x1F;
                    idx[3] = (w1 >> 10) & 0x1F;
                    idx[4] = (w1 >> 5) & 0x1F;
                    idx[5] = w1 & 0x1F;
                    idx[6] = (w0 >> 10) & 0x1F;
                    idx[7] = (w0 >> 5) & 0x1F;
                    idx[8] = w0 & 0x1F;
                    idx[9] = (w0 >> 23) & 0x1F;
                    idx[10] = (w0 >> 18) & 0x1F;
                    idx[11] = ((w1 >> 30) & 3) + (((w0 >> 15) & 7) << 2);
                    n = 12;
                }
                for (k = 0; k < n; k++) {
                    if (max < idx[k]) {
                        max = idx[k];
                    }
                }
                if (nest == 0 && first) {
                    lo = idx[0];
                    for (k = 1; k < n; k++) {
                        if (idx[k] < lo) {
                            lo = idx[k];
                        }
                    }
                    first = 0;
                    *out = (Vtx *)((u8 *)*out + ((lo & 0xFF) << 4));
                }
            }
            dl++;
        }
    }
    return (s32)(vbase + (max + 1) * 16 - (u32)*out) >> 4;
}

/* P181 */
u8 *allocate_memory(s32, s32, s32, s32);
s32 dl_find_texture_vertices(Gfx *dl, s32 key, Vtx **out, s32 skip);
extern s32 g_level_part_dls[];  /* level display lists; was D_800B0E00 */
extern s32 D_800B1214;    /* = g_level_part_dls[1]; was D_800B0E00 */
extern u8 *D_800DA280[];  /* texture scroller records, D_800D9E64 of them */
extern Vtx *D_800B1220[2]; /* the two vertex buffers the scrollers patch */

// tex_scroll_create: P181: creates the (only) texture scroller record (20 bytes, see tex_scroll_update): disabled flag
// +0xC = `off`, angle +0xE = 0, speed +0x10, radius +0x12. For texture key `key` in level display list 0 and key
// D_80091B68 in list 1 (dl_find_texture_vertices) it stores the vertex count (+8 / +9), the first vertex index in vertex
// buffer 0 / 1 (+0xA / +0xB) and a copy of their base texture coordinates (s16 pairs, +0 / +4). NULL when a record
// exists already or the allocation fails (the coordinate arrays are not checked).
/* was func_1510CA2C */
u8 *tex_scroll_create(s32 key, s32 off, s32 speed, s32 radius) {
    u8 *r;
    s16 *base;
    Vtx *v;
    s32 n;
    s32 i;

    if (D_800D9E64 != 0) {
        return NULL;
    }
    r = allocate_memory(20, 1, 0, 0);
    if (r == NULL) {
        return NULL;
    }
    D_800DA280[D_800D9E64++] = r;
    *(s16 **)(r + 0) = NULL;
    *(s16 **)(r + 4) = NULL;
    *(u16 *)(r + 0xE) = 0;
    r[0xC] = off;
    *(u16 *)(r + 0x10) = speed;
    *(u16 *)(r + 0x12) = radius;
    n = dl_find_texture_vertices((Gfx *)g_level_part_dls[0], key, &v, 0);
    if (n != 0) {
        r[8] = n;
        r[0xA] = ((u8 *)v - (u8 *)D_800B1220[0]) >> 4;
        base = (s16 *)allocate_memory(n * 4, 1, 0, 0);
        *(s16 **)(r + 0) = base;
        for (i = 0; i < n; i++) {
            base[i * 2] = v[i].v.tc[0];
            base[i * 2 + 1] = v[i].v.tc[1];
        }
    }
    n = dl_find_texture_vertices((Gfx *)D_800B1214, D_80091B68, &v, 0);
    if (n != 0) {
        r[9] = n;
        r[0xB] = ((u8 *)v - (u8 *)D_800B1220[1]) >> 4;
        base = (s16 *)allocate_memory(n * 4, 1, 0, 0);
        *(s16 **)(r + 4) = base;
        for (i = 0; i < n; i++) {
            base[i * 2] = v[i].v.tc[0];
            base[i * 2 + 1] = v[i].v.tc[1];
        }
    }
    return r;
}

/* P128 */
f32 sinf(f32);
f32 cosf(f32);
extern u8 *D_800DA280[]; /* texture scroller records, D_800D9E64 of them */
extern Vtx *D_800B1220[2]; /* the two vertex buffers the scrollers patch */

// tex_scroll_update: per frame, for every enabled texture scroller record r (r[0xC] == 0): advances its angle
// (u16 +0xE += speed +0x10 * D_800BE9E4), turns it into an offset (radius +0x12 * sin / cos of angle * 2pi / 65536)
// and writes base texture coordinates + offset into the Vtx tc of r[8] vertices of buffer 0 (from vertex r[0xA],
// base pairs at +0) and r[9] vertices of buffer 1 (from vertex r[0xB], base pairs at +4). A record without the
// buffer-0 list uses the offset of the previous record (the asm keeps it in registers; it starts as two
// uninitialised stack halfwords, 0 here). The asm returns nothing; s32 matches the caller's prototype.
/* was func_1510CE28 */
s32 tex_scroll_update(void) {
    u8 *r;
    Vtx *v;
    s16 *base;
    s32 i;
    s32 j;
    s16 dx;
    s16 dy;
    f32 a;
    f32 s;
    f32 c;
    f32 radius;
    u32 angle;

    dx = 0;
    dy = 0;
    for (i = 0; i < D_800D9E64; i++) {
        r = D_800DA280[i];
        if (r[0xC] != 0) {
            continue;
        }
        if (*(s16 **) r != NULL) {
            *(u16 *) (r + 0xE) += *(u16 *) (r + 0x10) * D_800BE9E4;
            angle = *(u16 *) (r + 0xE);
            v = D_800B1220[0] + r[0xA];
            a = angle * 9.58738e-05f; /* 2pi / 65536 */
            s = sinf(a);
            c = cosf(a);
            radius = (u32) * (u16 *) (r + 0x12);
            dx = radius * s;
            dy = radius * c;
            base = *(s16 **) r;
            for (j = 0; j < r[8]; j++) {
                v[j].v.tc[0] = base[j * 2] + dx;
                v[j].v.tc[1] = base[j * 2 + 1] + dy;
            }
        }
        if (*(s16 **) (r + 4) != NULL) {
            v = D_800B1220[1] + r[0xB];
            base = *(s16 **) (r + 4);
            for (j = 0; j < r[9]; j++) {
                v[j].v.tc[0] = base[j * 2] + dx;
                v[j].v.tc[1] = base[j * 2 + 1] + dy;
            }
        }
    }
    return 0;
}
