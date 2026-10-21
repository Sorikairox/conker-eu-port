#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_8009FC40;
void func_150B0F40(u8 *arg0, u8 *arg1, f32 *arg2, f32 *arg3, f32 *arg4, s16 *arg5) {
    f32 r;
    f32 k;
    f32 s;
    f32 m;

    *arg5 = *(f32 *)(arg0 + 0x40) * D_8009FC40 - 128.0f;
    r = func_150ADA68() * 248.0f;
    s = func_150ADA68() + -0.5f;
    if (r < 122.0f) {
        arg4[0] = arg2[0] * -31.5f + arg3[0] * s * 122.0f;
        arg4[1] = 0.0f;
        arg4[2] = arg2[1] * -31.5f + arg3[1] * s * 122.0f;
    } else {
        s32 step; // fakematch: permuter temp, schedules `r -= 122.0f` after the 63/61 loads

        m = 61.0f;
        r -= 122.0f;
        step = 0x40;
        k = m;
        if (r < 63.0f) {
            k = -m;
            *arg5 += step;
        } else {
            *arg5 -= 0x40;
        }
        arg4[0] = arg2[0] * 63.0f * s + arg3[0] * k;
        arg4[1] = 0.0f;
        arg4[2] = arg2[1] * 63.0f * s + arg3[1] * k;
    }
    arg4[0] += *(f32 *)(arg0 + 0x14);
    arg4[1] += *(f32 *)(arg1 + 0x118);
    arg4[2] += *(f32 *)(arg0 + 0x1C);
}

void func_150B1114(u8 *arg0) {
    func_150B1138(arg0, 0xFF, 1);
}

void func_150B1138(u8 *arg0, u8 arg1, s32 arg2) {
    struct {
        u8 *unk0;
        u8 unk4;
        f32 unk8;
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = 0.0f;
    temp_v0 = func_15149130(300, -1, 0x58, -1, 0, 0x43, 0xC, arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0xC);
    }
}

void func_150B11C0(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DE750/func_150B1200.s")
