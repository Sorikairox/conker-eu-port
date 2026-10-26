#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15011330 */
void level_obj_init_storm(void) {
    storm_controller_spawn();
    g_sound_fx_mix_boost = (u8)0x10;
}
