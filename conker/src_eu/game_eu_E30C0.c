#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_151D2AB0(s32 arg0);

struct260 *func_150B58B0(u8 *arg0, s16 arg1, u8 arg2, s32 arg3) {
    struct260 *temp_v0;
    struct {
        u8 *unk0;
        u8 unk4;
        f32 unk8;
        f32 unkC;
    } tmp;

    if (arg0 == NULL) {
        return NULL;
    }
    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = 0.0f;
    tmp.unkC = 0.0f;
    temp_v0 = func_15149130((arg1 == -1) ? 300 : arg1, -1, 0x24, -1, (arg1 == -1) ? 0 : 1, 0x23, 0x10, arg2, arg3);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x10);
        func_151D2AB0(6);
    }
    return temp_v0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E30C0/func_150B5988.s")

void func_150B5CA4(void *arg0) {
    func_151D2B4C(6);
}

void func_150B5CC8(void *arg0) {
    func_150B5CA4(arg0);
    func_1514933C(arg0);
}

void func_150B5CF4(void *arg0) {
    func_150B5CA4(arg0);
    func_15149368(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E30C0/func_150B5D20.s")
