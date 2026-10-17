#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BF960/func_15192150.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BF960/func_151922C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BF960/func_151925AC.s")

s32 func_151321F4(u8 *, u8 *, s32, u8 *, u8 *, u8 *);

s32 func_15192878(u8 *arg0, s32 arg1) {
    func_151321F4(arg0 + 0xAC, arg0 + 0xAE, (*(s32 *)((u8 *)arg0 + 0xA8)), arg0 + 0xB0, arg0 + 0x38, arg0 + 0x3C);
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BF960/func_151928C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BF960/func_15192AEC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BF960/func_151925C4.s")

void func_15192CEC(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}
