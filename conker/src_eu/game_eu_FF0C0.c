#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern f32 D_800A0C80;
extern f32 D_800A0C84;
extern f32 D_800A0C88;
void obj_update_ground_tilt(struct127 *);
/* was func_150D18B0 */
void obj_spin_decay_update(u8 *arg0) {
    f32 temp_f0;
    f32 temp_f2;
    temp_f0 = *(f32 *)(arg0 + 0xBC);
    temp_f2 = *(f32 *)(arg0 + 0x148);
    *(f32 *)(arg0 + 0xB8) += temp_f0;
    *(f32 *)(arg0 + 0xBC) = temp_f0 * D_800A0C80;
    *(f32 *)(arg0 + 0x3C) *= D_800A0C84;
    *(f32 *)(arg0 + 0xC4) += temp_f2;
    *(f32 *)(arg0 + 0x148) = temp_f2 * D_800A0C88;
    obj_update_ground_tilt(arg0);
}

u8 *world_record_find(s32);
/* was func_150D1920 */
void world_rec_f9_set_player0_flag(u8 *arg0) {
    u8 *temp_v0;
    temp_v0 = world_record_find(0xF9);
    if (temp_v0 != NULL) {
        if ((arg0 - (u8 *)g_objects) / 0x32C == 0) {
            temp_v0[0x6E] = 1;
        } else {
            temp_v0[0x6E] = 0;
        }
    }
}

/* was func_150D197C */
void world_rec_f9_set_flag(s32 arg0) {
    u8 *temp_v0 = world_record_find(0xF9);
    if (temp_v0 != NULL) {
        temp_v0[0x6E] = 1;
    }
}

extern f32 D_800A0C90;
/* was func_150D19AC */
void ambient_red_flicker_dim_update(s32 arg0) {
    f32 *sp28;
    sp28 = (f32 *)((arg0 ^ 0) + 0x28); sp28 = sp28;
    fx_random_flicker_update(arg0 + 0x30, 10.0f, arg0 + 0x2C, 50.0f, 100.0f, 123.0f, D_800A0C90, sp28);
    light_set_level_colour(*sp28, ((u8 *)&g_level_light_colour)[1], ((u8 *)&g_level_light_colour)[2], 0);
}
