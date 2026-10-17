#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B7D70/func_1518A560.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B7D70/func_1518A604.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B7D70/func_1518A784.s")

s32 func_1518A858(u8 *arg0, u8 *arg1) {
    if ((*(u8 **)(arg0 + 0x188))[0x6A] != 0) {
        *(s32 *)(arg0 + 0x58) &= ~2;
        *arg1 = 0;
    } else {
        *arg1 = 1;
    }
    return 1;
}

s32 func_1518A894(u8 *arg0, u8 *arg1) {
    if ((*(u8 **)(arg0 + 0x188))[0x6F] == 0) {
        *(s32 *)(arg0 + 0x58) &= ~2;
        *arg1 = 0;
    } else {
        *arg1 = 1;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B7D70/func_1518A8D0.s")
