#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    /* 0x00 */ u8 pad0[0x58];
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
} struct_eu_F3AD0_b;

typedef struct {
    /* 0x00 */ u8 pad0[0x58];
    /* 0x58 */ struct_eu_F3AD0_b *unk58;
    /* 0x5C */ u8 unk5C;
} struct_eu_F3AD0;


s32 func_150C6960();
void func_150C62C0(u8 *arg0) {
    if (*(s32 *)(arg0 + 0x58) != 0) {
        u8 *p = *(u8 **)(arg0 + 0x58);
        p += 0xB0;
        p[4] = 1;
    } else {
    *(s32 *)(arg0 + 0x58) = func_150C6960();
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F3AD0/func_150C630C.s")

void func_1513F6C0(u8 *, u8, u8);
s32 func_150C63FC(u8 *arg0) {
    u8 *p;
    p = *(u8 **)(arg0 + 0xB0);
    p += 0x59;  // fakematch: keeps the dead addiu (p += K+1; p--;)
    p--;  // fakematch: pairs with p += K+1
    *(s32 *)(p + 0) = 0;
    *(s32 *)(arg0 + 0xB0) = 0;
    *(s32 *)(arg0 + 0x18) |= 2;
    func_1513F6C0(arg0, 0, 0);
    return 0;
}

s32 func_150C6494(s32, u8 *, s32);

void func_150C6440(u8 *arg0)
{
  u8 *new_var2;
  long long new_var3;
  int new_var;
  s32 temp_a2;
  s32 *new_var5;
  s32 *new_var4;
  if (!arg0)
  {
    do
    {
    }
    while (0);
  }
  new_var2 = (u8 *) arg0;
  new_var5 = (s32 *) (new_var2 + 0x18);
  temp_a2 = *new_var5;
  new_var = 0x5C;
  new_var4 = &(*((s32 *) (((u8 *) arg0) + new_var)));
  if ((*((s32 *) (((u8 *) arg0) + new_var))) != 0)
  {
    new_var = (*new_var4) + 0x58;
    *((s8 *) (((u8 *) ((0, new_var))) + 4)) = 1;
    dummy_label_747774:
    ;

    ;
    return;
  }
  *((s32 *) (((u8 *) arg0) + new_var)) = func_150C6494(new_var3 = temp_a2, arg0, temp_a2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F3AD0/func_150C6494.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F3AD0/func_150C65D8.s")

s32 func_150C68EC(struct_eu_F3AD0 *arg0) {
    s32 ret = 1;

    if (arg0->unk5C == 0) {
        ret = 0;
    }
    arg0->unk5C = 0;
    return ret;
}

void func_150C6910(struct_eu_F3AD0 *arg0) {
    s32 *temp_v0 = &arg0->unk58->unk58;

    temp_v0[1] = 0;
    func_151346EC(arg0);
}

void func_150C6938(struct_eu_F3AD0 *arg0) {
    s32 *temp_v0 = &arg0->unk58->unk58;

    temp_v0[1] = 0;
    func_1513470C(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F3AD0/func_150C6960.s")
