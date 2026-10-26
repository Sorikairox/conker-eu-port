#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern f32 D_800A3830;
void func_15122EF0(u8 *);
void func_151220D0(u8 *arg0) {
    struct17 tmp;

    if (!(**(u16 **)(arg0 + 0x36C) & 4)) {
        func_15048F90((struct17 *)(arg0 + 0x2F8), (struct17 *)(arg0 + 0x2BC), &tmp);
        tmp.unk0 += *(f32 *)(arg0 + 0x2C8) - *(f32 *)(arg0 + 0x2BC);
        tmp.unk8 += *(f32 *)(arg0 + 0x2D0) - *(f32 *)(arg0 + 0x2C4);
        *(f32 *)(arg0 + 0x37C) = func_15048FC8(&tmp);
        *(f32 *)(arg0 + 0x39C) = *(f32 *)(arg0 + 0x37C) * D_800A3830;
    }
    func_15122EF0(arg0);
}

#ifdef NON_MATCHING
void func_15049978(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5);
void func_1512A390(struct108 *arg0);
void camera_update_eye_orbit(u8 *);
void func_1512E6B0(u8 *);
float sqrtf(float);

// camera_follow_target_update: camera p (struct108). With the mode flag (*(+0x36C) bit 2) set, or without a target
// (+0x614) or with the target straight above, it only runs func_15122EF0. Else the extra yaw +0x5DC decays by 8%,
// +0x6C4 = 0, camera_calc_yaw runs, and the yaw from the camera (+0x2BC / +0x2C4) to the target (heading from
// func_15048C30 of -dx / dist, in degrees, plus +0x5DC) wrapped into [0, 360] becomes the yaw +0x37C: directly with
// +0x23C (rate +0x630 = 0), else eased (func_15049978: 3 / 6 with +0x84 bit 30 or 26, else 1.5 / 2; frame step
// +0x7B4); +0x39C = yaw in radians. Skipped while +0x698 is set. Then func_1512A390 / camera_update_eye_orbit /
// func_1512E6B0, and with +0x84 bit 30 another camera_update_eye_orbit + func_1512E6B0 with +0x190 = 30.
void func_151226E0(struct108 *arg0) {
    u8 *p = (u8 *) arg0;
    f32 *target;
    f32 dx, dz;
    f32 dist;
    f32 a;
    f32 yaw;
    s32 flags;

    if (**(u16 **) (p + 0x36C) & 4) {
        func_15122EF0(p);
        return;
    }
    *(f32 *) (p + 0x5DC) = *(f32 *) (p + 0x5DC) - *(f32 *) (p + 0x5DC) * 0.08f; /* D_800A3840 */
    *(f32 *) (p + 0x6C4) = 0.0f;
    camera_calc_yaw(arg0);
    target = *(f32 **) (p + 0x614);
    if (target == NULL) {
        func_15122EF0(p);
        return;
    }
    dx = target[0] - *(f32 *) (p + 0x2BC);
    dz = target[2] - *(f32 *) (p + 0x2C4);
    dist = sqrtf(dx * dx + dz * dz);
    if (dist == 0.0f) {
        func_15122EF0(p);
        return;
    }
    a = func_15048C30(-dx / dist);
    if (0.0f < dz) {
        yaw = 270.0f - a * 57.2957764f; /* D_800A3844 */
    } else {
        yaw = a * 57.2957764f + 90.0f;  /* D_800A3848 */
    }
    yaw += -90.0f + *(f32 *) (p + 0x5DC);
    while (yaw < 0.0f) {
        yaw += 360.0f;
    }
    while (360.0f < yaw) {
        yaw -= 360.0f;
    }
    if (*(s32 *) (p + 0x698) == 0) {
        if (p[0x23C] != 0) {
            *(f32 *) (p + 0x630) = 0.0f;
            *(f32 *) (p + 0x37C) = yaw;
        } else {
            flags = *(s32 *) (p + 0x84);
            if ((flags & 0x40000000) || (flags & 0x04000000)) {
                func_15049978((f32 *) (p + 0x37C), yaw, (f32 *) (p + 0x630), 3.0f, 6.0f, *(f32 *) (p + 0x7B4));
            } else {
                func_15049978((f32 *) (p + 0x37C), yaw, (f32 *) (p + 0x630), 1.5f, 2.0f, *(f32 *) (p + 0x7B4));
            }
        }
        *(f32 *) (p + 0x39C) = *(f32 *) (p + 0x37C) * 0.0174532924f; /* D_800A384C */
    }
    func_1512A390(arg0);
    camera_update_eye_orbit(p);
    func_1512E6B0(p);
    if (*(s32 *) (p + 0x84) & 0x40000000) {
        camera_update_eye_orbit(p);
        *(f32 *) (p + 0x190) = 30.0f;
        func_1512E6B0(p);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_14FE50/func_151226E0.s")
#endif
