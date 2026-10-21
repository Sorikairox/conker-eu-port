#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_1510F800(s32 arg0);
#endif


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

#ifdef NON_MATCHING
s32 func_150A48C0(s32, s32, s32, s32 *);
s32 func_150A49D0(s32, s32 *, s32);
s32 func_150A69A8(s16, s16, s32 *, s32);
extern s32 D_800D3720;
extern s32 D_800D3C50;

f32 func_1510FBC8(f32 arg0, f32 arg1, f32 arg2) {
    struct {
        s32 u28;
    } sp;
    s32 sp20;
    s32 sp1C;
    f32 var_f2;
    s32 temp_f10;
    s32 temp_f6;

    func_1510F800(2);
    temp_f6 = (s32) arg0;
    temp_f10 = (s32) arg2;
    sp20 = temp_f6;
    sp1C = temp_f10;
    func_150A69A8((s16) temp_f6, (s16) temp_f10, &sp.u28, (s32) arg1);
    func_150A49D0(sp.u28, &D_800D3C50, 0);
    if (func_150A48C0(sp20, sp1C, sp.u28, &D_800D3C50) != 0) {
        var_f2 = (f32) D_800D3720 * 0.00390625f;
    } else {
        var_f2 = -10000.0f;
    }
    return var_f2;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13C400/func_1510FBC8.s")
#endif
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

extern u8 *D_800DC278;
s32 func_151103B0(u8 *arg0) {
    s32 count = 0;
    u8 *p = D_800DC278;

    while (p != NULL) {
        if (p == arg0) {
            return count;
        }
        if (*(s16 *)(p + 0xC) != 0) {
            p += *(s16 *)(p + 0xC);
        } else if (*(s16 *)(p + 4) != 0) {
            p += *(s16 *)(p + 4);
            count++;
        } else {
            p = NULL;
        }
    }
    return 0;
}
