#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_151482D4(s32, s32);

void func_150B42B0(void) {
    s8 sp24[4];

    func_151482D4(0, 5);
    sp24[0] = 0;
    func_151494E0((s32) sp24, 0x18U);
    sp24[0] = 2;
    func_151494E0((s32) sp24, 0x18U);
    sp24[0] = 4;
    func_151494E0((s32) sp24, 0x18U);
    sp24[0] = 1;
    func_151494E0((s32) sp24, 0x18U);
    sp24[0] = 3;
    func_151494E0((s32) sp24, 0x18U);
    sp24[0] = 5;
    func_151494E0((s32) sp24, 0x18U);
}

s32 func_1000FC18(u16, s16, s16, s16, s32);
void func_15147E64(u8 *);

void func_150B4354(u8 *arg0) {
    func_1000FC18(0x221, (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x10)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x14)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x18)), 0xFA0);
    func_15147E64(arg0);
}

s32 func_1000FC18(u16, s16, s16, s16, s32);
void func_15147E98(u8 *);

void func_150B43C8(u8 *arg0) {
    func_1000FC18(0x221, (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x10)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x14)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x18)), 0xFA0);
    func_15147E98(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E1AC0/func_150B443C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E1AC0/func_150B45C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E1AC0/func_150B4774.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E1AC0/func_150B4BF0.s")

void func_150B5540(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);

    arg0[0x30] = 0;
    *(u16 *)(arg0 + 0x1E) &= 0xFFFD;
    temp_v0[0x1C] |= 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E1AC0/func_150B5568.s")

void func_150B586C(u8 *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 5) {
        func_150B5540(arg0);
    }
}
