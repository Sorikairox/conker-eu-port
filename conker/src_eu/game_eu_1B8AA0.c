#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 func_1518B290(u8 *arg0) {
    struct {
        f32 uA4;
        f32 uA8;
        f32 uAC;
        u8 padB0[0xA];
        s16 uBA;
        s16 uBC;
        s16 uBE;
        s16 uC0;
        s16 uC2;
        s16 uC4;
        s16 uC6;
        s16 uC8;
        s16 uCA;
        s32 uCC;
        s32 uD0;
        s8 uD4;
        s8 uD5;
        u8 padD6[0x2];
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
        f32 u11C;
        f32 u120;
        f32 u124;
        s32 u128;
        s16 u12C;
        u16 u12E;
        s8 u130;
        u8 pad131[0x3];
        s32 u134;
        s8 u138;
        s8 u139;
        s8 u13A;
        s8 u13B;
        s8 u13C;
        s8 u13D;
        s8 u13E;
        s8 u13F;
        s8 u140;
        u8 pad141[0x1];
        s8 u142;
        u8 pad143[0x1];
        s32 u144;
        s8 u148;
        u8 pad149[0x1];
        s16 u14A;
        s16 u14C;
    } sp;
    f32 *temp_s4;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f28;
    f32 temp_f2;
    f32 temp_f4;
    s16 temp_v1;
    s16 var_s2;
    s32 temp_f10;
    s32 temp_f16;
    s32 temp_f8;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s1;
    s32 var_s1;
    u16 temp_v0_2;
    u8 *temp_v0;

    temp_s4 = arg0 + 0x170;
    if ((*(f32 *)((u8 *)arg0 + 0x3C)) < (*(f32 *)((u8 *)arg0 + 0x170))) {
        sp.u12C = 0x32;
        sp.uF4 = 1.0f;
        sp.uF8 = 1.0f;
        sp.uFC = 1.0f;
        sp.u128 = 0x9E8;
        sp.u12E = (*(u16 *)((u8 *)arg0 + 0x66));
        sp.uDC = 0.4f;
        sp.u120 = 0.0f;
        sp.u124 = -1.3f;
        sp.u100 = (*(f32 *)((u8 *)arg0 + 0x38));
        sp.u104 = *temp_s4;
        sp.u130 = 0;
        sp.u134 = 0;
        sp.u138 = 0xFF;
        sp.u139 = 1;
        sp.u13B = 0;
        sp.u13C = 0;
        sp.u13D = 0;
        sp.u13E = 0;
        sp.u13F = 0;
        sp.u140 = 0;
        sp.u142 = 2;
        sp.u144 = 0;
        sp.u148 = 0;
        sp.u14A = 1;
        sp.u14C = 0xFF;
        sp.u108 = (*(f32 *)((u8 *)arg0 + 0x40));
        temp_v1 = (func_150ADA20() & 3) + 4;
        var_s2 = temp_v1;
        if (temp_v1 > 0) {
            do {
                temp_f22 = (func_150ADA68() * ((*(f32 *)((u8 *)arg0 + 0x10)) * 0.5f)) + 0.05f;
                temp_s0 = func_150ADA20() & 0xFF;
                temp_s1 = (-0x20 - (func_150ADA20() & 0x1F)) & 0xFF;
                temp_f20 = (func_150ADA68() * 10.0f) + 5.0f;
                temp_f24 = func_151423D8((temp_s0 - 0x40) & 0xFF);
                temp_f26 = func_151423D8(temp_s0 & 0xFF);
                temp_f28 = func_151423D8((temp_s1 - 0x40) & 0xFF);
                temp_f2 = temp_f20 * func_151423D8(temp_s1 & 0xFF);
                sp.uD8 = temp_f22;
                sp.uE0 = temp_f22;
                sp.uE4 = temp_f22;
                sp.u10C = temp_f2 * temp_f24;
                sp.u110 = -temp_f20 * temp_f28;
                sp.u114 = temp_f2 * temp_f26;
                sp.uE8 = func_150ADA68() * 360.0f;
                sp.uEC = func_150ADA68() * 360.0f;
                sp.uF0 = func_150ADA68() * 360.0f;
                sp.u118 = 25.0f - (func_150ADA68() * 50.0f);
                sp.u11C = 25.0f - (func_150ADA68() * 50.0f);
                if (temp_f22 > 0.25f) {
                    sp.u13A = 2;
                } else {
                    sp.u13A = 4;
                }
                temp_v0 = func_15132FBC(&sp.uD8, 3, 0xFF, 4, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
                if (temp_v0 != NULL) {
                    (*(f32 *)((u8 *)temp_v0 + 0x170)) = (f32) *temp_s4;
                }
                var_s2 -= 1;
            } while (var_s2 > 0);
        }
        temp_v0_2 = (*(u16 *)((u8 *)arg0 + 0x66));
        if (temp_v0_2 != 4) {
            var_s1 = 0;
            if (temp_v0_2 != 5) {
                var_s1 = 0;
            }
        } else {
            var_s1 = 1;
        }
        sp.uA4 = (*(f32 *)((u8 *)arg0 + 0x38));
        sp.uA8 = *temp_s4;
        sp.uAC = (*(f32 *)((u8 *)arg0 + 0x40));
        temp_f16 = (s32) ((*(f32 *)((u8 *)arg0 + 0x10)) * 200.0f);
        sp.uBA = (s16) temp_f16;
        sp.uBC = (s16) temp_f16;
        temp_f4 = func_150ADA68() * 10.0f;
        sp.uC2 = 0;
        sp.uC4 = 0;
        temp_f10 = (s32) ((temp_f4 + 20.0f) * (*(f32 *)((u8 *)arg0 + 0x10)));
        sp.uBE = (s16) temp_f10;
        sp.uC0 = (s16) temp_f10;
        temp_s0_2 = var_s1 & 0xFF;
        sp.uC6 = (func_150ADA20() % 201U) + 0x12C;
        sp.uC8 = 0;
        sp.uCA = 0x258;
        func_151429E0(temp_s0_2 & 0xFF, &sp.uCC, &(*(s32 *)((u8 *)&sp + 0x29)), &(*(s32 *)((u8 *)&sp + 0x2A)));
        func_151429E0(temp_s0_2 & 0xFF, &(*(s32 *)((u8 *)&sp + 0x2B)), &sp.uD0, &(*(s32 *)((u8 *)&sp + 0x2D)));
        (*(s8 *)((u8 *)&sp + 0x2E)) = 0xFF;
        temp_f8 = (s32) ((*(f32 *)((u8 *)arg0 + 0x10)) * 511.0f);
        if ((f32) temp_f8 > 255.0f) {
            (*(s8 *)((u8 *)&sp + 0x2F)) = 0xFF;
        } else {
            (*(s8 *)((u8 *)&sp + 0x2F)) = (s8) temp_f8;
        }
        sp.uD4 = 0xA;
        sp.uD5 = 0;
        func_1518CFF0(&sp.uA4, 1);
        return 0;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B8AA0/func_1518B290.s")
#endif
s32 func_1518B71C(f32 *arg0) {
    if (arg0[0x3C / 4] < arg0[0x170 / 4]) {
        return 0;
    }
    return 1;
}

s32 func_1518B748(u8 *arg0) {
    f32 d;
    s32 a;
    s32 b;
    s32 c;

    d = *(f32 *)(arg0 + 0x3C) - *(f32 *)(arg0 + 0x170);
    if (d < 0.0f) {
        return 0;
    }
    b = *(s16 *)(arg0 + 0x64) * 4;
    if (b >= 0x100) {
        b = 0xFF;
    }
    c = (s32)d >> 1;
    if (c >= 0x100) {
        c = 0xFF;
    }
    a = (c < b) ? c : b;
    if (a < 0) {
        return 0;
    }
    arg0[0x70] = a;
    return 1;
}

void func_1518B7D4(s32 arg0, f32 arg1, f32 arg2, s32 arg3, u8 arg4) {
    func_1518B818(arg0, arg1, arg2, arg3, 4, 0xFF, arg4);
}

#ifdef NON_MATCHING
s32 func_15046F70(void *, u16, f32, void *); /* P95 */
void func_1518B818(s32 arg0, f32 arg1, f32 arg2, s32 arg3, u16 arg4, s32 arg5, u8 arg6) {
    struct {
        f32 u90;
        u8 pad94[0x14];
        s32 uA8;
        s8 uAC;
        s8 uAD;
        u8 padAE[0x2];
        s32 uB0;
        f32 uB4;
        f32 uB8;
        f32 uBC;
        f32 uC0;
        f32 uC4;
        f32 uC8;
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
        s32 u104;
        s16 u108;
        u16 u10A;
        s8 u10C;
        u8 pad10D[0x3];
        s32 u110;
        s8 u114;
        s8 u115;
        s8 u116;
        s8 u117;
        s8 u118;
        s8 u119;
        s8 u11A;
        s8 u11B;
        s8 u11C;
        u8 pad11D[0x1];
        s8 u11E;
        u8 pad11F[0x1];
        s32 u120;
        s8 u124;
        u8 pad125[0x1];
        s16 u126;
        s16 u128;
    } sp;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f2;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 var_s1;
    s32 var_s5;
    u8 *temp_v0;
    u8 *temp_v0_2;

    var_s5 = arg3;
    if (arg0 != 0) {
        sp.uA8 = 0;
        sp.uAC = 0;
        sp.uAD = 0;
        sp.uB0 = 0;
        sp.u108 = 0x12C;
        sp.u104 = 0x9E8;
        sp.u10C = 0;
        sp.u110 = 0;
        sp.u114 = 0xFF;
        sp.u115 = 1;
        sp.u117 = 0;
        sp.u118 = 0;
        sp.u119 = 0;
        sp.u11A = 0;
        sp.u11B = 0;
        sp.u11C = 0;
        sp.u11E = 2;
        sp.u120 = 0;
        sp.u124 = 0;
        sp.u126 = 1;
        sp.u128 = 0xFF;
        sp.uD0 = 1.0f;
        sp.uD4 = 1.0f;
        sp.uD8 = 1.0f;
        sp.u90 = 99999.9f;
        sp.uFC = 0.0f;
        sp.uE8 = 0.0f;
        sp.uEC = 0.0f;
        sp.uF0 = 0.0f;
        sp.uB8 = 0.4f;
        sp.u10A = arg4;
        sp.u100 = -1.3f;
        if (var_s5 > 0) {
            do {
                temp_s0 = func_150ADA20() & 0xFF;
                temp_f0 = func_150ADA68();
                sp.uBC = arg2;
                temp_f20 = temp_f0 * arg1;
                sp.uC0 = arg2;
                sp.uB4 = arg2;
                sp.uC4 = func_150ADA68() * 360.0f;
                sp.uC8 = func_150ADA68() * 360.0f;
                sp.uCC = func_150ADA68() * 360.0f;
                sp.uDC = (func_151423D8(temp_s0 & 0xFF) * temp_f20) + (*(f32 *)((u8 *)arg0 + 0));
                sp.uE0 = ((*(f32 *)((u8 *)arg0 + 4)) + arg1) - (2.0f * func_150ADA68() * arg1);
                sp.uE4 = (*(f32 *)((u8 *)arg0 + 8)) - (func_151423D8((temp_s0 - 0x40) & 0xFF) * temp_f20);
                sp.uF4 = 25.0f - (func_150ADA68() * 50.0f);
                sp.uF8 = 25.0f - (func_150ADA68() * 50.0f);
                if (func_15046F70(&sp.uDC, 0, -10000.0f, &sp.u90) != 0) { /* P95: was 0xC61C4000 as an int */
                    sp.u116 = 2;
                    temp_v0 = func_15132FBC(&sp.uB4, 3, 0xFF, 4, (s32) arg6, 0);
                    if (temp_v0 != NULL) {
                        (*(f32 *)((u8 *)temp_v0 + 0x170)) = sp.u90;
                    }
                    var_s1 = (func_150ADA20() & 3) + 1;
                    if (var_s1 > 0) {
                        do {
                            temp_s0_2 = func_150ADA20() & 0xFF;
                            temp_f20_2 = func_150ADA68() * arg2 * 16.0f;
                            temp_f2 = (func_150ADA68() * 0.3f) + 0.1f;
                            sp.uC0 = temp_f2;
                            sp.uBC = temp_f2;
                            sp.uB4 = temp_f2;
                            sp.uC4 = func_150ADA68() * 360.0f;
                            sp.uC8 = func_150ADA68() * 360.0f;
                            sp.uCC = func_150ADA68() * 360.0f;
                            sp.uDC += func_151423D8(temp_s0_2 & 0xFF) * temp_f20_2;
                            sp.uE0 = (func_150ADA68() * 25.0f) + ((arg2 * 16.0f) + sp.uE0);
                            sp.uE4 -= func_151423D8((temp_s0_2 - 0x40) & 0xFF) * temp_f20_2;
                            sp.uF4 = 25.0f - (func_150ADA68() * 50.0f);
                            temp_f0_2 = func_150ADA68();
                            sp.u116 = 3;
                            sp.uF8 = 25.0f - (temp_f0_2 * 50.0f);
                            temp_v0_2 = func_15132FBC(&sp.uB4, 3, 0xFF, 4, (s32) arg6, 0);
                            var_s1 -= 1;
                            if (temp_v0_2 != NULL) {
                                (*(f32 *)((u8 *)temp_v0_2 + 0x170)) = sp.u90;
                            }
                        } while (var_s1 != 0);
                    }
                }
                var_s5 -= 1;
            } while (var_s5 > 0);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B8AA0/func_1518B818.s")
#endif