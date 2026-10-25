#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
f32 sinf(f32);
f32 cosf(f32);
f32 sqrtf(f32);
void func_1510ED24(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u16 argA, s32 argB, f32 argC, f32 argD);
extern f32 D_80089900[];  /* per player: up / down speed */
extern f32 D_80089910[];  /* per player: roll / strafe speed */
extern f32 D_80089920[];  /* per player: pitch speed */
extern s32 D_800BEA08;    /* frame time step */
static const f32 freecam_deg2rad[1] = { 0.017453292f };  /* D_800A3A00, D_800A3A28 */
static const f32 freecam_rise_acc[1] = { 0.2f };          /* D_800A3A04 */
static const f32 freecam_fall_acc[1] = { 0.2f };          /* D_800A3A08 */
static const f32 freecam_no_acc[1] = { 0.2f };            /* D_800A3A0C */
static const f32 freecam_pitch_acc[1] = { 0.0125f };      /* D_800A3A10, D_800A3A14 */
static const f32 freecam_roll_k[1] = { 0.1f };            /* D_800A3A18, D_800A3A1C */
static const f32 freecam_strafe_acc[1] = { 0.4f };        /* D_800A3A20, D_800A3A24 */
static const f32 freecam_far[1] = { -10000.0f };          /* D_800A3A2C */

