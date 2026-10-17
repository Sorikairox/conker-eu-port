#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A0A10.s")

s32 func_1514CBE8(f32, f32, s32, f32, s32, s32, s32, s32, s32, f32, s32, s32);
extern f32 D_800A90F0;

void func_151A10A8(u8 *arg0) {
    u8 *temp_s0;

    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x38)) + (D_800A90F0 * D_800BE9A4));
    if ((*(f32 *)((u8 *)arg0 + 0x38)) > 1.0f) {
        temp_s0 = arg0 + 0x28;
        do {
            func_1514CBE8((*(f32 *)temp_s0), (*(f32 *)((u8 *)temp_s0 + 4)), (*(s32 *)((u8 *)temp_s0 + 8)), (func_150ADA68() * 25.0f) + 15.0f, 0, 0xFF, 5, 4, (s32) (*(u8 *)((u8 *)temp_s0 + 0xC)), 0.0f, 0, (s32) (*(u8 *)((u8 *)arg0 + 0xC)));
            (*(f32 *)((u8 *)temp_s0 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0x10)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s0 + 0x10)) > 1.0f);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A11BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A13F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A14D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A15C0.s")

void func_151A177C(f32 arg0, f32 arg1, s32 arg2, s32 arg3) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A1794.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A1D0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A1E8C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A1F48.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A23E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A2498.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A2564.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A2A58.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A2B90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A2C9C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A2F10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A2FC4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A3084.s")

void func_151A3134(f32 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, f32 *arg5) {
    f32 temp_f0 = 1.0f - arg4;

    arg5[0] = arg0[0] * temp_f0;
    arg5[1] = arg0[1] * temp_f0;
    arg5[2] = arg0[2] * temp_f0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A3180.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A31D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A34BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A3700.s")
