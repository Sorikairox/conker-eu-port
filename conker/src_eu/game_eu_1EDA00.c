#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C01F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C0350.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C0434.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C0648.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C0894.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C0910.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C09C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C0AA8.s")

void func_151D58E4(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4, s32 arg5, s32 arg6);

void func_151C0B54(s32 arg0, u8 arg1, s32 arg2) {
    func_151D58E4(arg0, 800.0f, 2000.0f, 0.0005f, 5, arg1, arg2);
}

void func_151C0BA0(struct17 *arg0, u8 arg1, s32 arg2) {
    func_151D5404(arg0, 800.0f, 2000.0f, 0.0005f, 0xF, 0x14, (s32) arg1, arg2);
}

s32 func_150E892C(s32, s16, u8, s32);

void func_151C0BF4(s32 arg0, u8 arg1, s32 arg2) {
    func_150E892C(arg0, (s16) ((func_150ADA20() % 62U) + 0x78), arg1, arg2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C0698.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C16BC.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C1E10.s")

void func_151C0894();

void func_151C1EF0(s32 arg0, s32 arg1, s32 *arg2) {
    func_151C0894(arg0, arg1, *arg2, arg2 + 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C1F1C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C230C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C1FB8.s")
