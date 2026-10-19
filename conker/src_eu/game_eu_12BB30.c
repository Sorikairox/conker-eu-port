#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern f32 D_800A2364;
extern f32 D_800A2368;
s32 func_150FDF38(struct127 *, u8, s32, s32 *, s32 *);
s32 func_151C284C(s32 *, s32, s32 *, s32 *, s32, s32, f32, f32, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, s32, s32, s32, s32, s32);
s32 func_150FDDA0(s32 arg0, u8 arg1, s32 arg2) {
    s32 pad; // fakematch: unused local moves the unnamed f32 spill temps down (frame layout)
    s32 spB0[3];
    s32 spA4[3];
    s32 sp98[3];
    s32 sp8C[3];

    if (arg0 == 0) {
        return 0;
    }
    func_15145740(arg0, (s32) sp98, (s32) spB0, 0, 0.0f);
    func_150FDF38(arg0, arg1, arg2, spA4, sp8C);
    return func_151C284C(sp8C, 0, sp8C, sp98, 0, 0, 300.0f, D_800A2364, (func_150ADA68() * 10.0f) + 25.0f, (func_150ADA68() * 201.0f) + D_800A2368, 50.0f, (func_150ADA20() % 56U) + 0xC8, arg0, 1, 1, 0, 0xFF, 1, 1, 0, (D_800BE9F0 == 0x2B) ? 0x27 : 0x1A, 0.0f, 0xFF, -1, 0, (s32) arg1, arg2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12BB30/func_150FDF38.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12BB30/func_150FE638.s")

void func_150FE7C8(s32 arg0, s32 arg1, s32 arg2) {
    func_151D43B4(arg0, arg2, &D_800A2340, D_80088F20, 0.0f);
}

void func_150FE808(u8 *arg0) {
    s8 sp18[8];
    if (*(s32 *)(arg0 + 0x318) != 0) {
        sp18[0] = 1;
        *(s16 *)(sp18 + 2) = ((u32)func_150ADA20() % 9) + 0xF;
        sp18[5] = 1 << (*(u8 **)(arg0 + 0x318))[0x23D];
        sp18[4] = (func_150ADA20() & 3) + 3;
        sp18[6] = -1;
        func_151D8E18(sp18, 0, 0xFF, 1);
    }
}
