#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
void func_150498A0(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5) {
    f32 sp4;
    f32 temp_f0;
    f32 temp_f18;
    f32 temp_f8;
    f32 var_f0;
    f32 var_f2;

    temp_f0 = arg1 - *arg0;
    if (temp_f0 < 0.0f) {
        var_f2 = -1.0f;
    } else {
        var_f2 = 1.0f;
    }
    temp_f18 = *arg2;
    *arg2 = temp_f18 + (((temp_f0 * arg3) - temp_f18) * arg4 * arg5);
    temp_f8 = (*arg2 * arg5) + *arg0;
    sp4 = temp_f8;
    if (arg1 < temp_f8) {
        var_f0 = -1.0f;
    } else {
        var_f0 = 1.0f;
    }
    if (var_f0 == var_f2) {
        *arg0 = sp4;
        return;
    }
    *arg0 = arg1;
    *arg2 = 0.0f;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_770B0/func_150498A0.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_770B0/func_15049978.s")
