#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_188D10/func_1515B500.s")

#ifdef NON_MATCHING
s32 memcpy(s32, f32 *, s32);

void func_1515B78C(u8 *arg0) {
    struct {
        f32 u6C;
        s8 u70;
        s8 u71;
        s8 u72;
        s8 u73;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        s8 u84;
        s8 u85;
        s8 u86;
        s8 u87;
        f32 u88;
        f32 u8C;
        f32 u90;
        s32 u94;
        s32 u98;
        s16 u9C;
        s16 u9E;
        s32 uA0;
        s32 uA4;
        s8 uA8;
        s8 uA9;
        s8 uAA;
        s8 uAB;
        s8 uAC;
        s8 uAD;
        s8 uAE;
        s8 uAF;
        s8 uB0;
        s8 uB1;
        s16 uB2;
        s16 uB4;
        s16 uB6;
        f32 uB8;
        f32 uBC;
        f32 uC0;
        s32 uC4;
        u8 padC8[0x8];
        f32 uD0;
        f32 uD4;
        f32 uD8;
        f32 uDC;
        f32 uE0;
        f32 uE4;
        f32 uE8;
        s32 uEC;
        u8 padF0[0x4];
        s8 uF4;
        s8 uF5;
        s8 uF6;
        s8 uF7;
    } sp;
    f32 temp_f2;
    s32 temp_v0;
    u8 *temp_s0;

    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x38)) + ((*(f32 *)((u8 *)arg0 + 0x34)) * D_800BE9A4));
    temp_s0 = arg0 + 0x28;
    if ((*(f32 *)((u8 *)arg0 + 0x38)) > 1.0f) {
        sp.uB1 = 0x2F;
        sp.u9C = 0xC01;
        sp.u94 = 0x200005;
        sp.u98 = 0;
        sp.uAE = 0;
        sp.uAD = 0;
        sp.uAC = 0;
        sp.uAB = 0;
        sp.uAA = 0;
        sp.uA9 = 0;
        sp.uA8 = 0;
        sp.uA4 = 0;
        sp.uA0 = 0;
        sp.uB0 = 0xFF;
        sp.uB6 = 0;
        sp.uB8 = 0.0f;
        sp.uEC = 0x3207;
        sp.uF4 = 5;
        sp.uF5 = 5;
        sp.uF6 = 4;
        sp.uF7 = -1;
        (*(s32 *)((u8 *)(&sp.uC4) + 0)) = (s32) (*(s32 *)((u8 *)temp_s0 + 0));
        (*(s32 *)((u8 *)(&sp.uC4) + 4)) = (s32) (*(s32 *)((u8 *)temp_s0 + 4));
        (*(s32 *)((u8 *)(&sp.uC4) + 8)) = (s32) (*(s32 *)((u8 *)temp_s0 + 8));
        sp.uD0 = 0.0f;
        sp.uD4 = 0.0f;
        sp.uD8 = 0.0f;
        sp.uB2 = 0x32;
        sp.uB4 = 5;
        sp.u70 = 0;
        sp.u71 = 0;
        sp.u84 = 0;
        sp.u85 = 0;
        sp.uDC = 0.0f;
        sp.uE4 = 0.0f;
        sp.u7C = 1.2f;
        sp.u80 = 0.8333333f;
        sp.u90 = (*(f32 *)((u8 *)temp_s0 + 0x14));
        if (func_150ADA20() & 1) {
            sp.uEC |= 0x40;
        }
        if (func_150ADA20() & 1) {
            sp.uEC |= 0x80;
        }
        do {
            sp.uE0 = func_150ADA68() * 12.0f * 0.1f;
            sp.u9E = (func_150ADA20() % 152U) + 0x96;
            sp.uAF = (func_150ADA20() % 151U) + 0x37;
            temp_f2 = (func_150ADA68() * 200.0f) + 100.0f;
            sp.uBC = temp_f2;
            sp.u6C = temp_f2;
            sp.uC0 = temp_f2;
            sp.u72 = (func_150ADA20() % 5U) + 4;
            sp.u73 = (func_150ADA20() % 5U) + 4;
            sp.u74 = ((func_150ADA68() * 0.25f) + 0.15f) * sp.u6C;
            sp.u78 = ((func_150ADA68() * 0.25f) + 0.15f) * sp.u6C;
            sp.u86 = (func_150ADA20() & 3) + 2;
            sp.u87 = (func_150ADA20() & 3) + 2;
            sp.u88 = ((func_150ADA68() * 0.07f) + 0.06f) * sp.u6C;
            sp.u8C = ((func_150ADA68() * 0.07f) + 0.06f) * sp.u6C;
            sp.uE8 = ((func_150ADA68() * 1005.0f) + 600.0f) * 0.001f;
            temp_v0 = func_1513092C(&sp.u94, 2, 0x28);
            if (temp_v0 != 0) {
                memcpy(temp_v0 + 0xA8, &sp.u6C, 0x28);
            }
            (*(f32 *)((u8 *)temp_s0 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0x10)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s0 + 0x10)) > 1.0f);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_188D10/func_1515B78C.s")
#endif
void func_1515BB64(s16 arg0) {
    s16 sp1C[2];

    sp1C[0] = arg0;
    func_15155C9C((f32 *)sp1C, 0xB);
}

void func_1515BB9C(u8 *arg0, s16 *arg1, u8 arg2) {
    if (arg2 == 0xB) {
        if (*(s16 *)(arg0 + 0x70) == *arg1) {
            func_1516972C((struct102 *)arg0);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_188D10/func_1515BBE4.s")

#ifdef NON_MATCHING
s32 func_1515BF04(u8 *arg0) {
    f32 temp_f14;
    f32 temp_f2;

    temp_f2 = (*(f32 *)((u8 *)arg0 + 0x78));
    temp_f14 = (*(f32 *)((u8 *)arg0 + 0x74));
    (*(f32 *)((u8 *)arg0 + 0x14)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x14)) + ((temp_f2 * D_800BE9A4) + (0.5f * temp_f14 * D_800BE9A4)));
    (*(f32 *)((u8 *)arg0 + 0x78)) = (f32) (temp_f2 + (temp_f14 * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x1C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x7C)) + ((*(f32 *)((u8 *)arg0 + 0x80)) * ((*(f32 *)((u8 *)arg0 + 0x78)) + temp_f2) * 0.5f));
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_188D10/func_1515BF04.s")
#endif
void func_1515BF80(s32 arg0) {
}

void func_1515BF8C(s16 arg0) {
    func_1515B500(arg0);
}

void func_1515BFB8(s32 arg0) {
}

void func_1515BFC4(s16 arg0) {
    func_1515BBE4(arg0);
}

void func_1515BFF0(s16 arg0) {
    func_1515BB64(arg0);
}

void func_1515C01C(s16 arg0) {
    func_1515BB64(arg0);
}
