#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
/* was func_15049AD0 */
f32 catmull_rom_eval(s32 arg0, s32 arg1, f32 arg2) {
    f32 sp8;
    f32 sp4;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f2;
    f32 temp_f6;
    f32 temp_f8;
    u8 *temp_v0;

    temp_v0 = arg0 + (arg1 * 4);
    temp_f12 = (*(f32 *)((u8 *)temp_v0 + 0));
    temp_f14 = -0.5f * temp_f12;
    temp_f16 = (*(f32 *)((u8 *)temp_v0 + 4));
    temp_f0 = (*(f32 *)((u8 *)temp_v0 + 8));
    temp_f2 = (*(f32 *)((u8 *)temp_v0 + 0xC));
    temp_f8 = (temp_f2 * -0.5f) + (temp_f12 + (-2.5f * temp_f16) + (2.0f * temp_f0));
    sp4 = temp_f8;
    temp_f6 = (temp_f0 * 0.5f) + temp_f14;
    sp8 = temp_f6;
    return (((((((temp_f2 * 0.5f) + (temp_f14 + (1.5f * temp_f16) + (-1.5f * temp_f0))) * arg2) + temp_f8) * arg2) + temp_f6) * arg2) + temp_f16;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_772E0/catmull_rom_eval.s")
#endif
#ifdef NON_MATCHING
/* was func_15049B94 */
f32 catmull_rom_eval_deriv(s32 arg0, s32 arg1, f32 arg2, f32 *arg3) {
    f32 sp18;
    f32 sp10;
    f32 temp_f0;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f2;
    f32 temp_f6;
    u8 *temp_v0;

    temp_v0 = arg0 + (arg1 * 4);
    temp_f12 = (*(f32 *)((u8 *)temp_v0 + 0));
    temp_f14 = -0.5f * temp_f12;
    temp_f16 = (*(f32 *)((u8 *)temp_v0 + 4));
    temp_f0 = (*(f32 *)((u8 *)temp_v0 + 8));
    temp_f2 = (*(f32 *)((u8 *)temp_v0 + 0xC));
    temp_f6 = (temp_f2 * 0.5f) + (temp_f14 + (1.5f * temp_f16) + (-1.5f * temp_f0));
    sp10 = temp_f6;
    temp_f18 = (temp_f2 * -0.5f) + (temp_f12 + (-2.5f * temp_f16) + (2.0f * temp_f0));
    temp_f10 = (temp_f0 * 0.5f) + temp_f14;
    sp18 = temp_f10;
    *arg3 = (((temp_f6 * 3.0f * arg2) + (2.0f * temp_f18)) * arg2) + temp_f10;
    return (((((temp_f6 * arg2) + temp_f18) * arg2) + temp_f10) * arg2) + temp_f16;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_772E0/catmull_rom_eval_deriv.s")
#endif