#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12CAC0/func_150FF2B0.s")

extern s32 D_800A2420;
void func_150FF550(u8 *arg0, s16 arg1, u8 *arg2) {
    s32 *sp34;
    u8 *sp30;
    s32 temp_v0;
    if (arg1 == -1) {
        *(f32 *)(arg2 + 0) = *(f32 *)(arg0 + 0x14);
        *(f32 *)(arg2 + 4) = *(f32 *)(arg0 + 0x18);
        *(f32 *)(arg2 + 8) = *(f32 *)(arg0 + 0x1C);
        return;
    }
    temp_v0 = func_15031C4C(arg0, arg1, 0);
    if (temp_v0 == 0) {
        *(f32 *)(arg2 + 0) = *(f32 *)(arg0 + 0x14);
        *(f32 *)(arg2 + 4) = *(f32 *)(arg0 + 0x18);
        *(f32 *)(arg2 + 8) = *(f32 *)(arg0 + 0x1C);
        return;
    }
    sp34 = &D_800A2420;
    sp30 = arg2;
    func_1514654C(arg0, temp_v0, 0, &sp34, &sp30, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12CAC0/func_150FF604.s")

void func_150FF808(s32 arg0) {
    func_15031C4C(arg0, 0x82, 0);
}

void func_150FF82C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_15145740(arg0, arg1, arg2, arg3, 0.81100005f);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12CAC0/func_150FF854.s")

typedef struct { s32 x, y, z; } V3i;
void func_150FF9F4(u8 *arg0, s32 arg1, u8 arg2, s32 arg3) {

    s32 var_s0;
    s32 var_v0;
    u8 *temp_t4;
    struct {
        s8 u84;
        s8 u85;
        s16 u86;
        s16 u88;
        u8 pad8A[0x2];
        s32 u8C;
        s32 u90;
        u8 u94;
        u8 u95;
        u8 u96;
        u8 u97;
        f32 u98;
        f32 u9C;
        s32 uA0;
        u8 padA4[0x8];
        s32 uAC;
        u8 padB0[0x8];
        f32 uB8;
        f32 uBC;
        f32 uC0;
        s32 uC4;
        s8 uC8;
        u8 uC9;
        s8 uCA;
        s8 uCB;
        s32 uCC;
        u8 uD0;
    } sp;

    sp.u84 = 0x5F;
    sp.u85 = 5;
    sp.u86 = 0x2203;
    sp.u8C = 0;
    sp.u90 = 0;
    sp.u94 = 0xFF;
    sp.u95 = 0xFF;
    sp.u96 = 0xFF;
    sp.u97 = 0xFF;
    *(V3i *) &sp.uA0 = *(V3i *) arg0;
    sp.uB8 = 0.0f;
    sp.uBC = 0.0f;
    sp.uC0 = 0.0f;
    sp.uC4 = 0x40CC0009;
    sp.uC9 = 0xFF;
    sp.uCA = 0;
    sp.uCB = 7;
    sp.uD0 = 0xFF;
    sp.uCC = 0;
    sp.u88 = (func_150ADA20() & 3) + 3;
    for (var_s0 = 0; var_s0 < 6; var_s0 = (var_s0 + 1) & 0xFF) {
        sp.u98 = (func_150ADA68() * 11.1f) + 5.0f;
        temp_t4 = (0, arg1) + (var_s0 * 0xC); // fakematch: comma puts arg1 first in addu
        sp.u9C = (func_150ADA68() * 0.9990001f) + 2.483f;
        *(V3i *) &sp.uAC = *(V3i *) temp_t4;
        sp.uC8 = (func_150ADA20() % 156U) + 0x64;
        if (func_150ADA20() & 1) {
            var_v0 = 2;
        } else {
            var_v0 = 0;
        }
        func_1513D2F0(&sp.u84, (s32) &D_800A4AA0, 0U, 0U, 0U, 0x1BU, (u8) (var_v0 + 1), 0, 0, 0, arg2, arg3);
    }
}

s32 func_150FFC34(u8 *arg0, s32 arg1, s32 arg2) {
    if (arg0[4] == 0x98) {
        return 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12CAC0/func_150FFC60.s")
