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
#endif
