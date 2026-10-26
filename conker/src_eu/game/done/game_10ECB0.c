#include <ultra64.h>
#include "functions.h"
#include "variables.h"

/* was func_150E1800 */
void camera_hook_event_403e(struct108 *arg0) {
    if (event_dispatch(1, 0x403E, 6, 0x2000) != 0) {
        arg0->unk84 |= 0x20;
        return;
    }
    arg0->unk84 &= ~0x20;
}
