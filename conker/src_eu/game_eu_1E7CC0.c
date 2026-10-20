#include <ultra64.h>
#include "functions.h"
#include "variables.h"


typedef struct {
    s8 u0;
    s8 u1;
    s8 u2;
    s16 u4;
    s32 u8_;
    s32 uC;
    s32 u10;
    s32 u14;
    s32 u18;
    s32 u1C;
    s32 u20;
    s8 u24;
    s8 u25;
    s32 u28;
    s32 u2C;
    s32 u30;
    s32 u34;
    s8 u38;
    u8 u39;
} Sa4b0;
typedef struct {
    u8 *p;
    u8 b;
} Ba4b0;
extern s8 D_800E0FFE[];
u8 *func_1513B5E0(Sa4b0 *, s32, s32, u8, s32);
u8 *func_151BA4B0(u8 *arg0, u8 arg1, s32 arg2)
{
  u8 *ret;
  Sa4b0 s;
  Ba4b0 b;
  s32 idx;
  if (arg0 == 0)
  {
    return 0;
  }
  b.p = arg0;
  b.b = arg0[0x3B];
  s.u0 = 2;
  s.u1 = -1;
  s.u2 = 3;
  s.u4 = 300;
  s.u30 = 9;
  s.u34 = 0x1AD;
  s.u39 = 0xFF;
  idx = (arg0 - ((u8 *) D_800CC2D0)) / 812;
  goto dummy_label_283214; // fakematch: label barrier (permuter) puts sw a0 (b.p) before the arg0[0x3B] load
  dummy_label_283214:
  ;
  if ((idx < 2) && (D_800E0FFE[idx] != 0))
  {
    if (D_80090130 == 2)
    {
      s.u39 = 0xFD;
    }
    else
      if (D_80090130 == 4)
    {
      if (idx == 0)
      {
        s.u39 = 0xFB;
      }
      else
      {
        s.u39 = 0xF7;
      }
    }
  }
  s.u8_ = 1;
  s.uC = 0x200205;
  s.u10 = 0x60600;
  s.u24 = 0;
  s.u25 = 0;
  s.u14 = 1;
  s.u18 = 0x36;
  s.u1C = 0x80;
  s.u20 = 0x20;
  s.u38 = 2;
  ret = func_1513B5E0(&s, 1, 8, arg1, arg2);
  if (ret != 0)
  {
    memcpy((ret + (*((s32 *) (ret + 0x50)))) + ((0, 0xF8)), &b, 8); // fakematch: comma expression (permuter) gives addu a0,v0,t9
  }
  return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BA634.s")

void func_151BAA18(u8 *arg0, s32 arg1, u8 arg2)
{
  u8 *q;
  s32 *p;
  s32 id;
  s32 t;
  q = arg0;
  q += *(s32 *)(arg0 + 0x50);
  q += 0xF8;
  p = (s32 *)q;
  id = p[0];
  t = id;
  if (arg2 == 0)
  {
    if ((t == ((s32 *)arg1)[0]) || (((u8 *) t)[0x3B] == ((u8 *) arg1)[4]))
    {
      func_1516972C((struct102 *)arg0);
    }
  }
  else
    if (arg2 == 0x2D)
  {
    t = ((s32 *)arg1)[0];
    if (t == *p)
    {
      p[0] = ((s32 *)arg1)[1];
      ((u8 *) p)[4] = ((u8 *) arg1)[9];
    }
    else if (((s32 *)arg1)[1] == *p)
    {
      p[0] = t;
      ((u8 *) p)[4] = ((u8 *) arg1)[8];
    }
  }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BAAC8.s")

extern s32 func_151BB690;

void func_151BB5F4(u8 *arg0) {
    func_1000FA64(0x4A7U, (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x14)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x18)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x1C)), 0x2000, 0x320U, 0xC8, (s32) &func_151BB690, arg0, 0, 8, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BB690.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BBBCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BC04C.s")

void func_151BC494(u8 *arg0, u8 arg1, s32 arg2) {
    s8 sp48[8];
    s32 sp3C[3];

    sp48[0] = 3;
    sp48[1] = -1;
    *(s16 *)(sp48 + 2) = (func_150ADA20() & 0xF) + 5;
    sp48[4] = 0;
    sp3C[0] = *(f32 *)(arg0 + 0);
    sp3C[1] = *(f32 *)(arg0 + 4);
    sp3C[2] = *(f32 *)(arg0 + 8);
    func_151602C0(sp48, sp3C, (func_150ADA20() % 21U) + 0x1E, 0xFF, 0x61, 0x36, 0xFFU, 0U, 0, arg1, arg2);
}

s32 func_150E856C(f32, s32, s32, s32, s16, u8, u8, u8, u8, u8, u8, s32);

void func_151BC56C(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    s32 pad;
    u32 sp40;
    f32 sp3C;

    sp3C = func_150ADA68();
    sp40 = func_150ADA20();
    func_150E856C((sp3C * 75.0f) + 75.0f, ((sp40 % 56U) + 0xC8) & 0xFF, arg0, arg1, (func_150ADA20() % 205U) + 0x12B, 1, 1, 0, 0, 0, (s32) arg2, 0);
}

struct225 *func_15160CDC(struct127 *arg0, u8 arg1, struct17 *arg2, struct17 *arg3, f32 arg4, u8 arg5, s16 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, u8 argB, u8 argC, u8 argD, u8 argE, s32 argF);
extern struct17 D_800AAB40;
extern struct17 D_800AAB4C;

void func_151BC624(struct127 *arg0) {
    if (arg0 != NULL) {
        func_15160CDC(arg0, 1, &D_800AAB40, &D_800AAB4C, 0.017699f, 2, 300, 255, 255, 255, 255, 1, 0, 0, 255, 1);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BC6B4.s")

void func_15143794(s16, s16, f32, void *);
s32 func_151A2C9C(f32 *, f32 *, f32 *, s32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_151BC920(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 *arg6) {
    f32 sp6C[9];
    f32 temp_f2;

    sp6C[6] = arg0;
    sp6C[7] = arg1;
    sp6C[8] = arg2;
    func_15143794((s16) (func_150ADA20() & 0xFF), (s16) ((func_150ADA20() % 65U) - 0x20), func_150ADA68() * 1680.0f * 0.01f, &sp6C[3]);
    temp_f2 = (func_150ADA68() * 202.0f) + 208.0f;
    sp6C[0] = 0.0f;
    sp6C[1] = 0.0f;
    temp_f2 = temp_f2 * 0.001f;
    sp6C[2] = 0.0f;
    sp6C[3] += -arg3 * D_800BEDC8 * temp_f2;
    sp6C[4] += -arg4 * D_800BEDC8 * temp_f2;
    sp6C[5] += -arg5 * D_800BEDC8 * temp_f2;
    func_151A2C9C(&sp6C[6], sp6C, &sp6C[3], 0x3F800000, ((func_150ADA68() * 1049.0f) + -1022.0f) * 0.001f, (func_150ADA68() * 124.0f) + 202.0f, (func_150ADA20() & 0xF) + 0x14, (func_150ADA20() % 201U) + 0x37, 0xF, 0xF, 0, -1, 0xCB, 0, 0, (s32) (*(u8 *)((u8 *)arg6 + 0xC)), (s32) (*(u8 *)((u8 *)arg6 + 1)));
}

s32 func_151BCB30(s32 **arg0) {
    s32 *temp_v0 = arg0[0x10];

    if (*temp_v0 == 0) {
        return 0;
    }
    return 1;
}

void func_151BCB54(void *arg0, void *arg1, u8 arg2) {
    s32 cur;
    u8 *temp_v0;
    cur = *(s32 *)((u8 *)arg0 + 0x40);
    if (arg2 == 0) {
        if (cur == (*(s32 *)((u8 *)arg1 + 0)) || ((*(u8 *)((u8 *)arg1 + 4)) == (*(u8 *)((u8 *)arg0 + 0x44)))) {
            func_1516972C(arg0);
        }
    } else {
        temp_v0 = (u8 *)arg0 + 0x40;
        if (arg2 == 0x2D) {
            if (*(s32 *)((u8 *)arg1 + 0) == *(s32 *)(temp_v0 + 0)) {
                *(s32 *)(temp_v0 + 0) = *(s32 *)((u8 *)arg1 + 4);
                *(u8 *)(temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 9);
                return;
            }
            if (*(s32 *)((u8 *)arg1 + 4) == *(s32 *)(temp_v0 + 0)) {
                *(s32 *)(temp_v0 + 0) = *(s32 *)((u8 *)arg1 + 0);
                *(u8 *)(temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 8);
            }
        }
    }
}

typedef struct { s32 x[3]; } S12_CBFC;
typedef struct { S12_CBFC pos; s16 t; u8 a; u8 pad[5]; } E20_CBFC;
s32 func_151BCBFC(u8 *arg0) {
    s16 temp_a2;
    s32 temp_lo;
    u8 *temp_v0;
    s32 var_a1;
    u8 *temp_t4;
    u8 *temp_v1;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x94));
    if (((*(s8 *)((u8 *)arg0 + 0x2C)) < 2) && ((*(u16 *)((u8 *)arg0 + 0x1E)) & 8)) {
        return 0;
    }
    var_a1 = (*(s8 *)((u8 *)arg0 + 0x2E));
    if (var_a1 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
        do {
            var_a1 -= 1;
            if (var_a1 < 0) {
                var_a1 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
            }
            temp_v1 = (var_a1 * 0x14) + temp_v0;
            (*(s16 *)((u8 *)temp_v1 + 0xC)) = (s16) ((*(s16 *)((u8 *)temp_v1 + 0xC)) - D_800BE9E4);
            temp_a2 = (*(s16 *)((u8 *)temp_v1 + 0xC));
            if (temp_a2 < 0) {
                if (var_a1 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
                    do {
                        (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2D)) + 1);
                        if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2D))) {
                            (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
                        }
                        (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) - 1);
                    } while (var_a1 != (*(s8 *)((u8 *)arg0 + 0x2D)));
                }
            } else if (temp_a2 < 0xA) {
                temp_lo = temp_a2 * 0x19;
                if (temp_lo < (s32) (*(u8 *)((u8 *)temp_v1 + 0xE))) {
                    (*(u8 *)((u8 *)temp_v1 + 0xE)) = (u8) temp_lo;
                }
            }
        } while (var_a1 != (*(s8 *)((u8 *)arg0 + 0x2D)));
    }
    if ((*(s8 *)((u8 *)arg0 + 0x2C)) > 0) {
        *(S12_CBFC *)(arg0 + 0x54) = ((E20_CBFC *)temp_v0)[*(s8 *)(arg0 + 0x2D)].pos;
    } else {
        (*(f32 *)((u8 *)arg0 + 0x54)) = 0.0f;
        (*(f32 *)((u8 *)arg0 + 0x58)) = 0.0f;
        (*(f32 *)((u8 *)arg0 + 0x5C)) = 0.0f;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BCD44.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BD040.s")

void func_151BD7CC(u8 *arg0, s32 *arg1, u8 arg2)
{
  s32 *p;
  s32 id;
  s32 t;
  p = *((s32 **) (arg0 + 0x98));
  id = p[0];
  t = id;
  if (arg2 == 0)
  {
    if ((t == arg1[0]) || (((u8 *) p)[4] == ((u8 *) arg1)[4]))
    {
      s32 blk_t; // fakematch: block-local declaration = basic-block boundary (unfilled jr ra delay slot, s69)
      arg0[0x30] = 0;
      *((u16 *) (arg0 + 0x1E)) |= 8;
    }
  }
  else
    if (arg2 == 0x2D)
  {
    t = arg1[0];
    if (t == *p)
    {
      p[0] = arg1[1];
      ((u8 *) p)[4] = ((u8 *) arg1)[9];
      return;
    }
    if (arg1[1] == *p)
    {
      p[0] = t;
      ((u8 *) p)[4] = ((u8 *) arg1)[8];
    }
  }
}

s32 func_151BD86C(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x28);

    if (*(s32 *)temp_v0 == 0) {
        return 0;
    }
    if (arg0[0x2C] != temp_v0[0x3B]) {
        return 0;
    }
    return 1;
}

