#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_18DB20/func_15160310.s")

u8 *func_151604E4(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    u8 *temp_v0;

    temp_v0 = func_15167A68(0x34, arg3, arg1 + 0x18, 1, (u8) (s32) arg2, 1U);
    if (temp_v0 == NULL) {
        return NULL;
    }
    memcpy(temp_v0 + 0xE, arg0, 8);
    return temp_v0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_18DB20/func_1516055C.s")

void func_eu_15160600(u8 *arg0, s32 arg1, u8 arg2) {
    void (*temp_v0)(u8 *, s32, u8) = D_8008B484[arg0[0x14]];

    if (temp_v0 != NULL) {
        temp_v0(arg0, arg1, arg2);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_18DB20/func_15160648.s")

void func_151607E4(s32 arg0, u8 arg1) {
    const s32 sp1C[1] = {0x34};

    func_15169260(sp1C, 0x1, arg0, arg1);
}
