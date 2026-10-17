#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_15100700(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    func_151494E0(&tmp, 0x48);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12DF10/func_15100734.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12DF10/func_151007B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12DF10/func_1510083C.s")
