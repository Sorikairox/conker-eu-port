#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10E600/func_150E0DF0.s")

#ifdef NON_MATCHING
s32 func_15021834(struct127 *, s32, s32);
s32 func_150535F4(struct127 *);
s32 func_15056B08(struct127 *, s32);
s32 func_150585F0(struct127 *, s32);
s32 func_150599C8(struct127 *, s32, u16);
extern u16 D_800CC766;

void func_150E1160(struct127 *arg0) {
    u8 temp_t0;
    u8 temp_v0;
    u8 var_v0;

    arg0->unkB0 = 0xF;
    arg0->unk80 = 0xA;
    if (arg0->unk87 != 0) {
        var_v0 = arg0->unk83;
        if ((s32) var_v0 < 0x64) {
            temp_t0 = var_v0 + D_800BE9A0;
            arg0->unk83 = temp_t0;
            var_v0 = temp_t0 & 0xFF;
        }
        if ((s32) var_v0 >= 5) {
            temp_v0 = arg0->unk251;
            if (temp_v0 != 3) {
                arg0->unk218 = NULL;
                arg0->unk232 = 4;
                arg0->unk78 = D_800CC766;
                if (temp_v0 == 2) {
                    arg0->unk232 = 2;
                }
            }
        }
    } else {
        if ((s32) arg0->unk83 >= 0x3D) {
            D_800D1580 = -0xFDFECD;
            D_800D154C = D_800CC2D0;
            func_1506E8D8();
            D_800D154C = arg0;
        }
        arg0->unk83 = 0;
    }
    if (arg0->unk232 == 4) {
        if (arg0->unk83 == 0) {
            arg0->unk78 = arg0->unk76;
        }
        func_150599C8(arg0, 3, arg0->unk78);
    }
    arg0->unk87 = 0;
    if (arg0->stunned == 0) {
        func_15056B08(arg0, 0x3D4C0000);
    } else {
        func_150585F0(arg0, 0x3D4CCCCD);
    }
    arg0->unk40 = (f32) (s16) (arg0->unk7A + 0x4000) * 0.005493164f;
    func_15059140(arg0);
    arg0->unkBC = arg0->x_position - arg0->old_x_position;
    arg0->unk148 = arg0->z_position - arg0->old_z_position;
    if (func_150535F4(arg0) == 0) {
        func_15021834(arg0, 0, -1);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10E600/func_150E1160.s")
#endif