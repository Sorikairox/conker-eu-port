#include <ultra64.h>
#include "functions.h"
#include "variables.h"


typedef struct { f32 x, y, z; } V368D0;
typedef struct { V368D0 pos; s16 u80; s16 u82; s32 u84; u8 pad88; s8 u89; u8 pad8A[2]; s32 pad8C; } SA68D0;
typedef struct { u8 *u44; u8 u48; u8 pad49[3]; V368D0 pos; f32 u58, u5C, u60, u64, u68, u6C; } SB68D0;
void *memcpy(void *, const void *, u32);
void func_151B68D0(u8 *arg0, u8 arg1, s32 arg2) {
    SA68D0 a;
    s32 pad; // fakematch: frame padding between the two spawn structs
    SB68D0 b;
    u8 *r;

    a.u89 = 10;
    a.pos.x = *(f32 *)(arg0 + 0x14);
    a.pos.y = *(f32 *)(arg0 + 0x18);
    a.pos.z = *(f32 *)(arg0 + 0x1C);
    a.u80 = 300;
    a.u82 = 6;
    b.u44 = arg0;
    b.u48 = arg0[0x3B];
    b.pos = a.pos;
    b.u58 = 0.0f;
    b.u5C = 0.0f;
    b.u64 = -16384.0f;
    b.u60 = -16384.0f;
    b.u68 = 0.0f;
    a.u84 = 0xD;
    r = func_15147FF0(&a, 0x30, 0x1C, 0xB, 0xB, 0xB, 0, 0, 0, arg1, arg2);
    if (r != NULL) {
        memcpy(*(void **)(r + 0x98), &b, sizeof(b));
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E40E0/func_151B69D0.s")

#ifdef NON_MATCHING
f32 func_15143E64(void *);

s32 func_151B6B84(u8 *arg0) {
    struct {
        f32 u84;
        f32 u88;
        f32 u8C;
        u8 pad90[0x10];
        f32 uA0;
        f32 uA4;
        f32 uA8;
        u8 padAC[0x4];
        s32 uB0;
        u8 * uB4;
    } sp;
    f32 sp58;
    f32 sp50;
    f32 sp48;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f24;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f6;
    f32 var_f16;
    f32 var_f18;
    f32 var_f20;
    s8 temp_v0_3;
    u8 *temp_a2;
    u8 *temp_t2;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_a2 = (*(u8 **)((u8 *)arg0 + 0x98));
    temp_v0 = (*(u8 **)((u8 *)temp_a2 + 0));
    if (((*(s32 *)((u8 *)temp_v0 + 0)) == 0) || ((*(u8 *)((u8 *)temp_a2 + 4)) != (*(u8 *)((u8 *)temp_v0 + 0x3B))) || ((*(f32 *)((u8 *)temp_v0 + 0x3C)) < 15.0f)) {
        (*(s8 *)((u8 *)arg0 + 0x30)) = 0;
        (*(u16 *)((u8 *)arg0 + 0x1E)) = (u16) ((*(u16 *)((u8 *)arg0 + 0x1E)) | 8);
        return 1;
    }
    (*(f32 *)((u8 *)arg0 + 0x10)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x14));
    (*(f32 *)((u8 *)arg0 + 0x14)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x18));
    (*(f32 *)((u8 *)arg0 + 0x18)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x1C));
    sp.uA0 = (*(f32 *)((u8 *)arg0 + 0x10)) - (*(f32 *)((u8 *)temp_a2 + 8));
    sp.uA4 = (*(f32 *)((u8 *)arg0 + 0x14)) - (*(f32 *)((u8 *)temp_a2 + 0xC));
    sp.uB0 = (*(s32 *)((u8 *)arg0 + 0x94));
    sp.uB4 = temp_a2;
    sp.uA8 = (*(f32 *)((u8 *)arg0 + 0x18)) - (*(f32 *)((u8 *)temp_a2 + 0x10));
    temp_f0 = func_15143E64(&sp.uA0);
    (*(f32 *)((u8 *)sp.uB4 + 0x14)) = (f32) ((*(f32 *)((u8 *)sp.uB4 + 0x14)) + (temp_f0 * 0.003722f * D_800BE9A4));
    temp_f2 = (*(f32 *)((u8 *)sp.uB4 + 0x14));
    (*(f32 *)((u8 *)sp.uB4 + 0x1C)) = (f32) ((*(f32 *)((u8 *)sp.uB4 + 0x1C)) + (temp_f0 * 4.409548f));
    sp58 = temp_f2;
    if (temp_f2 > 1.0f) {
        temp_t2 = sp.uB4 + 8;
        temp_f2_2 = 1.0f / sp58;
        (*(f32 *)((u8 *)(&sp.u84) + 0)) = (*(f32 *)((u8 *)temp_t2 + 0));
        (*(s32 *)((u8 *)(&sp.u84) + 4)) = (s32) (*(s32 *)((u8 *)temp_t2 + 4));
        var_f18 = (*(f32 *)((u8 *)sp.uB4 + 0x18)) + D_800BE9A4;
        (*(s32 *)((u8 *)(&sp.u84) + 8)) = (s32) (*(s32 *)((u8 *)temp_t2 + 8));
        temp_f12 = (*(f32 *)((u8 *)sp.uB4 + 0x20));
        var_f20 = (*(f32 *)((u8 *)sp.uB4 + 0x24));
        var_f16 = temp_f12;
        temp_f24 = -(var_f18 * temp_f2_2);
        sp50 = ((*(f32 *)((u8 *)sp.uB4 + 0x1C)) - temp_f12) * temp_f2_2;
        sp48 = temp_f0 * temp_f2_2;
        do {
            temp_v0_2 = ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x1C) + sp.uB0;
            (*(f32 *)((u8 *)temp_v0_2 + 0)) = (f32) (*(f32 *)((u8 *)(&sp.u84) + 0));
            (*(s32 *)((u8 *)temp_v0_2 + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u84) + 4));
            (*(s8 *)((u8 *)temp_v0_2 + 0x10)) = 0x9B;
            (*(f32 *)((u8 *)temp_v0_2 + 0x14)) = var_f16;
            (*(s32 *)((u8 *)temp_v0_2 + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u84) + 8));
            temp_f6 = 13.0f - var_f18;
            var_f18 += temp_f24;
            (*(f32 *)((u8 *)temp_v0_2 + 0xC)) = temp_f6;
            if (var_f16 > 16384.0f) {
                do {
                    (*(f32 *)((u8 *)temp_v0_2 + 0x14)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x14)) - 32768.0f);
                } while ((*(f32 *)((u8 *)temp_v0_2 + 0x14)) > 16384.0f);
            }
            (*(f32 *)((u8 *)temp_v0_2 + 0x18)) = var_f20;
            (*(s8 *)((u8 *)arg0 + 0x2E)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2E)) + 1);
            if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2E))) {
                (*(s8 *)((u8 *)arg0 + 0x2E)) = 0;
            }
            temp_v0_3 = (*(s8 *)((u8 *)arg0 + 0x2D));
            (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) + 1);
            if (temp_v0_3 == (*(s8 *)((u8 *)arg0 + 0x2E))) {
                (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) (temp_v0_3 + 1);
                if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2D))) {
                    (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
                }
                (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) - 1);
            }
            sp.u84 += sp.uA0 * temp_f2_2;
            sp.u88 += sp.uA4 * temp_f2_2;
            var_f16 += sp50;
            sp.u8C += sp.uA8 * temp_f2_2;
            var_f20 += sp48;
            (*(f32 *)((u8 *)sp.uB4 + 0x14)) = (f32) ((*(f32 *)((u8 *)sp.uB4 + 0x14)) - 1.0f);
        } while ((*(f32 *)((u8 *)sp.uB4 + 0x14)) > 1.0f);
        (*(f32 *)((u8 *)temp_t2 + 0)) = (f32) (*(f32 *)((u8 *)(&sp.u84) + 0));
        (*(s32 *)((u8 *)temp_t2 + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u84) + 4));
        (*(s32 *)((u8 *)temp_t2 + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u84) + 8));
        (*(f32 *)((u8 *)sp.uB4 + 0x20)) = var_f16;
        (*(f32 *)((u8 *)sp.uB4 + 0x24)) = var_f20;
        (*(f32 *)((u8 *)sp.uB4 + 0x18)) = var_f18;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E40E0/func_151B6B84.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E40E0/func_151B6ED8.s")

