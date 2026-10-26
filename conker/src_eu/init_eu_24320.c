#include <ultra64.h>
#include "functions.h"
#include "variables.h"

OSTime g_os_current_time; /* was D_80042D40 */ // __osCurrentTime (tentative definition: one lui for the u64 store)
extern u32 g_os_base_counter; /* was D_80042D48 */ // __osBaseCounter
extern u32 g_os_vi_intr_count; /* was D_80042D4C */ // __osViIntrCount
extern u32 g_os_timer_counter; /* was D_80042D50 */ // __osTimerCounter
extern OSTimer *g_os_timer_list; /* was D_8002C0C0 */ // __osTimerList
void __osSetTimerIntr(OSTime tim);
void __osSetCompare(u32);
OSTime __osInsertTimer(OSTimer *t);


void __osTimerServicesInit(void) {
    g_os_current_time = 0;
    g_os_base_counter = 0;
    g_os_vi_intr_count = 0;
    g_os_timer_list->prev = g_os_timer_list;
    g_os_timer_list->next = g_os_timer_list->prev;
    g_os_timer_list->value = 0;
    g_os_timer_list->interval = g_os_timer_list->value;
    g_os_timer_list->mq = NULL;
    g_os_timer_list->msg = 0;
}

void __osTimerInterrupt(void) {
    OSTimer *t;
    u32 count;
    u32 elapsed_cycles;

    if (g_os_timer_list->next == g_os_timer_list) {
        return;
    }
    while (1) {
        t = g_os_timer_list->next;
        if (t == g_os_timer_list) {
            __osSetCompare(0);
            g_os_timer_counter = 0;
            break;
        }
        count = osGetCount();
        elapsed_cycles = count - g_os_timer_counter;
        g_os_timer_counter = count;
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
    g_os_timer_counter = osGetCount();
    NewTime = g_os_timer_counter + tim;
    __osSetCompare(NewTime);
    __osRestoreInt(savedMask);
}

OSTime __osInsertTimer(OSTimer *t) {
    OSTimer *timep;
    OSTime tim;
    u32 savedMask;

    savedMask = __osDisableInt();
    for (timep = g_os_timer_list->next, tim = t->value; timep != g_os_timer_list && tim > timep->value;
         tim -= timep->value, timep = timep->next) {
        ;
    }
    t->value = tim;
    if (timep != g_os_timer_list) {
        timep->value -= tim;
    }
    t->next = timep;
    t->prev = timep->prev;
    timep->prev->next = t;
    timep->prev = t;
    __osRestoreInt(savedMask);
    return tim;
}

typedef struct {
    f32 factor;
    u16 offset;
    u32 scale;
} __OSViScale;
typedef struct {
    u16 state;
    u16 retraceCount;
    void *framep;
    OSViMode *modep;
    u32 control;
    OSMesgQueue *msgq;
    OSMesg msg;
    __OSViScale x;
    __OSViScale y;
} __OSViContext;
extern __OSViContext g_os_vi_contexts[2]; /* was D_8002C0D0 */ // vi
extern __OSViContext *g_os_vi_curr; /* was D_8002C130 */ // __osViCurr
extern __OSViContext *g_os_vi_next; /* was D_8002C134 */ // __osViNext
extern u32 g_os_vi_clock; /* was D_8002C138 */ // osViClock
void __osViSwapContext(void);

// __osViInit
/* was func_10024720 */
void os_vi_init(void) {
    bzero(g_os_vi_contexts, sizeof(g_os_vi_contexts));
    g_os_vi_curr = &g_os_vi_contexts[0];
    g_os_vi_next = &g_os_vi_contexts[1];
    g_os_vi_next->retraceCount = 1;
    g_os_vi_curr->retraceCount = 1;
    if (osTvType == OS_TV_PAL) {
        g_os_vi_next->modep = &osViModePalLan1;
        g_os_vi_clock = VI_PAL_CLOCK;
    } else if (osTvType == OS_TV_MPAL) {
        g_os_vi_next->modep = &osViModeMpalLan1;
        g_os_vi_clock = VI_MPAL_CLOCK;
    } else {
        g_os_vi_next->modep = &osViModeNtscLan1;
        g_os_vi_clock = VI_NTSC_CLOCK;
    }
    g_os_vi_next->state = 0x20 /* VI_STATE_BLACK */;
    g_os_vi_next->control = g_os_vi_next->modep->comRegs.ctrl;
    while (IO_READ(VI_CURRENT_REG) > 10) {
    }
    IO_WRITE(VI_CONTROL_REG, 0);
    __osViSwapContext();
}
