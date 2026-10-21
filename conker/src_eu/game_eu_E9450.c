#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
void func_15132FBC(s32, s32, s32, s32, u8, s32);

void func_150BB760(u8 *arg0) {
    struct {
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
        f32 uB4;
        f32 uB8;
        f32 uBC;
        f32 uC0;
        f32 uC4;
        f32 uC8;
        s32 uCC;
        s16 uD0;
        s16 uD2;
        s8 uD4;
        u8 padD5[0x3];
        s32 uD8;
        s8 uDC;
        s8 uDD;
        s8 uDE;
        s8 uDF;
        s8 uE0;
        s8 uE1;
        s8 uE2;
        s8 uE3;
        s8 uE4;
        u8 padE5[0x1];
        s8 uE6;
        u8 padE7[0x1];
        u8 * uE8;
        u8 uEC;
        u8 padED[0x1];
        s16 uEE;
        s16 uF0;
    } sp;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp68;
    f32 sp64;
    u8 sp63;
    f32 sp5C;
    f32 sp58;
    f32 sp50;
    f32 sp4C;
    u8 sp4B;
    f32 sp44;
    f32 sp40;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 temp_f10;
    f32 temp_f10_2;
    f32 temp_f12;
    f32 temp_f16;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f2_4;
    f32 temp_f6;
    u8 temp_t8;
    u8 temp_v0;

    if ((*(u8 *)((u8 *)arg0 + 4)) != 0x20) {
        return;
    }
    if ((arg0 != NULL) && ((*(s32 *)((u8 *)arg0 + 0)) != 0) && ((*(s32 *)((u8 *)arg0 + 0x1D4)) != 0)) {
        sp78 = (f32) (*(s16 *)((u8 *)arg0 + 0xE4));
        sp74 = (f32) (*(s16 *)((u8 *)arg0 + 0xE6));
        sp70 = func_151423D8(((s32) (*(u16 *)((u8 *)arg0 + 0x76)) >> 8) & 0xFF);
        temp_f2 = (*(f32 *)((u8 *)arg0 + 0x3C));
        temp_f6 = temp_f2 * func_151423D8((((s32) (*(u16 *)((u8 *)arg0 + 0x76)) >> 8) + 0x40) & 0xFF);
        sp68 = temp_f2 * sp70 * 0.5f;
        sp.uD2 = 1;
        sp.uCC = 0x29E9;
        sp.uD4 = 0;
        sp.uD8 = 0;
        sp.uDC = 0xFF;
        sp.uDD = 1;
        sp.uDE = 0;
        sp.uDF = 2;
        sp64 = temp_f6 * 0.5f;
        sp.uE0 = 0;
        sp.uE1 = 0;
        sp.uE2 = 0;
        sp.uE3 = 0;
        sp.uE4 = 0;
        sp.uE6 = 1;
        sp.uE8 = arg0;
        sp.u98 = 1.0f;
        sp.u9C = 1.0f;
        sp.uA0 = 1.0f;
        sp.uC4 = 0.0f;
        sp.uC8 = -1.0f;
        sp.uEE = 0x20;
        sp.uF0 = 7;
        sp.uEC = (*(u8 *)((u8 *)arg0 + 0x3B));
        temp_v0 = func_150ADA20();
        sp63 = temp_v0;
        sp5C = func_151423D8(temp_v0 & 0xFF);
        sp58 = func_151423D8((sp63 - 0x40) & 0xFF);
        temp_f2_2 = func_150ADA68() * sp78;
        sp50 = sp5C * temp_f2_2;
        sp4C = -sp58 * temp_f2_2;
        temp_t8 = (((s32) (*(u16 *)((u8 *)arg0 + 0x76)) >> 8) - (func_150ADA20() & 0x3F)) - 0x20;
        sp4B = temp_t8;
        sp44 = func_151423D8(temp_t8 & 0xFF);
        sp40 = func_151423D8((sp4B - 0x40) & 0xFF);
        temp_f2_3 = (func_150ADA68() * 5.0f) + 3.0f;
        temp_f10 = sp40 * temp_f2_3;
        sp38 = temp_f10;
        sp34 = sp44 * temp_f2_3;
        temp_f12 = (func_150ADA68() * 0.05f) + 0.01f;
        sp30 = temp_f12;
        temp_f16 = func_150ADA68() * 0.05f;
        sp.u84 = temp_f12;
        temp_f2_4 = temp_f16 + 0.01f;
        sp.u88 = temp_f2_4;
        sp.u7C = (temp_f12 + temp_f2_4) * 0.5f;
        sp.u8C = func_150ADA68() * 360.0f;
        sp.u90 = func_150ADA68() * 360.0f;
        sp.u94 = func_150ADA68() * 360.0f;
        sp.uA4 = (*(f32 *)((u8 *)arg0 + 0x14)) + sp50;
        sp.uA8 = (func_150ADA68() * sp74) + (*(f32 *)((u8 *)arg0 + 0x18)) + 4.0f;
        sp.uB0 = temp_f10 + sp68;
        sp.uAC = (*(f32 *)((u8 *)arg0 + 0x1C)) + sp4C;
        temp_f10_2 = (func_150ADA68() * 5.0f) + 3.0f;
        sp.uB8 = sp34 + sp64;
        sp.uB4 = temp_f10_2;
        sp.uBC = 25.0f - (func_150ADA68() * 50.0f);
        sp.uC0 = 25.0f - (func_150ADA68() * 50.0f);
        sp.uD0 = (func_150ADA20() & 0x1F) + 0x3C;
        sp.u80 = (func_150ADA68() * 0.2f) + 0.25f;
        func_15132FBC(&sp.u7C, 3, 0xFF, 0, 0xFF, 0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E9450/func_150BB760.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E9450/func_150BC03C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E9450/func_150BC968.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E9450/func_150BCBBC.s")
s32 func_150BD498(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    *(f32 *)(arg0 + 0x3C) = *(f32 *)(arg0 + 0x10) * 1.1f + arg4;
    if (*(f32 *)(arg0 + 0x48) > -2.0f) {
        *(f32 *)(arg0 + 0x44) = 0.0f;
        *(s32 *)(arg0 + 0x60) &= ~0x6F;
        *(f32 *)(arg0 + 0x48) = 0.0f;
        *(f32 *)(arg0 + 0x4C) = 0.0f;
    } else {
        f32 k = *(f32 *)(arg0 + 0x14);

        *(f32 *)(arg0 + 0x44) *= k;
        *(f32 *)(arg0 + 0x48) = -*(f32 *)(arg0 + 0x48) * k;
        *(f32 *)(arg0 + 0x4C) *= k;
        *(f32 *)(arg0 + 0x50) *= k;
        *(f32 *)(arg0 + 0x54) *= k;
        *(f32 *)(arg0 + 0x58) *= k;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E9450/func_150BD550.s")
