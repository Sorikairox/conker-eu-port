#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_15164CF0 */
u8 *cam_wobble_spawn(u8 *arg0, s32 arg1, u8 arg2, s32 arg3) {
    u8 *p;
    struct127 *obj;
    struct108 *e;

    e = &g_player_views[arg0[6]];
    obj = e->unk3D0;
    if (obj != NULL && obj->unk31C != NULL && obj->unk31C->unk198 != 0) {
        return NULL;
    }
    p = node_alloc(0x39, arg3, arg1 + 0x68, 1, arg2, 1);
    if (p == NULL) {
        return NULL;
    }
    memcpy(p + 0x10, arg0, 0x38);
    p[0x60] = 1;
    p[0x61] = 1;
    p[0x62] = 1;
    p[0x63] = 1;
    p[0x64] = 1;
    p[0x65] = 1;
    *(f32 *)(p + 0x48) = 0.0f;
    *(f32 *)(p + 0x4C) = 0.0f;
    *(f32 *)(p + 0x50) = 0.0f;
    *(f32 *)(p + 0x54) = 0.0f;
    *(f32 *)(p + 0x58) = 0.0f;
    *(f32 *)(p + 0x5C) = 0.0f;
    return p;
}

/* was func_15164DF8 */
void cam_wobble_stop_at_half_cycle(u8 *arg0) {
    arg0[0x10] |= 2;
}

extern s32 (*g_camera_wobble_end_fns[])(u8 *); /* was D_8008B730 */
extern f32 (*g_camera_wobble_scale_fns[])(u8 *); /* was D_8008B734 */
extern f32 g_camera_wobble_phase_limits; /* was D_800A6F00 */ // 6 consecutive limits (all pi)

// object_wobble_update: per-frame update of a 6-channel wobble / fade record (g_node_type_delete_fns handler). Optional life
// timer (+0x10 & 1: +0x14 -= frames) and end check (+0x11: g_camera_wobble_end_fns callback, 0 = done) end it via cam_wobble_stop_at_half_cycle.
// The amplitude scale is 1 or the +0x12 callback of g_camera_wobble_scale_fns (+0x10 & 4). Each channel i with a speed (+0x30 + 4i)
// advances its phase (+0x48 + 4i, wrapped by wrap_angle_rad), records the half-cycle in +0x60 + i (phase < pi), stops
// itself at a half-cycle change when +0x10 & 2, and adds sin(phase) * amplitude (+0x18 + 4i) * scale to float i of
// target record +0x16 of g_camera_view_offsets (0x18 bytes each). When every speed is 0 the record is freed (node_destroy).
/* was func_15164E0C */
void cam_wobble_update(u8 *arg0) {
    u8 prev[6];
    f32 scale;
    f32 phase;
    f32 *dst;
    s32 done = 0;
    s32 i;

    if (arg0[0x10] & 1) {
        *(s16 *) (arg0 + 0x14) -= g_frame_ticks;
        if (*(s16 *) (arg0 + 0x14) < 0) {
            done = 1;
        }
    }
    if (!done && (s8) arg0[0x11] != -1) {
        if (g_camera_wobble_end_fns[(s8) arg0[0x11]](arg0) == 0) {
            done = 1;
        }
    }
    if (done) {
        cam_wobble_stop_at_half_cycle(arg0);
    }
    for (i = 0; i < 6; i++) {
        prev[i] = arg0[0x60 + i];
    }
    scale = 1.0f;
    if ((arg0[0x10] & 4) && (s8) arg0[0x12] != -1) {
        scale = g_camera_wobble_scale_fns[(s8) arg0[0x12]](arg0);
    }
    for (i = 0; i < 6; i++) {
        if (*(f32 *) (arg0 + 0x30 + i * 4) != 0.0f) {
            phase = wrap_angle_rad(*(f32 *) (arg0 + 0x48 + i * 4) + *(f32 *) (arg0 + 0x30 + i * 4) * g_frame_step_f);
            *(f32 *) (arg0 + 0x48 + i * 4) = phase;
            arg0[0x60 + i] = (phase < (&g_camera_wobble_phase_limits)[i]);
            if ((arg0[0x10] & 2) && prev[i] != arg0[0x60 + i]) {
                *(f32 *) (arg0 + 0x30 + i * 4) = 0.0f;
                *(f32 *) (arg0 + 0x48 + i * 4) = 0.0f;
            }
            dst = (f32 *) (g_camera_view_offsets + arg0[0x16] * 0x18) + i;
            *dst += sinf(*(f32 *) (arg0 + 0x48 + i * 4)) * *(f32 *) (arg0 + 0x18 + i * 4) * scale;
        }
    }
    if (*(f32 *) (arg0 + 0x30) == 0.0f && *(f32 *) (arg0 + 0x34) == 0.0f && *(f32 *) (arg0 + 0x38) == 0.0f
        && *(f32 *) (arg0 + 0x3C) == 0.0f && *(f32 *) (arg0 + 0x40) == 0.0f && *(f32 *) (arg0 + 0x44) == 0.0f) {
        node_destroy((struct102 *) arg0);
    }
}

