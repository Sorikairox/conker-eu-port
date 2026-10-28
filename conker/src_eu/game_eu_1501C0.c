#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
void vec3_diff(struct17 *arg0, struct17 *arg1, struct17 *arg2);
f32 vec3_heading_deg(struct17 *arg0);
f32 math_angle_diff_deg(f32 arg0, f32 arg1);
void math_spring_approach(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5);
void camera_update_eye_orbit(u8 *);
void camera_update_eye_base(u8 *);
void camera_update_eye_height(u8 *);


f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
f32 sinf(f32);
f32 cosf(f32);
void camera_calc_relative_yaw(u8 *arg0);
void vec3_dir_to(struct17 *arg0, struct17 *arg1, struct17 *arg2);
extern f32 g_camera_orbit_last_yaw;  /* last yaw (degrees); was D_80089860 */
extern f32 g_camera_orbit_pitch_d2r;  /* pi / 180; was D_800A3850 */
extern f32 g_camera_orbit_half_pi;  /* pi / 2; was D_800A3854 */
extern f32 g_camera_orbit_no_override;  /* 999: "no yaw override" in +0x86C; was D_800A3858 */
extern f32 g_camera_orbit_yaw_d2r;  /* pi / 180; was D_800A385C */
extern f32 g_camera_orbit_rate_a, g_camera_orbit_rate_b; /* 2.2, 2.2; was D_800A3860; was D_800A3864 */
extern f32 g_camera_orbit_roll_ease;  /* 0.15; was D_800A3868 */
#define CAMF(off) (*(f32 *) (cam + (off)))

