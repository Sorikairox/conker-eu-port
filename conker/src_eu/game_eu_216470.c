#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151E8C60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151E8620.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151E8E94.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151E9150.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151E9E1C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EA4C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EA90C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EB5AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EB81C.s")

s32 func_151EC0E0(s32 arg0) {
    if (D_8009016C != 0) {
        arg0 = func_151EA90C(arg0, 0x6A, D_8009016C, 0);
    }
    return arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EC11C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EC300.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EC928.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EC9A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151ECB98.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151ECE00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151ED854.s")

u8 *func_1501A6CC(u8 *, s32, s32, s32, s32);
Gfx *func_151ED998(Gfx *gdl) {
    if ((u8)D_800E0FC6 == 0) {
        return gdl;
    }
    gDPPipeSync(gdl++);
    gDPSetOtherMode(gdl++, 0x082C3F, 0x504340);
    gDPSetCombine(gdl++, 0xFFFFFF, 0xFFFEFB7D);
    gDPSetEnvColor(gdl++, 0, 0, 0, (u8)D_800E0FC6);
    return (Gfx *)func_1501A6CC((u8 *)gdl, 0, 0, D_800BE620, D_800BE624);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EDA54.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EDBE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EE0C4.s")

void func_151EE310(u8 *arg0) {
    s32 i;

    if (arg0 != NULL) {
        func_1503FAA8(*(s32 *)(arg0 + 0x24));
        func_100043B4(arg0, 4);
        for (i = 0; i < arg0[0x14]; i++) {
            func_100043B4(((s32 **)(arg0 + 4))[i], 4);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EE394.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EE704.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EE93C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EF3A0.s")
