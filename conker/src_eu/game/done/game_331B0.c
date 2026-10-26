#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15005D00 */
void camera_level_hook12_setup(struct108 *arg0) {
    arg0->unk2C = 8;
    arg0->unk84 |= 0x300000;
    arg0->unk84 &= -5;
    arg0->unk1B4 = 1;
    arg0->unk1E0 = 3;
    camera_apply_zoom_level(arg0);
    arg0->unk134 = 0;
}
