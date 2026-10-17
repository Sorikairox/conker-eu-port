#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_15192E90(u8 *arg0) {
    struct260 *temp_v0;
    struct {
        u8 *unk0;
        u8 unk4;
        f32 unk8;
    } tmp;

    if (arg0 == NULL) {
        return;
    }
    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = 0.0f;
    temp_v0 = func_151491F4(0x23, -1, 0x14, 1, 0x10, 0xC, 255, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0xC);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C06A0/func_15192F14.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C06A0/func_151932B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C06A0/func_15193360.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C06A0/func_151937A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C06A0/func_15193850.s")
