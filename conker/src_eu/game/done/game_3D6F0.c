#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15010240 */
void level_setup_tex_scroll_pos(void) {
    level_dl_add_texture_scroll(D_800B0E00[0], D_800902E4, 0, -1, 0, 0, 0, 4);
    level_dl_add_texture_scroll(D_800B0E00[1], D_800902E4, 0, -1, 0, 1, 0, 4);
}
