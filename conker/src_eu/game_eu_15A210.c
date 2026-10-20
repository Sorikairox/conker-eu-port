#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15A210/func_1512C490.s")

void func_150498A0(f32 *, f32, f32 *, f32, f32, f32);
extern Mtx *D_800DC6D0[];

void func_1512D5E0(u8 *arg0) {
    Mtx m;
    f32 mf[4][4];
    f32 k;

    if ((*(s32 *)(arg0 + 0x2C) & 0x80000)) {
        k = 0.003f;
    } else if (*(s16 *)(arg0 + 0x298) != 0) {
        k = 0.04f;
    } else {
        k = 0.03f;
    }
    if ((*(s32 *)(arg0 + 0x2C) & 0x80000) || (*(s32 *)(arg0 + 0x5F0) & 1) || (*(s32 *)(arg0 + 0x2C) != 0x40000 && (*(s32 *)(arg0 + 0x5F0) & 8))) {
        *(f32 *)(arg0 + 0x7B0) += 0.04363323f * D_800BE9E4;
        if (*(f32 *)(arg0 + 0x7B0) > 3.1415927f) {
            *(f32 *)(arg0 + 0x7B0) -= 6.2831855f;
        }
    } else {
        k = 0.0f;
    }
    if (arg0[0x23C] != 0 || (*(s32 *)(arg0 + 0x5F0) & 4)) {
        *(f32 *)(arg0 + 0x7DC) = k;
    } else {
        func_150498A0((f32 *)(arg0 + 0x7DC), k, (f32 *)(arg0 + 0x7D8), 0.2f, 0.4f, *(f32 *)(arg0 + 0x7B4));
    }
    guMtxIdentF(mf);
    mf[0][0] = 2.0f * *(f32 *)(arg0 + 0x7DC) + 2.0f * (*(f32 *)(arg0 + 0x7DC) * func_150AD78C(*(f32 *)(arg0 + 0x7B0))) + 1.0f;
    mf[1][1] = *(f32 *)(arg0 + 0x7DC) + *(f32 *)(arg0 + 0x7DC) * func_150AD780(*(f32 *)(arg0 + 0x7B0)) + 1.0f;
    guMtxF2L(mf, &m);
    guMtxCatL(arg0[0x23D] + D_800DC6D0[D_800BE9C0], &m, arg0[0x23D] + D_800DC6D0[D_800BE9C0]);
}

s32 func_1502B5C8(u32 *, s32, s32, s32);
extern s32 D_800DC6B0[];
extern s32 D_800DC6C0[];
void func_1512D7A8(void) {
    u32 sp3C;
    s32 i;

    for (i = 0; i < 4; i++) {
        D_800DC6B0[i] = func_1502B5C8(&sp3C, 2, 0x1B, i);
        D_800DC6C0[i] = sp3C / 24;
    }
}

void func_1512D854(u8 *arg0, s32 arg1) {
    *(s32 *)(arg0 + 0x850) = arg1;
    arg0[0x84D] = 1;
}

extern s32 D_800DC6C0[];
void func_1512D868(u8 *arg0) {
    switch (arg0[0x84D]) {
    case 1:
        arg0[0x84E] = 0;
        arg0[0x84D] = 2;
        break;
    case 2:
        arg0[0x84E] += D_800BE9E4;
        if (arg0[0x84E] >= D_800DC6C0[*(s32 *)(arg0 + 0x850)]) {
            arg0[0x84D] = 0;
        }
        break;
    }
}

void func_1512D8D8(s32 arg0) {
}
