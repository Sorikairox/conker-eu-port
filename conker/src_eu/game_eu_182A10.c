#include <ultra64.h>
#include "functions.h"
#include "variables.h"

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_182A10/func_15155200.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_182A10/func_151552F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_182A10/func_151559FC.s")

void func_15155AD4(u8 *arg0, s32 arg1, u8 arg2) {
    void (*fp)(void *, s32, u8) = D_8008B0A4[arg0[0x2A]];
    if (fp != NULL) {
        fp(arg0, arg1, arg2);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_182A10/func_15155B1C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_182A10/func_15155C9C.s")
