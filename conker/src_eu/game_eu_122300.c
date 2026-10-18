#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_122300/func_150F4AF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_122300/func_150F4E50.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_122300/func_150F4FB8.s")

void func_150F527C(u8 *arg0, s32 arg1, u8 arg2) {
    u8 *v = arg0 + 0x170;

    if (arg2 == 0x4E) {
        arg0[0x71] = 0;
        v[0x24] |= 5;
    } else if (arg2 == 0x4F) {
        func_1516972C(arg0);
    }
}

void func_150F4D5C(u8 *arg0, s8 arg1, u8 arg2, u8 arg3, s32 arg4) {
    struct {
        u8 *unk0;
        f32 unk4;
        s8 unk8;
        u8 unk9;
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = arg0;
    tmp.unk4 = 0.0f;
    tmp.unk8 = arg1;
    tmp.unk9 = arg2;
    temp_v0 = func_15149130(300, -1, 0x56, -1, 0, 0, 0xC, arg3, arg4);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0xC);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_122300/func_150F536C.s")
