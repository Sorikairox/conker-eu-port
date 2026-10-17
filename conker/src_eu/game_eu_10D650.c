#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10D650/func_150DFE40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10D650/func_150DFEA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10D650/func_150E0150.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10D650/func_150E0228.s")

void func_150E0324(u8 *arg0) {
    f32 *temp_v0 = (f32 *)(*(u8 **)(arg0 + 0x1D4) + 0x40);
    temp_v0[0x30 / 4] = *(f32 *)(arg0 + 0x14);
    temp_v0[0x34 / 4] = D_800A1380;
    temp_v0[0x38 / 4] = *(f32 *)(arg0 + 0x1C);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10D650/func_150E0350.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10D650/func_150E047C.s")

void func_150E0840(u8 *arg0, s32 arg1, u8 arg2) {
    func_15149514(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}

void func_150E0880(void) {
    if (D_80088D20 == 0) {
        func_1515F170(6, 0);
        func_1513BAE8();
        D_80088D20 = 1;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10D650/func_150E08C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10D650/func_150E0978.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10D650/func_150E0B78.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10D650/func_150E0C58.s")
