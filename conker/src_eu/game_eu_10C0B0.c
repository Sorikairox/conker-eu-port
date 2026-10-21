#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_150DE8A0(s32 arg0) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10C0B0/func_150DE8AC.s")

#ifdef NON_MATCHING
s32 func_1510D66C(s32, s32 *, s32, s32);
void func_1510DDF4(s32, s32, s32, s32, s32);
extern s32 D_800905B4;

void func_150DE9D8(u8 *arg0) {
    struct {
        s32 u54;
    } sp;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f12;
    s32 *var_s1;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s0;
    s32 var_s2;

    if (((*(u8 *)((u8 *)arg0 + 0x73)) & 3) == 3) {
        temp_f12 = (f32) D_800BE9E4;
        (*(f32 *)((u8 *)arg0 + 0)) = (f32) ((*(f32 *)((u8 *)arg0 + 0)) + ((*(f32 *)((u8 *)arg0 + 0x60)) * temp_f12));
        temp_f0 = (*(f32 *)((u8 *)arg0 + 0));
        if (temp_f0 < 0.0f) {
            (*(f32 *)((u8 *)arg0 + 0)) = (f32) (temp_f0 + 360.0f);
        } else if (temp_f0 >= 360.0f) {
            (*(f32 *)((u8 *)arg0 + 0)) = (f32) (temp_f0 - 360.0f);
        }
        (*(f32 *)((u8 *)arg0 + 4)) = (f32) ((*(f32 *)((u8 *)arg0 + 4)) + ((*(f32 *)((u8 *)arg0 + 0x64)) * temp_f12));
        temp_f0_2 = (*(f32 *)((u8 *)arg0 + 4));
        if (temp_f0_2 < 0.0f) {
            (*(f32 *)((u8 *)arg0 + 4)) = (f32) (temp_f0_2 + 360.0f);
        } else if (temp_f0_2 >= 360.0f) {
            (*(f32 *)((u8 *)arg0 + 4)) = (f32) (temp_f0_2 - 360.0f);
        }
        (*(f32 *)((u8 *)arg0 + 8)) = (f32) ((*(f32 *)((u8 *)arg0 + 8)) + ((*(f32 *)((u8 *)arg0 + 0x68)) * temp_f12));
        temp_f0_3 = (*(f32 *)((u8 *)arg0 + 8));
        if (temp_f0_3 < 0.0f) {
            (*(f32 *)((u8 *)arg0 + 8)) = (f32) (temp_f0_3 + 360.0f);
        } else if (temp_f0_3 >= 360.0f) {
            (*(f32 *)((u8 *)arg0 + 8)) = (f32) (temp_f0_3 - 360.0f);
        }
        (*(s16 *)((u8 *)arg0 + 0x5C)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x5C)) - ((*(s32 *)((u8 *)arg0 + 0x3C)) * D_800BE9E4));
        (*(s16 *)((u8 *)arg0 + 0x10)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x10)) + ((*(s16 *)((u8 *)arg0 + 0x5A)) * D_800BE9E4));
        (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x12)) + ((*(s16 *)((u8 *)arg0 + 0x5C)) * D_800BE9E4));
        (*(s16 *)((u8 *)arg0 + 0x14)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x14)) + ((*(s16 *)((u8 *)arg0 + 0x5E)) * D_800BE9E4));
        temp_v0 = (*(u8 *)((u8 *)arg0 + 0x8A)) - D_800BE9E4;
        if (temp_v0 > 0) {
            (*(u8 *)((u8 *)arg0 + 0x8A)) = (u8) temp_v0;
        } else {
            (*(s8 *)((u8 *)arg0 + 0x6E)) = 1;
        }
    }
    if (((*(u16 *)((u8 *)arg0 + 0x54)) & 0xFFFF7FFF) == 0xC) {
        var_s2 = 4;
        var_s1 = ((*(s32 *)((u8 *)arg0 + 0x7C)) * 8) + &D_800905B4;
        var_s0 = 5;
        do {
            temp_v0_2 = func_1510D66C(*var_s1, &sp.u54, 3, 0);
            func_1510DDF4(arg0, temp_v0_2, (sp.u54 + temp_v0_2) - 0x200, var_s2, var_s0);
            var_s0 += 2;
            var_s1 += 4;
            var_s2 += 2;
        } while (var_s0 != 9);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10C0B0/func_150DE9D8.s")
#endif
#ifdef NON_MATCHING
void func_150DEC58(u8 *arg0) {
    (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) (s32) ((func_15048A40(((s32) (*(s32 *)((u8 *)arg0 + 0x7C)) >> 3) & 0xFF) * 10.2f) + 1130.0f);
    (*(f32 *)((u8 *)arg0 + 0)) = (f32) (func_15048A40(((s32) (*(s32 *)((u8 *)arg0 + 0x80)) >> 3) & 0xFF) * 1.1f);
    (*(f32 *)((u8 *)arg0 + 8)) = (f32) (func_15048A40(((s32) (*(s32 *)((u8 *)arg0 + 0x84)) >> 3) & 0xFF) * 1.1f);
    (*(s32 *)((u8 *)arg0 + 0x7C)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x7C)) + (D_800BE9E4 * 0xC));
    (*(s32 *)((u8 *)arg0 + 0x80)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x80)) + (D_800BE9E4 * 0x10));
    (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) + (D_800BE9E4 * 0x18));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10C0B0/func_150DEC58.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10C0B0/func_150DED40.s")

s32 func_150DF04C(u8 *arg0) {
    (*(f32 *)((u8 *)arg0 + 0x34)) += ((*(f32 *)((u8 *)arg0 + 0x110)) * D_800BE9A4);
    (*(f32 *)((u8 *)arg0 + 0x38)) += ((*(f32 *)((u8 *)arg0 + 0x114)) * D_800BE9A4);
    (*(f32 *)((u8 *)arg0 + 0x3C)) += ((*(f32 *)((u8 *)arg0 + 0x118)) * D_800BE9A4);
    (*(f32 *)((u8 *)arg0 + 0x11C)) -= D_800BE9A4;
    if ((*(f32 *)((u8 *)arg0 + 0x11C)) < 0.0f) {
        return 0;
    }
    return 1;
}

s32 func_15140410(s32, s32, s32, s16);
s32 func_150DF0D8(s32 arg0, s16 arg1) {
    if (D_800DBFF0[D_80082FA0].unk388 < 5.0f) {
        return 0;
    }
    return func_15140410(arg0, arg0 + 0x120, arg0 + 0x12C, arg1);
}

void func_150DF1A8(u8 arg0, s32 arg1);

void func_150DF160(s32 arg0) {
    u8 i;

    for (i = 0; i < 4; i++) {
        func_150DF1A8(i, 1);
    }
}

extern u8 D_800A10DB[];
extern u8 D_800A10FB[];
void func_150DF1A8(u8 arg0, s32 arg1) {
    s32 i = arg0 * 4;
    func_151616D0(D_800A10DB[i], 0x22, 0);
    func_151417C4(D_800A10FB[i], 0x22);
}
