#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183F10/func_15156700.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183F10/func_151568F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183F10/func_15156928.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183F10/func_15156A68.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183F10/func_15156E68.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183F10/func_151570C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183F10/func_15157294.s")

void func_15157504(s32 arg0) {
    func_151D5E30(arg0 + 0x88, arg0);
}

void func_15157528(struct102 *arg0) {
    func_15157504(arg0);
    func_15169804(arg0);
}

void func_15157554(struct102 *arg0) {
    func_15157504(arg0);
    func_15169824(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183F10/func_15157580.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183F10/func_15157734.s")

void func_151577B8(struct102 *arg0) {
    func_15157734(arg0);
    func_1518CF74(*(s32 *)((u8 *)arg0 + 0x18));
    func_1503FAA8(*(s32 *)((u8 *)arg0 + 0x68));
    func_15169804(arg0);
}

void func_151577FC(struct102 *arg0) {
    func_15157734(arg0);
    func_1518CF74(*(s32 *)((u8 *)arg0 + 0x18));
    func_1503FAA8(*(s32 *)((u8 *)arg0 + 0x68));
    func_15169824(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183F10/func_15157840.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183F10/func_15157990.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183F10/func_15157DD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183F10/func_15157E08.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183F10/func_15157E88.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183F10/func_15158018.s")

void func_151582F8(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x4C, arg0 + 0x50, arg0);
}

s32 func_15158338(s32 arg0) {
    func_1515835C(arg0, arg0 + 0x120);
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183F10/func_1515835C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183F10/func_151584F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183F10/func_15158558.s")

void func_151585E8(s32 arg0, u8 arg1) {
    func_15169260(D_800A6440, 3, arg0, arg1);
}
