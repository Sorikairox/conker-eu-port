#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_150C4BF0 */
void camera_hook_events_f20a0(struct108 *arg0) {
    if (event_dispatch(1, 0x403F, 6, 0x2000)) {
        arg0->unk84 |= 0x1000000;
    } else {
        arg0->unk84 &= 0xFEFFFFFF;
    }
    if (event_dispatch(1, 0x4019, 6, 0x2000)) {
        event_dispatch_alt(1, 0x9000, 0x10, 0xA0);
        return;
    }
    if (event_dispatch(1, 0x4044, 6, 0x2000)) {
        event_dispatch_alt(1, 0x9000, 0x10, 0);
        return;
    }
    if (event_dispatch(4, 0x2000, 0xAC, 0x401B, 0x401C, 0x401D, 0x401E)) {
        event_dispatch_alt(1, 0x9000, 0x10, -0x96);
        return;
    }
    event_dispatch_alt(1, 0x9000, 0x10, 0);
}
