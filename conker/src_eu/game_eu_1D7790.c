#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151A9F80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AA054.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AA150.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AA250.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AA370.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AA470.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AA578.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AA64C.s")

void func_151AA720(s32 arg0) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AA72C.s")

void func_151AA780(void) {
    func_1519F970();
}

void func_151AA7A0(void) {
    func_1519F970();
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AA7C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AA814.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AA8BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AAA3C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AAB54.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AAC88.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AAFFC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AB06C.s")

void func_151AB100(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x80) + 0x58;
    *(s32 *)(temp_v0 + 0x14) = 0;
    func_151352EC(arg0);
}

void func_151AB128(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x80) + 0x58;
    *(s32 *)(temp_v0 + 0x14) = 0;
    func_1513530C(arg0);
}

s32 func_151AB150(u8 *arg0) {
    s32 ret = 1;
    if (arg0[0x84] == 0) {
        ret = 0;
    }
    arg0[0x84] = 0;
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AABC4.s")

s32 func_151AB36C(u8 *arg0) {
    u8 *temp_v0;
    s32 temp_v1;
    temp_v0 = *(u8 **)(arg0 + 0x98);
    temp_v1 = *(s16 *)(arg0 + 0x1C) << 4;
    if (temp_v1 >= 0x100) {
        temp_v1 = 0xFF;
    }
    if (temp_v1 < temp_v0[0x1B]) {
        temp_v0[0x1B] = temp_v1;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AB3A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AB640.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AB730.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AB774.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AB874.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AB954.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151ABC68.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151ABD38.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151ABD88.s")

void func_151ABDD8(void **arg0) {
    func_15141DA4(arg0[0x18 / 4], 0, 4);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151ABE04.s")

void func_151AB920(s32 arg0, s32 arg1) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AB930.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151ABF78.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AC304.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AC3B0.s")
