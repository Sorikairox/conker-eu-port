#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C2600.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C284C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C2CE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C3080.s")

s32 func_151C33FC(u8 *arg0, u8 *arg1) {
    if (arg0 == arg1) {
        return 0;
    }
    if (*(s32 *)arg0 == 0) {
        return 0;
    }
    if (arg0[4] == 0xFF) {
        return 0;
    }
    return 1;
}

s32 func_151C3444(u8 *arg0, u8 *arg1) {
    if (arg0 == arg1) {
        return 0;
    }
    if (*(s32 *)arg0 == 0) {
        return 0;
    }
    if (arg0[4] == 0xFF) {
        return 0;
    }
    if (arg0[0x127] == 0xFF) {
        return 0;
    }
    return 1;
}

void func_151C34A0(s32 arg0, s32 arg1, u8 *arg2, s32 arg3, s32 arg4, s32 arg5) {
    func_151D535C(arg0, arg1, arg3, arg4, arg5, *(s32 *)(arg2 + 0x1B4), arg2 + 0x170, arg2[0xC], arg2[1]);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C34F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C384C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C3C88.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C40BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C491C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C4990.s")

void func_151C4AC0(u8 *arg0, u8 *arg1, f32 arg2) {
    (*(f32 *)((u8 *)arg0 + 0x34)) += ((*(f32 *)((u8 *)arg1 + 4)) * arg2);
    (*(f32 *)((u8 *)arg0 + 0x38)) += ((*(f32 *)((u8 *)arg1 + 8)) * arg2);
    (*(f32 *)((u8 *)arg0 + 0x3C)) += ((*(f32 *)((u8 *)arg1 + 0xC)) * arg2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C4B0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C4BF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C4DD0.s")

void func_151C5060(u8 *arg0, s32 *arg1, u8 arg2) {
    u8 *p = arg0 + 0x110;
    if (arg2 == 0x2D) {
        if (arg1[0] == *(s32 *)(p + 0x90)) {
            *(s32 *)(p + 0x90) = arg1[1];
            p[0x94] = ((u8 *)arg1)[9];
            return;
        }
        if (arg1[1] == *(s32 *)(p + 0x90)) {
            *(s32 *)(p + 0x90) = arg1[0];
            p[0x94] = ((u8 *)arg1)[8];
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C50BC.s")
