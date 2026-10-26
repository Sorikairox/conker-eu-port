#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_150106B0 */
void level_obj_set_target_hit_cb(void) {
    g_level_bullet_hit_cb = target_volume_hit_check_offset;
}
