#include <ultra64.h>

#include "functions.h"
#include "variables.h"
#include "libc/math.h"
// hoisted declarations of the NON_MATCHING bodies
void screen_clamp_rect(f32 *x0, f32 *y0, f32 *x1, f32 *y1);
extern s32 g_screen_width; /* was D_800BEA58 */
extern s32 g_screen_height; /* was D_800BEA70 */
extern f32 g_view_aspect_table[]; /* was D_80083338 */
extern f32 g_view_fov_2p; /* was D_80096C94 */
extern f32 g_view_fov_default; /* was D_80096C98 */
extern f32 g_cam_fov_x_deg_to_rad; /* was D_80096C9C */
extern f32 g_cam_fov_y_deg_to_rad; /* was D_80096CA0 */
extern s16 g_view_split_offsets[]; /* was D_800BEA88 */
extern u8 g_view_player_order[]; /* was D_800BEA50 */
s32 camera_rect_on_screen(s32);
void camera_setup_perspective(s32, s32);
void camera_projection_set_fov(s32, f32, f32, f32);


s32 allocate_memory(s32, s32, s32, s32);
s32 level_setup_screen_projection(s32);
s32 camera_record_setup(s32, s32, s32, s32);
void camera_set_screen_ortho(s32);
extern s8 g_dl_buffers_reinit_req; /* was D_800BEA34 */
extern s8 D_800BEA37;
extern s32 g_viewports; /* was D_800BEA4C */
extern s8 g_view_clear_black; /* was D_800BEA55 */
extern s32 g_view_widths; /* was D_800BEA5C */
extern f32 g_split_width_scale; /* was D_800BEAD8 */

/* was func_1501A220 */
void viewports_init(s32 arg0, s32 arg1) {
    f32 temp_f0;
    s32 temp_f16;
    s32 temp_s1;
    s32 var_s0;
    s32 var_s0_2;

    g_last_player_index = arg0;
    if (arg0 == 0) {
        var_s0 = 1;
    } else {
        var_s0 = arg0 + 2;
    }
    g_player_cams = allocate_memory(var_s0 * 0x180, 1, 1, 0);
    g_viewports = allocate_memory(var_s0 * 0x10, 1, 1, 0);
    if (g_last_player_index == 1) {
        temp_f0 = (f32) g_view_widths - 2.0f;
        temp_f16 = (s32) (temp_f0 * 0.8f);
        g_split_width_scale = (f32) (temp_f16 - (temp_f16 % 4)) / temp_f0;
    }
    level_setup_screen_projection(g_level_id);
    temp_s1 = g_last_player_index;
    var_s0_2 = 0;
    if (temp_s1 >= 0) {
        do {
            camera_record_setup(var_s0_2, temp_s1, 0x3FF, 0);
            var_s0_2 += 1;
        } while (g_last_player_index >= var_s0_2);
    }
    if (temp_s1 != 0) {
        camera_record_setup(var_s0_2, 0, 0x3FF, 0);
    }
    D_800BEA37 = 1;
    g_dl_buffers_reinit_req = 1;
    g_view_clear_black = 0;
    camera_set_screen_ortho(arg1);
}
// NON-MATCHING: 80% there
// void viewports_init(s32 arg0, s32 arg1) {
//     s32 phi_s0;
//     s32 i;
//
//     f32 temp_f0;
//     s32 temp_f16;
//
//     g_last_player_index = arg0;
//
//     if (arg0 == 0) {
//         phi_s0 = 1;
//     } else {
//         phi_s0 = arg0 + 2;
//     }
//     g_player_cams = allocate_memory((phi_s0 * 3) << 7, 1, 1, 0);
//     D_800BE62C = allocate_memory(phi_s0 * 16, 1, 1, 0);
//     if (g_last_player_index == 1) {
//         temp_f0 = D_800BE63C - 2.0f;
//         temp_f16 = temp_f0 * D_800968E0;
//         phi_s0 = temp_f16 & 3;
//         if ((temp_f16 < 0) && ((temp_f16 & 3) != 0)) {
//             phi_s0 -= 4;
//         }
//         D_800BE6B8 = (temp_f16 - phi_s0) / temp_f0;
//     }
//
//     level_setup_screen_projection(g_level_id);
//
//     for(i = 0; i <= g_last_player_index; i++) {
//         camera_record_setup(i, g_last_player_index, 1023, 0);
//     }
//     if (g_last_player_index != 0) {
//         camera_record_setup(i, 0, 1023, 0);
//     }
//
//     D_800BE617 = 1;
//     D_800BE614 = 1;
//     D_800BE635 = 0;
//     func_1510B070(arg1);
// }

