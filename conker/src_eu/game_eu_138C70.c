#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
/* was func_1510B460 */
s32 view_point_cull_test(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 *arg8, f32 *arg9) {
    f32 sp0;
    f32 temp_f16;
    f32 temp_f2;

    temp_f2 = -((*(f32 *)((u8 *)arg0 + 0x38)) + (((*(f32 *)((u8 *)arg0 + 8)) * arg1) + ((*(f32 *)((u8 *)arg0 + 0x18)) * arg2) + ((*(f32 *)((u8 *)arg0 + 0x28)) * arg3)));
    if (temp_f2 < arg4) {
        return 1;
    }
    if (arg5 < temp_f2) {
        return 1;
    }
    temp_f16 = fabsf((*(f32 *)((u8 *)arg0 + 0x30)) + (((*(f32 *)((u8 *)arg0 + 0)) * arg1) + ((*(f32 *)((u8 *)arg0 + 0x10)) * arg2) + ((*(f32 *)((u8 *)arg0 + 0x20)) * arg3))) * arg6;
    if (temp_f2 < temp_f16) {
        return 1;
    }
    sp0 = fabsf((*(f32 *)((u8 *)arg0 + 0x34)) + (((*(f32 *)((u8 *)arg0 + 4)) * arg1) + ((*(f32 *)((u8 *)arg0 + 0x14)) * arg2) + ((*(f32 *)((u8 *)arg0 + 0x24)) * arg3))) * arg7;
    if (temp_f2 < sp0) {
        return 1;
    }
    if (arg8 != NULL) {
        *arg8 = 1.0f - (temp_f16 / temp_f2);
    }
    if (arg9 != NULL) {
        *arg9 = 1.0f - (sp0 / temp_f2);
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_138C70/view_point_cull_test.s")
#endif