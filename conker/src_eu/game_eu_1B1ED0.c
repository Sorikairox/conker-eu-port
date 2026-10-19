#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/func_151846C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/func_151848D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/func_15185360.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/func_15185514.s")

u8 *func_151859C4(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 q;
    f32 temp_f16;

    q = (*(f32 *)(arg0 + 8) - *(f32 *)(arg0 + 4)) / ((*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) - (*(f32 *)(arg1 + 8) - *(f32 *)(arg0 + 8)));
    *(f32 *)(arg2 + 0) = (*(f32 *)(arg1 + 0) - *(f32 *)(arg0 + 0)) * q + *(f32 *)(arg0 + 0);
    temp_f16 = (*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) * q + *(f32 *)(arg0 + 4);
    *(f32 *)(arg2 + 8) = temp_f16;
    *(f32 *)(arg2 + 4) = temp_f16;
    *(s16 *)(arg2 + 0xC) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xC) - *(s16 *)(arg0 + 0xC)) * q + (f32) *(s16 *)(arg0 + 0xC));
    *(s16 *)(arg2 + 0xE) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xE) - *(s16 *)(arg0 + 0xE)) * q + (f32) *(s16 *)(arg0 + 0xE));
    *(s16 *)(arg2 + 0x10) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0x10) - *(s16 *)(arg0 + 0x10)) * q + (f32) *(s16 *)(arg0 + 0x10));
    return arg2 + 0x14;
}

s32 func_15185AC4(f32 *arg0) {
    return arg0[2] < arg0[1];
}

u8 *func_15185AEC(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 q;

    q = (*(f32 *)(arg0 + 8) + *(f32 *)(arg0 + 0)) / ((*(f32 *)(arg0 + 8) - *(f32 *)(arg1 + 8)) + (*(f32 *)(arg0 + 0) - *(f32 *)(arg1 + 0)));
    *(f32 *)(arg2 + 0) = (*(f32 *)(arg1 + 0) - *(f32 *)(arg0 + 0)) * q + *(f32 *)(arg0 + 0);
    *(f32 *)(arg2 + 4) = (*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) * q + *(f32 *)(arg0 + 4);
    *(f32 *)(arg2 + 8) = -*(f32 *)(arg2 + 0);
    *(s16 *)(arg2 + 0xC) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xC) - *(s16 *)(arg0 + 0xC)) * q + (f32) *(s16 *)(arg0 + 0xC));
    *(s16 *)(arg2 + 0xE) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xE) - *(s16 *)(arg0 + 0xE)) * q + (f32) *(s16 *)(arg0 + 0xE));
    *(s16 *)(arg2 + 0x10) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0x10) - *(s16 *)(arg0 + 0x10)) * q + (f32) *(s16 *)(arg0 + 0x10));
    return arg2 + 0x14;
}

s32 func_15185BEC(f32 *arg0) {
    return arg0[0] < -arg0[2];
}

u8 *func_15185C18(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 q;

    q = (*(f32 *)(arg0 + 8) + *(f32 *)(arg0 + 4)) / ((*(f32 *)(arg0 + 8) - *(f32 *)(arg1 + 8)) + (*(f32 *)(arg0 + 4) - *(f32 *)(arg1 + 4)));
    *(f32 *)(arg2 + 0) = (*(f32 *)(arg1 + 0) - *(f32 *)(arg0 + 0)) * q + *(f32 *)(arg0 + 0);
    *(f32 *)(arg2 + 4) = (*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) * q + *(f32 *)(arg0 + 4);
    *(f32 *)(arg2 + 8) = -*(f32 *)(arg2 + 4);
    *(s16 *)(arg2 + 0xC) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xC) - *(s16 *)(arg0 + 0xC)) * q + (f32) *(s16 *)(arg0 + 0xC));
    *(s16 *)(arg2 + 0xE) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xE) - *(s16 *)(arg0 + 0xE)) * q + (f32) *(s16 *)(arg0 + 0xE));
    *(s16 *)(arg2 + 0x10) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0x10) - *(s16 *)(arg0 + 0x10)) * q + (f32) *(s16 *)(arg0 + 0x10));
    return arg2 + 0x14;
}

s32 func_15185D20(f32 *arg0) {
    return arg0[1] < -arg0[2];
}

