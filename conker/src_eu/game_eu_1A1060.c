#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A1060/func_15173850.s")

s32 func_15173948(s32 arg0, s32 arg1)
{
  return arg0;
  if (arg0)
  {
  }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A1060/func_15173954.s")

s32 func_15173954(s32, s32, s32, s32, s32);
extern s32 D_800DC2D8;
extern s32 D_800DD714;

void func_15173E34(s32 arg0) {
    if ((s8) D_800B0DF0->pad2A[0x1C] == -1) {
        if (D_800DBFF0->unk5F0 & 1) {
            func_15173954(6, 6, arg0, 0, -1);
            (*(u8 *)((u8 *)(&D_800DC2D8) + 0)) = (u8) (*(u8 *)((u8 *)(&D_800DD714) + 0));
            (*(u8 *)((u8 *)(&D_800DC2D8) + 1)) = (u8) (*(u8 *)((u8 *)(&D_800DD714) + 1));
            (*(u8 *)((u8 *)(&D_800DC2D8) + 2)) = (u8) (*(u8 *)((u8 *)(&D_800DD714) + 2));
            return;
        }
        func_15173954(0, 0, arg0, 0, -1);
        (*(u8 *)((u8 *)(&D_800DC2D8) + 0)) = (u8) D_800B0DF0->unk5;
        (*(u8 *)((u8 *)(&D_800DC2D8) + 1)) = (u8) D_800B0DF0->unk6;
        (*(u8 *)((u8 *)(&D_800DC2D8) + 2)) = (u8) D_800B0DF0->unk7;
    }
}

s8 func_15173F04(s32 arg0) {
    return (s8) D_800B0DF0->pad2A[0x1C];
}
