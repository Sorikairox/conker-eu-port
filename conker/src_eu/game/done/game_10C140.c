#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_150DEC90 */
void level_hook_rain_stop(s32 arg0) {
    rain_update(0);
    D_800DD444 = 0;
}
