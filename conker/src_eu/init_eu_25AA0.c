#include <ultra64.h>
#include "functions.h"
#include "variables.h"

// libultra siacs.c (+ sirawdma.c)
extern u32 D_8002C170;          // __osSiAccessQueueEnabled
extern OSMesg D_80042E30[1];     // siAccessBuf
void __osSiCreateAccessQueue(void);


void __osSiCreateAccessQueue(void) {
    D_8002C170 = 1;
    osCreateMesgQueue(&D_80042E38, D_80042E30, 1);
    osSendMesg(&D_80042E38, NULL, OS_MESG_NOBLOCK);
}

#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_25AA0/__osSiGetAccess.s")

void __osSiRelAccess(void) {
    osSendMesg(&D_80042E38, NULL, OS_MESG_NOBLOCK);
}

#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_25AA0/func_10025B60.s")
