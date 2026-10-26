#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* P241: readable C for level_light2_orbit (game_eu_FCC80, 56 insns). */
// level_light2_orbit: level update handler (g_level_update_fns entry 6, `void (s32)`, argument unused): turns the point
// (76, 241) around (-1, 44) by the angle (degrees) at +8 of world_record_find(4) and stores it, with z = -1805, as the
// position of light slot 2 (trigger_set_position); then steps the g_level_anim_frame frame counter (level_anim_frame_counter_tick(5, 3)). The
// constants are the ELF's D_800A0C00 (pi / 180, 0x3C8EFA35) and D_800A0C04 (-1805.0, 0xC4E1A000).
s32 world_record_find(u8);
void trigger_set_position(s32, s16, s16, s16);
void level_anim_frame_counter_tick(s32, s32);
/* was func_150CF470 */
void level_light2_orbit(s32 arg0) {
    f32 angle = *(f32 *) (world_record_find(4) + 8) * 0.017453292f;
    f32 s = fast_sinf(angle);
    f32 c = fast_cosf(angle);
    f32 dx = 76.0f - -1.0f;
    f32 dy = 241.0f - 44.0f;

    trigger_set_position(2, (s16) (dx * c - dy * s + -1.0f), (s16) (dx * s + dy * c + 44.0f), (s16) -1805.0f);
    level_anim_frame_counter_tick(5, 3);
}

/* was func_150CF550 */
f32 math_angle_offset_scaled(s32 arg0, s32 arg1) {
    arg0++;
    arg1 -= 0x2C;
    return math_atan2f(arg0, arg1) * g_angle_offset_k_0c08;
}

/* was func_150CF590 */
void obj_set_flag84_4000(struct127 *arg0) {
    *(s32 *)((u8 *)arg0 + 0x84) |= 0x4000;
}
