#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern s32 g_look_points; /* was D_800C6A70 */
extern u32 g_look_points_count; /* was D_800C6A74 */

/* was func_1503E0C0 */
void look_point_remove(s32 arg0) {
    u32 temp_t5;
    u32 var_v0;
    u8 *var_v1;

    if ((arg0 >= 0) && ((u32) arg0 < (u32) g_look_points_count)) {
        (*(s16 *)((u8 *)((g_look_points + (arg0 * 0x14))) + 6)) = 2;
        var_v0 = g_look_points_count;
        if (var_v0 != 0) {
            var_v1 = g_look_points + ((var_v0 - 1) * 0x14);
            if ((*(u16 *)((u8 *)var_v1 + 6)) & 2) {
loop_4:
                temp_t5 = var_v0 - 1;
                g_look_points_count = temp_t5;
                var_v0 = temp_t5;
                var_v1 -= 0x14;
                if (temp_t5 != 0) {
                    if ((*(u16 *)((u8 *)var_v1 + 6)) & 2) {
                        goto loop_4;
                    }
                }
            }
        }
    }
}