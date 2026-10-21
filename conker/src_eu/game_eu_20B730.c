#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_151E5D28(void);

extern u8 D_800D3260;

extern s8 D_80090144;

void func_1501C710(s32, s32, s32, s32, s32);


void func_151DDF20(void) {
    s32 i;
    for (i = 0; i < 0x1C; i++) {
        D_800E1010[i] = D_800901F4[i];
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151DDF6C.s")

s32 func_151DE074(s32 arg0) {
    return ~arg0;
}

s32 func_1000E934();
s32 func_1000F1A8();

void func_151DE080(void) {
    D_800D3260 = 0;
    func_1501C710(6, 0x1D, 0, 0, 1);
    D_800E0B94 = 3;
    D_80090144 = 0;
    D_800BEAC1 = 0;
    func_151E5D28();
    func_1000F1A8();
    func_1000E934();
    D_8008FD8C = 1;
    D_80090130 = 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151DE100.s")

void func_151E5AB8(void);
void func_151DEBB4(void) {
    func_151E5AB8();
    *(s32 *)((u8 *)D_800CC2D0 + 0x25C) |= 0x200;
    D_800CC2D0[0].y_position = 1000.0f;
    if (D_80000300 != 0) {
        D_800E0EC0 = 0;
    }
    if (D_800E0EC0 >= 0x119 && (D_800E0FCA & 0x8000)) {
        if (D_800E0EC0 < 0x190) {
            D_800E0EC0 = 0x190;
        }
        if (D_800E0EC0 >= 0x1F5 && D_800E0EC0 < 0x258) {
            D_800E0EC0 = 0x258;
        }
    }
    if (D_800E0EC0 >= 0x2C7) {
        D_800901C8 = 2;
        D_800E0B94 = 1;
        D_800D3260 = 0;
        func_1501C710(6, 0x21, 0, 0, 1);
        *(u8 *)&D_800E0FC6 = 0xFF;
    }
}

void func_151DED3C(void);

void func_151DECB4(void) {
    D_800E0EC0 = 0;
    D_800E0FC7 = 0;
    D_800E0FC8 = 0;
    D_800E0EBC = 0;
    D_800901C8 = 2;
    func_151DED3C();
}

void func_151DECFC(void) {
    D_80090114 = 4;
    D_800E0FC6 = 0;
    if (D_800901D0 == 0) {
        func_1500764C();
    }
}


void func_151DED3C(void) {
    D_800D3260 = 0;
    func_1501C710(6, 0x1D, 0, 0, 1);
    D_800E0B94 = 3;
    D_80090120 = 1;
    D_800901C8 = 2;
    D_80090144 = 0;
    (*(s8 *)((u8 *)D_80090174 + 0x3E)) = 0;
    (*(s8 *)((u8 *)D_80090174 + 0x2B)) = 5;
    (*(s8 *)((u8 *)D_80090174 + 0x2C)) = (s8) (*(s8 *)((u8 *)D_80090174 + 0x2B));
}

void func_151DEDC8(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151DEDD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151DF6A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151DFD0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E06D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E0BBC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E1174.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E1308.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E19AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E1EDC.s")

void func_151E5AB8(void);
void func_151E4B40(void);

void func_151E2A1C(void) {
    D_80090120 = 3;
    func_151E5AB8();
    func_151E4B40();
    D_80090120 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E2A54.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E2B9C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E2C88.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E2FCC.s")

void func_151E86A4(void);
extern s8 D_800E0FE1;
extern s8 D_800BEA38;
extern s8 D_80090134;
extern u8 D_800E0FC9;
extern s16 D_8009015C;
extern s8 D_800D27C8;
s32 func_1509D1EC(s32);
s32 func_1509D338(s8, s32 *);
s32 func_1509D49C(s8, u8, s32 *, s32 *);
extern s8 D_80090110;
extern s16 D_8009014C;
extern u8 D_80090154;
extern s8 D_800902B0;
extern u8 D_800902B4;
extern s32 D_800BE804;
extern u8 D_800E1001;

void func_151E3864(void) {

    s32 sp24[3];

    sp24[0] = 0;
    if (D_80090154 != 0) {
        sp24[1] = (s32) D_8009014C;
    } else {
        func_1509D338(D_800902B0, &sp24[2]);
        func_1509D49C(D_800902B0, D_800902B4, &sp24[1], sp24);
        func_1509D464();
    }
    func_15017790();
    func_1509D0A4(sp24[1]);
    func_1509D1EC(sp24[1]);
    D_800BE9F4 = func_1509CE40(sp24[1]);
    func_15085710(0, 9, sp24[0]);
    D_800BE804 = sp24[0];
    D_800DD2C0 = func_1509CE60(sp24[1]);
    if (D_80090154 == 2) {
        D_800DD2C0 = D_800E1001;
    }
    D_80090110 = 0;
    D_800D27C8 = 0;
    D_8009015C = 0;
    D_8008FDA8 = -1;
    D_800E0B94 = 0;
    D_800E0FC9 = 1;
    D_8008FD8C = 1;
    D_80090130 = 1;
    D_80090134 = 1;
    D_800BEA38 = 1;
    D_80087260 = 3;
    if (D_800E9D00 & 0x200) {
        D_80087260 = 0x33;
    }
    *D_80087270 = 0;
    D_800D18A8 = 0;
    D_800E0FE1 = 1;
    func_151E86A4();
    D_800D3260 = 1;
    func_1501C710(6, (s32) D_800BE9F4, func_1509CE60(sp24[1]), 0, 1);
}

void func_151E86A4(void);
extern s8 D_80090134;
extern s16 D_8009015C;
extern s8 D_800BEA38;
extern s8 D_800D27C8;
extern u8 D_800E0FC9;
extern s8 D_800E0FE1;

void func_151E3A1C(void) {
    D_80087260 = 3;
    if (D_800E9D00 & 0x200) {
        D_80087260 = 0x33;
    }
    *D_80087270 = 0;
    D_8008FD8C = 1;
    D_80090130 = 1;
    D_80090134 = 1;
    D_8009015C = 0;
    D_800BEA38 = 1;
    D_800D27C8 = 0;
    D_800E0B94 = 0;
    D_800D3260 = 0;
    func_1501C710(6, (s32) (s8) D_800BE3DF, (s32) D_800BE800, 0, 1);
    D_800E0FC9 = 1;
    D_800E0FE1 = 1;
    func_151E86A4();
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E3AE4.s")

s32 func_151F2CDC();
void func_151F2D6C(s32, s32);
extern s32 *D_800E0EB8;
void func_151E2FCC(void);

void func_151E49C8(void) {
    if ((u8) D_80090120 != 0) {
        D_80090120 = 0;
        return;
    }
    func_151E5AB8();
    if ((D_800E0FCA != 0) || (D_800C35EA != 1)) {
        if ((D_800C35EA == 1) && (func_151F2CDC() == 1)) {
            func_151F2D6C(0, 0x370C);
        }
        D_800E0B94 = 7;
        D_800E0EB8 = &func_151E2FCC;
        D_80090114 = 8;
    }
}

s32 func_1501D348(s32, s32, s32, s32, s32);
extern u8 D_800ABA76[][10];
extern s16 D_800ABB88[][2];
void func_151E4A78(void) {
    s8 *p;
    s8 temp_v1;
    s8 var_a1;
    temp_v1 = D_800ABA76[((s8 *)D_80090174)[0x42]][0];
    if (temp_v1 >= 0) {
        if (D_800E1030[0] != 0) {
            p = (s8 *)&D_800ABB88[temp_v1];
            var_a1 = p[3];
        } else {
            p = (s8 *)&D_800ABB88[temp_v1];
            var_a1 = p[2];
        }
        func_1501D348(*(s16 *)p, var_a1, 0, 0, 0);
        *(u8 *)&D_80090120 = 1; // fakematch: u8 store keeps the constant out of the CSE
        D_800E0B94 = 5;
        D_8008FD8C = 1;
        D_80090130 = 1;
        return;
    }
    func_151E2FCC();
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E4B40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E533C.s")

void func_151E5528(void) {
    D_800E0B94 = 10;
}

void func_151E553C(void) {
    if (D_800E0FCA & 0x8020) {
        D_800E0B94 = 4;
    }
}

void func_151E5564(void) {
    D_8009016C = 0;
    func_151E5D28();
    D_800E0B94 = 3;
    D_80090144 = 0;
    D_80090120 = 0;
    D_800D3260 = 0;
    func_1501C710(6, 0x1D, 0, 0, 1);
}

s32 func_151E5D54();
extern s32 *D_800E0EB8;
void func_151E5564(void);

void func_151E55C8(void) {
    func_151E5AB8();
    func_151E5D54();
    if (D_800E0EC0 >= 0x3E9) {
        D_800E0FCA |= 0x8000;
    }
    if (D_800E0FCA != 0) {
        D_800E0B94 = 7;
        D_800E0EB8 = &func_151E5564;
        D_80090114 = 8;
    }
}

extern f32 D_80090170;
extern f32 D_800ABE30;
extern f32 D_800ABE34;
extern f32 D_800ABE38;

void func_151E564C(void)
{
  unsigned int n; // fakematch: permuter temp
  int ff; // fakematch: constant in a register gives beq a2,v0 operand order
  s32 v;
  f32 f;
  v = *((u8 *) (&D_800E0FC6));
  ff = 0xFF; // fakematch
  D_80090170 = 1.0f - (((u32) v) / 255.0f);
  if (((u8) D_80090114) == 0xFF)
  {
    f = D_800DDDC8;
    if (D_800ABE30 < f)
    {
      v = (u8) (D_800E0FC6 = v + D_800BE9E4);
      if (v < 0x55)
      {
        D_800DDDD8 = D_800ABE34;
      }
      else
      {
        D_800DDDD8 = D_800ABE38;
      }
    }
    if (f < ((float) 1.0f))
    {
      return;
    }
    if (v < 0x6E)
    {
      return;
    }
  }
  else
  {
    n = (u8) D_80090114;
    if (v != ff)
    {
      v += D_800BE9E4 * n;
      if (v >= 0x100)
      {
        v = 0xFF;
      }
      D_800E0FC6 = v;
      return;
    }
  }
  *((u8 *) (&D_800E0FC6)) = 0xFF;
  D_80090114 = 8;
  D_80090170 = 1.0f;
  if (1) // fakematch: empty ifs on separate lines
  {
  }
  if (1)
  {
  }
  ((void (*)(void)) D_800E0EB8)();
}

void func_151E5798(void) {
    (*(f32 *)D_80090174) = 0.0f;
    (*(f32 *)((u8 *)D_80090174 + 4)) = 0.0f;
    (*(s8 *)((u8 *)D_80090174 + 0x2B)) = 0;
    (*(s16 *)((u8 *)D_80090174 + 0x20)) = 0;
    (*(s8 *)((u8 *)D_80090174 + 0x3E)) = 0;
    (*(s8 *)((u8 *)D_80090174 + 0x3F)) = 0;
    (*(s8 *)((u8 *)D_80090174 + 0x41)) = 0;
    (*(s8 *)((u8 *)D_80090174 + 0x43)) = 0;
    (*(s8 *)((u8 *)D_80090174 + 0x44)) = 0;
    (*(f32 *)((u8 *)D_80090174 + 0x10)) = 0.0f;
    (*(s8 *)((u8 *)D_80090174 + 0x2A)) = 0;
    (*(f32 *)((u8 *)D_80090174 + 0x14)) = 0.0f;
    (*(f32 *)((u8 *)D_80090174 + 0x18)) = 0.0f;
    (*(f32 *)((u8 *)D_80090174 + 0x1C)) = 0.0f;
    (*(f32 *)((u8 *)D_80090174 + 0xC)) = 0.0f;
    (*(f32 *)((u8 *)D_80090174 + 8)) = 0.0f;
}

void func_151E73A8(void);
extern u8 D_800E0F20[];
extern u8 D_800AB950[];
extern u8 D_800E0FC5;

void func_151E582C(void) {
    s32 i;

    i = 0;
    do {
        D_800E1010[i] = D_800901F4[i];
        i++;
    } while (i < 0x1C);
    D_800E0EC0 = 0;
    func_151E73A8();
    if (D_80090174 == NULL) {
        D_80090174 = D_800E0F20;
        func_151E5798();
        if (*(s8 *)(D_80090174 + 0x3E) == 1) {
            *(s8 *)(D_80090174 + 0x2C) = D_800AB950[*(s8 *)(D_80090174 + 0x2C)];
        }
    }
    func_15017790();
    D_800E0B94 = 11;
    D_800D3260 = 0;
    func_1501C710(6, 0x25, 0, 0, 1);
    D_800E0FC5 = D_800E0B94;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E5928.s")

void func_151E5AB8(void)
{
  f32 temp_f0;
  s32 var_v1_2;
  if (D_800E0B94 != 2)
  {
    if (((u8) D_800E0FC6) != 0)
    {
      var_v1_2 = ((u8) D_800E0FC6) - (D_800BE9E4 * ((u8) D_80090114));
      if (var_v1_2 < 0)
      {
        var_v1_2 = 0;
      }
      D_800E0FC6 = var_v1_2;
    }
    if (((D_80090174 != 0) && ((*((s8 *) (((u8 *) D_80090174) + 0x2B))) == 0)) && ((*((f32 *) (((u8 *) D_80090174) + 0xC))) > 0.0f))
    {
      temp_f0 = *((f32 *) (((u8 *) D_80090174) + 8));
      if (temp_f0 > 0.5f)
      {
        var_v1_2 = (s32) ((temp_f0 - 0.5f) * 524.0f);
        if (var_v1_2 >= 0x100)
        {
          var_v1_2 = 0xFF;
        }
        D_800E0FC6 = (s8) var_v1_2;
      }
    }
  }
}

void func_151E533C(void);
extern u8 D_800901CC;
extern u16 D_80090160;
extern u8 D_800E0EB6;
extern s8 D_800ABA70[][10];

void func_151E5B94(s32 arg0) {
    s32 i;

    D_800E0EC0 = 0;
    D_800901CC = 0;
    D_80087270[0] = 0;
    if (D_800BE616 != 0) {
        D_800E0B94 = 7;
        D_80090114 = 8;
        if (D_800ABA70[(s8)D_80090174[0x42]][7] != -1) {
            D_80090174[0x3F] = 4;
            D_800E0EB8 = (s32 *)&func_151E533C;
        } else {
            D_80090174[0x3F] = 3;
            D_800E0EB8 = (s32 *)&func_151DE080;
        }
        for (i = 0; i < D_80090130; i++) {
            *(s16 *)(D_80090174 + i * 12 + 0x6C) = *(s16 *)(*(u8 **)((u8 *)&D_800CC2D0[i] + 0x31C) + 0x1AA);
        }
        D_80090160 &= 0xE35F;
        D_800E0EB6 = arg0;
        if (D_800ABA70[(s8)D_80090174[0x42]][7] == -2) {
            if (arg0 == 0) {
                func_151E533C();
            } else {
                D_800E0EB8 = (s32 *)&func_151DE080;
                D_80090174[0x3F] = 3;
            }
        }
    } else {
        D_800E0B94 = 4;
    }
}

void func_151E5D28(void) {
    D_800843F0[0] = 0;
    D_800843F0[1] = 1;
    D_800843F0[2] = 2;
    D_800843F0[3] = 3;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E5D54.s")

void func_151E5DD8(void) {
    if (D_800E0EBC != 0) {
        D_800E0EBC = 0;
    }
}

s8 func_151E5DF8(void) {
    return D_80090168;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E5E08.s")

s32 func_151E6710(s32 arg0) {
    s8 var_v1;
    if ((D_800BE616 != 0) || (D_800E0B94 != 0)) {
        var_v1 = D_800E1030[arg0];
        if (var_v1 < 0) {
            var_v1 = 0;
        }
        return var_v1;
    }
    return arg0;
}

s8 func_151E6758(void) {
    if (D_800E101B != 0) {
        if (D_8008FD8C >= 5) {
            return D_80090130;
        }
        return D_8008FD8C;
    }
    return D_80090130;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E67A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E7110.s")

void func_151E73A8(void) {
    D_800E1003 = 0;
    D_800E1004 = 0;
    D_80090178 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E73C8.s")

extern f32 D_800ABE94;
u8 *func_151149AC(u8);
extern u8 D_80090360[][6];

void func_151E856C(void)
{
  s32 var_s0;
  u8 var_a0;
  u8 *temp_v0;
 var_s0 = 0; if ((!((*((f32 *) (((u8 *) D_80090174) + 8))) < D_800ABE94)) || ((*((s8 *) (((u8 *) D_80090174) + 0x3E))) != 0)) { do { if ((*((s8 *) (((u8 *) D_80090174) + 0x3E))) == 0) { var_a0 = D_80090360[var_s0][*((s8 *) (((u8 *) D_80090174) + 0x2C))];
      }
      else
      {
        var_a0 = D_80090360[var_s0][0];
      }
      temp_v0 = func_151149AC(var_a0);
      var_s0 += 1;
      if (temp_v0 != 0)
      {
        *((s32 *) (((u8 *) temp_v0) + 0x80)) = 2;
      }
    }
    while (var_s0 != 2);
  }
}

extern s8 D_800E1019;

void func_151E8648(void) {
    if (D_800E1019 == 2) {
        func_10017870(1U);
        return;
    }
    if (D_800E1019 == 0) {
        func_10017870(2U);
        return;
    }
    func_10017870(4U);
}

extern s32 func_151DE100;
void func_151E86A4(void) {
    void (*new_var)(OSTask *tp); // fakematch: permuter temp pinning osSpTaskLoad address
    s32 var_v1;
    s32 *var_v0;
    func_151E8648();
    new_var = osSpTaskLoad; // fakematch
    var_v1 = 0;
    for (var_v0 = &func_151DE100; (u32) var_v0 < (u32) func_151DECB4; var_v0++) {
        var_v1 += *var_v0;
        if (!new_var) { } // fakematch
    }
    if (var_v1 != 0xBB9FE01C) {
        *((s32 *) new_var) = 0;
        if (func_151DECB4) { } // fakematch
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E870C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E8998.s")

s32 func_1517F54C();
extern s16 D_800E0EB0;

void func_151E89C0(void) {
    if (D_800E0B94 != 8) {
        if (func_1517F54C() == 0) {
            D_800E0EC0 = 0;
        }
        if (D_800E0EC0 >= 0xA1) {
            D_8009016C = 0;
            D_800E0B94 = 8;
            D_8008FD8C = 1;
            D_80090130 = 1;
            D_80090144 = 0;
            D_800E0EB0 = -2;
            D_800E0EC0 = 0;
            D_800D2E43 = 1;
        }
    }
}

void func_151E5AB8(void);

void func_151E8A64(void) {
    func_151E5AB8();
    if (D_800E0EB0 == -1 && D_800E0EC0 >= 0x79) {
        D_800E0B94 = 9;
        D_800E0EC0 = 0;
        D_8009016C = 0xFF;
        D_800E0EB0 = 0;
        func_1501C710(6, 0x1D, 0, 0, 1);
        return;
    }
    if (D_800E0EB0 == -2) {
        D_800E0EB0 = 0;
    }
    if (D_800E0EC0 >= 0x173 && D_800E0EB0 >= 0) {
        while (((u8 **)D_800E1008)[D_800E0EB0][0] != 0x2A) {
            D_800E0EB0++;
        }
        D_800E0EB0++;
        if (((u8 **)D_800E1008)[D_800E0EB0][0] == 0x3D) {
            D_800E0EB0 = -1;
        }
        D_800E0EC0 = 0;
    }
}

s32 func_1501D348(s32, s32, s32, s32, s32);

void func_151E8B94(void) {
    if (D_800E0EB0 == 0) {
        D_800E0EB0 = -1;
        func_1501D348(0x1D, 6, 0, 0, 0);
    }
    func_151E5AB8();
    if (func_1517F54C() == 0) {
        D_800E0EC0 = 0;
    }
    if (D_800E0EC0 >= 0x65) {
        func_151E5798();
        D_80090144 = 0;
        D_800E0B94 = 1;
        D_800E0EC0 = 0;
        D_800D3260 = 0;
        func_1501C710(6, 0x21, 0, 0, 1);
    }
}
