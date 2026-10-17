#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_15179420(void) {
    D_800DD864 = 0;
    D_800DD876 = 0;
    D_800DD444 = 600;
    D_800DD862 = 0xF0;
    D_800DD863 = 0x14;
    D_800DD866 = 0;
    D_800DD870 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A6C30/func_1517946C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A6C30/func_15179008.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A6C30/func_15179A38.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A6C30/func_15179B70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A6C30/func_15179D20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A6C30/func_1517A028.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A6C30/func_1517A084.s")

void func_1517A220(u8 *arg0) {
    f32 temp_f12;
    f32 temp_f2;
    f32 dist;

    temp_f2 = (f32) *(s16 *)(arg0 + 0xA0) - D_800DBFF0->unk300;
    temp_f12 = (f32) *(s16 *)(arg0 + 0x9C) - D_800DBFF0->unk2F8;
    dist = sqrtf((temp_f2 * temp_f2) + (temp_f12 * temp_f12));
    *(u8 *)(arg0 + 0xB4) = (s8)(u32)(255.0f - ((160.0f * dist) / 1000.0f));
}
