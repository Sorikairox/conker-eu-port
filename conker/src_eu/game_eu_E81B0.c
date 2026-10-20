#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_150BA4C0(u8 *arg0, u8 arg1, s32 arg2) {
    struct {
        u8 *unk0;
        u8 unk4;
        u8 pad5[3];
        f32 unk8;
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = 0.0f;
    temp_v0 = func_15149130((func_150ADA20() % 9U) + 15, -1, 0x52, -1, 1, 0x3F, 0xC, arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0xC);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E81B0/func_150BAA3C.s")

void func_150BADD0(u8 *arg0, s32 arg1, u8 arg2) {
    func_15149514(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}

s32 func_1504715C(s32, u8 *);
s32 func_15046F70(f32 *, s32, f32, s32);
extern f32 D_800A0230;

s32 func_150BAE10(f32 *arg0, u8 *arg1, s32 arg2, s32 arg3) {
    f32 sp24[3];

    arg0[0] = *(f32 *)(arg1 + 0x14);
    if (D_800A0230 < *(f32 *)(arg1 + 0x180)) {
        arg0[1] = *(f32 *)(arg1 + 0x180);
    } else {
        arg0[1] = *(f32 *)(arg1 + 0x18);
    }
    arg0[2] = *(f32 *)(arg1 + 0x1C);
    if (arg2 == 0) {
        return 1;
    }
    sp24[0] = arg0[0];
    sp24[1] = arg0[1] + 100.0f;
    sp24[2] = arg0[2];
    func_1504715C(arg2, arg1);
    return func_15046F70(sp24, 0, arg0[1] - 100.0f, arg2);
}

s32 func_150BAEE0(s32 arg0, s32 arg1) {
    return 9;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E81B0/func_150BAEF4.s")
