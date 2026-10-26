#include <ultra64.h>

#include "functions.h"
#include "variables.h"


void func_15011C70(void) {
    D_800D9AA0[0] = 0;
    D_800D9AA0[1] = 0;
    D_800D9AA0[2] = 0;
    sfx_cooldown_clear();
}

void func_15011CA0(void) {
    sfx_cooldown_clear();
}

void func_15011CC0(void) {
    level_dl_add_texture_scroll(D_800B0E00[0], D_800902E4, 0, -1, 0, 0, 0, 4);
    level_dl_add_texture_scroll(D_800B0E00[1], D_800902E4, 0, -1, 0, 1, 0, 4);
}