typedef struct {
    u8 u0;
    u8 *u4;
    s8 u8_;
    f32 uC;
    f32 u10;
    f32 u14;
    f32 u18;
    f32 u1C;
    f32 u20;
    s8 u24;
    s16 u26;
    s16 u28;
    s16 u2A;
    s16 u2C;
    s8 u2E;
    s8 u2F;
    s8 u30;
    f32 u34;
    s8 u38;
    s8 u39;
} Sd8a8;
s32 func_15134DAC(Sd8a8 *, s32, ...);
void func_151BD8A8(u8 *arg0, s32 arg1, s32 arg2)
{
  Sd8a8 s;
  s16 zp; // fakematch: unused pad, puts z at sp+0x20
  s16 z;
  s32 v;
  if (arg0 != 0)
  {
    s.u0 = arg0[0x3B];
    s.u4 = arg0;
    s.u8_ = 1;
    s.u24 = 0;
    s.u26 = 0x32;
    s.u28 = 0x64;
    s.u2A = 0x12C;
    s.uC = 31.0f;
    s.u2E = 4;
    s.u2F = 4;
    s.u30 = 3;
    s.u38 = 5;
    s.u39 = -1;
    z = 0;
    s.u10 = -34.0f;
    s.u14 = -117.0f;
    s.u18 = 35.0f;
    s.u1C = -24.0f;
    s.u20 = -182.0f;
    s.u34 = 0.30061f;
    v = func_15134DAC(&s, 2);
    if (v != 0)
    {
      memcpy((void *) (v + 0x80), &z, 2);
    }
    s.uC = -s.uC;
    s.u18 = -s.u18;
    v = func_15134DAC(&s, 2);
    if (v != 0)
    {
      memcpy((void *) (v + 0x80), &z, 2);
    }
  }
}

