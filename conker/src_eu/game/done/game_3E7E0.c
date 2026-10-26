#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15011330 */
void level_obj_init_storm(void) {
    storm_controller_spawn();
    D_80041FD8 = (u8)0x10;
}
