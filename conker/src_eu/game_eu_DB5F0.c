#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
/* was func_150ADDE0 */
f32 vec3f_dot(u8 *arg0, u8 *arg1) {
    return ((*(f32 *)((u8 *)arg0 + 0)) * (*(f32 *)((u8 *)arg1 + 0))) + ((*(f32 *)((u8 *)arg0 + 4)) * (*(f32 *)((u8 *)arg1 + 4))) + ((*(f32 *)((u8 *)arg0 + 8)) * (*(f32 *)((u8 *)arg1 + 8)));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DB5F0/vec3f_dot.s")
#endif
#ifdef NON_MATCHING
/* was func_150AD930 */
f32 vec3f_magnitude(f32 *arg0) {
    f32 temp_f0;
    f32 temp_f2;
    f32 temp_f4;

    temp_f0 = (*(f32 *)((u8 *)arg0 + 0));
    temp_f2 = (*(f32 *)((u8 *)arg0 + 4));
    temp_f4 = (*(f32 *)((u8 *)arg0 + 8));
    return sqrtf((temp_f0 * temp_f0) + (temp_f2 * temp_f2) + (temp_f4 * temp_f4));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DB5F0/vec3f_magnitude.s")
#endif