#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_150D87C0(s32 arg0) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_105FD0/func_150D87CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_105FD0/func_150D88E8.s")

s16 *func_150D8AA0(s16 *arg0, s32 arg1) {
    arg0[0] = 0x42;
    arg0[1] = 0;
    return arg0 + 2;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_105FD0/func_150D8ABC.s")

s32 func_150D8DBC(u8 *arg0) {
    if ((*(u8 **)(arg0 + 0x18))[0x6F] != 0) {
        (*(u8 **)(arg0 + 0x14))[9] = 0;
    } else {
        (*(u8 **)(arg0 + 0x14))[9] = 1;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_105FD0/func_150D8DF0.s")

s32 func_150D8F30(s32 arg0, s32 arg1) {
    return 8;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_105FD0/func_150D8F44.s")
