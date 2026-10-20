#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19E910/func_15171100.s")

void func_15171434(s32 arg0, u8 arg1, s32 arg2) {
    switch (D_800BE9F0) {
    case 2:
        func_15171100(arg0, 1, 1, 1, arg1, arg2);
        break;
    case 16:
        func_15171100(arg0, 0xA9, 8, 0, arg1, arg2);
        break;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19E910/func_151714BC.s")

void func_15171734(u8 *arg0) {
    if (arg0[4] == 0x33) {
        func_150C3D5C(arg0);
    }
    func_15060F28(arg0, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19E910/func_15171770.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19E910/func_15171B70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19E910/func_15171D6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19E910/func_15171E60.s")

s32 func_150AEEB0(struct127 *, u8);
s32 func_150BDC20(struct127 *, u8, s32);
s32 func_150CE0C0(struct127 *, u8, s32);

void func_15172164(struct127 *arg0, u8 arg1) {
    switch (arg0->id) {
    case 0x13:
    case 0x23:
        func_150AEEB0(arg0, arg1);
        func_10010154(0x69, arg0, 0x7D00, 0xC8, 0x7D0);
        break;
    case 0x1E:
        func_150BDC20(arg0, arg1, 1);
        break;
    case 0x54:
        func_150CE0C0(arg0, arg1, 1);
        break;
    }
}
