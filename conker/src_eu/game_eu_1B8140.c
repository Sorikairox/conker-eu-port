#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 func_15158620(u8 *, s32, s32, s32, s32, s32, s32);
s32 memcpy(s32, s16 *, s32);
extern s32 D_8008D950;
extern s32 D_8008D958;

s32 func_1518A930(u8 *arg0, u8 *arg1, f32 arg2, u8 *arg3, u8 *arg4, f32 arg5, f32 arg6, u8 arg7, s16 arg8, u8 arg9, s32 argA, u8 argB, s32 argC) {
    struct {
        s16 u30;
        u8 pad32[0x2];
        s32 u34;
        s16 u38;
        u8 pad3A[0xA];
        f32 u44;
        s32 u48;
        u8 pad4C[0x8];
        s32 u54;
        u8 pad58[0x8];
        f32 u60;
        f32 u64;
        u8 u68;
        s8 u69;
        s8 u6A;
        s8 u6B;
        s16 u6C;
        s8 u6E;
        u8 pad6F[0x1];
        s32 u70;
        s32 u74;
        s32 u78;
        s32 u7C;
        s32 u80;
        s32 u84;
        s32 u88;
        s8 u8C;
        s8 u8D;
        u8 pad8E[0x2];
        s8 u90;
        s8 u91;
        s8 u92;
        s8 u93;
        s8 u94;
        s8 u95;
        s8 u96;
        s8 u97;
        s32 u98;
        s8 u9C;
        s8 u9D;
        u8 pad9E[0x2];
        s32 uA0;
        u8 padA4[0x8];
        s32 uAC;
    } sp;
    s32 temp_v0;

    (*(s32 *)((u8 *)(&sp.u38) + 0)) = (s32) (*(s32 *)((u8 *)arg1 + 0));
    (*(s32 *)((u8 *)(&sp.u38) + 4)) = (s32) (*(s32 *)((u8 *)arg1 + 4));
    (*(s32 *)((u8 *)(&sp.u38) + 8)) = (s32) (*(s32 *)((u8 *)arg1 + 8));
    (*(s32 *)((u8 *)(&sp.u48) + 0)) = (s32) (*(s32 *)((u8 *)arg3 + 0));
    (*(s32 *)((u8 *)(&sp.u48) + 4)) = (s32) (*(s32 *)((u8 *)arg3 + 4));
    (*(s32 *)((u8 *)(&sp.u48) + 8)) = (s32) (*(s32 *)((u8 *)arg3 + 8));
    (*(s32 *)((u8 *)(&sp.u54) + 0)) = (s32) (*(s32 *)((u8 *)arg4 + 0));
    (*(s32 *)((u8 *)(&sp.u54) + 4)) = (s32) (*(s32 *)((u8 *)arg4 + 4));
    (*(s32 *)((u8 *)(&sp.u54) + 8)) = (s32) (*(s32 *)((u8 *)arg4 + 8));
    sp.u44 = arg2;
    sp.u6A = 1;
    sp.u6B = 1;
    sp.u60 = arg5;
    sp.u64 = arg6;
    sp.u68 = arg7;
    sp.u6C = arg8;
    if (arg9 != 0) {
        sp.u6E = (s8) *(&D_8008D958 + ((func_150ADA20() & 1) * 4));
    } else {
        sp.u6E = (s8) *(&D_8008D950 + ((func_150ADA20() & 1) * 4));
    }
    sp.u90 = 0xFF;
    sp.u74 = 0x220205;
    sp.u78 = 0x40600;
    sp.u8D = 7;
    sp.u7C = 1;
    sp.u80 = 0x4A;
    sp.u84 = 0x80;
    sp.u88 = 0x20;
    sp.u70 = 0;
    sp.u8C = 0;
    sp.u69 = 1;
    sp.u91 = 0xFF;
    sp.u92 = 0xFF;
    sp.u93 = 0xFF;
    sp.u94 = 0xFF;
    sp.u95 = 0xFF;
    sp.u96 = 0xFF;
    sp.u97 = 0xFF;
    sp.u98 = 0;
    sp.u9C = 0;
    sp.u9D = 2;
    (*(s32 *)((u8 *)(&sp.uA0) + 0)) = (s32) (*(s32 *)((u8 *)arg0 + 0));
    (*(s32 *)((u8 *)(&sp.uA0) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 4));
    (*(s32 *)((u8 *)(&sp.uA0) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 8));
    sp.u30 = 0xC;
    sp.u34 = 0x15;
    temp_v0 = func_15158620(&sp.u68, 3, 0xFF, 1, argA + 0x38, (s32) argB, argC);
    if (temp_v0 == 0) {
        return 0;
    }
    sp.uAC = temp_v0;
    memcpy(temp_v0 + 0xF8, &sp.u30, 8);
    memcpy(sp.uAC + 0x100, &sp.u38, 0x30);
    return sp.uAC;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B8140/func_1518A930.s")
#endif
#ifdef NON_MATCHING
s32 func_1518AB64(u8 *arg0) {
    struct {
        f32 u38;
        f32 u3C;
        f32 u40;
    } sp;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 var_f16;
    f32 var_f18;
    s32 temp_a0;
    s32 temp_a2;
    s32 var_v0;
    s32 var_v0_2;
    u8 *temp_v1;

    func_1515906C(arg0, arg0);
    temp_v1 = arg0 + 0x100;
    (*(f32 *)((u8 *)(&sp.u38) + 0)) = (*(f32 *)((u8 *)temp_v1 + 0x10));
    (*(f32 *)((u8 *)(&sp.u38) + 4)) = (f32) (*(f32 *)((u8 *)temp_v1 + 0x14));
    (*(f32 *)((u8 *)(&sp.u38) + 8)) = (f32) (*(f32 *)((u8 *)temp_v1 + 0x18));
    (*(f32 *)((u8 *)temp_v1 + 0x14)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x14)) + ((*(f32 *)((u8 *)temp_v1 + 0x28)) * D_800BE9A4));
    var_v0 = D_800BE9E4;
    if (var_v0 != 0) {
        temp_a2 = -(var_v0 & 3);
        temp_a0 = temp_a2 + var_v0;
        if (temp_a2 != 0) {
            temp_f0 = (*(f32 *)((u8 *)temp_v1 + 0x2C));
            var_v0 -= 1;
            var_f16 = (*(f32 *)((u8 *)temp_v1 + 0x10)) * temp_f0;
            if (temp_a0 != var_v0) {
                do {
                    (*(f32 *)((u8 *)temp_v1 + 0x10)) = var_f16;
                    var_v0 -= 1;
                    var_f16 = (*(f32 *)((u8 *)temp_v1 + 0x10)) * temp_f0;
                    (*(f32 *)((u8 *)temp_v1 + 0x14)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x14)) * temp_f0);
                    (*(f32 *)((u8 *)temp_v1 + 0x18)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x18)) * temp_f0);
                } while (temp_a0 != var_v0);
            }
            (*(f32 *)((u8 *)temp_v1 + 0x10)) = var_f16;
            (*(f32 *)((u8 *)temp_v1 + 0x14)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x14)) * temp_f0);
            (*(f32 *)((u8 *)temp_v1 + 0x18)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x18)) * temp_f0);
            if (var_v0 != 0) {
                goto block_5;
            }
        } else {
block_5:
            temp_f0_2 = (*(f32 *)((u8 *)temp_v1 + 0x2C));
            var_v0_2 = var_v0 - 4;
            var_f18 = (*(f32 *)((u8 *)temp_v1 + 0x10)) * temp_f0_2;
            if (var_v0_2 != 0) {
                do {
                    (*(f32 *)((u8 *)temp_v1 + 0x10)) = var_f18;
                    var_v0_2 -= 4;
                    (*(f32 *)((u8 *)temp_v1 + 0x14)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x14)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1 + 0x18)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x18)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x10)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1 + 0x14)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x14)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1 + 0x18)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x18)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x10)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1 + 0x14)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x14)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1 + 0x18)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x18)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x10)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1 + 0x14)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x14)) * temp_f0_2);
                    var_f18 = (*(f32 *)((u8 *)temp_v1 + 0x10)) * temp_f0_2;
                    (*(f32 *)((u8 *)temp_v1 + 0x18)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x18)) * temp_f0_2);
                } while (var_v0_2 != 0);
            }
            (*(f32 *)((u8 *)temp_v1 + 0x10)) = var_f18;
            (*(f32 *)((u8 *)temp_v1 + 0x14)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x14)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1 + 0x18)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x18)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x10)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1 + 0x14)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x14)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1 + 0x18)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x18)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x10)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1 + 0x14)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x14)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1 + 0x18)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x18)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x10)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1 + 0x14)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x14)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1 + 0x18)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x18)) * temp_f0_2);
        }
    }
    (*(f32 *)((u8 *)arg0 + 0x48)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x48)) + ((sp.u38 + (0.5f * (((*(f32 *)((u8 *)temp_v1 + 0x10)) - sp.u38) * D_800BEDC8) * D_800BE9A4)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x4C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x4C)) + ((sp.u3C + (0.5f * (((*(f32 *)((u8 *)temp_v1 + 0x14)) - sp.u3C) * D_800BEDC8) * D_800BE9A4)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x50)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x50)) + ((sp.u40 + (0.5f * (((*(f32 *)((u8 *)temp_v1 + 0x18)) - sp.u40) * D_800BEDC8) * D_800BE9A4)) * D_800BE9A4));
    (*(f32 *)((u8 *)temp_v1 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0)) + ((*(f32 *)((u8 *)temp_v1 + 0x1C)) * D_800BE9A4));
    (*(f32 *)((u8 *)temp_v1 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 4)) + ((*(f32 *)((u8 *)temp_v1 + 0x20)) * D_800BE9A4));
    (*(f32 *)((u8 *)temp_v1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 8)) + ((*(f32 *)((u8 *)temp_v1 + 0x24)) * D_800BE9A4));
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B8140/func_1518AB64.s")
#endif
s32 func_1518AE84(Mtx *arg0, u8 *arg1) {
    f32 *r;
    f32 mf[4][4];

    r = (f32 *)(arg1 + 0x100);
    func_150A8050(mf, r[0], r[1], r[2]);
    mf[3][0] = *(f32 *)(arg1 + 0x48);
    mf[3][1] = *(f32 *)(arg1 + 0x4C);
    mf[3][2] = *(f32 *)(arg1 + 0x50);
    mf[0][0] *= r[3];
    mf[0][1] *= r[3];
    mf[0][2] *= r[3];
    mf[1][0] *= r[3];
    mf[1][1] *= r[3];
    mf[1][2] *= r[3];
    mf[2][0] *= r[3];
    mf[2][1] *= r[3];
    mf[2][2] *= r[3];
    guMtxF2L(mf, arg0);
    return 1;
}
