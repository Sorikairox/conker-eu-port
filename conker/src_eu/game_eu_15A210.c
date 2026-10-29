#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void mtx_translate_fixed(Mtx *mtx, f32 x, f32 y, f32 z);
void math_spring_approach(f32 *, f32, f32 *, f32, f32, f32);
void mtx_look_at_reflect(Mtx *arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 argA);
void vec3_dir_to(struct17 *arg0, struct17 *arg1, struct17 *arg2);
f32 vec3_heading_deg(struct17 *arg0);
f32 math_atan2f(f32 arg0, f32 arg1);
void mtxf_rotate_xyz_deg(f32 mtx[4][4], f32 arg1, f32 arg2, f32 arg3);
void camera_calc_pitch(struct108 *arg0);
void camera_sync_angles(struct108 *arg0);
void mtx_rotate_xyz_deg_fixed(Mtx *m, f32 rx, f32 ry, f32 rz);
void camera_wobble_apply(u8 *arg0);
void camera_track_noop(s32 arg0);
void camera_track_update(u8 *arg0);
extern Mtx *g_view_mtx_bufs[];         /* per DL buffer: the per-player view matrices (0x40 each); was D_800DC6D0 */
extern u8 g_dl_buf_index;             /* current DL buffer; was D_800BE9C0 */
extern u8 g_cam_lookat_bufs[];           /* per DL buffer: LookAt (0x20); was D_800D9FB0 */
extern s32 g_camera_track_data[];         /* camera shake tables (camera_shake_tracks_load): 6 floats (0x18) per step; was D_800DC6B0 */
/* g_camera_view_offsets (u8[]): per player 6 floats (0x18): extra translation (0..2) and rotation (3..5) */
/* g_camera_shake_states (u8[][0x68]): per player, +0x54 translation, +0x60 roll (the asm reads it as D_800DC750) */

#define CAM_W(o) (*(s32 *)(p + (o)))
#define CAM_H(o) (*(s16 *)(p + (o)))
#define CAM_F(o) (*(f32 *)(p + (o)))
#define CAM_OBJ() (*(u8 **)(p + 0x3D4))
#define CAM_REC() (*(u8 **)(p + 0x3D0))
#define CAM_MTX() ((Mtx *)((u8 *)g_view_mtx_bufs[g_dl_buf_index] + p[0x23D] * 0x40))

/* Gameplay view matrix of one camera controller (camera_update_all's in-game branch): ease the orbit distances
 * (0x194 / 0x18C toward 0x198 / 0x190), pick eye (0x2F8) / target (0x2BC) (offset by the orbit around the
 * yaw 0x3A0 unless the object (0x3D4) has its own view, +0x197), look-at matrix into g_view_mtx_bufs[buffer][player]
 * with the LookAt g_cam_lookat_bufs[buffer], then post-rotations: shake (0x854..0x868, decayed by 0.08 or driven by
 * g_camera_track_data), roll 0x5EC, per-player g_camera_view_offsets rotation / translation. */
