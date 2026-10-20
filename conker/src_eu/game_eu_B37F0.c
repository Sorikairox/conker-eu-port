#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_15088CA0(u8 *);

extern s8 D_800D27B9;

extern s32 D_800D27B4;

extern s8 D_800D27B8;


u8 *func_1502B5C8(s32, s32, s32, s32);
s32 func_15086058();
extern s16 D_80087634;

void func_15085FE0(s32 arg0) {
    u8 *temp_v0;

    temp_v0 = func_1502B5C8(0, 2, 0x19, arg0);
    if (temp_v0 == NULL) {
        D_80087630 = 0;
        D_80087634 = 0;
        D_800D2778 = NULL;
    } else {
        D_80087630 = (*(s16 *)temp_v0);
        D_80087634 = (*(s16 *)((u8 *)temp_v0 + 2));
        D_800D2778 = temp_v0 + 4;
    }
    func_15086058();
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15086058.s")

s32 func_15086218(f32 arg0) {
    s32 i = 0;

    while (D_800D2788[i] <= arg0) {
        i++;
    }
    return D_800D2770[i];
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15086268.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15086508.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_150867D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15087040.s")

void func_150870E0(s32 arg0) {
    s32 temp_v1 = D_800D2778[arg0].unk4;

    func_150A3674(3, 0xB, D_800D2778[arg0].unk0, D_800D2778[arg0].unk2, temp_v1);
}

s32 func_1508712C(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    if ((arg0 < 0) || (arg0 >= D_80087630)) {
        return 0;
    }
    *arg1 = (f32) D_800D2778[arg0].unk0;
    *arg2 = (f32) D_800D2778[arg0].unk2;
    *arg3 = (f32) D_800D2778[arg0].unk4;
    return 1;
}

s32 func_150871B8(s32 arg0) {
    s32 i;

    for (i = 0; i < D_80087630; i++) {
        if (arg0 == D_800D2778[i].unk7) {
            return i;
        }
    }
    return 0xFF;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15087204.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15087540.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_150877C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15088130.s")

s32 func_15088D24(u8, u8, s32);
void func_1508823C(s32 arg0, s32 arg1) {
    struct_eu_80087640 *temp_v1;
    s32 temp_v0;
    if (D_80087640 != NULL) {
        temp_v1 = &D_80087640[arg0];
        if (arg1 != (s8) temp_v1->pad28[7]) {
            if (arg1 != 0) {
                temp_v0 = func_15088D24(temp_v1->pad28[3], temp_v1->pad28[4], 1);
                temp_v1->pad28[5] = temp_v0;
                temp_v1->pad28[6] = func_15088D24(temp_v1->pad28[4], temp_v0, 1);
            }
            temp_v1->pad28[7] = (u8) arg1;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_150882C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15088360.s")

void func_15088434(s32 arg0, s32 arg1) {
    struct_eu_80087640 *temp_v1;

    if (D_80087640 != NULL) {
        temp_v1 = &D_80087640[arg0];
        temp_v1->unk31 = arg1;
    }
}

void func_1508845C(s32 arg0, s32 arg1) {
    struct_eu_80087640 *temp_v1;

    if (D_80087640 != NULL) {
        temp_v1 = &D_80087640[arg0];
        temp_v1->unk4 = arg1 * (1.0f / 256);
    }
}

struct216 *func_1507BB28(s32, s32);

s32 func_1508849C(struct_eu_80087640 *arg0, struct127 *arg1, s32 arg2) {
    struct126 *temp_v0;

    temp_v0 = arg1->unk31C;
    if (temp_v0->unk120 != 0) {
        return 1;
    }
    if (D_800D18A0 & (1 << (arg1 - D_800CC2D0))) {
        return 1;
    }
    temp_v0->unk84 = 1;
    arg1->interaction_state = 0xC;
    arg1->unk232 = arg2;
    D_800D154C = arg1;
    D_800C3E78 = *(s8 *)&arg0->unk31;
    arg1->unk218 = func_1507BB28(0, arg2);
    arg1->unk21C = 0;
    arg1->immune = 0xFF;
    arg0->pad28[8] = 2;
    return 0;
}

s32 func_1508849C(struct_eu_80087640 *, struct127 *, s32); // 3 params: the asm never reads a3 (s87)
extern s8 D_800D27BA;

s32 func_15088568(s32 arg0, s32 arg1) {
    struct_eu_80087640 *temp_a0;
    struct127 *temp_a1;
    s8 temp_v1;
    s32 var_a2;
    struct_eu_80087640 *sp1C;

    var_a2 = 0;
    if (D_80087640 == NULL) {
        return 0;
    }
    temp_a0 = &D_80087640[arg0];
    temp_v1 = (s8) temp_a0->pad28[8];
    temp_a1 = &D_800CC2D0[(s8) temp_a0->unk31];
    if (temp_v1 == 0) {
        sp1C = temp_a0;
        var_a2 = func_1508849C(temp_a0, temp_a1, arg1);
    } else if (temp_v1 == 1) {
        temp_a0->pad28[8] = 2;
        temp_a1->immune = 0xFF;
    }
    temp_a0->pad28[2] = (u8) D_800D27BA;
    D_800D27BA += 1;
    return var_a2;
}

s32 func_1508863C(s32 arg0) {
    struct_eu_80087640 *temp_a0;

    if (D_80087640 == NULL) {
        return 0;
    }
    temp_a0 = &D_80087640[arg0];
    return temp_a0->unk0 * 256.0f;
}

s32 func_15088688(s32 arg0) {
    struct_eu_80087640 *temp_a0;
    s16 temp_a2;

    if (D_80087640 == NULL) {
        return 0;
    }
    temp_a0 = &D_80087640[arg0];
    temp_a2 = temp_a0->unk24;
    return (temp_a2 * 16) + (s32)(temp_a0->unk8 * 16.0f);
}

s32 func_150886E0(s32 arg0) {
    struct_eu_80087640 *temp_a0;

    if (D_80087640 == NULL) {
        return 0;
    }
    temp_a0 = &D_80087640[arg0];
    return temp_a0->unk14 * 0.8f;
}

s32 func_1508872C(s32 arg0) {
    struct_eu_80087640 *temp_a0;

    if (D_80087640 == NULL) {
        return 0;
    }
    temp_a0 = &D_80087640[arg0];
    return temp_a0->unk27;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15088760.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_1508882C.s")

// K&R: func_15088BFC calls this without the argument.
s32 func_150889D8(arg0)
    struct127 *arg0;
{
    s32 idx;
    s32 i;
    s32 n;
    struct_eu_80087640 *p;

    idx = arg0 - D_800CC2D0;
    if (D_80087640 == NULL) {
        return -1;
    }
    if (idx == 0) {
        return 0;
    }
    i = 1;
    n = D_800D27B8 + D_800D27B9;
    p = D_80087640 + 1;
    if (n >= 2) {
        for (;;) {
            if (idx == (s8)p->unk31) {
                return i;
            }
            i++;
            p++;
            if (i < n) { // fakematch: continue/break form keeps the loop rolled and the bnel shape
                continue;
            }
            break;
        }
    }
    return -1;
}

void func_15088A68(s32 arg0, s32 arg1)
{
  s32 a;
  s32 b;
  if (D_80087640 != 0) {
    a = (s8)D_80087640[arg1].unk31;
    b = (s8)D_80087640[arg1].pad28[8];
    bcopy(&D_80087640[arg0], &D_80087640[arg1], 0x84);
    D_80087640[arg1].unk31 = a;
    D_80087640[arg1].pad28[8] = b;
  }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15088B08.s")

s32 func_150889D8();

void func_15088BFC(void) {
    s32 temp_v0;

    if (D_80087640 != NULL) {
        temp_v0 = func_150889D8();
        D_80087640[temp_v0].unk31 = 0;
        D_800D27B4 &= ~(1 << (temp_v0 - D_800D27B8));
    }
}

s32 func_15088C74(void) {
    if (D_80087640 == NULL) {
        return 0;
    }
    return D_80087640->unk46 == 0xFF;
}

void func_15088CA0(u8 *arg0) {
    (*(s8 *)((u8 *)arg0 + 0x2B)) = 0;
    (*(s8 *)((u8 *)arg0 + 0x2C)) = 0;
    (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
    (*(s8 *)((u8 *)arg0 + 0x2E)) = 0;
    (*(s8 *)((u8 *)arg0 + 0x28)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x1C)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x18)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x20)) = -1;
    (*(s8 *)((u8 *)arg0 + 0x2F)) = 0;
    (*(f32 *)((u8 *)arg0 + 8)) = 0.0f;
    (*(f32 *)arg0) = 0.5f;
    (*(f32 *)((u8 *)arg0 + 4)) = 0.5f;
    (*(s16 *)((u8 *)arg0 + 0x24)) = 0;
    (*(s8 *)((u8 *)arg0 + 0x26)) = 0;
    (*(s8 *)((u8 *)arg0 + 0x27)) = 0;
    (*(s8 *)((u8 *)arg0 + 0x31)) = 0;
    (*(f32 *)((u8 *)arg0 + 0xC)) = 0.0f;
    (*(f32 *)((u8 *)arg0 + 0x14)) = 0.0f;
    (*(s8 *)((u8 *)arg0 + 0x33)) = 2;
    (*(s8 *)((u8 *)arg0 + 0x30)) = 0;
    (*(s8 *)((u8 *)arg0 + 0x2A)) = 0x7F;
    (*(s8 *)((u8 *)arg0 + 0x49)) = 0;
    (*(f32 *)((u8 *)arg0 + 0x10)) = 1.0f;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15088D24.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15088E84.s")

f32 func_15144BC8(f32);
f32 func_15049AD0(s32 *, s32, f32);
f32 func_15049B94(s32 *, s32, f32, s32 *);
s32 func_15088E84(struct_eu_80087640 *, f32); // 2 params: the asm never reads a2 (s87)
s32 func_150893AC(struct_eu_80087640 *, s32 *, s32 *, s32 *);

void func_150891D4(u8 *arg0)
{
  u8 *new_var;
  u8 *new_var2;
  s32 sp98[2];
  s32 sp88[4];
  s32 sp78[4];
  s32 sp68[4];
  f32 temp_f0;
  s16 temp_v0_2;
  s32 temp_v0;
  s32 var_v0;
  struct_eu_80087640 *temp_s4;
  struct_eu_800D2778 *temp_a1;
  u8 *var_v1;
  u8 temp_a0;
  u8 var_s0;
  temp_v0 = func_150889D8(arg0);
  if (temp_v0 >= 0)
  {
    temp_s4 = &D_80087640[temp_v0];
    temp_s4->unk0 = 0.5f;
    temp_s4->unk4 = 0.5f;
    temp_s4->unk8 = 0.5f;
    do
    {
      var_s0 = 0;
      var_v0 = 0;
      var_v1 = (u8 *) &D_800D2778[temp_s4->pad28[4]];
      do
      {
        temp_a0 = var_v1[9];
        var_v0 += 1;
        if (temp_a0 != 0xFF)
        {
          temp_a1 = &D_800D2778[temp_a0];
          if (temp_a1->pad8[6] == 4)
          {
            var_s0 = temp_a1->pad8[7];
          }
        }
        var_v1 += 1;
      }
      while (var_v0 != 5);
      if (var_s0)
      {
        func_15088E84(temp_s4, 1.0f);
      }
    }
    while (var_s0 != 0);
    temp_s4->unk8 = 0.0f;
    func_150893AC(temp_s4, sp88, sp78, sp68);
    *((f32 *) (((u8 *) arg0) + 0x14)) = func_15049B94(sp88, 0, temp_s4->unk8, &sp98[1]);
    new_var2 = ((u8 *) arg0) + 0x18; // fakematch: permuter temp
    *((f32 *) new_var2) = func_15049AD0(sp78, 0, temp_s4->unk8);
    *((f32 *) (((u8 *) arg0) + 0x1C)) = func_15049B94(sp68, 0, temp_s4->unk8, sp98);
    temp_f0 = func_15144BC8(((f32) (func_1505A630(*((f32 *) (((u8 *) temp_s4) + 0x10)), *((f32 *) (((u8 *) temp_s4) + 0xC)), 0) + 0x8000)) * 0.005493164f);
    new_var = (u8 *) arg0; // fakematch: permuter temp
    *((f32 *) (new_var + 0x40)) = temp_f0;
    temp_v0_2 = (s32) (temp_f0 * 182.04445f);
    temp_v0_2 = temp_v0_2 - 0x4000;
    *((s16 *) (((u8 *) arg0) + 0x7A)) = temp_v0_2;
    *((s16 *) (((u8 *) arg0) + 0x78)) = temp_v0_2;
    *((s16 *) (((u8 *) arg0) + 0x76)) = temp_v0_2;
  }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_150893AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_150894F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15089664.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15089B68.s")
