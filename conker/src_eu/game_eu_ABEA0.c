#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ABEA0/func_1507E690.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ABEA0/func_1507E7A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ABEA0/func_1507E8E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ABEA0/func_1507E9A8.s")

s32 func_15084E08();

s32 func_1507EA98(u8 *arg0)
{
  s32 temp_v0;
  u8 new_var;
  if ((*((u8 *) (((u8 *) arg0) + 0x1CA))) == 0)
  {
    goto dummy_label_268708;
    dummy_label_268708:
    ;

    ;
    goto block_9;
  }
  if ((*((u8 *) (((u8 *) arg0) + 0x70))) == (*((u8 *) (((u8 *) arg0) + 0x6F))))
  {
    return 1;
  }
  temp_v0 = func_15084E08();
  new_var = *((u8 *) (((u8 *) arg0) + 0x6F));
  if (temp_v0 == 0)
  {
    if (new_var == 0x15)
    {
      return 1;
    }
    goto block_9;
  }
  if (temp_v0 == 0x52)
  {
    return 1;
  }
  block_9:
  return 0;

}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ABEA0/func_1507EB1C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ABEA0/func_1507E7E4.s")

s32 func_1507ECE8(s32 arg0, s32 arg1) {
    s32 *p;
    s32 v;
    p = (s32 *)D_800D1C90[func_15084E08(arg0)];
    if (p != NULL) {
        p -= 2;
        v = *p;
        if (v != 0) {
            return (arg1 * 10) + v;
        }
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ABEA0/func_1507ED48.s")

void func_1507EDC8(s32 arg0, s32 arg1) {
}

s32 *func_1507EDD8(s32 arg0, s32 *arg1) {
    if (func_15084E08(arg0) == 0) {
        if (arg1 != NULL) {
            *arg1 = 5;
        }
        return &D_8009DCE0;
    }
    if (arg1 != NULL) {
        *arg1 = 0;
    }
    return NULL;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ABEA0/func_1507EE24.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ABEA0/func_1507EE9C.s")

void func_1507EF0C(struct127 *arg0) {
    func_1507EB4C(arg0, 0);
}

void func_1507EB4C(struct127 *arg0, s32 arg1) {
    if (arg1 != arg0->unk70) {
        arg0->unk70 = arg1;
        func_1507EE9C(arg0, arg1);
    }
}