/* was func_1501A39C */
void render_dl_buffers_init(void) {
    s32 i;
    Gfx *gfx;

    for (i = 0; i < 2; i++) {
        gfx = D_800BEDE8[i];
        gSPSegment(gfx++, 0, 0);
        gSPSegment(gfx++, 0, 0);
        gSPDisplayList(gfx++, g_dl_frame_init);
        gDPSetDepthImage(gfx++, g_zbuffer);
        gSPViewport(gfx++, &((struct_eu_BE628 *)g_player_cams)->unk40[i]);
        D_800BE9D8[i] = (s32)gfx;
    }
}
// NON-MATCHING: something along these lines
// extern Gfx* D_800BE9C8;
// extern s32 D_8002C930;
// Gfx *render_dl_buffers_init(void) {
//     s32 i;
//     Gfx *tmp = D_800BE9C8;
//     for (i = 0; i < 3; i++) {
//         gSPSegment(tmp++, 0x00, 0x00000000);
//         gSPSegment(tmp++, 0x00, 0x00000000);
//         gSPDisplayList(tmp++, D_8002C930);
//         gDPSetDepthImage(tmp++, D_800BE9C4);
//         gSPViewport(tmp++, g_player_cams + i + 0x40);
//     }
//     return tmp;
// }

/* was func_1501A490 */
s32 render_set_scissor(s32 arg0, s16 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    struct {
        f32 u30;
        f32 u34;
        f32 u38;
        f32 u3C;
    } sp;
    f32 temp_f0;
    f32 temp_f2;
    u8 *temp_s0;
    u8 *temp_v0;
    u8 *var_s0;

    (*(s32 *)((u8 *)arg0 + 0)) = 0xE7000000;
    (*(s32 *)((u8 *)arg0 + 4)) = 0;
    temp_s0 = arg0 + 8;
    if (arg1 == 0xFF) {
        (*(s32 *)((u8 *)temp_s0 + 0)) = 0xED008000;
        var_s0 = temp_s0 + 8;
        (*(s32 *)((u8 *)temp_s0 + 4)) = (s32) (((arg5 & 3) << 0x18) | (((s32) ((f32) (g_framebuffer_width - 2) * 4.0f) & 0xFFF) << 0xC) | ((s32) ((f32) g_framebuffer_height * 4.0f) & 0xFFF));
    } else {
        temp_v0 = g_player_cams + (arg1 * 0x180);
        sp.u3C = (*(f32 *)((u8 *)temp_v0 + 0x2C));
        sp.u38 = (*(f32 *)((u8 *)temp_v0 + 0x30));
        sp.u34 = (*(f32 *)((u8 *)temp_v0 + 0x24));
        if (arg4 != 0) {
            temp_f2 = (*(f32 *)((u8 *)temp_v0 + 0x28));
            temp_f0 = (f32) arg4;
            if (temp_f0 < temp_f2) {
                sp.u30 = temp_f0;
            } else {
                sp.u30 = temp_f2;
            }
        } else {
            sp.u30 = (*(f32 *)((u8 *)temp_v0 + 0x28));
        }
        screen_clamp_rect(&sp.u3C, &sp.u34, &sp.u38, &sp.u30);
        var_s0 = temp_s0 + 8;
        (*(s32 *)((u8 *)temp_s0 + 0)) = (s32) ((((s32) (sp.u3C * 4.0f) & 0xFFF) << 0xC) | 0xED000000 | ((s32) (sp.u34 * 4.0f) & 0xFFF));
        (*(s32 *)((u8 *)temp_s0 + 4)) = (s32) (((arg5 & 3) << 0x18) | (((s32) (sp.u38 * 4.0f) & 0xFFF) << 0xC) | ((s32) (sp.u30 * 4.0f) & 0xFFF));
    }
    return (s32) var_s0;
}
/* was func_1501A680 */
Gfx *render_set_color_image(Gfx *arg0) {
    gDPSetColorImage(arg0++, G_IM_FMT_RGBA, G_IM_SIZ_16b, g_framebuffer_width, g_framebuffers[g_dl_buf_index]);
    return arg0;
}

