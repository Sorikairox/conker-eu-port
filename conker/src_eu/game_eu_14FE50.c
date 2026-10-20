#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern f32 D_800A3830;
void func_15122EF0(u8 *);
void func_151220D0(u8 *arg0) {
    struct17 tmp;

    if (!(**(u16 **)(arg0 + 0x36C) & 4)) {
        func_15048F90((struct17 *)(arg0 + 0x2F8), (struct17 *)(arg0 + 0x2BC), &tmp);
        tmp.unk0 += *(f32 *)(arg0 + 0x2C8) - *(f32 *)(arg0 + 0x2BC);
        tmp.unk8 += *(f32 *)(arg0 + 0x2D0) - *(f32 *)(arg0 + 0x2C4);
        *(f32 *)(arg0 + 0x37C) = func_15048FC8(&tmp);
        *(f32 *)(arg0 + 0x39C) = *(f32 *)(arg0 + 0x37C) * D_800A3830;
    }
    func_15122EF0(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_14FE50/func_151226E0.s")
