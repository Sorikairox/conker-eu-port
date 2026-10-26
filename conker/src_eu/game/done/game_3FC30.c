#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15012780 */
void level_clear_dd410(void) {
    s32 i;

    g_vtx_anim_light_count = 0;
    for (i = 0; i < 2; i++)
    {
        g_vtx_anim_lights[i] = 0;
    }
}
