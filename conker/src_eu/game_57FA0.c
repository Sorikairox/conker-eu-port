#include <ultra64.h>

#include "functions.h"
#include "variables.h"

#include "macros.h"

void func_1502AAF0(void) {
}

void func_1502AAF8(s32 arg0) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502AB04.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502AC88.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502AF04.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502B020.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502B110.s")
s32 *allocate_memory(s32, s32, s32, s32);
s32 func_10004074(s32 *);
s32 func_10006530(s32 *, s32, u32);
s32 func_150ADC50();

s32 func_1502B224(u8 *arg0, s32 arg1, s32 arg2, s32 arg3)
{
  s32 *temp_v0;
  u32 temp_t6;
  s32 sp24;
  u32 temp_v0_2;
  u32 var_s1;
  temp_t6 = ((arg2 & 0x0FFFFFFF) + 1) & (~1);
  var_s1 = temp_t6;
  if ((arg3 != 0) && (((u32) arg3) < temp_t6))
  {
    var_s1 = (u32) arg3;
  }
  if ((arg2 & 0x70000000) == 0x10000000)
  {
    temp_v0 = allocate_memory((s32) var_s1, 1, 2, 2);
    if (temp_v0 == 0)
    {
      return 0;
    }
    func_10004514((s32) arg0, temp_v0, (var_s1 + 0xF) & (~0xF), 1);
    sp24 = (*temp_v0) & 0x7FFFFFFF;
    var_s1 = func_10006530(temp_v0, arg1, D_8003809C);
    if (sp24 != ((0, var_s1))) // fakematch: comma expression flips beq operand order
    {
      D_8003C8E0 = 0x0C000036;
      func_150ADC50();
    }
    func_10004074(temp_v0);
    goto block_10;
  }
  func_10004514((s32) arg0, (u8 *) arg1, (var_s1 + 0xF) & (~0xF), 1);
  block_10:
  return (s32) var_s1;

}
#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502B350.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502B4A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502B5C8.s")
#include <stdarg.h>
s32 func_1502B350(u8 *, s32, s32 *);
s32 func_1502B4A8(s32, s32);
s32 func_1502B6BC(s32 *arg0, s32 arg1, s32 *arg2, s32 arg3, ...) {
    s32 *var_s2;
    s32 v;
    s32 sp44;
    s32 var_s0;
    u8 *var_s0_2;
    s32 sp38;
    va_list ap;
    var_s2 = &sp44;
    if (arg0 != NULL) {
        var_s2 = arg0;
    }
    *var_s2 = 1;
    var_s0_2 = D_AB2240;
    va_start(ap, arg3);
    if (arg3 != 0) {
        do {
            v = va_arg(ap, s32);
            if (*var_s2 != 0) {
                var_s0_2 += func_1502AC88(var_s0_2, v, &sp38);
            }
            *var_s2 = sp38 & 0x0FFFFFFF;
        } while (--arg3 != 0);
    }
    if (*var_s2 != 0) {
        var_s0 = func_1502B350(var_s0_2, sp38, var_s2);
        if ((*var_s2 != 0) && (var_s0 != 0)) {
            arg1 = func_1502B4A8(var_s0, arg1);
        } else {
            arg1 = 0;
        }
        if (arg2 != NULL) {
            *arg2 = arg1;
        }
    } else {
        var_s0 = 0;
    }
    return var_s0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502B7F0.s")
// void func_1502B7F0(s32 *arg0, s32 arg1, s32 arg2, s32 arg3) {
//     s32 sp38;
//     s32 sp34;
//     s32 temp_s1;
//     s32 offset;
//     s32 i;
//
//     sp38 = 1;
//     offset = &D_00AB1950; // 0xAB1950 - assets offsets table
//     temp_s1 = &arg2;
//
//     i = arg1;
//     if (i != 0) {
//         do {
//             temp_s1 = ALIGN4(temp_s1);
//             if (sp38 != 0) {
//                 offset += func_1502AC88(offset, temp_s1, &sp34);
//             }
//             sp38 = sp34 & 0xFFFFFFF;
//             temp_s1 += 1;
//         } while (i-- != 0);
//     }
//
//     if (sp38 != 0) {
//         *arg0 = func_1502B350(offset, sp34, &sp38);
//     } else {
//         *arg0 = 0;
//     }
// }

#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502B8E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502B9B4.s")
// NON-MATCHING: maybe 50% there?
// s32 func_1502B9B4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
//
//     s32 stack2[2];
//     s32 stack1[2];
//     s32 stack0[5];
//
//     s32 more;
//     s32 offset;
//     s32 *tmp;
//     s32 i;
//
//     more = 1;
//     offset = &D_00AB1950;
//     tmp = &arg1;
//
//     for (i = arg0; i != 0; i--) {
//         tmp = ALIGN4(tmp) + 4;
//         if (more != 0) {
//             offset += func_1502AC88(offset, tmp - 4, &stack0);
//         }
//         more = *stack0 & 0xFFFFFFF;
//     }
//
//     if (more != 0) {
//         more = ALIGN2(stack0[0] & 0xFFFFFFF);
//         if ((*stack0 & 0x70000000) == 0x10000000) {
//             if (((s32) &stack1 & 8) != 0) {
//                 *stack1 = &stack2;
//             }
//             func_10004514(offset, stack1, 0x10, 1); // decompress?
//             more = *stack1;
//         }
//     }
//
//     return more;
// }
