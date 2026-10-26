#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15010680 */
void level_obj_set_hit_activate_cb(void) {
    g_world_obj_hit_cb = world_obj_hit_activate;
}
