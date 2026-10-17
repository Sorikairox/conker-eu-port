#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E39B0/func_151B61A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E39B0/func_151B6444.s")

void func_151B657C(u8 *arg0) {
    s32 temp_v0 = *(s32 *)(arg0 + 0x88);
    if (temp_v0 != 0) {
        func_100111C8(temp_v0);
        *(s32 *)(arg0 + 0x88) = 0;
    }
}
