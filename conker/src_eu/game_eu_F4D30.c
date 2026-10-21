#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 func_15134DAC(u8 *, s32);
void func_1516962C(s32, u8 *, u8);

void func_150C7520(u8 *arg0, s16 arg1, s32 arg2, s32 arg3) {
    struct {
        u8 u1C;
        u8 pad1D[0x3];
        u8 * u20;
        s8 u24;
        u8 pad25[0x3];
        f32 u28;
        f32 u2C;
        f32 u30;
        f32 u34;
        f32 u38;
        f32 u3C;
        s8 u40;
        u8 pad41[0x1];
        s16 u42;
        s16 u44;
        s16 u46;
        u8 pad48[0x2];
        s8 u4A;
        s8 u4B;
        s8 u4C;
        u8 pad4D[0x3];
        f32 u50;
        s8 u54;
        s8 u55;
    } sp;

    if (arg0 != NULL) {
        func_1516962C(0x29, arg0, 0x12);
        sp.u24 = 0xD;
        sp.u40 = 0;
        sp.u4A = -1;
        sp.u4B = 1;
        sp.u4C = -1;
        sp.u54 = 2;
        sp.u55 = -1;
        sp.u20 = arg0;
        sp.u1C = (*(u8 *)((u8 *)arg0 + 0x3B));
        sp.u30 = 34.0f;
        sp.u3C = 34.0f;
        sp.u28 = 2.0f;
        sp.u34 = -15.0f;
        sp.u2C = 0.0f;
        sp.u38 = 0.0f;
        sp.u50 = 0.47200003f;
        if (arg1 != 0) {
            sp.u46 = arg1;
            sp.u40 = 2;
        } else {
            sp.u46 = 0x12C;
        }
        sp.u42 = (func_150ADA20() % 66U) + 0x23;
        sp.u44 = (func_150ADA20() % 26U) + 0x19;
        func_15134DAC(&sp.u1C, 0);
        sp.u24 = 0xC;
        sp.u30 = 34.0f;
        sp.u3C = 34.0f;
        sp.u28 = -2.0f;
        sp.u2C = 0.0f;
        sp.u38 = 0.0f;
        sp.u34 = 15.0f;
        sp.u42 = (func_150ADA20() % 66U) + 0x23;
        sp.u44 = (func_150ADA20() % 26U) + 0x19;
        func_15134DAC(&sp.u1C, 0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F4D30/func_150C7520.s")
#endif
s32 func_151DB5D0(s32, u8 *, f32 *, f32, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32);

void func_150C76C0(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4, u8 *arg5) {
    f32 sp54[3];
    s16 sp52;

    sp54[0] = ((*(f32 *)((u8 *)arg1 + 0)) - (*(f32 *)((u8 *)arg0 + 0))) * 0.407f;
    sp54[1] = ((*(f32 *)((u8 *)arg1 + 4)) - (*(f32 *)((u8 *)arg0 + 4))) * 0.407f;
    sp54[2] = ((*(f32 *)((u8 *)arg1 + 8)) - (*(f32 *)((u8 *)arg0 + 8))) * 0.407f;
    sp52 = (func_150ADA20() % 31U) + 0x2A;
    func_151DB5D0(0, arg0, sp54, ((func_150ADA68()) * 70.0f) + 30.0f, ((func_150ADA68()) * 0.020000001f) + 1.0400001f, 1.0f, ((func_150ADA68()) * 0.194f) + -0.35000002f, (s32) sp52, (func_150ADA20() % 101U) + 0x9B, (s32) sp52, 0xFF / sp52, 1, (s32) (*(u8 *)((u8 *)arg5 + 0xC)), (s32) (*(u8 *)((u8 *)arg5 + 1)));
}