void func_151B7664(u8 *arg0, s32 *arg1, u8 arg2)
{
  s32 *p;
  s32 id;
  s32 t;
  p = *((s32 **) (arg0 + 0x98));
  id = p[0];
  t = id;
  if (arg2 == 0)
  {
    if (t == arg1[0])
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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E40E0/func_151B76F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E40E0/func_151B78D8.s")

s32 func_151B7C28(u8 *arg0, u8 *arg1)
{
  u8 *temp_a2;
  u8 *new_var;
  u8 *temp_v1;
  new_var = *((u8 **) (arg0 + 0x98)); temp_v1 = *((u8 **) (new_var + 4)); temp_a2 = *((u8 **) temp_v1);
  if (*((s32 *) temp_a2) == 0) goto ret0;
  if (temp_v1[4] != temp_a2[0x3B]) { ret0: return 0; }
  *((f32 *) (arg1 + 0)) = *((f32 *) (temp_a2 + 0x14));
  *((f32 *) (arg1 + 4)) = *((f32 *) (temp_a2 + 0x18));
  *((f32 *) (arg1 + 8)) = *((f32 *) (temp_a2 + 0x1C));
  return 1;
}

s32 func_151B7C7C(u8 *arg0, f32 *arg1) {
    u8 *p;
    u8 *q;
    u8 *obj;
    f32 mf[4][4];

    p = *(u8 **)(arg0 + 0x98);
    q = *(u8 **)(p + 4);
    obj = *(u8 **)q;
    func_150A8050(mf, *(f32 *)(obj + 0x20), *(f32 *)(obj + 0x24), *(f32 *)(obj + 0x28));
    mf[3][0] = *(f32 *)(obj + 0x38);
    mf[3][1] = *(f32 *)(obj + 0x3C);
    mf[3][2] = *(f32 *)(obj + 0x40);
    mf[0][0] *= *(f32 *)(obj + 0x18);
    mf[0][1] *= *(f32 *)(obj + 0x18);
    mf[0][2] *= *(f32 *)(obj + 0x18);
    mf[1][0] *= *(f32 *)(obj + 0x1C);
    mf[1][1] *= *(f32 *)(obj + 0x1C);
    mf[1][2] *= *(f32 *)(obj + 0x1C);
    mf[2][0] *= *(f32 *)(obj + 0x18);
    mf[2][1] *= *(f32 *)(obj + 0x18);
    mf[2][2] *= *(f32 *)(obj + 0x18);
    func_150A7E40(mf, 0.0f, 0.0f, -250.0f, &arg1[0], &arg1[1], &arg1[2]);
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E40E0/func_151B7DA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E40E0/func_151B7F48.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E40E0/func_151B81E8.s")

void func_151B887C(u8 *arg0, s32 arg1, u8 arg2) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);
    void (*temp_v1)(u8 *, s32, u8) = D_8008FF38[temp_v0[8]];

    if (temp_v1 != NULL) {
        temp_v1(arg0, arg1, arg2);
    }
}

void func_151B88C8(u8 *arg0, s32 *arg1, u8 arg2) {
    u8 *q = *(u8 **)(arg0 + 0x98);
    u8 *p = *(u8 **)(q + 4);
    s32 id;
    if (arg2 == 0) {
        id = arg1[0];
        if (id == *(s32 *)p || p[4] == ((u8 *)arg1)[4]) {
            func_1516972C(arg0);
        }
    }
}

void func_151B8920(u8 *arg0) {
    struct102 **temp_v0 = *(struct102 ***)(arg0 + 0x98);
    struct102 *temp_a1 = *temp_v0;

    if (temp_a1 != NULL) {
        func_1516972C(temp_a1);
    }
}

void func_151B8950(s32 arg0) {
    func_151B8920(arg0);
    func_15147E64(arg0);
}

void func_151B897C(s32 arg0) {
    func_151B8920(arg0);
    func_15147E98(arg0);
}
