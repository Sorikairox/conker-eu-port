#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15005E30 */
void camera_level_hook16_setup(struct108 *arg0) {
    if (D_800BE9F0 == 50) {
        arg0->unk1B4 = 2;
        arg0->unk1E0 = 4;
        camera_apply_zoom_level(arg0);
    }
}
