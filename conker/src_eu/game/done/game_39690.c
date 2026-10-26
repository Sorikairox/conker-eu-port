#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_1500C1E0 */
void anim_mesh_slots_reset(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        g_weather_slot_busy[i] = g_weather_slot_timers[i] = 0;
    }
    for (i = 0; i < 11; i++) {
        g_anim_mesh_state[i] = -2;
    }

    bzero(g_anim_mesh_slots, 220); // bzero 220 bytes

    for (i = 0; i < 11; i++) {
        g_anim_mesh_dls[i] = 0;
    }
}
