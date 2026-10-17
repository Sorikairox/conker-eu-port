#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F8DF0/func_150CB5E0.s")

s32 func_150CB6E0(s32 arg0, s32 arg1) {
    return 11;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F8DF0/func_150CB6F4.s")

s32 func_150CBCDC(u8 *arg0) {
    s16 temp_v0 = *(s16 *)(arg0 + 0x1C);
    if (temp_v0 < 32) {
        if ((temp_v0 * 8) < arg0[0x28]) {
            arg0[0x28] = temp_v0 * 8;
        }
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F8DF0/func_150CBD10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F8DF0/func_150CBF40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F8DF0/func_150CBFCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F8DF0/func_150CC1F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F8DF0/func_150CC398.s")

void func_150CC46C(u8 *arg0) {
    *(s32 *)(arg0 + 0x58) |= 1;
    *(s16 *)(arg0 + 0x1C) = 0x20;
}
