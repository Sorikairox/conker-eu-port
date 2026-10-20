#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    /* 0x00 */ u8 pad0[0x38];
    /* 0x38 */ s32 unk38[1];
} struct_eu_1DFE20_c;

typedef struct {
    /* 0x000 */ u8 pad0[0x178];
    /* 0x178 */ struct_eu_1DFE20_c *unk178;
    /* 0x17C */ u8 unk17C;
} struct_eu_1DFE20_d;

typedef struct {
    /* 0x00 */ u8 pad0[0x44];
    /* 0x44 */ s32 unk44;
} struct_eu_1DFE20_b;

typedef struct {
    /* 0x00 */ u8 pad0[0x4C];
    /* 0x4C */ struct_eu_1DFE20_b *unk4C;
} struct_eu_1DFE20;


void func_151B2610(u8 *arg0) {
    struct260 *temp_v0;
    struct {
        u8 *unk0;
        u8 unk4;
        struct127 *unk8;
        u8 unkC;
        u8 unkD;
        f32 unk10[3];
        s32 unk1C;
    } tmp;

    if (arg0 != NULL) {
        tmp.unk0 = arg0;
        tmp.unk4 = arg0[0x3B];
        tmp.unk8 = func_15083E90(1);
        tmp.unkC = 1;
        tmp.unkD = 0;
        bzero(tmp.unk10, 0xC);
        tmp.unk1C = 0;
        temp_v0 = func_151491F4(300, -1, 0x16, 0, 0x12, 0x20, 0xFF, 1);
        if (temp_v0 != NULL) {
            memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x20);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DFE20/func_151B26B0.s")

void func_151B27DC(u8 *);

void func_151B27BC(s32 arg0) {
    func_151B27DC(arg0);
}

void func_151B27DC(u8 *arg0) {
    u8 *base = arg0 + 0x28;
    u8 i;

    for (i = 0; i < 3; i++) {
        struct102 *p = ((struct102 **)(base + 0x10))[i];

        if (p != NULL) {
            func_1516972C(p);
        }
    }
    if (*(struct102 **)(base + 0x1C) != NULL) {
        func_1516972C(*(struct102 **)(base + 0x1C));
    }
}

void func_151B284C(void *arg0) {
    func_151B27BC(arg0);
    func_1514933C(arg0);
}

void func_151B2878(void *arg0) {
    func_151B27BC(arg0);
    func_15149368(arg0);
}

s32 func_151B28A4(u8 *arg0) {
    struct127 *temp_v0 = *(struct127 **)(arg0 + 0x28);
    s32 ret = 2;
    u8 *temp_v1 = *(u8 **)(arg0 + 0x30);

    if (((temp_v0 - D_800CC2D0) + 1 == temp_v1[0x65]) && (*(s32 *)(temp_v1 + 0x5C) == 1)) {
        return 1;
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DFE20/func_151B28F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DFE20/func_151B2C40.s")

void func_151B2F00(struct_eu_1DFE20_d *arg0) {
    struct_eu_1DFE20_c *temp_v0 = arg0->unk178;

    if (temp_v0 != NULL) {
        temp_v0->unk38[arg0->unk17C] = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DFE20/func_151B2F24.s")

void func_151B3474(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}

void func_151B34B4(u8 *arg0, s32 *arg1, u8 arg2)
{
  u8 *v = arg0 + 0x28;
  s32 a;
  s32 b;
  s32 c;
  if (arg2 == 0x2D) {
    a = arg1[0];
    c = *(s32 *)v;
    if (a == c) {
      *(s32 *)v = arg1[1];
      v[4] = ((u8 *)arg1)[9];
    } else if ((b = arg1[1]) == c) {
      *(s32 *)v = a;
      v[4] = ((u8 *)arg1)[8];
    }
    b = arg1[1];
    a = arg1[0];
    c = *(s32 *)(v + 8);
    if (a == c) {
      *(s32 *)(v + 8) = b;
      v[0xC] = ((u8 *)arg1)[9];
      return;
    }
    if (b == c) {
      
      *(s32 *)(v + 8) = a;
      v[0xC] = ((u8 *)arg1)[8];
    }
  }
}

s32 func_151B4D88(void *arg0, void *arg1, s32 arg2, u8 arg3);

void func_151B3550(u8 *arg0, s32 arg1, u8 arg2) {
    func_151B4D88(arg0, arg0 + 0x150, arg1, arg2);
}

void func_151B3580(struct_eu_1DFE20 *arg0) {
    struct_eu_1DFE20_b *temp_v0 = arg0->unk4C;
    if (temp_v0 != NULL) {
        temp_v0->unk44 = 0;
    }
}

void func_151B3598(void *arg0) {
    func_151B3580(arg0);
    func_1514933C(arg0);
}

void func_151B35C4(void *arg0) {
    func_151B3580(arg0);
    func_15149368(arg0);
}

void func_151B35F0(s32 arg0, s32 arg1, u8 arg2) {
    s32 pad;
    s32 temp_a2;

    temp_a2 = arg0 + 0x150;
    func_15169850(arg1, arg2, temp_a2, arg0 + 0x154, arg0);
    func_15169850(arg1, arg2, temp_a2 + 0x14, temp_a2 + 0x18, arg0);
}
