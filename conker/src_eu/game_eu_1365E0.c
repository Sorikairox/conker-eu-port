#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1365E0/func_15108850.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1365E0/func_15109034.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1365E0/func_15109100.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1365E0/func_15109140.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1365E0/func_151091B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1365E0/func_151092A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1365E0/func_15109390.s")

void func_1510957C(s32 arg0, s32 arg1, u8 arg2) {
    struct {
        s32 unk0;
        s32 unk4;
        u8 unk8;
    } sp24;
    s32 sp1C[2] = {0x38, 0x54};

    sp24.unk0 = arg0;
    sp24.unk4 = arg1;
    sp24.unk8 = arg2;
    func_15169260(sp1C, 2, (s32)&sp24, 0x1D);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1365E0/func_151095E4.s")

void func_1510965C(void) {
    s32 sp18[2] = {0x38, 0x54};

    func_15169260(sp18, 2, 0, 0x1E);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1365E0/func_151096A0.s")
