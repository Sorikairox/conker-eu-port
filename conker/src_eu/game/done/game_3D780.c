#include <ultra64.h>

#include "functions.h"
#include "variables.h"


void func_150102D0(void) {
    level_dl_add_texture_scroll(D_800B0E00[0], D_800902E8, 0, -1, 0, 0, 0, -6);
    level_dl_add_texture_scroll(D_800B0E00[1], D_800902E8, 0, -1, 0, 1, 0, -6);
    level_dl_add_texture_scroll(D_800B0E00[0], D_800902EC, 0, -1, 0, 0, 0, -3);
    level_dl_add_texture_scroll(D_800B0E00[1], D_800902EC, 0, -1, 0, 1, 0, -3);
    func_15149130(300, -1, 59, -1, 0, 0, 0, 255, 1);
}

void func_150103E0(void) {
    vtx_anim_light_create(0, 255, -3477, -963, 684, 0.0f, 15000, 15.0f, -106, 30, 127, 127, 127, 127, 127, 127);
    vtx_anim_light_create(4, 254,  2404, -992, 779, 0.0f,  2000, 15.0f, -106, 30, 127, 127, 127, 127, 127, 127);
}
