#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_150EBA04(void *arg0, f32 *arg1, s32 arg2);

void func_150EB430(void *arg0, void *arg1, s32 arg2) {
    f32 sp1C[3];

    sp1C[0] = ((f32 *)arg1)[0] + ((f32 *)arg0)[0];
    sp1C[1] = ((f32 *)arg1)[1] + ((f32 *)arg0)[1];
    sp1C[2] = ((f32 *)arg1)[2] + ((f32 *)arg0)[2];
    func_150EBA04(arg0, sp1C, arg2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1191C0/func_150EBA04.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1191C0/func_150EBB94.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1191C0/func_150EBE44.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1191C0/func_150EC200.s")
