#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_150110F0 */
void level_obj_init_scroll_xy(void) {
    level_dl_add_texture_scroll(D_800B0E00[0], g_tex_scroll_id_0318, 0, -1, 0, 0, 0, 8);
    level_dl_add_texture_scroll(D_800B0E00[0], g_tex_scroll_id_031c, 0, -1, 0, 0, 8, 0);
}
