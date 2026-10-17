#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 memcpy(u8 *, s32, s32);
extern f32 D_800AA770;

u8 *func_151B3660(s32 arg0, f32 arg1, s32 arg2, u8 arg3, s32 arg4) {
    u8 *temp_v0;
    f32 temp_f0;
    u8 *sp24;

    temp_v0 = func_15167A68(0x33, arg4, arg2 + 0x150, 1, (u8) (s32) arg3, 1U);
    if (temp_v0 == NULL) {
        return NULL;
    }
    sp24 = temp_v0;
    memcpy(temp_v0 + 0x10, arg0, 0x38);
    temp_f0 = (*(f32 *)((u8 *)temp_v0 + 0x38));
    (*(u8 *)((u8 *)temp_v0 + 0x10)) = (u8) ((*(u8 *)((u8 *)temp_v0 + 0x10)) | 0xE);
    (*(f32 *)((u8 *)temp_v0 + 0x138)) = (f32) (2.0f * ((temp_f0 * temp_f0) / D_800AA770));
    (*(s32 *)((u8 *)temp_v0 + 0x13C)) = (s32) (temp_f0 * arg1 * 4096.0f);
    bzero(temp_v0 + 0x140, 0x10);
    return sp24;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E0E70/func_151B3734.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E0E70/func_151B3878.s")

void func_151B3FE4(u8 *arg0, s32 arg1, u8 arg2) {
    void (*fp)(void *, s32, u8) = D_8008FF08[arg0[0x44]];
    if (fp != NULL) {
        fp(arg0, arg1, arg2);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E0E70/func_151B402C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E0E70/func_151B42A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E0E70/func_151B44D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E0E70/func_151B458C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E0E70/func_151B4854.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E0E70/func_151B4D88.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E0E70/func_151B4E8C.s")

s32 func_151B4F3C(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4, s32 *arg5, s32 *arg6, s32 *arg7, s32 *arg8, s32 *arg9, s32 *argA, s32 *argB, s8 *argC, s8 *argD) {
    *arg1 = 0x220005;
    *arg2 = 0x40600;
    *arg3 = 0xFF;
    *arg4 = 0xFF;
    *arg5 = 0xFF;
    *arg6 = 0xFF;
    *arg7 = 0xFF;
    *arg8 = 0xFF;
    *arg9 = 0xFF;
    *argA = 0xFF;
    *argB = 0;
    *argC = 5;
    *argD = 0x2B;
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E0E70/func_151B4FC4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E0E70/func_151B5128.s")

void func_151D5E30();

void func_151B51CC(void *arg0) {
    void (*fp)(void *);
    func_151D5E30((u8 *)arg0 + 0x140, arg0);
    fp = D_8008FF10[((u8 *)arg0)[0x44]];
    if (fp != NULL) {
        fp(arg0);
    }
}

void func_151B51CC(void *arg0);

void func_151B521C(void *arg0) {
    func_151B51CC(arg0);
    func_15169824(arg0);
}

void func_151B5248(void *arg0) {
    func_151B51CC(arg0);
    func_15169824(arg0);
}
