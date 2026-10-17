#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CC6F0/func_1519EEE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CC6F0/func_1519EF74.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CC6F0/func_1519EFE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CC6F0/func_1519F0FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CC6F0/func_1519F294.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CC6F0/func_1519F2F4.s")

s32 func_1519F474(u8 *arg0) {
    u8 *temp_v1;

    temp_v1 = (*(u8 **)((u8 *)arg0 + 0x110));
    (*(f32 *)((u8 *)arg0 + 0x2C)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x18)) * 10.0f);
    (*(f32 *)((u8 *)arg0 + 0x30)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x1C)) * 10.0f);
    (*(f32 *)((u8 *)arg0 + 0x40)) = (f32) (*(f32 *)((u8 *)temp_v1 + 0xC));
    (*(f32 *)((u8 *)arg0 + 0x44)) = (f32) (*(f32 *)((u8 *)temp_v1 + 0x10));
    (*(f32 *)((u8 *)arg0 + 0x48)) = (f32) (*(f32 *)((u8 *)temp_v1 + 0x14));
    (*(f32 *)((u8 *)arg0 + 0x34)) = (f32) (*(f32 *)temp_v1);
    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) (*(f32 *)((u8 *)temp_v1 + 4));
    (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) (*(f32 *)((u8 *)temp_v1 + 8));
    return 1;
}
