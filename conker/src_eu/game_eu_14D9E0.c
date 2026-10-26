#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
void camera_look_mode_defaults(u8 *arg0);


void aim_hud_spawn_for_mode(u8 *arg0, s32 arg1); // defined in game_eu_1F7960 (two arguments)

/* was func_151201D0 */
void camera_look_enter(u8 *arg0) {
    s32 sp20;
    u8 *sp1C;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f12;
    f32 temp_f2;
    u8 temp_v0;
    u8 temp_v0_2;
    u8 *var_v1;

    temp_v0 = (*(u8 *)((u8 *)arg0 + 0x23E));
    (*(s16 *)((u8 *)arg0 + 0x84A)) = 0x32;
    if (((*(s32 *)((u8 *)arg0 + 0x5F0)) & 2) || (temp_v0 == 9) || (temp_v0 == 0x38) || (temp_v0 == 0x39) || (temp_v0 == 0x37) || (var_v1 = arg0 + 0x740, (temp_v0 == 0x3B))) {
        var_v1 = arg0 + 0x740;
        (*(s8 *)((u8 *)var_v1 + 0x4D)) = 0;
        (*(s8 *)((u8 *)var_v1 + 0x4D)) = 1;
    } else {
        (*(s8 *)((u8 *)var_v1 + 0x4D)) = 1;
    }
    (*(s8 *)((u8 *)arg0 + 0x84C)) = 0;
    if ((*(s32 *)((u8 *)arg0 + 0x34)) == 0x40) {
        (*(f32 *)((u8 *)var_v1 + 0x34)) = (f32) (*(f32 *)((u8 *)arg0 + 0x37C));
    } else if ((*(u8 *)((u8 *)var_v1 + 0x4D)) != 0) {
        temp_v0_2 = (*(u8 *)((u8 *)arg0 + 0x23E));
        if ((temp_v0_2 == 9) || (temp_v0_2 == 0x38) || (temp_v0_2 == 0x39) || (temp_v0_2 == 0x37) || (temp_v0_2 == 0x3B) || (temp_v0_2 == 0x15) || (temp_v0_2 == 0x26) || (temp_v0_2 == 0x3A)) {
            (*(f32 *)((u8 *)var_v1 + 0x34)) = (f32) ((f32) (((*(u16 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x3D0))) + 0x7A)) - (*(s16 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x3D4))) + 0x12))) + 0xC000) * 0.005493164f);
        } else if ((g_hint_action == 0x42) && (temp_v0 == 0x1A)) {
            (*(f32 *)((u8 *)var_v1 + 0x34)) = (f32) (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x3D0))) + 0x40));
        } else {
            (*(f32 *)((u8 *)var_v1 + 0x34)) = (f32) ((*(f32 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x3D0))) + 0x40)) - 180.0f);
        }
    } else {
        (*(f32 *)((u8 *)var_v1 + 0x34)) = (f32) (*(f32 *)((u8 *)arg0 + 0x37C));
        (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) & ~0x280);
    }
    if ((temp_v0 == 9) || (temp_v0 == 0x38) || (temp_v0 == 0x39) || (temp_v0 == 0x37) || (temp_v0 == 0x3B) || (temp_v0 == 0x15) || (temp_v0 == 0x26) || (temp_v0 == 0x3A)) {
        (*(f32 *)((u8 *)var_v1 + 0x38)) = 0.0f;
        (*(f32 *)((u8 *)var_v1 + 0x3C)) = 0.0f;
        sp20 = (s32) temp_v0;
        sp1C = var_v1;
        aim_hud_spawn_for_mode(arg0, temp_v0);
        (*(s8 *)((u8 *)arg0 + 0x84C)) = 1;
    } else {
        if ((temp_v0 == 2) || (temp_v0 == 0x13)) {
            (*(f32 *)((u8 *)var_v1 + 0x38)) = 0.0f;
            goto block_43;
        }
        if (temp_v0 != 0x1C) {
            if (temp_v0 == 0x34) {
                (*(f32 *)((u8 *)var_v1 + 0x38)) = 0.0f;
                goto block_43;
            }
            if (temp_v0 == 0xF) {
                (*(f32 *)((u8 *)var_v1 + 0x38)) = 27.0f;
                (*(f32 *)((u8 *)var_v1 + 0x3C)) = 27.0f;
                (*(f32 *)((u8 *)var_v1 + 0x34)) = (f32) ((*(f32 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x3D0))) + 0x40)) + 225.0f);
            } else {
                (*(f32 *)((u8 *)var_v1 + 0x38)) = 0.0f;
block_43:
                (*(f32 *)((u8 *)var_v1 + 0x3C)) = 0.0f;
            }
        }
    }
    sp1C = var_v1;
    sp20 = (s32) temp_v0;
    camera_look_mode_defaults(arg0);
    math_wrap_deg_360(var_v1 + 0x34);
    if ((*(u8 *)((u8 *)var_v1 + 0x4C)) != 0) {
        temp_f0 = (*(f32 *)((u8 *)var_v1 + 0x50));
        (*(f32 *)((u8 *)var_v1 + 0x38)) = temp_f0;
        (*(f32 *)((u8 *)var_v1 + 0x3C)) = temp_f0;
        (*(f32 *)((u8 *)var_v1 + 0x44)) = (f32) (*(f32 *)((u8 *)var_v1 + 0x58));
        (*(f32 *)((u8 *)var_v1 + 0x34)) = (f32) ((*(f32 *)((u8 *)var_v1 + 0x34)) + (*(f32 *)((u8 *)var_v1 + 0x54)));
    }
    (*(f32 *)((u8 *)var_v1 + 0x20)) = (f32) (*(f32 *)((u8 *)arg0 + 0x37C));
    (*(f32 *)((u8 *)var_v1 + 0x2C)) = (f32) (*(s32 *)((u8 *)arg0 + 0x134));
    if ((*(u8 *)((u8 *)arg0 + 0x92C)) != 0) {
        temp_f2 = (*(f32 *)((u8 *)arg0 + 0x2BC)) - (*(f32 *)((u8 *)arg0 + 0x2F8));
        temp_f12 = (*(f32 *)((u8 *)arg0 + 0x2C4)) - (*(f32 *)((u8 *)arg0 + 0x300));
        (*(f32 *)((u8 *)var_v1 + 0x24)) = sqrtf((temp_f2 * temp_f2) + (temp_f12 * temp_f12));
        (*(f32 *)((u8 *)var_v1 + 0x28)) = (f32) (*(f32 *)((u8 *)arg0 + 0x344));
        (*(f32 *)((u8 *)var_v1 + 0x30)) = (f32) (*(f32 *)((u8 *)arg0 + 0x354));
    } else {
        (*(f32 *)((u8 *)var_v1 + 0x24)) = (f32) (*(f32 *)((u8 *)arg0 + 0x374));
        (*(f32 *)((u8 *)var_v1 + 0x28)) = (f32) (*(f32 *)((u8 *)arg0 + 0x348));
        (*(f32 *)((u8 *)var_v1 + 0x30)) = (f32) (*(f32 *)((u8 *)arg0 + 0x354));
    }
    temp_f0_2 = (*(f32 *)((u8 *)arg0 + 0x2C0));
    (*(f32 *)((u8 *)arg0 + 0x35C)) = temp_f0_2;
    (*(f32 *)((u8 *)arg0 + 0x354)) = temp_f0_2;
    (*(f32 *)((u8 *)var_v1 + 0x44)) = 110.0f;
    (*(f32 *)((u8 *)arg0 + 0x348)) = 30.0f;
    (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x3D4))) + 0x16C)) = (f32) (*(f32 *)((u8 *)var_v1 + 0x34));
    if ((temp_v0 == 0) || (temp_v0 == 0xC) || (temp_v0 == 9) || (temp_v0 == 0x38) || (temp_v0 == 0x39) || (temp_v0 == 0x37) || (temp_v0 == 0x3B) || (temp_v0 == 0x15) || (temp_v0 == 0x26) || (temp_v0 == 0x3A)) {
        (*(f32 *)((u8 *)arg0 + 0x348)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x348)) + 30.0f);
    }
    (*(s32 *)((u8 *)var_v1 + 0x64)) = 0;
    (*(s16 *)((u8 *)arg0 + 0x73C)) = 1;
    if ((*(u8 *)((u8 *)arg0 + 0x23C)) != 0) {
        (*(f32 *)((u8 *)var_v1 + 0x34)) = (f32) ((*(f32 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x3D0))) + 0x40)) - 180.0f);
        (*(f32 *)((u8 *)arg0 + 0x37C)) = (f32) (*(f32 *)((u8 *)var_v1 + 0x34));
        (*(f32 *)((u8 *)arg0 + 0x194)) = (f32) (*(f32 *)((u8 *)arg0 + 0x198));
        (*(f32 *)((u8 *)arg0 + 0x18C)) = (f32) (*(f32 *)((u8 *)arg0 + 0x190));
        (*(f32 *)((u8 *)arg0 + 0x39C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x37C)) * 0.017453292f);
    }
    temp_f0_3 = (*(f32 *)((u8 *)var_v1 + 0x44));
    if (temp_f0_3 < (*(f32 *)((u8 *)arg0 + 0x370))) {
        (*(s8 *)((u8 *)var_v1 + 0x4E)) = -1;
        (*(f32 *)((u8 *)var_v1 + 0x48)) = (f32) (temp_f0_3 * 1.2f);
    } else {
        (*(s8 *)((u8 *)var_v1 + 0x4E)) = 1;
        (*(f32 *)((u8 *)var_v1 + 0x48)) = (f32) (temp_f0_3 * 0.666666f);
    }
    if ((temp_v0 == 0xA) || (temp_v0 == 2) || (temp_v0 == 0x12) || (temp_v0 == 3) || (temp_v0 == 0x34)) {
        (*(s8 *)((u8 *)var_v1 + 0x4E)) = -1;
        (*(f32 *)((u8 *)var_v1 + 0x48)) = (f32) (*(f32 *)((u8 *)arg0 + 0x374));
    }
    (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) & ~0x280);
    (*(f32 *)((u8 *)arg0 + 0x374)) = (f32) (*(f32 *)((u8 *)var_v1 + 0x44));
}
// Camera state block at player +0x740 (shared by camera_look_enter / camera_look_mode_defaults / camera_look_exit).
typedef struct {
    f32 eye[3];    // 0x00: camera position (orbit point behind the player)
    f32 offX;      // 0x0C: sideways look offset x / z (eased)
    f32 unk10;
    f32 offZ;      // 0x14
    f32 yawVel;    // 0x18: easing state of yaw / pitch (math_spring_approach_angle)
    f32 pitchVel;  // 0x1C
    f32 yawGoal;   // 0x20: mode 3 (return) target yaw
    f32 dist3;     // 0x24: mode 3 distance / height / y
    f32 height3;   // 0x28
    f32 unk2C;
    f32 y3;        // 0x30
    f32 yawTarget; // 0x34
    f32 pitchTarget; // 0x38
    f32 pitch;     // 0x3C
    f32 pitchSigned; // 0x40: pitch in (-180, 180]
    f32 dist;      // 0x44
    f32 distLimit; // 0x48: mode 1 ends once the player is closer / farther than this
    u8 force;      // 0x4C
    u8 follow;     // 0x4D
    s8 dir;        // 0x4E: -1 = approach, else move away
    u8 pad4F[0xD];
    f32 offXVel;   // 0x5C
    f32 offZVel;   // 0x60
    s32 stickLock; // 0x64: 1 / 2 = stick x held right / left when the lock started
} CameraState;

