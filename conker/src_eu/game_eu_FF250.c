#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 func_1509BE40(s32, s32, s32, s32, s32, s32, s32, s32);

void func_150D1A40(struct108 *arg0) {
    f32 sp34;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 var_f0;
    s32 temp_t2;
    s32 var_v0;

    if (arg0->unk2C != 0x40) {
        if (arg0->unk5F0 & 0x80) {
            var_f0 = 0.0f;
            temp_f2 = arg0->unk3D0->xz_velocity;
            if (temp_f2 < 0.0f) {

            } else if (temp_f2 > 170.0f) {
                var_f0 = 170.0f;
            } else {
                var_f0 = temp_f2;
            }
            temp_f2_2 = var_f0 * 0.005882353f;
            sp34 = temp_f2_2;
            if (func_15123934(arg0, 8, 0, arg0->unk134, 3) != 0) {
                temp_t2 = arg0->unk84 | 0x01300080;
                arg0->unk84 = temp_t2;
                arg0->unk84 = temp_t2 & ~6;
                arg0->unk1B4 = 1;
                arg0->unk1E0 = 2;
            }
            temp_f0 = (34.0f * temp_f2_2) + 75.0f;
            arg0->unk374 = (-194.0f * temp_f2_2) + 280.0f;
            arg0->unk348 = temp_f0;
            arg0->unk34C = temp_f0;
            if (D_800BE9F0 == 0x32) {
                sp34 = temp_f2_2;
                var_v0 = func_1509BE40(4, arg0->unk23D | 0x2000, 0xAC, 0x4027, 0x4035, 0x4036, 0x4037, 0);
            } else {
                sp34 = temp_f2_2;
                var_v0 = func_1509BE40(5, arg0->unk23D | 0x2000, 0xAC, 0x400A, 0x400B, 0x400C, 0x400D, 0x400E);
            }
            if (var_v0 != 0) {
                arg0->unk84 |= 0x10000000;
            } else {
                if (arg0->unk3D0->unk81 != 0) {
                    arg0->unk190 = -30.0f;
                } else {
                    arg0->unk190 = 123.0f;
                }
                arg0->unk84 &= 0xEFFFFFFF;
            }
            temp_f0_2 = (24.599998f * sp34) + 10.0f;
            arg0->unk1A8 = temp_f0_2;
            arg0->unk1A4 = temp_f0_2;
            if (arg0->unk23C != 0) {
                arg0->unk1A4 = arg0->unk1A4;
                arg0->unk1A8 = arg0->unk1A8;
            }
        } else if (func_151239CC(arg0, 3) != 0) {
            arg0->unk1A8 = 0.0f;
            arg0->unk1A4 = 0.0f;
            arg0->unk190 = 0.0f;
        }
        if (D_800BE9F0 == 0x32) {
            if (func_1509BE40(1, 0x4039, 6, 0x9000, 0, 0, 0, 0) != 0) {
                arg0->unk84 |= 0x1000;
                return;
            }
            arg0->unk84 &= ~0x1000;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FF250/func_150D1A40.s")
#endif