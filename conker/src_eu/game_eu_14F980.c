#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void math_spring_approach_angle(u8 *, f32, u8 *, f32, f32, f32);

/* was func_15122170 */
void camera_yaw_ease_to(u8 *arg0, f32 arg1, s32 arg2, f32 arg3, f32 arg4) {
    math_spring_approach_angle(arg0 + 0x37C, arg1, arg0 + 0x8C0, arg3, arg4, *(f32 *)(arg0 + 0x7B4));
    *(f32 *)(arg0 + 0x39C) = *(f32 *)(arg0 + 0x37C) * 0.017453292f;
}

/* was func_151221D4 */
void camera_mode_noop(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
}
