#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_150A2D44(s32, s32);

s32 func_150A0890(s32 arg0, u32 arg1, u8 *arg2) {
    switch (arg1) {
    case 0:
        func_150A2D44(arg0, 0);
        return 1;
    case 1:
        func_150A2D44(arg0, 1);
        return 1;
    case 2:
        func_150A2E20(arg0, (*(s32 *)(arg2 + 8)), (*(s32 *)(arg2 + 0xC)));
        return 1;
    case 3:
        func_150A3924(arg0, (*(s16 *)(arg2 + 0xA)), (*(s16 *)(arg2 + 0xE)), (*(s16 *)(arg2 + 0x12)));
        return 0;
    case 4:
        func_150A3878(arg0, (u16) (*(s16 *)(arg2 + 0xA)), (*(s32 *)(arg2 + 0xC)), (*(s32 *)(arg2 + 0x10)), (*(s32 *)(arg2 + 0x14)), (*(s32 *)(arg2 + 0x18)));
        return 0;
    case 5:
        func_151C9CBC(*(s32 *)(arg2 + 8) == 0x3E7 ? 2 : (*(s32 *)(arg2 + 8) != 0 ? 0 : 1), (arg0 * 0x34) + D_800D34B8);
        break;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE0A0/func_150A09B8.s")