s32 func_151BD9DC(s16 *arg0) {
    arg0[0x40] = 0;
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BD9EC.s")

f32 func_151BDD00(s16 *arg0) {
    s16 temp_v0 = arg0[0x40];
    f32 ret = (f32)temp_v0 * 2 * D_800AAC40 + D_800AAC44;

    arg0[0x40] = temp_v0 + D_800BE9E4;
    return ret;
}

s32 func_15131C7C();

void func_151BDD4C(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0xB0));
    if (((*(s32 *)temp_v0) != 0) && ((*(u8 *)((u8 *)temp_v0 + 4)) != 0xFF)) {
        (*(f32 *)((u8 *)arg0 + 0x4C)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x14));
        (*(f32 *)((u8 *)arg0 + 0x50)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x18));
        (*(f32 *)((u8 *)arg0 + 0x54)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x1C));
    }
    func_15131C7C();
}

void func_151BDDA4(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    func_151494E0(&tmp, 0x3B);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BDDD8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BE33C.s")

typedef struct {
    s32 a;
    u8 b;
} K_E65C;
void func_1516972C(struct102 *arg0);
s32 func_15169850(s32, u8, s32, s32, s32);
void func_151BE65C(struct102 *arg0, K_E65C *arg1, u8 arg2) {
    s32 t;
    K_E65C *p;
    struct102 **pa0 = &arg0; // fakematch: address taken keeps arg0 in its home slot
    K_E65C **pa1 = &arg1; // fakematch: address taken keeps arg1 in its home slot
    u8 *pa2 = &arg2; // fakematch: address taken keeps arg2 in its home slot

    if (*pa2 == 0x3B) {
        p = (K_E65C *)((u8 *)*pa0 + 0x28);
        t = (*pa1)->a == p->a;
        if (1) { // fakematch: empty block keeps the first compare in its own basic block
        }
        if (t || (*pa1)->b == p->b) {
            func_1516972C(*pa0);
        }
    } else {
        p = (K_E65C *)((u8 *)*pa0 + 0x28);
        func_15169850((s32)*pa1, *pa2, (s32)p, (s32)p + 4, (s32)*pa0);
    }
}

void func_151BE6E8(u8 *arg0)
{
  u8 *v = arg0 + 0x28; // fakematch: v defined first so IDO keeps it as a separate pointer (not folded into offsets)
  if (*(s32 *)(arg0 + 0x30) != 0) { func_1516972C(*(struct102 **)(arg0 + 0x30)); }
  if (*(struct102 **)(v + 0xC)) { func_1516972C(*(struct102 **)(v + 0xC)); } // fakematch: pointer-typed test gives one load (s32 test double-loads like line above)
  if (*(struct102 **)(v + 0x10)) { func_1516972C(*(struct102 **)(v + 0x10)); }
  if (*(struct102 **)(v + 0x14)) { func_1516972C(*(struct102 **)(v + 0x14)); }
}

void func_151BE768(struct260 * arg0) {
    func_151BE6E8(arg0);
    func_1514933C(arg0);
}

void func_151BE794(struct260 * arg0) {
    func_151BE6E8(arg0);
    func_15149368(arg0);
}

s32 func_151BE7C0(u8 *arg0) {
    f32 *s = (f32 *)(arg0 + 0x110);

    s[9] -= D_800BE9A4;
    if (s[9] < 0.0f) {
        s[9] = func_150ADA68() * 4.0f;
        s[6] = s[2] + s[4] * func_150ADA68();
    }
    *(f32 *)(arg0 + 0x2C) += (s[6] - *(f32 *)(arg0 + 0x2C)) * 0.35f;
    s[10] -= D_800BE9A4;
    if (s[10] < 0.0f) {
        s[10] = func_150ADA68() * 9.0f;
        if (func_150ADA20() & 1) {
            s[7] = s[3] + s[5] * func_150ADA68();
        } else {
            s[7] = s[3] + s[8] * func_150ADA68();
        }
    }
    *(f32 *)(arg0 + 0x30) += (s[7] - *(f32 *)(arg0 + 0x30)) * 0.4f;
    s[14] -= D_800BE9A4;
    if (s[14] < 0.0f) {
        s[14] = func_150ADA68() * 10.0f;
        s[13] = s[11] + s[12] * func_150ADA68();
    }
    s[15] += (s[13] - s[15]) * 0.4f;
    arg0[0x5C] = s[15];
    s[16] += (s[18] - s[16]) * 0.65000004f;
    s[17] += (s[19] - s[17]) * 0.65000004f;
    return 1;
}

s32 func_1513FAB4(s32, s32, f32 *, s16);

s32 func_151BEA68(struct102 *arg0, s16 arg1) {
    u8 *temp_v0;
    u8 *temp_v0_2;
    f32 sp20[2];

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x110));
    if (((*(u8 *)((u8 *)arg0 + 0x114)) != (*(u8 *)((u8 *)temp_v0 + 0x3B))) || (temp_v0_2 = (u8 *)arg0 + 0x110, ((*(s32 *)((u8 *)temp_v0 + 0)) == 0))) {
        func_1516972C(arg0);
        return 0;
    }
    if (!((*(u8 *)((u8 *)temp_v0_2 + 0x58)) & 1)) {
        return 0;
    }
    sp20[0] = (*(f32 *)((u8 *)temp_v0_2 + 0x54)) * (*(f32 *)((u8 *)temp_v0_2 + 0x40));
    sp20[1] = (*(f32 *)((u8 *)temp_v0_2 + 0x54)) * (*(f32 *)((u8 *)temp_v0_2 + 0x44));
    return func_1513FAB4(arg0, 0, sp20, arg1);
}

