#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15005C30 */
void camera_level_hook09_setup(struct108 *arg0) {
    arg0->unk84 |= 0x100000;
    arg0->unk84 &= -5;
    arg0->unk1B4 = 2;
    arg0->unk1E0 = 5;
    camera_apply_zoom_level(arg0);
}
