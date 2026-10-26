#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_1500F210 */
void level_setup_tex_scroll_neg(void) {
    level_dl_add_texture_scroll(g_level_part_dls[0], g_tex_scroll_id_02b8, 1, -1, 0, 0, 0, -8);
    level_dl_add_texture_scroll(g_level_part_dls[1], g_tex_scroll_id_02b8, 1, -1, 0, 1, 0, -8);
}