void func_151BEB08(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *temp_v0;
    s32 temp_v1;
    temp_v0 = (u8 *)arg0 + 0xB0;
    if (arg2 == 0x2D) {
        if (*(s32 *)(arg1 + 0) == *(s32 *)(temp_v0 + 0)) {
            *(s32 *)(temp_v0 + 0) = *(s32 *)(arg1 + 4);
            *(u8 *)(temp_v0 + 4) = *(u8 *)(arg1 + 9);
            return;
        }
        if (*(s32 *)(arg1 + 4) == *(s32 *)(temp_v0 + 0)) {
            *(s32 *)(temp_v0 + 0) = *(s32 *)(arg1 + 0);
            *(u8 *)(temp_v0 + 4) = *(u8 *)(arg1 + 8);
        }
        goto dummy_label; dummy_label: ; // fakematch: b + target-copied lw ra
    } else if (arg2 == 0) {
        temp_v1 = *(s32 *)(arg1 + 0);
        if (temp_v1 == *(s32 *)(temp_v0 + 0) || *(u8 *)(temp_v0 + 4) == *(u8 *)(arg1 + 4)) {
            func_1516972C(arg0);
        }
    }
}

void func_151BEBB4(u8 *arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, (s32)(arg0 + 0x110), (s32)(arg0 + 0x114), (s32)arg0);
}

