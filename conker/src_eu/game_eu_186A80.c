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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_186A80/func_15159828.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_186A80/func_1515999C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_186A80/func_15159B04.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_186A80/func_1515AFF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_186A80/func_1515B0F8.s")
