#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15005A60 */
void camera_level_hook_dispatch(struct108 *arg0, s32 arg1) {
    if (D_800B0DF0->unkE != 0) {
        D_80082B40[D_800B0DF0->unkE](arg0);
    }
}
