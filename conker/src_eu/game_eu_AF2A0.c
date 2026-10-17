#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    /* 0x000 */ u8 pad0[0x1C9];
    /* 0x1C9 */ u8 unk1C9;
    /* 0x1CA */ u8 pad1CA[0xFA];
    /* 0x2C4 */ u8 *unk2C4;
    /* 0x2C8 */ u8 unk2C8;
} struct_eu_AF2A0;


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15081A90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15082020.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_1508220C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15082278.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_150829C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15082D5C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15082DD8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15082E44.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_150836AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15083784.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15083568.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_150836CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15083C3C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15083D54.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15083E20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15083F30.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15084208.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15083E0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15083E90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15083FB0.s")

s32 func_15084000(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    struct127 *temp_v0 = func_1505EEF4(arg0, arg1, arg2, arg3);

    if (temp_v0 != NULL) {
        return temp_v0 - D_800CC2D0;
    }
    return -1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_150844AC.s")

s32 func_15084814(u8 *, s32);

void func_150847B4(u8 *arg0) {
    s32 var_s0;
    u8 var_s1;

    var_s1 = (*(u8 *)((u8 *)arg0 + 0x2C9));
    if (var_s1 == 0) {
        var_s1 = 1;
    }
    var_s0 = 0;
    if ((s32) var_s1 > 0) {
        do {
            func_15084814(arg0, var_s0);
            var_s0 += 1;
        } while (var_s0 != var_s1);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15084814.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_150848F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_150849C0.s")

u8 func_15084E08(struct_eu_AF2A0 *arg0) {
    s32 temp_v1 = arg0->unk1C9;

    if (temp_v1 != 0) {
        return arg0->unk2C4[temp_v1 - 1];
    }
    return arg0->unk2C4[0];
}

u8 func_15084E34(struct_eu_AF2A0 *arg0, s32 *arg1) {
    s32 temp_v1;

    if (arg0->unk1C9 != 0) {
        temp_v1 = arg0->unk1C9 - 1;
    } else {
        temp_v1 = (arg0->unk2C8 != 0) ? arg0->unk2C8 - 1 : 0;
    }
    if (arg1 != NULL) {
        *arg1 = temp_v1;
    }
    return arg0->unk2C4[temp_v1];
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15084E80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15085098.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15085118.s")
