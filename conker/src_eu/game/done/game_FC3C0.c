#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_150CEF10 */
void camera_hook_zoom_reset(struct108 *arg0) {
    arg0->unk84 |= 0x10;
    if (arg0->unk1B4 == 3) {
        arg0->unk1E0 = 5;
        arg0->unk1B4 = 2;
        camera_apply_zoom_level(arg0);
    }
}
