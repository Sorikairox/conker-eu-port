#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_151046F0(s32 arg0, s32 arg1, s32 arg2) {
    u8 *temp_v0;

    temp_v0 = func_15167A68(0x64, 0, 0x20, 0, 0xFFU, 1U);
    if (temp_v0 != NULL) {
        (*(s16 *)((u8 *)temp_v0 + 0x18)) = 0xC;
        (*(s8 *)((u8 *)temp_v0 + 0x1A)) = 0;
        (*(s8 *)((u8 *)temp_v0 + 0x1B)) = 0;
        (*(s32 *)((u8 *)temp_v0 + 0x10)) = arg1;
        (*(s32 *)((u8 *)temp_v0 + 0x14)) = arg2;
        (*(s8 *)((u8 *)temp_v0 + 0x1C)) = (s8) arg0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_131F00/func_15104764.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_131F00/func_15104A0C.s")

s32 func_151044F4(void) {
    u8 *temp_v1 = D_800CCA0C;
    s32 ret = 0;

    if (temp_v1 != NULL) {
        return temp_v1[0x7D];
    }
    return ret;
}
