#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F3040/func_151C5280.s")

s32 func_151030B8(s32, s32, f32 *, f32 *, f32 *, s32, s32, f32, s32, s32, s32, s32, s32, s32);
extern f32 D_800AAE70[];
extern f32 D_800AAE7C[];

void func_151C5B38(s32 arg0, s32 arg1, s16 arg2, u8 arg3, s32 arg4) {
    f32 s[2];

    s[1] = ((func_150ADA68() * 1001.0f) + 604.0f) * 0.01f;
    s[0] = ((func_150ADA68() * 59.0f) + 141.0f) * 0.1f;
    func_151030B8(arg0, 0, D_800AAE70, D_800AAE7C, s, (func_150ADA20() & 3) + 6, (func_150ADA20() % 1U) + 0xFF /* fakematch: rand % 1 range-0 rand (folded, call + spill kept) */, (func_150ADA68() * 270.0f) + 359.0f, arg1, 0xFF, 0, arg2, arg3, arg4);
}

void func_151C5C54(u8 *arg0, u8 arg1, s32 arg2) {
    s8 sp48[8];
    s32 sp3C[3];

    sp48[0] = 3;
    sp48[1] = -1;
    *(s16 *)(sp48 + 2) = (func_150ADA20() % 3U) + 3;
    sp48[4] = 0;
    sp3C[0] = *(f32 *)(arg0 + 0);
    sp3C[1] = *(f32 *)(arg0 + 4);
    sp3C[2] = *(f32 *)(arg0 + 8);
    func_151602C0(sp48, sp3C, (func_150ADA20() & 1) + 6, 0xFF, 0xE8, 0xAB, 0xFFU, 0U, 0, arg1, arg2);
}

