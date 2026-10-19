#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A7B30/func_1517A320.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A7B30/func_1517A550.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A7B30/func_1517A75C.s")

s32 func_1517A904(s32 arg0) {
    return arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A7B30/func_1517A910.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A7B30/func_1517ABB4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A7B30/func_1517ADBC.s")

s32 func_1517AEC8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_800DD880 = -1;
    if ((arg1 == 0xC) || (arg1 == 0x59)) {
        arg0 = func_1517A904(arg0);
    }
    return arg0;
}

extern s32 D_800DD5E0;
extern u8 D_800909C4[];
s32 func_1517AF18(s32 arg0, s32 arg1) {
    s32 sp30[6]; // fakematch: stack layout guess (frame 0x48, &sp30[1] at 0x34)
    if (arg1 != D_800DD5E0) {
        arg0 = func_15095380(arg0, D_800909C4, (u32)arg1 << 8, &sp30[1], 0, 0, 0, 2, 3);
        D_800DD5E0 = arg1;
    }
    return arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A7B30/func_1517AF90.s")

void func_1517B0EC(s32 arg0, s32 arg1, s16 arg2) {
    func_1510BD34(arg0, arg2);
}
