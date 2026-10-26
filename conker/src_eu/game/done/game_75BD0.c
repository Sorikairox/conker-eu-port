#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15048720 */
f32 math_angle_lerp_deg(f32 arg0, f32 arg1, f32 arg2) {
    f32 res = math_angle_diff_deg(arg1, arg2) * arg0;
    return arg1 + res;
}

/* was func_15048758 */
void math_wrap_deg_360(f32 *arg0) {
    while (*arg0 < 0.0f) {
        *arg0 = (f32) (*arg0 + 360.0f);
    }
    while (*arg0 >= 360.0f) {
        *arg0 = (f32) (*arg0 - 360.0f);
    }
}
