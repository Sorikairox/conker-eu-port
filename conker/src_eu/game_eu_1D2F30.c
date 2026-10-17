#include <ultra64.h>
#include "functions.h"
#include "variables.h"

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D2F30/func_151A5720.s")

void func_151A5B84(u8 *arg0, s32 arg1, u8 arg2) {
    void (*f)(s32, void *, u8) = D_8008FCA4[arg0[0x19]];
    if (f != NULL) {
        f(arg0, arg1, arg2);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D2F30/func_151A5BCC.s")
