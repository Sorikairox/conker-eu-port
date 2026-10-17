#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ u8 unk2;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ s32 unk8;
} struct_eu_158110;


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512A390.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512B168.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512B2C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512B670.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512B728.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512BAAC.s")

void func_1512BB6C(struct_eu_158110 *arg0, s32 arg1, s32 arg2) {
    arg0->unk2 = arg0->unk1;
    if (arg0->unk4 < arg1) {
        arg0->unk1 = 0;
    } else {
        arg0->unk1 = 1;
    }
    arg0->unk8 = arg2;
    arg0->unk4 = arg1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512BBA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512BCA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512C080.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512C5D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512C6C0.s")

void func_1512C770(s32 arg0) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512C77C.s")

s32 func_1512C9EC(s32 arg0) {
    return 1;
}
