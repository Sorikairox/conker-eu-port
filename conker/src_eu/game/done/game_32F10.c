#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15005A60 */
void camera_level_hook_dispatch(struct108 *arg0, s32 arg1) {
    if (g_level_header->unkE != 0) {
        g_camera_level_hook_fns[g_level_header->unkE](arg0);
    }
}
