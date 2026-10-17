#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_150F7330(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    func_151494E0((s32)&tmp, 0x3E);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_124B40/func_150F7364.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_124B40/func_150F75EC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_124B40/func_150F7890.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_124B40/func_150F791C.s")

void func_150F798C(void *arg0) {
    func_150F791C(arg0);
    func_1514933C(arg0);
}

void func_150F79B8(void *arg0) {
    func_150F791C(arg0);
    func_15149368(arg0);
}
