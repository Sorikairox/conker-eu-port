#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E0E70/func_151B3660.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E0E70/func_151B3734.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E0E70/func_151B3878.s")

void func_151B3FE4(u8 *arg0, s32 arg1, u8 arg2) {
    void (*fp)(void *, s32, u8) = D_8008FF08[arg0[0x44]];
    if (fp != NULL) {
        fp(arg0, arg1, arg2);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E0E70/func_151B402C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E0E70/func_151B42A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E0E70/func_151B44D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E0E70/func_151B458C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E0E70/func_151B4854.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E0E70/func_151B4D88.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E0E70/func_151B4E8C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E0E70/func_151B4F3C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E0E70/func_151B4FC4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E0E70/func_151B5128.s")

void func_151D5E30();

void func_151B51CC(void *arg0) {
    void (*fp)(void *);
    func_151D5E30((u8 *)arg0 + 0x140, arg0);
    fp = D_8008FF10[((u8 *)arg0)[0x44]];
    if (fp != NULL) {
        fp(arg0);
    }
}

void func_151B51CC(void *arg0);

void func_151B521C(void *arg0) {
    func_151B51CC(arg0);
    func_15169824(arg0);
}

void func_151B5248(void *arg0) {
    func_151B51CC(arg0);
    func_15169824(arg0);
}
