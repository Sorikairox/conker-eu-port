#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_136060/func_eu_15108850.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_136060/func_15108BD8.s")

void func_15108D7C(u8 *arg0, s32 arg1, u8 arg2) {
    struct212 *temp_v0 = (struct212 *)(arg0 + 0x28);

    if (arg2 == 0x2B) {
        temp_v0->unk8 |= 1;
    } else if (arg2 == 0x2C) {
        temp_v0->unk8 &= ~1;
    }
}