/* was func_1512C490 */
void camera_build_view_matrix(struct108 *arg0) {
    u8 *p = (u8 *)arg0;
    f32 eye[3];       /* sp+0xEC */
    f32 at[3];        /* sp+0xE0 */
    f32 dir[3];       /* sp+0xB8 */
    f32 rot[4][4];    /* sp+0x64 */
    f32 ox, oy, oz;   /* sp+0xA4..0xAC */
    Mtx m158;
    Mtx m118;
    f32 scale;        /* sp+0xC4 */
    f32 dist, height, offX, offZ, s, c;
    f32 yaw;
    f32 k, a, b;
    u8 *obj;
    u8 *v;
    f32 *d;
    s32 fl;

    scale = *(f32 *)((u8 *)g_player_cams + p[0x23D] * 0x180 + 0x84);
    scale = (1.0f - scale) * 0.5f + scale;
    if (CAM_OBJ()[0x120] != 0) {
        CAM_F(0x198) = 0.0f;
        CAM_F(0x190) = 0.0f;
        CAM_F(0x74C) = 0.0f;
        CAM_F(0x754) = 0.0f;
    }
    if (p[0x23C] != 0) {
        CAM_F(0x7D0) = 0.0f;
        CAM_F(0x7D4) = 0.0f;
        CAM_F(0x194) = CAM_F(0x198);
        CAM_F(0x18C) = CAM_F(0x190);
    } else if (CAM_W(0x2C) == 0x100 || p[0x23E] != 0) {
        math_spring_approach((f32 *)(p + 0x194), CAM_F(0x198), (f32 *)(p + 0x7D0), 4.0f, 6.0f, CAM_F(0x7B4));
        math_spring_approach((f32 *)(p + 0x18C), CAM_F(0x190), (f32 *)(p + 0x7D4), 4.0f, 6.0f, CAM_F(0x7B4));
    } else {
        math_spring_approach((f32 *)(p + 0x194), CAM_F(0x198), (f32 *)(p + 0x7D0), 0.75f, 1.1f, CAM_F(0x7B4));
        math_spring_approach((f32 *)(p + 0x18C), CAM_F(0x190), (f32 *)(p + 0x7D4), 0.75f, 1.1f, CAM_F(0x7B4));
    }
    CAM_W(0x2E0) = CAM_W(0x2BC);
    CAM_W(0x2E4) = CAM_W(0x2C0);
    CAM_W(0x2E8) = CAM_W(0x2C4);
    CAM_W(0x2EC) = CAM_W(0x2F8);
    CAM_W(0x2F0) = CAM_W(0x2FC);
    CAM_W(0x2F4) = CAM_W(0x300);
    fl = CAM_W(0x2C);
    if ((fl & 0x40000) || (fl & 0x20)) {
        eye[0] = CAM_F(0x2F8);
        eye[1] = CAM_F(0x2FC);
        eye[2] = CAM_F(0x300);
        at[0] = CAM_F(0x2A4);
        at[1] = CAM_F(0x2A8);
        at[2] = CAM_F(0x2AC);
    } else if (CAM_OBJ()[0x197] != 0) {
        eye[0] = CAM_F(0x2F8);
        eye[1] = CAM_F(0x2FC);
        eye[2] = CAM_F(0x300);
        at[0] = CAM_F(0x2BC);
        at[1] = CAM_F(0x2C0);
        at[2] = CAM_F(0x2C4);
        camera_calc_pitch(arg0);
        camera_sync_angles(arg0);
    } else {
        dist = CAM_F(0x194);
        height = CAM_F(0x18C);
        offX = CAM_F(0x74C);
        offZ = CAM_F(0x754);
        s = sinf(CAM_F(0x3A0) - 1.5707964f) * dist;
        c = cosf(CAM_F(0x3A0) - 1.5707964f) * dist;
        eye[0] = CAM_F(0x2F8) + offX + s;
        eye[1] = CAM_F(0x2FC) + height;
        eye[2] = CAM_F(0x300) + offZ + c;
        at[0] = CAM_F(0x2BC) + offX + s;
        at[1] = CAM_F(0x2C0) + height;
        at[2] = CAM_F(0x2C4) + offZ + c;
        CAM_F(0x2F8) = eye[0];
        CAM_F(0x2FC) = eye[1];
        CAM_F(0x300) = eye[2];
        CAM_F(0x2BC) = at[0];
        CAM_F(0x2C0) = at[1];
        CAM_F(0x2C4) = at[2];
        camera_calc_pitch(arg0);
        camera_sync_angles(arg0);
    }
    vec3_dir_to((struct17 *)eye, (struct17 *)at, (struct17 *)dir);
    obj = CAM_OBJ();
    *(f32 *)(obj + 0x148) = at[0];
    *(f32 *)(obj + 0x14C) = at[1];
    *(f32 *)(obj + 0x150) = at[2];
    obj = CAM_OBJ();
    *(f32 *)(obj + 0x13C) = eye[0];
    *(f32 *)(obj + 0x140) = eye[1];
    *(f32 *)(obj + 0x144) = eye[2];
    obj = CAM_OBJ();
    *(f32 *)(obj + 0x130) = dir[0];
    *(f32 *)(obj + 0x134) = dir[1];
    *(f32 *)(obj + 0x138) = dir[2];
    mtx_look_at_reflect(CAM_MTX(), (s32)(g_cam_lookat_bufs + g_dl_buf_index * 0x20), eye[0], eye[1], eye[2], at[0], at[1], at[2],
                  0.0f, 1.0f, 0.0f);

    fl = CAM_W(0x2C);
    if (fl & 0x80000) {
        camera_wobble_apply(p);
        camera_track_noop((s32)p);
        return;
    }
    if (fl == 0x40000) {
        mtx_rotate_xyz_deg_fixed(&m158, 0.0f, 0.0f, CAM_F(0x5EC));
        guMtxCatL(CAM_MTX(), &m158, CAM_MTX());
        camera_wobble_apply(p);
        return;
    }

    /* shake */
    if (CAM_OBJ()[0x197] != 0) {
        if (p[0x84D] == 2) {
            d = (f32 *)(g_camera_track_data[CAM_W(0x850)] + p[0x84E] * 0x18);
            CAM_F(0x854) += d[3];
            CAM_F(0x858) += d[4];
            CAM_F(0x85C) += d[5];
            CAM_F(0x860) += d[0];
            CAM_F(0x864) += d[1];
            CAM_F(0x868) += d[2];
        } else {
            k = 0.08f; /* D_800A3A90 */
            CAM_F(0x854) -= CAM_F(0x854) * k;
            CAM_F(0x858) -= CAM_F(0x858) * k;
            CAM_F(0x85C) -= CAM_F(0x85C) * k;
            CAM_F(0x860) -= CAM_F(0x860) * k;
            CAM_F(0x864) -= CAM_F(0x864) * k;
            CAM_F(0x868) -= CAM_F(0x868) * k;
        }
        camera_track_update(p);
    } else {
        k = 0.08f; /* D_800A3A94 */
        CAM_F(0x854) -= CAM_F(0x854) * k;
        CAM_F(0x858) -= CAM_F(0x858) * k;
        CAM_F(0x85C) -= CAM_F(0x85C) * k;
        CAM_F(0x860) -= CAM_F(0x860) * k;
        CAM_F(0x864) -= CAM_F(0x864) * k;
        CAM_F(0x868) -= CAM_F(0x868) * k;
    }
    a = CAM_F(0x854) * scale;
    CAM_F(0x5EC) = CAM_F(0x5EC) + a;
    mtx_rotate_xyz_deg_fixed(&m158, -CAM_F(0x858) * scale, CAM_F(0x85C) * scale, a);
    guMtxCatL(CAM_MTX(), &m158, CAM_MTX());

    /* the object's view direction follows the shake */
    if (CAM_OBJ() != NULL) {
        yaw = vec3_heading_deg((struct17 *)(CAM_OBJ() + 0x130)) - 180.0f;
        obj = CAM_OBJ();
        a = *(f32 *)(obj + 0x130);
        b = *(f32 *)(obj + 0x138);
        a = math_atan2f(*(f32 *)(obj + 0x134), sqrtf(a * a + b * b));
        mtxf_rotate_xyz_deg(rot, -a * 57.2957764f - CAM_F(0x858) * scale, yaw - CAM_F(0x85C) * scale, 0.0f);
        guMtxXFMF(rot, 0.0f, 0.0f, 1.0f, &ox, &oy, &oz);
        *(f32 *)(CAM_OBJ() + 0x130) = ox;
        *(f32 *)(CAM_OBJ() + 0x134) = oy;
        *(f32 *)(CAM_OBJ() + 0x138) = oz;
    }
    if (CAM_OBJ()[0x197] != 0) {
        d = (f32 *)(g_camera_view_offsets + p[0x23D] * 0x18);
        mtx_rotate_xyz_deg_fixed(&m158, d[3], d[4], d[5]);
        d = (f32 *)(g_camera_view_offsets + p[0x23D] * 0x18);
        mtx_translate_fixed(&m118, d[0], d[1], d[2]);
        guMtxCatL(&m158, &m118, &m158);
        guMtxCatL(CAM_MTX(), &m158, CAM_MTX());
        return;
    }

    /* roll */
    fl = CAM_W(0x2C);
    if (((fl & 0x80) || CAM_REC()[0x102] != 0) && CAM_H(0x298) != 0) {
        a = *(f32 *)(CAM_REC() + 0xC4) * 0.25f;
    } else if ((CAM_W(0x5F0) & 0x80) && fl != 0x40) {
        a = *(f32 *)(CAM_REC() + 0xC4) * 0.5f;
    } else {
        a = 0.0f;
    }
    if (!(fl & 0x40000)) {
        if ((CAM_W(0x5F0) & 0x80) || CAM_REC()[0x102] != 0) {
            math_spring_approach((f32 *)(p + 0x5EC), a, (f32 *)(p + 0x264), 2.0f, 4.0f, CAM_F(0x7B4));
        } else {
            math_spring_approach((f32 *)(p + 0x5EC), a, (f32 *)(p + 0x264), 4.0f, 8.0f, CAM_F(0x7B4));
        }
    }
    camera_track_noop((s32)p);
    fl = CAM_W(0x2C);
    if (fl != 0x8000) {
        if (fl == 1) {
            CAM_F(0x388) = CAM_F(0x388) - CAM_F(0x5D0);
            CAM_F(0x398) = CAM_F(0x388) * 0.017453292f; /* D_800A3A9C */
        }
        d = (f32 *)(g_camera_view_offsets + p[0x23D] * 0x18);
        mtx_rotate_xyz_deg_fixed(&m158, d[3] + (CAM_F(0x5D0) + CAM_F(0x3A8) + CAM_F(0x38C)), d[4] + CAM_F(0x5E8),
                      d[5] + (CAM_F(0x5EC) + *(f32 *)&g_camera_shake_states[p[0x23D]][0x60] * 0.5f));
        if (CAM_W(0x2C) == 0x40000) {
            mtx_rotate_xyz_deg_fixed(&m158, 0.0f, 0.0f, CAM_F(0x5EC));
        }
    }
    guMtxCatL(CAM_MTX(), &m158, CAM_MTX());
    camera_wobble_apply(p);
    if (CAM_W(0x2C) & 0x40000) {
        return;
    }
    d = (f32 *)(g_camera_view_offsets + p[0x23D] * 0x18);
    v = g_camera_shake_states[p[0x23D]];
    mtx_translate_fixed(&m118, d[0] + *(f32 *)(v + 0x54), d[1] + *(f32 *)(v + 0x58), d[2] + *(f32 *)(v + 0x5C));
    guMtxCatL(CAM_MTX(), &m118, CAM_MTX());
}
#undef CAM_W
#undef CAM_H
#undef CAM_F
#undef CAM_OBJ
#undef CAM_REC
#undef CAM_MTX
void math_spring_approach(f32 *, f32, f32 *, f32, f32, f32);
extern Mtx *g_view_mtx_bufs[]; /* was D_800DC6D0 */

