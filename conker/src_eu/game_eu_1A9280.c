#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A9280/func_1517BA70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A9280/func_1517BC58.s")

s32 func_1517BD18(s16 *arg0, s16 *arg1, s32 *arg2, s32 arg3) {
    if (*arg2 >= 0x300) {
        if (*arg2 >= 0x501) {
            *arg2 -= 0x200;
        } else {
            *arg2 = 0x300;
        }
    }
    arg1[0] = arg0[0];
    arg1[1] = arg0[1];
    arg1[2] = arg0[2];
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A9280/func_1517BD68.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A9280/func_1517BE0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A9280/func_1517C11C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A9280/func_1517D534.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A9280/func_1517D5E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A9280/func_1517DAE8.s")

s32 func_1517DAE8(s16, s16, s16, f32, s32, s32, s32);

void func_1517DB6C(s16 arg0, s16 arg1, s16 arg2, s32 arg3, s32 arg4, s32 arg5) {
    func_1517DAE8(arg0, arg1, arg2, D_800DBFF0[arg3].unk380, arg4, arg5, (s32) D_800DDD1C >> 3);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A9280/func_1517DC00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A9280/func_1517D7B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A9280/func_1517E3CC.s")

void func_1517E5CC(s32 arg0, s32 arg1, s32 arg2) {
    D_800DD8A0[0] = arg0;
    D_800DD8A0[1] = arg1;
    D_800DD8A0[2] = arg2;
}
