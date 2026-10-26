#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15016670 */
void level_clear_d18c0(void) {
    g_idle_request_flags = 0;
}

/* was func_15016680 */
void start_points_clear(void) {
    g_start_points = 0;
}

/* was func_15016690 */
void start_points_load(s32 arg0) {
    s32 tmp;

    g_start_point_mask = -1;
    g_start_point_team_mask = -1;
    tmp = asset_load_ptr(&g_start_points, 3, 12, arg0, 6) / 24U;
    g_start_point_count = tmp;
    if (tmp == 0) {
        g_start_points = allocate_memory(24, 1, 0, 0);
        g_start_point_count = 1U;
        if (g_setup_entries) {
            g_start_points->unk0 = g_setup_entries->unk6;
            g_start_points->unk2 = g_setup_entries->unk8;
            g_start_points->unk4 = g_setup_entries->unkA;
            g_start_points->unk8 = g_setup_entries->unk6 + 100;
            g_start_points->unkC = g_setup_entries->unk8 + 100;
            g_start_points->unk10 = g_setup_entries->unkA;
            g_start_points->unk6 = 0;
            g_start_points->unk7 = g_setup_entries->unkC;
            g_start_points->unk15 = 0;
        } else {
            g_start_points->unk0 = 0xE10;
            g_start_points->unk2 = -0xC80;
            g_start_points->unk4 = -0x898;
            g_start_points->unk10 = 1000.0f;
            g_start_points->unk8 = g_start_points->unkC = g_start_points->unk10;
            g_start_points->unk6 = 0;
            g_start_points->unk7 = 0;
            g_start_points->unk15 = 0;
          }
    }
}
