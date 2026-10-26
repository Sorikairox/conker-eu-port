#include <ultra64.h>
#include "functions.h"

#define PI 3.1415927410125732f


/* was func_15048360 */
f32 math_acosf_lut(f32 arg0) {
    s16 phi_a0;

    if (arg0 >= 1.0f) {
        phi_a0 = 0x7FFF;
    } else if (arg0 <= -1.0f) {
        phi_a0 = -0x7FFF;
    } else {
        phi_a0 = arg0 * 32767.0f;
    }
    return math_acos_s16(phi_a0) * (PI / 65535);
}

/* was func_15048408 */
f32 math_asinf_lut(f32 arg0) {
    s16 phi_a0;

    if (arg0 >= 1.0f) {
        phi_a0 = 0x7FFF;
    } else if (arg0 <= -1.0f) {
        phi_a0 = -0x7FFF;
    } else {
        phi_a0 = arg0 * 32767.0f;
    }
    return math_asin_s16(phi_a0) * (PI / 65535);
}
