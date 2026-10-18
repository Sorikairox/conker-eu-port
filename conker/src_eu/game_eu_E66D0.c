#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E66D0/func_150B8EC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E66D0/func_150B9424.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E66D0/func_150B9A40.s")

s32 func_150B9ADC(u8 *arg0) {
    s16 temp_v0 = *(s16 *)(arg0 + 0x1C);
    if (temp_v0 < 32) {
        arg0[0x5C] = temp_v0 * 8;
    }
    return 1;
}

s32 func_150B9AFC(struct102 *arg0) {
    s16 temp_v0 = arg0->unk1C;
    if (temp_v0 < 64) {
        arg0->unk28 = temp_v0 * 4;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E66D0/func_150B9B1C.s")

s32 func_15142600(s32, s32, s32, s32, f32, f32, f32, f32, f32, f32, f32, f32);
s32 func_150BA1F4(s32 arg0, u8 *arg1) {
    func_15142600(arg0, *(s32 *)(arg1 + 0x18), *(s32 *)(arg1 + 0x1C), *(s32 *)(arg1 + 0x2C), *(f32 *)(arg1 + 0x30), *(f32 *)(arg1 + 0x34), *(f32 *)(arg1 + 0x38), *(f32 *)(arg1 + 0x3C), *(f32 *)(arg1 + 0x40), *(f32 *)(arg1 + 0x20), *(f32 *)(arg1 + 0x24), *(f32 *)(arg1 + 0x28));
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E66D0/func_150BA26C.s")
