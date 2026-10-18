#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F3040/func_151C5280.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F3040/func_151C5B38.s")

void func_151C5C54(u8 *arg0, u8 arg1, s32 arg2) {
    s8 sp48[8];
    s32 sp3C[3];

    sp48[0] = 3;
    sp48[1] = -1;
    *(s16 *)(sp48 + 2) = (func_150ADA20() % 3U) + 3;
    sp48[4] = 0;
    sp3C[0] = *(f32 *)(arg0 + 0);
    sp3C[1] = *(f32 *)(arg0 + 4);
    sp3C[2] = *(f32 *)(arg0 + 8);
    func_151602C0(sp48, sp3C, (func_150ADA20() & 1) + 6, 0xFF, 0xE8, 0xAB, 0xFFU, 0U, 0, arg1, arg2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F3040/func_151C5D2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F3040/func_151C6424.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F3040/func_151C64F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F3040/func_151C6750.s")

s32 func_151C6840(u8 *arg0, s32 arg1, s32 arg2) {
    switch (arg0[4]) {
        case 0x5A:
        case 0x74:
        case 0x7A:
            return 0;
        default:
            return 1;
    }
}
