#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_15100700(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    func_151494E0(&tmp, 0x48);
}

void func_15100734(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
        s16 unk6;
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk6 = 0;
    temp_v0 = func_15149130(300, -1, 0x4E, -1, 0, 0x3B, 8, 255, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 8);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12DF10/func_151007B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12DF10/func_1510083C.s")