/* camera_wobble_apply: stretches the view matrix by (1 + 2a + 2a sin phase, 1 + a + a cos phase) so the picture
 * breathes. Target amplitude 0.003 in the title menu camera (mode +0x2C 0x80000), 0.04 / 0.03 under water (+0x5F0
 * bit 0, eye below the water level) and for the drunk sway (+0x5F0 bit 3, not in cutscene mode 0x40000); the phase
 * +0x7B0 advances 2.5 degrees per tick, the amplitude +0x7DC eases to the target (instantly when +0x23C
 * is set or +0x5F0 bit 2). PORT option PORT_OPT_NO_DRUNK_FX (P331): only the under-water wobble is kept. */
/* was func_1512D5E0 */
void camera_wobble_apply(u8 *cam /* was arg0 */) {
    Mtx m;
    f32 mf[4][4];
    f32 k;
    s32 drunk = (*(s32 *)(cam + 0x2C) & 0x80000) || (*(s32 *)(cam + 0x2C) != 0x40000 && (*(s32 *)(cam + 0x5F0) & 8));

#ifdef PORT
    if (port_option(PORT_OPT_NO_DRUNK_FX)) {
        drunk = FALSE;
    }
#endif
    if ((*(s32 *)(cam + 0x2C) & 0x80000)) {
        k = 0.003f;
    } else if (*(s16 *)(cam + 0x298) != 0) {
        k = 0.04f;
    } else {
        k = 0.03f;
    }
    if (drunk || (*(s32 *)(cam + 0x5F0) & 1)) {
        *(f32 *)(cam + 0x7B0) += 0.04363323f * g_frame_ticks;
        if (*(f32 *)(cam + 0x7B0) > 3.1415927f) {
            *(f32 *)(cam + 0x7B0) -= 6.2831855f;
        }
    } else {
        k = 0.0f;
    }
    if (cam[0x23C] != 0 || (*(s32 *)(cam + 0x5F0) & 4)) {
        *(f32 *)(cam + 0x7DC) = k;
    } else {
        math_spring_approach((f32 *)(cam + 0x7DC), k, (f32 *)(cam + 0x7D8), 0.2f, 0.4f, *(f32 *)(cam + 0x7B4));
    }
    guMtxIdentF(mf);
    mf[0][0] = 2.0f * *(f32 *)(cam + 0x7DC) + 2.0f * (*(f32 *)(cam + 0x7DC) * fast_sinf(*(f32 *)(cam + 0x7B0))) + 1.0f;
    mf[1][1] = *(f32 *)(cam + 0x7DC) + *(f32 *)(cam + 0x7DC) * fast_cosf(*(f32 *)(cam + 0x7B0)) + 1.0f;
    guMtxF2L(mf, &m);
    guMtxCatL(cam[0x23D] + g_view_mtx_bufs[g_dl_buf_index], &m, cam[0x23D] + g_view_mtx_bufs[g_dl_buf_index]);
}

