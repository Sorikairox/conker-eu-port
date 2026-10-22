#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
extern u8 *D_800DC278;

s32 func_1503FAF0(u8 *arg0, s16 arg1, s16 arg2, s32 arg3, s32 arg4) {
    s16 temp_a0;
    s16 temp_a0_2;
    s16 temp_a0_3;
    s16 temp_a1;
    s16 temp_a2;
    s16 var_v0;
    u16 temp_v0;
    u8 *var_v1;

    temp_a2 = arg2;
    temp_a1 = arg1;
    arg1 = temp_a1;
    arg2 = temp_a2;
    func_1510F800(0, temp_a1, temp_a2);
    var_v1 = D_800DC278;
    if (var_v1 != NULL) {
loop_1:
        temp_a0 = (*(s16 *)((u8 *)var_v1 + 8));
        temp_v0 = (*(u16 *)((u8 *)var_v1 + 6));
        if (((temp_a0 + temp_v0) >= arg1) && (arg1 >= (temp_a0 - temp_v0))) {
            temp_a0_2 = (*(s16 *)((u8 *)var_v1 + 0xA));
            if (((temp_a0_2 + temp_v0) >= arg2) && (arg2 >= (temp_a0_2 - temp_v0))) {
                if (!((*(s16 *)((u8 *)var_v1 + 2)) & (1 << arg3))) {
                    goto block_15;
                }
                temp_a0_3 = (*(s16 *)((u8 *)var_v1 + 0xC));
                if (temp_a0_3 != 0) {
                    var_v0 = temp_a0_3;
                    goto block_11;
                }
                return 0;
            }
        }
        var_v0 = (*(s16 *)((u8 *)var_v1 + 4));
block_11:
        if (var_v0 != 0) {
            var_v1 += var_v0;
        } else {
            var_v1 = NULL;
        }
        if (var_v1 == NULL) {
            goto block_15;
        }
        goto loop_1;
    }
block_15:
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6D300/func_1503FAF0.s")
#endif
s32 func_1503FAF0(u8 *, s16, s16, s32, s32);

#ifdef NON_MATCHING
/* P48: the matched void body leaves func_1503FAF0's v0 in place and func_1502E7B4 tests it: return it explicitly. */
s32 func_1503FBF4(u8 *arg0, s32 arg1, s32 arg2) {
    return func_1503FAF0(arg0 + 0x320, (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x14)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x1C)), arg1, 1);
}
#else
void func_1503FBF4(u8 *arg0, s32 arg1, s32 arg2) {
    func_1503FAF0(arg0 + 0x320, (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x14)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x1C)), arg1, 1);
}
#endif

void func_1503FC54(void)
{
  int new_var; // fakematch: permuter temp for start + 1
  s32 i;
  s32 start;
  if (0 != D_800C67F0)
  {
    start = D_800C67F1;
    new_var = start + 1;
    i = new_var;
    if (i >= 0x19)
    {
      i = 0;
    }
    while (i != start)
    {
      if (D_800CC2D0[i].unkF8 & 0x800000)
      {
        D_800C67F1 = i;
        return;
      }
      i++;
      if (i >= 0x19)
      {
        i = 0;
      }
    }

  }
}
