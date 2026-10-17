#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_151D2C70(s16 arg0) {
    u8 *temp_v0;

    temp_v0 = func_15167A68(0x3C, 1, 0x18, 0, 0xFFU, 1U);
    (*(s16 *)((u8 *)temp_v0 + 0x14)) = 0;
    (*(s16 *)((u8 *)temp_v0 + 0x12)) = 0;
    (*(s16 *)((u8 *)temp_v0 + 0xE)) = 0;
    (*(s8 *)((u8 *)temp_v0 + 0x16)) = 1;
    (*(s16 *)((u8 *)temp_v0 + 0x10)) = arg0;
}

void func_151D2CC8(s16 arg0) {
    u8 *var_v0;

    for (var_v0 = D_800DD510; var_v0 != NULL; var_v0 = *(u8 **)(var_v0 + 8)) {
        if (arg0 == *(s16 *)(var_v0 + 0x10)) {
            *(s8 *)(var_v0 + 0x16) = -2;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_200480/func_151D2D0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_200480/func_151D2DE0.s")
