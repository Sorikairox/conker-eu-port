#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15005B10 */
void camera_level_hook04_setup(struct108 *arg0) {
    arg0->unk1E0 = 8;
    arg0->unk1B4 = 3;
    arg0->unk84 = arg0->unk84 & -5;
    camera_apply_zoom_level(arg0);
}
