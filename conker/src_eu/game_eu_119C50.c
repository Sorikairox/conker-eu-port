#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_119C50/func_150EBEC0.s")

s32 func_150EC954(u8 *arg0, u8 *arg1) {
    s32 temp_v0;
    if (arg0 == arg1) {
        return 0;
    }
    if ((*(s32 *)((u8 *)arg0 + 0)) == 0) {
        return 0;
    }
    temp_v0 = (*(u8 *)((u8 *)arg0 + 4));
    if (temp_v0 == 0xFF) {
        return 0;
    }
    if ((temp_v0 == 0) || (temp_v0 == 1) || (temp_v0 == 2) || (temp_v0 == 3) || (temp_v0 == 4) || (temp_v0 == 0x28) || (temp_v0 == 0x77)) {
        return 1;
    }
    return 0;
}

void func_150EC9DC(s32 arg0) {
    func_151C40BC(arg0, 1.0f, 1.0f, 1.0f, 0.0f, 0xFF, 0xFF, 0xFF);
}
