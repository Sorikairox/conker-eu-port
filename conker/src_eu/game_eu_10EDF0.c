#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern u8 D_800A13B0[];
u8 *func_151149AC(u8);

struct260 *func_150E15E0(u8 arg0, u8 arg1, s32 arg2) {
    struct260 *temp_v0;
    struct {
        u8 unk0;
        u8 pad1[3];
        u8 *unk4;
        s32 unk8;
        f32 unkC;
    } tmp;

    if ((s32)arg0 < 0) {
        return NULL;
    }
    if (arg0 >= 2) {
        return NULL;
    }
    tmp.unk0 = arg0;
    tmp.unk4 = func_151149AC(D_800A13B0[arg0]);
    if (tmp.unk4 == NULL) {
        return NULL;
    }
    func_1510F800(0);
    tmp.unk8 = func_1510FD20(*(s16 *)(tmp.unk4 + 0x10), *(s16 *)(tmp.unk4 + 0x14));
    tmp.unkC = 0.0f;
    temp_v0 = func_15149130(300, -1, 0x1F, -1, 0, 0x1F, 0x10, arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x10);
    }
    return temp_v0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10EDF0/func_150E16CC.s")
