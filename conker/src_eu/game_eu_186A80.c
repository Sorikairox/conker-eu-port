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
#ifdef NON_MATCHING
s32 func_15046EF0(f32 *, s32, f32, u8 *); /* P95: f32 parameter */
#else
s32 func_15046EF0(f32 *, s32, s32, u8 *);
#endif
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
#ifdef NON_MATCHING
      if (func_15046EF0(v, 0, *((f32 *) (arg0 + 0x44)), arg0 + 0x80) != 0) /* P95: f32 field (prototype param is f32 in NM) */
#else
      if (func_15046EF0(v, 0, *((s32 *) (arg0 + 0x44)), arg0 + 0x80) != 0)
#endif
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

#ifdef NON_MATCHING
s32 memcpy(s32, f32 *, s32);

s32 func_15159E00(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3) {
    struct {
        f32 u1C;
        s8 u20;
        s8 u21;
        s8 u22;
        s8 u23;
        f32 u24;
        f32 u28;
        f32 u2C;
        f32 u30;
        s8 u34;
        s8 u35;
        s8 u36;
        s8 u37;
        f32 u38;
        f32 u3C;
        f32 u40;
        s32 u44;
        s32 u48;
        s32 u4C;
        s16 u50;
        s16 u52;
        s32 u54;
        s32 u58;
        s8 u5C;
        s8 u5D;
        s8 u5E;
        s8 u5F;
        s8 u60;
        s8 u61;
        s8 u62;
        s8 u63;
        s8 u64;
        s8 u65;
        s16 u66;
        s16 u68;
        s16 u6A;
        f32 u6C;
        f32 u70;
        f32 u74;
        s32 u78;
        u8 pad7C[0x8];
        f32 u84;
        f32 u88;
        f32 u8C;
        s32 u90;
        u8 pad94[0x8];
        f32 u9C;
        s32 uA0;
        u8 padA4[0x4];
        s8 uA8;
        s8 uA9;
        s8 uAA;
        s8 uAB;
    } sp;
    f32 temp_f2;
    s32 temp_v0;
    s32 var_v1;

    sp.u65 = 0x2F;
    sp.u50 = 0xC01;
    sp.u48 = 0x200005;
    sp.u4C = 0;
    sp.u62 = 0;
    sp.u61 = 0;
    sp.u60 = 0;
    sp.u5F = 0;
    sp.u5E = 0;
    sp.u5D = 0;
    sp.u5C = 0;
    sp.u58 = 0;
    sp.u54 = 0;
    sp.u64 = 0xFF;
    sp.u6A = 0;
    sp.u6C = 0.0f;
    sp.uA0 = 0x3207;
    sp.uA8 = 5;
    sp.uA9 = 5;
    sp.uAA = 4;
    sp.uAB = -1;
    (*(s32 *)((u8 *)(&sp.u78) + 0)) = (s32) (*(s32 *)((u8 *)arg0 + 0));
    (*(s32 *)((u8 *)(&sp.u78) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 4));
    (*(s32 *)((u8 *)(&sp.u78) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 8));
    sp.u84 = 0.0f;
    sp.u88 = 0.0f;
    sp.u8C = 0.0f;
    sp.u20 = 0;
    sp.u21 = 0;
    sp.u34 = 0;
    sp.u35 = 0;
    sp.u40 = 1000.0f;
    sp.u2C = 4.0f;
    sp.u30 = 0.25f;
    (*(s32 *)((u8 *)(&sp.u90) + 0)) = (s32) (*(s32 *)((u8 *)arg1 + 0));
    (*(s32 *)((u8 *)(&sp.u90) + 4)) = (s32) (*(s32 *)((u8 *)arg1 + 4));
    (*(s32 *)((u8 *)(&sp.u90) + 8)) = (s32) (*(s32 *)((u8 *)arg1 + 8));
    if (func_150ADA20() & 1) {
        sp.uA0 |= 0x40;
    }
    if (func_150ADA20() & 1) {
        sp.uA0 |= 0x80;
    }
    sp.u52 = (func_150ADA20() % 25U) + 0x1E;
    sp.u66 = 0x1E;
    sp.u68 = 8;
    sp.u63 = (func_150ADA20() % 101U) + 0x64;
    temp_f2 = (func_150ADA68() * 20.0f) + 49.0f;
    sp.u70 = temp_f2;
    sp.u1C = temp_f2;
    sp.u74 = temp_f2;
    sp.u22 = (func_150ADA20() % 5U) + 4;
    sp.u23 = (func_150ADA20() % 5U) + 4;
    sp.u24 = ((func_150ADA68() * 0.25f) + 0.15f) * sp.u1C;
    sp.u28 = ((func_150ADA68() * 0.25f) + 0.15f) * sp.u1C;
    sp.u36 = (func_150ADA20() % 5U) + 4;
    sp.u37 = (func_150ADA20() % 5U) + 4;
    sp.u38 = ((func_150ADA68() * 0.1f) + 0.08f) * sp.u1C;
    sp.u3C = ((func_150ADA68() * 0.1f) + 0.08f) * sp.u1C;
    sp.u9C = ((func_150ADA68() * 254.0f) + 108.0f) * 0.001f;
    temp_v0 = func_1513092C(&sp.u48, 2, 0x28);
    var_v1 = temp_v0;
    if (temp_v0 != 0) {
        sp.u44 = temp_v0;
        memcpy(temp_v0 + 0xA8, &sp.u1C, 0x28);
        var_v1 = sp.u44;
    }
    return var_v1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_186A80/func_15159E00.s")
#endif
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

#ifdef NON_MATCHING
extern f32 D_800A67C4;
extern f32 D_800A67CC;
extern f32 D_800A67D0;
extern f32 D_800A67DC;
extern f32 D_800A67E0;
s32 func_151307F0(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
s32 memcpy(s32, f32 *, s32);

s32 func_1515A7A8(f32 *arg0, u8 *arg1, f32 arg2, f32 arg3, u8 *arg4, f32 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9, s32 argA) {
    struct {
        u8 u2C;
        u8 pad2D[0x1B];
        s8 u48;
        u8 pad49[0x7];
        f32 u50;
        s8 u54;
        s8 u55;
        s8 u56;
        s8 u57;
        f32 u58;
        f32 u5C;
        s8 u60;
        s8 u61;
        s8 u62;
        s8 u63;
        f32 u64;
        f32 u68;
        f32 u6C;
        f32 u70;
        s32 u74;
        s32 u78;
        s16 u7C;
        s16 u7E;
        s32 u80;
        s32 u84;
        s8 u88;
        s8 u89;
        s8 u8A;
        s8 u8B;
        s8 u8C;
        s8 u8D;
        s8 u8E;
        u8 u8F;
        s8 u90;
        s8 u91;
        s16 u92;
        s16 u94;
        s16 u96;
        f32 u98;
        f32 u9C;
        f32 uA0;
        s32 uA4;
        u8 padA8[0x8];
        f32 uB0;
        f32 uB4;
        f32 uB8;
        s32 uBC;
        u8 padC0[0x8];
        f32 uC8;
        s32 uCC;
        u8 padD0[0x4];
        s8 uD4;
        s8 uD5;
        s8 uD6;
        s8 uD7;
        s8 uD8;
        s8 uD9;
        u8 padDA[0xA];
        s32 uE4;
    } sp;
    s32 sp24;
    f32 temp_f8;
    s32 temp_v0;
    s32 var_v0;
    s32 var_v1;
    s32 var_v1_2;

    sp.u91 = 0x2F;
    sp.u7C = 0x2203;
    sp.u74 = 0x200005;
    sp.u78 = 0;
    sp.u8E = 0;
    sp.u8D = 0;
    sp.u8C = 0;
    sp.u8B = 0;
    sp.u8A = 0;
    sp.u89 = 0;
    sp.u88 = 0;
    sp.u84 = 0;
    sp.u80 = 0;
    sp.u90 = 0xFF;
    sp.u96 = 0;
    sp.u98 = 0.0f;
    if (func_150ADA20() & 1) {
        var_v1_2 = 0x40;
    } else {
        var_v1_2 = 0;
    }
    sp24 = var_v1_2;
    if (func_150ADA20() & 1) {
        var_v0 = 0x80;
    } else {
        var_v0 = 0;
    }
    sp.uCC = var_v0 | 0x1007 | var_v1_2 | 0xC000;
    sp.uD4 = 6;
    sp.uD5 = 8;
    if (arg8 != 0) {
        sp.uD6 = 0x15;
    } else {
        sp.uD6 = 0x14;
    }
    sp.uD7 = -1;
    sp.uD8 = -1;
    (*(s32 *)((u8 *)(&sp.uA4) + 0)) = (s32) (*(f32 *)((u8 *)arg0 + 0));
    (*(s32 *)((u8 *)(&sp.uA4) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 4));
    (*(s32 *)((u8 *)(&sp.uA4) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 8));
    sp.uB0 = 0.0f;
    sp.uB4 = 0.0f;
    sp.uB8 = 0.0f;
    sp.u92 = 1;
    sp.u94 = 0xFF;
    sp.u50 = arg5;
    sp.u9C = arg5;
    sp.uA0 = arg5;
    sp.u54 = func_150ADA20();
    sp.u55 = func_150ADA20();
    sp.u56 = (func_150ADA20() % 5U) + 4;
    sp.u57 = (func_150ADA20() % 5U) + 4;
    sp.u58 = ((func_150ADA68() * 0.25f) + D_800A67C4) * sp.u50;
    temp_f8 = func_150ADA68() * 0.25f;
    sp.u60 = 0;
    sp.u61 = 0;
    sp.u5C = (temp_f8 + D_800A67C4) * sp.u50;
    sp.u62 = (func_150ADA20() % 5U) + 4;
    sp.u63 = (func_150ADA20() % 5U) + 4;
    sp.u64 = ((func_150ADA68() * D_800A67CC) + D_800A67D0) * sp.u50;
    sp.u68 = ((func_150ADA68() * D_800A67CC) + D_800A67D0) * sp.u50;
    (*(f32 *)((u8 *)(&sp.uBC) + 0)) = (f32) (*(f32 *)((u8 *)arg1 + 0));
    (*(s32 *)((u8 *)(&sp.uBC) + 4)) = (s32) (*(s32 *)((u8 *)arg1 + 4));
    (*(f32 *)((u8 *)(&sp.uBC) + 8)) = (f32) (*(f32 *)((u8 *)arg1 + 8));
    sp.uD9 = 0;
    sp.u7E = arg6;
    sp.u8F = arg7;
    sp.uC8 = arg2;
    sp.u6C = arg3;
    if (((*(f32 *)((u8 *)arg1 + 0)) != 0.0f) || ((*(f32 *)((u8 *)arg1 + 8)) != 0.0f)) {
        sp.u70 = D_800A67DC;
    } else {
        if (arg4 != NULL) {
            *(struct_eu_bytes24 *)(&sp.u2C) = *(struct_eu_bytes24 *)(arg4);
        } else {
            sp.u48 = 0;
        }
        if (func_1514672C(arg0) != 0) {
            if (func_15046EF0(arg0, 0, 19500.0f, &sp.u2C) != 0) { /* P95: was 0x46985800 as an int */
                arg4 = &sp.u2C;
                sp.u70 = (f32) sp.u2C;
            } else {
                sp.u70 = D_800A67E0;
            }
        } else {
            sp.u70 = D_800A67E0;
        }
    }
    temp_v0 = func_151307F0(&sp.u74, 2, arg4, 0x24, (s32) arg9, argA);
    var_v1 = temp_v0;
    if (temp_v0 != 0) {
        sp.uE4 = temp_v0;
        memcpy(temp_v0 + 0xA8, &sp.u50, 0x24);
        var_v1 = sp.uE4;
    }
    return var_v1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_186A80/func_1515A7A8.s")
#endif
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

#ifdef NON_MATCHING
u8 func_1515ACFC(u8 *arg0, s32 arg1) {
    struct {
        f32 u3C;
        f32 u40;
        f32 u44;
        u8 pad48[0x3];
        u8 u4B;
    } sp;
    u8 *sp34;
    f32 temp_f0;

    sp.u4B = 1;
    func_1515AB7C(arg0, arg1);
    if ((*(f32 *)((u8 *)arg0 + 0x5C)) < 0.0f) {
        return 1U;
    }
    sp.u3C = (*(f32 *)((u8 *)arg0 + 0x40)) + (*(f32 *)((u8 *)arg0 + 0x4C));
    sp.u40 = (*(f32 *)((u8 *)arg1 + 4));
    sp34 = arg0 + 0xA8;
    sp.u44 = (*(f32 *)((u8 *)arg0 + 0x48)) + (*(f32 *)((u8 *)arg0 + 0x54));
    temp_f0 = (*(f32 *)((u8 *)(&arg0[0xA8]) + 0x20));
    if (temp_f0 == -99999.9f) {
        if (func_1514672C(&sp.u3C) == 0) {
            return 0U;
        }
        if (func_15046EF0(&sp.u3C, 0, (*(f32 *)((u8 *)arg0 + 0x44)), arg0 + 0x80) != 0) { /* P95: f32 field (prototype param is f32 in NM) */
            sp.u4B = 0;
            sp.u40 = (*(f32 *)((u8 *)arg0 + 0x80));
        }
        goto block_9;
    }
    if (temp_f0 <= (*(f32 *)&((*(s32 *)((u8 *)arg0 + 0x44))))) {
        sp.u40 = temp_f0;
        sp.u4B = 0;
    }
block_9:
    if ((sp.u4B == 0) && (func_150ADA68() < 0.2f) && ((*(u8 *)((u8 *)arg0 + 0x9D)) == 3)) {
        func_151DBCBC(func_151D8E20() & 0xFF, *sp34 * 0.2f, (s16) (*(u8 *)((u8 *)arg0 + 0x2B)), (s32) (arg0 + 0x84), &sp.u3C, (u8) (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
    }
    return sp.u4B;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_186A80/func_1515ACFC.s")
#endif
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

#ifdef NON_MATCHING
s32 func_151307F0(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
s32 memcpy(s32, f32 *, s32);

void func_1515B0F8(u8 *arg0) {
    struct {
        f32 u74;
        s8 u78;
        s8 u79;
        s8 u7A;
        s8 u7B;
        f32 u7C;
        f32 u80;
        f32 u84;
        f32 u88;
        s8 u8C;
        s8 u8D;
        s8 u8E;
        s8 u8F;
        f32 u90;
        f32 u94;
        f32 u98;
        s32 u9C;
        s32 uA0;
        s16 uA4;
        s16 uA6;
        s32 uA8;
        s32 uAC;
        u8 uB0;
        u8 uB1;
        u8 uB2;
        s8 uB3;
        s8 uB4;
        s8 uB5;
        s8 uB6;
        s8 uB7;
        s8 uB8;
        s8 uB9;
        s16 uBA;
        s16 uBC;
        s16 uBE;
        f32 uC0;
        f32 uC4;
        f32 uC8;
        s32 uCC;
        u8 padD0[0x8];
        f32 uD8;
        f32 uDC;
        f32 uE0;
        f32 uE4;
        f32 uE8;
        f32 uEC;
        f32 uF0;
        s32 uF4;
        u8 padF8[0x4];
        s8 uFC;
        s8 uFD;
        s8 uFE;
        s8 uFF;
        s8 u100;
        s8 u101;
    } sp;
    f32 temp_f10;
    s32 temp_v0;
    s32 var_s1;
    s32 var_v0;
    u8 *temp_s0;

    temp_s0 = arg0 + 0x28;
    (*(f32 *)((u8 *)temp_s0 + 0)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0)) + (((*(f32 *)((u8 *)temp_s0 + 0x14)) + (func_150ADA68() * (*(f32 *)((u8 *)temp_s0 + 0x18)))) * D_800BE9A4));
    if ((*(f32 *)((u8 *)temp_s0 + 0)) > 1.0f) {
        sp.u78 = 0;
        sp.u79 = 0;
        sp.u8C = 0;
        sp.u8D = 0;
        sp.u84 = (*(f32 *)((u8 *)temp_s0 + 0x2C));
        sp.u88 = (*(f32 *)((u8 *)temp_s0 + 0x30));
        sp.uB9 = 0x2F;
        sp.uA4 = 0x4403;
        sp.u9C = 0x200005;
        sp.uA0 = 0x9F0600;
        sp.uA6 = 0x12C;
        sp.uA8 = 0;
        sp.uAC = 0;
        sp.uB4 = 0xFF;
        sp.uB5 = 0xFF;
        sp.uB6 = 0xFF;
        sp.uB3 = 0xFF;
        sp.u98 = (*(f32 *)((u8 *)temp_s0 + 0x10));
        sp.uB0 = (*(u8 *)((u8 *)temp_s0 + 0x36));
        sp.uB1 = (*(u8 *)((u8 *)temp_s0 + 0x37));
        sp.uB8 = 0xFF;
        sp.uB2 = (*(u8 *)((u8 *)temp_s0 + 0x38));
        (*(s32 *)((u8 *)(&sp.uCC) + 0)) = (s32) (*(s32 *)((u8 *)temp_s0 + 4));
        (*(s32 *)((u8 *)(&sp.uCC) + 4)) = (s32) (*(s32 *)((u8 *)temp_s0 + 8));
        (*(s32 *)((u8 *)(&sp.uCC) + 8)) = (s32) (*(s32 *)((u8 *)temp_s0 + 0xC));
        sp.uE4 = 0.0f;
        sp.uE8 = 0.0f;
        sp.uEC = 0.0f;
        sp.uBA = 1;
        sp.uBC = 0xFF;
        sp.uBE = 1;
        sp.uC0 = 1.0f;
        sp.uFC = 6;
        sp.uFD = 9;
        sp.uFE = 4;
        sp.uFF = -1;
        sp.u100 = -1;
        sp.u101 = 0;
        sp.uD8 = 0.0f;
        sp.uDC = 0.0f;
        sp.uE0 = 0.0f;
        do {
            sp.u7A = (func_150ADA20() % 5U) + 4;
            sp.u7B = (func_150ADA20() % 5U) + 4;
            temp_f10 = (func_150ADA68() * (*(f32 *)((u8 *)temp_s0 + 0x20))) + (*(f32 *)((u8 *)temp_s0 + 0x1C));
            sp.uC8 = temp_f10;
            sp.uC4 = temp_f10;
            sp.u74 = temp_f10;
            sp.u7C = ((func_150ADA68() * 0.25f) + 0.15f) * sp.u74;
            sp.u80 = ((func_150ADA68() * 0.25f) + 0.15f) * sp.u74;
            sp.u8E = (func_150ADA20() % 5U) + 4;
            sp.u8F = (func_150ADA20() % 5U) + 4;
            sp.u90 = ((func_150ADA68() * 0.1f) + 0.08f) * sp.u74;
            sp.u94 = ((func_150ADA68() * 0.1f) + 0.08f) * sp.u74;
            sp.uF0 = (func_150ADA68() * (*(f32 *)((u8 *)temp_s0 + 0x28))) + (*(f32 *)((u8 *)temp_s0 + 0x24));
            sp.uB7 = (func_150ADA20() % (u32) ((*(u8 *)((u8 *)temp_s0 + 0x35)) + 1)) + (*(u8 *)((u8 *)temp_s0 + 0x34));
            var_s1 = 0;
            if (func_150ADA20() & 1) {
                var_s1 = 0x40;
            }
            if (func_150ADA20() & 1) {
                var_v0 = 0x80;
            } else {
                var_v0 = 0;
            }
            sp.uF4 = var_v0 | 6 | var_s1 | 0xF000;
            temp_v0 = func_151307F0(&sp.u9C, 2, 0, 0x28, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
            if (temp_v0 != 0) {
                memcpy(temp_v0 + 0xA8, &sp.u74, 0x28);
            }
            (*(f32 *)((u8 *)temp_s0 + 0)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s0 + 0)) > 1.0f);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_186A80/func_1515B0F8.s")
#endif