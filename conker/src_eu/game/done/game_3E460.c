#include <ultra64.h>

#include "functions.h"
#include "variables.h"


void func_15010FB0(void) {
    D_800BE4F0 = allocate_memory(16, 1, 0, 0);
    D_800BE4F0->unk0 = func_15195AA8(D_800B0E00[1], D_80090310, 1, -1, 0, 1, 0, 0);
    D_800BE4F0->unk4 = func_15195AA8(D_800B0E00[0], D_80090314, 0, -1, 0, 0, 0, 0);
    D_800BE4F0->unk8 = func_15195FB0(world_record_find(250), D_80090310, 1, -1, 0, 0, 0);
    D_800BE4F0->unkC = func_15195FB0(world_record_find(249), D_80090310, 1, -1, 0, 0, 0);
    collision_select_area(0);
    D_800D9A40 = zone_tree_find_leaf(0x1500, 0x700);
}
