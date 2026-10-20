#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FE5E0/func_150D0DD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FE5E0/func_150D13A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FE5E0/func_150D15F4.s")

extern f32 D_800A0C64;

s32 func_150D16C4(u8 *arg0) {
    (*(f32 *)((u8 *)arg0 + 0x74)) = (f32) (((func_150ADA68() * 150.0f) + 350.0f) * D_800A0C64);
    return 1;
}

s32 func_151DB5D0(s32, f32 *, f32 *, f32, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32);

extern f32 D_800A0C68, D_800A0C6C, D_800A0C70, D_800A0C74;
void func_150D1714(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, f32 arg4, u8 *arg5) {
    f32 a[3];
    f32 x;
    f32 y;
    f32 z;
    f32 d[3];
    s32 r4;
    s32 r3;
    f32 r2;
    f32 r1;

    a[0] = *(f32 *)(arg2 + 0) * arg4 + *(f32 *)(arg0 + 0);
    a[1] = *(f32 *)(arg2 + 4) * arg4 + *(f32 *)(arg0 + 4);
    a[2] = *(f32 *)(arg2 + 8) * arg4 + *(f32 *)(arg0 + 8);
    x = *(f32 *)(arg3 + 0) * arg4 + *(f32 *)(arg1 + 0);
    y = *(f32 *)(arg3 + 4) * arg4 + *(f32 *)(arg1 + 4);
    z = *(f32 *)(arg3 + 8) * arg4 + *(f32 *)(arg1 + 8);
    d[0] = *(f32 *)(arg5 + 0x74) * (x - a[0]);
    d[1] = *(f32 *)(arg5 + 0x74) * (y - a[1]);
    d[2] = *(f32 *)(arg5 + 0x74) * (z - a[2]);
    r1 = func_150ADA68();
    r2 = func_150ADA68();
    r3 = func_150ADA20();
    r4 = func_150ADA20();
    func_151DB5D0(0, a, d, r1 * 61.0f + 60.0f, D_800A0C68, D_800A0C6C, r2 * D_800A0C70 + D_800A0C74, (r3 & 0xF) + 0x23, r4 % 156U + 0x64, 0x1E, 8, 0, arg5[0xC], arg5[1]);
}
