#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_150D2960 */
void ambient_sine_colour_update(u8 *arg0) {
    f32 sp24;
    f32 sp20;
    u8 *temp_s0;

    sp20 = sinf((*(f32 *)((u8 *)arg0 + 0x40)));
    temp_s0 = arg0 + 0x28;
    sp24 = sinf((*(f32 *)((u8 *)arg0 + 0x44)));
    light_set_level_colour((u32) ((sp20 * (*(f32 *)((u8 *)temp_s0 + 0xC))) + (*(f32 *)((u8 *)temp_s0 + 0))) & 0xFF, (u32) ((sp24 * (*(f32 *)((u8 *)temp_s0 + 0x10))) + (*(f32 *)((u8 *)temp_s0 + 4))) & 0xFF, (u32) ((sinf((*(f32 *)((u8 *)temp_s0 + 0x20))) * (*(f32 *)((u8 *)temp_s0 + 0x14))) + (*(f32 *)((u8 *)temp_s0 + 8))) & 0xFF, 0U);
    (*(f32 *)((u8 *)temp_s0 + 0x18)) = wrap_angle_rad((*(f32 *)((u8 *)temp_s0 + 0x18)) + ((*(f32 *)((u8 *)temp_s0 + 0x24)) * g_frame_step_f));
    (*(f32 *)((u8 *)temp_s0 + 0x1C)) = wrap_angle_rad((*(f32 *)((u8 *)temp_s0 + 0x1C)) + ((*(f32 *)((u8 *)temp_s0 + 0x28)) * g_frame_step_f));
    (*(f32 *)((u8 *)temp_s0 + 0x20)) = wrap_angle_rad((*(f32 *)((u8 *)temp_s0 + 0x20)) + ((*(f32 *)((u8 *)temp_s0 + 0x2C)) * g_frame_step_f));
}