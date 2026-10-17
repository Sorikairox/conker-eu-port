#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern OSTimer *D_8002C0C0; // __osTimerList
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
    if (D_8002C0C0->next == t) {
        __osSetTimerIntr(tim);
    }
    return 0;
}
