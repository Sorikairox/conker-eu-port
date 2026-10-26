#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern OSThread *__osActiveQueue;
void os_dispatch_thread(void); // __osDispatchThread
void __osDequeueThread(OSThread **, OSThread *);

u8 __osContAddressCrc(u16 addr) {
    u8 temp = 0;
    u8 temp2;
    int i;

    for (i = 0; i < 16; i++) {
        if (temp & 0x10) {
            temp2 = 0x15;
        } else {
            temp2 = 0;
        }
        temp <<= 1;
        temp |= (u8)((addr & 0x400) ? 1 : 0);
        addr <<= 1;
        temp ^= temp2;
    }
    return temp & 0x1F;
}

u8 __osContDataCrc(u8 *data) {
    u8 temp = 0;
    u8 temp2;
    int i;
    int j;

    for (i = 0; i <= 32; i++) {
        for (j = 7; j >= 0; j--) {
            if (temp & 0x80) {
                temp2 = 0x85;
            } else {
                temp2 = 0;
            }
            temp <<= 1;
            if (i == 32) {
                temp |= 0;
            } else {
                temp |= ((*data & (1 << j)) ? 1 : 0);
            }
            temp ^= temp2;
        }
        data++;
    }
    return temp;
}

void osDestroyThread(OSThread *t) {
    register u32 saveMask;
    register OSThread *pred;
    register OSThread *succ;

    saveMask = __osDisableInt();
    if (t == NULL) {
        t = __osRunningThread;
    } else if (t->state != OS_STATE_STOPPED) {
        __osDequeueThread(t->queue, t);
    }
    if (__osActiveQueue == t) {
        __osActiveQueue = __osActiveQueue->tlnext;
    } else {
        pred = __osActiveQueue;
        succ = pred->tlnext;
        while (succ != NULL) {
            if (succ == t) {
                pred->tlnext = t->tlnext;
                break;
            }
            pred = succ;
            succ = pred->tlnext;
        }
    }
    if (t == __osRunningThread) {
        os_dispatch_thread();
    }
    __osRestoreInt(saveMask);
}
