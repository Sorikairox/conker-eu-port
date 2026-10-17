#include <ultra64.h>
#include "functions.h"
#include "variables.h"


u8 *allocate_memory(s32, s32, s32, s32);

void func_1503BAB0(u8 *arg0) {
    (*(u8 **)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x11C)) = allocate_memory(0x50, 1, 0, 0);
    bzero((*(u8 **)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x11C)), 0x50);
    (*(f32 *)((u8 *)((*(u8 **)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x11C))) + 0x44)) = 30.0f;
    (*(s16 *)((u8 *)((*(u8 **)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x11C))) + 0x4C)) = (s16) (func_150ADA20() % 30U);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_692C0/func_1503B840.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_692C0/func_1503BC4C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_692C0/func_1503BCAC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_692C0/func_1503CE88.s")
