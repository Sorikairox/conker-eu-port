#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_1513A594(u8 *arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4);
#endif

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
void func_1513A5E0(s32 arg0, u8 arg1, s32 arg2);
void func_15138120(struct127 *arg0, s32 arg1, u8 arg2);
void func_151382E0(void *arg0, s32 arg1, void *arg2, u8 arg3, s32 arg4);
s32 func_15138424(struct127 *arg0, void *arg1, s32 arg2, void *arg3, u8 arg4, s32 arg5);
void func_15137F30(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 arg4, struct161520 *arg5, f32 *arg6, f32 *arg7, f32 *arg8, f32 *arg9, s16 *argA, u8 *argB, f32 *argC);

// requires jump table
s32 func_15134070(struct127 *arg0) {
    switch (((u8 *)arg0)[4]) {
    case 0x87:
    case 0xB0:
        return 0xE;
    case 0xB1:
        return 0xF;
    case 0xB4:
        return 0x10;
    case 0x70:
    case 0xB2:
        return 0x11;
    case 0xAB:
        return 0x12;
    case 0x38:
    case 0x91:
    case 0x10:
        return 0xD;
    case 0x98:
        return 0xC;
    case 0x34:
        return 0xB;
    case 0x47:
        return 0xA;
    case 0x3B:
    case 0x11:
    case 0x14:
        return 0x1;
    case 0x5A:
    case 0x5F:
    case 0x74:
    case 0x75:
    case 0x7A:
        return 0x2;
    case 0x58:
    case 0x5B:
    case 0x80:
        return 0x3;
    case 0x88:
    case 0x90:
    case 0x16:
        return 0x4;
    case 0x9C:
        return 0x5;
    case 0x9D:
        return 0x6;
    case 0x96:
        return 0x7;
    case 0xA0:
        return 0x8;
    case 0x9F:
        return 0x9;
    case 0x9A:
        return 0x13;
    case 0x0:
    case 0x1:
    case 0x2:
    case 0x3:
    case 0x4:
        return 0;
    default:
        return 0x63;
    }
}

s32 func_1513416C(struct102 *arg0) {
    s16 temp_v0 = arg0->unk1C;
    if (temp_v0 < 32) {
        arg0->unk28 = temp_v0 * 8;
    }
    return 1;
}

s32 memcpy(u8 *, u8 *, s32);

struct102 *func_1513418C(u8 *arg0, s32 arg1, u8 arg2, s32 arg3) {
    u8 *e;
    u8 *v;
    u8 *m;

    e = func_15167A68(0x28, arg3, arg1 + 0x58, 1, arg2, 1);
    if (e == NULL) {
        return NULL;
    }
    memcpy(e + 0x10, arg0, 0x30);
    if (e[0x3A] & 2) {
        v = *(u8 **)(e + 0x1C);
        if (*(s32 *)v == 0 || e[0x18] != v[0x3B]) {
            func_1516972C((struct102 *)e);
            return NULL;
        }
        if (*(u8 **)(v + 0x1D4) != NULL && (v[0x74] & 0xF) != 0xF) {
            m = *(u8 **)(v + 0x1D4);
            m += e[0x20] << 6;
            func_15143134(e + 0x24, e + 0x40, m);
        } else {
            e[0x3A] |= 8;
        }
    } else {
        e[0x3A] |= 0x18;
    }
    *(f32 *)(e + 0x4C) = 1.0f / (*(f32 *)(e + 0x30) + *(f32 *)(e + 0x30));
    *(f32 *)(e + 0x50) = 0.0f;
    return (struct102 *)e;
}
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

#ifdef NON_MATCHING
/* object_list_move_1: D_80089E40 table entry (func_151342BC calls the entries as s32 (*)(obj) and runs
 * func_1516972C on the object when the result is 0): moves the object to list 1 (func_15169804). The asm returns
 * what func_15168A4C leaves in v0: the object's byte +1 (its type, read as the list index). */
s32 func_151346EC(struct102 *arg0) {
    func_15169804(arg0);
    return ((u8 *) arg0)[1];
}

/* object_list_free: D_80089E40 table entry: unlinks and frees the object (func_15169824). The asm returns the free
 * function's v0 (osSetIntMask's previous mask, never 0), so func_151342BC never touches the freed object: 1. */
