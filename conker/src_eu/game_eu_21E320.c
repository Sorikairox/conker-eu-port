#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern s32 D_8002C170;
extern u8 *D_800E1150;

void func_151F0B10(void) {
    D_8002C170 = 1;
    osCreateMesgQueue(&D_80042E38, &D_800E1150, 1);
    osSendMesg(&D_80042E38, NULL, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_21E320/func_151F0B60.s")

void func_151F0BA4(void) {
    osSendMesg(&D_80042E38, NULL, OS_MESG_NOBLOCK);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_21E320/func_151F0BD0.s")
