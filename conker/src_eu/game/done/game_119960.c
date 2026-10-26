#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_150EC4B0 */
void camera_hook_event_4023(struct108 *arg0) {
    if (event_dispatch(1, 0x4023, 6, 0x2000) != 0) {
        arg0->unk84 |= 0x1010;
    } else {
        arg0->unk84 &= ~0x1010;
    }
    arg0->unk84 &= ~8;
}
