#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_1508EF80 */
void vec_rotate_xz_about_point(u8 *arg0, u8 *arg1, f32 arg2, u8 *arg3) {
    f32 sp3C;
    f32 sp38;
    f32 sp28;
    f32 sp24;
    f32 temp_f20;
    f32 temp_f8;
    f32 temp_f8_2;

    temp_f8 = (*(f32 *)((u8 *)arg0 + 0)) - (*(f32 *)((u8 *)arg1 + 0));
    sp3C = temp_f8;
    temp_f20 = arg2 * 0.017453292f;
    sp38 = (*(f32 *)((u8 *)arg0 + 8)) - (*(f32 *)((u8 *)arg1 + 8));
    sp24 = cosf(temp_f20);
    sp28 = (sinf(temp_f20) * sp38) + (sp24 * temp_f8) + (*(f32 *)((u8 *)arg1 + 0));
    sp24 = sinf(temp_f20);
    temp_f8_2 = cosf(temp_f20) * sp38;
    (*(f32 *)((u8 *)arg3 + 0)) = sp28;
    (*(f32 *)((u8 *)arg3 + 8)) = (f32) (temp_f8_2 + (-sp24 * sp3C) + (*(f32 *)((u8 *)arg1 + 8)));
}
// NON-MATCHING: only the stack slots of x and the cosf() spill differ
// extern f32 D_8009E050; // degrees to radians
//
// // rotate pos around center in the XZ plane by angle degrees
// void vec_rotate_xz_about_point(f32 *pos, f32 *center, f32 angle, f32 *out) {
//     f32 dx = pos[0] - center[0];
//     f32 dz = pos[2] - center[2];
//     f32 rad = angle * D_8009E050;
//     f32 x;
//     f32 z;
//
//     x = center[0] + (cosf(rad) * dx + sinf(rad) * dz);
//     z = cosf(rad) * dz + -sinf(rad) * dx + center[2];
//     out[0] = x;
//     out[2] = z;
// }
