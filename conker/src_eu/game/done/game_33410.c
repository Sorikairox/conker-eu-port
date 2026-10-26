#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15005F60 */
void camera_level_hook21_setup(struct108 *arg0) {
    arg0->unk1B4 = (u16)2;
    camera_apply_zoom_level(arg0);
    arg0->unk84 |= 0x4000;
}