s32 asset_load(u32 *, s32, s32, s32);
extern s32 g_camera_track_data[]; /* was D_800DC6B0 */
extern s32 g_camera_track_lengths[]; /* was D_800DC6C0 */
/* was func_1512D7A8 */
void camera_shake_tracks_load(void) {
    u32 sp3C;
    s32 i;

    for (i = 0; i < 4; i++) {
        g_camera_track_data[i] = asset_load(&sp3C, 2, 0x1B, i);
        g_camera_track_lengths[i] = sp3C / 24;
    }
}

/* was func_1512D854 */
void camera_track_start(u8 *arg0, s32 arg1) {
    *(s32 *)(arg0 + 0x850) = arg1;
    arg0[0x84D] = 1;
}

extern s32 g_camera_track_lengths[]; /* was D_800DC6C0 */
/* was func_1512D868 */
void camera_track_update(u8 *arg0) {
    switch (arg0[0x84D]) {
    case 1:
        arg0[0x84E] = 0;
        arg0[0x84D] = 2;
        break;
    case 2:
        arg0[0x84E] += g_frame_ticks;
        if (arg0[0x84E] >= g_camera_track_lengths[*(s32 *)(arg0 + 0x850)]) {
            arg0[0x84D] = 0;
        }
        break;
    }
}

/* was func_1512D8D8 */
void camera_track_noop(s32 arg0) {
}

#ifdef PORT
/* P348 option "Photo mode" (port/ultra/pc_photo.c): the game side of the photo camera. Both functions run only while
 * photo mode is on: photo_game_camera when it starts (it only reads), photo_camera_apply inside the photo frames, whose
 * every change to game memory is undone by pc_photo.c's snapshot restore. */
extern f32 g_view_mtxf[][4][4];   /* per player: the view matrix as floats (camera_matrices_refresh_all); was D_800DA030 */
extern f32 g_camera_fov_extra;    /* was D_800C3A6C */
extern u8 g_game_frame_state;     /* was D_800BEA35 */
extern s16 g_scene_render_suspend; /* was D_80084810 */
void camera_projection_update(s32 player, f32 fovX, f32 fovY, f32 scale, f32 width);
void camera_matrices_refresh_all(void);

/* The start pose: player 1's view on screen, taken from the view matrix itself (g_view_mtxf[0], refreshed every frame),
 * so it is right for every camera (follow, cutscene, look / aim, fixed). out: eye (0..2), forward direction (3..5),
 * field of view x / y (6, 7: camera record +0x74 / +0x78, degrees). The matrix is a guLookAt (row vectors): rows 0..2
 * of columns 0..2 are the right / up / -forward axes, row 3 is -(eye . axis). Returns 1, or minus a mask of what rules
 * a photo out (1 split screen, 2 paused, 4 pause menu open, 8 mode change, 0x10 scene drawing suspended, 0x20 / 0x40
 * cameras / view matrices not set up). */
s32 photo_game_camera(f32 *out) {
    f32 (*m)[4] = g_view_mtxf[0];
    s32 j;

    s32 why = (g_last_player_index != 0) | (g_game_paused != 0) << 1 | (g_pause_open != 0) << 2 | (g_game_frame_state != 0) << 3 |
              (g_scene_render_suspend != 0) << 4 | (g_player_views == NULL || g_player_cams == 0) << 5 |
              (g_view_mtx_bufs[0] == NULL || g_view_mtx_bufs[1] == NULL) << 6;

    if (why != 0) {
        return -why;
    }
    for (j = 0; j < 3; j++) {
        out[j] = -(m[3][0] * m[j][0] + m[3][1] * m[j][1] + m[3][2] * m[j][2]);
        out[3 + j] = -m[j][2];
    }
    out[6] = *(f32 *)((u8 *)g_player_cams + 0x74);
    out[7] = *(f32 *)((u8 *)g_player_cams + 0x78);
    return 1;
}

