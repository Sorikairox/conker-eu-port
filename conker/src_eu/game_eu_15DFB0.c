#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_151307A0 */
void player_state_handler_dispatch(s32 arg0, s32 arg1) {
    u8 idx = ((u8 *)g_level_header)[0xF];

    if (idx != 0) {
        g_level_player_state_fns[idx](arg0);
    }
}
