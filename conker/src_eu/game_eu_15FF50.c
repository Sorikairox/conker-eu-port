#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted forward declaration(s) for func_151341C8, func_15134290
s32 func_15134108(u8 *, f32, f32, f32, f32, s32);


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15FF50/func_15132740.s")

void func_1513291C(u8 *arg0) {
    u8 var_v0 = (*(s32 *)(arg0 + 0x60) & 0x100) ? arg0[0x68] : 0;

    D_80089D50[var_v0](arg0);
}

void func_15132968(u8 *arg0) {
    u8 var_v0 = (*(s32 *)(arg0 + 0x60) & 0x100) ? arg0[0x68] : 0;

    D_80089D74[var_v0](arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15FF50/func_151329B4.s")

void func_15132AE0(struct102 * arg0) {
    func_151329B4(arg0);
    func_15169804(arg0);
}

void func_15132B0C(struct102 * arg0) {
    func_151329B4(arg0);
    func_15169824(arg0);
}

void func_15132B38(u8 *arg0) {
    s32 i;

    for (i = 0; i <= D_80082FA0; i++) {
        if (((s32 *)(arg0 + 0x154))[i]) {
            func_100043B4(((s32 *)(arg0 + 0x154))[i], 4);
        }
    }
    if (*(s32 *)(arg0 + 0x164) != 0) {
        func_100043B4(*(s32 *)(arg0 + 0x164), 4);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15FF50/func_15132BBC.s")

void func_15132FBC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5) {
    func_15132BBC(arg0, arg1, arg2, 0, arg3, arg4, arg5);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15FF50/func_15132FF8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15FF50/func_151330F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15FF50/func_1513334C.s")

s32 func_1513384C(u8 *arg0)
{
  f32 cs;
  *((f32 *) (arg0 + 0x2C)) = 1.0f;
  *((f32 *) (arg0 + 0x30)) = 1.0f;
  *((f32 *) (arg0 + 0x34)) = 1.0f;
  if ((*((s32 *) (arg0 + 0x60))) & 0x40)
  {
    *((f32 *) (arg0 + 0x20)) += (*((f32 *) (arg0 + 0x50))) * D_800BE9A4;
    *((f32 *) (arg0 + 0x24)) += (*((f32 *) (arg0 + 0x54))) * D_800BE9A4;
    *((f32 *) (arg0 + 0x28)) += (*((f32 *) (arg0 + 0x58))) * D_800BE9A4;
  }
  arg0[0x149] += ((s32) (576.0f * (*((f32 *) (arg0 + 0x144))))) * D_800BE9E4;
  if (arg0[0x149] < 0x80)
  {
    f32 s;
    s = func_151423D8(arg0[0x149] - 0x40);
    s = ((1.0f - (*((f32 *) (arg0 + 0x144)))) * (1.0f - (*((f32 *) (arg0 + 0x14))))) * s;
    if (arg0[0x148] & 8)
    {
      *((f32 *) (arg0 + 0x2C)) *= 1.0f + s;
      *((f32 *) (arg0 + 0x30)) *= 1.0f - s;
      *((f32 *) (arg0 + 0x34)) *= s + 1.0f;
      *((f32 *) (arg0 + 0x3C)) = (*((f32 *) (arg0 + 0x138))) - ((*((f32 *) (arg0 + 0x10))) * (0, s)); // fakematch: comma puts s in fs
    }
    if (arg0[0x148] & 0x10)
    {
      f32 sn;
      f32 d;
      sn = func_151423D8(((s8) arg0[0x14A]) - 0x40);
      cs = func_151423D8((u8) arg0[0x14A]);
      *((f32 *) (arg0 + 0x2C)) *= 1.0f - s;
      *((f32 *) (arg0 + 0x30)) *= 1.0f + s;
      *((f32 *) (arg0 + 0x34)) *= 1.0f - s;
      d = (*((f32 *) (arg0 + 0x10))) * (0, s); // fakematch: comma puts s in fs
      *((f32 *) (arg0 + 0x38)) = (*((f32 *) (arg0 + 0x134))) - (d * cs);
      *((f32 *) (arg0 + 0x40)) = (*((f32 *) (arg0 + 0x13C))) + (d * sn);
    }
  }
  else
  {
    memcpy(arg0 + 0x38, arg0 + 0x134, 0xC);
    arg0[0x149] = 0;
    arg0[0x148] &= ~0x18;
  }
  return 1;
}

s32 func_151424F4(s32, s32, s32, s32, f32, f32, f32, f32, f32, f32, f32, f32);
s32 func_15133A80(s32 arg0, u8 *arg1) {
    func_151424F4(arg0, *(s32 *)(arg1 + 0x18), *(s32 *)(arg1 + 0x1C), *(s32 *)(arg1 + 0x20), *(f32 *)(arg1 + 0x24), *(f32 *)(arg1 + 0x28), *(f32 *)(arg1 + 0x2C), *(f32 *)(arg1 + 0x30), *(f32 *)(arg1 + 0x34), *(f32 *)(arg1 + 0x38), *(f32 *)(arg1 + 0x3C), *(f32 *)(arg1 + 0x40));
    return 1;
}

void func_151B9C10(void *);
extern void (*D_80089D98[])(u8 *, u8 *, u8);
void func_15133AF8(u8 *arg0, u8 *arg1, u8 arg2)
{
  s32 idx;
  s32 sel = arg2;
  s32 t;
  s32 k; // fakematch: unused local fixes the arg2-copy spill slot
  if ((arg2 == 0x1B) && (*(u16 *)(arg0 + 0x66) == 0x22))
  {
    func_151B9C10(arg0);
  }
  if (sel == 0x2D)
  {
    if (*(s32 *)arg1 == *(s32 *)(arg0 + 0x7C)) { *(s32 *)(arg0 + 0x7C) = *(s32 *)(arg1 + 4); arg0[0x80] = arg1[9]; }
    else if (*(s32 *)(arg1 + 4) == *(s32 *)(arg0 + 0x7C)) {
      s32 blk_t; // fakematch: block-local declaration = basic-block boundary (s69)
      *(s32 *)(arg0 + 0x7C) = *(s32 *)arg1; arg0[0x80] = arg1[8]; }
  }
  else if (sel == 0)
  {
    t = *(s32 *)arg1;
    if ((t == *(s32 *)(arg0 + 0x7C)) || (arg0[0x80] == arg1[4])) { *(s32 *)(arg0 + 0x7C) = 0; arg0[0x80] = 0; }
  }
  if (*(s32 *)(arg0 + 0x60) & 0x100) { idx = arg0[0x68]; } else { idx = 0; }
  if (D_80089D98[idx] != NULL) { D_80089D98[idx](arg0, arg1, arg2); }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15FF50/func_15133C18.s")

s32 func_15142838(s32, s32, s32, s32, f32, f32, f32, f32, f32);
s32 func_15133CD0(s32 arg0, u8 *arg1) {
    func_15142838(arg0, *(s32 *)(arg1 + 0x18), *(s32 *)(arg1 + 0x1C), *(s32 *)(arg1 + 0x20), *(f32 *)(arg1 + 0x24), *(f32 *)(arg1 + 0x28), *(f32 *)(arg1 + 0x38), *(f32 *)(arg1 + 0x3C), *(f32 *)(arg1 + 0x40));
    return 1;
}

s32 func_15133D30(u8 *arg0) {
    *(f32 *)(arg0 + 0x38) += *(f32 *)(arg0 + 0x44) * D_800BE9A4;
    *(f32 *)(arg0 + 0x3C) += (*(f32 *)(arg0 + 0x48) * D_800BE9A4) + (*(f32 *)(arg0 + 0x5C) * D_800BE9A4 * D_800BE9A4 * 0.5f);
    *(f32 *)(arg0 + 0x40) += *(f32 *)(arg0 + 0x4C) * D_800BE9A4;
    *(f32 *)(arg0 + 0x48) += *(f32 *)(arg0 + 0x5C) * D_800BE9A4;
    *(f32 *)(arg0 + 0x20) += *(f32 *)(arg0 + 0x50) * D_800BE9A4;
    *(f32 *)(arg0 + 0x24) += *(f32 *)(arg0 + 0x54) * D_800BE9A4;
    *(f32 *)(arg0 + 0x28) += *(f32 *)(arg0 + 0x58) * D_800BE9A4;
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15FF50/func_15133E04.s")

s32 func_15133F44(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    f32 temp_f0;
    *(f32 *)(arg0 + 0x3C) = *(f32 *)(arg0 + 0x10) + arg4;
    temp_f0 = *(f32 *)(arg0 + 0x14);
    *(f32 *)(arg0 + 0x44) = *(f32 *)(arg0 + 0x44) * temp_f0;
    *(f32 *)(arg0 + 0x48) = *(f32 *)(arg0 + 0x48) * -temp_f0;
    *(f32 *)(arg0 + 0x4C) = *(f32 *)(arg0 + 0x4C) * temp_f0;
    *(f32 *)(arg0 + 0x50) = *(f32 *)(arg0 + 0x50) * temp_f0;
    *(f32 *)(arg0 + 0x54) = *(f32 *)(arg0 + 0x54) * temp_f0;
    *(f32 *)(arg0 + 0x58) = *(f32 *)(arg0 + 0x58) * temp_f0;
    return 1;
}

s32 func_15133FC0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    *(f32 *)(arg0 + 0x3C) = *(f32 *)(arg0 + 0x10) + arg4;
    *(f32 *)(arg0 + 0x44) = 0.0f;
    *(f32 *)(arg0 + 0x48) = 0.0f;
    *(f32 *)(arg0 + 0x4C) = 0.0f;
    *(f32 *)(arg0 + 0x50) = 0.0f;
    *(f32 *)(arg0 + 0x54) = 0.0f;
    *(f32 *)(arg0 + 0x58) = 0.0f;
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15FF50/func_15134004.s")

s32 func_15134108(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5)
{
  f32 temp_f18;
  f32 temp_f6;
  *((f32 *) (((u8 *) arg0) + 0x3C)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x10))) + arg4);
  temp_f18 = *((f32 *) (((u8 *) arg0) + 0x14));
  *((f32 *) (((u8 *) arg0) + 0x48)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x48))) * (-temp_f18));
  *((f32 *) (((u8 *) arg0) + 0x44)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x44))) * temp_f18);
  *((f32 *) (((u8 *) arg0) + 0x4C)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x4C))) * temp_f18);
  *((f32 *) (((u8 *) arg0) + 0x50)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x50))) * temp_f18);
  *((f32 *) (((u8 *) arg0) + 0x54)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x54))) * temp_f18);
  *((f32 *) (((u8 *) arg0) + 0x58)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x58))) * temp_f18);
  if (fabsf(*((f32 *) (((u8 *) arg0) + 0x48))) < 4.0f)
  {
    *((f32 *) (((u8 *) arg0) + 0x44)) = 0.0f;
    *((s32 *) (((u8 *) arg0) + 0x60)) = (s32) ((*((s32 *) (((u8 *) arg0) + 0x60))) & (~0x69));
    *((f32 *) (((u8 *) arg0) + 0x48)) = 0.0f;
    *((f32 *) (((u8 *) arg0) + 0x4C)) = 0.0f;
    *((f32 *) (((u8 *) arg0) + 0x50)) = 0.0f;
    *((f32 *) (((u8 *) arg0) + 0x54)) = 0.0f;
    *((f32 *) (((u8 *) arg0) + 0x58)) = 0.0f;
    *((f32 *) (((u8 *) arg0) + 0x5C)) = 0.0f;
  }
  return 1;
}

