#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_1519F500.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_1519F678.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_1519F6D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_1519F738.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_1519F928.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_1519F970.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_1519F9FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_1519FA60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_1519FD60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_151A03DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_151A0DBC.s")

void func_151A0E98(u8 *arg0) {
    u8 *p = *(u8 **)(arg0 + 0x28) + 0x58;
    if (arg0[0x2C] == 6) {
        *(s32 *)(p + 4) = 0;
    } else {
        *(s32 *)(p + 0xC) = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_151A0EC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_151A0F5C.s")
