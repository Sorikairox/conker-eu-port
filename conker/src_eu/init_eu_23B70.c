#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern s32 D_8002C0B0;
extern u8 *D_80042C80;
extern OSMesgQueue D_80042C88;

void func_10023B70(void) {
    D_8002C0B0 = 1;
    osCreateMesgQueue(&D_80042C88, &D_80042C80, 1);
    osSendMesg(&D_80042C88, NULL, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_23B70/func_10023BC0.s")

extern OSMesgQueue D_80042C88;

void func_10023C04(void) {
    osSendMesg(&D_80042C88, NULL, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_23B70/osSetEventMesg.s")
