#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_117D70/func_150EA560.s")

s32 func_150EA68C(u8 *arg0) {
    *(s32 *)(arg0 + 0x80) = 0;
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_117D70/func_150EA69C.s")

f32 func_150EAA10(u8 *arg0) {
    u8 **q;
    u8 *p;
    f32 r;

    q = &arg0;
    r = func_151423D8((((u32) (*(u32 *)((u8 *)arg0 + 0x80)) >> 0x10) - 0x40));
    p = *q;
    r = (*(f32 *)((u8 *)p + 0x88)) + ((*(f32 *)((u8 *)p + 0x8C)) * (0, r)); // fakematch: (0, x) comma flips commutative operand order
    p += 0x80;
    *(s32 *)(p + 0) = (*(s32 *)((u8 *)p + 4)) * D_800BE9E4 + (*(u32 *)((u8 *)p + 0));
    return r;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_117D70/func_150EAA80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_117D70/func_150EAB4C.s")

void func_150EAE60(s32 arg0) {
    func_150E6060();
}

void func_150EA904(s32 arg0, s32 arg1)
{
  u8 *p;
  p = ((u8 *) D_800DBEF4) + (arg1 * 0xA0);
  if (p[0x72] == 224)
  {
    p[0x73] = (p[0x73] & 0xFFFF) | 3;
  }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_117D70/func_150EAEC4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_117D70/func_150EB090.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_117D70/func_150EB3A4.s")
