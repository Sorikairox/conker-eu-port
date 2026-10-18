#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_100410/func_150D2C00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_100410/func_150D2C9C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_100410/func_150D2E34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_100410/func_150D327C.s")

s32 func_150D368C(u8 *arg0) {
    u8 *temp_s0;

    *(f32 *)(arg0 + 0x128) = (*(f32 *)(arg0 + 0x130) * D_800BE9A4) + *(f32 *)(arg0 + 0x128);
    *(f32 *)(arg0 + 0x12C) = (*(f32 *)(arg0 + 0x134) * D_800BE9A4) + *(f32 *)(arg0 + 0x12C);
    temp_s0 = arg0 + 0x110;
    (*(f32 *)((u8 *)temp_s0 + 0x18)) = func_15144B68((*(f32 *)((u8 *)arg0 + 0x128)));
    (*(f32 *)((u8 *)temp_s0 + 0x1C)) = func_15144B68((*(f32 *)((u8 *)temp_s0 + 0x1C)));
    *(f32 *)(temp_s0 + 0) = *(f32 *)(temp_s0 + 8) + (*(f32 *)(temp_s0 + 0x10) * sinf(*(f32 *)(temp_s0 + 0x18)));
    *(f32 *)(temp_s0 + 4) = *(f32 *)(temp_s0 + 0xC) + (*(f32 *)(temp_s0 + 0x14) * sinf(*(f32 *)(temp_s0 + 0x1C)));
    (*(f32 *)((u8 *)temp_s0 + 0x28)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0x28)) - D_800BE9A4);
    (*(s8 *)((u8 *)arg0 + 0x5C)) = (s8) (u32) ((*(f32 *)((u8 *)temp_s0 + 0x28)) * (*(f32 *)((u8 *)temp_s0 + 0x2C)));
    if ((*(f32 *)((u8 *)temp_s0 + 0x28)) > 0.0f) {
        return 1;
    }
    return 0;
}

void func_150D380C(u8 *arg0, u8 *arg1, u8 arg2) {
    u8 *p;
    if (arg2 == 0x34) {
        p = (*(u8 **)&arg0) + 0x28;
        if (arg1[0] == p[0x51]) {
            func_150D2C9C(*(s32 *)p, p + 0x10, arg0[0xC], arg0[1]);
        }
    }
}
