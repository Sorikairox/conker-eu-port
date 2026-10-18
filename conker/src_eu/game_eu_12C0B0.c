#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern f32 D_800A23BC;
s32 func_151C284C(s32 *, s32 *, s32, s32, s32, s32, f32, f32, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, s32, s32, s32, s32, s32);
s32 func_150FE49C(s32, u8, s32, s32 *, s32 *);
s32 func_150FE320(s32 arg0, u8 arg1, s32 arg2) {
    s32 pad; // fakematch: unused local moves the unnamed f32 spill temps down (frame layout)
    s32 spA8[3];
    s32 sp9C[3];
    s32 sp90[3];
    s32 sp84[3];

    if (arg0 == 0) {
        return 0;
    }
    func_15145740(arg0, (s32) sp84, (s32) spA8, 0, 0.0f);
    func_150FE49C(arg0, arg1, arg2, sp9C, sp90);
    return func_151C284C(sp90, sp84, 0, 0, 0, 0, 300.0f, D_800A23BC, (func_150ADA68() * 10.0f) + 25.0f, (func_150ADA68() * 200.0f) + 600.0f, 50.0f, (func_150ADA20() % 56U) + 0xC8, arg0, 1, 1, 0, 0xFF, 1, 1, 0, 0x23, 0.0f, 0xFF, -1, 0, (s32) arg1, arg2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12C0B0/func_150FE49C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12C0B0/func_150FEB84.s")

void func_150FED14(s32 arg0, s32 arg1, s32 arg2) {
    func_151D43B4(arg0, arg2, D_800A2398, D_80088F34, 0.0f);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12C0B0/func_150FED54.s")