/* Called at the start of world_update and after camera_update_all in a photo frame: the photo camera replaces player
 * 1's view in both DL buffers' view matrices (look-at with the reflection LookAt, as camera_build_view_matrix makes it,
 * then the roll about the view axis), the eye / target / direction the camera record keeps for the rest of the frame
 * (+0x3D4 record: +0x13C eye, +0x148 target, +0x130 direction), and with a zoom the field of view of the projection.
 * camera_matrices_refresh_all then derives the float view, view-projection and frustum planes from it, so the object
 * visibility test, the level triangle culling and the draw all use the photo camera. */
void photo_camera_apply(void) {
    f32 eye[3];
    f32 at[3];
    f32 dir[3];
    f32 fov[2];
    f32 roll;
    Mtx roll_mtx;
    Mtx *view;
    u8 *p = (u8 *)g_player_views;   /* player 1's camera controller */
    u8 *rec = (u8 *)g_player_cams;  /* player 1's camera record (projection) */
    u8 *obj;
    s32 buf;

    if (!port_photo_camera(eye, at, &roll, fov)) {
        return;
    }
    for (buf = 0; buf < 2; buf++) {
        view = (Mtx *)((u8 *)g_view_mtx_bufs[buf] + p[0x23D] * 0x40);
        mtx_look_at_reflect(view, (s32)(g_cam_lookat_bufs + buf * 0x20), eye[0], eye[1], eye[2], at[0], at[1], at[2], 0.0f, 1.0f, 0.0f);
        if (roll != 0.0f) {
            mtx_rotate_xyz_deg_fixed(&roll_mtx, 0.0f, 0.0f, roll);
            guMtxCatL(view, &roll_mtx, view);
        }
    }
    obj = *(u8 **)(p + 0x3D4);
    if (obj != NULL) {
        vec3_dir_to((struct17 *)eye, (struct17 *)at, (struct17 *)dir);
        *(f32 *)(obj + 0x13C) = eye[0];
        *(f32 *)(obj + 0x140) = eye[1];
        *(f32 *)(obj + 0x144) = eye[2];
        *(f32 *)(obj + 0x148) = at[0];
        *(f32 *)(obj + 0x14C) = at[1];
        *(f32 *)(obj + 0x150) = at[2];
        *(f32 *)(obj + 0x130) = dir[0];
        *(f32 *)(obj + 0x134) = dir[1];
        *(f32 *)(obj + 0x138) = dir[2];
    }
    if (fov[0] > 0.0f) {   /* camera_projection_update adds the base +0x6C / +0x70 and g_camera_fov_extra itself */
        camera_projection_update(0, fov[0] - *(f32 *)(rec + 0x6C) - g_camera_fov_extra,
                                 fov[1] - *(f32 *)(rec + 0x70) - g_camera_fov_extra, *(f32 *)(rec + 0x84), 0.0f);
    }
    camera_matrices_refresh_all();
    port_photo_camera_applied();
}

/* ---- P358 photo mode: Conker's pose and outfit (the "look"; port/ultra/pc_photo.c keeps the choices, LK_* / R_* ids).
 * Everything below runs only inside a photo frame (port_photo_look_active), so every change to game memory is undone
 * by the snapshot restore like the photo camera, except photo_look_scan, which only reads when photo mode starts.
 *
 * What the game's data allows (P358 findings):
 *  - Pose: Conker's object (g_objects[0]) plays one animation of his model's animation bank (g_model_anim_banks[model],
 *    8-byte entries {u16 file, u16 callback, s32 events}; 857 on model 0, all with data) on the animation state +0x2D0
 *    (struct_eu_anim: +4 id | hold 0x8000, +8 frame, +0x10 speed, +0x18 frame count). photo_look_pose restarts it with
 *    anim_start_entry (no blend, speed 0, hold) after the state handlers ran and before objects_update_all builds the
 *    joint matrices, so the skeleton is drawn in exactly that frame.
 *  - Model: he is one display list (model 0 has 1; the game's per-list hide mask +0x94 therefore has nothing to split
 *    on him) plus his level-of-detail models 1..4 and the extras of his part list +0x2C4. Models that share his
 *    skeleton and animations are listed in g_anim_bank_group_lists (group of model 0: 20 models); any of them can be
 *    drawn in his place (photo_look_swap_model: loaded from the ROM into the sandbox heap, his part list pointed at it,
 *    fresh vertex blocks), with his pose.
 *  - Materials: his display list loads one texture after the other (G_SETTIMG with the address of a texture entry of
 *    the model, g_model_tex_entries; or segment 6 / 7 / 0xA / 0xB, the face textures the game picks per frame) and
 *    draws triangles with it (Rare's 4-triangle commands 0x10..0x1F); runs without a texture are untextured groups.
 *    Per material: hidden (its triangle commands become G_NOOP), tinted (a renderer marker, gfx_f3dex2.c
 *    PHOTO_TINT_MARK, in place of the G_RDPPIPESYNC before it), or drawn with another texture entry of the same size.
 *  - Face: the game fills segments 6 / 7 (eyes, entries 25..27 by the blink selectors +0x6C / +0x6D) and 0xA / 0xB
 *    (mouth, +0x68 / +0x69) from the model's texture entries (obj_set_face_texture_segments); any entry can be put there.
 *  - Items: the 63 setup command lists (g_setup_cmd_lists, obj_setup_run) attach models to joints (held items, gear);
 *    up to 4 can be run on him. His own attachments (the g_attachment_list records he owns) can be hidden (+5 = 0). */
