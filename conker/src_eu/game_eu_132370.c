#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
void func_15104B60(s32 arg0, s32 arg1, f32 arg2) { /* P95: f32 (float bits were passed as an int) */
#else
void func_15104B60(s32 arg0, s32 arg1, s32 arg2) {
#endif
}

s32 func_15104B74(s32 arg0, s32 arg1) {
    return 1;
}

void func_15104B88(f32 arg0, f32 arg1, s32 arg2, s32 arg3) {
}

s32 func_15104BA0(s32 arg0, s32 arg1) {
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_132370/func_15104BB4.s")