s32 func_1513470C(struct102 *arg0) {
    func_15169824(arg0);
    return 1;
}
#else
void func_151346EC(struct102 *arg0) {
    func_15169804(arg0);
}

void func_1513470C(struct102 *arg0) {
    func_15169824(arg0);
}
#endif

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
    arg0->unk74 += 0.08f * D_800BE9A4;
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
    return func_151422DC(0, &D_800A3FB4, 0, 2000, 1000, &D_800A3FBC, 2938) * 0.001f;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_151356D4.s")

#ifdef NON_MATCHING
s32 func_15135BF8(u8 *arg0) {
    struct {
        f32 u8;
        f32 uC;
        u8 pad10[0x8];
    } sp;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f6;
    f32 temp_f8;
    f32 var_f4;
    s32 var_v1;
    u8 *temp_v0;
    u8 *temp_v0_2;

    var_v1 = 1;
    if ((*(s16 *)((u8 *)arg0 + 0x70)) > 0) {
        temp_v0 = arg0 + 0x70;
        (*(s16 *)((u8 *)temp_v0 + 0)) = (s16) ((*(s16 *)((u8 *)temp_v0 + 0)) - D_800BE9E4);
        (*(f32 *)((u8 *)arg0 + 0x10)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x10)) + ((*(f32 *)((u8 *)temp_v0 + 8)) * D_800BE9A4));
        (*(f32 *)((u8 *)arg0 + 0x14)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x14)) + ((*(f32 *)((u8 *)temp_v0 + 0xC)) * D_800BE9A4));
        (*(f32 *)((u8 *)arg0 + 0x18)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x18)) + ((*(f32 *)((u8 *)temp_v0 + 4)) * D_800BE9A4));
        var_f4 = (*(f32 *)((u8 *)arg0 + 0x1C)) + ((*(f32 *)((u8 *)temp_v0 + 4)) * D_800BE9A4);
    } else {
        temp_v0_2 = arg0 + 0x70;
        (*(f32 *)((u8 *)(&sp.u8) + 0)) = (*(f32 *)((u8 *)temp_v0_2 + 8));
        (*(f32 *)((u8 *)(&sp.u8) + 4)) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 0xC));
        (*(f32 *)((u8 *)arg0 + 0x14)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x14)) + (((*(f32 *)((u8 *)temp_v0_2 + 0xC)) * D_800BE9A4) + ((*(f32 *)((u8 *)temp_v0_2 + 0x10)) * D_800BE9A4 * D_800BE9A4 * 0.5f)));
        (*(f32 *)((u8 *)temp_v0_2 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0xC)) + ((*(f32 *)((u8 *)temp_v0_2 + 0x10)) * D_800BE9A4));
        temp_f8 = sp.u8 + (*(f32 *)((u8 *)temp_v0_2 + 8));
        sp.u8 = temp_f8;
        temp_f10 = temp_f8 * 0.5f;
        temp_f6 = sp.uC + (*(f32 *)((u8 *)temp_v0_2 + 0xC));
        sp.uC = temp_f6;
        sp.u8 = temp_f10;
        sp.uC = temp_f6 * 0.5f;
        temp_f12 = fabsf(temp_f10) * (*(f32 *)((u8 *)temp_v0_2 + 0x14));
        (*(f32 *)((u8 *)arg0 + 0x18)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x18)) + (temp_f12 * D_800BE9A4));
        var_f4 = (*(f32 *)((u8 *)arg0 + 0x1C)) + (temp_f12 * D_800BE9A4);
    }
    (*(f32 *)((u8 *)arg0 + 0x1C)) = var_f4;
    temp_f0 = (*(f32 *)((u8 *)arg0 + 0x10));
    if ((temp_f0 > 200.0f) || (temp_f0 < -200.0f) || (temp_f0_2 = (*(f32 *)((u8 *)arg0 + 0x14)), (temp_f0_2 > 200.0f)) || (temp_f0_2 < -200.0f)) {
        var_v1 = 0;
    }
    return var_v1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_15135BF8.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_15135DD0.s")

#ifdef NON_MATCHING
s32 func_15046F70(f32 *, s32, f32, f32 *);
void func_1504715C(void *, u8 *);
void func_15143874(s16, f32, f32 *, f32 *);

