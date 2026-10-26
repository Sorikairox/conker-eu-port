#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern u8 g_storm_thunder_sfx_timer; /* was D_80088B44 */
extern s32 g_player1_floor_flags; /* was D_800CC454 */

/* was func_150F51A0 */
void storm_thunder_flag_set(s32 arg0, s32 arg1) {
    g_storm_thunder_flag = 1;
}

/* was func_150F51BC */
s32 storm_thunder_flag_take(void) {
    if (g_storm_thunder_flag != 0) {
        g_storm_thunder_flag = 0;
        return 1;
    } else {
        return 0;
    }
}

/* was func_150F51E8 */
void storm_thunder_sfx_update(s32 arg0) {
    if (((g_player1_floor_flags & 0X1F) == 3) || ((g_player1_floor_flags & 0x1F) == 4)) {
        if (D_800BE9E4 < g_storm_thunder_sfx_timer){
            if(D_800C35EA != 1) {
                g_storm_thunder_sfx_timer = (g_storm_thunder_sfx_timer - D_800BE9E4);
            }
        } else {
            g_storm_thunder_sfx_timer = ((random_int() & 0x3F) + 0xC0);
            sound_play_2d(15, 18000, ((random_int() & 0x3F) + 0x20), 0, 0);
        }
    }
}
