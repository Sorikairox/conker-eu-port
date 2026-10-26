#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#include "controller.h"


extern OSTimer *g_os_timer_list; /* was D_8002C0C0 */
void __osSetTimerIntr(OSTime tim);
OSTime __osInsertTimer(OSTimer *t);
/* was func_151F0180 */
int game_os_set_timer(OSTimer *t, OSTime value, OSTime interval, OSMesgQueue *mq, OSMesg msg) {
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