#define PF32(o) (*(f32 *) (arg0 + (o)))
#define PS32(o) (*(s32 *) (arg0 + (o)))
#define PS16(o) (*(s16 *) (arg0 + (o)))
#define PU8(o) (*(u8 *) (arg0 + (o)))
#define PPTR(o) (*(u8 **) (arg0 + (o)))
// riding / vehicle camera modes (+0x23E)
#define CAM_MODE_RIDE(m) ((m) == 9 || (m) == 0x38 || (m) == 0x39 || (m) == 0x37 || (m) == 0x3B || (m) == 0x15 || \
                          (m) == 0x26 || (m) == 0x3A)

void collision_find_floor(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9,
                   u16 argA, s32 argB, f32 argC, f32 argD);
void math_spring_approach_angle(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5);
void math_spring_approach(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5);
void camera_look_exit(u8 *arg0);
void camera_update_eye_orbit(u8 *arg0);
void camera_update_eye_height(u8 *arg0);
void aim_hud_clear(u8 *arg0);

// player_camera_update: per-frame player camera (+0x740 block, camera object +0x3D4, player object +0x3D0,
// controller +0x36C). Gets the floor height under the camera (collision_find_floor), the player distance +0x370, sets the
// per-mode defaults (+0x23E), then runs the camera state +0x73C: 1 = moving into place (timer +0x84A, ends when
// close enough or not following), 2 = free orbit from the stick (yaw / pitch with per-mode pitch limits, riding
// modes take the yaw from the vehicle), 3 = returning to the default view (timer +0x84A, until the yaw is within
// 0.05 degrees). Then the sideways look offset (aim modes) is eased in and added to the camera, and the view is
// rebuilt (vec3_dir_to, camera_update_eye_orbit, camera_update_eye_height, camera_sync_angles).
/* was func_151206C8 */
void camera_look_update(u8 *arg0) {
    CameraState *cam = (CameraState *) (arg0 + 0x740);
    s32 mode;
    s32 special;
    f32 floorY;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 rate;
    f32 angle;
    f32 lim;
    f32 off;
    f32 ox;
    f32 oz;
    s32 ci;
    s32 reach;
    s32 dirBits;
    s8 sx;
    u8 *pad;
    u8 *view;

    mode = PU8(0x23E);
    special = (g_hint_action == 0x42) && (mode == 0x1A);
    collision_find_floor(0, 0, (s32) &floorY, (s32) (arg0 + 0x360), 0, 0, PF32(0x2F8), PF32(0x2FC), PF32(0x300), PF32(0x2FC), 0,
                  0, -10000.0f, PF32(0x2FC));
    *(s8 *) (PPTR(0x3D4) + 0x198) = PS16(0x73C);
    dx = PF32(0x2F8) - PF32(0x2BC);
    dz = PF32(0x300) - PF32(0x2C4);
    PF32(0x370) = sqrtf(dx * dx + dz * dz);
    if (PU8(0x23C) != 0) {
        PF32(0x770) = floorY;
    }
    if (mode != 0x2A && PS16(0x73C) != 3) {
        if (mode == 0xD) {
            PF32(0x190) = 100.0f;
        } else if (mode == 3) {
            cam->pitchTarget = 15.0f;
            PF32(0x198) = 0.0f;
            cam->dist = 350.0f;
            if (PU8(0x600) != 0) {
                cam->pitch = cam->pitch * (PF32(0x604) * 0.00285714283f);
                if (cam->pitch < 0.0f) {
                    cam->pitch = 0.0f;
                }
            }
        } else if (special) {
            PF32(0x190) = 18.0f;
            PF32(0x198) = 60.0f;
            cam->dist = 250.0f;
            cam->yawTarget = *(f32 *) (PPTR(0x3D0) + 0x40);
        } else if (mode == 0x1A) {
            PF32(0x190) = 35.0f;
            PF32(0x198) = 100.0f;
            cam->dist = 250.0f;
        } else {
            PF32(0x190) = 20.0f;
            PF32(0x198) = 0.0f;
            camera_look_mode_defaults(arg0);
        }
    }
    PF32(0x354) = PF32(0x2C0);
    PF32(0x35C) = PF32(0x2C0);
    obj_fade_command((struct127 *) PPTR(0x3D0), 2, 0xFF, 0x20, PU8(0x23D));
    dist = cam->dist;

    if (PS16(0x73C) == 1) {
        // moving into place
        if (PS16(0x84A) != 0) {
            PS16(0x84A) = PS16(0x84A) - g_frame_ticks;
            if (PS16(0x84A) <= 0) {
                *(s8 *) (PPTR(0x3D4) + 0x198) = 1;
                PS16(0x73C) = 2;
                cam->yawTarget = PF32(0x37C);
                return;
            }
        }
        PS32(0x134) = 1;
        ci = (s32) (cosf(cam->pitch * 0.017453292f) * dist);
        angle = sinf(cam->pitch * 0.017453292f);
        PF32(0x374) = ci;
        PF32(0x348) = (s32) (angle * dist);
        if (PU8(0x23C) != 0) {
            if (special) {
                cam->yawTarget = *(f32 *) (PPTR(0x3D0) + 0x40);
            } else {
                cam->yawTarget = *(f32 *) (PPTR(0x3D0) + 0x40) - 180.0f;
            }
            PF32(0x37C) = cam->yawTarget;
            PF32(0x194) = PF32(0x198);
            PF32(0x18C) = PF32(0x190);
            PF32(0x39C) = PF32(0x37C) * 0.017453292f;
        }
        if (cam->follow != 0) {
            math_angle_diff_deg(PF32(0x37C), cam->yawTarget); // result unused (compared with 0.01, no effect)
            if (cam->dir == -1) {
                reach = PF32(0x370) < cam->distLimit;
            } else {
                reach = cam->distLimit < PF32(0x370);
            }
            if (reach || cam->force != 0) {
                if (PU8(0x600) != 0) {
                    math_spring_approach_angle(&PF32(0x37C), cam->yawTarget, &cam->yawVel, 10.0f, 18.0f, PF32(0x7B4));
                } else {
                    math_spring_approach_angle(&PF32(0x37C), cam->yawTarget, &cam->yawVel, 5.0f, 9.0f, PF32(0x7B4));
                }
                math_spring_approach(&PF32(0x194), PF32(0x198), &PF32(0x7D0), 5.0f, 9.0f, PF32(0x7B4));
                math_spring_approach(&PF32(0x18C), PF32(0x190), &PF32(0x7D4), 5.0f, 9.0f, PF32(0x7B4));
                PF32(0x39C) = PF32(0x37C) * 0.017453292f;
            }
        } else {
            *(s8 *) (PPTR(0x3D4) + 0x198) = 1;
            PS16(0x73C) = 2;
        }
    } else if (PS16(0x73C) == 2) {
        // free orbit
        rate = (mode != 0) ? 0.0128f : 0.025f;
        if (PU8(0x23C) != 0) {
            if (special) {
                cam->yawTarget = *(f32 *) (PPTR(0x3D0) + 0x40);
            } else {
                cam->yawTarget = *(f32 *) (PPTR(0x3D0) + 0x40) - 180.0f;
            }
            PF32(0x37C) = cam->yawTarget;
            PF32(0x194) = PF32(0x198);
            PF32(0x18C) = PF32(0x190);
            PF32(0x39C) = PF32(0x37C) * 0.017453292f;
        }
        if (CAM_MODE_RIDE(mode)) {
            if (PU8(0x84C) == 0) {
                aim_hud_spawn_for_mode(arg0, mode);
                PU8(0x84C) = 1;
            }
        } else if (PU8(0x84C) != 0) {
            aim_hud_clear(arg0);
            PU8(0x84C) = 0;
        }
        if (mode != 0xD) {
            if (cam->follow == 0) {
                if (PU8(0x3E8) != 0) {
                    cam->stickLock = 0;
                } else {
                    if (cam->stickLock == 0) {
                        sx = (s8) PPTR(0x36C)[2];
                        if (sx > 0) {
                            dirBits = 1;
                        } else if (sx < 0) {
                            dirBits = 2;
                        } else {
                            dirBits = 0;
                        }
                        cam->stickLock = cam->stickLock | dirBits;
                    }
                    // camera look point = player head position (word copies)
                    PS32(0x2F8) = PS32(0x304);
                    PS32(0x2FC) = PS32(0x308);
                    PS32(0x300) = PS32(0x30C);
                    pad = PPTR(0x36C);
                    if (cam->stickLock & 1) {
                        if ((s8) pad[2] > 0) {
                            pad[2] = 0;
                        }
                    } else if (cam->stickLock & 2) {
                        if ((s8) pad[2] < 0) {
                            pad[2] = 0;
                        }
                    }
                }
            }
            if (CAM_MODE_RIDE(mode)) {
                cam->yawTarget = (f32) ((*(u16 *) (PPTR(0x3D0) + 0x7A) - *(s16 *) (PPTR(0x3D4) + 0x12)) + 0xC000) *
                                 0.0054931640625f;
            } else if (special) {
                cam->yawTarget = *(f32 *) (PPTR(0x3D0) + 0x40);
            } else if (mode != 0xF) {
                if (PS32(0x5F0) & 2) {
                    cam->yawTarget = (((f32) *(u16 *) (PPTR(0x3D0) + 0x7A) -
                                       (f32) *(s16 *) (PPTR(0x3D4) + 0x12) * 0.35f) + 49152.0f) * 0.0054931640625f;
                } else {
                    if (mode == 0x34) {
                        cam->yawTarget = cam->yawTarget - (f32) (s8) PPTR(0x36C)[2] * rate * (f32) g_frame_ticks;
                    }
                    cam->yawTarget = cam->yawTarget - (f32) (s8) PPTR(0x36C)[2] * rate * (f32) g_frame_ticks;
                }
            }
            if (mode != 3 && mode != 0x1A && !special && mode != 0xF) {
                cam->pitchTarget = cam->pitchTarget + (f32) (s8) PPTR(0x36C)[3] * rate * (f32) g_frame_ticks;
            }
            if (mode == 0x38) {
                // follow the vehicle's pitch change since the last frame (+0x8B4)
                if (*(u16 *) PPTR(0x36C) & 0x2000) {
                    off = PF32(0x8B4) - (f32) (*(u16 *) (*(u8 **) (PPTR(0x3D0) + 0x31C) + 0x1A2) >> 8) * 1.0986328125f;
                } else {
                    off = 0.0f;
                }
                cam->pitchTarget = cam->pitchTarget + off;
                PF32(0x8B4) = (f32) (*(u16 *) (*(u8 **) (PPTR(0x3D0) + 0x31C) + 0x1A2) >> 8) * 1.0986328125f;
            }
            math_wrap_deg_360(&cam->yawTarget);
            // pitch limits per mode
            if (mode == 0x34) {
                lim = -5.0f;
                if (cam->pitchTarget < lim) {
                } else if (15.0f < cam->pitchTarget) {
                    lim = 15.0f;
                } else {
                    lim = cam->pitchTarget;
                }
            } else if (mode == 0x12) {
                lim = -40.0f;
                if (cam->pitchTarget < lim) {
                } else if (15.0f < cam->pitchTarget) {
                    lim = 15.0f;
                } else {
                    lim = cam->pitchTarget;
                }
            } else if (mode == 2 || mode == 0xA || mode == 0x13) {
                lim = -37.0f;
                if (cam->pitchTarget < lim) {
                } else if (30.0f < cam->pitchTarget) {
                    lim = 30.0f;
                } else {
                    lim = cam->pitchTarget;
                }
            } else {
                lim = -45.0f;
                if (cam->pitchTarget < lim) {
                } else if (80.0f < cam->pitchTarget) {
                    lim = 80.0f;
                } else {
                    lim = cam->pitchTarget;
                }
            }
            cam->pitchTarget = lim;
            if (g_mp_mode_active == 0 && CAM_MODE_RIDE(mode)) {
                if (cam->pitchTarget < -20.0f) {
                    cam->pitchTarget = -20.0f;
                }
            }
            if (PU8(0x23C) != 0) {
                PF32(0x37C) = cam->yawTarget;
                cam->pitch = cam->pitchTarget;
                PF32(0x194) = PF32(0x198);
                PF32(0x18C) = PF32(0x190);
            } else if (mode != 0 || special) {
                math_spring_approach_angle(&PF32(0x37C), cam->yawTarget, &cam->yawVel, 3.91f, 8.21f, PF32(0x7B4));
                math_spring_approach_angle(&cam->pitch, cam->pitchTarget, &cam->pitchVel, 3.91f, 8.21f, PF32(0x7B4));
                math_spring_approach(&PF32(0x194), PF32(0x198), &PF32(0x7D0), 3.91f, 8.21f, PF32(0x7B4));
                math_spring_approach(&PF32(0x18C), PF32(0x190), &PF32(0x7D4), 3.91f, 8.21f, PF32(0x7B4));
            } else {
                math_spring_approach_angle(&PF32(0x37C), cam->yawTarget, &cam->yawVel, 4.3f, 7.3f, PF32(0x7B4));
                math_spring_approach_angle(&cam->pitch, cam->pitchTarget, &cam->pitchVel, 4.3f, 7.3f, PF32(0x7B4));
            }
        }
        view = PPTR(0x3D4);
        *(f32 *) (view + 0x16C) = PF32(0x37C);
        view = PPTR(0x3D4);
        *(f32 *) (view + 0x170) = cam->pitch;
        view = PPTR(0x3D4);
        *(s32 *) (view + 0x148) = PS32(0x2BC);
        *(s32 *) (view + 0x14C) = PS32(0x2C0);
        *(s32 *) (view + 0x150) = PS32(0x2C4);
        view = PPTR(0x3D4);
        *(s32 *) (view + 0x13C) = PS32(0x2F8);
        *(s32 *) (view + 0x140) = PS32(0x2FC);
        *(s32 *) (view + 0x144) = PS32(0x300);
        while (180.0f < *(f32 *) (PPTR(0x3D4) + 0x170)) {
            *(f32 *) (PPTR(0x3D4) + 0x170) = *(f32 *) (PPTR(0x3D4) + 0x170) - 360.0f;
        }
        while (*(f32 *) (PPTR(0x3D4) + 0x170) < -180.0f) {
            *(f32 *) (PPTR(0x3D4) + 0x170) = *(f32 *) (PPTR(0x3D4) + 0x170) + 360.0f;
        }
        ox = cosf(cam->pitch * 0.017453292f) * dist; // stored after the sinf call
        angle = sinf(cam->pitch * 0.017453292f);
        PF32(0x374) = ox;
        PF32(0x348) = angle * dist;
        cam->eye[0] = sinf(PF32(0x37C) * 0.017453292f + 3.1415927f) * dist + PF32(0x2BC);
        cam->eye[1] = sinf(cam->pitch * 0.017453292f + 3.1415927f) * dist + PF32(0x2C0);
        cam->eye[2] = cosf(PF32(0x37C) * 0.017453292f + 3.1415927f) * dist + PF32(0x2C4);
        if (180.0f <= cam->pitch) {
            cam->pitchSigned = cam->pitch - 360.0f;
        } else {
            cam->pitchSigned = cam->pitch;
        }
        camera_look_exit(arg0);
    } else if (PS16(0x73C) == 3) {
        // returning to the default view
        angle = fabsf(math_angle_diff_deg(PF32(0x37C), cam->yawGoal));
        PS32(0x134) = PS32(0x13C);
        if (PS16(0x84A) != 0) {
            PS16(0x84A) = PS16(0x84A) - g_frame_ticks;
            if (PS16(0x84A) <= 0) {
                *(s8 *) (PPTR(0x3D4) + 0x198) = 0;
                PS16(0x73C) = 0;
                return;
            }
        }
        if ((PS32(0x84) & 0x200000) || CAM_MODE_RIDE(PU8(0x23E))) {
            cam->follow = 0;
        }
        if (cam->follow == 0 || angle < 45.0f) {
            PF32(0x374) = cam->dist3;
            PF32(0x348) = cam->height3;
            if ((PS32(0x5F0) & 0x40) || PF32(0x360) != 0.0f) {
                PF32(0x35C) = cam->y3;
                PF32(0x354) = cam->y3;
            } else {
                PF32(0x35C) = *(f32 *) (PPTR(0x3D0) + 0x180);
                PF32(0x354) = *(f32 *) (PPTR(0x3D0) + 0x180);
            }
        }
        if (cam->follow == 0 || angle < 0.05f) {
            *(s8 *) (PPTR(0x3D4) + 0x198) = 0;
            PS16(0x73C) = 0;
        } else {
            math_spring_approach_angle(&PF32(0x37C), cam->yawGoal, &cam->yawVel, 5.0f, 9.0f, PF32(0x7B4));
        }
    }

    // sideways look offset (aim modes), eased in, added to the camera and its target
    PF32(0x39C) = PF32(0x37C) * 0.017453292f;
    if (mode == 2 || mode == 0x13 || mode == 0x12 || mode == 0xA || mode == 0x34) {
        if (PS32(0x5F0) & 2) {
            off = cam->yawTarget * -3.0f;
        } else {
            off = -35.0f;
        }
        ox = sinf(PF32(0x39C) - 1.5707964f) * off;
        oz = cosf(PF32(0x39C) - 1.5707964f) * off;
        if (PU8(0x23C) != 0) {
            cam->offX = ox;
            cam->offZ = oz;
            cam->offXVel = 0.0f;
        } else {
            math_spring_approach(&cam->offX, ox, &cam->offXVel, 4.0f, 9.0f, PF32(0x7B4));
            math_spring_approach(&cam->offZ, oz, &cam->offZVel, 4.0f, 9.0f, PF32(0x7B4));
        }
    } else {
        math_spring_approach(&cam->offX, 0.0f, &cam->offXVel, 4.0f, 9.0f, PF32(0x7B4));
        math_spring_approach(&cam->offZ, 0.0f, &cam->offZVel, 4.0f, 9.0f, PF32(0x7B4));
    }
    view = PPTR(0x3D4);
    *(f32 *) (view + 0x148) = *(f32 *) (view + 0x148) + cam->offX;
    view = PPTR(0x3D4);
    *(f32 *) (view + 0x150) = *(f32 *) (view + 0x150) + cam->offZ;
    view = PPTR(0x3D4);
    *(f32 *) (view + 0x13C) = *(f32 *) (view + 0x13C) + cam->offX;
    view = PPTR(0x3D4);
    *(f32 *) (view + 0x144) = *(f32 *) (view + 0x144) + cam->offZ;
    view = PPTR(0x3D4);
    vec3_dir_to((struct17 *) (view + 0x13C), (struct17 *) (view + 0x148), (struct17 *) (view + 0x130));
    camera_update_eye_orbit(arg0);
    camera_update_eye_height(arg0);
    camera_sync_angles((struct108 *) arg0);
}
#undef PF32
#undef PS32
#undef PS16
#undef PU8
#undef PPTR
#undef CAM_MODE_RIDE

