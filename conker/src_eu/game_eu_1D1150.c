#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D1150/func_151A3940.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D1150/func_151A3AB4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D1150/func_151A3BCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D1150/func_151A3D70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D1150/func_151A4194.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D1150/func_151A4B40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D1150/func_151A4BE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D1150/func_151A4DEC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D1150/func_151A4EB0.s")

void func_151A4F4C(u8 *arg0, u8 arg1) {
    struct260 *temp_v0;
    struct {
        u8 *unk0;
        u8 unk4;
        f32 unk8;
        f32 unkC;
        u8 unk10;
        f32 unk14;
        f32 unk18;
        f32 unk1C;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = 0.722f;
    tmp.unkC = 0.0f;
    tmp.unk10 = 1;
    tmp.unk14 = 0.0f;
    tmp.unk18 = 0.0f;
    tmp.unk1C = 0.0f;
    temp_v0 = func_151491F4(300, -1, 5, 0, 1, 0x20, arg1, 0);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x20);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D1150/func_151A4FE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D1150/func_151A5290.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D1150/func_151A5338.s")

s32 func_151A53E4(u8 *arg0, u8 *arg1) {
    s32 temp_v1;
    u32 idx;
    u8 *temp_v0;

    temp_v0 = *(u8 **)arg0;
    temp_v1 = *(s32 *)(temp_v0 + 0x1D4);
    if (temp_v1 == 0) {
        return 0;
    }
    if ((temp_v0[0x74] & 0xF) == 0xF) {
        return 0;
    }
    idx = arg0[5]; // permuter: unsigned local for the index
    func_15143134(arg0 + 8, arg1, temp_v1 + ((idx << 2) << 4));
    return 1;
}

void func_151A544C(u8 *arg0)
{
  u8 *temp_v0;
  temp_v0 = *((u8 **) (arg0 + 0x98));
  arg0[0x30] = 0;
  *((u16 *) (arg0 + 0x1E)) = *((u16 *) (arg0 + 0x1E)) & 0xFFFD;
  temp_v0[0x30] |= 1;
  temp_v0[0x30] |= 4;
}

s32 func_151A3AB4(u8 *, u8, u8 *);

void func_151A547C(u8 *arg0) {
    u8 *temp_v0;
    u8 sp1B;
    u8 *temp_a0;

    sp1B = 0;
    temp_a0 = arg0 + 0x28;
    if (**(s32 **)(arg0 + 0x28) == 0) {
        sp1B = 1;
    }
    temp_v0 = *(u8 **)temp_a0;
    if (temp_a0[4] != temp_v0[0x3B]) {
        sp1B = 1;
    }
    if ((sp1B == 0) && (*(s32 *)(temp_v0 + 0x1D4) != 0) && ((temp_v0[0x74] & 0xF) != 0xF)) {
        sp1B = 1; // permuter: the flag is stored before and after the call
        func_151A3AB4(temp_a0, arg0[0xC], arg0);
        sp1B = 1;
    }
    if (sp1B) {
        *(s16 *)(arg0 + 0xE) = -1;
        arg0[0xD] |= 1;
    }
}

void func_151A552C(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *temp_v0 = (u8 *)arg0 + 0x28;
    if ((arg2 == 0) && ((*(s32 *)temp_v0 == *(s32 *)arg1) || (temp_v0[4] == arg1[4]))) {
        func_1516972C(arg0);
    }
}

void *func_151A5580(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 arg6, s32 arg7) {
    u8 *temp_v0 = func_15167A68(0x5A, 0, arg7 + 0x20, 0, 0xFF, 1);
    if (temp_v0 == NULL) {
        return NULL;
    }
    temp_v0[0x14] = arg0;
    *(s32 *)(temp_v0 + 0x10) = arg1;
    temp_v0[0x15] = arg2;
    temp_v0[0x16] = arg3;
    temp_v0[0x17] = arg4;
    temp_v0[0x19] = arg6;
    temp_v0[0x18] = 0;
    temp_v0[0x1A] = arg5;
    return temp_v0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D1150/func_151A5620.s")

void func_151A56E0(s32 arg0, u8 *arg1, s16 arg2) {
    D_8008FCA0[arg1[0x14]](arg0, arg1, arg2);
}