/* was func_1501A6CC */
Gfx *render_fill_rect_clamped(Gfx *arg0, s32 a, s32 b, s32 c, s32 d) {
    if (a < 3) {
        a = 2;
    }
    if (b <= 0) {
        b = 0;
    }
    if (c >= (g_framebuffer_width - 2)) {
        c = g_framebuffer_width - 2;
    }
    if (d >= g_framebuffer_height) {
        d = g_framebuffer_height;
    }

    gDPFillRectangle(arg0++, a, b, c, d);
    return arg0;
}

void func_150A7A00(f32 arg0, f32 arg1, s32 arg2, f32 arg3, f32 arg4, f32 arg5, f32* arg6, f32* arg7, f32* arg8, f32* arg9);
extern u8 g_cam_view_proj_mtx[]; /* was D_800DA130 */
void mtxf_transform_point_w(u8 *, f32, f32, f32, f32 *, f32 *, f32 *, f32 *);
/* world_to_screen: projects (x, y, z) with view `view`'s matrix g_cam_view_proj_mtx[view] (mtxf_transform_point_w) and maps it into
 * the camera record g_player_cams + view * 0x180: screen x = (half width +0xC + 5) * x / w + centre +0x34, screen
 * y = centre +0x38 - (half height +0x10 + 5) * y / w, depth = (z offset + z / w * z scale) * 32 from the
 * g_dl_buf_index entry (s16 +0x4C / +0x44). (EU address 0x1501A744; the source keeps the US name.) */
/* was func_1501A764 */
void camera_world_to_screen(s32 view, f32 x, f32 y, f32 z, f32 *sx, f32 *sy, f32 *sz) {
    f32 px;
    f32 py;
    f32 pz;
    f32 w;
    u8 *cam;
    u8 *zv;

    mtxf_transform_point_w(g_cam_view_proj_mtx + (s16)view * 64, x, y, z, &px, &py, &pz, &w);
    w = 1.0f / w;
    cam = (u8 *)g_player_cams + (s16)view * 0x180;
    *sx = (*(f32 *)(cam + 0xC) + 5.0f) * px * w + *(f32 *)(cam + 0x34);
    *sy = *(f32 *)(cam + 0x38) - (*(f32 *)(cam + 0x10) + 5.0f) * py * w;
    zv = (u8 *)g_player_cams + (s16)view * 0x180 + g_dl_buf_index * 16;
    *sz = (*(s16 *)(zv + 0x4C) + pz * w * *(s16 *)(zv + 0x44)) * 32.0f;
}
// void camera_world_to_screen(s16 arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4, f32 *arg5, f32 *arg6) {
//     f32 sp34;
//     f32 sp30;
//     f32 sp2C;
//     f32 sp28;
//     struct140 *temp_v0_2;
//
//     func_150A7A00(arg1, arg2, &D_800D9D10 + (arg0 << 6), arg1, arg2, arg3, &sp34, &sp30, &sp2C, &sp28);
//     sp28 = 1.0f / sp28;
//     // temp_v1 = arg0 * 0x180;
//     temp_v0_2 = &g_player_cams[arg0];
//     // sp28 = temp_f8;
//     *arg4 = (((temp_v0_2->unkC + 5.0f) * sp34 * sp28) + temp_v0_2->unk34);
//     temp_v0_2 = &g_player_cams [arg0];
//     *arg5 = (temp_v0_2->unk38 - ((temp_v0_2->unk10 + 5.0f) * sp30 * sp28));
//     temp_v0_2 = &g_player_cams[arg0].unk50[g_dl_buf_index];  // (g_dl_buf_index * 0x10);
//     *arg6 = (((f32) temp_v0_2->unk4C + (sp2C * sp28 * (f32) temp_v0_2->unk44)) * 32.0f);
// }

