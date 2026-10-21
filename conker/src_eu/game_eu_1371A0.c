#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1371A0/func_15109990.s")

#ifdef NON_MATCHING
extern s32 D_80089000;
extern s32 D_80089004;
extern s32 D_800A28D4;

void func_15109A7C(u8 *arg0) {
    struct {
        f32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        f32 u98;
        f32 u9C;
        f32 uA0;
        f32 uA4;
        f32 uA8;
        f32 uAC;
        f32 uB0;
        s32 uB4;
        u8 padB8[0x8];
        u8 * uC0;
    } sp;
    s32 *var_v0;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f2;
    f32 var_f0;
    f32 var_f2;
    s32 temp_s3;
    s32 var_s0;
    s8 temp_v0_2;
    u8 *temp_s1;
    u8 *temp_s2;
    u8 *temp_s4;
    u8 *temp_v0;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x28));
    temp_s4 = arg0 + 0x28;
    if (((*(s32 *)((u8 *)temp_v0 + 0)) == 0) || ((*(u8 *)((u8 *)temp_s4 + 4)) != (*(u8 *)((u8 *)temp_v0 + 0x3B)))) {
        (*(s16 *)((u8 *)arg0 + 0xE)) = -1;
        return;
    }
    (*(f32 *)((u8 *)temp_s4 + 8)) = (f32) ((*(f32 *)((u8 *)temp_s4 + 8)) + ((*(f32 *)((u8 *)temp_s4 + 0xC)) * 351.8639f * D_800BE9A4));
    if (((*(s8 *)((u8 *)temp_s4 + 0x11)) != -1) && ((*(s32 *)((u8 *)temp_v0 + 0x1D4)) != 0)) {
        if ((*(f32 *)((u8 *)temp_s4 + 8)) > 1.0f) {
            sp.uC0 = temp_v0;
            do {
                var_s0 = 0;
                var_f2 = (*(f32 *)((u8 *)(&D_800A28D4) + 0x18)) * func_150ADA68();
                var_v0 = &D_800A28D4;
                if ((*(f32 *)((u8 *)(&D_800A28D4) + 0)) < var_f2) {
                    var_f0 = (*(f32 *)((u8 *)(&D_800A28D4) + 0));
                    do {
                        var_f2 -= var_f0;
                        var_f0 = (*(f32 *)((u8 *)var_v0 + 4));
                        var_s0 += 1;
                        var_v0 += 4;
                    } while (var_f0 < var_f2);
                }
                temp_f0 = func_150ADA68();
                temp_s3 = var_s0 * 0xC;
                temp_s1 = temp_s3 + "A ";
                temp_f2 = (*(f32 *)((u8 *)temp_s1 + 0));
                temp_f12 = (*(f32 *)((u8 *)temp_s1 + 4));
                temp_f14 = (*(f32 *)((u8 *)temp_s1 + 8));
                sp.u78 = (((*(f32 *)((u8 *)temp_s1 + 0xC)) - temp_f2) * temp_f0) + temp_f2;
                sp.u7C = (((*(f32 *)((u8 *)temp_s1 + 0x10)) - temp_f12) * temp_f0) + temp_f12;
                sp.u80 = (((*(f32 *)((u8 *)temp_s1 + 0x14)) - temp_f14) * temp_f0) + temp_f14;
                temp_s2 = (*(s32 *)((u8 *)sp.uC0 + 0x1D4)) + 0x240;
                func_15143134(&sp.u78, &sp.uB4, temp_s2);
                func_15143134(temp_s1, &sp.uA8, temp_s2);
                func_15143134(temp_s1 + 0xC, &sp.u9C, temp_s2);
                func_15143134(temp_s3 + "A ", &sp.u90, temp_s2);
                temp_f0_2 = func_150ADA68();
                sp.u84 = (((sp.u90 - sp.u9C) * temp_f0_2) + sp.u9C) - sp.uA8;
                sp.u88 = (((sp.u94 - sp.uA0) * temp_f0_2) + sp.uA0) - sp.uAC;
                sp.u8C = (((sp.u98 - sp.uA4) * temp_f0_2) + sp.uA4) - sp.uB0;
                func_15145128(sp.uA0, sp.uA4, &sp.u84, &sp.u84, 0, 0);
                ((s32 (*)()) *(s32 *)((u8 *)&D_80089004 + ((*(s8 *)((u8 *)temp_s4 + 0x11)) * 4)))(arg0, &sp.uB4, &sp.uA8, &sp.u9C, &sp.u90, &sp.u84);
                (*(f32 *)((u8 *)temp_s4 + 8)) = (f32) ((*(f32 *)((u8 *)temp_s4 + 8)) - 1.0f);
            } while ((*(f32 *)((u8 *)temp_s4 + 8)) > 1.0f);
        }
    } else if ((*(f32 *)((u8 *)temp_s4 + 8)) > 1.0f) {
        do {
            (*(f32 *)((u8 *)temp_s4 + 8)) = (f32) ((*(f32 *)((u8 *)temp_s4 + 8)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s4 + 8)) > 1.0f);
    }
    temp_v0_2 = (*(s8 *)((u8 *)temp_s4 + 0x10));
    if (temp_v0_2 != -1) {
        (*(s32 (**)())((u8 *)&D_80089000 + (temp_v0_2 * 4)))(arg0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1371A0/func_15109A7C.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1371A0/func_15109DC8.s")
