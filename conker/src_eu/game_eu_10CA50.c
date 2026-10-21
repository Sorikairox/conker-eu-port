#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10CA50/func_150DF240.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10CA50/func_150DF8B4.s")

#ifdef NON_MATCHING
s32 func_15149AC0(f32 *, s32, s32, s32, s32, s32);

void func_150DFA38(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    struct {
        f32 u88;
        u8 pad8C[0x4];
        f32 u90;
        f32 u94;
        f32 u98;
        f32 u9C;
        f32 uA0;
        f32 uA4;
        s16 uA8;
        s16 uAA;
        s16 uAC;
        s8 uAE;
        s8 uAF;
        s8 uB0;
        s8 uB1;
        s16 uB2;
        s8 uB4;
        s8 uB5;
        s8 uB6;
        s8 uB7;
        s32 uB8;
        s8 uBC;
        u8 padBD[0x3];
        f32 uC0;
        f32 uC4;
        f32 uC8;
        f32 uCC;
    } sp;
    f32 temp_f10;
    f32 temp_f18;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f2;
    f32 temp_f2_2;
    s32 temp_s7;
    s32 var_s0;

    temp_s7 = arg3 & 0xFF;
    (*(f32 *)((u8 *)(&sp.u88) + 0)) = (*(f32 *)((u8 *)arg0 + 0));
    (*(s32 *)((u8 *)(&sp.u88) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 4));
    (*(f32 *)((u8 *)(&sp.u88) + 8)) = (f32) (*(f32 *)((u8 *)arg0 + 8));
    temp_f20 = (func_150ADA68() * 0.5f) + 1.0f;
    temp_f10 = func_150ADA68() * 0.5f;
    sp.u94 = 22.6f * temp_f20;
    sp.u9C = 13.786f * temp_f20;
    temp_f2 = temp_f10 + 1.0f;
    sp.uAA = 0x1A4D;
    sp.uA8 = 0x6231;
    sp.u98 = 57.969f * temp_f2;
    sp.uA0 = 42.714f * temp_f2;
    sp.uA4 = 118.763f * temp_f2;
    sp.uAC = (func_150ADA20() % 151U) + 0x96;
    sp.uAE = 0;
    sp.uAF = 0;
    sp.uB0 = 0;
    sp.uB1 = 0xFF;
    sp.uB2 = 1;
    sp.uB4 = (func_150ADA20() % 156U) + 0x64;
    sp.uB5 = 0xFF;
    sp.uB6 = 0;
    sp.uB7 = 1;
    sp.uB8 = 0;
    sp.uBC = 0xF;
    sp.uC4 = 10000.0f;
    sp.uC8 = 0.045f;
    sp.uC0 = 0.0f;
    sp.uCC = 0.7f;
    func_15149AC0(&sp.u88, 0xA, 0, 0, temp_s7, arg4);
    var_s0 = (func_150ADA20() % 3U) + 1;
    if (var_s0 > 0) {
        do {
            func_15143874((s16) (func_150ADA20() & 0xFF), 0x41F00000, &sp.u88, &sp.u90);
            sp.u88 += (*(f32 *)((u8 *)arg0 + 0));
            sp.u90 += (*(f32 *)((u8 *)arg0 + 8));
            temp_f20_2 = (func_150ADA68() * 0.5f) + 0.75f;
            temp_f18 = func_150ADA68() * 0.5f;
            sp.u94 = 22.6f * temp_f20_2;
            sp.u9C = 13.786f * temp_f20_2;
            temp_f2_2 = temp_f18 + 0.75f;
            sp.u98 = 57.969f * temp_f2_2;
            sp.uA0 = 42.714f * temp_f2_2;
            sp.uA4 = 118.763f * temp_f2_2;
            sp.uAC = (func_150ADA20() % 151U) + 0x96;
            sp.uB4 = (func_150ADA20() % 156U) + 0x64;
            sp.uB7 = 0;
            func_15149AC0(&sp.u88, 0xA, 0, 0, temp_s7, arg4);
            var_s0 -= 1;
        } while (var_s0 != 0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10CA50/func_150DFA38.s")
#endif