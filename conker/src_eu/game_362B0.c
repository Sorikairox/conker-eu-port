#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_15008E00 */
void area_points_reset(void) {
    g_area_points_count = (u8)0;
}

void *allocate_memory(s32 size, s32 arg1, s32 arg2, s32 arg3);
extern u8 g_area_points_type[];        /* level area id per slot; was D_800DE284 */
extern f32 (*g_area_points[])[3]; /* 40 points per slot; was D_800DE290 */
extern u8 g_water_types[];        /* .game_data: 0x18-byte area records; was D_8008D3F0 */
// area_points_alloc: takes the next slot (g_area_points_count) for level area `area`: allocates its 40 zeroed points
// (0x1E0 bytes), sets the last one's z to the area record's s16 at +0x14 (g_water_types, 0x18 bytes each), clears the
// record's byte +0x17. Called twice from level_obj_init_area_points (areas 0 and 1); water_waves_update reads the slots.
/* was func_15008E10 */
void area_points_alloc(s32 area) {
    s32 i;
    u8 *rec;

    g_area_points_type[g_area_points_count] = area;
    g_area_points[g_area_points_count] = allocate_memory(0x1E0, 1, 0, 0);
    for (i = 0; i < 40; i++) {
        g_area_points[g_area_points_count][i][0] = 0.0f;
        g_area_points[g_area_points_count][i][1] = g_area_points[g_area_points_count][i][0];
        g_area_points[g_area_points_count][i][2] = g_area_points[g_area_points_count][i][1];
    }
    rec = g_water_types + area * 0x18;
    g_area_points[g_area_points_count][39][2] = *(s16 *) (rec + 0x14);
    rec[0x17] = 0;
    g_area_points_count++;
}
