#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D7760.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D7814.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D7958.s")

void func_151D79B4(void *arg0) {
    func_151D7D78(arg0);
}

void func_151D79D4(void *arg0) {
    func_151D79B4(arg0);
    func_1514933C(arg0);
}

void func_151D7A00(void *arg0) {
    func_151D79B4(arg0);
    func_15149368(arg0);
}

void func_151D7A2C(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    func_151494E0(&tmp, 0x3D);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D7A60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D7AE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D7B74.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D7CD4.s")

s32 func_151D7D20(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x40);
    u8 *temp_v1;
    temp_v1 = arg0 + 0x28;
    if (*(u16 *)(temp_v0 + 0x84) == 0) {
        temp_v1[5] &= ~1;
    }
    return 1;
}

s32 func_151D7D4C(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x40);
    u8 *temp_v1;
    temp_v1 = arg0 + 0x28;
    if (temp_v0[0xAD] != 0) {
        temp_v1[5] &= ~1;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D7D78.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D7DE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D7EDC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D7FE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D8280.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D8674.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D8CC8.s")

void func_151D8D14(u8 *arg0) {
    s32 **temp_v0 = *(s32 ***)(arg0 + 0x98);
    s32 *temp_v1 = *temp_v0;
    if (temp_v1 != NULL) {
        temp_v1[0x28 / 4] = 0;
    }
}

void func_151D8D30(void *arg0) {
    func_151D8D14(arg0);
    func_15147E64(arg0);
}

void func_151D8D5C(void *arg0) {
    func_151D8D14(arg0);
    func_15147E98(arg0);
}
