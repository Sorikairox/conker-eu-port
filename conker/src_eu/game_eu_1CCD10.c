#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_1519F500.s")

void func_1519F678(u8 *arg0) {
    u8 **temp_v0 = *(u8 ***)(arg0 + 0x98);
    s32 *temp_a0;

    if (*temp_v0 != NULL) {
        temp_a0 = (s32 *)(*temp_v0 + 0x58);
        if (*(s32 *)(arg0 + 0x20) == 6) {
            temp_a0[0] = 0;
        }
        if (*(s32 *)(arg0 + 0x20) == 7) {
            temp_a0[2] = 0;
        }
    }
    func_15147E64(arg0);
}

void func_1519F6D8(u8 *arg0) {
    u8 **temp_v0 = *(u8 ***)(arg0 + 0x98);
    s32 *temp_a0;

    if (*temp_v0 != NULL) {
        temp_a0 = (s32 *)(*temp_v0 + 0x58);
        if (*(s32 *)(arg0 + 0x20) == 6) {
            temp_a0[0] = 0;
        }
        if (*(s32 *)(arg0 + 0x20) == 7) {
            temp_a0[2] = 0;
        }
    }
    func_15147E98(arg0);
}

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
