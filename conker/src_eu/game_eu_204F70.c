#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_151D7D78(u8 *);


struct260 *func_151D7760(s16 arg0, u8 arg1, u8 arg2, f32 arg3, u8 *arg4, u8 arg5, s32 arg6) {
    struct260 *temp_v0;
    struct {
        s32 unk0;
        u8 unk4;
        u8 unk5;
        u8 pad6[2];
        f32 unk8;
        f32 unkC;
        f32 unk10;
        f32 unk14;
    } tmp;

    tmp.unk0 = 0;
    tmp.unk4 = arg2;
    tmp.unk5 = 0;
    tmp.unk8 = 0.0f;
    tmp.unkC = 0.0f;
    tmp.unk10 = 0.0f;
    tmp.unk14 = arg3;
    temp_v0 = func_15149130(arg0, -1, 0x42, -1, arg1, 0x36, (struct37 *)(arg4 + 0x18), arg5, arg6);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x18);
    }
    return temp_v0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D7814.s")

extern void (*D_80090044[])(u8 *, s32, u8);
void func_151D7958(u8 *arg0, s32 arg1, u8 arg2)
{
  u8 *new_var;
  if (D_80090044[arg0[0x2C]] != 0)
  {
    new_var = &arg0[0x2C]; // fakematch: second index read must not be CSEd
    if (arg1)
    {
    }
    D_80090044[*new_var](arg0, arg1, arg2);
  }
}

void func_151D79B4(void *arg0) {
    func_151D7D78(arg0);
}

void func_151D79D4(void *arg0) {
    func_151D79B4(arg0);
    func_1514933C(arg0);
}

void func_151D7A00(void *arg0) {
    func_151D79B4(arg0);
    func_15149368(arg0);
}

void func_151D7A2C(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    func_151494E0(&tmp, 0x3D);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D7A60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D7AE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D7B74.s")

s32 func_151D7CD4(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x40);
    u8 *temp_v0_2 = arg0 + 0x28;

    if ((*(s32 *)(temp_v0 + 0x94) & 2) || (*(u16 *)(temp_v0 + 0x84) == 4) ||
        (*(u16 *)(temp_v0 + 0x84) == 0xA) || (*(u16 *)(temp_v0 + 0x84) == 0xC)) {
        temp_v0_2[5] &= ~1;
    }
    return 1;
}

s32 func_151D7D20(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x40);
    u8 *temp_v1;
    temp_v1 = arg0 + 0x28;
    if (*(u16 *)(temp_v0 + 0x84) == 0) {
        temp_v1[5] &= ~1;
    }
    return 1;
}

s32 func_151D7D4C(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x40);
    u8 *temp_v1;
    temp_v1 = arg0 + 0x28;
    if (temp_v0[0xAD] != 0) {
        temp_v1[5] &= ~1;
    }
    return 1;
}

void func_151D7D78(u8 *arg0) {
    u8 **v;
    s32 *q;
    v = (u8 **)(arg0 + 0x28);
    if (*(s32 *)(arg0 + 0x28) != 0) {
        q = *(s32 **)(*v + 0x98);
        *(s8 *)(*v + 0x30) = 0;
        *(u16 *)(*v + 0x1E) &= 0xFFFD;
        *(u16 *)(*v + 0x1E) |= 8;
        *(u16 *)(*v + 0x1E) |= 1;
        *(s16 *)(*v + 0x1C) = 0x14;
        *q = 0;
        *v = NULL;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D7DE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D7EDC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D7FE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D8280.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D8674.s")

void func_151D8CC8(f32 *arg0, f32 *arg1, f32 arg2) {
    f32 temp_f2 = *arg1;

    *arg1 += D_800AB6CC * arg2;
    arg0[1] += (temp_f2 * arg2) + (D_800AB6D0 * (arg2 * arg2));
}

void func_151D8D14(u8 *arg0) {
    s32 **temp_v0 = *(s32 ***)(arg0 + 0x98);
    s32 *temp_v1 = *temp_v0;
    if (temp_v1 != NULL) {
        temp_v1[0x28 / 4] = 0;
    }
}

void func_151D8D30(void *arg0) {
    func_151D8D14(arg0);
    func_15147E64(arg0);
}

void func_151D8D5C(void *arg0) {
    func_151D8D14(arg0);
    func_15147E98(arg0);
}
