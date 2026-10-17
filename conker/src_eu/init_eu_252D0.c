#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern u32 D_80042D48; // __osBaseCounter
extern OSTime D_80042D40; // __osCurrentTime

OSTime osGetTime(void) {
    u32 tmptime;
    u32 elapseCount;
    OSTime currentCount;
    register u32 saveMask;

    saveMask = __osDisableInt();
    tmptime = osGetCount();
    elapseCount = tmptime - D_80042D48;
    currentCount = D_80042D40;
    __osRestoreInt(saveMask);
    return currentCount + elapseCount;
}
