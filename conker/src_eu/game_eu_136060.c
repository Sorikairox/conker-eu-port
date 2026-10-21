#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_136060/func_eu_15108850.s")

#ifdef NON_MATCHING
extern f32 D_800A2830;
extern f32 D_800A2834;
s32 func_15108BD8(u8 *arg0, s32 arg1) {
    u8 *var_v0;
    f32 temp_f2;
    f32 temp_f0_3;
    f32 temp_f0_2;
    f32 temp_f0;
    u8 *sp18;

    temp_f0 = (*(f32 *)((u8 *)arg0 + 0xA8));
    var_v0 = arg0 + 0xA8;
    temp_f2 = (*(f32 *)((u8 *)arg0 + 0xAC)) - temp_f0;
    if ((temp_f0 < (*(f32 *)((u8 *)arg0 + 0xB4))) || (temp_f2 < (*(f32 *)((u8 *)var_v0 + 0xC)))) {
        (*(s32 *)((u8 *)arg0 + 0x1C)) = 0;
        var_v0 = arg0 + 0xA8;
    } else {
        temp_f0_2 = (*(f32 *)((u8 *)var_v0 + 8));
        if (((*(f32 *)((u8 *)var_v0 + 0)) < temp_f0_2) || (temp_f2 < temp_f0_2)) {
            (*(s32 *)((u8 *)arg0 + 0x1C)) = 0x10000;
        } else {
            (*(s32 *)((u8 *)arg0 + 0x1C)) = 0x20000;
        }
    }
    temp_f0_3 = (*(f32 *)((u8 *)var_v0 + 0x10));
    if (temp_f0_3 != 0.0f) {
        if ((temp_f0_3 < D_800A2830) || ((11.0f - temp_f0_3) < D_800A2830)) {
            (*(s32 *)((u8 *)arg0 + 0x1C)) = 0;
            (*(s8 *)((u8 *)arg0 + 0x74)) = -1;
        } else {
            (*(s8 *)((u8 *)arg0 + 0x74)) = 3;
        }
        (*(f32 *)((u8 *)var_v0 + 0x10)) = (f32) ((*(f32 *)((u8 *)var_v0 + 0x10)) - D_800BE9A4);
        if ((*(f32 *)((u8 *)var_v0 + 0x10)) < 0.0f) {
            (*(f32 *)((u8 *)var_v0 + 0x10)) = 0.0f;
            (*(s8 *)((u8 *)arg0 + 0x74)) = -1;
        }
        goto block_19;
    }
    (*(f32 *)((u8 *)var_v0 + 0)) = (f32) ((*(f32 *)((u8 *)var_v0 + 0)) - D_800BE9A4);
    if ((*(f32 *)((u8 *)var_v0 + 0)) < 0.0f) {
        return 0;
    }
    if ((*(s32 *)((u8 *)arg0 + 0x1C)) == 0x20000) {
        sp18 = var_v0;
        if (func_150ADA68() < D_800A2834) {
            (*(f32 *)((u8 *)sp18 + 0x10)) = 11.0f;
        }
    }
block_19:
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_136060/func_15108BD8.s")
#endif
void func_15108D7C(u8 *arg0, s32 arg1, u8 arg2) {
    struct212 *temp_v0 = (struct212 *)(arg0 + 0x28);

    if (arg2 == 0x2B) {
        temp_v0->unk8 |= 1;
    } else if (arg2 == 0x2C) {
        temp_v0->unk8 &= ~1;
    }
}
