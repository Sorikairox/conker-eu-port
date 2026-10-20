#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F4D30/func_150C7520.s")

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
