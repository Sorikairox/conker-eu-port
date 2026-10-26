#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15016670 */
void level_clear_d18c0(void) {
    D_800D18C0 = 0;
}

/* was func_15016680 */
void start_points_clear(void) {
    g_start_points = 0;
}

/* was func_15016690 */
void start_points_load(s32 arg0) {
    s32 tmp;

    D_800D2120 = -1;
    D_800D2124 = -1;
    tmp = asset_load_ptr(&g_start_points, 3, 12, arg0, 6) / 24U;
    D_800D2128 = tmp;
    if (tmp == 0) {
        g_start_points = allocate_memory(24, 1, 0, 0);
        D_800D2128 = 1U;
        if (D_800D20FC) {
            g_start_points->unk0 = D_800D20FC->unk6;
            g_start_points->unk2 = D_800D20FC->unk8;
            g_start_points->unk4 = D_800D20FC->unkA;
            g_start_points->unk8 = D_800D20FC->unk6 + 100;
            g_start_points->unkC = D_800D20FC->unk8 + 100;
            g_start_points->unk10 = D_800D20FC->unkA;
            g_start_points->unk6 = 0;
            g_start_points->unk7 = D_800D20FC->unkC;
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
