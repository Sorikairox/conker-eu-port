#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15005E70 */
void camera_level_hook17_setup(struct108 *arg0) {
    arg0->unk1B4 = 2;
    camera_apply_zoom_level(arg0);
    arg0->unk23C = 1;
}

/* was func_15005EA0 */
void camera_level_hook18_setup(struct108 *arg0) {
    arg0->unk1B4 = 1;
    arg0->unk1E0 = 15;
    camera_apply_zoom_level(arg0);
    arg0->unk134 = 1;
}
