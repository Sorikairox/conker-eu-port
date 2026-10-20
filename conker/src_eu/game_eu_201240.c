#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D3A30.s")

s32 func_151D4300(u8 *arg0) {
    u8 *v;

    v = arg0 + 0x170;
    if (*(s16 *)(arg0 + 0x170) > 0) {
        *(f32 *)(v + 4) = (*(f32 *)(v + 8) * D_800BE9A4) + *(f32 *)(v + 4);
        *(f32 *)(v + 4) = func_15144B68(*(f32 *)(v + 4));
        *(f32 *)(arg0 + 0x24) = *(f32 *)(arg0 + 0x54) + (*(f32 *)(v + 0xC) * sinf(*(f32 *)(v + 4)));
        *(s16 *)(v + 0) = *(s16 *)(v + 0) - D_800BE9E4;
    } else {
        *(vertex *)(arg0 + 0x20) = *(vertex *)(arg0 + 0x50);
    }
    return 1;
}

void func_151D43B4(s32 arg0, s32 arg1, void *arg2, u8 arg3, f32 arg4) {
    u8 *temp_v0;
    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x1D4));
    if (temp_v0 != 0) {
        func_15143134(arg2, (u8 *) arg1, (u8 *)((s32)temp_v0 + (arg3 << 6)));
        return;
    }
    (*(f32 *)((u8 *)arg1 + 0)) = (f32) (*(f32 *)((u8 *)arg0 + 0x14));
    (*(f32 *)((u8 *)arg1 + 4)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x18)) + arg4);
    (*(f32 *)((u8 *)arg1 + 8)) = (f32) (*(f32 *)((u8 *)arg0 + 0x1C));
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D441C.s")

void func_151D44C4(u8 *arg0, u8 arg1, s32 arg2) {
    s8 sp48[8];
    s32 sp3C[3];

    sp48[0] = 3;
    sp48[1] = -1;
    *(s16 *)(sp48 + 2) = (func_150ADA20() % 3U) + 4;
    sp48[4] = 0;
    sp3C[0] = *(f32 *)(arg0 + 0);
    sp3C[1] = *(f32 *)(arg0 + 4);
    sp3C[2] = *(f32 *)(arg0 + 8);
    func_151602C0(sp48, sp3C, (func_150ADA20() % 13U) + 0x14, 0xFF, 0xE8, 0xAB, 0xFFU, 0U, 0, arg1, arg2);
}