u8 *func_15185D4C(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 q;

    q = (*(f32 *)(arg0 + 8) - *(f32 *)(arg0 + 0)) / ((*(f32 *)(arg1 + 0) - *(f32 *)(arg0 + 0)) - (*(f32 *)(arg1 + 8) - *(f32 *)(arg0 + 8)));
    *(f32 *)(arg2 + 0) = (*(f32 *)(arg1 + 0) - *(f32 *)(arg0 + 0)) * q + *(f32 *)(arg0 + 0);
    *(f32 *)(arg2 + 4) = (*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) * q + *(f32 *)(arg0 + 4);
    *(f32 *)(arg2 + 8) = *(f32 *)(arg2 + 0);
    *(s16 *)(arg2 + 0xC) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xC) - *(s16 *)(arg0 + 0xC)) * q + (f32) *(s16 *)(arg0 + 0xC));
    *(s16 *)(arg2 + 0xE) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xE) - *(s16 *)(arg0 + 0xE)) * q + (f32) *(s16 *)(arg0 + 0xE));
    *(s16 *)(arg2 + 0x10) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0x10) - *(s16 *)(arg0 + 0x10)) * q + (f32) *(s16 *)(arg0 + 0x10));
    return arg2 + 0x14;
}

s32 func_15185E44(f32 *arg0) {
    return arg0[2] < arg0[0];
}

u8 *func_15185E6C(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 q;

    q = (D_800D3AA8 - *(f32 *)(arg0 + 8)) / (*(f32 *)(arg1 + 8) - *(f32 *)(arg0 + 8));
    *(f32 *)(arg2 + 0) = (*(f32 *)(arg1 + 0) - *(f32 *)(arg0 + 0)) * q + *(f32 *)(arg0 + 0);
    *(f32 *)(arg2 + 4) = (*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) * q + *(f32 *)(arg0 + 4);
    *(f32 *)(arg2 + 8) = D_800D3AA8;
    *(s16 *)(arg2 + 0xC) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xC) - *(s16 *)(arg0 + 0xC)) * q + (f32) *(s16 *)(arg0 + 0xC));
    *(s16 *)(arg2 + 0xE) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xE) - *(s16 *)(arg0 + 0xE)) * q + (f32) *(s16 *)(arg0 + 0xE));
    *(s16 *)(arg2 + 0x10) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0x10) - *(s16 *)(arg0 + 0x10)) * q + (f32) *(s16 *)(arg0 + 0x10));
    return arg2 + 0x14;
}

s32 func_15185F6C(f32 *arg0) {
    return D_800D3AA8 < arg0[2];
}

u8 *func_15185F98(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 q;

    q = (D_800D3AAC - *(f32 *)(arg0 + 8)) / (*(f32 *)(arg1 + 8) - *(f32 *)(arg0 + 8));
    *(f32 *)(arg2 + 0) = (*(f32 *)(arg1 + 0) - *(f32 *)(arg0 + 0)) * q + *(f32 *)(arg0 + 0);
    *(f32 *)(arg2 + 4) = (*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) * q + *(f32 *)(arg0 + 4);
    *(f32 *)(arg2 + 8) = D_800D3AAC;
    *(s16 *)(arg2 + 0xC) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xC) - *(s16 *)(arg0 + 0xC)) * q + (f32) *(s16 *)(arg0 + 0xC));
    *(s16 *)(arg2 + 0xE) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xE) - *(s16 *)(arg0 + 0xE)) * q + (f32) *(s16 *)(arg0 + 0xE));
    *(s16 *)(arg2 + 0x10) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0x10) - *(s16 *)(arg0 + 0x10)) * q + (f32) *(s16 *)(arg0 + 0x10));
    return arg2 + 0x14;
}

s32 func_15186098(f32 *arg0) {
    return arg0[2] < D_800D3AAC;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/func_151860C4.s")

s32 func_151861B4(f32 *arg0) {
    return *arg0 <= 0.0f;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/func_151861DC.s")

s32 func_151862CC(f32 *arg0) {
    return arg0[1] <= 0.0f;
}

s32 func_151862F4(f32 *arg0) {
    return *arg0 > 0.0f;
}

s32 func_1518631C(f32 *arg0) {
    return arg0[1] > 0.0f;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/func_15186344.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/func_15186494.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/func_15186A9C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/func_15186D04.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/func_15187820.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/func_15187954.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/func_15187B50.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/func_15187EE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/func_15188008.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/func_151882DC.s")