// camera_orbit_update: third-person camera placement around the target cam+0x2BC. Pitch from the target's
// +0x40 (+90 deg) or, when flag 1 of +0x5F0 and the target's +0x102 are clear, +0x39C - pi/2; yaw from +0x86C unless
// it is 999 (then the target's +0xB8, +10 when +0x102, 0 when its +0x1CA is clear), halved when +0x102, clamped to
// +-88 deg and kept at the previous value g_camera_orbit_last_yaw within 10 deg. Distance 150 when flag 0x10 of *(+0x36C), else
// +0x374 (the shorter +0x370 when +0x102 and not +0x3E8). The new eye (height clamped to +-200 around the target) is set at
// once (+0x23C) or eased per axis by math_spring_approach (speeds +0x3C0.., rate 2 / 2.2+2.2, doubled when +0x102), kept
// at least 120 away from the target, at least 30 above the floor +0x35C. Also eases +0x5E8 to +0x5EC, sets
// +0x3DC (pitch), +0x344 / +0x348 (eye height over +0x354) and +0x370 (horizontal distance).
/* was func_151229B0 */
void camera_orbit_update(u8 *cam) {
    u8 *tgt;
    f32 pitch, yaw, prev, dist;
    f32 sinP, cosP;
    f32 v[3];
    f32 h, rate, speed;
    f32 x, y, z;
    f32 dx, dy, dz;
    f32 dir[3];

    pitch = (*(f32 *) (*(u8 **) (cam + 0x3D0) + 0x40) + 90.0f) * g_camera_orbit_pitch_d2r;
    camera_update_eye_base(cam);
    if (!(*(s32 *) (cam + 0x5F0) & 1) && *(*(u8 **) (cam + 0x3D0) + 0x102) == 0) {
        pitch = CAMF(0x39C) - g_camera_orbit_half_pi;
    }
    tgt = *(u8 **) (cam + 0x3D0);
    if (g_camera_orbit_no_override == CAMF(0x86C)) {
        if (tgt[0x1CA] == 0) {
            yaw = 0.0f;
        } else {
            yaw = (tgt[0x102] != 0 ? 10.0f : 0.0f) + *(f32 *) (tgt + 0xB8);
        }
    } else {
        yaw = CAMF(0x86C);
    }
    if (tgt[0x102] != 0) {
        yaw *= 0.5f;
    }
    if (yaw < -88.0f) {
        yaw = -88.0f;
    } else if (88.0f < yaw) {
        yaw = 88.0f;
    }
    prev = g_camera_orbit_last_yaw;
    if (fabsf(prev - yaw) < 10.0f) {
        yaw = prev;
    } else {
        g_camera_orbit_last_yaw = yaw;
    }
    yaw *= g_camera_orbit_yaw_d2r;
    camera_calc_relative_yaw(cam);
    if (**(u16 **) (cam + 0x36C) & 0x10) {
        dist = 150.0f;
    } else {
        dist = CAMF(0x374);
    }
    if ((*(u8 **) (cam + 0x3D0))[0x102] != 0 && cam[0x3E8] == 0 && CAMF(0x370) < CAMF(0x374)) {
        dist = CAMF(0x370);
    }
    h = cosf(yaw) * dist;
    y = sinf(yaw) * dist;
    sinP = sinf(pitch);
    cosP = cosf(pitch);
    CAMF(0x3DC) = pitch;
    z = -h * sinP;
    x = h * cosP;
    if (y < -200.0f) {
        y = -200.0f;
    } else if (200.0f < y) {
        y = 200.0f;
    }
    v[0] = x + CAMF(0x2BC);
    v[1] = y + CAMF(0x2C0);
    v[2] = z + CAMF(0x2C4);
    if (cam[0x23C] != 0) {
        CAMF(0x2F8) = v[0];
        CAMF(0x2FC) = v[1];
        CAMF(0x300) = v[2];
        CAMF(0x3C0) = 0.0f;
        CAMF(0x3C4) = 0.0f;
        CAMF(0x3C8) = 0.0f;
    } else {
        speed = 1.0f + 1.0f;
        rate = g_camera_orbit_rate_a + g_camera_orbit_rate_b;
        if ((*(u8 **) (cam + 0x3D0))[0x102] != 0) {
            speed += speed;
            rate += rate;
        }
        math_spring_approach(&CAMF(0x2F8), v[0], &CAMF(0x3C0), speed, rate, CAMF(0x7B4));
        math_spring_approach(&CAMF(0x2FC), v[1], &CAMF(0x3C4), speed, rate, CAMF(0x7B4));
        math_spring_approach(&CAMF(0x300), v[2], &CAMF(0x3C8), speed, rate, CAMF(0x7B4));
    }
    if ((*(u8 **) (cam + 0x3D0))[0x102] == 0 && !(*(u16 *) (cam + 0x36A) & 0x10)) {
        dx = CAMF(0x2F8) - CAMF(0x2BC);
        dy = CAMF(0x2FC) - CAMF(0x2C0);
        dz = CAMF(0x300) - CAMF(0x2C4);
        if (sqrtf(dx * dx + dy * dy + dz * dz) < 120.0f) {
            vec3_dir_to((struct17 *) &CAMF(0x2BC), (struct17 *) &CAMF(0x2F8), (struct17 *) dir);
            CAMF(0x2F8) = CAMF(0x2BC) + 120.0f * dir[0];
            CAMF(0x2FC) = CAMF(0x2C0) + 120.0f * dir[1];
            CAMF(0x300) = CAMF(0x2C4) + 120.0f * dir[2];
        }
    }
    if (CAMF(0x2FC) < CAMF(0x35C) + 30.0f) {
        CAMF(0x2FC) = CAMF(0x35C) + 30.0f;
    }
    CAMF(0x5E8) += (CAMF(0x5EC) - CAMF(0x5E8)) * g_camera_orbit_roll_ease;
    dx = CAMF(0x2F8) - CAMF(0x2BC);
    dz = CAMF(0x300) - CAMF(0x2C4);
    CAMF(0x344) = CAMF(0x348) = CAMF(0x2FC) - CAMF(0x354);
    CAMF(0x370) = sqrtf(dx * dx + dz * dz);
}
#undef CAMF