void func_151D45A4(u8 *arg0, u8 arg1, s32 arg2) {
    s8 sp48[8];
    s32 sp3C[3];

    sp48[0] = 3;
    sp48[1] = -1;
    *(s16 *)(sp48 + 2) = (func_150ADA20() % 11U) + 0x14;
    sp48[4] = 0;
    sp3C[0] = *(f32 *)(arg0 + 0);
    sp3C[1] = *(f32 *)(arg0 + 4);
    sp3C[2] = *(f32 *)(arg0 + 8);
    func_151602C0(sp48, sp3C, (func_150ADA20() % 24U) + 0x22, 0xFF, 0xA1, 0xA2, 0xFFU, 0U, 0, arg1, arg2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D4684.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D4898.s")

typedef struct { f32 x, y, z; } V3;

void func_151D49B8(u8 *arg0, u8 *arg1, s32 arg2, u8 *arg3, f32 arg4, u8 arg5, s32 arg6) {
    struct {
        s32 u38[6];
        u8 pad50[0x4];
        f32 u54[5];
        s32 u68[2];
        f32 u70;
        f32 u74;
        f32 u78;
        s32 u7C;
        u8 pad80[0x8];
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        f32 u98;
        f32 u9C;
        f32 uA0;
        s32 uA4;
        s16 uA8;
        s16 uAA;
        s8 uAC;
        u8 padAD[0x3];
        s32 uB0;
        u8 uB4;
        s8 uB5;
        s8 uB6;
        s8 uB7;
        s8 uB8;
        s8 uB9;
        s8 uBA;
        s8 uBB;
        s8 uBC;
        u8 padBD[0x1];
        s8 uBE;
        u8 padBF[0x1];
        u8 *uC0;
        u8 uC4;
        u8 padC5[0x1];
        s16 uC6;
        s16 uC8;
        u8 padCA[0x2];
        s32 uCC;
    } sp;

    func_1503F6F4(arg2, &sp.u38[3], &sp.u38[4], &sp.u38[5], &sp.u54[4], &sp.u68[0], &sp.u68[1], &sp.u38[0], &sp.u38[1], &sp.u38[2]);
    sp.u54[4] += 180.0f;
    {
        f32 temp_f0;

        temp_f0 = func_150ADA68();
        sp.u54[0] = 1.0f;
        sp.u54[1] = 1.0f;
        sp.u70 = 1.0f;
        sp.u74 = 1.0f;
        sp.u78 = 1.0f;
        sp.u54[3] = 0.042000003f * arg4;
        sp.u54[2] = sp.u54[3];
        *(V3 *)&sp.u7C = *(V3 *)arg0;
        arg4 = ((temp_f0 * 105.0f) + 199.0f) * 0.001f;
        sp.u88 = (*(f32 *)((u8 *)arg1 + 0)) * arg4;
        sp.u8C = (*(f32 *)((u8 *)arg1 + 4)) * arg4;
        sp.u90 = (*(f32 *)((u8 *)arg1 + 8)) * arg4;
        sp.u94 = ((func_150ADA68() * 6378.0f) + -3189.0f) * 0.001f;
        sp.u98 = 0.0f;
        sp.u9C = ((func_150ADA68() * 6378.0f) + -3189.0f) * 0.001f;
        sp.uA0 = ((func_150ADA68() * 320.0f) + -707.0f) * 0.001f;
        sp.uA4 = 0x29E8;
        sp.uA8 = (func_150ADA20() & 7) + 0x1C;
        sp.uAA = 0x25;
        sp.uAC = 0;
        sp.uB0 = 0;
        sp.uB4 = 0xFF;
        sp.uB5 = 8;
        sp.uB6 = 0;
        sp.uB7 = 0;
        sp.uB8 = 0;
        sp.uB9 = 0;
        sp.uBA = 0;
        sp.uBB = 0;
        sp.uBC = 2;
        sp.uBE = 1;
        sp.uC0 = arg3;
        sp.uC4 = (*(u8 *)((u8 *)arg3 + 0x3B));
        sp.uC6 = 6;
        sp.uC8 = 0x2A;
        func_15132FBC((u8 *)&sp.u54, 3, 0xFF, 0, (s32) arg5, arg6);
    }
}

void func_151D4668(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    func_151494E0(&tmp, 0x3C);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D469C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D4D44.s")

void func_151D51E8(struct102 *arg0, u8 *arg1, u8 arg2)
{
  u8 *p = (u8 *)arg0 + 0x28;
  if (arg2 == 0x3C) {
    if (*(s32 *)p == *(s32 *)arg1 || p[4] == arg1[4]) {
      func_1516972C(arg0);
    }
  } else if (arg2 == 4) {
    if (*(s32 *)p == *(s32 *)arg1 || p[4] == arg1[4]) {
      u8 *q = p + 0x10; // a declaration in the arm = basic-block boundary (unfilled b delay slot, s69)
      *q &= ~1;
    }
  } else {
    func_15149514((s32)arg1, arg2, (s32)p, (s32)(p + 4), (s32)arg0);
  }
}

s32 func_151D52B4(u8 *arg0, s32 arg1) {
    u8 *p = arg0 + 0xA8;

    func_15131D98(arg0, arg0 + 0xAC, p, arg0 + 0xAA);
    func_15131EC8(arg0 + 0x58, *(s32 *)(p + 0xC));
    return 1;
}

void func_151D5308(s32 arg0) {
    func_151D469C(arg0, 0, 0x50, 0xFF, 1);
    func_151D469C(arg0, 1, 0x50, 0xFF, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D535C.s")

void func_151D56F8(u8 *arg0) {
    if (*(s16 *)(*(u8 **)(arg0 + 0x31C) + 0x24) > 0) {
        *(s16 *)(*(u8 **)(arg0 + 0x31C) + 0x24) -= 1;
    }
    *(s16 *)(*(u8 **)(arg0 + 0x31C) + 0x1AA) += 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D5724.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D58E4.s")

typedef struct {
    struct17 pos;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    u8 unk18;
} Blk_151D5404;
void func_151D5404(struct17 *arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, s16 arg5, s32 arg6, s32 arg7) {
    s32 i;
    Blk_151D5404 sp38;
    structEU_151D8E18 sp30;
    s32 p;

    sp38.pos = *arg0;
    sp38.unkC = arg1;
    sp38.unk10 = arg2;
    sp38.unk14 = arg3;
    sp30.unk0 = 1;
    sp30.unk2 = (func_150ADA20() % (u32) (arg5 + 1)) + arg4;
    sp30.unk4 = 0;
    sp30.unk6 = 0;
    for (i = 0; i < D_80082FA0 + 1; i++) {
        sp30.unk5 = 1 << i;
        sp38.unk18 = i;
        p = func_151D8E18(&sp30, 0x1C, 0xFF, 0);
        if (p != 0) {
            memcpy((u8 *)p + 0x18, &sp38, 0x1C);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D5AC4.s")

void func_15154728(u8 *, f32, s32, f32, f32, u8, s32);
s32 func_151D5AC4(u8 *, u8, s32);

void func_151D5BF8(u8 *arg0, u8 arg1, s32 arg2) {

    func_151D5AC4(arg0, arg1, arg2);
    func_151D45A4(arg0, arg1, arg2);
    func_15154728(arg0, (func_150ADA68() * 4.0f) + 12.0f, 0x3FD20C49, (func_150ADA20() % 56U) + 0xC8, 0.0f, arg1, arg2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D5714.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D5DA8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D5FC8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D611C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D6310.s")

void func_151D5E30(s32 **arg0)
{
  s32 *new_var;
  u8 i;
  for (i = 0; i < 4; i++)
  {
    s32 *t = arg0[i];
    if (1)
    {
    }
    if (t)
    {
      new_var = arg0[i]; // fakematch: re-load of the element after the test
      func_100043B4(new_var, 3);
 } }
}
