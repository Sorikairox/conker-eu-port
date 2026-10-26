#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_150162B0 */
void records_table_reset(void) {

    bzero(&g_objects, 20300);
    g_obj_table_reset_word = 0;

    if (g_session_game_mode == 2) {
        g_records_game_mode = 2;
    } else if (g_session_game_mode == 3) {
        g_records_game_mode = 3;
    } else if (g_session_game_mode == 4) {
        g_records_game_mode = 4;
    } else {
        g_records_game_mode = 0;
    }
    D_800CC2B0 = 0;
    bzero(&D_800CC298, 24);
    g_records_flag_2a2 = 1;
    D_800D18D0 = 0;
}
