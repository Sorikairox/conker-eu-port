#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15030100.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_150302C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15030448.s")

void func_150305E0(s32 arg0, s32 arg1) {
    func_15030600(arg0, arg1, 0xFF);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15030600.s")

s32 func_15030448(u8 *, s32);

s32 func_150306D4(u8 *arg0) {
    s32 temp_s0;
    s32 var_a0;
    s32 var_s1;

    if ((*(u8 *)((u8 *)arg0 + 0x3B)) == 0) {
        return 0;
    }
    var_a0 = D_800C3EE0;
    var_s1 = 0;
    if (var_a0 != 0) {
        do {
            temp_s0 = (*(s32 *)((u8 *)var_a0 + 0x54));
            if ((*(u8 *)((u8 *)arg0 + 0x3B)) == (*(u8 *)var_a0)) {
                var_s1 = 1;
                func_15030448((u8 *) var_a0, 0);
            }
            var_a0 = temp_s0;
        } while (temp_s0 != 0);
    }
    return var_s1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15030758.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15030DE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15031044.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_150310F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15031284.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15031360.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_150314B4.s")

void func_15031C1C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *temp_v0 = func_15031C4C(arg0, arg1, arg3);
    if (temp_v0 != NULL) {
        temp_v0[3] = arg2;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15031C4C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15031CBC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15031D40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15031F04.s")

s32 func_1503211C(u8 *arg0, s32 arg1) {
    s32 var_v0 = *(s32 *)(arg0 + 0x38);

    if (*(s32 *)(arg0 + 0x38) >= 3) {
        var_v0 = 5 - var_v0;
    }
    *(s16 *)(arg0 + 0x18) = D_8009066C[var_v0];
    (*(s32 *)(arg0 + 0x38))++;
    if (*(s32 *)(arg0 + 0x38) >= 6) {
        *(s32 *)(arg0 + 0x38) = 0;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_1503216C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_150322B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_150334A8.s")

s32 func_1503F8A8(u8 *, s32, s32, s32, f32, s32);

s32 func_1503356C(u8 *arg0, s32 arg1) {
    u8 *var_s0;

    var_s0 = *(u8 **)(arg0 + 0x48);
    if (var_s0 == NULL) {
        return 0;
    }
    if ((*(u16 *)(var_s0 + 4) & 0x8000) != 0x8000) {
        func_1503F8A8(var_s0, 0, 0, 0x3F800000, 0.0f, 1);
        var_s0 = *(u8 **)(arg0 + 0x48);
    }
    if ((*(f32 *)(var_s0 + 0x18) - 1.0f) <= *(f32 *)(var_s0 + 8)) {
        return 1;
    }
    return 0;
}

s32 func_15033618(u8 *arg0, u8 *arg1)
{
  s32 temp_a1;
  if (D_800C35EA == 1)
  {
    return 0;
  }
  if (((*((u8 *) (((u8 *) arg1) + 0xAD))) == 0) && ((*((f32 *) (((u8 *) arg1) + 0x118))) < (*((f32 *) (((u8 *) arg1) + 0x180)))))
  {
    ;
    if (D_800BE9E4 < (*((s32 *) (((u8 *) arg0) + 0x38))))
    {
      *((s32 *) (((u8 *) arg0) + 0x38)) = (s32) ((*((s32 *) (((u8 *) arg0) + 0x38))) - D_800BE9E4);
      return 0;
    }
    return 1;
  }
  *((s32 *) (((u8 *) arg0) + 0x38)) = 0x19;
  return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15033698.s")

s32 func_15033730(u8 *arg0, u8 *arg1)
{
  switch (arg0[1]) {
  case 0x27:
  case 0x35:
    if (arg1[5] == 5) {
      arg0[2] = 0;
      *(s16 *)(arg0 + 0x22) += D_800BE9E4 * 0xAAA;
    }
    break;
  case 0x29:
    if (arg1[5] == 5) {
      arg0[2] = 0;
    }
    break;
  }
  return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_150337A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_150335C8.s")

s32 func_15033A7C(u8 *arg0, u8 *arg1) {
    u16 temp_v0;

    temp_v0 = (*(u16 *)((u8 *)arg1 + 0x84));
    if (((*(u8 *)((u8 *)arg0 + 1)) == 0x11) && ((temp_v0 == 0x3E) || (temp_v0 == 0x3D) || (temp_v0 == 0x41) || (temp_v0 == 0xD9) || (temp_v0 == 0x138) || (temp_v0 == 0x139))) {
        return 0;
    }
    return 1;
}

s32 func_15033AD4(u8 *arg0, s32 arg1) {
    *(s32 *)(arg0 + 0x38) += D_800BE9E4;
    if (*(s32 *)(arg0 + 0x38) >= 16) {
        *(s32 *)(arg0 + 0x38) = 0;
        *(s32 *)(arg0 + 0x3C) ^= 1;
    }
    *(s16 *)(arg0 + 0x18) = D_800906AC[*(s32 *)(arg0 + 0x3C)];
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15033B28.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15033CB8.s")

extern s32 func_15033ECC;

s32 func_15033DC8(u8 *arg0, u8 *arg1) {
    s32 temp_v0;

    if (D_800BE616 != 0) {
        func_1508B20C((*(f32 *)((u8 *)arg1 + 0x14)), (*(f32 *)((u8 *)arg1 + 0x18)), (*(f32 *)((u8 *)arg1 + 0x1C)), 900.0f);
    }
    if ((*(s32 *)((u8 *)arg0 + 0x38)) == 0) {
        temp_v0 = (*(s32 *)((u8 *)arg0 + 0x3C));
        if (temp_v0 < 0x19) {
            (*(s32 *)((u8 *)arg0 + 0x3C)) = (s32) (temp_v0 + D_800BE9E4);
        } else {
            (*(s32 *)((u8 *)arg0 + 0x3C)) = func_1000FA64(0x513U, (s16) (s32) (*(f32 *)((u8 *)arg1 + 0x14)), (s16) (s32) (*(f32 *)((u8 *)arg1 + 0x18)), (s16) (s32) (*(f32 *)((u8 *)arg1 + 0x1C)), 0x7D00, 0x3E8U, 0x1F4, (s32) &func_15033ECC, arg0, (s32) arg1, 0, 0);
            (*(s32 *)((u8 *)arg0 + 0x38)) = 0x513;
        }
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15033ECC.s")

s32 func_150340F0(s32 arg0, u8 *arg1) {
    if (arg1[5] == 3) {
        return 1;
    }
    return 0;
}

s32 func_15034118(u8 *arg0, s32 *arg1) {
    s32 n;
    u8 *p;
    u8 *next;
    n = 0;
    if (D_800C3EE0 == 0) {
        return 0;
    }
    p = (u8 *)D_800C3EE0;
    if (p != NULL) {
        do {
            next = *(u8 **)(p + 0x54);
            if (arg0[0x3B] == p[0]) {
                arg1[n] = (s32)p;
                n += 1;
            }
            p = next;
        } while (next != NULL);
    }
    return n;
}

u8 *func_15034174(u8 *arg0) {
    u8 *var_v1;
    u8 *next;
    for (var_v1 = (u8 *)D_800C3EE0; var_v1 != NULL; var_v1 = next) {
        next = *(u8 **)(var_v1 + 0x54);
        if (arg0[0x3B] == var_v1[0]) {
            return var_v1;
        }
    }
    return NULL;
}

void func_150341B4(s32 arg0, s32 arg1) {
    u8 *var_v0;
    u8 *next;
    for (var_v0 = (u8 *)D_800C3EE0; var_v0 != NULL; var_v0 = next) {
        next = *(u8 **)(var_v0 + 0x54);
        if (arg0 == var_v0[0]) {
            var_v0[0] = arg1;
        } else if (arg1 == var_v0[0]) {
            var_v0[0] = arg0;
        }
    }
}

s32 func_150341FC(s32 arg0, u8 *arg1) {
    u8 *temp_v1;

    if (D_800C35EA == 1) {
        return 0;
    }
    temp_v1 = (*(u8 **)((u8 *)arg1 + 0x31C));
    if ((temp_v1 != NULL) && ((*(u8 *)((u8 *)temp_v1 + 0x78)) != 9) && ((*(u8 *)((u8 *)temp_v1 + 0x11A)) != 3)) {
        (*(u8 *)((u8 *)temp_v1 + 0x11A)) = 0U;
        return 1;
    }
    return 0;
}

s32 func_15034260(s32 arg0, u8 *arg1) {
    u8 temp_v0;
    u8 *temp_v1;

    if (D_800C35EA == 1) {
        return 0;
    }
    temp_v1 = (*(u8 **)((u8 *)arg1 + 0x31C));
    if (temp_v1 != NULL) {
        temp_v0 = (*(u8 *)((u8 *)temp_v1 + 0x78));
        if ((temp_v0 != 0xC) && (temp_v0 != 0x16) && ((*(u8 *)((u8 *)temp_v1 + 0x11A)) != 3)) {
            (*(u8 *)((u8 *)temp_v1 + 0x11A)) = 0U;
            return 1;
        }
    }
    return 0;
}
