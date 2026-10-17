#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B8AA0/func_1518B290.s")

s32 func_1518B71C(f32 *arg0) {
    if (arg0[0x3C / 4] < arg0[0x170 / 4]) {
        return 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B8AA0/func_1518B748.s")

void func_1518B7D4(s32 arg0, f32 arg1, f32 arg2, s32 arg3, u8 arg4) {
    func_1518B818(arg0, arg1, arg2, arg3, 4, 0xFF, arg4);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B8AA0/func_1518B818.s")
