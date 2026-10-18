#include <ultra64.h>
#include "functions.h"
#include "variables.h"

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12D5D0/func_150FF840.s")

void func_151000EC(u8 *arg0, s32 arg1, struct127 *arg2, s32 arg3) {
    u16 w;
    s32 idx;
    w = *(u16 *)((u8 *)arg2 + 0x7A);
    idx = arg2 - D_800CC2D0;
    func_1505D1C4(*(f32 *)arg0, *(f32 *)(arg0 + 4), *(f32 *)(arg0 + 8), arg3 | 0x60000, idx, w, 0, arg1);
}

s32 func_15145EA4(s32 **, s32 *, s32, s32);
extern s32 D_800A2500;

void func_1510015C(u8 *arg0, s32 arg1, s32 arg2) {
    s32 *sp1C;
    s32 sp18;

    sp1C = &D_800A2500;
    sp18 = arg2;
    func_15145EA4(&sp1C, &sp18, (*(s32 *)((u8 *)arg0 + 0x1D4)) + (D_80088BB0 << 6), 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12D5D0/func_151001BC.s")

s32 func_151D5FC8(s32, s32, s32, s32, s32, s32, s32);
s32 func_151D441C(s32, s32, s32, s32);
extern s32 D_8009002C;
extern u8 *D_80090034;
void func_15100248(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
  func_151D5FC8(arg0, arg1, arg2, arg3, arg4, D_8009002C, *D_80090034);
  func_151D441C(arg0, arg1, arg1, 0x8003A);
}

void func_151002AC(s32 arg0, u8 *arg1, s32 arg2) {
    u8 temp_v0 = arg1[4];
    if (((temp_v0 == 0x9F) || (temp_v0 == 0xA0)) && !(*(s32 *)(arg1 + 0x94) & 0x80)) {
        func_1508220C(arg1, 4, 0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12D5D0/func_15100304.s")
