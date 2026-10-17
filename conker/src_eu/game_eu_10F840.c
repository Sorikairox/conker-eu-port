#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10F840/func_150E2030.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10F840/func_150E2294.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10F840/func_150E2E5C.s")

s32 func_150E3324(s32 arg0, s32 arg1) {
    return arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10F840/func_150E3334.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10F840/func_150E2EA4.s")

void func_150E3510(s32 arg0, s32 arg1, s16 arg2) {
    func_150E3324(arg0, arg2);
}

void func_150E3540(u8 *arg0, s32 *arg1, u8 arg2) {
    if (arg2 == 0x2D) {
        if (arg1[0] == *(s32 *)(arg0 + 0xDC)) {
            *(s32 *)(arg0 + 0xDC) = arg1[1];
            arg0[0xDA] = ((u8 *)arg1)[9];
            return;
        }
        if (arg1[1] == *(s32 *)(arg0 + 0xDC)) {
            *(s32 *)(arg0 + 0xDC) = arg1[0];
            arg0[0xDA] = ((u8 *)arg1)[8];
        }
    }
}
