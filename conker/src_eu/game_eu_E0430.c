#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E0430/func_150B2C20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E0430/func_150B3394.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E0430/func_150B3668.s")

#ifdef NON_MATCHING
s32 func_150B3B8C(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    f32 temp_f0;
    f32 temp_f2;
    s32 temp_t1;
    s32 temp_t7;
    s32 temp_t9;

    temp_f0 = (*(f32 *)((u8 *)arg0 + 0x48));
    (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x10)) + arg4);
    if ((*(f32 *)((u8 *)arg0 + 0x170)) < temp_f0) {
        temp_t7 = (*(s32 *)((u8 *)arg0 + 0x60)) & ~7;
        temp_t9 = temp_t7 & ~8;
        temp_t1 = temp_t9 & ~0x40;
        (*(s32 *)((u8 *)arg0 + 0x60)) = temp_t7;
        (*(s32 *)((u8 *)arg0 + 0x60)) = temp_t9;
        (*(s32 *)((u8 *)arg0 + 0x60)) = temp_t1;
        (*(s32 *)((u8 *)arg0 + 0x60)) = (s32) (temp_t1 & ~0x20);
        (*(f32 *)((u8 *)arg0 + 0x44)) = 0.0f;
        (*(f32 *)((u8 *)arg0 + 0x48)) = 0.0f;
        (*(f32 *)((u8 *)arg0 + 0x4C)) = 0.0f;
        if ((*(s16 *)((u8 *)arg0 + 0x64)) >= 0x21) {
            (*(s16 *)((u8 *)arg0 + 0x64)) = 0x20;
            return 1;
        }
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return 1;
    }
    temp_f2 = (*(f32 *)((u8 *)arg0 + 0x14));
    (*(f32 *)((u8 *)arg0 + 0x44)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x44)) * temp_f2);
    (*(f32 *)((u8 *)arg0 + 0x48)) = (f32) (-temp_f0 * temp_f2);
    (*(f32 *)((u8 *)arg0 + 0x4C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x4C)) * temp_f2);
    (*(f32 *)((u8 *)arg0 + 0x50)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x50)) * temp_f2);
    (*(f32 *)((u8 *)arg0 + 0x54)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x54)) * temp_f2);
    (*(f32 *)((u8 *)arg0 + 0x58)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x58)) * temp_f2);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E0430/func_150B3B8C.s")
#endif
s32 func_150B3C6C(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);
    s32 var_v1 = *(s16 *)(arg0 + 0x1C) * 16;

    if (var_v1 >= 0x100) {
        var_v1 = 0xFF;
    }
    if (var_v1 < temp_v0[0x1B]) {
        temp_v0[0x1B] = var_v1;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E0430/func_150B3CA8.s")
