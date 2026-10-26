#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15010FB0 */
void level_obj_init_scroll_handles(void) {
    D_800BE4F0 = allocate_memory(16, 1, 0, 0);
    D_800BE4F0->unk0 = level_dl_add_texture_scroll(D_800B0E00[1], D_80090310, 1, -1, 0, 1, 0, 0);
    D_800BE4F0->unk4 = level_dl_add_texture_scroll(D_800B0E00[0], D_80090314, 0, -1, 0, 0, 0, 0);
    D_800BE4F0->unk8 = texture_anim_start_for(world_record_find(250), D_80090310, 1, -1, 0, 0, 0);
    D_800BE4F0->unkC = texture_anim_start_for(world_record_find(249), D_80090310, 1, -1, 0, 0, 0);
    collision_select_area(0);
    D_800D9A40 = zone_tree_find_leaf(0x1500, 0x700);
}