/* was func_15165454 */
void cam_wobble_clear_offsets(void) {
    bzero(g_camera_view_offsets, 0x60);
}

/* P177 */
u8 *cam_wobble_spawn_params(u8 *arg0, s32 arg1, s8 arg2, s32 arg3, u8 arg4, s32 arg5);

// screen_effect_preset: starts preset `kind` (0..7) of the cam_wobble_spawn_params effect (record kind 0x39 via cam_wobble_spawn)
/* for view `view`: a block of 15 floats (3 periods, 9 coefficients, 3 more), with (-1, 0) for presets 0..3 and 7,
 * (0, 0) for 4 and (1, 0x18) for 5 / 6; presets 5 and 6 also copy 0x18 bytes of `data` to the new record's +0x108.
 * Returns the record (NULL when none was made; the asm returns a stale v0 for kind >= 8, NULL here). */
/* was func_1516547C */
u8 *cam_wobble_start_preset(u8 kind, u8 view, u8 *data, u8 arg3, s32 arg4) {
    f32 p[15];
    u8 *rec;

    switch (kind) {
    case 0:
        p[0] = 10.0f;
        p[1] = 4.0f;
        p[2] = 7.0f;
        p[3] = 0.78059995f;
        p[4] = 0.28689998f;
        p[5] = 0.88879997f;
        p[6] = 0.666f;
        p[7] = 1.194f;
        p[8] = 1.01f;
        p[9] = 0.4353f;
        p[10] = 0.58669996f;
        p[11] = 0.7097f;
        p[12] = 6.0f;
        p[13] = 17.0f;
        p[14] = 48.0f;
        return cam_wobble_spawn_params((u8 *)p, view, -1, 0, arg3, arg4);
    case 1:
        p[0] = 20.0f;
        p[1] = 19.0f;
        p[2] = 53.0f;
        p[3] = 0.0f;
        p[4] = 0.0f;
        p[5] = 1.4778f;
        p[6] = 0.60200006f;
        p[7] = 1.021f;
        p[8] = 1.1910001f;
        p[9] = 0.0f;
        p[10] = 0.0f;
        p[11] = 2.905f;
        p[12] = 3.0f;
        p[13] = 5.0f;
        p[14] = 30.0f;
        return cam_wobble_spawn_params((u8 *)p, view, -1, 0, arg3, arg4);
    case 2:
        p[0] = 10.0f;
        p[1] = 7.0f;
        p[2] = 6.0f;
        p[3] = 1.0029f;
        p[4] = 0.49769998f;
        p[5] = 1.4305999f;
        p[6] = 0.65400004f;
        p[7] = 1.062f;
        p[8] = 0.321f;
        p[9] = 0.5169f;
        p[10] = 0.77279997f;
        p[11] = 0.17559999f;
        p[12] = 2.0f;
        p[13] = 27.0f;
        p[14] = 15.0f;
        return cam_wobble_spawn_params((u8 *)p, view, -1, 0, arg3, arg4);
    case 3:
        p[0] = 7.0f;
        p[1] = 11.0f;
        p[2] = 5.0f;
        p[3] = 0.4321f;
        p[4] = 0.6329f;
        p[5] = 0.8082f;
        p[6] = 0.27600002f;
        p[7] = 0.53900003f;
        p[8] = 0.439f;
        p[9] = 1.6726999f;
        p[10] = 0.49469998f;
        p[11] = 0.98939997f;
        p[12] = 5.0f;
        p[13] = 15.0f;
        p[14] = 12.0f;
        return cam_wobble_spawn_params((u8 *)p, view, -1, 0, arg3, arg4);
    case 4:
        p[0] = 8.0f;
        p[1] = 17.0f;
        p[2] = 4.0f;
        p[3] = 0.7614f;
        p[4] = 1.5706999f;
        p[5] = 1.2667999f;
        p[6] = 0.587f;
        p[7] = 0.906f;
        p[8] = 0.40300003f;
        p[9] = 1.1592f;
        p[10] = 0.69729996f;
        p[11] = 1.3464f;
        p[12] = 5.0f;
        p[13] = 3.0f;
        p[14] = 45.0f;
        return cam_wobble_spawn_params((u8 *)p, view, 0, 0, arg3, arg4);
    case 5:
        p[0] = 15.0f;
        p[1] = 10.0f;
        p[2] = 19.0f;
        p[3] = 0.5397f;
        p[4] = 0.7679f;
        p[5] = 0.9881f;
        p[6] = 1.0450001f;
        p[7] = 0.63600004f;
        p[8] = 1.404f;
        p[9] = 0.4526f;
        p[10] = 0.48499998f;
        p[11] = 0.6843f;
        p[12] = 5.0f;
        p[13] = 5.0f;
        p[14] = 25.0f;
        rec = cam_wobble_spawn_params((u8 *)p, view, 1, 0x18, arg3, arg4);
        if (rec != NULL) {
            memcpy(rec + 0x108, data, 0x18);
        }
        return rec;
    case 6:
        p[0] = 15.0f;
        p[1] = 10.0f;
        p[2] = 19.0f;
        p[3] = 0.5397f;
        p[4] = 0.7679f;
        p[5] = 0.9881f;
        p[6] = 1.0450001f;
        p[7] = 0.63600004f;
        p[8] = 1.404f;
        p[9] = 0.4526f;
        p[10] = 0.48499998f;
        p[11] = 0.6843f;
        p[12] = 5.0f;
        p[13] = 5.0f;
        p[14] = 25.0f;
        rec = cam_wobble_spawn_params((u8 *)p, view, 1, 0x18, arg3, arg4);
        if (rec != NULL) {
            memcpy(rec + 0x108, data, 0x18);
        }
        return rec;
    case 7:
        p[0] = 8.0f;
        p[1] = 12.0f;
        p[2] = 9.0f;
        p[3] = 0.5f;
        p[4] = 0.19999999f;
        p[5] = 0.29999998f;
        p[6] = 1.156f;
        p[7] = 0.96400005f;
        p[8] = 0.45800003f;
        p[9] = 2.2786f;
        p[10] = 1.9194f;
        p[11] = 1.525f;
        p[12] = 4.0f;
        p[13] = 10.0f;
        p[14] = 16.0f;
        return cam_wobble_spawn_params((u8 *)p, view, -1, 0, arg3, arg4);
    }
    return NULL;
}

