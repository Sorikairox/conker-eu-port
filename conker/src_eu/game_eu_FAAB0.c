#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern f32 g_ground_colour_k_0ad0; /* was D_800A0AD0 */
extern f32 g_ground_colour_k_0ad4; /* was D_800A0AD4 */
extern f32 g_ground_colour_k_0ad8; /* was D_800A0AD8 */
extern f32 g_ground_colour_k_0adc; /* was D_800A0ADC */

/* was func_150CD2A0 */
void ground_colour_by_depth(f32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    f32 temp_f0;
    f32 temp_f0_2;

    if (arg0 > 0.0f) {
        *arg1 = 255.0f;
        *arg2 = 255.0f;
        *arg3 = 255.0f;
        return;
    }
    if (g_ground_colour_k_0ad0 < arg0) {
        temp_f0 = -arg0 * g_ground_colour_k_0ad4;
        *arg1 = 255.0f - (temp_f0 * 83.0f);
        *arg2 = 255.0f - (temp_f0 * 113.0f);
        *arg3 = 255.0f - (temp_f0 * 173.0f);
        return;
    }
    temp_f0_2 = -(arg0 + g_ground_colour_k_0ad8) * g_ground_colour_k_0adc;
    *arg1 = 172.0f - (temp_f0_2 * 50.0f);
    *arg2 = 142.0f - (temp_f0_2 * 42.0f);
    *arg3 = 82.0f - (temp_f0_2 * -1.0f);
}
