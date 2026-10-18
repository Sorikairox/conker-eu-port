#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FCE60/func_150CF650.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FCE60/func_150CF994.s")

void func_151CFE48(struct127 *, f32, s32);

void func_150CFA40(s32 arg0) {
    func_151CFE48(D_800CC2D0, D_800CC2D0->y_position + 300.0f, 0xC61C4000);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FCE60/func_150CFA88.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FCE60/func_150CFAF8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FCE60/func_150CFB90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FCE60/func_150CFD10.s")

void func_150D00FC(u8 *arg0, f32 *arg1, u8 arg2) {
    u8 *temp_v0 = arg0 + 0x70;
    if (arg2 == 0x52) {
        temp_v0[0] |= 1;
        *(f32 *)(temp_v0 + 4) = 0.0f;
        *(f32 *)(temp_v0 + 8) = *(f32 *)(arg0 + 0x10);
        *(f32 *)(temp_v0 + 0xC) = *arg1 - *(f32 *)(arg0 + 0x10);
    }
}

void func_150D0148(f32 arg0) {
    f32 sp1C = arg0;
    func_15155C9C(&sp1C, 0x52);
}

s32 func_150D0170(u8 *arg0) {
    f32 *v = (f32 *)(arg0 + 0x70);

    *(f32 *)(arg0 + 0x10) += v[0] * D_800BE9A4;
    *(f32 *)(arg0 + 0x14) += v[1] * D_800BE9A4 + 0.5f * v[2] * D_800BE9A4 * D_800BE9A4;
    v[1] += v[2] * D_800BE9A4;
    if (v[3] < *(f32 *)(arg0 + 0x14)) {
        *(f32 *)(arg0 + 0x14) = v[3];
        v[0] *= 0.3f;
        v[1] = fabsf(v[1]) * -0.15f;
    }
    return 1;
}

u8 *func_150D0230(u8 *arg0) {
    while ((*arg0 != 0xBD) && (*arg0 != 0)) {
        arg0++;
    }
    return arg0;
}

u8 *func_150D026C(u8 *arg0) {
    while (*arg0 != 0) {
        arg0++;
    }
    return arg0;
}

s32 func_150D0294(u8 *arg0, u8 **arg1) {
    u8 *temp_v0 = func_150D0230(arg0);
    *arg1 = temp_v0;
    return temp_v0 - arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FCE60/func_150D02C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FCE60/func_150D034C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FCE60/func_150D03A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FCE60/func_150D0420.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FCE60/func_150D0544.s")

extern void (*D_80088C50[])(u8 *, u8 *, u8);
void func_150D03A8(u8 *, u8 *, u8);
void func_150D05D0(u8 *arg0, u8 *arg1, u8 arg2) {
    void (*f)(u8 *, u8 *, u8);
    if (arg2 == 0x51) {
        if (arg0[0x28] == arg1[0]) {
            func_150D03A8(arg0, arg1, arg2);
        }
    } else {
        f = D_80088C50[arg0[0x4D]];
        if (f != NULL) {
            f(arg0, arg1, arg2);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FCE60/func_150D0644.s")
