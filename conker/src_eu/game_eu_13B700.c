#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
u8 *func_1510DEF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp28;
    s32 sp20;
    s32 temp_t0;
    s32 var_a0;
    s32 var_a0_2;
    u8 *temp_v0;
    u8 *var_v1;
    u8 *var_v1_2;

    temp_t0 = arg3 & 1;
    sp28 = 0x128;
    if (temp_t0 != 0) {
        sp28 = 0x13A;
    }
    sp20 = temp_t0;
    temp_v0 = func_15167A68(0x4B, 0, sp28, 1, 0xFFU, 1U);
    if (temp_v0 != NULL) {
        var_a0 = 0;
        var_v1 = temp_v0;
        do {
            var_a0 += 1;
            var_v1 += 0x40;
            (*(s16 *)((u8 *)var_v1 + 0x56)) = 0;
            (*(s16 *)((u8 *)var_v1 + 0x58)) = 0x800;
            (*(s16 *)((u8 *)var_v1 + 0x5A)) = 0;
            (*(s16 *)((u8 *)var_v1 + 0x66)) = 0;
            (*(s16 *)((u8 *)var_v1 + 0x68)) = 0;
            (*(s16 *)((u8 *)var_v1 + 0x6A)) = 0;
            (*(s16 *)((u8 *)var_v1 + 0x76)) = 0;
            (*(s16 *)((u8 *)var_v1 + 0x78)) = 0;
            (*(s16 *)((u8 *)var_v1 + 0x7A)) = 0x800;
            (*(s16 *)((u8 *)var_v1 + 0x86)) = 0;
            (*(s16 *)((u8 *)var_v1 + 0x88)) = 0x800;
            (*(s16 *)((u8 *)var_v1 + 0x8A)) = 0x800;
        } while (var_a0 < 2);
        var_a0_2 = 1;
        (*(s8 *)((u8 *)temp_v0 + 0x120)) = (s8) arg0;
        var_v1_2 = temp_v0 + 2;
        (*(s32 *)((u8 *)temp_v0 + 0x110)) = arg1;
        (*(s8 *)((u8 *)temp_v0 + 0x121)) = (s8) arg2;
        (*(s8 *)((u8 *)temp_v0 + 0x124)) = (s8) arg4;
        if (temp_t0 != 0) {
            (*(s16 *)((u8 *)temp_v0 + 0x128)) = 0x7FFF;
            do {
                var_a0_2 += 4;
                (*(s16 *)((u8 *)var_v1_2 + 0x12A)) = 0x7FFF;
                (*(s16 *)((u8 *)var_v1_2 + 0x12C)) = 0x7FFF;
                (*(s16 *)((u8 *)var_v1_2 + 0x12E)) = 0x7FFF;
                var_v1_2 += 8;
                (*(s16 *)((u8 *)var_v1_2 + 0x120)) = 0x7FFF;
            } while (var_a0_2 != 9);
        }
    }
    return temp_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13B700/func_1510DEF0.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13B700/func_1510E004.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13B700/func_1510E6A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13B700/func_1510E908.s")

Gfx *func_1510EBB4(Gfx *gdl, s32 arg1, s32 arg2) {
    gSPMatrix(gdl++, D_80089810, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    return gdl;
}
