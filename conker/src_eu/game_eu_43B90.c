#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern s32 g_level_blockers; /* was D_800D1CD0 */

/* was func_15016380 */
void level_load_ptr_table_3c(s32 arg0) {
    s32 *temp_v0;
    s32 *temp_v0_2;
    s32 temp_a3;
    s32 temp_t0;
    s32 temp_t8;
    s32 temp_t8_2;
    s32 temp_t9;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a0_3;
    s32 var_a1;
    s32 var_v0;
    u8 *temp_v0_3;
    u8 *temp_v0_4;
    u8 *temp_v0_5;

    if (asset_load_ptr(&g_level_blockers, 3, 0xC, arg0, 9) > 0) {
        var_a0 = 1;
        var_a1 = 0;
        var_v0 = g_level_blockers;
        if (*(s32 *)g_level_blockers != 0) {
            do {
                temp_t8 = (*(s32 *)((u8 *)var_v0 + 8));
                var_a0 += 1;
                var_v0 += 8;
            } while (temp_t8 != 0);
            var_a1 = 0;
        }
        temp_a3 = var_a0 - 1;
        if (temp_a3 > 0) {
            temp_t9 = (var_a0 - 1) & 3;
            if (temp_t9 != 0) {
                var_a0_2 = 0 * 8;
                do {
                    var_a1 += 1;
                    temp_v0 = g_level_blockers + var_a0_2;
                    temp_t0 = *temp_v0;
                    var_a0_2 += 8;
                    *temp_v0 = temp_t0 + g_level_blockers;
                } while (temp_t9 != var_a1);
                if (var_a1 != temp_a3) {
                    goto block_9;
                }
            } else {
block_9:
                var_a0_3 = var_a1 * 8;
                do {
                    temp_v0_2 = g_level_blockers + var_a0_3;
                    *temp_v0_2 += g_level_blockers;
                    temp_v0_3 = g_level_blockers + var_a0_3;
                    (*(s32 *)((u8 *)temp_v0_3 + 8)) = (s32) ((*(s32 *)((u8 *)temp_v0_3 + 8)) + g_level_blockers);
                    temp_v0_4 = g_level_blockers + var_a0_3;
                    (*(s32 *)((u8 *)temp_v0_4 + 0x10)) = (s32) ((*(s32 *)((u8 *)temp_v0_4 + 0x10)) + g_level_blockers);
                    temp_v0_5 = g_level_blockers + var_a0_3;
                    temp_t8_2 = (*(s32 *)((u8 *)temp_v0_5 + 0x18));
                    var_a0_3 += 0x20;
                    (*(s32 *)((u8 *)temp_v0_5 + 0x18)) = (s32) (temp_t8_2 + g_level_blockers);
                } while (var_a0_3 != (temp_a3 * 8));
            }
        }
    } else {
        g_level_blockers = 0;
    }
}