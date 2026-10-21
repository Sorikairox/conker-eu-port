#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    /* 0x000 */ u8 pad0[0x11B];
    /* 0x11B */ u8 unk11B;
} struct_eu_B2980_b;

typedef struct {
    /* 0x000 */ u8 pad0[0x31C];
    /* 0x31C */ struct_eu_B2980_b *unk31C;
} struct_eu_B2980;


#ifdef NON_MATCHING
extern s32 D_800875E0;
extern u8 D_8009DD24;

u8 func_15085170(u8 *arg0) {
    s32 var_a0;
    s32 var_v0;
    u8 *temp_a3;
    u8 *var_a1;
    u8 *var_t0;
    u8 temp_a2;
    u8 temp_v1;

    temp_v1 = (*(u8 *)((u8 *)arg0 + 4));
    var_a1 = &D_8009DD24;
    var_v0 = 0;
loop_1:
    temp_a2 = *var_a1;
    var_a0 = 0;
    if ((s32) temp_a2 > 0) {
        temp_a3 = *(s32 *)((u8 *)&D_800875E0 + (var_v0 * 4));
        var_t0 = temp_a3;
loop_3:
        var_a0 += 1;
        if (temp_v1 == *var_t0) {
            return *temp_a3;
        }
        var_t0 += 1;
        if (var_a0 >= (s32) temp_a2) {
            goto block_6;
        }
        goto loop_3;
    }
block_6:
    var_v0 += 1;
    var_a1 += 1;
    if (var_v0 == 7) {
        return temp_v1;
    }
    goto loop_1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B2980/func_15085170.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B2980/func_150851E0.s")

void func_15085880(struct_eu_B2980 *arg0, s32 arg1) {
    arg0->unk31C->unk11B = arg1;
}

u8 func_15085890(struct_eu_B2980 *arg0) {
    return arg0->unk31C->unk11B;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B2980/func_150858A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B2980/func_15085710.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B2980/func_150859AC.s")

void func_15085ABC(s16 arg0)
{
  long var_s0;
  var_s0 = 0;
  if (D_800D18A8 == 0)
  {
    do
    {
      if ((1 << var_s0) & arg0)
      {
        func_15085710(var_s0, 5, (s32) D_800CC2D0[var_s0].health);
      }
      var_s0 += 1;
    }
    while (var_s0 != 4);
  }
}