void func_151BEBF4(u8 *arg0) {
    u8 *temp_v0 = arg0 + 0x110;

    if (*(s32 *)(arg0 + 0x160) != 0) {
        u8 *temp_v1 = *(u8 **)(temp_v0 + 0x50);

        temp_v1 += 0x28;
        *(s32 *)(temp_v1 + temp_v0[5] * 4 + 8) = 0;
    }
}

void func_151BEC24(struct210 * arg0) {
    func_151BEBF4(arg0);
    func_1513CA6C(arg0);
}

void func_151BEC50(struct210 * arg0) {
    func_151BEBF4(arg0);
    func_1513CAA0(arg0);
}

typedef struct { s32 a[4]; } V4_151BEC7C;
extern V4_151BEC7C D_800AAB88;
s32 func_151BEC7C(u8 *arg0) {
    u8 *v = arg0 + 0x110;
    V4_151BEC7C sp24;
    f32 f;
    sp24 = D_800AAB88;
    *(s16 *)(arg0 + 0x170) = *(s16 *)(arg0 + 0x170) - D_800BE9E4;
    if (*(s16 *)(arg0 + 0x170) < 0) {
        *(s8 *)(arg0 + 0x18) = sp24.a[func_150ADA20() & 3];
        *(s16 *)(arg0 + 0x170) = (func_150ADA20() & 7) + 3;
    }
    f = *(f32 *)(v + 0x48);
    *(f32 *)(v + 0x48) += (*(f32 *)(arg0 + 0x174) - f) * 0.65000004f;
    return 1;
}

void func_151BED38(u8 *arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, (s32)(arg0 + 0x180), (s32)(arg0 + 0x184), (s32)arg0);
}

void func_151BED78(u8 *arg0) {
    u8 *temp_v0 = arg0 + 0x170;

    if (*(s32 *)(arg0 + 0x178) != 0) {
        u8 *temp_v1 = *(u8 **)(temp_v0 + 8);

        temp_v1 += 0x28;
        *(s32 *)(temp_v1 + temp_v0[0xC] * 4 + 0x10) = 0;
    }
}

void func_151BEDA8(struct210 * arg0) {
    func_151BED78(arg0);
    func_151411A4(arg0);
}

void func_151BEDD4(struct210 * arg0) {
    func_151BED78(arg0);
    func_151411C4(arg0);
}
