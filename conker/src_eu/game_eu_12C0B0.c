#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_151030B8(struct127 *, u8, u8 *, s32 *, f32 *, s32, s32, f32, s32, s32, s32, s32, s32, s32);
extern f32 D_800A23B0[];
s32 func_151C284C(s32 *, s32 *, s32, s32, s32, s32, f32, f32, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, s32, s32, s32, s32, s32);
s32 func_150FE49C(struct127 *, u8, s32, s32 *, s32 *);
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
    return func_151C284C(sp90, sp84, 0, 0, 0, 0, 300.0f, 0.0033333334f, (func_150ADA68() * 10.0f) + 25.0f, (func_150ADA68() * 200.0f) + 600.0f, 50.0f, (func_150ADA20() % 56U) + 0xC8, arg0, 1, 1, 0, 0xFF, 1, 1, 0, 0x23, 0.0f, 0xFF, -1, 0, (s32) arg1, arg2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12C0B0/func_150FE49C.s")

void func_150FEB84(struct127 *arg0, s32 arg1, u8 arg2, s32 arg3) {
    f32 sp60[2];
    u8 sp5F;

    if ((arg0->unk1D4 != NULL) && ((arg0->unk74 & 0xF) != 0xF)) {
        sp60[1] = (func_150ADA68() * 2) + 3.7099998f; // 0x406D70A3 (3.71f would round to ...A4)
        sp60[0] = (func_150ADA68() * 15.0f) + 35.0f;
        if ((arg0->unk31C != NULL) && (arg0->unk31C->unk197 != 0) && (arg0->camera != NULL)) {
            sp5F = (~(1 << arg0->camera->unk23D)) & 0xFFFFu;
        } else {
            sp5F = 0xFF;
        }
        func_151030B8(arg0, D_80088F34, D_800A2398, (s32 *)D_800A23B0, sp60, (func_150ADA20() % 3U) + 4, (func_150ADA20() % 56U) + 0xC8, (func_150ADA68() * 301.0f) + 500.0f, arg1, (s32) sp5F, 0, -1, (s32) arg2, arg3);
    }
}

void func_150FED14(s32 arg0, s32 arg1, s32 arg2) {
    func_151D43B4(arg0, arg2, D_800A2398, D_80088F34, 0.0f);
}

void func_150FED54(u8 *arg0) {
    s8 sp18[8];
    if (*(s32 *)(arg0 + 0x318) != 0) {
        sp18[0] = 1;
        *(s16 *)(sp18 + 2) = ((u32)func_150ADA20() % 13) + 0x14;
        sp18[5] = 1 << (*(u8 **)(arg0 + 0x318))[0x23D];
        func_150ADA20();
        sp18[4] = 8;
        sp18[6] = -1;
        func_151D8E18(sp18, 0, 0xFF, 1);
    }
}