#ifdef PORT
/* P347 option "Free camera" (PORT_OPT_FREE_CAMERA, port/web main.js 'freecam'). Off = this block does nothing.
 * The N64 follow camera (mode 1 / 0x800, camera_follow_mode_update below) is a lazy chase camera: its yaw +0x37C turns
 * only as far as needed to keep Conker in view, C-left / C-right swing it around him (camera_sideways_tilt), C-down
 * swings it behind him, C-up cycles three distances, and the height over Conker is fixed per distance (+0x348).
 * With the option on, the camera stick (right stick, IJKL, or the mouse under pointer lock; pc_pif.c) also turns the
 * yaw (orbit) and the elevation (pitch) freely, like a modern 3D platformer:
 *  - yaw: +0x37C += stick x * 130 deg/s (+ mouse x * 0.12 deg/pixel). The lazy follow keeps running on top, so when
 *    the player lets go the camera stays where it was put and goes on chasing Conker as on the N64. Conker's stick
 *    steers relative to the camera because the player code takes its heading from this same +0x37C
 *    (g_cur_cam_yaw in objects_run_state_handlers).
 *  - pitch: g_free_camera_pitch (degrees, + = higher, looking down; stick up = look up) moves the eye on the circle
 *    through the N64 eye (wanted distance +0x374, height +0x348): camera_update_eye_orbit takes the shorter
 *    distance from free_camera_wanted_distance and camera_update_eye_height the new height from
 *    free_camera_wanted_height. The elevation stays within -10..70 degrees.
 *  - pitch returns to the N64 height by itself once there was no camera input for 2 s and Conker moves, and at once
 *    (eased) on C-down, the N64's "camera behind Conker" button, which also swings the yaw behind him as before.
 *  - walls: the eye is placed by the N64 code that follows (the horizontal ray casts of camera_update_eye_orbit, the
 *    probe of camera_eye_collision, camera_cylinder_push), so an orbited / pitched camera is pushed out of walls the
 *    same way the N64 camera is.
 * The free camera only holds the camera in single player, in the plain follow camera, with no cutscene, pause, look /
 * aim view, swimming, riding or scripted camera request (free_camera_allowed); anywhere else this returns at once,
 * the game's own camera runs unchanged and the right stick is the C buttons again (pc_pif.c). Never online: the
 * camera stick is not part of the lockstep input, so pc_pif.c answers 0 in a session (and the page forces it off). */
#define FC_F(off) (*(f32 *) (cam + (off)))
f32 g_free_camera_pitch[4];         /* per player: elevation offset in degrees from the N64 eye (+ = higher) */
static f32 free_camera_pitch_vel[4];
static f32 free_camera_idle[4];     /* seconds since the last camera input */
static u8 *free_camera_cam;         /* the camera camera_follow_mode_update is updating with the free camera on */
static s8 free_camera_reason[4];    /* this frame: 0 = the free camera held the camera, else free_camera_allowed's reason */
int port_free_camera_enabled(void);
void port_free_camera_note(int ch, int reason);
void port_free_camera_log(int ch, int engaged, float yaw, float pitch, float dist, float height);

/* 0 when the free camera may hold this camera, else why not (the reasons pc_pif.c's ?freecamlog prints) */
static s32 free_camera_allowed(u8 *cam) {
    u8 *obj = *(u8 **) (cam + 0x3D0);
    u8 *ctl = *(u8 **) (cam + 0x3D4);
    u8 kind = cam[0x23E];
    s32 mode = *(s32 *) (cam + 0x2C);
    s32 req;

    if (!port_free_camera_enabled()) {
        return 1;   /* option off, or online */
    }
    if (g_mp_mode_active != 0) {
        return 2;   /* multiplayer */
    }
    if (g_cutscene_slot_state != 0 || g_cutscene_restart_transition != 0) {
        return 3;   /* cutscene */
    }
    if (g_game_paused != 0 || cam[0x23C] != 0) {
        return 4;   /* paused, or the camera snaps this frame */
    }
    if ((mode != 1 && mode != 0x800) || obj == NULL || ctl == NULL) {
        return 5;   /* not the follow camera */
    }
    if (*(s16 *) (cam + 0x73C) != 0 || ctl[0x120] != 0 || ctl[0x197] != 0 || ctl[0x198] != 0) {
        return 6;   /* look / aim views */
    }
    if (obj[0xAD] != 0) {
        return 7;   /* swimming */
    }
    if (obj[0x102] != 0 || kind == 9 || kind == 0x12 || kind == 0x37 || kind == 0x38 || kind == 0x39 || kind == 0x3B) {
        return 8;   /* riding / vehicle camera kinds */
    }
    req = *(s32 *) (cam + 0x6FC);
    if ((*(s32 *) (cam + 0x6C8) != 0 && req != 0 && req != 4 && req != 0xB && req != 0xD) ||
        (*(s32 *) (cam + 0x84) & 0x08000000)) {
        return 9;   /* a scripted camera request (camera_apply_request: node path 7, target pull 1, fixed views,
                     * look-ats); 0 (the zone's follow distance / height), 4 (hold), 0xB, 0xD (done) leave it free */
    }
    return 0;
}

