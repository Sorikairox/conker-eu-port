#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15010FB0 */
void level_obj_init_scroll_handles(void) {
    g_level_scroll_handles = allocate_memory(16, 1, 0, 0);
    g_level_scroll_handles->unk0 = level_dl_add_texture_scroll(D_800B0E00[1], g_tex_scroll_id_0310, 1, -1, 0, 1, 0, 0);
    g_level_scroll_handles->unk4 = level_dl_add_texture_scroll(D_800B0E00[0], g_tex_scroll_id_0314, 0, -1, 0, 0, 0, 0);
    g_level_scroll_handles->unk8 = texture_anim_start_for(world_record_find(250), g_tex_scroll_id_0310, 1, -1, 0, 0, 0);
    g_level_scroll_handles->unkC = texture_anim_start_for(world_record_find(249), g_tex_scroll_id_0310, 1, -1, 0, 0, 0);
    collision_select_area(0);
    D_800D9A40 = zone_tree_find_leaf(0x1500, 0x700);
}
