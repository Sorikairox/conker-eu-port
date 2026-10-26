#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15011C70 */
void level_reset_d9aa0_sfx(void) {
    D_800D9AA0[0] = 0;
    D_800D9AA0[1] = 0;
    D_800D9AA0[2] = 0;
    sfx_cooldown_clear();
}

/* was func_15011CA0 */
void level_sfx_cooldown_reset(void) {
    sfx_cooldown_clear();
}

/* was func_15011CC0 */
void level_obj_init_scroll_e4(void) {
    level_dl_add_texture_scroll(D_800B0E00[0], g_tex_scroll_id_02e4, 0, -1, 0, 0, 0, 4);
    level_dl_add_texture_scroll(D_800B0E00[1], g_tex_scroll_id_02e4, 0, -1, 0, 1, 0, 4);
}