/* Called first in camera_follow_mode_update: takes the camera input and turns the yaw / pitch. */
static void free_camera_update(u8 *cam) {
    s32 pl = cam[0x23D] & 3;
    f32 dt = FC_F(0x7B4);
    f32 x, y, mx, my, base;
    f32 *pitch = &g_free_camera_pitch[pl];
    s32 reason;

    free_camera_cam = NULL;
    reason = free_camera_allowed(cam);
    free_camera_reason[pl] = reason;
    if (reason != 0) {
        *pitch = 0.0f;
        free_camera_pitch_vel[pl] = 0.0f;
        free_camera_idle[pl] = 0.0f;
        return;
    }
    port_free_camera_engage(pl);
    free_camera_cam = cam;
    x = port_free_camera_axis(pl, 0) / 80.0f;
    y = port_free_camera_axis(pl, 1) / 80.0f;
    mx = (f32) port_free_camera_axis(pl, 2);
    my = (f32) port_free_camera_axis(pl, 3);
    if (x > 1.0f) x = 1.0f; else if (x < -1.0f) x = -1.0f;
    if (y > 1.0f) y = 1.0f; else if (y < -1.0f) y = -1.0f;
    if (x != 0.0f || y != 0.0f || mx != 0.0f || my != 0.0f) {
        free_camera_idle[pl] = 0.0f;
        FC_F(0x37C) += x * 130.0f * dt + mx * 0.12f;   /* stick right = the same way as C-right on the N64 */
        math_wrap_deg_360(&FC_F(0x37C));
        FC_F(0x39C) = FC_F(0x37C) * 0.017453292f;
        *pitch += -y * 75.0f * dt + my * 0.12f;
        free_camera_pitch_vel[pl] = 0.0f;
    } else {
        free_camera_idle[pl] += dt;
        if ((*(u16 *) (cam + 0x36A) & 4) || (free_camera_idle[pl] > 2.0f && *(s16 *) (cam + 0x298) != 0) ||
            free_camera_pitch_vel[pl] != 0.0f) {
            /* recentre (C-down) or idle while Conker moves: ease the pitch back to the N64 height */
            math_spring_approach(pitch, 0.0f, &free_camera_pitch_vel[pl], 2.0f, 4.0f, dt);
            if (*pitch > -0.5f && *pitch < 0.5f) {
                *pitch = 0.0f;
                free_camera_pitch_vel[pl] = 0.0f;
            }
        }
    }
    /* keep the elevation within -10..70 degrees, so a stick held past the limit has nothing to unwind */
    base = math_atan2f(FC_F(0x348), FC_F(0x374)) * 57.295776f;
    if (*pitch < -10.0f - base) *pitch = -10.0f - base; else if (*pitch > 70.0f - base) *pitch = 70.0f - base;
}

/* camera_update_all, around each player's camera update: before (begin = 1) marks "not run", after (begin = 0) tells
 * pc_pif.c who held the camera this frame (for ?freecamlog). The stick itself is handed back by the engage time-out. */
void free_camera_frame(u8 *cam, s32 begin) {
    s32 pl = cam[0x23D] & 3;

    if (begin) {
        free_camera_reason[pl] = -1;
        return;
    }
    if (free_camera_reason[pl] < 0) {   /* the follow camera did not run: say why */
        free_camera_reason[pl] = free_camera_allowed(cam);
        if (free_camera_reason[pl] == 0) {
            free_camera_reason[pl] = 5;
        }
        g_free_camera_pitch[pl] = 0.0f;
    }
    port_free_camera_note(pl, free_camera_reason[pl]);
}

