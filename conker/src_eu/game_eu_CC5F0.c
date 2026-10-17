#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CC5F0/func_1509EDE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CC5F0/func_1509F254.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CC5F0/func_1509F4D0.s")

s32 func_1509F728(s32 arg0, s32 *arg1) {
    if (arg0 != 0) {
        func_100111C8((arg1[0] & 0xFFFF0000) >> 16);
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CC5F0/func_1509F764.s")

s32 func_1509F81C(s32 arg0, s32 arg1, s32 arg2) {
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CC5F0/func_1509F834.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CC5F0/func_1509F95C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CC5F0/func_1509F9C8.s")

void func_1509FA88(s32 arg0, s32 arg1, s32 arg2) {
    func_10010F30(func_1000F568(arg0, (u8)(arg1 - arg0 + 1)), arg2, 0x40, 0, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CC5F0/func_1509FAD4.s")

void func_1509FB40(s32 arg0, s32 arg1) {
    struct127 *temp_v0 = func_1505EEF4(arg0);

    if (temp_v0 != NULL) {
        if (arg1 != 0) {
            func_10010A3C(temp_v0);
        } else {
            func_100109D0(temp_v0);
        }
    }
}

void func_1509FB90(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_10010F30(arg0, arg1, arg3, arg2, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CC5F0/func_1509FBC8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CC5F0/func_1509FC5C.s")

s32 func_1509FCE0(s32 arg0, s32 arg1, s32 arg2) {
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CC5F0/func_1509FCF8.s")