#ifdef NON_MATCHING
s32 func_151307F0(s32 *, s32, s32, s32, s32, s32);
s32 func_15137C64(s32 *, s32 *, f32 *, f32 *, f32 *, s32, s32, s32);
void func_15143794(s16, s16, f32, void *);
void func_15143874(s16, f32, f32 *, f32 *);
s32 func_151DA6F8(s32 *, f32 *, f32, s16, s32, f32, s32, s32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_151DC034(s32 *, f32, s32, s16, s32, s32, s32);
s32 memcpy(s32, f32 *, s32);

void func_151C5D2C(s32 arg0, s32 arg1, s32 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s32 arg7) {
    struct {
        f32 uB8;
        s32 uBC;
        s32 uC0;
        s16 uC4;
        s16 uC6;
        s32 uC8;
        s32 uCC;
        s8 uD0;
        s8 uD1;
        s8 uD2;
        s8 uD3;
        s8 uD4;
        s8 uD5;
        s8 uD6;
        s8 uD7;
        s8 uD8;
        s8 uD9;
        s16 uDA;
        s16 uDC;
        s16 uDE;
        f32 uE0;
        f32 uE4;
        f32 uE8;
        s32 uEC;
        u8 padF0[0x8];
        f32 uF8;
        f32 uFC;
        f32 u100;
        s32 u104;
        u8 pad108[0x8];
        f32 u110;
        s32 u114;
        u8 pad118[0x4];
        s8 u11C;
        s8 u11D;
        s8 u11E;
        s8 u11F;
        s8 u120;
        s8 u121;
        u8 pad122[0xE];
        f32 u130;
        f32 u134;
        f32 u138;
        u8 pad13C[0x8];
        f32 u144;
        f32 u148;
        f32 u14C;
        f32 u150;
        f32 u154;
        u8 pad158[0x4];
        f32 u15C;
        f32 u160;
        f32 u164;
        f32 u168;
        f32 u16C;
        f32 u170;
        f32 u174;
        f32 u178;
        f32 u17C;
        s32 u180;
        u8 pad184[0x8];
        s32 u18C;
    } sp;
    f32 temp_f16;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f20_3;
    f32 temp_f22;
    f32 temp_f22_2;
    f32 temp_f2;
    f32 temp_f2_2;
    s16 temp_v1;
    s16 var_s2;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s0_3;
    s32 temp_s1;
    s32 temp_s1_2;
    s32 temp_s1_3;
    s32 temp_s1_4;
    s32 temp_v0;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2_2;
    s32 var_s2_3;
    u32 temp_hi;

    if (func_15137C64(&sp.u18C, &sp.u180, &sp.u174, &sp.u168, &sp.u15C, arg0, arg1, arg2) != 0) {
        temp_f22 = func_150ADA68();
        temp_s1 = func_150ADA20();
        func_151DC034(&sp.u18C, (temp_f22 * 24.0f) + 168.0f, (((u32) temp_s1 % 101U) + 0x9B) & 0xFF, (s16) ((func_150ADA20() & 7) + 0xF), 1, (s32) arg6, arg7);
        if (arg4 != 0) {
            temp_v1 = (func_150ADA20() % 3U) + 5;
            var_s2 = temp_v1;
            if (temp_v1 != 0) {
                do {
                    temp_f20 = ((func_150ADA68() * 33.0f) + 60.0f) * 0.1f;
                    func_15143874((s16) (func_150ADA20() & 0xFF), temp_f20, &sp.u150, &sp.u154);
                    sp.u144 = (sp.u168 * sp.u150) + (sp.u15C * sp.u154);
                    sp.u148 = (sp.u16C * sp.u150) + (sp.u160 * sp.u154);
                    sp.u14C = (sp.u170 * sp.u150) + (sp.u164 * sp.u154);
                    temp_f20_2 = func_150ADA68();
                    temp_s0 = func_150ADA20();
                    temp_s1_2 = func_150ADA20();
                    temp_f22_2 = func_150ADA68();
                    func_150ADA20();
                    func_151DA6F8(&sp.u18C, &sp.u144, (temp_f20_2 * 0.162f) + 0.193f, (s16) (((u32) temp_s0 % 9U) + 0x12), ((u32) temp_s1_2 % 156U) + 0x64, (temp_f22_2 * 4.0f) + 4.0f, 3, 0, 1.0f, 1.0f, 1, 1, 0, 0x10, 0xF, 0, (s32) arg6, arg7);
                    var_s2 -= 1;
                } while (var_s2 != 0);
            }
        }
        if (arg3 != 0) {
            var_s2_2 = (func_150ADA20() % 6U) + 5;
            if (var_s2_2 != 0) {
                do {
                    temp_f2 = ((func_150ADA68() * 150.0f) + 200.0f) * 0.1f;
                    sp.u130 = sp.u174 * temp_f2;
                    sp.u134 = sp.u178 * temp_f2;
                    sp.u138 = sp.u17C * temp_f2;
                    temp_f20_3 = func_150ADA68();
                    temp_s1_3 = func_150ADA20();
                    temp_s0_2 = func_150ADA20();
                    func_151D9014(&sp.u180, &sp.u130, 1U, (temp_f20_3 * 0.68200004f) + -0.41200003f, (s16) (((u32) temp_s1_3 % 11U) + 5), (u8) (((u32) temp_s0_2 % 156U) + 0x64), (func_150ADA68() * 60.0f) + 80.0f, 0U, 1.0f, 1.0f, 1U, 0, 1U, 0U, (u8) (s32) arg6, arg7);
                    var_s2_2 -= 1;
                } while (var_s2_2 != 0);
            }
        }
        if (arg5 != 0) {
            temp_hi = func_150ADA20() % 7U;
            sp.uD9 = 0x6C;
            sp.uC4 = 0x5103;
            sp.uBC = 0x200005;
            sp.uDA = 0x14;
            sp.uDC = 0xC;
            sp.u114 = 0x80D207;
            sp.u11C = 8;
            sp.u11D = 6;
            sp.u11E = 0x10;
            sp.u120 = -1;
            sp.uC0 = 0;
            sp.uC8 = 0;
            sp.uCC = 0;
            sp.u11F = -1;
            sp.u121 = 0;
            sp.uDE = 1;
            sp.uE0 = 1.0f;
            sp.uD0 = 0xE2;
            sp.uD1 = 0xB2;
            sp.uD2 = 0x60;
            sp.uD3 = 0xFF;
            sp.uD4 = 0x39;
            sp.uD5 = 0xF;
            sp.uD6 = 0;
            sp.uD8 = 0xFF;
            sp.uB8 = 0.950865f;
            (*(s32 *)((u8 *)(&sp.uEC) + 0)) = (s32) (*(s32 *)((u8 *)(&sp.u180) + 0));
            var_s2_3 = temp_hi + 3;
            (*(s32 *)((u8 *)(&sp.uEC) + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u180) + 4));
            (*(s32 *)((u8 *)(&sp.uEC) + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u180) + 8));
            sp.uF8 = 0.0f;
            sp.uFC = 0.0f;
            sp.u100 = 0.0f;
            if (var_s2_3 > 0) {
                do {
                    temp_s1_4 = func_150ADA20();
                    temp_s0_3 = func_150ADA20();
                    func_15143794((s16) (temp_s1_4 & 0xFF), (s16) ((temp_s0_3 & 0x3F) * -1), (func_150ADA68() * 7.0f) + 2.0f, &sp.u104);
                    temp_f16 = func_150ADA68() * 117.0f;
                    sp.u114 &= ~0xC0;
                    sp.u110 = (temp_f16 + -197.0f) * 0.001f;
                    var_s1 = 0;
                    if (func_150ADA20() & 1) {
                        var_s1 = 0x80;
                    }
                    if (func_150ADA20() & 1) {
                        var_s0 = 0x40;
                    } else {
                        var_s0 = 0;
                    }
                    sp.u114 |= var_s0 | var_s1;
                    sp.uD7 = (func_150ADA20() % 66U) + 0xBE;
                    sp.uC6 = (func_150ADA20() % 45U) + 0x2C;
                    temp_f2_2 = (func_150ADA68() * 122.0f) + 77.0f;
                    sp.uE4 = temp_f2_2;
                    sp.uE8 = temp_f2_2;
                    temp_v0 = func_151307F0(&sp.uBC, 1, 0, 4, (s32) arg6, arg7);
                    if (temp_v0 != 0) {
                        memcpy(temp_v0 + 0xA8, &sp.uB8, 4);
                    }
                    var_s2_3 -= 1;
                } while (var_s2_3 != 0);
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F3040/func_151C5D2C.s")
#endif
void func_15137F30(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 arg4, u8 *arg5, f32 *arg6, f32 *arg7, f32 *arg8, f32 *arg9, s16 *argA, u8 *argB, f32 *argC);
void func_151C6424(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 arg4, u8 *arg5) {
    f32 sp6C[3];
    f32 sp60[3];
    f32 sp54[3];
    f32 sp50;
    s16 sp4E;
    u8 sp4D;
    f32 sp48;

    func_15137F30(arg0, arg1, arg2, arg3, arg4, arg5, sp6C, sp60, sp54, &sp50, &sp4E, &sp4D, &sp48);
    func_151D9014(sp6C, sp54, 1, sp50, sp4E, sp4D, sp48, 0, 1.0f, 1.0f, 1, 0, 1, 0, arg5[0xC], arg5[1]);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F3040/func_151C64F4.s")

typedef struct {
    s16 n0; s16 n1; s32 p; s16 c; s16 a; s16 d; s16 e;
    f32 f0; f32 f1; f32 f2; f32 f3; f32 f4;
    u8 b0; u8 b1; s16 h0; s16 h1; s16 pad;
    f32 g0; f32 g1; f32 g2; s32 q;
} SpawnC6750;
void func_15154BF4(SpawnC6750 *, u8, s32);
void func_151C6750(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    SpawnC6750 s;

    s.f0 = 5.0f;
    s.n0 = 10;
    s.f1 = 7.0f;
    s.n1 = 4;
    s.p = arg0;
    s.c = 0;
    s.d = 255;
    s.a = -24;
    s.e = 25;
    s.b0 = 0xBE;
    s.b1 = 0x41;
    s.h0 = 0xC8;
    s.h1 = 0x96;
    s.f2 = -0.208f;
    s.f3 = 0.085f;
    s.f4 = 0.970632f;
    s.g0 = 96.0f;
    s.g1 = 109.0f;
    s.g2 = 1.0f;
    s.q = arg1;
    func_15154BF4(&s, arg2, arg3);
}

s32 func_151C6840(u8 *arg0, s32 arg1, s32 arg2) {
    switch (arg0[4]) {
        case 0x5A:
        case 0x74:
        case 0x7A:
            return 0;
        default:
            return 1;
    }
}
