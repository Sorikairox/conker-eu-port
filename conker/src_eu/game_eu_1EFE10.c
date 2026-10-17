#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C2600.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C284C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C2CE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C3080.s")

s32 func_151C33FC(u8 *arg0, u8 *arg1) {
    if (arg0 == arg1) {
        return 0;
    }
    if (*(s32 *)arg0 == 0) {
        return 0;
    }
    if (arg0[4] == 0xFF) {
        return 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C3444.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C34A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C34F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C384C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C3C88.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C40BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C491C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C4990.s")

void func_151C4AC0(u8 *arg0, u8 *arg1, f32 arg2) {
    (*(f32 *)((u8 *)arg0 + 0x34)) += ((*(f32 *)((u8 *)arg1 + 4)) * arg2);
    (*(f32 *)((u8 *)arg0 + 0x38)) += ((*(f32 *)((u8 *)arg1 + 8)) * arg2);
    (*(f32 *)((u8 *)arg0 + 0x3C)) += ((*(f32 *)((u8 *)arg1 + 0xC)) * arg2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C4B0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C4BF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C4DD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C5060.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C50BC.s")
