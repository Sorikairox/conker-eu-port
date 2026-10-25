#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12C5F0/func_150FEDE0.s")

extern s32 D_800A23D0;
s32 func_15145EA4(s32 **, s32 *, s32, s32);
extern u8 D_80088F40;
void func_150FF148(u8 *arg0, s32 arg1, s32 arg2) {
    s32 pad;
    s32 *sp20;
    s32 sp1C;
    s32 v;
    v = *(s32 *)(arg0 + 0x1D4) + (D_80088F40 << 6);
    sp20 = &D_800A23D0;
    sp1C = arg2;
    func_15145EA4(&sp20, &sp1C, v, 1);
}

#ifdef NON_MATCHING /* P262: the C definition's exact types (game_eu_1306B0) */
void *func_151030B8(u8 *, u8, f32 *, f32 *, f32 *, s16, u8, f32, u8 *, u8, s32, s16, u8, s32);
#else
s32 func_151030B8(s32, u8, s32, s32, f32 *, s32, s32, f32, s32, s32, s32, s32, s32, s32);
#endif

void func_150FF1A8(s32 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5, s32 arg6) {
    f32 v[2];
    s32 r[3];

    v[1] = func_150ADA68() * 1.001f + 0.60400003f;
    v[0] = func_150ADA68() * 5.9f + 14.1f;
    r[0] = func_150ADA20();
    r[1] = func_150ADA20();
    func_151030B8((u8 *)arg0, arg1, (f32 *)arg2, (f32 *)arg3, v, (r[0] & 3) + 6, 0xFF, func_150ADA68() * 270.0f + 359.0f, (u8 *)arg4, 0xFF, 0, -1, arg5, arg6);
}
