#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void laser_switch_broadcast(s32 arg0, s32 arg1);
void light_group_set_disabled(s32, s32);

// level_effects_reset: resets the 17 effect slots 6..0x16 of g_level_zones (0x34 bytes each, laser_switch_broadcast mode 1;
// the asm copies the ids from a local table) and then calls light_group_set_disabled(9, 1). arg0 is unused.
/* was func_150F58C0 */
void level_effects_reset(s32 arg0) {
    static const s32 ids[17] = { 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22 };
    u8 i;

    for (i = 0; i <= 16; i++) {
        laser_switch_broadcast(1, (s32)(g_level_zones + ids[i] * 0x34));
    }
    light_group_set_disabled(9, 1);
}
