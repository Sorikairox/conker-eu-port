#include <ultra64.h>
#include "functions.h"
#include "variables.h"

s32 object_sound_position_cb();


#ifdef NON_MATCHING
Gfx *gfx_fill_rect_colour(Gfx *gdl, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 r, u8 g, u8 b);
u8 *view_frame_clear(u8 *);
s32 sky_level_distance(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
extern u8 D_800D9F89, D_800D9F8A, D_800D9F8B, D_800D9F8C, D_800D9F8D, D_800D9F8E, D_800D9F8F, D_800D9F90;
extern u8 D_800D9F91, D_800D9F92, D_800D9F93, D_800D9F99, D_800D9F9A, D_800D9F9B, D_800D9F9C, D_800D9F9D;
extern u8 D_800D9F9E, D_800D9F9F, D_800D9FA0, D_800D9FA1, D_800D9FA2, D_800D9FA3;
extern u8 D_800BEA55;
extern s32 D_800BE624;
extern s16 D_80083336;
/* camera/overlay draw callbacks, indexed by D_800B0DF0->unk8 */
extern Gfx *(*D_80089578[])(Gfx *, f32, f32, f32, f32, f32, f32, s32);

/* was func_15110420 */
Gfx *view_background_draw(Gfx *gdl, s32 arg1) {
    u8 *view;
    struct108 *player;
    f32 yaw;
    f32 pitch;
    f32 roll;
    f32 x;
    f32 y;
    f32 z;
    s32 handle;

    D_800D9F88[0] = 0;
    D_800D9F89 = 0;
    D_800D9F8A = 0;
    D_800D9F98[0] = 0;
    D_800D9F99 = 0;
    D_800D9F9A = 0;
    D_800D9F8B = 0;
    D_800D9F8C = 0;
    D_800D9F8D = 0;
    D_800D9F9B = 0;
    D_800D9F9C = 0;
    D_800D9F9D = 0;
    D_800D9F8E = 0;
    D_800D9F8F = 0;
    D_800D9F90 = 0;
    D_800D9F9E = 0;
    D_800D9F9F = 0;
    D_800D9FA0 = 0;
    D_800D9F91 = 0;
    D_800D9F92 = 0;
    D_800D9F93 = 0;
    D_800D9FA1 = 0;
    D_800D9FA2 = 0;
    D_800D9FA3 = 0;

    gdl->words.w0 = 0xD9FFF9FF;
    gdl->words.w1 = 0;
    gdl = (Gfx *)view_frame_clear((u8 *)(gdl + 1));
    gDPPipeSync(gdl++);
    if (D_800BEA55 != 0) {
        gdl = gfx_fill_rect_colour(gdl, 0, 0, D_800BE620, D_800BE624, 0, 0, 0);
    }
    if ((D_800C35EA == 1) && (D_800C3681 != 0)) {
        return gdl;
    }

    view = D_800DD210 + D_80082FA4 * 0x18;
    player = &D_800DBFF0[D_80082FA4];
    /* wrap the three angles (degrees): yaw and roll into [-180, 180), pitch into [0, 360) */
    yaw = 360.0f - (*(f32 *)(view + 0xC) + player->unk388);
    while (yaw < -180.0f) {
        yaw += 360.0f;
    }
    while (yaw >= 180.0f) {
        yaw -= 360.0f;
    }
    pitch = 360.0f - (*(f32 *)(view + 0x10) + player->unk380);
    while (pitch < 0.0f) {
        pitch += 360.0f;
    }
    while (pitch >= 360.0f) {
        pitch -= 360.0f;
    }
    roll = *(f32 *)(view + 0x14) + *(f32 *)&player->pad5EC;
    while (roll < -180.0f) {
        roll += 360.0f;
    }
    while (roll >= 180.0f) {
        roll -= 360.0f;
    }
    x = player->unk2F8;
    y = player->unk2FC;
    z = player->unk300;

    if (D_800C3682 != 0) {
        u8 *cam = (u8 *)D_800BE628 + D_80082FA4 * 0x180;
        return gfx_fill_rect_colour(gdl, (s32)*(f32 *)(cam + 0x2C), (s32)*(f32 *)(cam + 0x24),
                             (s32)(*(f32 *)(cam + 0x30) - 1.0f), (s32)*(f32 *)(cam + 0x28), 0x16, 0x1C, 0x1B);
    }

    handle = sky_level_distance(x, y, z, yaw);
    if (handle != 0) {
        gdl = D_80089578[D_800B0DF0->unk8](gdl, x, y, z, yaw, pitch, roll, handle);
    }
    gdl = (Gfx *)render_set_scissor((s32)gdl, D_80083336, 0, 0, 0, 0);
    gdl->words.w1 = 0x400;
    gdl->words.w0 = 0xD9FFFFFF;
    return gdl + 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/view_background_draw.s")
#endif
void mtxf_mul(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
/* was func_1511084C */
void matrix_rotate_ypr(f32 (*arg0)[4], f32 arg1, f32 arg2, f32 arg3) {
    f32 sp28[4][4];
    mtxf_rotate_xyz_deg(arg0, 0.0f, arg2, 0.0f);
    mtxf_rotate_xyz_deg(sp28, arg1, 0.0f, 0.0f);
    mtxf_mul(arg0, sp28, arg0);
    mtxf_rotate_xyz_deg(sp28, 0.0f, 0.0f, arg3);
    mtxf_mul(arg0, sp28, arg0);
}

void mtxf_mul(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
void matrix_rotate_ypr(f32 (*)[4], f32, f32, f32);
/* was func_151108E0 */
void camera_view_rotation_matrix(s32 arg0, f32 (*arg1)[4], f32 arg2, f32 arg3, f32 arg4) {
    matrix_rotate_ypr(arg1, arg2, arg3, arg4);
    mtxf_mul(arg1, (f32 (*)[4])((u8 *)D_800BE628 + arg0 * 0x180 + 0xBC), arg1);
}

#ifdef NON_MATCHING
Gfx *render_fill_rect_clamped(Gfx *gdl, s32 ulx, s32 uly, s32 lrx, s32 lry);
extern u8 D_800DC2D8[];

/* Default camera callback (D_80089578[0], called by view_background_draw): clear the current player's viewport
 * (D_800BE628[D_80082FA4] +0x24..0x30) to the level colour D_800DC2D8 via gfx_fill_rect_colour; in split screen, from
 * player 0 only, draw the black divider bars (horizontal across the middle; vertical too with 3-4 players). The
 * position / angle arguments are unused. */
/* was func_15110948 */
Gfx *view_clear_level_colour(Gfx *gdl, f32 x, f32 y, f32 z, f32 yaw, f32 pitch, f32 roll, s32 handle) {
    u8 *cam = (u8 *)D_800BE628 + D_80082FA4 * 0x180;
    s32 h;

    gdl = gfx_fill_rect_colour(gdl, (s32)*(f32 *)(cam + 0x2C), (s32)*(f32 *)(cam + 0x24), (s32)(*(f32 *)(cam + 0x30) - 1.0f),
                        (s32)*(f32 *)(cam + 0x28), D_800DC2D8[0], D_800DC2D8[1], D_800DC2D8[2]);
    if (D_80082FA0 == 0 || D_80082FA4 != 0) {
        return gdl;
    }
    gdl->words.w0 = 0xE7000000;
    gdl->words.w1 = 0;
    gdl = (Gfx *)render_set_scissor((s32)(gdl + 1), 0xFF, 0, 0, 0, 0);
    gdl->words.w0 = 0xF7000000;
    gdl->words.w1 = 0x10001;
    h = D_800BE624 >> 1;
    gdl = render_fill_rect_clamped(gdl + 1, 0, h - 6, D_800BE620, h + 6);
    if (D_80082FA0 != 1) {
        h = D_800BE620 >> 1;
        gdl = render_fill_rect_clamped(gdl, h - 1, 0, h + 1, D_800BE624);
    }
    return gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/view_clear_level_colour.s")
#endif
/* was func_15110AC4 */
Gfx *gfx_fill_rect_colour(Gfx *gdl, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 r, u8 g, u8 b) {
    gDPPipeSync(gdl++);
    gDPSetOtherMode(gdl++, 0x302C0F, 4);
    gdl = render_set_color_image(gdl);
    gDPSetFillColor(gdl++, (GPACK_RGBA5551(r, g, b, 1) << 16) | GPACK_RGBA5551(r, g, b, 1));
    return render_fill_rect_clamped(gdl, arg1, arg2, arg3, arg4);
}

extern u8 D_800DC2D8[];
#ifdef NON_MATCHING
// view_border_clear: camera callback D_80089578[3] (dispatcher view_background_draw passes 8 arguments; only gdl is used).
// On levels 0x1B / 0x1E, and on 0x31 while D_800DBFF0's record +0x3D4 has byte +0x78 == 3, fills the rectangle
// (2, 0)..(D_800BE620 - 2, D_800BE624) with the level colour D_800DC2D8 (gfx_fill_rect_colour); otherwise draws nothing.
// P244: NM signature = the dispatcher's type (it took 4 parameters: a wasm call_indirect signature mismatch).
/* was func_15110B80 */
Gfx *view_border_clear(Gfx *gdl, f32 x, f32 y, f32 z, f32 yaw, f32 pitch, f32 roll, s32 handle) {
    if (D_800BE9F0 == 0x1B || D_800BE9F0 == 0x1E
        || (D_800BE9F0 == 0x31 && *(u8 *)((u8 *)D_800DBFF0->unk3D4 + 0x78) == 3)) {
        gdl = gfx_fill_rect_colour(gdl, 2, 0, D_800BE620 - 2, D_800BE624, D_800DC2D8[0], D_800DC2D8[1], D_800DC2D8[2]);
    }
    return gdl;
}
#else
Gfx *view_border_clear(Gfx *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if ((D_800BE9F0 == 0x1B) || (D_800BE9F0 == 0x1E) || ((D_800BE9F0 == 0x31) && (*(u8 *)((u8 *)D_800DBFF0->unk3D4 + 0x78) == 3))) {
        arg0 = gfx_fill_rect_colour(arg0, 2, 0, D_800BE620 - 2, D_800BE624, D_800DC2D8[0], D_800DC2D8[1], D_800DC2D8[2]);
    }
    return arg0;
}
#endif

#ifdef NON_MATCHING
extern u8 D_800BEEE2;

/* was func_15110C28 */
u8 *view_frame_clear(u8 *arg0) {
    s32 temp_t5;
    s32 temp_t7;
    u8 *temp_a0;
    u8 *temp_a0_2;
    u8 *temp_a0_3;
    u8 *temp_a0_4;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 *var_a0;

    var_a0 = arg0;
    if (D_80082FA4 == 0) {
        temp_a0 = var_a0 + 8;
        (*(s32 *)((u8 *)var_a0 + 0)) = 0xE7000000;
        (*(s32 *)((u8 *)var_a0 + 4)) = 0;
        (*(s32 *)((u8 *)temp_a0 + 4)) = 4;
        (*(s32 *)((u8 *)temp_a0 + 0)) = 0xEF302C0F;
        temp_a0_2 = temp_a0 + 8;
        (*(s32 *)((u8 *)temp_a0_2 + 0)) = 0xFCFFFFFF;
        (*(s32 *)((u8 *)temp_a0_2 + 4)) = 0xFFFE793C;
        temp_a0_3 = temp_a0_2 + 8;
        (*(s32 *)((u8 *)temp_a0_3 + 0)) = (s32) (((D_800BE620 - 1) & 0xFFF) | 0xFF100000);
        temp_a0_4 = temp_a0_3 + 8;
        (*(s32 *)((u8 *)temp_a0_3 + 4)) = (s32) D_800BEDE4;
        (*(s32 *)((u8 *)temp_a0_4 + 0)) = 0xF7000000;
        (*(s32 *)((u8 *)temp_a0_4 + 4)) = 0xFFFCFFFC;
        temp_v0 = render_set_scissor((s32) (temp_a0_4 + 8), 0xFF, 0, 0, 0, 0);
        (*(s32 *)((u8 *)temp_v0 + 4)) = 0x8000;
        (*(s32 *)((u8 *)temp_v0 + 0)) = (s32) ((((D_800BE620 - 2) & 0x3FF) << 0xE) | 0xF6000000 | ((D_800BE624 & 0x3FF) * 4));
        (*(s32 *)((u8 *)temp_v0 + 8)) = 0xE7000000;
        (*(s32 *)((u8 *)temp_v0 + 0xC)) = 0;
        temp_v0_2 = render_set_color_image(temp_v0 + 0x10);
        var_a0 = temp_v0_2;
        if (D_80082FA0 != 0) {
            (*(s32 *)((u8 *)temp_v0_2 + 0)) = 0xE7000000;
            (*(s32 *)((u8 *)temp_v0_2 + 4)) = 0;
            temp_v0_3 = render_set_scissor((s32) (var_a0 + 8), 0xFF, 0, 0, 0, 0);
            (*(s32 *)((u8 *)temp_v0_3 + 0)) = 0xF7000000;
            (*(s32 *)((u8 *)temp_v0_3 + 4)) = 0x10001;
            temp_t5 = (s32) D_800BE624 >> 1;
            var_a0 = render_fill_rect_clamped(temp_v0_3 + 8, 0, temp_t5 - 6, D_800BE620, temp_t5 + 6);
            if (D_80082FA0 != 1) {
                temp_t7 = (s32) D_800BE620 >> 1;
                var_a0 = render_fill_rect_clamped(var_a0, temp_t7 - 1, 0, temp_t7 + 1, D_800BE624);
            }
            if (D_800BEEE2 != 0) {
                var_a0 = render_fill_rect_clamped(var_a0, 0, 0, D_800BE620, D_800BE624);
            }
        }
    }
    return var_a0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/view_frame_clear.s")
#endif
#ifdef NON_MATCHING
/* was func_15110E44 */
s32 sky_level_distance(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    struct {
        s32 u1C;
    } sp;
    s32 sp18;
    s32 var_a2;
    s32 var_v1;

    switch (D_800BE9F0) {
    case 0x6:
    case 0x3B:
        var_v1 = (s32) (((arg1 * 40.0f) / 1800.0f) + 200.0f);
        break;
    case 0x14:
        var_v1 = (s32) (((arg1 * 22.0f) / 1800.0f) + 113.0f);
        break;
    case 0xC:
        var_v1 = (s32) (((arg1 * 90.0f) / 1800.0f) + 150.0f);
        break;
    case 0x0:
        if ((arg1 < 1600.0f) && (arg3 > 26.0f)) {
            var_v1 = 0;
        } else {
            var_v1 = (s32) (((arg1 * 51.0f) / 1800.0f) + 134.0f);
        }
        break;
    case 0x7:
        if (arg2 < -1100.0f) {
        default:
block_46:
            var_v1 = 0x140;
        } else if (arg3 > 20.0f) {
            var_v1 = 0;
        } else {
            var_v1 = (s32) (((arg1 * 54.0f) / 1800.0f) + 167.0f);
        }
        break;
    case 0x41:
        var_v1 = 0x89;
        break;
    case 0x3C:
        if ((arg2 < -1650.0f) || ((arg0 > 3495.0f) && (arg0 < 4578.0f) && (arg2 < 2960.0f))) {
            goto block_46;
        }
        var_v1 = 0;
        break;
    case 0xB:
        sp18 = 0;
        if (trigger_test_player(0, 0x18) == 1) {
            var_a2 = sp18;
            if (trigger_test_player(0, 0x2E) == 0) {
                var_v1 = sp.u1C;
                if (arg3 > 0.0f) {
                    var_v1 = 0;
                } else {
                    var_a2 = 1;
                }
            } else {
                var_v1 = 0;
            }
        } else {
            var_a2 = 1;
            var_v1 = sp.u1C;
        }
        if (var_a2 != 0) {
            if (arg1 < 1218.0f) {
                var_v1 = 0x1E;
            } else {
                var_v1 = 0x140;
                if (arg1 < 2000.0f) {
                    var_v1 = 0xA0;
                }
            }
        }
        break;
    case 0x13:
        if ((D_800C35EA == 1) && ((D_800C3A08 == 2) || (D_800C3A08 == 1))) {
            goto block_46;
        }
        if (arg1 < 1900.0f) {
            var_v1 = 0x10E;
        } else {
            goto block_46;
        }
        break;
    case 0x1C:
        var_v1 = (s32) (((arg1 * 34.0f) / 1800.0f) + 130.0f);
        break;
    case 0xE:
        var_v1 = 0xA5;
        break;
    case 0x39:
        var_v1 = 0x54;
        break;
    case 0x2D:
        var_v1 = (s32) (((arg1 * 53.0f) / 1800.0f) + 139.0f);
        break;
    case 0x30:
        var_v1 = (s32) (((arg1 * 53.0f) / 1800.0f) + 139.0f);
        break;
    }
    return var_v1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/sky_level_distance.s")
#endif
#ifdef NON_MATCHING
/* P188: one face of the sky box (D_800A3170, 16 bytes): texture size in texels and two opposite corners; the axis
 * the face is perpendicular to is the one whose coordinate the corners share */
typedef struct {
    u16 w, h;
    s16 a[3];
    s16 b[3];
} SkyFace;
/* P188: a texture load the vertex builder sky_box_face_build queued (filled through its pointer argument) */
typedef struct {
    s32 addr; /* texture (palette at addr + tlut_offset[fmt]) */
    s32 fmt;  /* 0 = 8-bit CI (256 colours), 1 = 4-bit CI (16 colours) */
} SkyLoad;
extern SkyFace D_800A3170[];
extern s32 D_800DC2B8[];
extern s32 D_800DC2E0;
/* (one line: tools/port/protocheck.py reads single-line prototypes) */
Gfx *sky_box_face_build(Gfx *gdl, s32 *vtx, s32 tex, s32 arg3, s32 arg4, u32 w, u32 h, u32 step_s, u32 step_t, f32 x, f32 y, f32 z, s32 axis, f32 (*view)[4], s32 dist, s32 *count, s32 *first, SkyLoad *loads, s32 *last_fmt, u8 *arg19, u8 *arg20, s16 *tlut_offset, u8 *tlut_count, u8 *tile, s32 face);
#endif
#ifdef NON_MATCHING
/* P203 */
s32 view_sphere_depth(f32 *m, f32 x, f32 y, f32 z, f32 r, f32 ry, f32 far);
s32 texture_cache_lookup(s32, s32 *, s32, s32);
extern f32 D_800A32F0; /* sky tile view-test far distance */
extern u8 D_800DC2DB;  /* 1 on level 0x3C: load every visible tile's texture, even beyond the distance limit */
extern u8 D_800DC2DC;  /* bit 0 of D_800D2E4C->unk14: sky 1 face 2 shows the replacement tiles 0x1675.. */
extern s32 D_800DC2B0; /* sky asset: one format byte per tile (0 = CI8, 1 = CI4) */

// sky_box_face_build: P203: builds one face of the sky box (sky_box_draw) as a grid of textured quads in the
// frame's vertex buffer and queues their texture loads. The face lies in the plane `axis` ('x' / 'y' / 'z') through
// the corner (x, y, z) * 8 and spans w x h texels in tiles of step_s x step_t texels (8 world units per texel); rows
// run down from the corner's second coordinate, columns along its first. Per tile: the view test view_sphere_depth
// (centre of the quad, half sizes step * 8, far D_800A32F0) drops tiles outside the view; for the side faces
// (face < 4) only the first `dist` rows are kept with dist scaled from 0..320 to 0..rows (rounded up); the texture
// (tex + col * rows + row, or on sky 1 face 2 with D_800DC2DC the replacement 0x1675 + col * 3 + row - 10 for
// rows 4..6 / columns 2..3) is fetched with texture_cache_lookup(id, NULL, 3, 0) and queued in loads[] with the tile's
// format byte from the sky asset D_800DC2B0. On the 'y' faces the first and last columns grow by 3 units on each
// side (hides the seams). Every 16 vertices (4 quads) it emits one G_VTX and per quad the block / palette loads,
// a tile switch when the format changes (*last_fmt) and two triangles; *count / *first keep the partial batch for
// the caller, which flushes the rest. arg3 / arg4 are unused. Returns the advanced display list.
// Port: for an upper-case axis the asm leaves the start coordinates unset (garbage); the C starts them at 0.
/* was func_1511127C */
Gfx *sky_box_face_build(Gfx *gdl, s32 *vtx, s32 tex, s32 arg3, s32 arg4, u32 w, u32 h, u32 step_s, u32 step_t, f32 x, f32 y, f32 z, s32 axis, f32 (*view)[4], s32 dist, s32 *count, s32 *first, SkyLoad *loads, s32 *last_fmt, u8 *arg19, u8 *arg20, s16 *tlut_offset, u8 *tlut_count, u8 *tile, s32 face) {
    s32 q[4][3]; /* the quad's corners in vertex order */
    s32 vbuf, cur_first, n, fmt_last;
    s32 fx, fy, fz;
    s32 u_start, v_start, u, u2, v, v2;
    s32 du, dv, row, col, rows, cols, id, addr, k, lrs, fmt;
    u32 spos, tpos;
    u16 s_hi, t_hi;
    s16 *vp;
    u8 ax;

    x *= 8.0f;
    y *= 8.0f;
    z *= 8.0f;
    vbuf = *vtx;
    cur_first = *first;
    n = *count;
    fmt_last = *last_fmt;
    ax = axis;
    if (ax == 'x') {
        u_start = (s32) z;
        v_start = (s32) y;
    } else if (ax == 'y') {
        u_start = (s32) x;
        v_start = (s32) z;
    } else if (ax == 'z') {
        u_start = (s32) x;
        v_start = (s32) y;
    } else {
        u_start = 0;
        v_start = 0;
    }
    row = 0;
    if (face < 4) {
        if (dist > 320) {
            dist = 320;
        }
        dist = (s32) (dist * (h / step_t) + 319) / 320;
    } else {
        dist = 0x7FFF;
    }
    dv = step_t * 8;
    v = v_start - dv;
    for (tpos = 0; tpos < h; tpos += step_t, row++, v -= dv) {
        col = 0;
        u = u_start;
        du = step_s * 8;
        for (spos = 0; spos < w; spos += step_s, col++, u = u2) {
            u2 = u + du;
            v2 = v + dv;
            switch (ax) {
                case 'X':
                case 'x':
                    fx = (s32) x;
                    q[0][0] = fx, q[0][1] = v, q[0][2] = u;
                    q[1][0] = fx, q[1][1] = v, q[1][2] = u2;
                    q[2][0] = fx, q[2][1] = v2, q[2][2] = u2;
                    q[3][0] = fx, q[3][1] = v2, q[3][2] = u;
                    break;
                case 'Y':
                case 'y':
                    fy = (s32) y;
                    q[0][0] = u, q[0][1] = fy, q[0][2] = v;
                    q[1][0] = u2, q[1][1] = fy, q[1][2] = v;
                    q[2][0] = u2, q[2][1] = fy, q[2][2] = v2;
                    q[3][0] = u, q[3][1] = fy, q[3][2] = v2;
                    break;
                case 'Z':
                case 'z':
                    fz = (s32) z;
                    q[0][0] = u, q[0][1] = v, q[0][2] = fz;
                    q[1][0] = u2, q[1][1] = v, q[1][2] = fz;
                    q[2][0] = u2, q[2][1] = v2, q[2][2] = fz;
                    q[3][0] = u, q[3][1] = v2, q[3][2] = fz;
                    break;
            }
            /* view test of the quad's centre (corners 0 and 2 are opposite) */
            if (view_sphere_depth((f32 *) view, (f32) ((q[0][0] + q[2][0]) >> 1), (f32) ((q[0][1] + q[2][1]) >> 1),
                              (f32) ((q[0][2] + q[2][2]) >> 1), (f32) du, (f32) dv, D_800A32F0) == 0) {
                continue;
            }
            if (D_800DC2DB == 0 && row >= dist) {
                continue;
            }
            rows = h / step_t;
            id = tex + col * rows + row;
            if (D_800DC2DC != 0 && ((u8 *) D_800B0DF0)[9] == 1 && face == 2 && row >= 4 && row < 7 && col >= 2 &&
                col < 4) {
                id = 0x1675 + (col * 3 + row - 10);
            }
            addr = texture_cache_lookup(id, NULL, 3, 0);
            if (D_800DC2DB != 0 && row >= dist) {
                continue;
            }
            t_hi = (s32) (((f32) step_t + 0.5f) * 32.0f);
            s_hi = (s32) (((f32) step_s + 0.5f) * 32.0f);
            vp = (s16 *) (vbuf + (cur_first + n) * 16);
            cols = w / step_s;
            if (ax == 'y' && (spos == 0 || spos == w - step_s)) {
                q[0][0] -= 3;
                q[3][0] -= 3;
                q[2][0] += 3;
                q[1][0] += 3;
                q[0][2] -= 3;
                q[2][2] += 3;
                q[1][2] -= 3;
                q[3][2] += 3;
            }
            /* x, y, z, flag 0, s, t (10.5 fixed); the colour words stay */
            vp[0] = q[0][0], vp[1] = q[0][1], vp[2] = q[0][2], vp[3] = 0, vp[4] = 16, vp[5] = 16;
            vp[8] = q[1][0], vp[9] = q[1][1], vp[10] = q[1][2], vp[11] = 0, vp[12] = s_hi, vp[13] = 16;
            vp[16] = q[2][0], vp[17] = q[2][1], vp[18] = q[2][2], vp[19] = 0, vp[20] = s_hi, vp[21] = t_hi;
            vp[24] = q[3][0], vp[25] = q[3][1], vp[26] = q[3][2], vp[27] = 0, vp[28] = 16, vp[29] = t_hi;
            loads[n >> 2].addr = addr;
            loads[n >> 2].fmt = ((u8 *) D_800DC2B0)[col * rows + row + face * cols * rows];
            n += 4;
            if (n != 16) {
                continue;
            }
            /* a full batch: one G_VTX for the 16 vertices, then per quad its texture and two triangles */
            gdl->words.w0 = 0x01010020;
            gdl->words.w1 = vbuf + cur_first * 16;
            gdl++;
            for (k = 0; k < 16; k += 4) {
                fmt = loads[k >> 2].fmt;
                gdl->words.w0 = 0xE7000000;
                gdl->words.w1 = 0;
                gdl++;
                gdl->words.w0 = 0xFD100000;
                gdl->words.w1 = loads[k >> 2].addr;
                gdl++;
                lrs = ((arg19[fmt] + 0x800) >> arg20[fmt]) - 1;
                if (lrs >= 0x7FF) {
                    lrs = 0x7FF;
                }
                gdl->words.w0 = 0xF3000000;
                gdl->words.w1 = 0x07000000 | ((lrs & 0xFFF) << 12);
                gdl++;
                gdl->words.w0 = 0xFD100000;
                gdl->words.w1 = tlut_offset[fmt] + loads[k >> 2].addr;
                gdl++;
                gdl->words.w0 = 0xE6000000;
                gdl->words.w1 = 0;
                gdl++;
                gdl->words.w0 = 0xF0000000;
                gdl->words.w1 = 0x06000000 | (tlut_count[fmt] << 14);
                gdl++;
                if (fmt != fmt_last) {
                    fmt_last = fmt;
                    gdl->words.w0 = 0xD7000002 | ((tile[fmt] & 7) << 8);
                    gdl->words.w1 = 0xFFFFFFFF;
                    gdl++;
                }
                /* (k + 2, k, k + 1) and (k + 3, k, k + 2); G_TRI1 indices are vertex * 2 */
                gdl->words.w0 = 0x05000000 | (((k * 2 + 4) & 0xFF) << 16) | (((k * 2) & 0xFF) << 8) | ((k * 2 + 2) & 0xFF);
                gdl->words.w1 = 0;
                gdl++;
                gdl->words.w0 = 0x05000000 | (((k * 2 + 6) & 0xFF) << 16) | (((k * 2) & 0xFF) << 8) | ((k * 2 + 4) & 0xFF);
                gdl->words.w1 = 0;
                gdl++;
            }
            n = 0;
            cur_first += 16;
        }
    }
    *count = n;
    *first = cur_first;
    *vtx = vbuf;
    return gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/sky_box_face_build.s")
#endif

#ifdef NON_MATCHING
/* P133 */
void heap_free(s32);
void texture_unref_age3(s32);
void star_field_generate(void);
s32 asset_load_ptr(s32 *, s32, ...);
extern s32 *D_8008955C[];

/*
 * overlay_mode_set: switches the camera overlay (D_800B0DF0: +8 state, +9 overlay id). mode 1: state 1, frees the
 * overlay asset D_800DC2B0 (when loaded) and calls star_field_generate. Other modes, only when the id changes and the
 * state is 4: releases the 0x168 textures of the current overlay (D_8008955C[id], when D_80038080 is set), frees
 * D_800DC2B0, stores the new id and loads its asset (type 0xD) into D_800DC2B0 with asset_load_ptr.
 */
/* was func_15111CAC */
void overlay_mode_set(s32 mode) {
    s32 i;

    if (mode == 1) {
        D_800B0DF0->unk8 = 1;
        if (D_800DC2B0 != 0) {
            heap_free(D_800DC2B0);
        }
        star_field_generate();
        return;
    }
    if (mode == D_800B0DF0->unk9 || D_800B0DF0->unk8 != 4) {
        return;
    }
    if (D_80038080 != 0) {
        for (i = 0; i < 0x168; i++) {
            texture_unref_age3(*D_8008955C[D_800B0DF0->unk9] + i);
        }
    }
    heap_free(D_800DC2B0);
    D_800B0DF0->unk9 = mode;
    asset_load_ptr(&D_800DC2B0, 2, 0xD, D_800B0DF0->unk9);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/overlay_mode_set.s")
#endif

#ifdef NON_MATCHING
/* P136 */
void *allocate_memory(s32, s32, s32, s32);
s32 random_int(void); /* random */
f32 fast_sinf(f32);  /* sinf */
f32 fast_cosf(f32);  /* cosf */
extern f32 D_800A32F4; /* latitude spread scale */
extern f32 D_800A32F8; /* longitude: centidegrees -> radians */
extern f32 D_800A32FC; /* latitude: degrees -> radians */

/*
 * star_field_generate: allocates the overlay buffer D_800DC2B0 (8000 records of 8 bytes) and fills it with random
 * stars on a sphere of radius 256: longitude (rand % 36000) * D_800A32F8, latitude 89 - sqrt(t) or sqrt(-t) - 89
 * with t = ((rand % 1584400) - 792100) * D_800A32F4 (denser near the horizon). y = (s32) (sin(lat) * 256),
 * r = sqrt(0x10000 - y * y), x = (s32) (sin(lon) * r), z = (s32) (cos(lon) * r); byte +7 = 64 + rand % 191
 * (brightness), byte +6 = rand % 5.
 * Rare quirk kept: each coordinate is converted to float and the record gets the float's upper halfword (the asm
 * stores the value with swc1 and reads it back with lhu), not the integer; STAR_FLOAT_HI16 does that endian-neutrally.
 */
/* the upper halfword of (f32) v, endian-neutral (c: the function's float/word union) */
#define STAR_FLOAT_HI16(c, v) ((c).f = (f32) (v), (u16) ((c).u >> 16))

/* was func_15111DD8 */
void star_field_generate(void) {
    u8 *star;
    s32 i;
    f32 lon, lat, t, r;
    s32 y;
    union {
        f32 f;
        u32 u;
    } c;

    star = allocate_memory(0xFA00, 1, 0, 0);
    D_800DC2B0 = (s32) star;
    for (i = 0; i < 8000; i++, star += 8) {
        lon = (f32) ((u32) random_int() % 36000U) * D_800A32F8;
        t = (f32) (s32) (((u32) random_int() % 1584400U) - 792100) * D_800A32F4;
        if (t >= 0.0f) {
            lat = 89.0f - sqrtf(t);
        } else {
            lat = sqrtf(-t) + -89.0f;
        }
        y = (s32) (fast_sinf(lat * D_800A32FC) * 256.0f);
        *(u16 *) (star + 2) = STAR_FLOAT_HI16(c, y);
        r = sqrtf((f32) (s32) (0x10000 - (u32) (y * y)));
        *(u16 *) (star + 0) = STAR_FLOAT_HI16(c, (s32) (fast_sinf(lon) * r));
        *(u16 *) (star + 4) = STAR_FLOAT_HI16(c, (s32) (fast_cosf(lon) * r));
        star[7] = (u32) random_int() % 191U + 0x40;
        star[6] = (u32) random_int() % 5U;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/star_field_generate.s")
#endif

#ifdef NON_MATCHING
/* P188 */

/*
 * sky_box_draw: camera callback (D_80089578[], same signature as view_clear_level_colour) that draws the textured sky box of
 * the current player D_80082FA4. The position arguments are unused. Steps:
 *  - texture on, render_set_scissor (D_80083336) / render_set_color_image; on level 60 (and on level 19 in mode D_800C35EA == 1
 *    with D_800C3A08 == 1 or 2) the viewport is first cleared to black through gfx_fill_rect_colour (the camera record
 *    D_800BE628[p] +0x24..0x30, as view_clear_level_colour);
 *  - on level 65 the pitch is turned by -119 degrees (wrapped into [0, 360));
 *  - pipe sync, combiner: plain texture when the sky colour (D_800B0DF0 +5..7) is white, else texture * env colour;
 *    other modes, the 4-bit / 8-bit tile descriptors;
 *  - view matrix: matrix_rotate_ypr(yaw, pitch, roll) times the camera matrix (+0xBC) into the frame's Mtx
 *    D_800DC2E0[p * 2 + D_800BE9C0], D_80089810 as the projection, perspective normalisation (+0xB8);
 *  - faces `first`..`last - 1` (0..4; 4..4 on level 25; 0..5 on level 12): faces 0..3 (the sides, every 90 degrees
 *    of pitch) only when the pitch is within the field of view (95 degrees in mode D_80082FA0 == 1, else 80) of the
 *    face, faces 4 / 5 (down / up) by the yaw, face 5 only from distance `dist` >= 300. sky_box_face_build builds each
 *    face's quads into the frame's vertex buffer D_800DC2B8[p * 2 + D_800BE9C0] and queues the texture loads (the
 *    face's textures D_8008955C[sky +9][face, 0 for face 5]);
 *  - one G_VTX for all `count` vertices, then per quad (4 vertices): load its texture block and palette (tile
 *    changes only when the format does) and two triangles.
 */
/* was func_15112074 */
Gfx *sky_box_draw(Gfx *gdl, f32 x, f32 y, f32 z, f32 yaw, f32 pitch, f32 roll, s32 dist) {
    u8 tile[2];        /* {0, 1} */
    u8 tlut_count[2];  /* {0xFF, 0x0F} */
    s16 tlut_offset[2]; /* {0x800, 0x400} */
    u8 arg20[2];       /* {1, 2} */
    u8 arg19[2];       /* {1, 4} */
    f32 fov;
    u8 col[3];
    s32 last_fmt;
    SkyLoad loads[4];
    s32 first_vtx;
    s32 count;
    s32 vtx;
    f32 view[4][4];
    f32 m[4][4];
    s32 *texs;
    s32 i, last, axis, face, k, fmt;
    SkyFace *f;
    u8 *cam;
    u8 *sky;

    /* P188: the asm copies these from .data initialisers (D_8008958C..9C); set element-wise here because an
     * aggregate initialiser would put a .data section in the NM object, which the linker script discards */
    tile[0] = 0;
    tile[1] = 1;
    tlut_count[0] = 0xFF;
    tlut_count[1] = 0x0F;
    tlut_offset[0] = 0x800;
    tlut_offset[1] = 0x400;
    arg20[0] = 1;
    arg20[1] = 2;
    arg19[0] = 1;
    arg19[1] = 4;
    gdl->words.w0 = 0xD7000002;
    gdl->words.w1 = 0xFFFFFFFF;
    gdl = (Gfx *) render_set_scissor((s32) (gdl + 1), D_80083336, 0, 0, 0, 0);
    gdl = (Gfx *) render_set_color_image(gdl);
    if (D_80082FA0 == 1) {
        fov = 95.0f;
    } else {
        fov = 80.0f;
    }
    if (D_800BE9F0 == 65) {
        pitch -= 119.0f;
        if (pitch < 0.0f) {
            pitch += 360.0f;
        }
    } else if (D_800BE9F0 == 60 ||
               (D_800BE9F0 == 19 && D_800C35EA == 1 && (D_800C3A08 == 2 || D_800C3A08 == 1))) {
        cam = (u8 *) D_800BE628 + D_80082FA4 * 0x180;
        gdl = gfx_fill_rect_colour(gdl, (s32) *(f32 *) (cam + 0x2C), (s32) *(f32 *) (cam + 0x24),
                            (s32) (*(f32 *) (cam + 0x30) - 1.0f), (s32) *(f32 *) (cam + 0x28), 0, 0, 0);
    }
    sky = (u8 *) D_800B0DF0;
    col[0] = sky[5];
    col[1] = sky[6];
    col[2] = sky[7];
    gdl->words.w0 = 0xE7000000;
    gdl->words.w1 = 0;
    gdl++;
    if (col[2] + col[0] + col[1] == 765) {
        gdl->words.w0 = 0xFCFFFFFF;
        gdl->words.w1 = 0xFFFCF279;
        gdl++;
    } else {
        gdl->words.w0 = 0xFB000000;
        gdl->words.w1 = (col[0] << 24) | (col[1] << 16) | (col[2] << 8) | 0xFF;
        gdl++;
        gdl->words.w0 = 0xFC129A25;
        gdl->words.w1 = 0xFF37FFFF;
        gdl++;
    }
    gdl->words.w0 = 0xEF08AC0F;
    gdl->words.w1 = 0x0F0A4004;
    gdl++;
    gdl->words.w0 = 0xF5500000;
    gdl->words.w1 = 0x07000000;
    gdl++;
    gdl->words.w0 = 0xF5481000;
    gdl->words.w1 = 0x00080200;
    gdl++;
    gdl->words.w0 = 0xF2000000;
    gdl->words.w1 = 0x000F407C;
    gdl++;
    gdl->words.w0 = 0xF5400800;
    gdl->words.w1 = 0x01080200;
    gdl++;
    gdl->words.w0 = 0xF2000000;
    gdl->words.w1 = 0x010F407C;
    gdl++;
    gdl->words.w0 = 0xF5000100;
    gdl->words.w1 = 0x06000000;
    gdl++;
    matrix_rotate_ypr(view, yaw, pitch, roll);
    mtxf_mul(view, (f32 (*)[4]) ((u8 *) D_800BE628 + D_80082FA4 * 0x180 + 0xBC), m);
    guMtxF2L(m, (Mtx *) D_800DC2E0 + (D_80082FA4 * 2 + D_800BE9C0));
    gdl->words.w0 = 0xDA380007;
    gdl->words.w1 = (u32) ((Mtx *) D_800DC2E0 + (D_80082FA4 * 2 + D_800BE9C0));
    gdl++;
    gdl->words.w0 = 0xDA380003;
    gdl->words.w1 = (u32) D_80089810;
    gdl++;
    gdl->words.w0 = 0xDB0E0000;
    gdl->words.w1 = *(u16 *) ((u8 *) D_800BE628 + D_80082FA4 * 0x180 + 0xB8);
    gdl++;
    texs = D_8008955C[sky[9]];
    count = 0;
    first_vtx = 0;
    last_fmt = -1;
    vtx = D_800DC2B8[D_80082FA4 * 2 + D_800BE9C0];
    if (dist < 0) {
        dist = 0;
    }
    last = (D_800BE9F0 == 12) ? 6 : 5;
    i = (D_800BE9F0 == 25) ? 4 : 0;
    for (; i < last; i++) {
        switch (i) {
            case 0:
                if (pitch <= 180.0f) {
                    if (fov < pitch) {
                        continue;
                    }
                } else if (pitch < 360.0f - fov) {
                    continue;
                }
                break;
            case 1:
                if (270.0f + fov < pitch || pitch < 270.0f - fov) {
                    continue;
                }
                break;
            case 2:
                if (180.0f + fov < pitch || pitch < 180.0f - fov) {
                    continue;
                }
                break;
            case 3:
                if (90.0f + fov < pitch || pitch < 90.0f - fov) {
                    continue;
                }
                break;
            case 4:
                if (-90.0f + fov < yaw || yaw < -90.0f - fov) {
                    continue;
                }
                break;
            case 5:
                if (90.0f + fov < yaw || yaw < 90.0f - fov || dist < 300) {
                    continue;
                }
                break;
        }
        f = &D_800A3170[i];
        if (f->a[0] == f->b[0]) {
            axis = 'x';
        } else if (f->a[1] == f->b[1]) {
            axis = 'y';
        } else {
            axis = 'z';
        }
        face = (i == 5) ? 0 : i;
        gdl = sky_box_face_build(gdl, &vtx, texs[face], 0, 2, f->w, f->h, 60, 30, f->a[0], f->a[1], f->a[2], axis, view, dist,
                            &count, &first_vtx, loads, &last_fmt, arg19, arg20, tlut_offset, tlut_count, tile, face);
    }
    if (count != 0) {
        gdl->words.w0 = 0x01000000 | ((count & 0xFF) << 12) | ((count & 0x7F) << 1);
        gdl->words.w1 = vtx + first_vtx * 0x10;
        gdl++;
        for (k = 0; k < count; k += 4) {
            fmt = loads[k >> 2].fmt;
            gdl->words.w0 = 0xE7000000;
            gdl->words.w1 = 0;
            gdl++;
            gdl->words.w0 = 0xFD100000;
            gdl->words.w1 = loads[k >> 2].addr;
            gdl++;
            gdl->words.w0 = 0xF3000000;
            gdl->words.w1 = 0x077FF000;
            gdl++;
            gdl->words.w0 = 0xFD100000;
            gdl->words.w1 = loads[k >> 2].addr + tlut_offset[fmt];
            gdl++;
            gdl->words.w0 = 0xE6000000;
            gdl->words.w1 = 0;
            gdl++;
            gdl->words.w0 = 0xF0000000;
            gdl->words.w1 = 0x06000000 | (tlut_count[fmt] << 14);
            gdl++;
            if (fmt != last_fmt) {
                last_fmt = fmt;
                gdl->words.w0 = 0xD7000002 | ((tile[fmt] & 7) << 8);
                gdl->words.w1 = 0xFFFFFFFF;
                gdl++;
            }
            /* two triangles (k + 2, k, k + 1) and (k + 3, k, k + 2); G_TRI1 indices are vertex * 2 */
            gdl->words.w0 = 0x05000000 | (((k * 2 + 4) & 0xFF) << 16) | (((k * 2) & 0xFF) << 8) | ((k * 2 + 2) & 0xFF);
            gdl->words.w1 = 0;
            gdl++;
            gdl->words.w0 = 0x05000000 | (((k * 2 + 6) & 0xFF) << 16) | (((k * 2) & 0xFF) << 8) | ((k * 2 + 4) & 0xFF);
            gdl->words.w1 = 0;
            gdl++;
        }
    }
    return gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/sky_box_draw.s")
#endif

#ifdef NON_MATCHING
extern s16 D_800895D4;
extern f32 D_800DC2F0;

/* was func_15112AA0 */
void world_object_turn_to_player(u8 *arg0) {
    f32 sp58;
    f32 sp4C;
    f32 sp40;
    u8 *sp3C;
    f32 sp30;
    f32 sp2C;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f0_6;
    f32 temp_f0_7;
    f32 temp_f0_8;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f12_3;
    f32 temp_f14;
    f32 temp_f14_2;
    f32 temp_f14_3;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f20;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f6;
    f32 var_f12;
    f32 var_f16;
    f32 var_f16_2;
    f32 var_f16_3;
    f32 var_f20;
    f32 var_f20_2;
    f32 var_f2;
    f32 var_f2_2;
    f32 var_f2_3;
    s16 var_a1;
    u16 temp_v1;
    u8 *temp_t0;

    temp_t0 = (*(u8 **)((u8 *)arg0 + 0x3C));
    temp_f12 = D_800CC2D0->x_position - (f32) (*(s16 *)((u8 *)arg0 + 0x10));
    temp_f2 = temp_f12 * temp_f12;
    temp_f18 = (D_800CC2D0->y_position + 65.0f) - (f32) (*(s16 *)((u8 *)arg0 + 0x12));
    temp_f14 = D_800CC2D0->z_position - (f32) (*(s16 *)((u8 *)arg0 + 0x14));
    temp_f16 = temp_f14 * temp_f14;
    temp_f6 = temp_f2 + (temp_f18 * temp_f18) + temp_f16;
    D_800DC2F0 = temp_f6;
    temp_f0 = (*(f32 *)((u8 *)temp_t0 + 0x2C));
    if ((temp_f0 * temp_f0) < temp_f6) {
        var_f16 = (*(f32 *)((u8 *)temp_t0 + 0x28));
        var_f20 = (*(f32 *)((u8 *)temp_t0 + 0x24));
        if (var_f16 < 0.0f) {
            var_f16 += 360.0f;
        }
        sp40 = (*(f32 *)((u8 *)temp_t0 + 4));
    } else {
        sp3C = temp_t0;
        sp30 = temp_f2;
        sp2C = temp_f16;
        sp58 = temp_f18;
        temp_f20 = math_atan2f(temp_f12, temp_f14);
        var_f20_2 = temp_f20 * 57.295776f;
        temp_f2_2 = math_atan2f(sp58, sqrtf(temp_f2 + temp_f16)) * 57.295776f;
        var_f16_2 = temp_f2_2;
        if (temp_f2_2 < 0.0f) {
            var_f16_2 = temp_f2_2 + 360.0f;
        } else if (temp_f2_2 >= 360.0f) {
            var_f16_2 = temp_f2_2 - 360.0f;
        }
        if (var_f20_2 < 0.0f) {
            var_f20_2 += 360.0f;
        } else if (var_f20_2 >= 360.0f) {
            var_f20_2 -= 360.0f;
        }
        sp4C = var_f16_2;
        sp3C = temp_t0;
        temp_f0_2 = math_angle_diff_deg((*(f32 *)((u8 *)temp_t0 + 0x24)), var_f20_2);
        var_f16_3 = var_f16_2;
        if (var_f16_3 > 180.0f) {
            var_f16_3 -= 360.0f;
        }
        temp_f12_2 = (*(f32 *)((u8 *)temp_t0 + 0xC));
        temp_f14_2 = (*(f32 *)((u8 *)temp_t0 + 0x14));
        if (((temp_f12_2 + temp_f14_2) < temp_f0_2) || (var_f2 = (*(f32 *)((u8 *)temp_t0 + 0x10)), (temp_f0_2 < (var_f2 - temp_f14_2)))) {
            var_f20 = (*(f32 *)((u8 *)temp_t0 + 0x24));
            var_f16 = (*(f32 *)((u8 *)temp_t0 + 0x28));
            sp40 = (*(f32 *)((u8 *)temp_t0 + 4));
        } else {
            sp40 = (*(f32 *)((u8 *)temp_t0 + 0));
            if (temp_f0_2 < var_f2) {

            } else if (temp_f12_2 < temp_f0_2) {
                var_f2 = temp_f12_2;
            } else {
                var_f2 = temp_f0_2;
            }
            var_f20 = (*(f32 *)((u8 *)temp_t0 + 0x24)) + var_f2;
            if (var_f20 < 0.0f) {
                var_f20 += 360.0f;
            } else if (var_f20 >= 360.0f) {
                var_f20 -= 360.0f;
            }
            temp_f0_3 = (*(f32 *)((u8 *)temp_t0 + 0x18));
            temp_f12_3 = (*(f32 *)((u8 *)temp_t0 + 0x20));
            if (((temp_f0_3 + temp_f12_3) < var_f16_3) || (var_f2_2 = (*(f32 *)((u8 *)temp_t0 + 0x1C)), (var_f16_3 < (var_f2_2 - temp_f12_3)))) {
                var_f16 = 0.0f;
            } else {
                if (var_f16_3 < var_f2_2) {

                } else if (temp_f0_3 < var_f16_3) {
                    var_f2_2 = temp_f0_3;
                } else {
                    var_f2_2 = var_f16_3;
                }
                var_f16 = var_f2_2;
            }
        }
        if (var_f16 < 0.0f) {
            var_f16 += 360.0f;
        }
    }
    sp4C = var_f16;
    sp3C = temp_t0;
    temp_f0_4 = math_angle_diff_deg((*(f32 *)((u8 *)arg0 + 4)), var_f20);
    var_f12 = temp_f0_4;
    temp_f0_5 = fabsf(temp_f0_4);
    temp_f14_3 = (*(f32 *)((u8 *)temp_t0 + 8));
    if (temp_f14_3 < temp_f0_5) {
        if (var_f12 < 0.0f) {
            var_f2_3 = -1.0f;
        } else {
            var_f2_3 = 1.0f;
        }
        var_f12 = var_f2_3 * temp_f14_3;
    }
    (*(f32 *)((u8 *)arg0 + 4)) = (f32) ((*(f32 *)((u8 *)arg0 + 4)) + (var_f12 * sp40));
    if ((D_800895D4 == 0) && (temp_f0_5 > 4.0f)) {
        D_800895D4 = -1;
    }
    temp_f0_6 = (*(f32 *)((u8 *)arg0 + 4));
    if (temp_f0_6 < 0.0f) {
        (*(f32 *)((u8 *)arg0 + 4)) = (f32) (temp_f0_6 + 360.0f);
    } else if (temp_f0_6 >= 360.0f) {
        (*(f32 *)((u8 *)arg0 + 4)) = (f32) (temp_f0_6 - 360.0f);
    }
    sp3C = temp_t0;
    temp_f0_7 = math_angle_diff_deg((*(f32 *)((u8 *)arg0 + 0)), 360.0f - var_f16);
    var_a1 = D_800895D4;
    (*(f32 *)((u8 *)arg0 + 0)) = (f32) ((*(f32 *)((u8 *)arg0 + 0)) + (temp_f0_7 * sp40));
    if ((var_a1 == 0) && (fabsf(temp_f0_7) > 4.0f)) {
        var_a1 = -1;
    }
    temp_f0_8 = (*(f32 *)((u8 *)arg0 + 0));
    if (temp_f0_8 < 0.0f) {
        (*(f32 *)((u8 *)arg0 + 0)) = (f32) (temp_f0_8 + 360.0f);
    } else if (temp_f0_8 >= 360.0f) {
        (*(f32 *)((u8 *)arg0 + 0)) = (f32) (temp_f0_8 - 360.0f);
    }
    if ((var_a1 == -1) && (temp_v1 = (*(u16 *)((u8 *)temp_t0 + 0x32)), (temp_v1 != 0))) {
        D_800895D4 = (s16) temp_v1;
        if ((s32) (32000.0f - (D_800DC2F0 * 0.1f)) > 0) {
            sound_play_2d((s32) (*(u16 *)((u8 *)temp_t0 + 0x30)), 0x7D00U, 0x40U, 0, 0U);
        }
    } else {
        D_800895D4 = var_a1;
        if (var_a1 > 0) {
            D_800895D4 = var_a1 - 1;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/world_object_turn_to_player.s")
#endif
#ifdef NON_MATCHING
extern u8 D_800C3A7C;
extern f32 D_800D9F3C;   /* default draw distance of the world records */
extern u8 D_800DA030[];  /* per player: 0x40-byte view matrix for camera_view_test_sphere */
extern s32 D_800895E0[]; /* per player: pointer to the visible-list pointer (entries: s16 record index, s16 depth) */
extern u16 D_800DC318[]; /* per player: visible-list length */
s32 player_stat_get(s16 player, s32 field);
s32 cutscene_room_has_actor(s32, s32);
s32 zone_point_allowed(u8 *, s16, s16, s32, s32);
s32 camera_view_test_sphere(s32 cam, s32 *mtx, f32 x, f32 y, f32 z, f32 r, f32 ry, f32 far);

/* world_records_build_visible: per frame (world_update path, view arg0), for every active player view
 * (player_stat_get(player, 0)) rebuilds the list of visible world-object records (0xA0 bytes, D_800DBEF4[0 ..
 * D_800DC320 - 1]). Records come in groups: a record's +0x70 >> 4 is the number of records following it in the group.
 * For each record the player's bit in +0x6F is cleared; a record takes part unless it is kind 1 (+0x6E), hidden
 * (+0x70 & 8), disabled (!(+0x4F & 1)) or has no model (+0x8A == 0). In mode D_800C35EA[view] == 1, cutscene_room_has_actor
 * decides (without D_800C3A7C[view] a refusal skips the record; an acceptance skips the occlusion test below), else
 * records with +0x6C & 0x100 are skipped when zone_point_allowed(+0x98, x, z, player, 0) says they are hidden.
 * camera_view_test_sphere then gives the (absolute) view depth against the far distance (+0x90: 0 = D_800D9F3C, 1 = 40000,
 * D_800D9F3C when the player's object has +0x197 set) and the per-player fade byte +0x8B + player is updated:
 * depth 0 or beyond far: 0 (not visible); within 200 of far: (far - depth) * 255 / 200; nearer: with a near
 * distance +0x88, fades out by D_800BE9E4 * 10 per frame below it and in above it (0 = not visible), without one 0xFF.
 * If any record of a group is visible, every record of the group gets the player's +0x6F bit and an entry
 * (index, depth) in the player's list D_800895E0[player] (length D_800DC318[player]). */
/* was func_15113000 */
void world_records_build_visible(s32 view) {
    s32 depth[16];
    s32 player;
    s32 cam;
    s32 first;
    s32 last;
    s32 visible;
    s32 bit;
    s32 far;
    s32 step;
    s32 i;
    u8 *rec;
    u8 *mode;
    u8 *alpha;
    u8 *entry;

    for (player = 0; player <= D_80082FA0; player++) {
        cam = D_800BE628 + player * 0x180;
        if (player_stat_get((s16) player, 0) == 0) {
            continue;
        }
        D_800DC318[player] = 0;
        i = 0;
        while (i < D_800DC320) {
            visible = 0;
            first = i;
            last = i + (((u8 *) D_800DBEF4 + i * 0xA0)[0x70] >> 4);
            bit = 1 << player;
            for (; i <= last; i++) {
                rec = (u8 *) D_800DBEF4 + i * 0xA0;
                rec[0x6F] &= ~bit;
                if (rec[0x6E] == 1 || (rec[0x70] & 8) || !(rec[0x4F] & 1) || rec[0x8A] == 0) {
                    continue;
                }
                mode = &D_800C35EA + view;
                if ((&D_800C3A7C)[view] == 0 && *mode == 1 && cutscene_room_has_actor(i, view) == 0) {
                    continue;
                }
                if (!(*mode == 1 && cutscene_room_has_actor(i, view) != 0)) {
                    if ((*(u16 *) (rec + 0x6C) & 0x100)
                        && zone_point_allowed(rec + 0x98, *(s16 *) (rec + 0x10), *(s16 *) (rec + 0x14), player, 0) != 0) {
                        continue;
                    }
                }
                if ((*(u8 **) ((u8 *) D_800DBFF0 + player * 0x9A0 + 0x3D4))[0x197] != 0) {
                    far = D_800D9F3C;
                } else {
                    far = *(u16 *) (rec + 0x90);
                    if (far == 0) {
                        far = D_800D9F3C;
                    } else if (far == 1) {
                        far = 40000;
                    }
                }
                depth[i - first] = camera_view_test_sphere(cam, (s32 *) (D_800DA030 + player * 0x40), *(s16 *) (rec + 0x10),
                                                 *(s16 *) (rec + 0x12) + *(f32 *) (rec + 0x18), *(s16 *) (rec + 0x14),
                                                 *(u16 *) (rec + 0x50), *(u16 *) (rec + 0x52), far);
                if (depth[i - first] < 0) {
                    depth[i - first] = -depth[i - first];
                }
                alpha = rec + 0x8B + player;
                if (depth[i - first] == 0 || depth[i - first] > far) {
                    *alpha = 0;
                    continue;
                }
                if (depth[i - first] >= far - 200) {
                    step = (far - depth[i - first]) * 255 / 200;
                    *alpha = (step > 255) ? 255 : step;
                } else if (*(u16 *) (rec + 0x88) == 0) {
                    *alpha = 0xFF;
                } else {
                    step = D_800BE9E4 * 10;
                    if (depth[i - first] < *(u16 *) (rec + 0x88)) {
                        *alpha = (*alpha > step) ? *alpha - step : 0;
                    } else {
                        *alpha = (*alpha < 0xFF - step) ? *alpha + step : 0xFF;
                    }
                    if (*alpha == 0) {
                        continue;
                    }
                }
                visible |= bit;
            }
            if (visible != 0) {
                for (i = first; i <= last; i++) {
                    ((u8 *) D_800DBEF4 + i * 0xA0)[0x6F] |= bit;
                    entry = *(u8 **) D_800895E0[player] + D_800DC318[player] * 4;
                    ((s16 *) entry)[0] = i;
                    ((s16 *) entry)[1] = depth[i - first];
                    D_800DC318[player]++;
                }
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/world_records_build_visible.s")
#endif

#ifdef NON_MATCHING
/* was func_15113700 */
void world_records_flag_active(void) {
    s32 var_v0;
    s32 var_v1;
    u8 *temp_a0;
    u8 *temp_a0_2;
    u8 temp_a1;

    var_v0 = 0;
    var_v1 = 0;
    if (D_800DC320 > 0) {
        do {
            temp_a0 = &D_800DBEF4->pad[var_v1];
            (*(u8 *)((u8 *)temp_a0 + 0x6F)) = (u8) ((*(u8 *)((u8 *)temp_a0 + 0x6F)) & ~0x40);
            temp_a0_2 = &D_800DBEF4->pad[var_v1];
            temp_a1 = (*(u8 *)((u8 *)temp_a0_2 + 0x6F));
            if (((temp_a1 & 0xF) || (((*(u8 *)((u8 *)temp_a0_2 + 0x70)) & 4) == 4)) && ((*(s32 *)((u8 *)temp_a0_2 + 0x38)) != 0)) {
                (*(u8 *)((u8 *)temp_a0_2 + 0x6F)) = (u8) (temp_a1 | 0x40);
            }
            var_v0 += 1;
            var_v1 += 0xA0;
        } while (var_v0 < D_800DC320);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/world_records_flag_active.s")
#endif
#ifdef NON_MATCHING
void mtx_set_identity(Mtx *arg0);
void world_record_build_matrix(f32 (*arg0)[4], u8 *arg1);
extern s32 D_800895E0[];     /* per group: pointer to the group's entry list pointer (entries: u16 record id, u16) */
extern s32 D_800895F0[];     /* per DL buffer: pointer to the matrix array pointer (one Mtx per record id) */
extern u16 D_800DC318[];     /* per group: entry count */
extern f32 D_800DC338[][4][4]; /* per DL buffer: fallback matrix */

/* world_records_update_matrices: per-frame matrix pass over the world-object records (called by world_update, the
 * world update). For each group 0..D_80082FA0 that player_stat_get(group, 0) accepts, every listed record id gets its
 * Mtx in the current DL buffer's array (D_800895F0[D_800BE9C0]):
 *  - disabled record (+0x70 & 1): mtx_set_identity;
 *  - kind +0x4E 3: left as it is; kind < 3: from world_record_build_matrix (record orientation / position);
 *  - kind 0x65..0x7C (follows object D_800CC2D0[kind - 100]): rotation from the record angles +0x2C / +0x30 /
 *    +0x34 (mtxf_scale) at the object's position +0x14; with an attachment +0x1D4, at its +0x30 position,
 *    raised by the object's +0x90 (mtxf_translate_local), and that point is written back to the record (+0x10 / 12 / 14);
 *  - any other kind: the buffer's fallback matrix D_800DC338[D_800BE9C0]. */
/* was func_15113798 */
void world_records_update_matrices(void) {
    f32 mf[4][4];
    s32 group;
    s32 j;
    u16 id;
    u8 *rec;
    u8 *obj;
    u8 *att;
    s32 kind;

    for (group = 0; group <= D_80082FA0; group++) {
        if (player_stat_get((s16)group, 0) == 0) {
            continue;
        }
        for (j = 0; j < D_800DC318[group]; j++) {
            id = *(u16 *)(*(u8 **)D_800895E0[group] + j * 4);
            rec = (u8 *)D_800DBEF4 + id * 0xA0;
            if ((rec[0x70] & 1) == 1) {
                mtx_set_identity((Mtx *)(*(u8 **)D_800895F0[D_800BE9C0] + id * 0x40));
                continue;
            }
            kind = rec[0x4E];
            if (kind == 3) {
                continue;
            }
            if (kind < 3) {
                world_record_build_matrix(mf, rec);
            } else if (kind >= 0x65 && kind < 0x7D) {
                obj = (u8 *)D_800CC2D0 + (kind - 100) * 0x32C;
                if (*(u8 **)(obj + 0x1D4) == NULL) {
                    mtxf_scale(mf, *(s32 *)(rec + 0x2C), *(s32 *)(rec + 0x30), *(s32 *)(rec + 0x34));
                    mf[3][0] = *(f32 *)(obj + 0x14);
                    mf[3][1] = *(f32 *)(obj + 0x18);
                    mf[3][2] = *(f32 *)(obj + 0x1C);
                } else {
                    att = *(u8 **)(obj + 0x1D4);
                    mtxf_scale(mf, *(s32 *)(rec + 0x2C), *(s32 *)(rec + 0x30), *(s32 *)(rec + 0x34));
                    mf[3][0] = *(f32 *)(att + 0x30);
                    mf[3][1] = *(f32 *)(att + 0x34);
                    mf[3][2] = *(f32 *)(att + 0x38);
                    mtxf_translate_local(mf, 0.0f, (f32) * (s16 *)(obj + 0x90), 0.0f);
                    *(s16 *)(rec + 0x10) = (s32)mf[3][0];
                    *(s16 *)(rec + 0x12) = (s32)mf[3][1];
                    *(s16 *)(rec + 0x14) = (s32)mf[3][2];
                }
            } else {
                guMtxF2L(D_800DC338[D_800BE9C0], (Mtx *)(*(u8 **)D_800895F0[D_800BE9C0] + id * 0x40));
                continue;
            }
            id = *(u16 *)(*(u8 **)D_800895E0[group] + j * 4);
            guMtxF2L(mf, (Mtx *)(*(u8 **)D_800895F0[D_800BE9C0] + id * 0x40));
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/world_records_update_matrices.s")
#endif

#ifdef NON_MATCHING
s32 fog_identity_stub(s32 arg0, s32 arg1);
u8 *light_write_light_cmds(u8 *arg0, s32 arg1, u8 arg2, s32 arg3, s32 arg4);
s32 world_mesh_draw(s32, u8 *, s32, s16, s32, s32);
extern s32 D_800895E0[];
extern s32 D_800895F0[];
extern u8 D_800D9FF0[];
extern s32 D_800DA230[];
extern u8 D_800DA240;
extern u8 D_800DA241;
extern u16 D_800DC318[];

/* Draws the sky/world mesh list of player arg2: geometry-mode setup, the player's light block
 * (light_write_light_cmds), then one world_mesh_draw per entry of the player's u16-pair list
 * (entry index into the 0xA0-byte D_800DBEF4 records, extra value), then a fixed matrix pop
 * and the geometry-mode reset. arg1 != 0 passes flag 0x10 to every entry. */
/* was func_15113B44 */
Gfx *world_meshes_draw_player(Gfx *arg0, s32 arg1, s16 arg2) {
    s32 flags;
    s32 i;
    u8 *gdl;
    u16 *entry;
    u16 idx;

    if (arg1 == 0) {
        flags = 0;
    } else {
        flags = 0x10;
    }
    gdl = (u8 *) fog_identity_stub((s32) arg0, 0);
    *(s32 *) (gdl + 0x0) = 0xD9A3FFFF;
    *(s32 *) (gdl + 0x4) = 0;
    *(s32 *) (gdl + 0xC) = 0x20000;
    *(s32 *) (gdl + 0x8) = 0xD9FFFFFF;
    gdl = light_write_light_cmds(gdl + 0x10, D_800DA230[arg2], D_800DA240, D_800DA241,
                        (s32) (D_800D9FF0 + arg2 * 16 + D_800BE9C0 * 8));
    for (i = 0; i < D_800DC318[arg2]; i++) {
        entry = (u16 *) (*(u8 **) D_800895E0[arg2] + i * 4);
        idx = entry[0];
        gdl = (u8 *) world_mesh_draw((s32) gdl, (u8 *) D_800DBEF4 + idx * 0xA0,
                                   (idx << 6) + *(s32 *) D_800895F0[D_800BE9C0], arg2, entry[1], flags);
    }
    *(s32 *) (gdl + 0x0) = 0xDA380003;
    *(u8 **) (gdl + 0x4) = D_80089810;
    *(s32 *) (gdl + 0x8) = 0xD9AFFDFF;
    *(s32 *) (gdl + 0xC) = 0;
    *(s32 *) (gdl + 0x14) = 0x20000;
    *(s32 *) (gdl + 0x10) = 0xD9FFFFFF;
    return (Gfx *) (gdl + 0x18);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/world_meshes_draw_player.s")
#endif
#ifdef NON_MATCHING
/* P183 */
Gfx *tint_emit_prim_env_colors(Gfx *gdl, s32 arg1, s32 arg2, s32 arg3);
u8 *segment_override_emit(u8 *arg0, s32 arg1);
Gfx *tex_scroll_set_tile_sizes(Gfx *gdl);
Gfx *mesh_dl_cull_copy(s32, Gfx *, u8 *, s32, s32, s32);
extern u8 D_800840D0[];   /* combiner/othermode block for translucent meshes (segment 6 + 0x20) */
extern u8 D_80084250[];   /* the same block for opaque meshes */
extern u8 D_800DA030[];   /* per player: 0x40-byte view matrix (float) */
extern s32 D_800BEFC4;    /* display list capacity (commands) */

// world_mesh_draw: P183: draws one world mesh record `obj` (0xA0 bytes) for `player`: alpha =
// obj[0x8B + player] * obj[0x8A] / 255 (0xFF when both are 0xFF), nothing when 0 or when the opaque/translucent
// pass flag `pass` (0 or 0x10) does not match (opaque meshes draw only when obj[0x4F] & 0x10 differs from pass,
// translucent ones only in pass 0). Flags obj+0x6C bits 0/4/5 call the debug position hooks. Then pipe sync,
// render-mode block (D_800840D0 translucent / D_80084250 opaque), cull mode (obj[0x4F] & 2), tint_emit_prim_env_colors colour
// (0xFF, alpha), segment_override_emit, segment 1 = obj+0x20[frame], matrix `mtx`, optional tex_scroll_set_tile_sizes (flag 0x200),
// the mesh (mesh_dl_cull_copy when obj[0x70] & 2, else a G_DL to obj+0x1C). Returns the new gdl, or the start when
// the frame display list overflows. `unused` is never read.
/* was func_15113D54 */
s32 world_mesh_draw(s32 arg0, u8 *obj, s32 mtx, s16 player, s32 unused, s32 pass) {
    Gfx *gdl = (Gfx *) arg0;
    Gfx *start = gdl;
    s32 a = obj[0x8B + player];
    s32 alpha;
    u16 flags;

    if (a == 0xFF && obj[0x8A] == 0xFF) {
        alpha = 0xFF;
    } else {
        alpha = (s32) (a * obj[0x8A]) / 0xFF;
        if (alpha == 0) {
            return (s32) gdl;
        }
    }
    if (alpha == 0xFF) {
        if (pass == (obj[0x4F] & 0x10)) {
            return (s32) gdl;
        }
    } else if (pass != 0) {
        return (s32) gdl;
    }

    flags = *(u16 *) (obj + 0x6C);
    if (flags != 0) {
        if (flags & 1) {
            gdl = debug_gdl_pos_value_nop(gdl, (f32) *(s16 *) (obj + 0x10),
                                (f32) *(s16 *) (obj + 0x12) + *(f32 *) (obj + 0x18),
                                (f32) *(s16 *) (obj + 0x14), *(f32 *) (obj + 0x4), player);
        } else if (flags & 0x10) {
            gdl = debug_gdl_pos_value_nop(gdl, (f32) *(s16 *) (obj + 0x10),
                                (f32) *(s16 *) (obj + 0x12) + *(f32 *) (obj + 0x18),
                                (f32) *(s16 *) (obj + 0x14), (f32) *(s32 *) (obj + 0x7C), player);
        } else if (flags & 0x20) {
            gdl = debug_gdl_pos_nop(gdl, (f32) *(s16 *) (obj + 0x10),
                                (f32) *(s16 *) (obj + 0x12) + *(f32 *) (obj + 0x18),
                                (f32) *(s16 *) (obj + 0x14), player);
        }
    }

    gdl->words.w0 = 0xE7000000;
    gdl->words.w1 = 0;
    gdl++;
    gdl->words.w0 = 0xDB060020;
    if (alpha < 0xFF) {
        gdl->words.w1 = (u32) D_800840D0;
    } else {
        gdl->words.w1 = (u32) D_80084250;
    }
    gdl++;
    if ((obj[0x4F] & 2) == 2) {
        gdl->words.w0 = 0xD9FFFFFF;
        gdl->words.w1 = 0x400000;
    } else {
        gdl->words.w0 = 0xD9BFFFFF;
        gdl->words.w1 = 0;
    }
    gdl++;
    gdl->words.w0 = 0xD9FFFFFF;
    gdl->words.w1 = 0x20000;
    gdl++;
    gdl = tint_emit_prim_env_colors(gdl, 0xFF, alpha, player);
    gdl = (Gfx *) segment_override_emit((u8 *) gdl, (s32) obj);
    if (pass == 0) {
        gdl->words.w0 = 0xD9FFFFFF;
        gdl->words.w1 = 0x110000;
        gdl++;
    }
    gdl->words.w0 = 0xDB060004;
    gdl->words.w1 = *(u32 *) (obj + 0x20 + D_800BE9C0 * 4);
    gdl++;
    gdl->words.w0 = 0xDA380003;
    gdl->words.w1 = mtx;
    gdl++;
    gdl->words.w0 = 0xD9F7FFFF;
    gdl->words.w1 = 0;
    gdl++;
    if (*(u16 *) (obj + 0x6C) & 0x200) {
        gdl = tex_scroll_set_tile_sizes(gdl);
    }
    if ((obj[0x70] & 2) == 2) {
        gdl = mesh_dl_cull_copy(*(s32 *) (obj + 0x1C), gdl, D_800DA030 + player * 0x40, 0, 0,
                            *(s32 *) (obj + 0x20 + D_800BE9C0 * 4) + 0xFF000000);
    } else {
        gdl->words.w0 = 0xDE000000;
        gdl->words.w1 = *(u32 *) (obj + 0x1C);
        gdl++;
    }
    gdl->words.w0 = 0xD9EEFFFF;
    gdl->words.w1 = 0;
    gdl++;
    gdl->words.w0 = 0xE7000000;
    gdl->words.w1 = 0;
    gdl++;
    if (D_800BEFC4 < (((u8 *) gdl - (u8 *) D_800BEDE8[D_800BE9C0]) >> 3)) {
        return (s32) start;
    }
    return (s32) gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/world_mesh_draw.s")
#endif

extern u8 D_800C3A7C;
s32 cutscene_room_has_actor(s32, s32);
void *blob_shadow_create(s32, struct131 *, s32, s32, s32);

/* was func_15114208 */
void world_records_update_shadows(void) {
    s32 i;
    s32 j;
    s32 found;
    s32 ok;
    struct131 *e;

    for (i = 0; i < D_800DC320; i++) {
        e = &D_800DBEF4[i];
        found = 0;
        for (j = 0; j < D_80082FA0; j++) {
            do {
            } while (0); // fakematch: changes the s-register allocation
            if (player_stat_get(j, 0) && ((u8 *)e)[0x8B + j] == 0) {
                found = 1;
                break;
            }
        }
        if ((e->pad70[0] & 8) || ((u8 *)e)[0x4C] == 0 || (((u8 *)e)[0x4F] & 0x10) == 0x10 || found ||
            (D_800C3A7C == 0 && D_800C35EA == 1 && !cutscene_room_has_actor(i, 0)) || !(((u8 *)e)[0x4F] & 1)) {
            ok = 0;
        } else {
            ok = 1;
        }
        if (ok) {
            if (*(void **)((u8 *)e + 0x94) == NULL) {
                *(void **)((u8 *)e + 0x94) = blob_shadow_create(1, e, 0, 1, 0);
            }
        } else if (*(struct102 **)((u8 *)e + 0x94) != NULL) {
            node_destroy(*(struct102 **)((u8 *)e + 0x94));
            *(struct102 **)((u8 *)e + 0x94) = NULL;
        }
    }
}

#ifdef NON_MATCHING
/* the D_800DBEF4 record fields world_records_run_callbacks uses (0xA0 bytes) */
typedef struct {
    u8  pad0[0x38];
    void (*update)(void *);   /* 0x38 */
    u8  pad3C[0x5A - 0x3C];
    s16 pos[3];               /* 0x5A */
    u8  pad60[0x6E - 0x60];
    u8  busy;                 /* 0x6E */
    u8  flags;                /* 0x6F: 0x40 = needs update */
    u8  pad70[0x80 - 0x70];
    s32 extra;                /* 0x80 */
    u8  pad84[0xA0 - 0x84];
} Rec151143D4;

/* a D_800D23C0 group (0x18 bytes): ids[] are (type << 12 | record index); type 2 = D_800DBEF4 record */
typedef struct {
    u8  pad0[2];
    u16 count;                /* 0x2 */
    u8  pad4[4];
    u16 ids[8];               /* 0x8 */
} Group151143D4;

extern s32 D_800DC3C8;

/* Runs the update callback of every pending record (flags & 0x40, not busy): first the first
 * D_800DC320 - D_800DC3C8 records, then the type-2 groups. In a group, the first record's position (0x5A..0x5E)
 * and 0x80 value are copied to each following member before its update. arg0 is not used. */
/* was func_151143D4 */
void world_records_run_callbacks(s32 arg0) {
    Rec151143D4 *rec;
    Group151143D4 *grp;
    s16 x, y, z;
    s32 extra;
    s32 n, i, j;
    u16 id;

    x = y = z = 0;
    extra = 0;
    n = D_800DC320 - D_800DC3C8;
    for (i = 0; i < n; i++) {
        rec = (Rec151143D4 *) D_800DBEF4 + i;
        if ((rec->flags & 0x40) == 0x40 && rec->busy == 0) {
            rec->update(rec);
        }
    }
    for (i = 0; i < (s32) D_80087380; i++) {
        grp = (Group151143D4 *) D_800D23C0 + i;
        if ((grp->ids[0] >> 12) != 2) {
            continue;
        }
        for (j = 0; j < grp->count; j++) {
            id = ((Group151143D4 *) D_800D23C0)[i].ids[j];
            if ((id >> 12) != 2) {
                continue;
            }
            rec = (Rec151143D4 *) D_800DBEF4 + (id & 0xFFF);
            if ((rec->flags & 0x40) == 0x40 && rec->busy == 0) {
                if (j != 0) {
                    rec->pos[0] = x;
                    rec->pos[1] = y;
                    rec->pos[2] = z;
                    rec->extra = extra;
                }
                rec->update(rec);
                grp = (Group151143D4 *) D_800D23C0 + i;   /* the callback may move the groups */
            }
            if (j == 0) {
                x = rec->pos[0];
                y = rec->pos[1];
                z = rec->pos[2];
                extra = rec->extra;
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/world_records_run_callbacks.s")
#endif

extern s32 *D_800DC3C4;

/* was func_151145D0 */
s32 world_record_touched_by(struct131 *arg0, s32 arg1) {
    if (*((u8 *)arg0 + 0x4F) & 0x80) {
        if (arg1 == -1) {
            return 1;
        }
        if (D_800DC3C4[arg0 - D_800DBEF4] & (1 << arg1)) {
            return 1;
        }
    }
    return 0;
}

/* was func_15114644 */
s32 world_record_first_toucher(u8 *arg0) {
    s32 i;
    s32 v;
    s32 m; // fakematch: mask temp fixes the and operand order
    i = 0;
    if (arg0[0x4F] & 0x80) {
        v = D_800DC3C4[(arg0 - (u8 *)D_800DBEF4) / 160];
loop:
        m = 1 << i;
        if ((v & m) != 0) return i;
        m = 1 << (i + 1);
        if ((v & m) != 0) return i + 1;
        m = 1 << (i + 2);
        if ((v & m) != 0) return i + 2;
        m = 1 << (i + 3);
        if ((v & m) != 0) return i + 3;
        i += 4;
        if (i != 0x20) goto loop;
    }
    return 0;
}

#ifdef NON_MATCHING
void world_object_timer_update(struct127 *, s32);
extern s32 *D_800DC3C4;
typedef void (*fn15114708)(u8 *, struct127 *, u8 *, void *);

/* was func_15114708 */
void world_records_dispatch_touches(void) {
    s32 i;
    s32 j;
    s32 *mask;
    u8 *e;
    u8 *base;
    fn15114708 fn;
    struct127 *obj;
    u8 f;

    for (i = 0; i < D_800DC320; i++) {
        if (D_800DC3C4[i] == 0) {
            continue;
        }
        for (j = 0; j < 0x19 && D_800DC3C4[i] != 0; j++) {
            mask = &D_800DC3C4[i];
            if (!(*mask & (1 << j))) {
                continue;
            }
            *mask ^= 1 << j;
            base = (u8 *)D_800DBEF4;
            e = base + i * 0xA0;
            fn = *(fn15114708 *)(e + 0x78);
            obj = (struct127 *)((u8 *)D_800CC2D0 + j * 0x32C);
            if (fn != NULL && (e[0x92] != 0 || ((u8 *)obj)[0x127] != 0xFF)) {
                (*fn)(e, obj, base, (void *)fn);
                e = (u8 *)D_800DBEF4 + i * 0xA0;
            }
            f = e[0x4F];
            if ((f & 4) == 4 && !(f & 8)) {
                world_object_timer_update(obj, i);
            }
        }
        e = (u8 *)D_800DBEF4 + i * 0xA0;
        e[0x4F] &= 0x73;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/world_records_dispatch_touches.s")
#endif
#ifdef NON_MATCHING
/* P136 */
void mtxf_mul(f32 (*)[4], f32 (*)[4], f32 (*)[4]);

/*
 * world_object_rotate_point: rotates the point (*px, *py, *pz) by world-object record idx (D_800DBEF4, 0xA0 bytes)
 * around its pivot (s16 +0x10/+0x12/+0x14). The record's three base angles (f32 +0 about X, +8 about Z, +4 about Y,
 * each skipped when 0) first turn the local axes X/Y/Z (guRotateF + mtxf_transform_point on the two other axes); the
 * matrix is then R(+0x60, X) * R(+0x68, Z) * R(+0x64, Y) about those axes (mtxf_mul = matrix product).
 * Rare's result kept: each coordinate gets s16 offset (+0x5A/+0x5C/+0x5E) + (rotated - unrotated) added, where
 * the unrotated value is relative to the pivot.
 */
/* was func_151148C8 */
void world_object_rotate_point(s32 idx, f32 *px, f32 *py, f32 *pz) {
    f32 ax[3], ay[3], az[3];
    f32 m2[4][4];
    f32 m[4][4];
    f32 ox, oy, oz;
    f32 dx, dy, dz;
    f32 rx, ry, rz;
    u8 *rec;

    ax[0] = 1.0f; ax[1] = 0.0f; ax[2] = 0.0f;
    ay[0] = 0.0f; ay[1] = 1.0f; ay[2] = 0.0f;
    az[0] = 0.0f; az[1] = 0.0f; az[2] = 1.0f;
    rec = (u8 *) D_800DBEF4 + idx * 0xA0;
    dx = *px - (f32) *(s16 *) (rec + 0x10);
    dy = *py - (f32) *(s16 *) (rec + 0x12);
    dz = *pz - (f32) *(s16 *) (rec + 0x14);
    if (*(f32 *) (rec + 0) != 0.0f) {
        guRotateF(m, *(f32 *) (rec + 0), 1.0f, 0.0f, 0.0f);
        mtxf_transform_point(m, ay[0], ay[1], ay[2], &ay[0], &ay[1], &ay[2]);
        mtxf_transform_point(m, az[0], az[1], az[2], &az[0], &az[1], &az[2]);
        rec = (u8 *) D_800DBEF4 + idx * 0xA0;
    }
    if (*(f32 *) (rec + 8) != 0.0f) {
        guRotateF(m, *(f32 *) (rec + 8), az[0], az[1], az[2]);
        mtxf_transform_point(m, ay[0], ay[1], ay[2], &ay[0], &ay[1], &ay[2]);
        mtxf_transform_point(m, ax[0], ax[1], ax[2], &ax[0], &ax[1], &ax[2]);
        rec = (u8 *) D_800DBEF4 + idx * 0xA0;
    }
    if (*(f32 *) (rec + 4) != 0.0f) {
        guRotateF(m, *(f32 *) (rec + 4), ay[0], ay[1], ay[2]);
        mtxf_transform_point(m, ax[0], ax[1], ax[2], &ax[0], &ax[1], &ax[2]);
        mtxf_transform_point(m, az[0], az[1], az[2], &az[0], &az[1], &az[2]);
        rec = (u8 *) D_800DBEF4 + idx * 0xA0;
    }
    guRotateF(m, *(f32 *) (rec + 0x60), ax[0], ax[1], ax[2]);
    rec = (u8 *) D_800DBEF4 + idx * 0xA0;
    guRotateF(m2, *(f32 *) (rec + 0x68), az[0], az[1], az[2]);
    mtxf_mul(m, m2, m);
    rec = (u8 *) D_800DBEF4 + idx * 0xA0;
    guRotateF(m2, *(f32 *) (rec + 0x64), ay[0], ay[1], ay[2]);
    mtxf_mul(m, m2, m);
    mtxf_transform_point(m, dx, dy, dz, &ox, &oy, &oz);
    rec = (u8 *) D_800DBEF4 + idx * 0xA0;
    rx = (f32) *(s16 *) (rec + 0x5A) + (ox - dx);
    ry = (f32) *(s16 *) (rec + 0x5C) + (oy - dy);
    rz = (f32) *(s16 *) (rec + 0x5E) + (oz - dz);
    *px += rx;
    *py += ry;
    *pz += rz;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/world_object_rotate_point.s")
#endif

#ifdef NON_MATCHING
/* P133 */
void world_object_rotate_point(s32, f32 *, f32 *, f32 *);
extern f32 D_800A3330;   /* world-object timer scale */
extern u16 D_800CC1C0[]; /* per object: world-object index + 1 it follows */

/*
 * world_object_timer_update: for a visible world-object record idx (< D_800DC320) and its object, refreshes the
 * object's +0x14 / +0x18 / +0x1C (world_object_rotate_point) and advances its u16 timer +0x76 by the record's +0x64 speed
 * times D_800A3330 (float -> unsigned as IDO, stored as u16); when the object's +0x137 flag is set and its
 * D_800CC1C0 entry (index from the 0x32C-byte array D_800CC2D0) is idx + 1, +0x7A gets the same value.
 */
/* was func_15114CBC */
void world_object_timer_update(struct127 *arg0, s32 idx) {
    u8 *obj = (u8 *) arg0;
    u8 *rec;
    u32 t;

    if (obj == NULL || idx >= D_800DC320) {
        return;
    }
    world_object_rotate_point(idx, (f32 *) (obj + 0x14), (f32 *) (obj + 0x18), (f32 *) (obj + 0x1C));
    rec = (u8 *) D_800DBEF4 + idx * 0xA0;
    t = (f32) *(u16 *) (obj + 0x76) + *(f32 *) (rec + 0x64) * D_800A3330;
    *(u16 *) (obj + 0x76) = t;
    if (obj[0x137] != 0 && D_800CC1C0[(obj - (u8 *) D_800CC2D0) / 0x32C] == idx + 1) {
        *(u16 *) (obj + 0x7A) = t;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/world_object_timer_update.s")
#endif

void mtxf_mul(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
/* was func_15114E28 */
void world_record_base_rotation(f32 (*arg0)[4], u8 *arg1) {
    f32 sp18[4][4];
    mtxf_rotate_xyz_deg(arg0, 0.0f, *(f32 *)(arg1 + 4), 0.0f);
    mtxf_rotate_xyz_deg(sp18, *(f32 *)arg1, 0.0f, *(f32 *)(arg1 + 8));
    mtxf_mul(sp18, arg0, arg0);
}

/* was func_15114E8C */
void world_record_build_matrix(f32 (*arg0)[4], u8 *arg1) {
    f32 sp20[4][4];

    world_record_base_rotation(arg0, arg1);
    (*(f32 *)((u8 *)arg0 + 0x30)) = *(s16 *)(arg1 + 0x10);
    (*(f32 *)((u8 *)arg0 + 0x34)) = *(f32 *)(arg1 + 0x18) + *(s16 *)(arg1 + 0x12);
    (*(f32 *)((u8 *)arg0 + 0x38)) = *(s16 *)(arg1 + 0x14);
    mtxf_scale(sp20, *(s32 *)(arg1 + 0x2C), *(s32 *)(arg1 + 0x30), *(s32 *)(arg1 + 0x34));
    mtxf_mul(sp20, arg0, arg0);
}

#ifdef NON_MATCHING
// world_record_find: returns the world-object record (0xA0 bytes, D_800DBEF4[0 .. D_800DC320 - 1]) whose id byte
// +0x72 equals id, or NULL; id 0 never matches. Scene tracks with ref kind 3 and scene event 5 / 3 look records up here.
/* was func_151149AC */
u8 *world_record_find(u8 id) {
    u8 *rec;
    s32 i;

    if (id == 0) {
        return NULL;
    }
    rec = (u8 *) D_800DBEF4;
    for (i = 0; i < D_800DC320; i++, rec += 0xA0) {
        if (rec[0x72] == id) {
            return rec;
        }
    }
    return NULL;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/world_record_find.s")
#endif

#ifdef NON_MATCHING
/* Per-frame release of the per-entry blocks D_800DC328[i] (P15, hand C from the asm). Entries are the
 * 0xA0-byte D_800DBEF4 records. A disabled entry (flag 0x70 & 1) drops its block pointer unless it is
 * kept (0x6F & 0x80). Otherwise a live block is freed at once, or, for kept / type-3 entries (0x4E),
 * after its D_800DC32C[i] frame countdown reaches 0. */
void heap_free(s32);
/* was func_15114F9C */
void world_records_release_blocks(void) {
    s32 i;

    for (i = 0; i < D_800DC320; i++) {
        u8 *e = (u8 *)D_800DBEF4 + i * 0xA0;

        if ((e[0x70] & 1) == 1) {
            if (!(e[0x6F] & 0x80)) {
                D_800DC328[i] = 0;
            }
        } else if (D_800DC328[i] != 0) {
            if (e[0x4E] != 3 && !(e[0x6F] & 0x80)) {
                heap_free(D_800DC328[i]);
                D_800DC328[i] = 0;
            } else if (D_800DC32C[i] != 0) {
                D_800DC32C[i]--;
            } else {
                heap_free(D_800DC328[i]);
                D_800DC328[i] = 0;
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/world_records_release_blocks.s")
#endif
extern s32 D_800DC3C8;

/* was func_15115114 */
void world_record_remove(u32 arg0) {
    struct131 *p;
    u32 j;

    j = arg0 * 0xA0; // fakematch: j doubles as the row offset
    if (arg0 < D_800DC320) {
        p = (struct131 *)((u8 *)D_800DBEF4 + j);
        if (*(struct102 **)((u8 *)p + 0x94) != NULL) {
            node_destroy(*(struct102 **)((u8 *)p + 0x94));
            *(struct102 **)((u8 *)D_800DBEF4 + arg0 * 0xA0 + 0x94) = NULL;
            p = (struct131 *)((u8 *)D_800DBEF4 + arg0 * 0xA0);
        }
        p->pad70[0] |= 8;
        D_800DBEF4[arg0].pad5A[0x14] = 1;
    }
    arg0 = D_800DC320 - 1;
    j = D_800DC320 - D_800DC3C8;
    if (D_800DC320 != 0) {
        p = (struct131 *)((u8 *)D_800DBEF4 + arg0 * 0xA0);
        if (p->pad70[0] & 8) {
            do {
                if (arg0 >= j && D_800DC3C8 != 0) {
                    D_800DC3C8--;
                } else {
                    j--;
                }
                D_800DC320--;
                arg0--;
                p--;
            } while (D_800DC320 != 0 && (p->pad70[0] & 8));
        }
    }
}

/* was func_15115244 */
s32 object_sound_position_cb(u8 *arg0, s32 arg1, s32 *arg2, s32 arg3) {
    u8 *temp_v1;

    temp_v1 = (*(u8 **)((u8 *)arg0 + 0x18));
    if ((temp_v1 != NULL) && ((*arg2 != 0) || ((*(s32 *)((u8 *)arg0 + 0x1C)) == 0))) {
        (*(s32 *)((u8 *)arg0 + 0x1C)) = 1;
        (*(s16 *)((u8 *)arg0 + 2)) = (s16) (*(s16 *)((u8 *)temp_v1 + 0x10));
        (*(s16 *)((u8 *)arg0 + 4)) = (s16) (*(s16 *)((u8 *)temp_v1 + 0x12));
        (*(s16 *)((u8 *)arg0 + 6)) = (s16) (*(s16 *)((u8 *)temp_v1 + 0x14));
        return 0;
    }
    return 1;
}

#ifdef NON_MATCHING
/* P136 */

/*
 * object_sound_play: plays / updates the positional sound of a world object (handle u16 at obj +0x74, position s16
 * +0x10/+0x12/+0x14). flags 1: nothing to do when the handle still plays `sound` (sound_voice_get_id). sound -1: stops
 * the handle (sound_voice_stop) and clears it. flags 8: start a new voice instead of reusing the handle. flags 4:
 * sound_voice_play_at (one-shot at the position, volume vol, ranges r0 / r1); the handle is cleared unless flags 8.
 * flags 2: releases the old handle (sound_voice_stop_deferred) and stores sound_voice_play_at's new one. Otherwise releases it and
 * starts a tracked sound with sfx_emitter_start (update callback object_sound_position_cb with the object). Returns 0 (callers
 * declare s32 and ignore it; the asm returns nothing).
 */
/* was func_151152A4 */
s32 world_object_sound_play(u8 *obj, s32 sound, s32 vol, s16 r0, s16 r1, s32 flags) {
    u16 *handle = (u16 *) (obj + 0x74);
    s16 *pos = (s16 *) (obj + 0x10);
    u16 h;

    if ((flags & 1) && *handle != 0 && sound_voice_get_id(*handle) == sound) {
        return 0;
    }
    if (sound == -1) {
        if (*handle != 0) {
            sound_voice_stop(*handle);
            *handle = 0;
        }
        return 0;
    }
    h = (flags & 8) ? 0 : *handle;
    if (flags & 4) {
        sound_voice_play_at(h, sound, vol, 0, 0, -1, pos[0], pos[1], pos[2], r0, r1);
        if (!(flags & 8)) {
            *handle = 0;
        }
    } else if (flags & 2) {
        if (h != 0) {
            sound_voice_stop_deferred(h);
            h = 0;
        }
        *handle = sound_voice_play_at(h, sound, vol, 0, 0, -1, pos[0], pos[1], pos[2], r0, r1);
    } else {
        if (h != 0) {
            sound_voice_stop_deferred(h);
        }
        *handle = sfx_emitter_start(sound, pos[0], pos[1], pos[2], vol, r1, r0, (s32) object_sound_position_cb, obj, 0, 0, 0);
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/world_object_sound_play.s")
#endif

/* was func_15115484 */
void object_sound_set_volume_pitch(s32 arg0, s32 arg1, s32 arg2) {
    sfx_emitter_set_volume_pitch(object_sound_position_cb, arg0, 0, arg1, arg2);
}

s32 func_150ADC50();
extern s32 D_800DC3CC;
extern s32 D_800DC3D0;
extern s32 D_800DC3D4;

/* was func_151154C4 */
void level_tri_tables_check(s32 arg0, s32 arg1, s32 arg2)
{
    s32 i;
    s32 j;
    if (D_800BE9F0 == 0x12 || D_800BE9F0 == 0x36 || D_800BE9F0 == 0x13) {
        for (i = 0; i < 2; i++) {
            u32 *base = (u32 *)D_800DC208[i];
            for (j = 0; j < D_800DBE18[i]; j++) {
                if ((base[j * 3 + 0] & 0xF0000000) != 0x80000000 || (base[j * 3 + 1] & 0xF0000000) != 0x80000000 || (base[j * 3 + 2] & 0xF0000000) != 0x80000000 || (base[j * 3 + 0] & 3) || (base[j * 3 + 1] & 3) || (base[j * 3 + 2] & 3)) {
                    D_8003C8E0 = 0x0C00005A;
                    func_150ADC50();
                }
            }
        }
        D_800DC3CC = arg0;
        D_800DC3D0 = arg1;
        D_800DC3D4 = arg2;
    }
}
