#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_100410/func_150D2C00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_100410/func_150D2C9C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_100410/func_150D2E34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_100410/func_150D327C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_100410/func_150D368C.s")

void func_150D380C(u8 *arg0, u8 *arg1, u8 arg2) {
    u8 *p;
    if (arg2 == 0x34) {
        p = (*(u8 **)&arg0) + 0x28;
        if (arg1[0] == p[0x51]) {
            func_150D2C9C(*(s32 *)p, p + 0x10, arg0[0xC], arg0[1]);
        }
    }
}
