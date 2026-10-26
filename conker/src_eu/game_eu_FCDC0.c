#include <ultra64.h>
#include "functions.h"
#include "variables.h"


u8 * world_record_find(u8);
s32 scenery_pendulum_z_update();
/* was func_150CF5B0 */
void scenery_pendulum_trigger_update(u8 *arg0) {
    u8 *p;
    if ((arg0[0x73] & 3) != 2) {
        if ((arg0[0x4F] & 4) && ((u8 *)g_obj0_state)[0x57] != 0) {
            p = world_record_find(0xFE);
            p[0x73] &= 0xFFFC;
            p[0x73] |= 2;
            p = world_record_find(0xFD);
            p[0x73] &= 0xFFFC;
            p[0x73] |= 2;
        }
    } else {
        scenery_pendulum_z_update(arg0);
    }
}
