#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1231B0/func_150F59A0.s")

void func_150F5B10(u8 *arg0) {
    s32 temp_v0 = 0x1000 - *(s16 *)(arg0 + 0x24) * 4;

    *(s16 *)(arg0 + 0x38) = temp_v0;
    *(s16 *)(arg0 + 0x3A) = *(s16 *)(arg0 + 0x38);
    func_150F5B48(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1231B0/func_150F5B48.s")

void func_150F5C0C(s32 arg0) {
    func_15179008(0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1231B0/func_150F5C30.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1231B0/func_150F5FD4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1231B0/func_150F6188.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1231B0/func_150F6218.s")

void func_150F66B8(u8 *arg0, s32 arg1, u8 arg2) {
    func_15149514(arg1, arg2, (s32)(arg0 + 0x28), (s32)(arg0 + 0x2C), (s32)arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1231B0/func_150F66F8.s")

void func_150F689C(u8 *arg0) {
    struct102 *temp_a0;

    if (*(s32 *)(arg0 + 0x30) != 0) {
        func_1516972C(*(struct102 **)(arg0 + 0x30));
    }
    temp_a0 = *(struct102 **)(arg0 + 0x34);
    if (temp_a0 != NULL) {
        func_1516972C(temp_a0);
    }
}

void func_150F68E8(void *arg0) {
    func_150F689C(arg0);
    func_1514933C(arg0);
}

void func_150F6914(void *arg0) {
    func_150F689C(arg0);
    func_15149368(arg0);
}

void func_150F6940(u8 *arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, (s32)(arg0 + 0x28), (s32)(arg0 + 0x2C), (s32)arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1231B0/func_150F6980.s")

void func_150F69A0(void *arg0) {
    func_150F6980(arg0);
    func_1513CA6C(arg0);
}

void func_150F69CC(void *arg0) {
    func_150F6980(arg0);
    func_1513CAA0(arg0);
}

void func_150F69F8(s32 arg0) {
}

void func_150F6A04(void *arg0) {
    func_150F69F8(arg0);
    func_151411A4(arg0);
}

void func_150F6A30(void *arg0) {
    func_150F69F8(arg0);
    func_151411C4(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1231B0/func_150F6A5C.s")

void func_150F6DD0(u8 *arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, (s32)(arg0 + 0x28), (s32)(arg0 + 0x2C), (s32)arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1231B0/func_150F6E10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1231B0/func_150F6EDC.s")
