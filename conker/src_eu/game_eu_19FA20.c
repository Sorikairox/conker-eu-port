#include <ultra64.h>
#include "functions.h"
#include "variables.h"


u8 *func_15172210(s16 arg0, u16 arg1, u8 arg2, s32 arg3, s32 arg4, s32 arg5, u8 arg6, s32 arg7) {
    s32 var_a0;
    u8 *t;
    if (arg5 == 0) {
        var_a0 = 0xF;
    } else {
        var_a0 = 0x43;
    }
    t = func_15167A68(var_a0, arg7, 0x60, 1, (u8) (s32) arg6, 1U);
    if (t == NULL) {
        return NULL;
    }
    *(s16 *)(t + 0x50) = arg0;
    *(s16 *)(t + 0x52) = 0;
    *(s16 *)(t + 0x54) = arg4;
    *(u16 *)(t + 0x56) = arg1;
    *(u8 *)(t + 0x58) = arg2;
    *(s8 *)(t + 0x59) = arg3;
    *(s16 *)(t + 0x16) = 0;
    *(s16 *)(t + 0x26) = 0;
    *(s16 *)(t + 0x36) = 0;
    *(s16 *)(t + 0x46) = 0;
    return t;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19FA20/func_151722BC.s")

s32 func_15172B6C(s32, s32, f32, f32, f32, f32, s32, s32);
extern s32 D_8008CDEC;

void func_15172474(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s16 arg4, u16 arg5, u8 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, u8 argB, s32 argC) {
    u8 *temp_v0;
    u8 *sp2C;

    temp_v0 = func_15172210(arg4, arg5, arg6, arg8, arg9, argA, (s32) argB, argC);
    if (temp_v0 != NULL) {
        sp2C = temp_v0;
        if (func_15172B6C((s32)((u8 *)temp_v0 + 0x10), arg3, arg0, arg1, arg2, 0.0f, arg7, *(u16 *)((u8 *)((s32 *)&D_8008CDEC)[*((u8 *)temp_v0 + 0x58)] + 6)) == 0) {
            func_1516972C((struct102 *)sp2C);
        }
    }
}

void func_15172530(struct102 *arg0) {
    s16 temp_v0;
    s32 temp_v0_2;

    temp_v0 = (*(s16 *)((u8 *)arg0 + 0x50));
    if (temp_v0 < -1) {
        (*(s16 *)((u8 *)arg0 + 0x50)) = (s16) (temp_v0 + 1);
        if ((*(s16 *)((u8 *)arg0 + 0x50)) == -1) {
            func_1516972C(arg0);
        }
    } else {
        if (temp_v0 == 0) {
            (*(s16 *)((u8 *)arg0 + 0x50)) = -3;
            return;
        }
        if (temp_v0 != -1) {
            if (!((*(u8 *)((u8 *)arg0 + 0x59)) & 4)) {
                if (D_800BE9E4 < temp_v0) {
                    (*(s16 *)((u8 *)arg0 + 0x50)) = (s16) (temp_v0 - D_800BE9E4);
                } else {
                    (*(s16 *)((u8 *)arg0 + 0x50)) = 0;
                }
            }
            (*(s16 *)((u8 *)arg0 + 0x52)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x54)) + (*(s16 *)((u8 *)arg0 + 0x52)));
            temp_v0_2 = (*(u8 *)((u8 *)((&D_8008CDEC)[(*(u8 *)((u8 *)arg0 + 0x58))]) + 4));
            if (((s16) (*(s16 *)((u8 *)arg0 + 0x52)) / 256) >= temp_v0_2) {
                if ((*(u8 *)((u8 *)arg0 + 0x59)) & 4) {
                    (*(s16 *)((u8 *)arg0 + 0x50)) = -3;
                    return;
                }
                (*(s16 *)((u8 *)arg0 + 0x52)) = (s16) ((temp_v0_2 << 8) - 0x100);
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19FA20/func_15172634.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19FA20/func_15172B6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19FA20/func_15173090.s")
