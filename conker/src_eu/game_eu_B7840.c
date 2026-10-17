#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_15089BB0(void) {
    D_800D27D0 = NULL;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508A040.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508A41C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508A63C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508AB7C.s")

s32 func_1508B5F0(s32 arg0) {
    if (arg0 >= D_80090130) {
        return 0;
    }
    return *(s16 *)((u8 *)D_80090174 + arg0 * 12 + 0x70);
}

void func_1508B630(s32 arg0) {
    if (arg0 < D_80090130) {
        *(s16 *)((u8 *)D_80090174 + arg0 * 12 + 0x70) = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508B20C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508B704.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508B854.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508BE18.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508C07C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508C370.s")

s32 func_1508C5F0(s32 arg0) {
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508C600.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508CA14.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508CE28.s")

s32 func_1508CEE4(void) {
    D_800D27D0[0x1703]++;
    if (D_800D27D0[0x1703] >= D_80090130) {
        D_800D27D0[0x1703] = 0;
    }
    return D_800D27D0[0x1703];
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508CF34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508DCAC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508DE78.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508DF48.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508E080.s")

void func_1508EB24(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508EB2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508EBDC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508ECF8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508EFEC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508F054.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508F0B8.s")
