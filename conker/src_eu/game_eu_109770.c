#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_109770/func_150DBF60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_109770/func_150DC1E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_109770/func_150DC2F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_109770/func_150DCAD8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_109770/func_150DD420.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_109770/func_150DDBC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_109770/func_150DE450.s")

void func_150DE508(struct102 *arg0) {
    func_150DC2F0(arg0->unk28, arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_109770/func_150DE52C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_109770/func_150DE6AC.s")

s32 func_150DE824(struct102 *arg0) {
    s16 temp_v0 = arg0->unk1C;
    if (temp_v0 < 32) {
        arg0->unk28 = temp_v0 * 8;
    }
    return 1;
}

void func_150DE844(s16 *arg0) {
    arg0[0x34 / 2] -= 0x1A;
    arg0[0x36 / 2] -= 0x1A;
    if ((arg0[0x34 / 2] < 10) || (arg0[0x36 / 2] < 10)) {
        arg0[0x38 / 2] = 0;
    }
}
