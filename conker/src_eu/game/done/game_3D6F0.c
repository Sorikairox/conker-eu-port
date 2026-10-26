#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15010240 */
void level_setup_tex_scroll_pos(void) {
    level_dl_add_texture_scroll(g_level_part_dls[0], g_tex_scroll_id_02e4, 0, -1, 0, 0, 0, 4);
    level_dl_add_texture_scroll(g_level_part_dls[1], g_tex_scroll_id_02e4, 0, -1, 0, 1, 0, 4);
}
