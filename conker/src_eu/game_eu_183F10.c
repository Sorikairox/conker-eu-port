#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183F10/func_15156700.s")

s32 func_15156700(s32, u8, s32, u8, s32);
void func_151568F8(s32 arg0, u8 arg1, s32 arg2) {
    func_15156700(arg0, arg1, arg2, 0xFF, 0);
}

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
