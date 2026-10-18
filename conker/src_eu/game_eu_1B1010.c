#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1010/func_15183800.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1010/func_15183E20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1010/func_15183EE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1010/func_15183F60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1010/func_1518403C.s")

extern u8 D_800A76B0[];
extern s32 D_800DDF78[];

Gfx *func_15184114(Gfx *gdl, s32 arg1, s32 arg2, s32 arg3) {
    s32 i;
    s32 idx = -1;

    for (i = 0; i < 11; i++) {
        if (arg1 == D_800A76B0[i]) {
            idx = i;
            break;
        }
    }
    if (idx != -1) {
        if (D_800DDF78[idx] != 0) {
            gSPDisplayList(gdl++, D_800DDF78[idx]);
        }
    }
    return gdl;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1010/func_15184198.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1010/func_15184298.s")

s32 func_15184688(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x31C);
    if ((temp_v0 != NULL) && (temp_v0[0x57] != 0)) {
        return 1;
    }
    return 0;
}
