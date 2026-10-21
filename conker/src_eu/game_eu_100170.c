#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
void func_150D2960(u8 *arg0) {
    f32 sp24;
    f32 sp20;
    u8 *temp_s0;

    sp20 = sinf((*(f32 *)((u8 *)arg0 + 0x40)));
    temp_s0 = arg0 + 0x28;
    sp24 = sinf((*(f32 *)((u8 *)arg0 + 0x44)));
    func_1515D4D4((u32) ((sp20 * (*(f32 *)((u8 *)temp_s0 + 0xC))) + (*(f32 *)((u8 *)temp_s0 + 0))) & 0xFF, (u32) ((sp24 * (*(f32 *)((u8 *)temp_s0 + 0x10))) + (*(f32 *)((u8 *)temp_s0 + 4))) & 0xFF, (u32) ((sinf((*(f32 *)((u8 *)temp_s0 + 0x20))) * (*(f32 *)((u8 *)temp_s0 + 0x14))) + (*(f32 *)((u8 *)temp_s0 + 8))) & 0xFF, 0U);
    (*(f32 *)((u8 *)temp_s0 + 0x18)) = func_15144B68((*(f32 *)((u8 *)temp_s0 + 0x18)) + ((*(f32 *)((u8 *)temp_s0 + 0x24)) * D_800BE9A4));
    (*(f32 *)((u8 *)temp_s0 + 0x1C)) = func_15144B68((*(f32 *)((u8 *)temp_s0 + 0x1C)) + ((*(f32 *)((u8 *)temp_s0 + 0x28)) * D_800BE9A4));
    (*(f32 *)((u8 *)temp_s0 + 0x20)) = func_15144B68((*(f32 *)((u8 *)temp_s0 + 0x20)) + ((*(f32 *)((u8 *)temp_s0 + 0x2C)) * D_800BE9A4));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_100170/func_150D2960.s")
#endif