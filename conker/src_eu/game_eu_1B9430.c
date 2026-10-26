#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 func_15132FBC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
void func_151429E0(u8, u8 *, u8 *, u8 *);
void func_1518CFF0(u8 *, s32);

void func_1518BC20(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4) {
    struct {
        f32 u94;
        f32 u98;
        f32 u9C;
        u8 padA0[0xA];
        s16 uAA;
        s16 uAC;
        s16 uAE;
        s16 uB0;
        s16 uB2;
        s16 uB4;
        s16 uB6;
        s16 uB8;
        s16 uBA;
        s32 uBC;
        s32 uC0;
        s8 uC4;
        s8 uC5;
        u8 padC6[0x6];
        f32 uCC;
        f32 uD0;
        f32 uD4;
        f32 uD8;
        f32 uDC;
        f32 uE0;
        f32 uE4;
        f32 uE8;
        f32 uEC;
        f32 uF0;
        f32 uF4;
        f32 uF8;
        f32 uFC;
        f32 u100;
        f32 u104;
        f32 u108;
        f32 u10C;
        f32 u110;
        f32 u114;
        f32 u118;
        s32 u11C;
        s16 u120;
        s16 u122;
        s8 u124;
        u8 pad125[0x3];
        s32 u128;
        s8 u12C;
        s8 u12D;
        s8 u12E;
        s8 u12F;
        s8 u130;
        s8 u131;
        s8 u132;
        s8 u133;
        s8 u134;
        u8 pad135[0x1];
        s8 u136;
        u8 pad137[0x1];
        s32 u138;
        s8 u13C;
        u8 pad13D[0x1];
        s16 u13E;
        s16 u140;
    } sp;
    f32 temp_f12;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f28;
    f32 temp_f2;
    f32 temp_f30;
    s32 temp_s0;
    s32 temp_s1;
    s32 var_s2;

    sp.u122 = 4;
    sp.uE8 = 1.0f;
    sp.uEC = 1.0f;
    sp.uF0 = 1.0f;
    sp.u11C = 0x29E8;
    sp.u124 = 0;
    sp.u128 = 0;
    sp.u12C = 0xFF;
    sp.u12D = 1;
    sp.u12E = 0;
    sp.u12F = 0;
    sp.u130 = 0;
    sp.u131 = 0;
    sp.u132 = 0;
    sp.u133 = 0;
    sp.u134 = 0;
    sp.u136 = 2;
    sp.u138 = 0;
    sp.u13C = 0;
    sp.u13E = 0x4000;
    sp.u140 = 0;
    sp.uD0 = 0.4f;
    sp.u114 = 0.0f;
    sp.u118 = -1.3f;
    var_s2 = (func_150ADA20() & 7) + 3;
    if (var_s2 > 0) {
        do {
            temp_f24 = (func_150ADA68() * 0.7f) + 0.3f;
            temp_s0 = func_150ADA20() & 0xFF;
            temp_s1 = (-0x10 - (func_150ADA20() & 0x1F)) & 0xFF;
            temp_f26 = (func_150ADA68() * 10.0f) + 5.0f;
            temp_f20 = angle_byte_cos((temp_s0 - 0x40) & 0xFF);
            temp_f22 = angle_byte_cos(temp_s0 & 0xFF);
            temp_f28 = angle_byte_cos((temp_s1 - 0x40) & 0xFF);
            temp_f30 = angle_byte_cos(temp_s1 & 0xFF);
            temp_f2 = func_150ADA68() * 20.0f;
            sp.uF8 = arg1;
            temp_f12 = temp_f26 * temp_f30;
            sp.uF4 = (temp_f2 * temp_f20) + arg0;
            sp.uFC = (temp_f2 * temp_f22) + arg2;
            sp.u100 = temp_f12 * temp_f20;
            sp.u104 = -temp_f26 * temp_f28;
            sp.u108 = temp_f12 * temp_f22;
            sp.u120 = (func_150ADA20() & 0x1F) + 0x14;
            sp.uCC = temp_f24;
            sp.uD4 = temp_f24;
            sp.uD8 = temp_f24;
            sp.uDC = func_150ADA68() * 360.0f;
            sp.uE0 = func_150ADA68() * 360.0f;
            sp.uE4 = func_150ADA68() * 360.0f;
            sp.u10C = 25.0f - (func_150ADA68() * 50.0f);
            sp.u110 = 25.0f - (func_150ADA68() * 50.0f);
            func_15132FBC(&sp.uCC, 3, 0xFF, 0, arg3 & 0xFF, arg4);
            var_s2 -= 1;
        } while (var_s2 != 0);
    }
    sp.uAA = 0x1F4;
    sp.uAC = 0x1F4;
    sp.u94 = arg0;
    sp.u98 = arg1;
    sp.u9C = arg2;
    sp.uAE = (func_150ADA20() & 0xF) + 0x32;
    sp.uB0 = (func_150ADA20() & 0xF) + 0x32;
    sp.uB2 = 0;
    sp.uB4 = 0;
    sp.uB6 = (func_150ADA20() % 201U) + 0x12C;
    sp.uB8 = 0;
    sp.uBA = 0x258;
    func_151429E0(1, &sp.uBC, &(*(s32 *)((u8 *)&sp + 0x29)), &(*(s32 *)((u8 *)&sp + 0x2A)));
    func_151429E0(1, &(*(s32 *)((u8 *)&sp + 0x2B)), &sp.uC0, &(*(s32 *)((u8 *)&sp + 0x2D)));
    (*(s8 *)((u8 *)&sp + 0x2E)) = 0xFF;
    (*(s8 *)((u8 *)&sp + 0x2F)) = 0xFF;
    sp.uC4 = 0xA;
    sp.uC5 = 0;
    func_1518CFF0(&sp.u94, 1);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B9430/func_1518BC20.s")
#endif