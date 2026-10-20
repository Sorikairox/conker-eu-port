#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    /* 0x000 */ u8  unk0;
    /* 0x001 */ u8  unk1;
    /* 0x002 */ u8  pad2[0xA];
    /* 0x00C */ u8  unkC;
    /* 0x00D */ u8  padD[0x3];
    /* 0x010 */ s32 unk10;
    /* 0x014 */ u8  pad14[0x4];
    /* 0x018 */ u8  unk18;
    /* 0x019 */ u8  pad19[0x3];
    /* 0x01C */ s32 unk1C;
    /* 0x020 */ u8  pad20[0x1D];
    /* 0x03D */ u8  unk3D;
    /* 0x03E */ u8  pad3E[0x6];
    /* 0x044 */ u16 unk44;
    /* 0x046 */ u8  pad46[0xA];
    /* 0x050 */ u8  unk50;
    /* 0x051 */ u8  pad51[0xF];
    /* 0x060 */ s32 unk60;
    /* 0x064 */ u8  pad64[0x10];
    /* 0x074 */ f32 unk74;
    /* 0x078 */ u8  pad78[0xF8];
    /* 0x170 */ s32 unk170;
    /* 0x174 */ u8  pad174[0x60];
    /* 0x1D4 */ s32 unk1D4;
} struct161520;

typedef struct {
    s32 unk0;
    union {
        s32 w;
        u8  b;
    } unk4;
    u8  unk8;
    u8  unk9;
} struct161520_msg;

typedef struct {
    /* 0x000 */ u8  pad0[0x1C];
    /* 0x01C */ s16 unk1C;
    /* 0x01E */ u8  pad1E[0xE];
    /* 0x02C */ f32 unk2C;
    /* 0x030 */ f32 unk30;
    /* 0x034 */ u8  pad34[0x28];
    /* 0x05C */ u8  unk5C;
    /* 0x05D */ u8  pad5D[0xCB];
    /* 0x128 */ f32 unk128;
} struct161520_b;

typedef struct {
    /* 0x000 */ u8  pad0[0x14];
    /* 0x014 */ f32 unk14;
    /* 0x018 */ f32 unk18;
    /* 0x01C */ f32 unk1C;
    /* 0x020 */ u8  pad20[0xE];
    /* 0x02E */ u8  unk2E;
    /* 0x02F */ u8  pad2F[0x41];
    /* 0x070 */ f32 unk70;
    /* 0x074 */ f32 unk74;
} struct161520_c;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ struct17 unk8;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
} struct161520_e; // size 0x3C

void func_1513555C(struct161520 *arg0, struct161520_msg *arg1, u8 arg2);
void func_151355B8(struct161520 *arg0, struct161520_msg *arg1, u8 arg2);
s32 func_15134070(struct127 *arg0);
void func_15138120(struct127 *arg0, s32 arg1, u8 arg2);
void func_151382E0(void *arg0, s32 arg1, void *arg2, u8 arg3, s32 arg4);
s32 func_15138424(struct127 *arg0, void *arg1, s32 arg2, void *arg3, u8 arg4, s32 arg5);
void func_15137F30(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 arg4, struct161520 *arg5, f32 *arg6, f32 *arg7, f32 *arg8, f32 *arg9, s16 *argA, u8 *argB, f32 *argC);

// requires jump table
#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_15134070.s")

