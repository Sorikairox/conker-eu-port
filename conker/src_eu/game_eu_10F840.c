#include <ultra64.h>
#include "functions.h"
#include "variables.h"

s32 func_150E2030(s32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32, s32, struct127 *, s32, s32, s32, s32, s32, f32, f32, f32, f32, f32, f32);


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10F840/func_150E2030.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10F840/func_150E2294.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10F840/func_150E2E5C.s")

s32 func_150E3324(s32 arg0, s32 arg1) {
    return arg0;
}

void func_150E3334(s32 arg0, u8 arg1, s16 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, s16 argA, s16 argB, u16 argC, u8 argD) {
    func_150E2030(0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 40.0f, 400.0f, (s32) argC, 0x27, 1, (s32) argA, (s32) argB, (struct127 *)arg0, (s32) arg1, (s32) arg2, arg3, 0, (s32) argD, arg4, arg5, arg6, arg7, arg8, arg9);
}

void func_150E2EA4(struct127 *arg0, u8 arg1, s16 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, s16 argA, s16 argB, u16 argC, f32 argD, f32 argE, u8 argF, f32 arg10) {
    func_150E2030(0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, arg10, 0.0f, argD, argE, (s32) argC, 0x27, 1, (s32) argA, (s32) argB, arg0, (s32) arg1, (s32) arg2, arg3, 0, (s32) argF, arg4, arg5, arg6, arg7, arg8, arg9);
}

void func_150E3510(s32 arg0, s32 arg1, s16 arg2) {
    func_150E3324(arg0, arg2);
}

void func_150E3540(u8 *arg0, s32 *arg1, u8 arg2) {
    if (arg2 == 0x2D) {
        if (arg1[0] == *(s32 *)(arg0 + 0xDC)) {
            *(s32 *)(arg0 + 0xDC) = arg1[1];
            arg0[0xDA] = ((u8 *)arg1)[9];
            return;
        }
        if (arg1[1] == *(s32 *)(arg0 + 0xDC)) {
            *(s32 *)(arg0 + 0xDC) = arg1[0];
            arg0[0xDA] = ((u8 *)arg1)[8];
        }
    }
}
