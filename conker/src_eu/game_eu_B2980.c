#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    /* 0x000 */ u8 pad0[0x11B];
    /* 0x11B */ u8 unk11B;
} struct_eu_B2980_b;

typedef struct {
    /* 0x000 */ u8 pad0[0x31C];
    /* 0x31C */ struct_eu_B2980_b *unk31C;
} struct_eu_B2980;


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B2980/func_15085170.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B2980/func_150851E0.s")

void func_15085880(struct_eu_B2980 *arg0, s32 arg1) {
    arg0->unk31C->unk11B = arg1;
}

u8 func_15085890(struct_eu_B2980 *arg0) {
    return arg0->unk31C->unk11B;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B2980/func_150858A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B2980/func_15085710.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B2980/func_150859AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B2980/func_15085ABC.s")
