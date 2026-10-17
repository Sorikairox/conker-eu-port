#include <ultra64.h>
#include "functions.h"
#include "variables.h"

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_126330/func_150F8B20.s")

void func_150F8DCC(s32 arg0, s32 arg1) {
    s32 tmp[2];
    tmp[0] = arg1;
    func_151494E0(tmp, 0x3F);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_126330/func_150F8DFC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_126330/func_150F8EAC.s")

extern u8 D_800A2010[][2];

void func_150F9CA0(u8 arg0) {
    struct {
        s32 unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = 0;
    tmp.unk4 = D_800A2010[arg0][0];
    func_151494E0(&tmp, 0x42);
    tmp.unk4 = D_800A2010[arg0][1];
    func_151494E0(&tmp, 0x42);
}

void func_150F9D08(s32 arg0) {
}

void func_150F9D14(struct260 *arg0) {
    func_150F9D08(arg0);
    func_1514933C(arg0);
}

void func_150F9D40(struct260 *arg0) {
    func_150F9D08(arg0);
    func_15149368(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_126330/func_150F9D6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_126330/func_150F9ED0.s")
