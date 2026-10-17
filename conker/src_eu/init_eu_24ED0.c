#include <ultra64.h>
#include "functions.h"
#include "variables.h"


u32 __osSpGetStatus(void);
void __osSpSetStatus(u32);

OSYieldResult osSpTaskYielded(OSTask *tp) {
    s32 status;
    OSYieldResult result;

    status = __osSpGetStatus();
    if (status & SP_STATUS_YIELDED) {
        result = OS_TASK_YIELDED;
    } else {
        result = 0;
    }
    if (status & SP_STATUS_YIELD) {
        tp->t.flags |= result;
        tp->t.flags &= ~OS_TASK_DP_WAIT;
    }
    return result;
}

void osSpTaskYield(void) {
    __osSpSetStatus(SP_SET_YIELD);
}

#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_24ED0/osContStartReadData.s")

#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_24ED0/osContGetReadData.s")

#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_24ED0/contreaddata_text_017C.s")
