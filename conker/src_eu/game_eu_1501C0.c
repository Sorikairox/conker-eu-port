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
extern f32 D_80089860;  /* last yaw (degrees) */
extern f32 D_800A3850;  /* pi / 180 */
extern f32 D_800A3854;  /* pi / 2 */
extern f32 D_800A3858;  /* 999: "no yaw override" in +0x86C */
extern f32 D_800A385C;  /* pi / 180 */
extern f32 D_800A3860, D_800A3864; /* 2.2, 2.2 */
extern f32 D_800A3868;  /* 0.15 */
#define CAMF(off) (*(f32 *) (cam + (off)))

// camera_orbit_update: third-person camera placement around the target cam+0x2BC. Pitch from the target's
// +0x40 (+90 deg) or, when flag 1 of +0x5F0 and the target's +0x102 are clear, +0x39C - pi/2; yaw from +0x86C unless
// it is 999 (then the target's +0xB8, +10 when +0x102, 0 when its +0x1CA is clear), halved when +0x102, clamped to
// +-88 deg and kept at the previous value D_80089860 within 10 deg. Distance 150 when flag 0x10 of *(+0x36C), else
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

    pitch = (*(f32 *) (*(u8 **) (cam + 0x3D0) + 0x40) + 90.0f) * D_800A3850;
    camera_update_eye_base(cam);
    if (!(*(s32 *) (cam + 0x5F0) & 1) && *(*(u8 **) (cam + 0x3D0) + 0x102) == 0) {
        pitch = CAMF(0x39C) - D_800A3854;
    }
    tgt = *(u8 **) (cam + 0x3D0);
    if (D_800A3858 == CAMF(0x86C)) {
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
    prev = D_80089860;
    if (fabsf(prev - yaw) < 10.0f) {
        yaw = prev;
    } else {
        D_80089860 = yaw;
    }
    yaw *= D_800A385C;
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
        rate = D_800A3860 + D_800A3864;
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
    CAMF(0x5E8) += (CAMF(0x5EC) - CAMF(0x5E8)) * D_800A3868;
    dx = CAMF(0x2F8) - CAMF(0x2BC);
    dz = CAMF(0x300) - CAMF(0x2C4);
    CAMF(0x344) = CAMF(0x348) = CAMF(0x2FC) - CAMF(0x354);
    CAMF(0x370) = sqrtf(dx * dx + dz * dz);
}
#undef CAMF

/* P41: camera mode 1 (follow). Unless 0xDC == 4: turn yaw 0x37C by the angle between eye->0x2C8 and eye->at
 * (math_angle_diff_deg of the two headings) times the eased rate 0x8DC (toward 0x8D4: 0 when 0x298 is clear, 0.75 for
 * flag 0x100000 of 0x84 or 180 < 0x390 < 270, else 0.5); 0x39C = 0x37C in radians. Then the eye orbit
 * camera_update_eye_orbit, camera_update_eye_height and camera_update_eye_base. */
/* was func_15122EF0 */
void camera_follow_mode_update(u8 *arg0) {
    struct17 sp44;
    struct17 sp38;
    f32 a;
    f32 b;
    f32 v;

    if (*(s32 *)(arg0 + 0xDC) != 4) {
        vec3_diff((struct17 *)(arg0 + 0x2F8), (struct17 *)(arg0 + 0x2C8), &sp44);
        vec3_diff((struct17 *)(arg0 + 0x2F8), (struct17 *)(arg0 + 0x2BC), &sp38);
        a = vec3_heading_deg(&sp44);
        b = vec3_heading_deg(&sp38);
        if (*(s16 *)(arg0 + 0x298) == 0) {
            v = 0.0f;
        } else if ((*(s32 *)(arg0 + 0x84) & 0x100000) ||
                   (180.0f < *(f32 *)(arg0 + 0x390) && *(f32 *)(arg0 + 0x390) < 270.0f)) {
            v = 0.75f;
        } else {
            v = 0.5f;
        }
        *(f32 *)(arg0 + 0x8D4) = v;
        math_spring_approach((f32 *)(arg0 + 0x8DC), *(f32 *)(arg0 + 0x8D4), (f32 *)(arg0 + 0x8D8), 1.0f, 2.0f,
                      *(f32 *)(arg0 + 0x7B4));
        *(f32 *)(arg0 + 0x37C) = *(f32 *)(arg0 + 0x37C) + math_angle_diff_deg(a, b) * *(f32 *)(arg0 + 0x8DC);
        *(f32 *)(arg0 + 0x39C) = *(f32 *)(arg0 + 0x37C) * 0.017453292f;
    }
    camera_update_eye_orbit(arg0);
    camera_update_eye_height(arg0);
    camera_update_eye_base(arg0);
}