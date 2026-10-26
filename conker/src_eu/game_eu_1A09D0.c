#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern s8 g_warp_target_levels[]; /* was D_800DD6E0 */

/* reset the two 16-byte tables, then keep arg0 in the first entry */
/* was func_15172C50 */
void warp_requests_reset(u8 arg0) {
    s32 i;

    for (i = 0; i < 16; i++) {
        g_warp_target_levels[i] = -1;
        (&g_warp_entry_ids)[i] = 0;
    }
    g_warp_entry_ids = arg0;
}
s32 screen_fade_start(s32, s32, s32, s32, s32, s32);
extern s8 g_warp_target_levels[]; /* was D_800DD6E0 */

/* was func_15173218 */
void warp_request_cancel(s32 arg0) {
    s8 *temp_v0 = g_warp_target_levels + arg0;
    if (*temp_v0 != -1) {
        *temp_v0 = -1;
        screen_fade_start(0, 0, 0, 0, 1, arg0);
        screen_fade_start(0, 0, 0, 0x32, 0, arg0);
    }
}

/* was func_15173298 */
void warp_player_to_entry(u8 *arg0, s32 arg1) {
    u8 *t;
    obj_place_at_start(arg0, arg1, 1);
    *(u16 *)(arg0 + 0x2F8) &= 0xFFEF;
    if (g_level_first_frame == 0) {
        t = *(u8 **)(arg0 + 0x31C);
        if (t != NULL) {
            t[0x56] = 3;
        }
    }
}

s32 game_request_transition(s32, s8, s32, s32, s32);
s32 screen_fade_is_done(s32);

/* was func_15172D80 */
void warp_request_update(s32 arg0) {
    if (g_warp_target_levels[arg0] != -1) {
        if (g_objects[arg0].health == 0) {
            g_warp_target_levels[arg0] = -1;
            screen_fade_start(0, 0, 0, 0x32, 0, arg0);
        }
        if (screen_fade_is_done(arg0) != 0) {
            if (g_level_id != g_warp_target_levels[arg0]) {
                game_request_transition(1, g_warp_target_levels[arg0], 0, 0, 0);
                return;
            }
            warp_request_cancel(arg0);
            warp_player_to_entry((u8 *)&g_objects[arg0], (&g_warp_entry_ids)[arg0]);
        }
    }
}

/* was func_151733EC */
void warp_request_start(struct127 *arg0, s32 arg1, s32 arg2) {
    s32 temp_v1;

    temp_v1 = arg0->unk127;
    if ((arg0->health != 0) && ((arg0->unk31C == NULL) || ((s8) arg0->unk31C->pad17[0xC] <= 0))) {
        if (arg0->camera != NULL) {
            if (g_warp_target_levels[temp_v1] == -1) {
                screen_fade_start(0, 0, 0, 0xA, 1, (s32) temp_v1);
                arg0->unk2F8 |= 0x10;
                g_warp_target_levels[temp_v1] = (s8) arg1;
                (&g_warp_entry_ids)[temp_v1] = (u8) arg2;
            }
        } else if (arg1 == g_level_id) {
            warp_player_to_entry((u8 *) arg0, arg2);
        }
    }
}
