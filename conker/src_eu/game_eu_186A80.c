#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_15159270(void **arg0) {
    func_1514EDF0(arg0, arg0[0x18 / 4]);
    func_15169824(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_186A80/func_1515929C.s")

void func_15159514(u8 *arg0, u8 *arg1, u8 arg2)
{
  s32 t;
  s32 *key = (s32 *)(arg0 + 0x18);
  if (arg2 == 0)
  {
    if ((*key == *(s32 *)arg1) || (arg0[0x1C] == arg1[4]))
    {
      func_1516972C((struct102 *)arg0);
    }
  }
  else if (arg2 == 0x2D)
  {
    t = *(s32 *)arg1;
    if (t == *key)
    {
      *(s32 *)(arg0 + 0x18) = *(s32 *)(arg1 + 4);
      arg0[0x1C] = arg1[9];
    }
    else if (*(s32 *)(arg1 + 4) == *key)
    {
      s32 blk_t; // fakematch: block-local declaration = basic-block boundary (s69)
      *(s32 *)(arg0 + 0x18) = t;
      arg0[0x1C] = arg1[8];
    }
  }
  else if (arg2 == 4)
  {
    if ((*key == *(s32 *)arg1) || (arg0[0x1C] == arg1[4]))
    {
      func_1519F970(arg0);
    }
  }
}

s32 func_151595F4(u8 *arg0, u8 arg1) {
    s32 flags = *(s32 *)(arg0 + 0x184) & 0x1F;
    s32 ret;

    if ((arg1 == 2) || (arg1 == 3)) {
        ret = 0;
    } else if ((-10000.0f == *(f32 *)(arg0 + 0x118)) && !(flags & 0xA)) {
        ret = 1;
    } else if ((*(f32 *)(arg0 + 0x118) < *(f32 *)(arg0 + 0x18)) || (arg0[0x137] != 0)) {
        ret = 1;
    } else {
        ret = 0;
    }
    return ret;
}

s32 func_15159690(u8 *arg0, u8 arg1) {
    s32 r;
    if (arg1 == 2 || arg1 == 3) {
        r = 1;
    } else if (*(f32 *)(arg0 + 0x180) < *(f32 *)(arg0 + 0x118) - 35.0f) {
        r = 1;
    } else {
        r = 0;
    }
    return r;
}

s32 func_151596F4(u8 *arg0, u8 arg1) {
    s32 r;

    if (arg1 == 2 || arg1 == 3) {
        if (D_800C35EA != 1) {
            r = 0;
        } else if (*(f32 *)(arg0 + 0x118) - 75.0f < *(f32 *)(arg0 + 0x18)) {
            r = 1;
        } else {
            r = 0;
        }
    } else {
        if (*(f32 *)(arg0 + 0x118) - 75.0f < *(f32 *)(arg0 + 0x18)) {
            r = 1;
        } else {
            r = 0;
        }
    }
    return r;
}

s32 func_151597A0(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 r;
    if (*(f32 *)(arg1 + 0) != *(f32 *)(arg0 + 0x14) || *(f32 *)(arg1 + 4) != *(f32 *)(arg0 + 0x18) || *(f32 *)(arg1 + 8) != *(f32 *)(arg0 + 0x1C)) { if (arg2 == 1 || arg2 == 2) { r = 2; } else { r = 1; } } else { r = 0; }
    return r;
}

#ifdef NON_MATCHING
extern u16 D_8008B3E0;

s32 func_15159828(u8 *arg0, s32 arg1) {
    struct {
        u16 uC;
        u8 padE[0xA];
    } sp;
    s32 var_v0;
    s32 var_v1;
    u8 *var_a2;
    u8 temp_t8;

    var_v0 = 0;
    if (!(arg1 & 0xFF)) {
        var_v0 = 0;
        var_a2 = &(*(u8 *)((u8 *)&sp + 0x1));
        sp.uC = D_8008B3E0;
loop_2:
        temp_t8 = *var_a2;
        var_a2 -= 1;
        if ((*(u16 *)((u8 *)arg0 + 0x84)) == temp_t8) {
            var_v0 = 1;
        }
        if (var_v0 == 0) {
            if ((u32) var_a2 < (u32) &sp.uC) {

            } else {
                goto loop_2;
            }
        }
    }
    if (var_v0 != 0) {
        var_v1 = 3;
    } else if ((*(u8 *)((u8 *)arg0 + 0xAD)) != 0) {
        var_v1 = 2;
    } else {
        var_v1 = 4;
        if ((*(f32 *)((u8 *)arg0 + 0x28)) != 0.0f) {
            var_v1 = 1;
        }
    }
    return var_v1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_186A80/func_15159828.s")
#endif
s32 func_151598E0(struct127 *arg0, u8 *arg1) {
    s32 ret = 0;

    if (D_800BE616 != 0) {
        *arg1 = 0;
        ret = 1;
    }
    if (arg0->unique_id == 1) {
        *arg1 = 0;
        ret = 1;
    }
    if (arg0->unk5 == 5 || arg0->unk5 == 2) {
        *arg1 = 1;
        ret = 1;
    }
    switch (arg0->id) {
    case 8:
        *arg1 = 2;
        ret = 1;
        break;
    case 10:
        *arg1 = 3;
        ret = 1;
        break;
    case 41:
    case 42:
        *arg1 = 4;
        ret = 1;
        break;
    }
    return ret;
}

#ifdef NON_MATCHING
u8 func_1515999C(u8 *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    struct_eu_link *sp38;
    u8 sp37;
    s32 temp_v0;
    s32 var_a0;
    s32 var_a2;
    s32 var_a3;
    s32 var_t0;
    s32 var_t1;
    struct_eu_attached *temp_a1;
    u8 var_t2;

    sp37 = 0;
    var_t2 = sp37;
    if (func_1514F250((*(struct_eu_link **)((u8 *)arg0 + 0x2F4)), 0x13, &sp38) == 0) {
        return 0U;
    }
    temp_a1 = sp38->unk10;
    if (arg4 == -1) {
        var_t1 = 0x1E00;
    } else {
        var_t1 = 1 << (arg4 + 9);
    }
    if (arg3 == -1) {
        var_t0 = 0x1C0;
    } else {
        var_t0 = 1 << (arg3 + 6);
    }
    if (arg2 == -1) {
        var_a2 = 0x38;
    } else {
        var_a2 = 1 << (arg2 + 3);
    }
    if (arg1 == -1) {
        var_a3 = 7;
    } else {
        var_a3 = 1 << arg1;
    }
    if (arg5 == -1) {
        var_a0 = 0x3E000;
    } else {
        var_a0 = 1 << (arg5 + 0xD);
    }
    temp_v0 = var_a0 | var_a3 | var_a2 | var_t0 | var_t1;
    if (temp_v0 == (temp_v0 | ((1 << (*(u8 *)((u8 *)temp_a1 + 0x2C))) | (1 << ((*(u8 *)((u8 *)temp_a1 + 0x2D)) + 3)) | (1 << ((*(u8 *)((u8 *)temp_a1 + 0x2E)) + 6)) | (1 << ((*(u8 *)((u8 *)temp_a1 + 0x2F)) + 9)) | (1 << ((*(u8 *)((u8 *)temp_a1 + 0x30)) + 0xD))))) {
        var_t2 = 1;
    }
    return var_t2;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_186A80/func_1515999C.s")
#endif
s32 func_15046EF0(f32 *, s32, s32, u8 *);
s32 func_1514672C(f32 *);
s32 func_15159C2C(u8 *, u8 *);
s32 func_151D8E20();

u8 func_15159B04(u8 *arg0, u8 *arg1)
{
  u8 flag;
  flag = 1;
  if (func_15159C2C(arg0, arg1) != 0)
  {
    f32 v[4];
    if ((*((f32 *) (arg0 + 0x5C))) > 0.0f)
    {
      v[0] = (*((f32 *) (arg0 + 0x4C))) + (*((f32 *) (arg0 + 0x40)));
      v[1] = *((f32 *) (arg1 + 4));
      v[2] = (*((f32 *) (arg0 + 0x54))) + (*((f32 *) (arg0 + 0x48)));
      if (func_1514672C(v) == 0)
      {
        return 0;
      }
      if (func_15046EF0(v, 0, *((s32 *) (arg0 + 0x44)), arg0 + 0x80) != 0)
      {
        flag = 3; // fakematch: permuter, flag reused as the 3 constant (makes flag = 0 share the tail)
        v[1] = *((f32 *) (arg0 + 0x80));
        if (arg0[0x9D] == flag)
        {
          func_151DBCBC(func_151D8E20(), (*((f32 *) (arg0 + 0xA8))) * 0.2f, 0xFF, (s32) (arg0 + 0x84), v, arg0[0xC], arg0[1]);
        }
        flag = 0;
      }
    }
  }
  else
  {
    flag = 0;
  }
  return flag;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_186A80/func_15159C2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_186A80/func_15159E00.s")

void func_1515A120(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 *arg6) {
    f32 sp24[3];
    f32 sp18[3];

    sp24[0] = arg0;
    sp24[1] = arg1;
    sp18[0] = 0.0f;
    sp18[1] = 0.0f;
    sp18[2] = 0.0f;
    sp24[2] = arg2;
    func_15159E00(sp24, sp18, *(u8 *)(arg6 + 0xC), *(u8 *)(arg6 + 1));
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_186A80/func_1515A178.s")

s32 func_1515A68C(u8 *arg0, s32 arg1) {
    u8 *p;
    f32 s;
    f32 t;
    f32 c;

    p = arg0 + 0xA8;
    p[4] += *(s8 *)(p + 6) * D_800BE9E4;
    p[5] += *(s8 *)(p + 7) * D_800BE9E4;
    s = func_151423D8(p[4] - 0x40);
    c = func_151423D8(p[5] - 0x40);
    *(f32 *)(arg0 + 0x38) = *(f32 *)(p + 8) * s + *(f32 *)(p + 0);
    *(f32 *)(arg0 + 0x3C) = *(f32 *)(p + 0xC) * c + *(f32 *)(p + 0);
    if (D_800BE9E4 && D_800BE9E4 && D_800BE9E4) { // fakematch: permuter; orders the p[0x20] / D_800BE9A4 loads
    }
    *(f32 *)(p + 0x1C) += *(f32 *)(p + 0x20) * D_800BE9A4;
    *(f32 *)(p + 0x1C) = t = func_15144B68(*(f32 *)(p + 0x1C));
    s = sinf(t);
    *(f32 *)(arg0 + 0x4C) = *(f32 *)(p + 0x10) * s;
    *(f32 *)(arg0 + 0x50) = *(f32 *)(p + 0x14) * s;
    *(f32 *)(arg0 + 0x54) = *(f32 *)(p + 0x18) * s;
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_186A80/func_1515A7A8.s")

typedef struct { f32 unk0; u8 unk4; u8 unk5; s8 unk6; s8 unk7; f32 unk8; f32 unkC; u8 unk10; u8 unk11; u8 unk12; u8 unk13; f32 unk14; f32 unk18; f32 unk1C; } SubAB7C;
f32 func_151423D8(u8);
s32 func_1515AB7C(u8 *arg0, s32 arg1) {
    SubAB7C *p;
    s32 i;

    p = (SubAB7C *)(arg0 + 0xA8);
    *(f32 *)(arg0 + 0x38) = (func_151423D8(p->unk4 - 0x40) * p->unk8) + p->unk0;
    *(f32 *)(arg0 + 0x3C) = (func_151423D8(p->unk5 - 0x40) * p->unkC) + p->unk0;
    *(f32 *)(arg0 + 0x4C) = func_151423D8(p->unk10 - 0x40) * p->unk14;
    *(f32 *)(arg0 + 0x54) = func_151423D8(p->unk11 - 0x40) * p->unk18;
    p->unk4 += p->unk6 * D_800BE9E4;
    p->unk5 += p->unk7 * D_800BE9E4;
    p->unk10 += p->unk12 * D_800BE9E4;
    p->unk11 += p->unk13 * D_800BE9E4;
    for (i = D_800BE9E4; i > 0; i--) {
        *(f32 *)(arg0 + 0x58) *= p->unk1C;
        *(f32 *)(arg0 + 0x5C) *= p->unk1C;
        *(f32 *)(arg0 + 0x60) *= p->unk1C;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_186A80/func_1515ACFC.s")

s32 func_1515AE90(u8 *arg0, u8 **arg1) {
    struct_eu_link *sp1C;
    u8 *temp_v1;

    if (func_1514F250(*(struct_eu_link **)(arg0 + 0x2F4), 0x13, &sp1C) == 0) {
        return 0;
    }
    temp_v1 = (u8 *)sp1C->unk10;
    *arg1 = temp_v1 + 0x34;
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_186A80/func_1515AEE4.s")

typedef struct { f32 x, y, z; } V3_AFF4;
typedef struct { s32 w[10]; } Blk_AFF4;
typedef struct { f32 u0; V3_AFF4 pos; f32 u10; Blk_AFF4 blk; } Sp_AFF4;
void func_1515AFF4(u8 *arg0, V3_AFF4 *arg1, f32 arg2, s32 arg3) {
    Sp_AFF4 sp;
    s16 *r;
    struct260 *p;

    sp.u0 = 0.0f;
    sp.pos = *arg1;
    sp.u10 = arg2;
    sp.blk = *(Blk_AFF4 *)(arg0 + 0x84);
    r = (s16 *)(arg0 + 0x80);
    p = func_15149130((s16)(r[0] + (u32)func_150ADA20() % (r[1] + 1)), -1, 0x3F, -1, 1, 0, (struct37 *)0x3C, arg0[0xC], arg0[1]);
    if (p != NULL) {
        memcpy((u8 *)p + 0x28, &sp, 0x3C);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_186A80/func_1515B0F8.s")