/* Per-player camera record g_player_cams + p * 0x180 for a screen split into n + 1 views: viewport w/h (+4/+8, from
 * g_screen_width/g_screen_height[n], minus 2 when split; the 2-player width also * g_split_width_scale), +0x64 aspect table
 * g_view_aspect_table[n], +0x68 = 2, base fov +0x6C (g_view_fov_default, 2 players: g_view_fov_2p * g_split_width_scale) / +0x70 = 50, current fov
 * +0x74/+0x78, +0x60 w/h, half size +0xC/+0x10, centre +0x34/+0x38 (g_view_split_offsets table: 20 bytes per n, 4 per player),
 * clip rect +0x2C/+0x24/+0x30/+0x28, scale +0x14/+0x18 (camera_setup_perspective when flag), tan factors +0x7C/+0x80, the Vp
 * at g_viewports + p * 16 (scale (w + 10) * 2, depth zmax >> 1, translate centre * 4) copied into both frame
 * buffers' Vp at +0x40, +0x84 = 1.0, +1 = camera_rect_on_screen(p); clip rect via screen_clamp_rect, camera_projection_set_fov(p, 0, 0, 1). */
#define CAMREC(o) (*(f32 *)((u8 *)g_player_cams + p * 0x180 + (o)))
/* was func_1501A8C0 */
s32 camera_record_setup(s32 p, s32 n, s32 zmax, s32 flag) {
    f32 sw;
    f32 sh;
    f32 w;
    f32 h;
    f32 a;
    f32 s;
    s16 *ctr;
    s16 *vp;
    s32 *src;
    s32 *dst;
    u8 *rec;

    CAMREC(4) = (&g_screen_width)[n];
    CAMREC(8) = (&g_screen_height)[n];
    if (n != 0) {
        CAMREC(4) = CAMREC(4) - 2.0f;
        CAMREC(8) = CAMREC(8) - 2.0f;
    }
    CAMREC(0x64) = g_view_aspect_table[n];
    CAMREC(0x68) = 2.0f;
    if (n == 1) {
        CAMREC(4) = CAMREC(4) * g_split_width_scale;
        CAMREC(0x6C) = g_view_fov_2p * g_split_width_scale;
        CAMREC(0x70) = 50.0f;
    } else {
        CAMREC(0x6C) = g_view_fov_default;
        CAMREC(0x70) = 50.0f;
    }
    CAMREC(0x74) = CAMREC(0x6C);
    CAMREC(0x78) = CAMREC(0x70);
    CAMREC(0x60) = CAMREC(4) / CAMREC(8);
    CAMREC(0xC) = CAMREC(4) * 0.5f;
    CAMREC(0x10) = CAMREC(8) * 0.5f;
    ctr = (s16 *)((u8 *)g_view_split_offsets + n * 20 + p * 4);
    CAMREC(0x34) = ctr[0];
    CAMREC(0x38) = ctr[1];
    CAMREC(0x2C) = CAMREC(0x34) - CAMREC(0xC);
    CAMREC(0x24) = CAMREC(0x38) - CAMREC(0x10);
    CAMREC(0x30) = CAMREC(0xC) + CAMREC(0x34);
    CAMREC(0x28) = CAMREC(0x10) + CAMREC(0x38);
    if ((s16)flag != 0) {
        camera_setup_perspective(p, n);
    } else {
        sw = (&g_screen_width)[0];
        sh = (&g_screen_height)[0];
        w = CAMREC(4);
        h = CAMREC(8);
        CAMREC(0x14) = (w / sw) * ((sw / sh) / (w / h));
        CAMREC(0x18) = CAMREC(8) / (f32)(&g_screen_height)[0];
    }
    a = CAMREC(0x6C) * 0.5f * g_cam_fov_x_deg_to_rad;
    s = sinf(a);
    CAMREC(0x7C) = s / (CAMREC(0xC) * cosf(a));
    a = CAMREC(0x70) * 0.5f * g_cam_fov_y_deg_to_rad;
    s = sinf(a);
    CAMREC(0x80) = s / (CAMREC(0x10) * cosf(a));
    vp = (s16 *)(g_viewports + p * 16);
    w = CAMREC(4) + 10.0f;
    vp[0] = w + w;
    vp = (s16 *)(g_viewports + p * 16);
    h = CAMREC(8) + 10.0f;
    vp[1] = h + h;
    ((s16 *)(g_viewports + p * 16))[2] = zmax >> 1;
    ((s16 *)(g_viewports + p * 16))[3] = 0;
    ((s16 *)(g_viewports + p * 16))[4] = CAMREC(0x34) * 4.0f;
    ((s16 *)(g_viewports + p * 16))[5] = CAMREC(0x38) * 4.0f;
    ((s16 *)(g_viewports + p * 16))[6] = zmax >> 1;
    ((s16 *)(g_viewports + p * 16))[7] = 0;
    src = (s32 *)(g_viewports + p * 16);
    dst = (s32 *)((u8 *)g_player_cams + p * 0x180 + g_dl_buf_index * 16 + 0x40);
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
    rec = (u8 *)g_player_cams + p * 0x180;
    src = (s32 *)(rec + g_dl_buf_index * 16 + 0x40);
    dst = (s32 *)(rec + (g_dl_buf_index == 0) * 16 + 0x40);
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
    CAMREC(0x84) = 1.0f;
    *((u8 *)g_player_cams + p * 0x180 + 1) = camera_rect_on_screen(p);
    rec = (u8 *)g_player_cams + p * 0x180;
    screen_clamp_rect((f32 *)(rec + 0x2C), (f32 *)(rec + 0x24), (f32 *)(rec + 0x30), (f32 *)(rec + 0x28));
    camera_projection_set_fov(p, 0.0f, 0.0f, CAMREC(0x84));
    g_view_player_order[p] = p;
}
#undef CAMREC
/* was func_1501AE94 */
s32 camera_rect_on_screen(s32 arg0) {
    f32 w = (f32)g_framebuffer_width - 2.0f;
    f32 h = g_framebuffer_height;
    struct_eu_BE628 *e = &((struct_eu_BE628 *)g_player_cams)[arg0];

    if (e->unk2C < 2.0f || w < e->unk30) {
        return 0;
    }
    if (e->unk24 < 0.0f || h < e->unk28) {
        return 0;
    }
    return 1;
}

