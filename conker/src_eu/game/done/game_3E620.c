#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15011170 */
void level_obj_init_storm_sounds(void) {
    g_storm_thunder_flag = 0;
    lightning_emitter_spawn(g_player_views, 0, 0, 0xFF, 1);
    sfx_emitter_start(108, -3580,  -546, -6129, 18000, 1111, 1100, sfx_cb_ambient_random_chirp, 0, 0, 8, 0);
    sfx_emitter_start(108, -2929, -1121, -2158, 18000, 1590, 1580, sfx_cb_ambient_random_chirp, 0, 0, 8, 0);
    sfx_emitter_start(108,   497, -1071, -2105, 18000, 2040, 2030, sfx_cb_ambient_random_chirp, 0, 0, 8, 0);
    sfx_emitter_start(1567,   26,     0,     0, 12000, 2500, 1800, sfx_cb_keep_until_silent, 0, 0, 72, 0);
    sfx_emitter_start(1567,   27,     0,     0,  8000, 2000, 1000, sfx_cb_keep_until_silent, 0, 0, 72, 0);
}
