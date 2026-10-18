#include <ultra64.h>
#include "functions.h"
#include "variables.h"


f32 func_15144A74(u8 *, u8 *);
s32 func_15144E80(u8 *, u8 *, u8 *, u8 *);

void func_1514FBB0(u8 *arg0, u8 *arg1) {
    arg1[0] = 2;
    *(f32 *)(arg1 + 0x28) = *(f32 *)(arg0 + 0x20);
    if ((func_15144E80(arg0 + 0xC, arg1 + 0x10, arg1 + 0x1C, arg1 + 4) != 0) && (func_15144A74(arg1 + 4, arg0) < 0.0f)) {
        *(f32 *)(arg1 + 4) = -*(f32 *)(arg1 + 4);
        *(f32 *)(arg1 + 8) = -*(f32 *)(arg1 + 8);
        *(f32 *)(arg1 + 0xC) = -*(f32 *)(arg1 + 0xC);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_1514FC58.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_1514FD78.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_1514FE68.s")

s32 func_15146078(u8 *, s32 *, s32 *);
s32 func_1514FE68(u8 *, u8 *, s32 *, s32 *, f32, s32, s32);
void func_15150108(u8 *arg0, u8 arg1, s32 arg2) {
    s32 sp34[3];
    s32 sp28[3];
    if (func_15146078(arg0, sp34, sp28) != 0) {
        func_1514FE68(arg0 + 0x10, arg0, sp34, sp28, (*(f32 *)((u8 *)arg0 + 0xC)), (s32) arg1, arg2);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_1515016C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15150258.s")

void func_1514FBB0();
void func_151504B4();

void func_1515046C(s32 arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4) {
    u8 sp24[0x2C];
    func_1514FBB0(arg0, sp24);
    func_151504B4(sp24, arg1, arg2, arg3, arg4);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_151504B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_151506E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15150970.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15150D7C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_1515128C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15151500.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_1515176C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15151BE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15151FA8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_151522DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15152700.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15152A90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15152DE4.s")

extern u8 D_800A63C0[][3];

void func_1515302C(u8 *arg0) {
    u8 i = func_150ADA20() % 5U;
    u8 *e = D_800A63C0[i];

    arg0[3] = func_150ADA20() % 101U + 0x9B;
    arg0[0] = e[0];
    arg0[1] = e[1];
    arg0[2] = e[2];
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_151530A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_151534E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15153808.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15153BA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15153F24.s")

void func_1515423C();

void func_151541F4(s32 arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4) {
    u8 sp24[0x2C];
    func_1514FBB0(arg0, sp24);
    func_1515423C(sp24, arg1, arg2, arg3, arg4);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_1515423C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15154488.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15154728.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15154A9C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15154BF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15154DF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15154FF8.s")
