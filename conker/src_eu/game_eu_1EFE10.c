#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted forward declaration(s) for func_151C4B0C
extern void (*D_8008FF70[])(s32);


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C2600.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C284C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C2CE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C3080.s")

s32 func_151C33FC(u8 *arg0, u8 *arg1) {
    if (arg0 == arg1) {
        return 0;
    }
    if (*(s32 *)arg0 == 0) {
        return 0;
    }
    if (arg0[4] == 0xFF) {
        return 0;
    }
    return 1;
}

s32 func_151C3444(u8 *arg0, u8 *arg1) {
    if (arg0 == arg1) {
        return 0;
    }
    if (*(s32 *)arg0 == 0) {
        return 0;
    }
    if (arg0[4] == 0xFF) {
        return 0;
    }
    if (arg0[0x127] == 0xFF) {
        return 0;
    }
    return 1;
}

void func_151C34A0(s32 arg0, s32 arg1, u8 *arg2, s32 arg3, s32 arg4, s32 arg5) {
    func_151D535C(arg0, arg1, arg3, arg4, arg5, *(s32 *)(arg2 + 0x1B4), arg2 + 0x170, arg2[0xC], arg2[1]);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C34F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C384C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C3C88.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C40BC.s")

#ifdef NON_MATCHING
void func_151C491C(s32 arg0, u8 *arg1, s32 arg2) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f16;
    s32 var_a2;

    var_a2 = arg2;
    if (var_a2 > 0) {
        do {
            temp_f0 = (*(f32 *)((u8 *)arg1 + 0x10));
            temp_f12 = (*(f32 *)((u8 *)arg1 + 0x14));
            temp_f16 = (*(f32 *)((u8 *)arg1 + 0x18));
            var_a2 -= 1;
            (*(f32 *)((u8 *)arg1 + 0x10)) = (f32) (temp_f0 + (((*(f32 *)((u8 *)arg1 + 0x1C)) - temp_f0) * 0.228659f));
            (*(f32 *)((u8 *)arg1 + 0x14)) = (f32) (temp_f12 + (((*(f32 *)((u8 *)arg1 + 0x20)) - temp_f12) * 0.228659f));
            (*(f32 *)((u8 *)arg1 + 0x18)) = (f32) (temp_f16 + (((*(f32 *)((u8 *)arg1 + 0x24)) - temp_f16) * 0.228659f));
        } while (var_a2 > 0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C491C.s")
#endif
s32 func_15081A90(struct127 *, s32, s32, s32, f32, f32, f32, u8 *, f32, s32, s32, s32, s32, s32, s32);
typedef struct { s32 w0; s32 w4; u8 b8[0x18]; u8 b20[0x39]; u8 x59; u8 pad5A[0x1A]; } Res_151C4990;
s32 func_151C4990(u8 *arg0, u8 *arg1, f32 arg2)
{
  u8 ret;
  struct127 *t;
  Res_151C4990 r;
  f32 f;
  t = *((struct127 **) (arg1 + 0x90));
  ret = 1;
  if (arg1[0] & 4)
  {
    if ((*((f32 *) (arg1 + 0x8C))) < arg2)
    {
      f = (*((f32 *) (arg1 + 0x8C))) * (*((f32 *) (arg1 + 0x98)));
    }
    else
    {
      f = (*((f32 *) (arg1 + 0x98))) * arg2;
    }
    if (f != 0.0f)
    {
      func_15081A90(t, *((s32 *) (arg0 + 0x34)), *((s32 *) (arg0 + 0x38)), *((s32 *) (arg0 + 0x3C)), *((f32 *) (arg1 + 0x60)), *((f32 *) (arg1 + 0x64)), *((f32 *) (arg1 + 0x68)), (u8 *) (&r), f, 1, 0, !(arg1[0] & 8), *((s8 *) (arg1 + 0xA8)), 0, *((s32 *) (arg1 + 0xAC)));
      if (r.x59 >= 2)
      {
        func_151C34A0(r.w0, (s32) t, arg0, (s32) r.b8, (s32) r.b20, (s32) (&r));
        ret = 0;
        if (arg1) // fakematch: register order of ret/flags
        {
        }
      }
    }
  }
  return ret;
}

void func_151C4AC0(u8 *arg0, u8 *arg1, f32 arg2) {
    (*(f32 *)((u8 *)arg0 + 0x34)) += ((*(f32 *)((u8 *)arg1 + 4)) * arg2);
    (*(f32 *)((u8 *)arg0 + 0x38)) += ((*(f32 *)((u8 *)arg1 + 8)) * arg2);
    (*(f32 *)((u8 *)arg0 + 0x3C)) += ((*(f32 *)((u8 *)arg1 + 0xC)) * arg2);
}

s32 func_151C4B0C(s32 arg0, u8 *arg1, f32 arg2) {
    s32 temp_v1;
    s32 var_v1;
    s8 temp_v0;
    var_v1 = 1;
    (*(f32 *)((u8 *)arg1 + 0x8C)) = (f32) ((*(f32 *)((u8 *)arg1 + 0x8C)) - arg2);
    if ((*(f32 *)((u8 *)arg1 + 0x8C)) <= 0.0f) {
        if ((D_800E0940 != NULL) && ((*(u8 *)((u8 *)arg1 + 0)) & 1)) {
            temp_v1 = (*(s32 *)((u8 *)arg1 + 0x84));
            if (temp_v1 != 0) {
                ((void (*)(u8 *, s32)) D_800E0940)(arg1 + 0x30, (temp_v1 - (s32) D_800DBEF4) / 160);
            }
        }
        if ((*(u8 *)((u8 *)arg1 + 0)) & 2) {
            temp_v0 = (*(s8 *)((u8 *)arg1 + 0x9C));
            if (temp_v0 != -1) {
                D_8008FF70[temp_v0](arg0);
            }
        }
        var_v1 = 0;
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C4BF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C4DD0.s")

void func_151C5060(u8 *arg0, s32 *arg1, u8 arg2) {
    u8 *p = arg0 + 0x110;
    if (arg2 == 0x2D) {
        if (arg1[0] == *(s32 *)(p + 0x90)) {
            *(s32 *)(p + 0x90) = arg1[1];
            p[0x94] = ((u8 *)arg1)[9];
            return;
        }
        if (arg1[1] == *(s32 *)(p + 0x90)) {
            *(s32 *)(p + 0x90) = arg1[0];
            p[0x94] = ((u8 *)arg1)[8];
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C50BC.s")
