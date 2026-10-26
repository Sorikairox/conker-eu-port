#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15005EE0 */
void camera_level_hook19_setup(struct108 *arg0) {
    arg0->unk1B4 = (u16)2;
    arg0->unk1E0 = (u16)0xF;
    camera_apply_zoom_level(arg0);
    arg0->unk134 = 1;
}
