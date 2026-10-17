#include <ultra64.h>
#include "functions.h"
#include "variables.h"

OSTime D_80042D40;                // __osCurrentTime (tentative definition: one lui for the u64 store)
extern u32 D_80042D48;            // __osBaseCounter
extern u32 D_80042D4C;            // __osViIntrCount
extern u32 D_80042D50;            // __osTimerCounter
extern OSTimer *D_8002C0C0;       // __osTimerList
void __osSetTimerIntr(OSTime tim);
void __osSetCompare(u32);
OSTime __osInsertTimer(OSTimer *t);


void __osTimerServicesInit(void) {
    D_80042D40 = 0;
    D_80042D48 = 0;
    D_80042D4C = 0;
    D_8002C0C0->prev = D_8002C0C0;
    D_8002C0C0->next = D_8002C0C0->prev;
    D_8002C0C0->value = 0;
    D_8002C0C0->interval = D_8002C0C0->value;
    D_8002C0C0->mq = NULL;
    D_8002C0C0->msg = 0;
}

void __osTimerInterrupt(void) {
    OSTimer *t;
    u32 count;
    u32 elapsed_cycles;

    if (D_8002C0C0->next == D_8002C0C0) {
        return;
    }
    while (1) {
        t = D_8002C0C0->next;
        if (t == D_8002C0C0) {
            __osSetCompare(0);
            D_80042D50 = 0;
            break;
        }
        count = osGetCount();
        elapsed_cycles = count - D_80042D50;
        D_80042D50 = count;
        if (elapsed_cycles < t->value) {
            t->value -= elapsed_cycles;
            __osSetTimerIntr(t->value);
            return;
        } else {
            t->prev->next = t->next;
            t->next->prev = t->prev;
            t->next = NULL;
            t->prev = NULL;
            if (t->mq != NULL) {
                osSendMesg(t->mq, t->msg, OS_MESG_NOBLOCK);
            }
            if (t->interval != 0) {
                t->value = t->interval;
                __osInsertTimer(t);
            }
        }
    }
}

void __osSetTimerIntr(OSTime tim) {
    OSTime NewTime;
    u32 savedMask;

    savedMask = __osDisableInt();
    D_80042D50 = osGetCount();
    NewTime = D_80042D50 + tim;
    __osSetCompare(NewTime);
    __osRestoreInt(savedMask);
}

OSTime __osInsertTimer(OSTimer *t) {
    OSTimer *timep;
    OSTime tim;
    u32 savedMask;

    savedMask = __osDisableInt();
    for (timep = D_8002C0C0->next, tim = t->value; timep != D_8002C0C0 && tim > timep->value;
         tim -= timep->value, timep = timep->next) {
        ;
    }
    t->value = tim;
    if (timep != D_8002C0C0) {
        timep->value -= tim;
    }
    t->next = timep;
    t->prev = timep->prev;
    timep->prev->next = t;
    timep->prev = t;
    __osRestoreInt(savedMask);
    return tim;
}

#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_24320/func_10024720.s")
