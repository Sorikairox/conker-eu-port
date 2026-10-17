#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_110DB0/func_150E35A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_110DB0/func_150E3788.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_110DB0/func_150E3850.s")

s32 func_150E35A0(s32, s32, s32, s32, s32, s32, s32, f32, s32, f32, f32, f32, s32, s32);

void func_150E38C0(u8 *arg0, u8 *arg1, s32 arg2, s16 arg3) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a2;

    temp_a0 = (*(s32 *)arg1);
    temp_a1 = (*(s32 *)((u8 *)arg1 + 4));
    temp_a2 = (*(s32 *)((u8 *)arg1 + 8));
    func_150E35A0(temp_a0, temp_a1, temp_a2, temp_a0, temp_a1, temp_a2, 0x1A, 10.0f, 0, (*(f32 *)arg0), (*(f32 *)((u8 *)arg0 + 4)), (*(f32 *)((u8 *)arg0 + 8)), arg2, (s32) arg3);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_110DB0/func_150E394C.s")

extern s32 func_150E394C;

s32 func_150E3994(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, f32 arg8) {
    s32 temp_v0;
    s32 sp44;

    temp_v0 = func_150E35A0(arg3, arg4, arg5, 0, 0, 0, arg7, arg8, arg6, (f32) arg0, (f32) arg1, (f32) arg2, 0, -0x63);
    if (temp_v0 != 0) {
        sp44 = temp_v0;
        (*(u16 *)((u8 *)sp44 + 0x4A)) = func_1000FA64(0x2D0U, (s16) arg0, (s16) arg1, (s16) arg2, 0x5DC0, 0x1770U, 0x3E8, (s32) &func_150E394C, NULL, 0, 0, 0);
        return (*(u8 *)((u8 *)sp44 + 0x48)) + 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_110DB0/func_150E3A94.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_110DB0/func_150E3B5C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_110DB0/func_150E3C3C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_110DB0/func_150E3CB8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_110DB0/func_150E4590.s")

extern f32 D_800A1424;

void func_150E469C(s32 arg0) {
    func_151C40BC(arg0, 0.35200003f, 0.70100003f, 0.56600004f, D_800A1424, 0xFF, 0xFF, 0xFF);
}

s32 func_150E46F4(f32 *arg0) {
    arg0[0x2C / 4] += arg0[0x4C / 4] * D_800BE9A4;
    arg0[0x30 / 4] += arg0[0x54 / 4] * D_800BE9A4;
    return 1;
}
