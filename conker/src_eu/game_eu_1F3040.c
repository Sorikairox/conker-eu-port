#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F3040/func_151C5280.s")

s32 func_151030B8(s32, s32, f32 *, f32 *, f32 *, s32, s32, f32, s32, s32, s32, s32, s32, s32);
extern f32 D_800AAE70[];
extern f32 D_800AAE7C[];

void func_151C5B38(s32 arg0, s32 arg1, s16 arg2, u8 arg3, s32 arg4) {
    f32 s[2];

    s[1] = ((func_150ADA68() * 1001.0f) + 604.0f) * 0.01f;
    s[0] = ((func_150ADA68() * 59.0f) + 141.0f) * 0.1f;
    func_151030B8(arg0, 0, D_800AAE70, D_800AAE7C, s, (func_150ADA20() & 3) + 6, (func_150ADA20() % 1U) + 0xFF /* fakematch: rand % 1 range-0 rand (folded, call + spill kept) */, (func_150ADA68() * 270.0f) + 359.0f, arg1, 0xFF, 0, arg2, arg3, arg4);
}

void func_151C5C54(u8 *arg0, u8 arg1, s32 arg2) {
    s8 sp48[8];
    s32 sp3C[3];

    sp48[0] = 3;
    sp48[1] = -1;
    *(s16 *)(sp48 + 2) = (func_150ADA20() % 3U) + 3;
    sp48[4] = 0;
    sp3C[0] = *(f32 *)(arg0 + 0);
    sp3C[1] = *(f32 *)(arg0 + 4);
    sp3C[2] = *(f32 *)(arg0 + 8);
    func_151602C0(sp48, sp3C, (func_150ADA20() & 1) + 6, 0xFF, 0xE8, 0xAB, 0xFFU, 0U, 0, arg1, arg2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F3040/func_151C5D2C.s")

void func_15137F30(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 arg4, u8 *arg5, f32 *arg6, f32 *arg7, f32 *arg8, f32 *arg9, s16 *argA, u8 *argB, f32 *argC);
void func_151C6424(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 arg4, u8 *arg5) {
    f32 sp6C[3];
    f32 sp60[3];
    f32 sp54[3];
    f32 sp50;
    s16 sp4E;
    u8 sp4D;
    f32 sp48;

    func_15137F30(arg0, arg1, arg2, arg3, arg4, arg5, sp6C, sp60, sp54, &sp50, &sp4E, &sp4D, &sp48);
    func_151D9014(sp6C, sp54, 1, sp50, sp4E, sp4D, sp48, 0, 1.0f, 1.0f, 1, 0, 1, 0, arg5[0xC], arg5[1]);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F3040/func_151C64F4.s")

typedef struct {
    s16 n0; s16 n1; s32 p; s16 c; s16 a; s16 d; s16 e;
    f32 f0; f32 f1; f32 f2; f32 f3; f32 f4;
    u8 b0; u8 b1; s16 h0; s16 h1; s16 pad;
    f32 g0; f32 g1; f32 g2; s32 q;
} SpawnC6750;
void func_15154BF4(SpawnC6750 *, u8, s32);
void func_151C6750(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    SpawnC6750 s;

    s.f0 = 5.0f;
    s.n0 = 10;
    s.f1 = 7.0f;
    s.n1 = 4;
    s.p = arg0;
    s.c = 0;
    s.d = 255;
    s.a = -24;
    s.e = 25;
    s.b0 = 0xBE;
    s.b1 = 0x41;
    s.h0 = 0xC8;
    s.h1 = 0x96;
    s.f2 = -0.208f;
    s.f3 = 0.085f;
    s.f4 = 0.970632f;
    s.g0 = 96.0f;
    s.g1 = 109.0f;
    s.g2 = 1.0f;
    s.q = arg1;
    func_15154BF4(&s, arg2, arg3);
}

s32 func_151C6840(u8 *arg0, s32 arg1, s32 arg2) {
    switch (arg0[4]) {
        case 0x5A:
        case 0x74:
        case 0x7A:
            return 0;
        default:
            return 1;
    }
}
