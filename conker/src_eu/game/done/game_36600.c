#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15009150 */
void flare_nodes_level_init(s32 arg0) {
    struct162 *tmp;

    g_flare_nodes = 0;
    g_flare_state_byte = 0;
    g_sun_flash_alpha = 0;
    if ((g_level_lights_mode != 0) && (g_flare_level_points[g_level_header->unk10] != 0)) {
        tmp = flare_node_add(0, 0xFF);
        tmp->unk2E = 3;
    }
}
