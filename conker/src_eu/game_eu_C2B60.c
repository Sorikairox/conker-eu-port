#include <ultra64.h>
#include "functions.h"
#include "variables.h"

Gfx *func_15095350(Gfx *arg0) {
    gSPDisplayList(arg0++, D_80087770);
    D_800D30C0 = 0;
    return arg0;
}

s32 func_15095470(s32, s32, s32);
s32 func_150954E4(s32, s32 *, s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 D_800D30B0;

void func_15095380(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    func_15095470(arg1, arg2, arg3);
    func_150954E4(arg0, &D_800D30B0, arg4, arg5, 0, arg6, arg7, 0x100, 0x100, arg8);
}

s32 func_15095470(s32, s32, s32);
s32 func_150954E4(s32, s32 *, s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 D_800D30B0;

void func_150953F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA) {
    func_15095470(arg1, arg2, arg3);
    func_150954E4(arg0, &D_800D30B0, arg4, arg5, 0, arg6, arg7, arg8, arg9, argA);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C2B60/func_15095470.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C2B60/func_150954E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C2B60/func_15095A4C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C2B60/func_15095B70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C2B60/func_15095CC0.s")

void func_15095E58(s32 arg0, s32 arg1, f32 arg2, f32 arg3) {
    func_15095EA0(arg0, arg1, arg2, arg3, 4096.0f, 0, 0, 0, 0);
}

s32 func_15095F18(s32, f32, f32, f32, s32, s32 *);
s32 func_15096144(s32, s32, s32, s32, s32);
s32 func_15095EA0(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    s32 sp24;
    func_15095F18(arg1, arg2, arg3, arg4, arg5, &sp24);
    if (sp24 != 0) {
        arg0 = func_15096144(arg0, arg1, arg6, arg7, arg8);
    }
    return arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C2B60/func_15095F18.s")

void func_1509611C(s32 arg0, s32 arg1) {
    func_15096144(arg0, arg1, 0, 0, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C2B60/func_15096144.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C2B60/func_150966AC.s")

Gfx *func_15096D44(Gfx *arg0) {
    gSPDisplayList(arg0++, D_800877A8);
    D_800D31CB = 0;
    return arg0;
}