/* was func_1501AF44 */
void screen_clamp_rect(f32 *x0, f32 *y0, f32 *x1, f32 *y1) {
    f32 tmp;

    if (*x0 < 2.0f) {
        *x0 = 2.0f;
    } else {
        tmp = ((f32)g_framebuffer_width - 2.0f < *x0) ? (f32)g_framebuffer_width - 2.0f : *x0;
        *x0 = tmp;
    }
    if (*x1 < 2.0f) {
        *x1 = 2.0f;
    } else {
        tmp = ((f32)g_framebuffer_width - 2.0f < *x1) ? (f32)g_framebuffer_width - 2.0f : *x1;
        *x1 = tmp;
    }
    if (*y0 < 0.0f) {
        *y0 = 0.0f;
    } else {
        tmp = ((f32)g_framebuffer_height < *y0) ? (f32)g_framebuffer_height : *y0;
        *y0 = tmp;
    }
    if (*y1 < 0.0f) {
        *y1 = 0.0f;
    } else {
        tmp = ((f32)g_framebuffer_height < *y1) ? (f32)g_framebuffer_height : *y1;
        *y1 = tmp;
    }
}

extern f32 g_cam_persp_deg_to_rad; /* was D_80096CA4 */
extern f32 g_cam_persp_rad_to_deg; /* was D_80096CA8 */
void camera_projection_update(s32, f32, f32, f32, f32);
extern s32 g_screen_width; /* was D_800BEA58 */
extern s32 g_screen_height; /* was D_800BEA70 */