/* elevation of the N64 eye (distance d, height h) plus the player's pitch, kept within -10..70 degrees; radians */
static f32 free_camera_elevation(u8 *cam, f32 d, f32 h) {
    f32 a = math_atan2f(h, d) * 57.295776f + g_free_camera_pitch[cam[0x23D] & 3];

    if (a < -10.0f) a = -10.0f; else if (a > 70.0f) a = 70.0f;
    return a * 0.017453292f;
}
/* camera_update_eye_orbit: the wanted horizontal distance d of the pitched eye (same radius as the N64 eye) */
f32 free_camera_wanted_distance(u8 *cam, f32 d) {
    f32 h;

    if (cam != free_camera_cam || g_free_camera_pitch[cam[0x23D] & 3] == 0.0f) {
        return d;
    }
    h = FC_F(0x348);
    return sqrtf(d * d + h * h) * cosf(free_camera_elevation(cam, d, h));
}
/* camera_update_eye_height: the wanted eye height h over the base of the pitched eye */
f32 free_camera_wanted_height(u8 *cam, f32 h) {
    f32 d;

    if (cam != free_camera_cam || g_free_camera_pitch[cam[0x23D] & 3] == 0.0f) {
        return h;
    }
    d = FC_F(0x374);
    return sqrtf(d * d + h * h) * sinf(free_camera_elevation(cam, d, h));
}
/* camera_update_eye_height: 1 while the player is turning the camera (the height follows with the fast rates) */
s32 free_camera_turning(u8 *cam) {
    return cam == free_camera_cam && free_camera_idle[cam[0x23D] & 3] == 0.0f;
}
#undef FC_F
#endif

/* P41: camera mode 1 (follow). Unless 0xDC == 4: turn yaw 0x37C by the angle between eye->0x2C8 and eye->at
 * (math_angle_diff_deg of the two headings) times the eased rate 0x8DC (toward 0x8D4: 0 when 0x298 is clear, 0.75 for
 * flag 0x100000 of 0x84 or 180 < 0x390 < 270, else 0.5); 0x39C = 0x37C in radians. Then the eye orbit
 * camera_update_eye_orbit, camera_update_eye_height and camera_update_eye_base. */
/* was func_15122EF0 */
void camera_follow_mode_update(u8 *arg0) {
    struct17 eye_to_prev_target;   /* was sp44 */
    struct17 eye_to_target;        /* was sp38 */
    f32 heading_prev;              /* was a */
    f32 heading_now;               /* was b */
    f32 rate;                      /* was v */

#ifdef PORT
    free_camera_update(arg0);   /* P347 option "Free camera": camera stick -> yaw / pitch (nothing when off) */
#endif
    if (*(s32 *)(arg0 + 0xDC) != 4) {
        vec3_diff((struct17 *)(arg0 + 0x2F8), (struct17 *)(arg0 + 0x2C8), &eye_to_prev_target);
        vec3_diff((struct17 *)(arg0 + 0x2F8), (struct17 *)(arg0 + 0x2BC), &eye_to_target);
        heading_prev = vec3_heading_deg(&eye_to_prev_target);
        heading_now = vec3_heading_deg(&eye_to_target);
        if (*(s16 *)(arg0 + 0x298) == 0) {
            rate = 0.0f;
        } else if ((*(s32 *)(arg0 + 0x84) & 0x100000) ||
                   (180.0f < *(f32 *)(arg0 + 0x390) && *(f32 *)(arg0 + 0x390) < 270.0f)) {
            rate = 0.75f;
        } else {
            rate = 0.5f;
        }
        *(f32 *)(arg0 + 0x8D4) = rate;
        math_spring_approach((f32 *)(arg0 + 0x8DC), *(f32 *)(arg0 + 0x8D4), (f32 *)(arg0 + 0x8D8), 1.0f, 2.0f,
                      *(f32 *)(arg0 + 0x7B4));
        *(f32 *)(arg0 + 0x37C) = *(f32 *)(arg0 + 0x37C) + math_angle_diff_deg(heading_prev, heading_now) * *(f32 *)(arg0 + 0x8DC);
        *(f32 *)(arg0 + 0x39C) = *(f32 *)(arg0 + 0x37C) * 0.017453292f;
    }
    camera_update_eye_orbit(arg0);
    camera_update_eye_height(arg0);
    camera_update_eye_base(arg0);
#ifdef PORT
    if (free_camera_cam != NULL) {
        port_free_camera_log(free_camera_cam[0x23D], 1, *(f32 *)(arg0 + 0x37C), g_free_camera_pitch[free_camera_cam[0x23D] & 3],
                             *(f32 *)(arg0 + 0x370), *(f32 *)(arg0 + 0x2FC) - *(f32 *)(arg0 + 0x2C0));
    }
    free_camera_cam = NULL;
#endif
}