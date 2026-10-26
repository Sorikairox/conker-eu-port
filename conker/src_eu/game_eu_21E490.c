#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#include "controller.h"


extern OSTime g_os_current_time; /* was D_80042D40 */
extern u32 g_os_base_counter; /* was D_80042D48 */
/* was func_151F0C80 */
OSTime game_os_get_time(void) {
    u32 tmptime;
    u32 elapseCount;
    OSTime currentCount;
    register u32 saveMask;

    saveMask = __osDisableInt();
    tmptime = osGetCount();
    elapseCount = tmptime - g_os_base_counter;
    currentCount = g_os_current_time;
    __osRestoreInt(saveMask);
    return currentCount + elapseCount;
}
