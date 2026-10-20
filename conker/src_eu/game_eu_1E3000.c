#include <ultra64.h>
#include "functions.h"
#include "variables.h"


struct260 *func_151B57F0(s16 arg0, u8 arg1, s32 arg2) {
    extern f32 D_800AA7F8;
    struct260 *temp_v0;
    struct {
        u8 pad0[1408];
        u8 *unk580;
        u8 unk584;
        u8 pad585[3];
        u8 *unk588;
        u8 unk58C;
        u8 pad58D[3];
        f32 unk590;
        f32 unk594;
        f32 unk598;
        f32 unk59C;
        f32 unk5A0;
        u8 pad5A4[8];
    } tmp;

    tmp.unk584 = 0x17;
    tmp.unk58C = 0x16;
    tmp.unk580 = func_15083E90(0x17);
    tmp.unk588 = func_15083E90(tmp.unk58C);
    tmp.unk598 = 250.0f;
    tmp.unk590 = 18.0f;
    tmp.unk594 = 0.0f;
    tmp.unk5A0 = D_800AA7F8;
    tmp.unk59C = 1.0f / tmp.unk598;
    temp_v0 = func_15149130(arg0, -1, -1, 1, 1, 0x15, 0x5A8, arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x5A8);
    }
    return temp_v0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E3000/func_151B58D8.s")

void func_151B604C(u8 *arg0, u8 *arg1, u8 arg2)
{
  u8 *v = arg0 + 0x28;
  if (arg2 == 0x2D)
  {
    if (*(s32 *)arg1 == *(s32 *)(v + 0x580)) { *(s32 *)(v + 0x580) = *(s32 *)(arg1 + 4); v[0x584] = arg1[9]; }
    else if (*(s32 *)(arg1 + 4) == *(s32 *)(v + 0x580)) { *(s32 *)(v + 0x580) = *(s32 *)arg1; v[0x584] = arg1[8]; }
    if (*(s32 *)arg1 == *(s32 *)(v + 0x588)) { *(s32 *)(v + 0x588) = *(s32 *)(arg1 + 4); v[0x58C] = arg1[9]; }
    else if (*(s32 *)(arg1 + 4) == *(s32 *)(v + 0x588)) {
      s32 blk_t; // fakematch: block-local declaration = basic-block boundary (s69)
      *(s32 *)(v + 0x588) = *(s32 *)arg1; v[0x58C] = arg1[8]; }
  }
  else if (arg2 == 0)
  {
    s32 k = *(s32 *)arg1;
    if ((k == *(s32 *)(v + 0x580)) || (k == *(s32 *)(v + 0x588)) || (v[0x584] == arg1[4]) || (v[0x58C] == arg1[4])) { func_1516972C((struct102 *)arg0); }
  }
}
