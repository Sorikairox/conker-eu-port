#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    /* 0x00 */ u8  pad0[0x18];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ u8  pad1E[0xA];
    /* 0x28 */ u8  unk28;
    /* 0x29 */ u8  pad29[0x81 - 0x29];
    /* 0x81 */ u8  unk81;
    /* 0x82 */ u8  pad82[0xB0 - 0x82];
    /* 0xB0 */ s16 unkB0;
    /* 0xB2 */ s16 unkB2;
} struct_eu_E88D0;

void func_1513F6C0();


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E88D0/func_150BABE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E88D0/func_150BB4CC.s")

s32 func_150BB740(u8 *arg0, s32 arg1) {
    s32 i;
    f32 *p = (f32 *)(arg0 + 0xA8);
    for (i = D_800BE9E4; i != 0; i--) {
        *(f32 *)(arg0 + 0x58) *= *p;
        *(f32 *)(arg0 + 0x60) *= *p;
    }
    return 1;
}

void func_150BB8E8(struct_eu_E88D0 *arg0) {
    arg0->unk18 |= 1;
    arg0->unk1C = 50;
    arg0->unkB0 = arg0->unk1C;
    arg0->unkB2 = 5;
    func_1513F6C0(arg0, 6, arg0->unk81);
}

s32 func_150BB930(struct_eu_E88D0 *arg0) {
    if (arg0->unk1C < arg0->unkB0) {
        s16 temp_lo = arg0->unk1C * arg0->unkB2;
        if (temp_lo < arg0->unk28) {
            arg0->unk28 = temp_lo;
        }
    }
    return 1;
}

s32 func_150BB978(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, s32 argD, u8 argE) {
    s16 spBE;
    f32 spB8;
    f32 spB4;
    f32 spB0;
    f32 spAC;
    struct {
        f32 u28[13];
        f32 u5C;
        f32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        s32 u78;
        s16 u7C;
        s16 u7E;
        s8 u80;
        u8 pad81[0x3];
        s32 u84;
        u8 u88;
        s8 u89;
        s8 u8A;
        s8 u8B;
        s8 u8C;
        s8 u8D;
        s8 u8E;
        s8 u8F;
        s8 u90;
        u8 pad91[0x1];
        s8 u92;
        u8 pad93[0x1];
        s32 u94;
        s8 u98;
        u8 pad99[0x1];
        s16 u9A;
        s16 u9C;
        u8 padA0[0x8];
    } sp;
    f32 temp_f2;

    spB8 = func_151423D8(arg8 - 0x40);
    spB4 = func_151423D8(arg8);
    sp.u28[4] = 0.0f;
    sp.u28[5] = 0.0f;
    sp.u28[6] = 0.0f;
    sp.u28[7] = 1.0f;
    sp.u28[8] = 1.0f;
    sp.u28[9] = 1.0f;
    sp.u78 = 0x9E8;
    sp.u28[10] = arg2;
    sp.u28[11] = arg3;
    sp.u28[12] = arg4;
    sp.u28[1] = 0.2f;
    spBE = (func_150ADA20() % 13U) - 0x34;
    spB0 = func_151423D8(spBE - 0x40);
    spAC = func_151423D8(spBE);
    temp_f2 = (func_150ADA68() * 9.0f) + 3.0f;
    sp.u5C = temp_f2 * spAC * spB8;
    sp.u60 = -temp_f2 * spB0;
    sp.u64 = temp_f2 * spAC * spB4;
    sp.u68 = (func_150ADA68() * 50.0f) + -25.0f;
    sp.u6C = 0.0f;
    sp.u70 = (func_150ADA68() * 50.0f) + -25.0f;
    sp.u7C = (func_150ADA20() % 68U) + 0x26;
    sp.u74 = (func_150ADA68() * -0.1f) + -0.3f;
    sp.u28[0] = 1.0f;
    sp.u28[3] = (func_150ADA68() * 18.800001f) + 5.6f;
    sp.u28[2] = sp.u28[3];
    sp.u7E = 0x1F;
    sp.u80 = 0;
    sp.u84 = 0;
    sp.u88 = 0xFF;
    sp.u89 = 1;
    sp.u8A = 0;
    sp.u8B = 0;
    sp.u8C = 0;
    sp.u8D = 0;
    sp.u8E = 0;
    sp.u8F = 0;
    sp.u90 = 0;
    sp.u92 = 0;
    sp.u94 = 0;
    sp.u98 = 0;
    sp.u9A = 1;
    sp.u9C = 0xFF;
    func_15132FBC(&sp, 3, 0xFF, 0, argE, 0);
    return 1;
}
