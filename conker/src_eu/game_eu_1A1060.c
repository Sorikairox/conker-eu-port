#include <ultra64.h>
#include "functions.h"
#include "variables.h"


typedef struct {
    u8 c[4];
    s16 v[4];
    u16 a;
    u16 b;
} Info3850;
extern Info3850 D_8008D010;
extern s8 D_800DD710;
s32 func_15173954(s32, s32, s32, s32, s32);
void func_15173850(s32 arg0) {
    if (*(s16 *)((u8 *)D_800B0DF0 + 0x40) == *(s16 *)((u8 *)D_800B0DF0 + 0x3C) && *(s16 *)((u8 *)D_800B0DF0 + 0x3C) == 0) {
        *(s16 *)((u8 *)D_800B0DF0 + 0x40) = 100;
    }
    D_8008D010.c[0] = D_800B0DF0->pad2A[0x18];
    D_8008D010.c[1] = D_800B0DF0->pad2A[0x19];
    D_8008D010.c[2] = D_800B0DF0->pad2A[0x1A];
    D_8008D010.c[3] = D_800B0DF0->pad2A[0x1B];
    D_8008D010.v[0] = *(s16 *)((u8 *)D_800B0DF0 + 0x3A);
    D_8008D010.v[1] = *(s16 *)((u8 *)D_800B0DF0 + 0x3C);
    D_8008D010.v[2] = *(s16 *)((u8 *)D_800B0DF0 + 0x3E);
    D_8008D010.v[3] = *(s16 *)((u8 *)D_800B0DF0 + 0x40);
    D_8008D010.a = *(u16 *)((u8 *)D_800B0DF0 + 2);
    D_8008D010.b = *(u16 *)((u8 *)D_800B0DF0 + 0);
    if ((s8)D_800B0DF0->pad2A[0x1C] != -1) {
        D_800DD710 = 1;
        func_15173954((s8)D_800B0DF0->pad2A[0x1C], (s8)D_800B0DF0->pad2A[0x1C], arg0, 0, -1);
    } else {
        D_800DD710 = 0;
        func_15173954(0, 0, arg0, 0, -1);
    }
}

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
