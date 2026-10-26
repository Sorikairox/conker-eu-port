#include <ultra64.h>

#include "functions.h"
#include "variables.h"


f32 math_cos_u8(); // fakematch: K&R decl so math_sin_u8 re-masks the u8 arg (ref calls an undeclared function)
extern f32 g_cos_tbl_base_neg80[]; /* was D_8009A3E0 */
extern f32 g_cos_u8_table[]; /* was D_8009A5E0 */
extern u8 g_cos_tbl_mirror_80[]; /* was D_8009A7E0 */
extern u8 g_cos_tbl_mirror_100[]; /* was D_8009A9E0 */
/* was func_150489B0 */
f32 math_cos_u8(arg0)
u8 arg0;
{
    f32 r;
    s32 i;
    i = arg0;
    if (arg0 > 0x40) {
        if (arg0 > 0x80) {
            if (arg0 > 0xC0) {
                r = *(f32 *)(g_cos_tbl_mirror_100 + -(arg0 * 4));
            } else {
                r = -g_cos_tbl_base_neg80[i];
            }
        } else {
            r = -*(f32 *)(g_cos_tbl_mirror_80 + -(arg0 * 4));
        }
    } else {
        r = g_cos_u8_table[arg0];
    }
    return r;
}

/* was func_15048A40 */
f32 math_sin_u8(u8 arg0) {
    return math_cos_u8((arg0 - 0x40) & 0xFF);
}

/* was func_15048A70 */
f32 math_angle_diff_deg(f32 arg0, f32 arg1) {
    f32 tmp = arg0 - arg1;
    if (tmp > 180.0f) {
        arg0 -= 360.0f;
    } else {
        if (tmp <= -180.0f) {
            arg1 -= 360.0f;
        }
    }
    return arg1 - arg0;
}

/* was func_15048AD0 */
s32 math_angle_diff_deg_int(s32 arg0, s32 arg1) {
    s32 temp_v0 = arg0 - arg1;
    if (temp_v0 >= 181) {
        arg0 = arg0 - 360;
    } else {
        if (temp_v0 < -179) {
            arg1 = arg1 - 360;
        }
    }
    return arg1 - arg0;
}
