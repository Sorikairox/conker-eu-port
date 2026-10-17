#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_129650/func_150FBE40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_129650/func_150FC8E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_129650/func_150FC438.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_129650/func_150FCB94.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_129650/func_150FCD98.s")

s32 func_150FCEB0(u8 *arg0, s32 arg1, s32 arg2) {
    switch (arg0[4]) {
        case 0x12:
        case 0x23:
        case 0x73:
        case 0x8A:
            return 0;
        default:
            return 1;
    }
}

void func_150FCEF4(u8 *arg0) {
    if (*(s32 *)(arg0 + 0x38) != 0) {
        func_1516972C(*(struct102 **)(arg0 + 0x38));
    }
}

void func_150FCF24(void *arg0) {
    func_150FCEF4(arg0);
    func_1514933C(arg0);
}

void func_150FCF50(void *arg0) {
    func_150FCEF4(arg0);
    func_15149368(arg0);
}
