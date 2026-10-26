#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_15008E00 */
void area_points_reset(void) {
    D_800DDE50 = (u8)0;
}

void *allocate_memory(s32 size, s32 arg1, s32 arg2, s32 arg3);
extern u8 D_800DE284[];        /* level area id per slot */
extern f32 (*D_800DE290[])[3]; /* 40 points per slot */
extern u8 D_8008D3F0[];        /* .game_data: 0x18-byte area records */
// area_points_alloc: takes the next slot (D_800DDE50) for level area `area`: allocates its 40 zeroed points
// (0x1E0 bytes), sets the last one's z to the area record's s16 at +0x14 (D_8008D3F0, 0x18 bytes each), clears the
// record's byte +0x17. Called twice from level_obj_init_area_points (areas 0 and 1); water_waves_update reads the slots.
/* was func_15008E10 */
void area_points_alloc(s32 area) {
    s32 i;
    u8 *rec;

    D_800DE284[D_800DDE50] = area;
    D_800DE290[D_800DDE50] = allocate_memory(0x1E0, 1, 0, 0);
    for (i = 0; i < 40; i++) {
        D_800DE290[D_800DDE50][i][0] = 0.0f;
        D_800DE290[D_800DDE50][i][1] = D_800DE290[D_800DDE50][i][0];
        D_800DE290[D_800DDE50][i][2] = D_800DE290[D_800DDE50][i][1];
    }
    rec = D_8008D3F0 + area * 0x18;
    D_800DE290[D_800DDE50][39][2] = *(s16 *) (rec + 0x14);
    rec[0x17] = 0;
    D_800DDE50++;
}
