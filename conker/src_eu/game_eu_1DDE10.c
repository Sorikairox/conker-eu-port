#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DDE10/func_151B0600.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DDE10/func_151B01B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DDE10/func_151B03B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DDE10/func_151B09BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DDE10/func_151B1138.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DDE10/func_151B173C.s")

s32 func_151B1A28(u8 *arg0) {
    s16 temp_v0 = *(s16 *)(arg0 + 0x1C);
    s32 temp_v1;

    if (temp_v0 < 32) {
        temp_v1 = temp_v0 << 3;
        if (temp_v1 < arg0[0x5C]) {
            arg0[0x5C] = temp_v1;
        }
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DDE10/func_151B1A5C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DDE10/func_151B1DD8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DDE10/func_151B1EC8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DDE10/func_151B1F54.s")

void func_151B2008(void *arg0) {
    func_151B1EC8(arg0);
    func_1514933C(arg0);
}

void func_151B2034(void *arg0) {
    func_151B1EC8(arg0);
    func_15149368(arg0);
}

void func_151B2060(u8 *arg0) {
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
    temp_v0 = func_151491F4(0x3C, -1, 0x15, 1, 0x11, 0xC, 255, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0xC);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DDE10/func_151B20E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DDE10/func_151B255C.s")
