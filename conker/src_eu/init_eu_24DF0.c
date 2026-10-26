#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern OSTimer *g_os_timer_list; /* was D_8002C0C0 */ // __osTimerList
void __osSetTimerIntr(OSTime tim);
OSTime __osInsertTimer(OSTimer *t);

int osSetTimer(OSTimer *t, OSTime value, OSTime interval, OSMesgQueue *mq, OSMesg msg) {
    OSTime tim;

    t->next = NULL;
    t->prev = NULL;
    t->interval = interval;
    if (value != 0) {
        t->value = value;
    } else {
        t->value = interval;
    }
    t->mq = mq;
    t->msg = msg;
    tim = __osInsertTimer(t);
    if (g_os_timer_list->next == t) {
        __osSetTimerIntr(tim);
    }
    return 0;
}
