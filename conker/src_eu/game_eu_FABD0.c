#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FABD0/func_150CD3C0.s")

#ifdef NON_MATCHING
void func_151436B4(f32, f32, f32, void *);

s32 func_150CD68C(u8 *arg0) {
    u8 *sp20;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f12;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 var_f16;
    f32 var_f16_2;
    f32 var_f18;
    f32 var_f18_2;
    f32 var_f18_3;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    u8 *temp_v1;
    u8 *temp_v1_2;
    u8 *temp_v1_3;

    temp_f2 = (*(f32 *)((u8 *)arg0 + 0x114));
    temp_f12 = (*(f32 *)((u8 *)arg0 + 0x11C));
    (*(f32 *)((u8 *)arg0 + 0x34)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x34)) + ((*(f32 *)((u8 *)arg0 + 0x110)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x38)) + ((temp_f2 * D_800BE9A4) + (0.5f * temp_f12 * D_800BE9A4 * D_800BE9A4)));
    (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + ((*(f32 *)((u8 *)arg0 + 0x118)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x114)) = (f32) (temp_f2 + (temp_f12 * D_800BE9A4));
    var_v0 = D_800BE9E4;
    if (var_v0 != 0) {
        temp_a1 = -(var_v0 & 3);
        temp_a0 = temp_a1 + var_v0;
        if (temp_a1 != 0) {
            temp_v1 = arg0 + 0x110;
            temp_f0 = (*(f32 *)((u8 *)temp_v1 + 0x10));
            var_v0 -= 1;
            var_f18 = (*(f32 *)((u8 *)temp_v1 + 0)) * temp_f0;
            var_f16 = (*(f32 *)((u8 *)temp_v1 + 8)) * temp_f0;
            if (temp_a0 != var_v0) {
                do {
                    (*(f32 *)((u8 *)temp_v1 + 0)) = var_f18;
                    (*(f32 *)((u8 *)temp_v1 + 8)) = var_f16;
                    var_f18 = (*(f32 *)((u8 *)temp_v1 + 0)) * temp_f0;
                    var_v0 -= 1;
                    var_f16 = (*(f32 *)((u8 *)temp_v1 + 8)) * temp_f0;
                } while (temp_a0 != var_v0);
            }
            (*(f32 *)((u8 *)temp_v1 + 0)) = var_f18;
            (*(f32 *)((u8 *)temp_v1 + 8)) = var_f16;
            if (var_v0 != 0) {
                goto block_5;
            }
        } else {
block_5:
            temp_v1_2 = arg0 + 0x110;
            temp_f0_2 = (*(f32 *)((u8 *)temp_v1_2 + 0x10));
            var_v0_2 = var_v0 - 4;
            var_f16_2 = (*(f32 *)((u8 *)temp_v1_2 + 0)) * temp_f0_2;
            if (var_v0_2 != 0) {
                do {
                    (*(f32 *)((u8 *)temp_v1_2 + 0)) = var_f16_2;
                    var_v0_2 -= 4;
                    (*(f32 *)((u8 *)temp_v1_2 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 8)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1_2 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 0)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1_2 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 8)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1_2 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 0)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1_2 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 8)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1_2 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 0)) * temp_f0_2);
                    var_f16_2 = (*(f32 *)((u8 *)temp_v1_2 + 0)) * temp_f0_2;
                    (*(f32 *)((u8 *)temp_v1_2 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 8)) * temp_f0_2);
                } while (var_v0_2 != 0);
            }
            (*(f32 *)((u8 *)temp_v1_2 + 0)) = var_f16_2;
            (*(f32 *)((u8 *)temp_v1_2 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 8)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1_2 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 0)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1_2 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 8)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1_2 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 0)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1_2 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 8)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1_2 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 0)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1_2 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 8)) * temp_f0_2);
        }
    }
    temp_v1_3 = arg0 + 0x110;
    if ((*(f32 *)((u8 *)temp_v1_3 + 4)) > 0.0f) {
        var_v0_3 = D_800BE9E4;
        if (var_v0_3 != 0) {
            temp_a1_2 = -(var_v0_3 & 3);
            temp_f0_3 = (*(f32 *)((u8 *)temp_v1_3 + 0x10));
            if (temp_a1_2 != 0) {
                temp_a0_2 = temp_a1_2 + var_v0_3;
                var_v0_3 -= 1;
                var_f18_2 = (*(f32 *)((u8 *)temp_v1_3 + 4)) * temp_f0_3;
                if (temp_a0_2 != var_v0_3) {
                    do {
                        (*(f32 *)((u8 *)temp_v1_3 + 4)) = var_f18_2;
                        var_v0_3 -= 1;
                        var_f18_2 = (*(f32 *)((u8 *)temp_v1_3 + 4)) * temp_f0_3;
                    } while (temp_a0_2 != var_v0_3);
                }
                (*(f32 *)((u8 *)temp_v1_3 + 4)) = var_f18_2;
                if (var_v0_3 != 0) {
                    goto block_14;
                }
            } else {
block_14:
                var_v0_4 = var_v0_3 - 4;
                var_f18_3 = (*(f32 *)((u8 *)temp_v1_3 + 4)) * temp_f0_3;
                if (var_v0_4 != 0) {
                    do {
                        (*(f32 *)((u8 *)temp_v1_3 + 4)) = var_f18_3;
                        var_v0_4 -= 4;
                        (*(f32 *)((u8 *)temp_v1_3 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1_3 + 4)) * temp_f0_3);
                        (*(f32 *)((u8 *)temp_v1_3 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1_3 + 4)) * temp_f0_3);
                        (*(f32 *)((u8 *)temp_v1_3 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1_3 + 4)) * temp_f0_3);
                        var_f18_3 = (*(f32 *)((u8 *)temp_v1_3 + 4)) * temp_f0_3;
                    } while (var_v0_4 != 0);
                }
                (*(f32 *)((u8 *)temp_v1_3 + 4)) = var_f18_3;
                (*(f32 *)((u8 *)temp_v1_3 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1_3 + 4)) * temp_f0_3);
                (*(f32 *)((u8 *)temp_v1_3 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1_3 + 4)) * temp_f0_3);
                (*(f32 *)((u8 *)temp_v1_3 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1_3 + 4)) * temp_f0_3);
            }
        }
    }
    temp_f2_2 = (*(f32 *)((u8 *)temp_v1_3 + 0x3C));
    if ((*(f32 *)((u8 *)temp_v1_3 + 4)) < temp_f2_2) {
        (*(f32 *)((u8 *)temp_v1_3 + 4)) = temp_f2_2;
    }
    if ((*(f32 *)((u8 *)temp_v1_3 + 4)) < 0.0f) {
        sp20 = temp_v1_3;
        func_151436B4((*(f32 *)((u8 *)temp_v1_3 + 0x2C)), ((*(f32 *)((u8 *)temp_v1_3 + 0x38)) * sinf((*(f32 *)((u8 *)temp_v1_3 + 0x30)))) + 1.5707964f, (*(f32 *)((u8 *)temp_v1_3 + 0x24)), arg0 + 0x4C);
        (*(f32 *)((u8 *)temp_v1_3 + 0x24)) = (f32) ((*(f32 *)((u8 *)temp_v1_3 + 0x24)) + ((*(f32 *)((u8 *)temp_v1_3 + 0x28)) * D_800BE9A4));
        (*(f32 *)((u8 *)temp_v1_3 + 0x30)) = (f32) ((*(f32 *)((u8 *)temp_v1_3 + 0x30)) + ((*(f32 *)((u8 *)temp_v1_3 + 0x34)) * D_800BE9A4));
        if ((*(f32 *)((u8 *)temp_v1_3 + 0x30)) > 6.2831855f) {
            do {
                (*(f32 *)((u8 *)temp_v1_3 + 0x30)) = (f32) ((*(f32 *)((u8 *)temp_v1_3 + 0x30)) - 6.2831855f);
            } while ((*(f32 *)((u8 *)temp_v1_3 + 0x30)) > 6.2831855f);
        }
        if ((*(f32 *)((u8 *)temp_v1_3 + 0x30)) < 0.0f) {
            do {
                (*(f32 *)((u8 *)temp_v1_3 + 0x30)) = (f32) ((*(f32 *)((u8 *)temp_v1_3 + 0x30)) + 6.2831855f);
            } while ((*(f32 *)((u8 *)temp_v1_3 + 0x30)) < 0.0f);
        }
    }
    (*(f32 *)((u8 *)arg0 + 0x40)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x40)) + (*(f32 *)((u8 *)temp_v1_3 + 0x14)));
    (*(f32 *)((u8 *)arg0 + 0x44)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x44)) + (*(f32 *)((u8 *)temp_v1_3 + 0x18)));
    (*(f32 *)((u8 *)arg0 + 0x48)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x48)) + (*(f32 *)((u8 *)temp_v1_3 + 0x1C)));
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FABD0/func_150CD68C.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FABD0/func_150CDAAC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FABD0/func_150CDD08.s")

void func_150CE07C(s32 arg0) {
    u8 *temp_v1;

    if ((arg0 >= 0) && (arg0 < 0x100) && (D_80088C10 != NULL)) {
        temp_v1 = D_80088C10 + 0x28;
        *(f32 *)(temp_v1 + 4) = arg0 * D_800A0B74;
    }
}
