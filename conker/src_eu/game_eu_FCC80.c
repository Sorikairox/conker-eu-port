#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FCC80/func_150CF470.s")

f32 func_150CF550(s32 arg0, s32 arg1) {
    arg0++;
    arg1 -= 0x2C;
    return func_150484A0(arg0, arg1) * D_800A0C08;
}

void func_150CF590(struct127 *arg0) {
    *(s32 *)((u8 *)arg0 + 0x84) |= 0x4000;
}