/* was func_15121A00 */
void camera_ride_view_set(struct127 *arg0, u16 *arg1) {
    struct {
        f32 u28;
        f32 u2C;
        f32 u30;
        f32 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
    } sp;
    f32 sp24;
    f32 temp_f12;
    f32 temp_f16;
    f32 temp_f6;
    f32 temp_f6_2;
    struct126 *temp_v1;
    u8 temp_v0;

    arg0->unk31C->unk198 = 0;
    if ((*arg1 & 0x10) && ((temp_v1 = arg0->unk31C, temp_v0 = temp_v1->unk78, (temp_v0 == 9)) || (temp_v0 == 0x38) || (temp_v0 == 0x39) || (temp_v0 == 0x37) || (temp_v0 == 0x3B) || (temp_v0 == 0x15) || (temp_v0 == 0x26) || (temp_v0 == 0x3A))) {
        sp.u44 = arg0->x_position;
        temp_f12 = (arg0->unk40 - 90.0f) * 0.017453292f;
        sp.u48 = arg0->y_position + ((f32) (s16) temp_v1->unk114 * 0.75f);
        sp.u4C = arg0->z_position;
        (*(f32 *)((u8 *)(&sp.u38) + 0)) = (*(f32 *)((u8 *)(&sp.u44) + 0));
        (*(s32 *)((u8 *)(&sp.u38) + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u44) + 4));
        (*(s32 *)((u8 *)(&sp.u38) + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u44) + 8));
        sp.u34 = temp_f12;
        temp_f6 = sinf(temp_f12) * 100.0f;
        sp.u48 = sp.u3C;
        sp.u44 = temp_f6 + sp.u38;
        sp.u4C = (cosf(temp_f12) * 100.0f) + sp.u40;
        sp.u3C += arg0->y_position - arg0->old_y_position;
        (*(f32 *)((u8 *)temp_v1 + 0x13C)) = (f32) (*(f32 *)((u8 *)(&sp.u38) + 0));
        (*(s32 *)((u8 *)temp_v1 + 0x140)) = (s32) (*(s32 *)((u8 *)(&sp.u38) + 4));
        (*(s32 *)((u8 *)temp_v1 + 0x144)) = (s32) (*(s32 *)((u8 *)(&sp.u38) + 8));
        (*(f32 *)((u8 *)temp_v1 + 0x148)) = (f32) (*(f32 *)((u8 *)(&sp.u44) + 0));
        (*(s32 *)((u8 *)temp_v1 + 0x14C)) = (s32) (*(s32 *)((u8 *)(&sp.u44) + 4));
        temp_v1->unk198 = 1;
        (*(s32 *)((u8 *)temp_v1 + 0x150)) = (s32) (*(s32 *)((u8 *)(&sp.u44) + 8));
        sp.u28 = 1.0f;
        sp24 = cosf((*(f32 *)((u8 *)temp_v1 + 0x170)) * -0.017453292f) * sp.u28;
        temp_f16 = sinf((*(f32 *)((u8 *)temp_v1 + 0x170)) * -0.017453292f) * sp.u28;
        sp.u28 = sp24;
        sp.u2C = temp_f16;
        sp24 = cosf((*(f32 *)((u8 *)temp_v1 + 0x16C)) * -0.017453292f) * sp.u28;
        temp_f6_2 = sinf((*(f32 *)((u8 *)temp_v1 + 0x16C)) * -0.017453292f) * sp.u28;
        sp.u28 = sp24;
        sp.u30 = temp_f6_2;
        (*(f32 *)((u8 *)temp_v1 + 0x130)) = (f32) (*(f32 *)((u8 *)(&sp.u28) + 0));
        (*(s32 *)((u8 *)temp_v1 + 0x134)) = (s32) (*(s32 *)((u8 *)(&sp.u28) + 4));
        (*(s32 *)((u8 *)temp_v1 + 0x138)) = (s32) (*(s32 *)((u8 *)(&sp.u28) + 8));
    }
}
/* was func_15121C68 */
void camera_look_mode_defaults(u8 *arg0) {
    if (arg0[0x23E] != 0) {
        if (arg0[0x23E] == 0x34) {
            (*(f32 *)((u8 *)arg0 + 0x190)) = 80.0f;
            (*(f32 *)((u8 *)arg0 + 0x784)) = 350.0f;
            return;
        }
        if ((arg0[0x23E] == 0x3B) && ((g_level_id == 0x41) || (g_level_id == 0x3C))) {
            (*(f32 *)((u8 *)arg0 + 0x190)) = -12.0f;
            (*(f32 *)((u8 *)arg0 + 0x99C)) = -28.0f;
            (*(f32 *)((u8 *)arg0 + 0x784)) = 106.0f;
            return;
        }
        if ((arg0[0x23E] == 2) || (arg0[0x23E] == 0xA) || (arg0[0x23E] == 0x13)) {
            (*(f32 *)((u8 *)arg0 + 0x190)) = 10.0f;
            (*(f32 *)((u8 *)arg0 + 0x784)) = 135.0f;
            (*(f32 *)((u8 *)arg0 + 0x99C)) = 0.0f;
            (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) | 0x80);
            return;
        }
        if ((arg0[0x23E] == 0x12) && (g_level_id == 0x3C)) {
            (*(f32 *)((u8 *)arg0 + 0x190)) = 10.0f;
            (*(f32 *)((u8 *)arg0 + 0x784)) = 180.0f;
            (*(f32 *)((u8 *)arg0 + 0x99C)) = 0.0f;
            return;
        }
        if (arg0[0x23E] == 0xF) {
            (*(f32 *)((u8 *)arg0 + 0x190)) = 10.0f;
            (*(f32 *)((u8 *)arg0 + 0x784)) = 480.0f;
            (*(f32 *)((u8 *)arg0 + 0x99C)) = 0.0f;
            return;
        }
        if (arg0[0x23E] == 0x38) {
            (*(f32 *)((u8 *)arg0 + 0x784)) = 110.0f;
            (*(f32 *)((u8 *)arg0 + 0x190)) = 5.0f;
            (*(f32 *)((u8 *)arg0 + 0x99C)) = 0.0f;
            return;
        }
        if (arg0[0x23E] == 0x15) {
            (*(f32 *)((u8 *)arg0 + 0x784)) = 110.0f;
            (*(f32 *)((u8 *)arg0 + 0x190)) = 25.0f;
            (*(f32 *)((u8 *)arg0 + 0x99C)) = 0.0f;
            return;
        }
        (*(f32 *)((u8 *)arg0 + 0x190)) = 5.0f;
        (*(f32 *)((u8 *)arg0 + 0x784)) = 75.0f;
        (*(f32 *)((u8 *)arg0 + 0x99C)) = 0.0f;
        return;
    }
    (*(f32 *)((u8 *)arg0 + 0x784)) = 90.0f;
    (*(f32 *)((u8 *)arg0 + 0x190)) = 25.0f;
    (*(f32 *)((u8 *)arg0 + 0x99C)) = 0.0f;
}