// freecam_update: debug free-fly camera driven by the controller record at cam+0x36C (buttons +0, stick x / y +2 / +3,
// dead zone -4..4). Flag 0x400 in cam+0x36A toggles bit 31 of cam+0x5F0 (frozen): frozen, only the yaw (cam+0x37C) is
// kept and copied to +0x394. Otherwise the stick x turns (yaw +0x37C, quadratic, scaled by the time step D_800BEA08)
// and the stick y moves forward / back (quadratic * 7); C-up / C-down (4 / 8) accelerate up / down (D_80089900[player],
// height +0x2FC), A / B (0x8000 / 0x4000) pitch (D_80089920, +0x388 clamped to +-89.5 degrees), C-right / C-left
// (2 / 1) strafe, or with Z (0x2000) roll (D_80089910, +0x5EC clamped to +-45). The speeds are capped (40 / 100 / 8).
// The position +0x2F8..+0x300 moves along the yaw, the look-at point (+0x2A4 / +0x2BC) is 600 units ahead along yaw
// and pitch; then the view is rebuilt with func_1510ED24 (far -10000).
void func_1512A1A0(u8 *cam) {
    u8 *pad = *(u8 **)(cam + 0x36C);
    u16 buttons = *(u16 *)pad;
    u8 player = *(u8 *)(cam + 0x23D);
    f32 strafe = 0.0f;
    f32 fwd;
    f32 sx, sy, t;
    f32 acc;
    f32 *up = &D_80089900[player];
    f32 *roll = &D_80089910[player];
    f32 *pitch = &D_80089920[player];
    f32 s, c, dx, dz, r, rs, rc;
    f32 ax, ay, az;
    f32 buf[5];

    if (*(u16 *)(cam + 0x36A) & 0x400) {
        if (*(s32 *)(cam + 0x5F0) < 0) {
            *(s32 *)(cam + 0x5F0) &= 0x7FFFFFFF;
        } else {
            *(s32 *)(cam + 0x5F0) |= 0x80000000;
        }
    }
    if (*(s32 *)(cam + 0x5F0) < 0) {
        *(f32 *)(cam + 0x394) = *(f32 *)(cam + 0x37C);
    } else {
        sx = (*(s8 *)(pad + 2) < -4 || *(s8 *)(pad + 2) > 4) ? (f32)*(s8 *)(pad + 2) : 0.0f;
        sy = (*(s8 *)(pad + 3) < -4 || *(s8 *)(pad + 3) > 4) ? (f32)*(s8 *)(pad + 3) : 0.0f;
        t = sx / 80.0f;
        if (0.0f < t) {
            *(f32 *)(cam + 0x37C) -= t * t * (f32)D_800BEA08;
        } else {
            *(f32 *)(cam + 0x37C) += t * t * (f32)D_800BEA08;
        }
        *(f32 *)(cam + 0x39C) = *(f32 *)(cam + 0x37C) * freecam_deg2rad[0];
        t = sy / 80.0f * 7.0f;
        if (0.0f < t) {
            fwd = t * t * (f32)D_800BEA08;
        } else {
            fwd = -t * t * (f32)D_800BEA08;
        }

        if (buttons & 4) {
            acc = freecam_rise_acc[0];
            *up += acc;
            *(f32 *)(cam + 0x2FC) -= *up * (f32)D_800BEA08;
        } else if (buttons & 8) {
            acc = freecam_fall_acc[0];
            *up += acc;
            *(f32 *)(cam + 0x2FC) += *up * (f32)D_800BEA08;
        } else {
            *up = 0.0f;
            acc = freecam_no_acc[0];
        }
        if (buttons & 0x8000) {
            *pitch += freecam_pitch_acc[0];
            *(f32 *)(cam + 0x388) -= *pitch * (f32)D_800BEA08;
        } else if (buttons & 0x4000) {
            *pitch += freecam_pitch_acc[0];
            *(f32 *)(cam + 0x388) += *pitch * (f32)D_800BEA08;
        } else {
            *pitch = 0.0f;
        }
        if (*(f32 *)(cam + 0x388) < -89.5f) {
            *(f32 *)(cam + 0x388) = -89.5f;
        } else {
            *(f32 *)(cam + 0x388) = (89.5f < *(f32 *)(cam + 0x388)) ? 89.5f : *(f32 *)(cam + 0x388);
        }
        *(f32 *)(cam + 0x398) = *(f32 *)(cam + 0x388) * freecam_deg2rad[0];

        if (buttons & 0x2000) {
            if (buttons & 2) {
                *roll += acc;
                *(f32 *)(cam + 0x5EC) -= *roll * freecam_roll_k[0];
            } else if (buttons & 1) {
                *roll += acc;
                *(f32 *)(cam + 0x5EC) += *roll * freecam_roll_k[0];
            } else {
                *roll = 0.0f;
            }
        } else if (buttons & 2) {
            *roll += freecam_strafe_acc[0];
            strafe = 0.0f - *roll;
        } else if (buttons & 1) {
            *roll += freecam_strafe_acc[0];
            { /* P317: volatile zero: IDO folds `0.0f + x` (the asm adds, -0.0 -> +0.0; P310) */
                volatile f32 p317z = 0.0f;
                strafe = p317z + *roll;
            }
        } else {
            *roll = 0.0f;
        }
        *roll = (100.0f < *roll) ? 100.0f : *roll;
        *pitch = (8.0f < *pitch) ? 8.0f : *pitch;
        *up = (40.0f < *up) ? 40.0f : *up;
        if (*(f32 *)(cam + 0x5EC) < -45.0f) {
            *(f32 *)(cam + 0x5EC) = -45.0f;
        } else {
            *(f32 *)(cam + 0x5EC) = (45.0f < *(f32 *)(cam + 0x5EC)) ? 45.0f : *(f32 *)(cam + 0x5EC);
        }

        /* move along the yaw: forward (-sin, -cos), strafe (cos, -sin) */
        s = -sinf(*(f32 *)(cam + 0x39C));
        c = -cosf(*(f32 *)(cam + 0x39C));
        *(f32 *)(cam + 0x2F8) += s * fwd;
        *(f32 *)(cam + 0x300) += c * fwd;
        *(f32 *)(cam + 0x2F8) += -c * strafe;
        *(f32 *)(cam + 0x300) += s * strafe;
        *(f32 *)(cam + 0x344) = 0.0f;

        /* look-at point 600 units ahead, tilted by the pitch */
        dx = s * 600.0f;
        dz = c * 600.0f;
        r = sqrtf(dx * dx + dz * dz);
        rs = sinf(*(f32 *)(cam + 0x398)) * r;
        rc = cosf(*(f32 *)(cam + 0x398));
        dx = rc * dx;
        dz = cosf(*(f32 *)(cam + 0x398)) * dz;
        ax = *(f32 *)(cam + 0x2F8) + dx;
        ay = *(f32 *)(cam + 0x2FC) + rs;
        az = *(f32 *)(cam + 0x300) + dz;
        *(f32 *)(cam + 0x2A4) = *(f32 *)(cam + 0x2BC) = ax;
        *(f32 *)(cam + 0x2A8) = *(f32 *)(cam + 0x2C0) = ay;
        *(f32 *)(cam + 0x2AC) = *(f32 *)(cam + 0x2C4) = az;
        *(f32 *)(cam + 0x390) = 0.0f;
    }
    *(f32 *)(cam + 0x380) = *(f32 *)(cam + 0x37C);
    *(f32 *)(cam + 0x39C) = *(f32 *)(cam + 0x3A0) = *(f32 *)(cam + 0x37C) * freecam_deg2rad[0];
    func_1510ED24((s32)(cam + 0x644), (s32)(cam + 0x648), (s32)buf, (s32)(cam + 0x360), (s32)(cam + 0x640), 0,
                  *(f32 *)(cam + 0x2F8), *(f32 *)(cam + 0x2FC), *(f32 *)(cam + 0x300), *(f32 *)(cam + 0x2FC), 0, 0,
                  freecam_far[0], *(f32 *)(cam + 0x2FC));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1579B0/func_1512A1A0.s")
#endif

void func_1512A8D0(u8 *arg0) {
    func_151E73C8(arg0[0x23D], arg0);
}