/* was func_15165B98 */
u8 *cam_wobble_spawn_params(u8 *arg0, s32 arg1, s8 arg2, s32 arg3, u8 arg4, s32 arg5) {
    struct {
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
        f32 u50;
        f32 u54;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        s32 u98;
        u8 pad9C[0x8];
        s32 uA4;
        u8 padA8[0x8];
        s32 uB0;
        u8 padB4[0x8];
        s32 uBC;
        u8 padC0[0x8];
        f32 uC8;
        f32 uCC;
        f32 uD0;
        f32 uD4;
        u8 uD8;
        s8 uD9;
        s8 uDA;
        u8 padDB[0x1];
        s16 uDC;
        s8 uDE;
        u8 padDF[0x1];
        f32 uE0;
        f32 uE4;
        f32 uE8;
        f32 uEC;
        f32 uF0;
        f32 uF4;
        f32 uF8;
        f32 uFC;
        f32 u100;
        f32 u104;
        f32 u108;
        f32 u10C;
    } sp;
    f32 temp_f0;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f2;
    u8 *temp_v0;

    temp_f14 = (*(f32 *)((u8 *)arg0 + 0x30));
    if ((temp_f14 == 0.0f) || (temp_f16 = (*(f32 *)((u8 *)arg0 + 0x38)), (temp_f16 == 0.0f))) {
        return NULL;
    }
    temp_f0 = 1.0f / temp_f14;
    sp.uD8 = 4;
    sp.uD9 = 0;
    sp.uDC = 0x12C;
    sp.uDE = arg1 & 0xFF;
    sp.uDA = arg2;
    sp.uE0 = 0.0f;
    sp.uE4 = 0.0f;
    sp.uE8 = 0.0f;
    sp.uEC = 0.0f;
    sp.uF0 = 0.0f;
    sp.uF4 = 0.0f;
    sp.uF8 = 0.0f;
    sp.uFC = 0.0f;
    sp.u100 = 0.0f;
    sp.u104 = 0.0f;
    sp.u108 = 0.0f;
    sp.u10C = 0.0f;
    temp_f2 = 1.0f / temp_f16;
    sp.u38 = (*(f32 *)((u8 *)arg0 + 0)) * temp_f0;
    sp.u3C = (*(f32 *)((u8 *)arg0 + 4)) * temp_f0;
    sp.u40 = (*(f32 *)((u8 *)arg0 + 8)) * temp_f0;
    sp.u44 = (*(f32 *)((u8 *)arg0 + 0xC)) * temp_f0;
    sp.u48 = (*(f32 *)((u8 *)arg0 + 0x10)) * temp_f0;
    sp.u4C = (*(f32 *)((u8 *)arg0 + 0x14)) * temp_f0;
    sp.u50 = (*(f32 *)((u8 *)arg0 + 0x18)) * temp_f0;
    sp.u54 = (*(f32 *)((u8 *)arg0 + 0x1C)) * temp_f0;
    sp.u58 = (*(f32 *)((u8 *)arg0 + 0x20)) * temp_f0;
    sp.u5C = (*(f32 *)((u8 *)arg0 + 0x24)) * temp_f0;
    sp.u60 = (*(f32 *)((u8 *)arg0 + 0x28)) * temp_f0;
    sp.u64 = (*(f32 *)((u8 *)arg0 + 0x2C)) * temp_f0;
    sp.u74 = (*(f32 *)((u8 *)arg0 + 0)) * temp_f2;
    sp.u78 = (*(f32 *)((u8 *)arg0 + 4)) * temp_f2;
    sp.u7C = (*(f32 *)((u8 *)arg0 + 8)) * temp_f2;
    sp.u68 = (*(f32 *)((u8 *)arg0 + 0xC)) * temp_f2;
    sp.u6C = (*(f32 *)((u8 *)arg0 + 0x10)) * temp_f2;
    sp.u70 = (*(f32 *)((u8 *)arg0 + 0x14)) * temp_f2;
    sp.u8C = (*(f32 *)((u8 *)arg0 + 0x18)) * temp_f2;
    sp.u90 = (*(f32 *)((u8 *)arg0 + 0x1C)) * temp_f2;
    sp.u94 = (*(f32 *)((u8 *)arg0 + 0x20)) * temp_f2;
    sp.u80 = (*(f32 *)((u8 *)arg0 + 0x24)) * temp_f2;
    sp.u84 = (*(f32 *)((u8 *)arg0 + 0x28)) * temp_f2;
    sp.u88 = (*(f32 *)((u8 *)arg0 + 0x2C)) * temp_f2;
    (*(f32 *)((u8 *)(&sp.u98) + 0)) = (f32) (*(f32 *)((u8 *)arg0 + 0));
    (*(f32 *)((u8 *)(&sp.u98) + 4)) = (f32) (*(f32 *)((u8 *)arg0 + 4));
    (*(f32 *)((u8 *)(&sp.u98) + 8)) = (f32) (*(f32 *)((u8 *)arg0 + 8));
    (*(f32 *)((u8 *)(&sp.uA4) + 0)) = (f32) (*(f32 *)((u8 *)arg0 + 0xC));
    (*(f32 *)((u8 *)(&sp.uA4) + 4)) = (f32) (*(f32 *)((u8 *)arg0 + 0x10));
    (*(f32 *)((u8 *)(&sp.uA4) + 8)) = (f32) (*(f32 *)((u8 *)arg0 + 0x14));
    (*(f32 *)((u8 *)(&sp.uB0) + 0)) = (f32) (*(f32 *)((u8 *)arg0 + 0x18));
    (*(f32 *)((u8 *)(&sp.uB0) + 4)) = (f32) (*(f32 *)((u8 *)arg0 + 0x1C));
    (*(f32 *)((u8 *)(&sp.uB0) + 8)) = (f32) (*(f32 *)((u8 *)arg0 + 0x20));
    (*(f32 *)((u8 *)(&sp.uBC) + 0)) = (f32) (*(f32 *)((u8 *)arg0 + 0x24));
    (*(f32 *)((u8 *)(&sp.uBC) + 4)) = (f32) (*(f32 *)((u8 *)arg0 + 0x28));
    (*(f32 *)((u8 *)(&sp.uBC) + 8)) = (f32) (*(f32 *)((u8 *)arg0 + 0x2C));
    sp.uC8 = (*(f32 *)((u8 *)arg0 + 0x30));
    sp.uCC = (*(f32 *)((u8 *)arg0 + 0x34));
    sp.uD4 = 0.0f;
    sp.uD0 = (*(f32 *)((u8 *)arg0 + 0x38));
    temp_v0 = cam_wobble_spawn(&sp.uD8, arg3 + 0xA0, arg4, arg5);
    if (temp_v0 != NULL) {
        memcpy(temp_v0 + 0x68, &sp.u38, 0xA0);
    }
    return temp_v0;
}
/* was func_15165E4C */
s32 cam_wobble_beh_envelope(u8 *arg0) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f2;
    s32 var_v1;
    u8 *temp_v0;
    u8 *temp_v0_2;

    var_v1 = 1;
    temp_v0 = arg0 + 0x68;
    (*(f32 *)((u8 *)arg0 + 0x104)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x104)) + g_frame_step_f);
    if ((*(f32 *)((u8 *)arg0 + 0x104)) < (*(f32 *)((u8 *)arg0 + 0xF8))) {
        temp_v0_2 = arg0 + 0x68;
        (*(f32 *)((u8 *)arg0 + 0x18)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0)) * (*(f32 *)((u8 *)temp_v0_2 + 0x9C)));
        (*(f32 *)((u8 *)arg0 + 0x1C)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 4)) * (*(f32 *)((u8 *)temp_v0_2 + 0x9C)));
        (*(f32 *)((u8 *)arg0 + 0x20)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 8)) * (*(f32 *)((u8 *)temp_v0_2 + 0x9C)));
        (*(f32 *)((u8 *)arg0 + 0x24)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0xC)) * (*(f32 *)((u8 *)temp_v0_2 + 0x9C)));
        (*(f32 *)((u8 *)arg0 + 0x28)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x10)) * (*(f32 *)((u8 *)temp_v0_2 + 0x9C)));
        (*(f32 *)((u8 *)arg0 + 0x2C)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x14)) * (*(f32 *)((u8 *)temp_v0_2 + 0x9C)));
        (*(f32 *)((u8 *)arg0 + 0x30)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x18)) * (*(f32 *)((u8 *)temp_v0_2 + 0x9C)));
        (*(f32 *)((u8 *)arg0 + 0x34)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x1C)) * (*(f32 *)((u8 *)temp_v0_2 + 0x9C)));
        (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x20)) * (*(f32 *)((u8 *)temp_v0_2 + 0x9C)));
        (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x24)) * (*(f32 *)((u8 *)temp_v0_2 + 0x9C)));
        (*(f32 *)((u8 *)arg0 + 0x40)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x28)) * (*(f32 *)((u8 *)temp_v0_2 + 0x9C)));
        (*(f32 *)((u8 *)arg0 + 0x44)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x2C)) * (*(f32 *)((u8 *)temp_v0_2 + 0x9C)));
    } else {
        temp_f2 = (*(f32 *)((u8 *)temp_v0 + 0x9C));
        temp_f12 = (*(f32 *)((u8 *)temp_v0 + 0x90)) + (*(f32 *)((u8 *)temp_v0 + 0x94));
        if (temp_f2 < temp_f12) {
            (*(f32 *)((u8 *)arg0 + 0x18)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x60));
            (*(f32 *)((u8 *)arg0 + 0x1C)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x64));
            (*(f32 *)((u8 *)arg0 + 0x20)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x68));
            (*(f32 *)((u8 *)arg0 + 0x24)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x6C));
            (*(f32 *)((u8 *)arg0 + 0x28)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x70));
            (*(f32 *)((u8 *)arg0 + 0x2C)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x74));
            (*(f32 *)((u8 *)arg0 + 0x30)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x78));
            (*(f32 *)((u8 *)arg0 + 0x34)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x7C));
            (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x80));
            (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x84));
            (*(f32 *)((u8 *)arg0 + 0x40)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x88));
            (*(f32 *)((u8 *)arg0 + 0x44)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x8C));
        } else if (temp_f2 < (temp_f12 + (*(f32 *)((u8 *)temp_v0 + 0x98)))) {
            temp_f0 = temp_f2 - temp_f12;
            (*(f32 *)((u8 *)arg0 + 0x18)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x60)) - ((*(f32 *)((u8 *)temp_v0 + 0x3C)) * temp_f0));
            (*(f32 *)((u8 *)arg0 + 0x1C)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x64)) - ((*(f32 *)((u8 *)temp_v0 + 0x40)) * temp_f0));
            (*(f32 *)((u8 *)arg0 + 0x20)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x68)) - ((*(f32 *)((u8 *)temp_v0 + 0x44)) * temp_f0));
            (*(f32 *)((u8 *)arg0 + 0x24)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x6C)) - ((*(f32 *)((u8 *)temp_v0 + 0x30)) * temp_f0));
            (*(f32 *)((u8 *)arg0 + 0x28)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x70)) - ((*(f32 *)((u8 *)temp_v0 + 0x34)) * temp_f0));
            (*(f32 *)((u8 *)arg0 + 0x2C)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x74)) - ((*(f32 *)((u8 *)temp_v0 + 0x38)) * temp_f0));
            (*(f32 *)((u8 *)arg0 + 0x30)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x78)) - ((*(f32 *)((u8 *)temp_v0 + 0x54)) * temp_f0));
            (*(f32 *)((u8 *)arg0 + 0x34)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x7C)) - ((*(f32 *)((u8 *)temp_v0 + 0x58)) * temp_f0));
            (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x80)) - ((*(f32 *)((u8 *)temp_v0 + 0x5C)) * temp_f0));
            (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x84)) - ((*(f32 *)((u8 *)temp_v0 + 0x48)) * temp_f0));
            (*(f32 *)((u8 *)arg0 + 0x40)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x88)) - ((*(f32 *)((u8 *)temp_v0 + 0x4C)) * temp_f0));
            (*(f32 *)((u8 *)arg0 + 0x44)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x8C)) - ((*(f32 *)((u8 *)temp_v0 + 0x50)) * temp_f0));
        } else {
            var_v1 = 0;
        }
    }
    return var_v1;
}
f32 cam_wobble_fade_by_distance(void *arg0, void *arg1, s32 arg2, s32 arg3, f32 arg4);

