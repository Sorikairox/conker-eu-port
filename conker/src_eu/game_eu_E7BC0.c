#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E7BC0/func_150BA3B0.s")

s32 func_150BA83C(u8 *arg0) {
    s16 temp_v0;

    temp_v0 = (*(s16 *)((u8 *)arg0 + 0x1C));
    if (temp_v0 < 0x40) {
        (*(s8 *)((u8 *)arg0 + 0x28)) = (s8) (temp_v0 * 4);
    }
    return 1;
}

s32 func_150BA85C(f32 *arg0) {
    arg0[0x114 / 4] += D_800A01FC * D_800BE9A4;
    arg0[0x34 / 4] += arg0[0x110 / 4] * D_800BE9A4;
    arg0[0x38 / 4] += arg0[0x114 / 4] * D_800BE9A4;
    arg0[0x3C / 4] += arg0[0x118 / 4] * D_800BE9A4;
    arg0[0x40 / 4] += arg0[0x11C / 4] * D_800BE9A4;
    arg0[0x44 / 4] += arg0[0x120 / 4] * D_800BE9A4;
    return 1;
}

#ifdef NON_MATCHING
/* P143 */
// effect_fade_by_height: update handler (D_8008A100 slot 2) of a sprite effect: alpha +0x5C = min(life +0x1C * 16,
// height above +0x124 (y +0x38 minus floor) * 4, 255). Returns 0 (effect ends) once it is below the floor, else 1.
s32 func_150BA904(u8 *fx) {
    f32 height = *(f32 *)(fx + 0x38) - *(f32 *)(fx + 0x124);
    s32 byLife;
    s32 byHeight;

    if (height < 0.0f) {
        return 0;
    }
    byLife = *(s16 *)(fx + 0x1C) << 4;
    if (byLife >= 0x100) {
        byLife = 0xFF;
    }
    byHeight = (s32)height << 2;
    if (byHeight >= 0x100) {
        byHeight = 0xFF;
    }
    fx[0x5C] = (byHeight < byLife) ? byHeight : byLife;
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E7BC0/func_150BA904.s")
#endif
