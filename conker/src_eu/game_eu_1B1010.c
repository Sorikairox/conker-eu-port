#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1010/func_15183800.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1010/func_15183E20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1010/func_15183EE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1010/func_15183F60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1010/func_1518403C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1010/func_15184114.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1010/func_15184198.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1010/func_15184298.s")

s32 func_15184688(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x31C);
    if ((temp_v0 != NULL) && (temp_v0[0x57] != 0)) {
        return 1;
    }
    return 0;
}
