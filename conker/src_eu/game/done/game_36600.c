#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15009150 */
void flare_nodes_level_init(s32 arg0) {
    struct162 *tmp;

    D_800DDD64 = 0;
    g_flare_state_byte = 0;
    D_800DD2D0 = 0;
    if ((D_800DCDD0 != 0) && (D_8008CFFC[D_800B0DF0->unk10] != 0)) {
        tmp = flare_node_add(0, 0xFF);
        tmp->unk2E = 3;
    }
}
