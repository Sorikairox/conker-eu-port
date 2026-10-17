#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_1509CE20(s32 arg0) {
    return D_800877D0[arg0].unk0;
}

u16 func_1509CE40(s32 arg0) {
    return D_800877D0[arg0].unk8;
}

s32 func_1509CE60(s32 arg0) {
    return *(u16 *)((u8 *)&D_800877D0[arg0] + 0xA) & 0xFFF;
}

s32 func_1509CE88(s32 arg0) {
    return D_800877D0[arg0].unk4;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509CEA8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509CF78.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509CBD4.s")

void func_1509D0C4(s32 arg0);

void func_1509D0A4(s32 arg0) {
    func_1509D0C4(arg0);
}

s32 func_1509D274(s32, void (*)(s32), s32);
extern s32 D_800877DC;

void func_1509D0C4(s32 arg0) {
    func_1509D274(*(s32 *)((u8 *)&D_800877DC + (arg0 * 0x14)), func_1509D0C4, arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509D104.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509D1EC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509D274.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509D338.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509D464.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509D49C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509D590.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509DB90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509DD0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509DFCC.s")