void func_15136404(struct127 *arg0, f32 arg1, u8 arg2, s32 arg3) {
    struct {
        f32 u9C;
        f32 uA0;
        f32 uA4;
        f32 uA8;
        f32 uAC;
        f32 uB0;
        f32 uB4;
        s32 uB8;
        u8 padBC[0x15];
        s32 uD1;
    } sp;
    f32 temp_f20;
    f32 var_f22;
    s32 temp_s0;
    s32 temp_s0_2;

    if (arg0 != NULL) {
        var_f22 = ((func_150ADA68() * 305.0f) + 108.0f) * 0.000001f * (3.1415927f * arg1 * arg1);
        func_1504715C(&sp.uB4, arg0);
        if (var_f22 > 1.0f) {
            do {
                temp_s0 = func_150ADA20();
                func_15143874((s16) (temp_s0 & 0xFF), func_150ADA68() * arg1, &sp.uA8, &sp.uB0);
                sp.uA8 += arg0->x_position;
                sp.uB0 += arg0->z_position;
                sp.uAC = arg0->y_position + 500.0f;
                if ((func_15046F70(&sp.uA8, 0, arg0->y_position - 5000.0f, &sp.uB4) != 0) && (sp.uD1 != 3)) {
                    sp.u9C = sp.uA8;
                    sp.uA0 = sp.uB4;
                    sp.uA4 = sp.uB0;
                    temp_f20 = func_150ADA68();
                    temp_s0_2 = func_150ADA20();
                    func_151D9B8C(0U, (temp_f20 * 20.0f) + 10.0f, (((u32) temp_s0_2 % 101U) + 0x64) & 0xFF, (s32) &sp.uB8, (struct17 *) &sp.u9C, (s16) ((func_150ADA20() % 201U) + 0x190), 1U, 1U, 0U, (u8) (s32) arg2, arg3);
                }
                var_f22 -= 1.0f;
            } while (var_f22 > 1.0f);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_15136404.s")
#endif
typedef struct {
    s32 v[4];
} Tbl6698;

typedef struct {
    /* 0x00 */ u8 id;
    /* 0x02 */ s16 u2;
    /* 0x04 */ s16 u4;
    /* 0x08 */ s32 u8_;
    /* 0x0C */ s32 uC;
    /* 0x10 */ u8 u10;
    /* 0x11 */ u8 u11;
    /* 0x12 */ u8 u12;
    /* 0x13 */ u8 u13;
    /* 0x14 */ f32 u14;
    /* 0x18 */ f32 u18;
    /* 0x1C */ struct17 pos;
    /* 0x28 */ f32 u28;
    /* 0x2C */ f32 u2C;
    /* 0x30 */ f32 u30;
    /* 0x34 */ f32 u34;
    /* 0x38 */ f32 u38;
    /* 0x3C */ f32 u3C;
    /* 0x40 */ s32 u40;
    /* 0x44 */ u8 u44;
    /* 0x45 */ u8 u45;
    /* 0x46 */ u8 pad46[0x12];
} Blk6698;

extern Tbl6698 D_80089F4C;

s32 func_15136698(f32 arg0, f32 arg1, u8 arg2, u8 arg3, s16 arg4, s32 arg5, struct17 *arg6, u8 arg7, u8 arg8, u8 arg9, s32 argA) {
    s32 obj;
    Blk6698 b;
    f32 scale;
    Tbl6698 tbl;
    s32 a;
    s32 c;

    tbl = D_80089F4C;
    scale = arg1;
    b.id = tbl.v[func_150ADA20() & 3];
    b.u2 = (arg7 ? 2 : 1) + 0x300;
    b.u8_ = 0;
    b.uC = 0;
    b.u10 = 0;
    b.u11 = 0;
    b.u12 = 0;
    b.u13 = 0xFF;
    b.u18 = arg0;
    b.u14 = arg0;
    b.pos = *arg6;
    b.u40 = 0;
    b.u28 = 0.0f;
    b.u2C = 0.0f;
    b.u30 = 0.0f;
    b.u34 = 1.0f;
    b.u38 = 1.0f;
    b.u3C = 1.0f;
    if (arg4 == -1) {
        b.u4 = 300;
    } else {
        b.u4 = arg4 + 0x20;
        b.u40 = 1;
    }
    b.u44 = arg2;
    b.u45 = arg3;
    if (arg8) {
        a = 3;
        c = 0xFF;
    } else {
        a = 0;
        c = 0;
    }
    obj = func_1513D594((s32)&b, 0, 0, 0x1A, 0, (func_150ADA20() & 1) + (func_150ADA20() & 1), func_150ADA20() & 0xFF, 500.0f, 500.0f, 0, arg5, a, c, 0, 4, arg9, argA);
    if (obj != 0) {
        memcpy((void *)(obj + 0x128), &scale, 4);
    }
    return obj;
}

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

typedef struct {
    s32 u48;
    s16 u4C;
    u8 u4E;
    s32 u50;
    s32 u54;
    u8 u58;
    u8 u59;
    u8 u5A;
    u8 u5B;
    u8 u5C;
    u8 u5D;
    u8 u5E;
    u8 u5F;
    s32 u60;
    u8 pad64[0xC];
} Blk6918;

void func_15136918(f32 arg0, u8 arg1, u8 arg2, s16 arg3, s16 arg4, s32 arg5, f32 *arg6, u8 arg7, s32 arg8) {
    Blk6918 s;
    s32 pad; // fakematch: frame slot below the block

    s.u4E = 0x55;
    s.u48 = 0x300;
    s.u50 = 0;
    s.u54 = 0;
    s.u58 = arg1;
    s.u59 = arg2;
    s.u5A = 0;
    s.u5B = 0;
    s.u5C = 0;
    s.u5D = 0;
    s.u60 = 0x280001;
    s.u5E = 1;
    s.u5F = 1;
    if (arg3 == -1) {
        s.u4C = 300;
    } else {
        s.u48 = 0x301;
        s.u4C = arg3 + 0x20;
    }
    func_1513C73C((s32)&s, 0xD, 0, arg5, arg6[0], arg6[1], arg6[2], arg0, arg0, arg4, 0, 0, arg7, arg8);
}

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

    sp1C.unkC = 10.3f;
    sp1C.unk0 = arg0;
    sp1C.unk4 = arg1;
    sp1C.unk8 = arg2;
    sp1C.unk10 = 0.5009f;
    sp1C.unk14 = arg3;
    sp1C.unk16 = 5;
    sp1C.unk17 = 5;
    sp1C.unk18 = 2;
    sp1C.unk19 = -1;
    func_15134908(&sp1C, 0, arg4, arg5);
}

extern f32 D_800A4A04;
extern f32 D_800A4A08;
extern f32 D_800A4A0C;
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

#ifdef NON_MATCHING
/* func_1515128C smoke spec (0x2D bytes used) */
typedef struct {
    /* 0x00 */ s32 u00;
    /* 0x04 */ s32 u04;
    /* 0x08 */ f32 pos[3];
    /* 0x14 */ s16 u14;
    /* 0x16 */ s16 u16;
    /* 0x18 */ s16 u18;
    /* 0x1A */ s16 u1A;
    /* 0x1C */ f32 u1C;
    /* 0x20 */ f32 u20;
    /* 0x24 */ f32 u24;
    /* 0x28 */ s16 u28;
    /* 0x2A */ s16 u2A;
    /* 0x2C */ u8  dark;
} HitSmokeSpec;
void func_1504715C(void *, u8 *);
void func_1515C7B4(u8 *arg0, f32 *arg1, f32 *arg2, f32 *arg3);
void func_1515128C(u8 *arg0, u8 arg1, s32 arg2);
void func_151C6750(s32 arg0, s32 arg1, u8 arg2, s32 arg3);
void func_1513A24C(f32 *pos, s32 *ids, s32 *scales, s32 n, f32 scale, u8 kind, u8 arg6, u8 *obj, s32 *bounds, u8 arg9, s32 argA);
void func_1513A48C(struct17 *arg0, u8 arg1, s32 arg2);
void func_151A9DE4(f32 *arg0, f32 arg1, f32 arg2, void *arg3, s32 arg4, u8 arg5, s32 arg6, u8 arg7, s32 arg8);
extern s32 *D_80089DC0[];       /* per hit kind: debris model ids */
extern s32 D_800A4010[];        /* debris scales (all 1.0) */
extern s32 D_800A42F4[];        /* per hit kind: debris kinds */
extern s32 D_800A4344[];        /* per hit kind: debris spec byte +0x40 */
extern u8 D_800A43B8[][16];     /* per hit kind: +0xE == 2: debris only */

// object_hit_effects: the hit / break effects of an object by its hit kind (func_15134070, 0x63: none), at its
// effect position (func_1515C7B4): debris pieces (debris; two kinds fewer with fewer, or for kind 4 unless the
// object type is 0x16), then unless the kind's +0xE is 2: a smoke puff (smoke; dark for kinds 2 / 15 / 18),
// 18..23 floor splats within 300 below (splats), and the finishing effect (finish: func_151C6750 for kinds 2 / 15,
// else func_1513A48C). arg6 / arg7 are passed on to every spawner. The asm's v0 is left over from a callee; every
// caller ignores it (func_151086A0 returns it to its asm caller, which does not read it).
s32 func_15136C3C(u8 *obj, u8 smoke, u8 splats, u8 debris, u8 finish, u8 fewer, u8 arg6, s32 arg7) {
    HitSmokeSpec spec;
    s32 bounds[9];
    f32 pos[3];
    f32 sizeY;
    f32 sizeX;
    f32 size;
    s32 kind;
    s32 n;
    u8 *info;
    u8 dark;

    if (obj == NULL) {
        return 0;
    }
    size = (*(f32 *)(obj + 0x14C) + *(f32 *)(obj + 0x150)) * 0.5f;
    func_1515C7B4(obj, pos, &sizeX, &sizeY);
    kind = func_15134070((struct127 *)obj);
    if (kind == 0x63) {
        return 0;
    }
    func_1504715C(bounds, obj);
    if (debris) {
        if (fewer || (kind == 4 && obj[4] != 0x16)) {
            n = D_800A42F4[kind] - 2;
        } else {
            n = D_800A42F4[kind];
        }
        func_1513A24C(pos, D_80089DC0[kind], D_800A4010, n, size, kind, D_800A4344[kind], obj, bounds, arg6, arg7);
    }
    info = D_800A43B8[kind];
    if (info[0xE] == 2) {
        return 0;
    }
    if (smoke) {
        spec.u00 = 0xC;
        spec.u04 = 3;
        spec.pos[0] = pos[0];
        spec.pos[1] = pos[1];
        spec.pos[2] = pos[2];
        spec.u14 = 0;
        spec.u16 = 0xFF;
        spec.u18 = -0x40;
        spec.u1A = 0x45;
        spec.u28 = 0x96;
        spec.u2A = 0x64;
        spec.u1C = 998.0f;
        spec.u20 = 25.0f;
        spec.u24 = 10.0f;
        spec.dark = (kind == 2 || kind == 15 || kind == 18) ? 1 : 0;
        func_1515128C((u8 *)&spec, arg6, arg7);
    }
    if (splats) {
        dark = (kind == 2 || kind == 15 || kind == 18) ? 1 : 0;
        func_151A9DE4(pos, pos[1] - 300.0f, 300.0f, bounds, (func_150ADA20() % 6U) + 18, 0, (s32)&dark,
                      arg6, arg7);
    }
    if (finish) {
        if (kind == 2 || kind == 15) {
            func_151C6750((s32)pos, (s32)bounds, arg6, arg7);
            return 0;
        }
        func_1513A48C((struct17 *)pos, arg6, arg7);
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_15136C3C.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_15136F50.s")

typedef struct {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ u8 unk4;
    /* 0x005 */ u8 pad5[0x6F];
    /* 0x074 */ u8 unk74;
    /* 0x075 */ u8 pad75[0x8F];
    /* 0x104 */ u8 unk104;
    /* 0x105 */ u8 pad105[0x20];
    /* 0x125 */ u8 unk125;
    /* 0x126 */ u8 pad126[0xA4];
    /* 0x1CA */ u8 unk1CA;
    /* 0x1CB */ u8 pad1CB[9];
    /* 0x1D4 */ s32 unk1D4;
} Obj7610;

void func_15136F50(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
void func_151C5D2C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 arg6, s32 arg7);
void func_15103C34(s32 arg0, u8 arg1, s32 arg2);

void func_15137610(Obj7610 *arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5) {
    s32 v;

    if (arg0 != NULL) {
        if (arg0->unk1D4 == 0) {
            return;
        }
        if ((arg0->unk74 & 0xF) == 0xF) {
            return;
        }
        if (arg0->unk1CA <= 0) {
            return;
        }
        switch (arg0->unk4) {
        case 0x5:
        case 0xAD:
        case 0xAE:
        case 0xAF:
            v = 3;
            break;
        case 0x5B:
        case 0x70:
        case 0xA6:
        case 0xB2:
        case 0xB4:
            func_15103C34(arg1, arg4, arg5);
            v = 2;
            break;
        case 0x28:
        case 0x77:
        case 0x8A:
        case 0x8C:
            if (func_150ADA20() & 1) {
                return;
            }
            v = 2;
            break;
        case 0x42:
            if (func_150ADA20() & 3) {
                return;
            }
            v = 2;
            break;
        case 0x5A:
        case 0x5F:
        case 0x74:
        case 0x75:
        case 0x7A:
        case 0x8D:
        case 0xB1:
            if (arg0->unk125 == 0xFF) {
                if (func_150ADA20() & 0x1F) {
                    return;
                }
                v = 1;
            } else {
                if (arg0->unk125 != 0) {
                    return;
                }
                if (arg0->unk104 != 0) {
                    return;
                }
                v = 1;
            }
            break;
        default:
            if (arg0->unk125 != 0) {
                return;
            }
            if (arg0->unk104 != 0) {
                return;
            }
            v = 0;
            break;
        }
    } else {
        v = 0;
    }
    switch (v) {
    case 1:
        func_151C5D2C(arg1, arg2, arg3, 1, 1, 1, arg4, arg5);
        break;
    case 2:
        func_151C384C((void *)arg1, arg4, arg5);
        break;
    case 3:
        func_15136F50(arg1, arg2, arg3, 1, arg4, arg5);
        break;
    case 0:
    default:
        func_15136F50(arg1, arg2, arg3, 0, arg4, arg5);
        break;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_1513783C.s")

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec37C64;
s32 func_15145128(Vec37C64 *, Vec37C64 *, s32 *, s32 *);
s32 func_15146078(Vec37C64 *, s32, s32);

s32 func_15137C64(Vec37C64 *a, Vec37C64 *b, Vec37C64 *dir, s32 arg3, s32 arg4, Vec37C64 *p, Vec37C64 *q, Vec37C64 *d) {
    s32 sp2C;
    s32 sp28;

    if (p != NULL && q != NULL) {
        *a = *p;
        *b = *q;
    } else if (p != NULL) {
        *a = *p;
        *b = *p;
    } else if (q != NULL) {
        *a = *q;
        *b = *q;
    } else {
        return 0;
    }
    if (d == NULL) {
        dir->x = b->x - a->x;
        dir->y = b->y - a->y;
        dir->z = b->z - a->z;
        if (func_15145128(dir, dir, &sp2C, &sp28) == 0) {
            return 0;
        }
    } else {
        *dir = *d;
    }
    if (func_15146078(dir, arg3, arg4) == 0) {
        return 2;
    }
    return 1;
}

s32 func_15137E10(struct161520 *arg0) {
    arg0->unk74 = ((func_150ADA68() * 50.0f) + 580.0f) * 0.001f;
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
    *arg9 = ((func_150ADA68() * 217.0f) + -456.0f) * 0.001f;
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
void func_151382E0(void *arg0, s32 arg1, void *arg2, u8 arg3, s32 arg4) {
    struct_eu_15154488 sp24;
    s32 kind;

    kind = D_800A43C6[arg1 * 16];
    if (kind == 2) {
        return;
    }
    sp24.unk8 = *(struct17 *)arg0;
    sp24.unk14 = 1.9799999f;
    sp24.unk18 = 2.01f;
    sp24.unk1C = 0.202f;
    sp24.unk20 = 0.646f;
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
    sp24.unk40 = 0.3f;
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

#ifdef NON_MATCHING
s32 func_15138E98(struct127 *, s32 *, s32, s32 *, s32, s32);
s32 func_15139768(struct127 *, s32 *, f32, s32 *, s32, s32); /* P95: f32 (was the bit pattern as an int) */
s32 func_15139D74(struct127 *, s32 *, s32 *, s32, s32);
s32 func_1513A6E0(struct127 *, s32 *, s32 *, s32, s32);
s32 func_1513ABB8(struct127 *, s32 *, s32, s32 *, s32, s32);
s32 func_1513B0F8(struct127 *, s32 *, s32 *, s32, s32);

void func_15138C80(struct127 *arg0, s32 arg1, s32 arg2) {
    struct {
        s32 u38;
        u8 pad3C[0x23];
        u8 u5F;
        s32 u60;
        u8 pad64[0x8];
        s32 u6C;
    } sp;
    s32 temp_s1;
    s32 temp_v0;

    temp_s1 = arg1 & 0xFF;
    temp_v0 = func_15134070(arg0);
    if ((temp_v0 != 0x63) && (sp.u6C = temp_v0, sp.u5F = func_151380B4(arg0, temp_v0, &sp.u60), func_15138120(arg0, sp.u6C, 1U), (sp.u5F != 0))) {
        func_1504715C(&sp.u38, arg0);
        func_151382E0(&sp.u60, sp.u6C, &sp.u38, temp_s1 & 0xFF, arg2);
        switch (sp.u6C) {
        case 16:
            func_1513B0F8(arg0, &sp.u60, &sp.u38, temp_s1 & 0xFF, arg2);
            return;
        case 17:
            func_15103C34((s32) &sp.u60, temp_s1 & 0xFF, arg2);
            return;
        case 0:
        case 7:
            func_1513A6E0(arg0, &sp.u60, &sp.u38, temp_s1 & 0xFF, arg2);
            return;
        case 3:
            func_15138E98(arg0, &sp.u60, 1, &sp.u38, temp_s1, arg2);
            return;
        case 5:
        case 6:
            func_15138E98(arg0, &sp.u60, 0, &sp.u38, temp_s1, arg2);
            return;
        case 15:
            func_15139768(arg0, &sp.u60, 0.6f, &sp.u38, temp_s1, arg2); /* P95: was 0x3F19999A as an int */
            return;
        case 2:
            func_15139768(arg0, &sp.u60, 1.0f, &sp.u38, temp_s1, arg2); /* P95: was 0x3F800000 as an int */
            return;
        case 4:
            func_1513A594((u8 *) arg0, (s32) &sp.u60, (s32) &sp.u38, temp_s1 & 0xFF, arg2);
            return;
        case 8:
        case 9:
            func_1513ABB8(arg0, &sp.u60, (sp.u6C == 9) & 0xFF, &sp.u38, temp_s1, arg2);
            return;
        default:
            func_15139D74(arg0, &sp.u60, &sp.u38, temp_s1 & 0xFF, arg2);
            break;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_15138C80.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_15138E98.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_15139578.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_15139768.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_15139D74.s")

#ifdef NON_MATCHING
/* func_15150D7C debris burst spec (0x44 bytes) and the 0xC extra bytes copied to each piece (+0x170) */
typedef struct {
    /* 0x00 */ s32 countBase;
    /* 0x04 */ s32 countExtra;
    /* 0x08 */ f32 pos[3];
    /* 0x14 */ s16 u14;
    /* 0x16 */ s16 u16;
    /* 0x18 */ s16 u18;
    /* 0x1A */ s16 u1A;
    /* 0x1C */ f32 u1C;
    /* 0x20 */ f32 u20;
    /* 0x24 */ f32 u24;
    /* 0x28 */ f32 u28;
    /* 0x2C */ s16 u2C;
    /* 0x2E */ s16 u2E;
    /* 0x30 */ f32 sizeMin;
    /* 0x34 */ f32 sizeExtra;
    /* 0x38 */ f32 u38;
    /* 0x3C */ f32 solidChance;
    /* 0x40 */ u8  u40;
} DebrisSpec;
typedef struct {
    /* 0x00 */ s32 u0;
    /* 0x04 */ u16 model;
    /* 0x06 */ u8  u6;
    /* 0x08 */ s32 u8;
} DebrisExtra;
s32 func_15150D7C(s32 *arg0, s32 *ids, s32 *scales, s32 n, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                  s32 arg9, f32 arg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14);
void func_151343AC(s32 arg0, u8 arg1);
extern u16 D_800A4638[4];

// object_debris_burst: 40 debris pieces of the kinds ids[] / scales[] (n kinds) at pos, sized scale (debris spec
// for func_15150D7C, 0x0D: other spin / speed values; 0x13 in level 0x3C: never solid). Kind 1 adds the extra
// bytes {4, model D_800A4638[obj +0x128, at most 3], 6, 3} and mode 1. Then func_151343AC(0, 0x45).
void func_1513A24C(f32 *pos, s32 *ids, s32 *scales, s32 n, f32 scale, u8 kind, u8 arg6, u8 *obj, s32 *bounds,
                   u8 arg9, s32 argA) {
    DebrisSpec spec;
    DebrisExtra extra;
    u16 models[4];
    s32 mode;
    s32 i;

    spec.countBase = 0x28;
    spec.countExtra = 0;
    spec.pos[0] = pos[0];
    spec.pos[1] = pos[1];
    spec.pos[2] = pos[2];
    spec.sizeMin = 1.0f * scale;
    spec.u14 = 0;
    spec.u16 = 0xFF;
    spec.u2C = 0x190;
    spec.u2E = 0xC8;
    spec.sizeExtra = (f32)0 * scale; /* computed: -0.0 for a negative scale (IDO folds "0.0f * scale") */
    extra.u0 = 4;
    mode = -1;
    spec.u18 = -0x40;
    spec.u1A = 0xC;
    spec.u20 = 5.0f;
    spec.solidChance = 1.0f;
    spec.u1C = 13.0f;
    spec.u24 = -1.0070001f;
    spec.u28 = 0.252f;
    spec.u38 = 16.102001f;
    spec.u40 = arg6;
    if (kind == 1) {
        models[0] = D_800A4638[0];
        models[1] = D_800A4638[1];
        models[2] = D_800A4638[2];
        models[3] = D_800A4638[3];
        mode = 1;
        i = obj[0x128];
        if (i >= 4) {
            i = 3;
        }
        extra.u6 = 6;
        extra.u8 = 3;
        extra.model = models[i];
    } else if (kind == 0xD) {
        spec.u18 = -0x2E;
        spec.u1A = 0x14;
        spec.u1C = 15.0f;
        spec.u20 = 8.0f;
        spec.u24 = -1.2620001f;
        spec.u28 = 0.49f;
        spec.u38 = 12.911f;
    } else if (kind == 0x13 && D_800BE9F0 == 0x3C) {
        spec.solidChance = 0.0f;
    }
    func_15150D7C((s32 *)&spec, ids, scales, n, (s32)&extra, 0xC, 6, 1, mode, (s32)bounds, 5.0f, 1,
                  (D_800BE616 != 0) ? 1 : 0, arg9, argA);
    func_151343AC(0, 0x45);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_1513A24C.s")
#endif

extern u8 D_800A4648[];
extern u8 D_800A4650[];

typedef struct {
    s32 u2C;
    s32 u30;
    struct17 pos;
    s16 u40;
    s16 u42;
    s16 u44;
    s16 u46;
    f32 u48;
    f32 u4C;
    f32 u50;
    f32 u54;
    s16 u58;
    s16 u5A;
    f32 u5C;
    f32 u60;
    f32 u64;
} Blk15152700;

void func_1513A48C(struct17 *arg0, u8 arg1, s32 arg2) {
    Blk15152700 s;

    s.u2C = 8;
    s.u30 = 4;
    s.pos = *arg0;
    s.u40 = 0;
    s.u42 = 0xFF;
    s.u44 = -0x37;
    s.u46 = 0x20;
    s.u48 = 10.0f;
    s.u4C = 9.0f;
    s.u50 = -1.00400007f;
    s.u54 = 0.254f;
    s.u58 = 0x28;
    s.u5A = 0x14;
    s.u5C = 0.07f;
    s.u60 = 0.07f;
    s.u64 = 23.4460011f;
    func_15152700(&s, D_800A4640, D_800A4644, 1, 0.0f, 1, arg1, arg2);
}

void func_1513A594(u8 *arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4) {
    func_1513A5E0(arg1, arg3, arg4);
    if (*(s32 *)(arg0 + 0x1D4) != 0) { if (arg0) {} }
}

void func_1513A5E0(s32 arg0, u8 arg1, s32 arg2) {
    Blk15152700 s;

    s.u2C = 7;
    s.u30 = 7;
    s.pos = *(struct17 *)arg0;
    s.u40 = 0;
    s.u42 = 0xFF;
    s.u44 = -0x32;
    s.u46 = 0x1B;
    s.u48 = 4.0f;
    s.u4C = 4.0f;
    s.u50 = -0.43f;
    s.u54 = 0.272f;
    s.u58 = 0x19;
    s.u5A = 0x28;
    s.u5C = 0.0201f;
    s.u60 = 0.0201f;
    s.u64 = 20.187f;
    func_15152700(&s, D_800A4648, D_800A4650, 2, 0.0f, 1, arg1, arg2);
}

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
