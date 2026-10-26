#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_151307A0 */
void player_state_handler_dispatch(s32 arg0, s32 arg1) {
    u8 idx = ((u8 *)D_800B0DF0)[0xF];

    if (idx != 0) {
        D_80089A10[idx](arg0);
    }
}
