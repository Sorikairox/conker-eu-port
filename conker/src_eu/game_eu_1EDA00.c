#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C01F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C0350.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C0434.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C0648.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C0894.s")

s32 func_150E856C(f32, s32, s32, s32, s16, u8, u8, u8, u8, u8, u8, s32);

void func_151C0910(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    s32 pad;
    u32 sp40;
    f32 sp3C;

    sp3C = func_150ADA68();
    sp40 = func_150ADA20();
    func_150E856C((sp3C * 75.0f) + 75.0f, ((sp40 % 56U) + 0xC8) & 0xFF, arg0, arg1, (func_150ADA20() % 205U) + 0x12B, 1, 1, 0, 0, 0, (s32) arg2, 0);
}

void func_151C09C8(u8 *arg0, u8 arg1, s32 arg2) {
    s8 sp48[8];
    s32 sp3C[3];

    sp48[0] = 3;
    sp48[1] = -1;
    *(s16 *)(sp48 + 2) = (func_150ADA20() % 11U) + 0x14;
    sp48[4] = 0;
    sp3C[0] = *(f32 *)(arg0 + 0);
    sp3C[1] = *(f32 *)(arg0 + 4);
    sp3C[2] = *(f32 *)(arg0 + 8);
    func_151602C0(sp48, sp3C, (func_150ADA20() % 121U) + 0x3C, 0xFF, 0xFF, 0xFF, 0xFFU, 0U, 0, arg1, arg2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C0AA8.s")

void func_151D58E4(s32 arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5, s32 arg6);

void func_151C0B54(s32 arg0, u8 arg1, s32 arg2) {
    func_151D58E4(arg0, 800.0f, 2000.0f, 0.0005f, 5, arg1, arg2);
}

void func_151C0BA0(struct17 *arg0, u8 arg1, s32 arg2) {
    func_151D5404(arg0, 800.0f, 2000.0f, 0.0005f, 0xF, 0x14, (s32) arg1, arg2);
}

void func_150E892C(s32, s16, u8, s32);

void func_151C0BF4(s32 arg0, u8 arg1, s32 arg2) {
    func_150E892C(arg0, (s16) ((func_150ADA20() % 62U) + 0x78), arg1, arg2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C0698.s")

s32 func_151C16BC(u8 *arg0, s32 arg1, s32 *arg2, s32 arg3, s32 arg4, s32 arg5, s16 *arg6) {
    u8 *temp_v1;

    temp_v1 = (*(u8 **)((u8 *)arg0 + 0x18));
    if ((temp_v1 != NULL) && (*arg2 != 0)) {
        (*(s16 *)((u8 *)arg0 + 2)) = (s16) (s32) (*(f32 *)((u8 *)temp_v1 + 0x38));
        (*(s16 *)((u8 *)arg0 + 4)) = (s16) (s32) (*(f32 *)((u8 *)temp_v1 + 0x3C));
        (*(s16 *)((u8 *)arg0 + 6)) = (s16) (s32) (*(f32 *)((u8 *)temp_v1 + 0x40));
        return 0;
    }
    *arg6 = 0;
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C1730.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C1B20.s")

void func_151C1B20(void *arg0);
void func_15132AE0(void *arg0);
void func_15132B0C(void *arg0);

void func_151C1BAC(void *arg0) {
    func_151C1B20(arg0);
    func_15132AE0(arg0);
}

void func_151C1BD8(void *arg0) {
    func_151C1B20(arg0);
    func_15132B0C(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C1C04.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C1D48.s")

void func_151C1DC4(u8 *arg0, s32 *arg1, u8 arg2) {
    s32 *temp_v0 = (s32 *)(arg0 + 0x170);

    if (arg2 == 0x2D) {
        if (arg1[0] == temp_v0[0x1B]) {
            temp_v0[0x1B] = arg1[1];
        } else if (arg1[1] == temp_v0[0x1B]) {
            temp_v0[0x1B] = arg1[0];
        }
    }
}

void func_151C1E10(u8 *arg0, u8 arg1, s32 arg2) {
    s8 sp48[8];
    s32 sp3C[3];

    sp48[0] = 3;
    sp48[1] = -1;
    *(s16 *)(sp48 + 2) = (func_150ADA20() % 5U) + 5;
    sp48[4] = 0;
    sp3C[0] = *(f32 *)(arg0 + 0);
    sp3C[1] = *(f32 *)(arg0 + 4);
    sp3C[2] = *(f32 *)(arg0 + 8);
    func_151602C0(sp48, sp3C, (func_150ADA20() % 11U) + 5, 0xFF, 0xFF, 0xFF, 0xFFU, 0U, 0, arg1, arg2);
}

s32 func_151C0894();

void func_151C1EF0(s32 arg0, s32 arg1, s32 *arg2) {
    func_151C0894(arg0, arg1, *arg2, arg2 + 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C1F1C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C230C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C1FB8.s")
