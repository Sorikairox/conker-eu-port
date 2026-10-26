#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern s8 g_game_frame_state; /* was D_800BEA35 */
extern s32 g_level_start_player_mask; /* was D_800BEE20 */
extern s32 g_level_start_session_mode; /* was D_800BEE24 */
extern u16 g_objects_air_time; /* was D_800CC7A2 */
void start_points_clear(void);
void rumble_stop_all(void);

/* was func_1501C710 */
void game_request_transition(s32 arg0, u16 *arg1, s32 arg2, s32 arg3, s32 arg4) {
    rumble_stop_all();
    g_transition_air_time = 0;
    switch (arg0) {
    case 0:
        break;
    case 4:
    case 6:
        g_level_start_player_mask = arg4;
        g_level_start_session_mode = arg3;
        g_level_load_id = arg1;
        g_warp_entry_ids = (u8)arg2;
        g_game_frame_state = 2;
        break;
    case 1:
        g_game_frame_state = 3;
        g_level_load_id = arg1;
        g_transition_air_time = g_objects_air_time;
        break;
    case 2:
        g_game_frame_state = 3;
        g_level_load_id = arg1;
        g_warp_entry_ids = (u8)arg2;
        g_transition_air_time = g_objects_air_time;
        break;
    case 3:
        if (g_mp_mode_active == 0) {
            g_game_frame_state = 4;
            start_points_clear();
        }
        break;
    case 5:
        g_level_load_id = (u16 *)5;
        g_game_frame_state = 1;
        break;
    }
}
