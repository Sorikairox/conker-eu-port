#include <ultra64.h>
#include "functions.h"
#include "variables.h"


u8 *func_15169E70(u8 *arg0, s32 arg1) {
    u8 *temp_v0;

    temp_v0 = func_15167A68(0x5E, 0, 0x4C, 0, (u8) arg1, 1U);
    if (temp_v0 != NULL) {
        bcopy(arg0, temp_v0 + 0x10, 0x3C);
    }
    return temp_v0;
}

void func_15169ED8(s32 arg0) {
    func_15169E70(arg0, 0xFF);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_197680/func_15169EF8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_197680/func_15169FB8.s")