/* P162: entry 1 of g_camera_wobble_scale_fns; cam_wobble_update (asm) stores the entry's f0 result, so this returns cam_wobble_fade_by_distance's
   f32 instead of void. */
// object_distance_fade: fade factor of the object at obj + 0x108 (near / range / scale at +0x114 / +0x118 / +0x11C)
/* was func_151660F0 */
f32 cam_wobble_distance_fade(u8 *arg0) {
    return cam_wobble_fade_by_distance(arg0, arg0 + 0x108, *(s32 *)(arg0 + 0x114), *(s32 *)(arg0 + 0x118), *(f32 *)(arg0 + 0x11C));
}

f32 vec3_length(void *);

/* was func_15166120 */
f32 cam_wobble_fade_by_distance(void * arg0_p, void * arg1_p, s32 arg2, s32 arg3, f32 arg4) {
    u8 * arg0 = (u8 *) arg0_p;
    u8 * arg1 = (u8 *) arg1_p;
    struct {
        f32 u20;
        f32 u24;
        f32 u28;
    } sp;
    f32 *temp_v0;
    f32 temp_f0;
    f32 var_f2;

    temp_v0 = camera_get_pos((s32) (*(u8 *)((u8 *)arg0 + 0x16)));
    sp.u20 = (*(f32 *)((u8 *)arg1 + 0)) - (*(f32 *)((u8 *)temp_v0 + 0));
    sp.u24 = (*(f32 *)((u8 *)arg1 + 4)) - (*(f32 *)((u8 *)temp_v0 + 4));
    sp.u28 = (*(f32 *)((u8 *)arg1 + 8)) - (*(f32 *)((u8 *)temp_v0 + 8));
    temp_f0 = vec3_length(&sp.u20);
    if (temp_f0 < (*(f32 *)&(arg2))) {
        var_f2 = 1.0f;
    } else if (((*(f32 *)&(arg2)) + (*(f32 *)&(arg3))) < temp_f0) {
        var_f2 = 0.0f;
    } else {
        var_f2 = 1.0f - ((temp_f0 - (*(f32 *)&(arg2))) * arg4);
    }
    return var_f2;
}