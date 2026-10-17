#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7450/func_151B9C40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7450/func_151B9F14.s")

void func_151BA1A0(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9, s16 argA, s16 argB, s16 argC, s32 argD, u8 argE, s32 argF) {
    u8 *temp_v0;

    temp_v0 = func_15167A68(7, argF, 0x2C, 0, (u8) (s32) argE, 1U);
    if (temp_v0 != NULL) {
        (*(s8 *)((u8 *)temp_v0 + 0x14)) = (s8) arg0;
        (*(s8 *)((u8 *)temp_v0 + 0x15)) = (s8) arg1;
        (*(s16 *)((u8 *)temp_v0 + 0x16)) = arg2;
        (*(s16 *)((u8 *)temp_v0 + 0x18)) = arg3;
        (*(s16 *)((u8 *)temp_v0 + 0x1A)) = arg4;
        (*(s16 *)((u8 *)temp_v0 + 0x1C)) = arg5;
        (*(s16 *)((u8 *)temp_v0 + 0x1E)) = arg6;
        (*(s16 *)((u8 *)temp_v0 + 0x20)) = arg7;
        (*(s16 *)((u8 *)temp_v0 + 0x22)) = arg8;
        (*(s16 *)((u8 *)temp_v0 + 0x24)) = arg9;
        (*(s16 *)((u8 *)temp_v0 + 0x26)) = argA;
        (*(s16 *)((u8 *)temp_v0 + 0x28)) = argB;
        (*(s16 *)((u8 *)temp_v0 + 0x2A)) = argC;
        (*(s32 *)((u8 *)temp_v0 + 0x10)) = argD;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7450/func_151BA260.s")
