#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DD380/func_151AFB70.s")

s32 func_151AFC70(s32 arg0, s32 arg1) {
    return 0xC;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DD380/func_151AFC84.s")

s32 func_151B0184(u8 *arg0) {
    s16 temp_v0 = *(s16 *)(arg0 + 0x1C);
    s32 temp_v1;

    if (temp_v0 < 32) {
        temp_v1 = temp_v0 << 3;
        if (temp_v1 < arg0[0x28]) {
            arg0[0x28] = temp_v1;
        }
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DD380/func_eu_151B01B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DD380/func_151B0238.s")

s32 func_151B0454(u8 *arg0, s32 arg1) {
    s32 i;
    f32 *p = (f32 *)(arg0 + 0xA8);
    for (i = D_800BE9E4; i != 0; i--) {
        *(f32 *)(arg0 + 0x58) *= *p;
        *(f32 *)(arg0 + 0x60) *= *p;
    }
    return 1;
}
