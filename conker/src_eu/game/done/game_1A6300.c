#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_15178E50 */
s32 level_screen_effect_active(s32 arg0) {
    if ((g_level_header->unk14 == 1)) {
        s32 tmp = g_player_views->unk2FC;
        if (g_level_header->unk16 < tmp) {
            return 1;
        }
    }
    return 0;
}