s32 func_151341C8(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5) {
    func_15134108(arg0, arg1, arg2, arg3, arg4, arg5);
    if (func_150ADA20() & 1) {
        func_10010F88((func_150ADA20() % 9U) + 0x2DE, 0x2EE0U, 0, 0U, 0, (s16) (s32) arg1, (s16) (s32) arg2, (s16) (s32) arg3, 0x1F4, 0x3E8);
    }
    return 1;
}

s32 func_15134290(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5) {
    func_15134108(arg0, arg1, arg2, arg3, arg4, arg5);
    if (func_150ADA20() & 1) {
        func_10010F88((func_150ADA20() % 10U) + 0x1B8, 0x5DC0U, 0, 0U, 0, (s16) (s32) arg1, (s16) (s32) arg2, (s16) (s32) arg3, 0x1F4, 0x3E8);
    }
    return 1;
}

void func_15134358(struct102 *arg0, s32 *arg1, u8 arg2) {
    s32 id;
    if (arg2 == 0) {
        id = arg1[0];
        if (id == *(s32 *)((u8 *)arg0 + 0x7C) || ((u8 *)arg1)[4] == *((u8 *)arg0 + 0x80)) {
            func_1516972C(arg0);
        }
    }
}

void func_151343AC(s32 arg0, u8 arg1) {
    struct_eu_s32x2 sp18 = D_800A3C40;
    func_15169260(&sp18, 2, arg0, arg1);
}

void func_151343F4(s32 arg0, u8 *arg1, s32 arg2) {
    func_1513445C(arg0, *(u16 *)(arg1 + 0x170), arg1[0x172], *(s32 *)(arg1 + 0x174));
}

void func_15134428(s32 arg0, u8 *arg1, s32 arg2) {
    func_1513445C(arg0, *(u16 *)(arg1 + 0x174), arg1[0x176], *(s32 *)(arg1 + 0x178));
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15FF50/func_1513445C.s")

s32 func_15134548(s32 arg0, u8 *arg1, s32 arg2) {
    u8 *p = arg1 + 0x170;
    u8 *q = p;
    u8 *e;
    s32 i;

    for (i = 0; i < *q; i = (i + 1) & 0xFF) {
        e = (u8 *)((s32)p + (i << 3));
        arg0 = (s32)func_1513445C((u8 *)arg0, *(u16 *)(e + 4), *(u8 *)(e + 6), *(s32 *)(e + 8));
    }
    return arg0;
}
