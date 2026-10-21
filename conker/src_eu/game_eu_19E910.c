#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19E910/func_15171100.s")

void func_15171434(s32 arg0, u8 arg1, s32 arg2) {
    switch (D_800BE9F0) {
    case 2:
        func_15171100(arg0, 1, 1, 1, arg1, arg2);
        break;
    case 16:
        func_15171100(arg0, 0xA9, 8, 0, arg1, arg2);
        break;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19E910/func_151714BC.s")

void func_15171734(u8 *arg0) {
    if (arg0[4] == 0x33) {
        func_150C3D5C(arg0);
    }
    func_15060F28(arg0, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19E910/func_15171770.s")

void func_15171D6C(s16 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, f32 argA, u8 argB, s32 argC);
extern f32 D_800A73A0;
extern f32 D_800A73A4;

void func_15171B70(u8 *arg0, u8 arg1, s32 arg2) {
    switch (arg0[0x72]) {
    case 0xEB:
        func_15171D6C((s16 *)arg0, 400.0f, 500.0f, 0.0f, D_800A73A0, 0.0f, 2, 5, 20, 20, 1.0f, arg1, arg2);
        break;
    case 0xF6:
        func_15171D6C((s16 *)arg0, 200.0f, 400.0f, -1800.0f, -1000.0f, -1200.0f, 2, 5, 4, 10, 1.0f, arg1, arg2);
        break;
    case 0xF8:
        func_15171D6C((s16 *)arg0, 100.0f, 160.0f, -2500.0f, D_800A73A4, 0.0f, 2, 5, 4, 4, 0.5f, arg1, arg2);
        break;
    case 0xF9:
        func_15171D6C((s16 *)arg0, 200.0f, 100.0f, 100.0f, -300.0f, 0.0f, 1, 5, 4, 4, 1.0f, arg1, arg2);
        break;
    }
}

void func_15170648(f32 *, f32, f32, s32, f32, s32, s32, s32, u8, s32);
void func_15171D6C(s16 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, f32 argA, u8 argB, s32 argC) {
    f32 pts[4][3];
    f32 x;
    f32 y;
    f32 z;

    x = arg0[8] + arg3;
    y = arg0[9] + arg4;
    z = arg0[10] + arg5;
    pts[0][0] = arg1 + x;
    pts[0][1] = y;
    pts[0][2] = arg2 + z;
    pts[1][0] = x - arg1;
    pts[1][1] = y;
    pts[1][2] = arg2 + z;
    pts[2][0] = x - arg1;
    pts[2][1] = y;
    pts[2][2] = z - arg2;
    pts[3][0] = arg1 + x;
    pts[3][1] = y;
    pts[3][2] = z - arg2;
    func_15170648(pts[0], x, z, arg7, argA, arg6, arg8, arg9, argB, argC);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19E910/func_15171E60.s")

#ifdef NON_MATCHING
void func_150AEEB0(struct127 *, u8);
#else
s32 func_150AEEB0(struct127 *, u8);
#endif
#ifdef NON_MATCHING
void func_150BDC20(struct127 *, u8, s32);
#else
s32 func_150BDC20(struct127 *, u8, s32);
#endif
s32 func_150CE0C0(struct127 *, u8, s32);

void func_15172164(struct127 *arg0, u8 arg1) {
    switch (arg0->id) {
    case 0x13:
    case 0x23:
        func_150AEEB0(arg0, arg1);
        func_10010154(0x69, arg0, 0x7D00, 0xC8, 0x7D0);
        break;
    case 0x1E:
        func_150BDC20(arg0, arg1, 1);
        break;
    case 0x54:
        func_150CE0C0(arg0, arg1, 1);
        break;
    }
}
