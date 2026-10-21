#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
Gfx *func_150417F8(Gfx *gdl, s32 x, s32 y, s32 idx);
s32 func_15041770(u8 arg0);
#endif


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6EDC0/func_150415B0.s")

#ifdef NON_MATCHING
Gfx *func_150416EC(Gfx *arg0, s32 arg1, s32 arg2, u8 *arg3) {
    Gfx *temp_v0;
    Gfx *var_s2;
    s32 var_s1;
    u8 *var_s0;
    u8 temp_t6;
    u8 var_a0;

    var_s2 = arg0;
    temp_t6 = *arg3;
    var_s0 = arg3;
    var_s1 = arg1;
    var_a0 = temp_t6 & 0xFF;
    if (temp_t6 != 0) {
        do {
            temp_v0 = func_150417F8(var_s2, var_s1, arg2, func_15041770(var_a0));
            var_a0 = (*(u8 *)((u8 *)var_s0 + 1));
            var_s2 = temp_v0;
            var_s0 += 1;
            var_s1 += 8;
        } while (var_a0 != 0);
    }
    return var_s2;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6EDC0/func_150416EC.s")
#endif
extern u8 D_80084C60[];
s32 func_15041770(u8 arg0) {
    s32 i;
    for (i = 0; i < 0x50; i++) {
        if (arg0 == D_80084C60[i]) {
            return i;
        }
    }
    return i;
}

Gfx *func_150417F8(Gfx *gdl, s32 x, s32 y, s32 idx) {
    s32 col = idx % 8; // fakematch: locals keep the unfolded mod/sub/div
    s32 s = col * 8;
    s32 row = (idx - col) / 8;

    gSPTextureRectangle(gdl++, x << 2, y << 2, (x + 8) << 2, (y + 12) << 2, 0, s * 32, (row * 3) << 7, 0x400, 0x400);
    return gdl;
}

void func_150418D0(s32 arg0, s32 *arg1, s32 *arg2, f32 *arg3, s32 *arg4, f32 *arg5) {
    if ((arg0 >= 0xA8) && (arg0 < 0x100)) {
        *arg5 = 1.0f;
        switch (arg0) {
        case 0xA8:
        case 0xA9:
            *arg1 = 0x20;
            *arg2 = 0x12;
            *arg3 = 3.1f;
            *arg4 = 1;
            return;
        case 0xAA:
        case 0xAB:
        case 0xAC:
        case 0xAD:
            *arg1 = 0x20;
            *arg2 = 0x1B;
            *arg3 = 2.0f;
            *arg4 = 1;
            *arg5 = 0.603f;
            return;
        case 0xAE:
            *arg1 = 0x10;
            *arg2 = 0x11;
            *arg3 = -1.6f;
            *arg4 = 1;
            return;
        case 0xAF:
        case 0xB0:
            *arg1 = 0x2E;
            *arg2 = 0x10;
            *arg3 = 2.0f;
            *arg4 = 1;
            return;
        case 0xB6:
        case 0xB7:
        case 0xB8:
        case 0xB9:
            *arg1 = 0x10;
            *arg2 = 0xC;
            *arg3 = 2.0f;
            *arg4 = 0;
            return;
        case 0xBA:
            *arg4 = 0;
            *arg3 = 0.2f;
            *arg1 = 0x37;
            *arg2 = 0xC;
            return;
        case 0xB1:
            *arg1 = 0x26;
            *arg2 = 0x18;
            *arg3 = 2.0f;
            *arg4 = 1;
            *arg5 = 0.726f;
            return;
        default:
            *arg1 = 0xC;
            *arg2 = 0x10;
            *arg3 = 2.0f;
            *arg4 = 0;
            return;
        }
    } else {
        *arg3 = 0.0f;
        *arg1 = 0;
        *arg2 = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6EDC0/func_15041A9C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6EDC0/func_15042BC4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6EDC0/func_15042F30.s")
