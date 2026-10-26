#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_1500EB30 */
void level_fx_point_spawn(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    struct04 *temp_v0 = (struct04 *)effect_node_create_nodraw((s16) ((random_int() & 0x7F) + 0xA), 1, -1, 1, 0, 0xA, 0xFF, 0);
    if (temp_v0 != 0) {
        temp_v0->unk28 = arg0;
        temp_v0->unk2A = arg1;
        temp_v0->unk2C = arg2;
        temp_v0->unk2E = arg3;
        temp_v0->unk30 = arg4;
    }
}

/* was func_1500EBC4 */
void level_setup_fx_points(void) {
    level_fx_point_spawn(386,  571,  -1576,  422, 0);
    level_fx_point_spawn(-23,  797,  -2235, -145, 0);
    level_fx_point_spawn(113,  745,  -2246, -190, 0);
    level_fx_point_spawn(388,  1124, -1741,  481, 0);
    level_fx_point_spawn(388,  1124, -1560,  643, 0);
    level_fx_point_spawn(388,  1124, -1104,  916, 0);
    level_fx_point_spawn(1464, 1095, -2654, -492, 1);
    level_fx_point_spawn(1448, 1095, -2431,  502, 0);
    level_fx_point_spawn(1409, 1116, -1993, -379, 0);
    level_fx_point_spawn(1403, 1120, -569,  -404, 0);
    level_fx_point_spawn(1540, 1371, -1265, -525, 0);
    level_fx_point_spawn(892,  2181, -1759, 1736, 0);
    level_fx_point_spawn(763,  2181, -1225, 1654, 0);
    level_fx_point_spawn(1209, 2181, -899,  1376, 0);
    level_fx_point_spawn(1719, 2181, -781,  -565, 0);
    level_fx_point_spawn(1162, 2181, -644,  1437, 0);
    level_fx_point_spawn(1932, 2181, -1266, -623, 1);
}
