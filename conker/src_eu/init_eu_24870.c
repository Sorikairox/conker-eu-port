#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern OSThread *g_os_vi_curr; /* was D_8002C130 */ // really __osViCurr: this is __osViGetCurrentContext, misnamed by the port

OSThread *__osGetActiveQueue(void) {
    return g_os_vi_curr;
}
