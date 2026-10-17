#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_BC930/func_1508F120.s")

void func_1508F21C(u32 arg0) {
    if (arg0 < D_80087380) {
        *(s16 *)(D_800D23C0 + arg0 * 0x18 + 2) = 0;
        *(s32 *)(D_800D23C0 + arg0 * 0x18 + 4) = 0;
        *(s16 *)(D_800D23C0 + arg0 * 0x18) = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_BC930/func_1508F26C.s")
