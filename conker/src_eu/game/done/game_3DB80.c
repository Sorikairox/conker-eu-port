#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_150106D0 */
s32 level_obj_spawn_zone_effect(struct39 *arg0) {
    struct176 tmp;
    struct37 *temp_v0;

    tmp.unk0 = arg0;
    tmp.unk4 = spawn_region_area(arg0);
    tmp.unkC = 0.0f;

    collision_select_area(0);

    tmp.unk8 = zone_tree_find_leaf(arg0->unk0, arg0->unk4);
    if (tmp.unk8 == 0) {
        return 1;
    } else {
        temp_v0 = effect_node_create(300, -1, 89, -1, 0, 0, 16, 255, 0);
        if (temp_v0 != NULL) {
            memcpy(&temp_v0->unk28, &tmp, 16); // memcpy
        }
    }
    return 1;
}