void aim_hud_clear(u8 *arg0);

/* was func_15121E34 */
void camera_look_exit(u8 *arg0)
{
  u8 *new_var;
  u8 *temp_v0;
  new_var = arg0 + 0x740;
  if (!((*(*((u16 **) (((u8 *) arg0) + 0x36C)))) & 0x10))
  {
    if ((*((s32 *) (((u8 *) arg0) + 0x34))) == 0x40)
    {
      if ((*((s32 *) (((u8 *) arg0) + 0x6FC))) == 0xF)
      {
        *((f32 *) (((u8 *) arg0) + 0x898)) = 0.0f;
        *((f32 *) (((u8 *) arg0) + 0x89C)) = 0.0f;
      }
      *((s8 *) (((u8 *) (*((u8 **) (((u8 *) arg0) + 0x3D4)))) + 0x198)) = 0;
      *((s16 *) (((u8 *) arg0) + 0x73C)) = 0;
      *((s16 *) (((u8 *) arg0) + 0x84A)) = 0x32;
    }
    else
    {
      *((s16 *) (((u8 *) arg0) + 0x84A)) = 0x32;
      if (1)
      {
        *((s16 *) (((u8 *) arg0) + 0x73C)) = 3;
      }
    }
    temp_v0 = new_var;
    *((f32 *) (((u8 *) arg0) + 0x374)) = 200.0f;
    *((f32 *) (((u8 *) arg0) + 0x348)) = 100.0f;
    *((s32 *) (((u8 *) arg0) + 0x134)) = (s32) (*((f32 *) (((u8 *) temp_v0) + 0x2C)));
    *((s8 *) (((u8 *) temp_v0) + 0x4C)) = 0;
    *((f32 *) (((u8 *) arg0) + 0x190)) = 0.0f;
    *((f32 *) (((u8 *) arg0) + 0x99C)) = 0.0f;
    *((f32 *) (((u8 *) arg0) + 0x198)) = 0.0f;
    obj_fade_command(*((struct127 **) (((u8 *) arg0) + 0x3D0)), 2U, 0xFFU, 0x20U, (s32) (*((u8 *) (((u8 *) arg0) + 0x23D))));
    if ((*((u8 *) (((u8 *) arg0) + 0x84C))) != 0)
    {
      aim_hud_clear(arg0);
      *((u8 *) (((u8 *) arg0) + 0x84C)) = 0U;
    }
  }
}