int port_photo_look_active(void);
int port_photo_look_get(int key, int i);
int port_photo_look_once(int tag);
void port_photo_look_report(int what, int i, int value);
s32 anim_start_entry(struct127 *obj, s32 entry_addr, u8 *anim_addr, s32 unused, s32 restart, s32 id, s32 set,
                     f32 speed, f32 blend, f32 frame, f32 loop_start, s32 hold);
s32 model_header_load(s32 arg0, s32 arg1);
s32 anim_bank_load(s32 arg0, s32 arg1);
void obj_set_type(s32 slot, s32 type, s32 arg2);
void *allocate_memory(s32, s32, s32, s32);
extern s32 g_setup_cmd_lists;          /* was D_80087064: 63 lists {commands, count} */
extern s32 g_anim_bank_group_lists;    /* was D_800847A0: models sharing an animation bank */
extern u8 g_anim_bank_group_sizes;     /* was D_80098C38: their sizes, 0 terminated */
extern u16 g_model_dl_counts[];        /* was D_800C4B98 */
extern s32 g_model_dl_tables[];        /* was D_800C48A8 */
extern s32 g_model_tex_entries;        /* was D_800C5758: per model, 12-byte texture entries {address, id, u16 w, u16 h} */
extern s32 g_model_tex_counts;         /* was D_800C5A48: u16 per model */
enum { LK_ANIM, LK_FRAME, LK_MODEL, LK_ITEM, LK_ATT_HIDE, LK_DL_HIDE, LK_DL_SHOW, LK_FACE, LK_MAT_HIDE, LK_MAT_TINT, LK_MAT_TEX };
enum { R_ANIM_COUNT, R_ANIM_BAD, R_FRAMES, R_MODEL, R_GROUP, R_GROUP_N, R_ITEM_KIND, R_ITEM_ASSET, R_ATT, R_ATT_N,
       R_DRAWN_MODEL, R_DL_N, R_DL_MASK, R_MAT_N, R_MAT_KEY, R_MAT_TRIS, R_TEX_N, R_TEX_ID, R_TEX_WH, R_FACE,
       R_ANIM_GAME, R_FRAME_GAME, R_ERR };
#define PHOTO_TINT_MARK 0x0050544E   /* gfx_f3dex2.c: G_NOOP with this w0 = tint of the following draws (w1 RGBA) */
#define PHOTO_MAT_FACE 64            /* material keys: 0..63 texture entry, 64..67 face segment 6 / 7 / 0xA / 0xB, */
#define PHOTO_MAT_PLAIN 80           /* 80..95 untextured groups in display-list order */

/* When photo mode starts (read-only): Conker's animation count and which have data, the animation he plays, the models
 * of his skeleton group, the 63 item lists, his own attachments. */
void photo_look_scan(void) {
    u8 *o = (u8 *)&g_objects[0];
    struct_eu_anim *anim = (struct_eu_anim *)g_objects[0].unk2D0;
    s32 type = o[4];
    s32 i, k, g, n, found;
    u16 *bank;
    u8 *l;
    u8 *a;

    if (*(s32 *)o == 0 || type == 0xFF) {
        return;
    }
    port_photo_look_report(R_MODEL, 0, type);
    n = (u16)g_model_anim_counts[type];
    bank = (u16 *)g_model_anim_banks[type];
    port_photo_look_report(R_ANIM_COUNT, 0, n);
    for (i = 0; i < n && i < 1024; i++) {
        port_photo_look_report(R_ANIM_BAD, i, bank == NULL || bank[i * 4] == 999 || bank[i * 4] >= 30000);
    }
    port_photo_look_report(R_ANIM_GAME, 0, g_objects[0].unk84.uh);
    port_photo_look_report(R_FRAME_GAME, 0, anim != NULL ? (s32)(anim->unk8 * 100.0f) : 0);
    found = 0;
    for (g = 0; g < 8 && (&g_anim_bank_group_sizes)[g] != 0 && !found; g++) {
        l = ((u8 **)&g_anim_bank_group_lists)[g];
        for (k = 0; k < (&g_anim_bank_group_sizes)[g]; k++) {
            if (l[k] == type) {
                found = 1;
            }
        }
        if (found) {   /* the group's models, each once */
            n = 0;
            for (k = 0; k < (&g_anim_bank_group_sizes)[g]; k++) {
                for (i = 0; i < k && l[i] != l[k]; i++) {
                }
                if (i == k) {
                    port_photo_look_report(R_GROUP, n++, l[k]);
                }
            }
            port_photo_look_report(R_GROUP_N, 0, n);
        }
    }
    if (!found) {
        port_photo_look_report(R_GROUP, 0, type);
        port_photo_look_report(R_GROUP_N, 0, 1);
    }
    for (i = 0; i < 63; i++) {
        l = *(u8 **)((u8 *)&g_setup_cmd_lists + i * 8);
        n = ((u8 *)&g_setup_cmd_lists)[i * 8 + 4];
        g = 0;
        for (k = 0; k < n; k++) {
            g |= 1 << (l[k * 16 + 3] > 2 ? 2 : l[k * 16 + 3]);
        }
        port_photo_look_report(R_ITEM_KIND, i + 1, g);
        port_photo_look_report(R_ITEM_ASSET, i + 1, n > 0 ? l[0] : 0);
    }
    n = 0;
    for (a = (u8 *)g_attachment_list; a != NULL && n < 16; a = *(u8 **)(a + 0x54)) {
        if (a[0] == o[0x3B]) {
            port_photo_look_report(R_ATT, n++, a[1] << 8 | a[6]);
        }
    }
    port_photo_look_report(R_ATT_N, 0, n);
}

