#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
extern u8 D_800DE284[];
#endif


#ifdef NON_MATCHING
s32 func_1518354C(struct127 *, s32, s32);
extern s32 D_8008D3F0;
extern s32 D_8008D407;
extern s32 D_800DE290;

void func_15182D40(void) {
    struct {
        s32 uA4;
    } sp;
    u8 *sp90;
    f32 *temp_v0_3;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f20;
    f32 temp_f22;
    s32 *var_s2;
    s32 *var_s2_2;
    s32 *var_s3;
    s32 temp_v0;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s4;
    s32 var_s5;
    s32 var_s6;
    s32 var_s7;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    struct127 *temp_s0;
    struct127 *var_s0;
    u8 temp_v0_8;
    u8 temp_v1_2;
    u8 *temp_v0_2;
    u8 *temp_v0_4;
    u8 *temp_v0_5;
    u8 *temp_v0_6;
    u8 *temp_v0_7;
    u8 *temp_v1;
    u8 *temp_v1_3;

    var_s7 = 0;
    if ((s32) D_800DDE50 > 0) {
        var_s3 = &D_800DE290;
        sp90 = D_800DE284;
        do {
            var_s5 = 0;
            var_s6 = 0;
            temp_v1 = ((s32 *)((u8 *)&D_8008D3F0 + (*sp90 * 0x18)));
            temp_f20 = (*(f32 *)((u8 *)temp_v1 + 0));
            temp_f22 = (*(f32 *)((u8 *)temp_v1 + 4));
            var_s4 = 1;
            var_s2 = &sp.uA4;
loop_3:
            *var_s2 = 0;
            var_s0 = D_800CC2D0;
            var_s1 = 0;
loop_4:
            if (var_s0->interaction_state != 0) {
                temp_v0 = func_1518354C(var_s0, var_s4, var_s7);
                var_v1 = temp_v0;
                if (var_s0->unk84.uh == 0x4B) {
                    var_v1 = temp_v0 * 2;
                }
                *var_s2 += var_v1;
                if (var_v1 != 0) {
                    var_s5 = var_s1 + 1;
                }
            }
            var_s1 += 1;
            var_s0 = (struct127 *)((u8 *)var_s0 + (0x32C));
            if (var_s1 != 4) {
                goto loop_4;
            }
            var_s4 += 1;
            var_s2 = (s32 *)((u8 *)var_s2 + (4));
            if (var_s4 != 0x27) {
                goto loop_3;
            }
            var_s1_2 = 0;
loop_12:
            var_s2_2 = &sp.uA4;
            var_v1_2 = 0xC;
loop_13:
            temp_v0_2 = *var_s3 + var_v1_2;
            temp_f0 = (*(f32 *)((u8 *)temp_v0_2 + 8));
            (*(f32 *)((u8 *)temp_v0_2 + 0)) = (f32) ((f32) ((s32) ((*(f32 *)((u8 *)temp_v0_2 + -4)) - temp_f0) + (s32) ((*(f32 *)((u8 *)temp_v0_2 + 0x14)) - temp_f0)) + temp_f20);
            temp_v0_3 = *var_s3 + var_v1_2;
            *temp_v0_3 += (f32) *var_s2_2;
            temp_v0_4 = *var_s3 + var_v1_2;
            (*(f32 *)((u8 *)temp_v0_4 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v0_4 + 4)) + (*(f32 *)((u8 *)temp_v0_4 + 0)));
            temp_v0_5 = *var_s3 + var_v1_2;
            (*(f32 *)((u8 *)temp_v0_5 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v0_5 + 4)) * temp_f22);
            temp_v0_6 = *var_s3 + var_v1_2;
            temp_f0_2 = (*(f32 *)((u8 *)temp_v0_6 + 4));
            var_v1_2 += 0xC;
            if (fabsf(temp_f0_2) < 1.0f) {
                (*(f32 *)((u8 *)temp_v0_6 + 4)) = 0.0f;
            }
            var_s2_2 = (s32 *)((u8 *)var_s2_2 + (4));
            if (var_v1_2 < 0x1D4) {
                goto loop_13;
            }
            var_v1_3 = 0xC;
loop_17:
            temp_v0_7 = *var_s3 + var_v1_3;
            (*(f32 *)((u8 *)temp_v0_7 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v0_7 + 8)) + (*(f32 *)((u8 *)temp_v0_7 + 4)));
            if ((var_s5 != 0) && ((*(f32 *)((u8 *)((*var_s3 + var_v1_3)) + 4)) < -30.0f)) {
                var_s6 = 1;
            }
            var_v1_3 += 0xC;
            if (var_v1_3 != 0x1D4) {
                goto loop_17;
            }
            if (var_s5 == 0) {
                *(s32 *)((u8 *)&D_8008D407 + (*sp90 * 0x18)) = 0;
            }
            if ((var_s6 != 0) && (*(s32 *)((u8 *)&D_8008D407 + (*sp90 * 0x18)) == 0)) {
                temp_s0 = &D_800CC2D0[var_s5];
                temp_v1_2 = *sp90;
                *(s32 *)((u8 *)&D_8008D407 + (temp_v1_2 * 0x18)) = (func_150ADA20() & 0x3F) + 0x96;
                if ((temp_v1_2 == 2) || (temp_v1_2 == 3)) {
                    func_10010F88((func_150ADA20() & 8) + 0x507, 0x5DC0U, 0, 0U, 0, (s16) (s32) (*(f32 *)((u8 *)temp_s0 + -0x318)), (s16) (s32) (*(f32 *)((u8 *)temp_s0 + -0x314)), (s16) (s32) (*(f32 *)((u8 *)temp_s0 + -0x310)), 0x12C, 0x320);
                } else {
                    func_10010F88(0xF, 0x5DC0U, 0, 0U, 0, (s16) (s32) (*(f32 *)((u8 *)temp_s0 + -0x318)), (s16) (s32) (*(f32 *)((u8 *)temp_s0 + -0x314)), (s16) (s32) (*(f32 *)((u8 *)temp_s0 + -0x310)), 0x12C, 0x320);
                }
            } else if (var_s6 == 0) {
                temp_v1_3 = ((s32 *)((u8 *)&D_8008D3F0 + (*sp90 * 0x18)));
                temp_v0_8 = (*(u8 *)((u8 *)temp_v1_3 + 0x17));
                if ((temp_v0_8 != 0) && (temp_v0_8 != 0)) {
                    (*(u8 *)((u8 *)temp_v1_3 + 0x17)) = (u8) (temp_v0_8 - D_800BE9E4);
                }
            }
            var_s1_2 += 1;
            if (var_s1_2 != 3) {
                goto loop_12;
            }
            var_s7 += 1;
            sp90 += 1;
            var_s3 = (s32 *)((u8 *)var_s3 + (4));
        } while (var_s7 < (s32) D_800DDE50);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B0550/func_15182D40.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B0550/func_151831CC.s")

extern u8 D_800DE284[];
extern f32 D_8008D3F8[][6];

f32 func_151834C8(s32 arg0, s32 arg1) {
    f32 x;

    x = D_8008D3F8[D_800DE284[arg1]][0] * (f32)(arg0 * 40);
    if (x < 0.0f) {
        x = 0.0f;
    } else if (x > 39.0f) {
        x = 39.0f;
    }
    return x;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B0550/func_1518354C.s")
