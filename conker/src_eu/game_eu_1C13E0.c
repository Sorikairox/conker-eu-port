#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C13E0/func_15193660.s")

typedef struct {
    u8 u0;
    u8 *u4;
    s8 u8_;
    f32 uC;
    f32 u10;
    f32 u14;
    f32 u18;
    f32 u1C;
    f32 u20;
    s8 u24;
    s16 u26;
    s16 u28;
    s16 u2A;
    s16 u2C;
    s8 u2E;
    s8 u2F;
    s8 u30;
    f32 u34;
    s8 u38;
    s8 u39;
} SpA3C;
s32 func_15134DAC(SpA3C *, s32, ...);
extern f32 D_800A85C4;

void func_151937F4(u8 *arg0, s32 arg1, s32 arg2) {
    SpA3C s;

    if (arg0 != NULL && *(s32 *)arg0 != 0) {
        s.u0 = arg0[0x3B];
        s.u4 = arg0;
        s.u8_ = 0;
        s.uC = -28.0f;
        s.u10 = 6.0f;
        s.u14 = 1.0f;
        s.u18 = -58.0f;
        s.u1C = -3.0f;
        s.u20 = -31.0f;
        s.u24 = 2;
        s.u26 = 30;
        s.u28 = 25;
        s.u2A = 750;
        s.u2E = 3;
        s.u2F = 3;
        s.u30 = -1;
        s.u34 = D_800A85C4;
        s.u38 = 4;
        s.u39 = -1;
        func_15134DAC(&s, 0, arg0);
    }
}

s32 func_15193E54(struct102 *arg0) {
    *(f32 *)((u8 *)arg0 + 0x74) = D_800A85C8;
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C13E0/func_15193E6C.s")
