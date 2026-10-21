#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_113D60/func_150E6550.s")

#ifdef NON_MATCHING
f32 func_15144A74(void *, void *);
extern s32 D_80088DB0;

s8 func_150E67B0(u8 *arg0) {
    struct {
        f32 u30;
        f32 u34;
        f32 u38;
        u8 pad3C[0xB];
        s8 u47;
    } sp;
    u8 *sp20;
    f32 temp_f0;
    f32 var_f0;
    s8 temp_v1;
    s8 var_a3;
    u8 *temp_v0;

    var_a3 = 1;
    temp_v0 = arg0 + 0x110;
    if ((*(u8 *)((u8 *)arg0 + 0x110)) & 1) {
        sp.u30 = (*(f32 *)((u8 *)temp_v0 + 4)) - (*(f32 *)((u8 *)arg0 + 0x34));
        sp.u34 = (*(f32 *)((u8 *)temp_v0 + 8)) - (*(f32 *)((u8 *)arg0 + 0x38));
        sp.u47 = 1;
        sp20 = temp_v0;
        sp.u38 = (*(f32 *)((u8 *)temp_v0 + 0xC)) - (*(f32 *)((u8 *)arg0 + 0x3C));
        var_a3 = sp.u47;
        if (func_15144A74(&sp.u30, temp_v0 + 4) < 0.0f) {
            var_f0 = -1.0f;
        } else {
            var_f0 = 1.0f;
        }
        if (var_f0 != (*(f32 *)((u8 *)sp20 + 0x28))) {
            temp_v1 = (*(s8 *)((u8 *)sp20 + 0x2C));
            var_a3 = 0;
            if (temp_v1 != -1) {
                var_a3 = (*(s32 (**)())((u8 *)&D_80088DB0 + (temp_v1 * 4)))(arg0);
            }
        }
    }
    temp_f0 = (*(f32 *)((u8 *)arg0 + 0x50));
    (*(f32 *)((u8 *)arg0 + 0x34)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x34)) + ((*(f32 *)((u8 *)arg0 + 0x40)) * temp_f0 * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x38)) + ((*(f32 *)((u8 *)arg0 + 0x44)) * temp_f0 * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + ((*(f32 *)((u8 *)arg0 + 0x48)) * temp_f0 * D_800BE9A4));
    return var_a3;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_113D60/func_150E67B0.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_113D60/func_150E6920.s")

s32 func_150E6D1C(u8 *arg0) {
    s16 temp_v0 = *(s16 *)(arg0 + 0x1C);
    s32 temp_v1;

    if (temp_v0 < 8) {
        temp_v1 = temp_v0 << 5;
        if (temp_v1 < arg0[0x5C]) {
            arg0[0x5C] = temp_v1;
        }
    }
    return 1;
}

#ifdef NON_MATCHING
s32 func_150E6D50(u8 *arg0) {
    struct {
        s32 u48;
        s16 u4C;
        s8 u4E;
        u8 pad4F[0x1];
        s32 u50;
        s32 u54;
        s8 u58;
        s8 u59;
        s8 u5A;
        s8 u5B;
        s8 u5C;
        s8 u5D;
        u8 pad5E[0x2];
        s32 u60;
    } sp;
    u8 *temp_v1;

    sp.u4E = 0x3A;
    sp.u48 = 1;
    sp.u4C = 0x64;
    sp.u50 = 0;
    sp.u54 = 0;
    sp.u58 = 0xFF;
    sp.u59 = 0xFF;
    sp.u5A = 0;
    sp.u5B = 0;
    sp.u5C = 0;
    sp.u5D = 0xFF;
    sp.u60 = 0x130001;
    temp_v1 = arg0 + 0x110;
    func_1513C73C((s32) &sp.u48, 0U, 0U, (s32) (temp_v1 + 0x14), (*(f32 *)((u8 *)temp_v1 + 4)), (*(f32 *)((u8 *)temp_v1 + 8)), (*(f32 *)((u8 *)temp_v1 + 0xC)), 50.0f, 50.0f, (u8) (func_150ADA20() & 0xFF), 0U, 0, (u8) (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_113D60/func_150E6D50.s")
#endif