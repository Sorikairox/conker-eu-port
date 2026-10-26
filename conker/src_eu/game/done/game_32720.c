#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15005270 */
void obj_flagged_select_reset(void) {
    g_obj_flagged_select_idx = (u8)0;
    g_obj_flagged_pending = (u8)0;
}
