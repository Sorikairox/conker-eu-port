#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F3040/func_151C5280.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F3040/func_151C5B38.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F3040/func_151C5C54.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F3040/func_151C5D2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F3040/func_151C6424.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F3040/func_151C64F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F3040/func_151C6750.s")

s32 func_151C6840(u8 *arg0, s32 arg1, s32 arg2) {
    switch (arg0[4]) {
        case 0x5A:
        case 0x74:
        case 0x7A:
            return 0;
        default:
            return 1;
    }
}
