#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_1519C7C8(u8 *arg0);


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15195D20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15195D9C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15195DD8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15195EF4.s")

s32 func_15195FF4(s16 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15195AA8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15196270.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15196344.s")

void func_15195FB0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    func_15196344(*(s32 *)(arg0 + 0x1C), arg1, arg2, arg3, arg4, arg5, arg6);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15196560.s")

void func_15196888(u8 *arg0, s32 arg1, s32 arg2) {
    if (arg0 != NULL) {
        arg0[0x12] = arg1;
        arg0[0x13] = arg2;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_151968A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15196924.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15196438.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15196CB8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_151970BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_151976B8.s")

f32 func_15197F68(s32 arg0) {
    return D_800A8E84;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15197F7C.s")

f32 func_15197FD8(s32 arg0) {
    return D_800A8E8C;
}

void func_15197A7C(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
    } sp18;

    if (arg0 != NULL) {
        sp18.unk0 = arg0;
        sp18.unk4 = arg0[0x3B];
        func_151482D4(&sp18, 8);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15198024.s")

typedef struct {
    u8 pad0[0x1C];
    s16 unk1C;
    u8 pad1E[0xE];
    f32 unk2C;
    f32 unk30;
    u8 pad34[0x28];
    u8 unk5C;
    u8 pad5D[0x107];
    f32 unk164;
    s16 unk168;
    s16 unk16A;
} struct_1519812C;

s32 func_1519812C(struct_1519812C *arg0) {
    arg0->unk30 -= arg0->unk30 * arg0->unk164;
    arg0->unk2C -= arg0->unk2C * arg0->unk164;
    if (arg0->unk1C < arg0->unk168) {
        arg0->unk5C = arg0->unk1C * arg0->unk16A;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15198180.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_151985C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15198680.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15198AE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15198D3C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15198EEC.s")

void func_151991D0(void) {
    func_10010F30(0x1AA, 0x7FFF, 0x40, 0, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15199200.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_151992B0.s")

void func_151992EC(s32 arg0) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_151992F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_1519961C.s")

void func_15199924(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);

    arg0[0x30] = 0;
    *(u16 *)(arg0 + 0x1E) &= 0xFFFD;
    temp_v0[6] |= 1;
    temp_v0[6] |= 4;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15199954.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_151999BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15199A28.s")

void func_15199834(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
    } sp18;

    if (arg0 != NULL) {
        sp18.unk0 = arg0;
        sp18.unk4 = arg0[0x3B];
        func_151482D4(&sp18, 0x26);
    }
}

void func_15199DDC(struct102 *arg0, s32 *arg1, u8 arg2) {
    s32 id;
    s32 cur;
    u8 *p = *(u8 **)((u8 *)arg0 + 0x98);
    if (arg2 == 0 || arg2 == 2 || arg2 == 0x26) {
        if (*(s32 *)p == arg1[0] || p[4] == ((u8 *)arg1)[4]) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x2D) {
        if (arg1[0] == *(s32 *)p) {
            *(s32 *)p = arg1[1];
            p[4] = ((u8 *)arg1)[9];
        } else if (arg1[1] == *(s32 *)p) {
            *(s32 *)p = arg1[0];
            p[4] = ((u8 *)arg1)[8];
        }
    }
}

void func_15199E98(void *arg0) {
    func_15199EF0(arg0);
    func_15147E64(arg0);
}

void func_15199EC4(void *arg0) {
    func_15199EF0(arg0);
    func_15147E98(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15199EF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15199F80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_1519A1A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_1519AF14.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_1519BA28.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_1519C38C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_1519C428.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_1519C490.s")

void func_1519C4FC(void) {
    func_10010F30(0x1AA, 0x7FFF, 0x40, 0, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_1519C52C.s")

void func_1519C5DC(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);
    u16 temp_a1 = *(u16 *)(temp_v0 + 0x130);

    if (temp_a1 != 0) {
        func_100111C8(temp_a1);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_1519C60C.s")

void func_1519C770(void *arg0) {
    func_1519C7C8(arg0);
    func_151617C4(arg0);
}

void func_1519C79C(void *arg0) {
    func_1519C7C8(arg0);
    func_151617E4(arg0);
}

void func_1519C7C8(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(*(u8 **)(arg0 + 0x38) + 0x98);
    *(s32 *)(temp_v0 + 0x148) = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_1519C7DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_1519CA54.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_1519CADC.s")

s32 func_1519CE80(u8 *arg0)
{
  u8 *new_var;
  u16 temp_a1;
  u8 *temp_v0;
  temp_v0 = *((u8 **) (((u8 *) arg0) + 0x98));
  new_var = (u8 *) (*((u8 **) (((u8 *) temp_v0) + 0)));
  ;
  if ((*((s32 *) (((u8 *) temp_v0) + 0x158))) != (*((u16 *) (new_var + 0x84))))
  {
    if ((*((s32 *) (((u8 *) temp_v0) + 0x15C))) != (*((u16 *) (new_var + 0x84))))
    {
      return 0;
      return 1;
    }
  }
  return 1;
}

s32 func_1519CEB8(s32 arg0) {
    func_1519D320(arg0, 0.25f, 0x1C);
    return 0;
}

s32 func_1519CEE0(s32 arg0) {
    func_1519D320(arg0, 0.5f, 0x1D);
    return 0;
}

s32 func_1519CF08(s32 arg0) {
    func_1519D320(arg0, 0.2f, 0x1D);
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_1519CF34.s")

void func_1519D2D4(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x28);

    if ((*(s32 *)temp_v0 == 0) || (temp_v0[4] == 0xFF) || (arg0[0x2C] != temp_v0[0x3B])) {
        *(s16 *)(arg0 + 0xE) = -1;
        arg0[0xD] |= 1;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_1519D320.s")
