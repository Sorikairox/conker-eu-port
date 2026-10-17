#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E6E30.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E7104.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E73B4.s")

void func_150E7458(s32 arg0) {
    func_1514470C((&D_800D9A20)[func_150ADA20() & 1], arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E7498.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E752C.s")

void func_150E764C(f32 *arg0, f32 *arg1) {
    arg0[0] = arg1[5];
    arg0[1] = arg1[6];
    arg0[2] = arg1[7];
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E766C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E7764.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E7810.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E7B20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E7C50.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E7F14.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E821C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E856C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E8728.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E892C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E89F0.s")

s32 func_150E8DA4(u8 *arg0, s32 arg1) {
    func_15131D98(arg0, arg0 + 0xAC, arg0 + 0xA8, arg0 + 0xAA);
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E8854.s")

s32 func_150E8EB0(u8 *);
extern f32 D_800A1748;

void func_150E8E40(u8 *arg0) {
    (*(f32 *)((u8 *)arg0 + 0x28)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x28)) - D_800BE9A4);
    if ((*(f32 *)((u8 *)arg0 + 0x28)) < 0.0f) {
        (*(f32 *)((u8 *)arg0 + 0x28)) = (f32) ((func_150ADA68() * D_800A1748) + 201.0f);
        func_150E8EB0(arg0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E8EB0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E9000.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E909C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E92DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E965C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E96F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E995C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E9C9C.s")
