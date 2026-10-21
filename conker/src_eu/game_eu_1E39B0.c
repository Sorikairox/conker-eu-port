#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E39B0/func_151B61A0.s")

#ifdef NON_MATCHING
s32 func_15133E04(f32);

void func_151B6444(u8 *arg0) {
    u8 *sp38;
    f32 temp_f0;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 var_f12;
    u8 *temp_v0;

    (*(f32 *)((u8 *)arg0 + 0x170)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x170)) + (1.0020001f * D_800BE9A4));
    if ((*(f32 *)((u8 *)arg0 + 0x170)) > 29.9f) {
        (*(f32 *)((u8 *)arg0 + 0x170)) = 0.0f;
        func_10010F88(0x502, 0x5DC0U, 0, 0U, -1, (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x38)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x3C)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x40)), 0x64, 0x1F4);
    }
    temp_v0 = arg0 + 0x170;
    var_f12 = (*(f32 *)((u8 *)temp_v0 + 0));
    if (var_f12 < 12.566371f) {
        sp38 = temp_v0;
        temp_f0 = sinf(var_f12);
        var_f12 = (*(f32 *)((u8 *)temp_v0 + 4));
        temp_f2 = var_f12 + (temp_f0 * (0.05f * var_f12));
        (*(f32 *)((u8 *)arg0 + 0x1C)) = temp_f2;
        (*(f32 *)((u8 *)arg0 + 0x18)) = temp_f2;
    } else {
        temp_f2_2 = (*(f32 *)((u8 *)temp_v0 + 4));
        (*(f32 *)((u8 *)arg0 + 0x1C)) = temp_f2_2;
        (*(f32 *)((u8 *)arg0 + 0x18)) = temp_f2_2;
    }
    func_15133E04(var_f12);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E39B0/func_151B6444.s")
#endif
void func_151B657C(u8 *arg0) {
    s32 temp_v0 = *(s32 *)(arg0 + 0x88);
    if (temp_v0 != 0) {
        func_100111C8(temp_v0);
        *(s32 *)(arg0 + 0x88) = 0;
    }
}
