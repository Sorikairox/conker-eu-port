#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15005D60 */
void camera_level_hook13_setup(struct108 *arg0) {
    arg0->unk1B4 = 2;
    arg0->unk1E0 = 5;
    camera_apply_zoom_level(arg0);
    arg0->unk134 = 0;
    arg0->unk84 |= 0x4000;
}

/* was func_15005DA0 */
void camera_level_hook14_noop(s32 arg0) {
}
