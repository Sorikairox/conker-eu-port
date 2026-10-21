#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
f32 func_150ADDE0(u8 *arg0, u8 *arg1) {
    return ((*(f32 *)((u8 *)arg0 + 0)) * (*(f32 *)((u8 *)arg1 + 0))) + ((*(f32 *)((u8 *)arg0 + 4)) * (*(f32 *)((u8 *)arg1 + 4))) + ((*(f32 *)((u8 *)arg0 + 8)) * (*(f32 *)((u8 *)arg1 + 8)));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DB5F0/func_150ADDE0.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DB5F0/func_150AD930.s")
