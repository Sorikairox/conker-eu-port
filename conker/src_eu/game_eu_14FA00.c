#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void math_spring_approach(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5);
void math_spring_approach_angle(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5);
void camera_update_eye_base(struct108 *arg0);
void camera_update_eye_orbit(struct108 *arg0);
void camera_update_eye_height(u8 *arg0);
extern u8 D_800BE616;
extern u8 g_slowmo_divisor; /* was D_800BEE2C */
extern f32 D_800A3810;
extern f32 D_800A3814;
extern f32 D_800A3818;
extern f32 D_800A381C;
extern f32 D_800A3820;
extern f32 D_800A3824;

#define CAM_F32(off) (*(f32 *) (cam + (off)))

// camera_follow_update: per-frame yaw update of a player camera (arg0; +0x3D0 = the followed player object, +0x3D4
// its character record), then the position / collision / shake steps (camera_update_eye_base, camera_update_eye_orbit, camera_update_eye_height).
// Locked cameras (+0x5F0 & 0x10 with pad bit 0x10 held, *+0x36C) and +0x698 skip the yaw part. In multiplayer (or
// camera modes +0x23E 9 / 0x3B) with ctl +0x1B3 set: the yaw +0x37C eases (math_spring_approach_angle) toward the player's facing
// - 180, with the multiplayer gains +0x96C / +0x970 easing to 5 / 8 (math_spring_approach). Else the target yaw is the
// facing + turn (+0x7C) - 180 - arg1, minus the locked-camera tilt (+0x2E4 >> 16) and the ctl +0x12 offset for the
// riding modes (9, 0x37..0x39, 0x3B, 0x12), wrapped by math_wrap_deg_360; +0x23C snaps the yaw to ctl +0x18C (taking its
// saved position +0x160 into +0x2F8 / +0x304 once) or the target, else it eases with mode-dependent gains (unless
// g_slowmo_divisor). +0x39C = yaw * D_800A3810 / D_800A3824.
/* was func_151221F0 */
void camera_follow_yaw_update(struct108 *arg0, f32 arg1) {
    u8 *cam = (u8 *) arg0;
    u8 *ctl;
    s32 flag;
    s32 i;
    u8 mode;
    f32 yaw;
    f32 gain;
    f32 rate;

    flag = (*(s32 *) (cam + 0x5F0) & 0x10) != 0;
    if (flag) {
        flag = (**(u16 **) (cam + 0x36C) & 0x10) != 0;
    }
    if (!flag && (D_800BE616 != 0 || cam[0x23E] == 9 || cam[0x23E] == 0x3B) && (*(u8 **) (cam + 0x3D4))[0x1B3] != 0) {
        if (D_800BE616 != 0) {
            CAM_F32(0x97C) = 5.0f;
            CAM_F32(0x980) = 8.0f;
            math_spring_approach((f32 *) (cam + 0x96C), 5.0f, (f32 *) (cam + 0x98C), 1.0f, 2.0f, CAM_F32(0x7B4));
            math_spring_approach((f32 *) (cam + 0x970), CAM_F32(0x980), (f32 *) (cam + 0x990), 1.0f, 2.0f, CAM_F32(0x7B4));
            math_spring_approach_angle((f32 *) (cam + 0x37C), *(f32 *) (*(u8 **) (cam + 0x3D0) + 0x40) - 180.0f, (f32 *) (cam + 0x7C8),
                          CAM_F32(0x96C), CAM_F32(0x970), CAM_F32(0x7B4));
        } else {
            math_spring_approach_angle((f32 *) (cam + 0x37C), *(f32 *) (*(u8 **) (cam + 0x3D0) + 0x40) - 180.0f, (f32 *) (cam + 0x7C8),
                          5.0f, 8.0f, CAM_F32(0x7B4));
        }
        CAM_F32(0x39C) = CAM_F32(0x37C) * D_800A3810;
    } else if (*(s32 *) (cam + 0x698) == 0) {
        u8 *pl = *(u8 **) (cam + 0x3D0);
        yaw = ((*(f32 *) (pl + 0x40) + (f32) *(u16 *) (pl + 0x7C) * 0.0054931640625f) - 180.0f) - arg1;
        if (flag && cam[0x23E] != 0x1C) {
            yaw -= (f32) (*(s32 *) (*(u8 **) (cam + 0x3D0) + 0x2E4) >> 16) * D_800A3814;
        }
        mode = cam[0x23E];
        if (mode == 9 || mode == 0x38 || mode == 0x39 || mode == 0x37 || mode == 0x3B || mode == 0x12) {
            yaw -= (f32) *(s16 *) (*(u8 **) (cam + 0x3D4) + 0x12) * 0.0054931640625f;
        }
        math_wrap_deg_360(&yaw);
        if (cam[0x23C] != 0) {
            ctl = *(u8 **) (cam + 0x3D4);
            if (D_800A3818 != *(f32 *) (ctl + 0x18C)) {
                CAM_F32(0x37C) = *(f32 *) (ctl + 0x18C);
                for (i = 0; i < 3; i++) {
                    *(s32 *) (cam + 0x2F8 + i * 4) = *(s32 *) (ctl + 0x160 + i * 4);
                }
                for (i = 0; i < 3; i++) {
                    *(s32 *) (cam + 0x304 + i * 4) = *(s32 *) (ctl + 0x160 + i * 4);
                }
                *(f32 *) (*(u8 **) (cam + 0x3D4) + 0x18C) = D_800A3818;
            } else {
                CAM_F32(0x37C) = yaw;
            }
            CAM_F32(0x7C8) = 0.0f;
        } else {
            mode = cam[0x23E];
            if (flag || cam[0x600] != 0) {
                gain = 4.0f;
                rate = 6.0f;
            } else if ((mode == 9 && D_800BE616 != 0) || mode == 0x38 || mode == 0x39 || mode == 0x37 || mode == 0x3B
                       || mode == 0x12) {
                gain = 2.0f;
                rate = 6.0f;
            } else if (*(s32 *) (cam + 0x84) & 0x200000) {
                gain = 1.0f;
                rate = D_800A381C;
            } else {
                gain = 0.75f;
                rate = D_800A3820;
            }
            if (g_slowmo_divisor == 0) {
                math_spring_approach_angle((f32 *) (cam + 0x37C), yaw, (f32 *) (cam + 0x7C8), gain, rate, CAM_F32(0x7B4));
            }
        }
        CAM_F32(0x39C) = CAM_F32(0x37C) * D_800A3824;
    }
    camera_update_eye_base(arg0);
    camera_update_eye_orbit(arg0);
    camera_update_eye_height(cam);
}
#undef CAM_F32
