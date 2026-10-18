#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13C400/func_1510EBF0.s")

s32 func_1510EED0(s32, s32, s32, s32, s32, s32, s32, f32, f32, f32, f32, u16, s32, f32, f32, s32);
void func_1510ED24(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u16 argA, s32 argB, f32 argC, f32 argD) {
    func_1510EED0(arg0, arg1, 0, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, argA, argB, argC, argD, 0);
}

s32 func_1510EED0(s32, s32, s32, s32, s32, s32, s32, f32, f32, f32, f32, u16, s32, f32, f32, s32);
void func_1510EDAC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u16 argA, s32 argB) {
    func_1510EED0(arg0, arg1, 0, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, argA, argB, -10000.0f, 20000.0f, 0);
}

s32 func_1510EED0(s32, s32, s32, s32, s32, s32, s32, f32, f32, f32, f32, u16, s32, f32, f32, s32);
void func_1510EE3C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u16 argA, s32 argB, s32 argC, s32 argD, s32 argE) {
    func_1510EED0(arg0, arg1, 0, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, argA, argB, -10000.0f, 20000.0f, argE);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13C400/func_1510EED0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13C400/func_1510FBC8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13C400/func_1510FCA0.s")

void func_1510F800(s32 arg0) {
    func_150A4ED4(arg0);
}

s32 func_1510E908(s32, s32, f32 *, f32 *);
void func_1510FDA0(s32 arg0, s32 arg1, f32 *arg2, f32 *arg3, s32 arg4, f32 *arg5, f32 *arg6)
{
  f32 sp24;
  f32 sp20;
  f32 temp_f2;
  func_1510E908(arg0, arg1, &sp24, &sp20);
  temp_f2 = sqrtf((sp24 * sp24) + (sp20 * sp20));
  *arg5 = sp24;
  *arg6 = sp20;
  temp_f2 = temp_f2 * 0.02f;
  if (temp_f2 == 0.0f) {
    *arg2 = 1.0f;
    *arg3 = 0.0f;
    return;
  }
  *arg2 = sp24 / temp_f2;
  *arg3 = sp20 / temp_f2;
}

s32 func_1510FE4C(s32 arg0) {
    return arg0 & 0x1F;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13C400/func_1510FE58.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13C400/func_151101B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13C400/func_1510FD20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13C400/func_151103B0.s")
