#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15005FB0 */
void camera_level_hook23_setup(struct108 *arg0) {
    arg0->unk2C = 8;
    arg0->unk84 |= 0x300000;
    arg0->unk84 &= -5;
    arg0->unk1B4 = (u16)1;
    arg0->unk1E0 = (u16)3;
    camera_apply_zoom_level(arg0);
    arg0->unk134 = 0;
}
