#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15005F20 */
void camera_level_hook20_setup(struct108 *arg0) {
    arg0->unk1B4 = 3;
    arg0->unk1E0 = 15;
    camera_apply_zoom_level(arg0);
    arg0->unk134 = 1;
}
