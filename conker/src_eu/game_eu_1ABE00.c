#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ABE00/func_1517E080.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ABE00/func_1517E6A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ABE00/func_1517E71C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ABE00/func_1517E7FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ABE00/func_1517EA18.s")

Gfx *func_1517EFBC(Gfx *arg0) {
    gDPPipeSync(arg0++);
    gDPSetCombine(arg0++, 0xFFB3FF, 0xFF65FEFF);
    gDPSetOtherMode(arg0++, 0x2C0F, 0x504344);
    return arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ABE00/func_1517F01C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ABE00/func_1517F18C.s")