/* Model m (of his skeleton group) in place of Conker's: its header and animation bank loaded, every entry of his part
 * list (levels of detail) pointed at it with fresh vertex blocks (+0x28C, two words per entry: obj_model_vertex_blocks_get
 * makes them for m), the type set (obj_set_type). The display list and textures load when it is drawn (model_make_ready). */
static void photo_look_swap_model(struct127 *obj, s32 m) {
    u8 *o = (u8 *)obj;
    u8 *list;
    s32 n, i;

    if (model_header_load(m, 0) != 0 || g_type_descs[m] == NULL || anim_bank_load(m, 0) != 0) {
        port_photo_look_report(R_ERR, 0, 1);
        return;
    }
    n = o[0x2C9];
    if (n == 0) {
        n = 1;
    }
    list = (u8 *)allocate_memory(8, 1, 0, 2);
    if (list == NULL) {
        port_photo_look_report(R_ERR, 0, 1);
        return;
    }
    for (i = 0; i < n && i < 7; i++) {
        list[i] = m;
        *(u32 *)(o + 0x28C + i * 8) = 0;
        *(u32 *)(o + 0x290 + i * 8) = 0;
    }
    *(u8 **)(o + 0x2C4) = list;
    o[0x1C9] = 0;
    obj_set_type(0, m, 0);
}

/* The pose: animation id of Conker's bank at frame `frame`, held (speed 0, no blend). Restarted only when he plays
 * another one, so a frame's second world update only moves the frame. */
static void photo_look_pose(struct127 *obj, s32 id, f32 frame) {
    s32 type = ((u8 *)obj)[4];
    u16 *bank = (u16 *)g_model_anim_banks[type];
    struct_eu_anim *anim = (struct_eu_anim *)obj->unk2D0;
    u16 *e;
    f32 last;

    if (bank == NULL || anim == NULL || id >= (u16)g_model_anim_counts[type]) {
        port_photo_look_report(R_ERR, 0, 2);
        return;
    }
    e = bank + id * 4;
    if (*e == 999 || *e >= 30000) {
        port_photo_look_report(R_ERR, 0, 2);
        return;
    }
    if ((anim->unk4 & 0x7FFF) != id || obj->unk84.uh != id || anim->unk28 == 0) {
        anim_start_entry(obj, (s32)e, (u8 *)anim, 0, 1, id, 0, 0.0f, 0.0f, frame, 0.0f, 1);
    }
    last = anim->unk18 - 1.0f;
    if (frame > last) {
        frame = last;
    }
    if (frame < 0.0f) {
        frame = 0.0f;
    }
    anim->unk8 = frame;
    anim->unk10 = 0.0f;
    anim->unk3C = 0;
    obj->animation_speed = 0.0f;
    port_photo_look_report(R_FRAMES, 0, (s32)anim->unk18);
}

/* world_update, after the state handlers and before objects_update_all (game_45B80.c): model, items, pose */
void photo_look_apply(void) {
    struct127 *obj = &g_objects[0];
    u8 *o = (u8 *)obj;
    s32 m, i, v;

    if (!port_photo_look_active() || *(s32 *)o == 0 || o[4] == 0xFF) {
        return;
    }
    if (port_photo_look_once(1)) {
        m = port_photo_look_get(LK_MODEL, 0);
        if (m >= 0 && m < 0xBB && m != o[4]) {
            photo_look_swap_model(obj, m);
        }
        for (i = 0; i < 4; i++) {
            v = port_photo_look_get(LK_ITEM, i);
            if (v >= 1 && v <= 63) {
                obj_setup_run(obj, v, 1.0f, 0);
            }
        }
    }
    v = port_photo_look_get(LK_ANIM, 0);
    if (v >= 0) {
        photo_look_pose(obj, v, port_photo_look_get(LK_FRAME, 0) * 0.01f);
    }
}

/* the material key of a G_SETTIMG address for model `model`: a texture entry (0..63), a face segment (64..67), or -1
 * (a palette, or another address) */
static s32 photo_look_tex_key(s32 model, u32 addr) {
    u8 *t = ((u8 **)&g_model_tex_entries)[model];
    s32 n = ((u16 *)&g_model_tex_counts)[model];
    s32 i;
    u32 seg = addr >> 24;

    if ((addr & 0xFFFFFF) == 0) {
        if (seg == 6 || seg == 7) {
            return PHOTO_MAT_FACE + seg - 6;
        }
        if (seg == 0xA || seg == 0xB) {
            return PHOTO_MAT_FACE + seg - 8;
        }
    }
    for (i = 0; t != NULL && i < n && i < 64; i++) {
        if (*(u32 *)(t + i * 12) == addr) {
            return i;
        }
    }
    return -1;
}

/* Walks the model's display lists once per photo frame: reports its materials (key, triangle count) and its texture
 * entries, and makes the chosen changes in the (sandboxed) display list itself: triangles of a hidden material ->
 * G_NOOP, the G_RDPPIPESYNC in front of each material -> the tint marker (when any tint is chosen), the image (and its
 * palette, at the same distance) of a material drawn with another texture. */
