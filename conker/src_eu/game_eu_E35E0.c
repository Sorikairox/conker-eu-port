#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern s32 D_800CC76A;

u8 *func_150B5DD0(u8 *arg0, s32 arg1) {
    if (D_800C35EA == 1) {
        return arg0;
    }
    (*(s16 *)arg0) = 0x1A;
    (*(u16 *)((u8 *)arg0 + 2)) = *(u16 *)((u8 *)&D_800CC76A + (arg1 * 0x32C));
    return arg0 + 4;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E35E0/func_150B5E30.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E35E0/func_150B5F1C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E35E0/func_150B5C38.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E35E0/func_150B6314.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E35E0/func_150B64E0.s")

void func_150B60E0(u8 *arg0, u8 *arg1) {
    func_15143134(D_800A0000, arg1, (*(s32 *)((u8 *)arg0 + 0x1D4)) + 0x140);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E35E0/func_150B65F0.s")

void func_150B6930(struct102 *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 0x4A) {
        func_1516972C(arg0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E35E0/func_150B696C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E35E0/func_150B6BBC.s")

s32 func_15182BE0(u8, u8, u8, s32, s16, u8, u8, s32);

void func_150B6C34(u8 arg0, s32 arg1) {
    s32 pad;
    u32 sp28;

    sp28 = func_150ADA20();
    func_15182BE0(0xCC, 0xCC, 0xFF, ((sp28 % 56U) + 0xC8) & 0xFF, (func_150ADA20() % 11U) + 0xF, 0, (s32) arg0, arg1);
}