/* was func_1501B0A0 */
void camera_setup_perspective(s32 arg0, s32 arg1) {
    u8 *temp_v0;
    s32 temp_t8;
    s32 temp_t6;
    s32 temp_t4;
    f32 temp_f12;
    s32 sp24;
    s32 sp28;
    f32 sp2C;
    f32 sp34;
    f32 sp38;
    f32 sp44;
    f32 sp48;
    f32 sp4C;

    temp_t6 = arg0 * 0x180;
    temp_v0 = g_player_cams + temp_t6;
    sp28 = temp_t6;
    temp_f12 = (*(f32 *)((u8 *)temp_v0 + 0x6C)) * g_cam_persp_deg_to_rad;
    sp4C = temp_f12;
    sp48 = (*(f32 *)((u8 *)temp_v0 + 0x70)) * g_cam_persp_deg_to_rad;
    sp2C = sinf(temp_f12);
    sp44 = sp2C / cosf(sp4C);
    sp2C = sinf(sp48);
    temp_t8 = arg1 * 4;
    sp38 = (f32) *(((s32 *)((u8 *)&g_screen_height + temp_t8))) / (2.0f * (sp2C / cosf(sp48)));
    temp_t4 = arg1 * 0x180;
    sp34 = (math_atan2f((*(f32 *)((u8 *)((g_player_cams + sp28)) + 0xC)), (f32) *(((s32 *)((u8 *)&g_screen_width + temp_t8))) / (2.0f * sp44)) * g_cam_persp_rad_to_deg) - (*(f32 *)((u8 *)((g_player_cams + temp_t4)) + 0x6C));
    sp24 = temp_t4;
    camera_projection_update(arg0, sp34, (math_atan2f((*(f32 *)((u8 *)((g_player_cams + sp28)) + 0x10)), sp38) * g_cam_persp_rad_to_deg) - (*(f32 *)((u8 *)((g_player_cams + sp24)) + 0x70)), 1.0f, 0.0f);
}
/* was func_1501B22C */
void camera_compute_frustum_planes(s32 arg0) {
    f32 sp34;
    f32 sp28;
    f32 sp24;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f12_3;
    f32 temp_f2;
    f32 temp_f2_2;
    u8 *temp_s0;

    temp_s0 = (arg0 * 0x180) + g_player_cams;
    temp_f12 = -((*(f32 *)((u8 *)temp_s0 + 0x74)) * 0.5f) * 0.017453292f;
    sp28 = (*(f32 *)((u8 *)temp_s0 + 0x78)) * 0.5f;
    sp24 = temp_f12;
    sp34 = cosf(temp_f12);
    temp_f0 = sinf(temp_f12);
    (*(f32 *)((u8 *)temp_s0 + 0x9C)) = temp_f0;
    temp_f2 = -sp34;
    (*(f32 *)((u8 *)temp_s0 + 0x90)) = temp_f0;
    (*(f32 *)((u8 *)temp_s0 + 0x94)) = temp_f2;
    (*(f32 *)((u8 *)temp_s0 + 0x88)) = (f32) -temp_f2;
    (*(f32 *)((u8 *)temp_s0 + 0x98)) = 0.0f;
    (*(f32 *)((u8 *)temp_s0 + 0x8C)) = 0.0f;
    temp_f12_2 = sp28 * 0.017453292f;
    sp24 = temp_f12_2;
    sp34 = cosf(temp_f12_2);
    temp_f12_3 = -sinf(temp_f12_2);
    (*(f32 *)((u8 *)temp_s0 + 0xA0)) = 0.0f;
    (*(f32 *)((u8 *)temp_s0 + 0xA8)) = temp_f12_3;
    (*(f32 *)((u8 *)temp_s0 + 0xB4)) = temp_f12_3;
    temp_f2_2 = -sp34;
    (*(f32 *)((u8 *)temp_s0 + 0xAC)) = 0.0f;
    (*(f32 *)((u8 *)temp_s0 + 0xA4)) = temp_f2_2;
    (*(f32 *)((u8 *)temp_s0 + 0xB0)) = (f32) -temp_f2_2;
}
// JUSTREG: I think?
// void camera_compute_frustum_planes(s32 arg0) {
//     f32 tmp0;
//     f32 tmp1;
//     f32 tmp2;
//     f32 tmp3;
//     f32 tmp4;
//     f32 tmp5;
//     f32 tmp6;
//     f32 tmp7;
//
//     struct259 *temp_s0;
//
//     temp_s0 = g_player_cams + (arg0 * 0x180);
//     tmp0 = temp_s0->unk74 * 0.5f;
//     tmp7 = -tmp0;
//     tmp5 = temp_s0->unk78 * 0.5f;
//     tmp7 *= g_debris_linked_zone_pos;
//     tmp3 = cosf(tmp7);
//     tmp7 = sinf(tmp7);
//     temp_s0->unk9C = tmp7;
//     temp_s0->unk90 = tmp7;
//     tmp3 = -tmp3;
//     temp_s0->unk88 = -tmp3;
//     temp_s0->unk94 = tmp3;
//     temp_s0->unk98 = 0.0f;
//     temp_s0->unk8C = 0.0f;
//     tmp6 = tmp5 * D_80096904;
//     tmp2 = cosf(tmp6);
//     tmp0 = sinf(tmp6);
//     tmp4 = -tmp2;
//     tmp0 = -tmp0;
//     temp_s0->unkA0 = 0.0f;
//     temp_s0->unkB0 = -tmp4;
//     temp_s0->unkA8 = tmp0;
//     temp_s0->unkB4 = tmp0;
//     temp_s0->unkAC = 0.0f;
//     temp_s0->unkA4 = tmp4;
// }