static void photo_look_patch_model(s32 model) {
    u8 *t = ((u8 **)&g_model_tex_entries)[model];
    s32 ntex = ((u16 *)&g_model_tex_counts)[model];
    s32 tris[96];
    s8 order[96];
    s32 norder = 0, nplain = 0, anytint = 0;
    s32 k, i, key, plain, swap, cnt, istri;
    u32 *c, *sync, w0, w1, img_old, img_new;
    u8 op;

    for (i = 0; i < ntex && i < 64; i++) {
        port_photo_look_report(R_TEX_ID, i, *(s32 *)(t + i * 12 + 4));
        port_photo_look_report(R_TEX_WH, i, *(u16 *)(t + i * 12 + 8) << 16 | *(u16 *)(t + i * 12 + 10));
    }
    port_photo_look_report(R_TEX_N, 0, ntex < 64 ? ntex : 64);
    for (i = 0; i < 96; i++) {
        tris[i] = 0;
        anytint |= port_photo_look_get(LK_MAT_TINT, i) != 0;
    }
    for (k = 0; k < g_model_dl_counts[model]; k++) {
        c = ((u32 **)g_model_dl_tables[model])[k];
        key = -1;
        plain = 0;
        swap = 0;
        sync = NULL;
        img_old = img_new = 0;
        for (cnt = 0; c != NULL && cnt < 20000; cnt++, c += 2) {
            w0 = c[0];
            w1 = c[1];
            op = w0 >> 24;
            if (op == 0xDF || (op == 0xDE && ((w0 >> 16) & 0xFF) == 1)) {
                break;
            }
            if (op == 0xE7 || (op == 0 && w0 == PHOTO_TINT_MARK)) {
                sync = c;
                continue;
            }
            if (op == 0xFC) {
                plain = 1;
                continue;
            }
            istri = op == 0x05 || op == 0x06 || op == 0x07 || (op >= 0x10 && op <= 0x1F);
            if (op == 0xFD) {
                i = photo_look_tex_key(model, w1);
                if (i < 0) {
                    if (swap) {   /* the palette after the image: at the same distance from the new image */
                        c[1] = img_new + (w1 - img_old);
                        swap = 0;
                    }
                    continue;
                }
                key = i;
                plain = 0;
                swap = 0;
                if (key < 64) {
                    i = port_photo_look_get(LK_MAT_TEX, key);
                    if (i >= 0 && i < ntex && i != key) {
                        img_old = w1;
                        img_new = *(u32 *)(t + i * 12);
                        c[1] = img_new;
                        swap = 1;
                    }
                }
            } else if (istri && plain) {
                key = PHOTO_MAT_PLAIN + (nplain < 15 ? nplain : 15);
                nplain++;
                plain = 0;
            } else if (!istri) {
                continue;
            } else {
                goto tri;
            }
            /* a new material starts here: note it, put its tint marker in place of the sync in front of it */
            for (i = 0; i < norder && order[i] != key; i++) {
            }
            if (i == norder && norder < 96) {
                order[norder++] = key;
            }
            if (anytint && sync != NULL) {
                sync[0] = PHOTO_TINT_MARK;
                sync[1] = port_photo_look_get(LK_MAT_TINT, key);
                sync = NULL;
            }
            if (!istri) {
                continue;
            }
        tri:
            if (key >= 0) {
                tris[key] += op == 0x05 ? 1 : op < 0x10 ? 2 : 4;
                if (port_photo_look_get(LK_MAT_HIDE, key)) {
                    c[0] = 0;
                    c[1] = 0;
                }
            }
            sync = NULL;
        }
    }
    for (i = 0; i < norder; i++) {
        port_photo_look_report(R_MAT_KEY, i, order[i]);
        port_photo_look_report(R_MAT_TRIS, i, tris[(u8)order[i]]);
    }
    port_photo_look_report(R_MAT_N, 0, norder);
}

/* obj_draw_model_dl, Conker in a photo frame: reports what is drawn, patches the display list (once per frame) and
 * returns the display-list hide mask to use */
u32 photo_look_draw_begin(s32 model, u32 hide) {
    port_photo_look_report(R_DRAWN_MODEL, 0, model);
    port_photo_look_report(R_DL_N, 0, g_model_dl_counts[model]);
    port_photo_look_report(R_DL_MASK, 0, hide);
    if (port_photo_look_once(0x100 + model)) {
        photo_look_patch_model(model);
    }
    return (hide | (u32)port_photo_look_get(LK_DL_HIDE, 0)) & ~(u32)port_photo_look_get(LK_DL_SHOW, 0);
}

/* world_update after objects_update_all (attachment_update_all marked the attachments it placed as shown, +5):
 * Conker's own attachments the page hides are not drawn this frame */
void photo_look_after_update(void) {
    u8 *o = (u8 *)&g_objects[0];
    u8 *a;
    s32 i, key;

    if (!port_photo_look_active() || *(s32 *)o == 0) {
        return;
    }
    for (a = (u8 *)g_attachment_list; a != NULL; a = *(u8 **)(a + 0x54)) {
        if (a[0] != o[0x3B]) {
            continue;
        }
        key = a[1] << 8 | a[6];
        for (i = 0; i < 16; i++) {
            if (port_photo_look_get(LK_ATT_HIDE, i) == key) {
                a[5] = 0;
            }
        }
    }
}

/* obj_set_face_texture_segments, Conker in a photo frame: the face textures (segment 6 / 7 / 0xA / 0xB entries) */
void photo_look_face(u8 *sel, u8 *mouth) {
    s32 i, v;

    for (i = 0; i < 4; i++) {
        port_photo_look_report(R_FACE, i, i < 2 ? sel[i] : mouth[i - 2]);
        v = port_photo_look_get(LK_FACE, i);
        if (v >= 0 && v < 64) {
            if (i < 2) {
                sel[i] = v;
            } else {
                mouth[i - 2] = v;
            }
        }
    }
}
#endif
