#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void water_waves_update(void);
s32 random_int(void);
// level_ambient_cue_update: level update handler (g_level_update_fns[14]): runs water_waves_update, then counts the cue timer
// (byte at g_ambient_cue_timer) down by the frame delta g_frame_ticks; when it has run out, the first of the objects 0x15 /
// 0x1A / 0x1B / 0x1C / 0x1D / 0x20 that trigger_test_player reports absent (0) gets a random sound 0x6C..0x6E played at
// its point in g_level_zones (0x34-byte records), and the timer restarts at 0x80..0xFF.
/* was func_150D0C40 */
void level_ambient_cue_update(s32 arg0) {
    u8 *timer = (u8 *) g_ambient_cue_timer;
    s16 *pos;
    s32 id;

    id = 0;
    water_waves_update();
    if (*timer != 0) {
        if (g_frame_ticks < *timer) {
            *timer -= g_frame_ticks;
        } else {
            *timer = 0;
        }
        return;
    }
    if (trigger_test_player(0, 0x15) == 0) {
        id = 0x15;
    } else if (trigger_test_player(0, 0x1A) == 0) {
        id = 0x1A;
    } else if (trigger_test_player(0, 0x1B) == 0) {
        id = 0x1B;
    } else if (trigger_test_player(0, 0x1C) == 0) {
        id = 0x1C;
    } else if (trigger_test_player(0, 0x1D) == 0) {
        id = 0x1D;
    } else if (trigger_test_player(0, 0x20) == 0) {
        id = 0x20;
    }
    if (id == 0) {
        return;
    }
    *timer = (random_int() & 0x7F) + 0x80;
    pos = (s16 *) (g_level_zones + id * 0x34);
    sound_play_at((u32) random_int() % 3 + 0x6C, 0x5DC0, 0, 0, 0, pos[0], pos[1], pos[2], 0x320, 0x5DC);
}
