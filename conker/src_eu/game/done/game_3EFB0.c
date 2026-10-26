#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15011B00 */
void level_fx_spawn_random_life(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    struct04 *temp_v0 = effect_node_create_nodraw((s16) ((random_int() & 0x7F) + 10), 1, -1, 1, 0, 10, 255, 0);
    if (temp_v0 != NULL) {
        temp_v0->unk28 = arg0;
        temp_v0->unk2A = arg1;
        temp_v0->unk2C = arg2;
        temp_v0->unk2E = arg3;
        temp_v0->unk30 = 1;
    }
}

/* was func_15011B94 */
void level_obj_init_lights_sfx77(void) {
    level_fx_spawn_random_life(1257, 338, -2988, -367);
    level_fx_spawn_random_life(1901, 338, -2753, -367);
    light_group_set_disabled(1, 0);
    light_group_set_disabled(2, 1);
    sfx_emitter_start(77, 765, 55, -89, 12000, 600, 300, sfx_cb_keep_until_silent, 0, 0, 8, 0);
}
