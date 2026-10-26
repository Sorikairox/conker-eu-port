#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15005B70 */
void camera_level_hook07_send_events(s32 arg0) {
    s32 i;

    event_dispatch_alt(0, 0x4014, 0);
    for (i = 0 ; i < 3; i++)
    {
      event_dispatch_alt(0, i + 0x400C, 0);
    }
}
