#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_151B90F0 */
s32 fx_bob_y_drift_update(f32 *arg0) {
    arg0[0x3C / 4] = arg0[0x48 / 4] + (arg0[0x5C / 4] * sinf(arg0[0x44 / 4]));
    arg0[0x44 / 4] += arg0[0x4C / 4] * g_frame_step_f;
    arg0[0x44 / 4] = wrap_angle_rad(arg0[0x44 / 4]);
    arg0[0x20 / 4] += arg0[0x50 / 4] * g_frame_step_f;
    arg0[0x28 / 4] += arg0[0x58 / 4] * g_frame_step_f;
    return 1;
}

/* was func_151B9190 */
void dust_cloud_bob_update(f32 *arg0, s32 arg1)
{
  arg0[0x44 / 4] = arg0[0x5C / 4] + (arg0[0x64 / 4] * sinf(arg0[0x58 / 4]));
  arg0[0x58 / 4] += arg0[0x60 / 4] * g_frame_step_f;
  arg0[0x58 / 4] = wrap_angle_rad(arg0[0x58 / 4]);
  impact_dust_cloud_wobble(arg0, arg1);
}

/* was func_151B9204 */
s32 particle_bob_scale_update(u8 *arg0) {
    
    u8 *v = arg0 + 0x120;
    *(f32 *)(arg0 + 0x58) = *(f32 *)(v + 0x14) + (*(f32 *)(v + 0x28) * sinf(*(f32 *)(arg0 + 0x130)));
    *(f32 *)(v + 0x10) = (*(f32 *)(v + 0x18) * g_frame_step_f) + *(f32 *)(v + 0x10);
    *(f32 *)(v + 0x10) = wrap_angle_rad(*(f32 *)(v + 0x10));
    *(f32 *)(v + 0) = (*(f32 *)(v + 0x1C) * g_frame_step_f) + *(f32 *)(v + 0);
    *(f32 *)(v + 8) = (*(f32 *)(v + 0x24) * g_frame_step_f) + *(f32 *)(v + 8);
    return 1;
}

/* was func_151B92AC */
s32 fx_sway_x_drift_update(u8 *arg0)
{
    f32 *v = (f32 *)(arg0 + 0x110);
    *(f32 *)(arg0 + 0x38) = v[0] + v[1] * sinf(*(f32 *)(arg0 + 0x118));
    v[2] = v[3] * g_frame_step_f + v[2];
    v[2] = wrap_angle_rad(v[2]);
    *(f32 *)(arg0 + 0x40) += v[4] * g_frame_step_f;
    *(f32 *)(arg0 + 0x48) += v[6] * g_frame_step_f;
    return 1;
}
