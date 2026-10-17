#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E40E0/func_151B68D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E40E0/func_151B69D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E40E0/func_151B6B84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E40E0/func_151B6ED8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E40E0/func_151B7664.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E40E0/func_151B76F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E40E0/func_151B78D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E40E0/func_151B7C28.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E40E0/func_151B7C7C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E40E0/func_151B7DA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E40E0/func_151B7F48.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E40E0/func_151B81E8.s")

void func_151B887C(u8 *arg0, s32 arg1, u8 arg2) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);
    void (*temp_v1)(u8 *, s32, u8) = D_8008FF38[temp_v0[8]];

    if (temp_v1 != NULL) {
        temp_v1(arg0, arg1, arg2);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E40E0/func_151B88C8.s")

void func_151B8920(u8 *arg0) {
    struct102 **temp_v0 = *(struct102 ***)(arg0 + 0x98);
    struct102 *temp_a1 = *temp_v0;

    if (temp_a1 != NULL) {
        func_1516972C(temp_a1);
    }
}

void func_151B8950(s32 arg0) {
    func_151B8920(arg0);
    func_15147E64(arg0);
}

void func_151B897C(s32 arg0) {
    func_151B8920(arg0);
    func_15147E98(arg0);
}
