#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_1511FC20 */
void frame_hook_nop_1511fc20(s32 arg0) {
}

/* P183: real argument lists (see functions.h); the default build keeps the matching 4 x s32 form. */
// debug_pos_hook: debug build hook given gdl, a position (x, y, z), a value and the player; returns gdl unchanged
/* was func_1511FC2C */
Gfx *debug_gdl_pos_value_nop(Gfx *gdl, f32 x, f32 y, f32 z, f32 w, s32 player) {
    return gdl;
}

// debug_pos_hook2: as debug_gdl_pos_value_nop without the value; returns gdl unchanged
/* was func_1511FC44 */
Gfx *debug_gdl_pos_nop(Gfx *gdl, f32 x, f32 y, f32 z, s32 player) {
    return gdl;
}
