#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_150106B0 */
void level_obj_set_target_hit_cb(void) {
    D_800E0930 = target_volume_hit_check_offset;
}