s32 func_1513416C(struct102 *arg0) {
    s16 temp_v0 = arg0->unk1C;
    if (temp_v0 < 32) {
        arg0->unk28 = temp_v0 * 8;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_1513418C.s")
// void *func_1513418C(s32 arg0, s32 arg1 /* size/offset */, u8 arg2, s32 arg3) {
//     void *sp24;
//     s32 temp_v1;
//     u8 temp_a0;
//     void *temp_ret;
//     void *temp_v0;
//     struct127 *temp_v0_2;
//
//     temp_ret = func_15167A68(0x28, arg3, arg1 + 0x58, 1, arg2, 1);
//     temp_v0 = temp_ret;
//     if (temp_v0 == 0) {
//         return NULL;
//     }
//     sp24 = temp_v0;
//     memcpy(&temp_v0->unk10, arg0, 0x30); //, temp_v0);
//     temp_a0 = temp_v0->unk3A;
//     if ((temp_a0 & 2) != 0) {
//         temp_v0_2 = temp_v0->unk1C;
//         if ((temp_v0_2->unk0 == 0) || (temp_v0->unk18 != temp_v0_2->unk3B)) {
//             func_1516972C(temp_v0);
//             return NULL;
//         }
//         temp_v1 = temp_v0_2->unk1D4;
//         if ((temp_v1 != 0) && ((temp_v0_2->unk74 & 0xF) != 0xF)) {
//             sp24 = temp_v0;
//             func_15143134(temp_v0->unk24, temp_v0->unk40, temp_v1 + (temp_v0->unk20 << 6), temp_v0);
//         } else {
//             temp_v0->unk3A = (u8) (temp_a0 | 8);
//         }
//     } else {
//         temp_v0->unk3A = (u8) (temp_a0 | 0x18);
//     }
//     temp_ret->unk50 = 0.0f;
//     temp_ret->unk4C = (f32) (1.0f / (2.0f * temp_ret->unk30));
//     return temp_ret;
// }

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_151342BC.s")

s32 func_151346D0(s32 arg0, struct102 *arg1, s32 arg2) {
    arg1->unk3A &= 0xFFEF;
    return arg0;
}

void func_151346EC(struct102 *arg0) {
    func_15169804(arg0);
}

void func_1513470C(struct102 *arg0) {
    func_15169824(arg0);
}

void func_1513472C(struct102 *arg0) {
    s32 idx = arg0->unk3D;
    if (idx < 0) {
        idx = 0;
    }
    if (idx >= 10) {
        idx = 0;
    }
    D_80089AAC[idx]();
}

void func_1513477C(struct102 *arg0) {
  s32 idx = arg0->unk3D;
  if (idx < 0) {
      idx = 0;
  }
  if (idx >= 10) {
      idx = 0;
  }
    D_80089AD4[idx]();
}

void func_151347CC(struct161520 *arg0, struct161520_msg *arg1, u8 arg2) {
  s32 *key = &arg0->unk1C;
    if ((arg2 == 0) || (arg2 == 3)) {
        if ((arg1->unk0 == arg0->unk1C) || (arg1->unk4.b == arg0->unk18)) { func_1516972C((struct102 *)arg0); }
    } else if (arg2 == 0x11) {
        if ((arg0->unk3D == 5) && ((arg1->unk0 == arg0->unk1C) || (arg1->unk4.b == arg0->unk18))) { func_1516972C((struct102 *)arg0); }
    } else if (arg2 == 0x16) {
        if ((s32)arg1 == arg0->unk1C) { func_1516972C((struct102 *)arg0); }
    } else if (arg2 == 0x2D) {
        if (arg1->unk0 == *key) { arg0->unk1C = arg1->unk4.w; arg0->unk18 = arg1->unk9; }
        else if (arg1->unk4.w == *key) { arg0->unk1C = arg1->unk0; arg0->unk18 = arg1->unk8; }
    }
}

void func_151348F0(f32 arg0, f32 arg1, s32 arg2, s32 arg3) {
}

s32 memcpy(u8 *, u8 *, s32);
s32 func_15134908(struct_eu_EF410 *arg0, s32 arg1, u8 arg2, s32 arg3) {
    u8 *temp_v0;
    u8 *sp24; // fakematch: temp_v0 copy kept in a stack slot
    temp_v0 = func_15167A68(0x2A, arg3, arg1 + 0x40, 1, arg2, 1);
    if (temp_v0 == NULL) {
        return 0;
    }
    *((u8 *)arg0 + 0x16) |= 2;
    sp24 = temp_v0;
    memcpy(temp_v0 + 0x10, (u8 *)arg0, 0x1C);
    *(f32 *)(sp24 + 0x2C) = **(f32 **)(sp24 + 0x10);
    *(f32 *)(sp24 + 0x30) = **(f32 **)(sp24 + 0x14);
    *(f32 *)(sp24 + 0x34) = **(f32 **)(sp24 + 0x18);
    *(f32 *)(sp24 + 0x38) = 1.0f / (2.0f * *(f32 *)(sp24 + 0x1C));
    *(f32 *)(sp24 + 0x3C) = 0.0f;
    return (s32)sp24;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_151349D0.s")

void func_15134C98(struct102 *arg0, s32 arg1, u8 arg2) {
    if (arg0->unk28 == 1) {
        func_151BCB54(arg0, arg1, arg2);
    }
}

void func_15134CD4(f32 arg0, f32 arg1, s32 arg2, s32 arg3) {
}

s32 func_15134CEC(struct161520_c *arg0) {
    s32 temp_v1 = arg0->unk2E;

    arg0->unk70 += 0.125f * D_800BE9A4;
    arg0->unk74 += D_800A4990 * D_800BE9A4;
    arg0->unk14 += arg0->unk70 * D_800BE9A4;
    arg0->unk1C += arg0->unk74 * D_800BE9A4;
    if (arg0->unk14 > 130.0f) {
        return 0;
    }
    temp_v1 -= D_800BE9E4 * 2;
    if (temp_v1 < 0) {
        return 0;
    }
    arg0->unk2E = temp_v1;
    return 1;
}

s32 memcpy(u8 *, u8 *, s32);

u8 *func_15134DAC(u8 *arg0, s32 arg1) {
    u8 *temp_v0;
    u8 *sp24;

    temp_v0 = func_15167A68(0x29, 0, arg1 + 0x80, 1, 0xFFU, 1U);
    if (temp_v0 == NULL) {
        return NULL;
    }
    sp24 = temp_v0;
    memcpy(temp_v0 + 0x18, arg0, 0x3C);
    (*(s16 *)((u8 *)sp24 + 0x54)) = (s16) -(*(s16 *)((u8 *)arg0 + 0x28));
    (*(s32 *)((u8 *)sp24 + 0x10)) = 1;
    (*(s32 *)((u8 *)sp24 + 0x14)) = 0;
    (*(f32 *)((u8 *)sp24 + 0x70)) = 0.0f;
    (*(f32 *)((u8 *)sp24 + 0x74)) = 0.0f;
    (*(f32 *)((u8 *)sp24 + 0x78)) = 0.0f;
    return sp24;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_15134E48.s")

void func_151352EC(struct102 *arg0) {
    func_15169804(arg0);
}

void func_1513530C(struct102 *arg0) {
    func_15169824(arg0);
}

void func_1513532C(struct161520 *arg0) {
    s32 pad;
    s32 idx = arg0->unk50;

    if (idx < 0) {
        idx = 0;
    } else if (idx >= 6) {
        idx = 0;
    }
    if (arg0->unk44 != 0) {
        func_100111C8(arg0->unk44);
        arg0->unk44 = 0;
    }
    D_80089F10[idx](arg0);
}

void func_151353A8(struct161520 *arg0) {
    s32 pad;
    s32 idx = arg0->unk50;

    if (idx < 0) {
        idx = 0;
    } else if (idx >= 6) {
        idx = 0;
    }
    if (arg0->unk44 != 0) {
        func_100111C8(arg0->unk44);
        arg0->unk44 = 0;
    }
    D_80089F28[idx](arg0);
}

s32 func_15145EA4(s32 *, s32 *, s32, s32);
void func_15135424(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp20[2];
    s32 sp18[2];
    sp20[0] = arg1;
    sp20[1] = arg2;
    sp18[0] = arg3;
    sp18[1] = arg4;
    func_15145EA4(sp20, sp18, arg0, 2);
}

void func_15135480(struct161520 *arg0, struct161520_msg *arg1, u8 arg2)
{
  s32 t;
  s32 k;
  if (arg2 == 0x2D)
  {
    if (arg0->unk1C == arg1->unk0)
    {
      arg0->unk1C = arg1->unk4.w;
      arg0->unk18 = arg1->unk9;
    }
    else
      if (arg0->unk1C == arg1->unk4.w)
    {
      t = arg1->unk0;
      arg0->unk1C = t;
      arg0->unk18 = arg1->unk8;
    }
  }
  switch (arg0->unk50)
  {
    case 1:
      func_151355B8(arg0, arg1, arg2);
      break;

    case 2:
      func_1513555C(arg0, arg1, arg2);
      break;

    default:
      if (arg2 == 0)
    {
      k = arg0->unk1C;
      if (((k ^ 0) == arg1->unk0) || (arg0->unk18 == arg1->unk4.b)) // fakematch: (k ^ 0) keeps the key in v0 (s71/s72)
      {
        func_1516972C((struct102 *) arg0);
      }
    }
      break;

  }

}

void func_1513555C(struct161520 *arg0, struct161520_msg *arg1, u8 arg2) {
    if ((arg2 == 0) || (arg2 == 0x12)) {
        if ((arg0->unk1C == arg1->unk0) || (arg0->unk18 == arg1->unk4.b)) {
            func_1516972C(arg0);
        }
    }
}

void func_151355B8(struct161520 *arg0, struct161520_msg *arg1, u8 arg2) {
    switch (arg2) {
    case 0:
        if ((arg0->unk1C == arg1->unk0) || (arg0->unk18 == arg1->unk4.b)) {
            func_1516972C(arg0);
        }
        break;
    case 3:
        if ((arg0->unk1C == arg1->unk0) || (arg0->unk18 == arg1->unk4.b)) {
            arg0->unk10 &= ~1;
            arg0->unk10 = arg0->unk10;
        }
        break;
    }
}

s32 func_15135658(struct161520 *arg0) {
    arg0->unk74 = 1.0f;
    return 1;
}

f32 func_15135670(s32 arg0) {
    // "power", "../Effects/Blood/blood.c"
    return func_151422DC(0, &D_800A3FB4, 0, 2000, 1000, &D_800A3FBC, 2938) * D_800A45B4;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_151356D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_15135BF8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_15135DD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_15136404.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_15136698.s")

s32 func_151368A8(struct161520_b *arg0) {
    s16 temp_v0 = arg0->unk1C;
    f32 *temp_v1 = &arg0->unk128;

    if (temp_v0 < 32) {
        if ((temp_v0 * 8) < arg0->unk5C) {
            arg0->unk5C = temp_v0 * 8;
        }
    }
    arg0->unk2C += *temp_v1 * D_800BE9A4;
    arg0->unk30 += *temp_v1 * D_800BE9A4;
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_15136918.s")

s32 func_15136A1C(struct102 *arg0) {
    s16 temp_v0 = arg0->unk1C;
    if (temp_v0 < 32) {
        if ((temp_v0 * 8) < arg0->unk28) {
            arg0->unk28 = temp_v0 * 8;
        }
    }
    return 1;
}

void func_15136A50(s32 arg0, s32 arg1, s32 arg2, s16 arg3, u8 arg4, s32 arg5) {
    struct_eu_EF410 sp1C;

    sp1C.unkC = D_800A49FC;
    sp1C.unk0 = arg0;
    sp1C.unk4 = arg1;
    sp1C.unk8 = arg2;
    sp1C.unk10 = D_800A4A00;
    sp1C.unk14 = arg3;
    sp1C.unk16 = 5;
    sp1C.unk17 = 5;
    sp1C.unk18 = 2;
    sp1C.unk19 = -1;
    func_15134908(&sp1C, 0, arg4, arg5);
}

void func_15136AE4(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, struct161520 *arg6) {
    f32 sp6C[3];
    f32 sp60[3];
    f32 temp_f2;
    s32 pad;
    u32 sp54;
    u32 sp50;
    f32 sp4C;

    sp6C[0] = arg0;
    sp6C[1] = arg1;
    sp6C[2] = arg2;
    temp_f2 = ((func_150ADA68() * 112.0f) + 247.0f) * D_800A4A04;
    sp60[0] = -arg3 * temp_f2;
    sp60[1] = -arg4 * temp_f2;
    sp60[2] = -arg5 * temp_f2;
    sp4C = func_150ADA68();
    sp50 = func_150ADA20();
    sp54 = func_150ADA20();
    func_151D9014(sp6C, sp60, 0, (sp4C * D_800A4A08) + D_800A4A0C, (sp50 & 0xF) + 0x19, (sp54 % 101) + 0x9B, (func_150ADA68() * 119.0f) + 129.0f, 0, 1.0f, 1.0f, 1, 0, 1, 0, arg6->unkC, arg6->unk1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_15136C3C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_15136F50.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_15137610.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_1513783C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_15137C64.s")

s32 func_15137E10(struct161520 *arg0) {
    arg0->unk74 = ((func_150ADA68() * 50.0f) + 580.0f) * D_800A4C08;
    return 1;
}

void func_15137E60(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 arg4, struct161520 *arg5) {
    f32 sp6C[3];
    f32 sp60[3];
    f32 sp54[3];
    f32 sp50;
    s16 sp4E;
    u8 sp4D;
    f32 sp48;

    func_15137F30(arg0, arg1, arg2, arg3, arg4, arg5, sp6C, sp60, sp54, &sp50, &sp4E, &sp4D, &sp48);
    func_151D9014(sp6C, sp54, 0, sp50, sp4E, sp4D, sp48, 0, 1.0f, 1.0f, 1, 0, 1, 0, arg5->unkC, arg5->unk1);
}

extern f32 D_800A4C0C;
void func_15137F30(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 arg4, struct161520 *arg5, f32 *arg6, f32 *arg7, f32 *arg8, f32 *arg9, s16 *argA, u8 *argB, f32 *argC) {
    (*(f32 *)((u8 *)arg6 + 0)) = ((*(f32 *)((u8 *)arg2 + 0)) * arg4) + (*(f32 *)((u8 *)arg0 + 0));
    (*(f32 *)((u8 *)arg6 + 4)) = ((*(f32 *)((u8 *)arg2 + 4)) * arg4) + (*(f32 *)((u8 *)arg0 + 4));
    (*(f32 *)((u8 *)arg6 + 8)) = ((*(f32 *)((u8 *)arg2 + 8)) * arg4) + (*(f32 *)((u8 *)arg0 + 8));
    (*(f32 *)((u8 *)arg7 + 0)) = ((*(f32 *)((u8 *)arg3 + 0)) * arg4) + (*(f32 *)((u8 *)arg1 + 0));
    (*(f32 *)((u8 *)arg7 + 4)) = ((*(f32 *)((u8 *)arg3 + 4)) * arg4) + (*(f32 *)((u8 *)arg1 + 4));
    (*(f32 *)((u8 *)arg7 + 8)) = ((*(f32 *)((u8 *)arg3 + 8)) * arg4) + (*(f32 *)((u8 *)arg1 + 8));
    (*(f32 *)((u8 *)arg8 + 0)) = ((*(f32 *)((u8 *)arg7 + 0)) - (*(f32 *)((u8 *)arg6 + 0))) * arg5->unk74;
    (*(f32 *)((u8 *)arg8 + 4)) = (f32) (((*(f32 *)((u8 *)arg7 + 4)) - (*(f32 *)((u8 *)arg6 + 4))) * arg5->unk74);
    (*(f32 *)((u8 *)arg8 + 8)) = (f32) (((*(f32 *)((u8 *)arg7 + 8)) - (*(f32 *)((u8 *)arg6 + 8))) * arg5->unk74);
    *arg9 = ((func_150ADA68() * 217.0f) + -456.0f) * D_800A4C0C;
    *argA = (func_150ADA20() % 31U) + 0x1E;
    *argB = (func_150ADA20() % 156U) + 0x64;
    *argC = (func_150ADA68() * 35.0f) + 40.0f;
}

s32 func_151380B4(struct127 *arg0, s32 arg1, void *arg2) {
    struct255 *temp_v0 = arg0->unk1D4;

    if (temp_v0 == NULL) {
        return 0;
    }
    if ((arg0->unk74 & 0xF) == 0xF) {
        return 0;
    }
    func_15143134(D_800A43B8[arg1], arg2, (u8 *)temp_v0 + 0x300);
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_15138120.s")

extern u8 D_800A43C6[];
extern f32 D_800A4C10;
extern f32 D_800A4C14;
extern f32 D_800A4C18;
extern f32 D_800A4C1C;
extern f32 D_800A4C20;
void func_151382E0(void *arg0, s32 arg1, void *arg2, u8 arg3, s32 arg4) {
    struct_eu_15154488 sp24;
    s32 kind;

    kind = D_800A43C6[arg1 * 16];
    if (kind == 2) {
        return;
    }
    sp24.unk8 = *(struct17 *)arg0;
    sp24.unk14 = D_800A4C10;
    sp24.unk18 = D_800A4C14;
    sp24.unk1C = D_800A4C18;
    sp24.unk20 = D_800A4C1C;
    sp24.unk24 = 4.0f;
    sp24.unk28 = 9.0f;
    sp24.unk2C = 0x12;
    sp24.unk2E = 7;
    sp24.unk0 = 0;
    sp24.unk2 = 0xFF;
    sp24.unk4 = -0x3F;
    sp24.unk6 = 0x4E;
    sp24.unk30 = 3;
    sp24.unk32 = 3;
    sp24.unk34 = 0x14;
    sp24.unk36 = 0x1E;
    sp24.unk38 = 0x9B;
    sp24.unk3A = 0x64;
    sp24.unk44 = 0x10;
    sp24.unk46 = 0xF;
    sp24.unk48 = 0;
    sp24.unk40 = D_800A4C20;
    if (kind == 1) {
        sp24.unk3C = 1;
    } else {
        sp24.unk3C = 0;
    }
    func_15154488(&sp24, &sp24.unk8, (s32) arg2, arg3, arg4);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_15138424.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_151389A8.s")

void func_15138BC0(struct127 *arg0, u8 arg1, s32 arg2) {
    s32 temp_v0;
    f32 sp50[3];
    u8 sp4F;
    f32 sp28[9];

    temp_v0 = func_15134070(arg0);
    if (temp_v0 != 0x63) {
        sp4F = func_151380B4(arg0, temp_v0, sp50);
        func_15138120(arg0, temp_v0, 1);
        if (sp4F != 0) {
            func_1504715C(sp28, arg0);
            func_151382E0(sp50, temp_v0, sp28, arg1, arg2);
            func_15138424(arg0, sp50, temp_v0, sp28, arg1, arg2);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_15138C80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_15138E98.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_15139578.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_15139768.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_15139D74.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_1513A24C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_1513A48C.s")

void func_1513A594(u8 *arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4) {
    func_1513A5E0(arg1, arg3, arg4);
    if (*(s32 *)(arg0 + 0x1D4) != 0) { if (arg0) {} }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_1513A5E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_1513A6E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_1513ABB8.s")

void func_1513B0B8(struct161520 *arg0, s32 arg1, u8 arg2) {
    s32 *temp_v0 = &arg0->unk170;

    if (arg2 == 0x45) {
        if (--*temp_v0 < 0) {
            arg0->unk60 |= 0x80;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_1513B0F8.s")
