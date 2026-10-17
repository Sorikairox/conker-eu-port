#include <ultra64.h>
#include "functions.h"
#include "variables.h"

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EB430/func_150BDC20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EB430/func_150BDE34.s")

s32 func_150BE01C(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);
    if ((*(s16 *)(arg0 + 0x1C) << 3) < temp_v0[0x1B]) {
        temp_v0[0x1B] = *(s16 *)(arg0 + 0x1C) << 3;
    }
    return 1;
}
